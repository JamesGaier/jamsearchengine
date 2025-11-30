from flask import Flask, request, jsonify, g, render_template
import sqlite3
from dotenv import load_dotenv
import os, sys
import signal

load_dotenv()
app = Flask(__name__)
db = None
CLIENT_ERROR_CODE = 404

def signal_handler(sig, frame):
    print("SIGTERM was sent")
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)

def get_db():
    # TODO: Make the DB configurable not hardcoded
    db_path = "/app/data/links.db3"
    if db_path == None:
        return None
    
    db = sqlite3.connect(db_path, uri=True)
    return db

@app.teardown_appcontext
def close_connection(exception):
    if db is not None:
        db.close()


@app.route("/")
def render_site():
    return render_template("index.html")

@app.route("/search", methods=["POST"])
def search():
    rawSearch = request.form["search-bar"]

    if rawSearch == "":
        return render_template("index.html", results=["Search empty"])

    results = []
    try:
        search = f"%{rawSearch}%"
        query = "SELECT * FROM urls WHERE url LIKE ?"
        cur = get_db()
        results = cur.execute(query, [search])
        results = results.fetchall()
        cur.close()
    except Exception as ex:
        print(ex)
        return render_template("index.html", results=["No search results found"])


    if len (results) == 0:
        return render_template("index.html", results=["No search results found"])

    results = [link[1] for link in results]

    return render_template("index.html", results=results)
 