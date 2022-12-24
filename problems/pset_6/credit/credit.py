import sys


def main():

    valid = False

    while not valid:
        try:
            # Get User Input
            card = int(input('Enter an integer: '))
            valid = True
        except ValueError:
            # Input is not an INT
            print('Please only input digits')

    # Print Card Brand or Invalid with Conditions
    if validation(str(card)):
        if str(card)[0] == str(4):
            print("VISA")
        elif str(card)[:2] in {'34', '37'}:
            print("AMEX")
        elif str(card)[:2] in {'51', '52', '53', '54', '55'}:
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def validation(card):
    # Modified Luhn Algorithm from geeksforgeeks
    cardLength = len(card)

    # Invalid Length
    if cardLength < 13 or cardLength > 16:
        return False

    nSum = 0
    isSecond = False

    for i in range(cardLength - 1, -1, -1):
        d = ord(card[i]) - ord('0')

        if (isSecond == True):
            d = d * 2

        nSum += d // 10
        nSum += d % 10

        isSecond = not isSecond

    if (nSum % 10 == 0):
        return True
    else:
        return False


main()