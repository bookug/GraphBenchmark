#!/bin/bash
for file in `ls ../watdiv/`
do
	vertexNum=`grep "v" ../watdiv/$file | wc -l`
	echo $vertexNum
	python randht.py $vertexNum > ans.txt
	# veretxLabelNum and edgeLabelNum are both 10, range from 1 to 10
	awk '{num=int($0*1000);print num+1}' ans.txt > 28ruleVertex.txt
	edgeNum=`grep "e" ../watdiv/$file | wc -l`
	python randht.py $edgeNum > ans.txt
	echo $edgeNum
	awk '{num=int($0*1000);print num+1}' ans.txt > 28ruleEdge.txt
	awk  '{if(NR==FNR){s[NR-1]=$1}else{if($1=="v"){print "v "$2" "s[$2]}else{print $0}}}' 28ruleVertex.txt ../watdiv/$file > ans.txt
	echo "replace vetex done"
	# the num 69247 is the original start line of the "e ...", diffrent for each dataset
	awk -v vertexNum=$vertexNum '{if(NR==FNR){s[NR-1]=$1}else{if($1=="e"){print "e "$2" "$3" "s[FNR-vertexNum-2]}else{print $0}}}' 28ruleEdge.txt ans.txt > ../watdiv_g/$file
	#awk  '{if(NR==FNR){s[NR-1]=$1}else{if($1=="e"){print "e "$2" "$3" "FNR" "$vertexNum" "s[FNR-$vertexNum-1]}else{print $0}}}' 28ruleEdge.txt ans.txt > ../watdiv/watdiv10.g
done
