// #include "ros/ros.h"
// #include "nav_msgs/Odometry.h"


// void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
// {
//   ROS_INFO("Seq: [%d]", msg->header.seq);
//   ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
//   ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
//   ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
// }


// int main(int argc, char **argv)
// {

//   ros::init(argc, argv, "odom_list");

//   ros::NodeHandle n;

//   ros::Subscriber sub = n.subscribe("odom", 1000, chatterCallback);

//   ros::spinOnce();

//   ros::init(argc, argv, "publish_velocity");
//   ros::NodeHandle nh;

//   ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);


//   ros::Rate rate(2);
//   while(ros::ok()){
//     geometry_msgs::Twist msg;
//     msg.linear.x = 5;
//     // msg.linear.y = 10;
//     // msg.linear.z = 20;
//     // msg.angular.x = 50;
//     // msg.angular.y = 100;
//     // msg.angular.z = 200;

//     pub.publish(msg);
//     ros::spinOnce();

//     rate.sleep();
//   }


//   return 0;
// }

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"


class central {
  public:
   
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher pub;


  central(ros::NodeHandle& nh) { //constructor
 
    
    this->n = nh;
    

    sub = this->n.subscribe("odom",10, &central::odomCallback,this);
    pub = this->n.advertise<geometry_msgs::Twist>("cmd_vel",100);
    
  }

  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    ROS_INFO("Seq: [%d]", msg->header.seq);
    ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
    ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
  }



  void publish() {
    
    ros::Publisher pub = this->n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    ros::Rate rate(2);

    while(ros::ok()) { 
      geometry_msgs::Twist msg;
      msg.linear.x = 5;
      // msg.linear.y = 10;
      // msg.linear.z = 20;
      // msg.angular.x = 50;
      // msg.angular.y = 100;
      // msg.angular.z = 200;

      pub.publish(msg);
      ros::spinOnce();

      rate.sleep();
    }
  }
};

int main(int argc, char **argv) {
  ros::init(argc,argv,"controller");
  ros::NodeHandle nh;

  central ob(nh);

  ros::spin();


  return 0;
}