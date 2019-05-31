#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"
#include <stdlib.h>
int main(int argc, char **argv)
    {
    // Initialize the ROS system and become a node .

      ros::init(argc, argv, "ublisher");

      ros::NodeHandle nh;

    // Create a publisher object .
      ros::Publisher publisher = nh.advertise<sensor_msgs::Range>("sensor_msg/Range", 1000);

    // Loop at 2Hz until the node i s shut down.
      ros::Rate rate(5); 

    while (ros::ok())
      {


 	sensor_msgs::Range msg;
        msg.header.frame_id = "sensor_msgs";
        msg.range = double(rand())/double(RAND_MAX)*4;
        msg.min_range = 0.02;
        msg.max_range = 4;
        msg.field_of_view = 0.785;
        publisher.publish(msg);

    ros::spinOnce();
            rate.sleep();
      }  
      return 0;
}
