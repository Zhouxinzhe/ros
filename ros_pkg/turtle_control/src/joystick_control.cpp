#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

sensor_msgs::Joy joy_msg;
geometry_msgs::Twist v_msg;

void callback(const sensor_msgs::Joy::ConstPtr msg)
{
    joy_msg = *msg;
    v_msg.linear.x = joy_msg.axes[1];
    v_msg.linear.y = joy_msg.axes[0];
    //v_msg.linear.z = joy_msg.buttons[4];
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "joystick_control_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<sensor_msgs::Joy>("/joy", 1000, callback);
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    
    ros::Rate rate(5);
    while(ros::ok())
    {
        ros::spinOnce();
        pub.publish(v_msg);
        rate.sleep();

    }
    ros::shutdown();

    return 0;
}