import tkinter as tk
from tkinter import messagebox, ttk
from subprocess import Popen, PIPE
import datetime

class SAP1Simulator:
    def __init__(self, root):
        self.root = root
        self.root.title("SAP-1 Simulator")
        self.root.configure(bg="#808080")
        
        
        self.root.minsize(1000, 700)
        
        
        self.root.rowconfigure(0, weight=20)  # Main content
        self.root.rowconfigure(1, weight=1)   # Footer
        self.root.columnconfigure(0, weight=1)
        self.root.columnconfigure(1, weight=2)

        
        self.create_left_frame()
        self.create_right_frame()
        self.create_footer()
        
        # Initialize variables
        self.operation_var = tk.StringVar(value="+")
        self.delay_var = tk.StringVar(value="1")
        
        # Populate frames
        self.setup_input_section()
        self.setup_output_section()
        self.setup_status_bar()
        
        
        self.setup_keyboard_shortcuts()

    def run_simulation(self, op1, op2, op):
        try:
            # Run core.cpp
            process = Popen(["../Core/core", str(op1), str(op2), op], stdout=PIPE, stderr=PIPE)
            stdout, stderr = process.communicate()
            return stdout.decode(), stderr.decode()
        except FileNotFoundError:
            return "", "Error: Executable not found. Ensure 'core' is in the same directory."
        except Exception as e:
            return "", f"An unexpected error occurred: {str(e)}"

    def start_simulation(self, event=None):
        try:
            # Get input values
            op1_input = self.op1_entry.get()
            op2_input = self.op2_entry.get()
            op = self.operation_var.get()

            # Check if operands are numeric and within the valid range (0-255)
            if not (op1_input.isdigit() and op2_input.isdigit()):
                raise ValueError("Operands must be numeric values.")
            
            op1 = int(op1_input)
            op2 = int(op2_input)

            if not (0 <= op1 <= 255 and 0 <= op2 <= 255):
                raise ValueError("Operands must be between 0 and 255.")

            # Run the simulation and get the output
            stdout, stderr = self.run_simulation(op1, op2, op)

            if stderr:
                messagebox.showerror("Error", f"Error occurred: {stderr}")
            else:
                
                self.display_simulation_progress(stdout)

        except ValueError as e:
            messagebox.showerror("Input Error", str(e))

    def display_simulation_progress(self, output):
        self.output_text.delete(1.0, tk.END)  # Clear previous text
        delay_time = int(self.delay_var.get()) * 1000  # Delay

        # Step 1: Data written to RAM
        self.update_log("Writing data to RAM...\n")
        self.toggle_signal("RAM Write", "green", delay_time)
        self.root.after(delay_time, lambda: self.update_log("Data successfully written to RAM.\n"))

        # Step 2: Data read from RAM
        self.root.after(2 * delay_time, lambda: self.toggle_signal("RAM Read", "red", delay_time))
        self.root.after(2 * delay_time, lambda: self.update_log("Reading data from RAM...\n"))
        self.root.after(3 * delay_time, lambda: self.update_log("Data successfully read from RAM.\n"))

        # Step 3: Instruction Register active
        self.root.after(4 * delay_time, lambda: self.toggle_signal("IR", "blue", delay_time))
        self.root.after(4 * delay_time, lambda: self.update_log("Instruction loaded into IR...\n"))

        # Step 4: Accumulator active
        self.root.after(5 * delay_time, lambda: self.toggle_signal("AC", "yellow", delay_time))
        self.root.after(5 * delay_time, lambda: self.update_log("Result stored in Accumulator.\n"))

        # Final Step: Display program output
        self.root.after(6 * delay_time, lambda: self.update_log(f"Program Output:\n{output}"))

    def toggle_signal(self, signal_name, color, delay):
        self.signals[signal_name].config(fg=color)
        self.root.after(delay, lambda: self.signals[signal_name].config(fg="gray"))

    def update_log(self, message):
        self.output_text.insert(tk.END, message)
        self.output_text.see(tk.END)  # Auto-scroll 
        self.update_status("Processing simulation...")

    def create_left_frame(self):
        self.left_frame = tk.Frame(self.root, bg="#808080", relief="ridge", bd=2)
        self.left_frame.grid(row=0, column=0, sticky="nsew", padx=10, pady=10)

    def create_right_frame(self):
        self.right_frame = tk.Frame(self.root, bg="#808080", relief="ridge", bd=2)
        self.right_frame.grid(row=0, column=1, sticky="nsew", padx=10, pady=10)

    def create_footer(self):
        footer_frame = tk.Frame(self.root, bg="#4a4a4a", height=30)
        footer_frame.grid(row=1, column=0, columnspan=2, sticky="ew")
        footer_frame.grid_propagate(False)

        # Credits
        credits_text = "Created by: Rana Umar Nadeem & Muhammad Asad Naseem"
        credits_label = tk.Label(footer_frame, text=credits_text, 
                               bg="#4a4a4a", fg="white", 
                               font=("Arial", 10))
        credits_label.pack(side="left", padx=10)

        # Version and date
        version_text = f"Version 1.0 | {datetime.datetime.now().strftime('%Y')}"
        version_label = tk.Label(footer_frame, text=version_text,
                               bg="#4a4a4a", fg="white",
                               font=("Arial", 10))
        version_label.pack(side="right", padx=10)

    def setup_input_section(self):
        # Title for input section
        title = tk.Label(self.left_frame, text="SAP-1 Control Panel",
                        font=("Arial", 14, "bold"),
                        bg="#808080", fg="#000000")
        title.pack(pady=10)

        
        input_frame = tk.Frame(self.left_frame, bg="#909090", relief="raised", bd=2)
        input_frame.pack(padx=10, pady=5, fill="x")

        # Operand inputs with validation
        self.create_validated_entry(input_frame, "Operand 1 (0-255):", "op1_entry")
        self.create_validated_entry(input_frame, "Operand 2 (0-255):", "op2_entry")

        # Operation dropdown 
        tk.Label(input_frame, text="Operation:", 
                font=("Arial", 12, "bold"), 
                bg="#909090").pack(pady=5, anchor="w")
        operation_menu = ttk.OptionMenu(input_frame, self.operation_var, "+", "+", "-")
        operation_menu.pack(pady=5, fill="x")

        # Delay selection 
        tk.Label(input_frame, text="Delay (seconds):", 
                font=("Arial", 12, "bold"), 
                bg="#909090").pack(pady=5, anchor="w")
        delay_menu = ttk.OptionMenu(input_frame, self.delay_var, "1", "1", "2", "3", "4", "5")
        delay_menu.pack(pady=5, fill="x")

        # Start button with hover effect
        start_button = tk.Button(input_frame, text="Start Simulation",
                               font=("Arial", 12, "bold"),
                               bg="#4CAF50", fg="white",
                               activebackground="#45a049",
                               command=self.start_simulation)
        start_button.pack(pady=10, fill="x")

        # Signal indicators 
        self.create_signal_indicators(input_frame)

    def create_validated_entry(self, parent, label_text, entry_name):
        tk.Label(parent, text=label_text,
                font=("Arial", 12, "bold"),
                bg="#909090").pack(pady=5, anchor="w")
        entry = ttk.Entry(parent, font=("Arial", 12))
        entry.pack(pady=5, fill="x")
        setattr(self, entry_name, entry)

        # Add validation
        vcmd = (self.root.register(self.validate_number), '%P')
        entry.config(validate='key', validatecommand=vcmd)

    def create_signal_indicators(self, parent):
        signals_frame = tk.LabelFrame(parent, text="System Status",
                                    bg="#909090",
                                    font=("Arial", 12, "bold"))
        signals_frame.pack(pady=10, fill="x")

        # Create signal indicators 
        self.signals = {}
        for name in ["RAM Write", "RAM Read", "IR", "AC"]:
            frame = tk.Frame(signals_frame, bg="#909090")
            frame.pack(fill="x", pady=2)
            
            label = tk.Label(frame, text=name,
                           font=("Arial", 10),
                           bg="#909090")
            label.pack(side="left", padx=5)
            
            indicator = tk.Label(frame, text="●",
                               font=("Arial", 16),
                               fg="gray",
                               bg="#909090")
            indicator.pack(side="right", padx=5)
            
            self.signals[name] = indicator

    def setup_output_section(self):
        # Title for output section
        title = tk.Label(self.right_frame, text="Simulation Output",
                        font=("Arial", 14, "bold"),
                        bg="#808080", fg="#000000")
        title.pack(pady=10)

        # Output text 
        self.output_text = tk.Text(self.right_frame,
                                 font=("Courier", 12),
                                 fg="white",
                                 bg="#1e1e1e",
                                 wrap=tk.WORD)
        self.output_text.pack(padx=10, pady=5, fill="both", expand=True)

        # Add scrollbar
        scrollbar = ttk.Scrollbar(self.right_frame, orient="vertical",
                                command=self.output_text.yview)
        scrollbar.pack(side="right", fill="y")
        self.output_text.configure(yscrollcommand=scrollbar.set)

        # Refresh button with hover effect
        refresh_button = tk.Button(self.right_frame, text="Clear Output",
                                 font=("Arial", 12),
                                 bg="#ff4444", fg="white",
                                 activebackground="#cc0000",
                                 command=self.refresh_log)
        refresh_button.pack(pady=10)

    def setup_status_bar(self):
        self.status_var = tk.StringVar()
        status_bar = tk.Label(self.root, textvariable=self.status_var,
                            bd=1, relief=tk.SUNKEN, anchor=tk.W)
        status_bar.grid(row=2, column=0, columnspan=2, sticky="ew")
        self.update_status("Ready")

    def setup_keyboard_shortcuts(self):
        self.root.bind("<Return>", self.start_simulation)
        self.root.bind("<Control-r>", lambda e: self.refresh_log())
        self.root.bind("<Escape>", lambda e: self.root.quit())

    def validate_number(self, value):
        if value == "":
            return True
        try:
            num = int(value)
            return 0 <= num <= 255
        except ValueError:
            return False

    def update_status(self, message):
        self.status_var.set(message)

    def refresh_log(self):
        self.output_text.delete(1.0, tk.END)
        self.update_status("Output cleared")

if __name__ == "__main__":
    root = tk.Tk()
    app = SAP1Simulator(root)
    root.mainloop()