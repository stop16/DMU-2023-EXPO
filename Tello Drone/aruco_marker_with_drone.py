from djitellopy import tello
import cv2
import time
import threading

def add_num(arr, num, id):
    if id == 0:
        arr[0] = num
    if id == 1:
        arr[1] = num

def arr_avg(arr):
    if len(arr) == 2:
        return int((arr[0]+arr[1])/2)

cx_array = [0,0]
cy_array = [0,0]
def process_frame(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_5X5_250)
    parameters = cv2.aruco.DetectorParameters_create()
    corners, ids, rejectedImgPoints = cv2.aruco.detectMarkers(gray, aruco_dict, parameters=parameters)
    gray = frame
    global cx_array
    global cy_array
    if len(corners) > 0:
        ids = ids.flatten()

        for (markerCorner, markerID) in zip(corners, ids):
            corners = markerCorner.reshape((4,2))
            (top_Left, top_Right, bottom_Right, bottom_Left) = corners
            top_Right = (int(top_Right[0]), int(top_Right[1]))
            bottom_Right = (int(bottom_Right[0]), int(bottom_Right[1]))
            bottom_Left = (int(bottom_Left[0]), int(bottom_Left[1]))
            top_Left = (int(top_Left[0]), int(top_Left[1]))

            cv2.line(gray, top_Left, top_Right, (136, 12, 255), 2)
            cv2.line(gray, top_Right, bottom_Right, (136, 12, 255), 2)
            cv2.line(gray, bottom_Right, bottom_Left, (136, 12, 255), 2)
            cv2.line(gray, bottom_Left, top_Left, (136, 12, 255), 2)
            cX = int((top_Left[0] + bottom_Right[0]) / 2.0)
            cY = int((top_Left[1] + bottom_Right[1]) / 2.0)
            cv2.circle(gray, (cX, cY), 4, (136, 12, 255), -1)
            cv2.putText(gray, str(markerID),(top_Left[0], top_Left[1]-5), cv2.FONT_HERSHEY_SIMPLEX,2, (136, 12, 255), 2)
            #print("Aruco Marker ID: {}, X={}, Y={}".format(markerID,cX,cY))
            add_num(cx_array,cX,markerID)
            add_num(cy_array,cY,markerID)
            
    cv2.circle(gray, (arr_avg(cx_array), arr_avg(cy_array)), 10, (136, 12, 255))
    return gray

def move_to_center(threshold=30):
    timer = threading.Timer(5,move_to_center)
    timer.start()
    global cx_array
    global cy_array
    if cx_array[0] != 0 and cx_array[1] != 0:
        center_x = arr_avg(cx_array)
        center_y = arr_avg(cy_array)
        text = ''
        if center_x < 180-threshold:
            text = text + 'move left'
            drone.go_xyz_speed(0,20,0,10)
        elif center_x > 180+threshold:
            text = text + 'move right'
            drone.go_xyz_speed(0,-20,0,10)
        else:
            text = text + 'good x condition'
        
        text = text + ' '

        if center_y < 120-threshold:
            text = text + 'move up'
            drone.go_xyz_speed(0,0,20,10)
        elif center_y > 120+threshold:
            text = text + 'move down'
            drone.go_xyz_speed(0,0,-20,10)
        else:
            text = text + 'good y condition'
        print(text)

drone = tello.Tello()
drone.connect()
print(drone.get_battery())
drone.streamon()
time.sleep(3)
drone.takeoff()
time.sleep(3)
drone.move_up(80)
time.sleep(3)



if __name__ == "__main__":
    move_to_center()
    while True:
        img = drone.get_frame_read().frame
        img = cv2.resize(img, (360,240))
        cv2.imshow("image",process_frame(img))
        cv2.waitKey(1)