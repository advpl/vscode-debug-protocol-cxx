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
        DebugProtocolCallbacks():ProtocolCallbacks() {}
        void onInitialize(std::string content)  override;
        void onConfigurationDone(std::string content)  override;
        void onLaunch(std::string content) override ;
        void onContinue(std::string content) override ;
        void onThreads(std::string content) override ;
        void onDisconnect(std::string content) override;
        void onSetBreakPoint(std::string content) override;
        void onStackTrace(std::string content) override;
    };


}
#endif
