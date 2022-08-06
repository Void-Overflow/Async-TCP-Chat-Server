#include "server.h"

int main() {
	boost::asio::io_context io_context;
	server s(io_context, 9999); //server on port 9999
	io_context.run();

	return 0;
}
