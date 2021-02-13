import cv2
import sys
import time

try:
    # Camera
    camera = cv2.VideoCapture(0)

    # Cascade file for face detection
    cascade_path = "/usr/local/Cellar/opencv/4.5.1_2/share/opencv4/lbpcascades/lbpcascade_frontalface.xml"
    cascade = cv2.CascadeClassifier(cascade_path)

    # Frame processing loop
    start_time = time.time()
    frame_cnt = 0
    while True:
        # Get frame
        ret_val, frame = camera.read()

        # Convert to gray scale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect faces
        facerect = cascade.detectMultiScale(gray)

        # Draw rect to frame
        for rect in facerect:
            cv2.rectangle(frame, tuple(rect[0:2]),tuple(rect[0:2]+rect[2:4]), (0,0,255), thickness=3)

        # Display
        cv2.imshow('Face Detected', frame)
        if cv2.waitKey(1) == ord('q'):
            break

        frame_cnt += 1

    end_time = time.time()
    fps = frame_cnt / int(end_time - start_time)
    print("FPS=" + "{:.1f}".format(fps))

except Exception as e:
    print(str(e))

