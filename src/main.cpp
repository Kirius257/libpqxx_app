#include <iostream>
#include <iomanip>
#include <windows.h>
#include "menu.h"
#include "Functions.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  try {
    // url database
    std::string conn_str = "host=localhost port=5432 dbname=training_db "
                           "user=postgres password=90585";

    pqxx::connection conn(conn_str);

    if (conn.is_open()) {
      std::cout << "SUCCESS CONNECTION!" << std::endl;
      std::cout << "BASE: " << conn.dbname() << std::endl;
    }

    //here you can execute command
    
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}