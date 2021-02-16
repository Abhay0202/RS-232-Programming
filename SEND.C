//send.c
#define TXDATA 0x3F8
#define LSR 0x3FD
#define LCR 0x3FB

#include <stdio. h>
#include <conio.h>
#include <dos. h>


void setup_serial(void);
void send_character(int ch);

void setup_serial (void)
{
    outportb( LCR, 0x80);
// set up bit 7 to a 1 to set Register address bit
outportb(TXDATA,0x0C) ;
outportb(TXDATA+1,0x00);
*/
/* load TxRegister with 12, crystal frequency is 1.8432MHz */
    outportb(LCR, 0x0A);
/*Bit pattern loaded is 00001010b, from msb to lsb these are: */
/*Access TD/RD buffer, normal output, no stick bit */
/*even parity, parity on, 1 stop bit, 7 data bits */
}

void send_character(int ch)
{
char status;
    do
    {
	status = inportb(LSR) & 0x40;
    }while (status!=0x40);
	/*repeat until Tx buffer empty ie bit 6 set*/
	outportb(TXDATA, (char) ch);

}


int main (void)
{
    int ch;
    puts ("Transmitter program. Please enter text (Cntl-D to end)");
    setup_serial() ;
    do
    {
	ch=getch();
	send_character(ch);
     }while (ch!=4) ;
 return(0);
}