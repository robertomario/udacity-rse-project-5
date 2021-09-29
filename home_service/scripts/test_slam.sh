#!/bin/sh

ws_dir=$(cd "$(dirname "$0")/../../../.." && pwd)

xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; roslaunch home_service world.launch " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; rosrun teleop_twist_keyboard teleop_twist_keyboard.py"
