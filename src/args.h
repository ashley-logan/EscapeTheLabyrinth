#ifndef _args_h
#define _args_h

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <string_view>


// if a value is passed for --seed [-s] that is what will be used
// if the --seed [-s] flag is passed without a value it is disregarded
// if both --rand and --default is passed program throws an error

class Parser {
private:
  bool _rand;
  bool _default;
  std::string _seed;

  bool randFlag(std::string_view s) { return s == "--rand"; }
  bool defaultFlag(std::string_view s) { return s == "--default"; }
  bool seedFlag(std::string_view s) { return (s.starts_with("-s") || s.starts_with("--seed")); }

public:
  Parser(int argc, char *argv[]) {
    std::string_view arg;
    for (int i = 1; i < argc; i++) {
      arg = argv[i];
      bool seed = false;
      if (seedFlag(arg) && i+1 < argc) {
        arg = argv[++i];
        seed = true;
      }
      if (randFlag(arg)) {
        _rand = true;
      } else if (defaultFlag(arg)) {
        _default = true;
      } else if (seed) {
        _seed = arg;
      } else {
        std::cerr << "Unknown option " << arg
                  << "\nValid options are:\n\t--seed[-s] "
                     "<seed>\n\t--rand\n\t--default\n";
        throw 42;

      }
    }
  }
};

#endif