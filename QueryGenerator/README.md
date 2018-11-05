使用方法：

````
	./run data queryInfo [result_directory]

``
其中queryInfo是一个说明查询特点的文件，每行表示一个查询，第一个数字表示查询的节点数目，第二个数字表示边数。以-1结束查询描述文件。
例如，一个查询文件(test.info)可以包含像下面这样：
3 3 10
4 5 10
6 10 10
-1
表示生成三类查询（所有查询都在一个目录中，查询编号连续递增，每类包含十个查询），节点数目依次为3，4，7，边数依次为3，5，10

result_directory 参数是可选的，如果不加，默认是将结果输出到query目录中

---

## NOTICE

Duplicates are removed in the queries generated, but isomorphismic query graphs may exist due to the graph isomorphism in different parts of the data graph.

However, in a big data graph the graph isomorphism case should be rare because we are digging based on a random model.

