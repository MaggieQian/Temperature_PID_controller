import serial
import time
from datetime import datetime
import pandas as pd
import matplotlib.pyplot as plt

def NowStr():
    x = datetime.now()
    dateStr = f"{x.year:04}_{x.month:02}_{x.day:02}__{x.hour:02}{x.minute:02}{x.second:02}"
    return dateStr
# __start_time_str__ is initialised when the module / this file is loaded.
__start_time_str__ = NowStr() #Don't change it now we have it set.


# Set up Serial communication
ser = serial.Serial('COM4', 9600, timeout=1)  # Change 'COM4' to your Arduino port
time.sleep(2)  # Allow connection to establish

def Send_to_Arduino(K):
    str_val = str(K)
    print(f"{NowStr()} Sending: {str_val}")
    try:
        data_written = serial_obj.write(str_val.encode())
    except:
        print("Write to Arduino failed.")
    return

# pseuodo list of Kp, Ki, Kd
K_arr = [1,1,1]
Send_to_Arduino(K_arr)

#---------------------------------------------------------------------------------
# Specify file save location (Change this path as needed)
csv_file = f"E:\\Maggie\\temperature_log_Kp{Kp}_Ki{Ki}_Kd{Kd}.csv"
save_path_fig = f"E:\\Maggie\\temperature_log_Kp{Kp}_Ki{Ki}_Kd{Kd}.png"

# Create/open CSV file and write headers if it doesn’t exist
with open(csv_file, "w") as f:
    f.write("Elapsed Time (s), Temperature (C)\n")

# Lists to store data for plotting
time_elapsed_list = []
temperature_list = []

# Start time for elapsed time calculation
start_time = time.time()

try:
    while True:
        data = ser.readline().decode('utf-8').strip()
        if data:
            try: 
                temp = float(data)
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                elapsed_time = round(time.time() - start_time, 2)  # Time in seconds
                print(f"[{elapsed_time}s] {timestamp}: {temp} °C") # Live console output
                
                # Append data to CSV
                with open(csv_file, "a") as f:
                    f.write(f"{elapsed_time},{temp}\n")
                
                # Store data for plotting
                time_elapsed_list.append(elapsed_time)
                temperature_list.append(temp)

            except ValueError:
                pass  # Ignore invalid readings
        time.sleep(5)  # Log every 5 seconds

except KeyboardInterrupt:
    print("Logging stopped.")
    ser.close()

# Plot temperature vs. time elapsed after logging stops
plt.figure(figsize=(8, 5))
plt.plot(time_elapsed_list, temperature_list, marker='o', linestyle='-', color='b', label="Temperature (°C)")
plt.xlabel("Elapsed Time (seconds)")
plt.ylabel("Temperature (°C)")
plt.title("Temperature vs. Time Elapsed")
plt.legend()
plt.grid(True)
plt.show()
plt.savefig(save_path_fig)
