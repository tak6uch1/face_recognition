#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;

int main (int argc, char **argv){
    try {
        // Camera
        cv::VideoCapture camera(0);
        if (!camera.isOpened()) {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }
    
        // Cascade file for face detection
        const std::string cascade_name = "/usr/local/share/opencv4/lbpcascades/lbpcascade_frontalface.xml";
        cv::CascadeClassifier cascade;
        cascade.load(cascade_name);
    
        // Frame processing loop
        time_t start_time = time(NULL);
        double frame_cnt = 0;
        while (cv::waitKey(1) != 'q') {
            // Get frame
            cv::Mat frame, gray;
            camera >> frame;
            if (frame.empty() == true) break;

            // Convert to gray scale
            cv::cvtColor(frame, gray, cv::COLOR_BGRA2GRAY);
    
            // Detect faces
            std::vector<cv::Rect> faces;
            cascade.detectMultiScale(gray, faces);
    
            // Draw ract to frame
            for(std::vector<cv::Rect>::iterator it=faces.begin(); it!=faces.end(); it++){
                cv::rectangle(frame, *it, CV_RGB(255,0,0), 3);
            }
    
            // Display
            cv::imshow("Face Detected", frame);

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
