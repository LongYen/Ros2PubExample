#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <thread>

#define PI		3.14159265358979323846
#define RAD2DEG(x) x*180/PI
#define DEG2RAD(x) x*PI/180
/*
class JoinCommand: public rclcpp::Node
{
  public:
    JoinCommand():Node("minimal_publisher");
    publisher = node->create_publisher<sensor_msgs::msg::JointState>("joint_states_cmd", 10);
  
  private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
}
*/

rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher;

void process(rclcpp::Node::SharedPtr node)
{
  sensor_msgs::msg::JointState message;
  std::cout<<RAD2DEG(3.14)<<std::endl;
  while (rclcpp::ok) {
    message.header.frame_id = "joints";
    message.header.stamp = node->now();
    message.name = {"joint1" , "joint2" , "joint3" , "joint4" , "joint5" , "joint6"};
    message.position = {3.14, 3.14, 3.14, 0.0, 0.0, 0.0};

    publisher->publish(message);
  }
  rclcpp::shutdown();
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("minimal_publisher");
  publisher = node->create_publisher<sensor_msgs::msg::JointState>("joint_states_cmd", 10);
  
  std::thread command_process(process, node);
  // for the subscribe
  rclcpp::spin(node);
  return 0;
}