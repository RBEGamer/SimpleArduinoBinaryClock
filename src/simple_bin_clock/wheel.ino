


void wheel_h() {
   wheel_color_h[0] =getR(Wheel(wheel_pos_h));
  wheel_color_h[1] =getG(Wheel(wheel_pos_h));
  wheel_color_h[2] =getB(Wheel(wheel_pos_h));
}

void wheel_m() {
   wheel_color_m[0] =getR(Wheel(wheel_pos_m));
  wheel_color_m[1] =getG(Wheel(wheel_pos_m));
  wheel_color_m[2] =getB(Wheel(wheel_pos_m));
  
}




// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



//get Color (weil R und G vertauscht
uint32_t getColor(int r, int g, int b) {
  return strip.Color(g, r, b);
}
int getR(uint32_t c) {
  return (c % 65536)/256;
}
int getG(uint32_t c) {
  return c / 65536;
}
int getB(uint32_t c) {
  return (c % 65536)%256;
}
