/*
二分图的定义：如果一个图所有顶点可以被分为X和Y两个集合，并且所有边的两个顶点恰好
一个属于集合X，另一个属于集合Y，即每个集合内顶点没有边相连，那么此图就是二分图
步骤如下：
1.首先从任意一个未被配对的点u开始，从点u的边中任意选一条边(假设这条边是u->v)
开始配对。如果此时v还没有被配对，则配对成功，此时便找到一条增广路(只不过这条增广路
比较简单)。如果此时v已经被配对，那就要尝试进行连锁反应。如果尝试成功了，则找到一条增广路，
此时更新原来的配对关系，这里要用一个数组match来记录配对关系，比如点v与点u配对了，就记做
match[v] = u。配对成功后，记得要将配对数加1.配对的过程我们可以通过深度优先搜索来实现，
当然广度优先搜索也可以。
2.如果刚才所选的边配对失败，要从点u的边中重新选一条边，进行尝试。直到点
u配对成功，或者尝试过点u所有的边为止。
3.接下来继续对剩下没有被配对的点一一进行配对，直到所有的点都尝试完毕，找不到
新的增广路为止。
4.输出配对数
*/
#include "stdio.h"
int e[101][101];
int match[101];
int book[101];
int n,m;
int dfs(int u)
{
	int i;
	for(i = 1;i <=n;i++)
	{
		if(book[i] == 0 && e[u][i] == 1)
		{
			book[i] = 1;//标记i已经被访问过
			//如果点i未被配对或者找到了新的配对
			if(match[i] == 0 || dfs(match[i]))
			{
				//更新配对关系
				match[i] = u;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	int i,j,t1,t2,sum = 0;
	scanf("%d %d",&n,&m);//n个点m条边

	for(i = 1;i <= m;i++)
	{
		scanf("%d%d",&t1,&t2);
		e[t1][t2] =1;
	}

	for(i = 1;i <= n;i++)
	{
		match[i] = 0;
	}

	for(i = 1;i <= n;i++)
	{
		for(j = 1;j <= n;j++)
		{
			book[j] = 0;//清空上次搜索时的标记
		}
		if(dfs(i))
		{
			sum++;//寻找增广路，如果找到，匹配数加1
		}
	}
	printf("%d\n",sum );
	getchar();getchar();
	return 0;
}
/*
示例输入：
3 5			//第一行两个整数n和m，n表示男生和女生的人数均为n，男女生的编号也均为1~n。m表示接下来就m条关系
1 1 		//接下来m行，每行两个整数u和v，表示u号男生可以和v号女生坐在一起
1 2
2 2
2 3
3 1
示例输出：
3
*/