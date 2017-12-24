#!/usr/bin/env python
# Copyright 2017 Masahiro Kato
# Copyright 2017 Ryuichi Ueda
# Released under the BSD License.

import rospy, rosbag, rosparam
import math, sys, random, datetime
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan
from std_srvs.srv import Trigger, TriggerResponse
from raspimouse_ros_2.msg import ButtonValues
from raspimouse_gamepad_teach_and_replay_urg.msg import Event

class Logger():
    def __init__(self):
        self.sensor_values = LaserScan()
        self.cmd_vel = Twist()

        self._decision = rospy.Publisher('/event',Event,queue_size=100)
	rospy.Subscriber('/buttons', ButtonValues, self.button_callback, queue_size=1)
        rospy.Subscriber('/scan', LaserScan, self.sensor_callback)
        rospy.Subscriber('/cmd_vel', Twist, self.cmdvel_callback)

	self.on = False
	self.bag_open = False

    def button_callback(self,msg):
        self.on = msg.front_toggle

    def sensor_callback(self,messages):
        self.sensor_values = messages

    def cmdvel_callback(self,messages):
        self.cmd_vel = messages

    def output_decision(self):
	if not self.on:
	    if self.bag_open:
		self.bag.close()
		self.bag_open = False
	    return
	else:
	    if not self.bag_open:
		filename = datetime.datetime.today().strftime("%Y%m%d_%H%M%S") + '.bag'
		rosparam.set_param("/current_bag_file", filename)
		self.bag = rosbag.Bag(filename, 'w')
		self.bag_open = True

	s = self.sensor_values
	a = self.cmd_vel
	e = Event()

        e.scan = s
        e.linear_x = a.linear.x
        e.angular_z = a.angular.z

        self._decision.publish(e)
	self.bag.write('/event', e)

    def run(self):
        rate = rospy.Rate(10)
        data = Twist()

        while not rospy.is_shutdown():
            self.output_decision()
            rate.sleep()

if __name__ == '__main__':
    rospy.init_node('logger')
    Logger().run()
