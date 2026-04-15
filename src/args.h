#ifndef _args_h
#define _args_h

#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <chrono>
#include <string_view>


// if a value is passed for --seed [-s] that is what will be used
// if the --seed [-s] flag is passed without a value it is disregarded
// if both --rand and --default are passed then --default overrides --rand

class Parser {
private:
  bool _rand = false;
  bool _default = false;
  bool _twisty = false;

  bool randFlag(std::string_view s) { return s == "--rand"; }
  bool randFlag(char* s) { return strcmp(s, "--rand") == 0;}
  bool defaultFlag(std::string_view s) { return s == "--default"; }
  bool defaultFlag(char* s) { return strcmp(s, "--default") == 0;}
  bool twistyFlag(std::string_view s) { return s == "--twisty"; }
  bool twistyFlag(char* s) { return strcmp(s, "--twisty") == 0;}

  bool seedFlag(std::string_view s) {
    return (s.starts_with("-s") || s.starts_with("--seed"));
  }

  std::string genRandomSeed() {
    uint32_t t = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
    return std::to_string(t);
  }

public:
  std::string seedStr;
  
  Parser(int argc, char *argv[]) {

    std::string_view arg;
    for (int i = 1; i < argc; i++) {
      arg = argv[i];

      if (seedFlag(arg)) {
        std::cout << "init seedFlag\n";
        std::cout << (i+1 < argc) << "\n" << !randFlag(argv[i + 1]) << "\n" << !defaultFlag(argv[i + 1]) << "\n";
        if (arg.contains('=') && !arg.ends_with('=')) {
          std::cout << "lala\n";
          this->seedStr = arg.substr(arg.find_first_of('=') + 1);
          continue;
        } else if (i + 1 < argc && !randFlag(argv[i + 1]) &&
                   !defaultFlag(argv[i + 1])) {
          
          this->seedStr = argv[++i];
          std::cout << "init 2\n";
          continue;
        }
      }

      if (twistyFlag(arg)) {
        _twisty = true;
      } else if (randFlag(arg)) {
        _rand = true;
      } else if (defaultFlag(arg)) {
        _default = true;
      }
    }
    std::cout << "seed string: " << this->seedStr << "\n";
    if (!(this->seedStr).empty()) {
      return;
    } else if (!_default && _rand) {
      this->seedStr = genRandomSeed();
    } else {
      this->seedStr = "default";
      return;
    }
  }

  bool isReg() { return !_twisty; }
  bool isTwisty() {return _twisty; }
};

#endif