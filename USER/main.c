#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "bc26.h"
#include "timer.h"
#include "led.h"
#include "ds18b20.h"
#include "ph.h"
#include "tsw_30.h"

float Temperature = 0.0;
int 	TDS = 0;
float PH = 7.0;
	
	
 int main(void)
 {	
	 u8 i = 0;
	 char tempsp[200];
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 uart_init(115200);
	 uart3_init(115200);
	// LED_Init();			     //LED�˿ڳ�ʼ��
	 
	 //TIM3_Int_Init(9999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ 1 s  
	 
	 printf(" ok1!!!\r\n");	 
	 PH_Init();
	 TSW30_Init();
	 	while(DS18B20_Init())	//DS18B20��ʼ��	
		{
			
			delay_ms(200);
			printf("ds18b20 init\r\n");
			delay_ms(200);
		}								   

	 
	 
	 if(BC26_Init())
	 {
			printf("init is ok!!!\r\n");
	 }
	 if(MQTT_ALIYUN_CFG(0))
	 {
			printf("cfg is ok!!!\r\n");
	 }
	 while(!MQTT_ALIYUN_OPEN(0))
	 {
			printf("open is not ok!!!\r\n");
	 }
	 while(!MQTT_ALIYUN_CONN(0,"460043331009089"))
	 {
			printf("conn is not ok!!!\r\n");
	 }
	 //  �������  ʹ�ܶ�ʱ�� ��ʱ�ɼ�����  ��ʱ����
	 //TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx	
	 
	 
 		 while(1)
		 {
					Temperature=DS18B20_Get_Temp()/10.0;	
					printf("%f\r\n",Temperature);		
		
					PH = Get_PH_Value(); 
					printf("PH:%f\r\n",PH);
		
					TDS = Get_NTU_Value();
					printf("NTU:%d\r\n",TDS);
					delay_ms(1000);
			
					sprintf(tempsp, "{\"id\":\"1\",\"version\":\"1.0\",\"params\":{\"PH\":%.1f,\"TDS\":%d,\"Temperature\":%.1f}}", PH, TDS, Temperature);
					MQTT_ALIYUN_PUB(0, "/sys/a19Y6OQAflV/test_1/thing/event/property/post", tempsp);		//������Ϣ
					delay_ms(1000);
				

		 }
 }

