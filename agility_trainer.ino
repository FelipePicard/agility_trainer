#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// define the pins for our inputs and outputs
// ir is the infrared distance sensor and r, g and b are the RGB LED colors
#define ir A6
#define buzzer A3
#define r 3
#define g 5
#define b 6

RF24 radio(10, 9);
const byte addresses[][6] = {"00001", "00002", "00003", "00004"};
int data;
int device_number = 2;
int next_device;
int previous_device;

// define the initial values for our inputs and outputs
int rValue = 0;
int gValue = 0;
int bValue = 0;
int irValue = 0;

// creates an array (list) for storing the sequence of lights
int sequence[] = {};

// create the variables for timing the events
long previous_time = 0;
long previous_time2 = 0;
long previous_time3 = 0;
const long timeout = 1200;

void setup() {
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ir, INPUT);

  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  //radio.openReadingPipe(2, addresses[1]);
  //radio.openReadingPipe(3, addresses[2]);
  //radio.openReadingPipe(4, addresses[3]);
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
}

void loop() {
  radio.startListening();
  if(radio.available()){
  radio.read(&data, sizeof(data));
  }

  // current_time, or the millis() function, tracks how much time the arduino
  // has been turned on for, in milliseconds
  unsigned long current_time = millis();
  // the timer is the current time, or millis(), subtracted from the previous time.
  // initially, previous_time is 0, but we will make it equal to current_time at some
  // point in order to "restart" the timer --> timer = current_time - current_time = 0
  long timer = current_time - previous_time;
  long timer2 = current_time - previous_time2;
  long timer3 = current_time - previous_time3;

  // irValue is the value of the reading from the ir pin, and we also define the
  // red, green and blue values for the RGB LED
  irValue = analogRead(ir);
  RGB(rValue, gValue, bValue);

  if(data == 20 + device_number){ //change data value for each device
      rValue = 255;
      gValue = 0;
      bValue = 0;
      // 523 is the frequency in hertz that's being played in our buzzer
      tone(buzzer, 523);
  }

  if(data == 20 + device_number){ //change data value for each device
     rValue = 255;
     gValue = 0;
     bValue = 0;
     // 523 is the frequency in hertz that's being played in our buzzer
     tone(buzzer, 523);
  }

  else{
  // if the distance value is within our threshold (the user's hand is close
  // enough to the sensor)
  if(irValue > 550){
    // restart the timer
    previous_time = current_time;
    // while the timer value is lower than our timeout value, do the follwing
    if(timer < timeout){
      rValue = 0;
      gValue = 255;
      bValue = 0;
      // 523 is the frequency in hertz that's being played in our buzzer
      tone(buzzer, 523);
      // "roll a die" to see which will be the next device
      next_device = random(21, 24);
      if(next_device != 20 + device_number){
      previous_device = next_device;
      data = next_device;
      }
    }
  }
  // while the timer value is greater than our timeout value, do the follwing
  else if(timer > timeout){
      noTone(buzzer);
      rValue = 120;
      gValue = 0;
      bValue = 220;
      radio.stopListening();
      radio.write(&data, sizeof(data));
    }
  }
    Serial.println(data);
}

// this is a function to make it easier to choose the colors in the RGB LED.
// we use it in the loop() section of the code by writting RGB and the value
// we want for each color inside the parentheses --> (rValue, gValue, bValue)
void RGB(int rValue, int gValue, int bValue)
 {
  analogWrite(r, rValue);
  analogWrite(g, gValue);
  analogWrite(b, bValue);
}
