# swarm-mqp
Development of simulation for heterogeneous swarm.

# mapping System
Do this for each Terminal

cd catkin workspace
source ~/.bashrc
source devel/setup.bash

roscore

Open new terminal

rosrun ardrone_autonomy ardrone_driver

This node publishes data to ardrone topics, including the camera video data to ardrone/front/image_raw.


