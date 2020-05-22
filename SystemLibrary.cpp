#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdio> //rename
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
using namespace std;

class Book{
    private:
        string author;
        string title;
        string genre;
        string discription;
        int year;
        string keyWords;
        double rating;
        string isbn;
          /*  void copy(Book const& other)
            {
                author=other.author;
                title=other.title;
                genre=other.genre;
                discription=other.discription;
                year=other.year;
                keyWords=other.keyWords;
                rating=other.rating;
                isbn=other.isbn;

            }*/
        
    public:
        Book():year(0), rating(0.00){}

        Book(Book const &other){
           // copy(other);
           author=other.author;
                title=other.title;
                genre=other.genre;
                discription=other.discription;
                year=other.year;
                keyWords=other.keyWords;
                rating=other.rating;
                isbn=other.isbn;
        }
        Book(const string& _author, const string& _title, const string& _genre, 
            const string& _discription, int _year, const string& _keyWords,
            double _rating, const string& _isbn)
        {
               setBook(_author, _title, _genre, _discription, _year, _keyWords, _rating, _isbn);
        }

        Book &operator = (Book const& other)
        {
            if (this!=&other){
               // copy(other);
               author=other.author;
                title=other.title;
                genre=other.genre;
                discription=other.discription;
                year=other.year;
                keyWords=other.keyWords;
                rating=other.rating;
                isbn=other.isbn;
            }        
            return *this;
        }

        void printAllInf() const 
        {
        cout<<"Author: "<<getAuthor()<<endl;
        cout<<"Title: "<<getTitle()<<endl;
        cout<<"Genre: "<<getGenre()<<endl;
        cout<<"Discription "<<getDiscription()<<endl;
        cout<<"Year: "<<getYear()<<endl;
        cout<<"Key words: "<<getKeyWords()<<endl;
        cout<<"Rating: "<<getRating()<<endl;
        cout<<"ISBN: "<<getIsbn()<<endl;
        
        }
        void print() const 
        {
            cout<<getTitle()<<" "<<getAuthor()<<" "<<getGenre()<<" "<<getIsbn()<<endl;
        }
        void setBook(const string& _author, const string& _title, const string& _genre,
                     const string& _discription, int _year, const string& _keyWords, 
                     double _rating, const string& _isbn)
        {
                setAuthor(_author);
                setTitle(_title);
                setGenre(_genre);
                setDiscription(_discription);
                setYear(_year);
                setKeyWords(_keyWords);
                setRating(_rating);
                setIsbn(_isbn);
        }

        void setAuthor(const string& _author){author=_author;}
        void setTitle(const string& _title){title=_title;}
        void setGenre(const string& _genre){genre=_genre;}
        void setDiscription(const string& _discription){discription=_discription;}
        void setYear(int _year){year=_year;}
        void setKeyWords(const string& _keyWords){keyWords=_keyWords;}
        void setRating(double _rating){rating=_rating;}
        void setIsbn(const string& _isbn){isbn=_isbn;}

        string getAuthor()const {return author;}
        string getTitle()const {return title;}
        string getGenre()const {return genre;}
        string getDiscription()const {return discription;}
        int getYear()const {return year;}
        string getKeyWords()const {return keyWords;}
        double getRating()const {return rating;}
        string getIsbn()const {return isbn;}
     
        void getData(istream &in){
        string s;int i;double d;
        cout<<"Author: ";
        getline(in,s); 
        setAuthor(s);
        cout<<"Title: ";
        getline(in,s);
        setTitle(s);
        cout<<"Genre: ";
        getline(in,s);
        setGenre(s);
        cout<<"Discription: ";
        getline(in,s);
        setDiscription(s);
        cout<<"Year: "; 
        in>>i;
        setYear(i);
        in.ignore();
        cout<<"Key words: "; 
        getline(in,s);
        setKeyWords(s);
        cout<<"Rating: ";
        in>>d;
        setRating(d);
        in.ignore();
        cout<<"ISBN: ";
        getline(in,s);
        setIsbn(s);
       
        }
     friend istream& operator>>(istream& in, Book& other){
         getline(in, other.author);
         getline(in,other.title);
         getline(in,other.genre);
         getline(in,other.discription);
         in>>other.year;
         in.ignore();
         getline(in,other.keyWords);
         in>>other.rating;
         in.ignore();
         getline(in,other.isbn);
       
        return in;
        }

      /* ostream& operator<<(ostream& out, const Book& other){
             out<<other.author<<endl
                <<other.title<<endl
                <<other.genre<<endl
                <<other.discription<<endl
                <<other.year<<endl
                <<other.keyWords<<endl
                <<other.rating<<endl
                <<other.isbn<<endl;
        return out;
        }*/
};
ostream& operator<<(ostream& out, const Book& book){
         out<<book.getAuthor()<<endl
            <<book.getTitle()<<endl
            <<book.getGenre()<<endl
            <<book.getDiscription()<<endl
            <<book.getYear()<<endl
            <<book.getKeyWords()<<endl
            <<book.getRating()<<endl
            <<book.getIsbn()<<endl;
        return out;
        }

//Прототипи
void books_add();void books_all();void books_find();void books_remove();
void books_sort();void books_view();void close();void exit();void help();
void login();void logout();void open();void save();void saveas();
void users_add();void users_remove();
//Масив от функции
void (*menuNo[16])(void)={books_add,books_all,books_find,books_remove,
                          books_sort,books_view,close,exit,help,login,
                          logout,open,save,saveas,users_add,users_remove};
//Команда
struct Command
{ string menuItem;
  bool logon,adm;
  bool operator <(const Command &c) const
  {return menuItem<c.menuItem;}
  bool operator ==(const Command &c) const
  {return menuItem==c.menuItem;}
};
ostream &operator <<(ostream &os,const Command &c)
{return os<<c.menuItem;}
//Команди, подредени по азбучен ред
Command menu[16]=
{{"books add",true,true}, {"books all",true,false}, {"books find",true,false},
 {"books remove",true,true}, {"books sort",true,false}, {"books view",true,false},
 {"close",false,false}, {"exit",false,false}, {"help",false,false},
 {"login",false,false}, {"logout",true,false}, {"open",false,false},
 {"save",false,false}, {"saveas",false,false}, {"users add",true,true},
 {"users remove",true,true}};

struct User{
    string UserName, UserPassword;
    bool isUserAdmin;
    bool operator ==(const User &u) const
  {return (UserName == u.UserName && UserPassword == u.UserPassword && isUserAdmin == u.isUserAdmin);}
};
ostream& operator<<(ostream& os,const User& other){
             os<<other.UserName<<endl
                <<other.UserPassword<<endl
                <<other.isUserAdmin<<endl;
        return os;
    }
istream& operator>>(istream& in, User& other){
        in>>other.UserName>>other.UserPassword>>other.isUserAdmin;
        return in;
    }

//ГЛОБАЛИ
 int mNo=-1;//Номер на изпълняваната подпрограма
 string user;//Име на текущия потребител
 bool isAdmin=false;//Дали текущият потребител е администратор
 string Param;//Подадени параметри
vector<Book> books; // Вектор от книги
string currentFile; // времемен файл

string trim(string s)
{const char t[8] = " \t\n\r\f\v";
 s.erase(0, s.find_first_not_of(t));
 s.erase(s.find_last_not_of(t) + 1);
 return s;
}
int getCmdNo(string s)
{//двоично търсене в масива menu
  int l=0,r=15,m;
  Command t;
  t.menuItem = s;
  do
  { m=(l+r)>>1; 
    if (t==menu[m]) break;
    if (t<menu[m]) r=r-1;
    else l=l+1;
  } while (l<=r);
  if (l<=r) return m;
  return -1;
}
//Намира номера на командата и параметрите в глобалата Param
int getCmdAndParam(string s)
{int n,p,p1;
 string s1;
 n=getCmdNo(s);
 if (n>=0){Param="";return n;}
 p=s.find_first_of(" \t");
 if (p==string::npos) {Param="";return -1;}
 s1=trim(s.substr(p+1));
 p1=s1.find_first_of(" \t");
 if (p1==string::npos) 
 {
  Param=s1;
  return getCmdNo(s.substr(0,p));
 }
 n=getCmdNo(s.substr(0,p)+" "+s1.substr(0,p1));
 if (n>=0){Param=trim(s1.substr(p1+1));
  return n;
 }
 Param=s1;
 return getCmdNo(s.substr(0,p));
}
//Изчакване на клавиш без визуализиране
int getch(void)
{int r;
 cout << flush;
 r = _getch();
 
 HANDLE hCon = GetStdHandle(STD_INPUT_HANDLE);
 FlushConsoleInputBuffer(hCon);
 return r;
}
//Въвеждане на парола от клавиатурата
string getPassword()
{string s="";
 char c;
 do
 {c=getch();
  switch (c)
  {case 13: return s;
   case '\b':if (s.length()>0) {s.erase(s.length()-1,1);
                                cout<<"\b \b";
                                break;
                               }
   case 27:{for (int i=0;i<s.length();i++)cout<<"\b \b";
            s="";
            break;
           }
   default: if (c>=' ' && c<='z') {s+=c;cout<<'*';}
  }
 } while (true);
}

//Реализации на подпрограмите
// При влизане във всяка от долните функции, глобалите съдържат:
//  mNo - Номера на изпълняваната подпрограма
//  user - Името на текущия потребител (празе низ, ако е анониммен)
//  isAdmin - Дали текущият потребител е администратор (анонимният не е)
//  Param -Подадени параметри: низът, който се намира след разпознатата команда

void books_add(){//0
    if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return;
    }
    cout<<"Add a book:"<<endl;
       // cout<<"Author, Title, Genre, Discription, Year, Key words, Rating, ISBN: "<<endl;
        Book bNext;
        bNext.getData(cin);
        books.push_back(bNext);
} 
void books_all(){//1
    if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return;
    }
     for (unsigned i=0;i<books.size();i++)
        {
            books[i].print();
            cout<<endl;
        }
    
} 
void books_find(){ //2
  if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return;
    }
    string findBy, findWhat;
    findBy=Param.substr(0,Param.find_first_of(" ")); // критерий за търсене (title, author, discription)
    findWhat=Param.substr(Param.find_first_of(" ")+1);
    if (findBy=="author"){
        for(int i=0;i<books.size();i++)
        if ((books[i].getAuthor()).compare(findWhat)==0)
        {
            books[i].printAllInf();
            cout<<endl;
        }
        cout<<endl;
    }
    if (findBy=="title"){
         for(int i=0;i<books.size();i++)
        if ((books[i].getTitle()).compare(findWhat)==0)
        {
            books[i].printAllInf();
            cout<<endl;
        }
        cout<<endl;
    }
    if (findBy=="discription")
    {
        for(int i=0;i<books.size();i++)
        if ((books[i].getDiscription()).compare(findWhat)==0)
        {
            books[i].printAllInf();
            cout<<endl;
        }
        cout<<endl;
    }
}
void books_remove(){ //3
if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return;
    }
    for(int i=0;i<books.size();i++)
            if ((books[i].getIsbn()).compare(Param)==0)
            {
                books.erase(books.begin()+i);
            }

}
bool cmpTitle( Book &a, Book &b){
 return (a.getAuthor()<b.getAuthor());
}
bool cmpTitleDesc( Book &a, Book &b){
 return (a.getAuthor()>b.getAuthor());
}

bool cmpAuthor( Book &a, Book &b){
 return (a.getAuthor()<b.getAuthor());
}
bool cmpAuthorDesc( Book &a, Book &b){
 return (a.getAuthor()>b.getAuthor());
}

bool cmpYear( Book &a, Book &b){
 return (a.getYear()<b.getYear());
}
bool cmpYearDesc( Book &a, Book &b){
 return (a.getYear()>b.getYear());
}

bool cmpRating( Book &a, Book &b){
 return (a.getRating()<b.getRating());
}
bool cmpRatingDesc( Book &a, Book &b){
 return (a.getRating()>b.getRating());
}

void books_sort(){ //4
    if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return;
    }
    string sortBy,helper,firstP, secondP;
    firstP=Param.substr(0,Param.find_first_of(" \t")); // първа дума на Param
    helper=Param.substr(Param.find_first_of(" \t")+1); // от втората дума на Param
    secondP=helper.substr(0,helper.find_first_of(" \t")); // втора дума на Param
    cout<<"firstP: "<<firstP<<endl<<"secondP: "<<secondP<<endl;
    int k;
    if(firstP=="title" && secondP!="desc") k=0;
    if(firstP=="title" && secondP=="desc") k=1;
    if(firstP=="author" && secondP!="desc") k=2;
    if(firstP=="author" && secondP=="desc") k=3;
    if(firstP=="year" && secondP!="desc") k=4;
    if(firstP=="year" && secondP=="desc") k=5;
    if(firstP=="rating" && secondP!="desc") k=6;
    if(firstP=="rating" && secondP=="desc") k=7;

    switch(k){
        case 0:{sort(books.begin(),books.end(),cmpTitle); break;}
        case 1:{sort(books.begin(),books.end(),cmpTitleDesc); break;}
        case 2:{sort(books.begin(),books.end(),cmpAuthor); break;}
        case 3:{sort(books.begin(),books.end(),cmpAuthorDesc); break;}
        case 4:{sort(books.begin(),books.end(),cmpYear); break;}
        case 5:{sort(books.begin(),books.end(),cmpYearDesc); break;}
        case 6:{sort(books.begin(),books.end(),cmpRating); break;}
        case 7:{sort(books.begin(),books.end(),cmpRatingDesc); break;}
        default: break; 
    }
    books_all();
}
void books_view(){ //5
 if(user=="")
    {
        cout<<"You are not logged."<<endl;
        return;
    }
     for(int i=0;i<books.size();i++)
        if ((books[i].getIsbn()).compare(Param)==0)
        {
            books[i].printAllInf();
            cout<<endl;
        }
}
void close(){ //6
    books.clear();
}
void exit(){ //7
  //Командата няма параметри
  if (Param!="") {cout<<"Invalid parameter\n";mNo=-1;}
}
void help(){ //8
  /*cout<<"Commands available:\n";
  for (int i=0;i<16;i++) 
  {cout<<menu[i];
   if (i<15) cout<<", ";
  }
  cout<<endl;*/
  cout<<"The following commands are supported:"<<endl;
        cout<<"open <file>	     opens <file>"<<endl
            <<"close             closes currently opened file"<<endl
            <<"save              saves the currently open file"<<endl
            <<"saveas <file>     saves the currently open file in <file>"<<endl
            <<"help              prints this information"<<endl
            <<"login             logs in the system"<<endl
            <<"logout            logs out of the system"<<endl
            <<"exit              exists the program"<<endl
            <<"books all         shows all books"<<endl
            <<"books find        searches a book "<<endl
            <<"books sort        sorts books by title, author, year or rating"<<endl
            <<"books info        shows information for a book"<<endl
            <<"books add         adds a book in the system"<<endl
            <<"books remove      removes a book from the system"<<endl
            <<"users add         adds a user in the system"<<endl
            <<"users remove      removes a user from the system "<<endl;
        cout<<endl;
}

void login(){ //9
 string t,n,p; 
 bool a;
 if (Param=="")
 {cout<<"Username: ";
  getline(cin,t);
 }
 else t=Param;
 t=trim(t);
 if (user==t)
 {
   cout<<"You are already logged in.\n";
   return;
 }
 user=t;
 cout<<"Password: ";
 t=getPassword();
 cout<<endl;
 ifstream f("users.txt");
 if (!f) {cout<<"Invalid username or password\n"; 
          user="";
          isAdmin=false;
          return;
         }
 while (!f.eof())
 {getline(f,n);
  getline(f,p);
  f>>a;
  f.ignore();
  if (f.eof()) break;
  if (n==user && p==t)
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
void logout(){ //10
 user="";
 isAdmin=false;
}
void open(){ //11
if(Param.substr(Param.size()-4)!=".txt")
        Param.insert(Param.size(),".txt");
        currentFile=Param;
     ifstream f(Param);
        if (!f.good()){
            ofstream of(Param);
            of.close();
            f.close();
            return;
        }
    
    Book b;
    f>>b;
    while(f.good()){ 
        books.push_back(b);
      f>>b; 
    }
    f.close();
}
void save(){ //12
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
void saveas(){ //13
if(Param.substr(Param.size()-4)!=".txt")
        Param.insert(Param.size(),".txt");
    ofstream f(Param);
    if(!f){
            f.close();
            return;
    }
    for (unsigned i=0; i<books.size(); i++){
         f<<books[i];
    }
    f.close();
 }
       


void users_add(){ //14
    if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return;
    }

string n,p,un,up; 
 bool a, ua;
 if (Param=="")
 {cout<<"Username: ";
  getline(cin,un);
 }
 else un=Param;
 un=trim(un);
 cout<<"Password: ";
 up=getPassword();
 cout<<endl<<"Is admin? (0-false): ";
 cin>>ua;
 cin.ignore();
 ifstream addU("users.txt");
    if (!addU.good()){
        cout<<"The file can not be opened or created."<<endl;
        return;
    }
 while (!addU.eof())
 {
 getline(addU,n);
 getline(addU,p);
 addU>>a;
 addU.ignore();
  if (addU.eof()) {
      break;}
  if (n==un)
  {
    cout<<"A user with this username already exists!\n";
    return;
  }
 }
 addU.close();
 ofstream add("users.txt",ios::app);
 add<<un<<endl<<up<<endl<<ua<<endl;
 add.close();
 cout<<"Added\n";
 
}
void users_remove(){ //15
     if(!isAdmin)
    {
        cout<<"You are not admin."<<endl;
        return;
    }
    string n,p,un,up;
 bool a,ua;
 if (Param=="")
 {cout<<"Username: ";
  getline(cin,un);
 }
 else un=Param;
 un=trim(un);
 cout<<"Password: ";
 up=getPassword();
cout<<endl;
    ofstream temp("temp.txt",ios::app);
    if(!temp) {
        cout<<"The file can't be created."<<endl;
        return;
     } 
    ifstream users("users.txt");
    if(!users){
        cout<<"The file can't be opened or created."<<endl;
        return;
    }
    temp.clear();
while (!users.eof())
 {getline(users,n);
  getline(users,p);
  users>>a;
  users.ignore();
  if (users.eof()) break;
  if (n!=un || p!=up)
  {
    temp<<n<<endl<<p<<endl<<a<<endl;
  }
 }
 temp.close();
 users.close();
 remove("users.txt");
 rename("temp.txt","users.txt");

}
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
  {getline(cin,cmd);
   cmd=trim(cmd);
   mNo=getCmdAndParam(cmd);
   if (mNo>=0)  
   {menuNo[mNo]();
    cout<<"Done\n";
   }
   else cout<<"Unknown command. Type \"help\" to show all commands.\n";
   if (mNo==7) break;
  }while (true);
  return 0;
}
