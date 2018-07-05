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
     Jeff      18/07/04       0.1       adjust structure
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

struct Employee
{
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
int read();        //������ȡְ���������ݵĺ���
int write();       //��������ְ���������ݵĺ���
void find();       //������ѯְ���������ݵĺ���
void list();       //�������ְ���������ݵĺ���
void modify();     //�����޸�ְ���������ݵĺ���
void del();        //����ɾ��ְ���������ݵĺ���
void add();        //�������ְ���������ݵĺ���
void grsds(int i); //���������������˰�ĺ���


int main()
{
    char s[5], ch[5];
    int flag = 1;  //���ڿ���ѭ����

    system("cls");
    read();  //���ö�ȡ�ļ��ĺ���

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
            find();  //���ò�ѯ����
        }
        else if(strcmp(s ,"2") == 0)
        {
            modify();  //�����޸ĺ���
        }
        else if(strcmp(s ,"3") == 0)
        {
            if(n < 100)
            {
                add();  //С��100�����ݣ�������Ӻ���
            }
            else
            {
                printf("\n\t�����������ƣ�\n");

                printf("\n\tPress any key��");//��ʾ��һ��
                getch();
                system("cls");
            }
        }
        else if(strcmp(s ,"4") == 0)
        {
            del();  //����ɾ������
        }
        else if(strcmp(s ,"5") == 0)
        {
            write();  //���ñ��溯��
        }
        else if(strcmp(s ,"6") == 0)
        {
            list();  //�����������
        }
        else
        {
            printf("\n\t�Ƿ���Ҫ�����������ݣ�(y/n)\n\t");
            scanf("%s", ch);

            if(strcmp(ch, "y") == 0)
            {
                write();  //�˳�ʱ��ѡ���Ƿ���ú�����������
            }

            printf("\n\t�������˳���\n\t");
            flag = 0;  //�˳�ѭ��
        }
    }
    return 0;
}

void input_data(int i)  //��������ְԱ������Ϣ
{
    printf("\n\t��λ���ʣ�");
    scanf("%f", &zggz[i].gwgz);  //�����λ����

    printf("\n\tн�����ʣ�");
    scanf("%f", &zggz[i].xjgz);  //����н������

    printf("\n\tְ�������");
    scanf("%f", &zggz[i].subsidy);  //����ְ�����

    printf("\n\t��Ч���ʣ�");
    scanf("%f", &zggz[i].jxgz);  //���뼨Ч����

    //����Ӧ������
    zggz[i].yfgz = zggz[i].gwgz + zggz[i].xjgz 
            + zggz[i].subsidy + zggz[i].jxgz;

    grsds(i);  //�����������˰

    //����ʵ������
    zggz[i].sfgz = zggz[i].yfgz - zggz[i].tax;
}

void show_data(int i)  //��ʾĳְԱ��Ϣ�ĺ���
{
    printf("\n\t%s %s %.2f",
        zggz[i].number, zggz[i].name, zggz[i].gwgz);

    printf(" %.2f %.2f %.2f",
        zggz[i].xjgz, zggz[i].subsidy, zggz[i].jxgz);

    printf(" %.2f %.2f %.2f\n",
        zggz[i].yfgz, zggz[i].tax, zggz[i].sfgz);
}

int read()  //��ȡְ���������ݺ���
{
    //ֻ����һ���������ļ���ֻ���������
    FILE *fp = fopen("gx.dat", "rb");
    int i = 0;
    //int i, nRes;  //i ���ڿ���ѭ���壬nRes�����ж��ļ���ȡ�Ƿ���ȷ

    if(fp == NULL)    //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n\t�ļ���ʧ�ܣ�\n\t");
        printf("\n\tPress any key...");
        getch();
        system("cls");
        return 0;  //�ļ���ʧ�ܣ�ֱ�ӻص�������
    }

    /*
    for(i = 0; i < 100; i ++)    //��ȡ�ļ������ݲ��浽�ṹ������zggz��
    {
        nRes = fscanf(fp, "%s %s %f %f %f %f %f %f %f",
                            zggz[i].number, zggz[i].name, &zggz[i].gwgz, 
                            &zggz[i].xjgz, &zggz[i].subsidy, &zggz[i].jxgz,
                            &zggz[i].yfgz, &zggz[i].tax, &zggz[i].sfgz);

        if (nRes == -1)    //�ļ���ȡ����
        {
            n = i;    //��¼д�����ݵ�����
            break;
        }
    }
    */

    for(i = 0; i < 100; i ++)
    {
        if(fread(&zggz[i], sizeof(zggz[i]), 1, fp)==0)//�ж��Ƿ�����ļ�β
        {
            break;
        }
    }
    n = i;

    fclose(fp);  //�ر��ļ�
    printf("\n\t��д��%d������\n", n);

    printf("\n\tPress any key...");
    getch();
    system("cls");
    return 0;
}

int write()  //����ְ���������ݺ���
{  
    //ֻд�򿪻��߽���һ���������ļ���ֻ����д����
    FILE *fp = fopen("gx.dat","wb");
    int i;

    if(n <= 0)
    {
        printf("\n\tְԱ����Ϊ��\n\t");
        getch();
        system("cls");
        return 0;  //����Ϊ�գ����ܽ��д洢
    }
    else if(fp == NULL)  //�򿪵�ǰĿ¼���ļ�
    {
        printf("\n\t�ļ���ʧ�ܣ�\n\t");
        getch();
        system("cls");
        return 0;  //�ļ���ʧ�ܣ�ֱ�ӻص�������
    }

    /*
    for (i = 0; i < n; i ++)    //������д��������ļ�
    {
        fprintf(fp, "%s %s %f %f %f %f %f %f %f \n",
                    zggz[i].number, zggz[i].name, zggz[i].gwgz, 
                    zggz[i].xjgz, zggz[i].subsidy, 
                    zggz[i].jxgz, zggz[i].yfgz, 
                    zggz[i].tax, zggz[i].sfgz);
    }
    */

    for (i = 0; i < n; i ++)
    {
        fwrite(&(zggz[i]), sizeof(zggz[i]), 1, fp); //������д��������ļ�
    }
 
    fclose(fp);  //�ر��ļ�

    printf("\n\t�ļ�������ϣ�\n");

    printf("\n\tPress any key...");//��ʾ��һ��
    getch();
    system("cls");
    return 0;
}

void find()  //��ѯְ���������ݺ���
{
    char gonghao[10];
    int i;
    
    printf("\n\t");
    printf("------------------------------��ѯ------------------------------");

    printf("\n\t��������Ҫ��ѯ�Ĺ��ţ�");
    scanf("%s", gonghao);  //����Ҫ��ѯ�Ĺ���

    for(i = 0; i < n; i ++)
    {
        //ѭ�������Ƿ���ڸù���
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            printf("\n\t-----------------------");
            printf("����ѯ��ְ����ϢΪ");
            printf("-----------------------");

            show_data(i);  //��ʾְԱ������Ϣ

            printf("\n\t----------------------------");
            printf("��ѯ����");
            printf("-----------------------");
            break;  //�ҵ������Ӧ������Ϣ���˳�ѭ��
        }
    }
    if(i == n)  //���ṹ��������Ҫ��ѯ�Ĺ���ʱ��ѭ��n�κ�i = n
    {
        printf("\n\t�޴˹���ְԱ��Ϣ��");
    }

    printf("\n\tPress any key...");//��ʾ��һ��
    getch();
    system("cls");
}

void list()  //���ְ���������ݺ���
{
    int i;
    printf("\n\t------------------------");
    printf("���ְ����������");
    printf("-----------------------");
    for(i = 0; i < n; i ++)
    {
        if(((i % 10) == 0) && (i != 0))
        {
            printf("\n\t��һҳ");
            getch();
            system("cls");
            continue;
        }
        else
        {
            show_data(i);  //ͨ��ѭ����ʾ����ְԱ������Ϣ
        }
    }
    printf("\n\t----------------------------");
    printf("�������");
    printf("-----------------------");

    printf("\n\tPress any key...");//��ʾ��һ��
    getch();
    system("cls");
}

void modify()  //�޸�ְ���������ݺ���
{
    char gonghao[10];  //�洢Ҫ�޸�ְԱ�Ĺ���
    int i;

    printf("\n\t");
    printf("------------------------------�޸�------------------------------");

    printf("\n\t��������Ҫ����¼�����ݵ�ְԱ���ţ�");
    scanf("%s", gonghao);  //����Ҫ�޸�ְԱ�Ĺ���

    for(i = 0; i < n; i ++)
    {
        //ѭ�����ҹ��ţ�������������ú����޸�ְԱ������Ϣ
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            printf("\n\t��¼���ְԱ�������ݣ�\n");
                
            input_data(i);  //�������빤�����ݵĺ���

            printf("\n\t----------------------------");
            printf("�޸Ľ���");
            printf("-----------------------");

            break;
        }
    }
    if(i == n)
    {
        printf("\n\t-----------------------");
        printf("�޴˹���ְԱ��Ϣ��");
        printf("-----------------------");
    }

    printf("\n\tPress any key...");//��ʾ��һ��
    getch();
    system("cls");
}

void del()  //ɾ��ְ���������ݺ���
{
    char gonghao[10];  //��¼ְԱ����
    char s[5];  //��¼�û�ָ��

    int i, j;  //����ѭ�������

    int flag = 0;  //��flag = 0ʱ�޴˹���

    printf("\n\t");
    printf("------------------------------ɾ��------------------------------");
    printf("\n\t��������Ҫɾ����ְԱ���ţ�");
    scanf("%s", gonghao);  //����Ҫɾ����ְԱ����

    for(i = 0; i < n; i ++)  //ѭ�����ҹ���
    {
        if(strcmp(gonghao, zggz[i].number) == 0)
        {
            flag = 1;  //��ѯ��Ա����Ϣ����flag = 1��ֹ������޹�����Ϣ��

            printf("\n\t�Ƿ�ɾ����ְԱ��Ϣ��(y/n)\n\t");
            scanf("%s", s);  //����ָ��

            if(strcmp(s, "y") == 0)
            {
                for(j = i; j < n; j ++)
                {
                    zggz[j] = zggz[j+1];  //����������ǰ��
                }

                n -= 1;  //�ܹ�����������-1

                printf("\n\tɾ���ɹ���");
                break;
            }
            else
            {
                flag = 1;
                printf("\n\tɾ����ȡ����");
                break;
            }
        }
    }
    if(flag == 0)  //���Һ󲻴��ڹ���
    {
        printf("\n\t�޴˹���ְԱ��Ϣ��");
    }

    printf("\n\tPress any key...");//��ʾ��һ��
    getch();
    system("cls");
}

void add()  //���ְ���������ݺ���
{
    char s[10];  //��¼Ҫ���ְԱ�Ĺ���
    int i;
    int flag = 1;  //����ѭ����
    int flag_1 = 0;  //�����Ƿ���������

    printf("\n\t");
    printf("------------------------------���------------------------------");
    printf("\n\t������ְ��������Ϣ��\n");

    while(flag)
    {
        printf("\n\tְԱ���ţ�");
        scanf("%s", s);  //����ְԱ����

        for(i = 0; i < n; i ++)
        {
            if(strcmp(s, zggz[i].number) == 0)  //�жϹ����Ƿ��Ѵ���
            {
                printf("\n\t��ְԱ�����Ѵ��ڣ�\n");
                printf("\n\t�Ƿ��������룿(y/n)\n\t");
                scanf("%s", s);  //����ָ��

                if(strcmp(s, "y") == 0)
                {
                    flag = 1;  //ͬ�����������¹��������ְԱ������Ϣ
                }
                else
                {
                    flag = 0;  //��ͬ���������룬�˻����˵�
                }
                break;  //�˳�ѭ��
            }
        }
        if(i == n)  //ְԱ�������ظ�
        {
            flag = 0;  //�˳�whileѭ��
            flag_1 = 1;  //ȷ�����ְԱ��Ϣ
        }
    }
    if(flag_1) //��flag_1����1ʱִ��
    {
        strcpy(zggz[n].number, s);  //����ְԱ���Ÿ�ֵ

        printf("\n\tְԱ������");
        scanf("%s", zggz[n].name);  //����ְԱ����

        input_data(n);  //����ְԱ������Ϣ

        printf("\n\t--------------------------");
        printf("����ְ����Ϣ");
        printf("-----------------------");

        show_data(n);  //���ְԱ������Ϣ

        n += 1;  //�ܹ�����������+1
    }

    printf("\n\t");
    printf("--------------------------���ִ�н���--------------------------");
    
    printf("\n\tPress any key...");//��ʾ��һ��
    getch();
    system("cls");
}

void grsds(int i)  //����ְ����������˰����
{
    double count, tax;  //�洢Ӧ�����ʺ�ÿ���ֵ�˰
    int flag = 1;  //����ѭ����
    count = zggz[i].yfgz;  //Ӧ������
    zggz[i].tax = 0;  //���ۼ���

    while(flag)  //��������������ѭ��
    {
        if(count > 100000)  //����100000Ԫ�Ĳ���
        {
            tax = (count - 100000) * 0.45;
            count = 100000;
        }
        else if(count > 80000)  //����80000��100000Ԫ�Ĳ���
        {
            tax = (count - 80000) * 0.4;
            count = 80000;
        }
        else if(count > 60000)  //����60000��80000Ԫ�Ĳ���
        {
            tax = (count - 60000) * 0.35;
            count = 60000;
        }
        else if(count > 40000)  //����40000��60000Ԫ�Ĳ���
        {
            tax = (count - 40000) * 0.3;
            count = 40000;
        }
        else if(count > 20000)  //����20000��40000Ԫ�Ĳ���
        {
            tax = (count - 20000) * 0.25;
            count = 20000;
        }
        else if(count > 5000)  //����5000��20000Ԫ�Ĳ���
        {
            tax = (count - 5000) * 0.2;
            count = 5000;
        }
        else if(count > 2000)  //����2000��5000Ԫ�Ĳ���
        {
            tax = (count - 2000) * 0.15;
            count = 2000;
        }
        else if(count > 500)  //����500��2000Ԫ�Ĳ���
        {
            tax = (count - 500) * 0.1;
            count = 500;
        }
        else  //������500Ԫ�Ĳ���
        {
            tax = count * 0.05;
            flag = 0;  //Ӧ��������ȡ��������˰����С��500ֹͣ
        }
        zggz[i].tax += tax;  //�ۼ�ÿ��ĸ�������˰
    }
}