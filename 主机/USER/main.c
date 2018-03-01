#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "24l01.h"  
//ALIENTEK Mini STM32�����巶������24
//����ͨ��ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

#define CHA1 40 //Ƶ�� ȡֵ��Χ0-125
#define CHA2 80

int main(void)
{ 
	u16 t=0;			 
	u8 key = 0;
	u8 rece_buf[3]; 
	u8 temp[2];
	u8 tmp_buf[6];
	u8 i = 0; //ѭ������
	u8 channel = 0; //ͨ����

	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	NRF24L01_Init();    	//��ʼ��NRF24L01  

	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
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

//		//��һ��ʱ�����ʾһ��	
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
		//*************���豸1֮���ͨ�� CHA1*************//
		//************************************************//
		
		//======����======//
		channel = CHA1;
		NRF24L01_TX_Mode(channel);
		rece_buf[0] = 0x66; //�����¶�����
		NRF24L01_TxPacket(rece_buf);
		
		//======����======//
		NRF24L01_RX_Mode(channel);
		while(NRF24L01_RxPacket(rece_buf));
		temp[0] = rece_buf[0]; //temp[0]������
		temp[1] = rece_buf[1]; //temp[1]������

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
		//======����======//
		NRF24L01_TX_Mode(channel);//����Ϊ����ģʽ
		rece_buf[0]=0x88;//�����ҹ涨���������յ��¶ȵĻ�Ӧ����
		NRF24L01_TxPacket(rece_buf);

		
		//************************************************//
		//*************���豸2֮���ͨ�� CHA1*************//
		//************************************************//
		
		//======����======//
		channel = CHA2;
		NRF24L01_TX_Mode(channel);
		rece_buf[0] = 0x66; //�����¶�����
		NRF24L01_TxPacket(rece_buf);

		//======����======//
		NRF24L01_RX_Mode(channel);
		while(NRF24L01_RxPacket(rece_buf));
		temp[0] = rece_buf[0]; //temp[0]������
		temp[1] = rece_buf[1]; //temp[1]������

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
		//======����======//
		NRF24L01_TX_Mode(channel);//����Ϊ����ģʽ
		rece_buf[0]=0x88;//�����ҹ涨���������յ��¶ȵĻ�Ӧ����
		NRF24L01_TxPacket(rece_buf);
	}
}


