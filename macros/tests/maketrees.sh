#!/bin/bash

## Hi! This scripts changes the run number in the input/output files in the pareeksha_make_trees_gius.C macro,
## replacing the line that contain that number

## ACHTUNG! Make sure you have the correct setting file in pareeksha_make_trees_gius.C before running
## AND that the run number fits in the Form(inp/oututfile) digit-wise (this script and my modification to the
## macro are very stupid, so you have to put the correct number of 0s in the file name pattern)

for i in 195

do

	echo "Processing run $i"

	sed -i "s/Int_t rnum = [0-9]\+/Int_t rnum = ${i}/" /u/gandolfo/c4/c4Root/macros/tests/pareeksha_make_trees_gius.C
	root -b -q pareeksha_make_trees_gius.C
done
