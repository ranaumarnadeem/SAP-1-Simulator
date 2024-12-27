import tkinter as tk
from tkinter import messagebox
from subprocess import Popen, PIPE

# Function to run the SAP-1 simulation (this would call your C++ program)
def run_simulation(op1, op2, op):
    try:
        # Run the C++ program
        process = Popen(["./core", str(op1), str(op2), op], stdout=PIPE, stderr=PIPE)
        stdout, stderr = process.communicate()
        return stdout.decode(), stderr.decode()
    except FileNotFoundError:
        return "", "Error: Executable not found. Ensure 'core' is in the same directory."
    except Exception as e:
        return "", f"An unexpected error occurred: {str(e)}"

# Function to handle the start button click or Enter key press
def start_simulation(event=None):  # Accept `event` for Enter key binding
    try:
        # Get input values
        op1_input = op1_entry.get()
        op2_input = op2_entry.get()
        op = operation_var.get()

        # Check if operands are numeric and within the valid range (0-255)
        if not (op1_input.isdigit() and op2_input.isdigit()):
            raise ValueError("Operands must be numeric values.")
        
        op1 = int(op1_input)
        op2 = int(op2_input)

        if not (0 <= op1 <= 255 and 0 <= op2 <= 255):
            raise ValueError("Operands must be between 0 and 255.")

        # Run the simulation and get the output
        stdout, stderr = run_simulation(op1, op2, op)

        if stderr:
            messagebox.showerror("Error", f"Error occurred: {stderr}")
        else:
            # Display the process with signal updates
            display_simulation_progress(stdout)

    except ValueError as e:
        messagebox.showerror("Input Error", str(e))

# Function to simulate progress with delays between steps
def display_simulation_progress(output):
    output_text.delete(1.0, tk.END)  # Clear previous text
    delay_time = int(delay_var.get()) * 1000  # Convert to milliseconds

    # Step 1: Data written to RAM
    output_text.insert(tk.END, "Writing data to RAM...\n")
    toggle_signal(ram_write_label, "green", delay_time)
    root.after(delay_time, lambda: update_log("Data successfully written to RAM.\n"))

    # Step 2: Data read from RAM
    root.after(2 * delay_time, lambda: toggle_signal(ram_read_label, "red", delay_time))
    root.after(2 * delay_time, lambda: update_log("Reading data from RAM...\n"))
    root.after(3 * delay_time, lambda: update_log("Data successfully read from RAM.\n"))

    # Step 3: Instruction Register active
    root.after(4 * delay_time, lambda: toggle_signal(ir_label, "blue", delay_time))
    root.after(4 * delay_time, lambda: update_log("Instruction loaded into IR...\n"))

    # Step 4: Accumulator active
    root.after(5 * delay_time, lambda: toggle_signal(ac_label, "yellow", delay_time))
    root.after(5 * delay_time, lambda: update_log("Result stored in Accumulator.\n"))

    # Final Step: Display program output
    root.after(6 * delay_time, lambda: update_log(f"Program Output:\n{output}"))

# Helper function to toggle signals
def toggle_signal(label, color, delay):
    label.config(bg=color)
    root.after(delay, lambda: label.config(bg="gray"))

# Helper function to update the log with new text
def update_log(message):
    output_text.insert(tk.END, message)
    output_text.see(tk.END)  # Auto-scroll to the bottom

# Function to refresh the command log
def refresh_log():
    output_text.delete(1.0, tk.END)  # Clear previous text
    output_text.insert(tk.END, "Log refreshed.\n")  # Placeholder

# Set up the main window
root = tk.Tk()
root.title("SAP-1 Simulator")
root.configure(bg="#87CEEB")  # Set background color to sky blue

# Make the window resizable
root.rowconfigure(list(range(12)), weight=1)
root.columnconfigure(list(range(2)), weight=1)

# Styling variables
label_font = ("Arial", 12, "bold")
entry_font = ("Arial", 12)
text_font = ("Courier", 12)
text_color = "white"

# Operand 1 input
op1_label = tk.Label(root, text="Operand 1 (0-255):", font=label_font, bg="#87CEEB", fg=text_color)
op1_label.grid(row=0, column=0, padx=10, pady=10, sticky="e")
op1_entry = tk.Entry(root, font=entry_font)
op1_entry.grid(row=0, column=1, padx=10, pady=10, sticky="w")

# Operand 2 input
op2_label = tk.Label(root, text="Operand 2 (0-255):", font=label_font, bg="#87CEEB", fg=text_color)
op2_label.grid(row=1, column=0, padx=10, pady=10, sticky="e")
op2_entry = tk.Entry(root, font=entry_font)
op2_entry.grid(row=1, column=1, padx=10, pady=10, sticky="w")

# Operation input (dropdown)
operation_label = tk.Label(root, text="Operation (+ or -):", font=label_font, bg="#87CEEB", fg=text_color)
operation_label.grid(row=2, column=0, padx=10, pady=10, sticky="e")
operation_var = tk.StringVar(value="+")
operation_dropdown = tk.OptionMenu(root, operation_var, "+", "-")
operation_dropdown.grid(row=2, column=1, padx=10, pady=10, sticky="w")

# Delay input (dropdown)
delay_label = tk.Label(root, text="Delay (seconds):", font=label_font, bg="#87CEEB", fg=text_color)
delay_label.grid(row=3, column=0, padx=10, pady=10, sticky="e")
delay_var = tk.StringVar(value="1")
delay_dropdown = tk.OptionMenu(root, delay_var, "1", "2", "3", "4", "5")
delay_dropdown.grid(row=3, column=1, padx=10, pady=10, sticky="w")

# Start Button
start_button = tk.Button(root, text="Start Simulation", font=label_font, command=start_simulation)
start_button.grid(row=4, column=0, columnspan=2, pady=10)

# Output Text Box (for simulation progress)
output_label = tk.Label(root, text="Simulation Output:", font=label_font, bg="#87CEEB", fg=text_color)
output_label.grid(row=5, column=0, padx=10, pady=10, sticky="w")
output_text = tk.Text(root, height=15, font=text_font, fg=text_color, bg="black", wrap=tk.WORD)
output_text.grid(row=6, column=0, columnspan=2, padx=10, pady=10, sticky="nsew")

# Refresh Button (to clear and reload log)
refresh_button = tk.Button(root, text="Refresh Log", font=label_font, command=refresh_log)
refresh_button.grid(row=7, column=0, columnspan=2, pady=10)

# Signal indicators for RAM and Registers
ram_write_label = tk.Label(root, text="RAM Write", bg="gray", width=15, height=2, font=label_font)
ram_write_label.grid(row=8, column=0, padx=10, pady=10)

ram_read_label = tk.Label(root, text="RAM Read", bg="gray", width=15, height=2, font=label_font)
ram_read_label.grid(row=8, column=1, padx=10, pady=10)

ir_label = tk.Label(root, text="IR", bg="gray", width=15, height=2, font=label_font)
ir_label.grid(row=9, column=0, padx=10, pady=10)

ac_label = tk.Label(root, text="AC", bg="gray", width=15, height=2, font=label_font)
ac_label.grid(row=9, column=1, padx=10, pady=10)

# Bind the Enter key to start the simulation
root.bind("<Return>", start_simulation)

# Start the Tkinter event loop
root.mainloop()
