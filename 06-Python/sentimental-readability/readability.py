text = input("Text: ")

sent_num = len(text.split(".")) + len(text.split("!")) + len(text.split("?")) - 3
word_num = len(text.split(" "))
char_num = 0
for c in text:
    if c.isalpha():
        char_num += 1
L = 100*char_num/word_num
S = 100*sent_num/word_num

index = 0.0588 * L - 0.296 * S - 15.8
index = round(index)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
