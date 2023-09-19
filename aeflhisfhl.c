#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
void ReadDataFromFile(){
};
void WriteDataToFile(){
};
void booklist();
void addbook();
void removebook();
void issuedbook();
struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
}b;

struct student{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
}s;

FILE *fp;
int main() {
    int ch;
     ReadDataFromFile();
    
    while (1) {
        //system("COLOR F0");
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Book List\n");
        printf("2. Add Book\n");
        printf("3. Remove Book\n");
        printf("4. Issued Book\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);
        //Beep(700, 300);
        //Beep(600, 300);

        switch (ch) {
            case 1:
                booklist();
                break;

            case 2:
                addbook();
                break;

            case 3:
                removebook();
                break;

            case 4:
                issuedbook();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid Choice...\n");
        }
    }

    return 0;
}

void booklist() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("Library_Management_System.csv", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void addbook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);
    
    fp = fopen("Library_Management_System.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("Book Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void removebook() {
    int id, f = 0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("Library_Management_System.csv", "rb");
    ft = fopen("temp.csv", "wb"); // Use a temporary file for writing

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.");
    } else {
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("Library_Management_System.csv");
    rename("temp.csv", "Library_Management_System.csv"); // Rename the temporary file
}

void issuedbook() {
        char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    //Check if we have book of given id
    fp = fopen("Library_Management_System.csv", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.bookName, b.bookName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("Library_Management_System.csv", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}