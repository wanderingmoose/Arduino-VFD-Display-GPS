/*
Justifys to the right, Intrager only.
/*float tempReading;
float temptotal = 0;
float tempavg = 0;
const int avgnum = 10; //how many samples to average
//Temperature pins
#define tempPin1 A3  //Analog 2 for thermistor input
// Thermistor object
THERMISTOR thermistor1(tempPin1,  // Analog pin
                       10000,     // Nominal resistance at 25 ºC
                       3950,      // thermistor's beta coefficient
                       10000);    // Value of the series resistor

**************
 Thermistor 10k. Temp is for outside.
              +5volts
              |
              |
              10k Thermister
              |
              |
  Analog Ax---
              |
              |
              10k ohm resistor
              |
              |
              GND
*/


void tempC() {
  //Read temperature for control
  //*****
  temptotal = 0;  //take "avgnum" of samples in order to take an average sensor reading, this helps with sensor accuracy.
  for (int x = 0; x < avgnum; x++) {
    tempReading = thermistor1.read();  //read temperature sensor
    temptotal = temptotal + tempReading;
  }
   vfd.GU7000_setFontSize(2, 1, false);  // 1x1 normal font
  temperatureC = (temptotal / avgnum) / 10;
   char buffer1[4];
 snprintf(buffer1, sizeof(buffer1), "%3d", temperatureC);
  // Set the cursor position to the right-justified position
  // Assuming the display width is 112 pixels and each character is 8 pixels wide
  int xPos = 94 - (strlen(buffer1) * 8);
  int yPos = 0;  // Top line
  vfd.GU7000_setCursor(xPos, yPos);
  // Print the speed value to the display
  vfd.print(buffer1);
 
}