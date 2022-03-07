#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define BC26_DEBUG  1			//ʹ�� BC26 ģ���debugģʽ  ʹ�ܳɹ���  ������Ӧ�Ĵ���һ���ͽ��յ��� ����

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		//����״̬���	

extern u8  USART3_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	


void uart_init(u32 bound);		//���� 1 �ж� 	PA9(T) PA10(R)
void uart2_init(u32 bound);		//���� 2 �ж�		PA2(T) PA3(R)
void uart3_init(u32 bound);		//���� 3 �ж�		PB10(T) PB11(R)				����BC26ģ��

void Clear_Buf(u8 *buf);		//��� ���յ�����


void USART2_SendData(u8 *SendBuf, u16 SendBufLen);	//����2��ӡ����
void USART3_SendData(u8 *SendBuf, u16 SendBufLen);	//����3��ӡ����
void USART3_SendAT(char *SendAT);	//����3 ����ATָ��
#endif

