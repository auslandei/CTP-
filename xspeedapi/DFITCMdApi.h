/**
 * ��Ȩ����(C)2012-2016, �����ɴ���Ϣ�������޹�˾
 * �ļ����ƣ�DFITCMdApi.h
 * �ļ�˵��������XSpeed����API�ӿ�
 * ��ǰ�汾��1.0.14.45
 * ���ߣ�XSpeed��Ŀ��
 * �������ڣ�2015��5��6��
 */

#ifndef DLMDAPI_H_
#define DLMDAPI_H_


#include "DFITCApiStruct.h"


#ifdef WIN32
    #ifdef DFITCAPI_EXPORTS
        #define MDAPI_API __declspec(dllexport)
    #else
        #define MDAPI_API __declspec(dllimport)
    #endif//DFITCAPI_EXPORTS
#else
    #define MDAPI_API 
#endif//WIN32

namespace DFITCXSPEEDMDAPI
{
    class DFITCMdSpi
    {
    public:
        DFITCMdSpi(){}

        /** 
         * ��������������Ӧ
         */
        virtual void OnFrontConnected(){};

        /**
         * �������Ӳ�������Ӧ
         */
        virtual void OnFrontDisconnected(int nReason){};

        /**
         * ��½������Ӧ:���û�������¼�����ǰ�û�������Ӧʱ�˷����ᱻ���ã�֪ͨ�û���¼�Ƿ�ɹ���
         * @param pRspUserLogin:�û���¼��Ϣ�ṹ��ַ��
         * @param pRspInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
         */
		virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pRspUserLogin, struct DFITCErrorRtnField * pRspInfo) {};

        /**
         * �ǳ�������Ӧ:���û������˳������ǰ�û�������Ӧ�˷����ᱻ���ã�֪ͨ�û��˳�״̬��
         * @param pRspUsrLogout:�����û��˳���Ϣ�ṹ��ַ��
         * @param pRspInfo:������ʧ�ܣ����ش�����Ϣ��ַ��
         */
		virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pRspUsrLogout, struct DFITCErrorRtnField * pRspInfo) {};

        /**
         * ����Ӧ��
         * @param pRspInfo:������Ϣ��ַ��
         */
		virtual void OnRspError(struct DFITCErrorRtnField *pRspInfo) {};

        /**
         * ���鶩��Ӧ��:���û��������鶩�ĸ÷����ᱻ���á�
         * @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
         * @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
         */
		virtual void OnRspSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo) {};

        /**
         * ȡ����������Ӧ��:���û������˶������÷����ᱻ���á�
         * @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
         * @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
         */
		virtual void OnRspUnSubMarketData(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo) {};

        /**
         * ����ѯ��Ӧ��
         * @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
         * @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
         */
		virtual void OnRspSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo) {};

        /**
         * ȡ������ѯ��Ӧ��
         * @param pSpecificInstrument:ָ���Լ��Ӧ�ṹ���ýṹ������Լ�������Ϣ��
         * @param pRspInfo:������Ϣ������������󣬸ýṹ���д�����Ϣ��
         */
		virtual void OnRspUnSubForQuoteRsp(struct DFITCSpecificInstrumentField * pSpecificInstrument, struct DFITCErrorRtnField * pRspInfo) {};

        /**
         * ������ϢӦ��:�����������ɹ��������鷵��ʱ���÷����ᱻ���á�
         * @param pMarketDataField:ָ��������Ϣ�ṹ��ָ�룬�ṹ���а��������������Ϣ��
         */
		virtual void OnMarketData(struct DFITCDepthMarketDataField * pMarketDataField) {};

        /**
         * �Զ������������ϢӦ��:�����������ɹ��������鷵��ʱ���÷����ᱻ���á�
         * @param pMarketDataField:ָ��������Ϣ�ṹ��ָ�룬�ṹ���а��������������Ϣ��
         */
		virtual void OnCustomMarketData(struct DFITCCustomMarketDataField * pMarketDataField) {};

        /**
         * ѯ��֪ͨ
         * @param pForQuoteField:ָ��ѯ����Ϣ�ṹ��ָ�룬�ṹ���а��������ѯ����Ϣ��
         */
		virtual void OnRtnForQuoteRsp(struct DFITCQuoteSubscribeRtnField * pForQuoteField) {};

        /**
         * ������ȷ����Ӧ:���ڽ��ս�������Ϣ��
         * @param pTradingDayRtnData: ���ؽ���������ȷ����Ӧ�ṹ�ĵ�ַ��
         */
        virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData){};
    };//end of DFITCMdSpi

    class MDAPI_API DFITCMdApi
    {
    public:
        /**
         * ��������APIʵ��
         * @return ��������UserApi
         */
        static DFITCMdApi * CreateDFITCMdApi();

        /**
         * ����һϵ�г�ʼ������:ע��ص������ӿ�,��������ǰ�á�
         * @param pszSvrAddr:����ǰ�������ַ��
         *                  �����ַ�ĸ�ʽΪ:"protocol://ipaddress:port",��"tcp://127.0.0.1:10915"
         *                  ����protocol��ֵΪtcp,udp,udpb(�㲥����),��ʾ��������ķ�ʽ;�����udp������������,udp�Ķ˿ڽ���API����ȷ����
		 *                  �����udpb�㲥���飬��Ҫ���ڻ���˾ȷ�ϱ��̹㲥����˿ڡ�
         *                  ipaddress��ʾ����ǰ�õ�IP,port��ʾ����ǰ�õĶ˿�
         * @param pSpi:��DFITCMdSpi����ʵ��
         * @return 0 - �ɹ�; -1 - ʧ�ܡ�
         */
        virtual int Init(char * pszSvrAddr, DFITCMdSpi * pSpi) = 0;

        /**
         * ɾ���ӿڶ���������ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
         */
        virtual void Release() = 0;

        /**
         * ��������:�÷�����������ĳ������ĳЩ��Լ��������
         * @param ppInstrumentID[]:ָ�����飬ÿ��ָ��ָ��һ����Լ����*���������к�Լ��Ҳ�ɶ���ĳ���������к�Լ��DCE��
         * @param nCount:��Լ����
         * @return 0 - �����ͳɹ�; -1 - ������ʧ�ܡ�
         */
        virtual int SubscribeMarketData(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * �˶�����:�÷��������˶�ĳ��/ĳЩ��Լ��������
         * @param ppInstrumentID[]:ָ�����飬ÿ��ָ��ָ��һ����Լ����*�������˶����к�Լ��Ҳ���˶�ĳ���������к�Լ��DCE��
         * @param nCount:��Լ����
         * @return 0 - �����ͳɹ�; -1 - ������ʧ��
         */
        virtual int UnSubscribeMarketData(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * ����ѯ��
         * @param ppInstrumentID[]:ָ�����飬ÿ��ָ��ָ��һ����Լ����*����������ѯ�ۣ�Ҳ�ɶ���ĳ����������ѯ����DCE��
         * @param nCount:��Լ����
         * @return 0 - �����ͳɹ�; -1 - ������ʧ��
         */
        virtual int SubscribeForQuoteRsp(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

       /**
         * �˶�ѯ��
         * @param ppInstrumentID[]:ָ�����飬ÿ��ָ��ָ��һ����Լ����*�������˶�����ѯ�ۣ�Ҳ���˶�ĳ����������ѯ����DCE��
         * @param nCount:��Լ����
         * @return 0 - �����ͳɹ�; -1 - ������ʧ��
         */
        virtual int UnSubscribeForQuoteRsp(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * �û�������½����
         * @param pReqUserLoginField:ָ���û���¼����ṹ�ĵ�ַ��
         * @return 0 - �����ͳɹ�; -1 - ������ʧ��; -2 - ����쳣��
         */ 
        virtual int ReqUserLogin(struct DFITCUserLoginField * pReqUserLoginField) = 0;

        /**
         * �û������ǳ�����
         * @param pReqUserLogoutField:ָ���û���¼����ṹ�ĵ�ַ��
         * @return 0 - �����ͳɹ�; -1 - ������ʧ��; -2 - ����쳣��
         */ 
        virtual int ReqUserLogout(struct DFITCUserLogoutField * pReqUserLogoutField) = 0;

        /**
         * �����ղ�ѯ����
         * @return 0 - �����ͳɹ�; -1 - ������ʧ�ܡ�
         */
        virtual int ReqTradingDay(struct DFITCTradingDayField * pTradingDay) = 0;

    protected:
        virtual ~DFITCMdApi() = 0;

    };//end of MDAPI_API
} //end of namespace

#endif//DLMDAPI_H_
