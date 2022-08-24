# Deliverbot_using_ANPR
Deliverbot using ANPR

# Setup
Environment : Ubuntu 18.04 (VirtualBox) / Ros melodic

Install

1. Turtlebot3 : https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/

# Step

Mission #1 : SLAM

- roscore
- ssh ubuntu@{IP_ADDRESS_OF_UBUNTU}
- roslaunch turtlebot3_bringup turtlebot3_robot.launch
- roslaunch turtlebot3_slam turtlebot3_slam.launch
- roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
- rosrun map_server map_saver -f ~/map


Mission #2 : Navigation

- roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml


Mission #3 : Socket Communication

Ubuntu
- rosrun beginner_tutorials talker

Raspberry Pi
- python client.py
