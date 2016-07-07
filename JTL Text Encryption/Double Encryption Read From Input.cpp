#include <iostream> //for input/output stream

using namespace std;

void EncryptDecryptMessage(int Choice);

void WordToNumberConverter(int &PassNumber, char Password[]);
void RunThroughRandomNumbers(int PasswordNum);
void FillKey(char KeyBeingFilled[]);

char EncryptMessage(char KeyForEncrypting[], char Input);
char DecryptMessage(char KeyForDecrypting[], char Input);

const int ASCII_RANGE_SIZE_94 = 94;   //Range from ASCII value 32 to 126 = 94
const int SHIFT_SET_32        = 32;   //Move range up 32 values form (0-93) to (32 to 126)
const int PASSWORD_LENGHT_25  = 25;

/*

 add line comments
 change password to vector
 split large dual purpose function into two smaller one purpose functions
 
 clean up rest of code nicely
 use of const / & on varibles that apply
 
*/

int main()
{
    int Choice;
    
    cout << "\nJTL Text Encryption\n\n";
    
    do
    {
        cout << "=======================" << endl;
        cout << "Press 1 to encrypt"      << endl;
        cout << "Press 2 to decrypt"      << endl;
        cout << "Press other key to quit" << endl << endl;
        cout << "Choice: ";
        
        cin >> Choice;
        
        cin.ignore(1); //removes newline from input buffer
        
        EncryptDecryptMessage(Choice);
    }
    
    while (Choice ==1 || Choice == 2);
}

void EncryptDecryptMessage(int Choice)
{
    char Password[PASSWORD_LENGHT_25];
    
    int  PasswordNumber = 1;
    
    char Key1[ASCII_RANGE_SIZE_94] = {0};//One larger 0 - 93, not using 0
    char Key2[ASCII_RANGE_SIZE_94] = {0};
    char Key3[ASCII_RANGE_SIZE_94] = {0};
    
    char InputCharacter1, InputCharacter2, InputCharacter3;
    
    if (Choice == 1)
        cout << "\nEnter an encryption password: ";
    
    else
        cout << "\nEnter given encryption password: ";
        
    
    cin.getline(Password, PASSWORD_LENGHT_25);
    
    WordToNumberConverter(PasswordNumber, Password);
    
    srand(PasswordNumber);//Seed number for my random number generator
    
    RunThroughRandomNumbers(PasswordNumber);
    
    FillKey(Key1);
    
    RunThroughRandomNumbers(PasswordNumber);
    
    FillKey(Key2);
    
    RunThroughRandomNumbers(PasswordNumber);
    
    FillKey(Key3);
    
    if (Choice == 1)
    {
        cout << "\nInput message\n";
        cout << "=============\n\n";
    }
    
    else
    {
        cout << "\nInput message to decode\n";
        cout << "=======================\n\n";
    }
    
    cin.get(InputCharacter1);
    
    if (Choice == 1)
    {
        cout << "\nEncrypted message\n";
        cout << "=================\n\n";
    }
    
    else
    {
        cout << "\nDecoded Message\n";
        cout << "===============\n\n";
    }
    
    if (Choice == 1)
    {
        while (InputCharacter1!='\n')
        {
            InputCharacter2=EncryptMessage(Key1, InputCharacter1);
            InputCharacter3=EncryptMessage(Key2, InputCharacter2);
            
            cout << EncryptMessage(Key3, InputCharacter3);
            cin.get(InputCharacter1);
        }
    }
    
    else
    {
        while (InputCharacter1 != '\n')
        {
            InputCharacter2=DecryptMessage(Key3, InputCharacter1);
            InputCharacter3=DecryptMessage(Key2, InputCharacter2);
            
            cout << DecryptMessage (Key1, InputCharacter3);
            cin.get(InputCharacter1);
        }
    }
    
    cout << "\n\n";
}

void WordToNumberConverter(int &PassNumber, char Password[])
{
    for (int i = 0; Password[i]; i++)
    {
        PassNumber += (int) Password[i];
        PassNumber += i;
    }
}

void RunThroughRandomNumbers(int PasswordNum)//cycles through random numbers randomly
{
    int LoopLimit = rand() / PasswordNum;
    
    for (int i = 0; i <= LoopLimit; ++i)
    {
        rand();
    }
}

void FillKey(char KeyBeingFilled[])
{
    int RandomNumber;
    int KeySpot, j;
    
    for (KeySpot = 0; KeySpot < ASCII_RANGE_SIZE_94; ++KeySpot)
    {
        RandomNumber = SHIFT_SET_32 + rand() % ASCII_RANGE_SIZE_94;//0-93, then shifts up to 32-126 ASCII range
        
        for (j = 0; j <= KeySpot; ++j)//this bit of code checks to make sure new rand number isn't already used before
        {
            if (KeyBeingFilled[j] == RandomNumber)
            {
                RandomNumber = SHIFT_SET_32 + rand() % ASCII_RANGE_SIZE_94;//0-93, then shifts up to 32-126
                j = -1;
            }
        }
        
        KeyBeingFilled[KeySpot] = (char) RandomNumber;
    }
}

char EncryptMessage(char KeyForEncrypting[], char Input)
{
    return KeyForEncrypting[((int) Input) - SHIFT_SET_32];//-32 to get range back into 1-95 (range of Key)
}

char DecryptMessage(char KeyForDecrypting[], char Input)
{
    for (int Count = 0; Count < ASCII_RANGE_SIZE_94; ++Count)
    {
        if ((int) Input == KeyForDecrypting[Count])
        {
            return (char) Count+SHIFT_SET_32;//+32 to get back into 32-126 ASCII range
        }
    }
    
    return 0;
}