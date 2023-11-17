#include "ros/ros.h"
#include "service_pkg/AddTwoInts.h"

bool add(service_pkg::AddTwoInts::Request &req, service_pkg::AddTwoInts::Response &res)
{
    res.sum = req.a + req.b;
    ROS_INFO("request: a = %ld, b = %ld",req.a, req.b);
    ROS_INFO("response: sum = %ld", res.sum);
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "add_two_ints_server");
    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("add_two_ints",add);
    ROS_INFO("ready to add two ints.");
    ros::spin();

    return 0;
}