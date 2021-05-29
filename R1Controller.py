#!/usr/bin/env python
import rospy
import math
from std_msgs.msg import String

if __name__ == '__main__':
    pub = rospy.Publisher('yarp_rpc_publisher', String, queue_size=10)

    rospy.init_node('head_controler', anonymous=True)

    rate = rospy.Rate(1000) # 10hz

    while not rospy.is_shutdown():
        pub.publish("0_70.5")
        rate.sleep()