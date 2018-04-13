#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"
#include "cv_bridge/cv_bridge.h"
#include "kinect_yolo/DepthAndDetections.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <string>
#include <vector>

namespace kinect_viewer {
	class kinectViewer {
		public:
			kinectViewer(ros::NodeHandle& nodeHandle);
			virtual ~kinectViewer();
			void DetectionMessageCallback(const kinect_yolo::DepthAndDetections&);
			void DetectionImageCallback(const sensor_msgs::Image&);
		private:
			ros::NodeHandle nodeHandle_;
			ros::Subscriber DetectionImageSubscriber;
			ros::Subscriber DetectionMessageSubscriber;
			const std::string NodeName = "kinect_viewer";
			const std::string ParamNameSeparator = "/";
			std::string RGBImageTopicNameParamName = "node_rgb_image_topic";
			std::string IRImageTopicNameParamName = "node_ir_image_topic";
			std::string DetectionMessageTopicNameParamName = "node_detection_message_topic";
			std::string RGBImageTopicName;
			std::string IRImageTopicName;
			std::string DetectionImageTopicName;
			std::string DetectionMessageTopicName;
			std::string DetectionImageWindowName = "3D Object Detection";
			std::vector<double> DepthOfDetections;
			std::vector<unsigned int> DetectionsX;
			std::vector<unsigned int> DetectionsY;
			std::vector<unsigned int> DetectionsW;
			std::vector<unsigned int> DetectionsH;
			std::vector<std::string> DetectionsN;
			std::vector<unsigned int> DetectionsR;
			std::vector<unsigned int> DetectionsG;
			std::vector<unsigned int> DetectionsB;
			bool Light = true;
			const int ClassNameXShift = 5;
			const int ClassNameYShift = 15;
			const int DepthXShift = 5;
			const int DepthYShift = 40;
	};
}