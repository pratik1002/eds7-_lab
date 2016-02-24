
*/

// PD3 is an output to LED output, positive logic
// PD0 is an input from switch, positive logic
// to set the switch in the simulator type this into command window
// PORTD = 1 
// to release the switch in the simulator type this into command window
// PORTD = 0 
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
unsigned long in,out;
int main(void){ unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x08;           // Port D clock
  delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
  GPIO_PORTD_DIR_R |= 0x08;         // PD3 output
  GPIO_PORTD_DIR_R &= ~0x01;        // PD0 input 
  GPIO_PORTD_AFSEL_R &= ~0x09;      // not alternative
  GPIO_PORTD_AMSEL_R &= ~0x09;      // no analog
  GPIO_PORTD_PCTL_R &= ~0x0000F00F; // bits for PD3, PD0
  GPIO_PORTD_DEN_R |= 0x09;         // enable PD3, PD0
  while(1){
    in = (GPIO_PORTD_DATA_R&0x01); // in 0 if not pressed, 1 if pressed
    out = (in^0x01)<<3;   // out 8 if not pressed, 0 if switch pressed
    GPIO_PORTD_DATA_R = out;
  }
}

