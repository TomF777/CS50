# Return a string of text

from flask import Flask, render_template

app = Flask(__name__)


@app.route("/")
def index():
    return "hello flask"
