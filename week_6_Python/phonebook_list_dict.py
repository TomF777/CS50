people = [
        {"name": "Yulia", "number": "999111333"},
        {"name": "David", "number": "2226781234"},
        {"name": "John", "number": "+1-555-222"}
]

name = input("Name: ")
for person in people:
    if person["name"] == name:
        number = person["number"]
        print(f"Found {number}")
        break
else:
    print("Not found")
