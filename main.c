/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <xc.h>

void SYSTEM_Initialize(void);

int pinnumber = 0;

void setup() { 
	SYSTEM_Initialize();  // set 24 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us
	TRISDCLR = 0b11111;     // set bit 3 of Port D for output
    TRISBSET = 1<<9; // set input RB9 or button s1
    T1CONbits.TGATE = 0; 
    T1CONbits.TCS = 0;
    //select PBCLK as input clock for timer1
    T1CONbits.TCKPS = 0b11; // set prescaler to 1:256
    T1CONbits.TSYNC = 0;
    PR1 = 18750;
}

void loop() {
    int in_old = 0;
    int in_new = 0;
    int state = -1;
    int direction = 1;
	while(1) {
        in_old = in_new;
        in_new = (!(PORTB & 1<<9));
        if(!in_old && in_new){state = -1* state;}
        
        if(state>0){
            T1CONbits.ON = 1; // start timer1
            if(IFS0bits.T1IF){
                IFS0bits.T1IF = 0;
                LATDCLR = 1<<pinnumber;
                pinnumber+= direction;
                if(pinnumber>=4){
                    direction = -1;
                }else if(pinnumber<=0){
                    direction = 1;
                }
                LATDSET = 1<<pinnumber;
            }
        }else{
            T1CONbits.ON = 0; // stop timer1
            LATDCLR = 1<<pinnumber;
            TMR1SET = 0;
            pinnumber = 0;
        }
        
    }
}

int main(void) {
    setup();
    loop();
}