#include "ConsoleImpl.h"

namespace reyco {

Console::Console(std::istream &in, std::ostream &out) : in(in), out(out) {}

std::unique_ptr<Console> Console::make(std::istream &in, std::ostream &out) {
  return std::make_unique<ConsoleImpl>(in, out);
}

Console::~Console() = default;

Console::CmdHandler::CmdHandler(const std::string_view &cmd, Console &console)
    : cmd(cmd), console(console.registerCmd(cmd, *this)) {}

Console::CmdHandler::~CmdHandler() { console.unregisterCmd(cmd); }
}
