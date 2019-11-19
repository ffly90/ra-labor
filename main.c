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
    CCP1CON1bits.CCSEL = 0;
    CCP1CON1bits.T32 = 0;
    CCP1CON1bits.TRIGEN = 0;
    CCP1CON1bits.SYNC = 0;
    CCP1CON2bits.OCAEN = 1;
    CCP1CON3bits.OUTM = 0;
    CCP1CON3bits.POLACE = 0;
    CCP1TMRbits.TMRL = 0;
    CCP1PRbits.PRL = 0xffff;
    CCP1RA = 0 ; // counter overflow value
    CCP1RB = 0xffff ; //
    CCP1CON1bits.MOD = 0b0101; // dual edge buffered compare mode
    CCP1CON1bits.CLKSEL = 0; //select sysclk 
    CCP1CON1bits.TMRPS = 0; // prescaler 1:1
    CCP1CON1bits.ON = 1; // start timer
}

void loop() {
    int k = 0;
	while(1) {
        for(CCP1RA = 0; CCP1RA<0xffff; CCP1RA++){
            for(k = 0; k<100; k++){}
        }
        for(CCP1RA = 0xffff; CCP1RA>0 ; CCP1RA--){
            for(k = 0; k<100; k++){}
        }
    }
}

int main(void) {
    setup();
    loop();
}