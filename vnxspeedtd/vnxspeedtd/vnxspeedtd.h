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
#include "DFITCTraderApi.h"

//�����ռ�
using namespace std;
using namespace boost::python;
using namespace boost;
using namespace DFITCXSPEEDAPI;

//����
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONRSPINSERTORDER 5
#define ONRSPCANCELORDER 6
#define ONRTNERRORMSG 7
#define ONRTNMATCHEDINFO 8
#define ONRTNORDER 9
#define ONRTNCANCELORDER 10
#define ONRSPQRYORDERINFO 11
#define ONRSPQRYMATCHINFO 12
#define ONRSPQRYPOSITION 13
#define ONRSPCUSTOMERCAPITAL 14
#define ONRSPQRYEXCHANGEINSTRUMENT 15
#define ONRSPARBITRAGEINSTRUMENT 16
#define ONRSPQRYSPECIFYINSTRUMENT 17
#define ONRSPQRYPOSITIONDETAIL 18
#define ONRTNTRADINGNOTICE 19
#define ONRSPRESETPASSWORD 20
#define ONRSPQRYTRADECODE 21
#define ONRSPBILLCONFIRM 22
#define ONRSPEQUITYCOMPUTMODE 23
#define ONRSPQRYBILL 24
#define ONRSPCONFIRMPRODUCTINFO 25
#define ONRSPTRADINGDAY 26
#define ONRSPQUOTEINSERT 27
#define ONRTNQUOTEINSERT 28
#define ONRSPQUOTECANCEL 29
#define ONRTNQUOTECANCEL 30
#define ONRTNQUOTEMATCHEDINFO 31
#define ONRSPCANCELALLORDER 32
#define ONRSPQRYQUOTENOTICE 33
#define ONRSPFORQUOTE 34
#define ONRTNFORQUOTE 35
#define ONRSPQRYQUOTEORDERINFO 36
#define ONRSPQRYFORQUOTE 37
#define ONRSPQRYTRANSFERBANK 38
#define ONRSPQRYTRANSFERSERIAL 39
#define ONRSPFROMBANKTOFUTUREBYFUTURE 40
#define ONRSPFROMFUTURETOBANKBYFUTURE 41
#define ONRTNFROMBANKTOFUTUREBYFUTURE 42
#define ONRTNFROMFUTURETOBANKBYFUTURE 43
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 44
#define ONRSPQRYEXCHANGESTATUS 45
#define ONRTNEXCHANGESTATUS 46
#define ONRSPQRYDEPTHMARKETDATA 47

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

//���ֵ��л�ȡĳ����ֵ��Ӧ�ĳ�����������ֵ������ṹ������ֵ��
void getLong(dict d, string key, long* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ�Ķ�����������ֵ������ṹ������ֵ��
void getShort(dict d, string key, short* value);


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
class TdApi : public DFITCTraderSpi
{
private:
	DFITCTraderApi* api;			//API����
	thread *task_thread;				//�����߳�ָ�루��python���������ݣ�
	ConcurrentQueue<Task> task_queue;	//�������

public:
	TdApi()
	{
		function0<void> f = boost::bind(&TdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~TdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API�ص�����
	//-------------------------------------------------------------------------------------

	/* ��������������Ӧ:���ͻ����뽻�׺�̨�轨����ͨ������ʱ����δ��¼ǰ�����ͻ���API���Զ������ǰ�û�֮������ӣ�
	* ��������ã����Զ��������ӣ������ø÷���֪ͨ�ͻ��ˣ� �ͻ��˿�����ʵ�ָ÷���ʱ������ʹ���ʽ��˺Ž��е�¼��
	*���÷�������Api��ǰ�û��������Ӻ󱻵��ã��õ��ý�����˵��tcp�����Ѿ������ɹ����û���Ҫ���е�¼���ܽ��к�����ҵ�������
	*  ��¼ʧ����˷������ᱻ���á���
	*/
	virtual void OnFrontConnected();

	/**
	* �������Ӳ�������Ӧ�����ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	* @param  nReason:����ԭ��
	*        0x1001 �����ʧ��
	*        0x1002 ����дʧ��
	*        0x2001 ����������ʱ
	*        0x2002 ��������ʧ��
	*        0x2003 �յ�������
	*/
	virtual void OnFrontDisconnected(int nReason);
	/**
	* ��½������Ӧ:���û�������¼�����ǰ�û�������Ӧʱ�˷����ᱻ���ã�֪ͨ�û���¼�Ƿ�ɹ���
	* @param pUserLoginInfoRtn:�û���¼��Ϣ�ṹ��ַ��
	* @param pErrorInfo:����¼ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pUserLoginInfoRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* �ǳ�������Ӧ:���û������˳������ǰ�û�������Ӧ�˷����ᱻ���ã�֪ͨ�û��˳�״̬��
	* @param pUserLogoutInfoRtn:�����û��˳���Ϣ�ṹ��ַ��
	* @param pErrorInfo:���ǳ�ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* �ڻ�ί�б�����Ӧ:���û�¼�뱨����ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pOrderRtn:�����û��µ���Ϣ�ṹ��ַ��
	* @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* �ڻ�ί�г�����Ӧ:���û�������ǰ�÷�����Ӧ�Ǹ÷����ᱻ���á�
	* @param pOrderCanceledRtn:���س�����Ӧ��Ϣ�ṹ��ַ��
	* @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspCancelOrder(struct DFITCOrderRspDataRtnField * pOrderCanceledRtn, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* ����ر�
	* @param pErrorInfo:������Ϣ�Ľṹ��ַ��
	*/
	virtual void OnRtnErrorMsg(struct DFITCErrorRtnField * pErrorInfo);

	/**
	* �ɽ��ر�:��ί�гɹ����׺�η����ᱻ���á�
	* @param pRtnMatchData:ָ��ɽ��ر��Ľṹ��ָ�롣
	*/
	virtual void OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData);

	/**
	* ί�лر�:�µ�ί�гɹ��󣬴˷����ᱻ���á�
	* @param pRtnOrderData:ָ��ί�лر���ַ��ָ�롣
	*/
	virtual void OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData);

	/**
	* �����ر�:�������ɹ���÷����ᱻ���á�
	* @param pCancelOrderData:ָ�򳷵��ر��ṹ�ĵ�ַ���ýṹ�������������Լ�������Ϣ��
	*/
	virtual void OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData);

	/**
	* ��ѯ����ί����Ӧ:���û�����ί�в�ѯ�󣬸÷����ᱻ���á�
	* @param pRtnOrderData:ָ��ί�лر��ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ��ѯ���ճɽ���Ӧ:���û������ɽ���ѯ��÷����ᱻ���á�
	* @param pRtnMatchData:ָ��ɽ��ر��ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* �ֲֲ�ѯ��Ӧ:���û������ֲֲ�ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pPositionInfoRtn:���سֲ���Ϣ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* �ͻ��ʽ��ѯ��Ӧ:���û������ʽ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pCapitalInfoRtn:�����ʽ���Ϣ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ��������Լ��ѯ��Ӧ:���û�������Լ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pInstrumentData:���غ�Լ��Ϣ�ṹ�ĵ�ַ��
	* @param pErrorInfo:������Ϣ�ṹ�������ѯ���������򷵻ش�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ������Լ��ѯ��Ӧ:���û�����������Լ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pAbiInstrumentData:����������Լ��Ϣ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ��ѯָ����Լ��Ӧ:���û�����ָ����Լ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pInstrument:����ָ����Լ��Ϣ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ��ѯ�ֲ���ϸ��Ӧ:���û�������ѯ�ֲ���ϸ��ǰ�÷�����Ӧʱ�÷����ᱻ���á�
	* @param pPositionDetailRtn:���سֲ���ϸ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ����֪ͨ��Ӧ:���ڽ���XSPEED��̨�ֶ�����֪ͨ����֧��ָ���ͻ���Ҳ֧��ϵͳ�㲥��
	* @param pTradingNoticeInfo: �����û��¼�֪ͨ�ṹ�ĵ�ַ��
	*/
	virtual void OnRtnTradingNotice(struct DFITCTradingNoticeInfoField * pTradingNoticeInfo);

	/**
	* �����޸���Ӧ:�����޸��ʽ��˻���¼���롣
	* @param pResetPassword: ���������޸Ľṹ�ĵ�ַ��
	* @param pErrorInfo:���޸�����ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* ���ױ����ѯ��Ӧ:���ؽ��ױ�����Ϣ
	* @param pTradeCode: ���ؽ��ױ����ѯ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* �˵�ȷ����Ӧ:���ڽ��տͻ��˵�ȷ��״̬��
	* @param pBillConfirm: �����˵�ȷ�Ͻṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* ��ѯ�ͻ�Ȩ����㷽ʽ��Ӧ:���ؿͻ�Ȩ�����ķ�ʽ
	* @param pEquityComputMode: ���ؿͻ�Ȩ����㷽ʽ�ṹ�ĵ�ַ��
	*/
	virtual void OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode);

	/**
	* �ͻ������˵���ѯ��Ӧ:�����˵���Ϣ
	* @param pQryBill: ���ؿͻ������˵���ѯ�ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryBill(struct DFITCQryBillRtnField *pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ����IDȷ����Ӧ:���ڽ��ճ�����Ϣ��
	* @param pProductRtnData: ���س���IDȷ����Ӧ�ṹ�ĵ�ַ��
	*/
	virtual void OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData);


	/**
	* ������ȷ����Ӧ:���ڽ��ս�������Ϣ��
	* @param DFITCTradingDayRtnField: ���ؽ���������ȷ����Ӧ�ṹ�ĵ�ַ��
	*/
	virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData);

	/**
	* �����̱�����Ӧ
	* @param pRspQuoteData:ָ�������̱�����Ӧ��ַ��ָ�롣
	* @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspQuoteInsert(struct DFITCQuoteRspField * pRspQuoteData, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* �����̱����ر�
	* @param pRtnQuoteData:ָ�������̱����ر���ַ��ָ�롣
	*/
	virtual void OnRtnQuoteInsert(struct DFITCQuoteRtnField * pRtnQuoteData);

	/**
	* �����̳�����Ӧ
	* @param pRspQuoteCanceledData:ָ�������̳�����Ӧ��ַ��ָ�롣
	* @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspQuoteCancel(struct DFITCQuoteRspField * pRspQuoteCanceledData, struct DFITCErrorRtnField * pErrorInfo)  ;

	/**
	* �����̳����ر�
	* @param pRtnQuoteCanceledData:ָ�������̳����ر���ַ��ָ�롣
	*/
	virtual void OnRtnQuoteCancel(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData) ;

	/**
	* �����̳ɽ��ر�
	* @param pRtnQuoteMatchedData:ָ�������̳ɽ��ر���ַ��ָ�롣
	*/
	virtual void OnRtnQuoteMatchedInfo(struct DFITCQuoteMatchRtnField * pRtnQuoteMatchedData) ;

	/**
	* ����������Ӧ
	* @param pRspStripCancelOrderData:ָ������������Ӧ��ַ��ָ�롣
	* @param pErrorInfo:����������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspCancelAllOrder(struct DFITCCancelAllOrderRspField *pRspCancelAllOrderData, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* ѯ��֪ͨ��ѯ��Ӧ
	* @param pRtnQryQuoteNoticeData:��ѯѯ��֪ͨ�ر��ṹ��ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryQuoteNotice(struct DFITCQryQuoteNoticeRtnField * pRtnQryQuoteNoticeData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ѯ����Ӧ
	* @param pRspForQuoteData:ѯ��������Ӧ�ṹ��ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspForQuote(struct DFITCForQuoteRspField * pRspForQuoteData, struct DFITCErrorRtnField * pErrorInfo);

	/**
	* ѯ�ۻر�
	* @param pRtnForQuoteData:ѯ�ۻر��ṹ��ַ��
	*/
	virtual void OnRtnForQuote(struct DFITCForQuoteRtnField * pRtnForQuoteData);

	/**
	* ��ѯ���ձ���ί����Ӧ
	* @param pRtnQuoteOrderData:ָ�򱨼۲�ѯ�ر��ṹ�ĵ�ַ��
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryQuoteOrderInfo(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ѯ��ί�в�ѯ��Ӧ
	* @param pRtnQryForQuoteData:ָ��ѯ��ί�в�ѯ��Ӧ��ַ��ָ�롣
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryForQuote(struct DFITCQryForQuoteRtnField * pRtnQryForQuoteData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	/**
	* ��ѯת��������Ӧ
	* @param pTransferBank:ָ���ѯת�����лر���ַ��ָ�롣
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryTransferBank(struct DFITCTransferBankRspField * pTransferBank, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) ;

	/**
	* ��ѯת����ˮ��Ӧ
	* @param pTransferSerial:ָ���ѯת����ˮ�ر���ַ��ָ�롣
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryTransferSerial(struct DFITCTransferSerialRspField * pTransferSerial, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) ;

	/**
	* �ڻ����������ʽ�ת�ڻ�Ӧ��
	* @param pRspTransfer:ָ���ڻ����������ʽ�ת�ڻ�Ӧ���ַ��ָ�롣
	* @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspFromBankToFutureByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* �ڻ������ڻ��ʽ�ת����Ӧ��
	* @param pRspTransfer:ָ���ڻ������ڻ��ʽ�ת����Ӧ���ַ��ָ�롣
	* @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRspFromFutureToBankByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* �ڻ����������ʽ�ת�ڻ�֪ͨ
	* @param pRtnTransfer:ָ���ڻ����������ʽ�ת�ڻ�֪ͨ��ַ��ָ�롣
	* @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRtnFromBankToFutureByFuture(DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* �ڻ������ڻ��ʽ�ת����֪ͨ
	* @param pRtnTransfer:ָ���ڻ������ڻ��ʽ�ת����֪ͨ��ַ��ָ�롣
	* @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	*/
	virtual void OnRtnFromFutureToBankByFuture(DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) ;

	/**
	* ���з�������ڻ�ת����֪ͨ
	* @param pRspRepeal:ָ���ڻ������ڻ��ʽ�ת���г���֪ͨ��ַ��ָ�롣
	*/
	virtual void OnRtnRepealFromFutureToBankByBank(DFITCRepealRtnField * pRspRepeal) ;

	/**
	* ������״̬��ѯ��Ӧ
	* @param pRspExchangeStatusData:ָ������״̬��ѯ��Ӧ��ַ��ָ�롣
	*/
	virtual void OnRspQryExchangeStatus(struct DFITCExchangeStatusRspField * pRspExchangeStatusData);

	/**
	* ������״̬֪ͨ
	* @param pRtnExchangeStatusData:ָ������״̬֪ͨ��ַ��ָ�롣
	*/
	virtual void OnRtnExchangeStatus(struct DFITCExchangeStatusRtnField * pRtnExchangeStatusData);

	/**
	* �����ѯ��Ӧ
	* @param pDepthMarketData:ָ�������ѯ��Ӧ��ַ��ָ�롣
	* @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
	* @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
	*/
	virtual void OnRspQryDepthMarketData(struct DFITCDepthMarketDataField * pDepthMarketData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast);

	//-------------------------------------------------------------------------------------
	//task������
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspInsertOrder(Task task);

	void processRspCancelOrder(Task task);

	void processRtnErrorMsg(Task task);

	void processRtnMatchedInfo(Task task);

	void processRtnOrder(Task task);

	void processRtnCancelOrder(Task task);

	void processRspQryOrderInfo(Task task);

	void processRspQryMatchInfo(Task task);

	void processRspQryPosition(Task task);

	void processRspCustomerCapital(Task task);

	void processRspQryExchangeInstrument(Task task);

	void processRspArbitrageInstrument(Task task);

	void processRspQrySpecifyInstrument(Task task);

	void processRspQryPositionDetail(Task task);

	void processRtnTradingNotice(Task task);

	void processRspResetPassword(Task task);

	void processnRspQryTradeCode(Task task);

	void processRspBillConfirm(Task task);

	void processnRspEquityComputMode(Task task);

	void processRspQryBill(Task task);

	void processRspConfirmProductInfo(Task task);

	void processRspTradingDay(Task task);

	void processRspQuoteInsert(Task task);

	void processRtnQuoteInsert(Task task);

	void processRspQuoteCancel(Task task);

	void processRtnQuoteCancel(Task task);

	void processRtnQuoteMatchedInfo(Task task);

	void processRspCancelAllOrder(Task task);

	void processRspQryQuoteNotice(Task task);

	void processRspForQuote(Task task);

	void processRtnForQuote(Task task);

	void processRspQryQuoteOrderInfo(Task task);

	void processRspQryForQuote(Task task);

	void processRspQryTransferBank(Task task);

	void processRspQryTransferSerial(Task task);

	void processRspFromBankToFutureByFuture(Task task);

	void processRspFromFutureToBankByFuture(Task task);

	void processRtnFromBankToFutureByFuture(Task task);

	void processRtnFromFutureToBankByFuture(Task task);

	void processRtnRepealFromFutureToBankByBank(Task task);

	void processRspQryExchangeStatus(Task task);

	void processRtnExchangeStatus(Task task);

	void processRspQryDepthMarketData(Task task);

	void processRspQryTradeCode(Task task);

	void processRspEquityComputMode(Task task);

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

	virtual void onRspInsertOrder(dict data, dict error) {};

	virtual void onRspCancelOrder(dict data, dict error) {};

	virtual void onRtnErrorMsg(dict data) {};

	virtual void onRtnMatchedInfo(dict data) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRtnCancelOrder(dict data) {};

	virtual void onRspQryOrderInfo(dict data, dict error, bool last) {};

	virtual void onRspQryMatchInfo(dict data, dict error, bool last) {};

	virtual void onRspQryPosition(dict data, dict error, bool last) {};

	virtual void onRspCustomerCapital(dict data, dict error, bool last) {};

	virtual void onRspQryExchangeInstrument(dict data, dict error, bool last) {};

	virtual void onRspArbitrageInstrument(dict data, dict error, bool last) {};

	virtual void onRspQrySpecifyInstrument(dict data, dict error, bool last) {};

	virtual void onRspQryPositionDetail(dict data, dict error, bool last) {};

	virtual void onRtnTradingNotice(dict data) {};

	virtual void onRspResetPassword(dict data, dict error) {};

	virtual void onnRspQryTradeCode(dict data, dict error, bool last) {};

	virtual void onRspBillConfirm(dict data, dict error) {};

	virtual void onnRspEquityComputMode(dict data, dict error) {};

	virtual void onRspQryBill(dict data, dict error, bool last) {};

	virtual void onRspConfirmProductInfo(dict data, dict error) {};

	virtual void onRspTradingDay(dict data, dict error) {};

	virtual void onRspQuoteInsert(dict data, dict error) {};

	virtual void onRtnQuoteInsert(dict data) {};

	virtual void onRspQuoteCancel(dict data, dict error) {};

	virtual void onRtnQuoteCancel(dict data) {};

	virtual void onRtnQuoteMatchedInfo(dict data) {};

	virtual void onRspCancelAllOrder(dict data, dict error) {};

	virtual void onRspQryQuoteNotice(dict data, dict error, bool last) {};

	virtual void onRspForQuote(dict data, dict error) {};

	virtual void onRtnForQuote(dict data) {};

	virtual void onRspQryQuoteOrderInfo(dict data, dict error, bool last) {};

	virtual void onRspQryForQuote(dict data, dict error, bool last) {};

	virtual void onRspQryTransferBank(dict data, dict error, bool last) {};

	virtual void onRspQryTransferSerial(dict data, dict error, bool last) {};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error) {};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error) {};

	virtual void onRtnFromBankToFutureByFuture(dict data, dict error) {};

	virtual void onRtnFromFutureToBankByFuture(dict data, dict error) {};

	virtual void onRtnRepealFromFutureToBankByBank(dict data) {};

	virtual void onRspQryExchangeStatus(dict data, dict error, bool last) {};

	virtual void onRtnExchangeStatus(dict data) {};

	virtual void onRspQryDepthMarketData(dict data, dict error, bool last) {};

	virtual void onRspQryTradeCode(dict data, dict error, bool last) {};

	virtual void onRspEquityComputMode(dict data) {};


	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createDFITCTraderApi();

	void release();

	void init(string pszSvrAddr);

	int exit();

	int reqUserLogin(dict req);

	int reqUserLogout(dict req);

	int reqInsertOrder(dict req);

	int reqCancelOrder(dict req);

	int reqQryPosition(dict req);

	int reqQryCustomerCapital(dict req);

	int reqQryExchangeInstrument(dict req);

	int reqQryArbitrageInstrument(dict req);

	int reqQryOrderInfo(dict req);

	int reqQryMatchInfo(dict req);

	int reqQrySpecifyInstrument(dict req);

	int reqQryPositionDetail(dict req);

	int reqConfirmProductInfo(dict req);

	int reqResetPassword(dict req);

	int reqBillConfirm(dict req);

	int reqQryTradeCode(dict req);

	int reqEquityComputMode();

	int reqQryBill(dict req);

	int reqTradingDay(dict req);

	int reqQryQuoteNotice(dict req);

	int reqQuoteInsert(dict req);

	int reqQuoteCancel(dict req);

	int reqCancelAllOrder(dict req);

	int reqForQuote(dict req);

	int reqQryForQuote(dict req);

	int reqQryQuoteOrderInfo(dict req);

	int reqQryTransferBank(dict req);

	int reqQryTransferSerial(dict req);

	int reqFromBankToFutureByFuture(dict req);

	int reqFromFutureToBankByFuture(dict req);

	int reqQryExchangeStatus(dict req);

	int reqQryDepthMarketData(dict req);
};
