#include <SoftwareSerial.h>

// ESP32 connection //////////
/*
  ESP32---------- Arduino UNO
  =====           ===========
  U0T  ---------- D2
  U0R  ---------- D3
*/
//////////////////////////////

//MOTOR Right
const int IN_3=12;
const int IN_4=13;
const int EN_right=11; //speed control
const int offset_right = 35;

//MOTOR Left
const int IN_1=8;
const int IN_2=9;s
const int EN_left=10; //speed control
const int offset_left = 0;


int left_track_val = 0;
int right_track_val = 0;
String inputString = "";
boolean recording = false;

SoftwareSerial mySerial(2, 3); // RX, TX pins for SoftwareSerial

void setup() {
  Serial.begin(9600); // Initialize the hardware serial port for debugging
  mySerial.begin(115200); // Initialize the software serial port
}


void loop() {
  //gpt-bro///////////////////////////////////////////////////////
  while (mySerial.available()) {
    char data = mySerial.read();
    
    if (data == '<' && mySerial.peek() == '|') {
      // Start recording
      recording = true;
      inputString = "";
      mySerial.read(); // consume '|'
    } else if (recording && data == '|' && mySerial.peek() == '>') {
      // Stop recording
      recording = false;
      mySerial.read(); // consume '>'
      // Process the recorded data
      processInputString(inputString);
    } else if (recording) {
      // Record data
      inputString += data;
    }

    //Serial.println(data);
  }

  delay(50);
  //////////////////////////////////////////////////////////////////
drive();

}

void drive()
{
  //if left_track_val == (-ve) ,then the left motor will revers its spinning
  //so left motor reverse   IN_1 --> LOW
  //                        IN_2 --> HIGH
  digitalWrite(IN_1,((left_track_val<0)?LOW:HIGH));
  digitalWrite(IN_2,((left_track_val<0)?HIGH:LOW));
  analogWrite(EN_left,abs(left_track_val));


  //if right_track_val == (-ve) ,then the right motor will revers its spinning
  //so lright motor reverse   IN_3 --> LOW
  //                          IN_4 --> HIGH
  digitalWrite(IN_3,((right_track_val<0)?LOW:HIGH));
  digitalWrite(IN_4,((right_track_val<0)?HIGH:LOW));
  analogWrite(EN_right,abs(right_track_val));
}


void processInputString(String input) {
  int commaIndex = input.indexOf(',');
  
  if (commaIndex != -1) {
    String xString = input.substring(0, commaIndex);
    String yString = input.substring(commaIndex + 1);

    left_track_val = xString.toInt();
    right_track_val = yString.toInt();

    Serial.print("left : ");
    Serial.println(left_track_val);
    Serial.print("right : ");
    Serial.println(right_track_val);
  } else 
  {
    Serial.println("Invalid input format");
  }
}