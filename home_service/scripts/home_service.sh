#!/bin/sh

project_dir=$(cd "$(dirname "$0")/.." && pwd)
ws_dir=$(cd "$(dirname "$0")/../../../.." && pwd)

xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; roslaunch home_service world.launch " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; roslaunch home_service nav.launch " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; rosrun rviz rviz -d ${project_dir}/rvizConfig/home_service.rviz " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; rosrun home_service add_markers " & sleep 5
xterm  -e  " source /opt/ros/noetic/setup.bash; source ${ws_dir}/devel/setup.bash; rosrun home_service pick_objects " 
