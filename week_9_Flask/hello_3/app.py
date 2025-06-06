# Uses form to post data and request.args.get to get request parameter

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet", methods=["GET"])
def greet():
    name = request.args.get("name", default="flask")
    return render_template("greet.html", name=name)
