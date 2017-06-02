

void eeprom_read(){

wheel_pos_h = EEPROM.read(0);
wheel_pos_m = EEPROM.read(1);
nthen = EEPROM.read(2);
nth = EEPROM.read(3);
nthe = EEPROM.read(4);
alarm_en = EEPROM.read(5);
alarm_h = EEPROM.read(6);
alarm_m = EEPROM.read(7);


}



void eeprom_write(){
  EEPROM.write(0, wheel_pos_h);
  EEPROM.write(1, wheel_pos_m);
  EEPROM.write(2, nthen);
  EEPROM.write(3, nth);
  EEPROM.write(4, nthe);
  EEPROM.write(5, alarm_en);
  EEPROM.write(6, alarm_h);
  EEPROM.write(7, alarm_m);
}
