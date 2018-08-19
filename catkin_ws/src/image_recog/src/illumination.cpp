#include <opencv2/opencv.hpp>
#include <iostream>
#include <ros/ros.h>
using namespace cv;
using namespace std;

Mat frame, mask, dst;
int main(int argc, char** argv){
  ros::init(argc, argv,"illu");
  ros::NodeHandle nh;
  VideoCapture cap(0);
  cap.set(3, 320);
  cap.set(4, 240);
  cap.set(CAP_PROP_FPS, 30);
  while (cap.isOpened()){
    cap >> frame;
    illuminationChange(frame, mask, dst, 0.2f, 0.4f);
    imshow("dst", dst);
    waitKey(1);
  }
  cap.release();
  return 0;
}
