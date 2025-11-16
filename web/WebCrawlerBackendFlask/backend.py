from flask import Flask, request, jsonify, g
from flask_cors import CORS, cross_origin
import sqlite3
from dotenv import load_dotenv
import os, sys
import signal

load_dotenv()
app = Flask(__name__)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'
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

@app.route("/search")
@cross_origin()
def search():
    rawSearch = request.args.get('q')

    if rawSearch == "":
        return {"Result": "Search empty"}, CLIENT_ERROR_CODE

    search = f"%{rawSearch}%"
    query = "SELECT * FROM urls WHERE url LIKE ?"
    cur = get_db()
    results = cur.execute(query, [search])
    results = results.fetchall()
    cur.close()


    if len (results) == 0:
        return {"Result": "No search results found"}, CLIENT_ERROR_CODE

    results = [link[1] for link in results]

    toRet = {
        "Result": results
    }

    return jsonify(toRet)
 