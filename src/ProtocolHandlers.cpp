#include "ProtocolHandlers.h"

namespace vscode_debug {
    struct InitializeHandler : Handler {
        InitializeHandler(JSONOutput &Output, ProtocolCallbacks &Callbacks)
            : Handler(Output), Callbacks(Callbacks) {}
            void handleMethod(boost::property_tree::ptree Params, std::string ID) override {
              Callbacks.onInitialize(ID, Output);
            }
       /* void handleMethod(llvm::yaml::MappingNode *Params, StringRef ID) override {
          Callbacks.onInitialize(ID, Output);
        }*/
      
      private:
        ProtocolCallbacks &Callbacks;
      };
void vscode_debug::regiterCallbackHandlers(JSONRPCDispatcher &Dispatcher,JSONOutput &Out, ProtocolCallbacks &Callbacks) {
     Dispatcher.registerHandler("initialize", std::make_unique<InitializeHandler>(Out, Callbacks));
    }
}