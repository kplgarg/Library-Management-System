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
char filter(char &a){
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
		cout << "\nENTER BOOK NUMBER.";
		fflush(stdin);
		gets(bookNumber,bookNumberLength);
		cout << "\nENTER BOOK NAME";
		fflush(stdin);
		gets(bookName, bookNameLength);
		cout << "\nENTER AUTHOR NAME";
		fflush(stdin);
		gets(authorName, authorNameLength);
		cout << "\n\n\nBook Created..";
	}
	//showing book
	void showbook()
	{
		cout << "\nBook Number: " << bookNumber;
		cout << "\nBook Name: ";
		puts(bookName);
		cout << "\nBook Author Name: ";
		puts(authorName);
	}
	//modifying book
	void modifybook()
	{
		cout << "\nBook Number: " << bookNumber;
		cout << "\nModify Book Name :";
		fflush(stdin);
		gets(bookName, bookNameLength);
		cout << "\nModify Author's Name :";
		fflush(stdin);
		gets(authorName, authorNameLength);
	}
	char *returnBookNUmber()
	{
		return bookNumber;
	}
	void report()
	{
		cout << bookNumber << setw(90) << bookName << setw(80) << authorName << endl;
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
		cout << "\n\nEnter The Admission Number";
		fflush(stdin);
		gets(admissionNumber,studentAdmissionNumberLength);
		cout <<"\n\nEnter The Student Name";
		fflush(stdin);
		gets(name, studentNameLength);
		token = 0;
		studentBookNumber[0] = '\0';
		cout <<"\n\nStudent Record Created...";
	}
	//showing student
	void showstudent()
	{
		cout << "\nAdmission Number : " << admissionNumber;
		cout << "\nStudent Name : ";
		puts(name);
		cout << "\nNo of Book Issued : " << token;
		if (token == 1)
		{
			cout << "\nBook Number " << studentBookNumber;
		}
	}
	//modifying student
	void modifystudent()
	{
		cout << "\nAdmission Number " << admissionNumber;
		cout << "\nModify Student Name : ";
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
		cout << "\t" << admissionNumber << setw(90) << name << setw(80) << token << endl;
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
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
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
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
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
		cout << "\n\nBook does not exist";
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
		cout << "\n\nStudent does not exist";
	}
	getch();
}
void modifybook()
{
	char n[bookNumberLength];
	int found = 0;
	system("cls");
	cout << "\n\nMODIFY BOOK RECORD...";
	cout << "\n\nEnter the book no. ";
	fflush(stdin);
	gets(n,bookNumberLength);
	fp.open("book.txt", ios::in | ios::out);
	while (fp.read((char *)&bk, sizeof(book)) && found == 0)
	{
		if (strcmp(bk.returnBookNUmber(), n) == 0)
		{
			bk.showbook();
			cout << "\nEnter the new details book";
			bk.modifybook();
			int pos = -1 * sizeof(bk);
			fp.seekp(pos, ios::cur); // back from current position
			fp.write((char *)&bk, sizeof(book));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	getch(); // press key to get out
}
void modifystudent()
{
	char n[studentAdmissionNumberLength];
	int found = 0; // seach book of given data
	system("cls");
	cout << "\n\nMODIFY STUDENT RECORD...";
	cout << "\n\nEnter the Admission no. ";
	fflush(stdin);
	gets(n,studentAdmissionNumberLength);
	fp.open("student.txt", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmp(st.returnAdmissionNumber(), n) == 0)
		{
			st.showstudent();
			cout << "\nEnter the new details of student";
			st.modifystudent();
			int pos = -1 * sizeof(st);
			fp.seekp(pos, ios::cur); // back from current position
			fp.write((char *)&st, sizeof(student));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	getch(); // press key to get out
}

void deletestudent()
{
	char n[studentAdmissionNumberLength];
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE STUDENT...";
	cout << "\n\nEnter the Admission no> : ";
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
		cout << "\n\n\tRecord Deleted..";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	getch();
}
void deletebook()
{
	char n[bookNumberLength]; // book no.
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE BOOK...";
	cout << "\n\nEnter the Book no> : ";
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
		cout << "\n\n\tRecord Deleted... ";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	getch();
}
void displayalls()
{
	system("cls");
	fp.open("student.txt", ios::in); // read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		getch();
		return; // press any key and return
	}

	cout << "\n\n";
	gotoxy(92,2);
	cout<<"Student List\n\n";
	cout << "==================================================================================================================================================================================================================\n";
	cout << "\tAdmission No." << setw(80) << "Name" << setw(80) << "Book Issued\n";
	cout << "==================================================================================================================================================================================================================\n";
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
		cout << "File Could Not Be Open";
		getch();
		return; // press any key and return
	}
	cout << "\n\n";
	gotoxy(87,2);
	cout<<"Book List\n\n";
	cout << "==================================================================================================================================================================================================================\n";
	cout << "\tBook No." << setw(80) << "Book Name" << setw(80) << "Book Author\n";
	cout << "==================================================================================================================================================================================================================\n";
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
	cout << "\n\n\tEnter Admission no.";
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
				cout << "\n\n\tEnter The Book No.";
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
						cout << "\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exists";
				}
			}

			else
			{

				cout << "You Have Not Returned The Last Book";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Exists...";
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
	cout << "\n\nBOOK DEPOSIT...";
	cout << "\n\n\tEnter Admission no. Of Student";
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
						cout << "\n\n Book Deposited In No. Of Days";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\n Fine = " << fine;
						}
						st.resettoken();

						int pos = -1 * sizeof(st);
						fp.seekg(pos, ios::cur);
						fp.write((char *)&st, sizeof(student));
						cout << "\n\n\tBook Deposited Successfully";
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exists";
				}
			}

			else
			{

				cout << "No Book Issued";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Exists...";
	}
	getch();
	fp.close();
	fp1.close();
}

void start()
{
	system("cls");
	gotoxy(90, 4);
	cout << "GARV MAXIMUM LEARNING LIBRARY";
	gotoxy(94, 7);
	cout << "JAIPUR RAJASTHAN INDIA";
	cout << '\n';
	getch();
}
void adminmenu()
{
	system("cls");
	int ch2;
	cout << "\n\n\n\tADMINISTRATOR MENU";
	cout << "\n\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
	cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
	cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\n\t6.CREATE BOOK";
	cout << "\n\n\n\t7.CREATE ALL BOOKS";
	cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
	cout << "\n\n\n\t9.MODIFY BOOK RECORD";
	cout << "\n\n\n\t10.DELETE BOOK RECORD";
	cout << "\n\n\n\t11.BACK TO MAIN MENU";
	cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11)";
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
		cout << "\n\n\t Please enter admission no.";
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
		cout << "\n\n\tPlease enter book no.";
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
		cout << "Invalid choice";
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
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\n\t1 BOOK ISSUE";
		cout << "\n\n\n\t2 BOOK DEPOSIT";
		cout << "\n\n\n\t3 ADMINISTRATOR MENU";
		cout << "\n\n\n\t4 EXIT";
		cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4)";
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
	} while (ch != 4);
	return 0;
}
