#pragma once

#include <cstddef>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace minidb {

	enum class DataType { Int, Text };
	struct Column {
		std::string name;
		DataType type;
	};
	struct Condition {
		std::string column;
		std::string value;
	};
	struct Statement {
		enum class Kind { Create, Insert, Select, Update, Delete, Invalid } kind = Kind::Invalid;
		std::string table;
		std::vector<Column> columns;
		std::vector<std::string> values;
		std::string setColumn;
		std::string setValue;
		std::optional<Condition> where;
		std::string error;
	};

	class Parser {
	public:
		Statement parse(const std::string& sql) const;
	};

	class BPlusTree {
	public:
		explicit BPlusTree(std::size_t leafSize = 8);
		void insert(int key, std::size_t rowId);
		std::vector<std::size_t> find(int key) const;
		void clear();

	private:
		struct Leaf {
			std::vector<std::pair<int, std::size_t>> entries;
			std::size_t next = static_cast<std::size_t>(-1);
		};
		std::size_t leafSize_;
		std::vector<Leaf> leaves_;
	};

	class Table {
	public:
		Table() = default;
		Table(std::string name, std::vector<Column> columns);
		const std::string& name() const;
		const std::vector<Column>& columns() const;
		const std::vector<std::vector<std::string>>& rows() const;
		bool insert(const std::vector<std::string>& values, std::string& error);
		std::vector<std::vector<std::string>> select(const std::optional<Condition>& where, std::string& error) const;
		std::size_t update(const std::string& column, const std::string& value, const std::optional<Condition>& where, std::string& error);
		std::size_t erase(const std::optional<Condition>& where, std::string& error);
		void setRows(std::vector<std::vector<std::string>> rows);

	private:
		std::string name_;
		std::vector<Column> columns_;
		std::vector<std::vector<std::string>> rows_;
		std::optional<std::size_t> columnIndex(const std::string& name) const;
		bool matches(const std::vector<std::string>& row, const std::optional<Condition>& where, std::string& error) const;
		bool validValue(std::size_t column, const std::string& value) const;
	};

	class Storage {
	public:
		explicit Storage(std::string directory);
		bool save(const Table& table, std::string& error) const;
		std::optional<Table> load(const std::string& name, std::string& error) const;
		std::vector<std::string> listTables(std::string& error) const;

	private:
		std::string directory_;
	};

	class Database {
	public:
		explicit Database(std::string dataDirectory = "data");
		std::string execute(const std::string& sql);

	private:
		Parser parser_;
		Storage storage_;
		std::map<std::string, Table> tables_;
		std::map<std::string, BPlusTree> indexes_;
		void loadTables();
		void rebuildIndex(const std::string& tableName);
	};
}
