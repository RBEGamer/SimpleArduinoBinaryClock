void stop_alarm(){
    if(alarm_state == 1 && alarm_en ==1){
    alarm_state = 0;
    alarm_state =0;
  while(minute == alarm_m){ //SOLANGE warten bis die zeit vorbei ist
 
  Serial.println("ALARM DELAY WHILE"); 
  getDateDs1307();
  
  
  }
 
 alarm_process = 0; 
  alarm_state = 0; 
  delay(2000);
  
  
    }
}


void soundAlarm() {
  
  if(hour == alarm_h && minute == alarm_m && alarm_en == 1 && alarm_process == 0 ){
    alarm_process = 1;
    alarm_state = 1;
    
    
  }else{
 
  }
  

  
  if(alarm_state == 1 && alarm_en ==1){
    
    
    
    
 float alarmFrequency=1400; // The value for the alarm tone in Hz
 float period = (1.0 / alarmFrequency) * 1000000;
 long beepDuration=250000; // the time in microseconds (0.25 seconds)
 long elapsedTime = 0;
 while (elapsedTime < beepDuration) {
 digitalWrite(beeper_pin,HIGH);
 delayMicroseconds(period / 2);
 digitalWrite(beeper_pin, LOW);
 delayMicroseconds(period / 2);
 elapsedTime += (period);
 }
 digitalWrite(beeper_pin, LOW); 
 delayMicroseconds(beepDuration);
 }
  
}
