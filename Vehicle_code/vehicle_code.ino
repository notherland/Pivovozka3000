// подключите один мотор к клемме: M1+ и M1-
// а второй к клемме: M2+ и M2-
// Motor shield использует четыре контакта 4, 5, 6, 7 для управления моторами 
// 4 и 7 — для направления, 5 и 6 — для скорости
#include "Ultrasonic.h"
#include "Wire.h"                
//#include "I2Cdev.h"
//#include "MPU6050.h"
#include <SoftwareSerial.h>
#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include <Adafruit_NeoPixel.h>
#include "Ultrasonic.h"
#define SPEED_1      5 
#define DIR_1        4
#include <FastLED.h> 
#define SPEED_2      6
#define DIR_2        7
Ultrasonic ultrasonic(12, 13);
boolean A = true; boolean B = true;
unsigned int Speed_Lev = 0,
Speed_Prav = 0;
unsigned int interval = 40,
previous_time = 0,
current_time = 0,
interval2 = 70,
previous_time2 = 0;

  char junk;
  String inputString="";
  String condition ="";
void movement(boolean A, boolean B, unsigned int Speed_Lev, unsigned int Speed_Prav) {
    digitalWrite(DIR_1, A);
    
    analogWrite(SPEED_1, Speed_Lev);
 
    digitalWrite(DIR_2, B);
    
    analogWrite(SPEED_2, Speed_Prav);
}
  
void setup() {
  Serial.begin(9600);

  // настраиваем выводы платы 4, 5, 6, 7 на вывод сигналов 
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
  delay(1000);
 
                 
}
void loop(){
   current_time = millis();
  if(Serial.available()){
    while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar; 
      condition = inputString;//make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    if(inputString == "f"){         //in case of 'a' turn the LED on
      A = false;
      B = false;
      Speed_Lev = 200;
      Speed_Prav = 255;

    }else if(inputString == "b"){   //incase of 'b' turn the LED off
      A = true;
      B = true;
      Speed_Lev = 250;
      Speed_Prav = 250;
    }
    else if(inputString == "l"){   //incase of 'b' turn the LED off
       A = true;
       B = false;
       Speed_Lev = 255;
       Speed_Prav = 255;
    }
    else if(inputString == "r"){   //incase of 'b' turn the LED off
       A = false;
       B = true;
       Speed_Lev = 255;
       Speed_Prav =255;
    } 
    else if(inputString == "s"){   //incase of 'b' turn the LED off
       A = false;
       B = false;
       Speed_Lev = 0;
       Speed_Prav = 0; 
    }
  } 
  
  if (current_time >= interval + previous_time) {
        previous_time = current_time;
        float dist_cm = ultrasonic.Ranging(CM); //Нашли расстояние
        Serial.println(dist_cm);

        if ((condition != "l") && (condition != "r") && (condition != "s")) {
          if (dist_cm <= 25) {
             A=!B;
          } else {
              A=B;
 
          }
        }
  }
  inputString = "";
   movement(A,B, Speed_Lev, Speed_Prav);
  }         
