#include <IRremote.h>
#include <Servo.h>
#include <FastLED.h>
 
#define IR_RECV_PIN 4
#define IR_BUTTON_1 21
 
#define LED_PIN 7
#define NUM_LEDS 7
 
CRGB leds[NUM_LEDS];
Servo myservo;
const int buzz = 9;
bool stateOn = true;
 
int end = 0;
 
 
void setup() {
    Serial.begin(9600);
    
    IrReceiver.begin(IR_RECV_PIN);
    
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    
    myservo.attach(11);
    myservo.write(160);
 
    FastLED.setBrightness(0);
    FastLED.show();
}
 
void loop() {
    checkreci();
}
 
 
void checkreci()
{
 if (IrReceiver.decode())
 {
   IrReceiver.resume();
   int command = IrReceiver.decodedIRData.command;
   switch (command)
   {
     case IR_BUTTON_1:
     {
        FastLED.setBrightness(100);
        FastLED.show();
        Serial.println("Message received");
        delay(3000);
        buzzerAndLight();
 
       myservo.write(40);
       delay(100);
      myservo.detach();
        
        
        end = 1;
       while (end == 1)
       {
         afterComplete();
       }
     }
   }
 }
}
void buzzerAndLight()
{
  for (int j = 0; j <= 6; j++)
        {
           leds[j] = CRGB ( 255, 0, 0);
           FastLED.show();
        }
  for (int e = 0; e <= 4; e++)
  {
    tone(buzz, 1000);
    FastLED.setBrightness(100);
    FastLED.show();
    delay(300);
    noTone(buzz);
    FastLED.setBrightness(0);
    FastLED.show();
    delay(300);
   }
   FastLED.setBrightness(100);
    FastLED.show();
}
 
 
void afterComplete()
{
 for (int j = 0; j <= 6; j++)
        {
           leds[j] = CRGB ( 0, 255, 0);
           FastLED.show();
          delay(70);
        }
        delay(300);
 
 
  for (int i = 6; i >= 0; i--) 
        {
         leds[i] = CRGB ( 152, 102, 152);
         FastLED.show();
         delay(70);
        }
        delay(300);
 
}