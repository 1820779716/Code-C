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
8.grsds(int i)       //account employee's tax
9.input_data(int i)  //input salary data and account tax
10.show_data(int i)  //show employee's data

History:
   <author>     <time>     <version>        <desc>
     Jeff      18/07/02       0.1       adjust structure
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee{
    char number[10];    //职员工号
    char name[10];      //职员姓名
    float gwgz;         //岗位工资
    float xjgz;         //薪级工资
    float subsidy;      //职务津贴
    float jxgz;         //绩效工资
    float yfgz;         //应发工资
    float tax;          //个人所得税
    float sfgz;         //实发工资
}zggz[100];

int n = 0;    //用于记录写入结构体数据的总数

void input_data(int i);  //声明输入职员工资数据的函数
void show_data(int i);   //声明显示职员工资数据的函数
void read();        //声明读取职工工资数据的函数
void write();       //声明保存职工工资数据的函数
void find();        //声明查询职工工资数据的函数
void list();        //声明浏览职工工资数据的函数
void modify();      //声明修改职工工资数据的函数
void del();         //声明删除职工工资数据的函数
void add();         //声明添加职工工资数据的函数
void grsds(int i);  //声明计算个人所得税的函数


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
                add();//小于100条数据，调用添加函数
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
                write();//退出时可选择是否调用函数保存数据
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

void input_data(int i)    //用于输入职员工资信息
{
    printf("\n\t岗位工资：");    //输入岗位工资
    scanf("%f", &zggz[i].gwgz);

    printf("\n\t薪级工资：");    //输入薪级工资
    scanf("%f", &zggz[i].xjgz);

    printf("\n\t职务津贴：");    //输入职务津贴
    scanf("%f", &zggz[i].subsidy);

    printf("\n\t绩效工资：");    //输入绩效工资
    scanf("%f", &zggz[i].jxgz);

    zggz[i].yfgz = zggz[i].gwgz + zggz[i].xjgz 
            + zggz[i].subsidy + zggz[i].jxgz;

    grsds(i);    //计算个人所得税

    zggz[i].sfgz = zggz[i].yfgz - zggz[i].tax;
}

void show_data(int i)    //显示某职员信息的函数
{
    printf("\n\t职员工号：%s\n\t职员姓名：%s\n\t岗位工资：%.2f",
        zggz[i].number, zggz[i].name, zggz[i].gwgz);

    printf("\n\t薪级工资：%.2f\n\t职务津贴：%.2f\n\t绩效工资：%.2f",
        zggz[i].xjgz, zggz[i].subsidy, zggz[i].jxgz);

    printf("\n\t应发工资：%.2f\n\t个人所得税：%.2f\n\t实发工资：%.2f\n",
        zggz[i].yfgz, zggz[i].tax, zggz[i].sfgz);
}

void read()    //定义读取职工工资数据函数
{
    FILE *fp = fopen("gx.dat", "rb");    //定义文件指针
    int i = 0;    //充当结构体数组下标

    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n\t文件打开失败！\n");
        exit(-1);
    }

    while(!feof(fp))//判断是否读取到文件尾部
    {
        fread(&zggz[i], sizeof(zggz), 1, fp);
        if(!feof(fp))
        {
            i += 1;
        }
    }
    n = i;

    fclose(fp);    //关闭文件
}

void write()    //定义保存职工工资数据函数
{
    FILE *fp = fopen("gz.dat","wb");
    int i;
    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n\t文件打开失败！\n");
        exit(1);
    }

    for (i = 0; i < n; i ++)    //将数据写入二进制文件
    {
        fwrite(&zggz[i], sizeof(zggz), 1, fp);
    }
    fclose(fp);    //关闭文件
    printf("\n\t");
    printf("-------------------------文件保存完毕！-------------------------");
    printf("\n");
}

void find()    //定义查询职工工资数据函数
{
    char gonghao[10];
    int i;
    
    printf("\n\t");
    printf("------------------------------查询------------------------------");
    printf("\n\t请输入所要查询的工号：");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            printf("\n\t");
            printf("-----------------------所查询的职工信息为-----------------------");

            show_data(i);

            printf("\n\t");
            printf("----------------------------查询结束----------------------------");
            break;
        }
    }
    if(i == n)
    {
        printf("\n\t");
        printf("-----------------------无此工号职员信息！-----------------------");
    }
}

void list()    //定义浏览职工工资数据函数
{
    int i;
    printf("\n\t");
    printf("------------------------浏览职工工资数据------------------------");
    for(i = 0; i < n; i ++)
    {
        show_data(i);
    }
    printf("\n\t");
    printf("----------------------------浏览结束----------------------------");
}

void modify()    //定义修改职工工资数据函数
{
    char gonghao[10], s[10];
    int i;

    printf("\n\t");
    printf("------------------------------修改------------------------------");
    printf("\n\t请输入所要重新录入数据的职员工号：");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            printf("\n\t请录入该职员工资数据：\n");
                
            input_data(i);

            printf("\n\t");
            printf("----------------------------修改结束----------------------------");

            break;
        }
    }
    if(i == n)
    {
        printf("\n\t");
        printf("-----------------------无此工号职员信息！-----------------------");
    }
}

void del()    //定义删除职工工资数据函数
{
    char gonghao[10];
    char s[5];
    int i, j;
    int flag = 1;

    printf("\n\t");
    printf("------------------------------删除------------------------------");
    printf("\n\t请输入所要删除的职员工号：");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            printf("\n\t是否删除该职员信息？是：y，否：任意字符\n\t");
            scanf("%s", s);
            if(strcmp(s, "y") == 0)
            {
                for(j = i; j < n; j ++)
                {
                    zggz[j] = zggz[j+1];//后面数据往前移
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

void add()    //定义添加职工工资数据函数
{
    char s[10];
    int i;
    int flag = 1;    //控制循环体
    int flag_1 = 0;  //控制是否输入数据

    printf("\n\t");
    printf("------------------------------添加------------------------------");
    printf("\n\t请输入职工基本信息：\n");
    while(flag)
    {
        printf("\n\t职员工号：");    //输入职员工号
        scanf("%s", s);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(s, zggz[i].number) == 0)//判断工号是否已存在
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
        }
        if(i == n)
        {
            strcpy(zggz[n].number, s);//职员工号无重复，开始赋值
            flag = 0;
            flag_1 = 1;
        }
    }
    if(flag_1)
    {
        printf("\n\t职员姓名：");    //输入职员姓名
        scanf("%s", zggz[n].name);

        input_data(n);    //输入职员工资信息

        printf("\n\t");
        printf("--------------------------所增职工信息--------------------------");

        show_data(n);    //输出职员工资信息

        n += 1;    //总工资数据数量+1
    }
    printf("\n\t");
    printf("--------------------------添加执行结束--------------------------");
}

void grsds(int i)    //定义计算职工个人所得税函数
{
    double count, tax;
    int flag = 1;
    count = zggz[i].yfgz;    //应发工资
    zggz[i].tax = 0;    //作累加器

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
        zggz[i].tax += tax;    //累加每层的个人所得税
    }
}