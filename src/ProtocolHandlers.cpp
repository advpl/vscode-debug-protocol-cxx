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

    struct NextHandler : Handler {
        NextHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onNext(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };

    struct StepInHandler : Handler {
        StepInHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onStepInto(content);
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
    
    struct StackTraceHandler : Handler {
        StackTraceHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onStackTrace(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };

    struct ScopeHandler : Handler {
        ScopeHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onScope(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };



    struct VariablesHandler : Handler {
        VariablesHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onVariables(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };

    struct EvaluateHandler : Handler {
        EvaluateHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onEvaluate(content);
        }        
    private:
        ProtocolCallbacks &Callbacks;
    };

    struct SetExceptionBreakpointsHandler : Handler {
            SetExceptionBreakpointsHandler(ProtocolCallbacks &Callbacks)
                    : Handler(), Callbacks(Callbacks) {}

            void handleMethod(std::string content) override {
                Callbacks.onSetExceptionBreakpoints(content);
            }        
        private:
            ProtocolCallbacks &Callbacks;
        };
    struct SourceHandler : Handler {
            SourceHandler(ProtocolCallbacks &Callbacks)
                : Handler(), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onSource(content);
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

    // New handlers for DAP v1.71 -------------------------------------------
#define MAKE_HANDLER(Name, Method) \
    struct Name##Handler : Handler { \
        Name##Handler(ProtocolCallbacks &Callbacks) : Handler(), Callbacks(Callbacks) {} \
        void handleMethod(std::string content) override { Callbacks.Method(content); } \
    private: \
        ProtocolCallbacks &Callbacks; \
    };

    MAKE_HANDLER(Attach, onAttach)
    MAKE_HANDLER(Restart, onRestart)
    MAKE_HANDLER(Terminate, onTerminate)
    MAKE_HANDLER(Cancel, onCancel)
    MAKE_HANDLER(StepOut, onStepOut)
    MAKE_HANDLER(StepBack, onStepBack)
    MAKE_HANDLER(ReverseContinue, onReverseContinue)
    MAKE_HANDLER(RestartFrame, onRestartFrame)
    MAKE_HANDLER(Pause, onPause)
    MAKE_HANDLER(Goto, onGoto)
    MAKE_HANDLER(GotoTargets, onGotoTargets)
    MAKE_HANDLER(SetVariable, onSetVariable)
    MAKE_HANDLER(SetFunctionBreakpoints, onSetFunctionBreakpoints)
    MAKE_HANDLER(DataBreakpointInfo, onDataBreakpointInfo)
    MAKE_HANDLER(SetDataBreakpoints, onSetDataBreakpoints)
    MAKE_HANDLER(BreakpointLocations, onBreakpointLocations)
    MAKE_HANDLER(SetInstructionBreakpoints, onSetInstructionBreakpoints)
    MAKE_HANDLER(ReadMemory, onReadMemory)
    MAKE_HANDLER(WriteMemory, onWriteMemory)
    MAKE_HANDLER(Disassemble, onDisassemble)
    MAKE_HANDLER(Modules, onModules)
    MAKE_HANDLER(LoadedSources, onLoadedSources)
    MAKE_HANDLER(Completions, onCompletions)
    MAKE_HANDLER(ExceptionInfo, onExceptionInfo)

#undef MAKE_HANDLER
    
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
        Dispatcher.registerHandler("next", std::make_unique<NextHandler>(Callbacks));
        Dispatcher.registerHandler("stepIn", std::make_unique<StepInHandler>(Callbacks));
        
        Dispatcher.registerHandler("disconnect", std::make_unique<DisconnectHandler>(Callbacks));
        Dispatcher.registerHandler("setBreakpoints", std::make_unique<SetBreakPointtHandler>(Callbacks));
        Dispatcher.registerHandler("stackTrace", std::make_unique<StackTraceHandler>(Callbacks));
        Dispatcher.registerHandler("scopes", std::make_unique<ScopeHandler>(Callbacks));
        Dispatcher.registerHandler("variables", std::make_unique<VariablesHandler>(Callbacks));
        Dispatcher.registerHandler("evaluate", std::make_unique<EvaluateHandler>(Callbacks));
        Dispatcher.registerHandler("setExceptionBreakpoints", std::make_unique<SetExceptionBreakpointsHandler>(Callbacks));
        Dispatcher.registerHandler("source", std::make_unique<SourceHandler>(Callbacks));

        // New handlers for DAP v1.71
        Dispatcher.registerHandler("attach", std::make_unique<AttachHandler>(Callbacks));
        Dispatcher.registerHandler("restart", std::make_unique<RestartHandler>(Callbacks));
        Dispatcher.registerHandler("terminate", std::make_unique<TerminateHandler>(Callbacks));
        Dispatcher.registerHandler("cancel", std::make_unique<CancelHandler>(Callbacks));
        Dispatcher.registerHandler("stepOut", std::make_unique<StepOutHandler>(Callbacks));
        Dispatcher.registerHandler("stepBack", std::make_unique<StepBackHandler>(Callbacks));
        Dispatcher.registerHandler("reverseContinue", std::make_unique<ReverseContinueHandler>(Callbacks));
        Dispatcher.registerHandler("restartFrame", std::make_unique<RestartFrameHandler>(Callbacks));
        Dispatcher.registerHandler("pause", std::make_unique<PauseHandler>(Callbacks));
        Dispatcher.registerHandler("goto", std::make_unique<GotoHandler>(Callbacks));
        Dispatcher.registerHandler("gotoTargets", std::make_unique<GotoTargetsHandler>(Callbacks));
        Dispatcher.registerHandler("setVariable", std::make_unique<SetVariableHandler>(Callbacks));
        Dispatcher.registerHandler("setFunctionBreakpoints", std::make_unique<SetFunctionBreakpointsHandler>(Callbacks));
        Dispatcher.registerHandler("dataBreakpointInfo", std::make_unique<DataBreakpointInfoHandler>(Callbacks));
        Dispatcher.registerHandler("setDataBreakpoints", std::make_unique<SetDataBreakpointsHandler>(Callbacks));
        Dispatcher.registerHandler("breakpointLocations", std::make_unique<BreakpointLocationsHandler>(Callbacks));
        Dispatcher.registerHandler("setInstructionBreakpoints", std::make_unique<SetInstructionBreakpointsHandler>(Callbacks));
        Dispatcher.registerHandler("readMemory", std::make_unique<ReadMemoryHandler>(Callbacks));
        Dispatcher.registerHandler("writeMemory", std::make_unique<WriteMemoryHandler>(Callbacks));
        Dispatcher.registerHandler("disassemble", std::make_unique<DisassembleHandler>(Callbacks));
        Dispatcher.registerHandler("modules", std::make_unique<ModulesHandler>(Callbacks));
        Dispatcher.registerHandler("loadedSources", std::make_unique<LoadedSourcesHandler>(Callbacks));
        Dispatcher.registerHandler("completions", std::make_unique<CompletionsHandler>(Callbacks));
        Dispatcher.registerHandler("exceptionInfo", std::make_unique<ExceptionInfoHandler>(Callbacks));

        Callbacks.setJsonOutPut(&Out);
    }
};
