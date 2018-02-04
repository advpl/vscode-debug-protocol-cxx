#ifndef DEBUG_PROTOCOL_CALL_BACKS_H
#define DEBUG_PROTOCOL_CALL_BACKS_H
#include "ProtocolHandlers.hpp"
#include "DebugProtocolServer.hpp"
//#include <boost/property_tree/ptree.hpp>

namespace vscode_debug 
{
    
    class DebugProtocolCallbacks : public ProtocolCallbacks 
    {
    public:
        DebugProtocolCallbacks (DebugProtocolServer &LangServer): LangServer(LangServer) {}
        
        void onInitialize(std::string ID, JSONOutput &Out)  override;
        void onLaunch(std::string ID, JSONOutput &Out) override ;

    private:
        DebugProtocolServer &LangServer;
    };


}
#endif
