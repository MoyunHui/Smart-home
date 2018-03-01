#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "24l01.h"  
#include "ds18b20.h"
//ALIENTEK Mini STM32开发板范例代码24
//无线通信实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  

 int main(void)
 { 
	u8 rece_buf[2];
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	NRF24L01_Init();    	//初始化NRF24L01  

	 
	 
	  
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		printf("NRF24L01 Error");
 		delay_ms(200);
	}	
	while(DS18B20_Init())	//DS18B20初始化	
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
			NRF24L01_TX_Mode(40);//配置为发送模式
			rece_buf[1] = DS18B20_Get_Temp();
			NRF24L01_TxPacket(rece_buf);

			NRF24L01_RX_Mode(40);
			while(!(NRF24L01_Read_Reg(STATUS)&RX_OK));
			NRF24L01_RxPacket(rece_buf);
			while(rece_buf[0] != 0x88);
		}
	}
}
