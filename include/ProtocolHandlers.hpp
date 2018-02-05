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
      ProtocolCallbacks(){};
      void setJsonOutPut(JSONOutput *Out);      
      virtual void onInitialize(std::string content) = 0;
      virtual void onLaunch(std::string content) = 0;
      virtual void onDisconnect(std::string content) = 0;
      void PrepareErrorResponse(Response &response, int id, string format);
      /*void SendErrorResponse(Response response, int id, string format, vector<string>arguments,bool user, bool telemetry);
      void SendErrorResponse(Response response, int id, string format);
      void SendResponse(Response response);
      
      void SendMessage(ProtocolMessage message);*/
      JSONOutput *OutPut;
    };
    
    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out,
        ProtocolCallbacks &Callbacks);
        
        

}
#endif