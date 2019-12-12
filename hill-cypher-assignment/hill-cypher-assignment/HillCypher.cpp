// Hill Cypher Class
#include "HillCypher.h"

/*
 *		getInput func
 *
 *		Gets the input from the user via the console
 */
string HillCypher::getInput()
{
	string input;
	cout << "Enter Message   =>     ";
	getline(cin, input);
	cout << endl;
	return input;
}

/*
 *		getMatrixModulo func
 *
 *		Gets the modulo of each value in a 2x1 matrix
 *		Gets modulo 128 because cypher encrypts all chars into corresponding ASCII values
 */
vector<int> HillCypher::getMatrixModulo(vector<int> v)
{
	vector<int> modulo;
	modulo.insert(modulo.begin(), (v[0] % 128));
	modulo.insert(modulo.end(), (v[1] % 128));
	return modulo;
}

/*
 *		matrixMultiply func
 *
 *		Multiplies the 2x2 key matrix by each 2x1 character matrix
 */
vector<int> HillCypher::matrixMultiply(vector< vector<int> > k, vector<int> c)
{
	vector<int> multiplication;
	multiplication.insert(multiplication.begin(), ((k[0][0] * c[0]) + (k[0][1] * c[1])));
	multiplication.insert(multiplication.end(), ((k[1][0] * c[0]) + (k[1][1] * c[1])));
	return multiplication;
}

/*
 *		 encryptPlainText func
 * 
 *		Encrypts the plain text and returns cypher text
 *		If plain text length is odd number, add a space to the end
 *		Loops through each char pushes every two chars (as ASCII ints) to temporary vector
 *		Encrypts every two chars in temp vector by:
 *			1. Multiplying 2x2 key matrix by 2x1 char matrix
			2. Inserting answer into encryption matrix
			3. Getting modulo 128 of each value in encryption matrix (because ASCII values)
			4. Swapping each int in encryption matrix to the corresponding ASCII char
			5. Adding the char to cyphertext string
 */
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

/*
 *		decryptCypherText func
 *
 *		Decrypts the cypher text and returns plain text
 *		If cypher text length is odd number, add a space to the end (this should never happen)
 *		Reverses the encryption process
 */
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

