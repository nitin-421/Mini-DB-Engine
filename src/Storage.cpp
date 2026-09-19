#include "MiniDB.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace minidb {
	Storage::Storage(std::string directory)
		: directory_(std::move(directory)) {
		std::error_code ec;
		std::filesystem::create_directories(directory_, ec);
	}

	bool Storage::save(const Table& table, std::string& error) const {
		std::ofstream out(std::filesystem::path(directory_) / (table.name() + ".tbl"), std::ios::trunc);
		if (!out) {
			error = "Cannot write table file";
			return false;
		}

		out << table.name() << '\n' << table.columns().size() << '\n';
		for (const auto& c : table.columns()) {
			out << std::quoted(c.name) << ' ' << (c.type == DataType::Int ? "INT" : "TEXT") << '\n';
		}
		out << table.rows().size() << '\n';
		for (const auto& row : table.rows()) {
			for (const auto& value : row) {
				out << std::quoted(value) << ' ';
			}
			out << '\n';
		}
		return static_cast<bool>(out);
	}

	std::optional<Table> Storage::load(const std::string& name, std::string& error) const {
		std::ifstream in(std::filesystem::path(directory_) / (name + ".tbl"));
		if (!in) {
			error = "Cannot open table file";
			return std::nullopt;
		}

		std::string storedName, type;
		std::size_t ncols, nrows;
		
		if (!std::getline(in, storedName) || !(in >> ncols)) {
			error = "Invalid table file";
			return std::nullopt;
		}

		std::vector<Column> cols;
		for (std::size_t i = 0; i < ncols; ++i) {
			std::string col;
			if (!(in >> std::quoted(col) >> type) || (type != "INT" && type != "TEXT")) {
				error = "Invalid table schema";
				return std::nullopt;
			}
			cols.push_back({col, type == "INT" ? DataType::Int : DataType::Text});
		}

		if (!(in >> nrows)) {
			error = "Invalid table rows";
			return std::nullopt;
		}

		std::vector<std::vector<std::string>> rows(nrows, std::vector<std::string>(ncols));
		for (auto& row : rows) {
			for (auto& value : row) {
				if (!(in >> std::quoted(value))) {
					error = "Invalid row data";
					return std::nullopt;
				}
			}
		}

		Table table(storedName, cols);
		table.setRows(std::move(rows));
		return table;
	}

	std::vector<std::string> Storage::listTables(std::string& error) const {
		std::vector<std::string> names;
		std::error_code ec;
		for (const auto& item : std::filesystem::directory_iterator(directory_, ec)) {
			if (item.path().extension() == ".tbl") {
				names.push_back(item.path().stem().string());
			}
		}
		if (ec) {
			error = "Cannot read data directory";
		}
		return names;
	}
}
