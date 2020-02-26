#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <tuple>
#include <thread>
#include <queue>

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bluetooth.h"
#include "rfcomm.h"
#include <string>

#include "servo.h"

using namespace std;
using namespace cv;
void detectAndDisplay( Mat& frame );
void Detect_position(Mat frame);

queue<tuple<int,int>> buffer;
bool on_off;

CascadeClassifier face_cascade;


string convert(int size, char* buf){
    string temp = "";
    for(int i = 0; i< size; i++){
        temp += buf[i];
    }
    return temp;
}



void ble_control(int client){
    servo s1(0,60);
    servo s2(1,90);
    int bytes_read;
    char buf[1024] = { 0 };
    cout << "start bluetooth" << endl;
    while(1){
        bytes_read = read(client, buf, sizeof(buf));
        if( bytes_read > 0 ) {
                //printf("received [%s]\n", buf);
            string temp = convert(bytes_read,buf);
            //cout << temp << endl;
            float degree1 = 0.0;
            float degree2 = 0.0;
            if(temp == "on") on_off = true;
            if(temp == "off") on_off = false;
            if(temp == "quit") exit(0);
            if(temp == "up"){
                degree1 = s1.getDegree();
                degree2 = s2.getDegree();
                s1.setDegree((float)(degree1-3.1415));
            }
            if(temp == "down"){
                degree1 = s1.getDegree();
                s1.setDegree((float)(degree1+3.1415));
            }
            if(temp == "left"){
                degree2 = s2.getDegree();
                s2.setDegree((float)(degree2+3.1415));
            }
            if(temp == "right"){
                degree2 = s2.getDegree();
                s2.setDegree((float)(degree2-3.1415));
            }
            cout << temp << endl;
            
        }
    }
}


int main( int argc, const char** argv )
{
    on_off = true;
    //String face_cascade_name = "./data/haarcascades/haarcascade_frontalface_alt_tree.xml";
    //String face_cascade_name = "./data/haarcascades/haarcascade_frontalcatface.xml";
    String face_cascade_name = "./data/haarcascades/haarcascade_frontalface_alt.xml";
    queue<thread> threads;
    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    
    

    //bluetooth
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);
    char buf[1024] = { 0 };
    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    //loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    //memset(buf, 0, sizeof(buf));
    //END of bluetooth


    
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

    servo s1(0,60);
    servo s2(1,90);

    thread t1(ble_control,client);
    while ( capture.read(frame) )
    {
        //bluetooth
        

        //END of bluetooth

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
        if(on_off){
            if(++frame_counter == 5){
            cout << " detect ";
            threads.push(thread(Detect_position,frame));
            }
            if(!buffer.empty()){
                threads.front().join();
                threads.pop();
                if(buffer.front() != tuple<int,int>{0,0}){
                    int x = get<0>(buffer.front());
                    int y = get<1>(buffer.front());
                    cout << x << "," << y << endl;
                    
                    int temp = s2.getDegree();
                    s2.setDegree(temp-(x-432)/43);
    
                    int temp2 = s1.getDegree();
                    s1.setDegree(temp2+(y-324)/32);
                    
                }
                buffer.pop();
                //threads.push(thread(Detect_position,frame));
                frame_counter = 0;
            }
        }
        

        
        
        if( waitKey(10) == 27 )
        {
            break; // escape
        }
        imshow( "Capture - Face detection", frame );
        cout << endl;
    }
    t1.join();
    return 0;
}

void Detect_position(Mat frame){
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces, 1.1 ,3,0|2, Size(100,100));
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