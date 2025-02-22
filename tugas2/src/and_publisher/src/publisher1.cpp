#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(this->now().nanoseconds()/1000000000 + 2)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("and_operation", 10);
    timer_ = this->create_wall_timer(
      2000ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:

  bool state = false;

  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "publisher-1-(" + std::to_string(count_) + " sec) → ";
    count_+=2;
    if(state){message.data += "true"; state = false;} else {message.data += "false"; state = true;}
    RCLCPP_INFO(this->get_logger(), "%s", message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
