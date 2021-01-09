import matplotlib.pyplot as plt
import math

dataset_name="dblp"
igraph_path="../all_format_0/"+dataset_name+"_2.igraph"
xmin_yeast=0.8
xmin_human=1.1
xmin_email_enron=1
xmin_dblp=1.09

if(dataset_name=="yeast"):
    xmin=xmin_yeast
elif(dataset_name=="human"):
    xmin=xmin_human
elif(dataset_name=="email_enron"):
    xmin=xmin_email_enron
elif(dataset_name=="dblp"):
    xmin=xmin_dblp

def plot_distr_func(_degree2cnt):
    deg_list=list(_degree2cnt.keys())
    deg_list.sort(reverse=True)
    cnt_list=[]
    tot_cnt=0
    for tmp_deg in deg_list:
        tmp_cnt=_degree2cnt[tmp_deg]
        cnt_list.append(tmp_cnt)
        tot_cnt+=tmp_cnt
    log_p_list=[]
    for tmp_cnt in cnt_list:
        tmp_p=float(tmp_cnt)/tot_cnt
        log_p_list.append(math.log(tmp_p))
    plt.plot(deg_list,log_p_list,'.')
    plt.xlabel("degree")
    plt.ylabel("log prob")
    plt.title(dataset_name+" dataset")
    plt.legend()
    plt.savefig("distribution_"+dataset_name+".png")
    plt.show()
    print("max degree: "+str(max_degree))

def plot_comparison(_degree2cnt,_vnum,_alpha):
    deg_list=list(_degree2cnt.keys())
    deg_list.sort(reverse=False)
    cnt_list=[]
    tot_cnt=0
    for tmp_deg in deg_list:
        tmp_cnt=_degree2cnt[tmp_deg]
        cnt_list.append(tmp_cnt)
        tot_cnt+=tmp_cnt
    log_p_list=[]
    for tmp_cnt in cnt_list:
        tmp_p=float(tmp_cnt)/tot_cnt
        log_p_list.append(math.log(tmp_p))
    log_deg_list=[]
    for tmp_deg in deg_list:
        log_deg_list.append(math.log(tmp_deg))
    fitting_log_p_list=[]
    for tmp_log_deg in log_deg_list:
        fitting_log_p=math.log(_alpha-1)-_alpha*tmp_log_deg
        fitting_log_p_list.append(fitting_log_p)

    plt.plot(log_deg_list,log_p_list,'.',label="raw")
    plt.plot(log_deg_list,fitting_log_p_list,linestyle="-",label="fitting")
    plt.xlabel("log degree")
    plt.ylabel("log prob")
    plt.legend()
    plt.title(dataset_name+" alpha= "+str(_alpha))
    plt.savefig("power_distr_compar_"+dataset_name+".png")
    plt.show()


degree_map={}
with open(igraph_path,'r') as edge_file:
    while True:
        tmp_line=edge_file.readline()
        if not tmp_line:
            break
        tmp_edge=tmp_line.strip().split()
        ch=str(tmp_line[0])
        if(ch!="e"):
            continue
        vertex0=int(tmp_edge[1])
        vertex1=int(tmp_edge[2])
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


deg_log_sum=0
max_degree=0
degree2cnt={}
v_num=0
for vertex_id in degree_map:
    tmp_degree=degree_map[vertex_id]
    if(tmp_degree<xmin):
        continue
    v_num+=1
    deg_log_sum+=math.log(tmp_degree)
    if(tmp_degree>max_degree):
        max_degree=tmp_degree
    if tmp_degree in degree2cnt:
        degree2cnt[tmp_degree]+=1
    else:
        degree2cnt[tmp_degree]=1

deg_log_sum-=v_num*math.log(xmin)
alpha=float(v_num)/deg_log_sum+1
print(dataset_name+" alpha: "+str(alpha))

# plot_distr_func(degree2cnt)
plot_comparison(degree2cnt,v_num,alpha)






    