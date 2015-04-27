from pyduino import *
import time

if __name__ == '__main__':
    
    # if your arduino was running on a serial port other than '/dev/ttyACM0/'
    # declare: a = Arduino(serial_port='/dev/tty')
    a = Arduino()    

    # sleep to ensure ample time for computer to make serial connection 
    time.sleep(3)    

    # declare the pin our servo is attached to
    # make sure this matches line 26 of one_servo.ino
    # the line that says: int SERVO2_PIN = 2;
    PIN = 2         

    try:
        for i in range(0,1000):
            if i%2 == 0:
                print '180'
                # move servo on pin to an angle of 170 deg
                a.servo_write(PIN,170) 
            else:
                print '10'
                # move servo on pin to an angle of 10 deg
                a.servo_write(PIN,10) 

            time.sleep(1)

    except KeyboardInterrupt:
        # reset position of servo to 90 deg and close connection
        a.servo_write(PIN,90)
        a.close()
