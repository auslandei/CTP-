 /**
 * ��Ȩ����(C)2012-2016, �����ɴ���Ϣ�������޹�˾
 * �ļ����ƣ�DFITCTraderApi.h
 * �ļ�˵��������XSpeed���׽ӿ�
 * ��ǰ�汾��1.0.14.91
 * ���ߣ�XSpeed��Ŀ��
 * �������ڣ�2015��5��6��
 */

#ifndef DFITCTRADERAPI_H_
#define DFITCTRADERAPI_H_

#include "DFITCApiStruct.h"


#ifdef WIN32
     #ifdef DFITCAPI_EXPORTS
          #define DFITCTRADERAPI_API __declspec(dllexport)
     #else
          #define DFITCTRADERAPI_API __declspec(dllimport)
     #endif//DFITCAPI_EXPORTS
#else
     #define DFITCTRADERAPI_API
#endif//WIN32

namespace DFITCXSPEEDAPI
{
     class DFITCTraderSpi
     {
     public:

         /* ��������������Ӧ:���ͻ����뽻�׺�̨�轨����ͨ������ʱ����δ��¼ǰ�����ͻ���API���Զ������ǰ�û�֮������ӣ�
          * ��������ã����Զ��������ӣ������ø÷���֪ͨ�ͻ��ˣ� �ͻ��˿�����ʵ�ָ÷���ʱ������ʹ���ʽ��˺Ž��е�¼��
          *���÷�������Api��ǰ�û��������Ӻ󱻵��ã��õ��ý�����˵��tcp�����Ѿ������ɹ����û���Ҫ���е�¼���ܽ��к�����ҵ�������
          *  ��¼ʧ����˷������ᱻ���á���
          */
         virtual void OnFrontConnected(){};

         /**
          * �������Ӳ�������Ӧ�����ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
          * @param  nReason:����ԭ��
          *        0x1001 �����ʧ��
          *        0x1002 ����дʧ��
          *        0x2001 ����������ʱ
          *        0x2002 ��������ʧ�� 
          *        0x2003 �յ�������  
          */
         virtual void OnFrontDisconnected(int nReason){};
         /**
          * ��½������Ӧ:���û�������¼�����ǰ�û�������Ӧʱ�˷����ᱻ���ã�֪ͨ�û���¼�Ƿ�ɹ���
          * @param pUserLoginInfoRtn:�û���¼��Ϣ�ṹ��ַ��
          * @param pErrorInfo:����¼ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pUserLoginInfoRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * �ǳ�������Ӧ:���û������˳������ǰ�û�������Ӧ�˷����ᱻ���ã�֪ͨ�û��˳�״̬��
          * @param pUserLogoutInfoRtn:�����û��˳���Ϣ�ṹ��ַ��
          * @param pErrorInfo:���ǳ�ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * �ڻ�ί�б�����Ӧ:���û�¼�뱨����ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pOrderRtn:�����û��µ���Ϣ�ṹ��ַ��
          * @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * �ڻ�ί�г�����Ӧ:���û�������ǰ�÷�����Ӧ�Ǹ÷����ᱻ���á�
          * @param pOrderCanceledRtn:���س�����Ӧ��Ϣ�ṹ��ַ��
          * @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspCancelOrder(struct DFITCOrderRspDataRtnField * pOrderCanceledRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * ����ر�
          * @param pErrorInfo:������Ϣ�Ľṹ��ַ��
          */
         virtual void OnRtnErrorMsg(struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * �ɽ��ر�:��ί�гɹ����׺�η����ᱻ���á�
          * @param pRtnMatchData:ָ��ɽ��ر��Ľṹ��ָ�롣
          */
         virtual void OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData){};

         /**
          * ί�лر�:�µ�ί�гɹ��󣬴˷����ᱻ���á�
          * @param pRtnOrderData:ָ��ί�лر���ַ��ָ�롣
          */
         virtual void OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData){};

         /**
          * �����ر�:�������ɹ���÷����ᱻ���á�
          * @param pCancelOrderData:ָ�򳷵��ر��ṹ�ĵ�ַ���ýṹ�������������Լ�������Ϣ��
          */
         virtual void OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData){};

         /**
          * ��ѯ����ί����Ӧ:���û�����ί�в�ѯ�󣬸÷����ᱻ���á�
          * @param pRtnOrderData:ָ��ί�лر��ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ��ѯ���ճɽ���Ӧ:���û������ɽ���ѯ��÷����ᱻ���á�
          * @param pRtnMatchData:ָ��ɽ��ر��ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * �ֲֲ�ѯ��Ӧ:���û������ֲֲ�ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pPositionInfoRtn:���سֲ���Ϣ�ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * �ͻ��ʽ��ѯ��Ӧ:���û������ʽ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pCapitalInfoRtn:�����ʽ���Ϣ�ṹ�ĵ�ַ��
          * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
		  * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ��������Լ��ѯ��Ӧ:���û�������Լ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pInstrumentData:���غ�Լ��Ϣ�ṹ�ĵ�ַ��
          * @param pErrorInfo:������Ϣ�ṹ�������ѯ���������򷵻ش�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ������Լ��ѯ��Ӧ:���û�����������Լ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pAbiInstrumentData:����������Լ��Ϣ�ṹ�ĵ�ַ��
          * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ��ѯָ����Լ��Ӧ:���û�����ָ����Լ��ѯָ���ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pInstrument:����ָ����Լ��Ϣ�ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
		  * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ��ѯ�ֲ���ϸ��Ӧ:���û�������ѯ�ֲ���ϸ��ǰ�÷�����Ӧʱ�÷����ᱻ���á�
          * @param pPositionDetailRtn:���سֲ���ϸ�ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
		  * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ����֪ͨ��Ӧ:���ڽ���XSPEED��̨�ֶ�����֪ͨ����֧��ָ���ͻ���Ҳ֧��ϵͳ�㲥��
          * @param pTradingNoticeInfo: �����û��¼�֪ͨ�ṹ�ĵ�ַ��
          */
         virtual void OnRtnTradingNotice(struct DFITCTradingNoticeInfoField * pTradingNoticeInfo){};

         /**
          * �����޸���Ӧ:�����޸��ʽ��˻���¼���롣
          * @param pResetPassword: ���������޸Ľṹ�ĵ�ַ��
		  * @param pErrorInfo:���޸�����ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */ 
         virtual void OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * ���ױ����ѯ��Ӧ:���ؽ��ױ�����Ϣ
          * @param pTradeCode: ���ؽ��ױ����ѯ�ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
		  * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * �˵�ȷ����Ӧ:���ڽ��տͻ��˵�ȷ��״̬��
          * @param pBillConfirm: �����˵�ȷ�Ͻṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo){};
 
         /**
          * ��ѯ�ͻ�Ȩ����㷽ʽ��Ӧ:���ؿͻ�Ȩ�����ķ�ʽ
          * @param pEquityComputMode: ���ؿͻ�Ȩ����㷽ʽ�ṹ�ĵ�ַ��
          */
         virtual void OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode){};

         /**
          * �ͻ������˵���ѯ��Ӧ:�����˵���Ϣ
          * @param pQryBill: ���ؿͻ������˵���ѯ�ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryBill(struct DFITCQryBillRtnField * pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ����IDȷ����Ӧ:���ڽ��ճ�����Ϣ��
          * @param pProductRtnData: ���س���IDȷ����Ӧ�ṹ�ĵ�ַ��
          */
         virtual void OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData){};


         /**
          * ������ȷ����Ӧ:���ڽ��ս�������Ϣ��
          * @param DFITCTradingDayRtnField: ���ؽ���������ȷ����Ӧ�ṹ�ĵ�ַ��
          */
         virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData){};

         /**
          * �����̱�����Ӧ
          * @param pRspQuoteData:ָ�������̱�����Ӧ��ַ��ָ�롣
		  * @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspQuoteInsert(struct DFITCQuoteRspField * pRspQuoteData, struct DFITCErrorRtnField * pErrorInfo) {};

         /**
          * �����̱����ر�
          * @param pRtnQuoteData:ָ�������̱����ر���ַ��ָ�롣
          */
         virtual void OnRtnQuoteInsert(struct DFITCQuoteRtnField * pRtnQuoteData){};

         /**
          * �����̳�����Ӧ
          * @param pRspQuoteCanceledData:ָ�������̳�����Ӧ��ַ��ָ�롣
		  * @param pErrorInfo:������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspQuoteCancel(struct DFITCQuoteRspField * pRspQuoteCanceledData,struct DFITCErrorRtnField * pErrorInfo)  {};

         /**
          * �����̳����ر�
          * @param pRtnQuoteCanceledData:ָ�������̳����ر���ַ��ָ�롣
          */
         virtual void OnRtnQuoteCancel(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData) {};   

		 /**
          * �����̳ɽ��ر�
          * @param pRtnQuoteMatchedData:ָ�������̳ɽ��ر���ַ��ָ�롣
          */
         virtual void OnRtnQuoteMatchedInfo(struct DFITCQuoteMatchRtnField * pRtnQuoteMatchedData) {};

		 /**
          * ����������Ӧ
          * @param pRspStripCancelOrderData:ָ������������Ӧ��ַ��ָ�롣
		  * @param pErrorInfo:����������ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspCancelAllOrder(struct DFITCCancelAllOrderRspField * pRspCancelAllOrderData, struct DFITCErrorRtnField * pErrorInfo){};

		 /**
          * ѯ��֪ͨ��ѯ��Ӧ
          * @param pRtnQryQuoteNoticeData:��ѯѯ��֪ͨ�ر��ṹ��ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryQuoteNotice(struct DFITCQryQuoteNoticeRtnField * pRtnQryQuoteNoticeData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};
		 
         /**
          * ѯ����Ӧ
          * @param pRspForQuoteData:ѯ��������Ӧ�ṹ��ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspForQuote(struct DFITCForQuoteRspField * pRspForQuoteData, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * ѯ�ۻر�
          * @param pRtnForQuoteData:ѯ�ۻر��ṹ��ַ��
          */
         virtual void OnRtnForQuote(struct DFITCForQuoteRtnField * pRtnForQuoteData){};

         /**
          * ��ѯ���ձ���ί����Ӧ
          * @param pRtnQuoteOrderData:ָ�򱨼۲�ѯ�ر��ṹ�ĵ�ַ��
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryQuoteOrderInfo(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ѯ��ί�в�ѯ��Ӧ
          * @param pRtnQryForQuoteData:ָ��ѯ��ί�в�ѯ��Ӧ��ַ��ָ�롣
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryForQuote(struct DFITCQryForQuoteRtnField * pRtnQryForQuoteData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * ��ѯת��������Ӧ
          * @param pTransferBank:ָ���ѯת�����лر���ַ��ָ�롣
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryTransferBank(struct DFITCTransferBankRspField * pTransferBank, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) {};
		 
         /**
          * ��ѯת����ˮ��Ӧ
          * @param pTransferSerial:ָ���ѯת����ˮ�ر���ַ��ָ�롣
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryTransferSerial(struct DFITCTransferSerialRspField * pTransferSerial, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) {};
		 
         /**
          * �ڻ����������ʽ�ת�ڻ�Ӧ��
          * @param pRspTransfer:ָ���ڻ����������ʽ�ת�ڻ�Ӧ���ַ��ָ�롣
		  * @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspFromBankToFutureByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) {};
		 
         /**
          * �ڻ������ڻ��ʽ�ת����Ӧ��
          * @param pRspTransfer:ָ���ڻ������ڻ��ʽ�ת����Ӧ���ַ��ָ�롣
		  * @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRspFromFutureToBankByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) {};

         /**
          * �ڻ����������ʽ�ת�ڻ�֪ͨ
          * @param pRtnTransfer:ָ���ڻ����������ʽ�ת�ڻ�֪ͨ��ַ��ָ�롣
		  * @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRtnFromBankToFutureByFuture(struct DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) {};
		 
         /**
          * �ڻ������ڻ��ʽ�ת����֪ͨ
          * @param pRtnTransfer:ָ���ڻ������ڻ��ʽ�ת����֪ͨ��ַ��ָ�롣
		  * @param pErrorInfo:��ת��ʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          */
         virtual void OnRtnFromFutureToBankByFuture(struct DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) {};

         /**
          * ���з�������ڻ�ת����֪ͨ
          * @param pRspRepeal:ָ���ڻ������ڻ��ʽ�ת���г���֪ͨ��ַ��ָ�롣
          */
         virtual void OnRtnRepealFromFutureToBankByBank(struct DFITCRepealRtnField * pRspRepeal) {};

         /**
          * ������״̬��ѯ��Ӧ
          * @param pRspExchangeStatusData:ָ������״̬��ѯ��Ӧ��ַ��ָ�롣
          */
         virtual void OnRspQryExchangeStatus(struct DFITCExchangeStatusRspField * pRspExchangeStatusData){};

         /**
          * ������״̬֪ͨ
          * @param pRtnExchangeStatusData:ָ������״̬֪ͨ��ַ��ָ�롣
          */
         virtual void OnRtnExchangeStatus(struct DFITCExchangeStatusRtnField * pRtnExchangeStatusData){};
		
         /**
          * �����ѯ��Ӧ
          * @param pDepthMarketData:ָ�������ѯ��Ӧ��ַ��ָ�롣
		  * @param pErrorInfo:����ѯʧ�ܣ����ش�����Ϣ��ַ���ýṹ���д�����Ϣ��
          * @param bIsLast:�����Ƿ������һ����Ӧ��Ϣ��0 -��   1 -�ǣ���
          */
         virtual void OnRspQryDepthMarketData(struct DFITCDepthMarketDataField * pDepthMarketData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

	};//end of DFITCTraderSpi

     class DFITCTRADERAPI_API DFITCTraderApi
     {
     public:
         DFITCTraderApi();
         virtual ~DFITCTraderApi();
     public:
         /**
          * ��̬����������һ��apiʵ��
          * @return ��������UserApi
          */
         static DFITCTraderApi * CreateDFITCTraderApi(void);

         /**
          * ɾ���ӿڶ���������ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
          */
         virtual void Release(void) = 0;

         /**
          * �ͷ���������socket���ӣ�������һ�������̣߳� ͬʱ�÷���ע��һ���ص�������
          * @param pszFrontAddr:����ǰ�������ַ��
          *                     �����ַ�ĸ�ʽΪ:"protocol://ipaddress:port",��"tcp://172.21.200.103:10910"
          *                     ����protocol��ֵΪtcp��ʽ��
          *                     ipaddress��ʾ����ǰ�õ�IP,port��ʾ����ǰ�õĶ˿�     
          * @param *pSpi:��DFITCMdSpi����ʵ��
          * @return 0 - ��ʼ���ɹ�; -1 - ��ʼ��ʧ�ܡ�
          */
         virtual int Init(char * pszFrontAddr, DFITCTraderSpi * pSpi) = 0;

         /**
          * �ȴ��ӿ��߳̽������С�
          * @return �߳��˳����롣
          */
         virtual int Join(void) = 0;

         /**
          * �û�������¼����
          * @param pUserLoginData:ָ���û���¼����ṹ�ĵ�ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */ 
         virtual int ReqUserLogin(struct DFITCUserLoginField * pUserLoginData) = 0;

         /**
          * �û������ǳ�����
          * @param pUserLogoutData:ָ���û���¼����ṹ�ĵ�ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */ 
         virtual int ReqUserLogout(struct DFITCUserLogoutField * pUserLogoutData) = 0;

         /**
          * �ڻ�ί�б�������
          * @param pInsertOrderData:�û����󱨵���Ϣ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqInsertOrder(struct DFITCInsertOrderField * pInsertOrderData) = 0;

         /**
          * �ڻ���������
          * @param pCancelOrderData:�û����󳷵���Ϣ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          * (����ṩ��̨ί�к�(��̨ί�кŴ���-1)����ֻʹ�ù�̨ί�кŴ���ֻ�е���̨ί�к�С��0ʱ����ʹ�ñ���ί�кŽ��г���)
          */
         virtual int ReqCancelOrder(struct DFITCCancelOrderField * pCancelOrderData) = 0;

         /**
          * �ֲֲ�ѯ����
		  * @param pPositionData:�û�����ֲ���Ϣ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
		  *�����û���ṩ��Լ���룬���ѯȫ���ֲ���Ϣ����
          */
         virtual int ReqQryPosition(struct DFITCPositionField * pPositionData) = 0;

         /**
          * �ͻ��ʽ��ѯ����
          * @param pCapitalData:�����ʽ��ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��(�û���Ҫ���ýṹ�ĸ����ֶΡ�)
          */
         virtual int ReqQryCustomerCapital(struct DFITCCapitalField * pCapitalData) = 0;

         /**
          * ��ѯ��������Լ�б�����������
          * @param pExchangeInstrumentData:��������Լ��ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryExchangeInstrument(struct DFITCExchangeInstrumentField * pExchangeInstrumentData) = 0;

         /**
          * ��ѯ������������Լ�б�
          * @param pAbtriInstrumentData:������������Լ��ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryArbitrageInstrument(struct DFITCAbiInstrumentField * pAbtriInstrumentData) = 0;

         /**
          * ����ί�в�ѯ����
          * @param pOrderData:����ί�в�ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryOrderInfo(struct DFITCOrderField * pOrderData) = 0;

         /**
          * ���ճɽ���ѯ����
          * @param pMatchData:���ճɽ���ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryMatchInfo(struct DFITCMatchField * pMatchData) = 0;

         /**
          * ָ����Լ��Ϣ��ѯ����
          * @param pInstrument:ָ����Լ��ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQrySpecifyInstrument(struct DFITCSpecificInstrumentField * pInstrument) = 0;

         /**
          * �ֲ���ϸ��ѯ����
          * @param pPositionDetailData:�ֲ���ϸ��ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryPositionDetail(struct DFITCPositionDetailField * pPositionDetailData) = 0;

         /**
          * ����IDȷ������
		  * @param pConfirmProductData:����IDȷ�Ͻṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ�� -���� -����쳣��
          */
         virtual int ReqConfirmProductInfo(struct DFITCProductField * pConfirmProductData) = 0;

         /**
          * �����޸�����
          * @param pResetPasswordData:�����޸Ľṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqResetPassword (struct DFITCResetPwdField * pResetPasswordData) =0;

         /**
          * �˵�ȷ������
          * @param pBillConfirmData:�˵�ȷ�Ͻṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqBillConfirm(struct DFITCBillConfirmField * pBillConfirmData) = 0;

         /**
          * ���ױ����ѯ����
          * @param pTradeCodeData:���ױ����ѯ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryTradeCode(struct DFITCQryTradeCodeField * pTradeCodeData) = 0;

         /**
          * ��ѯ�ͻ�Ȩ����㷽ʽ����
          * @return 0 - �����ͳɹ�; -1 - ������ʧ�� -���� -����쳣��
          */
         virtual int ReqEquityComputMode() = 0;

         /**
          * �ͻ��˵������ѯ����
          * @param pQryBillData:�ͻ��˵���������ṹ��ַ�� 
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryBill(struct DFITCQryBillField * pQryBillData) = 0;

         /**
          * �����ղ�ѯ����
          * @param pTradingDay:�����ղ�ѯ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ�� -���� -����쳣��
          */
         virtual int ReqTradingDay(struct DFITCTradingDayField * pTradingDay) = 0;

		 /**
          * ѯ��֪ͨ��ѯ����
          * @param pQryQuoteNoticeData:��ѯѯ��֪ͨ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryQuoteNotice(struct DFITCQryQuoteNoticeField * pQryQuoteNoticeData) = 0;

         /**
          * �����̱�������
          * @param pQuoteInsertOrderData:�����̱�������ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQuoteInsert(struct DFITCQuoteInsertField * pQuoteInsertOrderData)  = 0;

         /**
          * �����̳�������
          * @param pQuoteCancelOrderData:�����̳�������ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQuoteCancel(struct DFITCCancelOrderField * pQuoteCancelOrderData) = 0;  
		 
         /**
          * ��������
          * @param pCancelAllOrderData:������������ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqCancelAllOrder(struct DFITCCancelAllOrderField * pCancelAllOrderData) = 0;

         /**
          * ѯ������
          * @param pForQuoteData:ѯ������ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqForQuote(struct DFITCForQuoteField * pForQuoteData) =0;

         /**
          * ѯ��ί�в�ѯ����
          * @param pQryForQuoteData:ѯ��ί�в�ѯ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryForQuote(struct DFITCQryForQuoteField * pQryForQuoteData) =0;

         /**
          * �����̱���ί�в�ѯ
          * @param pQuoteOrderData:�����̱���ί�в�ѯ�ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryQuoteOrderInfo(struct DFITCQuoteOrderField * pQuoteOrderData) =0;

         /**
          * ��ѯת������
          * @param pQryTransferBank:��ѯת����������ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryTransferBank(struct DFITCQryTransferBankField * pQryTransferBank) = 0;

         /**
          * ��ѯת����ˮ
          * @param pQryTransferSerial:��ѯת����ˮ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryTransferSerial(struct DFITCQryTransferSerialField * pQryTransferSerial) = 0;

         /**
          * �ڻ����������ʽ�ת�ڻ�
          * @param pReqTransfer:�����ʽ�ת�ڻ�����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqFromBankToFutureByFuture(struct DFITCReqTransferField * pReqTransfer) = 0;

         /**
          * �ڻ������ڻ��ʽ�ת����
          * @param pReqTransfer:�ڻ��ʽ�ת��������ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqFromFutureToBankByFuture(struct DFITCReqTransferField * pReqTransfer) = 0;

         /**
          * ������״̬��ѯ
          * @param pQryExchangeStatusData:������״̬��ѯ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryExchangeStatus(struct DFITCQryExchangeStatusField * pQryExchangeStatusData) = 0;

         /**
          * �����ѯ����
          * @param pQryDepthMarketData:�����ѯ����ṹ��ַ��
          * @return 0 - �����ͳɹ� -1 - ������ʧ��  -���� -����쳣��
          */
         virtual int ReqQryDepthMarketData(struct DFITCQryDepthMarketDataField * pQryDepthMarketData) = 0;
     };//end of DFITCTraderSpi
}
//end of namespace


#endif//DFITCTRADERAPI_H_

