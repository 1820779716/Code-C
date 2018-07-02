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
    char number[10];    //ְ������
    char name[10];      //ְ������
    float gwgz;         //��λ����
    float xjgz;         //н������
    float subsidy;      //ְ�����
    float jxgz;         //��Ч����
    float yfgz;         //Ӧ������
    float tax;          //��������˰
    float sfgz;         //ʵ������
    struct Employee *prior, *next;//����ǰ��ָ�롢���ָ��
}zggz;

zggz *head, *tail;

int n = 0;  //��¼ְ������

void show_data(zggz *p);   //������ʾְԱ�������ݵĺ���
void read();        //������ȡְ���������ݵĺ���
void write();       //��������ְ���������ݵĺ���
void find();        //������ѯְ���������ݵĺ���
void list();        //�������ְ���������ݵĺ���
void modify();      //�����޸�ְ���������ݵĺ���
void del();         //����ɾ��ְ���������ݵĺ���
void add();         //�������ְ���������ݵĺ���
void grsds(zggz *p);  //���������������˰�ĺ���

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


//��ʾĳְԱ��Ϣ�ĺ�������ɣ�
void show_data(zggz *p)    
{
    printf("\n\tְԱ���ţ�%s\n\tְԱ������%s\n\t��λ���ʣ�%.2f",
        p->number, p->name, p->gwgz);

    printf("\n\tн�����ʣ�%.2f\n\tְ�������%.2f\n\t��Ч���ʣ�%.2f",
        p->xjgz, p->subsidy, p->jxgz);

    printf("\n\tӦ�����ʣ�%.2f\n\t��������˰��%.2f\n\tʵ�����ʣ�%.2f\n",
        p->yfgz, p->tax, p->sfgz);
}

//��ȡ�ļ���ְ����Ϣ�������ƣ�β�����Ƕ�����һ���ռ䣩
void read()    //�����ȡְ���������ݺ���
{
    zggz *p;
    int i, nRes;
    FILE *fp = fopen("gx.dat", "rb");//�����ļ�ָ��

    head = (zggz *)malloc(sizeof(zggz));//��ʼ������
    head->prior = head;
    head->next = head;
    p = head;

    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n\t�ļ���ʧ�ܣ�\n");
        exit(-1);
    }
    
    for(i = 0; i < 100; i ++)
    {
        nRes = fscanf(fp, "%s %s %f %f %f %f %f %f %f",
                  p->number, p->name, &(p->gwgz), 
                  &(p->xjgz), &(p->subsidy), &(p->jxgz),
                  &(p->yfgz), &(p->tax), &(p->sfgz));

        if (nRes == -1)    //�ж��Ƿ��ȡ���ļ�β��
        {
            n = i;    //��¼д�����ݵ�����
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

//����ְ����Ϣ���ļ�
void write()
{
    FILE *fp = fopen("gz.dat","wb");
    int i;
    zggz *p = head;

    if((fp == NULL))    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n\t�ļ���ʧ�ܣ�\n");
        exit(1);
    }
    
    for (i = 0; i < n; i ++)    //������д��������ļ�
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
    fclose(fp);    //�ر��ļ�
    printf("\n\t");
    printf("-------------------------�ļ�������ϣ�-------------------------");
    printf("\n");
}

//��ѯְ��������Ϣ
void find()
{
    char gonghao[10];
    char s[5];
    int i;
    zggz *p = head;
    int flag = 1;
    
    printf("\n\t");
    printf("------------------------------��ѯ------------------------------");
    while(flag)
    {
        printf("\n\t��������Ҫ��ѯ�Ĺ��ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, p->number) == 0)
            {
                printf("\n\t");
                printf("-----------------------����ѯ��ְ����ϢΪ-----------------------");

                show_data(p);

                flag = 0;
                printf("\n\t");
                printf("----------------------------��ѯ����----------------------------");
                break;
            }
            p = p->next;
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

//�������ְ��������Ϣ
void list()
{
    int i;
    zggz *p = head;
    printf("\n\t");
    printf("------------------------���ְ����������------------------------");
    for(i = 0; i < n; i ++)
    {
        show_data(p);
        p = p->next;
    }
    printf("\n\t");
    printf("----------------------------�������----------------------------");
}

//�޸�ְ��������Ϣ��δ��ɣ�
void modify()    
{
    char gonghao[10], s[10];
    int i, flag = 1;
    zggz *p = head;
    printf("\n\t");
    printf("------------------------------�޸�------------------------------");
    while(flag)
    {
        printf("\n\t��������Ҫ����¼�����ݵ�ְԱ���ţ�");
        scanf("%s", gonghao);
        for(i = 0; i < n; i ++)
        {
            if(strcmp(gonghao, p->number) == 0)
            {
                printf("\n\t��¼���ְԱ�������ݣ�\n");
                
                //input_data(p);
                printf("\n\t��λ���ʣ�");    //�����λ����
                scanf("%f", p->gwgz);

                printf("\n\tн�����ʣ�");    //����н������
                scanf("%f", p->xjgz);

                printf("\n\tְ�������");    //����ְ�����
                scanf("%f", p->subsidy);

                printf("\n\t��Ч���ʣ�");    //���뼨Ч����
                scanf("%f", p->jxgz);

                p->yfgz = p->gwgz + p->xjgz 
                        + p->subsidy + p->jxgz;

                grsds(p);    //�����������˰

                p->sfgz = p->yfgz - p->tax;
                printf("\n\t");
                printf("----------------------------�޸Ľ���----------------------------");
                flag = 0;    //����ѭ������
                break;
            }
            p = p->next;
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

//ɾ��ְ����Ϣ��δ��ɣ�
void del()
{
    char gonghao[10];
    char s[5];
    int i, j;
    int flag = 1;
    zggz *p = head;

    printf("\n\t");
    printf("------------------------------ɾ��------------------------------");
    printf("\n\t��������Ҫɾ����ְԱ���ţ�");
    scanf("%s", gonghao);
    for(i = 0; i < n; i ++)
    {
        if(strcmp(gonghao, p->number) == 0)
        {
            printf("\n\t�Ƿ�ɾ����ְԱ��Ϣ���ǣ�y���������ַ�\n\t");
            scanf("%s", s);
            if(strcmp(s, "y") == 0)
            {
                for(j = i; j < n; j ++)
                {
                    p = p->next;
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

//���ְ��������Ϣ�������ƣ��޷��жϹ����Ƿ��ظ���
void add()
{
    zggz *p;
    p = tail;

    printf("\n\t");
    printf("------------------------------���------------------------------");
    printf("\n\t������ְ��������Ϣ��\n");
    printf("\n\tְ�����ţ�");
    scanf("%s", p->number);

    printf("\n\tְ��������");
    scanf("%s", p->name);

    printf("\n\t��λ���ʣ�");    //�����λ����
    scanf("%f", &(p->gwgz));
    
    printf("\n\tн�����ʣ�");    //����н������
    scanf("%f", &(p->xjgz));
    
    printf("\n\tְ�������");    //����ְ�����
    scanf("%f", &(p->subsidy));
    
    printf("\n\t��Ч���ʣ�");    //���뼨Ч����
    scanf("%f", &(p->jxgz));
    
    p->yfgz = p->gwgz + p->xjgz 
        + p->subsidy + p->jxgz;
    
    grsds(p);    //�����������˰
    
    p->sfgz = p->yfgz - p->tax;
    printf("\n\t");
    printf("--------------------------����ְ����Ϣ--------------------------");

    show_data(p);

    tail = (zggz *)malloc(sizeof(zggz));
    p->next = tail;
    tail->prior = p;
    tail->next = head;
    head->prior = tail;
    n += 1;    //��������+1

    printf("\n\t");
    printf("--------------------------���ִ�н���--------------------------");
}

//���������˰
void grsds(zggz *p)
{
    double count, tax;
    int flag = 1;
    count = p->yfgz;    //Ӧ������
    p->tax = 0;    //���ۼ���
    
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
        p->tax += tax;    //�ۼ�ÿ��ĸ�������˰
    }
}