/* Shift Register LED Animation

Created by Eric Bauer
Last Modified: 2/24/15
 
 */

// set pin numbers:
const int DSpin =  2;      // the serial data pin
const int STCPpin = 3;     // the Storage Register clock pin (loads the shift register buffer)
const int SHCPpin = 4;     // the Shift Register clock pin (loads serial data into the shift register buffer)

// Frame and Play speed information
byte frames[] = {0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00100100, 0b01000010, 0b10000001};             // custom animation frames can be hardcoded
byte frameDurations[] = {1, 1, 1, 2, 1, 1, 1};
int numberOfFrames = 7;
float framesPerSecond = 60;
int msecondsPerFrame = float(1/framesPerSecond)*1000; // milliseconds ot delay

// Animation functions
void playScanner(); // generated animation
void playFrames(); // hardcoded animation

// Shift Register functions
void shiftOutNew(byte data);

/****************************************
*        Main Control Functions
*****************************************/

void setup() {
  // set the digital pin as output:
  pinMode(DSpin, OUTPUT); 
  pinMode(STCPpin, OUTPUT); 
  pinMode(SHCPpin, OUTPUT); 
  //initialize pin states (don't want to clock anything in yet
  digitalWrite(STCPpin, LOW);
  digitalWrite(SHCPpin, LOW);
  digitalWrite(DSpin, LOW);  
}

void loop()
{
  //NOTE: Comment out one of these functions to choose an animation
  
  playFrames();
  //playScanner();
  
}

/****************************************
*        Shift Register Functions
*****************************************/

void shiftOutNew(byte data){
 int dataState = 0;
 digitalWrite(STCPpin, LOW);
 for(int i = 7; i>=0; i--){ //start by shifting out the LSB
  digitalWrite(SHCPpin, LOW);  
  dataState = (0b10000000 >> i) & data; // test each bit of "data"
  digitalWrite(DSpin, dataState);
  delay(5);
  digitalWrite(SHCPpin, HIGH);
  
 } 
 digitalWrite(STCPpin, HIGH); // load the buffer and output the frame
}

/****************************************
*        LED Animation Functions
*****************************************/

void playScanner(){
  byte frame = 0b00000001;
  for(int i = 0; i<8; i++){
    shiftOutNew(frame << i);
    delay(msecondsPerFrame);
  }
  frame =0b10000000;
  for(int i = 0; i<8; i++){
    shiftOutNew(frame >> i);
    delay(msecondsPerFrame);
  }
}

void playFrames(){
 for(int i = 0; i<numberOfFrames; i++){
   shiftOutNew(frames[i]);
   delay(msecondsPerFrame*frameDurations[i]);
 }  
}

