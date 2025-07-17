//! includes

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>

#include<iostream>

using namespace cv;
using namespace std;

int main() {

  Mat img = imread("./cat.png");

  if( img.empty() ) {

    cerr << "Error: Image not found or unable to open!\n";
    return 1;
    
  }
  
  imshow("Display window", img);

  int k = waitKey(0);

  if(k == 's') imwrite("./copy_cat.png", img);

  return 0;
}
