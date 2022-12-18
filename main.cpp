#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"
#include <fstream>
#include <iostream>
#include <optional>

class DirNode {
  std::size_t m_size{0};
  std::string m_name;
  std::weak_ptr<DirNode> m_parent;
  std::vector<std::shared_ptr<DirNode>> m_nodes;

public:
  DirNode(const std::string_view name, const std::shared_ptr<DirNode> &parent) : m_name{name}, m_parent{parent} {}

  [[nodiscard]] std::size_t getSize() const { return m_size; };
  [[nodiscard]] std::string_view getName() const { return m_name; };
  [[nodiscard]] std::weak_ptr<DirNode> getParent() const { return m_parent; }
  [[nodiscard]] const std::vector<std::shared_ptr<DirNode>> &getNodes() const { return m_nodes; }

  [[nodiscard]] std::optional<std::shared_ptr<DirNode>> getNodeByName(std::string_view name) const {
    for (const auto &node : m_nodes) {
      if (node->getName() == name) {
        return node;
      }
    }
    return std::nullopt;
  }

  void addDir(const std::shared_ptr<DirNode> &node) { m_nodes.emplace_back(node); }
  void addFile(std::size_t size) {
    m_size += size;
    if (const auto parent_owning = getParent().lock()) {
      parent_owning->addFile(size);
    }
  }
};

class Tree {
  std::shared_ptr<DirNode> root;
  std::weak_ptr<DirNode> current;

public:
  Tree() : root{std::make_shared<DirNode>("/", nullptr)}, current{root} {}

  void cd(const std::string_view name) {
    if (name == "/") {
      current = root;
      return;
    }

    if (name == "..") {
      if (auto current_owning = current.lock()) {
        current = current_owning->getParent();
        return;
      }
    }

    if (auto current_owning = current.lock()) {
      auto opt_dir = current_owning->getNodeByName(name);
      if (opt_dir.has_value()) {
        current = opt_dir.value();
        return;
      }

      auto new_dir = std::make_shared<DirNode>(name, current_owning);
      current_owning->addDir(new_dir);
      current = new_dir;
    }
  }

  void addFile(const std::size_t size) {
    if (auto current_owning = current.lock()) {
      current_owning->addFile(size);
    }
  }

  [[nodiscard]] std::shared_ptr<DirNode> getRoot() const { return root; }
};

void parse(Tree &tree, const std::vector<absl::string_view> &line) {
  if (line[0] == "$") {
    if (line[1] == "cd") {
      tree.cd(line[2]);
    }
  } else if ((line[0] != "dir")) {
    std::size_t size{0};
    absl::SimpleAtoi(line[0], &size);
    tree.addFile(size);
  }
}

std::size_t findSum(const std::shared_ptr<DirNode> &node, const std::size_t limit) {
  std::size_t sum{0};

  if (node->getSize() <= limit) {
    sum += node->getSize();
  }

  for (const auto &child : node->getNodes()) {
    sum += findSum(child, limit);
  }
  return sum;
}

std::vector<std::size_t> findFreeing(const std::shared_ptr<DirNode> &node, const std::size_t toFree) {
  std::vector<std::size_t> freeing{};

  if (node->getSize() >= toFree) {
    freeing.emplace_back(node->getSize());
  }

  for (const auto &child : node->getNodes()) {
    const auto others = findFreeing(child, toFree);
    freeing.insert(freeing.cend(), others.begin(), others.end());
  }

  return freeing;
}

int main() {
  std::fstream file{"data.txt"};
  std::string line;

  Tree tree;

  while (file.good()) {
    std::getline(file, line);
    const std::vector<absl::string_view> parts = absl::StrSplit(line, ' ');
    parse(tree, parts);
  }

  constexpr std::size_t LIMIT = 100000;
  std::cout << findSum(tree.getRoot(), LIMIT) << std::endl;

  const std::size_t amountToFree = 30000000 - (70000000 - tree.getRoot()->getSize());
  const auto freeing = findFreeing(tree.getRoot(), amountToFree);
  std::cout << *std::min_element(freeing.begin(), freeing.end()) << std::endl;
}
