The current project implements a program, written in C++, that is a book library management system project. It executes various operations, depending on whether there is a correctly logged in user and whether he is an administrator or not. Users have access to all books in the library. They can search for a particular book and sort books by different criteria. Administrators have the ability to add and delete books from the system, as well as register and remove users.

Compilation

c++ Book.cpp main.cpp -o main.exe

./main.exe

Input: open books.txt

Input: login

Username: admin

Password: ******

Welcome, admin!

Input: books add

Add a book:

Author: John Steinbeck

Title: East of Eden

Genre: Novel 

Description: Adam Trask came to California from the East to farm and raise his family on the new rich land. But the birth of his twins, Cal and Aaron, brings his wife to the brink of madness, and Adam is left alone to raise his boys to manhood. One boy thrives nurtured by the love of all those around him; the other grows up in loneliness enveloped by a mysterious darkness.

Year: 1952

Key words: farm love

Rating (0-10): 7.9

Input: books add

Add a book:

Author: Karl May

Title: Winnetou

Genre: Western

Description: Winnetou is the story of a young Apache chief told by his white 
friend and blood-brother Old Shatterhand. The action takes place in the U.S. 
Southwest, in the latter half of the 1800s, where the Indian way of life is threatened by the first transcontinental railroad. Winnetou, the only Native Indian chief who could have united the various rival tribes to reach a settlement with the whites, is murdered. His tragic death foreshadows the death of his people. May's central theme here, as in much of his work, is the relationship between aggression, racism, and religious intolerance.

Year: 1892

Key words: indians adventure

Rating (0-10): 8.8

Input: users add

Username: yana

Password: *****

Is admin? (0-false): 0

Added

Input: books sort title

East of Eden John Steinbeck Novel 53107

Winnetou Karl May Western 58788

Input: close

Input: logout

Input: exit
