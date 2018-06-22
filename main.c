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
1.read()    //reading file employee salary data and assigning it to 
             //an array of structures.
2.write()    //write structure array data to binary file.
3.find()    //query salary data of a certain employee 
            //and output it on the display.
4.list()    //browsing employee wage data starting from an employee.
5.modify()
6.del()
7.add()
8.grsds()

History:
   <author>     <time>     <version>           <desc>
     Jeff      18/06/21       0.1       perfect some functions
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct Employee{
    char number[10];    //职员工号
    char name[10];    //职员姓名
    float gw_salary;    //岗位工资
    float xj_salary;    //薪级工资
    float subsidy;    //职务津贴
    float jx_salary;    //绩效工资
    float yf_salary;    //应发工资
    float tax;    //个人所得税
    float actual_wage;    //实发工资
}zggz[100];

int n = 0;	//全局变量n，用于记录写入结构体数据的总数

void grsds(int m);    //声明计算职工工资数据函数

void read()    //定义读取职工工资数据函数
{
    FILE *fp = fopen("gx.dat","rb+");    //定义文件指针
    int i = 0;
    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n文件打开失败！");
        getch();
        exit(-1);
    }

    for(i = 0;i < 100;i ++)    //读取文件的数据并存到结构体数组zggz中
    {
        int nRes = fscanf(fp,"%s%s%f%f%f%f%f%f%f",
                  &zggz[i].number[10], &zggz[i].name[10], &zggz[i].gw_salary, 
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
         printf("\n%s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
		          zggz[i].number, zggz[i].name, zggz[i].gw_salary, 
                  zggz[i].xj_salary, zggz[i].subsidy, 
                  zggz[i].jx_salary, zggz[i].yf_salary, 
                  zggz[i].tax, zggz[i].actual_wage);
    }
    */

    fclose(fp);    //关闭文件
    printf("\n文件读取结束！");
    printf("\n共有%d条数据被存入结构体数组", n);
    printf("\n----------------------------------------------------\n");
}

void write()    //定义保存职工工资数据函数
{
    FILE *fp = fopen("gx.dat","wb+");
    int i = 0;

    if((fp == NULL))    //打开当前目录下文件
    {
        printf("\n文件打开失败！");
        getch();
        exit(-1);
    }

	for(i = 0; i < n; i ++)
    {
        fwrite(&zggz[i], sizeof(zggz[i]), 1, fp);    //将数据写入二进制文件
        fprintf(fp, "\n");    //给写入文件的数据尾部加入换行符
    }

    fclose(fp);
    printf("\n文件保存完毕！");
    printf("\n共有%d条数据被写入二进制文件\n\n", n);
}

void find()    //定义查询职工工资数据函数
{
    char gonghao[10];
    int i;
	int flag = 1;

    printf("\n请输入所要查询的工号：");
    do{
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, &zggz[i].number[10]) == 0)
            {
                printf("\n职员工号：%s\t\n姓名：%s\t\n岗位工资：%f\t", 
                        zggz[i].number, zggz[i].name, zggz[i].gw_salary);
                printf("\n薪级工资：%f\t\n职务津贴：%f\t\n绩效工资：%f\t", 
                        zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
                printf("\n应发工资：%f\t\n个人所得税：%f\t\n实发工资：%f\t\n",
                        zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
		    	flag = 0;
                break;
            }
        }
        if(i == n)
        {
            printf("\n无此工号职员信息\n");
	    	printf("\n请输入正确的工号：");
        }
    }while(flag);
}

void list()    //定义浏览职工工资数据函数
{
    char gonghao[10];
    int i, j;
	int flag = 1;

    do{
        printf("\n请输入所要浏览的工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, &zggz[i].number[10]) == 0)
            {
                for(j = i; j < n; j ++)
                {
                    printf("\n职员工号：%s\t\n职员姓名：%s\t\n岗位工资：%f\t",
                            zggz[j].number, zggz[j].name, zggz[j].gw_salary);
                    printf("\n薪级工资：%f\t\n职务津贴：%f\t\n绩效工资：%f\t", 
                            zggz[j].xj_salary, zggz[j].subsidy, zggz[j].jx_salary);
                    printf("\n应发工资：%f\t\n个人所得税：%f\t\n实发工资：%f\t\n", 
                            zggz[j].yf_salary, zggz[j].tax, zggz[j].actual_wage);
                }
		    	flag = 0;
                break;
            }
        }
        if(i == n)
        {
            printf("\n无此工号职员信息\n");
        }
    }while(flag);
}

void modify()    //定义修改职工工资数据函数
{
    char gonghao[10];
    int i;
    int flag = 1;

    do
    {
        printf("\n请输入所要重新录入的职员工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, &zggz[i].number[10]) == 0)
            {
                printf("\n请重新录入该职工数据：\n");
                /*
                printf("\n职员工号：");
                scanf("%s", zggz[i].number);
                */

                printf("\n职员姓名：");    //输入职员姓名
                scanf("%s", zggz[i].name);

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

                grsds(n);    //计算个人所得税

                zggz[n].actual_wage = zggz[n].yf_salary - zggz[n].tax;
            }
        }
    	if(i == n)
        {
            printf("\n无此工号职工信息\n");
        }
    }while(flag);
}

void del()    //定义删除职工工资数据函数
{
    char gonghao[10];
    int i, j;
	int flag = 1;

	do
    {
        printf("\n请输入所要删除的职员工号：");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 1)
            {
                for(j = i; j < n; j ++)
                {
                    zggz[j] = zggz[j+1];
                }
                n -= 1;
                break;
            }
        }
        if(i == n)    //查找后不存在工号
        {
            printf("\n无此工号职工信息\n");
		}
    }while(flag);
}

void add()    //定义添加职工工资数据函数
{
    char ch, s[10];
	int i;
	int flag = 0;

    printf("\n请输入职工基本信息：");
    for(; n < 100; n ++)
    {
        do
        {
            printf("\n职员工号：");    //输入职员工号
            scanf("%s", s);
            for(i = 0; i < n; i ++)
            {
                if(strcmp(s, &zggz[i].number[10]) == 0)
                {
                    printf("\n该职员工号已存在，请重新输入！\n");
                    flag = 1;
                    break;
                }
            }
            if(i == n)    //职员工号无重复，开始赋值
            {
                strcpy(s, zggz[n].number);
                flag = 0;
            }
        }while(flag);

        printf("\n职员姓名：");    //输入职员姓名
        scanf("%s", zggz[n].name);

        printf("\n岗位工资：");    //输入岗位工资
        scanf("%f", &zggz[n].gw_salary);

        printf("\n薪级工资：");    //输入薪级工资
        scanf("%f", &zggz[n].xj_salary);

        printf("\n职务津贴：");    //输入职务津贴
        scanf("%f", &zggz[n].subsidy);

        printf("\n绩效工资：");    //输入绩效工资
        scanf("%f", &zggz[n].jx_salary);

    	zggz[n].yf_salary = zggz[n].gw_salary + zggz[n].xj_salary
		    +zggz[n].subsidy + zggz[n].jx_salary;    //计算应发工资

        grsds(n);    //计算个人所得税

        zggz[n].actual_wage = zggz[n].yf_salary - zggz[n].tax;   //计算实发工资

        printf("\n是否结束输入？是：y 否：n");    //判断是否要结束输入
        scanf("%s", &ch);
        if(strcmp(&ch, "y") == 0)
        {
            break;
        }
        else if(strcmp(&ch, "n") == 0)
        {
            continue;
        }
    }
}

void grsds(int m)    //定义计算职工个人所得税函数
{
	float count, tax;
	int flag = 0;
	count = zggz[n].yf_salary;
	zggz[n].tax = 0;

    do
    {
        if(count < 500)
        {
	        tax = count * 0.05;
            flag = 0;
        }
        else if(count < 2000)
        {
            tax = (count - 500) * 0.1;
	    	count -= 500;
        }
        else if(count < 5000)
        {
    		tax = count - 2000 * 0.15;
	    	count -= 2000;
        }
        else if(count < 20000)
        {
    		tax = (count - 5000) * 0.2;
	    	count -= 5000;
        }
        else if(count < 40000)
        {
    		tax = (count - 20000) * 0.25;
	    	count -= 20000;
        }
        else if(count < 60000)
        {
    		tax = (count - 40000) * 0.3;
	    	count -= 40000;
        }
        else if(count < 80000)
        {
            tax = (count - 60000) * 0.35;
	    	count -= 60000;
        }
        else if(count < 10000)
        {
    		tax = (count - 80000) * 0.4;
	    	count -= 80000;
        }
        else
        {
            tax = (count - 100000) * 0.45;
	    	count -= 100000;
        }
        zggz[n].tax += tax;
    }while(flag);
}

int main()
{
    char ch;
    int flag = 1;    //用于控制循环体
    read();
    printf("本系统有如下指令：");
    printf("\n1（查询），2（修改），3（添加），4（删除）");
    printf("\n5（保存），6（浏览），7（退出）");
    printf("\n----------------------------------------------------\n");
    do
    {
        printf("请输入想进行操作的指令：");
        scanf("%s",  &ch);
        if(strcmp(&ch ,"1") == 0)
        {
            find();
            printf("\n查询执行结束！\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"2") == 0)
        {
            modify();
            printf("\n修改执行结束！\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"3") == 0)
        {
            add();
            printf("\n添加执行结束！");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"4") == 0)
        {
            del();
            printf("\n删除执行结束！\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"5") == 0)
        {
            write();
            printf("\n保存执行结束！\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"6") == 0)
        {
            list();
            printf("\n浏览执行结束！\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"7") == 0)
        {
            printf("\n请确认文件是否已经保存,是：y，否：n\n\n");
            scanf("%s", &ch);
            if(strcmp(&ch, "y") == 0)
            {
                flag = 0;
            }
			else if(strcmp(&ch, "n") == 0)
            {
                write();
                printf("\n数据写入完毕！\n");
                flag = 0;
            }
            printf("\n退出程序中......\n");
            break;
            printf("\n----------------------------------------------------\n");
        }
        else
        {
            printf("\n无该指令，请重新输入！\n\n");
        }
    }while(flag);
    return 0;
}
