import requests, json, threading, datetime, nuritello

url = 'http://192.168.0.232:8080/'

def precision_land():
    now = datetime.datetime.now()
    print(now.strftime('%H:%M:%S.%f')[:-3],"try land after takeoff")
    nuritello.precision_landing()

show_trigger_drone = False
def receive_from_server():
    t = threading.Timer(1, receive_from_server)
    t.start()
    global show_trigger_drone
    response = requests.get(url+'get')
    json_data = response.json()
    #print('origin:',json_data)
    if json_data["show_trigger"] == True and json_data["phase"] == 0:
        precision_land()
        show_trigger_drone = True
        json_data["phase"] = 1
    json_data["show_trigger_drone"] = show_trigger_drone
    #print('current:',json_data)
    header = {
        'Content-type': 'application/json'
    }
    requests.post(url+'post', data=json.dumps(json_data), headers = header) # 정보 전달

if __name__ == '__main__':
    receive_from_server()