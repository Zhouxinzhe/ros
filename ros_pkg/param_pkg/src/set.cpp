#include "ros/ros.h"
#include<vector>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "set_node");
    ros::NodeHandle nh;
    std::vector<std::string> subject;
    subject.push_back("math");
    subject.push_back("science");
    nh.setParam("name", "zhouxinzhe");
    nh.setParam("age",19);
    nh.setParam("subject", subject);
    /* or
    ros::param::set("name", "zhouxinzhe");
    ros::param::set("age",19);
    ros::param::set("subject", subject);
    */
    
    ros::shutdown();
    return 0;
}