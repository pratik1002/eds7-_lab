#include "PLL.h"
#include "tm4c123gh6pm.h"
// Constant declarations to access port registers using 
// symbolic names instead of addresses

void SysTick_Wait10ms(unsigned long delay);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

void SysFun(void);
void SysLoad(unsigned long period);
void SysTick_Init(void);
void PortB_Init(void);

// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){
  PLL_Init();  
	
  	// 80 MHz
   
	// initialize output and interrupts
  EnableInterrupts();
	 PortB_Init();/*Initialize ports and timers*/
	 SysTick_Init();
  while(1){   
  
		/*Your code goes here*/
		GPIO_PORTB_DATA_R=0X05;
		SysTick_Wait10ms(1);
		GPIO_PORTB_DATA_R=0X06;
		SysTick_Wait10ms(1);
		GPIO_PORTB_DATA_R=0X0A;
		SysTick_Wait10ms(1);
		GPIO_PORTB_DATA_R=0X09;
		SysTick_Wait10ms(1);
		
  }
}


void SysLoad(unsigned long period){

	
	NVIC_ST_RELOAD_R = period-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
	
}

void SysFun(void){
	
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;
          
} 

void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<=delay; i++){
    SysLoad(800000);  // wait 10ms
  }
}

void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x02;          // 1) activate Port B
  delay = SYSCTL_RCGC2_R;          // allow time for clock to stabilize
                                   // 2) no need to unlock PB7-0
  GPIO_PORTB_AMSEL_R &= ~0xFF;     // 3) disable analog functionality on PB7-0
  GPIO_PORTB_PCTL_R = 0x00000000;  // 4) configure PB7-0 as GPIO
  GPIO_PORTB_DIR_R |= 0xFF;        // 5) make PB7-0 out
  GPIO_PORTB_AFSEL_R &= ~0xFF;     // 6) disable alt funct on PB7-0
  GPIO_PORTB_DR8R_R |= 0xFF;       // enable 8 mA drive on PB7-0
  GPIO_PORTB_DEN_R |= 0xFF;        // 7) enable digital I/O on PB7-0
}
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 0x00FFFFFF;        // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it             
  NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock
}
