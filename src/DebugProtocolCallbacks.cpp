#include "DebugProtocolCallbacks.hpp"
namespace vscode_debug {    
    void DebugProtocolCallbacks::onInitialize(std::string content, JSONOutput &Out){
        //Out.writeMessage("Json de Retonro");
        

    }
    void DebugProtocolCallbacks::onLaunch(std::string ID, JSONOutput &Out) {
    }

}