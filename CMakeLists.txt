# CMakeList.txt: projekt CMake dla elementu Demo_01, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("Demo_01")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (Demo_01 "main.cpp" "main.h" "helper.cpp" "helper.hpp" "txn/txn.cpp" "txn/txn.hpp" "txn/typeRemoveUser.cpp" "txn/typeRemoveUser.hpp")

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
