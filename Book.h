#ifndef _BOOK_H_
#define _BOOK_H_
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
class Book{
    private:
        string author; // Автор
        string title; // Заглавие
        string genre; // Жанр
        string description; // Описание
        int year; // Година
        string keyWords; // Ключови думи
        double rating; // Рейтинг (0-10)
        string isbn; // Уникален номер      
    public:
    Book():year(0), rating(0.00){} // Конструктор по подразбиране
    Book(Book const &other); // Копи-конструктор
    Book(const string& _author, const string& _title, const string& _genre, 
            const string& _description, int _year, const string& _keyWords,
            double _rating, const string& _isbn); //Конструктор с параметри
    Book &operator = (Book const& other); // Предефиниране на оператор "="
    void printAllInf() const; // Извежда цялата информация за дадена книга
    void print() const; // Извежда заглавие, автор, жанр и уникален номер
    void setBook(const string& _author, const string& _title, const string& _genre,
                     const string& _description, int _year, const string& _keyWords, 
                     double _rating, const string& _isbn); // Създава книга
    // Set- функции
    void setAuthor(const string& _author){author=_author;}
    void setTitle(const string& _title){title=_title;}
    void setGenre(const string& _genre){genre=_genre;}
    void setDescription(const string& _description){description=_description;}
    void setYear(int _year){year=_year;}
    void setKeyWords(const string& _keyWords){keyWords=_keyWords;}
    void setRating(double _rating){rating=_rating;}
    void setIsbn(){
        isbn=setRandIsbn();}

    string setRandIsbn(); // Връща случайно генериран номер
    //Get - функции
    string getAuthor()const {return author;}
    string getTitle()const {return title;}
    string getGenre()const {return genre;}
    string getDescription()const {return description;}
    int getYear()const {return year;}
    string getKeyWords()const {return keyWords;}
    double getRating()const {return rating;}
    string getIsbn()const {return isbn;}
    void getData(istream &in); // За вход от клавиатура с подсказки         
    friend istream& operator>>(istream& in, Book& other); // Предефиниран поток за вход">>" (удобен за достъп до файл)
    friend ostream& operator<<(ostream& out, const Book& other); // Предефиниран поток за изход "<<" 
// Булеви функции, необходими за сортирането на книги по заглавие, автор, година и рейтинг
static bool cmpTitle( Book &a, Book &b);
static bool cmpTitleDesc( Book &a, Book &b);

static bool cmpAuthor( Book &a, Book &b);
static bool cmpAuthorDesc( Book &a, Book &b);

static bool cmpYear( Book &a, Book &b);
static bool cmpYearDesc( Book &a, Book &b);

static bool cmpRating( Book &a, Book &b);
static bool cmpRatingDesc( Book &a, Book &b);
};


#endif