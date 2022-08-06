#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>

using namespace boost::asio::ip;

class client {
private:
	#ifdef _WIN32
	#include <Windows.h>

	void enableEscapeCodesForWindows() {
		DWORD consoleMode;
		HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleMode(outputHandle, &consoleMode))
			SetConsoleMode(outputHandle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}

	#else 
	void enableEscapeCodesForWindows() { return; };
	#endif

	tcp::socket client_socket_;
public:
	client(boost::asio::io_service& service, std::string server_addr, short port) : client_socket_(service) { 
		client_socket_.connect(tcp::endpoint(address::from_string(server_addr), port)); 
		enableEscapeCodesForWindows();
	};

	void introduceUser(std::string client_name);

	std::string getData();
	void sendData(const std::string& message);
};

#endif
