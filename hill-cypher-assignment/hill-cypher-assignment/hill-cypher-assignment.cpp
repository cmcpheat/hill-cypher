// Hill Cypher
#include <iostream>
#include <string>
#include <locale>
#include <vector>

// decryption video - https ://www.youtube.com/watch?v=kfmNeskzs2o

using namespace std;


class HillCypher
{
public:
	int getDeterminant(vector < vector<int> >);
	string getInput();
	vector< vector<int> > setKey();
	vector< vector<int> > setInverseKey(vector< vector<int> >);
	vector<int> getMatrixModulo(vector<int>);
	vector<int> matrixMultiply(vector< vector<int> >, vector<int>);
	string encryptPlainText(vector< vector<int> >, string);
	string decryptCypherText(vector< vector<int> >, string);
	bool checkMatrixIsInvertible(vector< vector<int> >);

private:
	int determinant;
	string input;
	string cyphertext;
	string plaintext;
	vector<int> modulo;
	vector<int> multiplication;
	vector< vector<int> > key;
	vector< vector<int> > inverseKey;
};

// Matrix modulo operation
vector<int> HillCypher::getMatrixModulo(vector<int> v)
{
	vector<int> modulo;
	modulo.insert(modulo.begin(), (v[0] % 128));
	modulo.insert(modulo.end(), (v[1] % 128));
	return modulo;
}

// Asks user to enter a plain text message
string HillCypher::getInput()
{
	string input;
	cout << "Enter Message   =>     ";
	getline(cin, input);
	cout << endl;
	return input;
}

// Checks if determinant of matrix is odd number between 1-25
bool HillCypher::checkMatrixIsInvertible(vector< vector<int> > v)
{
	int det = getDeterminant(v);

	if (det >= 1 && det <= 25 && det % 2 != 0) {
		return true;
	}
	else {
		return false;
	}
}

int HillCypher::getDeterminant(vector< vector<int> > v)
{
	int determinant = ((v[0][0] * v[1][1]) - (v[0][1] * v[1][0]));
	return determinant;
}

// Generates random 2x2 key vector matrix
vector< vector<int> > HillCypher::setKey()
{
	bool invertible = false;
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

		if (checkMatrixIsInvertible(key) == true) {
			invertible = true;
		}
		else {
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
	modInverse[0][0] = ((v[1][1] % 128 + 128) % 128);
	modInverse[0][1] = ((-(v[0][1]) % 128 + 128) % 128);
	modInverse[1][0] = ((-(v[1][0]) % 128 + 128) % 128);
	modInverse[1][1] = ((v[0][0]) % 128 + 128) % 128;

	// Caculate determinant of key
	int determinant = getDeterminant(v);

	// Calculate inverse key matrix
	float f = 1 / (static_cast<float>(determinant));
	int detInverse = static_cast<int>(determinant * f);
	int i = 0;

	while ((determinant * i) % 128 != detInverse) {
		i++;
	}

	inverseKey[0][0] = (((modInverse[0][0] * i) % 128 + 128) % 128);
	inverseKey[0][1] = (((modInverse[0][1] * i) % 128 + 128) % 128);
	inverseKey[1][0] = (((modInverse[1][0] * i) % 128 + 128) % 128);
	inverseKey[1][1] = (((modInverse[1][1] * i) % 128 + 128) % 128);

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

		int ich = ch;

		// Push char to temporary vector
		// ** converts to ASCII char **
		vec.push_back(ich);

		// If vector is 2 chars long, encrypt
		if (vec.size() % 2 == 0) {

			// Multiply 2x2 key with 2x1 char matrix
			// and get modulo of result
			encryption = getMatrixModulo(matrixMultiply(key, vec));

			// Swap encrypted integer with corresponding
			// letter in the alphabet
			char c0 = encryption[0];
			char c1 = encryption[1];

			// Add chars to cyphertext string
			cyphertext += c0;
			cyphertext += c1;

			// Empty the vector
			vec.clear();
		}
	}
	return cyphertext;
}

// Decrypts cypher text into plain text
// Takes inverse key and cypher text string
string HillCypher::decryptCypherText(vector< vector<int> > ik, string ct)
{
	string plaintext;
	vector<int> decryption;
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

		int ich = ch;

		// Push char to temporary vector
		// ** converts to ASCII char **
		vec.push_back(ich);

		// If vector is 2 chars long, encrypt
		if (vec.size() % 2 == 0) {

			// Multiply 2x2 inverse key with 2x1 char matrix
			// and get modulo of result

			decryption = getMatrixModulo(matrixMultiply(ik, vec));

			char c0 = decryption[0];
			char c1 = decryption[1];

			// Add chars to cyphertext string
			plaintext += c0;
			plaintext += c1;

			// Empty the vector
			vec.clear();
		}
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

	cout << "Key :\n";
	cout << "( " << key[0][0] << " " << key[0][1] << " )\n";
	cout << "( " << key[1][0] << " " << key[1][1] << " )\n\n";

	// Get the user's input (plaintext)
	string input = hillCypherObj.getInput();

	cout << "Press Enter to begin the encryption...\n";
	cin.get();

	// Encrypt the plaintext
	string cyphertext = hillCypherObj.encryptPlainText(key, input);

	// Print the cyphertext to console
	cout << "Encryption      =>     " << cyphertext << endl << endl;

	// Invert key
	vector< vector<int> > inverseKey(2, vector<int>(2));
	inverseKey = hillCypherObj.setInverseKey(key);

	cout << "Press Enter to begin the decryption...\n";
	cin.get();

	// Decrypt the cyphertext
	string plain = hillCypherObj.decryptCypherText(inverseKey, cyphertext);

	// Print the cyphertext to console
	cout << "Decryption      =>     " << plain << endl;
	// Print the cyphertext to console
	cout << "User's Input    =>     " << input << endl;
}
