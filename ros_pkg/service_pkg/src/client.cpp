#include "ros/ros.h"
#include "std_msgs/Int64MultiArray.h"
#include "service_pkg/AddTwoInts.h"
#include<iostream>

long int x = 0, y = 0;
bool flag = false;
void callback(const std_msgs::Int64MultiArray::ConstPtr msg)
{
    x = msg->data[0];
    y = msg->data[1];
    ROS_INFO("successfully receive data: %ld, %ld", x, y);
    flag = true;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "add_two_ints_client");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::Int64MultiArray>("data_for_service", 1000, callback);
    ros::ServiceClient client = nh.serviceClient<service_pkg::AddTwoInts>("add_two_ints");
    service_pkg::AddTwoInts srv;
    ros::Rate rate(1);
    while(!flag)
    {
        ROS_INFO("failed to receive data.");
        ros::spinOnce();
        rate.sleep();
    }
    while(true)
    {
        srv.request.a = x;
        srv.request.b = y;
        if(client.call(srv))
        {
            ROS_INFO("sum = %ld", (long int)srv.response.sum);
            break;
        }
        else
        {
            ROS_INFO("failed to call service add_two_ints.");
        } 
        rate.sleep();
    }
    ros::spin();


    return 0;
}