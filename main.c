/****************************************************************************
Copyright (C), 2018, Jeff, Ltd.

File name: main.cpp    

Author:  Jeff   Version:  0.1    Date:  2018.06.23

Description: This programe is use to manage emplyee's salary, the controls
             include read and write the binary file, query, browse, insert,
             delete data and save the data into the binary file, and it
             also could account the salary about the after-tax wages.

Others: Interface to be beautified.

Function List:
1.read()    //reading file employee salary data and assigning it to 
             //an array of structures.
2.write()    //write structure array data to binary file.
3.find()    //query salary data of a certain employee 
            //and output it on the display.
4.list()    //browsing employee wage data starting from an employee.
5.modify()    //modify employee's wage data
6.del()    //delete employee's data
7.add()    //add new employee's data
8.grsds()    //account employee's tax

History:
   <author>     <time>     <version>             <desc>
     Jeff      18/06/25       0.1        correct the function of grsds
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee{
    char number[10];    //职员工号
    char name[10];    //职员姓名
    double gw_salary;    //岗位工资
    double xj_salary;    //薪级工资
    double subsidy;    //职务津贴
    double jx_salary;    //绩效工资
    double yf_salary;    //应发工资
    double tax;    //个人所得税
    double actual_wage;    //实发工资
}zggz[100];

int n = 0;	//全局变量n，用于记录写入结构体数据的总数

void grsds(int m);    //声明计算职工工资数据函数

void read()    //定义读取职工工资数据函数
{
    FILE *fp = fopen("gx.dat","rb");    //定义文件指针
    int i;
	char ch;
    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n文件打开失败！");
        exit(-1);
    }

    for(i = 0;i < 100;i ++)    //读取文件的数据并存到结构体数组zggz中
    {
        int nRes = fscanf(fp,"%s %s %f %f %f %f %f %f %f",
                  zggz[i].number, zggz[i].name, &zggz[i].gw_salary, 
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
    for (i = 0; i < n; i ++)    //输出结构体数组数据（用于检测）
    {
         printf("\n%s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",
		          zggz[i].number, zggz[i].name, zggz[i].gw_salary, 
                  zggz[i].xj_salary, zggz[i].subsidy, 
                  zggz[i].jx_salary, zggz[i].yf_salary, 
                  zggz[i].tax, zggz[i].actual_wage);
    }
    */

    fclose(fp);    //关闭文件
    printf("\n文件读取结束！");
    printf("\n共有%d条数据被存入结构体数组", n);
    printf("\n------------------------------------------------\n");
}

void write()    //定义保存职工工资数据函数
{
    FILE *fp = fopen("gx.dat","wb");
    int i;
    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n文件打开失败！");
        exit(1);
    }

    for (i = 0; i < n; i ++)    //将数据写入二进制文件
    {
        fprintf(fp, "%s %s %f %f %f %f %f %f %f \n",
		          zggz[i].number, zggz[i].name, zggz[i].gw_salary, 
                  zggz[i].xj_salary, zggz[i].subsidy, 
                  zggz[i].jx_salary, zggz[i].yf_salary, 
                  zggz[i].tax, zggz[i].actual_wage);
    }
	/*
	for(i = 0; i < n; i ++)
    {
        fwrite(&zggz[i], sizeof(zggz[i]), 1, fp);    //将数据写入二进制文件
    }
	*/
    fclose(fp);
    printf("\n文件保存完毕！");
    printf("\n共有%d条数据被写入文件\n\n", i);
}

void find()    //定义查询职工工资数据函数
{
    char gonghao[10];
    int i;
	int flag = 1;
	
    printf("\n----------------------查询----------------------\n");
    printf("\n请输入所要查询的工号：");
    do{
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n---------------所查询的职工信息为---------------\n");
                printf("\n职员工号：%s\t\n姓名：%s\t\n岗位工资：%.2f\t", 
                    zggz[i].number, zggz[i].name, zggz[i].gw_salary);
                printf("\n薪级工资：%.2f\t\n职务津贴：%.2f\t\n绩效工资：%.2f\t", 
                    zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
                printf("\n应发工资：%.2f\t\n个人所得税：%.2f\t\n实发工资：%.2f\t\n",
                    zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
		    	flag = 0;
                printf("\n--------------------查询结束--------------------\n");
                break;
            }
        }
        if(flag == 1)
        {
            printf("\n无此工号职员信息\n");
	    	printf("\n请输入正确的工号：");
        }
    }while(flag);
}

void list()    //定义浏览职工工资数据函数
{
    int i;
    printf("\n----------------------浏览----------------------\n");
    printf("\n------------------职工工资数据------------------\n");
    for(i = 0; i < n; i ++)
    {
        printf("\n职员工号：%s\t\n职员姓名：%s\t\n岗位工资：%.2f\t", 
			zggz[i].number, zggz[i].name, zggz[i].gw_salary);
        printf("\n薪级工资：%.2f\t\n职务津贴：%.2f\t\n绩效工资：%.2f\t", 
            zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
        printf("\n应发工资：%.2f\t\n个人所得税：%.2f\t\n实发工资：%.2f\t\n", 
            zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
     }
     printf("\n--------------------浏览结束--------------------\n");
}

void modify()    //定义修改职工工资数据函数
{
    char gonghao[10];
    int i;
    int flag = 1;
    printf("\n----------------------修改----------------------\n");

    do
    {
        printf("\n请输入所要重新录入数据的职员工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n请录入该职工的工资数据：\n");
                
                printf("\n岗位工资：");    //输入岗位工资
                scanf("%f", &zggz[i].gw_salary);

                printf("\n薪级工资：");    //输入薪级工资
                scanf("%f", &zggz[i].xj_salary);

				printf("\n职务津贴：");    //输入职务津贴
				scanf("%f", &zggz[i].subsidy);

				printf("\n绩效工资：");    //输入绩效工资
				scanf("%f", &zggz[i].jx_salary);

				zggz[i].yf_salary = zggz[i].gw_salary + zggz[i].xj_salary 
                        + zggz[i].subsidy + zggz[i].jx_salary;

                grsds(i);    //计算个人所得税

                zggz[i].actual_wage = zggz[i].yf_salary - zggz[i].tax;
				flag = 0;
				break;
            }
        }
    	if(flag == 1)
        {
            printf("\n无此工号职工信息\n");
        }
    }while(flag);
    printf("\n--------------------修改结束--------------------\n");
}

void del()    //定义删除职工工资数据函数
{
    char gonghao[10];
	char s[5];
    int i, j;
	int flag = 1;
    printf("\n----------------------删除----------------------\n");

    do
    {
        printf("\n请输入所要删除的职员工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n是否删除该职员信息？是：y，否：n\n");
                scanf("%s", s);
                if(strcmp(s, "y") == 0)
                {
                    for(j = i; j < n; j ++)
                    {
                        zggz[j] = zggz[j+1];
                    }
                    n -= 1;    //记录总人数
                    flag = 0;
                    printf("\n--------------------删除成功--------------------\n");
                    break;
                }
                else if(strcmp(s, "n") == 0)
                {
                    flag = 0;
                    printf("\n--------------------删除取消--------------------\n");
                    break;
                }
            }
        }
        if(flag == 1)    //查找后不存在工号
        {
            printf("\n无此工号职员信息\n");
            flag = 0;
		}
    }while(flag);
}

void add()    //定义添加职工工资数据函数
{
    char ch[10], s[10];
	int i, j = n;
	int flag = 1;

    printf("\n----------------------添加----------------------\n");
    printf("\n请输入职工基本信息：");
    for(; j < 100; )
    {
        do
        {
            printf("\n职员工号：");    //输入职员工号
            scanf("%s", s);
            for(i = 0; i < j; i ++)
            {
                if(strcmp(s, zggz[i].number) == 0)
                {
                    printf("\n该职员工号已存在，请重新输入！\n");
                    flag = 1;
                    break;
                }
            }
            if(i == j)    //职员工号无重复，开始赋值
            {
                strcpy(zggz[j].number, s);
				//printf("\n职员工号：%s\n", zggz[i].number);
                flag = 0;    //赋值后控制循环体结束循环
            }
        }while(flag);

        printf("\n职员姓名：");    //输入职员姓名
        scanf("%s", zggz[j].name);

        printf("\n岗位工资：");    //输入岗位工资
        scanf("%lf", &zggz[j].gw_salary);

        printf("\n薪级工资：");    //输入薪级工资
        scanf("%lf", &zggz[j].xj_salary);

        printf("\n职务津贴：");    //输入职务津贴
        scanf("%lf", &zggz[j].subsidy);

        printf("\n绩效工资：");    //输入绩效工资
        scanf("%lf", &zggz[j].jx_salary);

    	zggz[j].yf_salary = zggz[j].gw_salary + zggz[j].xj_salary
		    +zggz[j].subsidy + zggz[j].jx_salary;    //计算应发工资

        grsds(j);    //计算个人所得税

        zggz[j].actual_wage = zggz[j].yf_salary - zggz[j].tax;   //计算实发工资
		
        n = j;    //记录总人数
		break;
    }
    printf("\n------------------所增职工信息------------------\n");
    printf("\n职员工号：%s\t\n姓名：%s\t\n岗位工资：%.2f\t",
        zggz[n].number, zggz[n].name, zggz[n].gw_salary);
    printf("\n薪级工资：%.2f\t\n职务津贴：%.2f\t\n绩效工资：%.2f\t", 
        zggz[n].xj_salary, zggz[n].subsidy, zggz[n].jx_salary);
    printf("\n应发工资：%.2f\t\n个人所得税：%.2f\t\n实发工资：%.2f\t",
        zggz[n].yf_salary, zggz[n].tax, zggz[n].actual_wage);
    printf("\n--------------------添加完成--------------------\n");
}

void grsds(int m)    //定义计算职工个人所得税函数
{
	double count, tax;
	int flag = 0;
	count = zggz[m].yf_salary;    //应发工资
	zggz[m].tax = 0;    //作累加器

    do
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
        zggz[m].tax += tax;    //累加每层的个人所得税
    }while(flag);
}

int main()
{
    char s[5], ch[5];
    int flag = 1;    //用于控制循环体
    read();
    printf("\n-----------------本系统指令如下-----------------\n");
    printf("\n1（查询），2（修改），3（添加），4（删除）");
    printf("\n5（保存），6（浏览），7（退出）");
    printf("\n------------------------------------------------\n");
    do
    {
        printf("请输入想进行操作的指令：");
        scanf("%s",  s);
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
            add();
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
            printf("\n请确认文件是否已经保存,是：y，否：n\n\n");
            scanf("%s", ch);
            if(strcmp(ch, "y") == 0)
            {
            }
			else if(strcmp(ch, "n") == 0)
            {
                write();
                printf("\n数据写入完毕！\n");
			}
            printf("\n退出程序中......");
            printf("\n----------------------------------------------------\n");
            flag = 0;
        }
        else
        {
            printf("\n无该指令，请重新输入！\n\n");
        }
    }while(flag);
    return 0;
}
