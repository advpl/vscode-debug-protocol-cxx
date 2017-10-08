#ifndef JSONOUTPUT_H
#define JSONOUTPUT_H

#include <iostream>
#include <mutex>
#include "Logger.h"
namespace vscode_debug {
    class JSONOutput : public Logger {

    public:
        JSONOutput(std::ostream &Outs, std::ostream &Logs)
            : Outs(Outs), Logs(Logs) {}
      
        /// Emit a JSONRPC message.
        void writeMessage(const std::string &Message);
      
        /// Write to the logging stream.        
        void log(const std::string Message) override;      
    
    private:
        std::ostream &Outs;
        std::ostream &Logs;
    
        std::mutex StreamMutex;
    };
}
#endif