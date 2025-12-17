#include<LPC21XX.h>
#include "delay.h"
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "types.h"
extern u32 hour,min,sec,onhour,onmin,onsec,offhour,offmin,offsec,date,month,year,day;
//edit_RTC_SET_TIME(u32,u32,u32,u32,u32,u32,u32);
//edit_device_set_time(u32,u32,u32,u32,u32,u32);
//void display_menu(void);
void edit_RTC_SET_TIME(void);
void edit_device_set_time(void);
s8 week_1[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
u32 KeyV;

void set_time(void)
{
CmdLCD(CLEAR_LCD);
StrLCD("INTERRUPT RAISED");
delay_s(1);
CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1.EDIT RTC INFO");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("2.DEVICE ");
CmdLCD(GOTO_LINE2_POS0+9);
StrLCD("3.EXIT");
//delay_s(1);
KeyV=KeyScan();
delay_ms(200);
while(ColScan()==0);
//delay_ms(200);
//CmdLCD(CLEAR_LCD);
//delay_s(1);
switch(KeyV)
{
case 1:
CmdLCD(CLEAR_LCD);
edit_RTC_SET_TIME();
CmdLCD(CLEAR_LCD);
return;
//DisplayRTCTime(hour,min,sec);
case 2:
CmdLCD(CLEAR_LCD);
edit_device_set_time();
CmdLCD(CLEAR_LCD);
return;
//DisplayRTCTime(onhour,onmin,onsec);
//DisplayRTCTime(offhour,offmin,offsec);
case 3:
CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("EXIT");
return;
default: 
StrLCD("INVALID");
delay_s(1);
break;

}
}
void edit_RTC_SET_TIME(void)
{
menu2:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1.H 2.M 3.S ");
CmdLCD(GOTO_LINE1_POS0+11);
StrLCD("4.D");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("5.DT 6.MT 7.Y");
CmdLCD(GOTO_LINE2_POS0+13);
StrLCD("8.E");
//CmdLCD(CLEAR_LCD);
KeyV=KeyScan();
delay_ms(200);
while(ColScan()==0);
//CmdLCD(CLEAR_LCD);
switch(KeyV)
{
case 1:	
h:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit hour");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&hour);
if(hour>23&&hour<1)
{
StrLCD("Invalid hours!enter again");
goto h;
}
HOUR=hour;
goto menu2;
case 2:
m:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit min");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&min);
if(min>59&&min<1)
{
StrLCD("Invalid min !enter again");
goto m;
}
MIN=min;
goto menu2;
case 3:
s:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit sec");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&sec);
if(sec>59&&sec<1)
{
StrLCD("Invalid sec !enter again");
goto s;
}
SEC=sec;
goto menu2;
case 4:
d:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit day");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&day);
if(day>6&&day<1)
{
StrLCD("Invalid day !enter again");
goto d;
}
DOW=day;
goto menu2;
case 5:
dt:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit date");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&date);
if(date>31&&date<1)
{
StrLCD("Invalid date !enter again");
goto dt;
}
DOM=date;
goto menu2;
case 6:
mn:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit mon");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&month);
if(month>12&&month<1)
{
StrLCD("Invalid month !enter again");
goto mn;
}
MONTH=month;
goto menu2;
case 7:
y:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("edit year");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&year);
if(year>4095&&year<1)
{
StrLCD("Invalid year!enter again");
goto y;
}
YEAR=year;
goto menu2;
case 8:
CmdLCD(CLEAR_LCD);
return;
default:
goto menu2;
}
}
void edit_device_set_time(void)
{
menu3:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1.E.ONTIME3.EXIT");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("2.E.OFFTIME");
//delay_ms(200);
KeyV=KeyScan();
delay_ms(200);
//CmdLCD(CLEAR_LCD);
switch(KeyV)
{
case 1:
doh:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1-24 on hrs");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&onhour);
if(onhour>23&&onhour<1)
{
StrLCD("Invalid device on time in hr!enter again");
goto doh;
}
dom:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1-59 on min");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&onmin);
if(onmin>59&&onmin<1)
{
StrLCD("Invalid device on time in min!enter again");
goto dom;
}
goto menu3;
case 2:
dofh:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1-24 off hrs");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&offhour);
if(offhour>23&&offhour<1)
{
StrLCD("Invalid device off time in hr!enter again");
goto dofh;
}
dofm:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0);
StrLCD("1-59 off min");
CmdLCD(GOTO_LINE2_POS0);
ReadNum(&offmin);
if(offmin>59&&offmin<1)
{
StrLCD("Invalid device off time in min!enter again");
goto dofm;
}
case 3:return;
default:
goto menu3;
}
}
