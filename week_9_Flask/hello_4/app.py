# Uses layout for html and only one route for GET and POST

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name", "flask")
        return render_template("greet.html", name=name)
    else:
        return render_template("index.html")



