/*
 * Problem Statement :-
 * Consider telephone book database of N clients.
 * Make use of a hash table implementation to
 * quickly look up client‘s telephone number.
 * Using Chaining.
 */

/*
 * Created by Devashish Katoriya on 08-04-2017
 */

#include <iostream>
#include <cstring>

using namespace std;

#define MAX 10

//Various Functions
int getInt()                            //A function which only accepts Integer values and handles error if the input is not of type int.
{
    int x;
m1: if(!(cin >> x))
    {
        cin.clear();            //clear the current input buffer
        cin.ignore(99999, '\n');    //ignore the next entered values
        cout<<"\nInvalid Input!";
        cout<<"\nPlease try again :- ";
        goto m1;                //re-ask to enter new value
    }
    return x;
}

//Class Definitions
class Entry                                                   //Book Class
{
public :
    Entry()
    {
        chain = -1;
    }
    char name[MAX];
    long telephone_no;
    int chain;
};

class HashTable                                             //Hash Table Class
{
    Entry ht[MAX];
    void insert(Entry);
    void insertQ(Entry);
    inline int HashFunc(char []);
public :
    HashTable()
    {
        for(int i=0;i<MAX;i++)
        {
            strcpy(ht[i].name,"");
            ht[i].telephone_no = 0;
        }
    }
    bool isFull()
    {
        for(int i=0;i<MAX;i++)
        {
            if(ht[i].telephone_no==0)
            {
                return false;
            }
        }
        return true;
    }
    void clr()
    {
        for(int i=0;i<MAX;i++)
        {
            strcpy(ht[i].name,"");
            ht[i].telephone_no = 0;
        }
    }
    void construct();
    void display();
    void search();
    void delete_value();
};

void HashTable::construct()                                   //Function for Insertion
{
    if(isFull())
    {
        cout<<"\nSorry, the Telephone Directory is Full.";
        return;
    }
    
    int ch;
    cout<<"\n\n 1 for Linear Hashing.";
    cout<<"\n 2 for Quadratic Hashing.";
    cout<<"\nEnter which Hashing Technique to use ? ";
    ch = getInt();
    if(ch==1)
    {
        Entry B;
        cout<<"\nEnter Record Details :- ";
        cout<<"\nEnter Name \t: ";
        cin>>B.name;
        cout<<"Enter Ph.No.\t: ";
        B.telephone_no = getInt();
        insert(B);
    }
    else if(ch==2)
    {
        Entry B;
        cout<<"\nEnter Record Details :- ";
        cout<<"\nEnter Name \t: ";
        cin>>B.name;
        cout<<"Enter Ph.No.\t: ";
        B.telephone_no = getInt();
        insertQ(B);
    }
    else
        cout<<"\nInvalid Option!";
}

void HashTable::insert(Entry B)                                 //Insertion using Linear Probing
{
    int pos;
    pos = HashFunc(B.name);
    if(ht[pos].telephone_no==0)
    {
        ht[pos] = B;
    }
    else
    {
        int current,previous;
        bool original;
    
        previous = pos;
        do
        {
            current = (previous+1)%MAX;
            original = (current==HashFunc(ht[current].name));
            if(!original)
            {
                if(ht[current].telephone_no==0)
                {
                    ht[previous].chain = current;
                    ht[current] = B;
                    break;
                }
            }
            previous = current;
        }while(current!=pos);
    }
}

void HashTable::insertQ(Entry B)                               //Insertion using Quadratic Probing
{
    int pos;
    pos = HashFunc(B.name);
    if(ht[pos].telephone_no==0)
    {
        ht[pos] = B;
    }
    else
    {
        int current,previous;
        bool original;
        
        previous = pos;
        for(int i=1; i<(MAX-1)/2; i++)
        {
            current = (pos+(i*i))%MAX;
            original = (current == HashFunc(ht[current].name));
            if(!original)
            {
                if (ht[current].telephone_no == 0)
                {
                    ht[previous].chain = current;
                    ht[current] = B;
                    break;
                }
                previous = current;
            }
        }
    }
}

int HashTable::HashFunc(char key[MAX])                             //Hash Function
{
    int i,first,middle,last,total;
    /*
    	We are using Fold-Shift
    	For eg. 9874512332
    	then First = 987
    		Middle = 451
    		  Last = 2332
    */
    first = middle = last = 0;
    
    for(i=0;i<3 && key[i]!='\0';i++)
        first = (first*10) + key[i];
    for(i=3;i<6 && key[i]!='\0';i++)
        middle = (middle*10) + key[i];
    for(i=6;key[i]!='\0';i++)
        last = (last*10) + key[i];
    
    total = first + middle + last;
    return total % MAX;
}

void HashTable::display()                                               //Display
{
    cout<<"\n\t\tTelephone Directory";
    cout<<"\n---------------------------------------------";
    cout<<"\nPos.\tName\t\tPh.No.\t\tChain";
    cout<<"\n---------------------------------------------";
    for(int i=0;i<MAX;i++)
    {
        cout<<"\n"<<i<<"\t"<<ht[i].name<<"\t\t"<<ht[i].telephone_no<<"\t\t"<<ht[i].chain;
    }
    cout<<"\n---------------------------------------------";
    cout<<"\nMAX is "<<MAX;
}

void HashTable::search()                                                //Searching using chaining
{
    char name[MAX];
    int pos;
    cout<<"\nEnter name to Search : ";
    cin>>name;
    pos = HashFunc(name);

    int i=pos;
    while(ht[i].chain!=-1)
    {
        if(strcmp(ht[i].name,name)==0)
        {
            cout << "\nName\t: " << ht[i].name;
            cout << "\nPh.No.\t: " << ht[i].telephone_no;
        }
        i = ht[i].chain;
    }
    if(strcmp(name,ht[i].name)==0)
    {
        cout << "\nName\t: " << ht[i].name;
        cout << "\nPh.No.\t: " << ht[i].telephone_no;
        return;
    }
    cout<<"\nRecord NOT found!";
    
}

void HashTable::delete_value()                                                 //Deletion using chaining
{
    char name[MAX];
    int pos;
    cout<<"\nEnter name to Delete : ";
    cin>>name;
    pos = HashFunc(name);

    int i=pos,prev,next;
    prev = pos;
    while(ht[i].chain!=-1)
    {
        next = ht[i].chain;
        if(strcmp(ht[i].name,name)==0)
        {
            strcpy(ht[i].name,ht[next].name);
            ht[i].telephone_no = ht[next].telephone_no;
        }
        prev = i;
        i = ht[i].chain;
    }
    if(strcmp(ht[i].name,name)==0)
    {
        ht[prev].chain = -1;
        strcpy(ht[i].name,"");
        ht[i].telephone_no = 0;
        cout<<"\nEntry Deleted Successfully!";
        return;
    }
    cout<<"\nRecord NOT found!";
    
}

//main()
int main()
{
    HashTable obj;
    char choice;
    int ch;
    cout<<"\nProgram to implement Telephone Directory using Hash Table.";
    do
    {
        choice = 'n';
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 to Insert new Record";
        cout<<"\n 2 to Display Telephone Directory";
        cout<<"\n 3 to Search a name";
        cout<<"\n 4 to Delete a entry";
        cout<<"\n 5 for IsFull";
        cout<<"\n -1 to Clear whole Directory";
        cout<<"\n  0 to Quit";
        cout<<"\nEnter your choice : ";
        ch = getInt();
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch) {
            case 1 :
                obj.construct();
                break;
            case 2 :
                obj.display();
                break;
            case 3 :
                obj.search();
                break;
            case 4 :
                obj.delete_value();
                break;
            case 5 :
                if(obj.isFull())
                    cout<<"\nYes, the Telephone Directory is Completely Full.";
                else
                    cout<<"\nNo, the Telephone Directory is Not full.";
                break;
            case -1 : cout<<"\nAre you sure you want to clear directory (y/n) ? ";
                cin>>choice;
                if(choice=='y'||choice=='Y')
                {
                    obj.clr();
                    cout<<"\nTelephone Directory Cleared Successfully!";
                }
                else
                    cout<<"\nCancelled!";
            case 0 : break;
            default : cout<<"\nInvalid Option!";
        }
        
        /*
        if(ch!=0)
        {
            cout<<"\n\n\n\n\n\n\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
        */
    }while(ch!=0);
    
    cout<<"\nThank you for using this program :) \n\n";
    return 0;
}

/* OUTPUT

Program to implement Telephone Directory using Hash Table.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


 1 for Linear Hashing.
 2 for Quadratic Hashing.
Enter which Hashing Technique to use ?1
 1

Enter Record Details :-
Enter Name      :d
 d
Enter Ph.No.    :1
 1


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


 1 for Linear Hashing.
 2 for Quadratic Hashing.
Enter which Hashing Technique to use ?1
 1

Enter Record Details :-
Enter Name      :d
 d
Enter Ph.No.    :2
 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :1
 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


 1 for Linear Hashing.
 2 for Quadratic Hashing.
Enter which Hashing Technique to use ?1
 1

Enter Record Details :-
Enter Name      :d
 d
Enter Ph.No.    :3
 3


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :2
 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                Telephone Directory
---------------------------------------------
Pos.    Name            Ph.No.          Chain
---------------------------------------------
0       d               1               1
1       d               2               2
2       d               3               -1
3                       0               -1
4                       0               -1
5                       0               -1
6                       0               -1
7                       0               -1
8                       0               -1
9                       0               -1
---------------------------------------------
MAX is 10

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :3
 3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Name to search :d
 d

Name    : d
Ph.No.  : 1
Name    : d
Ph.No.  : 2
Name    : d
Ph.No.  : 3

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :3
 3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enter Name to search :e
 e

Record NOT found!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 1 to Insert new Record
 2 to Display Telephone Directory
 3 to Search a name
 4 for IsFull
 -1 to Clear whole Directory
  0 to Quit
Enter your choice :0
 0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thank you for using this program :)

*/
