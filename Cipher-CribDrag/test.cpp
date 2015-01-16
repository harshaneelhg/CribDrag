#include<fstream>
#include<string>
#include<iostream>
#include<cstring>
#include<stdlib.h>
int DONE=0;
int MAX_LENGTH;
int temp=0;

using namespace std;

string message1;
string message2;
string message3;
string message4;
string cipherText1;
string cipherText2;
string cipherText3;
string cipherText4;
string key;

//FUNCTION DECLARATIONS.

string* loadWords();
string exor(string,string);
void decrypt(string *, string);
string* search1(string*,string);
int searchString(string*, string);
int cribDrag(string, string* ,string);
bool hasWeiredChars(string);
string* split(string, string);
int count(string *s);
int checkAchieved(string, string*);

//MAIN FUNCTION.

int main (int argc, char *argv[])
{
    //LOAD DICTIONARY IN ARRAY OF STRINGS

    cout<<"Loading dictionary..."<<"\n";
    string* wordlist = loadWords();
    int length=0;
    while(wordlist[length]!="")
    {
       length = length + 1;
    }
    cout<<"Loading complete...loaded "<<length<<" words in memory...\n";

    //READING CIPHER TEXTS FROM FILES

    string homedir= getenv("HOME");
    char w1,w2,w3,w4;
    ifstream cipher1;
    string fileloc=homedir+"/cipher000";
    cout<<fileloc<<"\n";
    cipher1.open(fileloc.c_str());
    ifstream cipher2;
    fileloc=homedir+"/cipher001";
    cipher2.open(fileloc.c_str());
    ifstream cipher3;
    fileloc=homedir+"/cipher002";
    cipher3.open(fileloc.c_str());
    ifstream cipher4;
    fileloc=homedir+"/cipher003";
    cipher4.open(fileloc.c_str());
    string word1="";
    string word2="";
    string word3="";
    string word4="";
    w1= cipher1.get();
    w2= cipher2.get();
    w3= cipher3.get();
    w4= cipher4.get();
    while(w1!=EOF)
    {
        word1+=w1;
        w1=cipher1.get();
    }
    cipherText1=word1;
    while(w2!=EOF)
    {
        word2+=w2;
        w2=cipher2.get();
    }
    cipherText2=word2;
    while(w3!=EOF)
    {
        word3+=w3;
        w3=cipher3.get();
    }
    cipherText3=word3;
    while(w4!=EOF)
    {
        word4+=w4;
        w4=cipher4.get();
    }
    cipherText4=word4;
    cout<<"Ciphertext reading complete...\n";

    //PERFORM CIPHERTEXT_1 EXOR CIPHERTEXT_2
    //WHICH IS EQUIVALANT TO MESSAGE_1 EXOR MESSAGE_2

    char c;
    int i=0;
    string ex="";

    while(i<word1.size())
    {
        c=word1[i]^word2[i];
        ex+=c;
        i=i+1;
    }

    //SET MAX_LENGTH VARIABLE WHICH WE WILL USE FOR CHECKING
    //IF WE HAVE ACHIEVED OUR GOAL.

    MAX_LENGTH=ex.size();
    int j=0;
    while(wordlist[j]!="")
    {
        //THERE ARE NO ONE LETTER WORDS IN ENGLISH EXCEPT "A" and "I"
        //SO WE WILL SKIP GIVING RECURSIVE CALLS FOR OTHER ONE LETTER
        //WORDS.

        if(wordlist[j].size()==1&&(wordlist[j]!="A"||wordlist[j]!="I"))
        {
            j=j+1;
            continue;
        }

        //FIRST CALL TO FUNCTION cribDrag().

        int achieved = cribDrag(ex,wordlist, wordlist[j]);
        j=j+1;
        if(achieved==1)
            break;
    }
    int pos=cipherText1.size();

    //PROGRAM COMES IN THIS SECTION ONCE ALL THE RECURSIVE
    //CALLS TO cribDrag() FUNCTION ARE OVER.



    cout<<"MESSAGE-1 : "<<message1<<"\n";
    cout<<"MESSAGE-2 : "<<message2<<"\n";
    if(exor(message1,cipherText1.substr(0,cipherText1.size()-1))==exor(message2,cipherText2.substr(0,cipherText2.size()-1)))
    {
        key=exor(message1,cipherText1.substr(0,cipherText1.size()-1));
        message3=exor(cipherText3.substr(0,cipherText3.size()-1),key);
        message4=exor(cipherText4.substr(0,cipherText4.size()-1),key);
        cout<<"MESSAGE-3 : "<<message3<<"\n";
        cout<<"MESSAGE-4 : "<<message4<<"\n";
    }
    else
    {
        key=exor(message2,cipherText1.substr(0,cipherText1.size()-1));
        message3=exor(cipherText3.substr(0,cipherText3.size()-1),key);
        message4=exor(cipherText4.substr(0,cipherText4.size()-1),key);
        cout<<"MESSAGE-3 : "<<message3<<"\n";
        cout<<"MESSAGE-4 : "<<message4<<"\n";
    }
    cout<<"KEY :"<<key<<"\n";

    //Writing messages to files.

    ofstream m1,m2,m3,m4,pad;
    m1.open((homedir+"/msg000").c_str());
    m2.open((homedir+"/msg001").c_str());
    m3.open((homedir+"/msg002").c_str());
    m4.open((homedir+"/msg003").c_str());
    pad.open((homedir+"/pad").c_str());
    int wr=0;
    while(wr<message1.size())
    {
        m1.put(message1[wr]);
        m2.put(message2[wr]);
        m3.put(message3[wr]);
        m4.put(message4[wr]);
        pad.put(key[wr]);
        wr=wr+1;
    }
}

int cribDrag(string ex,string* wordlist,string word)
{
    string s = exor(ex,word);

    //CHECK IF EXORED PART OF MESSAGE HAS ANY UNUSUAL CHARACTERS.
    //IF SO THEN THERE IS NO POINT GOING AHEAD WITH THAT.
    //HENCE RETURN.

    if(s==""||hasWeiredChars(s))
    {
        return 0;
    }

    //SPACE AFTER ONE WORD IN A STRING COINSIDES WITH LAST LETTER OF OTHER MESSAGE.
    //THEN ENTER INTO THIS SECTION.
    //EXAMPLE: SAY WE HAVE TWO PLAINTEXTS 'the program' and 'nice window'.
    //WHEN WE ARE AT STAGE WHEN message1= 'the ' and message2='nice' THEN WE ALREADY
    //KNOW THAT NEXT CHARACTER AFTER 'nice' IS SPACE. USING THAT ASSUMPTION WE CAN
    //DECRYPT ' ' WITH CORRESPONDING CHARACTER IN CIPHERTEXT TO GET 'p'. SO NOW WE ARE
    //AT STAGE WHERE message1= 'the p' and message2= 'nice ' AND 'p' WILL SERVE AS OUR
    //CLUE FOR NEXT GUESS.

    if(s[s.size()-1]==' ')
    {
        char c=ex[s.size()]^' ';
        s=s+c;
        word=word+' ';
    }

    //CHECK IF WE ARE DONE WITH EVALUATING BOTH THE MESSAGES.

    int ach= checkAchieved(s,wordlist);

    //IF WE ARE DONE EVALUATING TWO MESSAGES THEN ASSINGN MESSAGE VALUES TO CORRESPONDING
    //GLOBAL VARIABLE AND THEN RETURN.

    if(ach==1)
    {
        message1=s;
        message2=word;
        return 1;
    }

    //IF WE ARE YET TO EVALUATE ENTIRE MESSGAE THEN ENTER INTO THIS SECTION.
    //WE WILL SPLIT THE STRING ON THE BASIS OF SPACE CHARACTER AND STORE ALL
    //THE WORDS IN STRING ARRAY. EVERY STRING EXCEPT LAST STRING SHOULD BE
    //A MEANINGFUL WORD AND LAST STRING IN STRING ARRAY IS THE CLUE FOR THE NEXT
    //WORD. EX. IF WE HAVE PART OF THE STRING AS "THE PRO" THEN THE SHOULD BE THERE
    //IN THE DICTIONARY AND OUR NEXT GUESS WILL BE ON THE BASIS OF WORD 'PRO'.

    string* x = split(s," ");
    int index=0;
    string aug="";

    //CHECKING EVERY ELEMENT EXCEPT LAST ONE IN SPLIT STRING ARRAY.

    while(index<count(x)-1)
    {
        //IF WORDS BEFORE LAST SPACE CHARACTER ARE NOT IN THE DICTIONARY THEN
        //CLEARLY OUR GUESS IS WRONG HENCE RETURN 0.

        if(searchString(wordlist,x[index])==-1)
            return 0;

        //AUGMENT ALL THE STRINGS WITH SPACES IN BETWEEN EXCEPT LAST ONE.
        //EXAMPLE: IF WE ARE AT A STAGE WHERE message= 'A LOVELY D', THEN
        //AFTER EXECUTION OF WHILE LOOP WE WILL HAVE aug='A LOVELY '.
        //AND WE WILL USE 'D' FOR NEXT GUESS.

        aug=aug+x[index]+" ";
        index=index+1;
    }

    //CHECK IF WE ARE DONE EVALUATING MESSAGES. WE CAN BE SURE THAT WE ARE DONE
    //BY TWO CHECKS- 1. LENGTH OF GUESSED MESSAGE IS SAME AS LENGTH OF CIPHERTEXT.
    //2. EVERY WORD IN GUESSED STRING (WHICH WE CAN GET BY SPLITTING STRING USING ' ')
    //MUST EXIST IN THE DICTIONARY.

    if(s.length()==MAX_LENGTH-1&&searchString(wordlist,x[index])!=-1)
    {
        return 1;
    }

    //FIND LIST OF ALL THE WORDS IN DICTIONARY WHERE PART OF LAST STRING IN
    //STRIN ARRAY APPEARS AT THE START. THAT MEANS, CREATE LIST FOR NEXT GUESS.

    else
    {
        string* l = search1(wordlist,x[index]);
        int p=0;

        while(l[p]!="")
        {
            int a;
            if(aug+l[p]!=s)
            {
                //RECURSIVE CALL TO cribDrag() FUNCTION PASSING STRING GUESSED TILL NOW
                //AS AN ARGUMENT.
                a =cribDrag(ex,wordlist,aug+l[p]);
            }
            if(a==1)
            {
                return 1;
            }
            p=p+1;
            temp= temp+1;
        }
    }
}

//FUNCTION TO CHECK IF PART OF MESSAGES DECRYPTED TILL NOW CONTAINS WEIRED CHARACTERS.

bool hasWeiredChars(string s)
{
    int i=0;
    while(i<s.size())
    {
        if(!((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z')||s[i]==' '||s[i]=='!'||s[i]=='?'))
            return true;
        i++;
    }
    return false;
}

//FUNCTION TO SPLIT STRING ON THE BASIS OF A STRING.
//FUNCTION ACCEPTS STRING AND DELIMETER AND RETURNS ARRAY OF STRINGS
//SEPARATED BY SPACE CHARACTER.

string* split(string s, string delim)
{
    string* splitString=new string[100];
    int i=0;
    size_t pos = 0;

    string str;
    while ((pos = s.find(delim)) != string::npos) {
        str = s.substr(0, pos);
        splitString[i]=str;
        s.erase(0, pos + delim.length());
        i++;
    }
    splitString[i]=s;
    return splitString;
}

//FUNCTION TO COUNT NUMBER OF STRINGS IN ARRAY OF STRINGS.

int count(string*  s)
{
    int i=0;
    while(s[i]!="")
        i++;
    return i;
}

//FUNCTION TO CHECK IF WE HAVE ACHIEVED OUR GOAL.
//WE CAN BE SURE THAT WE ARE DONE BY TWO CHECKS-
//1. LENGTH OF GUESSED MESSAGE IS SAME AS LENGTH OF CIPHERTEXT.
//2. EVERY WORD IN GUESSED STRING (WHICH WE CAN GET BY SPLITTING STRING USING ' ')
//MUST EXIST IN THE DICTIONARY.
//RETURNS 1 IF WE HAVE REACHED OUR GOAL AND RETURNS 0 IF WE HAVE NOT.

int checkAchieved(string s,string* wordlist)
{
    if(s.size()==MAX_LENGTH-1)
    {
        string* list = split(s," ");
        int cnt= count(list);
        int i=0;
        while(i<cnt)
        {
            if(searchString(wordlist,list[i])==-1)
            {
                return 0;
            }
            i=i+1;
        }
        return 1;
    }
    return 0;
}
