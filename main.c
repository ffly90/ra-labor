/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <xc.h>
#include <sys/attribs.h>

void SYSTEM_Initialize(void);

unsigned int analog_in;
typedef unsigned int u32;

void setup() { 
	SYSTEM_Initialize();  // set 24 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us
    //Zähler Konfiguration
    T1CONbits.TGATE = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0;
    T1CONbits.TSYNC = 0;
    PR1 = 3225;
    T1CONbits.ON = 1;
    //DAC Konfiguration
    DAC1CONbits.DACDAT = 0;
    DAC1CONbits.DACOE = 1;
    DAC1CONbits.REFSEL = 0b11;
    DAC1CONbits.ON = 1;
    //ADC Konfiguration
    ANSELCbits.ANSC8 = 1;
    TRISCbits.TRISC8 = 1;
    AD1CON1bits.SSRC = 0;
    AD1CON1bits.MODE12 = 0;
    AD1CHSbits.CH0SA = 14;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.ADCS = 0;
    AD1CON1bits.ON = 1;
    //Interrupt
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC4bits.T1IP = 2;
    //AD1CON1bits.SAMP = 1;
}

void readADC() {
    AD1CON1bits.SAMP = 1;
    delay_us(100);
    while (!AD1CON1bits.DONE);
    analog_in = ADC1BUF0;
    AD1CON1bits.SAMP = 0;
}

void __ISR(_TIMER_1_VECTOR, IPL2SOFT) nextOutput(void) {
    DAC1CONbits.DACDAT++;
    IFS0bits.T1IF = 0;
}

unsigned int temp;
void loop() {
    while(1){
        readADC();
        temp = -(860*analog_in)/341+3225;
        PR1 = temp;
    }
}

int main(void) {
    setup();
    loop();
}