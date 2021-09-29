#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf2/LinearMath/Quaternion.h>

visualization_msgs::Marker set_pose(const float& x, const float& y, const float& yaw, const int& id) {
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "add_markers";
  marker.id = id;
  marker.type = visualization_msgs::Marker::CUBE;
  marker.action = visualization_msgs::Marker::ADD;  
  tf2::Quaternion orientation{};
  orientation.setRPY(0, 0, yaw);
  orientation.normalize();
  marker.pose.position.x = x;
  marker.pose.position.y = y;
  marker.pose.position.z = 0.0;
  marker.pose.orientation.x = orientation[0];
  marker.pose.orientation.y = orientation[1];
  marker.pose.orientation.z = orientation[2];
  marker.pose.orientation.w = orientation[3];
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();
  return marker;
}

void check_subs_before_publish(ros::Publisher& publisher, visualization_msgs::Marker& marker) {
  while (publisher.getNumSubscribers() < 1) {
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  publisher.publish(marker);
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  visualization_msgs::Marker pickup_marker = set_pose(9.0, 0.6, 0.5, 0);
  check_subs_before_publish(marker_pub, pickup_marker);
  ROS_INFO("Added first marker");
  ros::Duration(5.0).sleep();
  pickup_marker.action = visualization_msgs::Marker::DELETE;
  check_subs_before_publish(marker_pub, pickup_marker);
  ROS_INFO("Removed first marker");
  ros::Duration(5.0).sleep();
  visualization_msgs::Marker dropoff_marker = set_pose(-3.5, -2.5, 2.8, 1);
  check_subs_before_publish(marker_pub, dropoff_marker);
  ROS_INFO("Added second marker");
  return 0;
}