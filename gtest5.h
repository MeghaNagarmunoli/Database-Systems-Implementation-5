#ifndef GTEST_5_H
#define GTEST_5_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "Pipe.h"
#include "DBFile.h"
#include "Record.h"

#include "gtest/gtest.h"

using namespace std;

struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;

char *tpch_dir = new char[200];
// make sure that the information below is correct

char* catalog_path = "catalog";
char* dbfile_dir = "../bin/";
char* tpch_rel_dir = "../tpch-dbgen/";

// make sure that the information below is correct

extern "C" int yyparse();										 // defined in y.tab.c
extern "C" struct YY_BUFFER_STATE *yy_scan_string(const char *); // defined in lex.yy.c

extern struct AndList *final;

typedef struct
{
	Pipe *pipe;
	OrderMaker *order;
	bool print;
	bool write;
} testutil;

class relation
{

  private:
	char *rname;
	char *prefix;
	char rpath[100];
	Schema *rschema;

  public:
	relation(char *_name, Schema *_schema, char *_prefix) : rname(_name), rschema(_schema), prefix(_prefix)
	{
		sprintf(rpath, "%s%s.bin", prefix, rname);
	}
	char *name() { return rname; }
	char *path() { return rpath; }
	Schema *schema() { return rschema; }
	void info()
	{
		cout << " relation info\n";
		cout << "\t name: " << name() << endl;
		cout << "\t path: " << path() << endl;
	}

	void get_cnf(CNF &cnf_pred, Record &literal)
	{
		cout << "\n enter CNF predicate (when done press ctrl-D):\n\t";
		if (yyparse() != 0)
		{
			cout << " Error: can't parse your CNF.\n";
			exit(1);
		}
		cnf_pred.GrowFromParseTree(final, schema(), literal); // constructs CNF predicate
	}
	void get_sort_order(OrderMaker &sortorder)
	{
		cout << "\n specify sort ordering (when done press ctrl-D):\n\t ";
		if (yyparse() != 0)
		{
			cout << " Error: can't parse your CNF.\n";
			exit(1);
		}
		Record literal;
		CNF sort_pred;
		sort_pred.GrowFromParseTree(final, schema(), literal); // constructs CNF predicate
		OrderMaker dummy;
		sort_pred.GetSortOrders(sortorder, dummy);
	}
};

relation *rel;

char *supplier = "supplier";
char *partsupp = "partsupp";
char *part = "part";
char *nation = "nation";
char *customer = "customer";
char *orders = "orders";
char *region = "region";
char *lineitem = "lineitem";

relation *s, *p, *ps, *n, *li, *r, *o, *c;

struct StatsTestFixture : testing::Test
{

	StatsTestFixture()
	{
		strcpy(tpch_dir, homedir);
		strcat(tpch_dir, tpch_rel_dir);

		s = new relation(supplier, new Schema(catalog_path, supplier, NULL), dbfile_dir);
		ps = new relation(partsupp, new Schema(catalog_path, partsupp, NULL), dbfile_dir);
		p = new relation(part, new Schema(catalog_path, part, NULL), dbfile_dir);
		n = new relation(nation, new Schema(catalog_path, nation, NULL), dbfile_dir);
		li = new relation(lineitem, new Schema(catalog_path, lineitem, NULL), dbfile_dir);
		r = new relation(region, new Schema(catalog_path, region, NULL), dbfile_dir);
		o = new relation(orders, new Schema(catalog_path, orders, NULL), dbfile_dir);
		c = new relation(customer, new Schema(catalog_path, customer, NULL), dbfile_dir);
	}

	~StatsTestFixture()
	{
		delete s, p, ps, n, li, r, o, c;
	}
};

#endif
