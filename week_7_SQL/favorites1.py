import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)

    # display all data from column 'language'
    # for row in reader:
    #     print(row["language"])

    scratch, c, python = 0, 0, 0

    for row in reader:
        favorite = row["language"]
        if favorite == "Scratch":
            scratch += 1
        elif favorite == "C":
            c += 1
        elif favorite == "Python":
            python += 1

print(f"Scratch: {scratch}, C:{c}, Python: {python}")



