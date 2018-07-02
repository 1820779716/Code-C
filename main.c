/****************************************************************************
Copyright (C), 2018, Jeff, Ltd.

File name: main.c

Author:  Jeff   Version:  0.1    Date:  2018.06.23

Description: This programe is use to manage emplyee's salary, the controls
             include read and write the binary file, query, browse, insert,
             delete data and save the data into the binary file, and it
             also could account the salary about the after-tax wages.

Others: function of add isn't finish.

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
9.input_data(int i)  //input salary data and account tax
10.show_data(zggz *p)  //show employee's data

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
}zggz;    //把zggz定义为struct Employee的别名

zggz *head, *tail;    //定义头节点和尾节点

int n = 0;  //记录职工数量的全局变量
void input_data(zggz *p);  //声明输入职员工资数据的函数
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
            find();//调用查询函数
        }
        else if(strcmp(s ,"2") == 0)
        {
            modify();//调用修改函数
        }
        else if(strcmp(s ,"3") == 0)
        {
            if(n < 100)
            {
                add();//数据记录条数小于100时调用
            }
            else
            {
                printf("\n\t人数超出限制！\n\n");
            }
        }
        else if(strcmp(s ,"4") == 0)
        {
            del();//调用删除函数
        }
        else if(strcmp(s ,"5") == 0)
        {
            write();//调用保存函数
        }
        else if(strcmp(s ,"6") == 0)
        {
            list();//调用浏览函数
        }
        else if(strcmp(s ,"7") == 0)
        {
            printf("\n\t是否需要帮您保存数据？是：y，否：任意字符\n\t");
            scanf("%s", ch);
            if(strcmp(ch, "y") == 0)
            {
                write();//满足条件时调用保存函数
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

void input_data(zggz *p)//输入某个员工工资信息
{
    printf("\n\t岗位工资：");    //输入岗位工资
    scanf("%f", &(p->gwgz));

    printf("\n\t薪级工资：");    //输入薪级工资
    scanf("%f", &(p->xjgz));

    printf("\n\t职务津贴：");    //输入职务津贴
    scanf("%f", &(p->subsidy));

    printf("\n\t绩效工资：");    //输入绩效工资
    scanf("%f", &(p->jxgz));

    p->yfgz = p->gwgz + p->xjgz 
            + p->subsidy + p->jxgz;//统计应发工资

    grsds(p);    //计算个人所得税

    p->sfgz = p->yfgz - p->tax;//计算实发工资
}

void show_data(zggz *p)//显示某职员信息的函数
{
    printf("\n\t职员工号：%s\n\t职员姓名：%s\n\t岗位工资：%.2f",
        p->number, p->name, p->gwgz);

    printf("\n\t薪级工资：%.2f\n\t职务津贴：%.2f\n\t绩效工资：%.2f",
        p->xjgz, p->subsidy, p->jxgz);

    printf("\n\t应发工资：%.2f\n\t个人所得税：%.2f\n\t实发工资：%.2f\n",
        p->yfgz, p->tax, p->sfgz);
}

void read()//读取文件中职工工资数据并赋值给链表
{
    zggz *p;
    int i, nRes;
    FILE *fp = fopen("gx.dat", "rb");//定义文件指针

    head = (zggz *)malloc(sizeof(zggz));//初始化链表
    head->prior = head;//头节点前驱指针指向头节点
    head->next = head;//头节点后继指针指向头节点
    p = head;

    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n\t文件打开失败！\n");
        exit(-1);
    }
    
    for(i = 0; i < 100; i ++)
    {
        /*
        nRes = fscanf(fp, "%s %s %f %f %f %f %f %f %f",
                  p->number, p->name, &(p->gwgz), 
                  &(p->xjgz), &(p->subsidy), &(p->jxgz),
                  &(p->yfgz), &(p->tax), &(p->sfgz));

        if (nRes == -1)    //判断是否读取到文件尾部
        {
            n = i;    //记录写入数据的条数
            break;
        }
        */
        fread(p, sizeof(zggz), 1, fp);

        tail = (zggz *)malloc(sizeof(zggz));
        p->next = tail;
        tail->prior = p;
        tail->next = head;
        head->prior = tail;
        p = tail;

        if(feof(fp))
        {
            n = i;
            break;
        }
    }

    /*把多申请的空间释放，了；令节点p的前驱指针和
	后继指针均指向自身，最后释放*/
    p->next->prior = p->prior;
    p->prior->next = p->next;
    free(p);
    
    fclose(fp);
}

void write()//保存职工工资数据信息至文件
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
        /*
        fprintf(fp, "%s %s %f %f %f %f %f %f %f \n",
                    p->number, p->name, p->gwgz, 
                    p->xjgz, p->subsidy, 
                    p->jxgz, p->yfgz, 
                    p->tax, p->sfgz);
        p = p->next;
        */
        fwrite(p , sizeof(zggz), 1, fp);
        p = p->next;
    }
    fclose(fp);    //关闭文件
    printf("\n\t");
    printf("-------------------------文件保存完毕！-------------------------");
    printf("\n");
}

void find()//查询职工工资信息
{
    char gonghao[10];//存储所查询的职工工号
    int i;
    zggz *p = head;//从链表头开始查询
    
    printf("\n\t");
    printf("------------------------------查询------------------------------");
    printf("\n\t请输入所要查询的工号：");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, p->number) == 0)
        {
            printf("\n\t");
            printf("-----------------------所查询的职工信息为-----------------------");

            show_data(p);//输出所查询工号的工资数据

            printf("\n\t");
            printf("----------------------------查询结束----------------------------");
            break;
        }
        p = p->next;//指向下一个节点
    }
    if(i == n)//for循环循环n次后，查无工号，i自加1后等于n
    {
        printf("\n\t");
        printf("-----------------------无此工号职员信息！-----------------------");
    }
}

void list()//浏览所有职工工资信息
{
    int i;
    zggz *p;
    p = head;//另p等于头节点
    printf("\n\t");
    printf("------------------------浏览职工工资数据------------------------");
    for(i = 0; i < n; i ++)//通过p->next遍历输出节点数据
    {
        show_data(p);
        p = p->next;
    }
    printf("\n\t");
    printf("----------------------------浏览结束----------------------------");
}

void modify()//修改职工工资信息
{
    char gonghao[10];//记录所要修改职员工资信息的工号
    int i;
    zggz *p = head;

    printf("\n\t");
    printf("------------------------------修改------------------------------");
    printf("\n\t请输入所要重新录入数据的职员工号：");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(p->number, gonghao) == 0)//满足条件输入工资数据
        {
            printf("\n\t请录入该职员工资数据：\n");

            input_data(p);//调用输入工资数据的函数

            printf("\n\t");
            printf("----------------------------修改结束----------------------------");
            break;
        }
        p = p->next;//指向下个节点数据
    }
    if(i == n)
    {
        printf("\n\t");
        printf("-----------------------无此工号职员信息！-----------------------");
    }
}

void del()//删除职工信息
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
        p = p->next;
        if(strcmp(gonghao, p->number) == 0)//查询链表中满足条件的节点
        {
            printf("\n\t是否删除该职员信息？是：y，否：任意字符\n\t");
            scanf("%s", s);
            /* 删除链表中某个元素，令p的前驱节点和后驱节点
            相互指向即可，如果p是尾节点则直接将前驱节点指向NULL*/
            if(strcmp(s, "y") == 0)
            {
                if(p->next == NULL)
                {
                    p->prior->next = NULL;
                    free(p);
                }
                else
                {
                     p->next->prior = p->prior;
                     p->prior->next = p->next;
                     free(p);
                }
                n -= 1;    //总工资数据数量-1
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

void add()//添加职工工资信息（不完善）
{
    zggz *p, *q;
    char s[10];
    int i;
    int flag = 1;    //控制循环体
    int flag_1 = 0;  //控制是否输入数据
    p = head;

    printf("\n\t");
    printf("------------------------------添加------------------------------");
    printf("\n\t请输入职工基本信息：\n");
    while(flag)
    {
        printf("\n\t职员工号：");    //输入职员工号
        scanf("%s", s);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(s, p->number) == 0)//判断工号是否已存在
            {
                printf("\n\t该职员工号已存在！\n");
                printf("\n\t是否重新输入？是：y，否：任意字符\n\t");
                scanf("%s", s);
                if(strcmp(s, "y") == 0)
                {
                    flag = 1;//同意重新输入新工号来添加职员工资信息
                }
                else
                {
                    flag = 0;//不同意重新输入，退回主菜单
                }
                break;//退出循环
            }
			p = p->next;
        }
        if(i == n)
        {
			p = p->next;
            strcpy(p->number, s);//职员工号无重复，开始赋值
            flag = 0;
            flag_1 = 1;
        }
    }
    if(flag_1 == 1)
    {
        printf("\n\t职工姓名：");    //输入职员姓名
        scanf("%s", p->name);

        input_data(p);    //输入职员工资信息

        printf("\n\t");
        printf("--------------------------所增职工信息--------------------------");

        show_data(p);
        n += 1;    //总工资数据数量+1
		tail = (zggz *)malloc(sizeof(zggz));
        p->next = tail;
        tail->prior = p;
        tail->next = head;
        head->prior = tail;
    }
    printf("\n\t");
    printf("--------------------------添加执行结束--------------------------");
}

void grsds(zggz *p)//计算个人所得税
{
    double count, tax;
    int flag = 1;
    count = p->yfgz;    //应发工资
    p->tax = 0;    //作累加器
    
    while(flag)
    {
        if(count > 100000)    //超过100000元的部分
        {
            tax = (count - 100000) * 0.45;
            count = 100000;
        }
        else if(count > 80000)    //超过80000到100000元的部分
        {
            tax = (count - 80000) * 0.4;
            count = 80000;
        }
        else if(count > 60000)    //超过60000到80000元的部分
        {
            tax = (count - 60000) * 0.35;
            count = 60000;
        }
        else if(count > 40000)    //超过40000到60000元的部分
        {
            tax = (count - 40000) * 0.3;
            count = 40000;
        }
        else if(count > 20000)    //超过20000到40000元的部分
        {
            tax = (count - 20000) * 0.25;
            count = 20000;
        }
        else if(count > 5000)    //超过5000到20000元的部分
        {
            tax = (count - 5000) * 0.2;
            count = 5000;
        }
        else if(count > 2000)    //超过2000到5000元的部分
        {
            tax = (count - 2000) * 0.15;
            count = 2000;
        }
        else if(count > 500)    //超过500到2000元的部分
        {
            tax = (count - 500) * 0.1;
            count = 500;
        }
        else    //不超过500元的部分
        {
            tax = count * 0.05;
            flag = 0;    //应发工资收取个人所得税部分小于500停止
        }
        p->tax += tax;    //累加每层的个人所得税
    }
}