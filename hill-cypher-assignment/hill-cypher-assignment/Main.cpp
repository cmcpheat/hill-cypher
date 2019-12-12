#include "HillCypher.h"
#include "Key.h"
#include <iostream>
#include <locale>

using namespace std;

int main()
{
	// Reset random generator to NULL
	srand(time(NULL));

	// Create new Hill Cypher object "hillCypherObject"
	HillCypher hillCypherObject;

	// Call Key Singleton getInstance and
	// create a random 2x2 key matrix
	vector< vector<int> > key = Key::getInstance()->setKey();

	cout << "Random Key :\n";
	cout << "( " << key[0][0] << " " << key[0][1] << " )\n";
	cout << "( " << key[1][0] << " " << key[1][1] << " )\n\n";

	// Get the user's input (plaintext)
	string input = hillCypherObject.getInput();

	cout << "Press Enter to begin the encryption...\n";
	cin.get();

	// Encrypt the plaintext
	string cyphertext = hillCypherObject.encryptPlainText(key, input);

	// Print the cyphertext to console
	cout << "Encryption      =>     " << cyphertext << endl << endl;
		
	// Invert key
	vector< vector<int> > inverseKey(2, vector<int>(2));
	inverseKey = Key::getInstance()->setInverseKey(key);

	cout << "Press Enter to begin the decryption...\n";
	cin.get();

	// Decrypt the cyphertext
	string plain = hillCypherObject.decryptCypherText(inverseKey, cyphertext);

	// Print the cyphertext to console
	cout << "Decryption      =>     " << plain << endl;
	// Print the cyphertext to console
	cout << "User's Input    =>     " << input << endl;
	
	return 0;
}