#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>
//#include <opencv2/core/ocl.hpp>
//#include <QtGui/QImage> //may be useful for displaying a live image

using namespace cv;
using namespace std;

void detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale);
string cascadeName, nestedCascadeName;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int, char**){
  Mat frame, image;
  //--- INITIALIZE VIDEOCAPTURE
  VideoCapture capture;
    
  CascadeClassifier cascade, nestedCascade;
  double scale=1;

  //ocl::setUseOpenCL(false);
  
  nestedCascade.load("/home/pi/opencv-4.2.0/data/haarcascades/haarcascade_eye_tree+eyeglasses.xml");

  nestedCascade.load("/home/pi/opencv-4.2.0/data/haarcascades/haarcascade_frontalcatface.xml");
    
  capture.open(0);
  if(capture.isOpened()){
    cout << "Face Detection Started..." << endl;
    while(waitKey(10) != 27){ //hold down any key to display a live image
      capture >> frame;
      if(frame.empty())
	      break;
      Mat frame1 = frame.clone();
      cout << "Starting detect and draw" << endl;
      detectAndDraw(frame1,cascade,nestedCascade,scale);
      //char c = (char)waitKey(25);

      //if( c== 27 || c == 'q' || c == 'Q')
      //break;
    }
  }
  else
    cout << "Could not open the camera!" << endl;
  return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale){
  vector<Rect> faces, faces2;
  Mat gray, smallImg;


  cvtColor(img, gray, COLOR_BGR2GRAY); // convert to grayscale
  double fx = 1/ scale;
  cout << "Converted to grayscale!" << endl;
  //resize image
  resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
  equalizeHist(smallImg, smallImg);
  cout << "Shrunk the image!" << endl;
  // imshow("small gray", smallImg);
  // waitKey(0);
  //Detect faces of different sizes using cascade classifier
  cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
  //Draw circles around the faces

  for(size_t i = 0; i < faces.size(); i++){
    Rect r = faces[i];
    Mat smallImgROI;
    vector<Rect> nestedObjects;
    Point center;
    Scalar color = Scalar(255,0,255); //coilor for drawing tool
    int radius;
    cout << "Initialized the radius" << endl;
    double aspect_ratio = (double)r.width/r.height;
    if(0.75 < aspect_ratio && aspect_ratio < 1.3){
      center.x = cvRound((r.x + r.width*0.5)*scale);
      center.y = cvRound((r.x + r.width*0.5)*scale);
      radius = cvRound((r.x + r.height)*0.25*scale);
      circle(img,center,radius,color,3,8,0);
    }
    else
      rectangle(img,cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
		cvPoint(cvRound((r.x + r.width-1)*scale),
		        cvRound((r.y + r.height-1)*scale)),color,3,8,0);
    cout << "successfully drew one circle" << endl;
    if(nestedCascade.empty())
      continue;
    smallImgROI = smallImg(r);

    //Draw circles around eyes
    //nestedCascade.detectMultiScale(smallImgROI,nestedObjects,1.1,2, 0|CASCADE_SCALE_IMAGE,Size(30,30));
    
  }
  imshow("Face Detection", img);
}
