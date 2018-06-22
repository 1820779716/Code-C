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
    char number[10];    //ְԱ����
    char name[10];    //ְԱ����
    float gw_salary;    //��λ����
    float xj_salary;    //н������
    float subsidy;    //ְ�����
    float jx_salary;    //��Ч����
    float yf_salary;    //Ӧ������
    float tax;    //��������˰
    float actual_wage;    //ʵ������
}zggz[100];

int n = 0;	//ȫ�ֱ���n�����ڼ�¼д��ṹ�����ݵ�����

void grsds(int m);    //��������ְ���������ݺ���

void read()    //�����ȡְ���������ݺ���
{
    FILE *fp = fopen("gx.dat","rb+");    //�����ļ�ָ��
    int i = 0;
    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n�ļ���ʧ�ܣ�");
        getch();
        exit(-1);
    }

    for(i = 0;i < 100;i ++)    //��ȡ�ļ������ݲ��浽�ṹ������zggz��
    {
        int nRes = fscanf(fp,"%s%s%f%f%f%f%f%f%f",
                  &zggz[i].number[10], &zggz[i].name[10], &zggz[i].gw_salary, 
                  &zggz[i].xj_salary, &zggz[i].subsidy, &zggz[i].jx_salary,
                  &zggz[i].yf_salary, &zggz[i].tax, &zggz[i].actual_wage);
        if (nRes == -1)    //�ж��Ƿ��ȡ���ļ�β��
        {
            n = i;    //��¼д�����ݵ�����
            fclose(fp);
            break;
        }	
    }

    /*
    for (i = 0; i < n; i ++)    //����ṹ���������ݣ����ڼ�⣩
    {
         printf("\n%s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
		          zggz[i].number, zggz[i].name, zggz[i].gw_salary, 
                  zggz[i].xj_salary, zggz[i].subsidy, 
                  zggz[i].jx_salary, zggz[i].yf_salary, 
                  zggz[i].tax, zggz[i].actual_wage);
    }
    */

    fclose(fp);    //�ر��ļ�
    printf("\n�ļ���ȡ������");
    printf("\n����%d�����ݱ�����ṹ������", n);
    printf("\n----------------------------------------------------\n");
}

void write()    //���屣��ְ���������ݺ���
{
    FILE *fp = fopen("gx.dat","wb+");
    int i = 0;

    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n�ļ���ʧ�ܣ�");
        getch();
        exit(-1);
    }

	for(i = 0; i < n; i ++)
    {
        fwrite(&zggz[i], sizeof(zggz[i]), 1, fp);    //������д��������ļ�
        fprintf(fp, "\n");    //��д���ļ�������β�����뻻�з�
    }

    fclose(fp);
    printf("\n�ļ�������ϣ�");
    printf("\n����%d�����ݱ�д��������ļ�\n\n", n);
}

void find()    //�����ѯְ���������ݺ���
{
    char gonghao[10];
    int i;
	int flag = 1;

    printf("\n��������Ҫ��ѯ�Ĺ��ţ�");
    do{
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, &zggz[i].number[10]) == 0)
            {
                printf("\nְԱ���ţ�%s\t\n������%s\t\n��λ���ʣ�%f\t", 
                        zggz[i].number, zggz[i].name, zggz[i].gw_salary);
                printf("\nн�����ʣ�%f\t\nְ�������%f\t\n��Ч���ʣ�%f\t", 
                        zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
                printf("\nӦ�����ʣ�%f\t\n��������˰��%f\t\nʵ�����ʣ�%f\t\n",
                        zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
		    	flag = 0;
                break;
            }
        }
        if(i == n)
        {
            printf("\n�޴˹���ְԱ��Ϣ\n");
	    	printf("\n��������ȷ�Ĺ��ţ�");
        }
    }while(flag);
}

void list()    //�������ְ���������ݺ���
{
    char gonghao[10];
    int i, j;
	int flag = 1;

    do{
        printf("\n��������Ҫ����Ĺ��ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, &zggz[i].number[10]) == 0)
            {
                for(j = i; j < n; j ++)
                {
                    printf("\nְԱ���ţ�%s\t\nְԱ������%s\t\n��λ���ʣ�%f\t",
                            zggz[j].number, zggz[j].name, zggz[j].gw_salary);
                    printf("\nн�����ʣ�%f\t\nְ�������%f\t\n��Ч���ʣ�%f\t", 
                            zggz[j].xj_salary, zggz[j].subsidy, zggz[j].jx_salary);
                    printf("\nӦ�����ʣ�%f\t\n��������˰��%f\t\nʵ�����ʣ�%f\t\n", 
                            zggz[j].yf_salary, zggz[j].tax, zggz[j].actual_wage);
                }
		    	flag = 0;
                break;
            }
        }
        if(i == n)
        {
            printf("\n�޴˹���ְԱ��Ϣ\n");
        }
    }while(flag);
}

void modify()    //�����޸�ְ���������ݺ���
{
    char gonghao[10];
    int i;
    int flag = 1;

    do
    {
        printf("\n��������Ҫ����¼���ְԱ���ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, &zggz[i].number[10]) == 0)
            {
                printf("\n������¼���ְ�����ݣ�\n");
                /*
                printf("\nְԱ���ţ�");
                scanf("%s", zggz[i].number);
                */

                printf("\nְԱ������");    //����ְԱ����
                scanf("%s", zggz[i].name);

                printf("\n��λ���ʣ�");    //�����λ����
                scanf("%f", &zggz[i].gw_salary);

                printf("\nн�����ʣ�");    //����н������
                scanf("%f", &zggz[i].xj_salary);

				printf("\nְ�������");    //����ְ�����
				scanf("%f", &zggz[i].subsidy);

				printf("\n��Ч���ʣ�");    //���뼨Ч����
				scanf("%f", &zggz[i].jx_salary);

				zggz[i].yf_salary = zggz[i].gw_salary + zggz[i].xj_salary 
                        + zggz[i].subsidy + zggz[i].jx_salary;

                grsds(n);    //�����������˰

                zggz[n].actual_wage = zggz[n].yf_salary - zggz[n].tax;
            }
        }
    	if(i == n)
        {
            printf("\n�޴˹���ְ����Ϣ\n");
        }
    }while(flag);
}

void del()    //����ɾ��ְ���������ݺ���
{
    char gonghao[10];
    int i, j;
	int flag = 1;

	do
    {
        printf("\n��������Ҫɾ����ְԱ���ţ�");
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
        if(i == n)    //���Һ󲻴��ڹ���
        {
            printf("\n�޴˹���ְ����Ϣ\n");
		}
    }while(flag);
}

void add()    //�������ְ���������ݺ���
{
    char ch, s[10];
	int i;
	int flag = 0;

    printf("\n������ְ��������Ϣ��");
    for(; n < 100; n ++)
    {
        do
        {
            printf("\nְԱ���ţ�");    //����ְԱ����
            scanf("%s", s);
            for(i = 0; i < n; i ++)
            {
                if(strcmp(s, &zggz[i].number[10]) == 0)
                {
                    printf("\n��ְԱ�����Ѵ��ڣ����������룡\n");
                    flag = 1;
                    break;
                }
            }
            if(i == n)    //ְԱ�������ظ�����ʼ��ֵ
            {
                strcpy(s, zggz[n].number);
                flag = 0;
            }
        }while(flag);

        printf("\nְԱ������");    //����ְԱ����
        scanf("%s", zggz[n].name);

        printf("\n��λ���ʣ�");    //�����λ����
        scanf("%f", &zggz[n].gw_salary);

        printf("\nн�����ʣ�");    //����н������
        scanf("%f", &zggz[n].xj_salary);

        printf("\nְ�������");    //����ְ�����
        scanf("%f", &zggz[n].subsidy);

        printf("\n��Ч���ʣ�");    //���뼨Ч����
        scanf("%f", &zggz[n].jx_salary);

    	zggz[n].yf_salary = zggz[n].gw_salary + zggz[n].xj_salary
		    +zggz[n].subsidy + zggz[n].jx_salary;    //����Ӧ������

        grsds(n);    //�����������˰

        zggz[n].actual_wage = zggz[n].yf_salary - zggz[n].tax;   //����ʵ������

        printf("\n�Ƿ�������룿�ǣ�y ��n");    //�ж��Ƿ�Ҫ��������
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

void grsds(int m)    //�������ְ����������˰����
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
    int flag = 1;    //���ڿ���ѭ����
    read();
    printf("��ϵͳ������ָ�");
    printf("\n1����ѯ����2���޸ģ���3����ӣ���4��ɾ����");
    printf("\n5�����棩��6���������7���˳���");
    printf("\n----------------------------------------------------\n");
    do
    {
        printf("����������в�����ָ�");
        scanf("%s",  &ch);
        if(strcmp(&ch ,"1") == 0)
        {
            find();
            printf("\n��ѯִ�н�����\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"2") == 0)
        {
            modify();
            printf("\n�޸�ִ�н�����\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"3") == 0)
        {
            add();
            printf("\n���ִ�н�����");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"4") == 0)
        {
            del();
            printf("\nɾ��ִ�н�����\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"5") == 0)
        {
            write();
            printf("\n����ִ�н�����\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"6") == 0)
        {
            list();
            printf("\n���ִ�н�����\n");
            printf("\n----------------------------------------------------\n");
        }
        else if(strcmp(&ch ,"7") == 0)
        {
            printf("\n��ȷ���ļ��Ƿ��Ѿ�����,�ǣ�y����n\n\n");
            scanf("%s", &ch);
            if(strcmp(&ch, "y") == 0)
            {
                flag = 0;
            }
			else if(strcmp(&ch, "n") == 0)
            {
                write();
                printf("\n����д����ϣ�\n");
                flag = 0;
            }
            printf("\n�˳�������......\n");
            break;
            printf("\n----------------------------------------------------\n");
        }
        else
        {
            printf("\n�޸�ָ����������룡\n\n");
        }
    }while(flag);
    return 0;
}
