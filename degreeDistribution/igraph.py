# WARN: this file does not generate right distribution.
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

#TODO: parameters and set title...
#NOTICE: we can also generate a table then draw with Matlab

degree_map={}
with open("dbpedia1B.g",'r') as edge_file:
    while True:
        tmp_line=edge_file.readline()
        if not tmp_line:
            break
        tmp_edge=tmp_line.strip().split()
        if tmp_edge[0] != "e":
            continue
        vertex0=tmp_edge[1]
        vertex1=tmp_edge[2]
        if vertex0 in degree_map:
            degree_map[vertex0]+=1
        else:
            degree_map[vertex0]=1
        if vertex1 in degree_map:
            degree_map[vertex1]+=1
        else:
            degree_map[vertex1]=1

# print(len(degree_map))
# for tmp_pair in degree_map.items():
#     print("vertex id: "+str(tmp_pair[0])+' '+"degree: "+str(tmp_pair[1]))

# vertex_cnt=len(degree_map)
# degree_list=list(degree_map.values())
# degree_list.sort(reverse=True)
# plt.plot(range(vertex_cnt),degree_list)

degree2cnt={}
for vertex_id in degree_map:
    tmp_degree=degree_map[vertex_id]
    if tmp_degree in degree2cnt:
        degree2cnt[tmp_degree]+=1
    else:
        degree2cnt[tmp_degree]=1

# deg_list=list(degree2cnt.keys())
# deg_list.sort(reverse=True)
# cnt_list=[]
# for tmp_deg in deg_list:
    # cnt_list.append(degree2cnt[tmp_deg])

max_deg=max(degree2cnt.keys())
print("max_deg: %d" % max_deg)
deg_list=range(1, max_deg+1)
cnt_list=[]
for tmp_deg in deg_list:
    if tmp_deg in degree2cnt:
        cnt_list.append(degree2cnt[tmp_deg])
    else:
        cnt_list.append(0)

fig, ax = plt.subplots()
ax.plot(deg_list,cnt_list)
ax.set(xlabel='degree', ylabel='count', title='degree distribution')
ax.grid()
# plt.plot(deg_list,cnt_list,'.')
# plt.xlabel("degree")
# plt.ylabel("count")
# plt.title("facebook dataset")
# fig.savefig("distribution_facebook.jpg")
fig.savefig("degree.png")
# plt.show()




    
