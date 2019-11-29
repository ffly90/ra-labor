/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <xc.h>
#include <sys/attribs.h>

void SYSTEM_Initialize(void);

int ADCResult;
typedef unsigned int u32;

void setup() { 
	SYSTEM_Initialize();  // set 24 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us
    //Zähler Konfiguration
    T1CONbits.TGATE = 0;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCS = 1;
    T1CONbits.TCKPS = 0;
    T1CONbits.TSYNC = 0;
    PR1 = 0x7fff;
    T1CONbits.ON = 1;
    //DAC Konfiguration
    DAC1CONbits.DACDAT = 0;
    DAC1CONbits.DACOE = 1;
    DAC1CONbits.REFSEL = 11;
    DAC1CONbits.ON = 1;
    //Interrupt
//    IEC0bits.T1IE = 1;
//    IFS0bits.T1IF = 0;
//    IPC4bits.T1IP = 2;
//    AD1CON1bits.SAMP = 1;
}

//void __ISR(_TIMER_1_VECTOR, IPL2SOFT) nextOutput(void) {
//    DAC1CONbits.DACDAT++;
//    IFS0bits.T1IF = 0;
//}

void loop() {
    int i, r;
    u32 us = 62;
    while(1){
        DAC1CONbits.DACDAT++;
        delay_us(us);
    }
}

int main(void) {
    setup();
    loop();
}