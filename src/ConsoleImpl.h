#include <reyco/ConsoleCmdHandler.h>
#include <unordered_map>
#include <iostream>
#include <optional>

namespace reyco {

class ConsoleImpl : public Console {
public:
  using Console::Console;

private:
  bool start() override {
    std::string cmd = "(started)";
    while (true) {
      out << '\n' << cmd << ">> ";
      if (!(in >> cmd))
        return false;

      try {
        CmdHandler &handler = cmdHandlers.at(cmd).get();
        std::optional<bool> result = handler.handle();

        if (!result.has_value())
          continue;
        return *result;
      } catch (std::out_of_range) {
        using namespace std::string_literals;
        throw std::runtime_error("no such command: '"s + cmd + "'"s);
      }
    }
    return false;
  }

  Console &registerCmd(const std::string_view &cmd, CmdHandler &handler) override {
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
