# 3.2-MSD-Project

## Automatic Pill Dispenser 

### Objective
Our project’s main aim is to make a smart medicine box for those users
who regularly take medicines and the prescription of their medicine is very
long as it is hard to remember to patients and also for their care giver.
Also Old age patients suffer from problems of forget to take pills on proper
time which causes certain health issues for patients having permanent diseases like diabetes, blood pressure, breathing problem, heart problems,
cancer diseases etc. Thus based on these problems we have decided to
make Medi-minder which will solve these problems by setting up time
table of prescribed medicines given in prescription. This smart box be
served for some more purposes such as pulse rate measurement, temperature and humidity measurement of room. The environmental control is
very important for a patient. So, he/she needs to know that. A patient
also needs to know his/her pulse rate. Pulse rate indicates the strength
of the pulse. Our Medi-minder will serve these purposes for patients to
ensure healthy life.

### Required Components
These following parts and tools are required for building this project
- Arduino Mega 2560: The Arduino MEGA 2560 can be used to design for projects that require more I/O lines, more sketch memory and more RAM. With 54 digital I/O pins, 16 analog inputs and
a larger space for your sketch it is the recommended board for 3D
printers and robotics projects. In our project it is used to connect
and control all the different modules.

- RTC(Real Time Clock for Alarm): The RTC module is used
to set the time for alarm.
1
- POT(10k): Manually varies resistance to control the flow of electric
current. Used to get different distance value from ultrasonic sensor.
- Servo Motor: In our project, Servo motor is used to move the
wheel backward and open the box cover.
- Push Button: Causes a temporary change in the state of an electrical circuit. Used to turn on the heartbeat sensor to take pulse and
measure pulse rate.
- 4*4 matrix Keypad: Allows to quickly input numeric values. For
our project it is used to take input to set alarm for a specific time.
- Buzzer: Typically used as alarm devices. In our project buzzers
are used for alarms and confirmation sounds.
- Box: Box is used in our project to keep pills.
- Resistor(1k and 10k): Implements electrical resistance as a circuit
element. Used for the same purpose in our project.
- 16*2 LCD Display: Uses LCD technology to display characters.
Used to show various texts and data in our project.
- 20*4 LCD Display: Uses LCD technology to display characters.
Used to show various texts and data in our project.
- LED: It emits light when current flows through it. In our project
LED is used to represent various light bulbs when the alarm goes on
at the specified time.
- Breadboard: Used to make quick electrical connections between
components.
- Male-male/ female-female/ male-female jumper wires: Generally used to connect various components together. Used for the
same purpose in our project.
- Battery(9volt): Acts as power source. Used for the same purpose
in our project.
- Ultrasonic sensor: Ultrasonic sensors work by emitting sound
waves at a frequency too high for humans to hear. They then wait
for the sound to be reflected back, calculating distance based on the
time required. This is similar to how radar measures the time it
2
takes a radio wave to return after hitting an object. Used for the
same purpose in our project.
- Heartbeat sensor: The Heartbeat sensor is used to measure pulse
rate.
- Logic-state: Used to take as pulse in our project.
- DHT22 sensor: The DHT22 sensor is used to measure room temperature and humidity in our project.


## Working Flow
The flow of working is discussed below:
- The DHT22 sensor which is used in home appliances and consumer
products for measuring temperature and humidity values. It is one of
the most important sensors, in medical units to detect the humidity
values in isolation unit of patients. As soon as the power is turned
on, the DHT22 sensor will sense the temperature and humidity of
room and show it in the 20x4 LCD monitor. It will also show the
humidity and temperature is favorable for patient’s health or not.
- Medicines will be pre-loaded by the user to the corresponding pill
box(day/noon/night).User can set the time by using keypad to give
input and RTC module will set the time for alarm.The time set for
notification will be displayed on the LCD.

- There are 1 keypad and 3 LCDs for taking input and showing the it
for alarm in our project. After running the project 1st LCD will ask
”Want to set alarm?” and there are two options: 1.Yes 2.No . If we
press 2 The 1st LCD will go off/clear and 2nd LCD will work like the
1st one. If we press 1 then it will show ”Set Alarm:” and a format
will show like ”88:88”. We can set our alarm here. For hour’s 1st
digit if we press 0/1/2 button it will show on lcd. but 3/4/5/6/7/8/9
won’t show up although we press it in keypad as hour’s 1st digit can
be greater than 2. for hour’s 2nd digit there are two conditions. If
it is 0/1 then it will take 0-9. but if the 1st digit is 2 then it will
only take 0-3 although other key’s are pressed. because 23 is the
last valid hour. For minute, the 1st digit can be 0-5. other keys
won’t work. because 59 is the last valid minute. for minute’s 2nd
digit 0-9 will be allowed. we are using string for digits. The strings
are converted to integer when they are put in the array. There will
be 1 array for keeping the track of hours for 3 lcds and 1 array for
keeping the track of minutes for 3 lcds . There are two additional
feature during the time of taking input. when a person starts to set
alarm and press key, if he set wrong key then he can press ”-” button
then it will go to ”initialization”. that means ”88:88” will show up
again for that lcd. if one press ”=” during setting alarm then it will
go to ”set option”. that means again it will ask ”want to set time?
1.yes 2.no”. Then user can again choose it according to his demand.
After an action is done for lcd 1 same things will happen to lcd 2.
And after an action is taken for lcd 2 same things will happen for
lcd 3. after taking actions for the 3 lcds one can press ”on” button
on the keyboard and it will start work from the beginning of 1st
lcd and onwards.User can use this feature if he wants to change his
alarm time. The buzzer will start to buzz during the alarm time.
the alarm is matched with real time clock using RTC. Description of
using RTC is discussed below.
- When the time set for alarm matches with the real time clock ,a
notification will be given by ringing the buzzer and the LED of the
corresponding pill box will be lighten up for 1 minute. RTC module
will set the time for alarm.
- Along with buzzer and LED,the cover of the specific pill box will
open by the servo motor.The push button attached with the servo
motor will help it to move the wheel backward and open the box
cover.

- There will be a ultrasonic sensor on the top of each box.While the
alarm is running if the distance between patient and box is reduced(less than or equal 4cm), then the pin of the buzzer and LED
will get a LOW value and alarm will off.If the distance of patient
and box is not reduced and it is greater than 4 cm then the buzzer
and LED will give alarm for 3 times with a time laps of 2 minutes.
- The heartbeat sensor starts with pressing a push button. After pressing the push button, time-count starts and the sensor take pulse from
patient’s finger. The 20x4 LCD will show the time in second, the
pulse taken from patient’s finger will be shown in the LCD monitor.
After 10 seconds, the patient can see his/her pulse rate per minute.
Because the pulse rate of 10 seconds will be multiplied with 6 and
provide the result on the basis of minute.

