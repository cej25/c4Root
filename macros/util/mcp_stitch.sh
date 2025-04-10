#!/bin/bash
while true
 do 
 cd /461248
  list=$(ls -tr *.lmd)
  for file in $list
  do
	cd /u/despec/lustre/gamma/s092_s143_files/ts/
	if test -f "$file"; then
    	echo "time-stitched $file exists, waiting for a new file to come in."
	cd /u/despec/lustre/despec/s092_s143/
	continue
	else
	echo "time-stitched $file does not exists, proceed with time stitching:"
	cd ~/DAQ/ucesb_may24/
 	./despec /u/despec/lustre/despec/s092_s143/$file --time-stitch=wr,3000 --output=wp,/u/despec/lustre/gamma/s092_s143_files/ts/$file
	fi
	cd /u/despec/lustre/despec/s092_s143/
	
	
  done
  sleep 300
done


  
