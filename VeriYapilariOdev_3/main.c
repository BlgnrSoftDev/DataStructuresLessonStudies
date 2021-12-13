#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct ogrenci
{
    char* name;
    char* surname;
    char* age;
    long id;
    char* department;
    char* classs;

}OGRENCI;

int compare(void* param1, void* param2);
void printInstructions(void);
void process(int choice, LIST* list);
long convertToLong(char* id);
bool isValidDigit( char* number );
void printStudentInfo(long id_v2, LIST* pList);
void addStudent(LIST* pList);
void updateStudent(LIST* pList, long id);
void deleteStudent(LIST* pList, long id);
void initialize(OGRENCI* stu);
void printAllStudents(LIST* pList);

void main(void)
{
    int choice;
    int ch;
    LIST* list = createList(&compare);
    printf("(Enter Basiniz)");
    printf("\n\n OGRENCI YONETIM SISTEMNINE HOSGELDINIZ!!");
    while(true)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
            continue;
        printInstructions();
        choice = getchar() - 48;
        getchar();
        process(choice, list);
    }
}

int compare(void* param1, void* param2)
{
    long num1 = ((OGRENCI*)param1)->id;
    long num2 = ((OGRENCI*)param2)->id ;

    if((num1) > (num2))
        return 1;
    else if((num1) == (num2))
        return 0;
    else
    {
        return -1;
    }

}


void printInstructions()
{
    printf("\
           \n\n\rEger islem yapmak istiyorsaniz, \n\
           \r 1-) Yeni Ogrenci Ekleme \n\
           \r 2-) Guncel Ogrenci Islemleri \n\
           \r 3-) Cikis\n\
           \r 4-) Tum ogrencileri bagli sekilde goster\n\
           \rtuslayiniz. \n\r==>");
}

void process(int choice, LIST* pList)
{
    switch( choice )
    {
    case 1:
        addStudent(pList);
        break;
    case 3:
        exit(3);
        break;
    case 4:
        printAllStudents(pList);
        break;
    }

    if( choice == 2)
    {
        printf("\n(Enter basiniz)\n\n");
        long id_v2;
        char* id = (char*) calloc(9, sizeof(char));
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            continue;
        printf(" \nOncelikle Islem Yapmak Istediginiz Ogrencinin Numarasini Giriniz: ( 9 haneli )\n==>");
        fgets(id, 10, stdin);
        if( isValidDigit(id) )
        {
            id_v2 = convertToLong(id);
        }
        else
        {
            printf("\nGirdiginiz numara hatalidir!\n");
        }

        printStudentInfo(id_v2, pList);

        printf("\n\n\rEger ilgili ogrenci ile islem yapmak istiyorsaniz, \n\
               \r 1-) Ogrenciyi SIL \n\
               \r 2-) Ogrenci bilgilerini guncelle \n\
               \r 3-) GEC \n\n==>");

        while ((ch = getchar()) != '\n' && ch != EOF)
            continue;
        int decision = (getchar() - 48);
        getchar();
        if(decision == 1)
        {
            deleteStudent(pList, id_v2);
        }
        else if( decision == 2)
        {
            updateStudent(pList, id_v2);
        }
        else if( decision == 3)
        {
            printf("\n(Enter basiniz)\n");
        }

    }

}

void updateStudent(LIST* pList, long id)
{
    printf("\n\nGuncellemek istediginiz bilgileri girip, \
           \rdegismesini istemediginiz bilgileri '-' tek bir tane (eksi) isareti yaziniz. \n");
    char* temp;


    OGRENCI* keyValue = (OGRENCI*) malloc(sizeof(OGRENCI));
    keyValue->id = id;

    NODE* node = retrieveNode(pList, keyValue);
    OGRENCI* data = (OGRENCI*) node->data;

    temp = (char*) calloc(30, sizeof(char));
    printf(" \nOgrencinin adini giriniz :\n==>");
    fgets(temp, 31, stdin);
    if( !(temp[0] == '-') )
    {
        data->name = temp;
    }

    temp = (char*) calloc(30, sizeof(char));
    printf(" Ogrencinin soyadini giriniz :\n==>");
    fgets(temp, 31, stdin);
    if( !(temp[0] == '-') )
    {
        data->surname = temp;
    }

    temp = (char*) calloc(30, sizeof(char));
    printf(" Ogrencinin bolumunu giriniz :\n==>");
    fgets(temp, 31, stdin);
    if( !(temp[0] == '-') )
    {
        data->department = temp;
    }

    temp = (char*) calloc(30, sizeof(char));
    printf(" Ogrencinin sinifini giriniz :\n==>");
    fgets(temp, 31, stdin);
    if( !(temp[0] == '-') )
    {
        data->classs = temp;
    }

    temp = (char*) calloc(2, sizeof(char));
    printf(" Ogrencinin yasini giriniz :\n==>");
    fgets(temp, 3, stdin);
    if( !(temp[0] == '-') )
    {
        data->age = temp;
    }


    printf("\nogrenci guncellendi.\n");

}
void deleteStudent(LIST* pList, long id)
{

    OGRENCI* keyValue = (OGRENCI*) malloc(sizeof(OGRENCI));
    keyValue->id = id;

    if( removeNode(pList, keyValue) )
        printf("\nOgrenci basarili bir sekilde silindi.\n");
    else
        printf("\nOgrenci silinemedi.\n");
}

void initialize(OGRENCI* stu)
{
    stu->name = (char*)calloc(30, sizeof(char));
    stu->surname = (char*)calloc(30, sizeof(char));
    stu->age = (char*)calloc(30, sizeof(char));
    stu->id = 0;
    stu->department = (char*)calloc(30, sizeof(char));
    stu->classs = (char*)calloc(30, sizeof(char));
}
void addStudent(LIST* pList)
{
    OGRENCI* newStudent = (OGRENCI*) malloc(sizeof(OGRENCI));
    initialize(newStudent);

    if( newStudent )
    {
        long id = rand() % 100000000 + 100000000;
        newStudent->id = id;

        printf(" \nOgrencinin adini giriniz :\n==>");
        fgets(newStudent->name, 31, stdin);
        printf(" Ogrencinin soyadini giriniz :\n==>");
        fgets(newStudent->surname, 31, stdin);
        printf(" Ogrencinin bolumunu giriniz :\n==>");
        fgets(newStudent->department, 31, stdin);
        printf(" Ogrencinin sinifini giriniz :\n==>");
        fgets(newStudent->classs, 31, stdin);
        printf(" Ogrencinin yasini giriniz :\n==>");
        fgets(newStudent->age, 3, stdin);

        if( !addNode(pList, newStudent) )
        {
            printf("Ogrenci basarili bir sekilde eklendi.");
            printf("\t(Ogrenci numarasi : %ld)", id);

        }

        else
            printf("Ogrenci eklenemedi.");

    }
    else
        exit(6);

}

void printStudentInfo(long id_v2, LIST* pList)
{
    OGRENCI* keyValue = (OGRENCI*) malloc(sizeof(OGRENCI));
    keyValue->id = id_v2;

    NODE* student = retrieveNode(pList, keyValue);

    if( student  != NULL )
    {
        OGRENCI* info = (OGRENCI*) student->data;
        printf("\n\n------- OGRENCI RAPORU ------- \n\n\
               \r|ID: %ld\n\
               \r|AD: %s \n\
               \r|SOYAD: %s\n\
               \r|SINIF: %s \n\
               \r|YAS: %s \n\
               \r|BOLUM: %s \n\n\n\
                ", info->id, info->name, info->surname, info->classs, info->age, info->department);

    }
    else
    {
        printf("\rilgili numaraya sahip ogrenci yoktur.\n");
    }
}

bool isValidDigit( char* number )
{
    int n = 0;
    while( number[n] != '\n' )
    {
        if( isdigit(number[n]) )
        {
            n++;
        }
        else
            break;
    }

    if(n == 9)
        return true;

    return false;
}



long convertToLong(char* id)
{
    long number = 0;
    int step = 0;

    for(int i = (strlen(id)-1); i >= 0; i--)
    {
        number += ((int)pow(10.0, (double)step)) * (id[i] - 48);
        step++;
    }

    return number;

}


void printAllStudents(LIST* pList)
{
    NODE* traverser = pList->pHead;
    OGRENCI* temp;
    printf("\n Liste Ogrenci Numarasina Gore Siralidir...\n\n");
    while(traverser != NULL)
    {
        temp = (OGRENCI*)traverser->data;
        printf("\rAD: %s \n", temp->name);
        printf("\rSOYAD:  %s \n",temp->surname);
        printf("\rID: %d \n",temp->id);
        printf("_________\n\n");
        traverser = traverser->next;
    }


    printf("\n\n(Enter basiniz.)");

}
