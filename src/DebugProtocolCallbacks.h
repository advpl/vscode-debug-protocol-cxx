#ifndef DEBUG_PROTOCOL_CALL_BACKS_H
#define DEBUG_PROTOCOL_CALL_BACKS_H
#include "ProtocolHandlers.h"
#include "DebugProtocolServer.h"
namespace vscode_debug 
{
    class DebugProtocolCallbacks : public ProtocolCallbacks 
    {
    public:
        DebugProtocolCallbacks (DebugProtocolServer &LangServer): LangServer(LangServer) {}
        
        void onInitialize(std::string ID, JSONOutput &Out)  override;


    private:
        DebugProtocolServer &LangServer;
    };


}
#endif
