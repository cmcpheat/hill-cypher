#ifndef HILLCYPHER_H
#define HILLCYPHER_H

#include <iostream>
#include <string>
#include <locale>
#include <vector>
using namespace std;

class HillCypher
{
public:
	string getInput();
	vector<int> getMatrixModulo(vector<int>);
	vector<int> matrixMultiply(vector< vector<int> >, vector<int>);
	string encryptPlainText(vector< vector<int> >, string);
	string decryptCypherText(vector< vector<int> >, string);

private:
	string input;
	string cyphertext;
	string plaintext;
	vector<int> modulo;
	vector<int> multiplication;
};

#endif // !HILLCYPHER_H