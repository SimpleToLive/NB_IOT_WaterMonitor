#include "sys.h"

#define PRODUCTKEY		"a19Y6OQAflV"
#define	DEVICENAME		"test_1"
#define DEVICESECRET	"0dc1033a31132bacb0d2c834fbf9bc6b"
 
u8 BC26_Init();			//初始化BC26模块   检查网络状态

u8 MQTT_ALIYUN_OPEN(u8 tcpconnectID);		//tcpconnectID:连接编号   范围为：0~5

u8 MQTT_ALIYUN_CFG(u8 tcpconnectID);		// 配置产品号，设备名、秘钥

u8 MQTT_ALIYUN_CONN(u8 tcpconnectID, char *mac);		//连接 阿里云 

u8 MQTT_ALIYUN_PUB(u8 tcpconnectID, char *topic, char *msg);		//发布消息
