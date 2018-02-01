#ifndef LOGGER_H
#define LOGGER_H
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <string>
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace vscode_debug {

static std::string CreateFormat() {
  logging::add_common_attributes();
  logging::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
  return "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%";
}
static void init_log() {
  logging::add_file_log
      (
          keywords::file_name = "log_%N.log",
          keywords::rotation_size = 10 * 1024 * 1024,
          keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),

          keywords::format = CreateFormat()
      );

}
static void log_info(std::string msg) {
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;
  BOOST_LOG_SEV(lg, info) << msg;

}
static void log_error(std::string msg) {
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;
  BOOST_LOG_SEV(lg, error) << msg;

}

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

class FileLogger : public Logger {
 public:
  static FileLogger &getInstance();

  void log(const std::string Message) override;

 private:
  FileLogger() = default;
};

}

#endif
