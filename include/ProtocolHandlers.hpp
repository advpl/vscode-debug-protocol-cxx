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
      // Pure virtual: existing commands that every adapter must implement
      virtual void onInitialize(std::string content) = 0;
      virtual void onConfigurationDone(std::string content) = 0;
      virtual void onContinue(std::string content) = 0;
      virtual void onNext(std::string content) = 0;
      virtual void onStepInto(std::string content) = 0;
      virtual void onScope(std::string content) = 0;
      virtual void onThreads(std::string content) = 0;
      virtual void onLaunch(std::string content) = 0;
      virtual void onDisconnect(std::string content) = 0;
      virtual void onSetBreakPoint(std::string content) = 0;
      virtual void onStackTrace(std::string content) = 0;
      virtual void onVariables(std::string content) = 0;
      virtual void onEvaluate(std::string content) = 0;
      virtual void onSetExceptionBreakpoints(std::string content) = 0;
      virtual void onSource(std::string content) = 0;

      // New commands — default no-op; override to support
      virtual void onAttach(std::string content) {}
      virtual void onRestart(std::string content) {}
      virtual void onTerminate(std::string content) {}
      virtual void onCancel(std::string content) {}
      virtual void onStepOut(std::string content) {}
      virtual void onStepBack(std::string content) {}
      virtual void onReverseContinue(std::string content) {}
      virtual void onRestartFrame(std::string content) {}
      virtual void onPause(std::string content) {}
      virtual void onGoto(std::string content) {}
      virtual void onGotoTargets(std::string content) {}
      virtual void onSetVariable(std::string content) {}
      virtual void onSetFunctionBreakpoints(std::string content) {}
      virtual void onDataBreakpointInfo(std::string content) {}
      virtual void onSetDataBreakpoints(std::string content) {}
      virtual void onBreakpointLocations(std::string content) {}
      virtual void onSetInstructionBreakpoints(std::string content) {}
      virtual void onReadMemory(std::string content) {}
      virtual void onWriteMemory(std::string content) {}
      virtual void onDisassemble(std::string content) {}
      virtual void onModules(std::string content) {}
      virtual void onLoadedSources(std::string content) {}
      virtual void onCompletions(std::string content) {}
      virtual void onExceptionInfo(std::string content) {}
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