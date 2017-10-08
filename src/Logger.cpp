#include "Logger.h"
using namespace vscode_debug;
EmptyLogger &EmptyLogger::getInstance() {
    static EmptyLogger Logger;
    return Logger;
  }
  
  void EmptyLogger::log(const std::string Message) {}
  