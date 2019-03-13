#!/bin/bash

#WARN: each a time, not support parallelism in the same directory
#NOTICE: only add vertex labels for RDF datasets
#WARN: the data file placed in ./data/ will be overwrite

#settings
vLabelNum=1000
for file in `ls ./data/`
do
	vertexNum=`grep "v" ./data/$file | wc -l`
	echo $vertexNum
	python randht.py $vertexNum > ans.txt
	# veretxLabelNum and edgeLabelNum are both 10, range from 1 to 10
	awk -v vLabelNum=$vLabelNum '{num=int($0*vLabelNum);print num+1}' ans.txt > 28ruleVertex.txt
    mv ./data/$file ans.txt
    awk -v vLabelNum=$vLabelNum '{if(NR==FNR){s[NR-1]=$1}else{if(FNR==2){print $1" "$2" "vLabelNum" "$4}else if($1=="v"){print "v "$2" "s[$2]}else{print $0}}}' 28ruleVertex.txt ans.txt > ./data/$file
	echo "replace vetex done"
done
