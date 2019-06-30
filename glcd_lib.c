#include "glcd_lib.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include<avr/interrupt.h>


int col=64,pos=0;
const char PROGMEM letter[600]= {
0x00 , 0x00 , 0x00 , 0x00 , 0x00,0, // space // 32 - 43
0x00 , 0x06 , 0x5F , 0x06 , 0x00,0, // !
0x07 , 0x03 , 0x00 , 0x07 , 0x03,0, // ''
0x24 , 0x7E , 0x24 , 0x7E , 0x24,0, // #
0x24 , 0x2B , 0x6A , 0x12 , 0x00,0, // $
0x63 , 0x13 , 0x08 , 0x64 , 0x63,0, // %
0x36 , 0x49 , 0x56 , 0x20 , 0x50,0, // &
0x00 , 0x07 , 0x03 , 0x00 , 0x00,0, // '
0x00 , 0x3E , 0x41 , 0x00 , 0x00,0, // (
0x00 , 0x41 , 0x3E , 0x00 , 0x00,0, // )
0x08 , 0x3E , 0x1C , 0x3E , 0x08,0, // *
0x08 , 0x08 , 0x3E , 0x08 , 0x08,0, // +
0x00 , 0xE0 , 0x60 , 0x00 , 0x00,0, // , // 44 - 55
0x08 , 0x08 , 0x08 , 0x08 , 0x08,0, // -
0x00 , 0x60 , 0x60 , 0x00 , 0x00,0, // .
0x20 , 0x10 , 0x08 , 0x04 , 0x02, 0,// /
0x3E , 0x51 , 0x49 , 0x45 , 0x3E,0, // 0
0x00 , 0x42 , 0x7F , 0x40 , 0x00,0, // 1
0x62 , 0x51 , 0x49 , 0x49 , 0x46,0, // 2
0x22 , 0x49 , 0x49 , 0x49 , 0x36,0, // 3
0x18 , 0x14 , 0x12 , 0x7F , 0x10,0, // 4
0x2F , 0x49 , 0x49 , 0x49 , 0x31,0, // 5
0x3C , 0x4A , 0x49 , 0x49 , 0x30,0, // 6
0x01 , 0x71 , 0x09 , 0x05 , 0x03,0, // 7
0x36 , 0x49 , 0x49 , 0x49 , 0x36,0, // 8 // 56 - 67
0x06 , 0x49 , 0x49 , 0x29 , 0x1E,0, // 9
0x00 , 0x6C , 0x6C , 0x00 , 0x00,0, // :
0x00 , 0xEC , 0x6C , 0x00 , 0x00,0, // ;
0x08 , 0x14 , 0x22 , 0x41 , 0x00,0, // <
0x24 , 0x24 , 0x24 , 0x24 , 0x24,0, // =
0x00 , 0x41 , 0x22 , 0x14 , 0x08,0, // >
0x02 , 0x01 , 0x59 , 0x09 , 0x06,0, // ?
0x3E , 0x41 , 0x5D , 0x55 , 0x1E,0, // @
0x7E , 0x09 , 0x09 , 0x09 , 0x7E,0, // A
0x7F , 0x49 , 0x49 , 0x49 , 0x36,0, // B
0x3E , 0x41 , 0x41 , 0x41 , 0x22,0, // C
0x7F , 0x41 , 0x41 , 0x41 , 0x3E,0, // D // 68 - 79
0x7F , 0x49 , 0x49 , 0x49 , 0x41,0, // E
0x7F , 0x09 , 0x09 , 0x09 , 0x01,0, // F
0x3E , 0x41 , 0x49 , 0x49 , 0x7A,0, // G
0x7F , 0x08 , 0x08 , 0x08 , 0x7F,0, // H
0x00 , 0x41 , 0x7F , 0x41 , 0x00,0, // I
0x30 , 0x40 , 0x40 , 0x40 , 0x3F,0, // J
0x7F , 0x08 , 0x14 , 0x22 , 0x41,0, // K
0x7F , 0x40 , 0x40 , 0x40 , 0x40,0, // L
0x7F , 0x02 , 0x04 , 0x02 , 0x7F,0, // M
0x7F , 0x02 , 0x04 , 0x08 , 0x7F,0, // N
0x3E , 0x41 , 0x41 , 0x41 , 0x3E,0, // O
0x7F , 0x09 , 0x09 , 0x09 , 0x06,0, // P // 80 - 91
0x3E , 0x41 , 0x51 , 0x21 , 0x5E,0, // Q
0x7F , 0x09 , 0x09 , 0x19 , 0x66,0, // R
0x26 , 0x49 , 0x49 , 0x49 , 0x32,0, // S
0x01 , 0x01 , 0x7F , 0x01 , 0x01,0, // T
0x3F , 0x40 , 0x40 , 0x40 , 0x3F,0, // U
0x1F , 0x20 , 0x40 , 0x20 , 0x1F,0, // V
0x3F , 0x40 , 0x3C , 0x40 , 0x3F,0, // W
0x63 , 0x14 , 0x08 , 0x14 , 0x63,0, // X
0x07 , 0x08 , 0x70 , 0x08 , 0x07,0, // Y
0x71 , 0x49 , 0x45 , 0x43 , 0x00,0, // Z
0x00 , 0x7F , 0x41 , 0x41 , 0x00,0, // [
0x02 , 0x04 , 0x08 , 0x10 , 0x20,0, // \ // 92 - 103
0x00 , 0x41 , 0x41 , 0x7F , 0x00,0, // ]
0x04 , 0x02 , 0x01 , 0x02 , 0x04,0, // ^
0x80 , 0x80 , 0x80 , 0x80 , 0x80,0, // _
0x00 , 0x03 , 0x07 , 0x00 , 0x00,0, // `
0x20 , 0x54 , 0x54 , 0x54 , 0x78,0, // a
0x7F , 0x44 , 0x44 , 0x44 , 0x38,0, // b
0x38 , 0x44 , 0x44 , 0x44 , 0x28,0, // c
0x38 , 0x44 , 0x44 , 0x44 , 0x7F,0, // d
0x38 , 0x54 , 0x54 , 0x54 , 0x18,0, // e
0x08 , 0x7E , 0x09 , 0x09 , 0x00,0, // f
0x18 , 0xA4 , 0xA4 , 0xA4 , 0x7C,0, // g
0x7F , 0x04 , 0x04 , 0x78 , 0x00,0, // h // 104 - 115
0x00 , 0x00 , 0x7D , 0x00 , 0x00,0, // i
0x40 , 0x80 , 0x84 , 0x7D , 0x00,0, // j
0x7F , 0x10 , 0x28 , 0x44 , 0x00,0, // k
0x00 , 0x00 , 0x7F , 0x40 , 0x00,0, // l
0x7C , 0x04 , 0x18 , 0x04 , 0x78,0, // m
0x7C , 0x04 , 0x04 , 0x78 , 0x00,0, // n
0x38 , 0x44 , 0x44 , 0x44 , 0x38,0, // o
0xFC , 0x44 , 0x44 , 0x44 , 0x38,0, // p
0x38 , 0x44 , 0x44 , 0x44 , 0xFC,0, // q
0x44 , 0x78 , 0x44 , 0x04 , 0x08,0, // r
0x08 , 0x54 , 0x54 , 0x54 , 0x20,0, // s
0x04 , 0x3E , 0x44 , 0x24 , 0x00,0, // t // 116 - 126
0x3C , 0x40 , 0x20 , 0x7C , 0x00,0, // u
0x1C , 0x20 , 0x40 , 0x20 , 0x1C,0, // v
0x3C , 0x60 , 0x30 , 0x60 , 0x3C,0, // w
0x6C , 0x10 , 0x10 , 0x6C , 0x00,0, // x
0x9C , 0xA0 , 0x60 , 0x3C , 0x00,0, // y
0x64 , 0x54 , 0x54 , 0x4C , 0x00,0, // z
0x08 , 0x3E , 0x41 , 0x41 , 0x00,0, // {
0x00 , 0x00 , 0x7F , 0x00 , 0x00,0, // |
0x00 , 0x41 , 0x41 , 0x3E , 0x08,0, // }
0x02 , 0x01 , 0x02 , 0x01 , 0x00,0}; // ~


int glcd_init(void)
{	cli();
	dataport=0x00;
	dataddr=0xff;
	conddr=0b10111100;
	conport=0x00;
	glcd_reset();
	//_delay_ms(10);
	rslow();
	_elow();
	cs1low();
	cs2low();
	//_delay_ms(5);
	//_delay_ms(5);
	cs1high();
	cs2low();
	//_delay_ms(5);
	glcd_cmd(0x3F);
	//_delay_ms(5);
	glcd_cmd(0xC0);
	//_delay_ms(5);
	cs1low();
	cs2high();
	//_delay_ms(1);
	glcd_cmd(0x3F);
	//_delay_ms(1);
	glcd_cmd(0xC0);
	//_delay_ms(1);
	glcd_reset();
	//_delay_ms(1);
	//_delay_ms(5);
	glcd_clear(1);
	glcd_clear(2);
	glcd_set(2);
	sei();
	return 0;
}


int glcd_reset()
{
	rstlow();
	//_delay_ms(10);
	rsthigh();
	return 0;
}

int glcd_send(char i)
{
	dataport=i;
	_delay_us(5);
	_ehigh();
	_delay_us(5);
	_elow();
	_delay_us(5);
	return 0;
}

int glcd_cmd (char i)
{
	rslow();
	glcd_send(i);
	return 0;
}

int glcd_data (char i)
{
	rshigh();
	glcd_send(i);
	return 0;
}

int display11on(void)
{
	//_delay_ms(5);
	//_delay_ms(5);
	cs1low();
	cs2high();
	//_delay_ms(5);

	//_delay_ms(5);
	glcd_cmd(0xC0);
	return 0;
}

int display12on(void)
{
	//_delay_ms(5);
	//_delay_ms(5);
	cs1high();
	cs2low();
	//_delay_ms(5);

	//_delay_ms(5);
	glcd_cmd(0xC0);
	return 0;
}


void glcd_clear(int o)
{
	char j;
	char p=184;
	if(o==1)
	{
		//_delay_ms(5);
		glcd_set(1);
	}
	else
	{
		//_delay_ms(5);
		glcd_set(2);
	}
	for(p=184;p<192;p++){
	glcd_cmd(p);
	
	for(j=0;j<64;j++)
	{
		glcd_data(0);//_delay_ms(1);
	}
	}
	
}


void glcd_display1_pgm(char arr[])
{
	int im=0;
	glcd_set(1);
	glcd_cmd(0x3F);_delay_ms(1);
	glcd_cmd(0xC0);_delay_ms(1);
	glcd_cmd(256);
	glcd_cmd(184);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im));}
	glcd_cmd(185);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(1*col)));}
	glcd_cmd(186);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(2*col)));}
	glcd_cmd(187);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(3*col)));}
	glcd_cmd(188);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(4*col)));}
	glcd_cmd(189);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(5*col)));}
	glcd_cmd(190);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(6*col)));}
	glcd_cmd(191);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(7*col)));}
}


void glcd_display1_dir(char arr[])
{
	int im=0;
	glcd_set(1);
	glcd_cmd(0x3F);_delay_ms(1);
	glcd_cmd(0xC0);_delay_ms(1);
	glcd_cmd(256);
	glcd_cmd(184);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im]);}
	glcd_cmd(185);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(1*col)]);}
	glcd_cmd(186);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(2*col)]);}
	glcd_cmd(187);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(3*col)]);}
	glcd_cmd(188);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(4*col)]);}
	glcd_cmd(189);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(5*col)]);}
	glcd_cmd(190);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(6*col)]);}
	glcd_cmd(191);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(7*col)]);}


}

void glcd_display2_pgm(char arr[])
{
	int im=0;
	glcd_set(2);
	glcd_cmd(0x3F);_delay_ms(1);
	glcd_cmd(0xC0);_delay_ms(1);
	glcd_cmd(256);
	glcd_cmd(184);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im));}
	glcd_cmd(185);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(1*col)));}
	glcd_cmd(186);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(2*col)));}
	glcd_cmd(187);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(3*col)));}
	glcd_cmd(188);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(4*col)));}
	glcd_cmd(189);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(5*col)));}
	glcd_cmd(190);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(6*col)));}
	glcd_cmd(191);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(pgm_read_byte(arr+im+(7*col)));}
}

void glcd_display2_dir(char arr[])
{
	int im=0;
	glcd_set(2);
	glcd_cmd(0x3F);_delay_ms(1);
	glcd_cmd(0xC0);_delay_ms(1);
	glcd_cmd(256);
	glcd_cmd(184);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im]);}
	glcd_cmd(185);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(1*col)]);}
	glcd_cmd(186);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(2*col)]);}
	glcd_cmd(187);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(3*col)]);}
	glcd_cmd(188);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(4*col)]);}
	glcd_cmd(189);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(5*col)]);}
	glcd_cmd(190);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(6*col)]);}
	glcd_cmd(191);glcd_cmd(64);for(im=0;im<col;im++){glcd_data(arr[im+(7*col)]);}


}


void glcd_set(int u)
{
	if(u==1)
	{
		cs1low();
		cs2high();
		//_delay_ms(1);
	}
	else
	{
		cs1high();
		cs2low();
		//_delay_ms(1);
	}
}



void glcd_string(char a[],int line,int col)
{



int i1,i,j,k1=0,k,n,x=184,y1=63,y2=63,l,j1,j2=0,j3=0;
int q,r=1;

cli();
	x=184+line-1;
	y1=63+col-1;
	y2=63;
	
	glcd_set(2);
	for(i=0;i<strlen(a);i++)
	{
		n=a[i];
		l=(n-32)*6;
	/*	if(a[i]==32 && y1>=127)
		{
		
		check(i);
		 
		}*/
		if(127-y2<(6*r))
			{
				glcd_set(2);
				y1=63;
				x++;
				glcd_cmd(y1);
				glcd_cmd(x);
				r=1;
				y2=63;
			}
		for(j=0;j<6;j++)
		{
			if(y1<127)
			{
				y1++;
				glcd_cmd(y1);
				glcd_cmd(x);
			}
			else if(y1>=127 && y2<127)
			{
				glcd_set(1);
				y2++;
				glcd_cmd(y2);
				glcd_cmd(x);
			}
			else if(y2>=127)
			{
				glcd_set(2);
				y1=63;
				x++;
				glcd_cmd(y1);
				glcd_cmd(x);
				
				y2=63;
			}
			
			glcd_data(pgm_read_byte(letter+l+j));
		}	
	
	}
	sei();
}

void putstring(int d,char a[],int z)
{
int i,j,k,l,x,y=64,n;
glcd_set(d);
for(i=0;i<strlen(a);i++)
	{

		n=a[i];
		k=i/10;
		l=(n-32)*6;
		x=184+z-1;
		glcd_cmd(x);
		glcd_cmd(y);
		for(j=0;j<6;j++)
		{
			glcd_data(pgm_read_byte(letter+l+j));
			y++;
		}
		//_delay_ms(100);
		
	}
}


void eight(char data[8],int line,int col)
{
	int x,y,i=0,j=0;
	glcd_set(2);
	x=183+line+1;
	y=64+(8*(col));
	glcd_cmd(y);
	glcd_cmd(x);
	for(i=0;i<8;i++)
	{
		glcd_data(data[i]);
	}
	
}


void rshigh()
{
	conport|=(1<<RS);
}

void rslow()
{
	conport&=~(1<<RS);
}
void _ehigh()
{
	conport|=(1<<_E);
}

void _elow()
{
	conport&=~(1<<_E);
}
void cs1high()
{
	conport|=(1<<CS1);
}

void cs1low()
{
	conport&=~(1<<CS1);
}
void cs2high()
{
	conport|=(1<<CS2);
}

void cs2low()
{
	conport&=~(1<<CS2);
}
void rsthigh()
{
	conport|=(1<<RST);
}

void rstlow()
{
	conport&=~(1<<RST);
}
void button1(int x,int y,char j)
{
	cs1high();
	cs2low();
		glcd_cmd(0x3F);_delay_ms(1);
		glcd_cmd(0xC0);_delay_ms(1);
		//glcd_cmd(256);
	int i=0,x1,y1;
	x1=184+(x*2);
	y1=64+(y*16);
	glcd_cmd(x1);
	glcd_cmd(y1);
	for(i=0;i<16;i++)
	{
		if(i==0 || i==15)
			glcd_data(~0xff);
		else if( i<5 || i>10)
			glcd_data(~0x01);
		else
		{
			int temp,temp1;
				//glcd_data(0xff);
			temp=(j-32)*6;
			temp1=pgm_read_byte(letter+temp+i-5);
			temp1=temp1&0b00001111;
			temp1=temp1<<4;
			temp1=temp1|0b00000001;
			glcd_data(~temp1);
		}
	}
	x1=185+(x*2);
	y1=64+(y*16);
	glcd_cmd(x1);
	glcd_cmd(y1);
	for(i=0;i<16;i++)
	{
		if(i==0 || i==15)
			glcd_data(~0xff);
		else if( i<5 || i>10)
			glcd_data(~0x80);
		else
		{
			int temp,temp1;
				//glcd_data(0xff);
				temp=(j-32)*6;

					temp1=pgm_read_byte(letter+temp+i-5);
					temp1=temp1&0b11110000;
					temp1=temp1>>4;
					temp1=temp1|0b10000000;
					glcd_data(~temp1);
		}
	}

}
void button0(int x,int y,char j)
{
	cs1low();
	cs2high();
		glcd_cmd(0x3F);_delay_ms(1);
		glcd_cmd(0xC0);_delay_ms(1);
		//glcd_cmd(256);
	int i=0,x1,y1;
	x1=184+(x*2);
	y1=64+(y*16);
	glcd_cmd(x1);
	glcd_cmd(y1);
	for(i=0;i<16;i++)
	{
		if(i==0 || i==15)
			glcd_data(~0xff);
		else if( i<5 || i>10)
			glcd_data(~0x01);
		else
		{
			int temp,temp1;
				//glcd_data(0xff);
			temp=(j-32)*6;
			temp1=pgm_read_byte(letter+temp+i-5);
			temp1=temp1&0b00001111;
			temp1=temp1<<4;
			temp1=temp1|0b00000001;
			glcd_data(~temp1);
		}
	}
	x1=185+(x*2);
	y1=64+(y*16);
	glcd_cmd(x1);
	glcd_cmd(y1);
	for(i=0;i<16;i++)
	{
		if(i==0 || i==15)
			glcd_data(~0xff);
		else if( i<5 || i>10)
			glcd_data(~0x80);
		else
		{
			int temp,temp1;
				//glcd_data(0xff);
				temp=(j-32)*6;

					temp1=pgm_read_byte(letter+temp+i-5);
					temp1=temp1&0b11110000;
					temp1=temp1>>4;
					temp1=temp1|0b10000000;
					glcd_data(~temp1);
		}
	}

}

/*void glcd_display1_rectangle(int x1, int y1, char arr[])
{
	//glcd_set(1);
	glcd_cmd(184+y1);
	glcd_cmd(64+x1);


	for(int i=0; i<=60;i++)
	{
		if(i==0||i==60)
			glcd_data(0xff);
		else if(i<2 || i>60)
		{
			glcd_data(0x01);
		}

		else
		{glcd_data(0x01);
			//int im=0;
				//glcd_set(1);
				//glcd_cmd(0x3F);_delay_ms(1);
				//glcd_cmd(0xC0);_delay_ms(1);
				//glcd_cmd(256);
		//for(im=0;im<(6*strlen(arr));im++){glcd_data((pgm_read_byte(letter+(6*(arr[im/6]-32)+im%6))));}


			/*int temp,temp1, k;
							//glcd_data(0xff);
			for(k=0;k<=strlen(a);k++)
						temp=(a[k]-32)*6;
						temp1=pgm_read_byte(letter+temp+i-5);
						temp1=temp1&0b00001111;
						temp1=temp1<<4;
						temp1=temp1|0b00000001;
						glcd_data(~temp1);

	}}

	glcd_cmd(185+y1);
		glcd_cmd(64+x1);
	for(int i=0; i<=63;i++)
			if(i==0||i==63)
				glcd_data(0xff);
			else
			{
				/*int temp,temp1,k;
											//glcd_data(0xff);
							for(k=0;k<=strlen(a);k++)
										temp=(a[k]-32)*6;
										temp1=pgm_read_byte(letter+temp+i-5);
										temp1=temp1&0b00001111;
										temp1=temp1<<4;
										temp1=temp1|0b00000001;
										glcd_data(~temp1);
		}
}*/
