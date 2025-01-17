import csv

name = input("Name: ")
number = input("Number:")

with open("phonebook.csv", "a") as file:
    # save data as list into csv file
    writer = csv.writer(file)
    writer.writerow([name, number, "text"])

    # save data as dict into csv file
    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow({"name": name, "number": number})


