#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int val;    // variable to read the value from the analog pin
const int analogInPin = A0; 
int score = 0; 

int RedPin = 5; 
int GreenPin = 4; 
int buttonStateRed = 0;         // current state of the button
int lastButtonStateRed = 1;     // previous state of the button
int buttonStateGreen = 0;         // current state of the button
int lastButtonStateGreen = 1;     // previous state of the button
int question = 0; 
bool questionone = 1; 
bool questiontwo = 1; 
bool questionthree = 1;
bool questionfour = 1;
bool questionfive = 1; 

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Blackbox Vending Machine"); 
 pinMode(RedPin, INPUT_PULLUP); //red button
 pinMode(GreenPin, INPUT_PULLUP); //green button 
  tft.begin();
  tft.setRotation(1);
  testText();
  delay(3000);

}
    
void loop() {

switch (question) {
    case 0: 
      instructions(); 
      while(digitalRead(GreenPin) == HIGH) {
      delay(5); 
      }
      delay(1000); 
      question=1;    
      break; 
    case 1:    
      question1();
      break;
    case 2: 
      question2();
      break;
    case 3:  
      question3();
      break;
    case 4:  
      question4();
      break;
    case 5:  
      question5();
      break;
    case 6:    
      vending();
      question = 0;
      score = 0; 
      questionone = 1; 
      questiontwo = 1; 
      questionthree = 1;
      questionfour = 1;
      questionfive = 1;
      break;
  }

checkButtonRed(); 
checkButtonGreen(); 
delay(50); 
       
}

void checkButtonRed()
{
  
  // read the pushbutton input pin:
  buttonStateRed = digitalRead(RedPin);

  // compare the buttonState to its previous state
  if (buttonStateRed != lastButtonStateRed) {
    // if the state has changed, increment the counter
    if (buttonStateRed == LOW) {
      // if the current state is LOW then the button
      // went from off to on:
      score--;
      question++; 
      Serial.println("Red button pushed");
      Serial.print("score:  ");
      Serial.println(score);
    }
    else {
      // if the current state is HIGH then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateRed = buttonStateRed;
}

void checkButtonGreen()
{
  
  // read the pushbutton input pin:
  buttonStateGreen = digitalRead(GreenPin);

  // compare the buttonState to its previous state
  if (buttonStateGreen != lastButtonStateGreen) {
    // if the state has changed, increment the counter
    if (buttonStateGreen == LOW) {
      // if the current state is LOW then the button
      // wend from off to on:
      score++;
      question++; 
      Serial.println("Green button pushed");
      Serial.print("score:  ");
      Serial.println(score);
    }
    else {
      // if the current state is HIGH then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateGreen = buttonStateGreen;
}


  
void getBall(bool turn){ 
  Serial.println("running getBall routine"); 
    if (turn) {  
    Serial.println("turning right");   
  myservo.attach(3);
  myservo.write(180); //92 to advance the servo past the hall sensor
  delay(300);
  while (analogRead(analogInPin) <=360) {
    //Serial.println(analogRead(analogInPin)); 
  //myservo.attach(3);
  myservo.write(180); //92             
  delay(3); 
  }
  //myservo.write(180);
  myservo.detach(); 
  }else if (!turn) {  
  Serial.println("turning left");   
  myservo.attach(3);
  myservo.write(70); //97to advance past hall sensors       
  delay(300); 
  while (analogRead(analogInPin) <=360) {
    //Serial.println(analogRead(analogInPin)); 
  //myservo.attach(3);
  myservo.write(70);   //97      
  delay(3); 
  }
  myservo.detach(); 
  }
}

  
  unsigned long testText() {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
    tft.println("");
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");    
    tft.println("I am a Blackbox Vending Machine");
    return micros() - start;
}

 unsigned long instructions() {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println("");    
    tft.println("Would you like to make a moral technology?"); 
    tft.println("");
    tft.println("Press green button to begin!"); 
    return micros() - start;
 } 

unsigned long question1() {
    if (questionone) {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);  tft.setTextWrap(true);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println("");    
    tft.println("Prompt 1");
    tft.println("I am interested in 3D     printing's capacity to    circumvent geographic     boundaries.");
    tft.println("");
    tft.println("Press Green for Yes");
    tft.setTextColor(ILI9341_RED); 
    tft.println("or Red for No");
    questionone = 0; 
    }
    //return micros() - start;
}
    
 unsigned long question2() {
   if (questiontwo) {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println("");        
    tft.println("Prompt 2");
    tft.println("I am interested in how 3D printing unsettles notions of expertise in manufacturing.");
    tft.println("");
    tft.println("Press Green for Yes");
    tft.setTextColor(ILI9341_RED); 
    tft.println("or Red for No");    
    questiontwo = 0; 
   }
    //return micros() - start;
 }
 
 unsigned long question3() {
   if (questionthree) {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println("");  
    tft.println("Prompt 3");
    tft.println("I am interested in how new knowledge practices and epistemic cultures form around 3D printing.");
    tft.println("");
    tft.println("Press Green for Yes");
    tft.setTextColor(ILI9341_RED); 
    tft.println("or Red for No");    
    //return micros() - start;
    questionthree = 0; 
   }   
 }

 unsigned long question4() {
   if (questionfour) {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println("");  
    tft.println("Prompt 4");
    tft.println("I am interested in the capacity of 3D printing to produce customizable goods.");
    tft.println("");
    tft.println("Press Green for Yes");
    tft.setTextColor(ILI9341_RED); 
    tft.println("or Red for No");    
    questionfour = 0; 
   }
    //return micros() - start;
 }

 unsigned long question5() {
   if (questionfive) {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println("");  
    tft.println("Prompt 5");
    tft.println("I am interested in 3D printing's potential to disrupt/disturb institutional or legal authority.");
    tft.println("");
    tft.println("Press Green for Yes");
    tft.setTextColor(ILI9341_RED); 
    tft.println("or Red for No");    
    questionfive = 0; 
   }
    //return micros() - start;
 }

 unsigned long vending() {
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(5);
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");    
    tft.println("");
    tft.println("");
    tft.println(""); 
    tft.println("vending");
    
    if (score>0) {
    Serial.println("vending leg");   
    getBall(0); 
    }else {
   Serial.println("vending gun");    
   getBall(1);
    } 
   delay(3000);    
   return micros() - start;
 } 
