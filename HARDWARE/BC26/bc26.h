#include "sys.h"

#define PRODUCTKEY		"a19Y6OQAflV"
#define	DEVICENAME		"test_1"
#define DEVICESECRET	"0dc1033a31132bacb0d2c834fbf9bc6b"
 
u8 BC26_Init();			//��ʼ��BC26ģ��   �������״̬

u8 MQTT_ALIYUN_OPEN(u8 tcpconnectID);		//tcpconnectID:���ӱ��   ��ΧΪ��0~5

u8 MQTT_ALIYUN_CFG(u8 tcpconnectID);		// ���ò�Ʒ�ţ��豸������Կ

u8 MQTT_ALIYUN_CONN(u8 tcpconnectID, char *mac);		//���� ������ 

u8 MQTT_ALIYUN_PUB(u8 tcpconnectID, char *topic, char *msg);		//������Ϣ
