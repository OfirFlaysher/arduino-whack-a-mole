#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int BLUE_LED = 4;
const int YELLOW_LED = 10;
const int WHITE_LED = 9; 
const int RED_LED = 11; 
const int GREEN_LED = 7; 
const int BLUE_BUTTON = 2;
const int YELLOW_BUTTON = 5;
const int WHITE_BUTTON = 6;
const int RED_BUTTON = 3;
const int GREEN_BUTTON = 8;
const int BUZZER = 12;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int score = 0;
unsigned long startGameTime;
unsigned long endGameTime;
const unsigned long GAME_TIME = 100000;
 
void setup() 
{  
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(WHITE_BUTTON, INPUT_PULLUP);
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  
  randomSeed(analogRead(0));

  blinkAll();
}

void loop() 
{
  startGameTime = millis();
  endGameTime = startGameTime + GAME_TIME;
  
  while(millis() < endGameTime)
  {
    int color = random(0, 5);
    onOffLED(color, 1);
    int button = getButtonPressed();
    while(button != -1 && button != color) 
    {
      button = getButtonPressed();
    }
    if(button != -1)
    {
      onOffLED(color, 0);
      score++;
      lcd.clear();
      lcd.print(score);
    }
  }

  score = 0;
  blinkAll();
  delay(2000);
  lcd.clear();
  lcd.print(0);
}

void onOffLED(int color, int x)
{
  if(color == 0)
  {
    digitalWrite(BLUE_LED, x);
  }
  else if(color == 1)
  {
    digitalWrite(YELLOW_LED, x);
  }
  else if(color == 2)
  {
    digitalWrite(WHITE_LED, x);
  }
  else if(color == 3)
  {
    digitalWrite(RED_LED, x);
  }
  else if(color == 4)
  {
    digitalWrite(GREEN_LED, x);
  }
}

void blinkAll()
{
  for(int i = 0; i < 3; i++)
  {  
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(WHITE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
}

void beep(int frequencyInHertz, long timeInMilliseconds)
{ 
  int x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++)
  {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(delayAmount);
  }
}

int getButtonPressed()
{
  int led = 5;
  int button;
  while(true)
  {
    if(digitalRead(BLUE_BUTTON) == HIGH)
    {
      led = 0;
      button = BLUE_BUTTON;
    }
    else if(digitalRead(YELLOW_BUTTON) == HIGH)
    {
      led = 1;
      button = YELLOW_BUTTON;
    }
    else if(digitalRead(WHITE_BUTTON) == HIGH)
    {
      led = 2;
      button = WHITE_BUTTON;
    }
    else if(digitalRead(RED_BUTTON) == HIGH)
    {
      led = 3;
      button = RED_BUTTON;
    }
    else if(digitalRead(GREEN_BUTTON) == HIGH)
    {
      led = 4;
      button = GREEN_BUTTON;
    }
    
    if(millis() >= endGameTime)
    {
      return -1;
    }
    
    if(led != 5)
    {
      beep(2093,100);
      return led;
    }
  }
}

