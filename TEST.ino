//Imports the BitVoicer library to the sketch
#include <BitVoicer11.h>
//Instantiates the BitVoicerSerial class
BitVoicerSerial bvSerial = BitVoicerSerial();
//Stores the data type retrieved by getData()
byte dataType = 0;
//Stores the state of pin 4
byte pinVal = 0;
//Stores the state of pin 5
byte pinVal7 = 0;
//Stores true if the Audio Streaming Calibration tool
//is running
boolean sampleTest = false;
void setup()
{
 //Sets the analog reference to external (AREF pin)
 //WARNING!!! If anything is conected to the AREF pin,
 //this function MUST be called first. Otherwise, it will
 //damage the board.
 bvSerial.setAnalogReference(BV_EXTERNAL);
 //Sets up the microcontroller to perform faster analog reads
 //on the specified pin
 bvSerial.setAudioInput(0);
 //Starts serial communication at 115200 bps
 Serial.begin(115200);
 //Sets digital pin 4 as OUTPUT
 pinMode(4, OUTPUT);
// //Turns off pin 4
digitalWrite(4, pinVal);

 //Sets digital pin 7 as OUTPUT
 pinMode(7, OUTPUT);
 //Turns off pin 4
 digitalWrite(7, pinVal7);
}
void loop()
{
  //Serial.println("test");
  //delay(1000);
 //Captures audio and sends it to BitVoicer if the Audio
 //Streaming Calibration Tool is running
 if (sampleTest == true)
 {
 //The value passed to the function is the time
 //(in microseconds) that the function has to wait before
 //performing the reading. It is used to achieve about
 //8000 readings per second.
 bvSerial.processAudio(46); }

 //Captures audio and sends it to BitVoicer if the Speech
 //Recognition Engine is running
 if (bvSerial.engineRunning)
 {
 //The value passed to the function is the time
 //(in microseconds) that the function has to wait before
 //performing the reading. It is used to achieve about
 //8000 readings per second.
 bvSerial.processAudio(46);
 }

 //Updates the pin 4 state on every loop
 digitalWrite(4, pinVal);
  digitalWrite(7, pinVal);
}
//This function runs every time serial data is available
//in the serial buffer after a loop
void serialEvent()
{
 //Reads the serial buffer and stores the received data type
 dataType = bvSerial.getData();

 //Changes the value of sampleTest if the received data was
 //the start/stop sampling command
 if (dataType == BV_COMMAND)
 sampleTest = bvSerial.cmdData;

 //Signals BitVoicer's Speech Recognition Engine to start
//listening to audio stream after the engineRunning status
 //was received
 if (dataType == BV_STATUS && bvSerial.engineRunning == true)
 bvSerial.startStopListening();

 //Checks if the data type is the same as the one in the
 //Voice Schema
 if (dataType == BV_BYTE)
 {
  Serial.print(bvSerial.byteData);
  //Serial.print("%x",dataType);
 //Checks the value stored in byteData by getData() and
 //changes the pin value
 if (bvSerial.byteData == 0){
    pinVal = LOW;
    pinVal7 = HIGH; 
 }

 else if (bvSerial.byteData == 2){
    pinVal = LOW;
    pinVal7 = HIGH;
 }
  else if (bvSerial.byteData == 1){
    pinVal = HIGH;
    pinVal7 = LOW;
 }else{
    pinVal = LOW;
    pinVal7 = LOW;
 }
 }
}

