# labels must be positive
# use grep "v" xxx.g|wc -l and grep "e" xxx.g|wc -l to count vertexNum and edgeNum
# add "veretxNum edgeNum 10 10" to the dataset below the "t # 0"
python randht.py 100 > ans.txt
# veretxLabelNum and edgeLabelNum are both 10, range from 1 to 10
awk '{num=int($0*10);print num+1}' ans.txt > 28rule_100_vertex.txt
python randht.py 10000 > ans.txt
awk '{num=int($0*10);print num+1}' ans.txt > 28rule_10000_edge.txt
awk  '{if(NR==FNR){s[NR-1]=$1}else{if($1=="v"){print "v "$2" "s[$2]}else{print $0}}}' 28rule_69244.txt ../enron/enron.g > ans.txt
# the num 69247 is the original start line of the "e ...", diffrent for each dataset
awk  '{if(NR==FNR){s[NR-1]=$1}else{if($1=="e"){print "e "$2" "$3" "s[FNR-69247]}else{print $0}}}' 28rule_274608.txt ans.txt > enron.g

# to generate 10 labels for vertex and edge, in 80/20 rule
awk -F " " 'BEGIN{srand();}{label=int(rand()*10);if(label<8){label=int(label/4)+1}else{label=(label-8)*4+3+int(rand()*4)}if($1=="v"){print $1" "$2" "label}else if($1=="e"){print $1" "$2" "$3" "label}else{print $0}}' largeG/largeG.g > temp.g
# to generate 100 labels for vertex and edge, in 80/20 rule
 awk -F " " 'BEGIN{srand();}{label=int(rand()*100);if(label<80){label=int(label/4)+1}else{label=(label-80)*4+21+int(rand()*4)}if($1=="v"){print $1" "$2" "label}else if($1=="e"){print $1" "$2" "$3" "label}else{print $0}}' largeG/largeG.g > temp.g

# to generate 10 labels for vertex and edge, in uniform distribution 
 awk -F " " 'BEGIN{srand();}{if($1=="v"){label=int(rand()*10+1);print $1" "$2" "label}else if($1=="e"){label=int(rand()*10+1);print $1" "$2" "$3" "label}}' sample.g > sample.txt 
