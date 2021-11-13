#include <ros/ros.h>
#include <pkg_tf_micromouse/goal_sent.srv>

int main(int argc, char **argv) {
    ros::init(argc, argv, "goal_sent_client");
    ros::NodeHandle n;
    
    ros::ServiceClient client = n.serviceClient<pkg_tf_micromouse::goal_sent>("send the goal");

    pkg_tf_micromouse::goal_sent srv;

    srv.request.goalpoint

}

