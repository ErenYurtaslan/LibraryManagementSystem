#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book{
    int id;
    char title[60];
    char author[60];
    int is_borrowed;
    int student_id;
};

struct Library{
   struct Book books[MAX_BOOKS];
   int book_count;
};

void addBook(struct Library* lib, int id, const char* title, const char* author)
{
    if(lib->book_count<MAX_BOOKS){
        if(strlen(title)==0 ||strlen(author)==0){
            printf("Invalid input! Please enter a valid title and author!\n");
            return;
        }

    struct Book newBook;
    newBook.id=id;
    strcpy(newBook.title, title);
    strcpy(newBook.author, author);
    newBook.is_borrowed = 0;
    newBook.student_id = -1;

    //***************ÖNEMLÝ***************
    lib->books[lib->book_count++] = newBook;
    printf("Book added.\n");

    }else printf("Library is full, can not add book.\n");
}



void listAllBooks(struct Library* lib){
    if(lib->book_count == 0){printf("Library is empty."); return;}

    printf("ALL BOOKS\n");
    printf("%-5s %-25s %-25s %-15s\n", "ID","Title","Author","Status");
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
    for(int i=0; i<lib->book_count; i++){
        printf("%-5d %-25s %-25s %-15s\n", lib->books[i].id, lib->books[i].title,
               lib->books[i].author, lib->books[i].is_borrowed ? "Borrowed" : "Available");
    }
}


void search(struct Library* lib, int id){
    for(int i = 0; i<lib->book_count; i++){
        if(lib->books[i].id==id){
            printf("Book found!\n");
            printf("ID: %d\n", lib->books[i].id);
            printf("Title: %s\n", lib->books[i].title);
            printf("Author: %s\n", lib->books[i].author);
            printf("Status: %s\n", lib->books[i].is_borrowed ? "Borrowed" : "Available");
            printf("Student ID: %d\n", lib->books[i].student_id);
            return;
        }
    }
    printf("Book not found!\n");
}



void returnTheBook(struct Library* lib, int id)
{
     for(int i = 0; i<lib->book_count; i++){
        if(lib->books[i].id==id){
            if(lib->books[i].is_borrowed){
                lib->books[i].is_borrowed=0;
                lib->books[i].student_id=-1;
                printf("Book returned.\n");
            }

        else{
        printf("This book is already in the library!\n");
            }
        return;
        }

    }
    printf("Book not found!\n");
}



void borrowTheBook(struct Library* lib, int id, int student_id)
{
    for(int i = 0; i<lib->book_count; i++){
        if(lib->books[i].id==id){
            if(lib->books[i].is_borrowed){
                printf("This book is already borrowed.\n");
            }else{
                lib->books[i].is_borrowed = 1;
                lib->books[i].student_id = student_id;
                printf("The book with ID %d was borrowed by the student with ID %d.\n", id, student_id);
            }
            return;
        }
    }

    printf("Book ID not found!\n");
}

int main()
{

    struct Library lib;
    lib.book_count=0;
    int student_id, id;
    int choice;
    char title[60],author[60];

    do{
        printf("\n*+*+*+*+*+*+*+*+*+*+*+*+LIBRARY MANAGEMENT SYSTEM*+*+*+*+*+*+*+*+*+*+*+*+");
        printf("\n\n1.Add Book\n2.List All Books\n3.Search Book by ID\n4.Borrow Book\n5.Return Book\n0.Exit\nENTER YOUR CHOICE: ");
        scanf("%d", &choice);


        switch(choice){
            case 1:
                printf("Id: ");
                scanf("%d", &id);
                printf("Title: ");
                getchar();//clear the newline from previous scanf
                gets(title);
                printf("Author: ");
                gets(author);
                addBook(&lib, id, title, author);
                break;
            case 2:
                listAllBooks(&lib);
                break;
            case 3:
                printf("Enter ID of book: ");
                scanf("%d", &id);
                search(&lib, id);
                break;
            case 4:
                printf("Enter ID of book for borrow: ");
                scanf("%d", &id);
                printf("Enter ID of student: ");
                scanf("%d", &student_id);
                borrowTheBook(&lib, id, student_id);
                break;
            case 5:
                printf("Enter ID of book for return: ");
                scanf("%d", &id);
                returnTheBook(&lib, id);
                break;
            case 0:
                printf("Exit....\n");
            default:
                printf("Invalid choice, please try again!\n");
        }






    }while(choice!=0);




    return 0;
}
