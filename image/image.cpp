#include "image.h"

int main(int argc, char** argv){
  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
  cap.set(CV_CAP_PROP_FPS, 60);
  namedWindow(" panel ", 0);
  createTrackbar("thresh value", " panel ", &v_threshold, 255);
  while (cap.isOpened()){
    cap >> frame;
    flip(frame, frame, 1);
    
    //contoursImg = frame.clone();
    Mat roi_top(frame, Rect(0, height * 0.25, width, height * 0.25)); 
    Mat roi_butm(frame, Rect(0, height * 0.5, width, height * 0.25));
    
     
    roi1.my_contour(roi_top, 0.25);
    roi2.my_contour(roi_butm, 0.5);
    calculate_theta();
    
    line(frame, roi1.center, roi2.center, Scalar(0, 0, 255), 3, CV_AA);
    imshow("frame", frame);
    
    waitKey(1);
  }
  cap.release();
  return 0;
}
