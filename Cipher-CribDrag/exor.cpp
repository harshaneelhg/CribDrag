#include<string>
#include<iostream>
using namespace std;

//exor() FUNCTION ACCEPTS CIPHERTXT AND A STRING. IT RETURNS THE EXORED VALUE
//OF BOTH THE STRINGS.

string exor(string cipher, string word)
{

    //IF A GUESSED WORD IS LARGER THAN CIPHERTEXT THEN CLEARLY
    //OUR GUESSED WORD IS WRONG. SO RETURN EMPTY STRING.

    if(word.size()>cipher.size())
    {
        return "";
    }

    //OTHERWISE WE WILL COMPUTE EXORED VALUE AND RETURN EXORED  VALUE.

    else
    {
        int i=0;
        string str="";
        while(i<word.size())
        {
            str+=cipher[i]^word[i];
            i=i+1;
        }
        return str;
    }
}
