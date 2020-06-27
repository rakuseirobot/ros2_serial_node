#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "serial_message/msg/serial.hpp"
#include "serial_message/msg/serial_array.hpp"

using std::placeholders::_1;

class Subscriber : public rclcpp::Node {
public:
    inline Subscriber();
private:
    inline void ShowMessage(serial_message::msg::Serial::SharedPtr data);
    rclcpp::Subscription<serial_message::msg::Serial>::SharedPtr subscriber_;
};

Subscriber::Subscriber() : Node("serial_sub1"){
    std::string input_topic;
    this->declare_parameter<std::string>("input_topic", "RxSerial1");
    this->get_parameter("input_topic", input_topic);
    subscriber_ = this->create_subscription<serial_message::msg::Serial>(input_topic, 10, std::bind(&Subscriber::ShowMessage, this , _1));
}

void Subscriber::ShowMessage(serial_message::msg::Serial::SharedPtr data){
    std::cout << std::hex <<static_cast<int>(data->data) << " ";
}

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Subscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    exit(0);
}