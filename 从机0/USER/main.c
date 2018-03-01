#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "24l01.h"  
#include "ds18b20.h"
//ALIENTEK Mini STM32�����巶������24
//����ͨ��ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

 int main(void)
 { 
	u8 rece_buf[2];
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	NRF24L01_Init();    	//��ʼ��NRF24L01  

	 
	 
	  
 	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
		printf("NRF24L01 Error");
 		delay_ms(200);
	}	
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		printf("DS18B20 Error");
 		delay_ms(200);
	}		
		
	
	
	while(1)
	{
		NRF24L01_RX_Mode(40);
		while(NRF24L01_RxPacket(rece_buf));
		
		if(rece_buf[0] == 0x66)
		{
			NRF24L01_TX_Mode(40);//����Ϊ����ģʽ
			rece_buf[1] = DS18B20_Get_Temp();
			NRF24L01_TxPacket(rece_buf);

			NRF24L01_RX_Mode(40);
			while(!(NRF24L01_Read_Reg(STATUS)&RX_OK));
			NRF24L01_RxPacket(rece_buf);
			while(rece_buf[0] != 0x88);
		}
	}
}
