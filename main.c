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
     Jeff      18/07/01       0.1       adjust structure
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee{
    char number[10];    //ְԱ����
    char name[10];      //ְԱ����
    float gwgz;         //��λ����
    float xjgz;         //н������
    float subsidy;      //ְ�����
    float jxgz;         //��Ч����
    float yfgz;         //Ӧ������
    float tax;          //��������˰
    float sfgz;         //ʵ������
}zggz[100];

int n = 0;    //���ڼ�¼д��ṹ�����ݵ�����

void input_data(int i);  //��������ְԱ�������ݵĺ���
void show_data(int i);   //������ʾְԱ�������ݵĺ���
void read();        //������ȡְ���������ݵĺ���
void write();       //��������ְ���������ݵĺ���
void find();        //������ѯְ���������ݵĺ���
void list();        //�������ְ���������ݵĺ���
void modify();      //�����޸�ְ���������ݵĺ���
void del();         //����ɾ��ְ���������ݵĺ���
void add();         //�������ְ���������ݵĺ���
void grsds(int i);  //���������������˰�ĺ���


int main()
{
    char s[5], ch[5];
    int flag = 1;    //���ڿ���ѭ����
    read();

    while(flag)
    {
        printf("\n\n\n\t");
        printf("###  ��ӭʹ�ù��������ѧ�������Ϣ��ȫѧԺְ�����ʹ���ϵͳ  ###");
        printf("\n\n\n\t");
        printf("��ѡ��1 - 7����\n\t");
        printf("================================================================");
        printf("\n\t");
        printf("|        1. ��ѯְ�����ʼ�¼                                   |");
        printf("\n\t");
        printf("|        2. �޸�ְ�����ʼ�¼                                   |");
        printf("\n\t");
        printf("|        3. ���ְ�����ʼ�¼                                   |");
        printf("\n\t");
        printf("|        4. ɾ��ְ�����ʼ�¼                                   |");
        printf("\n\t");
        printf("|        5. �������ݵ��ļ�                                     |");
        printf("\n\t");
        printf("|        6. ���ְ����¼                                       |");
        printf("\n\t");
        printf("|        7. �˳�ϵͳ                                           |");
        printf("\n\t");
        printf("================================================================");
        printf("\n\n\t");
        printf("���ѡ���ǣ�");
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
                printf("\n\t�����������ƣ�\n\n");
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
            printf("\n\t�Ƿ���Ҫ�����������ݣ��ǣ�y���������ַ�\n\t");
            scanf("%s", ch);
            if(strcmp(ch, "y") == 0)
            {
                write();
            }
            printf("\n\t");
            printf("---------------------------�������˳�---------------------------");
            printf("\n\t");
            flag = 0;
        }
        else
        {
            printf("\n\t�޸�ָ����������룡\n\n");
        }
    }
    return 0;
}

void input_data(int i)    //��������ְԱ������Ϣ
{
    printf("\n\t��λ���ʣ�");    //�����λ����
    scanf("%f", &zggz[i].gwgz);

    printf("\n\tн�����ʣ�");    //����н������
    scanf("%f", &zggz[i].xjgz);

    printf("\n\tְ�������");    //����ְ�����
    scanf("%f", &zggz[i].subsidy);

    printf("\n\t��Ч���ʣ�");    //���뼨Ч����
    scanf("%f", &zggz[i].jxgz);

    zggz[i].yfgz = zggz[i].gwgz + zggz[i].xjgz 
            + zggz[i].subsidy + zggz[i].jxgz;

    grsds(i);    //�����������˰

    zggz[i].sfgz = zggz[i].yfgz - zggz[i].tax;
}

void show_data(int i)    //��ʾĳְԱ��Ϣ�ĺ���
{
    printf("\n\tְԱ���ţ�%s\n\tְԱ������%s\n\t��λ���ʣ�%.2f",
        zggz[i].number, zggz[i].name, zggz[i].gwgz);

    printf("\n\tн�����ʣ�%.2f\n\tְ�������%.2f\n\t��Ч���ʣ�%.2f",
        zggz[i].xjgz, zggz[i].subsidy, zggz[i].jxgz);

    printf("\n\tӦ�����ʣ�%.2f\n\t��������˰��%.2f\n\tʵ�����ʣ�%.2f\n",
        zggz[i].yfgz, zggz[i].tax, zggz[i].sfgz);
}

void read()    //�����ȡְ���������ݺ���
{
    FILE *fp = fopen("gx.dat", "rb");    //�����ļ�ָ��
    int i = 0;
    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n\t�ļ���ʧ�ܣ�\n");
        exit(-1);
    }

    /*
    for(i = 0; i < 100; i ++)    //��ȡ�ļ������ݲ��浽�ṹ������zggz��
    {
        int nRes = fscanf(fp, "%s %s %f %f %f %f %f %f %f",
                  zggz[i].number, zggz[i].name, &zggz[i].gwgz, 
                  &zggz[i].xjgz, &zggz[i].subsidy, &zggz[i].jxgz,
                  &zggz[i].yfgz, &zggz[i].tax, &zggz[i].sfgz);

        if (nRes == -1)    //�ж��Ƿ��ȡ���ļ�β��
        {
            n = i;    //��¼д�����ݵ�����
            fclose(fp);
            break;
        }
    }
    */
    while(!feof(fp))
    {
        fread(&zggz[i], sizeof(zggz), 1, fp);
        if(!feof(fp))
        {
            i += 1;
        }
    }
    n = i;

    fclose(fp);    //�ر��ļ�
    /*
    for (i = 0; i < n; i ++)    //����ṹ���������ݣ����ڼ�⣩
    {
        show_data(i);
        printf("\n\t");
        printf("-------------------------�ļ���ȡ��ϣ�-------------------------");
        printf("\n");
    }
    */
}

void write()    //���屣��ְ���������ݺ���
{
    FILE *fp = fopen("gz.dat","wb");
    int i;
    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n\t�ļ���ʧ�ܣ�\n");
        exit(1);
    }

    for (i = 0; i < n; i ++)    //������д��������ļ�
    {
        /*
        fprintf(fp, "%s %s %f %f %f %f %f %f %f \n",
                    zggz[i].number, zggz[i].name, zggz[i].gwgz, 
                    zggz[i].xjgz, zggz[i].subsidy, 
                    zggz[i].jxgz, zggz[i].yfgz, 
                    zggz[i].tax, zggz[i].sfgz);
        */
        fwrite(&zggz[i], sizeof(zggz), 1, fp);
    }
    fclose(fp);    //�ر��ļ�
    printf("\n\t");
    printf("-------------------------�ļ�������ϣ�-------------------------");
    printf("\n");
}

void find()    //�����ѯְ���������ݺ���
{
    char gonghao[10];
    char s[5];
    int i;
    int flag = 1;
    
    printf("\n\t");
    printf("------------------------------��ѯ------------------------------");
    while(flag)
    {
        printf("\n\t��������Ҫ��ѯ�Ĺ��ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n\t");
                printf("-----------------------����ѯ��ְ����ϢΪ-----------------------");

                show_data(i);

                flag = 0;
                printf("\n\t");
                printf("----------------------------��ѯ����----------------------------");
                break;
            }
        }
        if(flag == 1)
        {
            printf("\n\t�޴˹���ְԱ��Ϣ\n");
            printf("\n\t�Ƿ������ѯ���ǣ�y���������ַ�\n\t");
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

void list()    //�������ְ���������ݺ���
{
    int i;
    printf("\n\t");
    printf("------------------------���ְ����������------------------------");
    for(i = 0; i < n; i ++)
    {
        show_data(i);
    }
    printf("\n\t");
    printf("----------------------------�������----------------------------");
}

void modify()    //�����޸�ְ���������ݺ���
{
    char gonghao[10], s[10];
    int i, flag = 1;

    printf("\n\t");
    printf("------------------------------�޸�------------------------------");
    while(flag)
    {
        printf("\n\t��������Ҫ����¼�����ݵ�ְԱ���ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, zggz[i].number) == 0)
            {
                printf("\n\t��¼���ְԱ�������ݣ�\n");
                
                input_data(i);

                printf("\n\t");
                printf("----------------------------�޸Ľ���----------------------------");
                flag = 0;    //����ѭ������
                break;
            }
        }
        if(flag)
        {
            printf("\n\t�޴˹���ְ����Ϣ\n\t");

            printf("�Ƿ�����޸ģ��ǣ�y �������ַ�\n\t");
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

void del()    //����ɾ��ְ���������ݺ���
{
    char gonghao[10];
    char s[5];
    int i, j;
    int flag = 1;

    printf("\n\t");
    printf("------------------------------ɾ��------------------------------");
    printf("\n\t��������Ҫɾ����ְԱ���ţ�");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            printf("\n\t�Ƿ�ɾ����ְԱ��Ϣ���ǣ�y���������ַ�\n\t");
            scanf("%s", s);
            if(strcmp(s, "y") == 0)
            {
                for(j = i; j < n; j ++)
                {
                    zggz[j] = zggz[j+1];
                }
                n -= 1;    //��¼������
                flag = 0;
                printf("\n\t");
                printf("----------------------------ɾ���ɹ�----------------------------");
                break;
            }
            else
            {
                flag = 0;
                printf("\n\t");
                printf("----------------------------ɾ��ȡ��----------------------------");
                break;
            }
        }
    }
    if(flag)    //���Һ󲻴��ڹ���
    {
        printf("\n\t");
        printf("-----------------------�޴˹���ְԱ��Ϣ��-----------------------");
    }
}

void add()    //�������ְ���������ݺ���
{
    char s[10];
    int i;
    int flag = 1;    //����ѭ����
    int flag_1 = 0;  //�����Ƿ���������

    printf("\n\t");
    printf("------------------------------���------------------------------");
    printf("\n\t������ְ��������Ϣ��\n");
    while(flag)
    {
        printf("\n\tְԱ���ţ�");    //����ְԱ����
        scanf("%s", s);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(s, zggz[i].number) == 0)
                {
                    printf("\n\t��ְԱ�����Ѵ��ڣ�\n");
                    printf("\n\t�Ƿ��������룿�ǣ�y���������ַ�\n\t");
                    scanf("%s", s);
                    if(strcmp(s, "y") == 0)
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                    }
                    break;
                }
        }
        if(i == n)    //ְԱ�������ظ�����ʼ��ֵ
        {
            strcpy(zggz[n].number, s);
            flag = 0;
            flag_1 = 1;
        }
    }
    if(flag_1)
    {
        printf("\n\tְԱ������");    //����ְԱ����
        scanf("%s", zggz[n].name);

        input_data(n);

        printf("\n\t");
        printf("--------------------------����ְ����Ϣ--------------------------");

        show_data(n);

        n += 1;    //������+1
    }
    printf("\n\t");
    printf("--------------------------���ִ�н���--------------------------");
}

void grsds(int i)    //�������ְ����������˰����
{
    double count, tax;
    int flag = 1;
    count = zggz[i].yfgz;    //Ӧ������
    zggz[i].tax = 0;    //���ۼ���

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
            flag = 0;    //Ӧ��������ȡ��������˰����С��500ֹͣ
        }
        zggz[i].tax += tax;    //�ۼ�ÿ��ĸ�������˰
    }
}