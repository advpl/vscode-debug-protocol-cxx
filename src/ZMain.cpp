#include "DebugProtocolServer.h"
#include "DebugProtocolCallbacks.h"
#include "ProtocolHandlers.h"
#include <fcntl.h>
#include <io.h>
int main()
{
	int result = _setmode( _fileno( stdout ), _O_BINARY );
	vscode_debug::DebugProtocolServer server;
	vscode_debug::JSONOutput Out(std::cout, std::cerr);
	vscode_debug::JSONRPCDispatcher Dispatcher(std::make_unique<vscode_debug::Handler>(Out));	
	vscode_debug::DebugProtocolCallbacks Callbacks(server);
	vscode_debug::regiterCallbackHandlers(Dispatcher,Out,Callbacks);
	server.run(std::cin,Out,Dispatcher);
	return 0;
}
