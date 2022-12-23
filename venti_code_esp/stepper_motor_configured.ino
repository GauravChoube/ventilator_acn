
// #include<math.h>
// const int stepPin = 3; 
// const int dirPin = 4; 
// int p= 800; //ml
// int q= 15; //bpm
// float r = (0.056 * p); //% of ambu bag compression

// float s = (r * 2.4); //degrees for the rotation of stepper motor

// float t = (s * 0.056); //steps for stepper motor

// float u = ((60/q) * 1000) - 1000;




 
// void setup() {
//   // Sets the two pins as Outputs
//   pinMode(stepPin,OUTPUT); 
//   pinMode(dirPin,OUTPUT);

  
// }
// void loop() {
//   digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
//   // Makes 200 pulses for making one full cycle rotation
  
//   for(int x = 0; x < t; x++) {
//     digitalWrite(stepPin,HIGH); 
//     delayMicroseconds(1000); 
//     digitalWrite(stepPin,LOW); 
//     delayMicroseconds(1000); 
//   }
//   delay(1000);// One second delay
  
//   digitalWrite(dirPin,LOW); //Changes the rotations direction
//   // Makes 400 pulses for making two full cycle rotation
  
//   for(int x = 0; x < t; x++) {
//     digitalWrite(stepPin,HIGH);
//     delayMicroseconds(u);
//     digitalWrite(stepPin,LOW);
//     delayMicroseconds(u);
//   }
//   delay(1000);
// }