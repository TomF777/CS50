import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get user's current cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # get user's shares
    shares_balance = db.execute("SELECT share_symbol, SUM(shares) as total_shares \
                                 FROM users, purchases \
                                 WHERE users.id = purchases.user_id AND purchases.user_id = ? \
                                 GROUP BY share_symbol HAVING total_shares>0 ", session["user_id"])

    # user's total cash balance
    grand_total = 0

    for share in shares_balance:
        symbol_quote = lookup(share['share_symbol'])
        share["name"] = symbol_quote["name"]
        share["price"] = symbol_quote["price"]
        share["shares_value"] = round(share["price"] * share["total_shares"], 2)
        grand_total += share["shares_value"]

    return render_template("index.html", shares=shares_balance, grand_total=usd(grand_total), user_cash=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # lookup the stocks' price
        lookup_result = lookup(symbol)

        if not lookup_result:
            return apology("Invalid stock symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Shares number must be integer")


        price = lookup_result["price"]
        user_id = session["user_id"]

        # user's money balance
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # cost of shares to buy
        shares_cost = float(shares) * price

        if cash < shares_cost:
            return apology("You can't afford to buy shares")

        # store successful transaction as history into purchases database
        db.execute("""INSERT INTO purchases (user_id, share_name, share_symbol, shares, price)
                        VALUES (?, ?, ?, ?, ?)""",
                   session["user_id"],
                   lookup_result["name"],
                   lookup_result["symbol"],
                   int(shares),
                   lookup_result["price"]
                   )

        # update user's money balance into users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash-shares_cost, session["user_id"])

        # put info on top of the screen
        flash(f"{shares} shares of {lookup_result["name"]}({lookup_result["symbol"]}) bought")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT share_symbol, share_name,  (CASE WHEN shares > 0 THEN 'B' ELSE 'S' END) AS 'transaction', shares, price, timestamp  \
                                FROM users, purchases \
                                WHERE users.id = purchases.user_id AND purchases.user_id = ? \
                                ", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        name = request.form.get("symbol")
        lookup_result = lookup(name)

        if lookup_result is not None:
            return render_template("quoted.html", **lookup_result)
        else:
            return apology("Invalid stock symbol")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # invalid input handling
        if not name or not password or not confirmation:
            return apology("some field is blank")

        if password != confirmation:
            return apology("password and confirmation are not the same")

        # query all usernames from DB
        users = db.execute("SELECT username FROM users")

        # check if username already exists
        for user in users:
            if name == user["username"]:
                return apology("Username already taken")

        # hash the password. This hides the plain text from password
        hash = generate_password_hash(password)

        # insert new user into DB
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, hash)

        # update current session user id
        session["user_id"] = user_id
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/change_pass", methods=["GET", "POST"])
def change_pass():
    """Change user's password"""
    
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        old_pass = request.form.get("old_password")
        new_pass = request.form.get("new_password")
        confirmation = request.form.get("confirmation")
        
        # invalid input handling
        if new_pass != confirmation:
            return apology("password and confirmation not the same")
        
        print(f"{old_pass}  {new_pass}  {confirmation}")
        
        # Query database for current password of the user
        current_pass = db.execute(
            "SELECT hash FROM users WHERE id = ?", session["user_id"]
        )[0]["hash"]
        
        # new and old password the same
        if check_password_hash(current_pass, new_pass):
             return apology("new password the same as old one. Choose different")
        
        # update the new password in the DB
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_pass), session["user_id"]) 
        flash(f"Password Changed")
        
        return redirect("/")
        
    else:
        return render_template("change_pass.html")


@app.route("/add_cash", methods=["GET", "POST"])
def add_cash():
    """Add extra cash to user's account"""
    
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        try:
            extra_cash = float(request.form.get("cash"))
        except ValueError:
            return apology("Only number allowed")
        
        if float(extra_cash) <= 0:
            return apology("You can only ad positive amount of cash")
        
        # user's money balance
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        
        # update the new password in the DB
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + float(extra_cash), session["user_id"]) 
        flash(f"Extra cash of {extra_cash}$ added")
        
        return redirect("/")
        
    else:
        return render_template("add_cash.html")
        
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        # get share sumbol to sell
        symbol = request.form.get("symbol")

        # get amount of shares to sell
        shares_to_sell = int(request.form.get("shares"))

        # get total number of shares with given symbol which user owns
        shares_total = db.execute("SELECT SUM(shares) as total_shares \
                             FROM users, purchases \
                             WHERE users.id = purchases.user_id AND purchases.user_id = ? \
                             AND purchases.share_symbol = ? \
                             GROUP BY share_symbol", session["user_id"], symbol
                                  )[0]["total_shares"]

        # invalid input handling
        if not symbol:
            return apology("No share symbol selected")
        elif int(shares_to_sell) <= 0:
            return apology("Share's amount must be positive integer number")
        elif int(shares_to_sell) > shares_total:
            return apology("You don't have so many shares")

        # get price of the share
        price = lookup(symbol)["price"]
        share_name = lookup(symbol)["name"]

        # insert the sold shares with negative amount number into database as transaction history
        db.execute("INSERT INTO purchases (user_id, share_name, share_symbol, shares, price) \
                    VALUES (?, ?, ?, ?, ?)", session["user_id"], share_name, symbol, -shares_to_sell, price)

        # get user's cash balance
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # update user's money balance into users table after successful transaction
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   cash+(shares_to_sell*price), session["user_id"])

        # put info on top of the screen
        flash(f"{shares_to_sell} of {share_name}({symbol}) shares sold")
        return redirect("/")

    # Execute when GET request

    # get user's shares
    shares_balance = db.execute("SELECT DISTINCT share_symbol \
                                 FROM users, purchases \
                                 WHERE users.id = purchases.user_id AND purchases.user_id = ? \
                                 ", session["user_id"])

    symbols = []

    # populate list with share's symbols which the user owns
    for symbol in shares_balance:
        symbols.append(symbol['share_symbol'])

    return render_template("sell.html", symbols=symbols)
