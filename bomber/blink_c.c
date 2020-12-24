#include <stdint.h>

/* Values from the BCM2835-ARM-Peripherals.pdf manual */

/* Note this value is different on pi1 models */
#define IO_BASE	0x3f000000


#define GPIO_BASE	(IO_BASE+0x200000)

#define GPIO_GPFSEL0	0
#define GPIO_GPFSEL1	1
#define GPIO_GPFSEL2	2
#define GPIO_GPFSEL3	3
#define GPIO_GPFSEL4	4

#define GPIO_GPSET0	7
#define GPIO_GPSET1	8

#define GPIO_GPCLR0	10
#define GPIO_GPCLR1	11


#define GPIO_GPLEV0	13
/* GPIO PIN EVENT DETECTION 0*/

#define RPI_SYSTIMER_BASE	(IO_BASE + 0x3000)

typedef struct {
    volatile uint32_t control_status;
    volatile uint32_t counter_lo;
    volatile uint32_t counter_hi;
    volatile uint32_t compare0;
    volatile uint32_t compare1;
    volatile uint32_t compare2;
    volatile uint32_t compare3;
} rpi_sys_timer_t;

static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;

rpi_sys_timer_t* RPI_GetSystemTimer(void)
{
    return rpiSystemTimer;
}

void RPI_WaitMicroSeconds( uint32_t us )
{
    volatile uint32_t ts = rpiSystemTimer->counter_lo;

    while( ( rpiSystemTimer->counter_lo - ts ) < us )
    {
        /* BLANK */
    }
}

/* Reference to the GPIO space */
/* An array of 32-bit integers */
volatile uint32_t *gpio;

/* main function */
int main(int argc, char **argv) {

	/* Point to the physical GPIO region */
	gpio = (uint32_t *)GPIO_BASE;

	/* Enable GPIO18 in the proper GPFSEL1 register to OUTPUT(TRIGGLE)*/
	// 1 is output
	gpio[GPIO_GPFSEL1]&=~(0x7<<24);
	gpio[GPIO_GPFSEL1]|= (1<<24);
	
	/* Enable GPIO23 in the proper GPFSEL2 register to OUTPUT(BUZZER)*/
	gpio[GPIO_GPFSEL2]&=~(0x7<<9);
	gpio[GPIO_GPFSEL2]|= (1<<9);
	
	/* Enable GPIO24 in the proper GPFSEL2 register to INPUT(ECHO)*/
	// 0 input
	gpio[GPIO_GPFSEL2]&=~(0x7<<12);
	gpio[GPIO_GPFSEL2]|= (0<<12);
	
	while(1) {
		/*trigerwait High*/
		
		
		gpio[GPIO_GPSET0]&=~(0x1<<18);  // set 18 GPIO_18 ****not use 
		gpio[GPIO_GPSET0]|= (1<<18);
		
		
		/*start*/
		RPI_WaitMicroSeconds(10000);
		
		gpio[GPIO_GPCLR0]&=~(0x1<<18); // clr 18 ****not use
		gpio[GPIO_GPCLR0]|= (1<<18);
		
		/*close buz*/
		gpio[GPIO_GPCLR0]&=~(0x1<<23);	// clr 23 is GPIO_23
		gpio[GPIO_GPCLR0]|= (1<<23);
		//gpio[GPIO_GPSET0]&=~(0x1<<23);
		//gpio[GPIO_GPSET0]|= (1<<23);
		

		/*w8 for sensor is cuming */
		while(gpio[GPIO_GPLEV0] & (1 << 24))
		{
		/*run buz*/
		
		gpio[GPIO_GPSET0]&=~(0x1<<23);	// set 23 buz
		gpio[GPIO_GPSET0]|= (1<<23);

		//gpio[GPIO_GPCLR0]&=~(0x1<<23);
		//gpio[GPIO_GPCLR0]|= (1<<23);
		

		}
		
		
	}


	/* Hang forever; there is no OS to return to! */
	while(1) {
	}

	return 0;
}
