#include "bc26.h"
#include "usart.h"
#include "delay.h"
#include "string.h"




u8 BC26_Init()
{
	  char* strflag;
		USART3_SendAT("AT");
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"OK");//返回OK
		Clear_Buf(USART3_RX_BUF);
	
		while(strflag == NULL)
		{
				Clear_Buf(USART3_RX_BUF);
				USART3_SendAT("AT");
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"OK");//返回OK
		}
		
		USART3_SendAT("AT+CFUN=1");		//获取卡号
		delay_ms(300);
		USART3_SendAT("AT+CIMI");		//获取卡号
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"460");//返460，表明识别到卡了
		Clear_Buf(USART3_RX_BUF);
		
		while(strflag == NULL)
    {
				Clear_Buf(USART3_RX_BUF);
				USART3_SendAT("AT+CIMI");
        delay_ms(300);
        strflag=strstr((const char*)USART3_RX_BUF,(const char*)"460");//返回OK,说明卡是存在的
    }
		
		USART3_SendAT("AT+CGATT=1");		//激活网络
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"OK");//返OK
		Clear_Buf(USART3_RX_BUF);
		USART3_SendAT("AT+CGATT?");		//查询激活状态
		delay_ms(300);
		strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+CGATT: 1");//返1
		Clear_Buf(USART3_RX_BUF);
		
		while(strflag == NULL)
		{
				Clear_Buf(USART3_RX_BUF);
				USART3_SendAT("AT+CGATT?");		//查询激活状态
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+CGATT: 1");//返1 表明注册网络成功
		}
		
		USART3_SendAT("AT+CGATT?");		//查看 CSQ 
		delay_ms(300);
		strflag = strstr((const char*)USART3_RX_BUF,(const char*)"+CESQ");		//返回CESQ
		

		return 1;
	

		

}


u8 MQTT_ALIYUN_OPEN(u8 tcpconnectID)		//tcpconnectID:连接编号   范围为：0~5
{
	char tempsp[200];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5)
		{
				sprintf(tempsp, "AT+QMTOPEN=%d,\"139.196.135.135\",1883",tcpconnectID);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTOPEN: 0,0");//看下返回状态
				while(strflag == NULL)
				{
						strflag = strstr((const char*)USART3_RX_BUF,(const char*)"+QMTOPEN: 0,0");//确认返回值正确
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

u8 MQTT_ALIYUN_CFG(u8 tcpconnectID)		// 配置产品号，设备名、秘钥
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


u8 MQTT_ALIYUN_CONN(u8 tcpconnectID, char *mac)		//连接 阿里云 
{
	char tempsp[200];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5 && mac != NULL)
		{
				sprintf(tempsp, "AT+QMTCONN=%d,\"%s\"",tcpconnectID,mac);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTCONN: 0,0,0");//看下返回状态
				while(strflag==NULL)
				{
						strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTCONN: 0,0,0");//看下返回状态
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


u8 MQTT_ALIYUN_PUB(u8 tcpconnectID, char *topic, char *msg)		//发布消息
{
	char tempsp[400];
	char *strflag;
		if(tcpconnectID >= 0 && tcpconnectID <= 5 && topic != NULL)
		{
				sprintf(tempsp, "AT+QMTPUB=%d,0,0,0,\"%s\",\"%s\"",tcpconnectID,topic,msg);
			
				USART3_SendAT(tempsp);
				delay_ms(300);
				strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTPUB: 0,0,0");//看下返回状态
				while(strflag==NULL)
				{
						strflag=strstr((const char*)USART3_RX_BUF,(const char*)"+QMTPUB: 0,0,0");//看下返回状态
				}
				Clear_Buf(USART3_RX_BUF);
				return 1;

			
		}
		else
		{
				return 0;
		}

}



