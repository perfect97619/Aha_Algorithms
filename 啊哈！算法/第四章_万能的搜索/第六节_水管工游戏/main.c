/*
游戏规则：
一块矩形土地被分为N*M的单位正方形，现在这块土地上已经埋设有一些水管，水管将从坐标为(1,1)的
矩形土地的左上角左部边缘，延伸到坐标为(N,M)的矩形土地的右下角右部边缘，水管只有弯管和直管
两种管道，每种管道占据一个单位正方形土地，可以旋转管道，使其构成一个管道系统，即创造一条从
(1,1)到(N,M)的连通管道，标有树木的地方表示这里没有管道。
定义：
0表示没有管道，1表示上右型管道，2表示下右型管道，3表示下左型管道，4表示上左型管道，
5表示左右型管道，6表示上下型管道，5~6表示直管的两种状态，1~4表示弯管的四种状态
进水口在左边用1表示，进水口在上边用2表示，进水口在右边用3表示，进水口在下边用4表示
使用深度优先搜索来解决，重点在于对弯管和直管时面对四种不同进水口时的解决办法
如果能找到解决方案，输出解决路径，不能则输出impossible
*/
#include "stdio.h"
int a[51][51];//假设土地的大小不超过50*50
int book[51][51],n,m,flag = 0;
struct note
{
	int x;//横坐标
	int y;//纵坐标
}s[100];//与struct note s[100];作用想同
int top;
void dfs(int x,int y,int front)
{
	int i;
	//判断是否到达终点，请注意这里y的坐标是m+1，想一想为什么
	if(x == n && y == m + 1)
	{
		flag = 1;//找到铺设方案
		for(i = 1;i <= top;i++)
		{
			printf("(%d,%d)",s[i].x,s[i].y);//打印出路径
		}
		return;
	}
	//判断是否越界
	if(x < 1 || x > n || y < 1 || y > m)
	{
		return;
	}
	//判断设个管道是否在路径中已经使用过
	if(book[x][y] == 1)
	{
		return;
	}
	book[x][y] = 1;//标记这个管道已使用

	//将当前尝试的坐标入栈
	top++;
	s[top].x = x;
	s[top].y = y;

	//当前水管是直管的情况
	if(a[x][y] >= 5 && a[x][y] <= 6)
	{
		if(front == 1)//当前管进水口在左边的情况
		{
			dfs(x,y + 1,1);//当前管只能使用5号管，左右型管道，且下个管道应该在当前管道的右侧则坐标为y+1，为左进
		}
		if(front == 2)//当前管进水口在上边的情况
		{
			dfs(x + 1,y,2);//当前管只能使用6号管，上下型管道，且下个管道应该在当前管道的下侧则坐标为x+1，为上进
		}
		if(front == 3)//当前管进水口在右边的情况
		{
			dfs(x,y - 1,3);//当前管只能使用5号管，左右型管道，且下个管道应该在当前管道的左侧则坐标为y-1，为右进
		}
		if(front == 4)//当前管进水口在左边的情况
		{
			dfs(x - 1,y,1);//当前管只能使用6号管，上下型管道，且下个管道应该在当前管道的上侧则坐标为x-1，为下进
		}
	}

	//当前水管为弯管的情况
	if(a[x][y] >= 1 && a[x][y] <= 4)
	{
		if(front == 1)//当前管进水口在左边的情况
		{
			dfs(x + 1,y,2);//当前管使用3号管，左下型管道，且下个管道应该在当前管道的下侧则坐标为x+1，为上进
			dfs(x - 1,y,4);//当前管使用4号管，左上型管道，且下个管道应该在当前管道的上侧则坐标为x-1，为下进
		}
		if(front == 2)//当前管进水口在上边的情况
		{
			dfs(x,y + 1,1);//当前管只能使用1号管，上右型管道，且下个管道应该在当前管道的右侧则坐标为y+1，为左进
			dfs(x,y - 1,3);//当前管只能使用4号管，上左型管道，且下个管道应该在当前管道的左侧则坐标为y-1，为右进
		}
		if(front == 3)//当前管进水口在右边的情况
		{
			dfs(x + 1,y,2);//当前管只能使用2号管，右下型管道，且下个管道应该在当前管道的下侧则坐标为x+1，为上进
			dfs(x - 1,y,4);//当前管只能使用1号管，右上型管道，且下个管道应该在当前管道的上侧则坐标为x-1，为下进
		}
		if(front == 4)//当前管进水口在左边的情况
		{
			dfs(x,y + 1,1);//当前管只能使用2号管，下右型管道，且下个管道应该在当前管道的右侧则坐标为y+1，为左进
			dfs(x,y - 1,3);//当前管只能使用3号管，下左型管道，且下个管道应该在当前管道的左侧则坐标为y-1，为右进
		}
	}
	book[x][y] = 0;//取消标记
	top--;//将当前尝试的坐标出栈
	return;
}

int main() 
{
	int i,j,num = 0;
	scanf("%d %d",&n,&m);
	//读入游戏地图
	for(i = 1;i <= n;i++)
	{
		for(j = 1;j <= m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	//开始搜索，从(1,1)开始，进水方向也是1
	dfs(1,1,1);
	//判断是否找到铺设方案
	if(flag == 0)
	{
		printf("impossible\n");
	}
	getchar();getchar();
	return 0;
}
/*
示例输入：
5 4
5 3 5 3
1 5 3 0
2 3 5 1
6 1 1 5
1 5 5 4
示例输出：
(1,1)(1,2)(2,2)(3,2)(3,3)(3,4)(4,4)(5,4)
*/
