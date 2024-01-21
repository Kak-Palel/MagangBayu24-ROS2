#include <memory>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

float eksekusi(float num1, char op, float num2)
{
  if(op == '+') {return num1 + num2;}
  else if(op == '-') {return num1 - num2;}
  else if(op == '*') {return num1 * num2;}
  else if(op == '/') {return num1 / num2;}
  else if(op == '%') {return (float)((int)num1 % (int)num2);}
  return -1;
}

std::string menghitung(std::string soal)
{
  int result;
  int batas = 0;
  std::vector<int> numbers;
  std::vector<char> ops;
  for(size_t i = 0; i < soal.size(); i++)
  {
    if(soal[i] == ' ' || i == soal.size()-1)
    { 
      numbers.push_back(std::stoi(soal.substr(batas, i - batas + 1)));
      if(i != soal.size()-1) {ops.push_back((char)soal[i+1]);}
      i+=2;
      batas = i;
    }
  }
  // std::cout<<"ops 1 : " << ops[0] << " and ops 2 : " << ops[1] << " and nums : " << numbers[0] << ' ' << numbers[1] << ' ' << numbers[2] <<std::endl;
  if(ops[0] == '*' || ops[0] == '/' || ops[0] == '%')
  {
    result = (int)eksekusi(eksekusi((float)numbers[0], ops[0], (float)numbers[1]), ops[1], (float)numbers[2]);
  }
  else
  {
    result = (int)eksekusi((float)numbers[0], ops[0], eksekusi((float)numbers[1], ops[1], (float)numbers[2]));
  }
  return std::to_string(result);
}


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "matematika", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    std::string soal = msg->data.c_str();
    std::string jawaban = menghitung(soal);
    RCLCPP_INFO(this->get_logger(), soal + " = " + jawaban);
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