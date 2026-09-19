#include "MiniDB.hpp"
#include <gtest/gtest.h>
#include <filesystem>

TEST(Database, Crud) {
  const std::string path = "test_data_database";
  std::filesystem::remove_all(path);

  minidb::Database db(path);

  EXPECT_EQ(db.execute("CREATE TABLE users (id INT, name TEXT);"),
		"Table created.");

  EXPECT_EQ(db.execute("INSERT INTO users VALUES (1, 'Nitin');"),
		"1 row inserted.");

  EXPECT_NE(db.execute("SELECT * FROM users WHERE id = 1;").find("Nitin"),
		std::string::npos);

  EXPECT_EQ(db.execute("UPDATE users SET name = 'Rahul' WHERE id = 1;"),
		"1 row(s) updated.");
		
  EXPECT_EQ(db.execute("DELETE FROM users WHERE id = 1;"),
		"1 row(s) deleted.");

  std::filesystem::remove_all(path);
}
