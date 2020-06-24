#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "serial_message/msg/serial.hpp"

class Publisher : public rclcpp::Node{
public:
    inline Publisher();
    inline void publish(uint8_t num);
private:
    rclcpp::Publisher<serial_message::msg::Serial>::SharedPtr publisher_;
};

Publisher::Publisher() : Node("serial1"){
    publisher_ = this->create_publisher<serial_message::msg::Serial>("serial1",10);
}

void Publisher::publish(uint8_t num){
    auto message = serial_message::msg::Serial();
    message.data = num;
    publisher_->publish(message);
}

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Publisher>();
    while(rclcpp::ok()){
        node->publish(1);
        RCLCPP_INFO(node->get_logger(), "published");
    }
    rclcpp::shutdown();
    return 0;
}