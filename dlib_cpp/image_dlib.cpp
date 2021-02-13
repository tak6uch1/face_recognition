#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

using namespace dlib;
using namespace std;

// Command line option
const cv::String keys = "{@image||Input image.}";

// Convert dlib rectangle to Mat
static cv::Rect dlibRectangleToOpenCV (dlib::rectangle r) {
    return cv::Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
}

int main (int argc, char **argv) {
    try {
        // Parse command line
        cv::CommandLineParser parser(argc, argv, keys);
        cv::String filepath;
        if (parser.has("@image")) {
            filepath = parser.get<cv::String>("@image");
            cout << "Input file: " << filepath << endl;
        } else {
            return 1;
        }

        // Input image
        cv::Mat img = cv::imread(filepath);

        // Viewer
        image_window win;

        // Load face detection and pose estimation models
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Convert Mat to cimg
        cv_image<bgr_pixel> cimg(img);

        // Detect faces 
        std::vector<rectangle> faces = detector(cimg);

        // Detect feature of each face
        std::vector<full_object_detection> shapes;
        for (int i = 0; i < faces.size(); ++i)
            shapes.push_back(pose_model(cimg, faces[i]));

        // Display
        win.clear_overlay();
        win.set_image(cimg);
        win.add_overlay(faces, rgb_pixel(255,0,0));
        win.add_overlay(render_face_detections(shapes));

        // Output image file
        for (int i = 0; i < faces.size(); ++i) {
            cv::rectangle(img, dlibRectangleToOpenCV(faces[i]), CV_RGB(255,0,0), 3);
        }

        // Write image
        cv::imwrite("output.jpg", img);

        win.wait_until_closed();
    }
    catch(exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}

