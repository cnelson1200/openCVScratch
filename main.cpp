#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int, char **) {
    Mat frame;
    Mat keyFrame;
    Mat res;
    CvFont font;
    cvInitFont(&font, 1, 1, 1);
    double sum = 0;
    uint32_t thresh = 1000000;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    cap.read(keyFrame);
    for (;;) {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        res = keyFrame - frame;
        sum = cv::sum(res)[0];
        putText(res, to_string(sum), cvPoint(100, 100), 1, 1, 255);
        // show live and wait for a key with timeout long enough to show images
        if (sum > thresh) {
            imshow("Live", 255 - res);
        } else {
            imshow("Live", res);
        }
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}