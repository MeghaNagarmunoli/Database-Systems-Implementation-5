#!/bin/bash
echo "All test cases" > output5.txt
./test.out < tcAll.sql >> output5.txt 2 > &1
