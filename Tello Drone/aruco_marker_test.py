import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while True:
    try:
        ret, frame = cap.read()
    except:
        while not ret:
            ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    
    aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_5X5_250)
    parameters = cv2.aruco.DetectorParameters_create()
    corners, ids, rejectedImgPoints = cv2.aruco.detectMarkers(gray, aruco_dict, parameters=parameters)
    gray = frame
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
            print("Aruco Marker ID: {}, X={}, Y={}".format(markerID,cX,cY))
    
    cv2.imshow("Image", gray)
    if cv2.waitKey(1) == 27:
        break # esc to quit
cv2.destroyAllWindows()