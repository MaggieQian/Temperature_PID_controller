import serial
import time
import pandas as pd
import matplotlib.pyplot as plt

# Set up Serial communication
ser = serial.Serial('COM4', 9600, timeout=1)  # Change 'COM4' to your Arduino port
time.sleep(2)  # Allow connection to establish

def Send_to_Arduino(K):
    args = ['Control values'] + K
    str_val = str(args)
    #print(f"{NowStr()} Sending: {str_val}")
    try:
        data_written = serial_obj.write(str_val.encode())
    except:
        print("Write to Arduino failed.")
    #Read_from_Arduino()
    return

#=====================
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
