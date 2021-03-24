#include <SPI.h>
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
int device_number = 1;
int next_device;
int previous_device;

// define the initial values for our inputs and outputs
int rValue = 0;
int gValue = 0;
int bValue = 0;
int irValue = 0;

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
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  //radio.openReadingPipe(2, addresses[1]);
  //radio.openReadingPipe(3, addresses[2]);
  //radio.openReadingPipe(4, addresses[3]);
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
}

void loop() {
  delay(5);
  radio.startListening();
  if (radio.available()) {
    radio.read(&data, sizeof(data));
  }

  unsigned long current_time = millis();
  long timer = current_time - previous_time;
  long timer2 = current_time - previous_time2;
  long timer3 = current_time - previous_time3;

  irValue = analogRead(ir);
  RGB(rValue, gValue, bValue);

  if (data == 20 + device_number) {
    if (irValue > 550) {
      radio.stopListening();
      previous_time = current_time;
      if (timer < timeout) {
        rValue = 0;
        gValue = 255;
        bValue = 0;
        tone(buzzer, 523);
        next_device = random(21, 24);
        if (next_device != 20 + device_number && next_device != previous_device) {
          previous_device = next_device;
        }
      }
    }
    else if(timer > timeout){
      noTone(buzzer);
      rValue = 120;
      gValue = 0;
      bValue = 220;
      data = next_device;
    }
  }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// CODE FOR AUTONOMOUS MODE //////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

  else {
    if(irValue > 550){
      previous_time2 = current_time;
      if(timer2 < timeout){
        rValue = 0;
        gValue = 255;
        bValue = 0;
        tone(buzzer, 523);
        if (data == 0){
          next_device = 21;//random(21, 24);
          if (next_device != 20 + device_number){
            previous_device = next_device;
          }
        }
      }
    }

    else if(timer2 > timeout){
      noTone(buzzer);
      rValue = 120;
      gValue = 0;
      bValue = 220;
      data = next_device;
      delay(5);
      radio.stopListening();
      radio.write(&data, sizeof(data));
    }
  }
  
  Serial.println(data);
}

void RGB(int rValue, int gValue, int bValue)
{
  analogWrite(r, rValue);
  analogWrite(g, gValue);
  analogWrite(b, bValue);
}
