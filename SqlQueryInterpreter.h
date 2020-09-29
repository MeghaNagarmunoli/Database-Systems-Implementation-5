#ifndef SQL_QUERY_INTERPRETER_H_
#define SQL_QUERY_INTERPRETER_H_

#include "ParseTree.h"

class SqlQueryInterpreter {
public:
  void run();

private:
  void clear();
};

#endif
