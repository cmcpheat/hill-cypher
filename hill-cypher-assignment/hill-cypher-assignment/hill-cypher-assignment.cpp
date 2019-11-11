// Hill Cypher
#include <iostream>
#include <string>
#include <locale>
#include <vector>

using namespace std;

string input;
int n, c;

// Array of alphabet chars
char alpha[26] = { 'a','b','c','d','e','f','g','h','i',
				'j','k','l','m','n','o','p','q','r',
				's','t','u','v','w','x','y','z' };

// Modulo operation
int mod(int a)
{
	n = a % 26;
	return n;
}

// Swaps alpha chars to corresponding num in alphabet (e.g. A=0, Z=25)
int swaptonum(char ch)
{
	int y, num;
	for (y = 0; y < 26; y++)
	{
		if ((ch == alpha[y]))
		{
			num = y;
		}
	}
	return num;
}

// Asks user to enter a plain text message
string getinput()
{
	cout << "Enter a message: ";
	getline(cin, input);
	return input;
}

// Generates random 2x2 key matrix
vector< vector<int> > keygen()
{
	int r, c;
	vector< vector<int> > key(2, vector<int>(2));
	for (r = 0; r < 2; r++)
	{
		for (c = 0; c < 2; c++)
		{
			key[r][c] = int(rand() % 10 + 1);
			// cout << key[r][c] << endl;
		}
	}
	return key;
}

// Encrypts plain text into cypher text
//string encrypt(vector< vector<int> > k, string pt)
//{
//
//}

// Main function to run program
int main()
{
	srand(time(NULL));

	vector< vector<int> > key = keygen();

	//cout << "0.0: " << key[0][0] << endl;
	//cout << "0.1: " << key[0][1] << endl;
	//cout << "1.0: " << key[1][0] << endl;
	//cout << "1.1: " << key[1][1] << endl;

	string plaintext = getinput();

	int len = plaintext.length();

	// cout << len << endl;

	for (int i = 0; i < len; i++)
	{
		char ch = plaintext[i];

		if (isalpha(ch))
			cout << "Yes: " << swaptonum(ch) << endl;
		else
			cout << "No:  " << ch << endl;
	}
}










// cout << k[0] << k[1] << k[2] << k[3] << endl;
// int k[4] = { 3, 3, 2, 5 };
// int pt[2] = { 7, 4 };
// int answer[4] = { (k[0]*pt[0]) + (k[1]*pt[1]) + (k[2]*pt[0]) + (k[3]*pt[1]) };
// cout << alpha[mod((k[0] * pt[0]) + (k[1] * pt[1]))] << endl;
// cout << alpha[mod((k[2] * pt[0]) + (k[3] * pt[1]))] << endl;

//int* keygen(int key)
//{
//	int i, j, key;
//
//	int* return_array; 
//
//	int key[2][2];
//
//	return_array = key; 
//
//	srand(time(NULL));
//	for (i = 0; i < 2; i++)
//	{
//		for (j = 0; j < 2; j++)
//		{
//			key[i][j] = int(rand() % 100 + 1);
//			cout << key[i][j] << endl;
//		}
//	}
//	cout << "0.0: " << key[0][0] << endl;
//	cout << "0.1: " << key[0][1] << endl;
//	cout << "1.0: " << key[1][0] << endl;
//	cout << "1.1: " << key[1][1] << endl;
// 
//}







//
//Stack Stuff
//
//// Hill Cypher
//#include <iostream>
//#include <string>
//#include <locale>
//#include <vector>
//#include<stack>
//
//using namespace std;
//
//string input;
//int n, c, swp;
//stack<int> sint, schar;
//
//// Array of alphabet chars
//char alpha[26] = { 'a','b','c','d','e','f','g','h','i',
//				'j','k','l','m','n','o','p','q','r',
//				's','t','u','v','w','x','y','z' };
//
//// Modulo operation
//int mod(int a)
//{
//	n = a % 26;
//	return n;
//}
//
//// Swaps alpha chars to corresponding num in alphabet (e.g. A=0, Z=25)
//int swaptonum(char ch)
//{
//	int y, num;
//	for (y = 0; y < 26; y++)
//	{
//		if ((ch == alpha[y]))
//		{
//			// cout << ch << "+" << alpha[y] << endl;
//			num = y;
//		}
//	}
//	return num;
//}
//
//// Asks user to enter a plain text message
//string getinput()
//{
//	cout << "Enter a message: ";
//	getline(cin, input);
//	return input;
//}
//
//// Generates random 2x2 key matrix
//vector< vector<int> > keygen()
//{
//	int r, c;
//	vector< vector<int> > key(2, vector<int>(2));
//	for (r = 0; r < 2; r++)
//	{
//		for (c = 0; c < 2; c++)
//		{
//			key[r][c] = int(rand() % 10 + 1);
//			// cout << key[r][c] << endl;
//		}
//	}
//	return key;
//}
//
//// Encrypts plain text into cypher text
////string encrypt(vector< vector<int> > k, string pt)
////{
////
////}
//
//// Main function to run program
//int main()
//{
//	srand(time(NULL));
//
//	vector< vector<int> > key = keygen();
//
//	//cout << "0.0: " << key[0][0] << endl;
//	//cout << "0.1: " << key[0][1] << endl;
//	//cout << "1.0: " << key[1][0] << endl;
//	//cout << "1.1: " << key[1][1] << endl;
//
//	string plaintext = getinput();
//
//	int len = plaintext.length();
//
//	// cout << len << endl;
//
//	for (int i = 0; i < len; i++)
//	{
//		char ch = plaintext[i];
//
//		if (isalpha(ch)) {
//			swp = swaptonum(ch);
//			cout << "Yes: " << swp << endl;
//
//			for (int j = 0; j < 2; j++)
//			{
//				for (int k = 0; k < 2; k++)
//				{
//
//				}
//			}
//		}
//		else
//			cout << "No:  " << ch << endl;
//	}
//}