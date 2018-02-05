#include "ProtocolHandlers.hpp"

namespace vscode_debug {
    struct InitializeHandler : Handler {
        InitializeHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onInitialize(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };
    struct LaunchHandler : Handler {
        LaunchHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onLaunch(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };
    struct DisconnectHandler : Handler {
        DisconnectHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onDisconnect(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };

    
    void ProtocolCallbacks::setJsonOutPut(JSONOutput *Out) {
        OutPut= Out;
    }
  /*  void ProtocolCallbacks::SendResponse(Response response)
    {
        Json j = response;
        OutPut->writeMessage(j.dump());
    }
    void ProtocolCallbacks::SendMessage(ProtocolMessage message)
    {
        message.seq = _sequenceNumber++;
        Json j = message;
        OutPut->writeMessage(j.dump());
    }*/
    /*void ProtocolCallbacks::PrepareErrorResponse(Response &response, int id, string format, vector<string>arguments,bool user, bool telemetry)
    {
        Message msg(id, format, arguments, user, telemetry);
        string message ="Utilities.ExpandVariables(msg.format, msg.variables)";
        ErrorResponseBody erb(msg);
        response.SetErrorBody(message,erb);        
    }*/
    void ProtocolCallbacks::PrepareErrorResponse(Response &response, int id, string format)
    {
        Message msg(id, format);
        ErrorResponseBody erb(msg);
        response.SetErrorBody(format,erb);     
    }

    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out, ProtocolCallbacks &Callbacks) {
        Dispatcher.registerHandler("initialize", std::make_unique<InitializeHandler>( Callbacks));
        Dispatcher.registerHandler("launch", std::make_unique<LaunchHandler>(Callbacks));
        Dispatcher.registerHandler("disconnect", std::make_unique<DisconnectHandler>(Callbacks));
        Callbacks.setJsonOutPut(&Out);
        //virtual void onLaunch(std::string content, JSONOutput &Out) = 0;
    }
};
