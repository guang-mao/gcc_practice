#ifndef IMAGE_H_
#define IMAGE_H_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define PI 3.14159265

using namespace cv;
using namespace std;
typedef volatile unsigned int vu16;
Mat frame;
VideoCapture cap(0);
int v_threshold = 50;
vu16 width = 640, height = 480;
double theta;

class ROI{
  public:
    Point center;
    void my_contour(Mat &image, float value){
      rectangle(frame, Point(0, height * value), Point(width, height * value + height * 0.25), Scalar(0, 0, 255), 2, CV_AA); 
      cvtColor(image, image, COLOR_BGR2GRAY);
      GaussianBlur(image, image, Size(5,5), 1.3, 1.3);
      threshold(image, image, v_threshold, 255, THRESH_BINARY_INV);
      //Canny(image, image, min_canny, max_canny, 3); 
      findContours(image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,height * value));
      vector<Rect> boundRect(contours.size());
      for (int i = 0; i < contours.size(); i++){
        boundRect[i] = boundingRect(contours[i]);
          //if ((boundRect[i].br().x - boundRect[i].tl().x) < 100 && (boundRect[i].br().y - boundRect[i].tl().y ) < 100){
          center.x = (int) (( boundRect[i].br().x + boundRect[i].tl().x ) * 0.5);
          center.y = (int) (height * 0.25 * 0.5 + height * value);
          rectangle(frame, Point(boundRect[i].tl().x, height * value), Point(boundRect[i].br().x, height * value + height * 0.25), Scalar(0, 255, 0), 2, CV_AA);
          circle(frame, center, 4, Scalar(255, 0, 0), -1, CV_AA);
          //}//if
      } //for
    }
  private:
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
};

ROI roi1, roi2;

void calculate_theta(){
  char my_string[10];
  
  double slope = ((double) (roi2.center.x - roi1.center.x) / (double) (roi2.center.y - roi1.center.y));
  double cosine = (roi1.center.y - roi2.center.y) * (-240) / ( 240 * sqrt(pow((roi1.center.x - roi2.center.x), 2) + pow((roi1.center.y - roi2.center.y), 2)));
  //cout << "X: " << (roi2.center.x - roi1.center.x) << endl;
  //cout << "Y: " << (roi2.center.y - roi1.center.y) << endl;
  //cout << "slope: " << slope << endl;
  //cout << "cosine: " << cosine << endl;
  if (slope < 0){
    theta = acos(cosine) * 180 / PI;
  }
  else if(slope > 0) {
    theta = -(acos(cosine)) * 180 / PI;
    
    
  }
  else if(cosine == 0){
    theta = 90;
  }
  sprintf(my_string, "Theta: %f" ,theta);
  putText(frame, my_string, Point(50,50), 0, 1, Scalar(0, 215, 255), 3, CV_AA);
}



#endif