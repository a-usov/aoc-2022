#include "absl/strings/numbers.h"
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>

constexpr std::size_t N = 9;

std::array<std::list<char>, N> readInput(std::fstream &file) {
  std::array<std::list<char>, N> blocks{};

  char c{0};
  bool finishedBuilding{false};

  while (!finishedBuilding) {
    for (std::size_t n{0}; c != '\n'; ++n) {
      file.get();
      file.get(c);

      if (c != ' ') {
        if (isdigit(c) != 0) {
          finishedBuilding = true;
        } else {
          blocks[n].emplace_front(c);
        }
      }

      file.get();
      file.get(c);
    }

    c = 0;
  }

  return blocks;
}

int one() {
  std::fstream file{"data.txt"};

  std::array<std::list<char>, N> blocks{readInput(file)};

  std::string line;
  while (file.good()) {
    std::getline(file, line, ' ');

    std::getline(file, line, ' ');
    std::size_t toMove{0};
    absl::SimpleAtoi(line, &toMove);

    std::getline(file, line, ' ');

    std::getline(file, line, ' ');
    std::size_t from{0};
    absl::SimpleAtoi(line, &from);

    std::getline(file, line, ' ');

    std::getline(file, line);
    std::size_t to{0};
    absl::SimpleAtoi(line, &to);

    for (std::size_t n{0}; n < toMove; ++n) {
      auto end = std::prev(blocks[from - 1].end());

      blocks[to - 1].splice(blocks[to - 1].cend(), blocks[from - 1], end);
    }
  }

  for (auto &list : blocks) {
    std::cout << list.back();
  }
  std::cout << std::endl;
}

int two() {
  std::fstream file{"data.txt"};

  std::array<std::list<char>, N> blocks{readInput(file)};

  std::string line;
  while (file.good()) {
    std::getline(file, line, ' ');

    std::getline(file, line, ' ');
    std::size_t toMove{0};
    absl::SimpleAtoi(line, &toMove);

    std::getline(file, line, ' ');

    std::getline(file, line, ' ');
    std::size_t from{0};
    absl::SimpleAtoi(line, &from);

    std::getline(file, line, ' ');

    std::getline(file, line);
    std::size_t to{0};
    absl::SimpleAtoi(line, &to);

    auto end = blocks[from - 1].cend();
    auto start = blocks[from - 1].rbegin();
    std::advance(start, toMove);

    blocks[to - 1].splice(blocks[to - 1].cend(), blocks[from - 1], start.base(), end);
  }

  for (auto &list : blocks) {
    std::cout << list.back();
  }
  std::cout << std::endl;
}

int main() {
  one();
  two();
}
