/****************************************************************************
Copyright (C), 2018, Jeff, Ltd.

File name: main.c

Author:  Jeff   Version:  0.1    Date:  2018.06.23

Description: This programe is use to manage emplyee's salary, the controls
             include read and write the binary file, query, browse, insert,
             delete data and save the data into the binary file, and it
             also could account the salary about the after-tax wages.

Others: 

Function List:
1.read()     //reading file employee salary data and assigning it to 
             //an array of structures.
2.write()    //write structure array data to binary file.
3.find()     //query salary data of a certain employee 
             //and output it on the display.
4.list()     //browsing employee wage data starting from an employee.
5.modify()   //modify employee's wage data
6.del()      //delete employee's data
7.add()      //add new employee's data
8.grsds(zggz *p)       //account employee's tax
9.show_data(zggz *p)  //show employee's data

History:
   <author>     <time>     <version>            <desc>
     Jeff      18/07/02       0.1       use double list to achieve 
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee
{
    char number[10];    //职工工号
    char name[10];      //职工姓名
    float gwgz;         //岗位工资
    float xjgz;         //薪级工资
    float subsidy;      //职务津贴
    float jxgz;         //绩效工资
    float yfgz;         //应发工资
    float tax;          //个人所得税
    float sfgz;         //实发工资
    struct Employee *prior, *next;//定义前驱指针、后继指针
}zggz;

zggz *head, *tail;

int n = 0;  //记录职工数量

void show_data(zggz *p);   //声明显示职员工资数据的函数
void read();        //声明读取职工工资数据的函数
void write();       //声明保存职工工资数据的函数
void find();        //声明查询职工工资数据的函数
void list();        //声明浏览职工工资数据的函数
void modify();      //声明修改职工工资数据的函数
void del();         //声明删除职工工资数据的函数
void add();         //声明添加职工工资数据的函数
void grsds(zggz *p);  //声明计算个人所得税的函数

int main()
{
    char s[5], ch[5];
    int flag = 1;    //用于控制循环体
    read();

    while(flag)
    {
        printf("\n\n\n\t");
        printf("###  欢迎使用广西民族大学软件与信息安全学院职工工资管理系统  ###");
        printf("\n\n\n\t");
        printf("请选择（1 - 7）：\n\t");
        printf("================================================================");
        printf("\n\t");
        printf("|        1. 查询职工工资记录                                   |");
        printf("\n\t");
        printf("|        2. 修改职工工资记录                                   |");
        printf("\n\t");
        printf("|        3. 添加职工工资记录                                   |");
        printf("\n\t");
        printf("|        4. 删除职工工资记录                                   |");
        printf("\n\t");
        printf("|        5. 保存数据到文件                                     |");
        printf("\n\t");
        printf("|        6. 浏览职工记录                                       |");
        printf("\n\t");
        printf("|        7. 退出系统                                           |");
        printf("\n\t");
        printf("================================================================");
        printf("\n\n\t");
        printf("你的选择是：");
        scanf("%s",  s);
        printf("\n\t");

        if(strcmp(s ,"1") == 0)
        {
            find();
        }
        else if(strcmp(s ,"2") == 0)
        {
            modify();
        }
        else if(strcmp(s ,"3") == 0)
        {
            if(n < 100)
            {
                add();
            }
            else
            {
                printf("\n\t人数超出限制！\n\n");
            }
        }
        else if(strcmp(s ,"4") == 0)
        {
            del();
        }
        else if(strcmp(s ,"5") == 0)
        {
            write();
        }
        else if(strcmp(s ,"6") == 0)
        {
            list();
        }
        else if(strcmp(s ,"7") == 0)
        {
            printf("\n\t是否需要帮您保存数据？是：y，否：任意字符\n\t");
            scanf("%s", ch);
            if(strcmp(ch, "y") == 0)
            {
                write();
            }
            printf("\n\t");
            printf("---------------------------程序已退出---------------------------");
            printf("\n\t");
            flag = 0;
        }
        else
        {
            printf("\n\t无该指令，请重新输入！\n\n");
        }
    }
    return 0;
}


//显示某职员信息的函数（完成）
void show_data(zggz *p)    
{
    printf("\n\t职员工号：%s\n\t职员姓名：%s\n\t岗位工资：%.2f",
        p->number, p->name, p->gwgz);

    printf("\n\t薪级工资：%.2f\n\t职务津贴：%.2f\n\t绩效工资：%.2f",
        p->xjgz, p->subsidy, p->jxgz);

    printf("\n\t应发工资：%.2f\n\t个人所得税：%.2f\n\t实发工资：%.2f\n",
        p->yfgz, p->tax, p->sfgz);
}

//读取文件中职工信息（不完善，尾部总是多申请一个空间）
void read()    //定义读取职工工资数据函数
{
    zggz *p;
    int i, nRes;
    FILE *fp = fopen("gx.dat", "rb");//定义文件指针

    head = (zggz *)malloc(sizeof(zggz));//初始化链表
    head->prior = head;
    head->next = head;
    p = head;

    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n\t文件打开失败！\n");
        exit(-1);
    }
    
    for(i = 0; i < 100; i ++)
    {
        nRes = fscanf(fp, "%s %s %f %f %f %f %f %f %f",
                  p->number, p->name, &(p->gwgz), 
                  &(p->xjgz), &(p->subsidy), &(p->jxgz),
                  &(p->yfgz), &(p->tax), &(p->sfgz));

        if (nRes == -1)    //判断是否读取到文件尾部
        {
            n = i;    //记录写入数据的条数
            fclose(fp);
            break;
        }
        tail = (zggz *)malloc(sizeof(zggz));
        p->next = tail;
        tail->prior = p;
        tail->next = head;
        head->prior = tail;
        p = tail;
    }
    fclose(fp);
}

//保存职工信息至文件
void write()
{
    FILE *fp = fopen("gz.dat","wb");
    int i;
    zggz *p = head;

    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n\t文件打开失败！\n");
        exit(1);
    }
    
    for (i = 0; i < n; i ++)    //将数据写入二进制文件
    {
        fprintf(fp, "%s %s %f %f %f %f %f %f %f \n",
                    p->number, p->name, p->gwgz, 
                    p->xjgz, p->subsidy, 
                    p->jxgz, p->yfgz, 
                    p->tax, p->sfgz);
        p = p->next;
        /*
        fwrite(p , sizeof(zggz), 1, fp);
        p = p->next;
        */
    }
    fclose(fp);    //关闭文件
    printf("\n\t");
    printf("-------------------------文件保存完毕！-------------------------");
    printf("\n");
}

//查询职工工资信息
void find()
{
    char gonghao[10];
    char s[5];
    int i;
    zggz *p = head;
    int flag = 1;
    
    printf("\n\t");
    printf("------------------------------查询------------------------------");
    while(flag)
    {
        printf("\n\t请输入所要查询的工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, p->number) == 0)
            {
                printf("\n\t");
                printf("-----------------------所查询的职工信息为-----------------------");

                show_data(p);

                flag = 0;
                printf("\n\t");
                printf("----------------------------查询结束----------------------------");
                break;
            }
            p = p->next;
        }
        if(flag == 1)
        {
            printf("\n\t无此工号职员信息\n");
            printf("\n\t是否继续查询？是：y，否：任意字符\n\t");
            scanf("%s", s);
            if(strcmp(s, "y") == 0)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
    }
}

//浏览所以职工工资信息
void list()
{
    int i;
    zggz *p = head;
    printf("\n\t");
    printf("------------------------浏览职工工资数据------------------------");
    for(i = 0; i < n; i ++)
    {
        show_data(p);
        p = p->next;
    }
    printf("\n\t");
    printf("----------------------------浏览结束----------------------------");
}

//修改职工工资信息（未完成）
void modify()    
{
    char gonghao[10], s[10];
    int i, flag = 1;
    zggz *p = head;
    printf("\n\t");
    printf("------------------------------修改------------------------------");
    while(flag)
    {
        printf("\n\t请输入所要重新录入数据的职员工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, p->number) == 0)
            {
                printf("\n\t请录入该职员工资数据：\n");
                
                //input_data(p);
                printf("\n\t岗位工资：");    //输入岗位工资
                scanf("%f", p->gwgz);

                printf("\n\t薪级工资：");    //输入薪级工资
                scanf("%f", p->xjgz);

                printf("\n\t职务津贴：");    //输入职务津贴
                scanf("%f", p->subsidy);

                printf("\n\t绩效工资：");    //输入绩效工资
                scanf("%f", p->jxgz);

                p->yfgz = p->gwgz + p->xjgz 
                        + p->subsidy + p->jxgz;

                grsds(p);    //计算个人所得税

                p->sfgz = p->yfgz - p->tax;
                printf("\n\t");
                printf("----------------------------修改结束----------------------------");
                flag = 0;    //控制循环结束
                break;
            }
            p = p->next;
        }
        if(flag)
        {
            printf("\n\t无此工号职工信息\n\t");

            printf("是否继续修改？是：y 否：任意字符\n\t");
            scanf("%s", s);

            if(strcmp(s, "y") == 1)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
    }
}

//删除职工信息（未完成）
void del()
{
    char gonghao[10];
    char s[5];
    int i, j;
    int flag = 1;
    zggz *p = head;

    printf("\n\t");
    printf("------------------------------删除------------------------------");
    printf("\n\t请输入所要删除的职员工号：");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, p->number) == 0)
        {
            printf("\n\t是否删除该职员信息？是：y，否：任意字符\n\t");
            scanf("%s", s);
            if(strcmp(s, "y") == 0)
            {
                for(j = i; j < n; j ++)
                {
                    p = p->next;
                }
                n -= 1;    //记录总人数
                flag = 0;
                printf("\n\t");
                printf("----------------------------删除成功----------------------------");
                break;
            }
            else
            {
                flag = 0;
                printf("\n\t");
                printf("----------------------------删除取消----------------------------");
                break;
            }
        }
    }
    if(flag)    //查找后不存在工号
    {
        printf("\n\t");
        printf("-----------------------无此工号职员信息！-----------------------");
    }
}

//添加职工工资信息（不完善，无法判断工号是否重复）
void add()
{
    zggz *p;
    p = tail;

    printf("\n\t");
    printf("------------------------------添加------------------------------");
    printf("\n\t请输入职工基本信息：\n");
    printf("\n\t职工工号：");
    scanf("%s", p->number);

    printf("\n\t职工姓名：");
    scanf("%s", p->name);

    printf("\n\t岗位工资：");    //输入岗位工资
    scanf("%f", &(p->gwgz));
    
    printf("\n\t薪级工资：");    //输入薪级工资
    scanf("%f", &(p->xjgz));
    
    printf("\n\t职务津贴：");    //输入职务津贴
    scanf("%f", &(p->subsidy));
    
    printf("\n\t绩效工资：");    //输入绩效工资
    scanf("%f", &(p->jxgz));
    
    p->yfgz = p->gwgz + p->xjgz 
        + p->subsidy + p->jxgz;
    
    grsds(p);    //计算个人所得税
    
    p->sfgz = p->yfgz - p->tax;
    printf("\n\t");
    printf("--------------------------所增职工信息--------------------------");

    show_data(p);

    tail = (zggz *)malloc(sizeof(zggz));
    p->next = tail;
    tail->prior = p;
    tail->next = head;
    head->prior = tail;
    n += 1;    //数据总数+1

    printf("\n\t");
    printf("--------------------------添加执行结束--------------------------");
}

//计算跟所得税
void grsds(zggz *p)
{
    double count, tax;
    int flag = 1;
    count = p->yfgz;    //应发工资
    p->tax = 0;    //作累加器
    
    while(flag)
    {
        if(count > 100000)
        {
            tax = (count - 100000) * 0.45;
            count = 100000;
        }
        else if(count > 80000)
        {
            tax = (count - 80000) * 0.4;
            count = 80000;
        }
        else if(count > 60000)
        {
            tax = (count - 60000) * 0.35;
            count = 60000;
        }
        else if(count > 40000)
        {
            tax = (count - 40000) * 0.3;
            count = 40000;
        }
        else if(count > 20000)
        {
            tax = (count - 20000) * 0.25;
            count = 20000;
        }
        else if(count > 5000)
        {
            tax = (count - 5000) * 0.2;
            count = 5000;
        }
        else if(count > 2000)
        {
            tax = (count - 2000) * 0.15;
            count = 2000;
        }
        else if(count > 500)
        {
            tax = (count - 500) * 0.1;
            count = 500;
        }
        else
        {
            tax = count * 0.05;
            flag = 0;    //应发工资收取个人所得税部分小于500停止
        }
        p->tax += tax;    //累加每层的个人所得税
    }
}