PowerChrono is an intelligent time-based power management system designed to automate electrical devices based on predefined schedules.
It uses a Real Time Clock (RTC) to control device ON/OFF operations, reducing energy wastage and improving efficiency in industrial and automation environments.
 >>Aim
To design and implement a time-driven energy automation system that controls electrical loads automatically using RTC, keypad-based user input, and LCD display.
>>Objectives
Display RTC date and time on a 16×2 LCD
Allow users to edit RTC settings using a 4×4 matrix keypad
Enable users to set device ON and OFF timings
Automatically control device state (ON/OFF) based on programmed time
Provide user-friendly menu-driven operation using interrupt

 >>Block Diagram
Main Components:
LPC2148 Microcontroller
RTC
16×2 LCD
4×4 Matrix Keypad
External Interrupt Switch
Device (LED)
Hardware Requirements
LPC2148 Microcontroller
16×2 LCD Display
4×4 Matrix Keypad
LED (Device)
Push Button Switch
USB-UART Converter / DB-9 Cable
 >>Software Requirements
Embedded C
Flash Magic
Keil µVision (or equivalent IDE)
>>Project Workflow
Initialize RTC, LCD, keypad, LED, and interrupt
Continuously read RTC time and display it on LCD
Compare current time with user-defined ON/OFF times
Turn device ON if current time ≥ ON time and ≤ OFF time
Turn device OFF otherwise
On switch press, generate interrupt to enter edit menu
Allow user to:
Edit RTC information
Edit device ON/OFF timings
Exit to normal operation
>>Menu Structure
Main Menu
1. EDIT TIME
2. EDIT ON/OFF TIME
3. EXIT

>>RTC Edit Menu
1. HOUR
2. MIN
3. SEC
4. DAY
5. DATE
6. MONTH
7. YEAR
8. EXIT
>>Device Time Edit Menu
1. DEVICE ON TIME
2. DEVICE OFF TIME
3. EXIT
>> User Interaction
Keypad used to navigate menus and enter values
>>Input validation for:
Hours (0–23)
Minutes/Seconds (0–59)
Date (based on month & leap year)
Invalid entries prompt retry
Valid entries update RTC registers or timing variables
User Interaction
Keypad used to navigate menus and enter values
>>Input validation for:
Hours (0–23)
Minutes/Seconds (0–59)
Date (based on month & leap year)
Invalid entries prompt retry
Valid entries update RTC registers or timing variables
Interrupt Functionality
Dedicated switch triggers external interrupt
Interrupt pauses main loop and opens edit menu
After editing, system resumes normal operation
>>Applications
Industrial automation
Energy management systems
Smart electrical scheduling
Embedded real-time control systems
