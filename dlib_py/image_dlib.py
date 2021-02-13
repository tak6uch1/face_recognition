import dlib
from imutils import face_utils
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

    # Load face detection and pose estimation models
    detector = dlib.get_frontal_face_detector()
    shape_predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

    # Detect faces
    faces = detector(gray)

    # Detect feature of each face
    for face in faces:
        shapes = shape_predictor(gray, face)
        shapes_np = face_utils.shape_to_np(shapes)

        # Draw rect to frame
        cv2.rectangle(img, (face.left(), face.top()), (face.right() ,face.bottom()), (0,0,255), thickness=3)
        for (x, y) in shapes_np:
            cv2.circle(img, (x, y), 2, (0,255,0), -1)

    # Write image
    cv2.imwrite("output.jpg", img)

    # Display
    while True:
        cv2.imshow('tf-pose-estimation result', img)
        if cv2.waitKey(1) == ord('q'):
            sys.exit(0)

except Exception as e:
    print(str(e))

