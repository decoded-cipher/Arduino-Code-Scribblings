from pyfirmata import Arduino
import time

# Define the port where Arduino is connected
port = 'COM3'  # Replace with your port

# Establish a connection with the Arduino
board = Arduino(port)

# Set-up the pin modes
# d => digital, 10 => Number of the pin, o => output
led_pin = board.get_pin('d:10:o')

# Blink the LED for 5 times then exit
for i in range(5):
    # Turn the LED ON
    led_pin.write(1)  
    print("LED ON")
    time.sleep(1)
    # Turn the LED OFF
    led_pin.write(0)  
    print("LED OFF")
    time.sleep(1)

# Closing the communication with the Arduino
board.exit()