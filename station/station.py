import requests, json, threading, nuriserial

url = 'http://192.168.0.232:8080/'

alignbar_pos = 0
overhead_pos = 0
# functions
def move_alignbar(pos):
    global alignbar_pos
    if pos == 0 and alignbar_pos != 0: # 기본 위치
        print("move alignbar pos #0")
        nuriserial.val_macro('a')
        alignbar_pos = 0
    if pos == 1 and alignbar_pos != 1: # 대기 위치
        print("move alignbar pos #1")
        nuriserial.val_macro('b')
        alignbar_pos = 1
    if pos == 2 and alignbar_pos != 2: # 화물 교환 위치
        print("move alignbar pos #2")
        nuriserial.val_macro('c')
        alignbar_pos = 2

def move_overhead(pos):
    global overhead_pos
    if pos == 0 and overhead_pos != 0: # 닫힌 상태
        print("overhead door closed")
        nuriserial.val_macro('d')
        overhead_pos = 0
    if pos == 1 and overhead_pos != 1: # 열린 상태
        print("overhead door opened")
        nuriserial.val_macro('e')
        overhead_pos = 1

overhead_status = True
def receive_from_server():
    t = threading.Timer(1, receive_from_server)
    t.start()
    global overhead_status
    response = requests.get(url+'get')
    json_data = response.json()
    #print('origin:',json_data)
    if json_data["show_trigger_agv"] == True and json_data["phase"] == 2:
        move_alignbar(1)
        move_overhead(1)
        overhead_status = False
        json_data["phase"] = 3
    if json_data["lift_status"] == True and json_data["phase"] == 4:
        move_alignbar(2)
        json_data["phase"] = 5
    json_data["overhead_status"] = overhead_status
    #print('current:',json_data)
    header = {
        'Content-type': 'application/json'
    }
    requests.post(url+'post', data=json.dumps(json_data), headers = header) # 정보 전달

if __name__ == '__main__':
    receive_from_server()