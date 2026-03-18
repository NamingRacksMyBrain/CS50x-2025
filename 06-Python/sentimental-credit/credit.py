def main():
    number = input("Number: ")
    length = len(number)
    num_list = list(map(int, number))

    if length == 15 and Amex(num_list):
        if Luhn(length, num_list):
            print("AMEX")
        else:
            print("INVALID")

    elif length == 16 and Master(num_list):
        if Luhn(length, num_list):
            print("MASTERCARD")
        else:
            print("INVALID")

    elif (length == 13 or length == 16) and Visa(num_list):
        if Luhn(length, num_list):
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")


def Amex(num_list):
    if num_list[0] == 3 and (num_list[1] == 4 or num_list[1] == 7):
        return True
    else:
        return False


def Master(num_list):
    if num_list[0] == 5 and (num_list[1] == 1 or num_list[1] == 2 or num_list[1] == 3 or num_list[1] == 4 or num_list[1] == 5):
        return True
    else:
        return False


def Visa(num_list):
    if num_list[0] == 4:
        return True
    else:
        return False


def Luhn(length, num_list):
    sum = 0
    for i in range(length % 2, length, 2):
        p = num_list[i]*2
        sum += p % 10 + p//10
    for j in range((length-1) % 2, length, 2):
        sum += num_list[j]
    if sum % 10 == 0:
        return True
    else:
        return False


main()
