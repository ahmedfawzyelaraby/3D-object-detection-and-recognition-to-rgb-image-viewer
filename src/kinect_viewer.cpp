#include "kinect_viewer/kinect_viewer.hpp"

namespace kinect_viewer {

kinectViewer::kinectViewer(ros::NodeHandle& nodeHandle) : nodeHandle_(nodeHandle)
{
	RGBImageTopicNameParamName = ParamNameSeparator + NodeName + ParamNameSeparator + RGBImageTopicNameParamName;
	IRImageTopicNameParamName = ParamNameSeparator + NodeName + ParamNameSeparator + IRImageTopicNameParamName;
	DetectionMessageTopicNameParamName = ParamNameSeparator + NodeName + ParamNameSeparator + DetectionMessageTopicNameParamName;

	ROS_INFO_STREAM(RGBImageTopicNameParamName);
	ROS_INFO_STREAM(IRImageTopicNameParamName);
	ROS_INFO_STREAM(DetectionMessageTopicNameParamName);

	nodeHandle_.getParam(RGBImageTopicNameParamName, RGBImageTopicName);
	nodeHandle_.getParam(IRImageTopicNameParamName, IRImageTopicName);
	nodeHandle_.getParam(DetectionMessageTopicNameParamName, DetectionMessageTopicName);

	DetectionImageTopicName = RGBImageTopicName;

	cv::namedWindow(DetectionImageWindowName);

	DetectionMessageSubscriber = nodeHandle_.subscribe(DetectionMessageTopicName,1, &kinectViewer::DetectionMessageCallback, this);
	DetectionImageSubscriber = nodeHandle_.subscribe(DetectionImageTopicName,1, &kinectViewer::DetectionImageCallback, this);
}

kinectViewer::~kinectViewer()
{
}

void kinectViewer::DetectionMessageCallback(const kinect_yolo::DepthAndDetections& DetectionMessage)
{
	DepthOfDetections = DetectionMessage.EquivalentDepth;
	DetectionsX = DetectionMessage.DetectionsX;
	DetectionsY = DetectionMessage.DetectionsY;
	DetectionsW = DetectionMessage.DetectionsWidth;
	DetectionsH = DetectionMessage.DetectionsHeight;
	DetectionsN = DetectionMessage.DetectionsName;
	DetectionsR = DetectionMessage.DetectionsRColor;
	DetectionsG = DetectionMessage.DetectionsGColor;
	DetectionsB = DetectionMessage.DetectionsBColor;

	if (Light != DetectionMessage.Light)
	{
		Light = DetectionMessage.Light;
		if (Light == true)
		{
			DetectionImageTopicName = RGBImageTopicName;
			DetectionImageSubscriber = nodeHandle_.subscribe(DetectionImageTopicName,1, &kinectViewer::DetectionImageCallback, this);
		}
		else
		{
			DetectionImageTopicName = IRImageTopicName;
			DetectionImageSubscriber = nodeHandle_.subscribe(DetectionImageTopicName,1, &kinectViewer::DetectionImageCallback, this);
		}		
	}
}

void kinectViewer::DetectionImageCallback(const sensor_msgs::Image& DetectionImage)
{
	cv_bridge::CvImagePtr DetectionCVImage;
	DetectionCVImage = cv_bridge::toCvCopy(DetectionImage, DetectionImage.encoding);

	cv::Mat TmpImage = DetectionCVImage->image.clone();
	for (int iterator = 0; iterator < DepthOfDetections.size(); iterator++)
	{
		cv::rectangle(TmpImage, cv::Rect(DetectionsX[iterator], DetectionsY[iterator], DetectionsW[iterator], DetectionsH[iterator]), cv::Scalar(DetectionsB[iterator], DetectionsG[iterator], DetectionsR[iterator]), 2);
		cv::putText(TmpImage, cv::String(DetectionsN[iterator]), cv::Point2f(DetectionsX[iterator] + ClassNameXShift, DetectionsY[iterator] + ClassNameYShift), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(DetectionsB[iterator], DetectionsG[iterator], DetectionsR[iterator]), 2);
		cv::putText(TmpImage, cv::String(std::to_string(DepthOfDetections[iterator])), cv::Point2f(DetectionsX[iterator] + DepthXShift, DetectionsY[iterator] + DepthYShift), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(DetectionsB[iterator], DetectionsG[iterator], DetectionsR[iterator]), 2);
	}
	cv::imshow(DetectionImageWindowName, TmpImage);
	cv::waitKey(1);
}

}