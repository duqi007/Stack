#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK      1
#define ERROR   0

typedef char SElemType;
typedef int Status;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}sqStack;

void visit(SElemType e);                            //显示元素的函数
Status InitStack(sqStack *S);                       //初始化栈
Status Push(sqStack *S, SElemType e);               //压栈
Status Pop(sqStack *S, SElemType *e);               //弹栈
Status GetTop(sqStack *S, SElemType *e);            //获取栈顶元素，不删除栈顶元素
Status DestroyStack(sqStack *S);                    //销毁栈
Status ClearStack(sqStack *S);                      //清空栈
int StackLength(sqStack s);                         //获取当前栈的长度
Status StackEmpty(sqStack S);                       //判断栈是否为空
Status StackTraverse(sqStack S);                    //遍历栈元素显示出来


Status InitStack(sqStack *S){
    S->base = (SElemType * )malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base){
        exit(0);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;

}


Status Push(sqStack *S, SElemType e)
{
    if(S->top - S->base >= S->stacksize)           //栈满， 追加空间
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(SElemType));
        if(!S->base){
            exit(0);                 //分配失败
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }

    *(S->top) = e;
    S->top++;
    return OK;
}

Status Pop(sqStack *S, SElemType *e){
    if(S->top == S->base){
        return ERROR;                  //判空
    }
    *e = * --(S->top);
    return OK;
}

Status GetTop(sqStack *S, SElemType *e){
    if(S->top == S->base){
        return ERROR;
    }
    *e = *(S->top-1);
    return OK;

}

Status DestroyStack(sqStack *S){
    free(S);
    return OK;
}
Status ClearStack(sqStack *S){

    S->top = S->base;
    S->stacksize = 0;
    return OK;
}
int StackLength(sqStack s){
    return (s.top - s.base);
}

Status StackEmpty(sqStack S){
    if(S.top - S.base == 0){
        //printf("StackEmpty()当前栈为空！\n");
        return ERROR;
    }
    return OK;
}
//从栈底开始依次显示栈内元素
Status StackTraverse(sqStack S){
    SElemType e;
    sqStack T;              //辅助栈
    InitStack(&T);
    if(StackEmpty(S) == 0){
        printf("当前栈为空！\n");
        return ERROR;
    }
    while(1){
        if(StackEmpty(S) == 0){
            break;
        }
        Pop(&S, &e);

        Push(&T,e);
    }
    while(1){
        if(StackEmpty(T) == 0){
            break;
        }
        Pop(&T, &e);
        visit(e);
        Push(&S, e);
    }
    printf("\n");
    return OK;
}

void visit(SElemType e){
    printf("%c  ", e);
}

int main()
{
    SElemType c;
    sqStack S;
    int Len;
    //int i, sum = 0;
    InitStack(&S);
    printf("请输入任意字符，回车表示结束:\n");
    //printf("请输入二进制数，回车表示结束:\n");
    scanf("%c", &c);
    while(c != 10){
        Push(&S, c);
        scanf("%c", &c);
    }
    //getchar();
    Len = StackLength(S);

    printf("当前栈的长度：%d\n", Len);

    /*for(i=0; i<Len ; i++)
    {
       Pop(&S,&c);
       sum = sum + (c-48) * pow(2,i);
    }*/
    //printf("转换的数值是：%d\n",sum);
    StackTraverse(S);
    StackTraverse(S);
    ClearStack(&S);
    Len = StackLength(S);
    printf("清空后，当前栈的长度：%d\n", Len);
    StackEmpty(S);
    DestroyStack(&S);
    system("pause");
    return 0;
}
