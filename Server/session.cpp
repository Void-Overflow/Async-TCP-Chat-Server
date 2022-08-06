#include "session.h"

#include <vector>

enum { max_length = 1024 };
char data_[max_length];

std::vector<std::pair<std::string, tcp::socket>> clients_; //name, socket

void session::start() {
	clients_.emplace_back(std::make_pair("NULLVALUEFILLERFORSTR" , std::move(socket_)));
	do_read();
}

std::string session::return_clients() {
	std::string msg = "\n---------------\n";

	for (int i = 0; i < clients_.size(); i++)
		msg += clients_.at(i).first + '\n';
	msg += "---------------\n";

	return msg;
}

void session::do_read() {
	auto self(shared_from_this());

	for (int i = 0; i < clients_.size(); i++) {
		clients_.at(i).second.async_read_some(boost::asio::buffer(data_, max_length),
			[&, i,  this, self](boost::system::error_code ec, std::size_t length) {
				if (boost::asio::error::eof == ec || boost::asio::error::connection_reset == ec) { //client disconnect
					std::string msg = "..." + clients_.at(i).first + " has left the chat...\n";
					strcpy_s(data_, msg.c_str());

					do_write(msg.length());
					clients_.erase(clients_.begin() + i);
				}
				else if (!ec) {
					if (clients_.at(i).first == "NULLVALUEFILLERFORSTR") { //client connects
						clients_.at(i).first = std::string(data_); //sets person's name
						clients_.at(i).first.erase( //removes \n from the string
							std::remove(clients_.at(i).first.begin(), clients_.at(i).first.end(), '\n'),
							clients_.at(i).first.cend());

						std::string msg = "..." + clients_.at(i).first + " has joined the chat...\n";
						strcpy_s(data_, msg.c_str());
						do_write(msg.length());
					}
					else { //client sends data
						if (!ec) {
							std::string msg = clients_.at(i).first + " : " + std::string(data_);

							if (std::string(data_) == "!clients\n")
								msg += return_clients();

							strcpy_s(data_, msg.c_str());
							do_write(msg.length());			
						}
					}
				}
		});
	}
}

void session::do_write(std::size_t length) {
	auto self(shared_from_this());

	for (int i = 0; i < clients_.size(); i++) {
		boost::asio::async_write(clients_.at(i).second, boost::asio::buffer(data_, length),
			[&, this, self](boost::system::error_code ec, std::size_t){
				if (!ec) 
					do_read();
		});
	}
	memset(data_, 0, sizeof(data_)); //clears buffer
}
