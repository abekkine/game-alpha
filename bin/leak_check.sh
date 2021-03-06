#!/bin/bash
BINFILE=$1
SUPPFILE=$2

valgrind --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --error-limit=no --suppressions=$SUPPFILE --gen-suppressions=all --log-file=valgrind.log $BINFILE

cat valgrind.log | ./parse_sup.sh > new.supp

