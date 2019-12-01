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
	char setLetter(int);
	int setNumber(char);
	string getInput();
	vector< vector<int> > setKey();
	vector< vector<int> > setInverseKey(vector< vector<int> >);
	vector<int> getMatrixModulo(vector<int>);
	vector<int> matrixMultiply(vector< vector<int> >, vector<int>);
	string encryptPlainText(vector< vector<int> >, string);
	string decryptCypherText(vector< vector<int> >, string);
	bool checkMatrixIsInvertible(vector< vector<int> >);

private:
	char letter;
	int determinant;
	string input;
	string cyphertext;
	string plaintext;
	vector<int> modulo;
	vector<int> multiplication;
	vector< vector<int> > key;
	vector< vector<int> > inverseKey;
};

// Swaps num to corresponding letter in alphabet (e.g. 0=A, 25=Z)
char HillCypher::setLetter(int n)
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
vector<int> HillCypher::getMatrixModulo(vector<int> v)
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
	int invertible = false;
	vector< vector<int> > key(2, vector<int>(2));

	while (invertible == false)
	{
		int r, c;

		for (r = 0; r < 2; r++)
		{
			for (c = 0; c < 2; c++)
			{
				key[r][c] = int(rand() % 10 + 1);
			}
		}

		cout << "Key :\n";
		cout << "( " << key[0][0] << " " << key[0][1] << " )\n";
		cout << "( " << key[1][0] << " " << key[1][1] << " )\n\n";

		if (checkMatrixIsInvertible(key) == true) {
			cout << "Key is invertible\n" << endl;
			invertible = true;
		}
		else {
			cout << "Key is NOT invertible\n" << endl;
			invertible = false;
		}
	}

	return key;
}

vector< vector<int> > HillCypher::setInverseKey(vector < vector<int> > v)
{
	vector< vector<int> > modInverse(2, vector<int>(2));
	vector< vector<int> > inverseKey(2, vector<int>(2));

	// Invert the key and perform modulo
	modInverse[0][0] = ((v[1][1] % 26 + 26) % 26);
	modInverse[0][1] = ((-(v[0][1]) % 26 + 26) % 26);
	modInverse[1][0] = ((-(v[1][0]) % 26 + 26) % 26);
	modInverse[1][1] = ((v[0][0]) % 26 + 26) % 26;

	// Caculate determinant of key
	int determinant = ((v[0][0] * v[1][1]) - (v[0][1] * v[1][0]));

	// Calculate inverse key matrix
	float f = 1 / (static_cast<float>(determinant));
	int detInverse = static_cast<int>(determinant * f);
	int i = 0;

	while ((determinant * i) % 26 != detInverse)
		i++;

	inverseKey[0][0] = (((modInverse[0][0] * i) % 26 + 26) % 26);
	inverseKey[0][1] = (((modInverse[0][1] * i) % 26 + 26) % 26);
	inverseKey[1][0] = (((modInverse[1][0] * i) % 26 + 26) % 26);
	inverseKey[1][1] = (((modInverse[1][1] * i) % 26 + 26) % 26);

	return inverseKey;
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

	// Length of plain text string
	// Static cast to prevent loss of data
	int len = static_cast<int>(pt.length());

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
			vec.push_back(setNumber(ch));

			// If vector is 2 chars long, encrypt
			if (vec.size() % 2 == 0) {

				// Multiply 2x2 key with 2x1 char matrix
				// and get modulo of result
				encryption = getMatrixModulo(matrixMultiply(key, vec));

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

// Decrypts cypher text into plain text
// Takes inverse key and cypher text string
string HillCypher::decryptCypherText(vector< vector<int> > ik, string ct)
{
	string plaintext;
	vector<int> encryption;
	vector<int> vec;

	int len = ct.length();

	// If string length is odd number, add on a space to end of plaintext
	if (len % 2 != 0) {
		ct = ct += " ";
		len++;
	}
	// If even, then do nothing with plaintext
	else {
		ct = ct;
	}

	// Loop through each char in plaintext
	for (int i = 0; i < len; i++)
	{
		char ch = ct[i];

		// If char is alphanumeric...
		// if (isalpha(ch)) {

		int ich = ch;
		cout << ch << " > " << ich << endl;

		// Push char to temporary vector
		// ** converts to number, e.g. A=0, Z=25 **

		// Not using setNumber so I can convert to ASCII
		vec.push_back(setNumber(ch));

		// If vector is 2 chars long, encrypt
		if (vec.size() % 2 == 0) {

			// Multiply 2x2 inverse key with 2x1 char matrix
			// and get modulo of result
			encryption = getMatrixModulo(matrixMultiply(ik, vec));

			// Swap encrypted integer with corresponding
			// letter in the alphabet
			char swapped0 = setLetter(encryption[0]);
			char swapped1 = setLetter(encryption[1]);

			// Add chars to cyphertext string
			plaintext += swapped0;
			plaintext += swapped1;

			// Empty the vector
			vec.clear();
		}
		//}
		// If not alphanumeric, add to cyphertext string
		//else {
		//	cyphertext += ch;
		//}
	}
	return plaintext;
}

int main()
{
	// Reset random generator to NULL
	srand(time(NULL));

	// Create new Hill Cypher object "hillCypherObj"
	HillCypher hillCypherObj;

	// Create a random 2x2 key matrix
	vector< vector<int> > key = hillCypherObj.setKey();

	//vector< vector<int> > key(2, vector<int>(2));

	//key[0][0] = 3;
	//key[0][1] = 3;
	//key[1][0] = 2;
	//key[1][1] = 5;

	cout << "Key 2 :\n";
	cout << "( " << key[0][0] << " " << key[0][1] << " )\n";
	cout << "( " << key[1][0] << " " << key[1][1] << " )\n\n";

	// Get the user's input (plaintext)
	string plaintext = hillCypherObj.getInput();

	// Encrypt the plaintext
	string cyphertext = hillCypherObj.encryptPlainText(key, plaintext);

	// Print the cyphertext to console
	cout << "Cypher text:\n" << cyphertext << endl;

	// Invert key
	vector< vector<int> > inverseKey(2, vector<int>(2));
	inverseKey = hillCypherObj.setInverseKey(key);

	cout << "main 0.0: " << inverseKey[0][0] << endl;
	cout << "main 0.1: " << inverseKey[0][1] << endl;
	cout << "main 1.0: " << inverseKey[1][0] << endl;
	cout << "main 1.1: " << inverseKey[1][1] << endl;

	// Decrypt the cyphertext
	string plain = hillCypherObj.decryptCypherText(inverseKey, cyphertext);

	// Print the cyphertext to console
	cout << "Plain text:\n" << plain << endl;
}