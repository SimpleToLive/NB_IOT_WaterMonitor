#include "bc26.h"
#include "usart.h"
#include "delay.h"
#include "string.h"




u8 BC26_Init()
{
	  char* strflag;
		USART3_SendAT("AT");
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"OK");//����OK
		Clear_Buf(USART3_RX_BUF);
	
		while(strflag == NULL)
		{
				Clear_Buf(USART3_RX_BUF);
				USART3_SendAT("AT");
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"OK");//����OK
		}
		
		USART3_SendAT("AT+CFUN=1");		//��ȡ����
		delay_ms(300);
		USART3_SendAT("AT+CIMI");		//��ȡ����
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"460");//��460������ʶ�𵽿���
		Clear_Buf(USART3_RX_BUF);
		
		while(strflag == NULL)
    {
				Clear_Buf(USART3_RX_BUF);
				USART3_SendAT("AT+CIMI");
        delay_ms(300);
        strflag=strstr((const char*)USART3_RX_BUF,(const char*)"460");//����OK,˵�����Ǵ��ڵ�
    }
		
		USART3_SendAT("AT+CGATT=1");		//��������
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"OK");//��OK
		Clear_Buf(USART3_RX_BUF);
		USART3_SendAT("AT+CGATT?");		//��ѯ����״̬
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+CGATT: 1");//��1
		Clear_Buf(USART3_RX_BUF);
		
		while(strflag == NULL)
		{
				Clear_Buf(USART3_RX_BUF);
				USART3_SendAT("AT+CGATT?");		//��ѯ����״̬
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+CGATT: 1");//��1 ����ע������ɹ�
		}
		
		USART3_SendAT("AT+CGATT?");		//�鿴 CSQ 
		delay_ms(300);
		strflag = strstr((const char*)USART3_RX_BUF,(const char*)"+CESQ");		//����CESQ
		

		return 1;
	

		

}


u8 MQTT_ALIYUN_OPEN(u8 tcpconnectID)		//tcpconnectID:���ӱ��   ��ΧΪ��0~5
{
	char tempsp[200];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5)
		{
				sprintf(tempsp, "AT+QMTOPEN=%d,\"139.196.135.135\",1883",tcpconnectID);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTOPEN: 0,0");//���·���״̬
				while(strflag == NULL)
				{
						strflag = strstr((const char*)USART3_RX_BUF,(const char*)"+QMTOPEN: 0,0");//ȷ�Ϸ���ֵ��ȷ
				} 
				Clear_Buf(USART3_RX_BUF);
				delay_ms(300);
				return 1;

			
		}
		else
		{
				return 0;
		}




}

u8 MQTT_ALIYUN_CFG(u8 tcpconnectID)		// ���ò�Ʒ�ţ��豸������Կ
{
	char tempsp[200];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5)
		{
				sprintf(tempsp, "AT+QMTCFG=\"aliauth\",%d,\"%s\",\"%s\",\"%s\"",tcpconnectID,PRODUCTKEY,DEVICENAME,DEVICESECRET);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				
				return 1;

			
		}
		else
		{
				return 0;
		}
	

}


u8 MQTT_ALIYUN_CONN(u8 tcpconnectID, char *mac)		//���� ������ 
{
	char tempsp[200];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5 && mac != NULL)
		{
				sprintf(tempsp, "AT+QMTCONN=%d,\"%s\"",tcpconnectID,mac);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTCONN: 0,0,0");//���·���״̬
				while(strflag==NULL)
				{
						strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTCONN: 0,0,0");//���·���״̬
				}
				Clear_Buf(USART3_RX_BUF);
				delay_ms(300);
				return 1;

			
		}
		else
		{
				return 0;
		}
	

}


u8 MQTT_ALIYUN_PUB(u8 tcpconnectID, char *topic, char *msg)		//������Ϣ
{
	char tempsp[400];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5 && topic != NULL)
		{
				sprintf(tempsp, "AT+QMTPUB=%d,0,0,0,\"%s\",\"%s\"",tcpconnectID,topic,msg);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTPUB: 0,0,0");//���·���״̬
				while(strflag==NULL)
				{
						strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTPUB: 0,0,0");//���·���״̬
				}
				Clear_Buf(USART3_RX_BUF);
				return 1;

			
		}
		else
		{
				return 0;
		}

}



