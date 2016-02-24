#include "PLL.h"
#include "tm4c123gh6pm.h" // Constant declarations to access port registers using 
// symbolic names instead of addresses
void SysTick_Wait10ms(unsigned long delay); 
void DisableInterrupts(void); // Disable interrupts 
void EnableInterrupts(void);  // Enable interrupts 
void WaitForInterrupt(void);  // low power mode 
void PortA_Init(void) ;  
void SysFun(void); 
void SysLoad(unsigned long period); 


int main(void) {  PLL_Init();   
	SysFun();  // 80 MHz 
	PortA_Init() ; // initialize output and interrupts  
	EnableInterrupts(); 
	/*Initialize ports and timers*/  
	while(1){ 
unsigned long i,j;

for(i=80000; i<=160000; i+=16000)            /*on time starts from 1msec to 2msec with a increment of 0.2msec risein on tim */
		{
			for(j=0;j<4;j++)
			{
				GPIO_PORTA_DATA_R |= (0x40); 
				SysLoad(i); 
				GPIO_PORTA_DATA_R &= ~(0x40); 
				SysLoad(1600000-i);
			}
		}
for(i=160000; i>=80000; i-=16000)
		{
			for(j=0;j<4;j++)
			{
				GPIO_PORTA_DATA_R |= (0x40); 
				SysLoad(i); 
				GPIO_PORTA_DATA_R &= ~(0x40); 
				SysLoad(1600000-i);
			}
		}
  }
}
void PortA_Init(void){ unsigned long volatile delay;
  /*PORT Initialization*/

SYSCTL_RCGC2_R |= 0x01; // Port A clock
delay = SYSCTL_RCGC2_R; // wait 3-5 bus cycles
GPIO_PORTA_DIR_R |= 0x40; // PA6 output
GPIO_PORTA_AFSEL_R &= ~0x40; // not alternative
GPIO_PORTA_AMSEL_R &= ~0x40; // no analog
GPIO_PORTA_PCTL_R &= ~0x0F000000; // bits for PA6
GPIO_PORTA_DEN_R |= 0x40; // enable PA6
}
void SysLoad(unsigned long period){
NVIC_ST_RELOAD_R = period-1;  // number of counts to wait  
	NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears  
	while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag 
		}
}
void SysFun(void)
	{
NVIC_ST_CTRL_R = 0;               // disable SysTick during setup  
	NVIC_ST_CTRL_R = 0x00000005; 
	} 

	
	
	  
	