#include <iostream>
#include <thread>

#include "client.h"

boost::asio::io_service io_service;
client usr(io_service, "SERVER_IP", 9999); //service, server ip, port

void readServer() {
    while (true) {
		std::string response = usr.getData(); //thread reads incoming data from server
		response.pop_back();

		if (response != "")
			std::cout << '\n' << response << '\n';
    }
}

int main(){
    std::cout << "Enter your name: ";

    std::string u_name;
    std::getline(std::cin, u_name);
	usr.introduceUser(u_name);

    std::thread thread_obj(readServer);
    thread_obj.detach();

	while (true) {
		std::string reply;
		std::getline(std::cin, reply);

		std::cout << "\033[A"; //moves up a line
		std::cout << "\33[2K"; //deletes line entered by cin -- the same message will be replaced by the server

		if (reply != "") 
			usr.sendData(reply);	
    }
    return 0;
}
