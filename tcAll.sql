--CREATE
CREATE TABLE myTable (n_nationkey INTEGER, n_name STRING, n_regionkey INTEGER, n_comment STRING) AS HEAP;
--INSERT
INSERT '../../../tpch-dbgen/nation.tbl' INTO myTable;
--QUERY
SELECT n.n_nationkey
FROM myTable AS n 
WHERE (n.n_name = 'UNITED STATES');
--DROP
DROP TABLE myTable;
-- Query 1
SELECT n.n_nationkey
FROM nation AS n 
WHERE (n.n_name = 'UNITED STATES');
-- Query 2
SELECT n.n_name
FROM nation AS n, region AS r
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_nationkey > 5);
-- Query 3
SELECT SUM (n.n_nationkey) 
FROM nation AS n, region AS r 
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_name = 'UNITED STATES');
-- Query 4
SELECT SUM (n.n_regionkey) 
FROM nation AS n, region AS r 
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_name = 'UNITED STATES') 
GROUP BY n.n_regionkey;
-- Query 5
SELECT SUM DISTINCT (n.n_nationkey + r.r_regionkey)
FROM nation AS n, region AS r, customer AS c 
WHERE (n.n_regionkey = r.r_regionkey) AND (n.n_nationkey = c.c_nationkey) AND (n.n_nationkey > 10)
GROUP BY r.r_regionkey;

