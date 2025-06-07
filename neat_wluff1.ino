/*
  Candoli Leo
  22/05/2025
  ReactionWar 1v1
*/
#include <LiquidCrystal.h>

#define WINPOINT 100000
#define LEDTIME 5000  

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //LCD display pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int ledPinG1 = 6; //Led/button pins
const int buttonPinG1 = 7;
const int ledPinG2 = 8;
const int buttonPinG2 = 9;

unsigned long int pointG1 = 0;
unsigned long int pointG2 = 0;


bool checkWin(int g)
{
  return g>=WINPOINT;
}


bool debounce(int pin) {
  static unsigned long lastTime = 0;  
  unsigned long currentTime = millis();  
 
 
  if (currentTime - lastTime > 50) {
    lastTime = currentTime;  
    return digitalRead(pin) == HIGH;  
  }
  return false;
}


int awardPoints(int reaction){
  if (reaction >= 500)
  {
    return 5000;
  }
  else if(reaction < 500 && reaction > 200 )
  {
    return 8000;
  }
  else{
    return 10000;
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(ledPinG1, OUTPUT);  
  pinMode(ledPinG2, OUTPUT);      
  pinMode(buttonPinG1, INPUT);
  pinMode(buttonPinG2, INPUT);
  randomSeed(analogRead(0)); //For random number
  lcd.begin(16, 2);
}


void loop() {


  int long time=0;
  int long reactionS=0;
  int player = random(0, 10) % 2;


  switch(player){
    case 0:
      delay(random(0, 10) * 100 + 100);
      lcd.clear();
      digitalWrite(ledPinG1, HIGH);
      reactionS = millis();
      while(!debounce(buttonPinG1))
      {  
      }
      time = millis();
      pointG1 += awardPoints(time - reactionS);
      lcd.setCursor(0, 0);
      lcd.print("G1's Points: ");
      lcd.setCursor(0, 1);
      lcd.print(pointG1);
      digitalWrite(ledPinG1, LOW);
      if(checkWin(pointG1))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("G1 WON!!!");
      }
      break;
    case 1:
      delay(random(0, 10) * 100 + 100);
      lcd.clear();
      digitalWrite(ledPinG2, HIGH);
      reactionS = millis();
      while(!debounce(buttonPinG2))
      {  
      }
      time = millis();
      pointG2 += awardPoints(time - reactionS);
      digitalWrite(ledPinG2, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("G2's Points: ");
      lcd.setCursor(0, 1);
      lcd.print(pointG2);
      digitalWrite(ledPinG2, LOW);
      if(checkWin(pointG2))
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("G2 WON!!!");
      }
      break;
  }


  delay(LEDTIME);
}
