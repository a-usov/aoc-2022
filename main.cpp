#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::fstream file{"data.txt"};
  std::string line;

  std::int64_t count_complete = 0;
  std::int64_t count_partial = 0;

  while (std::getline(file, line)) {
    const std::pair<absl::string_view, absl::string_view> regions = absl::StrSplit(line, ',');

    const std::pair<absl::string_view, absl::string_view> elf1_str = absl::StrSplit(regions.first, '-');
    std::pair<std::int64_t, std::int64_t> elf1{0, 0};
    absl::SimpleAtoi(elf1_str.first, &elf1.first);
    absl::SimpleAtoi(elf1_str.second, &elf1.second);

    const std::pair<absl::string_view, absl::string_view> elf2_str = absl::StrSplit(regions.second, '-');
    std::pair<std::int64_t, std::int64_t> elf2{0, 0};
    absl::SimpleAtoi(elf2_str.first, &elf2.first);
    absl::SimpleAtoi(elf2_str.second, &elf2.second);

    if (elf2.first < elf1.first) {
      std::swap(elf1, elf2);
    } else if (elf2.first == elf1.first) {
      if (elf2.second > elf1.second) {
        std::swap(elf1, elf2);
      }
    }

    std::cout << elf1.first << " " << elf1.second << " " << elf2.first << " " << elf2.second << std::endl;

    if (elf1.second >= elf2.second) {
      ++count_complete;
    }

    if (elf2.first <= elf1.second) {
      ++count_partial;
    }
  }

  std::cout << "Overlaps: " << count_complete << " partial: " << count_partial << std::endl;
}
