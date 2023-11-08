# install with pip
import serial

OUTPUT_QUEUE_SIZE = 64
# String below is whatever port appears in "Tools, Ports" in the Arduino software.
ser = serial.Serial('/dev/ttyUSB0', 9600)
# reads the 'A' sent by the arduino and ignores it
# allows you to check that the arduino is up and running before python starts to write
ser.read(1)
while True:
    if ser.out_waiting < OUTPUT_QUEUE_SIZE:
        # python allows you to convert the input to a bytes 
        ledValueByteArray = (ledValue).to_bytes(1, byteorder='big')
        ser.write(ledValueByteArray)