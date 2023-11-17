#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <sstream>

#define PI 3.14159265

geometry_msgs::Twist trajectory(int count, int n)
{
    geometry_msgs::Twist msg;
    int t = count % n ;
    double angle = (double)t / n * 2 * PI;
    msg.linear.x = cos(angle);
    msg.linear.y = sin(angle);
    return msg;
}

geometry_msgs::Twist run_squre(int count)
{
    geometry_msgs::Twist msg;
        if(count/10 % 4 == 0)
        {
            msg.linear.x = 1;
            msg.linear.y = 0;
            msg.linear.z = 0; 
        }
        else if(count/10 % 4 == 1)
        {
            msg.linear.x = 0;
            msg.linear.y = 1;
            msg.linear.z = 0; 
        }
        else if(count/10 % 4 == 2)
        {
            msg.linear.x = -1;
            msg.linear.y = 0;
            msg.linear.z = 0;
        }
        else
        {
            msg.linear.x = 0;
            msg.linear.y = -1;
            msg.linear.z = 0;
        }
        return msg;
}


int main(int argc, char **argv) {
	ros::init(argc, argv, "publisher");
	ros::NodeHandle n;
    n = ros::NodeHandle("turtle1");
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
	ros::Rate loop_rate(1);
	int count = 0;
	while (ros::ok()) {
		geometry_msgs::Twist msg;
        msg = trajectory(count, 3);
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	return 0;
}