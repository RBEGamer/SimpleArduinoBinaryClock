int btn_delay = 200;


void get_btn_state(){
  if(digitalRead(btn_add_pin) == HIGH){btn_add_state = 1; }else{btn_add_state = 0;}
  if(digitalRead(btn_sub_pin) == HIGH){btn_sub_state = 1;}else{btn_sub_state = 0;}
  if(digitalRead(btn_time_pin) == HIGH){btn_time_state = 1;}else{btn_time_state = 0;}
  if(digitalRead(btn_alarm_pin) == HIGH){btn_alarm_state = 1;}else{btn_alarm_state = 0;}
  if(digitalRead(btn_sone_pin) == HIGH){btn_sone_state = 1;}else{btn_sone_state = 0;}
  
 if(btn_add_state == 1){Serial.println("add");}else{}
 if(btn_sub_state == 1){Serial.println("sub");}else{}
 if(btn_time_state == 1){Serial.println("time");}else{}
 if(btn_alarm_state == 1){Serial.println("alarm");}else{}
 if(btn_sone_state == 1){Serial.println("sone");}else{}
    


}




void button(){
  
  get_btn_state();

 
 if(btn_sone_state == 1){
 stop_alarm();
 }
 
 
 //COLOR M ADD
if(btn_add_state == 1 &&  btn_sub_state == 0 && btn_time_state == 0 && btn_alarm_state == 0 && prev_state_button == 0){ 
prev_state_button = 1;
while (btn_add_state == 1){ 
  delay(btn_delay);
  if(wheel_pos_m >= 255){wheel_pos_m = 0;}else{wheel_pos_m+=5;}
 Serial.println("Wheel_m : " + String(wheel_pos_m));
wheel_m();
get_btn_state();
//getDateDs1307();
display_time(hour, minute);
}//END WHILE
eeprom_write();



//COLOR H ADD
}else if(btn_add_state == 0 &&  btn_sub_state == 1 && btn_time_state == 0 && btn_alarm_state == 0 && prev_state_button == 0){ 
prev_state_button = 1;
while (btn_sub_state == 1){ 
  if(wheel_pos_h >= 255){wheel_pos_h = 0;}else{wheel_pos_h+=5;}
wheel_h();
  get_btn_state();
Serial.println("Wheel_h : " + String(wheel_pos_h));
getDateDs1307();

delay(btn_delay);
}//END WHILE
eeprom_write();





//TIME ADD
}else if(btn_add_state == 0 &&  btn_sub_state == 0 && btn_time_state == 1 && btn_alarm_state == 0 && prev_state_button == 0){ 
prev_state_button = 1;
while (btn_time_state == 1){ 
   get_btn_state();

  
    if(btn_add_state == 1){
  if(hour >= 23){hour = 0;}else{hour++;}
  }
  
    if(btn_sub_state == 1){
  if(minute >= 59){minute = 0;}else{minute++;}
  }
  
  delay(btn_delay);
  Serial.println(" Set Time : " + String(hour) + ":" + String(minute) + ":" + String(second));
display_time(hour, minute);

}//END WHILE
setDateDs1307();
eeprom_write();






//ALARM ADD
}else if(btn_add_state == 0 &&  btn_sub_state == 0 && btn_time_state == 0 && btn_alarm_state == 1 && prev_state_button == 0){ 
prev_state_button = 1;

while (btn_alarm_state == 1){ 
 get_btn_state();


   
  if(btn_add_state == 1 && btn_sub_state == 1){
  if(alarm_en == 0){
  delay(50);
  alarm_en = 1;
}else{
alarm_en = 0;
}
 
  
  }else if(btn_add_state == 1 && alarm_en == 1  && btn_sub_state == 0){
  if(alarm_h >= 23){alarm_h = 0;}else{alarm_h++;}
  
  }else if(btn_sub_state == 1 && alarm_en == 1 && btn_add_state == 0){
  if(alarm_m >= 59){alarm_m = 0;}else{alarm_m++;}
  }
  
  Serial.println("Set Alarm : " + String(alarm_h) + ":" + String(alarm_m) + "  EN=" + String(alarm_en));
 // display_time(alarm_h, alarm_m);
if(alarm_en == 1){display_time(alarm_h, alarm_m);}else{display_time(0, 0);}

 delay(btn_delay);
}//END WHILE
eeprom_write();




//NIGHTMODE ADD
}else if(btn_add_state == 0 &&  btn_sub_state == 0 && btn_time_state == 1 && btn_alarm_state == 1 && prev_state_button == 0){ 
prev_state_button = 1;
while (btn_alarm_state == 1 && btn_time_state == 1){ 
 
   get_btn_state();
delay(btn_delay);
   
  if(btn_add_state == 1 && btn_sub_state == 1 ){
  if(nthen == 0){nthen = 1;}else{nthen = 0;}
  delay(50);
  
  }else if(btn_add_state == 1  && nthen == 1){
  if(nth >= 23){nth = 0;}else{nth++;}
  
  
  }else if(btn_sub_state == 1  && nthen == 1){
    if(nthe >= 23){nthe = 0;}else{nthe++;}
  }
  
  
 
if(nthen == 1){display_time(nth, nthe);}else{display_time(0, 0);}


 Serial.println("Set Nightmode : " + String(nth) + "->" + String(nthe) + "  EN=" + String(nthen));

}//END WHILE


eeprom_write();
}//END IF






//WERTE ÜBERNHEMEN












if(prev_state_button == 1){

eeprom_write();
}

if(btn_add_state == 0 &&  btn_sub_state == 0 && btn_time_state == 0 && btn_alarm_state == 0){ 
  prev_state_button = 0;
} 


}

