"""
A library to interface Arduino Servos through serial connection
"""
import serial

class Arduino():
    """
    Models an Arduino connection
    """

    def __init__(self, serial_port='/dev/ttyACM0', baud_rate=9600,
            read_timeout=5):
        """
        Initializes the serial connection to the Arduino board
        """
        self.conn = serial.Serial(serial_port, baud_rate)
        self.conn.timeout = read_timeout # Timeout for readline()
        print 'Connection initiated'
     
    def servo_write(self, pin_number, digital_value):
        """
        Writes the digital_value on pin_number
        Internally sends b'WS{pin_number}:{digital_value}' over the serial
        connection 
        """
        command = "WS{}:{}".format(str(pin_number),str(digital_value)).encode()
        self.conn.write(command) 

    def close(self):
        """
        To ensure we are properly closing our connection to the
        Arduino device. 
        """
        self.conn.close()
        print 'Connection to Arduino closed'

