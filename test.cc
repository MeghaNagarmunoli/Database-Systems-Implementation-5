#include <iostream>

#include "SqlQueryInterpreter.h"

using namespace std;

char* catalog_path = "catalog";
char* dbfile_dir = "../../../tpch-dbgen";
char* tpch_dir = "../../../tpch-dbgen";

int main (int argc, char* argv[]) {
  SqlQueryInterpreter it;
  it.run();
  return 0;
}
