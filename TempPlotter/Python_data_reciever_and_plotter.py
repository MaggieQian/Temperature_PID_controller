import serial
import tkinter as tk
from collections import deque
import statistics

class RollingBuffer:
    def __init__(self, size = 5):
        self.buffer = deque(maxlen=size)
    def add_data(self, data_point):
        self.buffer.append(data_point)
    def get_data(self):
        return list(self.buffer)
    def get_mean(self):
        if self.buffer:
            return statistics.mean(self.buffer)
        return 0
buffer_temp1 = RollingBuffer()
buffer_temp2 = RollingBuffer()
buffer_temp3 = RollingBuffer()

arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)
root = tk.Tk()
root.title("Real-Time Temperature Display")
label1 = tk.Label(root, text="Temp 1: -- °C", font=("Arial", 16))
label1.pack()
label2 = tk.Label(root, text="Temp 2: -- °C", font=("Arial", 16))
label2.pack()
label3 = tk.Label(root, text="Temp 3: -- °C", font=("Arial", 16))
label3.pack()

def update_temperatures():
    data = arduino.readline().decode().strip()  # Read Serial data
    print(data)
   # if data and not data.startswith("Thermocouple"):  # Ignore header
    values = data.split(",")  # Split into list

    if len(values) == 3:  # Ensure correct data format
        try:
            buffer_temp1.add_data(float(values[0]))
            buffer_temp2.add_data(float(values[1]))
            buffer_temp3.add_data(float(values[2]))
            print('entered')
            
            label1.config(text=f"Temp 1: {buffer_temp1.get_mean():.2f} °C")
            label2.config(text=f"Temp 2: {buffer_temp2.get_mean():.2f} °C")
            label3.config(text=f"Temp 3: {buffer_temp3.get_mean():.2f} °C")
        except Exception as e:
            print(f"Error updating values: {e}")

    root.after(1000, update_temperatures)  # Refresh every second

update_temperatures()

root.mainloop()

arduino.close()