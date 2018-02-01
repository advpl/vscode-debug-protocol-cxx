#ifndef PROTOCOL_HANDLERS_H
#define PROTOCOL_HANDLERS_H
#include "JSONOutput.hpp"
#include "Handler.hpp"
#include "JSONRPCDispatcher.hpp"
#include <string>
namespace vscode_debug {
    class ProtocolCallbacks {
    public:
      virtual ~ProtocolCallbacks() = default;
    
      virtual void onInitialize(std::string ID, JSONOutput &Out) = 0;
    };

    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out,
        ProtocolCallbacks &Callbacks);

}
#endif