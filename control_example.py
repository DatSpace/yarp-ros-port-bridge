#!/usr/bin/env python
import rospy, time, math, random
import numpy as np
from std_msgs.msg import String

def PointsInCircum( r, n=10):
    return [(math.cos(2 * math.pi / n * x) * r, math.sin(2 * math.pi / n * x) * r) for x in range( 0,n+1)]

doCircle = True

if __name__ == '__main__':
    rospy.init_node('yarp_ros_port_bridge_write_example', anonymous=True)
    pub = rospy.Publisher('yarp_ros_port_bridge_write', String, queue_size=10)

    rospy.rostime.wallsleep(0.5)

    pub.publish("connect /SIM_CER_ROBOT/head/rpc:i")
    pub.publish("connect /SIM_CER_ROBOT/torso/rpc:i")

    path_points = PointsInCircum(15) # Circle with a radius of 15.

    while not rospy.is_shutdown():
        if (doCircle):
            for point in path_points:
                pub.publish("write /SIM_CER_ROBOT/head/rpc:i set pos 1 " + str(point[0]))
                pub.publish("write /SIM_CER_ROBOT/head/rpc:i set pos 0 " + str(point[1]))
                pub.publish("write /SIM_CER_ROBOT/torso/rpc:i set pos 3 " + str(point[0]))
                pub.publish("write /SIM_CER_ROBOT/torso/rpc:i set pos 2 " + str(point[1]))
                rospy.rostime.wallsleep(1.0)
        else:
            point = random.choice(path_points)
            pub.publish("write /SIM_CER_ROBOT/head/rpc:i set pos 1 " + str(point[0]))
            pub.publish("write /SIM_CER_ROBOT/head/rpc:i set pos 0 " + str(point[1]))
            pub.publish("write /SIM_CER_ROBOT/torso/rpc:i set pos 3 " + str(point[0]))
            pub.publish("write /SIM_CER_ROBOT/torso/rpc:i set pos 2 " + str(point[1]))
            rospy.rostime.wallsleep(1.0)
