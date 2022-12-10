#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

namespace {

enum class Opponent { ROCK = 'A', PAPER = 'B', SCISSOR = 'C' };
enum class Me { ROCK = 'X', PAPER = 'Y', SCISSOR = 'Z' };
enum class State { Win = 'Z', Loss = 'X', Draw = 'Y' };

const std::unordered_map<Me, std::int64_t> scores{// NOLINT
                                                  {Me::ROCK, 1},
                                                  {Me::PAPER, 2},
                                                  {Me::SCISSOR, 3}};

const std::unordered_map<State, std::int64_t> scores_state{// NOLINT
                                                           {State::Win, 6},
                                                           {State::Loss, 0},
                                                           {State::Draw, 3}};

std::int64_t first() {
  const std::map<std::pair<Opponent, Me>, State> map{
      {{Opponent::ROCK, Me::ROCK}, State::Draw},
      {{Opponent::ROCK, Me::PAPER}, State::Win},
      {{Opponent::ROCK, Me::SCISSOR}, State::Loss},
      {{Opponent::PAPER, Me::ROCK}, State::Loss},
      {{Opponent::PAPER, Me::PAPER}, State::Draw},
      {{Opponent::PAPER, Me::SCISSOR}, State::Win},
      {{Opponent::SCISSOR, Me::ROCK}, State::Win},
      {{Opponent::SCISSOR, Me::PAPER}, State::Loss},
      {{Opponent::SCISSOR, Me::SCISSOR}, State::Draw},
  };

  std::fstream file{"data.txt"};
  std::int64_t points{0};
  std::string line;

  for (std::uint64_t i = 0; std::getline(file, line); ++i) {
    const auto opponent = static_cast<Opponent>(line[0]);
    const auto me = static_cast<Me>(line[2]);

    points += scores_state.find((map.find({opponent, me})->second))->second;
    points += scores.find(me)->second;
  }

  return points;
}

std::int64_t second() {
  const std::map<std::pair<Opponent, State>, Me> map{
      {{Opponent::ROCK, State::Win}, Me::PAPER},
      {{Opponent::ROCK, State::Loss}, Me::SCISSOR},
      {{Opponent::ROCK, State::Draw}, Me::ROCK},
      {{Opponent::PAPER, State::Win}, Me::SCISSOR},
      {{Opponent::PAPER, State::Loss}, Me::ROCK},
      {{Opponent::PAPER, State::Draw}, Me::PAPER},
      {{Opponent::SCISSOR, State::Win}, Me::ROCK},
      {{Opponent::SCISSOR, State::Loss}, Me::PAPER},
      {{Opponent::SCISSOR, State::Draw}, Me::SCISSOR},
  };

  std::fstream file{"data.txt"};
  std::int64_t points{0};
  std::string line;

  for (std::uint64_t i = 0; std::getline(file, line); ++i) {
    const auto opponent = static_cast<Opponent>(line[0]);
    const auto state = static_cast<State>(line[2]);

    points += scores_state.find(state)->second;
    const Me me = map.find({opponent, state})->second;
    points += scores.find(me)->second;
  }

  return points;
}

} // namespace

int main() {
  std::cout << "Number of points: " << first() << "\n";
  std::cout << "Number of points: " << second() << "\n";
  std::cout.flush();
}
