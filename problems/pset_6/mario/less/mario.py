from cs50 import get_int


def main():
    # Get Height
    height = get_int("Height: ")
    if height > 0 and height < 9:
        for i in range(height):

            # Get Number of Hashes
            hash = i + 1
            hash_string = "#" * hash

            # Get Number of Spaces
            space = abs(i + 1 - height)
            space_string = " " * space

            # Print
            print(space_string+hash_string)

    else:
        # Run main Again if height is incorrect
        main()


main()