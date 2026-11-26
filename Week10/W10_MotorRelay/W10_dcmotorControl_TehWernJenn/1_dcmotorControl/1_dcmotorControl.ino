/*
  DM3014 Interactive Devices, Teh Wern Jenn 2026
  Week 10 - Motors & Relays
  ESP32-C3 DC Motor Control
  Start, stop, and change direction of motor.
  Additional Components: 12V DC Motor, 2-Channel 12V Relay Module

  Edits; 
 1) Rotate longer , 3 rounds/cycle, then 2, then 1 (forwards)
 1) Rotate longer , 3 rounds (backwards)
 2) Delay time decreases (forwards & backwards) 
 3) Increase stop time  to 2s

Realised cannot remove delay as it resulted in the motor not moving at all. - delay also is how long the motor keeps spinning

*/

const int R1 = 6; // relay 1: motor terminal A
const int R2 = 7; // relay 2: motor terminal B

void motor(int dir) { 
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  delay(100);
  // 0 = stop
  if (dir == 1)  digitalWrite(R1, HIGH); //  1 = forwards
  if (dir == -1) digitalWrite(R2, HIGH); // -1 = reverse
}

void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  motor(0);
  Serial.begin(115200);
}

void loop() {

//realsied these below cannot work as it needs delay to turn
//  1) No delay forwards 3 times, No delay 1 backwards
//   - Stop
//   2) No dealy frowards 2, No delay backwards
//   - Stop 
//   3) No delay forwards 1, 3 delay backwards.
//   - Stop
//   // 1) forwards3 and backwards 1 nonstop no delay
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("forwards");
//   motor(1);

// //stop 
//   Serial.println("stop");
//   motor(0);
//   delay(1000);
  
// //2) forwards 2, backwards 2 No delay 
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("reverse");
//   motor(-1);
//   Serial.println("reverse");
//   motor(-1);

// //stop 
//   Serial.println("stop");
//   motor(0);
//   delay(1000);

// //3) forwards 1, backwards 3 No delay 
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("reverse");
//   motor(-1);
//   Serial.println("reverse");
//   motor(-1);
//   Serial.println("reverse");
//   motor(-1);

//   // 1) forwards3 and backwards 1 
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("forwards");
//   motor(1);
//   Serial.println("forwards");
//   motor(1);


// motor run for longer 
  Serial.println("forwards");
  motor(1);
  delay(7000); // 3 turns 

// motor run for longer 
  Serial.println("forwards");
  motor(1);
  delay(5000); // 2 turns 
// motor run for longer 
  Serial.println("forwards");
  motor(1);
  delay(2000); // 1 turns

// motor run for longer 
  Serial.println("reverse");
  motor(-1);
  delay(7000); // Runs for 3 seconds instead of 2 seconds

//stop 
  Serial.println("stop");
  motor(0);
  delay(1000);

//1) Delay decreasess forwards
Serial.println("forwards");
  motor(1);
  delay(2000); // short delay to reverse

  Serial.println("forwards");
  motor(1);
  delay(1500); // short delay to reverse

  Serial.println("forwards");
  motor(1);
  delay(1000); // short delay to reverse

  Serial.println("forwards");
  motor(1);
  delay(500); // short delay to reverse

  //stop 
  Serial.println("stop");
  motor(0);
  delay(1000);

//1) Delay decreasess Backwards
  Serial.println("reverse");
  motor(-1);
  delay(2000);

  Serial.println("reverse");
  motor(-1);
  delay(1500);
    
  Serial.println("reverse");
  motor(-1);
  delay(1000);

  Serial.println("reverse");
  motor(-1);
  delay(500);

// 3) Increase stop longer
  Serial.println("stop");
  motor(0);
  delay(2000);

}
