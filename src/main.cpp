// I, Martin De Jesus Gonzalez Santos, 000790179 certify that this is my original work.

// COMP-10184 – Mohawk College
// PIR Sensor Test Application
// Turn on the blue LED with motion is detected.

#include <Arduino.h>

// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
int LED_TIME_ON = 10000;
int BLINKS_PER_MINUTE = 4;
bool ALARM_ENABLED = true;

// *************************************************************
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);

  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);

  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // Start the program with LED off
  digitalWrite(LED_BUILTIN, true);
}

// *************************************************************
void loop()
{
  bool bPIR;
  int buttonValue = digitalRead(PIN_BUTTON);

  if (buttonValue == 0)
  {    
    // The user clicked on the button to re-enable the alarm
    ALARM_ENABLED = true;
  }

  // read PIR sensor (true = Motion detected!).  As long as there
  // is motion, this signal will be true.  About 2.5 seconds after
  // motion stops, the PIR signal will become false.
  bPIR = digitalRead(PIN_PIR);

  // send the PIR signal directly to the LED
  // but invert it because true = LED off!  
  if (bPIR && ALARM_ENABLED){
    bool DEACTIVATE = false;
    for (int i = 0; i < BLINKS_PER_MINUTE * (LED_TIME_ON / 1000); i++)
    {
      buttonValue = digitalRead(PIN_BUTTON);      
      if (buttonValue == 0)
      {
        DEACTIVATE = true;        
        break;
      }
      digitalWrite(LED_BUILTIN, !bPIR);
      delay(125);
      digitalWrite(LED_BUILTIN, bPIR);
      delay(125);
    }    
    
    if (DEACTIVATE)
    {
      // The user clicked on the button to deactivate the alarm
      digitalWrite(LED_BUILTIN, true);
      ALARM_ENABLED = false;
      buttonValue = 1;
    }
    else
    {
      // The user did not click on the button to deactivate the alarm
      ALARM_ENABLED = false;
      digitalWrite(LED_BUILTIN, false);
    }

  }
}