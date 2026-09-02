#include "menu.h"

void SELECT(pqxx::connection &conn) {
  pqxx::work txn(conn);

  std::string req = "SELECT * FROM employees";
  pqxx::result res = txn.exec(req);

  if (res.empty()) {
    std::cout << "Not found nothing" << std::endl;
  } else {
    std::cout << "Found " << res.size() << " results" << std::endl;
    for (const auto &row : res) {

      std::cout << row[0].as<int>() << "\t" << row[1].as<std::string>() << "\t"
                << row[2].as<std::string>() << "\t" << row[3].as<double>()
                << "\t"
                << "\t" << row[4].as<std::string>() << "\t" << row[5].as<int>()
                << std::endl;
    }
  }
  txn.commit();
}

void INSERT(pqxx::connection &conn) {
  std::string name, position, hired_date;
  std::string salary_str;

  std::cout << "Data of worker" << std::endl;

  std::cout << "Enter name: ";
  std::getline(std::cin, name);

  std::cout << "Enter position: ";
  std::getline(std::cin, position);

  std::cout << "Enter salary: ";
  std::getline(std::cin, salary_str);
  double salary = std::stod(salary_str);

  std::cout << "Enter hired date (YYYY-MM-DD): ";
  std::getline(std::cin, hired_date);

  pqxx::work txn(conn);

  std::string req =
      "INSERT INTO employees (id, name, position, salary, hired_date) "
      "VALUES ((SELECT COALESCE(MAX(id), 0) + 1 FROM employees), $1, $2, $3, "
      "$4);";

  txn.exec(req, pqxx::params{name, position, salary, hired_date});
  txn.commit();

  std::cout << "Employee added successfully!" << std::endl;
}

void DEL(pqxx::connection &conn) {
  std::string id_str;

  std::cout << "Enter id: ";
  std::getline(std::cin, id_str);

  int id = std::stoi(id_str);

  pqxx::work txn(conn);

  std::string req = "DELETE FROM employees WHERE id = $1;";
  pqxx::result res = txn.exec(req, pqxx::params{id});

  txn.commit();

  if (res.affected_rows() > 0) {
    std::cout << "Deleted " << res.affected_rows() << " rows" << std::endl;
  } else {
    std::cout << "Employees with " << id << " not found" << std::endl;
  }
}

void UPDATE(pqxx::connection &conn) {
  std::string id_str;
  std::string salary_str;

  std::cout << "Enter id: ";
  std::getline(std::cin, id_str);
  int id = std::stoi(id_str);

  std::cout << "Enter salary: ";
  std::getline(std::cin, salary_str);
  double salary = std::stod(salary_str);

  pqxx::work txn(conn);

  std::string req = "UPDATE employees SET salary = $1 WHERE id = $2;";
  pqxx::result res = txn.exec(req, pqxx::params{salary, id});

  txn.commit();

  if (res.affected_rows() > 0) {
    std::cout << "Updated " << res.affected_rows() << " rows" << std::endl;
  } else {
    std::cout << "Employees with " << id << " not found" << std::endl;
  }
}