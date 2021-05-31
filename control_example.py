#!/usr/bin/env python
import rospy, time
import numpy as np
import math
from std_msgs.msg import String

def PointsInCircum( r, n=100):
    return [(math.cos(2 * math.pi / n * x) * r, math.sin(2 * math.pi / n * x) * r) for x in range( 0,n+1)]

if __name__ == '__main__':
    pub = rospy.Publisher('yarp_rpc_publisher', String, queue_size=10)

    rospy.init_node('head_controler', anonymous=True)

    pub.publish("/SIM_CER_ROBOT/head/rpc:i")
    path_points = PointsInCircum(15)
    while not rospy.is_shutdown():
        for point in path_points:
            pub.publish("1_" + str(point[0]))
            pub.publish("0_" + str(point[1]))
            time.sleep(0.1)
