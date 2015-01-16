#include<cstring>
#include<string>
#include<iostream>

using namespace std;

string* search1(string*,string);
int searchString(string*,string);


//search1() FUNCTION ACCEPTS THE LIST OF WORDS AND A SEARCH-STRING AND RETURNS
//LIST OF WORDS IN WHICH SEARCH-STRING IS FOUND.
//EXAMPLE: IF WE GIVE OUR CALL AS string* s= search1(dictionary, "pre"); THEN
//THIS FUNCTION WILL RETURNS LIST OF WORDS STARTING WITH 'pre' FROM dictionary.

string* search1(string* wordlist, string s)
{
    string* list = new string[10000];
    int i=0;
    int j=99170;
    int mid=(i+j)/2;
    bool found=false;
    int index =-1;

    //BIINARY SEARCH ALGORITHM IS USED TO FIND A WORD IN DICTIONARY
    //WHICH STARTS WITH A GIVEN SEARCH-STRING. BUT THERE COULD BE
    //FEW MORE WORDS STARTING WITH SEARCH-STRING ABOVE AND BELOW
    //THE WORD WHERE INDEX POINTER HAS STOPPED IN BINARY SEARCH.

    while(!found && i<j)
    {
        mid = (i+j)/2;
        if(wordlist[mid].substr(0, s.size()) == s)
        {
            found=true;
            index=mid;
        }
        else if(wordlist[mid]>s)
        {
            j=mid-1;
        }
        else if(wordlist[mid]<s)
        {
            i=mid+1;
        }
    }
    if(index!=-1)
    {

        //ASSIGN SAME VALUE AS INDEX TO TWO MORE POINTERS P AND Q

        int p=index-1;
        int q=index+1;
        int k=1;
        list[0]=wordlist[index];

        //DECREMENT ONE POINTER TILL WE GET SEARCH-STRING AS STARTING SUBSTRING

        while(wordlist[p].substr(0, s.size()) == s && p>0)
        {
            list[k]=wordlist[p];
            k=k+1;
            p=p-1;
        }

        //INCREMENT OTHER POINTER TILL WE GET SEARCH-STRING AS STARTING SUBSTRING

        while(wordlist[q].substr(0, s.size()) == s&& q<99170)
        {
            list[k]=wordlist[q];
            k=k+1;
            q=q+1;
        }
    }
    return list;
}

//searchString() FUNCTION IS AN IMPLEMENTATION NORMAL BINARY SEARCH ALGORITHM.
//It will return index of a string in array if it is found else it will return -1.

int searchString(string* wordlist, string s)
{
    int i=0;
    int j=99170;
    int mid=(i+j)/2;
    bool found=false;
    int index =-1;
    while(!found && i<=j)
    {
        mid = (i+j)/2;
        if(wordlist[mid] == s)
        {
            found=true;
            index=mid;
            return mid;
        }
        else if(wordlist[mid]>s)
        {
            j=mid-1;
        }
        else if(wordlist[mid]<s)
        {
            i=mid+1;
        }
    }
    return -1;
}
