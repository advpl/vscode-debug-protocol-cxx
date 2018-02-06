#include "DebugProtocolServer.hpp"
#include "DebugProtocolCallbacks.hpp"
#include "ProtocolHandlers.hpp"
#include "json.hpp"
#include <fcntl.h>

int main()
{
	//vscode_debug::DebugProtocolServer server;
	vscode_debug::JSONOutput Out(std::cout, std::cerr);
	vscode_debug::JSONRPCDispatcher Dispatcher(std::make_unique<vscode_debug::Handler>());	
	vscode_debug::DebugProtocolCallbacks Callbacks;
	vscode_debug::registerCallbackHandlers(Dispatcher,Out,Callbacks);
	vscode_debug::run(std::cin,Out,Dispatcher,Callbacks.IsDone);
	

	return 0;
}
