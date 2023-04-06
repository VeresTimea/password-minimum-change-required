#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int countChars(string s)
{
    int hasLowercase = 1, hasUppercase = 1, hasDigit = 1;
    for (char c : s)
    {
        if (islower(c)) hasLowercase = 0;
        else if (isupper(c)) hasUppercase = 0;
        else if (isdigit(c)) hasDigit = 0;
    }
    return hasLowercase + hasUppercase + hasDigit;  //how many different types of characters the input string contains.
}

int minimumPasswordChanges(string password)
{
    int requiredChar = countChars(password);   // get the number of different types of characters
    if (password.length() < 6) return max(requiredChar,6-(int)password.length());

    int replacements = 0;  int oneRepeatingChar = 0;   int twoRepeatingChar = 0;

    for (int i = 0; i < password.length();)   //checking for three repeating characters in a row
    {
        int len = 1;
        while (i + len < password.length() && password[i + len] == password[i + len - 1]) len++;
        if (len >= 3)
        {
            replacements += len / 3;
            if (len % 3 == 0) oneRepeatingChar += 1; //we need to insert/change one character to break the sequence.
            if (len % 3 == 1) twoRepeatingChar += 2; //we need to insert/change two characters to break the sequence
        }
        i += len;
    }

    if (password.length() <= 20) return max(requiredChar, replacements);

    int deleteCount = password.length() - 20; //make it at most 20 characters long.

    //making sure not to introduce new repeating character(s)
    //number of repeating sequences that can be eliminated with a single replacement
    replacements=replacements- min(deleteCount, oneRepeatingChar);

    //can be eliminated with two replacements,
    replacements=replacements -min(max(deleteCount - oneRepeatingChar, 0), twoRepeatingChar) / 2;

    //can be eliminated with three replacements
    replacements=replacements- max(deleteCount - oneRepeatingChar - twoRepeatingChar, 0) / 3;

    return deleteCount + max(requiredChar, replacements);
}

int main()
{
    string password;
    cout << "Enter your password: ";
    cin >> password;

    if(!password.empty()){
    int minChange =minimumPasswordChanges(password);
    cout << "Minimum change required: " << minChange << endl;
    }

    return 0;
}

