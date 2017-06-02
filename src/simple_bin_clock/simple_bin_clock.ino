//5 BUTTONS



#include "Wire.h" //damit man i2c benutzen kann
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h> //damit man die led benutzen kann
const int btn_add_pin = 2;
const int btn_sub_pin = 3;
const int btn_time_pin = 4;
const int btn_alarm_pin = 5;
const int btn_sone_pin = 6;
const int led_pin = 7; //an welchem pin ist der Din vom strip angeschlossen
const int led_amount = 16; //anzahl der leds im strip (2x4*2)
const int beeper_pin = 13; //pin fuer den beeper
//hier sind die states der buttons drinne 1 wenn gedrckt 0 wenn nicht
int btn_add_state = 0;
int btn_sub_state = 0;
int btn_time_state = 0;
int btn_alarm_state = 0;
int btn_sone_state = 0;
int prev_state_button = 0;
//fuer das farbrad
byte wheel_pos_h = 0; //0-255 Farbe der stunden
byte wheel_pos_m = 0;//0-255 Farbe der minuten
//hier werden die farben fuer minuten und stunden gespeichert  0=R, 1=G, 2=B
int wheel_color_h[3]; 
int wheel_color_m[3];
//hier ist die aus farbe (r,g,b)
int wheel_color_h_aus[3] = {1,1,1};
int wheel_color_m_aus[3] = {1,1,1};
//hier ist die nachtmode farbe (r,g,b)
int nightmode_color_m[3] = {0,0,0};
int nightmode_color_h[3] = {0,0,0};

int nightmode_color_m_aus[3] = {0,0,0};
int nightmode_color_h_aus[3] = {0,0,0};
//NACHTMODE VARS
int nthstate = 0; // ist der nachtmode gerade aktiv (0-1)
int nthen = 0; // nachmode an oder aus (0-1)
int nth = 0; //startstunde des nachtmode (0-23)
int nthe = 7;//endstunde des nachtmode)0-23)
//ALARM VARS
int alarm_en = 0; //ALARM ON/OFF (0-1)
int alarm_h = 0; //Alarm-Stunde
int alarm_m = 0; // Alarm-Minute
int alarm_process = 0;  //klingelt es gerade
int alarm_state = 0; // klingel trigger
//damit werden die leds angesprochen dadurch ist das ganze sehr einfach
Adafruit_NeoPixel strip = Adafruit_NeoPixel(led_amount, led_pin, NEO_RGB + NEO_KHZ800);
//damit man das uhrmodul lesen kann denn die hat eine bestimmte adresse und die ist hier definiert
#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address
// Arduino version compatibility Pre-Compiler Directives
#if defined(ARDUINO) && ARDUINO >= 100   // Arduino v1.0 and newer
  #define I2C_WRITE Wire.write 
  #define I2C_READ Wire.read
#else                                   // Arduino Prior to v1.0 
  #define I2C_WRITE Wire.send 
  #define I2C_READ Wire.receive
#endif
byte decToBcd(byte val){return ( (val/10*16) + (val%10) );}
byte bcdToDec(byte val){return ( (val/16*10) + (val%16) );}
//HIER SIND ALLE ZEIT VARIABLEN DRINNEN
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year, _hour;
byte test;
byte zero;
//variablen fur das splitten von decimaler zeit zu binaer
int _value;
byte binwert_s_z;
byte binwert_s_e;
int s_z = 0;
int s_e = 0; 



void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  zero=0x00;
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

eeprom_read();




/*
   second = 0;
   minute = 29;
   hour = 20;

   dayOfWeek = 1;
   dayOfMonth = 1;
   month = 1;
   year= 1;
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   I2C_WRITE(zero);
   I2C_WRITE(decToBcd(second) & 0x7f);    // 0 to bit 7 starts the clock
   I2C_WRITE(decToBcd(minute));
   I2C_WRITE(decToBcd(hour));      // If you want 12 hour am/pm you need to set                                  // bit 6 (also need to change readDateDs1307)
   I2C_WRITE(decToBcd(dayOfWeek));
   I2C_WRITE(decToBcd(dayOfMonth));
   I2C_WRITE(decToBcd(month));
   I2C_WRITE(decToBcd(year));
   Wire.endTransmission(); 
*/   
   
   
}



void loop() {
  // put your main code here, to run repeatedly:
color_wheel();
getDateDs1307();
button();
soundAlarm();
delay(200);
//display_time(7, 7);  
}


void color_wheel(){
wheel_h();
wheel_m();
}






// Gets the date and time from the ds1307 and prints result
void getDateDs1307()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  I2C_WRITE(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  second     = bcdToDec(I2C_READ() & 0x7f);
  minute     = bcdToDec(I2C_READ());
  hour       = bcdToDec(I2C_READ() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(I2C_READ());
  dayOfMonth = bcdToDec(I2C_READ());
  month      = bcdToDec(I2C_READ());
  year       = bcdToDec(I2C_READ());

if(nthen == 1){
//LIEGT DIE ZEIT ZWISCHEN DEN BEIDEN GERENDZEN
if(nth > nthe-1){
//WENN ANFANG > ALS ENDE
if(hour <= nth && hour <= nthe-1){
nthstate = 1;
}else if(hour >= nth && hour >= nthe-1){
nthstate = 1;
}else{
nthstate = 0;
}
}else if (nth < nthe-1){
  //WENN ANFANG > ALS ENDE
if(hour <= nth && hour >= nthe-1){
nthstate = 1;
}else if(hour >= nth && hour <= nthe-1){
nthstate = 1;
}else{
nthstate = 0;
}
}else if( nth == nthe-1){
  if(hour == nth || hour == nthe-1){
  nthstate = 1;
  }else{
  nthstate = 0;
  }
}else{
nthstate = 0;
}
}else{
nthstate == 0;
}
if(nthstate == 1 && nthen == 1){

//NACHTMODE AKTIVE

//Hier einfach die farben mit der nachtmode farbe berschreoben
 wheel_color_h[0] = nightmode_color_h[0]; 
 wheel_color_h[1] = nightmode_color_h[1]; 
 wheel_color_h[2] = nightmode_color_h[2]; 

wheel_color_m[0] = nightmode_color_m[0];
wheel_color_m[1] = nightmode_color_m[1];
wheel_color_m[2] = nightmode_color_m[2];


wheel_color_h_aus[0] = nightmode_color_h_aus[0];
wheel_color_h_aus[1] = nightmode_color_h_aus[1];
wheel_color_h_aus[2] = nightmode_color_h_aus[2];

wheel_color_m_aus[0] = nightmode_color_m_aus[0];
wheel_color_m_aus[1] = nightmode_color_m_aus[1];
wheel_color_m_aus[2] = nightmode_color_m_aus[2];


}else{
  
  //NACHTMODE NICHT AKTIV


  
}
display_time(hour, minute);  
}





void setDateDs1307()                
{
   second = 0;
  // minute = 0;
  // hour = 0;

   dayOfWeek = 1;
   dayOfMonth = 1;
   month = 1;
   year= 1;
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   I2C_WRITE(zero);
   I2C_WRITE(decToBcd(second) & 0x7f);    // 0 to bit 7 starts the clock
   I2C_WRITE(decToBcd(minute));
   I2C_WRITE(decToBcd(hour));      // If you want 12 hour am/pm you need to set                                  // bit 6 (also need to change readDateDs1307)
   I2C_WRITE(decToBcd(dayOfWeek));
   I2C_WRITE(decToBcd(dayOfMonth));
   I2C_WRITE(decToBcd(month));
   I2C_WRITE(decToBcd(year));
   Wire.endTransmission(); 
}







 void display_time(int _hour, int _minute){   
   if(_minute > 59){_minute-=59;}
_value = _minute;
 s_z = (_value % 100) / 10;
 s_e = _value % 10;
 binwert_s_z = byte(s_z);
 binwert_s_e = byte(s_e);
      //MINUTEN ZEHNER
   if(bitRead(binwert_s_z,0) == 1){
    strip.setPixelColor(7,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
      strip.setPixelColor(7,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   }  
   if(bitRead(binwert_s_z,1) == 1){
 strip.setPixelColor(6,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
    strip.setPixelColor(6,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   } 
   if(bitRead(binwert_s_z,2) == 1){
     strip.setPixelColor(5,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
     strip.setPixelColor(5,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   }  
   if(bitRead(binwert_s_z,3) == 1){
     strip.setPixelColor(4,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
strip.setPixelColor(4,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   }  
   //MINUTE EINER
   if(bitRead(binwert_s_e,0) == 1){
   strip.setPixelColor(0,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
strip.setPixelColor(0,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   }  
   if(bitRead(binwert_s_e,1) == 1){
    strip.setPixelColor(1,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
     strip.setPixelColor(1,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   } 
   if(bitRead(binwert_s_e,2) == 1){
 strip.setPixelColor(2,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
  strip.setPixelColor(2,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   }  
   if(bitRead(binwert_s_e,3) == 1){
   strip.setPixelColor(3,  strip.Color(wheel_color_m[0], wheel_color_m[1], wheel_color_m[2])); 
   }else{
    strip.setPixelColor(3,  strip.Color(wheel_color_m_aus[0], wheel_color_m_aus[1], wheel_color_m_aus[2])); 
   }
     if(_hour > 23){_hour-=24;}
_value = _hour;
 s_z = (_value % 100) / 10;
 s_e = _value % 10;
 binwert_s_z = byte(s_z);
 binwert_s_e = byte(s_e);
 
      //HOUR ZEHNER
   if(bitRead(binwert_s_z,3) == 1){
  strip.setPixelColor(12,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
     strip.setPixelColor(12,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   }  
   if(bitRead(binwert_s_z,2) == 1){
  strip.setPixelColor(13,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
       strip.setPixelColor(13,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   } 
   if(bitRead(binwert_s_z,1) == 1){
   strip.setPixelColor(14,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); ;
   }else{
       strip.setPixelColor(14,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   }  
   if(bitRead(binwert_s_z,0) == 1){
   strip.setPixelColor(15,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
     strip.setPixelColor(15,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   }
   //HOUR EINER
   if(bitRead(binwert_s_e,3) == 1){
 strip.setPixelColor(11,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
     strip.setPixelColor(11,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   }  
   if(bitRead(binwert_s_e,2) == 1){
   strip.setPixelColor(10,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
      strip.setPixelColor(10,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   } 
   if(bitRead(binwert_s_e,1) == 1){
  strip.setPixelColor(9,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
      strip.setPixelColor(9,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   }  
   if(bitRead(binwert_s_e,0) == 1){
   strip.setPixelColor(8,  strip.Color(wheel_color_h[0], wheel_color_h[1], wheel_color_h[2])); 
   }else{
       strip.setPixelColor(8,  strip.Color(wheel_color_h_aus[0], wheel_color_h_aus[1], wheel_color_h_aus[2]));
   }
    Serial.println("Time : " + String(hour) + ":" + String(minute) + ":" + String(second));
 strip.show();
 }









