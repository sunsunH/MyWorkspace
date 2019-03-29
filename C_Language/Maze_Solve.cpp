/*--------------------------------------------------------------------*/
/*       �ļ���:Maze_Solve      2016.12.12-12.18                      */
/*       ����:��������Թ�   ��ʱ�ֶ�����                                         */
/*            ͨ�������ⷨ���һ���Թ�ͨ··��(���޽�)      ����        */
/*            ͨ���ݹ鷨����Թ�����ͨ·  ������                            */
/*            �Է������ʽ����Թ�����ͨ·�Թ��е����п��ܵ�ͨ·      ֻ�ܴ�ӡ��һ��������·��*/
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#define MAXLEN 10//�Թ�������ǽ���������Ŀ 
#define TRUE 1 
#define FALSE 0 
#define OK 1 
#define ERROR 0 
#define OVERFLOW -2 
#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������ 
typedef int Status; 
typedef struct{ 
    int row; 
    int col; 
}PosType;//�Թ������е�λ�� 
typedef struct MazeType{ 
    int row; 
    int col; 
    int arr[MAXLEN][MAXLEN]; 
}MazeType; //�Թ����� 
typedef struct{ 
    int ord; //ͨ������·���ϵ�"���" 
    PosType seat; //ͨ�������Թ��е�"����λ��" 
    int di; //�Ӵ�ͨ����������һͨ�����"����" 
}SElemType;  //ջ��Ԫ������ 
typedef struct Stacknode{ 
   SElemType data;  //������ 
   struct Stacknode *next;  //ָ���� 
}*LinkStack; 
// ============����һ����ջS================== 
int InitLinkStack(LinkStack &S) 
{ 
   S=(LinkStack)malloc(sizeof(LinkStack)); //ͨ��malloc��������ռ� 
   if (!S) 
   return ERROR; //�������ʧ�ܣ��򷵻� 
   S->next=NULL; 
   return OK; 
} 
//==========�ж�ջ�Ƿ�Ϊ�� ===========================
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
//====����Ԫ��eΪ�µ�ջ��Ԫ��=========================
Status PushLinkStack(LinkStack &S,SElemType e) 
{ 
    LinkStack q=S; 
    LinkStack m=(LinkStack)malloc(sizeof(LinkStack)); //ͨ��malloc�� ������ռ� 
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
//==��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR==
Status PopLinkStack(LinkStack &S,SElemType &e) 
{ 
    LinkStack q=S; 
    if (S!=NULL) 
	{ 
    if (q->next!=NULL) //��ջ���ǿյ� 
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
    return TRUE; // �����ǰλ���ǿ���ͨ�������� 
    else return FALSE; // ����������� 
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
// ���Թ�maze�д����start������end��ͨ���������һ�������ջ�� 
// ����ջ�׵�ջ������������TRUE�����򷵻�FALSE 
    LinkStack S,S1; 
    PosType curpos; 
    int curstep; 
    SElemType e; 
    InitLinkStack(S); 
    InitLinkStack(S1); 
    curpos = start; // �趨"��ǰλ��"Ϊ"���λ��" 
    curstep = 1; // ̽����һ�� 
    do{ 
    if(Pass(maze,curpos)) { // ��ǰλ�ÿ�ͨ��������δ���ߵ�����ͨ���� 
    FootPrint(maze,curpos); // �����㼣 
    e.ord = curstep; 
    e.seat= curpos; 
    e.di =1; 
    PushLinkStack(S,e); // ����·�� 
    if(curpos.row == end.row && curpos.col==end.col){ //�����յ�(����)
    while(!LinkStackEmpty(S)){ 
    PopLinkStack(S,e); 
    PushLinkStack(S1,e); 
	} 
    printf("�Թ���·����"); 
    while(!LinkStackEmpty(S1)){ 
    PopLinkStack(S1,e); 
    printf("��%d����(%d,%d,%d) ",e.ord,e.seat,e.di); 
	} 
    return (TRUE); // �����յ㣨���ڣ� 
	} 
    curpos = NextPos(curpos, 1); // ��һλ���ǵ�ǰλ�� �Ķ��� 
    curstep++; // ̽����һ�� 
	} 
    else { // ��ǰλ�ò���ͨ�� 
    if (!LinkStackEmpty(S)) { 
    PopLinkStack(S,e); 
    while (e.di==8 && !LinkStackEmpty(S)) { 
    MarkPrint(maze,e.seat); //���²���ͨ���ı�� 
    PopLinkStack(S,e); //���˻� һ�� 
    curstep--; 
	} // while 
    if (e.di<8) { 
    e.di++; 
    PushLinkStack(S,e); // ����һ������̽�� 
    curpos = NextPos(e.seat,e.di); // ��ǰλ����Ϊ�·�������ڿ� 
	} // if 
	} // if 
} // else 
} 
	while (!LinkStackEmpty(S) ); 
    printf("���Թ���ͨ·!\n"); 
    return FALSE; 
} // MazePath 
//========��ʼ���Թ�========================= 
Status InitMaze(MazeType &maze){ 
    int i,j; 
    printf("�������Թ����к�����: "); 
    scanf("%d,%d",&maze.row,&maze.col); 
    printf("�������Թ�(0�Ա�ʾ����,1��ʾ���ϰ�)��\n"); 
    for(i=1;i<=maze.row;i++){ 
    for(j=1;j<=maze.col;j++)
    maze.arr[i][j]=rand()%2; 
    //scanf("%d",&maze.arr[i][j]); 
	} 
    for(i=0;i<=maze.col+1;i++){//�Թ�����ǽ 
    maze.arr[0][i]=1; 
    maze.arr[maze.row+1][i]=1; 
	}//for 
    for(i=1;i<=maze.row;i++){//�Թ�����ǽ 
    maze.arr[i][0]=1; 
    maze.arr[i][maze.col+1]=1; 
	} 
    return OK; 
} 
//=========�Է�����ʽ����Թ�����ͨ·============= 
void PrintMaze(MazeType &maze){ 
//�����·����Ϣ���Թ�������ն�(������ǽ) 
    int i,j; 
    for(i=0;i<=maze.row+1;i++){ 
    for(j=0;j<=maze.col+1;j++) 
    printf("%2d",maze.arr[i][j]);//����Թ�//��ǰλ�õı��  
    printf("\n\n"); 
 } 
}//PrintMaze 
//============�ݹ��㷨============================
LinkStack L,L1; 
void MazePath_Recursion(MazeType &maze,PosType cur,PosType end,int curstep) 
{ 
    int i; 
    SElemType e; 
    PosType next; // ��һ��λ�� 
    // {������,������},�ƶ�����,����Ϊ�������� 
    PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}};  
    for(i=0;i<=3;i++) // ������̽���������ĸ����� 
	{ 
    next.row=cur.row+direc[i].row; 
    next.col=cur.col+direc[i].col; 
    if(maze.arr[next.row][next.col]==0) // ��ͨ· 
	{ 
    e.seat=next; 
    PushLinkStack(L,e); 
    maze.arr[next.row][next.col]=++curstep; 
    if(next.row != end.row || next.col != end.col) // û���� �� 
    MazePath_Recursion(maze,next,end,1); // ��̽��һ��(�ݹ� ����) 
    else{ 
    printf("\n"); 
    printf("�Թ���·����"); 
    while(!LinkStackEmpty(L)){ 
    PopLinkStack(L,e); 
    PushLinkStack(L1,e); 
	} 
    while(!LinkStackEmpty(L1)){ 
    PopLinkStack(L1,e); 
    printf("(%d,%d ) ",e.seat); 
	} 
	} 
    maze.arr[next.row][next.col]=0; // �ָ�Ϊͨ·����̽��һ�� · 
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
    printf("\n\t\t|       1.����һ���Թ�                   |"); 
    printf("\n\t\t|       2.����Թ�ͨ·��·��             |"); 
    printf("\n\t\t|       3.�ݹ����·��                   |"); 
    printf("\n\t\t|       4.������ʽ����Թ�����ͨ·       |"); 
    printf("\n\t\t++++++++++++++++++++++++++++++++++++++++++\n"); 
    while(1){ 
    printf("��ѡ��: "); 
    scanf("%d",&n); 
    switch(n){ 
    case 1: 
		InitMaze(maze); 
        printf("\n��������Թ�Ϊ:\n\n"); 
        PrintMaze(maze); 
        printf("������ڵĺ�����,������:\n"); 
        scanf("%d,%d",&start.row,&start.col); 
        printf("������ڵĺ�����,������:\n"); 
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
		printf("\n�Է�����ʽ����Թ�����ͨ·:(2:��ʾ��ͨ·��,3:��ʾ����ͬ):\n"); 
        PrintMaze(maze); 
        break; 
} 
} 
// return OK;
}
