import serial.tools.list_ports
import serial
import dotenv
import time
import os

import format


dotenv.load_dotenv()


def get_daisy_port() -> str:
    ports = serial.tools.list_ports.comports();
    target = os.getenv("DAISY_SERIAL_NUMBER")

    for port in ports:
        if port.serial_number == target:
            return port.name

    format.throw(f"No port found with serial number {target}. Ensure the device is connected.")  


def connect_to_daisy(port_name, baud_rate = 9600):
    format.temp(f"Connecting to port {port_name}...")

    serial_connection = serial.Serial(port_name, baud_rate, timeout=1)

    format.success(f"Connected and listening on port {serial_connection.name}")

    while True:
        if serial_connection.in_waiting > 0:

            incoming_data = serial_connection.readline().decode('utf-8').strip()

            print(f"{format.CYAN}Recieved: {format.CLEAR}{incoming_data}")
    
        time.sleep(0.1)


if __name__ == "__main__":
    connect_to_daisy(get_daisy_port())