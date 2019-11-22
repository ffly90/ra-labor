/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <xc.h>

void SYSTEM_Initialize(void);

typedef unsigned char u8;

void setup() { 
	SYSTEM_Initialize();  // set 24 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us
    initDisplay(); //initialize disp
    initSelect(); //init selector
    T1CONbits.TECS = 0b10;
    T1CONbits.TCS = 1;
    T1CONbits.TCKPS = 0b11;
    T1CONbits.TSYNC = 0;
    PR1 = 10000;
    T1CONbits.ON = 1;
}

void loop() {
    u8 k, einer, zehner, hunderter;
    int i;
    while(1){
        for(i=0; i<100; i++){
            writeDec(TMR1/10);
            //writeDot(1);
        }
    }
}

int main(void) {
    setup();
    loop();
}