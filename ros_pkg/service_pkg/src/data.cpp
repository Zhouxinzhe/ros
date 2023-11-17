#include "ros/ros.h"
#include "std_msgs/Int64MultiArray.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "data_pub");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::Int64MultiArray>("data_for_service",10);
    ros::Rate rate(1);
    while(ros::ok())
    {
        std_msgs::Int64MultiArray msg;
        msg.data = {1,2};
        ROS_INFO("data_pub: %ld, %ld", msg.data[0], msg.data[1]);
        pub.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}