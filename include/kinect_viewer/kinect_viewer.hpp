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
		private:
			ros::Subscriber DetectionImageSubscriber;
			ros::Subscriber DepthImageSubscriber;
			ros::Subscriber DetectionMessageSubscriber;
			const std::string Nodename = "kinect_viewer";
			const std::string ParamNameSeparator = "/";
			std::string RGBImageTopicName;
			std::string IRImageTopicName;
			std::string DepthImageTopicName;
			std::string DetectionMessageTopicName;
			std::string DetectionImageWindowName;
			std::string DepthImageWindowName;
	}
}