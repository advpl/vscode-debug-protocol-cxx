#ifndef DEBUG_PROTOCOL_SERVER_H
#define DEBUG_PROTOCOL_SERVER_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility/string_ref.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "JSONRPCDispatcher.h"
#include "JSONOutput.h"

namespace vscode_debug {
    class DebugProtocolServer {

        public:
             void run (std::istream &input, JSONOutput &Out, JSONRPCDispatcher &Dispatcher);
    };
}
#endif