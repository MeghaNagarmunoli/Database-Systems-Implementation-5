#include <iostream>

#include "Errors.h"
#include "SqlQueryInterpreter.h"
#include "ParseTree.h"
#include "Statistics.h"
#include "QueryPlanDriver.h"
#include "TableDriver.h"

using std::cout;

extern "C" {
  int yyparse(void);     // defined in y.tab.c
}

extern struct FuncOperator *finalFunction; // the aggregate function (NULL if no agg)
extern struct TableList *tables; // the list of tables and aliases in the query
extern struct AndList *boolean; // the predicate in the WHERE clause
extern struct NameList *groupingAtts; // grouping atts (NULL if no grouping)
extern struct NameList *attsToSelect; // the set of attributes in the SELECT (NULL if no such atts)
extern int distinctAtts; // 1 if there is a DISTINCT in a non-aggregate query 
extern int distinctFunc;  // 1 if there is a DISTINCT in an aggregate query
extern char* newtable;
extern char* oldtable;
extern char* newfile;
extern char* deoutput;
extern struct AttrList *newattrs; //Use this to build Attribute* array and record schema

void SqlQueryInterpreter::run() {
  char *fileName = "Statistics.txt";
  Statistics s;
  TableDriver d; 
  QueryPlan plan(&s);

  while(true) {
    cout << "SQL Query >>> ";
    if (yyparse() != 0) {
      cout << "Can't parse your CNF.\n";
      continue;
    }

    s.Read(fileName);

    if (newtable) {
      if (d.createTable()) cout << "Create table " << newtable << std::endl;
      else cout << "Table " << newtable << " already exists." << std::endl;
    } else if (oldtable && newfile) {
      if (d.insertInto()) cout << "Insert into " << oldtable << std::endl;
      else cout << "Insert failed." << std::endl;
    } else if (oldtable && !newfile) {
      if (d.dropTable()) cout << "Drop table " << oldtable << std::endl;
      else cout << "Table " << oldtable << " does not exist." << std::endl;
    } else if (deoutput) {
      plan.setOutput(deoutput);
    } else if (attsToSelect || finalFunction) {
      plan.plan();
      plan.print();
      //cout<<"\nPrint executed\n";
      plan.execute();
    }
    clear();
  }
}

// TODO: free lists
void SqlQueryInterpreter::clear() {
  newattrs = NULL;
  finalFunction = NULL;
  tables = NULL;
  boolean = NULL;
  groupingAtts = NULL;
  attsToSelect = NULL;
  newtable = oldtable = newfile = deoutput = NULL;
  distinctAtts = distinctFunc = 0;
  FATALIF (!remove ("*.tmp"), "remove tmp files failed");
}
