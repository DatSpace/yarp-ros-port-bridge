#!/usr/bin/env python
import rospy, time, math
from std_msgs.msg import String


def wrapperCallback(msg):
    print(msg.data)

if __name__ == '__main__':
    rospy.init_node('yarp_rpc_wrapper_read_example', anonymous=True)
    pub = rospy.Publisher('yarp_rpc_wrapper_write', String, queue_size=10)
    sub = rospy.Subscriber('yarp_rpc_wrapper_read', String, callback=wrapperCallback, queue_size=10)

    rospy.rostime.wallsleep(0.5)

    pub.publish("connect /SIM_CER_ROBOT/head/rpc:i")

    while not rospy.is_shutdown():
        pub.publish("read /SIM_CER_ROBOT/head/rpc:i get pos 1")
        pub.publish("read /SIM_CER_ROBOT/head/rpc:i get pos 0")
        rospy.rostime.wallsleep(1.0)
