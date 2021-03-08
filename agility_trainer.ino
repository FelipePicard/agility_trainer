

// define the pins for our inputs and outputs
// ir is the infrared distance sensor and r, g and b are the RGB LED colors
#define ir A6
#define buzzer A3
#define r 3
#define g 5
#define b 6

// define the initial values for our inputs and outputs
int rValue = 255;
int gValue = 0;
int bValue = 255;
int irValue = 0;

// create the variables for timing the events
long previous_time = 0;
const long timeout = 1200;

void setup() {
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ir, INPUT);
  Serial.begin(9600);
}

void loop() {
  // current_time, or the millis() function, tracks how much time the arduino
  // has been turned on for, in milliseconds
  unsigned long current_time = millis();
  // the timer is the current time, or millis(), subtracted from the previous time.
  // initially, previous_time is 0, but we will make it equal to current_time at some
  // point in order to "restart" the timer --> timer = current_time - current_time = 0
  long timer = current_time - previous_time;

  // irValue is the value of the reading from the ir pin, and we also define the
  // red, green and blue values for the RGB LED
  irValue = analogRead(ir);
  RGB(rValue, gValue, bValue);

  // if the distance value is within our threshold (the user's hand is close
  // enough to the sensor)
  if(irValue > 450){
    // restart the timer
    previous_time = current_time;
    // while the timer value is lower than our timeout value, do the follwing
    if(timer < timeout){
      rValue = 0;
      gValue = 60;
      bValue = 0;
      // 523 is the frequency in hertz that's being played in our buzzer
      tone(buzzer, 523);
    }
  }
  // while the timer value is greater than our timeout value, do the follwing
  else if(timer > timeout){
      noTone(buzzer);
      rValue = 255;
      gValue = 0;
      bValue = 255;
    }
  Serial.println(timer);
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
