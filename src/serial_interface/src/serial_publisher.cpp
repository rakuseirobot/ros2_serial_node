#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "serial_message/msg/serial.hpp"
#include "Serial.hpp"

class Publisher : public rclcpp::Node{
public:
    inline Publisher();
    inline void publish(uint8_t num);
private:
    rclcpp::Publisher<serial_message::msg::Serial>::SharedPtr publisher_;
};

Publisher::Publisher() : Node("serial1"){
    publisher_ = this->create_publisher<serial_message::msg::Serial>("serial1",10);
    this->declare_parameter<std::string>("Port", "/dev/ttyUSB0");
    this->declare_parameter<std::int64_t>("Baud_Rate", 9600);
}

void Publisher::publish(uint8_t num){
    auto message = serial_message::msg::Serial();
    message.data = num;
    publisher_->publish(message);
}

int main(int argc, char **argv){
    std::string port_name;
    Serial serial;
    unsigned int baud_rate;
    unsigned char serial_byte;

    rclcpp::init(argc, argv);
    auto node = std::make_shared<Publisher>();

    node->get_parameter("Port", port_name);
    node->get_parameter("Baud_Rate", baud_rate);

    if(!serial.open(port_name, baud_rate)){
        RCLCPP_ERROR(node->get_logger(), "couldn't open serial port, \"%s\"", port_name.c_str());
        rclcpp::shutdown();
        //return -1;
        exit(-1);
    }

    while(rclcpp::ok()){
        serial_byte = serial.read1byte();
        node->publish(serial_byte);
        RCLCPP_INFO(node->get_logger(), "published");
    }
    rclcpp::shutdown();
    exit(0);
}