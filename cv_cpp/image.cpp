#include <opencv2/opencv.hpp>

using namespace std;

// Command line option
const cv::String keys = "{@image||Input image.}";

int main (int argc, char **argv){
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
        cv::Mat img, gray;
        img = cv::imread(filepath);
        if (img.empty() == true) return 1;

        // Convert to gray scale
        cv::cvtColor(img, gray, cv::COLOR_BGRA2GRAY);

        // Cascade file for face detection
        const string cascade_name = "/usr/local/Cellar/opencv/4.5.1_2/share/opencv4/lbpcascades/lbpcascade_frontalface.xml";;
        cv::CascadeClassifier cascade;
        cascade.load(cascade_name);

        // Detect faces
        std::vector<cv::Rect> faces;
        cascade.detectMultiScale(gray, faces);

        // Draw rect to frame
        for(std::vector<cv::Rect>::iterator it=faces.begin(); it!=faces.end(); it++){
            cv::rectangle(img, *it, CV_RGB(255,0,0), 3);
        }

        // Write image
        cv::imwrite("output.jpg", img);

        // Display
        while (cv::waitKey(1) != 'q') {
            cv::imshow("Face Detected", img);
        }
    } catch(exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
