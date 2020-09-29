Instructions:
=======================
* Make sure you have loaded all the tpch tables into your system 
* Set up the `Statistics.txt` module so that it can give meaningful plans
* To compile the project: make a5.out

For more please visit:
----------------------
[Report](https://github.com/MeghaNagarmunoli/Database-Systems-Implementation-5/blob/master/Report.pdf) 
[Video](https://github.com/MeghaNagarmunoli/Database-Systems-Implementation-5/blob/master/FinalVideo.mp4) 


Execute
=======
--CREATE
```sql
CREATE TABLE myTable (n_nationkey INTEGER, n_name STRING, n_regionkey INTEGER, n_comment STRING) AS HEAP;
```

--INSERT
```sql
INSERT '../../../tpch-dbgen/nation.tbl' INTO myTable;
```

--QUERY
```sql
SELECT n.n_nationkey
FROM myTable AS n 
WHERE (n.n_name = 'UNITED STATES');
```

--DROP
```sql
DROP TABLE myTable;
```


Queries run on nation.tbl from tpch tables
-- Query 1
```sql
SELECT n.n_nationkey
FROM nation AS n 
WHERE (n.n_name = 'UNITED STATES');
```

-- Query 2
```sql
SELECT n.n_name
FROM nation AS n, region AS r
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_nationkey > 5);
```

-- Query 3
```sql
SELECT SUM (n.n_nationkey) 
FROM nation AS n, region AS r 
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_name = 'UNITED STATES');
```

-- Query 4
```sql
SELECT SUM (n.n_regionkey) 
FROM nation AS n, region AS r 
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_name = 'UNITED STATES') 
GROUP BY n.n_regionkey;
```

-- Query 5
```sql
SELECT SUM DISTINCT (n.n_nationkey + r.r_regionkey)
FROM nation AS n, region AS r, customer AS c 
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_nationkey = c.c_nationkey) AND (n.n_nationkey > 10)
GROUP BY r.r_regionkey;
```
