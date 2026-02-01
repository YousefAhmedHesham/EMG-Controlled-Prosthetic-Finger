#include <Servo.h>
// Pin definitions
const int emgPin = A0; // Analog pin for EMG sensor
const int servoPin = 9; // Digital pin for servo control
const int switchPin = 7; // Digital pin for the mode switch
// Servo object
Servo myServo;
// EMG signal processing variables
const int WINDOW = 1000; // Window size for RMS calculation
const float FILTER_COEFF = 0.2; // Filter coefficient
float rms = 0.0; // RMS value
float emg_value = 0.0; // Current EMG value
float filtered_emg = 0.0; // Filtered EMG value
float filtered_prev = 0.0; // Previous filtered value
float output = 0.0; // Output signal
int currentPos = 120; // Current servo position
void setup() {
pinMode(switchPin, INPUT_PULLUP); // Configure the switch pin
myServo.attach(servoPin); // Attach the servo to the
specified pin
Serial.begin(9600); // Initialize serial
communication
}
void loop() {
int switchState = digitalRead(switchPin); // Read the switch
state
if (switchState == LOW) { // Proportional control mode
proportionalControl();
} else { // Sequential control mode
sequentialControl();
}
}
void proportionalControl() {
rms = 0.0; // Reset RMS value
// Calculate filtered signal and RMS value
for (int i = 0; i < WINDOW; i++) {
  emg_value = analogRead(emgPin);
filtered_prev = filtered_emg;
filtered_emg = FILTER_COEFF * emg_value + (1 - FILTER_COEFF)
* filtered_emg;
output = filtered_emg - filtered_prev;
rms += (output * output);
}
rms = sqrt(rms / WINDOW); // Final RMS value
rms = rms * 10; // Scale RMS value for better range
Serial.println(rms);
// Map RMS value to servo angle
int servoAngle = map(rms, 0, 400, 0, 180);
// Constrain and write to servo
myServo.write(constrain(servoAngle, 0, 180));
delay(100); // Adjust delay for responsiveness
}
void sequentialControl() {
// High-pass filter for EMG signal
float filteredValue = 0.0;
float prevFilteredValue = 0.0;
filteredValue = 0.1 * (filteredValue + analogRead(emgPin) -
prevFilteredValue);
prevFilteredValue = filteredValue;
// Print filtered EMG signal to Serial Plotter
Serial.println("Sequential Mode - Filtered EMG Value: ");
Serial.println(filteredValue);
if (filteredValue >= 600 && filteredValue <= 1023) {
if (currentPos == 120) {
moveServo(40); // Move servo from 120 degrees to 40
degrees
} else if (currentPos == 40) {
moveServo(-40); // Move servo from 40 degrees to -40
degrees
} else if (currentPos == -40) {
moveServo(120); // Move servo from -40 degrees to 120
degrees
}
// Wait for the EMG reading to change
while (filteredValue >= 600 && filteredValue <= 1023) {
filteredValue = analogRead(emgPin);
delay(10); // Adjust delay as needed
}
}
delay(50); // Adjust delay as needed
}
void moveServo(int targetPos) {
int step = (targetPos > currentPos) ? 1 : -1;
while (currentPos != targetPos) {
currentPos += step;
myServo.write(currentPos);
delay(15); // Adjust delay as needed
}
}