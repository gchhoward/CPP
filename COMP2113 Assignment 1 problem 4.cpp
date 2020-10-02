#include <iostream>
#include <string>
using namespace std;
char CasesarShift(char c, int k);

int main() {
  char s,c; 
  int k; 
  cin >> s >> k;
  if (s == 'd'){
    k = -k;
  }
  while(c != '!'){
    cin >> c;
    cout << CasesarShift(c, k)<<endl;
  }
}

char CasesarShift(char c, int k)
{
    if (isalpha(c))
    {
        if (isupper(c)){
          c = tolower((((c - 65) + k + 26) % 26) + 65); //65 is the number of the althabet and the number
        }
        else{
          c = toupper(c);
          c = (((c - 65) + k + 26) % 26) + 65;
        }
    }
    return c;
}

