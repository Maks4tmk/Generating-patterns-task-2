// Порождающие шаблоны задание 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

class SqlSelectQueryBuilder {
public:
	SqlSelectQueryBuilder() = default;

	SqlSelectQueryBuilder& AddColumn(const std::string& column) {
		columns_.push_back(column);
		return *this;
	}

	SqlSelectQueryBuilder& AddFrom(const std::string& table) {
		from_ = table;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
		for (const auto& pair : kv) {
			AddWhere(pair.first, pair.second);
		}
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
		where_conditions_.emplace_back(column + "=" + value);
		return *this;
	}

	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
		for (const auto& column : columns) {
			AddColumn(column);
		}
		return *this;
	}

	std::string BuildQuery() {
		std::string query = "SELECT ";

		if (columns_.empty()) {
			query += "* ";
		}
		else {
			for (const auto& column : columns_) {
				query += column + ", ";
			}
			query.pop_back();
			query.pop_back();
		}

		query += " FROM " + from_;

		if (!where_conditions_.empty()) {
			query += " WHERE ";
			for (int i = 0; i < where_conditions_.size(); ++i) {
				query += where_conditions_[i];
				if (i < where_conditions_.size() - 1) {
					query += " AND ";
				}
				else {
					query += ";";
				}
			}

		}

		return query;
	}

private:
	std::vector<std::string> columns_;
	std::string from_;
	std::vector<std::string> where_conditions_;
};

int main() {
	setlocale(LC_ALL, "ru");

	SqlSelectQueryBuilder query_builder;

	query_builder.AddColumn("name").AddColumn("phone");
	query_builder.AddFrom("students");
	query_builder.AddWhere({ {"id", "42"}, {"name", "John"} });

	std::string query = query_builder.BuildQuery();
	std::string example = "SELECT name, phone FROM students WHERE id=42 AND name=John;";

	if (query == example) {
		std::cout << "Запрос сформирован корректно." << std::endl;
	}
	else {
		std::cout << "Ошибка в формировании запроса." << std::endl;
	}

	return 0;
}