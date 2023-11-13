# install with pip
import serial
import time

from django.http import HttpRequest

# This may present an issue of writing over the previous array or reading 
def processPresets(upCloud, downCloud, storm, noStorm, changeRight, changeLeft, changed):
    print("hit")
    OUTPUT_QUEUE_SIZE = 64
    # String below is whatever port appears in "Tools, Ports" in the Arduino software.
    ser = serial.Serial('/dev/cu.usbserial-0001', 9600)
    # reads the 'A' sent by the arduino and ignores it
    # allows you to check that the arduino is up and running before python starts to write
    ser.read(1)
    while changed:
        changed = False
        if ser.out_waiting < OUTPUT_QUEUE_SIZE:
            # python allows you to convert the input to a bytes 
            boolList = [upCloud, downCloud, storm, noStorm, changeRight, changeLeft]
            my_bytearray = bytearray()
            my_bytearray.extend(boolList)
            print(my_bytearray)
            my_bytes = bytes(my_bytearray)
            ser.write(my_bytes)
        time.sleep(3) # Sleep for 3 seconds