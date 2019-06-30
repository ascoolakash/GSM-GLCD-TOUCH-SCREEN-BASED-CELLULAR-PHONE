/*
 * touch_gsm_glcd.c
 *
 *  Created on: 25-Jun-2013
 *      Author: Akash Saurabh
 */
#include <stdio.h>
#include <avr/io.h>
#include "adc_lib.h"
#include <util/delay.h>
#include"lcd_lib.h"
#include "glcd_lib.h"
#include "uart_lib.h"
#include "avr/interrupt.h"

#define Y1 450
#define Y2 550
#define Y3 680
//#define Y4 738
//#define Y5 934

#define X1 900
#define X2 800
#define X3 700
#define X4 600
#define X5 500
#define X6 400
#define X7 300
#define X8 200
#define X9 110

#define INRANGE(p,q,a,b,c,d) (p<a&&p>b&&q<c&&q>d)


int i=0, key_status=0, key_pressed=0;
char A[14]="  ", num[2]=" ";
int x=0,x1=0,x2=0,y1=0,y2=0,y=0,xx=0,yy=0,index=0;
char coordinates[10]=" ";

ISR(USART_RXC_vect) {
A[index] = UDR;
if (A[index]==10)index = 0;
else index++;
}

/*void read_location()
{
	DDRA =0b00000101;
	PORTA=0b00000100;

	x1=read_adc(3);
	_delay_ms(15);

	x2=read_adc(3);
	if(x1==x2){x=x2;
	key_status=0;
	}

	DDRA =0b00001010;
	PORTA=0b00001000;

	y1=read_adc(2);
	_delay_ms(15);

	y2=read_adc(2);
	if((y1<(y2+30))|(y1>(y2-30))){y=y2;
	if(key_pressed==1){
	key_pressed=0;
	key_status=0;}}
	else key_pressed=1;
	}*/
void read_xy(){
	DDRA =0b00000101;
	PORTA=0b00001110;
	yy=read_adc(3);
	DDRA =0b00001010;
	PORTA=0b00001101;
	xx=read_adc(2);
	}

int main(){
	glcd_init();
   glcd_clear(1);
   glcd_clear(2);
	ADCinit();
	set_uartbaud(9600);
	enable_uart_rxcint();
	sendchar_uart(0x1a);
	sei();
	while(1)
	{	read_xy();
		//sprintf(coordinates,"%4d,%4d",xx,yy);
		//glcd_string(coordinates,3,2);
	//sprintf(num,"%d",1);
	//glcd_string(num,1,1);
		_delay_ms(100);
		get_button();
		call();
	}
}


void get_button()
{
	if(x>1000&&x<1024&&y>970&&y<1000)
	{
	key_status=0;
	}
		if(key_status==0)
		{

			if(INRANGE(xx,yy,X1,X2,Y2,Y1)){
				sprintf(num,"%d",1);
				A[i++]='1';
				key_status=1;
			}
			else if(INRANGE(xx,yy,X2,X3,Y2,Y1))
							{
							sprintf(num,"%d",2);
							A[i++]='2';
							key_status=1;}

		else if( INRANGE(xx,yy,X3,X4,Y2,Y1) )
				{sprintf(num,"%d",3);
				A[i++]='3';
				key_status=1; }

			else if(INRANGE(xx,yy,X4,X5,Y2,Y1))
				{
				sprintf(num,"%d",4);
				A[i++]='4';
				key_status=1;}

			else if(INRANGE(xx,yy,X5,X6,Y2,Y1))
				{sprintf(num,"%d",5);
				A[i++]='5';
				key_status=1;}

			else if(INRANGE(xx,yy,X6,X7,Y2,Y1))
				{sprintf(num,"%d",6);
				A[i++]='6';
				key_status=1;}

			else if(INRANGE(xx,yy,X7,X8,Y2,Y1))
				{sprintf(num,"%d",7);
				A[i++]='7';
				key_status=1;}

			else if(INRANGE(xx,yy,X8,X9,Y2,Y1))
				{sprintf(num,"%d",8);
				A[i++]='8';
				key_status=1;}

			else if(INRANGE(xx,yy,X1,X2,Y3,Y2))
				{sprintf(num,"%d",9);
				A[i++]='9';
				key_status=1;}

			else if(INRANGE(xx,yy,X2,X3,Y3,Y2))
				{sprintf(num,"%d",0);
				A[i++]='0';
				key_status=1;}

			else if(INRANGE(xx,yy,X3,X4,Y3,Y2))
				{sprintf(num,"%c",'#');
				A[i++]='#';
				key_status=1;}

			else if(INRANGE(xx,yy,X4,X5,Y3,Y2))
				{sprintf(num,"%c",'*');

				A[i++]='*';
				key_status=1;}

			else if(INRANGE(xx,yy,X5,X6,Y3,Y2))
				{sprintf(num,"%c",'p');
				//A[i++]='p';
				key_status=1;
				phone();
				}

			else if(INRANGE(xx,yy,X6,X7,Y3,Y2))
				{sprintf(num,"%c",'h');
				//A[i++]='h';
				key_status=1;
				hang();
				}

				else if(INRANGE(xx,yy,X8,X9,Y3,Y2))
			   {sprintf(num,"%c",'c');
		     	i--;
		    	A[i]=' ';
		    	key_status=1;}}
		/*else
		{

			sprintf(num,"%d",0);
							A[i++]='1';
							key_status=1;
		}*/
			key_status=0;
			glcd_string(A,3,70);
			//glcd_string(num,4,70);
	    	     _delay_ms(100);}



void call()
	{
			glcd_string("ABHISHEK",1,40);
			numeric_button();
			button1(3,1,'0');
		    button1(3,2,'#');
		    button1(3,3,'*');
		    button0(3,3,'C');
		    button0(3,0,'P');
		    button0(3,1,'H');

	}
void numeric_button()
	{
		    button1(2,0,'1');
			button1(2,1,'2');
			button1(2,2,'3');
			button1(2,3,'4');
			button0(2,0,'5');
			button0(2,1,'6');
			button0(2,2,'7');
			button0(2,3,'8');
			button1(3,0,'9');
			button1(3,1,'0');
	}

void phone()
{
	glcd_string("calling",3,2);
sendstring_uart("ATD");
_delay_ms(50);
sendstring_uart(A);
_delay_ms(50);
sendstring_uart(";\r\n");
}

void hang()
{
	sendstring_uart("ATH");
		_delay_ms(50);
		sendstring_uart(A);
		_delay_ms(50);
		sendstring_uart(";\r\n");
		glcd_clear(0);
		glcd_clear(1);
}
