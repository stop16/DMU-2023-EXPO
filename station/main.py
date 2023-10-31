from http import HTTPStatus
from flask import Flask, jsonify, redirect, render_template, request, url_for
import json

app = Flask(__name__)

frontend_info = {
    "Drone_battery_level": 100,
    "Drone_status":"이륙 준비 완료",
    "Cargo_status": "탑재됨",
    "AGV_status":"대기중",
    "AGV_battery_level": 100,
    "AGV_estimated": "5km",
    "AGV_eta": "",
    "Station_status": "대기중",
    "Station_aruco": "#0 and #1",
    "Station_overhead_status": "닫힘",
    "Station_power_status": "양호",
    "Station_server_status": "정상"
}

origin_data = {
    'show_trigger': False,
    'overhead_status': True,
    'lift_status': False,
    'show_trigger_agv': False,
    'show_trigger_drone': False,
    'phase': 0
}

def find_difference(origin_data, json_data):
    result_data = origin_data
    data = json_data
    origin_data_keys = origin_data.keys()
    json_data_keys = data.keys()
    for i in origin_data_keys:
        for j in json_data_keys:
            if i == j:
                if result_data[i] != json_data[j]:
                    result_data[i] = json_data[j]
    return result_data

@app.route('/')
def main_page():
    return render_template('index.html')

@app.route('/manager', methods=['GET','POST'])
def manage_page():
    data = request.form.to_dict()
    print(data)
    return render_template('manage.html')

@app.route('/start')
def lets_start():
    global origin_data
    origin_data["show_trigger"] = True
    return "show started!"

@app.route('/get', methods=['GET'])
def get():
    return json.dumps(origin_data)


@app.route('/post', methods=['POST'])
def post():
    params = request.get_json()
    data = find_difference(origin_data, params)
    if data["phase"] == 5:
        print("finished!")
    return json.dumps(data)


if __name__ == '__main__':
    # app.run(host= '192.168.0.232', port=8080, debug=True)
    app.run(port=8080, debug=True)