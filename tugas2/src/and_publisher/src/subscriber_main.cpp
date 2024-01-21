#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

std::string pub2 = "empty";
std::string pub1 = "empty";

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "and_operation", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    std::string received = msg->data;
    if(received[10] == '1') {pub1 = received;}
    else if(received[10] == '2') {pub2 = received;}

    if(pub1 != "empty" && pub2 != "empty")
    {

    if(pub1.substr(12, 16) == pub2.substr(12, 16))
    {
      // std::cout << "update: Pub1: " << pub1 << " | Pub2: " << pub2 << std::endl;
      // std::cout << "update: Pub1: " << pub1.substr(12, 16) << " | Pub2: " << pub2.substr(12, 16) << std::endl;
      // std::cout << "update: Pub1: " << pub1[33] << " | Pub2: " << pub2[33] << std::endl;
      if(pub1[33] == pub2[33]) {std::cout<<"sudah siap nih, gass min!\n";}
      else {std::cout<<"tunggu dulu, kami belum ready!\n";}
    }
    }

    // std::cout<<msg->data.c_str()<<std::endl;
    // RCLCPP_INFO(this->get_logger(), "hoh '%s'", msg->data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
