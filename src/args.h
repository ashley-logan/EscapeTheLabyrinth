#ifndef _args_h
#define _args_h

#include <string>
#include <string_view>

class Parser {
private:
  bool _rand;
  bool _default;
  std::string _seed;

  bool randFlag(std::string_view s) { return s == "--rand"; }
  bool defaultFlag(std::string_view s) { return s == "--default"; }
  bool seedFlag(std::string_view s) { return s. }

public:
  Parser(int argc, char *argv[]) {
    std::string arg;
    bool s for (int i = 1; i < argc; i++) {
      arg = argv[i];
      if (arg == "--rand") {
        _rand = true;
      } else if (arg == "--default") {
        _default = true;
      } else if (arg == "-s" || arg == "--seed") {
        i
      }
    }
  }
};

#endif