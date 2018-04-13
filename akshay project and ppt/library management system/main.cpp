#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;
void admi();
class book
{
     public:
    char bookid[10];
    char bookname[30];
    float bookprice;
    char rakeno[10];
    book()
         {

              strcpy(bookid,"no name");
              strcpy(bookname,"no name");
              bookprice=0;
              strcpy(rakeno,"no name");
         }
         void addbook()
         {
              //system("cls");
              cout<<"\t\tEnter book name: ";
              fflush(stdin);
              cin.getline(bookname,29);
              cout<<"\t\tEnter book id: ";
              fflush(stdin);
              cin.getline(bookid,10);
              cout<<"\t\tEnter book price: ";
              cin>>bookprice;
            while(1)
                {
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"\n\t\tInvalid Entry.....\n\t\tPlease Enter a floating number:";
                cin>>bookprice;
                }
                if(!cin.fail())
                break;
                }
              cout<<"\t\tEnter rake number: ";
              fflush(stdin);
              cin.getline(rakeno,9);
         }
         void displayHead()
         {
            cout<<"\t\t"<<"book id"<<setw(20)<<"book name"<<setw(20)<<"bookprice"<<setw(20)<<"rakeno"<<endl<<endl;
            cout<<setw(10)<<"\t\t-----------------------------------------------------------------------------"<<endl;
         }
         void display()
         {
              cout<<"\t\t"<<bookid<<setw(25)<<bookname<<setw(25)<<bookprice<<setw(25)<<rakeno<<endl<<endl;
              cout<<"\t\t--------------------------------------------------------------------------------\n";
         }
         char* retbno()
         {
               return bookid;
         }

       void writebook();
       void readbook();
       int deletebook(char *);
       int modifybook(char *);
       void searchbook();
};
class membership
{
     public:
     char name[30];
     char id[10];
     char department[30];
     char type[20];
     int token;
     char stbno[10];
     membership()
     {
          strcpy(name,"no name");
          strcpy(id,"no name");
          strcpy(department,"no name");
          strcpy(type,"no name");
     }
     void student()
     {
              cout<<"\t\tEnter student name: ";
              fflush(stdin);
              cin.getline(name,29);
              cout<<"\t\tEnter student id: ";
              fflush(stdin);
              cin.getline(id,9);
              cout<<"\t\tEnter department: ";
              fflush(stdin);
              cin.getline(department,29);
              cout<<"\t\tEnter membership type:";
              fflush(stdin);
              cin.getline(type,29);
              token=0;
		    stbno[0]='/0';
     }
     char* retadmno()
	{
		return id;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}
	void displayHead()
	{
	    cout<<setw(20)<<"id"<<setw(20)<<"name"<<setw(20)<<"department"<<endl;
        cout<<"\t\t-----------------------------------------------------"<<endl;
	}
    void display()
    {
        cout<<"\t\t"<<id<<setw(25)<<name<<setw(25)<<department<<endl<<endl;
        cout<<"\t\t------------------------------------------------------\n";

    }
    void writemember();
    int readmember();
    int deletemember(char *);
    int modifymember(char *);
    void searchmember();

};

/****write a book detail into file***/
void book::writebook()
{
     ofstream fout;
     fout.open("file.dat",ios::app | ios::binary);
     fout.write((char *)this , sizeof(*this));
     fout.close();
}
/****read a book detail from file***/
void book::readbook()
{
     ifstream fin;
     fin.open("file.dat",ios::in|ios::binary);
     if(!fin)
          cout<<"\n\t\t\tError:file doesnot exit!!!!!!!!!";
     else
     {
           fin.read((char *)this,sizeof(*this));
           while(!fin.eof())
           {
                display();
                fin.read((char *)this,sizeof(*this));
           }
     }
     fin.close();
}
/***delete a book from file*****/
int book::deletebook(char *newid)
{
     int c=0,found=0,x;
     ofstream fout;
     ifstream fin;
     fin.open("file.dat",ios::in|ios::binary);
     if(!fin){
          cout<<"\n\t\t\tError:file does not exist!!!!!";
          return 0;
          }
     else
     {
           fout.open("tempfile.dat",ios::out|ios::app|ios::binary);
           fin.read((char *)this,sizeof(*this));
           while(!fin.eof())
           {
                if(strcmp(bookid,newid))
                {
                    fout.write((char *)this,sizeof(*this));
                    found++;
                }
                  fin.read((char *)this,sizeof(*this));
                  c++;
           }
     }
     fin.close();
     fout.close();
     remove("file.dat");
     rename("tempfile.dat","file.dat");
     x=c-found;
     return x;
}
int book::modifybook(char *n)
{
   fstream file;
     file.open("file.dat",ios::in|ios::out|ios::ate|ios::binary);
     if(!file)
          cout<<"\n\t\t\tError!!!!!!!!!";
     else
     {
          file.seekp(0);
          file.read((char *)this,sizeof(*this));
          while(!file.eof())
          {
               if(strcmp(bookid,n)==0)
               {
                      cout<<"\t\tEnter book name: ";
                      fflush(stdin);
                      cin.getline(bookname,29);
                      cout<<"\t\tEnter book price: ";
                      cin>>bookprice;
                       while(1)
                        {
                        if(cin.fail())
                        {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cout<<"\n\t\tEnter a float no:";
                        cin>>bookprice;
                        }
                        if(!cin.fail())
                        break;
                        }
                      cout<<"\t\tEnter rake number: ";
                      fflush(stdin);
                      cin.getline(rakeno,9);
                    file.seekg(file.tellp()-sizeof(*this));
                    file.write((char *)this,sizeof(*this));
                   return 1;
               }
               file.read((char *)this,sizeof(*this));
          }
     }
     file.close();
     return 0;
     getch();
}
/****write a member detail into file***/
void membership::writemember()
{
     ofstream fout;
     fout.open("file1.dat",ios::app | ios::binary);
     fout.write((char *)this , sizeof(*this));
     fout.close();
}
/*****delete a member from file**/
int membership::deletemember(char *newid)
{
     int c=0,found=0,x;
     ofstream fout;
     ifstream fin;
     fin.open("file1.dat",ios::in|ios::binary);
     if(!fin)
          cout<<"\n\t\t\tError:file doesnot exist!!!!!";
     else
     {
          fout.open("tempfile1.dat",ios::app|ios::binary);
           fin.read((char *)this,sizeof(*this));
           while(!fin.eof())
           {
                if(strcmp(id,newid))
                {
                    fout.write((char *)this,sizeof(*this));
                    found++;
                }
                fin.read((char *)this,sizeof(*this));
                c++;
           }
     }
     fin.close();
     fout.close();
     x=c-found;
     remove("file1.dat");
     rename("tempfile1.dat","file1.dat");
     return x;
}
/****read a member detail from file***/
int membership::readmember()
{
     ifstream fin;
     int c=0;
     fin.open("file1.dat",ios::in|ios::binary);
     if(!fin)
          cout<<"\n\t\t\tError:file doesnot exit!!!!!!!!!";
     else
     {
           fin.read((char *)this,sizeof(*this));
           while(!fin.eof())
           {
               display();
               c++;
               fin.read((char *)this,sizeof(*this));
           }
     }
     fin.close();
     if(c==0)
        cout<<"\n\n\t\t\tNo record found........";
}
/****modify a member detail in file******/
int membership::modifymember(char *n)
{
     fstream file;
     file.open("file1.dat",ios::in|ios::out|ios::ate|ios::binary);
     if(!file)
          cout<<"\n\n\t\tError!!!!!!!!!";
     else
     {
          file.seekp(0);
          file.read((char *)this,sizeof(*this));
          while(!file.eof())
          {
               if(strcmp(id,n)==0)
               {
                      cout<<"\t\tEnter student name: ";
                      fflush(stdin);
                      cin.getline(name,29);
                      cin.getline(id,9);
                      cout<<"\t\tEnter department: ";
                      fflush(stdin);
                      cin.getline(department,29);
                      cout<<"\t\tEnter membership type:";
                      fflush(stdin);
                      cin.getline(type,29);
                    file.seekg(file.tellp()-sizeof(*this));
                    file.write((char *)this,sizeof(*this));
                     return 1;
               }
               file.read((char *)this,sizeof(*this));
          }
     }
     file.close();
     return 0;
     getch();
}
/**issue book**/
int issuebook()
    {
        fstream fp,fp1;
        membership st;
        book bk;
        char sn[10],bn[10];
        int found=0,flag=0;
        cout<<"\n\n\t\tEnter The student's Id:";
        cin>>sn;
        fp.open("file1.dat",ios::in|ios::out);
    	fp1.open("file.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(membership)) && found==0)
       	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"\n\n\t\tEnter the book Id: ";
				     cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
			   		if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.display();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
       						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(membership));
						cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date 	in backside of book and submit within 15 days fine Rs. 1 for each day 		after 15 days period";
					}
		    		}
		  		if(flag==0)
		    			cout<<"\n\t\t\tBook no does not exist";
			}
	    		else
		  		cout<<"\n\t\t\tYou have not returned the last book ";

		}
	}
	fp.close();
  	fp1.close();
    if(found==0)
    cout<<"\n\n\t\t\tStudent record not exist...\n\t\t\tso register student to this system....";
    cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
	getch();
}
/**return book**/
void returnbook()
{
    fstream fp,fp1;
    char sn[6],bn[6];
    book bk;
    membership st;
    int found=0,flag=0,day,fine;
    cout<<"\n\n\t\tEnter The student’s admission no.";
    cin>>sn;
    fp.open("file1.dat",ios::in|ios::out);
    fp1.open("file.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(membership)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.display();
				flag=1;
				cout<<"\n\n\t\tBook deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\n\t\tFine has to deposited Rs.. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(membership));
					cout<<"\n\n\t\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"\t\tBook no does not exist\n\t\t\tEnter correct book Id....";
		      }
		  else
			cout<<"\n\t\tNo book is issued..please check!!";
		}
	   }
     if(found==0)
	 cout<<"\n\n\n\t\tStudent record not exist...";
	 cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
	 getch();
     fp.close();
     fp1.close();
  }
  void membership::searchmember()
{
     int c=0;
     char i[6];
     cout<<"\n\t\tEnter book id:";
     cin>>i;
     ifstream fin;
     fin.open("file1.dat",ios::in|ios::binary);
     if(!fin)
     {
          cout<<"\n\t\t\tError:File doesnot exist";
          return;
     }
     else
     {
          fin.read((char *)this,sizeof(*this));
          while(!fin.eof())
          {
               if(strcmp(id,i)==0)
               {
                    displayHead();
                    display();
                    c++;
                    break;
               }
                fin.read((char *)this,sizeof(*this));
          }
     }
     fin.close();
     if(c==0)
          cout<<"\n\t\t\trecord does not exist!!!!!!!\n";
     else
          cout<<"\n\t\t\trecord found\n";
}
/**update a record from file***/
void book::searchbook()
{
     int c=0;
     char i[10];
     cout<<"\n\t\tEnter book id:";
     cin>>i;
     ifstream fin;
     fin.open("file.dat",ios::in|ios::binary);
     if(!fin)
     {
          cout<<"\n\t\t\tError:File doesnot exist";
          return;
     }
     else
     {
          fin.read((char *)this,sizeof(*this));
          while(!fin.eof())
          {
               if(strcmp(bookid,i)==0)
               {
                    displayHead();
                    display();
                    c++;
                    break;
               }
               fin.read((char *)this,sizeof(*this));
          }
     }
     fin.close();
     if(c==0)
          cout<<"\n\t\t\trecord does not exist!!!!!!!\n";
     else
          cout<<"\n\t\t\trecord found\n";
}

void specialfm()
{
            do
            {
                     system("cls");
                     int choice;
                     cout<<"\n\n\t\tSPECIAL FUNCTION MENU\n";
                     cout<<"\n\t**************************************"<<endl;
                     cout<<"\n\n\t\t\t\t1) ISSUE BOOK";
                     cout<<"\n\n\t\t\t\t2) DIPOSIT BOOK";
                     cout<<"\n\n\t\t\t\t3) RETURN";
                     cout<<"\n\t\tEnter choice:";
                     cin>>choice;
                     if(choice==1)
                      {
                           system("cls");
                           cout<<"\n\n\t\t\t\t    ISSUE BOOK ";
                           cout<<"\n\n\t\t\t\t*******************\n\n";
                           issuebook();
                           cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
                           getch();
                      }
                      else if(choice==2)
                      {
                           system("cls");
                           cout<<"\n\n\t\t\t\t    RETURN BOOK ";
                           cout<<"\n\n\t\t\t\t*******************\n\n";
                           returnbook();
                           cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
                           getch();
                      }
                      else if(choice==3)
                      {
                          return;
                      }
                      else
                      {
                           system("cls");
                           cout<<"\n\n\n\n\t\t\t\t\t\tSORRY...INVALID CHOICE....:";
                           cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
                           getch();
                      }

        }while(1);
}
void generalfm()
{
            do
            {
                     system("cls");
                     book b;
                     membership m;
                     int ch,x=0;
                     char n[10];
                     cout<<"\n\n\t\tGENERAL FUNCTION MENU\n";
                     cout<<"\n\t**************************************"<<endl;
                     cout<<"\n\t\t1.ADD BOOK"<<endl;
                     cout<<"\n\t\t2.ADD MEMBER"<<endl;
                     cout<<"\n\t\t3.DISPLAY BOOK"<<endl;
                     cout<<"\n\t\t4.DISPLAY MEMBERS"<<endl;
                     cout<<"\n\t\t5.DELETE BOOK"<<endl;
                     cout<<"\n\t\t6.DELETE MEMBER"<<endl;
                     cout<<"\n\t\t7.UPDATE MEMBER"<<endl;
                     cout<<"\n\t\t8.UPDATE BOOK"<<endl;
                     cout<<"\n\t\t9.RETURN TO MAIN MENU"<<endl;
                     cout<<endl;
                     cout<<"\t\tENTER YOUR CHOICE:";
                     cin>>ch;
                     cout<<endl;
                     if(ch==1)
                     {
                          system("cls");
                          char c;
                          do
                          {
                              system("cls");
                              cout<<"\n\n\t\tADD BOOK"<<endl;
                              cout<<"\n\t----------------------------"<<endl;
                              b.addbook();
                              b.writebook();
                              cout<<"\n\t\tIf you want to insert another book then press 'Y' or 'y': ";
                              cin>>c;
                          }while(c=='Y' || c=='y');
                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();
                     }
                     else if(ch==2)
                     {
                          system("cls");
                          char c;

                          do
                          {
                              system("cls");
                              cout<<"\n\n\t\tMEMBERSHIP ENTRY\n"<<endl;
                              cout<<"\t  ------------------------"<<endl;
                              m.student();
                              m.writemember();
                              cout<<"\n\t\tIf you want to insert another book then press 'Y' or 'y': ";
                              cin>>c;
                          }while(c=='Y' || c=='y');
                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();

                     }
                      else if(ch==3)
                     {
                          system("cls");
                          cout<<"\n\n\t\t\t\tDISPLAY BOOK"<<endl;
                          cout<<"\t\t\t       ------------"<<endl;
                          cout<<"\t\t"<<"book id"<<setw(20)<<"book name"<<setw(20)<<"bookprice"<<setw(20)<<"rakeno"<<endl<<endl;
                          cout<<setw(10)<<"\t\t-----------------------------------------------------------------------------"<<endl;
                          b.readbook();
                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();

                     }
                      else if(ch==4)
                     {
                          system("cls");
                          cout<<"\n\n\t\tDISPLAY MEMBERS"<<endl;
                          cout<<"\t----------------------------"<<endl;
                          cout<<setw(20)<<"id"<<setw(20)<<"name"<<setw(20)<<"department"<<endl;
                          cout<<"\t\t-----------------------------------------------------"<<endl;
                          m.readmember();
                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();
                     }
                     else if(ch==5)
                     {
                          system("cls");
                          cout<<"\n\n\t\tDELETE BOOK\n"<<endl;
                          cout<<"\t----------------------------"<<endl;
                          cout<<"\t\tEnter id:";
                          cin>>n;
                          x=b.deletebook(n);
                          if(x==0)
                            cout<<"\n\t\t\trecord does not exist!!!!!";
                          else
                            cout<<"\n\t\t\trecord is deleted!!!!";
                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();
                     }

                     else if(ch==6)
                     {
                          system("cls");
                          cout<<"\n\n\t\tDELETE MEMBERSHIP\n"<<endl;
                          cout<<"\t----------------------------"<<endl;
                          cout<<"\t\tEnter id:";
                          cin>>n;
                          x=m.deletemember(n);
                          if(x==0)
                            cout<<"\n\t\t\trecord does not exist!!!!!";
                          else
                            cout<<"\n\t\t\trecord is deleted!!!!";

                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();
                     }
                     else if(ch==7)
                     {
                          system("cls");
                          char n[20];
                          int x;
                          cout<<"\n\n\t\tUPDATE MEMBER\n";
                          cout<<"\t----------------------------"<<endl;
                          cout<<"\t\tEnter id:";
                          cin>>n;
                          x=m.modifymember(n);
                          if(x==0)
                            cout<<"\n\t\t\trecord does not exist!!!!!";
                          else
                            cout<<"\n\t\t\trecord is modified!!!!";

                          cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();
                     }
                     else if(ch==8)
                     {
                          system("cls");
                          cout<<"\n\n\t\tUPDATE BOOK\n";
                          cout<<"\t----------------------------"<<endl;
                          cout<<"\t\tEnter id:";
                          cin>>n;
                          x=b.modifybook(n);
                          if(x==0)
                            cout<<"\n\t\t\trecord does not exist!!!!!";
                          else
                            cout<<"\n\t\t\trecord is modified!!!!";
                            cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                          getch();
                     }

                      else if(ch==9)
                     {
                          cout<<"\t\t\tEXIT"<<endl;
                          return;

                     }
                     else
                     {
                            cout<<"\n\t\t\tError:Invalid choice!!!!\n";
                            cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                            getch();
                            cout<<"\n\n\n\t\tpress any key!!!!!!!\n";
                     }
            }while(1);

}
void user()
{
    system("cls");
    book b;
    membership m;
    int ch;
    while(1)
    {
        system("cls");
        cout<<"\n\n\t\tUSER'S MENU\n";
        cout<<"\n\t*****************************"<<endl;
        cout<<"\n\t\t1.SEARCH BOOK"<<endl;
        cout<<"\n\t\t2.SEARCH MEMBER"<<endl;
        cout<<"\n\t\t3.RETURN"<<endl;
        cout<<"\n\t\tEnter choice:";
        cin>>ch;
        if(ch==1)
        {
            system("cls");
            cout<<"\n\t\tSEARCH BOOK"<<endl;
            cout<<"\n\t\t------------"<<endl;
            b.searchbook();
            cout<<"\n\n\t\t\tPress any key...........\n";
            getch();
        }
        else if(ch==2)
        {
            system("cls");
            cout<<"\n\t\t2.SEARCH MEMBER"<<endl;
            cout<<"\n\t\t--------------"<<endl;
            m.searchmember();
            cout<<"\n\n\t\t\tPress any key.......\n";
            getch();
        }
        else if(ch==3)
        {
            return;
        }
        else
        {
            cout<<"\n\t\t\tError:Invalid choice!!!!\n";
            cout<<"\n\n\n\t\t\tpress any key!!!!!!!\n";
            getch();
        }
    }
}
void PrintMenu()
{
     system("cls");
     cout<<"\n\n\t\t\t\t  LIBRARY MANAGEMENT SYATEM";
     cout<<"\n\n\t\t\t\t*****************************\n\n";
     cout<<"\n\t\t\t\t1) ADMINISTRATIVE MENU";
     cout<<"\n\n\t\t\t\t2) USER'S MENU";
     cout<<"\n\n\t\t\t\t3) EXIT";
}
int GetChoice()
{
     int ch;
     cout<<"\n\n\n\t\t\t\t\tEnter choice: ";
     cin>>ch;
     return ch;
}
void intro()
  {
        system("cls");
        printf("\n\n\n\n\t\tLIBRARY\n\n\t\t\tMANAGEMENT\n\n\t\t\t\tSYSTEM");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tNAME:AKSHAYA KUMAR ROUT\n\n\t\t\t\t\tROLLNO:160511201006\n\n\t\t\t\t\tGUIDED BY:Prof. RUCHA PATEL");
        printf("\n\n\n\n\t\t\t\t\t\t\t\tpress any key");
        getch();
  }
int main()
{
     int choice;
     intro();
     while(1)
     {
          PrintMenu();
          choice=GetChoice();
          if(choice==1)
          {
               system("cls");
               cout<<"\n\n\t\t\t\t    ADMINISTRATIVE MENU";
               cout<<"\n\n\t\t\t\t****************************\n\n";
               admi();
               cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
               getch();
          }
          else if(choice==2)
          {
               system("cls");
               cout<<"\n\n\t\t\t\t    USER'S MENU";
               cout<<"\n\n\t\t\t\t****************************\n\n";
               user();
               cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
               getch();

          }
          else if(choice==3)
          {
               break;
          }
          else
          {
               system("cls");
               cout<<"\n\n\n\n\t\t\t\t\t\tSORRY...INVALID CHOICE....:";
               cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
               getch();
          }
     }

     return 0;
}
void admi()
{
        int ch;
        do
        {
             system("cls");
             cout<<"\n\n\t\tADMINISTRATIVE MENU\n";
             cout<<"\n\t*************************************************"<<endl;
             cout<<"\n\n\t\t1.SPECIAL FUNCTION MENU";
             cout<<"\n\n\t\t2.GENERAL FUNCTION MENU";
             cout<<"\n\n\t\t3.RETURN";
             cout<<"\n\n\t\tEnter choice:";
             cin>>ch;
             if(ch==1)
             {
                     specialfm();
             }
             else if(ch==2)
             {
                    generalfm();
             }
             else if(ch==3)
                      {
                          return;
                      }
             else
                      {
                           system("cls");
                           cout<<"\n\n\n\n\t\t\t\t\t\tSORRY...INVALID CHOICE....:";
                           cout<<"\n\n\n\t\t\t\t\tPress any key to continue.....";
                           getch();
                      }

        }while(1);
}
