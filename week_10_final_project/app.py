"""Real-time data analytics for sensor from industrial area"""

import time
import json
from random import random, uniform
import logging
from cs50 import SQL
from flask import Flask, render_template, request, make_response
import threading
from helpers import *

# algorithm's constants
MODEL_SIZE = 30
ANOMALY_LIST_SIZE = 30


logging.basicConfig(level=logging.DEBUG,
                    format="%(levelname)s:%(name)s:%(message)s")

app = Flask(__name__)

control_app = ControlCommand()

# initialize algorithm object for sensor
sensor_anomaly_algorithm = AnomalyDetectZscore(name="sensor1",
                                               model_size=MODEL_SIZE)

db = SQL("sqlite:///data.db")


def signal_generator():
    """Generate random data as simulation of sensor output"""
    loop_count = 0

    while True:
        time.sleep(0.5)
        # generate sensor data only when production line is running
        if control_app.run:
            # add artificial noise and outliers to the sensor signal
            sim_anomaly_level = float(control_app.sim_anomaly_level)

            random_offset = uniform(-5, 5)

            if sim_anomaly_level > 0:
                if loop_count % (11 - int(sim_anomaly_level)) == 0:
                    random_offset = 2 * sim_anomaly_level + \
                        uniform(-sim_anomaly_level, sim_anomaly_level)

            sensor_data = round(float(100 + random_offset), 2)

            sensor_anomaly_algorithm.z_score_thresh = float(control_app.z_score_thresh)
            sensor_anomaly_algorithm.check_if_anomaly(sensor_data)
            sensor_anomaly_algorithm.calculate_anomaly_ratio(anomaly_list_size=ANOMALY_LIST_SIZE)

            db.execute("""INSERT INTO SensorData (sensor_value, \
                                                  avg, \
                                                  anomaly, \
                                                  anomaly_ratio, \
                                                  z_score, \
                                                  z_score_thresh) VALUES (?, ?, ?, ?, ?, ?)""",
                       sensor_data,
                       sensor_anomaly_algorithm.model_avg,
                       sensor_anomaly_algorithm.anomaly,
                       sensor_anomaly_algorithm.anomaly_ratio,
                       sensor_anomaly_algorithm.z_score,
                       sensor_anomaly_algorithm.z_score_thresh)

        logging.debug(f"Thread control run status: {control_app.run}")


@app.route("/")
def index():
    """main route"""

    thread_number = 0

    # check if thread for 'signal_generator' already running
    for thread in threading.enumerate():
        if 'signal_generator' in thread.name:
            thread_number += 1

    if thread_number == 0:
        thread_signal_gen = threading.Thread(target=signal_generator)
        thread_signal_gen.daemon = True
        thread_signal_gen.start()

    return render_template("index.html")


@app.route("/get_data", methods=["GET"])
def data():
    """GET request from JavaScript client"""

    # if GET request method and animation production line is running
    # send data analytics to javscript client
    if control_app.run:
        data = {"time": time.time() * 1000, "value": round(random() * 100, 2)}

        sensor_data = db.execute("SELECT * FROM ( \
                                SELECT sensor_value, avg, anomaly, anomaly_ratio, z_score, z_score_thresh, timestamp \
                                FROM SensorData \
                                ORDER BY timestamp \
                                DESC LIMIT ?) as 'OutputData' \
                        ORDER BY 'OutputData'.timestamp ASC;", control_app.time_window)

        sensor_data.append({"model_completeness": sensor_anomaly_algorithm.model_completeness})
        response = send_response(sensor_data)
        return response

    data = {"stopped": "true"}
    response = make_response(json.dumps(data))
    return (response, 200)


@app.route("/send_control", methods=["POST"])
def send_data():
    """
    POST request from Javascript client
    with control commands(stored in control_app object)
    """

    if request.method == "POST":

        key = list(request.get_json().keys())[0]
        value = list(request.get_json().values())[0]

        if key == "zScoreThresh":
            control_app.z_score_thresh = value
        elif key == "anomalySimLevel":
            control_app.sim_anomaly_level = value
        elif key == "startStop":
            control_app.run = not control_app.run
            logging.info(f"app_run: {control_app.run}")
        elif key == "timeWindow":
            control_app.time_window = value * 60
            logging.info(f"time window: {control_app.time_window}")
        elif key == "reset":
            sensor_anomaly_algorithm.reset_algorithm()
            logging.info("reset algorithm")

        logging.info(f"{control_app.z_score_thresh}   {control_app.sim_anomaly_level}")

        return ('control sent successfully to the server', 200)


@app.route("/get_control", methods=["GET", "POST"])
def get_control():
    """send control commands to javascript client"""

    data = {"run": control_app.run,
            "z_score_thresh": control_app.z_score_thresh,
            "sim_anomaly_level": control_app.sim_anomaly_level,
            "time_window": control_app.time_window}

    response = send_response(data)
    return response


def send_response(data):
    """ make JSON POST response to the javascript client """

    response = make_response(json.dumps(data))
    # response.content_type = 'application/json'
    return response


if __name__ == '__main__':

    app.run(debug=False, use_reloader=False)
