#include <ros/ros.h>
#include "kinect_viewer/kinect_viewer.hpp"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "kinect_viewer");
	ros::NodeHandle nodeHandle;

	kinect_viewer::kinectViewer Kinect_Displayer(nodeHandle);

	ros::spin();
	return 0;
}