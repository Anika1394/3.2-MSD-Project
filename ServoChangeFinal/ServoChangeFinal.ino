#include <TimerOne.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <Keypad.h>
#include  <Servo.h>
const int DHTPIN = 16 ;
double Temp, RH;
#define DHTTYPE DHT22       // DHT22 sensor is used
DHT dht(DHTPIN, DHTTYPE);
#include "RTClib.h"
#include <DS1307.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd1(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd2(22, 23, 24, 25, 26, 27);
LiquidCrystal lcd3(28, 29, 30, 31, 32, 33);
/*Heart Beat*/
LiquidCrystal lcd4(44, 45, 46, 47, 48, 49);
LiquidCrystal lcd5(53, 52, 51, 50, 14, 15);
RTC_DS1307 rtc;

const int echoPin =9; // Echo Pin of Ultrasonic Sensor
const int triggerPin =10 ; // Trigger Pin of Ultrasonic Sensor
/*SERVO MOTOR*/
Servo servo1;
Servo servo2;
Servo servo3;// create servo object to control a servo
int pos = 0; 
 int pos2 = 0; 
int pos3 = 0; 

//int Servo2=55;
//int Servo3=56;

/*Heart Beat*/
int HBSensor = 43;
int HBCount = 0;
int HBCheck = 0;
int TimeinSec = 0;
int HBperMin = 0;
int HBStart = 42;
int HBStartCheck = 0;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'*', '0', '#', '+'}
};
byte rowPins[ROWS] = {38, 39, 40, 41}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {34, 35, 36, 37}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad cusKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int lcdDisplay[3];
int firstAlarmLED = 13;
int secondAlarmLED = 18;
int thirdAlarmLED = 19;
char key1;
char key2;
char key3;
int clock[7];
int hourArray[3];
int minuteArray[3];

int buzz1 = 8;
int buzz2 = 7;
int buzz3 = 6;

//alarm off and repeat
int countAlarm1Repeat=0;
int countAlarm2Repeat=0;
int countAlarm3Repeat=0;
int flagAlarm1Off=0;
int flagAlarm2Off=0;
int flagAlarm3Off=0;
long cm;



void lcd1SetTime();
void lcd2SetTime();
void lcd3SetTime();

void setup() {
  // put your setup code here, to run once:
//pinMode(Servo1,OUTPUT);
//pinMode(Servo2,OUTPUT);
//pinMode(Servo3,OUTPUT);
servo1.attach(54);
servo2.attach(55);
servo3.attach(56);

  pinMode(buzz1, OUTPUT);
  pinMode(buzz2, OUTPUT);
  pinMode(buzz3, OUTPUT);
  
  pinMode(firstAlarmLED, OUTPUT);
  pinMode(secondAlarmLED, OUTPUT);
  pinMode(thirdAlarmLED, OUTPUT);

  pinMode(triggerPin,OUTPUT); 
  pinMode(echoPin,INPUT);
   
 
  rtc.begin();

  
  lcd1.begin(16, 2);
  lcd1.clear();
  lcd1.setCursor(0, 1);

  lcd2.begin(16, 2);
  lcd2.clear();
  lcd2.setCursor(0, 1);

  lcd3.begin(16, 2);
  lcd3.clear();
  lcd3.setCursor(0, 1);

  lcdDisplay[0] = 1;
  lcdDisplay[1] = 1;
  lcdDisplay[2] = 1;

  Serial.begin(9600);


/*Heart Beat*/
  lcd4.begin(20, 4);
  pinMode(HBSensor, INPUT);
  pinMode(HBStart, INPUT_PULLUP);
  Timer1.initialize(800000); 
  Timer1.attachInterrupt( timerIsr );
  lcd4.clear();
  lcd4.setCursor(0,0);
  lcd4.print("Current HB  : ");
  lcd4.setCursor(0,1);
  lcd4.print("Time in Sec : ");
  lcd4.setCursor(0,2);
  lcd4.print("HB per Min  : 0.0");

//Temperature and humidity detector
   lcd5.begin(20, 4);

   dht.begin();
 
}

void loop() {
  
   RH = dht.readHumidity();
Temp =  dht.readTemperature();


lcd5.setCursor(0,0); 
lcd5.print("Temp= "); 
lcd5.print(Temp);
lcd5.print((char)223);
lcd5.print("C");
lcd5.setCursor(0,1); 
lcd5.print("RH= ");
lcd5.print(RH);
lcd5.print("%");
lcd5.setCursor(0,2); 
if(RH>40){
  lcd5.print("RH is not normal   ");
  
}
if(RH<=40){
   lcd5.print("Rh is normal   ");
}
lcd5.setCursor(0,3); 
if(Temp>23){
  lcd5.print("Temp is not normal   ");
  
}
if(Temp<=23){
   lcd5.print("Temp is okay   ");
}


  // put your main code here, to run repeatedly:

  /*Heart Beat*/
  if(digitalRead(HBStart) == LOW)
     { 
          
       lcd4.setCursor(0,3);
       lcd4.print("HB Counting ..             ");
       HBStartCheck = 1;
     }
   if(HBStartCheck == 1)
     {
      if((digitalRead(HBSensor) == HIGH) && (HBCheck == 0))
      {
        HBCount = HBCount + 1;
        HBCheck = 1;
        lcd4.setCursor(14,0);
        lcd4.print(HBCount);
        lcd4.print("   ");
      }
      if((digitalRead(HBSensor) == LOW) && (HBCheck == 1))
      {
        HBCheck = 0;   
      }
      if(TimeinSec == 10)
      {
          HBperMin = HBCount * 6;
          HBStartCheck = 0;
          lcd4.setCursor(14,2);
          lcd4.print(HBperMin);
          lcd4.print(". ");
          lcd4.setCursor(0,3);
          lcd4.print("Press Button again.");
          HBCount = 0;
          TimeinSec = 0;    
      }
  }


  



  // when reset is needed for each clock
  if (lcdDisplay[0] == 0 && lcdDisplay[1] == 0 && lcdDisplay[2] == 0)
  {
    key1 = cusKeypad.getKey();
    //Serial.println(key1);
    if (key1 == '*') {
      lcdDisplay[0] = 1;
      lcdDisplay[1] = 1;
      lcdDisplay[2] = 1;

      lcd1.clear();
      lcd2.clear();
      lcd3.clear();

      noTone(buzz1);
      noTone(buzz2);
      noTone(buzz3);
      
      digitalWrite(firstAlarmLED, LOW);
      digitalWrite(secondAlarmLED, LOW);
      digitalWrite(thirdAlarmLED, LOW);

      

    }
  }

  //for 1st alarm

  lcd1SetTime();

  // for 2nd alarm
  lcd2SetTime();

  // for 3rd alarm
  lcd3SetTime();

DateTime now = rtc.now();
  
  DateTime alarmRepeat (now + TimeSpan(0, 0, 2, 0));//if alarm is not off it will repeat after every 2 minutes
  
  // cm=distance();
   
   
   if (minuteArray[0] == now.minute() && hourArray[0] == now.hour()) {
    if(pos==0){
       for (pos = 0; pos <= 360; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);  
    // tell servo to go to position in variable 'pos'
  
       }
    }if(pos==360){
        for (pos = 360; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);  
    // tell servo to go to position in variable 'pos'
 
       }
    }
       cm=distance();
     if( flagAlarm1Off!=1){
      
       digitalWrite(firstAlarmLED, HIGH);
       tone(buzz1, 1000);
     
       alarmOneOFF();
    
      //Alarm Repeat 
      if(cm>=5 && now.second()>58 && countAlarm1Repeat<2){
         
             minuteArray[0]=alarmRepeat.minute();
             hourArray[0]=alarmRepeat.hour();
             countAlarm1Repeat++;
            
           } 
     } 
     
  }
  else {
    digitalWrite(firstAlarmLED, LOW);
    noTone(buzz1);

  }

  if (minuteArray[1] == now.minute() && hourArray[1] == now.hour()) {
  if(pos2==0){
       for (pos2 = 0; pos2 <= 360; pos2 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo2.write(pos2);  
    // tell servo to go to position in variable 'pos'
 
       }
    }if(pos2==360){
        for (pos2 = 360; pos2 >= 0; pos2 -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo2.write(pos2);  
    // tell servo to go to position in variable 'pos'

       }
    }
    cm=distance();
    if( flagAlarm2Off!=1){
       digitalWrite(secondAlarmLED, HIGH);
       tone(buzz2, 1000);
   
        alarmTwoOFF(); 
     
         //Alarm Repeat 
         if(cm>=5 && now.second()>58 && countAlarm2Repeat<2){
         
             minuteArray[1]=alarmRepeat.minute();
             hourArray[1]=alarmRepeat.hour();
             countAlarm2Repeat++;
            
           }
    }
    
  }
  else {
    digitalWrite(secondAlarmLED, LOW);
    noTone(buzz2);
  }

  if (minuteArray[2] == now.minute() && hourArray[2] == now.hour()) {
  if(pos3==0){
       for (pos3 = 0; pos3 <= 360; pos3 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo3.write(pos3);  
    // tell servo to go to position in variable 'pos'
 
       }
    }if(pos3==360){
        for (pos3 = 360; pos3 >= 0; pos3 -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo3.write(pos3);  
    // tell servo to go to position in variable 'pos'
  
       }
    }
    cm=distance();
    if( flagAlarm3Off!=1){
       digitalWrite(thirdAlarmLED, HIGH);
       tone(buzz3, 1000);

       alarmThreeOFF();

         //Alarm Repeat 
         if(cm>=5 && now.second()>58 && countAlarm3Repeat<2){
         
             minuteArray[2]=alarmRepeat.minute();
             hourArray[2]=alarmRepeat.hour();
             countAlarm3Repeat++;
            
           }
    }
  }
  else {
    digitalWrite(thirdAlarmLED, LOW);
    noTone(buzz3);
  }
  

 

}


void lcd1SetTime() {

  if (lcdDisplay[0] == 1)
  {
SetOption:
    lcd1.setCursor(0, 0);
    lcd1.print("Set time?");
    lcd1.setCursor(0, 1);
    lcd1.print("1.Yes    2.No");
  }

  while (lcdDisplay[0] == 1)
  {
    key1 = cusKeypad.getKey();

    if (key1 == '2') { //if no pressed
      lcd1.clear();
      lcdDisplay[0] = 0;
      hourArray[0] = -1;
      minuteArray[0] = -1;

    }


    else if (key1 == '1') { //if yes pressed


Initialize:
      lcd1.clear();
      lcd1.setCursor(0, 0);
      lcd1.print("Alarm: ");
      lcd1.setCursor(0, 1);
      lcd1.print("88:88 ");

      int check = 0;
      String hour1, hour2, min1, min2;
      String hour3, min3;
      while (1)
      {

        key1 = cusKeypad.getKey();
        lcd1.setCursor(0, 1);
        lcd1.print("_");

        // for set as before (using like back function)
        if (key2 == '#')
        {
          goto SetOption;
        }

        if (key2 == '-')
        {
          goto Initialize;
        }


        if (key1 == '0' || key1 == '1' || key1 == '2') // for hour 1st digit
        {
          lcd1.setCursor(0, 1);
          lcd1.print(key1);
          hour1 = key1;
          if ( key1 == '2')
            check = 1;

          break;
        }
      }

      while (1)
      {
        key1 = cusKeypad.getKey();
        lcd1.setCursor(1, 1);
        lcd1.print("_");

        // for set as before (using like back function)
        if (key1 == '#')
        {
          goto SetOption;
        }

        if (key1 == '-')
        {
          goto Initialize;
        }

        if (check == 1 ) // for hour 2nd digit checking if 1st digit is 2
        {
          if (key1 == '0' || key1 == '1' || key1 == '2' || key1 == '3')
          {
            lcd1.setCursor(1, 1);
            lcd1.print(key1);
            hour2 = key1;
            break;
          }
        }

        //if 1st digit is 1 or 0
        else if (check == 0)
        {
          if (key1 == '0' || key1 == '1' || key1 == '2' || key1 == '3' || key1 == '4' || key1 == '5'  || key1 == '6' || key1 == '7' || key1 == '8' || key1 == '9' )
          {
            lcd1.setCursor(1, 1);
            lcd1.print(key1);
            hour2 = key1;
            break;
          }
        }

      }


      hour3 = hour1 + hour2;
      hourArray[0] = hour3.toInt();
      Serial.print(hourArray[0]);

      while (1)
      {
        key1 = cusKeypad.getKey();
        lcd1.setCursor(3, 1);
        lcd1.print("_");

        // for set as before (using like back function)
        if (key1 == '#')
        {
          goto SetOption;
        }

        if (key1 == '-')
        {
          goto Initialize;
        }

        if (key1 == '0' || key1 == '1' || key1 == '2' || key1 == '3' || key1 == '4' || key1 == '5') // for min 1st digit
        {
          lcd1.setCursor(3, 1);
          lcd1.print(key1);
          min1 = key1;
          break;
        }
      }

      while (1)
      {
        key1 = cusKeypad.getKey();
        lcd1.setCursor(4, 1);
        lcd1.print("_");

        // for set as before (using like back function)
        if (key1 == '#')
        {
          goto SetOption;
        }

        if (key1 == '-')
        {
          goto Initialize;
        }

        // for min 2nd digit
        if (key1 == '0' || key1 == '1' || key1 == '2' || key1 == '3' || key1 == '4' || key1 == '5'  || key1 == '6' || key1 == '7' || key1 == '8' || key1 == '9')
        {
          lcd1.setCursor(4, 1);
          lcd1.print(key1);
          min2 = key1;
          break;
        }
      }

      min3 = min1 + min2;
      minuteArray[0] = min3.toInt();
      Serial.print("    ");
      Serial.print(minuteArray[0]);
      Serial.println();

      lcdDisplay[0] = 0;

      
       
    }
  }
}


void lcd2SetTime() {

  if (lcdDisplay[1] == 1)
  {
SetOption:
    lcd2.setCursor(0, 0);
    lcd2.print("Set time?");
    lcd2.setCursor(0, 1);
    lcd2.print("1.Yes    2.No");
  }

  while (lcdDisplay[1] == 1)
  {

    key2 = cusKeypad.getKey();
    if (key2 == '2') { // if no pressed
      lcd2.clear();
      lcdDisplay[1] = 0;
      hourArray[1] = -1;
      minuteArray[1] = -1;
    }


    else if (key2 == '1') { //if yes pressed


Initialize:
      lcd2.clear();
      lcd2.setCursor(0, 0);
      lcd2.print("Alarm: ");
      lcd2.setCursor(0, 1);
      lcd2.print("88:88 ");

      int check = 0;
      String hour1, hour2, min1, min2;
      String hour3, min3;
      while (1)
      {

        key2 = cusKeypad.getKey();
        lcd2.setCursor(0, 1);
        lcd2.print("_");

        // for set as before (using like back function)
        if (key2 == '#')
        {
          goto SetOption;
        }

        if (key2 == '-')
        {
          goto Initialize;
        }


        if (key2 == '0' || key2 == '1' || key2 == '2') // for hour 1st digit
        {
          lcd2.setCursor(0, 1);
          lcd2.print(key2);
          hour1 = key2;
          if ( key2 == '2')
            check = 1;

          break;
        }
      }

      while (1)
      {
        key2 = cusKeypad.getKey();
        lcd2.setCursor(1, 1);
        lcd2.print("_");

        // for set as before (using like back function)
        if (key2 == '#')
        {
          goto SetOption;
        }

        if (key2 == '-')
        {
          goto Initialize;
        }

        if (check == 1 ) // for hour 2nd digit checking if 1st digit is 2
        {
          if (key2 == '0' || key2 == '1' || key2 == '2' || key2 == '3')
          {
            lcd2.setCursor(1, 1);
            lcd2.print(key2);
            hour2 = key2;
            break;
          }
        }

        //if 1st digit is 1 or 0
        else if (check == 0)
        {
          if (key2 == '0' || key2 == '1' || key2 == '2' || key2 == '3' || key2 == '4' || key2 == '5'  || key2 == '6' || key2 == '7' || key2 == '8' || key2 == '9' )
          {
            lcd2.setCursor(1, 1);
            lcd2.print(key2);
            hour2 = key2;
            break;
          }
        }

      }


      hour3 = hour1 + hour2;
      hourArray[1] = hour3.toInt();
      Serial.print(hourArray[1]);

      while (1)
      {
        key2 = cusKeypad.getKey();
        lcd2.setCursor(3, 1);
        lcd2.print("_");

        // for set as before (using like back function)
        if (key2 == '#')
        {
          goto SetOption;
        }

        if (key2 == '-')
        {
          goto Initialize;
        }

        if (key2 == '0' || key2 == '1' || key2 == '2' || key2 == '3' || key2 == '4' || key2 == '5') // for min 1st digit
        {
          lcd2.setCursor(3, 1);
          lcd2.print(key2);
          min1 = key2;
          break;
        }
      }

      while (1)
      {
        key2 = cusKeypad.getKey();
        lcd2.setCursor(4, 1);
        lcd2.print("_");

        // for set as before (using like back function)
        if (key2 == '#')
        {
          goto SetOption;
        }

        if (key2 == '-')
        {
          goto Initialize;
        }

        // for min 2nd digit
        if (key2 == '0' || key2 == '1' || key2 == '2' || key2 == '3' || key2 == '4' || key2 == '5'  || key2 == '6' || key2 == '7' || key2 == '8' || key2 == '9')
        {
          lcd2.setCursor(4, 1);
          lcd2.print(key2);
          min2 = key2;
          break;
        }
      }

      min3 = min1 + min2;
      minuteArray[1] = min3.toInt();
      Serial.print("    ");
      Serial.print(minuteArray[1]);
      Serial.println();


      lcdDisplay[1] = 0;
    }

  }
}



void lcd3SetTime() {

  if (lcdDisplay[2] == 1)
  {
SetOption:
    lcd3.setCursor(0, 0);
    lcd3.print("Set time?");
    lcd3.setCursor(0, 1);
    lcd3.print("1.Yes    2.No");
  }
  while (lcdDisplay[2] == 1)
  {
    key3 = cusKeypad.getKey();

    if (key3 == '2') {
      lcd3.clear();
      lcdDisplay[2] = 0;
      hourArray[2] = -1;
      minuteArray[2] = -1;

    }

    else if (key3 == '1') { //if yes pressed


Initialize:
      lcd3.clear();
      lcd3.setCursor(0, 0);
      lcd3.print("Alarm: ");
      lcd3.setCursor(0, 1);
      lcd3.print("88:88 ");

      int check = 0;
      String hour1, hour2, min1, min2;
      String hour3, min3;
      while (1)
      {

        key3 = cusKeypad.getKey();
        lcd3.setCursor(0, 1);
        lcd3.print("_");

        // for set as before (using like back function)
        if (key3 == '#')
        {
          goto SetOption;
        }

        if (key3 == '-')
        {
          goto Initialize;
        }


        if (key3 == '0' || key3 == '1' || key3 == '2') // for hour 1st digit
        {
          lcd3.setCursor(0, 1);
          lcd3.print(key3);
          hour1 = key3;
          if ( key3 == '2')
            check = 1;

          break;
        }
      }

      while (1)
      {
        key3 = cusKeypad.getKey();
        lcd3.setCursor(1, 1);
        lcd3.print("_");

        // for set as before (using like back function)
        if (key3 == '#')
        {
          goto SetOption;
        }

        if (key3 == '-')
        {
          goto Initialize;
        }

        if (check == 1 ) // for hour 2nd digit checking if 1st digit is 2
        {
          if (key3 == '0' || key3 == '1' || key3 == '2' || key3 == '3')
          {
            lcd3.setCursor(1, 1);
            lcd3.print(key3);
            hour2 = key3;
            break;
          }
        }

        //if 1st digit is 1 or 0
        else if (check == 0)
        {
          if (key3 == '0' || key3 == '1' || key3 == '2' || key3 == '3' || key3 == '4' || key3 == '5'  || key3 == '6' || key3 == '7' || key3 == '8' || key3 == '9' )
          {
            lcd3.setCursor(1, 1);
            lcd3.print(key3);
            hour2 = key3;
            break;
          }
        }

      }


      hour3 = hour1 + hour2;
      hourArray[2] = hour3.toInt();
      Serial.print(hourArray[2]);

      while (1)
      {
        key3 = cusKeypad.getKey();
        lcd3.setCursor(3, 1);
        lcd3.print("_");

        // for set as before (using like back function)
        if (key3 == '#')
        {
          goto SetOption;
        }

        if (key3 == '-')
        {
          goto Initialize;
        }

        if (key3 == '0' || key3 == '1' || key3 == '2' || key3 == '3' || key3 == '4' || key3 == '5') // for min 1st digit
        {
          lcd3.setCursor(3, 1);
          lcd3.print(key3);
          min1 = key3;
          break;
        }
      }

      while (1)
      {
        key3 = cusKeypad.getKey();
        lcd3.setCursor(4, 1);
        lcd3.print("_");

        // for set as before (using like back function)
        if (key3 == '#')
        {
          goto SetOption;
        }

        if (key3 == '-')
        {
          goto Initialize;
        }

        // for min 2nd digit
        if (key3 == '0' || key3 == '1' || key3 == '2' || key3 == '3' || key3 == '4' || key3 == '5'  || key3 == '6' || key3 == '7' || key3 == '8' || key3 == '9')
        {
          lcd3.setCursor(4, 1);
          lcd3.print(key3);
          min2 = key3;
          break;
        }
      }

      min3 = min1 + min2;
      minuteArray[2] = min3.toInt();
      Serial.print("    ");
      Serial.print(minuteArray[2]);
      Serial.println();


      lcdDisplay[2] = 0;

    }

  }

}
//Alarm Off for 1st alarm
void alarmOneOFF(){
  
 cm=distance();
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(100);
  
  
  if(digitalRead(firstAlarmLED)==HIGH){
 
     if(cm<=4)
    {
      if(flagAlarm1Off==0){
        digitalWrite(firstAlarmLED,LOW);
        noTone(buzz1);
        flagAlarm1Off=1;
      }
      
    }
    
  
  } 
  
}

//Alarm Off for 2nd alarm
void alarmTwoOFF(){
  
 cm=distance();
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(100);
  
  
  if(digitalRead(secondAlarmLED)==HIGH){
 
     if(cm<=4)
    {
       if(flagAlarm2Off==0){
        
          digitalWrite(secondAlarmLED,LOW);
          noTone(buzz2);
          flagAlarm2Off=1;
         }
     
      }
    
    }
    
  
  } 
  
//Alarm Off for 3rd alarm
void alarmThreeOFF(){
  
 cm=distance();
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(100);
  
  
  if(digitalRead(thirdAlarmLED)==HIGH){
 
     if(cm<=4)
    {
      
      if(flagAlarm3Off==0){
        
        digitalWrite(thirdAlarmLED,LOW);
        noTone(buzz3);
        flagAlarm3Off=1;
      }
      
    }
    
  
  } 
  
}
long distance(){

  long duration, inches, cm;
  
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
  
    digitalWrite(triggerPin, LOW);

  
     duration = pulseIn(echoPin, HIGH); // using pulsin function to determine total time
     inches = microsecondsToInches(duration); // calling method
     cm = microsecondsToCentimeters(duration); // calling method
     
  
  return cm;
}
long microsecondsToInches(long microseconds) // method to convert microsec to inches 
{
 return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) // method to covnert microsec to centimeters
{
   return microseconds / 29 / 2;
}

/*Heart Beat*/
void timerIsr()
{
  if(HBStartCheck == 1)
  {
      TimeinSec = TimeinSec + 1;
      lcd4.setCursor(14,1);
      lcd4.print(TimeinSec);
      lcd4.print(" ");
  }
}
