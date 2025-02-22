import serial
import tkinter as tk

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
    if data and not data.startswith("Thermocouple1"):  # Ignore header
        values = data.split(",")  # Split into list
        if len(values) == 3:  # Ensure correct data format
            try:
                
                label1.config(text=f"Temp 1: {values[0]} °C")
                label2.config(text=f"Temp 2: {values[1]} °C")
                label3.config(text=f"Temp 3: {values[2]} °C")
            except Exception as e:
                print(f"Error updating values: {e}")

    root.after(1000, update_temperatures)  # Refresh every second

update_temperatures()

root.mainloop()

arduino.close()