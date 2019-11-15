/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <xc.h>

void SYSTEM_Initialize(void);

const int pinnumber = 4;

void setup() { 
	SYSTEM_Initialize();  // set 24 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us
	TRISDCLR = 1<<pinnumber;     // set bit 3 of Port D for output
}

void loop() { 
	int i;
	while(1) {
		LATDSET = 1<<pinnumber;       // set bit 3 of Port D
		for (i=0; i< 1000000; i++);
        
        LATDCLR = 1<<pinnumber;       // clear bit 3 of Port D
        for (i=0; i< 1000000; i++); 
  }
}

int main(void) {
    setup();
    loop();
}