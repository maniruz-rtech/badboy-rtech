#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{

  ros::init(argc, argv, "plan22");

  ros::NodeHandle node_handle;

  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "sia5";


  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  //moveit::planning_interface::MoveGroupInterface::Plan my_plan;
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


  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
	
//my_plan.trajectory_=trajectory;

//move_group.execute(my_plan);
  ros::shutdown();
  return 0;
}
