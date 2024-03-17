# import serial for serial communication
import serial
# import time for adding delay
import time

# creating a  serial port object
arduino = serial.Serial('COM3',9600, timeout=1) 
# waiting for 1 second (just for the connection to get establish)
# time.sleep(1)

# read the serial data and print it as line

def getValue(data):
    arduino.write(b'g')
    data =  arduino.readline().decode('ascii')
    print(data)
    return data

print ("Press 1 to turn ON LED or Press 0 to turn OFF LED")

while  True:
    userInput = input()
    if userInput == "y":
        print("value:" )
        getValue(userInput)
    elif userInput == "n":
        getValue(userInput)

