#include<ros/ros.h>
#include<sensor_msgs/PointCloud2.h>
//PCL specific includes
#include<pcl_conversions/pcl_conversions.h>
#include<pcl/point_cloud.h>
#include<pcl/point_types.h>
#include<pcl/filters/voxel_grid.h>

static const std::string IMAGE_TOPIC = "/usb_cam/image_raw";
static const std::string PUBLISH_TOPIC = "/image_converter/output_video";

ros::Publisher pub;

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& input)
{
    pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
    pcl::PCLPointCloud2 cloud_filtered;

    pcl_conversions::toPCL(*input, *cloud);

    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloudPtr);
    sor.setLeafSize(0.1, 0.1, 0.1);
    sor.filter(cloud_filtered);

    sensor_msgs::PointCloud2 output;
    pcl_conversions::fromPCL(cloud_filtered, output);

    pub.publish(output);
}

 int main(int argc, char** argv)
 {
    ros::init(argc, argv, "plc_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe(IMAGE_TOPIC, 1, cloud_cb);
    // ros::Subscriber sub = nh.subscribe<sensor_msgs::ImageConstPtr>(IMAGE_TOPIC, 10, image_cb);
    pub = nh.advertise<sensor_msgs::PointCloud2>(PUBLISH_TOPIC, 10);
    ros::spin();

    ros::shutdown();
    return 0;
 }
