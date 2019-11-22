/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <xc.h>
#include <sys/attribs.h>

void SYSTEM_Initialize(void);

int ADCResult;
typedef unsigned char u8;

void setup() { 
	SYSTEM_Initialize();  // set 24 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us
    initDisplay(); //initialize disp
    initSelect(); //init selector
    //Zähler Konfiguration
    T1CONbits.TGATE = 0;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCS = 1;
    T1CONbits.TCKPS = 0;
    T1CONbits.TSYNC = 0;
    PR1 = 0x7fff;
    T1CONbits.ON = 1;
    //ADC Konfiguration
    ANSELAbits.ANSA0 = 1;
    TRISASET = 1;
    AD1CON1bits.SSRC = 0;
    AD1CHSbits.CH0SA = 0;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.ADCS = 8;
    AD1CON1bits.ON = 1;
    //Interrupt
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC4bits.T1IP = 2;
}

unsigned int readADC() {
    unsigned int res;
    asm volatile(
        "lw $t0, AD1CON1                \n\t"
        "li $t1, 0xFFFFFFFD             \n\t"
        "and $t0, $t0, $t1              \n\t"
        "sw $t0, AD1CON1                \n\t"
        " 1: "
        "lw $t0, AD1CON1                \n\t"
        "andi $t0, $t0, 1               \n\t"
    //    "beq $t0, $zero, 1b             \n\t"
        "nop                            \n\t"
        "lw %0, ADC1BUF0                \n\t"
    //    "li %0, 123                     \n\t"
        "lw $t0, AD1CON1                \n\t"
        "ori $t0, $t0, 2                \n\t"
        "sw $t0, AD1CON1                "
        : "=r" (res)
    );
//    AD1CON1bits.SAMP = 1;
//    delay_us(2000);
//    AD1CON1bits.SAMP = 0;
//    
//    while (AD1CON1bits.DONE != 1);
//    return (ADC1BUF0);
    return res;
}

void __ISR(_TIMER_1_VECTOR, IPL2SOFT) handler(void) {
    ADCResult = readADC();
    IFS0bits.T1IF = 0;
}

void loop() {
    int i, r;
    while(1){
        for(r=0; r<100; r++){
            writeDec(ADCResult);
        }
    }
}


int main(void) {
    setup();
    loop();
}