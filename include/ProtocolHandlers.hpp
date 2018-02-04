#ifndef PROTOCOL_HANDLERS_H
#define PROTOCOL_HANDLERS_H
#include "JSONOutput.hpp"
#include "Handler.hpp"
#include "JSONRPCDispatcher.hpp"
#include "Protocol.hpp"
#include <string>
#include <vector>
namespace vscode_debug {
    class ProtocolCallbacks {
    public:
      virtual ~ProtocolCallbacks() = default;
    
      virtual void onInitialize(std::string content, JSONOutput &Out) = 0;
      virtual void onLaunch(std::string content, JSONOutput &Out) = 0;
      void SendErrorResponse(Response response, int id, string format, vector<string>arguments,bool user, bool telemetry);
    };

    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out,
        ProtocolCallbacks &Callbacks);
        
        

}
#endif