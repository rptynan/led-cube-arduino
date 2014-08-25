/*
   4x4x4 LED Cube Controller
   LED Cube controller for 4x4x4 with support for one button.
*/

#include <PinChangeInt.h>



// Set Column and Layer Levels, (HIGH or LOW)
const int collev = LOW;
const int laylev = HIGH;
// Set Layer Pins, (Z axis co-ordinate: l0; l1; l2; l3)
const int l0 = A0;
const int l1 = A1;
const int l2 = A2;
const int l3 = A3;
// Set Column Pins, (X and Y co-ordinate, eg: c00; c0; c02; c03; c10)
const int c00 = 0;
const int c01 = 1;
const int c02 = 2;
const int c03 = 3;
const int c10 = 4;
const int c11 = 5;
const int c12 = 6;
const int c13 = 7;
const int c20 = 8;
const int c21 = 9;
const int c22 = 10;
const int c23 = 11;
const int c30 = 12;
const int c31 = 13;
const int c32 = A4;
const int c33 = A5;
// Setup for Arrays
const int layarray[] = {l0,l1,l2,l3};
const int colarray[] = {c00, c01, c02, c03, c10, c11, c12, c13, c20, c21, c22, c23, c30, c31, c32, c33};
// Set Button Input Pin (bip), Level When Closed (lwc) and Delay for Button Input Timeout (buttondelay)
const int bip = 8;
long start = 0;
int buttondelay = 1000;
// Set Column and Layar Indicators (colind & layind)
int colind= c00;
int layind= l0;
// Setup for Mode Counter 
int mode=0;



//Various Functions for turning on and off LEDs

void onoff(int ColCo, int LayCo, int dela){
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
  delay(dela);
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
}

void onoff1(int ColCo, int LayCo){
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
}

void off(int ColCo, int LayCo){
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
}

void on(int ColCo, int LayCo){
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
}

void offon(int ColCo, int LayCo, int dela){
  digitalWrite(ColCo, laylev);
  digitalWrite(LayCo, collev);
  delay(dela);
  digitalWrite(ColCo, collev);
  digitalWrite(LayCo, laylev);
}



void setup(){
  //Sets a Random Seed for random() function from any random pin (except button pin which is tied)
  randomSeed(analogRead(c00));
  
  //Sets the Pins Modes that we need
  pinMode(bip, INPUT);
  pinMode(layind, OUTPUT);
  pinMode(colind, OUTPUT);
 //Turns off pin 13 because the arduino writes it low during the setup, making it appear on to us
  digitalWrite(13,laylev);
  //The mode counting part, counts how many times the button is pushed
  on(colind, layind);                                        //turns on indicator LED
  while(1){
    if(digitalRead(bip)==LOW){ //&& millis()-start<buttondelay){ //if button pressed within timeout
      mode++;
      offon(colind, layind, 200);                            //flashes indicator LED off to acknowledge button press
      start=millis();}                                       //resets timer
    else if(millis()-start>buttondelay && mode>0){
      break;}                                                //breaks loop if no button press within timeout and if button has been pressed at least once
  }
  off(colind, layind);
  delay(500);
  //Blink Mode Number
  for(int i=0; i<mode; i++){
    onoff(colind, layind, 100);
    delay(100);}
    
  //Actual Layar pinModes
  pinMode(l0, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  //Actual Column pinModes
  pinMode(c00, OUTPUT);
  pinMode(c01, OUTPUT);
  pinMode(c02, OUTPUT);
  pinMode(c03, OUTPUT);
  pinMode(c10, OUTPUT);
  pinMode(c11, OUTPUT);
  pinMode(c12, OUTPUT);
  pinMode(c13, OUTPUT);
  pinMode(c20, OUTPUT);
  pinMode(c21, OUTPUT);
  pinMode(c22, OUTPUT);
  pinMode(c23, OUTPUT);
  pinMode(c30, OUTPUT);
  pinMode(c31, OUTPUT);
  pinMode(c32, OUTPUT);
  pinMode(c33, OUTPUT);
  //Sets all LEDs to off
  for(int x=0; x<4; x++){
    for(int y=0; y<16; y++){
      off(colarray[y], layarray[x]);
    }
  }
}



void loop(){
//MODE 1 - Solid Cube
  if(mode==0 || mode==1){
    while(1){
      for(int x=0; x<4; x++){
        for(int y=0; y<16; y++){
          onoff1(colarray[y], layarray[x]);
        }
      }
    }
  }
//MODE 2 - Flashing Cube
  if(mode==2){
    while(1){
      for(int x=0; x<4; x++){
        for(int y=0; y<16; y++){
          onoff(colarray[y], layarray[x], 2);
        }
      }
    }
  }
//MODE 3 - Flittering
  if(mode==3){
    while(1){
      for(int x=0; x<4; x++){
        for(int y=0; y<16; y++){
          onoff(colarray[y], layarray[x], 12);
        }
      }
    }
  }
//MODE 4 - Random
  if(mode==4){
    while(1){
      int x=random(0,15);
      int y=random(0,3);
      onoff(colarray[x], layarray[y], 30);
    }
  }
//MODE 5 - Faster Random
  if(mode==5){
    while(1){
      int x=random(16);
      int y=random(4);
      onoff(colarray[x], layarray[y], 4);
    }
  }
//MODE 6 - Falling Random Columns
  if(mode==6){
    while(1){
      int x=random(16);
      for(int y=3; y>=0; y--){
        onoff(colarray[x], layarray[y], 75);}
    }
  }

}//End of Loop

