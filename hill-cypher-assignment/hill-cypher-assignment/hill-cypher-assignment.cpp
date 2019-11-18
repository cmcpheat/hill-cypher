// Hill Cypher
#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <stack>

using namespace std;

string input;
int n, c;
char alpha[26] = { 'a','b','c','d','e','f','g','h','i',
				'j','k','l','m','n','o','p','q','r',
				's','t','u','v','w','x','y','z' };

// Swaps num to corresponding letter in alphabet (e.g. 0=A, 25=Z)
int swaptochar(int n)
{
	int y;
	char ch;
	for (y = 0; y < 26; y++)
	{
		if (n == y)
		{
			ch = alpha[y];
		}
	}
	return ch;
}

// Matrix modulo operation
vector<int> mod(vector<int> v)
{
	vector<int> a;
	a.insert(a.begin(), (v[0] % 26));
	a.insert(a.end(), (v[1] % 26));
	return a;
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
vector<int> multiply(vector< vector<int> > k, vector<int> c)
{
	vector<int> v;
	v.insert(v.begin(), ((k[0][0] * c[0]) + (k[0][1] * c[1])));
	v.insert(v.end(), ((k[1][0] * c[0]) + (k[1][1] * c[1])));
	return v;
}

// TODO: void
void encrypt(vector< vector<int> > key, string pt)
{
	string cyphertext;
	vector<int> encryption;
	vector<int> matrix;

	string tempstr = "";
	int len = pt.length();

	if (len % 2 != 0) {
		pt = pt += " ";
		len++;
	}
	else {
		pt = pt;
	}

	cout << "len: " << len << endl;

	for (int i = 0; i < len; i++)
	{	
		char ch = pt[i];
		if (isalpha(ch)) {
			
			matrix.push_back(ch);

			if (matrix.size() % 2 == 0) {

				cout << "matrix 0: " << matrix[0] << endl;
				cout << "matrix 1: " << matrix[1] << endl;
			
				encryption = mod(multiply(key, matrix));

				cout << "encrypt 0: " << encryption[0] << endl;
				cout << "encrypt 1: " << encryption[1] << endl;

				char swapped0 = swaptochar(encryption[0]);
				char swapped1 = swaptochar(encryption[1]);

				cout << "swapped 0: " << swapped0 << endl;
				cout << "swapped 1: " << swapped1 << endl;

				cyphertext += swapped0;
				cyphertext += swapped1;

				matrix.clear();
			}
		}
		else {
			cyphertext += ch;
			cout << "Char: " << ch << " is NOT alpha" << endl;
		}
	}
	cout << "The cypher text: " << cyphertext << endl;
}

int main()
{
	srand(time(NULL));
	vector< vector<int> > key = keygen();
	string pt = getinput();
	encrypt(key, pt);
}

