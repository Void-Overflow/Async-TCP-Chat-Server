#include "client.h"

void client::introduceUser(std::string client_name) {
	sendData(client_name);
}

std::string client::getData(){
	boost::asio::streambuf buf;
	read_until(client_socket_, buf, "\n");

	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	return data;
}

void client::sendData(const std::string& message){
	boost::asio::write(client_socket_, boost::asio::buffer(message + "\n"));
}
