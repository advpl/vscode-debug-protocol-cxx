#include "DebugProtocolCallbacks.hpp"
namespace vscode_debug {    
    void DebugProtocolCallbacks::onInitialize(std::string content){
        //Out.writeMessage("Json de Retonro");
        

    }
    void DebugProtocolCallbacks::onConfigurationDone(std::string ID) {
    }
    void DebugProtocolCallbacks::onLaunch(std::string ID) {
    }
    void DebugProtocolCallbacks::onContinue(std::string ID) {
    }
    void DebugProtocolCallbacks::onDisconnect(std::string content) {

    }
    void DebugProtocolCallbacks::onSetBreakPoint(std::string content)
    {
        
    }
    void DebugProtocolCallbacks::onThreads(std::string content) {
        
    }
    void DebugProtocolCallbacks::onStackTrace(std::string content)
    {
        
    }
    void DebugProtocolCallbacks::onNext(std::string content)
    {

    }
    void DebugProtocolCallbacks::onStepInto(std::string content)
    {
        
    }
    void DebugProtocolCallbacks::onScope(std::string content)
    {
        
    }
    void DebugProtocolCallbacks::onVariables(std::string content)
    {
        
    }
    void DebugProtocolCallbacks::onEvaluate(std::string content)
    {
        
    }
    void DebugProtocolCallbacks::onSetExceptionBreakpoints(std::string content)
    {
        
    }
    
}