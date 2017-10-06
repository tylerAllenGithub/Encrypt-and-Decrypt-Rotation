/*Tyler Allen
  Assignment 1
Purpose: Encrypt and decrypt a data file utilizing a cryptogram method and a Rot method
Output: Will be able to output to a file both encrypted and decrypted strings that are stored inside vectors
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

void getUserPreferences(const vector<string>v);//ask user for preferences and calls all other decrypt/encrypt functions
vector<string>getOriginalData();//gets and returns file contents
vector<string>encryptRot(const vector<string>v, int rotNum);//encrypts and returns vector string using rotation
string encryptWordRot(string word, int rotNum);//encrypts and returns word using rotation
vector<string>encryptCrypto(const vector<string>v);//encrypts and returns vector string using cryptogram
string encryptWordCrypto(string word, string keyCode);//encrypts and returns word using cryptogram
vector<string>decryptRot(int rotNum);//returns decrypted vector string using rotation
string decryptWordRot(string word, int rotNum);//decrpyts word and returns decrypted word using rotation
vector<string>decryptCrypto();//returns decrypted vector string using cryptogram
string decryptWordCrypto(string word, string keyCode);//decrypts word and returns decrypted string using cryptogram
void outputFile(const vector<string>v, string fileName);//outputs vector to file

int main()
{
  vector<string>original = getOriginalData(); //store vector from original file into vector
  getUserPreferences(original);//ask user for preference then calls apropriate function
  return 0;
}

void getUserPreferences(const vector<string>v)//ask user for preferences and calls all other decrypt/encrypt functions
{
  string input1;//chocie of encryption or decryption
  string input2;//choice of rot or cryptogram
  string fileName;//file that is to be written to
  int key;//rot number
  vector<string>encRot;
  vector<string>encCrypto;
  vector<string>decRot;
  vector<string>decCrypto;
  do
    {
  cout<<"Do you want to do encryption or decryption? ";
  cin>>input1;
  if(input1=="encryption")
    {
     do
     {
      cout<<"Would you like to use rot or cryptogram? ";
      cin>>input2;
      if(input2=="rot")
        {
          cout<<"Enter an encryption key: ";
          cin>>key;
          encRot= encryptRot(v, key);//stores encrypted vector into encRot vector
          fileName="encrypt01.txt";
          outputFile(encRot, fileName);//store output in encrypt01.txt
        }
      else if(input2=="cryptogram")
        {
          fileName="encrypt02.txt";
          encCrypto=encryptCrypto(v);//set vector to result of cryptogram encryption function
          outputFile(encCrypto, fileName);//output to file encrypt02.txt
        }
      else
        {
          cout<<"Not a valid choice. Please enter rot or cryptogram."<<endl;//In case the user has a muscle spasm
        }
     } while(input2!="rot" && input2!="cryptogram");//in case the user has continuous muscle spasms
    }
  else if(input1=="decryption")
    {
        do
         {
          cout<<"Would you like to use rot or cryptogram? ";
          cin>>input2;
          if(input2=="rot")
            {
              cout<<"Enter a decryption key: ";
              cin>>key;//the key has to be known by user for decryption or else the enemy could get their hands on it
              decRot= decryptRot(key);//set vector to result of decrypted rot function
              fileName="decrypt01.txt";
              outputFile(decRot, fileName);//outputs decrypted vector contents to decrypt01.txt

            }
          else if(input2=="cryptogram")
            {
              fileName="decrypt02.txt";
              decCrypto=decryptCrypto();//set vector to result of decrypted cryptogram function
              outputFile(decCrypto, fileName);//outputs decrypted vector contents to decrypt02.txt
            }
          else
            {
              cout<<"Not a valid choice. Please enter rot or cryptogram."<<endl;//in case the user's cat walks on their computer
            }
         } while(input2!="rot" && input2!="cryptogram");//will continue to ask for input as long as that cat is on the keyboard

    }
  else
    {
      cout<<"Not a valid choice. Please enter encryption or decryption."<<endl;//regarding the first decision the user makes
    }

    } while((input1!="encryption") && (input1!="decryption"));//makes sure there will be no error if there is incorrect input
 }



vector<string>getOriginalData()//gets and returns file contents
{
  vector<string>v;
  ifstream fin;
  string word;
   fin.open("original.txt");
 while(fin>>word)
    {
      v.push_back(word);//stores original file into vector v and returns it
    }
  return v;
}

void outputFile(const vector<string>v, string fileName)//outputs vector to file
{
  ofstream outFile;
  outFile.open(fileName.c_str());//opens the file that is to be written to that has been passed as a parameter
  for(int i=0; i<v.size();i++)
    {
      outFile<<v[i]<<" ";//prints the vector in the designated file
    }
}

vector<string>encryptRot(const vector<string>v, int rotNum)//encrypts and returns vector string using rotation
{
  vector<string>encV;
  if(rotNum>=26)
    {    rotNum=rotNum%26;//breaks down larger numbers so they will work with the rot function
    }

  for(int i=0;i<v.size();i++)
    {
      encV.push_back(encryptWordRot(v[i], rotNum));//store encrypted strings from encryptWordRot function into encV vector
    }
  return encV;//returns encrypted vector
}

string encryptWordRot(string word, int rotNum)//encrypts and returns word using rotation
{
  string encWord=word;
  int modNum;

  for(int i=0; i<word.size();i++)
    {
      if(word[i]>='A'&&word[i]<='Z')//checks to see if word's letters are uppercase
      {
        word[i] = tolower(word[i]);//changes word's letters to lowercase
      }
    }
  for(int k=0; k<word.size();k++)
    {
      if(word[k]>='a'&&word[k]<='z')//makes sure they are letters and not punctuation
     {
       if((word[k]+rotNum)>'z')//check to see if the adjusted letter is greater than z
        {
          modNum = 26-rotNum;//makes sure modNum is within range of the alphabet (26 letters)
          encWord[k]=(char)(word[k]-modNum);//encrypts letter if the letter went out of bounds(beyond z)
        }
   else
        {
          encWord[k]=(char)(word[k]+rotNum);//sets letter to be equal to itself + the rot number
        }
     }
    }
      return encWord;
}

vector<string>encryptCrypto(const vector<string>v)//encrypts and returns vector string using cryptogram
{
  vector<string>encV;
  string keyCode;
  ifstream fin;
  fin.open("Cryptogram.txt");//file that consists of one string with new "alphabet"
 fin>>keyCode;//stores the whole cryptogram file into string keyCode
  for(int i=0;i<v.size();i++)
    {
      encV.push_back(encryptWordCrypto(v[i], keyCode));//stores encrypted strings into encV
    }
  return encV;
}

string encryptWordCrypto(string word, string keyCode)//encrypts and returns word using cryptogram
{
  string encS;
  for(int i=0; i<word.size();i++)
    {
      if(word[i]>='A'&&word[i]<='Z')//checks to see if word's letters are uppercase
        {
          word[i] = tolower(word[i]);//changes word's letters to lowercase
        }
    }

  encS=word;//sets encS to word after word was changed to lowercase

  for(int i=0; i<keyCode.size();i++)
    {
      if(word[i]>='a'&&word[i]<='z')
        encS[i]=keyCode[word[i]-'a'];//sets encrypted letter to index of keyCode where index = word's index-a
    }
  return encS;
}

vector<string>decryptRot(int rotNum)//returns decrypted vector string using rotation
{
  vector<string>decV;
  vector<string>encV;
  ifstream fin;
  string word;
  fin.open("encrypt01.txt");//opens appropriate file to decrypt
  while(fin>>word)
    {
      encV.push_back(word);//stores encrypted file contents into encV
    }

  if(rotNum>=26)
    {    rotNum=rotNum%26;//breaks down larger numbers so they will work with the rot function
    }

  for(int i=0;i<encV.size();i++)
    {
      decV.push_back(decryptWordRot(encV[i], rotNum));//stores decrypted words into decV
    }
  return decV;
}

string decryptWordRot(string word, int rotNum)//decrpyts word and returns decrypted word using rotation
{
    string decWord=word;
    int modNum;

    for(int k=0; k<word.size();k++)
      {//tolower isn't necessary since encrypted contents are already lowercase
        if(word[k]>='a'&&word[k]<='z')//makes sure they are letters and not punctation
          {
          if((word[k]-rotNum)<'a')//checks if adjusted letter value is less than a
              {
                modNum = rotNum-26;//value to keep adjusted letter value in alphabet range
                decWord[k]=(char)(word[k]-modNum);//decrypts letter into original form
              }
            else
              {
                decWord[k]=(char)(word[k]-rotNum);//decrypts letter into original form
              }
          }
      }
    return decWord;//returns decrypted word

}

vector<string>decryptCrypto()//returns decrypted vector string using cryptogram
{
  vector<string>decV;
  vector<string>encV;
  string keyCode;
  ifstream key;//refers to Cryptogram.txt file
  ifstream crypto;//refers to encrypted file encrypt02.txt
  string word;
  key.open("Cryptogram.txt");//open Cryptogram file
  if(!key)
    cout<<"Could not open File"<<endl;//error message
else
  key>>keyCode;//stores Cryptogram.txt in keyCode
  crypto.open("encrypt02.txt");//open encrypted file to read from
  if(!crypto)
    cout<<"Could not open File"<<endl;//error message
  crypto>>word;//stores first word
  while(crypto)
    {
      encV.push_back(word);//fills encrypted vector with encrypt01.txt contents
      crypto>>word;
    }

  for(int i=0;i<encV.size();i++)
    {
      decV.push_back(decryptWordCrypto(encV[i], keyCode));//adds decrypted word to decV
    }
  return decV;
}

string decryptWordCrypto(string word, string keyCode)//decrypts word and returns decrypted string using cryptogram
{

  string decS = word;
  int indexOfWord;
   for(int i=0; i<word.size();i++)
     {
       if(word[i]>='a'&&word[i]<='z')//check to make sure not punctuation
        {
          indexOfWord=keyCode.find(word[i],0);//finds index of letter in keyCode
          decS[i]=(char)(indexOfWord+'a');//sets decrypted letter to indexOfWord+a
        }
     }
return decS;
}

