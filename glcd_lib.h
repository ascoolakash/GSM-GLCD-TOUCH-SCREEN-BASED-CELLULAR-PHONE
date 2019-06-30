
#include <inttypes.h>

#define dataport PORTB
#define dataddr DDRB

#define conport PORTC
#define conddr DDRC


#define RS 2
#define _E 3
#define CS1 4
#define CS2 5
#define RST 6


////sirs circuit
/*#define RShigh PORTB=PORTB|(1<<2)//PORTB.2 D.7
#define RWhigh PORTB=PORTB|(1<<1)//PORTB.1 D.6
#define _Ehigh PORTB=PORTB|(1<<0)//PORTB.0 D.5
#define C1high PORTC=PORTC|(1<<7)//PORTC.7 D.4
#define C2high PORTC=PORTC|(1<<6)//PORTC.6 D.3
#define RSThigh PORTC=PORTC|(1<<5)//PORTC.5 D.0

#define RSlow PORTB=PORTB&(~(1<<2))//PORTB.2 D.7
#define RWlow PORTB=PORTB&(~(1<<1))//PORTB.1 D.6
#define _Elow PORTB=PORTB&(~(1<<0))//PORTB.0 D.5
#define C1low PORTC=PORTC&(~(1<<7))//PORTC.7 D.4
#define C2low PORTC=PORTC&(~(1<<6))//PORTC.6 D.3
#define RSTlow PORTC=PORTC&(~(1<<5))//PORTC.5 D.0*/




int glcd_init(void);
int glcd_reset();
int glcd_send(char);
int glcd_cmd (char);
int glcd_data (char);
int display11on(void);
int display12on(void);
int clear1(void);
void glcd_display1_pgm(char arr[]);////display data from program space
void glcd_display1_dir(char arr[]);////display image from program
void glcd_display2_pgm(char arr[]);////display data from program space
void glcd_display2_dir(char arr[]);////display image from program

void glcd_set2();
void glcd_set1();
