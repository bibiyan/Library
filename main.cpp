#include <iostream>
#include <cstdio> //rename
#include <fstream>
//#include <iomanip>
#include <vector>
#include <algorithm> // sort, remove
#include "tools.h"
#include "Book.h"

using namespace std;

//Прототипи
void books_add();void books_all();void books_find();void books_remove();
void books_sort();void books_view();void close();void exit();void help();
void login();void logout();void open();void save();void saveas();
void users_add();void users_remove();
//Масив от функции
void (*menuNo[16])(void)={books_add,books_all,books_find,books_remove,
                          books_sort,books_view,close,exit,help,login,
                          logout,open,save,saveas,users_add,users_remove};
//Структура Команда
struct Command
{ string menuItem; //Име на команда
  bool logon, adm; //Булеви променливи logon(дали има влязъл потребител в системата) и amd(дали потребителят е администратор)
  bool operator <(const Command &c) const//Предефиниране на оператор "<"
  {return menuItem<c.menuItem;}
  bool operator ==(const Command &c) const // Предефиниране на оператор "=="
  {return menuItem==c.menuItem;}
};
ostream &operator <<(ostream &os,const Command &c) //Предефиниран поток за изход "<<"
{return os<<c.menuItem;}
//Команди, подредени по азбучен ред
Command menu[16]=
{{"books add",true,true}, {"books all",true,false}, {"books find",true,false},
 {"books remove",true,true}, {"books sort",true,false}, {"books info",true,false},
 {"close",false,false}, {"exit",false,false}, {"help",false,false},
 {"login",false,false}, {"logout",true,false}, {"open",false,false},
 {"save",false,false}, {"saveas",false,false}, {"users add",true,true},
 {"users remove",true,true}};
//Структура Потребител
struct User{
    string UserName, UserPassword; //Потребителско име и парола
    bool isUserAdmin; //Дали потребителят е администратор
    bool operator ==(const User &u) const //Предефиниране на оператор "=="
  {return (UserName == u.UserName && UserPassword == u.UserPassword && isUserAdmin == u.isUserAdmin);}
};
ostream& operator<<(ostream& os,const User& other) //Предефиниране на поток за изход "<<"
{ 
        os<<other.UserName<<endl
          <<other.UserPassword<<endl
          <<other.isUserAdmin<<endl;
        return os;
}
istream& operator>>(istream& in, User& other) ////Предефиниране на поток за вход">>"
{
        in>>other.UserName>>other.UserPassword>>other.isUserAdmin;
        return in;
}

//ГЛОБАЛИ
 int mNo=-1;//Номер на изпълняваната подпрограма
 string user;//Име на текущия потребител
 bool isAdmin=false;//Дали текущият потребител е администратор
 string Param;//Подадени параметри
 vector<Book> books; // Вектор от книги
 string currentFile; // Текущ файл

//Търси команда от менюто и ако намери, извежда нейния номер
int getCmdNo(string s)
{
  int l=0,r=15,m; // left, right, middle
  Command t;
  t.menuItem = s;
  do
  {
    m=(l+r)/2;
    if (t==menu[m]) break;
    if (t<menu[m]) r=r-1;
    else l=l+1;
  } while (l<=r);
  if (l<=r) return m;//Номерът в менюто е m
  return -1;//Командата не е намерена
}
//Намира номера на командата и параметрите в глобалата Param
int getCmdAndParam(string s)
{int number,p,p1;
 string s1;
 //Ако целият входен низ е команда - ОК
 number=getCmdNo(s);
 if (number>=0)
 {
     Param="";
     return number;
 }
 p=s.find_first_of(" \t");//Иначе търсим интервал или табулатор в s
 if (p==string::npos)
 {
      Param="";
      return -1;//Ако няма интервал или табулатор- лоша команда
 }
 //Търсим втори разделител в s
 s1=Tools::trim(s.substr(p+1));
 p1=s1.find_first_of(" \t");
 if (p1==string::npos) //Ако няма, s1 е параметър, а думата преди него - команда
 {
    Param=s1;
    return getCmdNo(s.substr(0,p));
 }
 //Има втори разделител.
 number=getCmdNo(s.substr(0,p)+" "+s1.substr(0,p1));
 if (number>=0) // Първите две думи са команда и всичко след тях параметър
 {
    Param=Tools::trim(s1.substr(p1+1));
    return number;
 }
 //Първата дума е команда и всичко след нея - параметри
 Param=s1;
 return getCmdNo(s.substr(0,p));
}

//Реализации на подпрограмите
// При влизане във всяка от долните функции, глобалите съдържат:
//  mNo - Номера на изпълняваната подпрограма
//  user - Името на текущия потребител (празе низ, ако е анониммен)
//  isAdmin - Дали текущият потребител е администратор (анонимният не е)
//  Param -Подадени параметри: низът, който се намира след разпознатата команда

//Добавя книга
void books_add() //0
{
    if(!isAdmin) //Проверка дали има влязъл администратор в системата
    {
        cout<<"You are not admin."<<endl;
        return; //Ако няма, командата не се извършва
    }
    //Иначе добавя книга във вектора от книги
    cout<<"Add a book:"<<endl;
        Book bNext;
        bNext.getData(cin);
        books.push_back(bNext);
} 

//Извежда заглавие, автор, жанр, персонален номер за всяка книга в библиотеката.
void books_all()//1
{
    //Проверка дали има коректно влязъл потребител в системата
    if(user=="")
    {
        cout<<"You are not logged."<<endl; 
        return; //Ако няма, командата не се извършва
    }
    
     for (unsigned i=0;i<books.size();i++)
        {
            books[i].print();
        }
}
//Tърси книга по различен критерий (заглавие, автор, ключова дума).
void books_find()//2
{ 
  if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return; //Ако няма коректно влязъл потребител в системата, операцията не се изпълнява
    }
    string findBy, findWhat;
    findBy=Param.substr(0,Param.find_first_of(" ")); // Първата дума на Param - критерий за търсене (title, author, tag)
    findWhat=Param.substr(Param.find_first_of(" ")+1); // Какво да търси 
    if (findBy=="author") // Ако критерият е "автор"
    {
        for(int i=0;i<books.size();i++)
        if ((books[i].getAuthor()).compare(findWhat)==0)
        {
            books[i].printAllInf();
            cout<<endl;
        }
        cout<<endl;
    }
    if (findBy=="title") // Ако критерият е "заглавие"
    {
         for(int i=0;i<books.size();i++)
        if ((books[i].getTitle()).compare(findWhat)==0)
        {
            books[i].printAllInf();
            cout<<endl;
        }
        cout<<endl;
    }
    if (findBy=="tag") // Ако критерият е "ключова дума"
    {
        for(int i=0;i<books.size();i++)
        {
            size_t x=books[i].getKeyWords().find(findWhat);
            if(x!=string::npos)
            {
                books[i].printAllInf();
                cout<<endl;
            }
        }
        cout<<endl;
    }
}
//Премахва книга.
void books_remove() //3
{ 
    if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return; //Ако в системата не е влязъл администратор, операцията не се изпълнява
    }
    for(int i=0;i<books.size();i++)
    {
        if ((books[i].getIsbn()).compare(Param)==0)
            {
                books.erase(books.begin()+i); //Премахва конкретната книга от вектора с книги
            }
    }
}
//Сортира по заглавие, автор или година.
void books_sort()//4
{ 
    if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return; //Ако няма коректно влязъл потребител в системата, операцията не се изпълнява
    }
    string sortBy,helper,firstP, secondP;
    firstP=Param.substr(0,Param.find_first_of(" \t")); // първа дума на Param
    helper=Param.substr(Param.find_first_of(" \t")+1); // от втората дума на Param
    secondP=helper.substr(0,helper.find_first_of(" \t")); // втора дума на Param
    if(firstP=="title") // Сортиране по заглавие
    {
        if(secondP=="desc") // Проверка дали сортирането да бъде в низходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpTitleDesc);
        }
        else // Иначе сортира във възходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpTitle);
        }
    }
    if(firstP=="author") // Сортиране по автор
    {
        if(secondP=="desc") // Проверка дали сортирането да бъде в низходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpAuthorDesc);
        }
        else // Иначе сортира във възходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpAuthor);
        }
    }
    if(firstP=="year") // Сортиране по година
    {
        if(secondP=="desc") // Проверка дали сортирането да бъде в низходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpYearDesc);
        }
        else // Иначе сортира във възходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpYear);
        }
    }
    if(firstP=="rating") //Сортиране по рейтинг
    {
        if(secondP=="desc") // Проверка дали сортирането да бъде в низходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpRatingDesc);
        }
        else //Иначе сортира във възходящ ред
        {
            sort(books.begin(), books.end(), Book::cmpRating);
        }
    }
    books_all();
}
// Извежда подробна информация за книга с персонален номер, равен на <isbn_value>.
void books_view()//5
{ 
 if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return; // Ако няма коректно влязъл потребител в системата, операцията не се извършва
    }
     for(int i=0;i<books.size();i++)
        if ((books[i].getIsbn()).compare(Param)==0)
        {
            books[i].printAllInf();
            cout<<endl;
            return;
        }
}
//Затваря текущо отворения документ, изчиства текущо заредената информация. 
void close()//6
{ 
    books.clear();
}
//Излизане от програмата.
void exit()//7
{ 
  //Командата няма параметри
  if (Param!="") {cout<<"Invalid parameter\n";mNo=-1;}
}
//Извежда кратка информация за поддържаните от програмата команди.
void help()//8
{ 
  cout<<"The following commands are supported:"<<endl;
        cout<<"open <file>	                  opens <file>"<<endl
            <<"close                          closes currently opened file"<<endl
            <<"save                           saves the currently open file"<<endl
            <<"saveas <file>                  saves the currently open file in <file>"<<endl
            <<"help                           prints this information"<<endl
            <<"login (username)               logs in the system"<<endl
            <<"logout                         logs out of the system"<<endl
            <<"exit                           exists the program"<<endl
            <<"books all                      shows all books"<<endl
            <<"books find <option_string>     searches a book "<<endl
            <<"books sort <option> [desc]     sorts books by title, author, year or rating"<<endl
            <<"books info <isbn_value>        shows information for a book"<<endl
            <<"books add                      adds a book in the system"<<endl
            <<"books remove                   removes a book from the system"<<endl
            <<"users add                      adds a user in the system"<<endl
            <<"users remove                   removes a user from the system "<<endl;
        cout<<endl;
}
//Влизане на потребител в системата.
void login()//9
{ 
    string t,n,p; // t - помощна, n - за име, p - за парола
    bool a;
    if (Param=="") //Ако няма въведен парамтър(Param), се въвежда потребителско име
    {
        cout<<"Username: ";
        getline(cin,t);
    }
    else t=Param; // Иначе потребителското име = Param
    t=Tools::trim(t);
    if (user==t) //При повторен опит за login
    {
        cout<<"You are already logged in.\n";
        return;
    }
    user=t;
    cout<<"Password: ";
    t=Tools::getPassword();
    cout<<endl;
    //Проверка за валидно потребителско име и парола
    ifstream f("users.txt");
    if (!f)
    {
        cout<<"Invalid username or password\n"; 
        user="";
        isAdmin=false;
        return;
    }

    while (!f.eof())
    {
        getline(f,n);
        getline(f,p);
        f>>a;
        f.ignore();
        if (f.eof()) break;
        if (n==user && p==t) //Намира регистриран потребител
        {
            isAdmin=a;
            cout<<"Welcome, "<<user<<"!\n";
            return;
        }
    }
    cout<<"Invalid username or password\n";
    user="";
    isAdmin=false;
}
//Напускане на потребител от системата
void logout(){ //10
 user="";
 isAdmin=false;
}
//Зарежда съдържанието на даден файл. 
//Ако такъв не съществува, се създава нов с празно съдържание.
void open()//11
{ 
    if(Param.substr(Param.size()-4)!=".txt")
       Param.insert(Param.size(),".txt"); // Ако се въведе име на файл без текстово разширение, се добавя такова
    currentFile=Param;
    ifstream f(Param);
    if (!f.good())
    {
        ofstream of(Param);
        of.close();
        return;
    }
    Book b;
    f>>b;
    while(f.good()) // Вмъкване на информацията от файла с книги във вектора от книги
    { 
        books.push_back(b);
        f>>b;
    }
    f.close();
}
//Записва направените промени в текущия файл
void save() //12
{ 
    ofstream f(currentFile);
    if(!f){
            f.close();
            return;
    }
    for (unsigned i=0; i<books.size(); i++){
         f<<books[i];
    }
    f.close();   
}
//Записва направените промени в нов файл с име, избрано от потребителя
void saveas()//13
{ 
    if(Param.substr(Param.size()-4)!=".txt")
       Param.insert(Param.size(),".txt"); // Ако се въведе име на файл без текстово разширение, се добавя такова
    ofstream f(Param);
    if(!f)
    {
        f.close();
        return;
    }
    for (unsigned i=0; i<books.size(); i++){
         f<<books[i];
    }
    f.close();
 }
//Добавяне на потребител
void users_add()//14
{ 
    if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return; //Ако в системата не е влязъл администратор, операцията не се изпълнява
    }
    string name,pass,uName,uPass; 
    bool admin, uAdmin;
    if (Param=="")
    {
        cout<<"Username: ";
        getline(cin,uName);
    }
    else 
        uName=Param;
    uName=Tools::trim(uName);
    cout<<"Password: ";
    uPass=Tools::getPassword();
    cout<<endl<<"Is admin? (0-false): ";
    cin>>uAdmin;
    cin.ignore();
    ifstream addU("users.txt");
    if (!addU.good())
    {
        cout<<"The file can not be opened or created."<<endl;
        return;
    }
    //Проверка за заето потребителско име
    while (!addU.eof())
    {
        getline(addU,name);
        getline(addU,pass);
        addU>>admin;
        addU.ignore();
        if (addU.eof()) 
        {
            break;
        }
        if (name==uName) // Намира потребител с такова потребителско име
        {
            cout<<"A user with this username already exists!\n";
            return;
        }
    }
    addU.close();
    ofstream add("users.txt",ios::app);
    add<<uName<<endl<<uPass<<endl<<uAdmin<<endl; //Добавя потребител с потребителско име uName и парола uPass във файла с потребители
    add.close();
    cout<<"Added\n";
 
}
//Премахване на потребител
void users_remove()//15
{ 
     if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return; //Ако в системата не е влязъл администратор, командата не се изпълнява
    }
    string name,pass,uName,uPass;
    bool admin,uAdmin;
    if (Param=="")
    {
        cout<<"Username: ";
        getline(cin,uName);
    }
    else 
        uName=Param;
    uName=Tools::trim(uName);
    cout<<"Password: ";
    uPass=Tools::getPassword();
    cout<<endl;
    ofstream temp("temp.txt",ios::app); // Създаване на временен файл, в който да се запишат всички потребители,
                                        // освен този, който администраторът иска да премахне
    if(!temp) 
    {
        cout<<"The file can't be created."<<endl;
        return;
    } 
    ifstream users("users.txt");
    if(!users)
    {
        cout<<"The file can't be opened or created."<<endl;
        return;
    }
    temp.clear();
    //Презаписване на потребителите във временния файл
    while (!users.eof())
    {
        getline(users,name);
        getline(users,pass);
        users>>admin;
        users.ignore();
        if (users.eof()) 
            break;
        if (name!=uName || pass!=uPass)
        {
            temp<<name<<endl<<pass<<endl<<admin<<endl;
        }
    }
    temp.close();
    users.close();
    remove("users.txt");
    rename("temp.txt","users.txt");

}
//За регистриране на първия администратор.
void firstAdmin()
{
   ofstream f("users.txt");
   if (!f.good()) return;
   bool a=true;
   f<<"admin"<<endl<<"i<3c++"<<endl<<a<<endl;
   f.close();

}
int main()
{
   firstAdmin();
    //Основен цикъл
 string cmd;
  do
  {getline(cin,cmd);//Четем входния ред
   cmd=Tools::trim(cmd);//Премахваме водещи и крайни "празни" символи
   mNo=getCmdAndParam(cmd);//Намираме номера на командата
   if (mNo>=0)  //Ако е двйствителна ...
   {menuNo[mNo]();//... изпълняваме я...
    cout<<"Done\n";//... и отразяваме, че е изпълнена.
   }
   else cout<<"Unknown command. Type \"help\" to show all commands.\n";
   if (mNo==7) break;//exit
  }while (true);
  return 0;
}
