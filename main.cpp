#include "call_backend.hpp"

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		if (!::strcasecmp(argv[1], "client")) // client
		{
			std::string address("127.0.0.1"), login("test"), password("nopasswerd"), display_name("Test");
//			std::cout << "Address: ";
//			std::getline(std::cin, address);
//			std::cout << "\nLogin: ";
//			std::getline(std::cin, login);
//			std::cout << "Password: ";
//			std::getline(std::cin, password);
			
			call_backend cbk(address, login, password);

//			std::string y_n;
//			std::cout << "\nRegister? [y/N]:";
//			std::getline(std::cin, y_n);
//			if (y_n == "y" || y_n == "Y")
			{
				std::cout << "Registering...\n";
				cbk.register_user(display_name);
			}
			
			cbk.begin_session();
			
			std::string destuser;
			std::cout << "\nSend to: ";
			std::getline(std::cin, destuser);
			
			std::cout << "\"" << destuser << "\" " << (cbk.check_online_status(destuser) == "1" ? "[online]" : "[offline]") << "\n";
			
			std::string message;
			std::cout << "\nText: ";
			std::getline(std::cin, message);
			
			cbk.send_message(destuser, {message.begin(), message.end()});
			
			std::cout << "Waiting for response...\n\n";
			
			auto response_message = cbk.query_incoming(destuser);
			std::cout << "Received from \"" << destuser << "\" message:\n";
			for (auto c: response_message)
				std::cout << c;
			std::cout << "\n";
			
			cbk.end_session();
		}
		else // server
		{
			char* args[]{backend, "-m", "server", "-a", PLACEHOLDER, "-c", PLACEHOLDER, nullptr};
			
			std::string address, max_connections;
			
			std::cout << "Address: ";
			std::getline(std::cin, address);
			args[4] = address.data();
			
			std::cout << "\n"
						 "Max connections simultaneously: ";
			std::getline(std::cin, max_connections);
			args[6] = max_connections.data();
			
			pid_t pid = exec::execute_program(args, nullptr);
			return exec::wait_for_program(pid);
		}
	}
	else
	{
		std::cout << argv[0] << " client/server\n";
	}
	return 0;
}
