from flask import Flask, render_template
import random
app = Flask(__name__)

@app.route("/")
def home():
    return render_template('index.html')

@app.get("/update")
def update():

    total = str(random.random()) ## replace this with what you want to send

    return total

if __name__ == "__main__":
    app.run(port=5012, debug=True)