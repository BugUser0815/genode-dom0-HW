#pragma once

#include <base/heap.h>

//#include "tcp_socket.h"
//#include <taskloader/taskloader_connection.h>
//#include <parser/parser_connection.h>
#include <timer_session/connection.h>
//#include "sched_controller_session/connection.h"



/*extern "C" {
#include <lwip/stats.h>
}*/

#include <util/xml_node.h>

extern "C" {
#include <lwip/sockets.h>
#include <lwip/api.h>
}

#define NETCHECK_LOOP(x)\
	if(x<1)\
	{ \
		PINF("Connection terminated. Waiting for new connection.\n");\
		break;\
	}

// Get XML node attribute if it exists and copy default if not.
bool attribute_value(const Genode::Xml_node& config_node, const char* type, char* dst, const char* default_val, size_t max_len);

namespace Dom0_server{

class Dom0_server// : public Tcp_socket
{
private:
	Genode::Env &env;

	int target_socket {};
	struct sockaddr_in _target_sockaddr_in {};

	int _listen_socket {};
	struct sockaddr_in _in_addr {};
	sockaddr _target_addr {};
	//Taskloader_connection _task_loader {};
	//Parser_connection _parser {};
	//Timer::Connection timer;
	//Sched_controller::Connection _controller {};

	ssize_t receive_data(void* data, size_t size, int _target_socket);
	ssize_t receiveInt32_t(Genode::int32_t& data, int _target_socket);
	ssize_t send_data(void* data, size_t size, int _target_socket);
	ssize_t sendInt32_t(Genode::int32_t data, int _target_socket);

public:
	Dom0_server(Genode::Env&);

	~Dom0_server();

	int connect(Genode::Env&);

	void serve(Genode::Env&);

	void disconnect();

	void start();

	void send_profile(Genode::String<32> task_name);


};
}
