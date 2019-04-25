使用方法：


	./run.exe query_pattern data_path query_requirement_path [result_directory]

	(query_pattern: line, rand)


其中queryInfo是一个说明查询特点的文件，每行表示一个查询，第一个数字表示查询的节点数目，第二个数字表示边数。以-1结束查询描述文件。
例如，一个查询文件(test.info)可以包含像下面这样：
3 3 10
4 5 10
6 10 10
-1
表示生成三类查询（所有查询都在一个目录中，查询编号连续递增，每类包含十个查询），节点数目依次为3，4，7，边数依次为3，5，10

result_directory 参数是可选的，如果不加，默认是将结果输出到query目录中

---

## Degree

In real graphs, edge num is usually 2x-5x of node num.

As for sparse graphs, we suggesting generating queries whose edge num is 2n-2.
Otherwise, generating may fail.

---

## NOTICE

Duplicates are removed in the queries generated, but isomorphismic query graphs may exist due to the graph isomorphism in different parts of the data graph.

However, in a big data graph the graph isomorphism case should be rare because we are digging based on a random model.


We consider different query patterns.
## line query
For line query, we only need to specify how many vertices in the query and do not need to specify the edge number. The query requirements(query info) file will indicate query vertices and query num in each line.
For example,
5 3
6 3
which means we need 3 querys which have 5 vertices and 3 queries which have 6 vertices.
eg:

	./run.exe line data/delaunay_prev.txt query_requirement/line_query_request.txt

## clique query
The query requirements(query info) file will indicate query vertices and query num in each line.
For example,
5 3
6 3
which means we need 3 querys which have 5 vertices and 3 queries which have 6 vertices.
eg:

	./run.exe clique data/delaunay_prev.txt query_requirement/clique_query_request.txt

## triangle query
Triangle is a clique which has 3 vertices.
Use clique query instead.

## ring query
Number of query edges is the same of number of query vertices
The query requirements(query info) file will indicate query vertices and query num in each line.
For example,
5 3
6 3
which means we need 3 querys which have 5 vertices and 3 queries which have 6 vertices.
eg:

	./run.exe ring data/delaunay_prev.txt query_requirement/ring_query_requirement.txt