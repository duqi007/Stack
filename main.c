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

void visit(SElemType e);                            //��ʾԪ�صĺ���
Status InitStack(sqStack *S);                       //��ʼ��ջ
Status Push(sqStack *S, SElemType e);               //ѹջ
Status Pop(sqStack *S, SElemType *e);               //��ջ
Status GetTop(sqStack *S, SElemType *e);            //��ȡջ��Ԫ�أ���ɾ��ջ��Ԫ��
Status DestroyStack(sqStack *S);                    //����ջ
Status ClearStack(sqStack *S);                      //���ջ
int StackLength(sqStack s);                         //��ȡ��ǰջ�ĳ���
Status StackEmpty(sqStack S);                       //�ж�ջ�Ƿ�Ϊ��
Status StackTraverse(sqStack S);                    //����ջԪ����ʾ����


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
    if(S->top - S->base >= S->stacksize)           //ջ���� ׷�ӿռ�
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(SElemType));
        if(!S->base){
            exit(0);                 //����ʧ��
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
        return ERROR;                  //�п�
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
        //printf("StackEmpty()��ǰջΪ�գ�\n");
        return ERROR;
    }
    return OK;
}
//��ջ�׿�ʼ������ʾջ��Ԫ��
Status StackTraverse(sqStack S){
    SElemType e;
    sqStack T;              //����ջ
    InitStack(&T);
    if(StackEmpty(S) == 0){
        printf("��ǰջΪ�գ�\n");
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
    printf("�����������ַ����س���ʾ����:\n");
    //printf("����������������س���ʾ����:\n");
    scanf("%c", &c);
    while(c != 10){
        Push(&S, c);
        scanf("%c", &c);
    }
    //getchar();
    Len = StackLength(S);

    printf("��ǰջ�ĳ��ȣ�%d\n", Len);

    /*for(i=0; i<Len ; i++)
    {
       Pop(&S,&c);
       sum = sum + (c-48) * pow(2,i);
    }*/
    //printf("ת������ֵ�ǣ�%d\n",sum);
    StackTraverse(S);
    StackTraverse(S);
    ClearStack(&S);
    Len = StackLength(S);
    printf("��պ󣬵�ǰջ�ĳ��ȣ�%d\n", Len);
    StackEmpty(S);
    DestroyStack(&S);
    system("pause");
    return 0;
}
