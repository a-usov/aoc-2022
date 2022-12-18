#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  constexpr std::size_t N = 14;

  std::fstream file{"data.txt"};

  std::deque<char> queue{};
  std::unordered_map<char, std::int64_t> map{};

  std::int64_t position{0};

  char current{0};
  while (file.good()) {
    file.get(current);
    ++position;

    if (queue.size() >= N) {
      const char last = queue.back();
      queue.pop_back();

      auto itr = map.find(last);
      --itr->second;
      if (itr->second == 0) {
        map.erase(itr);
      }
    }
    queue.emplace_front(current);

    auto itr = map.find(current);
    if (itr != map.cend()) {
      ++itr->second;
    } else {
      map[current] = 1;
    }

    if (map.size() >= N) {
      std::cout << position;
      break;
    }
  }
}
