#!/usr/bin/env python
import rospy, time, math
from std_msgs.msg import String


def subCallback(msg):
    print(msg.data)

if __name__ == '__main__':
    rospy.init_node('yarp_ros_port_bridge_read_example', anonymous=True)
    pub = rospy.Publisher('yarp_ros_port_bridge_write', String, queue_size=10)
    sub = rospy.Subscriber('yarp_ros_port_bridge_read', String, callback=subCallback, queue_size=10)

    rospy.rostime.wallsleep(0.5)

    pub.publish("connect /SIM_CER_ROBOT/head/rpc:i")

    while not rospy.is_shutdown():
        pub.publish("read /SIM_CER_ROBOT/head/rpc:i get pos 1")
        pub.publish("read /SIM_CER_ROBOT/head/rpc:i get pos 0")
        rospy.rostime.wallsleep(1.0)
