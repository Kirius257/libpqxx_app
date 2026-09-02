#include "Functions.h"
#include <iomanip>
#include <iostream>

void transaction(pqxx::connection &conn) {
  std::string id_str;

  std::cout << "Enter id: " << std::endl;
  std::getline(std::cin, id_str);
  int id = std::stoi(id_str);

  pqxx::work txn(conn);

  std::string req_id = "SELECT salary FROM employees WHERE id = $1";
  pqxx::result res_req_id = txn.exec(req_id, pqxx::params{id});

  if (!res_req_id.empty()) {
    for (const auto &row : res_req_id) {
      double salary = row[0].as<double>();
      salary *= 1.2;
      if (salary > 100000) {
        txn.exec("ROLLBACK");
        return;
      }
      std::string req_update = "UPDATE employees SET salary = $1 WHERE id = $2";
      pqxx::result res_req_update =
          txn.exec(req_update, pqxx::params{salary, id});
    }

  } else {
    return;
  }
  txn.commit();
  std::cout << "Transaction successfully completed!" << std::endl;
}

void try_delete_dep(pqxx::connection &conn) {
  std::string id_str;

  std::cout << "Enter id: " << std::endl;
  std::getline(std::cin, id_str);
  int id = std::stoi(id_str);

  pqxx::work txn(conn);

  try {
    std::string req_del = "DELETE FROM departaments WHERE id = $1";
    pqxx::result res_del = txn.exec(req_del, pqxx::params{id});

    txn.commit(); // always wrap in try
  } catch (const pqxx::sql_error &e) {
    std::string error_msg = e.what();
    if (error_msg.find("foreign key constraint") != std::string::npos) {
      std::cout << "Cannot delete department: it still has employees assigned."
                << std::endl;
    } else {
      std::cout << "SQL Error: " << error_msg << std::endl;
    }
  } catch (const std::exception &e) {
    std::cout << "General error: " << e.what() << std::endl;
  }
}

void reassign_emp(pqxx::connection &conn) {
  std::string old_id_dep_str;
  std::string new_id_dep_str;

  std::cout << "Enter id departament for delete: " << std::endl;
  std::getline(std::cin, old_id_dep_str);
  int old_id_dep = std::stoi(old_id_dep_str);

  std::cout << "Enter id departament for assign: " << std::endl;
  std::getline(std::cin, new_id_dep_str);
  int new_id_dep = std::stoi(new_id_dep_str);
  try {
    pqxx::work txn(conn);

    std::string req_select1 = "SELECT id FROM departaments WHERE id = $1";
    pqxx::result res_req1 = txn.exec(req_select1, pqxx::params{old_id_dep});

    std::string req_select2 = "SELECT id FROM departaments WHERE id = $1";
    pqxx::result res_req2 = txn.exec(req_select2, pqxx::params{new_id_dep});

    if (!res_req1.empty() && !res_req2.empty()) {
      std::string req_update =
          "UPDATE employees SET department_id = $1 WHERE department_id = $2";
      pqxx::result res_req3 =
          txn.exec(req_update, pqxx::params{new_id_dep, old_id_dep});
      std::cout << "departament with id " << old_id_dep << " changed id on "
                << new_id_dep << "in table employees" << std::endl;

      std::string req_delete = "DELETE FROM departaments WHERE id = $1";
      pqxx::result res_req4 = txn.exec(req_delete, pqxx::params{old_id_dep});
      std::cout << "departament with id " << old_id_dep
                << "was deleted in table departaments" << std::endl;

    } else {
      std::cout << "departament(s) with entered id not found" << std::endl;
      return;
    }

    txn.commit();
  } catch (const pqxx::sql_error &e) {
    std::cerr << "SQL Error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "General Error: " << e.what() << std::endl;
  }
}

void show_avg_salary(pqxx::connection &conn) {
  pqxx::work txn(conn);
  std::string req = "SELECT name,salary,AVG(salary) OVER (PARTITION BY department_id) as avg FROM "
                    "employees ORDER BY id;";

  pqxx::result res_req = txn.exec(req);

  for (const auto &row : res_req) {
    std::cout << std::left << row[0].as<std::string>() << "\t"
              << row[1].as<double>() << "\t" << row[2].as<double>()
              << std::endl;
  }

  txn.commit();
}