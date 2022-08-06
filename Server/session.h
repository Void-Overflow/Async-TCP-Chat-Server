#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
private:
	tcp::socket socket_;

	std::string return_clients();

	void do_write(std::size_t length);
	void do_read();
public:
	session(tcp::socket socket) : socket_(std::move(socket)) {}

	void start();
};

#endif
