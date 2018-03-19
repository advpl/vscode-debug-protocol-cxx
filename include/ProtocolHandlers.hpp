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
      bool IsDone;
      int _sequenceNumber = 1;
      ProtocolCallbacks():IsDone(false){};
      void setJsonOutPut(JSONOutput *Out);      
      virtual void onInitialize(std::string content) = 0;
      virtual void onConfigurationDone(std::string content) = 0  ;
      virtual void onContinue(std::string content) = 0;
      virtual void onNext(std::string content) = 0;
      virtual void onStepInto(std::string content) = 0;
      virtual void onScope(std::string content) = 0;
      virtual void onThreads(std::string content) = 0 ;      
      virtual void onLaunch(std::string content) = 0;
      virtual void onDisconnect(std::string content) = 0;
      virtual void onSetBreakPoint(std::string content) =0;
      virtual void onStackTrace(std::string content) = 0 ;
      void PrepareErrorResponse(Response &response, int id, string format);
      /*void SendErrorResponse(Response response, int id, string format, vector<string>arguments,bool user, bool telemetry);
      void SendErrorResponse(Response response, int id, string format);
      void SendResponse(Response response);
      
      void SendMessage(ProtocolMessage message);*/
      JSONOutput *OutPut;
      int getNextSequenceNumber();
    };
    
        
    
    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out,
        ProtocolCallbacks &Callbacks);
        
        

}
#endif