#include <fstream>
#include <iostream>
#include <optional>
#include <set>

constexpr char UPPER_BASE = 38;
constexpr char LOWER_BASE = 96;

std::optional<char> findCommon(std::string_view first, std::string_view second) {
  std::set<char> set;

  for (const char c : first) {
    set.emplace(c);
  }

  for (const char c : second) {
    if (set.contains(c)) {
      return c;
    }
  }

  return std::nullopt;
}

std::optional<char> findCommons(std::string_view first, std::string_view second, std::string_view third) {
  std::set<char> first_set;
  std::set<char> second_set;

  for (const char c : first) {
    first_set.emplace(c);
  }

  for (const char c : second) {
    if (first_set.contains(c)) {
      second_set.emplace(c);
    }
  }

  for (const char c : third) {
    if (second_set.contains(c)) {
      return c;
    }
  }

  return std::nullopt;
}

std::int64_t first() {
  std::fstream file{"data.txt"};
  std::string line;

  std::int64_t sum = 0;

  while (std::getline(file, line)) {
    const std::string_view line_sv{line};
    auto half = line_sv.size() / 2;
    auto opt_char = findCommon(line_sv.substr(0, half), line_sv.substr(half, half));

    if (opt_char.has_value()) {
      auto c = opt_char.value();
      if (isupper(c) != 0) {
        sum += c - UPPER_BASE;
      } else {
        sum += c - LOWER_BASE;
      }
    }
  }
  return sum;
}

std::int64_t second() {
  std::fstream file{"data.txt"};
  std::string elf1;
  std::string elf2;
  std::string elf3;

  std::int64_t sum = 0;

  do {
    std::getline(file, elf1);
    std::getline(file, elf2);
    std::getline(file, elf3);

    auto opt_char = findCommons(elf1, elf2, elf3);

    if (opt_char.has_value()) {
      auto c = opt_char.value();
      if (isupper(c) != 0) {
        sum += c - UPPER_BASE;
      } else {
        sum += c - LOWER_BASE;
      }
    }
  } while (!file.fail());

  return sum;
}

int main() { std::cout << "First problem: " << first() << " Second Problem: " << second() << std::endl; }
