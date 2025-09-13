#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/string.hpp" //sebelum pakai interface tutorial 
#include "tutorial_interfaces/msg/num.hpp" //setelah pakai interface

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
    public:
        MinimalPublisher()
        : Node ("minimal_publisher"), count_(0)
        {
            // publisher_ = this ->create_publisher <std_msgs::msg::String>("topic",10); //Sebelum pakai interface
            publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic", 10);  // CHANGE
            timer_ = this->create_wall_timer(
                500ms, std::bind(&MinimalPublisher::timer_callback, this)
            );
        }
    
        private:
        // void timer_callback()
        // {
        //     auto message = std_msgs::msg::String();
        //     message.data = "Hello, world!" + std::to_string(count_++);
        //     RCLCPP_INFO(this->get_logger(), "Publishing : '%s'", message.data.c_str());
        //     publisher_->publish(message);
        // } // sebelum menggunakan interface
        void timer_callback()
        {
            auto message = tutorial_interfaces::msg::Num();                                   // CHANGE
            message.num = this->count_++;                                                     // CHANGE
            RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'");    // CHANGE
            publisher_->publish(message);
        }
  

        rclcpp::TimerBase::SharedPtr timer_;
        // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // Sebelum menggunakan interface
        rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_; //CHANGE
        size_t count_;
};

int main (int argc, char * argv[])
{
    rclcpp::init (argc,argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}