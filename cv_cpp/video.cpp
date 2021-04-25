#include <opencv2/opencv.hpp>

using namespace std;

// Command line option
const cv::String keys = "{@video||Input video.}";

int main (int argc, char **argv){
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
            return 1;
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
     
        // Cascade file for face detection
        const string cascade_name = "/usr/local/Cellar/opencv/4.5.2/share/opencv4/lbpcascades/lbpcascade_frontalface.xml";
        cv::CascadeClassifier cascade;
        cascade.load(cascade_name);
    
        // Frame processing loop
        while (cv::waitKey(1) != 'q') {
            // Get frame
            cv::Mat frame, gray;
            video >> frame;
            if (frame.empty() == true) break;
    
            // Convert to gray scale
            cv::cvtColor(frame, gray, cv::COLOR_BGRA2GRAY);
    
            // Detect faces
            std::vector<cv::Rect> faces;
            cascade.detectMultiScale(gray, faces);
    
            // Draw rect to frame
            for(std::vector<cv::Rect>::iterator it=faces.begin(); it!=faces.end(); it++){
                cv::rectangle(frame, *it, CV_RGB(255,0,0), 3);
            }
    
            // Output video file
            writer << frame;
    
            // Display
            cv::imshow("Face Detected", frame);
        }
    } catch(exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
