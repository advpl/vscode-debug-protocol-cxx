#include "JSONRPCDispatcher.hpp"
namespace vscode_debug {
void JSONRPCDispatcher::registerHandler(std::string method, std::unique_ptr<Handler> H) {
//assert(!Handlers.count(Method) && "Handler already registered!");
    Handlers[method] = std::move(H);
}
    static void callHandler(std::unique_ptr<Handler> &handle,std::string Content)
    {
        handle->handleMethod(Content);
    }    
    
    bool JSONRPCDispatcher::call(boost::string_ref Content) 
    {
        std::stringstream ss;
        ss << Content;
      
        //boost::property_tree::ptree pt;
        //boost::property_tree::read_json(ss, pt);
        Json request = Json::parse(ss.str());
        std::string method = request["command"];
        //std::string method = pt.get<std::string>("command");
        MapHandler::iterator it = Handlers.find(method);
        //std::unordered_map<std::string, std::unique_ptr<Handler> > ::iterator it;
        it = Handlers.find(method);
        
        if(it != Handlers.end() )
        {
            callHandler(it->second ,ss.str());
        }
        
        return true;

    }
    
}