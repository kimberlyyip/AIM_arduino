# install with pip
import serial
import time

from django.http import HttpRequest

"""
Sends the appropriate boolean values to the arduino.
------------
Parameters:
    bool upCloud: Reports whether the clouds are currently raised
    bool downCloud: Reports whether the clouds are currently lowered
    bool storm: Reports whether the current setting is stormy
    bool noStorm: Reports whether the current setting is not stormy
    bool changeRight: Reports whether the backdrop should move right
    bool changeLeft: Reports whether the backdrop should move left
    bool changed: Reports whether the data has been changed
------------
""" 
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
            # Create a list of the boolean values you want to send
            boolList = [upCloud, downCloud, storm, noStorm, changeRight, changeLeft]
            # Instantiate a bytearray
            my_bytearray = bytearray()
            # convert your boolList to a bytearray using extend
            my_bytearray.extend(boolList)
            print(my_bytearray)
            # convert you bytearray to bytes to write to the queue
            my_bytes = bytes(my_bytearray)
            ser.write(my_bytes)
        # sleep for 1 sec to allow information to be sent and processed
        time.sleep(1)