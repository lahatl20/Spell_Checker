#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctype.h>
#include "BinarySearchTree.h"

using namespace std;

#include "dictionary.h"

//struct for the binary node containing a word and line number per element
struct BNode
{
  string word;
  int lineNum;
  
  bool operator < (BNode otherStruct) const
  {
    return (word < otherStruct.word);
  }
};
typedef BinarySearchTree<BNode> BST;    //defined binary search tree object

//overloaded operator method for writing elements to "notfound.txt"
ostream & operator << (ostream & out, BNode & temp)
{
  out << temp.word << "  " << temp.lineNum;
  return out;
}

//prototype methods; each method is defined later
void readDictionary(Dictionary<string> &dict);
void storeMisspell(string &word, int &lineNum, BST &bt);
void userAction(string &word, int &lineNum, Dictionary<string> dict);
void spellSuggest(string &word, Dictionary<string> dict);
void writeMisspell(BST &bt);

//main function of the client program
int main(int argc, char *argv[])
{
  //Post: starts the program by clearing the screen; it reads the dictionary file, executes the program, and writes all misspelled words to a file,
  //while the argv[1] file is being read, if a word in the file is not found, it puts the word in a binary search tree, and asks the user what
  //they want to do with it
  system("clear");
  
  if(argc == 1)
  {
    cout << "You did not enter the file name of the file to be checked.\n\n";
    exit(0);
  }
  
  cout << "------ Welcome to the Spell Checker Program ------";
  
  Dictionary<string> dict("ZZZ", 1000);
  BNode nf = {"ZZZ", -1};
  BST bt(nf);  ifstream inFile;  int lineNum = 1;
  string word;  string found;  string line;
  
  readDictionary(dict);    //read the dictionary file
  
  inFile.open(argv[1]);
  
  if(inFile)    //execute the program
  {
     while(getline(inFile, line))
     {
       int i = 0;

       while(i<line.length())
       {
         if(isalpha(line[i]) || line[i] == '\'')
         {
           word += tolower(line[i]);  i++;
         }
         else
         {
           i++;  found = dict.lookup(word);
         
           if(found == "ZZZ")
           {
             storeMisspell(word, lineNum, bt);
             userAction(word, lineNum, dict);
           }
           
           word = "";
         }
       }      
       lineNum++;
     }
     inFile.close();
  }
  
  writeMisspell(bt);
}

void readDictionary(Dictionary<string> &dict)
{
  ifstream inFile;
  string line;
  inFile.open("dict.txt");
  
  if(inFile.is_open())
  {
    while(!inFile.eof())
    {
      getline(inFile, line);
      dict.insert(line);
    }
    inFile.close();
  }
  else
  {
    cout << "Unable to open file.";
    exit(0);
  }
}

void storeMisspell(string &word, int &lineNum, BST &bt)
{
  //Post: store the misspelled word in a binary search tree
  BNode bn = {word, lineNum};
  bt.insert(bn);
}

void userAction(string &word, int &lineNum, Dictionary<string> dict)
{
  //Post: Asks the user what to do with the misspelled word; user can add word to dictionary, ignore the misspelled word and skip future references, move on to the next word,
  //search fo a suggested spelling, or quit the program
  char selection;
  
  cout << "\n\n" << word << " on line " << lineNum << " was not found in the dictionary\n\n";
  
  cout << "A) Add word to dictionary\n";
  cout << "I) Ignore word and skip future references\n";
  cout << "G) Go on to next word\n";
  cout << "S) Search for a suggested spelling\n";
  cout << "Q) Quit spell checking file\n\n";
  
  cout << "Selection:  ";
  cin >> selection;
  cout << "\n";
  switch(toupper(selection))
  {
    case 'A':
      dict.insert(word);
      break;
    case 'I':
      dict.insert(word);
      break;
    case 'G':
      break;
    case 'S':
      spellSuggest(word, dict);
      break;
    case 'Q':
      cout << "Thank you for using the spell checker!\n";
      cout << "Now exiting the program...\n\n";
      dict.makeEmpty();
      exit(0);
      break;
    default:
      cout << "Invalid input.";
      userAction(word, lineNum, dict);
  }
}

void spellSuggest(string &word, Dictionary<string> dict)
{
  //Post: Switches letters in the misspelled word until a match is found in dictionary hash table
  int j = 1;  char temp;  string suggest;
  
  for(int i = 0; j<word.length();i++)
  {
    temp = word[i];
    word[i] = word[j];
    word[j] = temp;
    
    suggest = dict.lookup(word);
    
    if(suggest == "ZZZ")
    {
      temp = word[i];
      word[i] = word[j];
      word[j] = temp;
      j += 1;
    }
    else
    {
      cout << "Suggested Spelling: " << suggest << "\n\n";
      break;
    }
  }
  
  cout << "Press ENTER to continue...";
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
  cin.get();
}

void writeMisspell(BST &bt)
{
  //Post: writes the binary search tree to an external file called "notfound.txt"
  ofstream outFile;
  outFile.open("notfound.txt");
  
  bt.printTree(outFile);
  
  outFile.close();
}