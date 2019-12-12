#ifndef KEY_H
#define KEY_H

#include <iostream>
#include <string>
#include <locale>
#include <vector>

using namespace std;

class Key
{
public:
	int getDeterminant(vector < vector<int> >);
	vector< vector<int> > setKey();
	vector< vector<int> > setInverseKey(vector< vector<int> >);
	bool checkMatrixIsInvertible(vector< vector<int> >);

private:
	int determinant;
	vector< vector<int> > key;
	vector< vector<int> > inverseKey;
};

#endif // !KEY_H