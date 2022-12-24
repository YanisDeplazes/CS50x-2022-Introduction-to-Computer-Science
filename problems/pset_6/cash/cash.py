# TODO

def getCents():
    while True:
        try:
            cents = float(input("Change owed:"))
        except ValueError:
            continue
        else:
            if cents > 0:
                return round(cents * 100)
                break
            continue


cents = getCents()

# Get Quarters
coins = cents // 25
cents = cents % 25

# Get Dimes
coins += cents // 10
cents = cents % 10

# Get Nickels
coins += cents // 5
cents = cents % 5

# Get Pennies
coins += cents // 1
cents = cents % 1

print(coins)