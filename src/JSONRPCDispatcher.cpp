#include "JSONRPCDispatcher.h"
namespace vscode_debug {
void JSONRPCDispatcher::registerHandler(std::string Method, std::unique_ptr<Handler> H) {
//assert(!Handlers.count(Method) && "Handler already registered!");
    Handlers[Method] = std::move(H);
}
    bool JSONRPCDispatcher::call(boost::string_ref Content) const
    {
        std::stringstream ss;
        ss << Content;
      
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);

        std::string method = pt.get<std::string>("type");

        return true;

    }
}