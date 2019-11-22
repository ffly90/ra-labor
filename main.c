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
    //ADC Konfiguration
    ANSELAbits.ANSA0 = 1;
    TRISASET = 1;
    AD1CON1bits.SSRC = 0;
    AD1CHSbits.CH0SA = 0;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.ADCS = 8;
    AD1CON1bits.ON = 1;
}

unsigned int readADC() {
    int ADCResult;
    AD1CON1bits.SAMP = 1;
    delay_us(2000);
    AD1CON1bits.SAMP = 0;
    
    while (AD1CON1bits.DONE != 1);
    return (ADC1BUF0);
}

void loop() {
    u8 k, einer, zehner, hunderter;
    int i, r;
    while(1){
        for(r=0; r<100; r++){
            writeDec(readADC());
        }
    }
}


int main(void) {
    setup();
    loop();
}