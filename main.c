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
    CCP1RA = 0x0000 ; // counter overflow value
    CCP1RB = 0x8000; //
    CCP1CON1bits.MOD = 0b0101; // center dual edge buffered compare mode
    CCP1CON1bits.CLKSEL = 0; //select sysclk 
    CCP1CON1bits.TMRPS = 0; // prescaler 1:8
    CCP1CON1bits.ON = 1; // start timer
}

void loop() {
    int i = 0;
    int b = 0;
	while(1) {
        for(i = 0; i<100000; i++){
            CCP1RA = i;
            for(b = 0; b<100; b++){}
        }
    }
}

int main(void) {
    setup();
    loop();
}