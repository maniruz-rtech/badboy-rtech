#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <random_husky_driver/move.h>
#include <stdlib.h>

int main(int argc, char **argv) {
Twist add(random_husky_driver::AddTwoInts::Request  &req,
             random_husky_drive::AddTwoInts::Response &res)
//Initializes ROS, and sets up a node
ros::init(argc, argv, "random_husky_commands");
ros::NodeHandle nh;

//Ceates the publisher, and tells it to publish
//to the husky_velocity_controller/cmd_vel topic, with a queue size of 100
ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel", 100);

//Sets up the random number generator
srand(time(0));

//Sets the loop to publish at a rate of 10Hz
ros::Rate rate(10);

  while(ros::ok()) {
    //Declares the message to be sent
    geometry_msgs::Twist msg;

    //Random x value between -3 and 3 if w press the huskey will go forward by 0.1 step each
  (if req.w=='w'){
    msg.linear.x=6*double(rand())/double(RAND_MAX)-3;
    res.msg+=0.1;
	}
//Random y value between -3 and 3
//if s is pressed from keybord the huskey will go backwork linearly by -0.1 setep each
   (else if req.s=='s') {
     msg.linear.x=6*double(rand())/double(RAND_MAX)-3;
    res.msg-=0.1;
	}
    pub.publish(msg);

    //Delays until it is time to send another message
    rate.sleep();
    }
}

