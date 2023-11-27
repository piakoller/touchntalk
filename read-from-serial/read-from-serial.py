import serial
import time
from pyembedded.rfid_module.rfid import RFID


rfid = RFID(port='/dev/ttyUSB0', baud_rate=9600)
print(rfid.get_id())



tags = ['one', 'two', 'three'];


ser = serial.Serial(
    # TODO Proper serial information
    # Figure out what the port name is and if the other settings are correct.
    port='SERIAL',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)

#this will store the line
seq = []
count = 1

while True:
    tag_number = rfid.get_id();
    

    for c in ser.read():
        seq.append(chr(c)) #convert from ANSII
        joined_seq = ''.join(str(v) for v in seq) #Make a string from array

        if chr(c) == '\n':
            print("Line " + str(count) + ': ' + joined_seq)
            seq = []
            count += 1
            break

    

ser.close()
