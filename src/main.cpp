/*
 * Based on
 * InternalClockSync.ino 
 * example code illustrating time synced from a DCF77 receiver
*/

#include "DCF77.h"
#include "TimeLib.h"

#define DCF_PIN 2	         // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0		 // Interrupt number associated with pin


DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);


void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void setup() {
  Serial.begin(9600); 
  DCF.Start();
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
}

void loop() {
  delay(1000);
  time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
  if (DCFtime!=0)
  {
    Serial.println("Time is updated");
    setTime(DCFtime);
  }	
  digitalClockDisplay();  
}