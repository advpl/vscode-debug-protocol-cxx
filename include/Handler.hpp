#ifndef HANDLE_H
#define HANDLE_H

#include <boost/utility/string_ref.hpp>
#include <boost/unordered_map.hpp>
//#include <boost/property_tree/ptree.hpp>
#include "json.hpp"
#include "Logger.hpp"
#include "JSONOutput.hpp"
using Json = nlohmann::json;
namespace vscode_debug {
    class Handler {
    public:
      Handler(JSONOutput &Output) : Output(Output) {}
      virtual ~Handler() = default;
    
      /// Called when the server receives a method call. This is supposed to return
      /// a result on Outs. The default implementation returns an "unknown method"
      /// error to the client and logs a warning.
      virtual void handleMethod(Json Params, std::string ID)
      {

      }
      /// Called when the server receives a notification. No result should be
      /// written to Outs. The default implemetation logs a warning.
      //virtual void handleNotification(llvm::yaml::MappingNode *Params);
    
    protected:
      JSONOutput &Output;
    
      /// Helper to write a JSONRPC result to Output.
      void writeMessage(const std::string &Message) { 
          Output.writeMessage(Message);
         }
    };
}
#endif