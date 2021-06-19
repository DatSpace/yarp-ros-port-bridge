# yarp-ros-port-bridge 
A simple ROS bridge for YARP ports

# Instructions

Build and run the executable using plain CMake. It requires at least YARP 3.4 and ROS installed (obviously).

You can control any available part and joint that can receive rpc commands in YARP from your robot.

Once running you can connect to any number of ports using: 'connect \<port_name\>'
Then you can write or read from that port by publishing to the topic: '/yarp_ros_port_bridge_write'

The format of the write command is: 'write \<port-you-connected\> command'
The format of the read command is: 'read \<port-you-connected\> command'

You can disconnect from a port with: 'disconnect \<port\>'

There is an example writter and reader script included.
