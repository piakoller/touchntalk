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
baud_rate = 115200

serial_inst = serial.Serial(serial_port, baud_rate)
serial_inst.flushInput()

root = tk.Tk()

root.title("Selected Words")
root.geometry("1000x680")

# Text widget to display selected words
selected_words = tk.Text(root, height=1000, width=680, font=("Helvetica", 32))
selected_words.pack()

while True:
    if serial_inst.in_waiting > 0:
        # Read line from serial
        input_from_arduino = serial_inst.readline().decode().strip()
        print("Received from Arduino:", input_from_arduino)

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

        # Update the selected_words Text widget with the selected_word
        selected_words.insert(tk.END, selected_word + "\n")
        # Scroll the Text widget to the last added position
        selected_words.see(tk.END)
        root.update()

        # root.mainloop()
