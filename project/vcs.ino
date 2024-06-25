// Read voltage from anlog pin
/*
             **************
 Voltage input
              + VDC Input
              |
              |
              10k Resistor
              |
              |
  Analog Ax---
              |
              |
              2k2 resistor
              |
              |
              GND
//Battery Voltage
#define Vin A1  // analog pin to read volatage on
 //Voltage divider info
const float Vref = 5.00;                // Actual voltage and resistor values can be set here.
const float R1 = 109500.0;              // R1 is nominally 100000.0 measure the actual values and place here for both resistors. Top of divider
const float R2 = 22000.0;               // R2 is nominally 22000.0. Bottom of divider
const float resDiv = ((R1 + R2)/R2);  // Resistor divider factor applied to measured voltage.
// Voltage setup
int vlts;
int raw;
int raw1;
int vlts1;
*/
void vcs()  
{
  int raw = 0;  // Get voltage at R1-R2 junction.
  for (int i = 0; i < avgnum; i++) {
    raw += analogRead(Vin);
    delay(10);
  }
  raw1 = (raw / avgnum);
  //vlts1 = ((raw1 / 1024.0) * Vref);
  vlts = (raw1 * (Vref/1024) * (resDiv)) *10;
  //vlts = ((vlts1 / resDiv)) * 10;
}