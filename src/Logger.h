#ifndef LOGGER_H
#define LOGGER_H
#include <string>
namespace vscode_debug {

class Logger {
public:
  virtual ~Logger() = default;

  /// Implementations of this method must be thread-safe.
  virtual void log(const std::string Message)=0;
};

/// Logger implementation that ignores all messages.
class EmptyLogger : public Logger {
public:
  static EmptyLogger &getInstance();

  void log(const std::string Message) override;

private:
  EmptyLogger() = default;
};

}

#endif
