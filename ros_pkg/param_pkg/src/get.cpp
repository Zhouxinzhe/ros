#include "ros/ros.h"
#include<vector>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "get_node");
    ros::NodeHandle nh;
    std::string name;
    int age;
    std::vector<std::string> subject;
    nh.getParam("name", name);
    nh.getParam("age", age);
    nh.getParam("subject",subject);
    /* or
    ros::param::get.....
    */
    ROS_INFO("The param name is %s", name.c_str());
    ROS_INFO("The param age is %d", age);
    for(std::string tmp: subject)
    {
        ROS_INFO("The param subject includes %s", tmp.c_str());
    }
    ros::shutdown();
    return 0;
}