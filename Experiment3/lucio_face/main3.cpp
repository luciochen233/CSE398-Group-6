#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <tuple>
#include <thread>
#include <queue>

using namespace std;
using namespace cv;
void detectAndDisplay( Mat& frame );
void Detect_position(Mat frame);

queue<tuple<int,int>> buffer;

CascadeClassifier face_cascade;


int main( int argc, const char** argv )
{
    //String face_cascade_name = "./data/haarcascades/haarcascade_frontalface_alt_tree.xml";
    String face_cascade_name = "./data/haarcascades/haarcascade_frontalcatface.xml";
    queue<thread> threads;
    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    
    
    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open( 0 );
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    Mat frame;
    int frame_counter = 0;
    while ( capture.read(frame) )
    {
        cout << "new frame ";
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        resize(frame,frame,Size(864,648));
        cout << " resize  ";
        //-- 3. Apply the classifier to the frame
        //detectAndDisplay( frame );
        if(++frame_counter == 2){
            cout << " detect ";
            threads.push(thread(Detect_position,frame));
        }

        if(!buffer.empty()){
            threads.front().join();
            threads.pop();
            if(buffer.front() != tuple<int,int>{0,0}){
                cout << get<0>(buffer.front()) << "," << get<1>(buffer.front()) << endl;
            }
            buffer.pop();
            //threads.push(thread(Detect_position,frame));
            frame_counter = 0;
        }

        
        
        if( waitKey(10) == 27 )
        {
            break; // escape
        }
        imshow( "Capture - Face detection", frame );
        cout << endl;
    }
    return 0;
}

void Detect_position(Mat frame){
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces, 1.1);
    //tuple<int,int> t1;
    for ( size_t i = 0; i < faces.size() && i<1; i++ )
    {
        //Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        buffer.push(tuple<int,int>{faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2}) ;
        return;
        //ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
    }
    buffer.push(tuple<int,int>{0,0});
}

void detectAndDisplay( Mat& frame )
{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces, 1.3);
    
    for ( size_t i = 0; i < faces.size() && i<1; i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
        //Mat faceROI = frame_gray( faces[i] );
        //-- In each face, Detect_position eyes
        // std::vector<Rect> eyes;
        // eyes_cascade.detectMultiScale( faceROI, eyes );
        // for ( size_t j = 0; j < eyes.size(); j++ )
        // {
        //     Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
        //     int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
        //     circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
        // }
    }
    //-- Show what you got
    imshow( "Capture - Face detection", frame );
}