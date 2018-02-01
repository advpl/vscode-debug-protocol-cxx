/*#include "JSONOutput.h"
namespace vscode_debug {    
    void JSONOutput::writeMessage(const std::string &Message) {
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
*/
#include "JSONOutput.hpp"
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
  // Outs << "Content-Length: " << M.size() << "\r\n\r\n" << M;
  Outs << this->createJsonRpc(Message);
  Outs.flush();
}

void JSONOutput::writeMessage(const nlohmann::json &j) {
  this->writeMessage(j.dump());
}

std::string JSONOutput::createJsonRpc(const std::string &Message) {
  return "Content-Length: " + std::to_string(Message.size()) + "\r\n\r\n" + Message;
}

std::string JSONOutput::createJsonRpc(const nlohmann::json &j) {
  return this->createJsonRpc(j.dump());
}

void JSONOutput::log(const std::string Message) {
  std::lock_guard<std::mutex> Guard(StreamMutex);
  Logs << Message;
  Logs.flush();
}

/*
 * ShowMessage Notification
 *
 * method: ‘window/showMessage’
 * params: ShowMessageParams
 *
 * The show message notification is sent from a server to a client to ask the client to display a particular message
 * in the user interface.
 *
 * https://microsoft.github.io/language-server-protocol/specification#window_showMessage
 *
 */
void JSONOutput::showMessage(int status, const std::string &Message) {
  this->writeMessage(
      nlohmann::json({
                         {"jsonrpc", "2.0"},
                         {"method", "window/showMessage"},
                         {"params", {
                             {"type", status},
                             {"message", Message}
                         }}
                     })
  );
}
void JSONOutput::showErrorMessage(const std::string &Message) { this->showMessage(1, Message); }
void JSONOutput::showWarningMessage(const std::string &Message) { this->showMessage(2, Message); }
void JSONOutput::showInfoMessage(const std::string &Message) { this->showMessage(3, Message); }
void JSONOutput::showLogMessage(const std::string &Message) { this->showMessage(4, Message); }

/*
 * LogMessage Notification
 *
 * method: ‘window/logMessage’
 * params: LogMessageParams
 *
 * The log message notification is sent from the server to the client to ask the client to log a particular message.
 *
 * https://microsoft.github.io/language-server-protocol/specification#window_logMessage
 *
 */
void JSONOutput::logMessage(int status, const std::string &Message) {
  this->writeMessage(
      nlohmann::json({
                         {"jsonrpc", "2.0"},
                         {"method", "window/logMessage"},
                         {"params", {
                             {"type", status},
                             {"message", Message}
                         }}
                     })
  );
}
void JSONOutput::logErrorMessage(const std::string &Message) { this->logMessage(1, Message); }
void JSONOutput::logWarningMessage(const std::string &Message) { this->logMessage(2, Message); }
void JSONOutput::logInfoMessage(const std::string &Message) { this->logMessage(3, Message); }

}  // namespace advpl_ls