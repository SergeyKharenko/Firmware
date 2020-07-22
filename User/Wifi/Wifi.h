#include "stm32f10x.h"
#include "bsp_usart.h"
#include <stdbool.h>

enum Wifi_State
{
	AT_Init_Test_Failed = 0x01,
	AP_Build_Failed = 0x02,
	AP_SETUP_Failed = 0x03,
	AP_MULTI_CONNECTION_DISABLE_Failed=0x04,
	NO_CLIENT_CONNECT=0x05,
	TCP_SETUP_Failed=0x06,
	DIRECT_CONNECTION_Failed=0x07,
	NO_ERROR = 0x10
};

struct Cache_Container
{
	int iterator;
	char cache[100];
};

char* WIFI_CMD_TCP_SETUP(char* ip_address);		//TCP连接生成函数


struct Cache_Container Cache_Init_Get();
void Cache_Clear(struct Cache_Container* Cache);
void Cache_Add(struct Cache_Container* Cache,char data);

//###############  初始化函数  ##################
enum Wifi_State Wifi_Init();

void Wifi_Delay_A_While();      //简单延时函数
bool Wifi_Client_Connected();  //客户端连接判断 
void Wifi_Get_Client_IP();		//获取客户端IP地址
enum Wifi_State Wifi_TCP_Setup();			//建立TCP/IP连接
enum Wifi_State Wifi_Direct_CMD(bool mode);	//透传模式切换
void Wifi_Send(const char* string,uint32_t data,bool is_data);		//串口发送数据
void Wifi_Receive_IRQ_CMD(bool mode);//Wifi串口中断使能切换
bool Wifi_Receive_CMD_CMP(const char* Cmd,uint8_t len,uint8_t start_since);//返回指令队列比较 需要手动删除缓存 
