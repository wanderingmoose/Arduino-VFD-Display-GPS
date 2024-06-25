/*
Wanderingmoose Sketch to show GPS/VDC/Temperature/Cardinal direction in motion on a Noritake GU7000 type display 
Library for the GU7000 VFD display can be gotten from there Noritake web site. Search for your displays basic name and arduino.
This sketch will display GPS Speed, altitude and Cardinal direction of movement as well as outside temperature, and input voltage. 
I hope this is documented enough for someone to achive what I did.
Split up the voids into there own seperate tabs. Will try to achieve going forward to allow me to just grab them for other projects.
Also will attemp to place in each void the required setup info to help in future sketches.(Lots of work to go yet on this one)
June 11,2024
https://github.com/wanderingmoose
VerA   speed|(Direction/ Temp)/(Altitude  Voltage).
Arduino Nano:
Sketch uses 12654 bytes (41%) of program storage space. Maximum is 30720 bytes.
Global variables use 753 bytes (36%) of dynamic memory, leaving 1295 bytes for local variables. Maximum is 2048 bytes.
**************
Hardware:
Arduino NANO
Display Noritake GU7000 112x16 VFD *******If using the VFD display, make sure to have external 5volt supply, the displays can draw up 250ma.*************
Thermistor Temperature sensor 10K NTC
Voltage divider to measure battery voltage
Simple cheap GPS module that works with TINYGPSPLUS 
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
              **************
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

*/
//Libraries Used
#include <GU7000_Interface.h>
#include <GU7000_Serial_Async.h>
#include <Noritake_VFD_GU7000.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <thermistor.h>
// Define the pins for the GU7000_Serial_Async interface Async connection 1=5V 2=SIN 3=GND 4=Busy 5=NC(Sync SCK) 6= Reset
#define SIN_PIN 3       //Pin 2 of Dispaly
#define BUSY_PIN 5      //Pin 4 of Display
#define RESET_PIN 7     //Pin 6 of Display
//Battery Voltage
#define Vin A1  // analog pin to read volatage on
//Temperature pins
#define tempPin1 A3  //Analog 2 for thermistor input
//GPS pins and baud
static const int RXPin = 11, TXPin = 12; //GPS serial pins
static const uint32_t GPSBaud = 9600; //GPS baud rate
// The TinyGPSPlus object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);  //Setup GPS serial communications
//variables
int speedint;
int satint;
int degint;
int degrees;
int altint;
// Voltage setup
int vlts;
int raw;
int raw1;
int vlts1;
//Temperature setup
float tempReading;
float temptotal = 0;
float tempavg = 0;
int temperatureC;
const int avgnum = 10;
// Thermistor object
THERMISTOR thermistor1(tempPin1,  // Analog pin
                       10000,     // Nominal resistance at 25 ºC
                       3950,      // thermistor's beta coefficient
                       10000);    // Value of the series resistor
// Voltage divider infor
const float Vref = 5.00;                // Actual voltage and resistor values can be set here.
const float R1 = 10000.0;              // R1 is nominally 100000.0 measure the actual values and place here for both resistors
const float R2 = 2100.0;               // R2 is nominally 22000.0
//
const float resDiv = ((R1 + R2) / R2);  // Resistor divider factor applied to measured voltage.
// Initialize the display interface with specified parameters
GU7000_Serial_Async interface(38400, SIN_PIN, BUSY_PIN, RESET_PIN);  // BAUD RATE,SIN,BUSY,RESET
// Initialize the Noritake_VFD_GU7000 object
Noritake_VFD_GU7000 vfd;
//Timers
// previous time for the tasks depending upon time.
unsigned long prevTime_T1 = millis();
//unsigned long prevTime_T2 = millis();
unsigned long prevTime_T4 = millis();
// time intervals for the tasks
long interval_T1 = 500;  // 
long interval_T4 = 4000;  // 
int sensorValue;
//**************************
void setup() {
   
  pinMode(Vin, INPUT);
  ss.begin(GPSBaud);
  pinMode(tempPin1, INPUT);     //ensure A2 is an input
  digitalWrite(tempPin1, LOW);  //ensure pullup is off on A2
  //*********************
   //Initialize the VFD display
  delay(250);                //allow display to power up after init
  vfd.begin(112, 16);        // 140x16 module
  vfd.interface(interface);  // select which interface to use
  vfd.isModelClass(7003);
  vfd.GU7000_reset();                   // reset module
  vfd.GU7000_init();                    // initialize module
                                        //Print splash screen
  delay(250);                           //allow display to power up after int
  vfd.GU7000_setScreenBrightness(75);   //0-100 percent brighness control
  vfd.GU7000_setFontSize(2, 1, false);  // 2x1 Big font on a single line.
  vfd.GU7000_setCursor(0, 0);
  vfd.print("GPSspeed   V4");
  delay(2000);
  vfd.GU7000_clearScreen();
  vfd.GU7000_setFontSize(1, 1, false);  // 1x1 normal font
vfd.print ("//github.com/   wanderingmoose");
  //vfd.print("Wanderingmoose");
  //vfd.GU7000_setCursor(0, 8);
  //vfd.print("Tinkering 2024");
  delay(3000);
  vfd.GU7000_clearScreen();
}
void loop() {
  unsigned long currentTime = millis();
   
  // Timer1 : get gps info and display
  if (currentTime - prevTime_T1 > interval_T1) {
    shrink();
    speed();
    cardint();
    prevTime_T1 = currentTime;
  }
  // Timer 4 : get vdc & temp and display
  if (currentTime - prevTime_T4 > interval_T4) {
    tempC(); 
    vdc();
    prevTime_T4 = currentTime;
  }
  smartDelay(250); //parse gps data to varibles
}

