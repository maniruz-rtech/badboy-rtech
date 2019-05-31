

/* Author: Sachin Chitta, Dave Coleman, Mike Lautman */

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{
//creating node called "plan"
  ros::init(argc, argv, "plan");
	// creating a object name "node_handle" of class NodeHandle
	// To publishe or subscribe or to handle the created node.
  ros::NodeHandle node_handle;
/****
does not conform to the abstract INTERFACE. Instead, it spins asynchronously when you call start(), and stops when either you call stop(), ros::shutdown() is called, or its destructor is called?
*****/
  ros::AsyncSpinner spinner(1);
  spinner.start();
 /*********setup******************/
 // MoveIt! operates on sets of joints called "planning groups" and stores them in an object called
  // the `JointModelGroup`. Throughout MoveIt! the terms "planning group" and "joint model group"
  // are used interchangably.

  static const std::string PLANNING_GROUP = "sia5";

  // The :move_group_interface:`MoveGroup` class can be easily
  // setup using just the name of the planning group you would like to control and plan for.
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
	
  // Cartesian Paths
  // ^^^^^^^^^^^^^^^
  // You can plan a Cartesian path directly by specifying a list of waypoints
  // for the end-effector to go through. The initial pose (start state) does not
  // need to be added to the **WAYPOINT** list but adding **IT CAN HELP WITH VISUALIZATIONS**
  geometry_msgs::Pose target_pose = move_group.getCurrentPose().pose;

  std::vector<geometry_msgs::Pose> waypoints;
  waypoints.push_back(target_pose);

  target_pose.position.z -= 0.2;
  waypoints.push_back(target_pose);  // down

  target_pose.position.y -= 0.2;
  waypoints.push_back(target_pose);  // right

  target_pose.position.z += 0.2;
  target_pose.position.y += 0.2;
  waypoints.push_back(target_pose);  // up and left


  // Cartesian motions are frequently needed to be slower for actions such as approach and retreat
  // grasp motions. Here we demonstrate how to reduce the speed of the robot arm via a scaling factor
  // of the maxiumum speed of each joint. Note this is not the speed of the end effector point.
 // move_group.setMaxVelocityScalingFactor(0.1);

  // We want the Cartesian path to be interpolated at a resolution of 1 cm
  // which is why we will specify 0.01 as the max step in Cartesian
  // translation.  We will specify the jump threshold as 0.0, effectively disabling it.
  // Warning - disabling the jump threshold while operating real hardware can cause
  // large unpredictable motions of redundant joints and could be a safety issue
  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);



  // END_TUTORIAL

  ros::shutdown();
  return 0;
}
