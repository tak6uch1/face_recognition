import argparse
import sys
import cv2

try:
    # Parse command line
    parser = argparse.ArgumentParser(description='Detect Face')
    parser.add_argument('--image', type=str, default='', help='Input image.')
    args = parser.parse_args()

    # Input image
    img = cv2.imread(args.image)

    # Convert to gray scale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Cascade file for face detection
    cascade_path = "/usr/local/share/opencv4/lbpcascades/lbpcascade_frontalface.xml"
    cascade = cv2.CascadeClassifier(cascade_path)

    # Detect faces
    facerect = cascade.detectMultiScale(gray)

    # Draw rect to frame
    for rect in facerect:
        cv2.rectangle(img, tuple(rect[0:2]),tuple(rect[0:2]+rect[2:4]), (0,0,255), thickness=3)

    # Write image
    cv2.imwrite("output.jpg", img)

    # Display
    while True:
        cv2.imshow('tf-pose-estimation result', img)
        if cv2.waitKey(1) == ord('q'):
            sys.exit(0)

except Exception as e:
    print(str(e))

