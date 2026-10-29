import serial
import time
import csv

# --- AETHER MK-1 DATA LOGGER ---

# 1. User Inputs
filename = input("Enter filename to save (e.g., real_idle.csv or real_struggle.csv): ")
com_port = input("Enter your RX Board COM port (e.g., COM3): ").upper()
baud_rate = 115200
record_duration = 60  # Exactly 60 seconds of data
countdown = 15        # 15 seconds to evacuate the room

try:
    # Open the serial port
    ser = serial.Serial(com_port, baud_rate, timeout=1)
    time.sleep(2) # Brief pause to let serial connection stabilize
    ser.reset_input_buffer()

    # 2. The Evacuation Timer
    print(f"\n[!] WARNING: Commencing data acquisition in {countdown} seconds.")
    print(">>> EVACUATE THE ROOM NOW / GET IN POSITION <<<")
    
    for i in range(countdown, 0, -1):
        print(f"Recording starts in: {i}...")
        time.sleep(1)

    print("\n[REC] RECORDING ACTIVE! CAPTURING DATA FOR 60 SECONDS.")
    
    # 3. Data Collection
    start_time = time.time()
    data_points = []
    
    # Add the CSV header
    data_points.append(["timestamp", "rssi"])

    while (time.time() - start_time) < record_duration:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            # Ensure the line has our comma-separated format (timestamp,rssi)
            if "," in line:
                try:
                    ts, rssi = line.split(",")
                    data_points.append([ts, rssi])
                except ValueError:
                    pass # Ignore any corrupted serial lines

    # 4. Save and Close
    ser.close()
    print("\n[STOP] RECORDING COMPLETE. PORT CLOSED.")

    # Write to CSV file
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data_points)

    print(f"[SUCCESS] Data successfully saved to {filename} in your current folder.")
    print(f"[INFO] Total data points collected: {len(data_points) - 1}")

except serial.SerialException:
    print(f"\n[ERROR] Could not open {com_port}. Check if your board is plugged in or if the Arduino IDE Serial Monitor is still open (it blocks Python from reading).")