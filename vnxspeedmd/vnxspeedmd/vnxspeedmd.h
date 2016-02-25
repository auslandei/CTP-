//˵������

//ϵͳ
#include "stdafx.h"
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python��װ
#include <boost/python/def.hpp>		//python��װ
#include <boost/python/dict.hpp>	//python��װ
#include <boost/python/object.hpp>	//python��װ
#include <boost/python.hpp>			//python��װ
#include <boost/thread.hpp>			//������е��̹߳���
#include <boost/bind.hpp>			//������е��̹߳���
#include <boost/any.hpp>			//������е�����ʵ��

//API
#include "DFITCMdApi.h"

//�����ռ�
using namespace std;
using namespace boost::python;
using namespace boost;
using namespace DFITCXSPEEDMDAPI;

//����
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONRSPERROR 5
#define ONRSPSUBMARKETDATA 6
#define ONRSPUNSUBMARKETDATA 7
#define ONRSPSUBFORQUOTERSP 8
#define ONRSPUNSUBFORQUOTERSP 9
#define ONMARKETDATA 10
#define ONCUSTOMMARKETDATA 11
#define ONRTNFORQUOTERSP 12
#define ONRSPTRADINGDAY 13
#define EXIT 0


///-------------------------------------------------------------------------------------
///API�еĲ������
///-------------------------------------------------------------------------------------

//GILȫ�����򻯻�ȡ�ã�
//���ڰ���C++�̻߳��GIL�����Ӷ���ֹpython����
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//��ĳ�����������д����ö���ʱ�����GIL��
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//��ĳ��������ɺ����ٸö���ʱ�����GIL��
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};


//����ṹ��
struct Task
{
	int task_name;		//�ص��������ƶ�Ӧ�ĳ���
	any task_data;		//���ݽṹ��
	any task_error;		//����ṹ��
	int task_id;		//����id
	bool task_last;		//�Ƿ�Ϊ��󷵻�
};


///�̰߳�ȫ�Ķ���
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//��׼�����
	mutable mutex the_mutex;							//boost������
	condition_variable the_condition_variable;			//boost��������

public:

	//�����µ�����
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				//��ȡ������
		the_queue.push(data);							//������д�������
		lock.unlock();									//�ͷ���
		the_condition_variable.notify_one();			//֪ͨ���������ȴ����߳�
	}

	//�������Ƿ�Ϊ��
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//ȡ��
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//������Ϊ��ʱ
		{
			the_condition_variable.wait(lock);			//�ȴ���������֪ͨ
		}

		Data popped_value = the_queue.front();			//��ȡ�����е����һ������
		the_queue.pop();								//ɾ��������
		return popped_value;							//���ظ�����
	}

};


//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getInt(dict d, string key, int* value);


//���ֵ��л�ȡĳ����ֵ��Ӧ�ĸ�����������ֵ������ṹ������ֵ��
void getDouble(dict d, string key, double* value);


//���ֵ��л�ȡĳ����ֵ��Ӧ�ĵ��ַ�������ֵ������ṹ������ֵ��
void getChar(dict d, string key, char* value);


//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ���������ֵ������ṹ������ֵ��
void getString(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class MdApi : public DFITCMdSpi
{
private:
	DFITCMdApi* api;			//API����
	thread *task_thread;				//�����߳�ָ�루��python���������ݣ�
	ConcurrentQueue<Task> task_queue;	//�������

public:
	MdApi()
	{
		function0<void> f = boost::bind(&MdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~MdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API�ص�����
	//-------------------------------------------------------------------------------------

		/**
		* ��������������Ӧ
		*/
		virtual void OnFrontConnected();

		/**
		* �������Ӳ�������Ӧ
		*/
		virtual void OnFrontDisconnected(int nReason);

		/**
		* ��½������Ӧ:���û�������¼�����ǰ�û�������Ӧʱ�˷����ᱻ���ã�֪ͨ�û���¼�Ƿ�ɹ���
		* @param pRspUserLogin:�û���¼��Ϣ�ṹ��ַ��
		* @param pRspInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
		*/
		virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pRspUserLogin, struct DFITCErrorRtnField * pRspInfo);

		/**
		* �ǳ�������Ӧ:���û������˳������ǰ�û�������Ӧ�˷����ᱻ���ã�֪ͨ�û��˳�״̬��
		* @param pRspUsrLogout:�����û��˳���Ϣ�ṹ��ַ��
		* @param pRspInfo:������ʧ�ܣ����ش�����Ϣ��ַ��
		*/
		virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo);

		/**
		* ����Ӧ��
		* @param pRspInfo:������Ϣ��ַ��
		*/
		virtual void OnRspError(struct DFITCErrorRtnField *pRspInfo);

		/**
		* ���鶩��Ӧ��:���û��������鶩�ĸ÷����ᱻ���á�
		* @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
		* @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
		*/
		virtual void OnRspSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* ȡ����������Ӧ��:���û������˶������÷����ᱻ���á�
		* @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
		* @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
		*/
		virtual void OnRspUnSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* ����ѯ��Ӧ��
		* @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
		* @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
		*/
		virtual void OnRspSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* ȡ������ѯ��Ӧ��
		* @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
		* @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
		*/
		virtual void OnRspUnSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo);

		/**
		* ������ϢӦ��:�����������ɹ��������鷵��ʱ���÷����ᱻ���á�
		* @param pMarketDataField:ָ��������Ϣ�ṹ��ָ�룬�ṹ���а��������������Ϣ��
		*/
		virtual void OnMarketData(struct DFITCDepthMarketDataField * pMarketDataField);

		/**
		* �Զ������������ϢӦ��:�����������ɹ��������鷵��ʱ���÷����ᱻ���á�
		* @param pMarketDataField:ָ��������Ϣ�ṹ��ָ�룬�ṹ���а��������������Ϣ��
		*/
		virtual void OnCustomMarketData(struct DFITCCustomMarketDataField * pMarketDataField);

		/**
		* ѯ��֪ͨ
		* @param pForQuoteField:ָ��ѯ����Ϣ�ṹ��ָ�룬�ṹ���а��������ѯ����Ϣ��
		*/
		virtual void OnRtnForQuoteRsp(struct DFITCQuoteSubscribeRtnField * pForQuoteField);

		/**
		* ������ȷ����Ӧ:���ڽ��ս�������Ϣ��
		* @param pTradingDayRtnData: ���ؽ���������ȷ����Ӧ�ṹ�ĵ�ַ��
		*/
		virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);


	//-------------------------------------------------------------------------------------
	//task������
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspError(Task task);

	void processRspSubMarketData(Task task);

	void processRspUnSubMarketData(Task task);

	void processRspSubForQuoteRsp(Task task);

	void processRspUnSubForQuoteRsp(Task task);

	void processMarketData(Task task);

	void processCustomMarketData(Task task);

	void processRtnForQuoteRsp(Task task);

	void processRspTradingDay(Task task);

	//-------------------------------------------------------------------------------------
	//data���ص������������ֵ�
	//error���ص������Ĵ����ֵ�
	//id������id
	//last���Ƿ�Ϊ��󷵻�
	//i������
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onRspUserLogin(dict data, dict error) {};

	virtual void onRspUserLogout(dict data, dict error) {};

	virtual void onRspError(dict error) {};

	virtual void onRspSubMarketData(dict data, dict error) {};

	virtual void onRspUnSubMarketData(dict data, dict error) {};

	virtual void onRspSubForQuoteRsp(dict data, dict error) {};

	virtual void onRspUnSubForQuoteRsp(dict data, dict error) {};

	virtual void onMarketData(dict data) {};

	virtual void onCustomMarketData(dict data) {};

	virtual void onRtnForQuoteRsp(dict data) {};

	virtual void onRspTradingDay(dict data) {};

	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createDFITCMdApi();

	void release();

	void init(string pszSvrAddr);

	int exit();
	
	int subscribeMarketData(string instrumentID, int nRequestID);

	int unSubscribeMarketData(string instrumentID, int nRequestID);

	int subscribeForQuoteRsp(string instrumentID, int nRequestID);

	int unSubscribeForQuoteRsp(string instrumentID, int nRequestID);

	int reqUserLogin(dict req);

	int reqUserLogout(dict req);

	int reqTradingDay(dict req);
};
