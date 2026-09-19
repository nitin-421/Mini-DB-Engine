#include "MiniDB.hpp"
#include <iostream>
#include <string>

int main() {
  minidb::Database database;
  std::cout << "MiniDB - type EXIT to quit.\n";

  std::string sql;
  while (true) {
    std::cout << "MiniDB> ";
    if (!std::getline(std::cin, sql)) {
      break;
    }
    if (sql == "EXIT" || sql == "exit" || sql == "QUIT" || sql == "quit") {
      break;
    }
    if (sql.empty()) {
      continue;
    }
    std::cout << database.execute(sql) << "\n";
  }
  return 0;
}
