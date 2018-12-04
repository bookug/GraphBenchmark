# GraphBenchmark

a benchmark for generating all kinds of graphs and queries

---

### Real-life Dataset

http://snap.stanford.edu/data/

http://vlado.fmf.uni-lj.si/pub/networks/data/

http://konect.uni-koblenz.de/networks/


---

### R-MAT Generator

https://www.boost.org/doc/libs/1_68_0/libs/graph_parallel/doc/html/rmat_generator.html

---

### RDF Generator

WatDiv

LUBM

BSBM

https://github.com/graphMark/gmark

http://konect.uni-koblenz.de/networks/amazon-ratings

stream

https://firehose.sandia.gov/

---

### Query Generator

based on digging to ensure that only queries with answers are generated

使用方法：
	./run data queryInfo
其中queryInfo是一个说明查询特点的文件，每行表示一个查询，第一个数字表示查询的节点数目，第二个数字表示边数。以-1结束查询描述文件。
例如，一个查询文件可以包含像下面这样：
3 3
4 5
7 10
-1
表示生成三个查询，节点数目依次为3，4，7，边数依次为3，5，10.

---

### RDF2Graph

transform RDF datasets(both real-life and synthetic) to the graph format we need


---

### open academic

https://www.openacademic.ai/oag/

---

### GTgraph

http://www.cse.psu.edu/~kxm85/software/GTgraph/

---

### iGraph

many small datasets

igraph is a collection of network analysis tools with the emphasis on efficiency, portability and ease of use. igraph is open source and free. igraph can be programmed in R, Python and C/C++. 

http://igraph.org/

--

### Sparse Matrix

https://sparse.tamu.edu/

---

### HPRD

http://www.hprd.org/download/

yeast 

human

---

