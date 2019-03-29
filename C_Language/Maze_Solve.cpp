/*--------------------------------------------------------------------*/
/*       文件名:Maze_Solve      2016.12.12-12.18                      */
/*       功能:随机生成迷宫   暂时手动输入                                         */
/*            通过穷举求解法求出一条迷宫通路路径(或无解)      完美        */
/*            通过递归法求出迷宫所有通路  有问题                            */
/*            以方阵的形式输出迷宫及其通路迷宫中的所有可能的通路      只能打印出一条求解出的路径*/
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#define MAXLEN 10//迷宫包括外墙最大行列数目 
#define TRUE 1 
#define FALSE 0 
#define OK 1 
#define ERROR 0 
#define OVERFLOW -2 
#define STACK_INIT_SIZE 100 //存储空间初始分配量 
typedef int Status; 
typedef struct{ 
    int row; 
    int col; 
}PosType;//迷宫中行列的位置 
typedef struct MazeType{ 
    int row; 
    int col; 
    int arr[MAXLEN][MAXLEN]; 
}MazeType; //迷宫类型 
typedef struct{ 
    int ord; //通道块在路径上的"序号" 
    PosType seat; //通道块在迷宫中的"坐标位置" 
    int di; //从此通道块走向下一通道块的"方向" 
}SElemType;  //栈的元素类型 
typedef struct Stacknode{ 
   SElemType data;  //数据域 
   struct Stacknode *next;  //指针域 
}*LinkStack; 
// ============构建一个空栈S================== 
int InitLinkStack(LinkStack &S) 
{ 
   S=(LinkStack)malloc(sizeof(LinkStack)); //通过malloc函数分配空间 
   if (!S) 
   return ERROR; //如果分配失败，则返回 
   S->next=NULL; 
   return OK; 
} 
//==========判断栈是否为空 ===========================
Status LinkStackEmpty(LinkStack &S) 
{ 
    if (S!=NULL)  
{ 
    if (S->next==NULL) 
	{ 
    return OK; 
	} 
} 
    return ERROR; 
} 
//====插入元素e为新的栈顶元素=========================
Status PushLinkStack(LinkStack &S,SElemType e) 
{ 
    LinkStack q=S; 
    LinkStack m=(LinkStack)malloc(sizeof(LinkStack)); //通过malloc函 数分配空间 
    if (S!=NULL) 
	{ 
    while (q->next!=NULL) 
	{ 
    q=q->next; 
	} 
    m->data=e; 
    m->next=NULL; 
    q->next=m; 
	} 
    return ERROR; 
} 
//==若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR==
Status PopLinkStack(LinkStack &S,SElemType &e) 
{ 
    LinkStack q=S; 
    if (S!=NULL) 
	{ 
    if (q->next!=NULL) //若栈不是空的 
	{ 
    while (q->next->next!=NULL) 
	{ 
    q=q->next;  
	} 
    e=q->next->data; 
    q->next=NULL; 
    return OK; 
	} 
	} 
    return ERROR; 
} 
Status Pass(MazeType MyMaze,PosType CurPos) { 
    if(MyMaze.arr[CurPos.row][CurPos.col]==0) 
    return TRUE; // 如果当前位置是可以通过，返回 
    else return FALSE; // 其它情况返回 
} 
Status FootPrint(MazeType &MyMaze,PosType CurPos){ 
    MyMaze.arr[CurPos.row][CurPos.col]=2; 
    return OK;
} 
void MarkPrint(MazeType &MyMaze,PosType CurPos) { 
    MyMaze.arr[CurPos.row][CurPos.col]=3; 
//return OK;
} 
PosType NextPos(PosType CurPos,int Dir){ 
    PosType ReturnPos; 
    switch (Dir) { 
    case 1:
         ReturnPos.row=CurPos.row;
         ReturnPos.col=CurPos.col+1;
         break;
    case 2:
         ReturnPos.row=CurPos.row+1;
         ReturnPos.col=CurPos.col+1;
         break;
    case 3:
         ReturnPos.row=CurPos.row+1;
         ReturnPos.col=CurPos.col;
         break;
    case 4:
         ReturnPos.row=CurPos.row+1;
         ReturnPos.col=CurPos.col-1;
         break;
    case 5:
         ReturnPos.row=CurPos.row;
         ReturnPos.col=CurPos.col-1;
         break;
    case 6:
         ReturnPos.row=CurPos.row-1;
         ReturnPos.col=CurPos.col-1;
         break;
    case 7:
         ReturnPos.row=CurPos.row-1;
         ReturnPos.col=CurPos.col;
         break;
    case 8:
         ReturnPos.row=CurPos.row-1;
         ReturnPos.col=CurPos.col+1;
         break;

    /*case 1: 
        ReturnPos.row=CurPos.row; 
        ReturnPos.col=CurPos.col+1; 
		//ReturnPos.row=CurPos.row;
		//ReturnPos.col+=1;
        break; 
    case 2: 
        ReturnPos.row=CurPos.row+1; 
        ReturnPos.col=CurPos.col; 
		//ReturnPos.row+=1;
		//ReturnPos.col=ReturnPos.col;
        break; 
    case 3: 
        ReturnPos.row=CurPos.row; 
        ReturnPos.col=CurPos.col-1; 
		//ReturnPos.row=ReturnPos.row;
		//ReturnPos.col-=1;
        break; 
    case 4: 
        ReturnPos.row=CurPos.row-1; 
        ReturnPos.col=CurPos.col; 
		//ReturnPos.row-=1;
		//ReturnPos.col=ReturnPos.col;
        break; */
	} 
    return ReturnPos; 
} 
Status MazePath(MazeType &maze, PosType start, PosType end) {  
// 若迷宫maze中从入口start到出口end的通道，则求得一条存放在栈中 
// （从栈底到栈顶），并返回TRUE；否则返回FALSE 
    LinkStack S,S1; 
    PosType curpos; 
    int curstep; 
    SElemType e; 
    InitLinkStack(S); 
    InitLinkStack(S1); 
    curpos = start; // 设定"当前位置"为"入口位置" 
    curstep = 1; // 探索第一步 
    do{ 
    if(Pass(maze,curpos)) { // 当前位置可通过，即是未曾走到过的通道块 
    FootPrint(maze,curpos); // 留下足迹 
    e.ord = curstep; 
    e.seat= curpos; 
    e.di =1; 
    PushLinkStack(S,e); // 加入路径 
    if(curpos.row == end.row && curpos.col==end.col){ //到达终点(出口)
    while(!LinkStackEmpty(S)){ 
    PopLinkStack(S,e); 
    PushLinkStack(S1,e); 
	} 
    printf("迷宫的路径："); 
    while(!LinkStackEmpty(S1)){ 
    PopLinkStack(S1,e); 
    printf("第%d步：(%d,%d,%d) ",e.ord,e.seat,e.di); 
	} 
    return (TRUE); // 到达终点（出口） 
	} 
    curpos = NextPos(curpos, 1); // 下一位置是当前位置 的东邻 
    curstep++; // 探索下一步 
	} 
    else { // 当前位置不能通过 
    if (!LinkStackEmpty(S)) { 
    PopLinkStack(S,e); 
    while (e.di==8 && !LinkStackEmpty(S)) { 
    MarkPrint(maze,e.seat); //留下不能通过的标记 
    PopLinkStack(S,e); //并退回 一步 
    curstep--; 
	} // while 
    if (e.di<8) { 
    e.di++; 
    PushLinkStack(S,e); // 换下一个方向探索 
    curpos = NextPos(e.seat,e.di); // 当前位置设为新方向的相邻块 
	} // if 
	} // if 
} // else 
} 
	while (!LinkStackEmpty(S) ); 
    printf("此迷宫无通路!\n"); 
    return FALSE; 
} // MazePath 
//========初始化迷宫========================= 
Status InitMaze(MazeType &maze){ 
    int i,j; 
    printf("请输入迷宫的行和列数: "); 
    scanf("%d,%d",&maze.row,&maze.col); 
    printf("请输入迷宫(0以表示可走,1表示有障碍)：\n"); 
    for(i=1;i<=maze.row;i++){ 
    for(j=1;j<=maze.col;j++)
    maze.arr[i][j]=rand()%2; 
    //scanf("%d",&maze.arr[i][j]); 
	} 
    for(i=0;i<=maze.col+1;i++){//迷宫行外墙 
    maze.arr[0][i]=1; 
    maze.arr[maze.row+1][i]=1; 
	}//for 
    for(i=1;i<=maze.row;i++){//迷宫列外墙 
    maze.arr[i][0]=1; 
    maze.arr[i][maze.col+1]=1; 
	} 
    return OK; 
} 
//=========以方阵形式输出迷宫及其通路============= 
void PrintMaze(MazeType &maze){ 
//将标记路径信息的迷宫输出到终端(包括外墙) 
    int i,j; 
    for(i=0;i<=maze.row+1;i++){ 
    for(j=0;j<=maze.col+1;j++) 
    printf("%2d",maze.arr[i][j]);//输出迷宫//当前位置的标记  
    printf("\n\n"); 
 } 
}//PrintMaze 
//============递归算法============================
LinkStack L,L1; 
void MazePath_Recursion(MazeType &maze,PosType cur,PosType end,int curstep) 
{ 
    int i; 
    SElemType e; 
    PosType next; // 下一个位置 
    // {行增量,列增量},移动方向,依次为东南西北 
    PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}};  
    for(i=0;i<=3;i++) // 依次试探东南西北四个方向 
	{ 
    next.row=cur.row+direc[i].row; 
    next.col=cur.col+direc[i].col; 
    if(maze.arr[next.row][next.col]==0) // 是通路 
	{ 
    e.seat=next; 
    PushLinkStack(L,e); 
    maze.arr[next.row][next.col]=++curstep; 
    if(next.row != end.row || next.col != end.col) // 没到终 点 
    MazePath_Recursion(maze,next,end,1); // 试探下一点(递归 调用) 
    else{ 
    printf("\n"); 
    printf("迷宫的路径："); 
    while(!LinkStackEmpty(L)){ 
    PopLinkStack(L,e); 
    PushLinkStack(L1,e); 
	} 
    while(!LinkStackEmpty(L1)){ 
    PopLinkStack(L1,e); 
    printf("(%d,%d ) ",e.seat); 
	} 
	} 
    maze.arr[next.row][next.col]=0; // 恢复为通路，试探下一条 路 
   curstep--; 
	}
	} 
} 
int main(){ 
    MazeType maze; 
    PosType start,end; 
    InitLinkStack(L); 
    InitLinkStack(L1); 
    int n; 
    printf("\n\t\t++++++++++++++++++++++++++++++++++++++++++"); 
    printf("\n\t\t|       1.创建一个迷宫                   |"); 
    printf("\n\t\t|       2.求出迷宫通路的路径             |"); 
    printf("\n\t\t|       3.递归求出路径                   |"); 
    printf("\n\t\t|       4.方阵形式输出迷宫及其通路       |"); 
    printf("\n\t\t++++++++++++++++++++++++++++++++++++++++++\n"); 
    while(1){ 
    printf("请选择: "); 
    scanf("%d",&n); 
    switch(n){ 
    case 1: 
		InitMaze(maze); 
        printf("\n所输入的迷宫为:\n\n"); 
        PrintMaze(maze); 
        printf("输入入口的横坐标,纵坐标:\n"); 
        scanf("%d,%d",&start.row,&start.col); 
        printf("输入出口的横坐标,纵坐标:\n"); 
        scanf("%d,%d",&end.row,&end.col); 
        break; 
    case 2: 
		MazePath(maze,start,end); 
        printf("\n"); 
        break; 
    case 3: 
		MazePath_Recursion(maze,start,end,1); 
        printf("\n"); 
        break; 
    case 4: 
		printf("\n以方阵形式输出迷宫及其通路:(2:表示可通路径,3:表示死胡同):\n"); 
        PrintMaze(maze); 
        break; 
} 
} 
// return OK;
}
