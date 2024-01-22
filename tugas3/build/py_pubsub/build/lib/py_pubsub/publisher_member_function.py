import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Twist 

#commands
translasi = [0.00, 4.00, 0.00, 4.00, 0.00, 4.00, 0.00, 6.28, -0.1, 0.000, 6.28, -0.2, 0.000, 6.28]
rotasi___ = [2.08, 0.00, 2.08, 0.00, 2.08, 0.00, 0.52, 3.14, 0.00, -1.04, 3.14, 0.00, -1.04, 3.14]

class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        timer_period = 2  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = Twist()
        msg.linear.x = translasi[self.i]
        # msg.linear.y = 0.0 
        msg.angular.z = rotasi___[self.i]
        self.publisher_.publish(msg)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()