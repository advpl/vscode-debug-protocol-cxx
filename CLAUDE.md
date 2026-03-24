# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

C++ library implementing the [VS Code Debug Adapter Protocol](https://microsoft.github.io/debug-adapter-protocol/). It provides a server that reads DAP messages from stdin, parses JSON-RPC, and dispatches to registered handler objects. It is consumed by a separate debugger adapter (the ADVPL debug bridge).

## Build

**Requirements:** Boost (installed at `/opt/boost` on Linux), CMake 3.0+, C++14 compiler.

```bash
mkdir build && cd build
cmake ..
make
```

**Run tests:**
```bash
cd build
ctest
# or run directly:
./test/debug-protocol-test
```

**Node.js mock client** (in `node_mock_client/`):
```bash
npm install
npm run build
```

## Architecture

The library is structured around a read loop in `DebugProtocolServer` that:

1. Reads HTTP-style headers from stdin (`Content-Length: N\r\n\r\n`)
2. Reads `N` bytes of JSON body
3. Passes the JSON to `JSONRPCDispatcher`, which routes by `command` field to the matching `Handler`
4. Handlers call back into `ProtocolCallbacks` (abstract interface) — the consumer implements this interface to respond to debug events
5. Responses and events are written back via `JSONOutput`, which formats messages with proper `Content-Length` headers and uses a mutex for thread safety

**Key files:**
- `include/Protocol.hpp` — All DAP message types (Request, Response, Event, and their typed subclasses) with nlohmann/json serialization
- `src/Protocol.cpp` — JSON serialization/deserialization implementations
- `include/ProtocolHandlers.hpp` / `src/ProtocolHandlers.cpp` — Handler registration, the `ProtocolCallbacks` abstract interface, and handler dispatch
- `include/DebugProtocolServer.hpp` / `src/DebugProtocolServer.cpp` — stdin read loop
- `include/JSONOutput.hpp` / `src/JSONOutput.cpp` — Thread-safe output formatting
- `include/json.hpp` — Bundled nlohmann/json (header-only, do not modify)

**Adding a new DAP command:**
1. Add message types to `Protocol.hpp` and their serialization to `Protocol.cpp`
2. Create a `Handler` subclass in `ProtocolHandlers.hpp`/`.cpp`
3. Add a virtual method to `ProtocolCallbacks` and register the handler in `ProtocolHandlers.cpp`

## Platform Notes

- Linux: Boost expected at `/opt/boost`
- Windows: Boost expected at `C:/local/boost_1_74_0`
- macOS: Requires OpenSSL and Iconv in addition to Boost
- The `BOOST_ROOT`/`BOOST_INCLUDEDIR`/`BOOST_LIBRARYDIR` CMake variables can be set externally to override defaults
