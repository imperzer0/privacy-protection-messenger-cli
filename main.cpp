#include "call_backend.hpp"

int main(int argc, char** argv)
{
	if (argc == 5)
	{
		std::string address(argv[1]), login(argv[2]), password("nopasswerd"), display_name(argv[3]);
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
		
		display_name += "_Changed";
		cbk.set_display_name(display_name);
		
//		cbk.set_password(password + "+=");
//		cbk.set_password(password);
		
		if (!cbk.begin_session())
			std::cout << "{ERROR} Session was not began!\n";
		
		std::string destuser(argv[4]);
//			std::cout << "\nSend to: ";
//			std::getline(std::cin, destuser);
		bool online;
		if (cbk.check_online_status(online, destuser))
			std::cout << "\"" << destuser << "\" " << (online ? "[online]" : "[offline]") << "\n";
		else
			std::cout << "{ERROR} Online check failed.\n";
		
		std::string message("Mc Lick is already here!!!<br/>svfdb<br/>svdbg");
//			std::cout << "\nText: ";
//			std::getline(std::cin, message);
		
		if (!cbk.send_message(destuser, {message.begin(), message.end()}))
			std::cout << "{ERROR} Sending failed!\n";
		
		std::cout << "Waiting for response...\n\n";
		
		std::vector<uint8_t> response_message;
		if (!cbk.query_incoming(destuser, response_message))
			std::cout << "{ERROR} Failed to receive message.\n";
		
		std::cout << "Received message from \"" << destuser << "\":\n";
		for (auto c: response_message)
			std::cout << c;
		std::cout << "\n";
	}
	else
	{
		std::cout << argv[0] << " client/server\n";
	}
	return 0;
}
