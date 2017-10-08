#include "JSONOutput.h"
namespace vscode_debug {    
    void JSONOutput::writeMessage(const std::string &Message) {
        /*llvm::SmallString<128> Storage;
        StringRef M = Message.toStringRef(Storage);
      
        std::lock_guard<std::mutex> Guard(StreamMutex);
        // Log without headers.
        Logs << "--> " << M << '\n';
        Logs.flush();
      */
        // Emit message with header.
        Outs << "Content-Length: " << Message.size() << "\r\n\r\n" << Message;
        Outs.flush();
      }
      
      void JSONOutput::log(const std::string Message) {
        std::lock_guard<std::mutex> Guard(StreamMutex);
        Logs << Message;
        Logs.flush();
      }


}