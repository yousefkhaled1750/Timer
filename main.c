#include <stdint.h>
#include <TM4C123GH6PM.h>

void init(void);
void delay_ms(uint16_t period);
void init(void){
	SYSCTL->RCGCGPIO = 0x20;
	while(SYSCTL->PRGPIO == 0);
	
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR = 0x0E;
	GPIOF->DEN = 0x0E;
	GPIOF->DIR = 0x0E;
	
}

void delay_ms(uint16_t period){
	uint16_t i;
	SYSCTL->RCGCTIMER |= 0x01;
	TIMER0->CTL = 0;
	TIMER0->CFG = 0x04;
	TIMER0->TAMR = 0x02;
	TIMER0->TAILR = 16000 - 1;
	TIMER0->ICR |= 0x01;
	TIMER0->CTL |= 0x01;
	
	for( i = 0; i<=period; i++){
		while ((TIMER0->RIS & 0x1) == 0);
		TIMER0->ICR |= 0x01;
		
	}
	
}

int main(void){

	init();
	while(1){
	GPIOF->DATA = 0x02;
	delay_ms(1000);
	GPIOF->DATA = 0;
	delay_ms(1000);
	}
}

