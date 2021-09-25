#!/bin/sh

xterm  -e  " source /opt/ros/noetic/setup.bash; source ~/ros/roberto_ws/devel/setup.bash; roslaunch home_service world.launch " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ~/ros/roberto_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:='$(find home_service)/map/map.yaml' initial_pose_x:='8.0' initial_pose_y:='-5.0' initial_pose_a:='2.5' " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ~/ros/roberto_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " 
