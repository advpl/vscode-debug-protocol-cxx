#ifndef JSONRPCDISPATCHER_H
#define JSONRPCDISPATCHER_H

#include <boost/utility/string_ref.hpp>
//#include <boost/unordered_map.hpp>
#include <unordered_map>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include "JSONOutput.hpp"
#include "Handler.hpp"
namespace vscode_debug {

typedef std::unordered_map<std::string, std::unique_ptr<Handler> > MapHandler;
// Main JSONRPC entry point. This parses the JSONRPC "header" and calls the
/// registered Handler for the method received.
class JSONRPCDispatcher {
public:
  /// Create a new JSONRPCDispatcher. UnknownHandler is called when an unknown
  /// method is received.
  JSONRPCDispatcher(std::unique_ptr<Handler> UnknownHandler)
      : UnknownHandler(std::move(UnknownHandler)) {        
      }

  /// Registers a Handler for the specified Method.
  void registerHandler(std::string Method, std::unique_ptr<Handler> H);

  /// Parses a JSONRPC message and calls the Handler for it.
  bool call(boost::string_ref Content) ;

private:
  MapHandler Handlers;
  std::unique_ptr<Handler> UnknownHandler;
};
}
#endif