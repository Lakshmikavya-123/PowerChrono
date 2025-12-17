 #include<LPC21XX.h>
#include "delay.h"
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "types.h"
extern u32 hour,min,sec,onhour,onmin,onsec,offhour,offmin,offsec,date,month,year,day;
u32 i_flag;
void set_time(void);
void eint0_isr(void)__irq
{
    CmdLCD(CLEAR_LCD);
    StrLCD("INTERRUPT RAISED");
    delay_s(1);
        i_flag=1;
    //set_time();
        EXTINT=1<<0;
        VICVectAddr=0;
}