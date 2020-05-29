#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;
//Инструменти
//Премахване на водещи и крайни "празни" символи
namespace Tools{
string trim(string s)
{const char t[8] = " \t\n\r\f\v";//интервал,табулатор,нов ред,надолу,нова страница,вертикален табулатор
 s.erase(0, s.find_first_not_of(t));
 s.erase(s.find_last_not_of(t) + 1);
 return s;
}
//Изчакване на клавиш без визуализиране
//Готова функция
int getch(void)
{int r;
 cout << flush;
 r = _getch();
 HANDLE hCon = GetStdHandle(STD_INPUT_HANDLE);
 FlushConsoleInputBuffer(hCon);
 return r;
}
//Въвеждане на парола от клавиатурата
//Функция, направена с помощ
string getPassword()
{string s="";
 char c;
 do
 {c=getch();
  switch (c)
  {case 13: return s;//Клавиш <Enter>
   //Клавиш <Backspace>
   case '\b':if (s.length()>0) {s.erase(s.length()-1,1);//Изтрива един символ от натрупаното
                                cout<<"\b \b";//Изтрива една звездичка
                                break;
                               }
   //Клавиш <Esc>
   case 27:{for (int i=0;i<s.length();i++)cout<<"\b \b";//Изтрива всички звездички
            s="";//Празен низ за парола
            break;
           }
   //Иначе го приема, само ако е в "нормалните" ASCII-граници
   //(не по-малко от интервал и не след z)
   default: if (c>=' ' && c<='z') {s+=c;cout<<'*';}
  }
 } while (true);
}
};