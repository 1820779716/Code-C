/****************************************************************************
Copyright (C), 2018, Jeff, Ltd.

File name: main.cpp    

Author:  Jeff   Version:  0.1    Date:  2018.06.20

Description: This programe is use to manage emplyee's salary, the controls
             include read and write the binary file, query, browse, insert,
             delete data and save the data into the binary file, and it
             also could account the salary about the after-tax wages.

Others: This project is unfinish. Still have some moudles are wait to build.

Function List:
1. read()    //reading file employee salary data and assigning it to 
             //an array of structures.
2.write()    //write structure array data to binary file.(unfinish)
3.find()    //query salary data of a certain employee 
            //and output it on the display.
4.list()    //browsing employee wage data starting from an employee.

History:
   <author>     <time>     <version>           <desc>
     Jeff      18/06/21       0.1     change the functions interface
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct Employee{
    char number[10];    //工号
    char name[10];    //姓名
    float gw_salary;    //岗位工资
    float xj_salary;    //薪级工资
    float subsidy;    //职务津贴
    float jx_salary;    //绩效工资
    float yf_salary;    //应发工资
    float tax;    //个人所得税
    float actual_wage;    //实发工资
}zggz[100];

int n = 0;	//全局变量n，用于记录写入结构体数据的总数

void read()    //定义读取职工工资数据函数
{
    FILE *fp = fopen("gx.dat","rb+");    //定义文件指针
    int i = 0;
    if((fp==NULL)){    //打开当前目录下文件
        printf("\n文件打开失败！");
        getch();
        exit(-1);
    }

    for(i = 0;i < 100;i ++)    //读取文件的数据并存到结构体数组zggz中
    {
        int nRes = fscanf(fp,"%s%s%f%f%f%f%f%f%f", &zggz[i].number[10], &zggz[i].name[10], &zggz[i].gw_salary, 
                                                    &zggz[i].xj_salary, &zggz[i].subsidy, &zggz[i].jx_salary,
                                                    &zggz[i].yf_salary, &zggz[i].tax, &zggz[i].actual_wage);
        if (nRes == -1)    //判断是否读取到文件尾部
        {
            n = i;    //记录写入数据的条数
            fclose(fp);
            break;
        }	
    }

    /*
    for (i = 0; i<n; i++)    //输出结构体数组数据（用于检测）
    {
         printf("\n%s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", zggz[i].number, zggz[i].name,
                                zggz[i].gw_salary, zggz[i].xj_salary, zggz[i].subsidy, 
                                zggz[i].jx_salary, zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
    }
    */

    fclose(fp);    //关闭文件
    printf("\n文件读取结束！");
    printf("\n共有%d条数据被存入结构体数组\n\n", n);
}

void write()    //定义保存职工工资数据函数
{
    FILE *fp = fopen("gx.dat","wb+");
    int i = 0;

    if((fp==NULL)){    //打开当前目录下文件
        printf("\n文件打开失败！");
        getch();
        exit(-1);
    }

	for(i=0; i<n; i++)
    {
        fwrite(zggz, sizeof(zggz), 1, fp);    //将数据写入二进制文件
    }

    fclose(fp);
    printf("\n文件保存完毕！");
    printf("\n共有%d条数据被写入二进制文件\n\n", n);
}

void find()    //定义查询职工工资数据函数
{
    int i,j;
    char gonghao[10];
    printf("\n请输入要查询工资数据的工号：");
    scanf("%s", gonghao);
    for(i=0; i<n ;i++)
    {
        if(strcmp(gonghao, &zggz[i].number[10]) == 0)
        {
            printf("\n职员工号：%s\t\n姓名：%s\t\n岗位工资：%f\t", 
                        zggz[i].number, zggz[i].name, zggz[i].gw_salary);
            printf("\n薪级工资：%f\t\n职务津贴：%f\t\n绩效工资：%f\t", 
                        zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
            printf("\n应发工资：%f\t\n个人所得税：%f\t\n实发工资：%f\t\n",
                        zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
            break;
        }
    } 
	if(i == n)
    {
        printf("\n无此工号职工信息\n");
    }
}

void list()    //定义浏览职工工资数据函数
{
    char gonghao[10];
    int i, j;
    printf("\n请输入所要浏览的工号：");
    scanf("%s", gonghao);
    for(i=0; i<n; i++)
    {
        if(strcmp(gonghao, &zggz[i].number[10]) == 0)
        {
            for(j=i; j<n; j++)
            {
                printf("\n职员工号：%s\t\n姓名：%s\t\n岗位工资：%f\t",
                        zggz[j].number, zggz[j].name, zggz[j].gw_salary);
                printf("\n薪级工资：%f\t\n职务津贴：%f\t\n绩效工资：%f\t", 
                        zggz[j].xj_salary, zggz[j].subsidy, zggz[j].jx_salary);
                printf("\n应发工资：%f\t\n个人所得税：%f\t\n实发工资：%f\t\n", 
                        zggz[j].yf_salary, zggz[j].tax, zggz[j].actual_wage);
            }
            break;
        }
        
    }
    if(i == n)
    {
        printf("\n无此工号职工信息\n");
    }
}

void modify()    //定义修改职工工资数据函数
{
    char gonghao[10];
    int i, j;
    printf("\n请输入所要重新录入的工号：");
    scanf("%s", gonghao);
    for(i=0; i<n; i++)
    {
        if(strcmp(gonghao, &zggz[i].number[10]) == 0)
        {
            printf("\n请重新录入该职工数据：\n");
            printf("\n职员工号：\t");
            scanf("%s", zggz[i].number);
            printf("\n姓名：\t");
            scanf("%s", zggz[i].name);
            printf("\n岗位工资：\t");
            scanf("%f", zggz[i].gw_salary);
            printf("\n薪级工资：\t");
            scanf("%f", zggz[i].xj_salary);
        }
    }
	if(i == n)
    {
        printf("\n无此工号职工信息\n");
    }
	/*write();//保存写入到文件中*/
}

void del()    //定义删除职工工资数据函数
{
    /*
    char gonghao[10];
    int i, j;
    printf("\n请输入所要删除的工号：");
    scanf("%s", gonghao);
    for(i=0; i<n; i++)
    {
        if(strcmp(gonghao, zggz[i].number)==1)
        {
            for(j=i; j<n; j++)
            {}
        }
        else
        {
            printf("\n无此工号职工信息\n");
            break;
        }
    }
    */
}

void add()    //定义添加职工工资数据函数
{
    char s;
    printf("\n请输入职工基本信息：");
    for(; n<100; n++)
    {
        printf("\n工号：");
        scanf("%s", zggz[n].number);
        printf("\n姓名：");
        scanf("%s", zggz[n].name);
        printf("\n岗位工资：");
        scanf("%f", &zggz[n].gw_salary);
        printf("\n薪级工资：");
        scanf("%f", &zggz[n].xj_salary);
        printf("\n职务津贴：");
        scanf("%f", &zggz[n].subsidy);
        printf("\n绩效工资：");
        scanf("%f", &zggz[n].jx_salary);
        //grsds();

        printf("\n是否结束输入？是：y 否：n");
        scanf("%c", &s);
        if(strcmp(&s, "y") == 0)
        {
            break;
        }
        else if(strcmp(&s, "n") == 0)
        {
            continue;
        }
    }
}

void grsds()    //定义计算职工工资数据函数
{
}

int main()
{
    char s;
    int flag = 1;
    read();
    printf("请输入想进行操作的指令:");
    printf("\n1（查询），2（修改），3（添加），4（删除）");
    printf("\n5（保存），6（浏览），7（退出）\n\n");
    do
    {
        scanf("%s",  &s);
        if(strcmp(&s ,"1") == 0)
        {
            find();
        }
        else if(strcmp(&s ,"2") == 0)
        {
            modify();
        }
        else if(strcmp(&s ,"3") == 0)
        {
            add();
        }
        else if(strcmp(&s ,"4") == 0)
        {
            del();
        }
        else if(strcmp(&s ,"5") == 0)
        {
            write();
        }
        else if(strcmp(&s ,"6") == 0)
        {
            list();
        }
        else if(strcmp(&s ,"7") == 0)
        {
            flag = 0;
        }
        printf("\n无该指令，请重新输入！\n\n");
    }while(flag);
    return 0;
}
