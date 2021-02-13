import dlib
from imutils import face_utils
import argparse
import sys
import cv2

try:
    # Parse command line
    parser = argparse.ArgumentParser(description='Detect Face')
    parser.add_argument('--video', type=str, default='', help='Input video.')
    args = parser.parse_args()

    # Input video
    video = cv2.VideoCapture(args.video)
    if video.isOpened() is False:
        sys.exit(1)

    # Video writer
    width  = int(video.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(video.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps    = int(video.get(cv2.CAP_PROP_FPS))
    codec = cv2.VideoWriter_fourcc(*'mp4v')
    writer = cv2.VideoWriter('output.mp4', codec, fps, (width, height))

    # Load face detection and pose estimation models
    detector = dlib.get_frontal_face_detector()
    shape_predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

    # Frame processing loop
    while video.isOpened():
        # Get frame
        ret_val, frame = video.read()

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

        # Output video file
        writer.write(frame)

        # Display
        cv2.imshow('Face Detected', frame)
        if cv2.waitKey(1) == ord('q'):
            sys.exit(0)

except Exception as e:
    print(str(e))

