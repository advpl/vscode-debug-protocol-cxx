#include "ProtocolHandlers.hpp"

namespace vscode_debug {
    struct InitializeHandler : Handler {
        InitializeHandler(JSONOutput &Output, ProtocolCallbacks &Callbacks)
                : Handler(Output), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onInitialize(content, Output);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };
    struct LaunchHandler : Handler {
        LaunchHandler(JSONOutput &Output, ProtocolCallbacks &Callbacks)
                : Handler(Output), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onLaunch(content, Output);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };
    void ProtocolCallbacks::SendErrorResponse(Response response, int id, string format, vector<string>arguments,bool user, bool telemetry)
    {
        
    }

    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out, ProtocolCallbacks &Callbacks) {
        Dispatcher.registerHandler("initialize", std::make_unique<InitializeHandler>(Out, Callbacks));
        Dispatcher.registerHandler("launch", std::make_unique<LaunchHandler>(Out, Callbacks));
        //virtual void onLaunch(std::string content, JSONOutput &Out) = 0;
    }
};
