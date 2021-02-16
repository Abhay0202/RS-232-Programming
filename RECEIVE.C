// receive.c
#define TXDATA 0x3F8
#define LSR 0x3FD
#define LCR 0x3FB

#include <stdio.h>
#include <conio.h>
#include <dos. h>


void setup_serial(void);

int get_character(void);

void setup_serial(void)
{
    outportb( LCR, 0x80);
// set up bit 7 to a 1 to set Register address bit
outportb(TXDATA,0x0C);
outportb(TXDATA+1,0x00);

/* load TxRegister with 12, crystal frequency is 1.8432MHz */
    outportb(LCR, 0x0A);
/*Bit pattern loaded is 00001010b, from msb to lsb these are: */
/*Access TD/RD buffer, normal output, no stick bit */
/*even parity, parity on, 1 stop bit, 7 data bits */
}

int get_character (void)
{
    int status;
    do
    {
	status = inportb(LSR) & 0x01;
    }while (status!=0x01);
/* Repeat until bit 1 in LSR is set */
return ( (int)inportb(TXDATA));
}

int main (void)
{
    int inchar;
    setup_serial();
    do
    {
	inchar=get_character();
	putchar ( inchar) ;
    }while(inchar!=4);
return(0) ;
}
