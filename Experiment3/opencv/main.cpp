#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
int main(int, char**)
{
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap(0);
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
   
    // open selected camera using selected API
    //cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    cap >> frame;
    // wait for a new frame from camera and store it into 'frame'
    // show live and wait for a key with timeout long enough to show images
    imshow("Live", frame);
     
    imwrite("capture.png",frame);
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
