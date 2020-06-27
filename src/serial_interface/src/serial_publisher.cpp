#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "serial_message/msg/serial.hpp"
#include "serial_message/msg/serial_array.hpp"
#include "Serial.hpp"

using std::placeholders::_1;

Serial serial; //Serial port instance

class Publisher : public rclcpp::Node{
public:
    inline Publisher();
    inline void publish(uint8_t num);
private:
    inline void send_serial_data(const serial_message::msg::SerialArray::SharedPtr data);
    rclcpp::Publisher<serial_message::msg::Serial>::SharedPtr publisher_;
    rclcpp::Subscription<serial_message::msg::SerialArray>::SharedPtr subscriber_;
};

Publisher::Publisher() : Node("serial1"){
    std::string input_topic;
    std::string output_topic;
    this->declare_parameter<std::string>("Port", "/dev/ttyUSB0");
    this->declare_parameter<std::int64_t>("Baud_Rate", 9600);
    this->declare_parameter<std::string>("Input_Topic", "TxSerial1");
    this->declare_parameter<std::string>("Output_Topic", "RxSerial1");
    this->get_parameter("Output_Topic", output_topic);
    this->get_parameter("Input_Topic", input_topic);
    publisher_ = this->create_publisher<serial_message::msg::Serial>(output_topic, 10);
    subscriber_ = this->create_subscription<serial_message::msg::SerialArray>(input_topic, 10, std::bind(&Publisher::send_serial_data, this, _1));
}

void Publisher::publish(uint8_t num){
    auto message = serial_message::msg::Serial();
    message.data = num;
    publisher_->publish(message);
}

void Publisher::send_serial_data(const serial_message::msg::SerialArray::SharedPtr data){
    RCLCPP_WARN(this->get_logger(), "data");
    
}


int main(int argc, char **argv){
    std::string port_name;
    //Serial serial;
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

    //rclcpp::spin(node);

    while(rclcpp::ok()){
        serial_byte = serial.read1byte();
        node->publish(serial_byte);
        RCLCPP_INFO(node->get_logger(), "published");
        rclcpp::spin_some(node);
    }
    //serial.close();
    rclcpp::shutdown();
    exit(0);
}