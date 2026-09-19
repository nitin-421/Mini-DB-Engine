#include "MiniDB.hpp"
#include <gtest/gtest.h>
#include <filesystem>

TEST(Storage, SavesAndLoads) {
  const std::string path = "test_data_storage";
  std::filesystem::remove_all(path);

  minidb::Storage s(path);
  minidb::Table t(
    "people",
    {{"id", minidb::DataType::Int},
    {"name", minidb::DataType::Text}}
  );
  std::string error;

  ASSERT_TRUE(t.insert({"1", "A person"}, error));
  ASSERT_TRUE(s.save(t, error));

  auto loaded = s.load("people", error);
  ASSERT_TRUE(loaded.has_value());
  EXPECT_EQ(loaded->rows()[0][0], "1");
  EXPECT_EQ(loaded->rows()[0][1], "A person");

  std::filesystem::remove_all(path);
}
