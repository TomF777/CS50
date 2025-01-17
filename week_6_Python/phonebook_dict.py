people = {
            "Yulia": "999111333",
            "David": "2226781234",
            "John": "+1-555-222"
}

name  = input("Name: ")
if name in people:
    print(f"Number: {people[name]}")
else:
    print("Not found")

