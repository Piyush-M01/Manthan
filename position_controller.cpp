#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>

class controller
{
	public:
	geometry_msgs::Pose2D current_pose;
	ros::Publisher pub_pose2d;
	double x,y,z;
	double roll,pitch,yaw;
	void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg);
};

void controller::chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
	{
		ROS_INFO("Seq: [%d]", msg->header.seq);
		ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
		ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
		ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);

		controller ob;
		ob.current_pose.x = msg->pose.pose.position.x;
    	ob.current_pose.y = msg->pose.pose.position.y;
		ob.z=msg->pose.pose.position.z;

		tf::Quaternion quat;
		tf::quaternionMsgToTF(msg->pose.pose.orientation,quat);
		//double roll,pitch,yaw;
		tf::Matrix3x3(quat).getRPY(ob.roll,ob.pitch,ob.current_pose.theta);
		//ob.pub_pose2d.publish(current_pose);
		//ROS_INFO("Roll : [%f]",roll);
		//ROS_INFO("Pitch : [%f]",pitch);
	}

int main(int argc, char **argv)
{

	
	ros::init(argc, argv, "odom_listener");
	//create a handle node
	ros::NodeHandle n;
	controller ob;
	ROS_INFO("X [%f]",ob.x);
	ros::Subscriber sub = n.subscribe("odom",1000, &controller::chatterCallback,&ob);
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
	geometry_msgs::Twist speed;
	geometry_msgs::Point goal;
	ros::Rate loop_rate(10);
	goal.x=5;
	goal.y=5;
	while(ros::ok())
	{

		double difX=goal.x - ob.current_pose.x;
		double difY=goal.y - ob.current_pose.y;
		double dist=sqrt(pow(difX,2)+pow(difY,2));

		double angle=atan2(difY,difX);
		ROS_INFO("Angle [%f]",ob.x);
		if (abs(angle-ob.current_pose.theta)>0.1)
		{
			speed.linear.x=0;
			speed.angular.z=1;
		}
		else
		{
			speed.linear.x=5;
			//speed.linear.y=5;
			speed.angular.z=0.0;
		}
		chatter_pub.publish(speed);
		ros::spinOnce();
	}
		//subscriber lister the msgs of given topic
		//run it until you press ctrl+c
		return 0;
	
}
