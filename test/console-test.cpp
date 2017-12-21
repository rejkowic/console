#include <iostream>
#include <reyco/AppFactory.h>
#include <reyco/ConsoleCmdHandler.h>

namespace reyco {

bool main(const AppFactory::Argv &) {
  auto console = Console::make(std::cin, std::cout);
  auto quote = console->addCommand("quote", [](auto &in, auto &out) {
    std::string msg;
    in >> msg;
    out << '"' << msg << '"' << '\n';
  });
  return console->start();
}
}

int main(int argc, char *argv[]) {
  return reyco::AppFactory::make(reyco::main, argc, argv);
}
