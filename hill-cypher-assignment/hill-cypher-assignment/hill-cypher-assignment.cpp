// Hill Cypher
#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <stack>
#include <cmath>

// decryption video - https ://www.youtube.com/watch?v=kfmNeskzs2o

using namespace std;


class HillCypher
{
public:
	int setLetter(int);
	int setNumber(char);
	vector< vector<int> > setKey();
	string getInput();
	vector<int> getModulo(vector<int>);
	vector<int> matrixMultiply(vector< vector<int> >, vector<int>);
	bool checkMatrixIsInvertible(vector< vector<int> >);
	string encryptPlainText(vector< vector<int> >, string);
	// string decryptCypherText(vector< vector<int> >, string);

private:
	char letter;
	string input;
	vector<int> modulo;
	vector< vector<int> > key;
	vector<int> multiplication;
	string cyphertext;
	string plaintext;
};

// Swaps num to corresponding letter in alphabet (e.g. 0=A, 25=Z)
int HillCypher::setLetter(int n)
{
	char alpha[26] = { 'a','b','c','d','e','f','g','h','i',
				'j','k','l','m','n','o','p','q','r',
				's','t','u','v','w','x','y','z' };
	int y;
	char letter;
	for (y = 0; y < 26; y++)
	{
		if (n == y)
		{
			letter = alpha[y];
		}
	}
	return letter;
}

// Swaps letter in alphabet to corresponding number (e.g. A=0, Z=25)
int HillCypher::setNumber(char c)
{
	char alpha[26] = { 'a','b','c','d','e','f','g','h','i',
				'j','k','l','m','n','o','p','q','r',
				's','t','u','v','w','x','y','z' };
	int y;
	int number;
	for (y = 0; y < 26; y++)
	{
		if (c == alpha[y])
		{
			number = y;
		}
	}
	return number;
}

// Matrix modulo operation
vector<int> HillCypher::getModulo(vector<int> v)
{
	vector<int> modulo;
	modulo.insert(modulo.begin(), (v[0] % 26));
	modulo.insert(modulo.end(), (v[1] % 26));
	return modulo;
}

// Asks user to enter a plain text message
string HillCypher::getInput()
{
	string input;
	cout << "Enter a message: ";
	getline(cin, input);
	return input;
}

bool HillCypher::checkMatrixIsInvertible(vector< vector<int> > v)
{
	if (((v[0][0] * v[1][1]) - (v[0][1] * v[1][0])) != 0) {
		// cout << "Matrix is invertible" << endl;
		cout << "Determinant : \n" << ((v[0][0] * v[1][1]) - (v[0][1] * v[1][0])) << "\n\n";
		return true;
	}
	else {
		// cout << "Matrix is not invertible" << endl;
		return false;
	}
}

// Generates random 2x2 key vector matrix
vector< vector<int> > HillCypher::setKey()
{
	int invertible = 0;
	vector< vector<int> > key(2, vector<int>(2));

	while (invertible == 0)
	{
		int r, c;

		for (r = 0; r < 2; r++)
		{
			for (c = 0; c < 2; c++)
			{
				key[r][c] = int(rand() % 10 + 1);
				// cout << key[r][c] << endl;
			}
		}

		cout << "Key :\n";
		cout << "( " << key[0][0] << " " << key[0][1] << " )\n";
		cout << "( " << key[1][0] << " " << key[1][1] << " )\n\n";

		if (checkMatrixIsInvertible(key) == true) {
			cout << "Key is invertible\n" << endl;
			invertible = 1;
		}
		else {
			cout << "Key is NOT invertible\n" << endl;
			invertible = 0;
		}
	}

	return key;
}

// Invert matrix
vector< vector<float> > invertMatrix(vector< vector<int> > v)
{
	vector< vector<float> > inverse(2, vector<float>(2));
	//float k00 = v[0][0];
	//float k01 = v[0][1];
	//float k10 = v[1][0];
	//float k11 = v[1][1];

	inverse[0][0] = v[1][1];
	inverse[0][1] = -(v[0][1]);
	inverse[1][0] = -(v[1][0]);
	inverse[1][1] = v[0][0];

	//float mult = (1 / ((k00 * k11) - (k01 * k10)));

	//inverse[0][0] = k11 * mult;
	//inverse[0][1] = -(k01 * mult);
	//inverse[1][0] = -(k10 * mult);
	//inverse[1][1] = k00 * mult;

	//cout << "Mult: " << mult << endl;

	return inverse;
}

// Get determinant
float getDeterminant(vector< vector<int> > v)
{
	float determinant;
	determinant = ((v[0][0] * v[1][1]) - (v[0][1] * v[1][0]));
	return determinant;
}

// Takes 2x2 KEY matrix and multiplies by 2x1 CHAR matrix
vector<int> HillCypher::matrixMultiply(vector< vector<int> > k, vector<int> c)
{
	vector<int> multiplication;
	multiplication.insert(multiplication.begin(), ((k[0][0] * c[0]) + (k[0][1] * c[1])));
	multiplication.insert(multiplication.end(), ((k[1][0] * c[0]) + (k[1][1] * c[1])));
	return multiplication;
}

// Encrypts the plaintext into cyphertext
string HillCypher::encryptPlainText(vector< vector<int> > key, string pt)
{
	string cyphertext;
	vector<int> encryption;
	vector<int> vec;

	int len = pt.length();

	// If string length is odd number, add on a space to end of plaintext
	if (len % 2 != 0) {
		pt = pt += " ";
		len++;
	}
	// If even, then do nothing with plaintext
	else {
		pt = pt;
	}

	// Loop through each char in plaintext
	for (int i = 0; i < len; i++)
	{
		char ch = pt[i];

		// If char is alphanumeric...
		// if (isalpha(ch)) {

		int ich = ch; 
		cout << ch << " > " << ich << endl;

			// Push char to temporary vector
			// ** converts to number, e.g. A=0, Z=25 **
			
			// Not using setNumber so I can convert to ASCII
			vec.push_back(ch);

			// If vector is 2 chars long, encrypt
			if (vec.size() % 2 == 0) {

				// Multiply 2x2 key with 2x1 char matrix
				// and get modulo of result
				encryption = getModulo(matrixMultiply(key, vec));

				// Swap encrypted integer with corresponding
				// letter in the alphabet
				char swapped0 = setLetter(encryption[0]);
				char swapped1 = setLetter(encryption[1]);

				// Add chars to cyphertext string
				cyphertext += swapped0;
				cyphertext += swapped1;

				// Empty the vector
				vec.clear();
			}
		//}
		// If not alphanumeric, add to cyphertext string
		//else {
		//	cyphertext += ch;
		//}
	}
	return cyphertext;
}

//string HillCypher::decryptCypherText(vector< vector<int> > key, string ct)
//{
//
//}

int main()
{
	// Reset random generator to NULL
	srand(time(NULL));

	// Create new Hill Cypher object "myCypher"
	HillCypher myCypher;

	// Create a random 2x2 key matrix
	// vector< vector<int> > key = myCypher.setKey();

	vector< vector<int> > key(2, vector<int>(2));

	key[0][0] = 3;
	key[0][1] = 3;
	key[1][0] = 2;
	key[1][1] = 5;

	// 	cout << "Key 2 :\n";
	// 	cout << "( " << key[0][0] << " " << key[0][1] << " )\n";
	// 	cout << "( " << key[1][0] << " " << key[1][1] << " )\n\n";


	// Get the user's input (plaintext)
	string plaintext = myCypher.getInput();

	// Encrypt the plaintext
	string cyphertext = myCypher.encryptPlainText(key, plaintext);

	// Print the cyphertext to console
	cout << "Cypher text:\n" << cyphertext << endl;

	// Invert key
	vector< vector<float> > inverse(2, vector<float>(2));
	inverse = invertMatrix(key);

	cout << inverse[0][0] << endl;
	cout << inverse[0][1] << endl;
	cout << inverse[1][0] << endl;
	cout << inverse[1][1] << endl;

	float determinant = getDeterminant(key);
	//cout << "Det: " << determinant << endl;

	//cout << "Multiply by Inverse: " << determinant * (1 / determinant) << endl;

	// det * ? = 1 mod 26

	// for (int g=0; g)


	//cout << fmod((inverse[0][0]), 26) << endl;
	//cout << fmod((inverse[0][1]), 26) << endl;
	//cout << fmod((inverse[1][0]), 26) << endl;
	//cout << fmod((inverse[1][1]), 26) << endl;

	//// Decrypt the cyphertext
	//string plain = myCypher.decryptCypherText(key, cyphertext);

	//// Print the cyphertext to console
	//cout << "Plain text:\n" << plain << endl;
}