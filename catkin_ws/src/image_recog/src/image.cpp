#include "image.h"
#include <geometry_msgs/Twist.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include<opencv2/highgui/highgui.hpp>

namespace enc = sensor_msgs::image_encodings;
static const std::string OPENCV_WINDOW = "Image window";
int my_FPS, width, height;
VideoCapture cap(0);

int efrt_roll, efrt_pitch;
bool f_line = 0;
string pixel_format;
void draw_line(const geometry_msgs::Twist &msg);

class ImageConverter
{
  ros::NodeHandle nh;
  ros::Publisher pub;
  ros::Subscriber sub; 
  ros::Subscriber l_sub;
  
  image_transport::Subscriber image_sub;
 
  
  public:
    
    ImageConverter() 
      : nh("~")
    {
      image_transport::ImageTransport it(nh);
      image_sub = it.subscribe("/usb_cam/image_raw", 1, &ImageConverter::imageCb, this);
      pub = nh.advertise<geometry_msgs::Point>("circle_center_data",10);
      sub = nh.subscribe("stepflag",10, callback); 
      l_sub = nh.subscribe("custom/rc/input", 10, draw_line);
      
      namedWindow(OPENCV_WINDOW);
    }
    
    ~ImageConverter()
    {
      destroyWindow(OPENCV_WINDOW);
    }
    
    void imageCb(const sensor_msgs::ImageConstPtr& image_msg);
    void FindCircle(Mat& frame);
      
};



int main(int argc, char**argv){
  ros::init(argc, argv, "Image");
  
  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);  //cap.set(3,320);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height); //cap.set(4,240);
  cap.set(CAP_PROP_FPS, my_FPS);
  
  /*image_transport::Publisher image_pub = it.advertise("/image_pub", 1);
  nh.param("pixel_format", pixel_format, string("bgr8"));
  nh.param("WIDTH", width, 320);
  nh.param("HEIGHT", height, 240);
  nh.param("frame_rate", my_FPS, 30); 
  cv_bridge::CvImagePtr cv_ptr(new cv_bridge::CvImage);*/
  
  ImageConverter ic;
  
  ros::spin();
  return 0;
}
//-----------------------------------------------------------------------------------




//--------------------------------------Subroutines----------------------------------

void ImageConverter::FindCircle(Mat& frame){
  vector<Vec3f> circles;
  cvtColor(frame, dst, COLOR_BGR2GRAY);
  GaussianBlur(dst, dst, Size(5,5), 1.3, 1.3);
  HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100, 0, 320); //30
  if(circles.size() > 0) f_line = 1;
  for (int i=0; i<circles.size(); i++){
    Point center(circles[i][0],circles[i][1]);   //declare variable that are two integer type variables(x,y).
    Point g_center(circles[i][0],circles[i][1]);
    if (f_line == true){
      line(frame, Point(g_center), Point(( g_center.x + efrt_roll), ( g_center.y  + efrt_pitch)), Scalar(0, 0, 255), 5, CV_AA);
      //line(frame, g_center, (g_center[0][0], (g_center[0][1] + efrt_pitch)), Scalar(0, 0, 255), 5, CV_AA);
      f_line = 0;
    }
    radius=cvRound(circles[i][2]);  //rounding the data number before assign to radius.
    circle(frame, center, radius, Scalar(0,0,255), 1, 8, 0);  //drawing a circle and the circle is solid
    circle(frame, center, 1, Scalar(0,255,0), 1, 8, 0); 
    
    ROS_INFO("Center X: [%i] , Y: [%i] ",center.x,center.y);
    msg.x = center.x;      
    msg.y = center.y;
    msg.z = radius;
    pub.publish(msg);
    
  }   //for
  
}

void C_buffer_and_RFPS(unsigned int rfps){
  static unsigned int count = 0;
  rfps = my_FPS / (my_FPS - rfps);
  count++; 
  if (rfps >= count){ 
    cap.grab();
    count = 0;
  }
}

void callback(const std_msgs::Float64 &msg){
  flag = msg.data;
}

void draw_line(const geometry_msgs::Twist &msg){
  efrt_roll = (int) msg.angular.x;
  efrt_pitch = (int) msg.angular.y;
  efrt_roll = (efrt_roll - 1500) * 2;
  efrt_pitch = (efrt_pitch - 1500) * 2;
}

void ImageConverter::imageCb(const sensor_msgs::ImageConstPtr& image_msg){
  cv_bridge::CvImagePtr cv_ptr;
  try{
    cv_ptr = cv_bridge::toCvCopy(image_msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  FindCircle(cv_ptr -> image);
  imshow(OPENCV_WINDOW, cv_ptr -> image);
  waitKey(1);
}