#include "JSONRPCDispatcher.h"
namespace vscode_debug {
void JSONRPCDispatcher::registerHandler(std::string Method, std::unique_ptr<Handler> H) {
//assert(!Handlers.count(Method) && "Handler already registered!");
    Handlers[Method] = std::move(H);
}

}