import tkinter as tk
from PIL import ImageTk, Image
import cv2
from djitellopy import Tello

tello = Tello()

tello.connect()
tello.streamon()

def receive_cam():
    frame = tello.get_frame_read().frame
    img = Image.fromarray(frame) # Image 객체로 변환
    imgtk = ImageTk.PhotoImage(image=img) # ImageTk 객체로 변환
    # OpenCV 동영상
    lbl1.imgtk = imgtk
    lbl1.configure(image=imgtk)
    lbl1.after(10, receive_cam)

win = tk.Tk()
win.title("Stram in GUI Test")
win.geometry("920x640+50+50") # 지오메트리: 너비x높이+x좌표+y좌표
win.resizable(False, False) # x축, y축 크기 조정 비활성화


lbl = tk.Label(win, text="Tkinter와 OpenCV를 이용한 GUI 프로그래밍")
lbl.grid(row=0, column=0) # 라벨 행, 열 배치

frm = tk.Frame(win, bg="white", width=720, height=480) # 프레임 너비, 높이 설정
frm.grid(row=1, column=0) # 격자 행, 열 배치

lbl1 = tk.Label(frm)
lbl1.grid()

receive_cam()
win.mainloop() #GUI 시작