// Hill Cypher
#include <iostream>
#include <string>
#include <locale>
#include <vector>

// https:// stackoverflow.com/questions/25022880/c-split-string-every-x-characters

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
	int y, num=0;
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

// Generates random 2x2 key vector matrix
vector< vector<int> > keygen()
{
	int r, c;
	vector< vector<int> > key(2, vector<int>(2));
	for (r = 0; r < 2; r++)
	{
		for (c = 0; c < 2; c++)
		{
			key[r][c] = int(rand() % 10 + 1);
			cout << key[r][c] << endl;
		}
	}
	return key;
}

// Takes 2x2 KEY matrix and multiplies by 2x1 CHAR matrix
vector< vector<int> > multiply(vector< vector<int> > k, vector< vector<int> > c)
{
	vector< vector<int> > ans(2, vector<int>(2));
	ans[0][0] = (k[0][0] * c[0][0]) + (k[0][1] * c[0][1]);
	ans[0][1] = (k[1][0] * c[0][0]) + (k[1][1] * c[0][1]);
	return ans;
}

// Splits plain text into 2x1 matrices
vector<string> split(const string& str)
{
	int NumSubstrings = str.length() / 2;
	cout << NumSubstrings << endl;
	vector<string> ret;

	for (int i = 0; i < NumSubstrings; i++)
	{
		int c = i * 2;
		ret.push_back(str.substr(c, 2));
	}

	// If there are leftover characters, create a shorter item at the end.
	if (str.length() % 2 != 0)
	{
		int num = 2 * NumSubstrings;
		string extra = str.substr(num);
		ret.push_back(extra);
	}
	return ret;
}

int main()
{
	vector< vector<int> > mtrx(2, vector<int>(2));
	srand(time(NULL));

	vector< vector<int> > key = keygen();

	//cout << "0.0: " << key[0][0] << endl;
	//cout << "0.1: " << key[0][1] << endl;
	//cout << "1.0: " << key[1][0] << endl;
	//cout << "1.1: " << key[1][1] << endl;

	// Get plain text from user
	string pt = getinput();

	int len = pt.length();

	vector<string> tsplit = split(pt);
	
	cout << tsplit[0] << endl;
	cout << tsplit[1] << endl;
	cout << tsplit[2] << endl;
	cout << tsplit[3] << endl;
	cout << tsplit[4] << endl;



	for (int i = 0; i < len; i++)
	{
		char ch = pt[i];

		if (isalpha(ch)) {

		}
		else {
			cout << "No:  " << ch << endl;
			return ch;
		}

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
//	int* return_array; e
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