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
    struct ConfigurationDoneHandler : Handler {
        ConfigurationDoneHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onConfigurationDone(content);
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
    struct ContinueHandler : Handler {
        ContinueHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onContinue(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };

    struct ThreadHandler : Handler {
        ThreadHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onThreads(content);
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
    struct SetBreakPointtHandler : Handler {
        SetBreakPointtHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onSetBreakPoint(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };
    
    void ProtocolCallbacks::setJsonOutPut(JSONOutput *Out) {
        OutPut= Out;
    }
    int ProtocolCallbacks::getNextSequenceNumber()
    {
        _sequenceNumber++;
        return _sequenceNumber;

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
        Dispatcher.registerHandler("configurationDone", std::make_unique<ConfigurationDoneHandler>( Callbacks));
        Dispatcher.registerHandler("launch", std::make_unique<LaunchHandler>(Callbacks));
        Dispatcher.registerHandler("threads", std::make_unique<ThreadHandler>(Callbacks));
        Dispatcher.registerHandler("continue", std::make_unique<ContinueHandler>(Callbacks));
        Dispatcher.registerHandler("disconnect", std::make_unique<DisconnectHandler>(Callbacks));
        Dispatcher.registerHandler("setBreakpoints", std::make_unique<SetBreakPointtHandler>(Callbacks));
        Callbacks.setJsonOutPut(&Out);
        //virtual void onLaunch(std::string content, JSONOutput &Out) = 0;
    }
};
