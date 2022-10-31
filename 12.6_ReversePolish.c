#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define INT 1
#define DOU 2
#define N 20
int i;

union DataType
{
    int Integar;            //存放整形数据
    double Double;          //存放双精度数据
};

typedef struct node
{
    union DataType data;
    int typeflag;           //表示结构体中union的状态
}NodeType;

typedef struct stack
{
    NodeType Data[N];
    int top;                //栈顶
}STACK;

void Push(STACK *stack, NodeType data);
NodeType pop(STACK *stack);
NodeType Op2Int(int d1, int d2, int op);
NodeType Op1Int(int d1, double d2, int op);
NodeType Op2Double(double d1, double d2, int op);
NodeType Op1Double(double d1, int d2, int op);
NodeType OpData(NodeType *d1, NodeType *d2, int op);

int main(void)
{
    char word[10];
    int flag = 0;           //标记当前数据类型
    NodeType d1, d2, d3;
    STACK stack;
    stack.top = 0;          //初始化栈顶
    while (scanf("%s", word) == 1 && word[0] != '#')
    {
        flag = 0;
        for (i = 0; i < N; i++)
        {
            if (word[i] == 46)  flag = DOU; //判定双精度数
        }
        if (flag == DOU)
        {
            d1.data.Double = atof(word);
            d1.typeflag = DOU;              //置union状态为双精度
            Push(&stack, d1);
        }
        else
        {
            if (isdigit(word[0]))
            {
                d1.data.Integar = atoi(word);
                d1.typeflag = INT;          //置union状态为整型数
                Push(&stack, d1);
            }
            else
            {
                d1 = pop(&stack);
                d2 = pop(&stack);
                d3 = OpData(&d1, &d2, word[0]);
                Push(&stack, d3);
            }
        }
    }
    d1 = pop(&stack);
    if (d1.typeflag == INT) printf("%d", d1.data.Integar);
    else                    printf("%lf", d1.data.Double);
    return 0;
}
//函数功能：将结构体压入栈
void Push(STACK *stack, NodeType data)
{
    memcpy(&stack->Data[stack->top], &data, sizeof(data));
    stack->top = stack->top + 1;
}
//函数功能：从栈中弹出结构体
NodeType pop(STACK *stack)
{
    stack->top = stack->top - 1;
    return stack->Data[stack->top];
}
//函数功能：进行两个数据均为整形数的运算
NodeType Op2Int(int d1, int d2, int op)
{
    NodeType res;
    if       (op == '+')    res.data.Integar = d2 + d1;
    else if  (op == '-')    res.data.Integar = d2 - d1;
    else if  (op == '*')    res.data.Integar = d2 * d1;
    else if  (op == '/')    res.data.Integar = d2 / d1;
    res.typeflag = INT;     //返回结构体union状态为整型
    return res;
}
//函数功能：进行两个数据均为双精度数的运算
NodeType Op2Double(double d1, double d2, int op)
{
    NodeType res;
    if       (op == '+')    res.data.Double = d2 + d1;
    else if  (op == '-')    res.data.Double = d2 - d1;
    else if  (op == '*')    res.data.Double = d2 * d1;
    else if  (op == '/')    res.data.Double = d2 / d1;
    res.typeflag = DOU;
    return res;
}
//函数功能：进行d1为整型，d2为双精度的运算
NodeType Op1Int(int d1, double d2, int op)
{
    NodeType res;
    if       (op == '+')    res.data.Double = d2 + (double)d1;
    else if  (op == '-')    res.data.Double = d2 - (double)d1;
    else if  (op == '*')    res.data.Double = d2 * d1;
    else if  (op == '/')    res.data.Double = d2 / d1;
    res.typeflag = DOU;
    return res;
}
//函数功能：进行d1为双精度，d2为整型的运算
NodeType Op1Double(double d1, int d2, int op)
{
    NodeType res;
    if       (op == '+')    res.data.Double = (double)d2 + d1;
    else if  (op == '-')    res.data.Double = (double)d2 - d1;
    else if  (op == '*')    res.data.Double = d2 * d1;
    else if  (op == '/')    res.data.Double = d2 / d1;
    res.typeflag = DOU;
    return res;
}
//函数功能：读取union的状态并执行相应的运算
NodeType OpData(NodeType *d1, NodeType *d2, int op)
{
    NodeType res;
    if (d1->typeflag == INT && d2->typeflag == INT) 
    res = Op2Int(d1->data.Integar, d2->data.Integar, op);
    
    else if (d1->typeflag == INT && d2->typeflag == DOU)
    res = Op1Int(d1->data.Integar, d2->data.Double, op);
    
    else if (d1->typeflag == DOU && d2->typeflag == INT)
    res = Op1Double(d1->data.Double, d2->data.Integar, op);
    
    else if (d1->typeflag == DOU && d2->typeflag == DOU)
    res = Op2Double(d1->data.Double, d2->data.Double, op);
    
    return res;
}