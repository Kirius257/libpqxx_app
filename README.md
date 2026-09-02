# PostgreSQL C++ приложение с использованием libpqxx
---

## Содержание проекта
Это консольное приложение на C++ с использованием библиотеки **libpqxx**
для взаимодействия с базой данных PostgreSQL. 
Проект реализует операции: 
- Create
- Read
- Update
- Delete 

Также реализованы следующие возможности:
*   Подключение к базе данных PostgreSQL.
*   Выполнение SQL-запросов: SELECT, INSERT, UPDATE, DELETE.
*   Обработка результатов запросов и извлечение данных.
*   Работа с транзакциями

## Технологический стек

*   **Язык:** C++20
*   **Библиотека для PostgreSQL:** libpqxx
*   **Драйвер PostgreSQL:** libpq
*   **Система сборки:** CMake.
*   **Инструменты анализа:** clang-format, clang-tidy.

## Требования к системе
- **Компилятор с поддержкой C++20:**
  - **GCC** 10+
  - **Clang** 10+
  - **MSVC ** 2019 16.10+ или 2022 с поддержкой `/std:c++20`

## Зависимости 
- **Инструменты сборки**
  -**CMake** 3.15+
- **Библиотеки и драйверы**
  - **PostgreSQL Server** — для подключения и тестирования.
  - **libpqxx** — для работы с PostgreSQL.
  - **libpq** — клиентский драйвер PostgreSQL
  - **OpenSSL**  — `libcrypto` и `libssl`.
  - **Дополнительные зависимости для Windows:** библиотеки `libiconv`, `libintl`, `libwinpthread`
- **Менеджер пакетов**
  - **Vckpg**
---

## Инструкция по установке libpqxx
**1. Откройте `Пуск->Изменение системных переменных среды->Переменные среды`**
**2. Создайте новую системную переменную с именем `PostgreSQL_ROOT`
   и укажите путь `C:/Program Files/PostgreSQL/<Your version PostgreSQL>`**
**3. Через менеджер пакетов vcpkg установите libpqxx**
   ```bash
   vcpkg install libpqxx:x64-windows
   ```

**4. Включите использование библиотек в Visual Studio и CMake**
   ```bash
   vcpkg integrate install
   ``` 

## Сборка проекта

1.  **Клонирование репозитория:**
    ```bash
    git clone https://github.com/Kirius257/libpqxx_app
    cd libpqxx_app
    ```

2.  **Создание системы сборки и
      подключение vcpkg к проекту:**
    ```bash
    cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
    ```

3.  **Сборка проекта**
    ```bash
    cmake --build . --config Release
    ```
