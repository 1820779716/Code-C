/****************************************************************************
Copyright (C), 2018, Jeff, Ltd.

File name: main.cpp    

Author:  Jeff   Version:  0.1    Date:  2018.06.23

Description: This programe is use to manage emplyee's salary, the controls
             include read and write the binary file, query, browse, insert,
             delete data and save the data into the binary file, and it
             also could account the salary about the after-tax wages.

Others: The function of write still have some quetions.

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
   <author>     <time>     <version>           <desc>
     Jeff      18/06/23       0.1       correct some problem
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
    FILE *fp = fopen("gx.dat","rb");    //�����ļ�ָ��
    int i = 0;
    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n�ļ���ʧ�ܣ�");
        getch();
        exit(-1);
    }

    for(i = 0;i < 100;i ++)    //��ȡ�ļ������ݲ��浽�ṹ������zggz��
    {
        int nRes = fscanf(fp,"%s %s %f %f %f %f %f %f %f",
                  zggz[i].number, zggz[i].name, &zggz[i].gw_salary, 
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
         printf("\n%s %s %.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",
		          zggz[i].number, zggz[i].name, zggz[i].gw_salary, 
                  zggz[i].xj_salary, zggz[i].subsidy, 
                  zggz[i].jx_salary, zggz[i].yf_salary, 
                  zggz[i].tax, zggz[i].actual_wage);
    }
    */

    fclose(fp);    //�ر��ļ�
    printf("\n�ļ���ȡ������");
    printf("\n����%d�����ݱ�����ṹ������", n);
    printf("\n------------------------------------------------\n");
}

void write()    //���屣��ְ���������ݺ���
{
    FILE *fp = fopen("gx.dat","rb+");
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
        fprintf(fp, " \n");    //��д���ļ�������β�����뻻�з�
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
	
    printf("\n----------------------��ѯ----------------------\n");
    printf("\n��������Ҫ��ѯ�Ĺ��ţ�");
    do{
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n---------------����ѯ��ְ����ϢΪ---------------\n");
                printf("\nְԱ���ţ�%s\t\n������%s\t\n��λ���ʣ�%.2f\t", 
                    zggz[i].number, zggz[i].name, zggz[i].gw_salary);
                printf("\nн�����ʣ�%.2f\t\nְ�������%.2f\t\n��Ч���ʣ�%.2f\t", 
                    zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
                printf("\nӦ�����ʣ�%.2f\t\n��������˰��%.2f\t\nʵ�����ʣ�%.2f\t\n",
                    zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
		    	flag = 0;
                printf("\n--------------------��ѯ����--------------------\n");
                break;
            }
        }
        if(flag == 1)
        {
            printf("\n�޴˹���ְԱ��Ϣ\n");
	    	printf("\n��������ȷ�Ĺ��ţ�");
        }
    }while(flag);
}

void list()    //�������ְ���������ݺ���
{
    int i;
    printf("\n----------------------���----------------------\n");
    printf("\n------------------ְ����������------------------\n");
    for(i = 0; i < n; i ++)
    {
        printf("\nְԱ���ţ�%s\t\nְԱ������%s\t\n��λ���ʣ�%.2f\t", 
			zggz[i].number, zggz[i].name, zggz[i].gw_salary);
        printf("\nн�����ʣ�%.2f\t\nְ�������%.2f\t\n��Ч���ʣ�%.2f\t", 
            zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
        printf("\nӦ�����ʣ�%.2f\t\n��������˰��%.2f\t\nʵ�����ʣ�%.2f\t\n", 
            zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
     }
     printf("\n--------------------�������--------------------\n");
}

void modify()    //�����޸�ְ���������ݺ���
{
    char gonghao[10];
    int i;
    int flag = 1;
    printf("\n----------------------�޸�----------------------\n");

    do
    {
        printf("\n��������Ҫ����¼�����ݵ�ְԱ���ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n��¼���ְ���Ĺ������ݣ�\n");
                
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

                grsds(i);    //�����������˰

                zggz[i].actual_wage = zggz[i].yf_salary - zggz[i].tax;
				flag = 0;
				break;
            }
        }
    	if(flag == 1)
        {
            printf("\n�޴˹���ְ����Ϣ\n");
        }
    }while(flag);
    printf("\n--------------------�޸Ľ���--------------------\n");
}

void del()    //����ɾ��ְ���������ݺ���
{
    char gonghao[10];
	char s[5];
    int i, j;
	int flag = 1;
    printf("\n----------------------ɾ��----------------------\n");
    /*
    do
    {
        printf("\n��������Ҫɾ����ְԱ���ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                for(j = i; j < n; j ++)
                {
                    zggz[j] = zggz[j+1];
                }
                n -= 1;
                flag = 0;
                break;
            }
        }
        if(flag == 1)    //���Һ󲻴��ڹ���
        {
            printf("\n�޴˹���ְ����Ϣ\n");
		}
    }while(flag);
    */
    do
    {
        printf("\n��������Ҫɾ����ְԱ���ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n�Ƿ�ɾ����ְԱ��Ϣ���ǣ�y����n\n");
                scanf("%s", s);
                if(strcmp(s, "y") == 0)
                {
                    for(j = i; j < n; j ++)
                    {
                        zggz[j] = zggz[j+1];
                    }
                    n -= 1;    //��¼������
                    flag = 0;
                    printf("\n--------------------ɾ���ɹ�--------------------\n");
                    break;
                }
                else if(strcmp(s, "n") == 0)
                {
                    flag = 0;
                    printf("\n--------------------ɾ��ȡ��--------------------\n");
                    break;
                }
            }
        }
        if(flag == 1)    //���Һ󲻴��ڹ���
        {
            printf("\n�޴˹���ְԱ��Ϣ\n");
            flag = 0;
		}
    }while(flag);
}

void add()    //�������ְ���������ݺ���
{
    char ch[10], s[10];
	int i, j = n;
	int flag = 1;

    printf("\n--------------------------���--------------------------\n");
    printf("\n������ְ��������Ϣ��");
    for(; j < 100; )
    {
        do
        {
            printf("\nְԱ���ţ�");    //����ְԱ����
            scanf("%s", s);
            for(i = 0; i < j; i ++)
            {
                if(strcmp(s, zggz[i].number) == 0)
                {
                    printf("\n��ְԱ�����Ѵ��ڣ����������룡\n");
                    flag = 1;
                    break;
                }
            }
            if(i == j)    //ְԱ�������ظ�����ʼ��ֵ
            {
                strcpy(zggz[n].number, s);
				//printf("\nְԱ���ţ�%s\n", zggz[i].number);
                flag = 0;    //��ֵ�����ѭ�������ѭ��
            }
        }while(flag);

        printf("\nְԱ������");    //����ְԱ����
        scanf("%s", zggz[j].name);

        printf("\n��λ���ʣ�");    //�����λ����
        scanf("%f", &zggz[j].gw_salary);

        printf("\nн�����ʣ�");    //����н������
        scanf("%f", &zggz[j].xj_salary);

        printf("\nְ�������");    //����ְ�����
        scanf("%f", &zggz[j].subsidy);

        printf("\n��Ч���ʣ�");    //���뼨Ч����
        scanf("%f", &zggz[j].jx_salary);

    	zggz[j].yf_salary = zggz[j].gw_salary + zggz[j].xj_salary
		    +zggz[j].subsidy + zggz[j].jx_salary;    //����Ӧ������

        grsds(j);    //�����������˰

        zggz[j].actual_wage = zggz[j].yf_salary - zggz[j].tax;   //����ʵ������
		
        n = j + 1;    //��¼������
		break;
        /*
        j += 1;    //����+1

        printf("\n�Ƿ�������룿�ǣ�y ��n\n");    //�ж��Ƿ�Ҫ��������
        scanf("%s", ch);
        if(strcmp(ch, "y") == 0)
        {
            for(; n < j; n +=1)
            {
                printf("\n--------------------����ְ����Ϣ--------------------\n");
                printf("\nְԱ���ţ�%s\t\n������%s\t\n��λ���ʣ�%.2f\t",
                    zggz[n].number, zggz[n].name, zggz[n].gw_salary);
                printf("\nн�����ʣ�%.2f\t\nְ�������%.2f\t\n��Ч���ʣ�%.2f\t", 
                    zggz[n].xj_salary, zggz[n].subsidy, zggz[n].jx_salary);
                printf("\nӦ�����ʣ�%.2f\t\n��������˰��%.2f\t\nʵ�����ʣ�%.2f\t",
                    zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
            }
            break;
        }
        else if(strcmp(ch, "n") == 0)
        {
            continue;
        }
        */
    }
    printf("\n----------------------����ְ����Ϣ----------------------\n");
    printf("\nְԱ���ţ�%s\t\n������%s\t\n��λ���ʣ�%.2f\t",
        zggz[i].number, zggz[i].name, zggz[i].gw_salary);
    printf("\nн�����ʣ�%.2f\t\nְ�������%.2f\t\n��Ч���ʣ�%.2f\t", 
        zggz[i].xj_salary, zggz[i].subsidy, zggz[i].jx_salary);
    printf("\nӦ�����ʣ�%.2f\t\n��������˰��%.2f\t\nʵ�����ʣ�%.2f\t",
        zggz[i].yf_salary, zggz[i].tax, zggz[i].actual_wage);
    printf("\n------------------------������------------------------\n");
}

void grsds(int m)    //�������ְ����������˰����
{
	float count, tax;
	int flag = 0;
	count = zggz[n].yf_salary;    //Ӧ������
	zggz[n].tax = 0;    //���ۼ���

    do
    {
        if(count < 500)
        {
	        tax = count * 0.05;
            flag = 0;    //Ӧ��������ȡ��������˰����С��500ֹͣ
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
        zggz[n].tax += tax;    //�ۼ�ÿ��ĸ�������˰
    }while(flag);
}

int main()
{
    char s[5], ch[5];
    int flag = 1;    //���ڿ���ѭ����
    read();
    printf("\n-----------------��ϵͳָ������-----------------\n");
    printf("\n1����ѯ����2���޸ģ���3����ӣ���4��ɾ����");
    printf("\n5�����棩��6���������7���˳���");
    printf("\n------------------------------------------------\n");
    do
    {
        printf("����������в�����ָ�");
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
            printf("\n��ȷ���ļ��Ƿ��Ѿ�����,�ǣ�y����n\n\n");
            scanf("%s", ch);
            if(strcmp(ch, "y") == 0)
            {
            }
			else if(strcmp(ch, "n") == 0)
            {
                write();
                printf("\n����д����ϣ�\n");
			}
            printf("\n�˳�������......");
            printf("\n----------------------------------------------------\n");
            flag = 0;
        }
        else
        {
            printf("\n�޸�ָ����������룡\n\n");
        }
    }while(flag);
    return 0;
}
