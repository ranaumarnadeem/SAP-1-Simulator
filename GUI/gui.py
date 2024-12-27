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
# Set up the main window
root = tk.Tk()
root.title("SAP-1 Simulator")
root.configure(bg="#808080")  # Changed to gray background

# Configure grid weights for left and right sections
root.rowconfigure(list(range(12)), weight=1)
root.columnconfigure(0, weight=1)  # Left side
root.columnconfigure(1, weight=2)  # Right side (larger for output)

# Create frames for left and right sections
left_frame = tk.Frame(root, bg="#808080")
left_frame.grid(row=0, column=0, sticky="nsew", padx=10, pady=10)
right_frame = tk.Frame(root, bg="#808080")
right_frame.grid(row=0, column=1, sticky="nsew", padx=10, pady=10)

# Styling variables
label_font = ("Arial", 12, "bold")
entry_font = ("Arial", 12)
text_font = ("Courier", 12)
text_color = "black"  # Changed to black for better visibility on gray

# Left side - Input controls
# Operand 1 input
op1_label = tk.Label(left_frame, text="Operand 1 (0-255):", font=label_font, bg="#808080", fg=text_color)
op1_label.pack(pady=5, anchor="w")
op1_entry = tk.Entry(left_frame, font=entry_font)
op1_entry.pack(pady=5, fill="x")

# Operand 2 input
op2_label = tk.Label(left_frame, text="Operand 2 (0-255):", font=label_font, bg="#808080", fg=text_color)
op2_label.pack(pady=5, anchor="w")
op2_entry = tk.Entry(left_frame, font=entry_font)
op2_entry.pack(pady=5, fill="x")

# Operation input
operation_label = tk.Label(left_frame, text="Operation (+ or -):", font=label_font, bg="#808080", fg=text_color)
operation_label.pack(pady=5, anchor="w")
operation_var = tk.StringVar(value="+")
operation_dropdown = tk.OptionMenu(left_frame, operation_var, "+", "-")
operation_dropdown.pack(pady=5, fill="x")

# Delay input
delay_label = tk.Label(left_frame, text="Delay (seconds):", font=label_font, bg="#808080", fg=text_color)
delay_label.pack(pady=5, anchor="w")
delay_var = tk.StringVar(value="1")
delay_dropdown = tk.OptionMenu(left_frame, delay_var, "1", "2", "3", "4", "5")
delay_dropdown.pack(pady=5, fill="x")

# Start Button
start_button = tk.Button(left_frame, text="Start Simulation", font=label_font, command=start_simulation)
start_button.pack(pady=10)

# Signal indicators frame
signals_frame = tk.Frame(left_frame, bg="#808080")
signals_frame.pack(pady=10, fill="x")

# Signal indicators for RAM and Registers
ram_write_label = tk.Label(signals_frame, text="RAM Write", bg="gray", width=15, height=2, font=label_font)
ram_write_label.pack(pady=5)

ram_read_label = tk.Label(signals_frame, text="RAM Read", bg="gray", width=15, height=2, font=label_font)
ram_read_label.pack(pady=5)

ir_label = tk.Label(signals_frame, text="IR", bg="gray", width=15, height=2, font=label_font)
ir_label.pack(pady=5)

ac_label = tk.Label(signals_frame, text="AC", bg="gray", width=15, height=2, font=label_font)
ac_label.pack(pady=5)

# Right side - Output terminal
output_label = tk.Label(right_frame, text="Simulation Output:", font=label_font, bg="#808080", fg=text_color)
output_label.pack(pady=5, anchor="w")

output_text = tk.Text(right_frame, height=30, font=text_font, fg="white", bg="black", wrap=tk.WORD)
output_text.pack(pady=5, fill="both", expand=True)

# Refresh Button
refresh_button = tk.Button(right_frame, text="Refresh Log", font=label_font, command=refresh_log)
refresh_button.pack(pady=10)

# Bind the Enter key to start the simulation
root.bind("<Return>", start_simulation)

# Start the Tkinter event loop
root.mainloop()