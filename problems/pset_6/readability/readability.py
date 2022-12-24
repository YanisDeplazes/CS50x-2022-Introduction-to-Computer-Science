from cs50 import get_string

# get text as a string
text = get_string("Text: ")


# Counting the number of words in a string returning the number of space-separated substrings.
word_list = text.split()
words = len(word_list)


# Counting the number of letters in a string with isalpha method
letters = 0
for i in text:
    if(i.isalpha()):
        letters += +1

# Counting the number of sentences in a string with count method
sentences = text.count('.') + text.count('!') + text.count('?')

# Coleman-Liau index
L = letters / words * 100
S = sentences / words * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

# Print
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")