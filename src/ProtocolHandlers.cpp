#include "ProtocolHandlers.hpp"

namespace vscode_debug {
    struct InitializeHandler : Handler {
        InitializeHandler(JSONOutput &Output, ProtocolCallbacks &Callbacks)
                : Handler(Output), Callbacks(Callbacks) {}

        void handleMethod(std::string content) override {
            Callbacks.onInitialize(content, Output);
        }
        /* void handleMethod(llvm::yaml::MappingNode *Params, StringRef ID) override {
           Callbacks.onInitialize(ID, Output);
         }*/

    private:
        ProtocolCallbacks &Callbacks;
    };

    void registerCallbackHandlers(JSONRPCDispatcher &Dispatcher, JSONOutput &Out, ProtocolCallbacks &Callbacks) {
        Dispatcher.registerHandler("initialize", std::make_unique<InitializeHandler>(Out, Callbacks));
    }
};
