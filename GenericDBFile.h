#ifndef GENDBFILE_H
#define GENDBFILE_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"

#define SUCCESS 1
#define FAILURE 0

typedef enum {heap, sorted, tree} fType;

// stub DBFile header..replace it with your own DBFile.h 

class GenericDBFile {
public:
	char *filepath; 
	File metaFilefile;
    off_t totalPageCount;
    off_t currentPage;
	Page page;
	ComparisonEngine comparator; 
	virtual int Create (const char *fpath, fType file_type, void *startup) = 0;
	virtual int Open (const char *fpath) = 0;
	virtual int Close () = 0;

	virtual void Load (Schema &myschema, const char *loadpath) = 0;

	virtual void MoveFirst ()= 0;
	virtual void Add (Record &addme)= 0;
	//virtual void HopefullyHarmless()= 0;
	virtual int GetNext (Record &fetchme)= 0;
	virtual int GetNext (Record &fetchme, CNF &cnf, Record &literal)= 0;

};
#endif
