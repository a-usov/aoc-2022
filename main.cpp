#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::fstream file{"data.txt"};

  std::vector<std::int64_t> calories;

  std::string line;
  std::int64_t currentElf{0};
  for (; std::getline(file, line);) {
    if (!line.empty()) {
      currentElf += std::stoll(line);
    } else {
      calories.emplace_back(currentElf);
      currentElf = 0;
    }
  }

  std::cout << "Max carried by Elf: "
            << *std::max_element(calories.cbegin(), calories.cend())
            << std::endl;

  std::sort(calories.begin(), calories.end(), std::greater<>());

  std::cout << "Carried by top 3 elves: " << calories[0] << " " << calories[1]
            << " " << calories[2] << std::endl;
}
