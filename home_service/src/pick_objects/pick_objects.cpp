#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf2/LinearMath/Quaternion.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

move_base_msgs::MoveBaseGoal set_pose(const float& x, const float& y, const int& yaw) {
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  tf2::Quaternion orientation{};
  orientation.setRPY(0, 0, yaw);
  orientation.normalize();
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.x = orientation[0];
  goal.target_pose.pose.orientation.y = orientation[1];
  goal.target_pose.pose.orientation.z = orientation[2];
  goal.target_pose.pose.orientation.w = orientation[3];
  return goal;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "pick_objects");
  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  move_base_msgs::MoveBaseGoal pickup_zone = set_pose(9.0, 0.6, 0.5);
  ROS_INFO("Moving towards pickup zone");
  ac.sendGoal(pickup_zone);
  ac.waitForResult();
  if(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The robot failed to arrive to pickup zone");
    return 1;
  }
  ROS_INFO("The robot arrived to pickup zone");
  ros::Duration(5.0).sleep();
  move_base_msgs::MoveBaseGoal dropoff_zone  = set_pose(-3.5, -2.5, 2.8);
  ROS_INFO("Moving towards dropoff zone");
  ac.sendGoal(dropoff_zone);
  ac.waitForResult();
  if(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("The robot failed to arrive to dropoff zone");
    return 1;
  }
  ROS_INFO("The robot arrived to dropoff zone");
  return 0;
}