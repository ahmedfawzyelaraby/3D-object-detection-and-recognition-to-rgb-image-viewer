# Kinect 3D Object Detection and Recognition ROS Viewer Node
This is a c++ ROS node code, whose role is to read the RGB images from the kinect and the detections message published  from the Kinect **YOLO** ROS node. It displays the RGB images, draw bounding boxes arroung each detected object and types the class of the object and its depth inside that box.
## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. **Please be noted that this code is tested on Ubuntu OS only**.
### Prerequisites
Things you need on your local machine, in order to be able to compile and use this ROS node.

- [Kinect 3D Object Detection and Recognition ROS **YOLO** Node](https://AhmedFawzyElaraby@bitbucket.org/AhmedFawzyElaraby/ros_kinect_to_yolo_node.git)
### Installation
```
$ cd [ROS_WorkSpace]/src
$ git clone https://AhmedFawzyElaraby@bitbucket.org/AhmedFawzyElaraby/ros_kinect_to_yolo_node.git
$ source ../depl/setup.bash
$ catkin build kinect_viewer
```
### Deployment
This node is dependent on the Kinect 3D Object Detection and Recognition ROS YOLO Node, so it is launched automatically with the launch file of the other node, as follows:
```
$ cd [ROS_WorkSpace]/src
$ source ../depl/setup.bash
$ roslaunch kinect_yolo/launch/kinect.launch
```