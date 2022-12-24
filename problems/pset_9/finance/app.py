import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime, timezone

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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

    portfolio = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])

    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash_db[0]["cash"]

    total = cash

    total_shares = 0

    for row in portfolio:
        quote = lookup(row["symbol"])
        row["per_symbol_share_value"] = quote["price"]
        row["symbol_totalShares_value"] = (row["per_symbol_share_value"] * row["shares"])
        total_shares += row["symbol_totalShares_value"]

    total = total + total_shares

    return render_template("index.html", database=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get Variables
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        shares = request.form.get("shares")

        # Symbol Validation
        if not symbol:
            return apology("You must provide a symbol.")

        # Stock Validation
        if not stock:
            return apology("Stock doesn't exists")

        # Shares Validation
        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive Integer.")

        if shares < 0:
            return apology("Negative Share not allowed.")

        # Calculate Price
        price = shares * stock["price"]
        cash = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])[0]["cash"]
        remain = cash - price

        # Shares Value with User Cash
        if cash < price:
            return apology("Insufficient Money.")

        # Update
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?,?,?,?,?)",
                   session["user_id"], stock["symbol"], shares, stock["price"], datetime.now())

        flash("Bought.")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
        # Save Data as Variables
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        # Symbol Validation
        if not symbol:
            return apology("You must provide a symbol.")

        # Stock Validation
        if not stock:
            return apology("Stock doesn't exists.")

        # Return Quoted Template
        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Save Data as Variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if Username is not Empty
        if not username:
            return apology("You must provide an username.")

        # Check if Password is not Empty
        if not password:
            return apology("You must provide a password.")

        # Check if Confirmation is not Empty
        if not confirmation:
            return apology("You must confirm your password.")

        # Check if Username already exists
        if len(db.execute("SELECT * FROM users WHERE username = ?", username)) == 1:
            return apology("Username already exists.")

        # Check if Passwords Matches
        if confirmation != password:
            return apology("Passwords don't match.")

        # Validate Password Length
        if len(password) < 8:
            return apology("Your password must contain 8 or more characters.")

        # Update DB
        db.execute("INSERT INTO users(username, hash) VALUES (?,?)", username, generate_password_hash(password))

        # Login User
        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        flash("You are now registered.")
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
 # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get Variables
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        shares = request.form.get("shares")

        # Symbol Validation
        if not symbol:
            return apology("You must provide a symbol.")

        # Stock Validation
        if not stock:
            return apology("Stock doesn't exists")

       # Shares Validation
        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive Integer.")

        if shares < 0:
            return apology("Negative Share not allowed.")

        ownshares = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE user_id= ? AND symbol = ?",
                               session["user_id"], symbol)[0]["shares"]

        if shares > ownshares:
            return apology("Not enough share in your Portfolio.")

        # Calculate Price
        price = shares * stock["price"]
        cash = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])[0]["cash"]
        remain = cash + price

        # Update
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?,?,?,?,?)",
                   session["user_id"], stock["symbol"], -shares, stock["price"], datetime.now())

        flash("Bought.")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols])
