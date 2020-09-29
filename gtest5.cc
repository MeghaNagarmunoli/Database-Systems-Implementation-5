#include "gtest5.h"

#include <iostream>
#include <stdlib.h>
#include "Statistics.h"
#include "ParseTree.h"
#include "QueryPlanDriver.h"
#include <math.h>
#include <fstream>
#include "Errors.h"
#include "SqlQueryInterpreter.h"
#include "ParseTree.h"
#include "Statistics.h"
#include "QueryPlanDriver.h"
#include "TableDriver.h"

using namespace std;

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
extern struct AttrList *newattrs; 
char *fileName = "Statistics.txt";
//Statistics s;
TableDriver d; 

TEST(TESTING_TABLE_CREATE, CreateTable)
{
	ASSERT_EQ(d.exists("TEMP_TEST"), false);
	char *cnf = "CREATE TABLE TEMP_TEST (n_nationkey INTEGER, n_name STRING, n_regionkey INTEGER, n_comment STRING) AS HEAP;";
	yy_scan_string(cnf);
	yyparse();
	d.createTable();
	ASSERT_EQ(d.exists("TEMP_TEST"), true);
}

TEST(TESTING_TABLE_DROP, DropTable)
{
	ASSERT_EQ(d.exists("TEMP_TEST"), true);
	char *cnf = "DROP TABLE TEMP_TEST;";
	yy_scan_string(cnf);
	yyparse();
	d.dropTable();
	ASSERT_EQ(d.exists("TEMP_TEST"), false);
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
