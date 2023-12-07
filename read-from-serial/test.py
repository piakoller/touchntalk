import serial
import tkinter as tk

# Define word matrices
word_matrix_1 = [
    ['i', 'Am / to be', 'pass', 'yes', 'no'],
    ['you', 'do', 'want', 'please', 'thanks'],
    ['me', 'like', 'have', 'feel', 'not']
]

word_matrix_3 = [
    ['hope', 'excited', 'time', 'Too /also', 'the'],
    ['exam', 'nervous', 'present', 'what', '(plural)'],
    ['difficult', 'past', 'future', '(possessive)', '?']
]

word_matrix_2 = [
    ['school', 'ready', 'study', 'after', 'relax'],
    ['together', 'Engineering Interactive Technologies', 'grab', 'before', 'A lot'],
    ['fail', 'hate', 'beer', 'until', 'but']
]

# Open serial port
serial_port = 'COM4'
baud_rate = 9600

serial_inst = serial.Serial(serial_port, baud_rate)
serial_inst.flushInput()

root = tk.Tk()
# specify size of window.
root.geometry("250x170")

# Create text widget and specify size.
T = tk.Text(root, height=5, width=52)

# Create label
l = tk.Label(root, text="Selected Words")
l.config(font=("Courier", 14))

l.pack()
T.pack()

def update_selected_words(word):
    T.insert(tk.END, word + "\n")

while True:
    if serial_inst.in_waiting > 0:
        # Read line from serial
        input_from_arduino = serial_inst.readline().decode().strip()

        # Extract paper number, row, and column from input string
        input_values = input_from_arduino[1:-1].split(';')
        paper_number = int(input_values[0])
        row, column = map(int, input_values[1].split(','))

        # Choose the appropriate word matrix based on the paper number
        if paper_number == 1:
            word_matrix = word_matrix_1
        elif paper_number == 2:
            word_matrix = word_matrix_2
        elif paper_number == 3:
            word_matrix = word_matrix_3
        else:
            print("Invalid paper number")
            continue

        # Retrieve the word from the selected matrix
        selected_word = word_matrix[row][column]

        # Print the selected word
        print(f"The selected word is: {selected_word}")

        # Insert the selected word in the Tkinter window
        update_selected_words(selected_word)

    root.update_idletasks()  # Update Tkinter window

    root.mainloop()  # Start the Tkinter main loop
