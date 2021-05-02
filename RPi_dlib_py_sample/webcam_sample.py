import dlib
from imutils import face_utils
import cv2
import sys
import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
SERVO_PIN = 23
LED_PIN   = 24

GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, False)

GPIO.setup(SERVO_PIN, GPIO.OUT)
Servo = GPIO.PWM(SERVO_PIN, 50)
Servo.start(0)
Servo.ChangeDutyCycle(12)

try:
    # Camera
    camera = cv2.VideoCapture(0)
    width  = camera.get(cv2.CAP_PROP_FRAME_WIDTH)
    height = camera.get(cv2.CAP_PROP_FRAME_HEIGHT)

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
        servo_flg = False

        # Detect feature of each face
        if len(faces) == 0:
            # LED OFF
            GPIO.output(LED_PIN, False)
            # Servo normal position
            if servo_flg:
                Servo.ChangeDutyCycle(12)
                servo_flg = False

        for face in faces:
            shapes = shape_predictor(gray, face)
            shapes_np = face_utils.shape_to_np(shapes)

            # Draw rect to frame
            cv2.rectangle(frame, (face.left(), face.top()), (face.right() ,face.bottom()), (0,0,255), thickness=3)

            led_flg = False
            (x0, y0, x1, y1) = (0, 0, 0, 0)

            i = 0
            for (x, y) in shapes_np:
                pcolor = (0,255,0)
                if i == 27:
                    x0 = x
                    y0 = y
                    pcolor = (0,0,255)
                if i == 30:
                    x1 = x
                    y1 = y
                    pcolor = (0,0,255)
                #cv2.circle(frame, (x, y), 2, (0,255,0), -1)
                cv2.circle(frame, (x, y), 2, pcolor, -1)
                i += 1
            if abs(x1 - width/2)/width < 0.2 and abs(y1 - height/2)/height < 0.2:
                # LED ON
                led_flg = True
            else:
                # LED OFF
                led_flg = False
            GPIO.output(LED_PIN, led_flg)

            # Detect face inclination
            if led_flg and (x0 - x1)/(y0 - y1) > 0.3:
                if not servo_flg:
                    Servo.ChangeDutyCycle(7.25)
                print("Flag")
                servo_flg = True
            else:
                Servo.ChangeDutyCycle(12)
                servo_flg = False

        # Display
        cv2.imshow('Face Detected', frame)
        if cv2.waitKey(1) == ord('q'):
            break

        frame_cnt += 1

    # LED OFF
    GPIO.output(LED_PIN, False)
    end_time = time.time()
    fps = frame_cnt / int(end_time - start_time)
    print("FPS=" + "{:.1f}".format(fps))

except Exception as e:
    print(str(e))

