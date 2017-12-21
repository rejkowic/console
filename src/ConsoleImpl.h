#include <iostream>
#include <optional>
#include <reyco/ConsoleCmdHandler.h>
#include <sstream>
#include <unordered_map>

namespace reyco {

class ConsoleImpl : public Console {
public:
  using Console::Console;

private:
  bool start() override {
    std::string cmd;
    std::string line;
    out << "Starting console...\n";
    std::string_view prompt = &in == &std::cin ? ">> " : "";
    while (true) {
      out << prompt;
      if (!std::getline(in, line))
        return false;
      if (line.empty())
        continue;

      std::istringstream ss(line);
      ss >> cmd;
      try {
        CmdHandler &handler = cmdHandlers.at(cmd).get();
        std::optional<bool> result = handler.handle(ss);

        if (!result.has_value())
          continue;
        return *result;
      } catch (std::out_of_range) {
        using namespace std::string_literals;
        throw std::runtime_error("no such command: '"s + cmd + "'"s);
      }
    }
    out << "Exiting console...\n";
    return false;
  }

  Console &registerCmd(const std::string_view &cmd,
                       CmdHandler &handler) override {
    cmdHandlers.emplace(cmd, std::ref(handler));
    return *this;
  }
  void unregisterCmd(const std::string_view &cmd) override {
    cmdHandlers.erase(cmd);
  }

  using CmdHandlerRef = std::reference_wrapper<CmdHandler>;
  std::unordered_map<std::string_view, CmdHandlerRef> cmdHandlers;
};
}
