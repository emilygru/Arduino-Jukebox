#include <SPI.h>
#include <RFID.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AceSorting.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>
#include "Arduino.h"

using ace_sorting::bubbleSort;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t rowPins[ROWS] = { 23, 25, 27, 29 }; // Pins connected to R1, R2, R3, R4
uint8_t colPins[COLS] = { 31, 33, 35, 37 }; // Pins connected to C1, C2, C3, C4

int cursor = 0;

int numbers[] = {};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 9
#define RESET_DIO 8
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

int greenPin = 36;
int redPin = 47;

const int rxPin = 42; 
const int txPin = 43; 

SoftwareSerial mySoftwareSerial(rxPin, txPin);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{ 
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  pinMode(greenPin, OUTPUT); //comment out to make less bright
  pinMode(redPin, OUTPUT); //comment out to make less bright
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, HIGH);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init(); 

  lcd.init();
  lcd.backlight();
  lcd.blink();
  lcd.setCursor(0,0);

  Serial.println("Initializing DFPlayer...");

  // Initialize the DFPlayer Mini
  if (!myDFPlayer.begin(mySoftwareSerial, /*isACK = */true, /*doReset = */true))   
  {
    Serial.println("DFPlayer Mini not detected. Please check connections and if SD card is inserted.");
  }
  Serial.println("DFPlayer initialized!");
  myDFPlayer.volume(12);
}

void loop()
{

  
  void(* resetFunc) (void) = 0;  // Create a function pointer that points nothing
  char key = keypad.getKey();

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("Card detected:");
    //delay (500);

    for(int i=0;i<5;i++)
    {
    Serial.println(RC522.serNum[i],DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    //delay (500);
    }

    if(RC522.serNum[0] == 55 && digitalRead(redPin) == HIGH)
    {
      //Serial.println(RC522.serNum[0],DEC);
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
      Serial.println("Card detected once");
      delay (1000);
    }

    else if (RC522.serNum[0] == 55 && digitalRead(greenPin) == HIGH)
    {
      //Serial.println(RC522.serNum[0], DEC);
      Serial.println("Card detected twice");
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
      delay (1000);
    }

    if(RC522.serNum[0] == 58 || RC522.serNum[0] == 74)
    {
      //Serial.println(RC522.serNum[0],DEC);
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
      delay (1000);
    }
  }

   if (digitalRead(redPin) == HIGH) 
   {
      lcd.setCursor(0, 1);
      lcd.clear(); // Clear the display
   }

  if (key != NO_KEY && cursor < 16 && digitalRead(greenPin) == HIGH) 
  {
    lcd.print(key);

    if (key == '*')
    {
      lcd.setCursor(0, 1);
      lcd.clear(); // Clear the display
    }
    static char buffer[100] = {0};
    static int i = 0;

    if (key == '#')
    {
      //buffer[i] = 'A1';
      //i = 0;
      // Process buffer here...
      Serial.println(buffer);


      if(buffer[0] == 'A' && buffer[1] == '1') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Die With A Smile");
      Serial.println("Die With A Smile");
      myDFPlayer.play(1);
      delay (252000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    if (key == '#')
    {
      //buffer[i] = 'A2';
      //i = 0;
      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'A' && buffer[1] == '2') {

      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Talking in Your Sleep");
      Serial.println("Talking in Your Sleep");
      myDFPlayer.play(2);
      delay (235000);
      resetFunc();  //Call function when you want to force the Arduino to reset


      }

    }

    if (key == '#')
    {
      //buffer[i] = 'A3';
      //i = 0;
      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'A' && buffer[1] == '3') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Everybody Wants to Rule the World");
      myDFPlayer.play(3);
      delay (252000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }


    }

    if (key == '#')
    {
      //buffer[i] = 'A4';
      //i = 0;
      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'A' && buffer[1] == '4') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("When Doves Cry");
      myDFPlayer.play(4);
      delay (353000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

        if (key == '#')
    {

      Serial.println(buffer);

      if(buffer[0] == 'A' && buffer[1] == '5') {

      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Lucky Star");
      myDFPlayer.play(5);
      delay (338000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'A' && buffer[1] == '6') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Girls Just Want To Have Fun");
      myDFPlayer.play(6);
      delay (236000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }


    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);
      if(buffer[0] == 'B' && buffer[1] == '1') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Cupid's Chokehold / Breakfast in America");
      myDFPlayer.play(7);
      delay (244000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }


    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);
      
      if(buffer[0] == 'B' && buffer[1] == '2') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Rock Your Body");
      myDFPlayer.play(8);
      delay (268000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'B' && buffer[1] == '3') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("We R Who We R");
      myDFPlayer.play(9);
      delay (205000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'B' && buffer[1] == '4') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Say My Name");
      myDFPlayer.play(10);
      delay (272000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'B' && buffer[1] == '5') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("I Want It That Way");
      myDFPlayer.play(11);
      delay (214000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    if (key == '#')
    {

      // Process buffer here...
      Serial.println(buffer);

      if(buffer[0] == 'B' && buffer[1] == '6') {
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Good Luck, Babe!");
      myDFPlayer.play(12);
      delay (219000);
      resetFunc();  //Call function when you want to force the Arduino to reset
      }

    }

    else
    {
      buffer[i] = key;
      i++;
      if (i == 100)
      {
        //clear
        i = 0;
      }
    }
  }
}