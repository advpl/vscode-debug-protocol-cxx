#include "DebugProtocolCallbacks.h"
namespace vscode_debug {    
    void DebugProtocolCallbacks::onInitialize(std::string ID, JSONOutput &Out){
        Out.writeMessage("Json de Retonro");
        

    }

}