import serial
import tkinter as tk


# Define word matrices
word_matrix_1 = [
    ['i', 'Am / to be', 'pass', 'yes', 'no'],
    ['you', 'do', 'want', 'please', 'thanks'],
    ['me', 'like', 'have', 'feel', 'not']
]

word_matrix_2 = [
    ['hope', 'excited', 'time', 'Too /also', 'the'],
    ['exam', 'nervous', 'present', 'what', '(plural)'],
    ['difficult', 'past', 'future', '(possessive)', '?']
]

word_matrix_3 = [
    ['school', 'ready', 'study', 'after', 'relax'],
    ['together', 'Engineering Interactive Technologies', 'grab', 'before', 'A lot'],
    ['fail', 'hate', 'beer', 'until', 'but']
]

# Open serial port
serial_port = 'COM4'
baud_rate = 9600

serial_inst = serial.Serial(serial_port, baud_rate)
serial_inst.flushInput()

def add_word():
    word = entry.get()
    if word: 
        selected_words.insert(tk.END, word + "\n")  
        entry.delete(0, tk.END)

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

        # root = tk.Tk()
        # root.title("Selected Words")

        # # Entry widget to input words
        # entry = tk.Entry(root, width=30)
        # entry.pack()

        # # Button to add words
        # add_button = tk.Button(root, text="Add Word", command=add_word)
        # add_button.pack()

        # # Text widget to display selected words
        # selected_words = tk.Text(root, height=10, width=30)
        # selected_words.pack()

        # root.mainloop()
