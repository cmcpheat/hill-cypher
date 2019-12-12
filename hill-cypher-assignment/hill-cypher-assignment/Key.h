#ifndef KEY_H
#define KEY_H

#include <iostream>
#include <string>
#include <locale>
#include <vector>

using namespace std;

class Key
{
private:
	Key();
	static Key* k;
	int determinant = 0;
	vector< vector<int> > key;
	vector< vector<int> > inverseKey;
public:
	int getDeterminant(vector < vector<int> >);
	vector< vector<int> > setKey();
	vector< vector<int> > setInverseKey(vector< vector<int> >);
	bool checkMatrixIsInvertible(vector< vector<int> >);

	Key(const Key&) = delete;
	Key& operator=(const Key&) = delete;

	~Key();

	static Key* getInstance();
};

#endif // !KEY_H