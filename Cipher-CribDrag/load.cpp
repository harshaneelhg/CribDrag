#include<fstream>
#include<string>
#include<iostream>
using namespace std;
string* loadWords();

//loadwords() READS ALL THE STRINGS IN THE FILE AND STORES THEM INTO
//ARRAY OF STRINGS.

string* loadWords()
{
    string* wordlist=new string[100000];
    string word="";
    ifstream input("/usr/share/dict/words");
    int i=0;
    while((!input.eof()))
    {
        getline(input,word);
        wordlist[i]=word;
        i=i+1;
    }
    input.close();
    return wordlist;
}
