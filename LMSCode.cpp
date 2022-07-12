#include <iostream>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <ostream>
#include <windows.h>
using namespace std;
COORD coord = {0, 0};
const int bookNumberLength = 6;
const int bookNameLength = 50;
const int authorNameLength = 20;
const int studentAdmissionNumberLength = 6;
const int studentNameLength = 20;
//capitalizing letter here
char filter(char &a)
{
    if(int(a)>='a'&&int(a)<='z')
    {
        a='A'+a-'a';
    }
    return a;
}
//go at specific location on screen
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//taking input into char array
void gets(char s[], int m)
{
    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF && i < m-1)
    {
        ch=filter(ch);
        s[i] = ch;
        ++i;
    }
    s[i] = '\0';
    fflush(stdin);
    return;
}
//color
void Color(int P)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, P);;
}
//output char array
void puts(char s[])
{
    int i=0;
    while(s[i]!='\0')
    {
        cout<<s[i];
        i++;
    }
}
//creating book class here
class book
{
    char bookNumber[bookNumberLength]; // bookno.
    char bookName[bookNameLength];	   // bookname
    char authorName[authorNameLength]; // authorname
public:
    //creating new book
    void createbook()
    {
        cout << "\nNEW BOOK ENTRY GOING ON...\n";
        cout << "\nENTER BOOK NUMBER : ";
        fflush(stdin);
        gets(bookNumber,bookNumberLength);
        cout << "\nENTER BOOK NAME : ";
        fflush(stdin);
        gets(bookName, bookNameLength);
        cout << "\nENTER AUTHOR NAME : ";
        fflush(stdin);
        gets(authorName, authorNameLength);
        Color(2);
        cout << "\n\n\nBOOK CREATED SUCCESSFULLY.";
        Color(7);
    }
    //showing book
    void showbook()
    {
        cout << "\nBOOK NUMBER : " << bookNumber;
        cout << "\nBOOK NAME : ";
        puts(bookName);
        cout << "\nBOOK AUTHOR NAME : ";
        puts(authorName);
    }
    //modifying book
    void modifybook()
    {
        cout << "\nBOOK NUMBER : " << bookNumber;
        cout << "\nMODIFY BOOK NAME : ";
        fflush(stdin);
        gets(bookName, bookNameLength);
        cout << "\nMODIFY AUTHOR'S NAME : ";
        fflush(stdin);
        gets(authorName, authorNameLength);
    }
    char *returnBookNUmber()
    {
        return bookNumber;
    }
    void report()
    {
        Color(6);
        cout << bookNumber << setw(90) << bookName << setw(80) << authorName << endl;
        Color(7);
    }
};
// class ends here
//creating student class
class student
{
    char admissionNumber[studentAdmissionNumberLength];
    char name[studentNameLength];
    char studentBookNumber[bookNumberLength];
    int token;
public:
    //creating new student
    void createstudent()
    {
        system("cls");
        cout << "\n\nNEW STUDENT ENTRY IS GOING ...";
        cout << "\n\nENTER THE ADMISSION NUMBER : ";
        fflush(stdin);
        gets(admissionNumber,studentAdmissionNumberLength);
        cout <<"\n\nENTER THE STUDENT NAME : ";
        fflush(stdin);
        gets(name, studentNameLength);
        token = 0;
        studentBookNumber[0] = '\0';
        Color(2);
        cout <<"\n\nSTUDENT RECORD CREATED SUCCESSFULLY.";
        Color(7);
    }
    //showing student
    void showstudent()
    {
        cout << "\nADMISSION NUMBER : " << admissionNumber;
        cout << "\nSTUDENT NAME : ";
        puts(name);
        cout << "\nNUMBER OF BOOK ISSUED : " << token;
        if (token == 1)
        {
            cout << "\nBOOK NUMBER : " << studentBookNumber;
        }
    }
    //modifying student
    void modifystudent()
    {
        cout << "\nADMISSION NUMBER  : " << admissionNumber;
        cout << "\nMODIFY STUDENT NAME : ";
        fflush(stdin);
        gets(name, studentNameLength);
    }
    char *returnAdmissionNumber()
    {
        return admissionNumber;
    }
    char *returnStudentBookNumber()
    {
        return studentBookNumber;
    }
    int returnToken()
    {
        return token;
    }
    void addtoken()
    {
        token = 1;
    }
    void resettoken()
    {
        token = 0;
    }
    void getstudentBookNumber(char t[])
    {
        strcpy(studentBookNumber, t);
    }
    void report()
    {
        Color(6);
        cout << "\t" << admissionNumber << setw(90) << name << setw(80) << token << endl;
        Color(7);
    }
};
fstream fp, fp1;
book bk;
student st;

void writebook()
{
    char ch;
    fp.open("book.txt", ios::out | ios::app); // write and append data
    do
    {
        system("cls");
        bk.createbook();
        fp.write((char *)&bk, sizeof(book)); // size of class
        Color(3);
        cout << "\n\nDO YOU WANT TO ADD MORE RECORD?(Y/N?) ";
        Color(7);
        cin >> ch;
    }
    while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writestudent()
{
    char ch;
    fp.open("student.txt", ios::out | ios::app); // write and append data
    do
    {
        system("cls");
        st.createstudent();
        fp.write((char *)&st, sizeof(student)); // size of class
        Color(3);
        cout << "\n\nDO YOU WANT TO ADD MORE RECORD?(Y/N?) ";
        Color(7);
        cin >> ch;
    }
    while (ch == 'y' || ch == 'Y');
    fp.close();
}
void displayspb(char n[])
{
    cout << "\nBOOK DETAILS\n";
    int flag = 0;				  // book not found
    fp.open("book.txt", ios::in); // read data
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmp(bk.returnBookNUmber(), n) == 0)
        {
            bk.showbook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) // book not found
    {
        Color(4);
        cout << "\n\nBOOK DOES NOT EXIST.";
        Color(7);
    }
    getch();
}
void displaysps(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;					 // student not found
    fp.open("student.txt", ios::in); // read data
    while (fp.read((char *)&st, sizeof(student)))
    {
        if (strcmp(st.returnAdmissionNumber(), n) == 0) // not case sensitive
        {
            st.showstudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) // student not found
    {
        Color(4);
        cout << "\n\nSTUDENT DOES NOT EXIST.";
        Color(7);
    }
    getch();
}
void modifybook()
{
    char n[bookNumberLength];
    int found = 0;
    system("cls");
    cout << "\n\nMODIFY BOOK RECORD.";
    cout << "\n\nENTER THE BOOK NUMBER : ";
    fflush(stdin);
    gets(n,bookNumberLength);
    fp.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0)
    {
        if (strcmp(bk.returnBookNUmber(), n) == 0)
        {
            bk.showbook();
            cout << "\nENTER THE NEW DETAILS BOOK ";
            bk.modifybook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur); // back from current position
            fp.write((char *)&bk, sizeof(book));
            Color(2);
            cout << "\n\nRECORD UPDATED";
            Color(7);
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        Color(4);
        cout << "\n\nRECORD NOT FOUND.";
        Color(7);
    }
    getch(); // press key to get out
}
void modifystudent()
{
    char n[studentAdmissionNumberLength];
    int found = 0; // seach book of given data
    system("cls");
    cout << "\n\nMODIFY STUDENT RECORD.";
    cout << "\n\nEnter the Admission Number : ";
    fflush(stdin);
    gets(n,studentAdmissionNumberLength);
    fp.open("student.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.returnAdmissionNumber(), n) == 0)
        {
            st.showstudent();
            cout << "\nENTER THE NEW DETAILS OF STUDENT";
            st.modifystudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur); // back from current position
            fp.write((char *)&st, sizeof(student));
            Color(2);
            cout << "\n\nRECORD UPDATED.";
            Color(7);
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        Color(4);
        cout << "\n\nRECORD NOT FOUND.";
        Color(7);
    }
    getch(); // press key to get out
}

void deletestudent()
{
    char n[studentAdmissionNumberLength];
    int flag = 0;
    system("cls");
    cout << "\n\n\n\tDELETE STUDENT.";
    cout << "\n\nENTER THE ADMISSION NUMBER : ";
    fflush(stdin);
    gets(n,studentAdmissionNumberLength);
    fp.open("student.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if (strcmp(st.returnAdmissionNumber(), n) != 0)
        {
            fp2.write((char *)&st, sizeof(student));
        }
        else
        {
            flag = 1; // student found
        }
    }
    fp2.close();
    fp.close();
    remove("student.txt");
    rename("temp.txt", "student.txt"); // data after deletion moved to temp
    if (flag == 1)
    {
        Color(2);
        cout << "\n\n\tRECORD DELETED SUCCESSFULLY.";
        Color(7);
    }
    else
    {
        Color(4);
        cout << "\n\nRECORD NOT FOUND.";
        Color(7);
    }
    getch();
}
void deletebook()
{
    char n[bookNumberLength]; // book no.
    int flag = 0;
    system("cls");
    cout << "\n\n\n\tDELETE BOOK.";
    cout << "\n\nENTER THE BOOK NUMBER : ";
    fflush(stdin);
    gets(n,bookNumberLength);
    fp.open("book.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out); // temp having data else than that to be deleted
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmp(bk.returnBookNUmber(), n) != 0)
        {
            fp2.write((char *)&bk, sizeof(book));
        }
        else
        {
            flag = 1; // student found
        }
    }
    fp2.close();
    fp.close();
    remove("book.txt");
    rename("Temp.txt", "book.txt"); // data after deletion moved to temp
    if (flag == 1)
    {
        Color(2);
        cout << "\n\n\tRECORD DELETED SUCCESSFULLY.";
        Color(7);
    }
    else
    {
        Color(4);
        cout << "\n\nRECORD NOT FOUND.";
        Color(7);
    }
    getch();
}
void displayalls()
{
    system("cls");
    fp.open("student.txt", ios::in); // read mode
    if (!fp)
    {
        Color(4);
        cout << "FILE COULD NOT BE OPEN.";
        Color(7);
        getch();
        return; // press any key and return
    }

    cout << "\n\n";
    gotoxy(92,2);
    Color(6);
    cout<<"STUDENT LIST\n\n";
    cout << "==================================================================================================================================================================================================================\n";
    cout << "\tADMISSION NUMBER" << setw(80) << "NAME" << setw(80) << "BOOK ISSUED\n";
    cout << "==================================================================================================================================================================================================================\n";
    Color(7);
    while (fp.read((char *)&st, sizeof(student)))
    {
        st.report();
    }
    fp.close();
    getch();
}
void displayallb()
{
    system("cls");
    fp.open("book.txt", ios::in); // read mode
    if (!fp)
    {
        Color(4);
        cout << "FILE COULD NOT BE OPEN.";
        Color(7);
        getch();
        return; // press any key and return
    }
    cout << "\n\n";
    gotoxy(87,2);
    Color(6);
    cout<<"Book List\n\n";
    cout << "==================================================================================================================================================================================================================\n";
    cout << "\tBOOK NUMBER" << setw(80) << "BOOK NAME" << setw(80) << "BOOK AUTHOR\n";
    cout << "==================================================================================================================================================================================================================\n";
    Color(7);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    getch();
}
void bookissue()
{
    char sn[studentAdmissionNumberLength], bn[bookNumberLength];
    int found = 0, flag = 0;
    system("cls");
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tENTER ADMISSION NUMBER : ";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.returnAdmissionNumber(), sn) == 0) // compare admsn no.
        {
            found = 1;
            if (st.returnToken() == 0) // if book not issued
            {
                cout << "\n\n\tENTER THE BOOK NUMBER : ";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmp(bk.returnBookNUmber(), bn) == 0) // compare book no.
                    {
                        flag = 1;
                        st.addtoken();
                        st.getstudentBookNumber(bk.returnBookNUmber()); // pass book no.
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        Color(2);
                        cout << "\n\n\tBOOK ISSUED SUCCESSFULLY.\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of Rs 100 Per Day";
                        Color(7);
                    }
                }
                if (flag == 0)
                {
                    Color(4);
                    cout << "BOOK NUMBER DOES NOT EXISTS.";
                    Color(7);
                }
            }

            else
            {
                Color(4);
                cout << "YOU HAVE NOT RETURNED THE LAST BOOK.";
                Color(7);
            }
        }
    }
    if (found == 0)
    {
        Color(4);
        cout << "STUDENT RECORD NOT EXISTS.";
        Color(7);
    }
    getch();
    fp.close();
    fp1.close();
}

void bookdeposit()
{
    char sn[studentAdmissionNumberLength], bn[bookNumberLength];
    int found = 0, flag = 0, day, fine;
    system("cls");
    cout << "\n\nBOOK DEPOSIT.";
    cout << "\n\n\tENTER ADMISSION NUMBER OF STUDENT : ";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.returnAdmissionNumber(), sn) == 0) // compare admsn no.
        {
            found = 1;
            if (st.returnToken() == 1) // if book issued
            {
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmp(bk.returnBookNUmber(), st.returnStudentBookNumber()) == 0)
                    {
                        flag = 1;
                        bk.showbook();
                        cout << "\n\nBOOK DEPOSITED IN NUMBER OF DAYS : ";
                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 100;
                            cout << "\n\n FINE = " << fine;
                        }
                        st.resettoken();

                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        Color(2);
                        cout << "\n\n\tBOOK DEPOSITED SUCCESSFULLY.";
                        Color(7);
                    }
                }
                if (flag == 0)
                {
                    Color(4);
                    cout << "BOOK NUMBER DOES NOT EXISTS";
                    Color(7);
                }
            }

            else
            {
                Color(4);
                cout << "NO BOOK ISSUED";
                Color(7);
            }
        }
    }
    if (found == 0)
    {
        cout << "STUDENT RECORD NOT EXISTS.";
    }
    getch();
    fp.close();
    fp1.close();
}

void start()
{
    system("cls");
    gotoxy(90, 4);
    Color(1);
    cout << "GARV MAXIMUM LEARNING LIBRARY";
    gotoxy(94, 7);
    cout << "JAIPUR RAJASTHAN INDIA";
    cout << '\n';
    Color(7);
    getch();
}
void adminmenu()
{
    system("cls");
    int ch2;
    Color(11);
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
    cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\n\t6.CREATE BOOK";
    cout << "\n\n\n\t7.DISPLAY ALL BOOK RECORD";
    cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\n\n\t9.MODIFY BOOK RECORD";
    cout << "\n\n\n\t10.DELETE BOOK RECORD";
    cout << "\n\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11)";
    Color(7);
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        writestudent();
        break;
    case 2:
        displayalls();
        break;
    case 3:
        char num[studentAdmissionNumberLength];
        system("cls");
        cout << "\n\n\tPLEASE ENTER ADMISSION NUMBER : ";
        cin >> num;
        displaysps(num);
        break;
    case 4:
        modifystudent();
        break;
    case 5:
        deletestudent();
        break;
    case 6:
        writebook();
        break;
    case 7:
        displayallb();
        break;
    case 8:
    {
        char num[bookNumberLength];
        system("cls");
        cout << "\n\n\tPLEASE ENTER BOOK NUMBER : ";
        cin >> num;
        displayspb(num);
        break;
    }
    case 9:
        modifybook();
        break;
    case 10:
        deletebook();
        break;
    case 11:
        return;
    default:
        cout << "INVALID CHOICE.";
    }
    adminmenu();
}
int main()

{
    char ch;
    system("cls");
    start();
    do
    {
        system("cls");
        Color(11);
        cout << "\n\n\n\t MAIN MENU";
        cout << "\n\n\n\t1 BOOK ISSUE";
        cout << "\n\n\n\t2 BOOK DEPOSIT";
        cout << "\n\n\n\t3 ADMINISTRATOR MENU";
        cout << "\n\n\n\t4 EXIT";
        cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4)";
        Color(7);
        ch = getche();
        switch (ch)
        {
        case '1':
            bookissue();
            break;
        case '2':
            bookdeposit();
            break;
        case '3':
            adminmenu();
            break;
        case '4':
            exit(0);
            break;
        default:
            cout << "INVALID CHOICE";
        }
    }
    while (ch != 4);
    return 0;
}
