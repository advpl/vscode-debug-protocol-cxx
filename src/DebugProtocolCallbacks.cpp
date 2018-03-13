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
}