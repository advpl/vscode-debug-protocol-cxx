#include "JSONRPCDispatcher.h"
namespace vscode_debug {
void JSONRPCDispatcher::registerHandler(std::string method, std::unique_ptr<Handler> H) {
//assert(!Handlers.count(Method) && "Handler already registered!");
    Handlers[method] = std::move(H);
}
    static void  callHandler(std::unique_ptr<Handler> &handle,boost::property_tree::ptree pt)
    {
        handle->handleMethod(pt,"funciona");
    }    
    
    bool JSONRPCDispatcher::call(boost::string_ref Content) 
    {
        std::stringstream ss;
        ss << Content;
      
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        
        std::string method = pt.get<std::string>("command");
        MapHandler::iterator it = Handlers.find(method);
        //std::unordered_map<std::string, std::unique_ptr<Handler> > ::iterator it;
        it = Handlers.find(method);
        
        if(it != Handlers.end() )
        {
            callHandler(it->second ,pt);
        }
        
        return true;

    }
    
}