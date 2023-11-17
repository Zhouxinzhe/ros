#include "ros/ros.h"
#include "turtle_control/num.h"
#include "geometry_msgs/Twist.h"
#include<cmath>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "turtle_control_client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<turtle_control::num>("turtle_control");
    turtle_control::num srv;
    srv.request.n = 13;
    ros::Rate rate(1);
    while(ros::ok())
    {
        if(client.call(srv))
        {
            ROS_INFO("successfully to call service turtle_control.");
        }
        else
        {
            ROS_INFO("failed to call service turtle_control.");
            return 1;
        }
        ros::spinOnce();
        rate.sleep();
    }
    

    return 0;
}
