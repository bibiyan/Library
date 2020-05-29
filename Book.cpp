#include <iostream>
#include "Book.h"
using namespace std;
//Реализация на методите на клас Book
    Book::Book(Book const &other){
           author=other.author;
                title=other.title;
                genre=other.genre;
                description=other.description;
                year=other.year;
                keyWords=other.keyWords;
                rating=other.rating;
                isbn=other.isbn;
        }
    Book::Book(const string& _author, const string& _title, const string& _genre, 
            const string& _description, int _year, const string& _keyWords,
            double _rating, const string& _isbn)
        {
               setBook(_author, _title, _genre, _description, _year, _keyWords, _rating, _isbn);
        }

    Book &Book::operator = (Book const& other)
        {
            if (this!=&other){
               // copy(other);
               author=other.author;
                title=other.title;
                genre=other.genre;
                description=other.description;
                year=other.year;
                keyWords=other.keyWords;
                rating=other.rating;
                isbn=other.isbn;
            }        
            return *this;
        }

    void Book::printAllInf() const 
        {
        cout<<"Author: "<<getAuthor()<<endl;
        cout<<"Title: "<<getTitle()<<endl;
        cout<<"Genre: "<<getGenre()<<endl;
        cout<<"Description: "<<getDescription()<<endl;
        cout<<"Year: "<<getYear()<<endl;
        cout<<"Key words: "<<getKeyWords()<<endl;
        cout<<"Rating: "<<getRating()<<endl;
        cout<<"ISBN: "<<getIsbn()<<endl;
        
        }
    void Book::print() const 
        {
            cout<<getTitle()<<" "<<getAuthor()<<" "<<getGenre()<<" "<<getIsbn()<<endl;
        }
    void Book::setBook(const string& _author, const string& _title, const string& _genre,
                     const string& _description, int _year, const string& _keyWords, 
                     double _rating, const string& _isbn)
        {
            setAuthor(_author);
            setTitle(_title);
            setGenre(_genre);
            setDescription(_description);
            setYear(_year);
            setKeyWords(_keyWords);
            setRating(_rating);
            setIsbn();
        }
    string Book::setRandIsbn()
    {
        string a;
        srand(time(NULL)); // За генериране всеки път различно число
        char symbol[10]={'0','1','2','3','4','5','6','7','8','9'};
        int i;
        for ( i=0; i<5; i++)
        {
            a.push_back(symbol[rand()%10]);
        }
        return a;
    }
    void Book::getData(istream &in){
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
            cout<<"Description: ";
            getline(in,s);
            setDescription(s);
            cout<<"Year: "; 
            in>>i;
            setYear(i);
            in.ignore();
            cout<<"Key words: "; 
            getline(in,s);
            setKeyWords(s);
            do{
                cout<<"Rating (0-10): ";
                in>>d;
            }while(d<0||d>10);
            setRating(d);
            in.ignore();
           setIsbn();
    }
    istream& operator>>(istream& in, Book& other){
         getline(in, other.author);
         getline(in,other.title);
         getline(in,other.genre);
         getline(in,other.description);
         in>>other.year;
         in.ignore();
         getline(in,other.keyWords);
         in>>other.rating;
         in.ignore();
         getline(in,other.isbn);
       
         return in;
    }

    ostream& operator<<(ostream& out, const Book& other){
         out<<other.author<<endl
            <<other.title<<endl
            <<other.genre<<endl
            <<other.description<<endl
            <<other.year<<endl
            <<other.keyWords<<endl
            <<other.rating<<endl
            <<other.isbn<<endl;
        return out;
    }
bool Book::cmpTitle( Book &a, Book &b)
{
 return (a.getAuthor()<b.getAuthor());
}
bool Book::cmpTitleDesc( Book &a, Book &b)
{
 return (a.getAuthor()>b.getAuthor());
}

bool Book::cmpAuthor( Book &a, Book &b)
{
 return (a.getAuthor()<b.getAuthor());
}
bool Book::cmpAuthorDesc( Book &a, Book &b)
{
 return (a.getAuthor()>b.getAuthor());
}

bool Book::cmpYear( Book &a, Book &b)
{
 return (a.getYear()<b.getYear());
}
bool Book::cmpYearDesc( Book &a, Book &b)
{
 return (a.getYear()>b.getYear());
}

bool Book::cmpRating( Book &a, Book &b)
{
 return (a.getRating()<b.getRating());
}
bool Book::cmpRatingDesc( Book &a, Book &b)
{
 return (a.getRating()>b.getRating());
}
