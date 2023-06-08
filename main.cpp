#include <stdio.h>
#include <stdlib.h>


//定义数据类型
typedef char DataType;
//定义树的结构
typedef struct TreeNode{
    DataType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode,*Tree;

typedef Tree LinkDataType;
//存储树的结点地址
typedef struct tag{
    Tree p;//树的某一个节点
    struct tag *pnext;
}tag_t,*ptag_t;
//队列的相关数据结构。

//看不懂
typedef struct LinkNode{
    LinkDataType data;
    struct  LinkNode* next;
}LinkNode;

typedef struct{
    LinkNode *front,*rear;
}LinkQueue;

//初始化队列
void IniQueue(LinkQueue &Q){//初始化这个地方没加引用，导致前后节点没链接在一起。这个函数无效
    Q.front=Q.rear=(LinkNode*)malloc(sizeof(LinkNode));//强转是结构体*才能强转。
    Q.front->next=NULL;//Q.front=Q.rear=NULL 这里犯了一个错误，只应该让头指针化为NULL.//也不是错误，初始化一个就行了
}

//判断队列是否为空
bool  IsEmpt(LinkQueue Q){
    if(Q.front==Q.rear)
    {
        return false;
    }
    else{
        return true;
    }
}


//进队，尾插法，使最后一个节点，保存数据，指针为空。
void EnQueue(LinkQueue &Q,LinkDataType x){
    //申请空间，然后尾插法插入就可以
    LinkNode *s=(LinkNode*)malloc(sizeof(LinkNode));
    s->data=x;
    s->next=NULL;//定义尾节点数据和指针值。
    Q.rear->next=s;
    Q.rear=s;
}


//出队
bool DeQueue(LinkQueue &Q,LinkDataType &x){//因为要改变队列内容，所以要引用加入&符号
    //首先判断队列是否为空，空的话无法出队。
    IsEmpt(Q);
    LinkNode *p=Q.front->next;//头节点为空，下一个节点才是有效节点。
    x=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
    {
        Q.rear=Q.front;
        free(p);
        return true;
    }
    return true;
}


//层序建树
void  BuildCharTree(Tree &T){
    Tree pnew;
    char c;
    T= NULL;//首先定义一个树根为NULL;
    //然后定义一个队列。这个队列是一个链表的
    ptag_t phead=NULL,ptail=NULL,listpnew=NULL,pcur=NULL;//初始化这个队列的头尾和当前指针。
    //abcdefghij，定义输入内容
    //开始输入
    while (scanf("%c",&c))//实际上Clino没有这个判断机制，EOF实际上为-1，表示输入的数据有问题
    {
        if(c=='\n')//上来就是结束条件，回车符号代表结束。单引号用于比较字符，双引号用于比较字符串。应该问题不大，等会试一下
        {
            break;
        }
        else
        {
            pnew=(Tree)calloc(1,sizeof(TreeNode));//申请结构体大小地址，然后强转为结构体指针。
            pnew->data=c;//把C的数据放到队列里面
            listpnew=(ptag_t)calloc(1,sizeof(tag_t));//给队列新节点申请空间
            listpnew->p=pnew;//存放地址。
            if (NULL==T)
            {
                T=pnew;
                phead=listpnew;
                ptail=listpnew;
                pcur=listpnew;
                continue;
            }
            else
            {
                ptail->pnext=listpnew;//入队，尾插法
                ptail=listpnew;//ptail指向尾部

            }
            if(NULL==pcur->p->lchild)
            {
                pcur->p->lchild=pnew;
            }
            else if(NULL==pcur->p->rchild)
            {
                pcur->p->rchild=pnew;
                pcur=pcur->pnext;
            }
        }
    }
}

//中历遍序，也称深度遍历
void InOrder(Tree p){//前历遍序
    if(p!=NULL)
    {
//        printf("%c",&p);

        InOrder(p->lchild);
        putchar(p->data);//打印数据，因为你不一定是输出数字，可能打印字母，也可能打印整型
        InOrder(p->rchild);
    }
}

//后历遍序，也称深度遍历
void BackOrder(Tree p){//前历遍序
    if(p!=NULL)
    {
//        printf("%c",&p);
        BackOrder(p->lchild);
        BackOrder(p->rchild);
        putchar(p->data);//打印数据，因为你不一定是输出数字，可能打印字母，也可能打印整型
    }
}



//层序遍历
void LevelOrder(Tree T){
    LinkQueue (Q);
    IniQueue (Q);
    Tree p;
    EnQueue(Q,T);//树根入队？
    while(IsEmpt(Q))//IsEmpt 这个函数返回的值是bool类型的
    {
        DeQueue(Q,p);
        putchar(p->data);
        if(p->lchild!=NULL)
        {
            EnQueue(Q,p->lchild);
        }
        if(p->rchild!=NULL)
        {
            EnQueue(Q,p->rchild);
        }
    }


}






//课时15练习题，二叉树的建立。层次查询
//主要包括以下流程，第一步循环scanf数据，然后运用结构体进行练习
//二叉树需要一个辅助队列，每次进入一个树，就入队，然后判断前面的数据左右孩子是否为空。
//如果不为空，则就放进左孩子，不空就放入有孩子。
int main() {
    Tree T=NULL;
    BuildCharTree(T);
    InOrder(T);
    printf("\n");
    BackOrder(T);
    printf("\n");
    LevelOrder(T);
    printf("\n");
    return 0;

}
