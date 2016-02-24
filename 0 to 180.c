// 180 degree programme
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define GPIO_LOCK_KEY            0x4C4F434B                                 // Unlocks the GPIO_CR register 
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTA_DATA_BITS_R  ((volatile unsigned long *)0x40004000)
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_IS_R         (*((volatile unsigned long *)0x40004404))
#define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)0x40004408))
#define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTA_IM_R         (*((volatile unsigned long *)0x40004410))
#define GPIO_PORTA_RIS_R        (*((volatile unsigned long *)0x40004414))
#define GPIO_PORTA_MIS_R        (*((volatile unsigned long *)0x40004418))
#define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)0x4000441C))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DR2R_R       (*((volatile unsigned long *)0x40004500))
#define GPIO_PORTA_DR4R_R       (*((volatile unsigned long *)0x40004504))
#define GPIO_PORTA_DR8R_R       (*((volatile unsigned long *)0x40004508))
#define GPIO_PORTA_ODR_R        (*((volatile unsigned long *)0x4000450C))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x40004514))
#define GPIO_PORTA_SLR_R        (*((volatile unsigned long *)0x40004518))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_ADCCTL_R     (*((volatile unsigned long *)0x40004530))
#define GPIO_PORTA_DMACTL_R     (*((volatile unsigned long *)0x40004534))	

	
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Init(void);
void PortA_Init(void);
unsigned long led;
unsigned long on;
unsigned long off;






void PortA_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000001;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTA_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
	GPIO_PORTA_CR_R = 0xFF;           // allow changes to PF4-0
  GPIO_PORTA_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTA_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTA_DIR_R = 0x2E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTA_AFSEL_R = 0x00;        // 6) disable alt funct on 
  GPIO_PORTA_DEN_R = 0xFF;          // 7) enable digital I/O on PF4-0
}

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 0x00FFFFFF;        // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it             
  NVIC_ST_CTRL_R = 0x00000005;          // enable SysTick with core clock
}


void SysTick_Wait(unsigned long delay)
{ NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0)
	{
	}
}


void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(24000);  // wait 10ms (assumes 50 MHz clock)
  }}

	
	
	int main(void)
	{int i;
		PortA_Init();
		SysTick_Init();
		while(1)
		{
			for(on=8000;on<=32000;on+=1000)
			{
				for(i=0;i<3;i++)
				{
		SysTick_Wait(320000-on);
			GPIO_PORTA_DATA_R|=0x20;
			SysTick_Wait(on);
			GPIO_PORTA_DATA_R&=~0x20;}}
			
			for(off=32000;off>=8000;off-=1000)
			{
				for(i=0;i<3;i++)
				{

				GPIO_PORTA_DATA_R&=~0x20;
				SysTick_Wait(320000-off);
				GPIO_PORTA_DATA_R|=0x20;
				SysTick_Wait(off);	}}
				
    
			
			
			
		}}
		
		