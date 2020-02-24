#include <opencv2/opencv.hpp>

using namespace cv;

// Take the name of an image file
// as an argument, and display it
// on screen.

int main(int argc, char** argv){


  Mat img = imread(argv[1],-1);
  if(img.empty())
    return -1;
  namedWindow( "Example",WINDOW_AUTOSIZE);
  imshow("Example",img);
  waitKey(0);
  destroyWindow("Example");
  return 0;
}
