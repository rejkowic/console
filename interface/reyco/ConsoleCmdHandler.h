#include <optional>
#include <reyco/Console.h>

namespace reyco {

class Console::CmdHandler {
public:
  CmdHandler(const std::string_view &cmd, Console &console);
  virtual ~CmdHandler();

  virtual std::optional<bool> handle(std::istream &in) = 0;

protected:
  std::string_view cmd;
  Console &console;
};

auto Console::addCommand(const std::string_view &cmd, auto handler) {

  constexpr bool isVoid = std::is_void_v<decltype(handler(in, out))>;
  constexpr auto innerHandler = handler;
  if
    constexpr(isVoid) {
      class InlineCmdHandler : public Console::CmdHandler {
      public:
        using CmdHandler::CmdHandler;
        std::optional<bool> handle(std::istream &in) override {
          innerHandler(in, console.out);
          return {};
        }
      };
      return std::make_unique<InlineCmdHandler>(cmd, *this);
    }
  else {
    constexpr auto recipe = handler;
    class InlineCmdHandler : public Console::CmdHandler {
    public:
      using CmdHandler::CmdHandler;
      std::optional<bool> handle(std::istream &in) override {
        return innerHandler(in, console.out);
      }
    };
    return std::make_unique<InlineCmdHandler>(cmd, *this);
  }
}
}
