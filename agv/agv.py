import requests, json, threading, datetime, nuriserial

url = 'http://192.168.0.232:8080/'

lift_pos = 0
# functions
def goto_station():
    now = datetime.datetime.now()
    print(now.strftime('%H:%M:%S.%f')[:-3],'AGV moved into station')
    nuriserial.val_macro('a')

def move_lift(pos):
    global lift_pos
    now = datetime.datetime.now()
    if pos == 0 and lift_pos != 0:
        print(now.strftime('%H:%M:%S.%f')[:-3],"lift moved down")
        nuriserial.val_macro('b')
        lift_pos = 0
    if pos == 1 and lift_pos != 1:
        print(now.strftime('%H:%M:%S.%f')[:-3],"lift moved up")
        nuriserial.val_macro('c')
        lift_pos = 1

show_trigger_agv = False
lift_status = False
def receive_from_server():
    t = threading.Timer(1, receive_from_server)
    t.start()
    global show_trigger_agv, lift_status
    response = requests.get(url+'get')
    json_data = response.json()
    #print('origin:',json_data)
    if json_data["show_trigger_drone"] == True and json_data["phase"] == 1:
        goto_station()
        show_trigger_agv = True
        json_data["phase"] = 2
    if json_data["overhead_status"] == False  and json_data["phase"] == 3:
        move_lift(1)
        lift_status = True
        json_data["phase"] = 4
    json_data["show_trigger_agv"] = show_trigger_agv
    json_data["lift_status"] = lift_status
    #print('current:',json_data)
    header = {
        'Content-type': 'application/json'
    }
    requests.post(url+'post', data=json.dumps(json_data), headers = header) # 정보 전달

if __name__ == '__main__':
    receive_from_server()