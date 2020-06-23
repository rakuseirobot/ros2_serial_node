#include <chrono>
#include <thread>
#include <iostream>
#include <boost/asio.hpp>

int main(void){
  boost::asio::io_service io;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  // ポートは /dev/ttyACM0
  boost::asio::serial_port serial(io, "/dev/ttyUSB0");
  // 速度は 9600bps
  serial.set_option(boost::asio::serial_port_base::baud_rate(9600));

  // テキトウに5秒待つ
  //std::this_thread::sleep_for(std::chrono::seconds(5));

  // "ping" を送信
  //boost::asio::write(serial, boost::asio::buffer("ping\n"));

  // serial から response_buf に '\n' まで読み込む
  boost::asio::streambuf response_buf;
  while(true){
    response_buf.consume(120);
  //boost::asio::read_until(serial, response_buf, '\n');
    boost::asio::read(serial, response_buf, boost::asio::transfer_exactly(1));

  // 表示して終わり
    //std::cout << 0+boost::asio::buffer_cast<const unsigned char*>(response_buf.data())[0] << std::endl;
    for(int i = 0; i < 1; i++){
      std::cout << std::hex << 0+boost::asio::buffer_cast<const unsigned char*>(response_buf.data())[i] << " ";
    }
    //std::cout << std::endl;
  }
  return 0;
}