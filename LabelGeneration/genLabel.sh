#!/bin/bash

#WARN: each a time, not support parallelism in the same directory
#WARN: the data file placed in ./data/ will be overwrite

#settings
vLabelNum=10
eLabelNum=100
for file in `ls ./data/`
do
	vertexNum=`grep "v" ./data/$file | wc -l`
	echo $vertexNum
	python randht.py $vertexNum > ans.txt
	# veretxLabelNum and edgeLabelNum are both 10, range from 1 to 10
	awk -v vLabelNum=$vLabelNum '{num=int($0*vLabelNum);print num+1}' ans.txt > 28ruleVertex.txt
	edgeNum=`grep "e" ./data/$file | wc -l`
	python randht.py $edgeNum > ans.txt
	echo $edgeNum
	awk -v eLabelNum=$eLabelNum '{num=int($0*eLabelNum);print num+1}' ans.txt > 28ruleEdge.txt
	awk  '{if(NR==FNR){s[NR-1]=$1}else{if($1=="v"){print "v "$2" "s[$2]}else{print $0}}}' 28ruleVertex.txt ./data/$file > ans.txt
	echo "replace vetex done"
	# the num 69247 is the original start line of the "e ...", diffrent for each dataset
    awk -v vertexNum=$vertexNum -v vLabelNum=$vLabelNum -v eLabelNum=$eLabelNum '{if(NR==FNR){s[NR-1]=$1}else{if(FNR==2){print $1" "$2" "vLabelNum" "eLabelNum}else if($1=="e"){print "e "$2" "$3" "s[FNR-vertexNum-3]}else{print $0}}}' 28ruleEdge.txt ans.txt > ./data/$file
	#awk  '{if(NR==FNR){s[NR-1]=$1}else{if($1=="e"){print "e "$2" "$3" "FNR" "$vertexNum" "s[FNR-$vertexNum-1]}else{print $0}}}' 28ruleEdge.txt ans.txt > ../watdiv/watdiv10.g
	echo "replace edge done"
done
