#include<mega32.h>
#include<lcd.h>
#include<stdio.h>
#include<stdlib.h>
#asm
.equ __lcd_port=0x1b
#endasm
int s=0,m=0,h=0,t=0,r=0,q=0,w=0,sN=0,mN=0,hN=0;
int check=0;
char s1[3],m1[3],h1[3];
char s2[3],m2[3],h2[3];
interrupt[TIM2_OVF] void saat(void)
{
    s++;
    if(s==60)
    {
        m++;
        s=0;
    }
    if(m==60)
    {
        h++;
        m=0;        
    }            
    if(h==24)
    {
        h=0;
    }           
    itoa(s,s1);
    itoa(m,m1);
    itoa(h,h1);
    lcd_gotoxy(0,0);
    lcd_puts(h1);
    lcd_putsf(":");
    lcd_puts(m1);
    lcd_putsf(":");
    lcd_puts(s1);
}

void main(void)
{
    lcd_init(16);
    lcd_clear();
    
    DDRB=0x00;
    DDRC=0b00000001;
    
    PORTB.0=1;
    PORTB.1=1;
    PORTB.2=1;
    PORTB.3=1;
    
        itoa(sN,s2);
        itoa(mN,m2);
        itoa(hN,h2);
        
        lcd_gotoxy(0,1);
        lcd_puts(h2);
        lcd_putsf(":");
        lcd_puts(m2);
        lcd_putsf(":");
        lcd_puts(s2);
    
while(1)
{
    //start Timer
    if(PINB.0==0 && t==0)
    {
        TCCR2=0x05;
        ASSR=0x08;
        #asm("sei")
        TIMSK=0x40;
        check=1;
        t=1;
    }
    if(PINB.0==1) t=0;
    
    //for seconde
    if(PINB.1==0 && r==0)
    {
        sN++;
        itoa(sN,s2);
        itoa(mN,m2);
        itoa(hN,h2);
        
        lcd_gotoxy(0,1);
        lcd_puts(h2);
        lcd_putsf(":");
        lcd_puts(m2);
        lcd_putsf(":");
        lcd_puts(s2);
        r=1;
    }
    if(PINB.1==1) r=0;
    
    //for minute
    if(PINB.2==0 && q==0)
    {
        mN++;
        itoa(sN,s2);
        itoa(mN,m2);
        itoa(hN,h2);
        
        lcd_gotoxy(0,1);
        lcd_puts(h2);
        lcd_putsf(":");
        lcd_puts(m2);
        lcd_putsf(":");
        lcd_puts(s2);
        q=1;
    }
    if(PINB.2==1) q=0;
    
    //for hour
    if(PINB.3==0 && w==0)
    {
        hN++;
        itoa(sN,s2);
        itoa(mN,m2);
        itoa(hN,h2);
        
        lcd_gotoxy(0,1);
        lcd_puts(h2);
        lcd_putsf(":");
        lcd_puts(m2);
        lcd_putsf(":");
        lcd_puts(s2);
        w=1;
    }
    if(PINB.3==1) w=0;
    
    //check :
    if(s == sN && m == mN && h == hN && check==1)
    {
         PORTC = 0b00000001;
         TCCR2=0x00;
         ASSR=0x00;   
    }
}
}
