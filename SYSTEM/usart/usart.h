#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define BC26_DEBUG  1			//使能 BC26 模块的debug模式  使能成功后  会在相应的串口一发送接收到的 数据

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

extern u8  USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记	

extern u8  USART3_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	


void uart_init(u32 bound);		//串口 1 中断 	PA9(T) PA10(R)
void uart2_init(u32 bound);		//串口 2 中断		PA2(T) PA3(R)
void uart3_init(u32 bound);		//串口 3 中断		PB10(T) PB11(R)				接入BC26模块

void Clear_Buf(u8 *buf);		//清空 接收的数据


void USART2_SendData(u8 *SendBuf, u16 SendBufLen);	//串口2打印数据
void USART3_SendData(u8 *SendBuf, u16 SendBufLen);	//串口3打印数据
void USART3_SendAT(char *SendAT);	//串口3 发送AT指令
#endif

