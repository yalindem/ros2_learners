#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
//#include "pcl/filters/boost.h"
#include "pcl/io/pcd_io.h"
#include "pcl/filters/boost.h"
#include "pcl/point_types.h"
#include "pcl/filters/voxel_grid.h"



class LidarListener : public rclcpp::Node
{
public:
    LidarListener() : Node("lidar_listener")
    {
        // Subscribe to /scan topic
        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&LidarListener::scanCallback, this, std::placeholders::_1));
    }

private:
    // Callback function to handle incoming LaserScan messages
    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg) const
    {
        // Example: Print out the range at the center of the scan
        int num_readings = msg->ranges.size();
        int middle_index = num_readings / 2;

        RCLCPP_INFO(this->get_logger(), "Middle range: %f", msg->ranges[middle_index]);
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    // Create a shared pointer to LidarListener node and spin
    rclcpp::spin(std::make_shared<LidarListener>());

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}
