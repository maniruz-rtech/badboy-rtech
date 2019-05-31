   #include "ros/ros.h"
   #include "std_msgs/String.h"
   
   #include <sstream>
   
   /**
    * This tutorial demonstrates simple sending of messages over the ROS system.
    */
   int main(int argc, char **argv)
   {
    
	//initialize new ROS node called "talker" 
     ros::init(argc, argv, "talker");
   
    
	//create a node handle:it is reference assigned to a new node.
     ros::NodeHandle n;// it is used for both publisher and subscriber
   
	//chatter_pub is a publisher object(like c++ class object call later to publish msg)
	//create a publisher with a topic "chatter" that will send a string message
	//std_msgs= is the advertise type and it contain string inside it.
     ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
	//Rate is a class this is used to define frequency for a loop. Here we send a message each two seconds  
     ros::Rate loop_rate(0.5);//0.5 is the number of msg persecond, each msg will publish in 2 seconds. 
	//if it is 10 then 10 msg per second.
   
     int count = 0;
	//keep spinning loop untill user press Ctrl+c
     while (ros::ok())
     {
       //create a new String ROS message.std_msg=(ros type)standard messages
	//message definition in this link http://docs.ros.org/api/std_msg/html/msg/String.html
       std_msgs::String msg;
   	//create a string for the data. here it is c++ type
       std::stringstream ss;
       ss << "hello world " << count;
	//assign the string data to ROS message data field
       msg.data = ss.str();
  	//print the content of the message in the terminal
       ROS_INFO("%s", msg.data.c_str());

   	//we are calling chatter_pub here and pulishing message.
      chatter_pub.publish(msg);
  	/** after publication all the msg are store to buffer leter when spinOnce() call message published. it means the number of msg we set 		to publish in a second will be in the buffer by "chatter_pub.publish(msg)" later when the "ros::spinOnce() called the whole buffer msg 		will be publish.
      
	**/
	ros::spinOnce();//need to call this function often to allow ROS to process incoming messages
	//it has set to 1 second  
      loop_rate.sleep();// sleep for the rest of the cycle, to enforce the loop rate
      ++count;
    }
  
  
    return 0;
  }

