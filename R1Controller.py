#!/usr/bin/env python
import rospy, time
import numpy as np
from std_msgs.msg import String

if __name__ == '__main__':
    pub = rospy.Publisher('yarp_rpc_publisher', String, queue_size=10)

    rospy.init_node('head_controler', anonymous=True)

    pub.publish("/SIM_CER_ROBOT/head/rpc:i")
    while not rospy.is_shutdown():
        for i in np.arange(-20.0, 35.0, 0.5):
            pub.publish("0_" + str(i))
            time.sleep(0.05)
        for i in np.arange(35.0, -20.0, -0.5):
            pub.publish("0_" + str(i))
            time.sleep(0.05)
