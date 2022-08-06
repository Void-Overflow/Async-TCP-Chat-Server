#ifndef SERVER_H
#define SERVER_H

#include "session.h"

class server {
private:
	tcp::acceptor acceptor_;

	void do_accept();
public:
	server(boost::asio::io_context& io_context, short port) 
		: acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) 
	{  do_accept(); }
};

#endif
