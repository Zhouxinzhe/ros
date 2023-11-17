#include "ros/ros.h"
#include "turtle_control/num.h"
#include "geometry_msgs/Twist.h"
#include<cmath>

#define PI 3.14159265

ros::Publisher pub;

geometry_msgs::Twist trajectory(int count, int n)
{
    geometry_msgs::Twist msg;
    int t = (count+1) % n ;
    double angle = (double)t / n * 2 * PI;
    msg.linear.x = cos(angle);
    msg.linear.y = sin(angle);
    return msg;
}

bool run(turtle_control::num::Request &req, turtle_control::num::Response &res)
{
    ROS_INFO("start to control.");
    int n = req.n;
    //ros::NodeHandle nh;
    //ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    if(n < 3)
    {
        ROS_INFO("the n must be larger than 3");
        return false;
    }
    int count = 0;
    ros::Rate rate(1);
    while(count < n)
    {
        geometry_msgs::Twist msg;
        msg = trajectory(count, n);
        pub.publish(msg);
        count++; 
        rate.sleep();
    }
    
    ROS_INFO("end control.");
    return true;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "turtle_control_server"); // "turtle_control_server" is the name of the node
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("turtle_control",run); // "turtle_control" is the name of the service
    pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    ROS_INFO("ready to control the turtle.");
    ros::spin(); 

    return 0;
}