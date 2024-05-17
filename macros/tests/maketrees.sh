#!/bin/bash

for i in 115 118 120

do

	echo "Processing run $i"

	sed -i "s/Int_t rnum = [0-9]\+/Int_t rnum = ${i}/" /u/gandolfo/c4/c4Root/macros/tests/pareeksha_make_trees_gius.C
	root -b -q pareeksha_make_trees_gius.C
done
