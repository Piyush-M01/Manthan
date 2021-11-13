#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

float linx, angZ;

void filterVelocityCallback(const geometry_msgs::Twist::ConstPtr& msg){
  ROS_INFO("Linear -> x: [%f], y: [%f], z: [%f]", msg->linear.x, msg->linear.y, msg->linear.z);
  ROS_INFO("Angular -> x: [%f], y: [%f], z: [%f]", msg->angular.x, msg->angular.y, msg->angular.z);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("turtle1/cmd_vel",1000,&filterVelocityCallback);
 
  ros::spin();     
}