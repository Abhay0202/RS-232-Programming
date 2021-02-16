//This program transmits a character from COM1: and receives it via this port.
// The TD is connected to RD.

#define COM1BASE 0x3F8
#define COM2BASE Ox2F8
#define TXDATA COM1BASE
#define LCR (COM1BASE+3) /* Ox3FB line control */
#define LSR (COM1BASE+5) /* Ox3FD line status */
#include <conio.h> /* required for getch() */
#include <dos.h> /*required for inportb() and outportb() */
#include <stdio.h>

void setup_serial(void);
void send_character(int ch);
int get_character(void);

void setup_serial (void)
{
	outportb( LCR, 0x80);
	/* set up bit 7 to a 1 to set Register address bit */

	outportb(TXDATA,0X0C) ;        //setting Baud rate to 9600
	outportb(TXDATA+1,0x00) ;

	/* load TxRegister with 12, crystal frequency is 1.8432MHz */
	outportb(LCR, 0x0A);

/*Bit pattern loaded is 00001010b, from msb to 1sb these are: */
/* 0 - access TD/RD buffer, 0 - normal output * /
/* 0 - no stick bit, 0 - even parity * /
/*1 - parity on, 0 - 1 stop bit */
/*10 - 7 data bits */
}

void send_character(int ch)
{
  char status;
	do
	{
	    status = inportb(LSR) & 0x40;
	} while (status!=0x40);
/*repeat until Tx buffer empty ie bit 6 set*/
outportb(TXDATA, (char) ch);
}

int get_character (void)
{
	int status;
		do
		{
			status = inportb(LSR) & 0x01;
		} while (status!=0x01);
/* Repeat until bit 1 in LSR is set */
	return ( (int)inportb(TXDATA));
}

int main (void)
{
	int inchar,outchar;
	setup_serial() ;
	do
	{
		puts("Enter char to be transmitted (Cntrl-D to end)");
		outchar=getch();
		send_character(outchar) ;
		inchar=get_character();
		printf ("Character received was %c\n", inchar) ;
	}while (outchar!=4);
	return(0);
}d