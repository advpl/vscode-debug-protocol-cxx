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
      //Handler(JSONOutput &Output) : Output(Output) {}
      virtual ~Handler() = default;
    
      /// Called when the server receives a method call. This is supposed to return
      /// a result on Outs. The default implementation returns an "unknown method"
      /// error to the client and logs a warning.
      virtual void handleMethod(std::string content)
      {

      }
      /// Called when the server receives a notification. No result should be
      /// written to Outs. The default implemetation logs a warning.
      //virtual void handleNotification(llvm::yaml::MappingNode *Params);
    };
}
#endif