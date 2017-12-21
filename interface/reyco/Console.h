#pragma once
#include <iosfwd>
#include <memory>

namespace reyco {

class Console {
public:
  class CmdHandler;

  Console(std::istream &in, std::ostream &out);
  static std::unique_ptr<Console> make(std::istream &in, std::ostream &out);
  virtual ~Console();
  virtual bool start() = 0;

  auto addCommand(const std::string_view &cmd, auto handler);

protected:
  virtual Console &registerCmd(const std::string_view &cmd,
                               CmdHandler &handler) = 0;
  virtual void unregisterCmd(const std::string_view &cmd) = 0;

  std::istream &in;
  std::ostream &out;
};
}
