while True:
    h = input("Height: ")
    if not h.isdigit():
        continue
    h = int(h)
    if 0 < h < 9:
        break
for i in range(h):
    print(" "*(h-i-1) + "#" * (i+1)+"  "+"#" * (i+1))
