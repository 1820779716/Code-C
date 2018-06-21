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
    char number[10];    //����
    char name[10];    //����
    float gw_salary;    //��λ����
    float xj_salary;    //н������
    float subsidy;    //ְ�����
    float jx_salary;    //��Ч����
    float yf_salary;    //Ӧ������
    float tax;    //��������˰
    float actual_wage;    //ʵ������
}zggz[100];

int n = 0;	//ȫ�ֱ���n�����ڼ�¼д��ṹ�����ݵ�����

void read()    //�����ȡְ���������ݺ���
{
    FILE *fp = fopen("gx.dat","rb+");    //�����ļ�ָ��
    int i = 0;
    if((fp==NULL)){    //�򿪵�ǰĿ¼���ļ�
        printf("\n�ļ���ʧ�ܣ�");
        getch();
        exit(-1);
    }

    for(i = 0;i < 100;i ++)    //��ȡ�ļ������ݲ��浽�ṹ������zggz��
    {
        int nRes = fscanf(fp,"%s%s%f%f%f%f%f%f%f", &zggz[i].number[10], &zggz[i].name[10], &zggz[i].gw_salary, 
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
    for (i = 0; i<n; i++)    //����ṹ���������ݣ����ڼ�⣩
    {
         printf("\n%s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", zggz[i].number, zggz[i].name,
                                zggz[i].gw_salary, zggz[i].xj_salary, zggz[i].subsidy, 
                                zggz[i].jx_salary, zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
    }
    */

    fclose(fp);    //�ر��ļ�
    printf("\n�ļ���ȡ������");
    printf("\n����%d�����ݱ�����ṹ������\n\n", n);
}

void write()    //���屣��ְ���������ݺ���
{
    FILE *fp = fopen("gx.dat","wb+");
    int i = 0;

    if((fp==NULL)){    //�򿪵�ǰĿ¼���ļ�
        printf("\n�ļ���ʧ�ܣ�");
        getch();
        exit(-1);
    }

	for(i=0; i<n; i++)
    {
        fwrite(zggz, sizeof(zggz), 1, fp);    //������д��������ļ�
    }

    fclose(fp);
    printf("\n�ļ�������ϣ�");
    printf("\n����%d�����ݱ�д��������ļ�\n\n", n);
}

void find()    //�����ѯְ���������ݺ���
{
    int i,j;
    char gonghao[10];
    printf("\n������Ҫ��ѯ�������ݵĹ��ţ�");
    scanf("%s", gonghao);
    for(i=0; i<n ;i++)
    {
        if(strcmp(gonghao, &zggz[i].number[10]) == 0)
        {
            printf("\nְԱ���ţ�%s\t\n������%s\t\n��λ���ʣ�%f\t", 
                        zggz[i].number, zggz[i].name, zggz[i].gw_salary);
            printf("\nн�����ʣ�%f\t\nְ�������%f\t\n��Ч���ʣ�%f\t", 
                        zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
            printf("\nӦ�����ʣ�%f\t\n��������˰��%f\t\nʵ�����ʣ�%f\t\n",
                        zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
            break;
        }
    } 
	if(i == n)
    {
        printf("\n�޴˹���ְ����Ϣ\n");
    }
}

void list()    //�������ְ���������ݺ���
{
    char gonghao[10];
    int i, j;
    printf("\n��������Ҫ����Ĺ��ţ�");
    scanf("%s", gonghao);
    for(i=0; i<n; i++)
    {
        if(strcmp(gonghao, &zggz[i].number[10]) == 0)
        {
            for(j=i; j<n; j++)
            {
                printf("\nְԱ���ţ�%s\t\n������%s\t\n��λ���ʣ�%f\t",
                        zggz[j].number, zggz[j].name, zggz[j].gw_salary);
                printf("\nн�����ʣ�%f\t\nְ�������%f\t\n��Ч���ʣ�%f\t", 
                        zggz[j].xj_salary, zggz[j].subsidy, zggz[j].jx_salary);
                printf("\nӦ�����ʣ�%f\t\n��������˰��%f\t\nʵ�����ʣ�%f\t\n", 
                        zggz[j].yf_salary, zggz[j].tax, zggz[j].actual_wage);
            }
            break;
        }
        
    }
    if(i == n)
    {
        printf("\n�޴˹���ְ����Ϣ\n");
    }
}

void modify()    //�����޸�ְ���������ݺ���
{
    char gonghao[10];
    int i, j;
    printf("\n��������Ҫ����¼��Ĺ��ţ�");
    scanf("%s", gonghao);
    for(i=0; i<n; i++)
    {
        if(strcmp(gonghao, &zggz[i].number[10]) == 0)
        {
            printf("\n������¼���ְ�����ݣ�\n");
            printf("\nְԱ���ţ�\t");
            scanf("%s", zggz[i].number);
            printf("\n������\t");
            scanf("%s", zggz[i].name);
            printf("\n��λ���ʣ�\t");
            scanf("%f", zggz[i].gw_salary);
            printf("\nн�����ʣ�\t");
            scanf("%f", zggz[i].xj_salary);
        }
    }
	if(i == n)
    {
        printf("\n�޴˹���ְ����Ϣ\n");
    }
	/*write();//����д�뵽�ļ���*/
}

void del()    //����ɾ��ְ���������ݺ���
{
    /*
    char gonghao[10];
    int i, j;
    printf("\n��������Ҫɾ���Ĺ��ţ�");
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
            printf("\n�޴˹���ְ����Ϣ\n");
            break;
        }
    }
    */
}

void add()    //�������ְ���������ݺ���
{
    char s;
    printf("\n������ְ��������Ϣ��");
    for(; n<100; n++)
    {
        printf("\n���ţ�");
        scanf("%s", zggz[n].number);
        printf("\n������");
        scanf("%s", zggz[n].name);
        printf("\n��λ���ʣ�");
        scanf("%f", &zggz[n].gw_salary);
        printf("\nн�����ʣ�");
        scanf("%f", &zggz[n].xj_salary);
        printf("\nְ�������");
        scanf("%f", &zggz[n].subsidy);
        printf("\n��Ч���ʣ�");
        scanf("%f", &zggz[n].jx_salary);
        //grsds();

        printf("\n�Ƿ�������룿�ǣ�y ��n");
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

void grsds()    //�������ְ���������ݺ���
{
}

int main()
{
    char s;
    int flag = 1;
    read();
    printf("����������в�����ָ��:");
    printf("\n1����ѯ����2���޸ģ���3����ӣ���4��ɾ����");
    printf("\n5�����棩��6���������7���˳���\n\n");
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
        printf("\n�޸�ָ����������룡\n\n");
    }while(flag);
    return 0;
}
