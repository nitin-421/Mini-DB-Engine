#include "MiniDB.hpp"
#include <algorithm>
#include <charconv>

namespace minidb {
	Table::Table(std::string name, std::vector<Column> columns)
		: name_(std::move(name)), columns_(std::move(columns)) {}

	const std::string& Table::name() const {
		return name_;
	}

	const std::vector<Column>& Table::columns() const {
		return columns_;
	}

	const std::vector<std::vector<std::string>>& Table::rows() const {
		return rows_;
	}

	std::optional<std::size_t> Table::columnIndex(const std::string& name) const {
		for (std::size_t i = 0; i < columns_.size(); ++i)
			if (columns_[i].name == name)
				return i;
			
		return std::nullopt;
	}

	bool Table::validValue(std::size_t column, const std::string& value) const {
		if (columns_[column].type == DataType::Text) {
			return true;
		}

		int n;
		auto [p, e] = std::from_chars(value.data(), value.data() + value.size(), n);
		return e == std::errc{} && p == value.data() + value.size();
	}

	bool Table::matches(const std::vector<std::string>& row, const std::optional<Condition>& where, std::string& error) const {
		if (!where) {
			return true;
		}

		auto i = columnIndex(where->column);
		if (!i) {
			error = "Unknown column: " + where->column;
			return false;
		}

		return row[*i] == where->value;
	}

	bool Table::insert(const std::vector<std::string>& values, std::string& error) {
		if (values.size() != columns_.size()) {
			error = "Column count does not match values";
			return false;
		}

		for (std::size_t i = 0; i < values.size(); ++i) {
			if (!validValue(i, values[i])) {
				error = "Invalid value for column: " + columns_[i].name;
				return false;
			}
		}

		rows_.push_back(values);
		return true;
	}

	std::vector<std::vector<std::string>> Table::select(const std::optional<Condition>& where, std::string& error) const {
		std::vector<std::vector<std::string>> result;
		for (const auto& row : rows_) {
			auto prior = error;
			bool ok = matches(row, where, error);
			if (!error.empty() && error != prior) {
				return {};
			}
			if (ok) {
				result.push_back(row);
			}
		}
		return result;
	}

	std::size_t Table::update(const std::string& column, const std::string& value, const std::optional<Condition>& where, std::string& error) {
		auto target = columnIndex(column);
		if (!target) {
			error = "Unknown column: " + column;
			return 0;
		}
		if (!validValue(*target, value)) {
			error = "Invalid value for column: " + column;
			return 0;
		}

		std::size_t n = 0;
		for (auto& row : rows_) {
			if (matches(row, where, error)) {
				row[*target] = value;
				++n;
			}
		}
		return n;
	}

	std::size_t Table::erase(const std::optional<Condition>& where, std::string& error) {
		auto old = rows_.size();
		auto end = std::remove_if(rows_.begin(), rows_.end(), [&](const auto& row) {
			return matches(row, where, error);
		});
		rows_.erase(end, rows_.end());
		return old - rows_.size();
	}

	void Table::setRows(std::vector<std::vector<std::string>> rows) {
		rows_ = std::move(rows);
	}
}