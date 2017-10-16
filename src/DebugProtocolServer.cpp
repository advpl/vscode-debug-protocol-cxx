#include "DebugProtocolServer.h"

namespace vscode_debug {
	void DebugProtocolServer::run (std::istream &input, JSONOutput &Out, JSONRPCDispatcher &Dispatcher)
	{	 
		
		
		//Se precisar esperar pelo debug
		using namespace boost::algorithm;
		/*using namespace std::chrono_literals;
		auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(10s);
		auto end = std::chrono::high_resolution_clock::now();*/
		while (input.good()) {
			// A Debug Protocol message starts with a set of HTTP headers,
			// delimited  by \r\n, and terminated by an empty line (\r\n).
			unsigned long long ContentLength = 0;
			while (input.good()) {
			std::string Line;
			std::getline(input, Line);		  
			if (!input.good() && errno == EINTR) {
					input.clear();
					continue;
			}
			if (starts_with(Line,"Content-Length: ")) {
					Line = erase_head_copy(Line,16);
					trim(Line);
					ContentLength = boost::lexical_cast<long>(Line);
					continue;
			}
			else 
			{
				trim(Line);   
				if(!empty(Line))
				{
					continue;   // It's another header, ignore it.
				}
				else
				{
					break;
				}
				
			}
			}
			if (ContentLength > 0) {
				// Now read the JSON.
				std::vector<char> JSON(ContentLength);
				input.read(JSON.data(), ContentLength);
				if (!input) {
					/*Out.log("Input was aborted. Read only "
							+ std::to_string(In.gcount())
							+ " bytes of expected "
							+ std::to_string(ContentLength)
							+ ".\n");*/
					break;
				}
				boost::string_ref JSONRef(JSON.data(), ContentLength);
				if (!Dispatcher.call(JSONRef))
					Out.log("JSON dispatch failed!\n");

			}
		}
	}
}
