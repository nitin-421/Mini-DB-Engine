#include "MiniDB.hpp"
#include <gtest/gtest.h>

TEST(Parser, ParsesCreate){
  minidb::Parser p;

  auto s = p.parse("CREATE TABLE users (id INT, name TEXT);");
	
  EXPECT_EQ(s.kind, minidb::Statement::Kind::Create);
  EXPECT_EQ(s.columns.size(), 2);
}

TEST(Parser, ParsesCrudAndWhere) {
  minidb::Parser p;
  EXPECT_EQ(
		p.parse("INSERT INTO users VALUES (1, 'Nitin');").kind,
		minidb::Statement::Kind::Insert
	);

  auto select = p.parse("SELECT * FROM users WHERE id = 1;");

	EXPECT_EQ(select.kind, minidb::Statement::Kind::Select);
		ASSERT_TRUE(select.where.has_value());

		EXPECT_EQ(
			p.parse("UPDATE users SET name = 'Rahul' WHERE id = 1;").kind,
			minidb::Statement::Kind::Update
		);
		EXPECT_EQ(
			p.parse("DELETE FROM users WHERE id = 1;").kind,
			minidb::Statement::Kind::Delete
		);
}

TEST(Parser, RejectsInvalidSql) {
  minidb::Parser p;
  EXPECT_EQ(p.parse("DROP TABLE users").kind,
		minidb::Statement::Kind::Invalid);
}
