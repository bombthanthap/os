/* Barebones code to Blink LED on Raspberry Pi board */

/* Defines from the BCM2835 ARM Peripherals Document */

/* Note, the GPIO base is different on a pi2/3 vs pi1 */
.equ GPIO_BASE,		0x3f200000

.equ GPIO_GPFSEL0,	0x00
.equ GPIO_GPFSEL1,	0x04
.equ GPIO_GPFSEL2,	0x08
.equ GPIO_GPFSEL3,	0x0c
.equ GPIO_GPFSEL4,	0x10

.equ GPIO_GPSET0,	0x1c
.equ GPIO_GPSET1,	0x20

.equ GPIO_GPCLR0,	0x28
.equ GPIO_GPCLR1,	0x2C


.globl _start
_start:

	/* Load the GPIO region into r0 */
	ldr	r0,=GPIO_BASE

	/* Enable GPIO18 by writing the proper value to the GPFSEL register */

	/* YOUR CODE HERE */


blink_loop:

	/* Write 1 to 18th bit of SET GPIO register	*/

	/* YOUR CODE HERE */

	/* delay */
	mov	r2,#0x50000
delay_loop:
	subs	r2,r2,#1
	bne	delay_loop


	/* Write 1 to 18th bit of CLEAR GPIO register	*/

	/* YOUR CODE HERE */

	/* delay */
	mov	r2,#0x50000
delay_loop2:
	subs	r2,r2,#1
	bne	delay_loop2



	b	blink_loop		/* blink forever */

should_never_get_here:
	wfe				/* suspend CPU, low-power */
	b	should_never_get_here	/* branch forever */

