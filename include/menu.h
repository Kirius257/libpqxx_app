#pragma once
#include <pqxx/pqxx>
#include <iostream>

void SELECT(pqxx::connection &conn);
void INSERT(pqxx::connection &conn);
void DEL(pqxx::connection &conn);
void UPDATE(pqxx::connection &conn);