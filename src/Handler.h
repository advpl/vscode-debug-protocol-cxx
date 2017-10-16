#ifndef HANDLE_H
#define HANDLE_H

#include <boost/utility/string_ref.hpp>
#include <boost/unordered_map.hpp>
#include <boost/property_tree/ptree.hpp>
#include "Logger.h"
#include "JSONOutput.h"
namespace vscode_debug {
    class Handler {
    public:
      Handler(JSONOutput &Output) : Output(Output) {}
      virtual ~Handler() = default;
    
      /// Called when the server receives a method call. This is supposed to return
      /// a result on Outs. The default implementation returns an "unknown method"
      /// error to the client and logs a warning.
      virtual void handleMethod(boost::property_tree::ptree Params, std::string ID)
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