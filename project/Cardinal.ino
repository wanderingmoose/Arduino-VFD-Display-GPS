// This sketch is used to take degrees compass/gps to cardinal direction
//Will only show correct cardinal from gps units once in you are in motion.

void cardint() {
  char heading[3];
  get_cardinal_heading(degrees, heading, sizeof(heading)); //get gps degrees using TinyGpsPlus library
  vfd.GU7000_setFontSize(2, 1, false);  // 1x1 normal font  //for Noritake VFD display
  vfd.GU7000_setCursor(43, 0);
  { vfd.print(heading); }
}
//**********************************************************
void get_cardinal_heading(int const degrees, char* const output, int const len) {
  if (len <= 0) return;
/*
//For 16 points
 int heading = (int)((degrees + 11.25f) / 22.5f);
  char const* const cardinal_points[17] = { "N  ","NNE","NE ","ENE","E  ","ESE","SE ","SSE","S  ","SSW","SW ","WSW","W  ","WNW","NW ","NNW","N  " };
strncpy(output, cardinal_points[heading], len - 1);
  output[len - 1] = '\0';
  }
*/
//For 8 points
  int heading = (int)((degrees + 22.5f) / 45.0f);
   char const* const cardinal_points[9] = { "N ", "NE", "E ", "SE", "S ", "SW", "W ", "NW", "N " }; 
  strncpy(output, cardinal_points[heading], len - 1);
  output[len - 1] = '\0';
}