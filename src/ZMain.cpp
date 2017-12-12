#include "DebugProtocolServer.h"
#include "DebugProtocolCallbacks.h"
#include "ProtocolHandlers.h"
#include "json.hpp"

int main()
{
	
	/*json saida;
	saida["supportsConfigurationDoneRequest"] = true;
	std::cout << saida.dump();*/

	vscode_debug::DebugProtocolServer server;

	vscode_debug::JSONOutput Out(std::cout, std::cerr);
	vscode_debug::JSONRPCDispatcher Dispatcher(std::make_unique<vscode_debug::Handler>(Out));	
	vscode_debug::DebugProtocolCallbacks Callbacks(server);
	vscode_debug::regiterCallbackHandlers(Dispatcher,Out,Callbacks);
	server.run(std::cin,Out,Dispatcher);

	return 0;
}
