from cs50 import SQL

# open sqlite DB
db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")
row = db.execute("SELECT COUNT(*) as number FROM favorites WHERE language = ?", favorite)
row = row[0]

print(row["number"])
