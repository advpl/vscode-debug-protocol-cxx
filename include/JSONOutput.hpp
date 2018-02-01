#ifndef JSONOUTPUT_H
#define JSONOUTPUT_H

#include <iostream>
#include <mutex>
#include "Logger.hpp"
#include "json.hpp"
namespace vscode_debug {
class JSONOutput : public Logger {
     public:
  JSONOutput(std::ostream &Outs, std::ostream &Logs)
      : Outs(Outs), Logs(Logs) {}

  /// Emit a JSONRPC message.
  void writeMessage(const std::string &Message);
  void writeMessage(const nlohmann::json &j);

  std::string createJsonRpc(const std::string &Message);
  std::string createJsonRpc(const nlohmann::json &j);

  /// Write to the logging stream.
  void log(const std::string Message) override;

  /// Show message method
  void showMessage(int status, const std::string &Message);
  void showErrorMessage(const std::string &Message);
  void showWarningMessage(const std::string &Message);
  void showInfoMessage(const std::string &Message);
  void showLogMessage(const std::string &Message);

  /// Log message method
  void logMessage(int status, const std::string &Message);
  void logErrorMessage(const std::string &Message);
  void logWarningMessage(const std::string &Message);
  void logInfoMessage(const std::string &Message);

 private:
  std::ostream &Outs;
  std::ostream &Logs;

  std::mutex StreamMutex;
};
}
#endif