/*
 * Sketch to control the pins of Arduino via serial interface
 *
 * Commands implemented with examples:
 *
 * - RD13 -> Reads the Digital input at pin 13
 * - RA4 - > Reads the Analog input at pin 4
 * - WD13:1 -> Writes 1 (HIGH) to digital output pin 13
 * - WA6:125 -> Writes 125 to analog output pin 6 (PWM)
 */

#include <Servo.h>


char operation; // Holds operation (R, W, ...)
char mode; // Holds the mode (D, A)
int pin_number; // Holds the pin number
int digital_value; // Holds the digital value
int analog_value; // Holds the analog value
int value_to_write; // Holds the value that we want to write
int wait_for_transmission = 5; // Delay in ms in order to receive the serial data

// create servo object to control a servo
// a maximum of eight servo objects can be created
Servo SERVO2; 
Servo SERVO3;
Servo SERVO4;

int SERVO2_PIN = 2; // azimuth angle
int SERVO3_PIN = 3; // altitude angle
int SERVO4_PIN = 4; // wrist angle


void setup() {
    Serial.begin(9600); // Serial Port at 9600 baud
    Serial.setTimeout(500); // Instead of the default 1000ms, in order
                            // to speed up the Serial.parseInt() 
    
    SERVO2.attach(SERVO2_PIN);
    SERVO2.write(180); // reset to original position

    SERVO3.attach(SERVO3_PIN);
    SERVO3.write(90); // reset to original position
    // servo3 limit 0-85

    SERVO4.attach(SERVO4_PIN);
    SERVO4.write(90); // reset to original position
}


void servo_write(int pin_number, int servo_value){
    /*
     * Performs a servo write on pin_number with the servo_value
     * The value must be 0 to 180 (might change depending on servo)
     */
     
     if (pin_number==SERVO2_PIN)
     {
       SERVO2.write(servo_value);
       delay(10);
       
     } 
     else if (pin_number == SERVO3_PIN) 
     {
       SERVO3.write(servo_value);
       delay(10);
     }
     else if (pin_number == SERVO4_PIN) 
     {
       SERVO4.write(servo_value);
       delay(10);
     }

}


void loop() {
    // Check if characters available in the buffer
    if (Serial.available() > 0) 
    {
        // parse information
        // courtesy of lekum 
        operation = Serial.read();
        delay(wait_for_transmission); // If not delayed, second character is not correctly read
        mode = Serial.read();
        pin_number = Serial.parseInt(); // Waits for an int to be transmitted
        
        if (Serial.read()==':')
        {
            value_to_write = Serial.parseInt(); // Collects the value to be written
        }

        // if we recieve proper input write servo
        if (operation == 'W')
        {
            if (mode == 'S')
            {
                servo_write(pin_number, value_to_write);
            }
        }
        
    }
}
