//*************************************************************************************************************
//				HEADER FILE USED IN PROJECT
//*************************************************************************************************************

#include<conio.h>
#include<ctype.h>
#include<fstream.h>
#include<iostream.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//*************************************************************************************************************
//				CLASSES USED IN PROJECT
//*************************************************************************************************************

class book
{   	int book_no;
	char book_name[50],author_name[20];
	public:
		void create_book();
		void show_book();
		void modify_book();
		void report();
		int return_book_no();
};

class student
{   	int admission_no,token,student_book_no;
	char name[20];
	public:
		void create_student();
		void show_student();
		void modify_student();
		void addtoken();
		void resettoken();
		void getstudent_book_no(int);
		void report();
		int return_admission_no();
		int return_student_book_no();
		int return_token();
};

//*************************************************************************************************************
//                  		FUNCTIONS USED IN THE CLASSES
//*************************************************************************************************************

void book::create_book()
{       clrscr();
	cout<<"\nNEW BOOK ENTRY...\n";
	cout<<"\nEnter The book no.";
	cin>>book_no;
	cout<<"\n\nEnter The Name of The Book ";
	gets(book_name);
	cout<<"\n\nEnter The Author's Name ";
	gets(author_name);
	cout<<"\n\n\nBook Created..";
}
void book::show_book()
{	cout<<"\nBook no. : "<<book_no;
	cout<<"\nBook Name : ";
	puts(book_name);
	cout<<"Author Name : ";
	puts(author_name);
}
void book::modify_book()
{	cout<<"\nBook no. : "<<book_no;
	cout<<"\nModify Book Name : ";
	gets(book_name);
	cout<<"\nModify Author's Name of Book : ";
	gets(author_name);
	cout<<"\n\n\nBook Modified..";
}
void book::report()
{   	cout<<book_no<<setw(30)<<book_name<<setw(30)<<author_name<<endl;
}
int book::return_book_no()
{   	return book_no;
}

void student::create_student()
{   	clrscr();
	cout<<"\nNEW STUDENT ENTRY...\n";
	cout<<"\nEnter The admission no.:";
	cin>>admission_no;
	cout<<"\n\nEnter The Name of The Student:";
	gets(name);
	token=0;
	student_book_no=0;
	cout<<"\n\nStudent Record Created..";
}
void student::show_student()
{   	cout<<"\nAdmission no. : "<<admission_no;
	cout<<"\nStudent Name : ";
	puts(name);
	cout<<"\nNo of Book issued : "<<token;
	if(token==1)
		cout<<"\nBook No "<<student_book_no;
}
void student::modify_student()
{   	cout<<"\nAdmission no. : "<<admission_no;
	cout<<"\nModify Student Name : ";
	gets(name);
	cout<<"\n\nStudent Record Modified..";
}
void student::addtoken()
{   	token=1;
}
void student::resettoken()
{   	token=0;
}
void student::getstudent_book_no(int t)
{   	student_book_no=t;
}
void student::report()
{   	cout<<"\t"<<admission_no<<setw(20)<<name<<setw(10)<<token<<endl;
}
int student::return_admission_no()
{   	return admission_no;
}
int student::return_student_book_no()
{   	return student_book_no;
}
int student::return_token()
{   	return token;
}

//*************************************************************************************************************
//				GLOBAL DECLARATION FOR STREAM OBJECT, OBJECT
//*************************************************************************************************************

fstream fp1,fp2;
book bk;
student st;

//*************************************************************************************************************
//				FUNCTION TO WRITE IN THE FILE
//*************************************************************************************************************

void write_book()
{   	char ch;
	fp1.open("book.dat",ios::out|ios::app);
	do
	{	bk.create_book();
		fp1.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(toupper(ch)=='Y');
	fp1.close();
}
void write_student()
{   	char ch;
	fp1.open("student.dat",ios::out|ios::app);
	do
	{	st.create_student();
		fp1.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(toupper(ch)=='Y');
	fp1.close();
}

//*************************************************************************************************************
//				FUNCTION TO READ SPECIFIC RECORD FROM FILE
//*************************************************************************************************************

void display_specific_book_record(int n)
{   	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp1.open("book.dat",ios::in);
	while(fp1.read((char*)&bk,sizeof(book)))
		if(bk.return_book_no()==n)
		{   	bk.show_book();
			flag=1;
		}
	fp1.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}
void display_specific_student_record(int n)
{   	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp1.open("student.dat",ios::in);
	while(fp1.read((char*)&st,sizeof(student)))
		if(st.return_admission_no()==n)
		{   	st.show_student();
			flag=1;
		}
	fp1.close();
	if(flag==0)
		cout<<"\n\nStudent does not exist";
	getch();
}

//*************************************************************************************************************
//				FUNCTION TO MODIFY RECORD OF FILE
//*************************************************************************************************************

void modify_book()
{   	int n, found=0;
	clrscr();
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp1.open("book.dat",ios::in|ios::out);
	while(fp1.read((char*)&bk,sizeof(book)) && found==0)
		if(bk.return_book_no()==n)
		{	bk.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp1.seekp(pos,ios::cur);
			fp1.write((char*)&bk,sizeof(book));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	fp1.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}
void modify_student()
{   	int n, found=0;
	clrscr();
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp1.open("student.dat",ios::in|ios::out);
	while(fp1.read((char*)&st,sizeof(student)) && found==0)
		if(st.return_admission_no()==n)
		{	st.show_student();
			cout<<"\nEnter The New Details of student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp1.seekp(pos,ios::cur);
			fp1.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	fp1.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//*************************************************************************************************************
//				FUNCTION TO DELETE RECORD FROM FILE
//*************************************************************************************************************

void delete_student()
{	int n, flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp1.open("student.dat",ios::in|ios::out);
	fp2.open("Temp.dat",ios::out);
	fp1.seekg(0,ios::beg);
	while(fp1.read((char*)&st,sizeof(student)))
	{	if(st.return_admission_no()!=n)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}
	fp2.close();
	fp1.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}
void delete_book()
{	int n;
	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp1.open("book.dat",ios::in|ios::out);
	fp2.open("Temp.dat",ios::out);
	fp1.seekg(0,ios::beg);
	while(fp1.read((char*)&bk,sizeof(book)))
	{	if(bk.return_book_no()!=n)
		{	fp2.write((char*)&bk,sizeof(book));
		}
	}
	fp2.close();
	fp1.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}

//*************************************************************************************************************
//				FUNCTION TO DISPLAY ALL STUDENTS LIST
//*************************************************************************************************************

void display_all_student_record()
{	clrscr();
	fp1.open("student.dat",ios::in);
	if(!fp1)
	{	cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}
	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==============================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"==============================================================\n";
	while(fp1.read((char*)&st,sizeof(student)))
	st.report();
	fp1.close();
	getch();
}

//*************************************************************************************************************
//				FUNCTION TO DISPLAY ALL BOOKS LIST
//*************************************************************************************************************

void display_all_library()
{	clrscr();
	fp1.open("book.dat",ios::in);
	if(!fp1)
	{	cout<<"ERROR!!! FILE COULD NOT BE OPEN. ";
		getch();
		return;
	}
	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"==============================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"==============================================================\n";
	while(fp1.read((char*)&bk,sizeof(book)))
	bk.report();
    fp1.close();
    getch();
}

//*************************************************************************************************************
//				FUNCTION TO ISSUE BOOK
//*************************************************************************************************************

void book_issue()
{	int student_no,b_no,found=0,flag=0;
	clrscr();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no.";
	cin>>student_no;
	fp1.open("student.dat",ios::in|ios::out);
	fp2.open("book.dat",ios::in|ios::out);
	while(fp1.read((char*)&st,sizeof(student)) && found==0)
		if(st.return_admission_no()==student_no)
		{	found=1;
			if(st.return_token()==0)
			{	cout<<"\n\n\tEnter the book no. ";
				cin>>b_no;
				while(fp2.read((char*)&bk,sizeof(book))&& flag==0)
					if(bk.return_book_no()==b_no)
					{	bk.show_book();
						flag=1;
						st.addtoken();
						st.getstudent_book_no(bk.return_book_no());
						int pos=-1*sizeof(st);
						fp1.seekp(pos,ios::cur);
						fp1.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully\n";
						cout<<"\nPlease Note: Write current date in backside of book.";
					}
				if(flag==0)
					cout<<"Book no does not exist";
			}
			else
				cout<<"You have not return_urned the last book ";
		}
	if(found==0)
		cout<<"Student record not exist...";
	getch();
	fp1.close();
	fp2.close();
}

//*************************************************************************************************************
//				FUNCTION TO DEPOSIT BOOK
//*************************************************************************************************************

void book_deposit()
{	int student_no,b_no,found=0,flag=0,day,fine;
	clrscr();
	cout<<"\n\nBOOK DEPOSIT ...";
	cout<<"\n\n\tEnter The student's admission no.";
	cin>>student_no;
	fp1.open("student.dat",ios::in|ios::out);
	fp2.open("book.dat",ios::in|ios::out);
	while(fp1.read((char*)&st,sizeof(student)) && found==0)
	{	if(st.return_admission_no()==student_no)
		{	found=1;
			if(st.return_token()==1)
			{	while(fp2.read((char*)&bk,sizeof(book))&& flag==0)
					if(bk.return_book_no()==st.return_student_book_no())
					{	bk.show_book();
						flag=1;
						cout<<"\n\nBook deposited in no. of days";
						cin>>day;
						if(day>15)
						{	fine=(day-15)*1;
							cout<<"\n\nFine has to deposited Rs. "<<fine;
						}
						st.resettoken();
						int pos=-1*sizeof(st);
						fp1.seekp(pos,ios::cur);
						fp1.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book deposited successfully";
					}
			}
			if(flag==0)
				cout<<"Book no does not exist";
		}
		else
			cout<<"No book is issued..please check!!";
	}
	if(found==0)
		cout<<"Student record not exist...";
	getch();
	fp1.close();
	fp2.close();
}

//*************************************************************************************************************
//    				INTRODUCTION FUNCTION
//*************************************************************************************************************

void intro()
{	clrscr();
	gotoxy(31,5);
	cout<<"WELCOME TO THE PROJECT";
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(33,7);
	cout<<" LIBRARY MANAGEMENT ";
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	gotoxy(15,10);
	cout<<"This project has facility of maintaining records";
	gotoxy(15,11);
	cout<<"of BOOKS and STUDENTS.";
	gotoxy(15,13);
	cout<<"This project can hold books records as much as you can";
	gotoxy(15,16);
	cout<<"One member can issue one book at a time. If he/she";
	gotoxy(15,17);
	cout<<"does not return book upto 15 days he/she have to";
	gotoxy(15,18);
	cout<<"pay fine of Rs.1/- per day till he returns the book";
	textcolor(YELLOW+BLINK);
	gotoxy(28,21);
	cout<<" BY #PROGRAMMER-ABHIJEET";
	textcolor(LIGHTGRAY+BLINK);
	gotoxy(27,25);
	cout<<" Press any key to continue ";
	textcolor(LIGHTGRAY);
	getch();
}

//*************************************************************************************************************
//    				ADMINISTRATOR MENU FUNCTION
//*************************************************************************************************************

void admin_menu()
{	clrscr();
	int ch,num;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\n\n\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
	cin>>ch;
	switch(ch)
	{	case 1: write_student();
			break;
		case 2: display_all_student_record();
			break;
		case 3: clrscr();
			cout<<"\n\n\tPlease Enter The Admission No. ";
			cin>>num;
			display_specific_student_record(num);
			break;
		case 4: modify_student();
			break;
		case 5: delete_student();
			break;
		case 6: write_book();
			break;
		case 7: display_all_library();
			break;
		case 8: num=0;
			clrscr();
			cout<<"\n\n\tPlease Enter The book No. ";
			cin>>num;
			display_specific_book_record(num);
			break;
		case 9: modify_book();
			break;
		case 10:delete_book();
			break;
		case 11:return;
		default:cout<<"\a";
	}
	admin_menu();
}

//*************************************************************************************************************
//    				THE MAIN FUNCTION OF PROGRAM
//*************************************************************************************************************

void main()
{	int ch;
	clrscr();
	intro();
	do
	{       clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
		cout<<"\n\n\t03. ADMINISTRATOR MENU";
		cout<<"\n\n\t04. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-4) ";
		cin>>ch;
		switch(ch)
		{	case 1:	book_issue();
				break;
			case 2: book_deposit();
				break;
			case 3: admin_menu();
				break;
			case 4: exit(0);
			default:cout<<"\a";
		}
	}while(ch!='4');
	getch();
}

//*************************************************************************************************************
//    				END OF PROJECT
//*************************************************************************************************************
