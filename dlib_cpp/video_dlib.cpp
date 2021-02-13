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
const cv::String keys = "{@video||Input video.}";

// Convert dlib rectangle to Mat
static cv::Rect dlibRectangleToOpenCV (dlib::rectangle r) {
    return cv::Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
}

int main (int argc, char **argv) {
    try {
        // Parse command line
        cv::CommandLineParser parser(argc, argv, keys);
        cv::String filepath;
        if (parser.has("@video")) {
            filepath = parser.get<cv::String>("@video");
            cout << "Input file: " << filepath << endl;
        }

        // Input video
        cv::VideoCapture video;
        video.open(filepath);
        if (video.isOpened() == false) {
            return 0;
        }

        // Video writer
        cv::VideoWriter writer;
        int width, height, fourcc;
        fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); // mp4
        double fps;
        width  = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
        height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
        fps    = video.get(cv::CAP_PROP_FPS);
        writer.open("output.mp4", fourcc, fps, cv::Size(width, height));

        // Viewer
        image_window win;

        // Load face detection and pose estimation models
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Frame processing loop
        while(!win.is_closed()) {
            // Get frame
            cv::Mat frame;
            video >> frame;
            if (frame.empty() == true) break;

            // Convert Mat to cimg
            cv_image<bgr_pixel> cimg(frame);

            // Detect faces 
            std::vector<rectangle> faces = detector(cimg);

            // Detect feature of each face
            std::vector<full_object_detection> shapes;
            for (int i = 0; i < faces.size(); ++i)
                shapes.push_back(pose_model(cimg, faces[i]));

            // Draw rect and face feature
            win.clear_overlay();
            win.set_image(cimg);
            win.add_overlay(faces, rgb_pixel(255,0,0));
            win.add_overlay(render_face_detections(shapes));

            // Draw rect to frame
            for (int i = 0; i < faces.size(); ++i) {
                cv::rectangle(frame, dlibRectangleToOpenCV(faces[i]), CV_RGB(255,0,0), 3);
            }

            // Output movie file
            writer << frame;
        }
    } catch(exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}

