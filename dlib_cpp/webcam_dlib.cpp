#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <time.h>

using namespace dlib;
using namespace std;

int main() {
    try {
        // Set camera
        cv::VideoCapture camera(0);
        if (!camera.isOpened()) {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        // Viewer
        image_window win;

        // Load face detection and pose estimation models
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Frame processing loop
        time_t start_time = time(NULL);
        double frame_cnt = 0;
        while(!win.is_closed()) {
            // Get frame
            cv::Mat frame;
            if (!camera.read(frame)) {
                break;
            }

            // Convert to gray scale (Deleted because gray scale was little faster)
            //cv::Mat gray;
            //cv::cvtColor(frame, gray, cv::COLOR_BGRA2GRAY);

            // Convert Mat to cimg
            cv_image<bgr_pixel> cimg(frame);
            //cv_image<uchar> cimg(gray);

            // Detect faces 
            std::vector<rectangle> faces = detector(cimg);

            // Detect feature of each face
            std::vector<full_object_detection> shapes;
            for (unsigned long i = 0; i < faces.size(); ++i)
                shapes.push_back(pose_model(cimg, faces[i]));

            // Draw rect and face feature
            win.clear_overlay();
            win.set_image(cimg);
            win.add_overlay(faces, rgb_pixel(255,0,0));
            win.add_overlay(render_face_detections(shapes));

            frame_cnt++;
        }
        // FPS
        time_t end_time = time(NULL);
        double fps = frame_cnt / (end_time - start_time);
        cout << "FPS=" << std::setprecision(2) << fps << endl;
    } catch(exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
