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

    # Cascade file for face detection
    cascade_path = "/usr/local/share/opencv4/lbpcascades/lbpcascade_frontalface.xml"
    cascade = cv2.CascadeClassifier(cascade_path)

    # Frame processing loop
    while video.isOpened():
        # Get frame
        ret_val, frame = video.read()

        # Convert to gray scale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect faces
        facerect = cascade.detectMultiScale(gray)

        # Draw rect to frame
        for rect in facerect:
            cv2.rectangle(frame, tuple(rect[0:2]),tuple(rect[0:2]+rect[2:4]), (0,0,255), thickness=3)

        # Output video file
        writer.write(frame)

        # Display
        cv2.imshow('Face Detected', frame)
        if cv2.waitKey(1) == ord('q'):
            sys.exit(0)

except Exception as e:
    print(str(e))

