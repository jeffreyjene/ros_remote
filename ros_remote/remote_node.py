#!/usr/bin/env python3
import serial
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

ser = serial.Serial('/dev/ttyACM0', 57600, timeout=1)


class TwistGenerator(Node):
    def __init__(self):
        super().__init__("twist_generator")
        self.twist_generator_ = self.create_publisher(Twist, "cmd_vel", 10)
        self.timer = self.create_timer(0.1, self.publish_twist)

    def publish_twist(self):
        
        ser.reset_input_buffer()
        vals = [8]
        
        line = ser.readline().decode('utf-8').rstrip()
        vals = line.split(",")
        #VALUES FROM REMOTE
        #0 = left stick y
        #1 = left stick x
        #2 = right stick y
        #3 = right stick x
        #4 = lower button
        #5 = middle button
        #6 = top button
        #7 = cherry button
        print(line)
        twist = Twist()
        twist.linear.x = float(vals[0])
        twist.angular.z = float(vals[1])
        self.twist_generator_.publish(twist)

def main(args=None):
    
    rclpy.init(args=args)
    node = TwistGenerator()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()



        

