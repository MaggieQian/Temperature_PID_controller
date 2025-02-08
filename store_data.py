import serial
import time
import pandas as pd
from openpyxl import Workbook
from datetime import datetime

def NowStr():
    x = datetime.now()
    dateStr = f"{x.year:04}_{x.month:02}_{x.day:02}__{x.hour:02}{x.minute:02}{x.second:02}"
    return dateStr
# __start_time_str__ is initialised when the module / this file is loaded.
__start_time_str__ = NowStr()
# Specify file save location (Change this path as needed)
save_path = f"C:/Users/YourUsername/Documents/temperature_log_{__start_time_str__}.xlsx"

# Set up Serial communication
ser = serial.Serial('COM4', 9600, timeout=1)  # Change 'COM4' to your Arduino port
time.sleep(2)  # Allow connection to establish

# Create Excel file
wb = Workbook()
ws = wb.active
ws.append(["Timestamp", "Temperature (C)"])

try:
    while True:
        data = ser.readline().decode('utf-8').strip()
        if data:
            try: 
                temp = float(data)
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                print(f"{timestamp}: {temp} °C")
                ws.append([timestamp, temp])
                wb.save(save_path)  # Save continuously
            except ValueError:
                pass  # Ignore invalid readings
        time.sleep(5)  # Log every 5 seconds

except KeyboardInterrupt:
    print("Logging stopped.")
    ser.close()