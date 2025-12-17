#include<LPC21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "types.h"
#include "pin_function_defines.h"
#include "pin_connect_block.h"
#include "rtc.h"
#include "kpm.h"
#include "types.h"
#include "delay.h"
#include "defines.h"
#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16
#define LED 30
#define ONOFF_SW 5

u8 cgramLUT1[16]={0X0E,0X1F,0X1F,0X1F,0X1F,0X0E,0X0A,0X0A,0X0E,0X11,0X11,0X11,0X1F,0X0E,0X0A,0X0A};
u32 hour,min,sec,onhour,onmin,onsec,offhour,offmin,offsec,date,month,year,day;
extern u32 i_flag;
void eint0_isr(void)__irq;
void edit_RTC_SET_TIME(void);
void edit_device_set_time(void);
void Init_interrupt(void);
void set_time(void);

int main()
{
IODIR1|=1<<LED;
InitLCD();
Init_KPM();
RTC_Init();
Init_interrupt();
while(1)
{
        GetRTCTimeInfo(&hour,&min,&sec);
                DisplayRTCTime(hour,min,sec);
                GetRTCDay(&day);
                DisplayRTCDay(day);
                GetRTCDateInfo(&date,&month,&year);
                DisplayRTCDate(date,month,year);

                if(READBIT(IOPIN0,ONOFF_SW)==0)
                {
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("ONTIME:");
            CmdLCD(GOTO_LINE1_POS0+7);
                U32LCD(onhour);
                CmdLCD(GOTO_LINE1_POS0+9);
                CharLCD(':');
                CmdLCD(GOTO_LINE1_POS0+11);
                U32LCD(onmin);

                CmdLCD(GOTO_LINE2_POS0);
								StrLCD("OFTIME:");
            CmdLCD(GOTO_LINE2_POS0+7);
                U32LCD(offhour);
                CmdLCD(GOTO_LINE2_POS0+9);
                CharLCD(':');
                CmdLCD(GOTO_LINE2_POS0+11);
                U32LCD(offmin);
                delay_s(1);
                CmdLCD(CLEAR_LCD);
                while( READBIT(IOPIN0,ONOFF_SW)==0);
                CmdLCD(CLEAR_LCD);
                }

                if(i_flag==1)
                {
                i_flag=0;
                set_time();
                }
//              eint0_isr(void);
                if(((HOUR>=onhour)&&(MIN>=onmin))&&((HOUR<=offhour)&&(MIN<=offmin)))
                {
                IOSET1=1<<LED;
                CmdLCD(GOTO_LINE2_POS0+12);
                StrLCD("D:");
                BuildCGRAM(cgramLUT1,16);
                CmdLCD(GOTO_LINE2_POS0+14);
                 CharLCD(0);
                }
                else
                {
                IOCLR1=1<<LED;
                CmdLCD(GOTO_LINE2_POS0+12);
                StrLCD("D:");
                BuildCGRAM(cgramLUT1,16);
                CmdLCD(GOTO_LINE2_POS0+14);
        CharLCD(1);
                }
}
}
void Init_interrupt()
{
//cfg p0.1 pin as EINT0 input pin
CfgPortPinFunc(0,1,PIN_FUNC4);
//cfg VIC peripheral
//cfg EINT0 as irq types,default all are irq type
//VICIntSelect=0;
//enable EINT0 via VIC
VICIntEnable=1<<EINT0_VIC_CHNO;
//cfg EINT0 as v.irq with highest priority
//and allow to load eint0_isr addr
VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
//load eint0 isr addr
VICVectAddr0=(u32)eint0_isr;
//cfg external interrupt peripheral
//allow/enable EINT0,default all are enabled
//EXTINT=0;
//cfg eint0 as edge triggered
EXTMODE=1<<0;
//def all are falling edge
//EXTPOLAR=0;
//cfg eint0 status led pin as gpio out
}

                                           