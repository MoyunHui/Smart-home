#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "24l01.h"  
//ALIENTEK Mini STM32开发板范例代码24
//无线通信实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  

#define CHA1 40 //频道 取值范围0-125
#define CHA2 80

int main(void)
{ 
	u16 t=0;			 
	u8 key = 0;
	u8 rece_buf[3]; 
	u8 temp[2];
	u8 tmp_buf[6];
	u8 i = 0; //循环变量
	u8 channel = 0; //通道号

	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	NRF24L01_Init();    	//初始化NRF24L01  

	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		printf("t0.txt=");
		printf("\"NO NRF24L01\"");
		delay_ms(200);
	}	

//	while(1)
//	{
//		key=KEY_Scan(0);
//		if(key==KEY0_PRES) {break;}
//		else if(key==KEY1_PRES) {break;}
//		else if(key==WK_UP) {break;}

//		//格一段时间就显示一次	
//		t++;
//		if(t==100)printf("KEY_UP: aKEY1:TX_Mode  KEY0:RX_Mode\n");
// 		if(t==200) {t=0;}
//		delay_ms(5);	  
//	}

	printf("page 1");

	while(1)
	{ 
		printf("n0.val=");
		printf("5");
		//************************************************//
		//*************与设备1之间的通信 CHA1*************//
		//************************************************//
		
		//======发送======//
		channel = CHA1;
		NRF24L01_TX_Mode(channel);
		rece_buf[0] = 0x66; //发送温度命令
		NRF24L01_TxPacket(rece_buf);
		
		//======接收======//
		NRF24L01_RX_Mode(channel);
		while(NRF24L01_RxPacket(rece_buf));
		temp[0] = rece_buf[0]; //temp[0]放命令
		temp[1] = rece_buf[1]; //temp[1]放数据

		tmp_buf[0] = 32;
		tmp_buf[1] = 48 + temp[1]/100;
		tmp_buf[2] = 48 + (temp[1]/10)%10;
		tmp_buf[3] = 46;
		tmp_buf[4] = 48 + temp[1]%10;
		tmp_buf[5] = 0;	   

		printf("tempreate1 = ");
		for (i = 0; i < 5; i++)
		{
			printf("%c", tmp_buf[i]);
		}
		//======发送======//
		NRF24L01_TX_Mode(channel);//配置为发送模式
		rece_buf[0]=0x88;//这是我规定的主机接收到温度的回应数据
		NRF24L01_TxPacket(rece_buf);

		
		//************************************************//
		//*************与设备2之间的通信 CHA1*************//
		//************************************************//
		
		//======发送======//
		channel = CHA2;
		NRF24L01_TX_Mode(channel);
		rece_buf[0] = 0x66; //发送温度命令
		NRF24L01_TxPacket(rece_buf);

		//======接收======//
		NRF24L01_RX_Mode(channel);
		while(NRF24L01_RxPacket(rece_buf));
		temp[0] = rece_buf[0]; //temp[0]放命令
		temp[1] = rece_buf[1]; //temp[1]放数据

		tmp_buf[0] = 32;
		tmp_buf[1] = 48 + temp[1]/100;
		tmp_buf[2] = 48 + (temp[1]/10)%10;
		tmp_buf[3] = 46;
		tmp_buf[4] = 48 + temp[1]%10;
		tmp_buf[5] = 0;	   

		printf("tempreate2 = ");
		for (i = 0; i < 5; i++)
		{
			printf("%c", tmp_buf[i]);
		}
		//======发送======//
		NRF24L01_TX_Mode(channel);//配置为发送模式
		rece_buf[0]=0x88;//这是我规定的主机接收到温度的回应数据
		NRF24L01_TxPacket(rece_buf);
	}
}


