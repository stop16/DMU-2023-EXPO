from djitellopy import Tello # Import library to control tello drone
import time # Import library about time
import threading # Import threading library because djitellopy uses opencv internally.
import cv2 # Import opencv library
import tkinter # Import tkinter library for GUI
from PIL import Image, ImageTk
#import gamepad_control

LOW_BATTERY_VAL = 50

tello = Tello()

tello.connect() #Connects tello drone with AP mode(Wifi mode does not supports video streaming.)
#tello.set_video_fps(Tello.FPS_30)
#tello.set_video_resolution(Tello.RESOLUTION_480P)

tello.streamon() #Turn on video streaming

def check_battery(ignore_flag=False):
    if ignore_flag == True and tello.get_battery() < LOW_BATTERY_VAL:
        print("battery level low, continue anyway by ignore flag")
    elif ignore_flag == False and tello.get_battery() < LOW_BATTERY_VAL:
        print("battery level low. end program")
        tello.end()

def video_thread():
    global img
    while True:
        src = tello.get_frame_read().frame
        mid_img = Image.fromarray(src)
        img = ImageTk.PhotoImage(mid_img)

try:
    check_battery()
    shared_variables_lock = threading.Lock()
    thread_tello_stream = threading.Thread(target=video_thread,args=())
    #thread_tello_stream.daemon = True
    thread_tello_stream.start()
    #thread_gamepad = threading.Thread(target=gamepad_control.main,args=())
    #thread_gamepad.daemon = True
    #thread_gamepad.start()

    window = tkinter.Tk()
    window.title("Test")
    window.geometry("640x480+100+100")
    thread_tello_stream.join()
    label = tkinter.Label(window,image=img)
    window.mainloop()

except KeyboardInterrupt:
    #tello.land()
    tello.end()