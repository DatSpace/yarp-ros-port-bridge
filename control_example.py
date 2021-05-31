#!/usr/bin/env python
import rospy, time, math, random
import numpy as np
from std_msgs.msg import String

def PointsInCircum( r, n=100):
    return [(math.cos(2 * math.pi / n * x) * r, math.sin(2 * math.pi / n * x) * r) for x in range( 0,n+1)]

doCircle = False

if __name__ == '__main__':
    pub = rospy.Publisher('yarp_rpc_publisher', String, queue_size=10)

    rospy.init_node('head_controler', anonymous=True)

    rospy.rostime.wallsleep(0.5)

    pub.publish("/SIM_CER_ROBOT/head/rpc:i")
    pub.publish("set vel 0 5")
    pub.publish("set vel 1 5")

    path_points = PointsInCircum(15) # Circle with a radius of 15.

    while not rospy.is_shutdown():
        if (doCircle):
            for point in path_points:
                pub.publish("set pos 1 " + str(point[0]))
                pub.publish("set pos 0 " + str(point[1]))
                rospy.rostime.wallsleep(0.1)
        else:
            point = random.choice(path_points)
            pub.publish("set pos 1 " + str(point[0]))
            pub.publish("set pos 0 " + str(point[1]))
            rospy.rostime.wallsleep(1.0)
