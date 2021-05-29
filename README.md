# yarp-rpc-ros-wrapper
A simple ROS wrapper for YARP rpc ports

# Instructions

Build and run the executable using plain CMake. It requires at least YARP 3.4 and ROS installed (obviously).

You can control any available part and joint that can receive rpc commands in YARP from your robot.

You can send commands to the rpc port by publishing to the topic: '/yarp_rpc_publisher'

If the message you send (string) starts with a '/' then the string will become the new yarp server (the part to send commands to).

Otherwise, the format that it expects is this: 'joint_position', where joint (int) and position (float) are the values you want to send. Ex. "3_20.5"


There is an example publisher in the python script.
