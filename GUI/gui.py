import tkinter as tk
from tkinter import messagebox
from subprocess import Popen, PIPE

# Function to run the SAP-1 simulation (this would call your C++ program)
def run_simulation(op1, op2, op):
    # Run the C++ program (assuming it's compiled and the executable is "core")
    process = Popen(["./core", str(op1), str(op2), op], stdout=PIPE, stderr=PIPE)
    stdout, stderr = process.communicate()
    return stdout.decode(), stderr.decode()

# Function to handle the start button click event
def start_simulation():
    try:
        # Get input values
        op1 = int(op1_entry.get())
        op2 = int(op2_entry.get())
        op = operation_var.get()

        if not (0 <= op1 <= 255 and 0 <= op2 <= 255):
            raise ValueError("Operands must be between 0 and 255.")

        # Run the simulation and get the output
        stdout, stderr = run_simulation(op1, op2, op)

        if stderr:
            messagebox.showerror("Error", f"Error occurred: {stderr}")
        else:
            # Show the results in the Text widget
            output_text.delete(1.0, tk.END)  # Clear previous text
            output_text.insert(tk.END, stdout)  # Display the new output

    except ValueError as e:
        messagebox.showerror("Input Error", str(e))

# Set up the main window
root = tk.Tk()
root.title("SAP-1 Simulator")

# Operand 1 input
op1_label = tk.Label(root, text="Operand 1 (0-255):")
op1_label.grid(row=0, column=0, padx=10, pady=10)
op1_entry = tk.Entry(root)
op1_entry.grid(row=0, column=1, padx=10, pady=10)

# Operand 2 input
op2_label = tk.Label(root, text="Operand 2 (0-255):")
op2_label.grid(row=1, column=0, padx=10, pady=10)
op2_entry = tk.Entry(root)
op2_entry.grid(row=1, column=1, padx=10, pady=10)

# Operation input (dropdown)
operation_label = tk.Label(root, text="Operation (+ or -):")
operation_label.grid(row=2, column=0, padx=10, pady=10)
operation_var = tk.StringVar(value="+")
operation_dropdown = tk.OptionMenu(root, operation_var, "+", "-")
operation_dropdown.grid(row=2, column=1, padx=10, pady=10)

# Start Button
start_button = tk.Button(root, text="Start Simulation", command=start_simulation)
start_button.grid(row=3, column=0, columnspan=2, pady=10)

# Output Text Box (for simulation progress)
output_label = tk.Label(root, text="Simulation Output:")
output_label.grid(row=4, column=0, padx=10, pady=10)
output_text = tk.Text(root, height=10, width=50)
output_text.grid(row=5, column=0, columnspan=2, padx=10, pady=10)

# Start the Tkinter event loop
root.mainloop()
