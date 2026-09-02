#pragma once
#include <pqxx/pqxx>

void transaction(pqxx::connection &conn);
void try_delete_dep(pqxx::connection &conn);
void reassign_emp(pqxx::connection &conn);
void show_avg_salary(pqxx::connection &conn);