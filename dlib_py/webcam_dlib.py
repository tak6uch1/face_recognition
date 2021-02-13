import dlib
from imutils import face_utils
import cv2
import sys
import time

try:
    # Camera
    camera = cv2.VideoCapture(0)

    # Load face detection and pose estimation models
    detector = dlib.get_frontal_face_detector()
    shape_predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

    # Frame processing loop
    start_time = time.time()
    frame_cnt = 0
    while True:
        # Get frame
        ret_val, frame = camera.read()

        # Convert to gray scale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect faces
        faces = detector(gray)

        # Detect feature of each face
        for face in faces:
            shapes = shape_predictor(gray, face)
            shapes_np = face_utils.shape_to_np(shapes)

            # Draw rect to frame
            cv2.rectangle(frame, (face.left(), face.top()), (face.right() ,face.bottom()), (0,0,255), thickness=3)
            for (x, y) in shapes_np:
                cv2.circle(frame, (x, y), 2, (0,255,0), -1)

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

