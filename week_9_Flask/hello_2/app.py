# Uses request.args.get to get request parameter

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    # needs /?key=value e.g. /?name=Tom at the end of url address
    name = request.args.get("name", default="Flask")
    return render_template("index.html", name=name)
