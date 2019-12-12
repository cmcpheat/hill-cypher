// Key Class
#include "Key.h"

// Initially sets the ptr to the Key object to NULL
Key* Key::k = nullptr;

/*
 *		Key() constructor
 *
 *		Singleton design pattern
 *		When getInstance() is called it constructs key vector
 */
Key::Key()
	: key(setKey())
{

}

/*
 *		Key() destructor
 *
 *		Singleton design pattern
 *		When the program ends the single instance of Key is deleted
 *		And ptr is set to NULL
 */
Key::~Key()
{
	if (k)
	{
		delete k;
		k = nullptr;
	}
}

/*		getInstance func
 *
 *		Singleton design pattern
 *		Returns the only object / instance of the Key class
 */
Key* Key::getInstance()
{
	if (!k)
	{
		k = new Key;
	}
	return k;
}

/*		setKey func
 *
 *		Generates random 2x2 key matrix
 */
vector< vector<int> > Key::setKey()
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

/*		getDeterminant func
 *
 *		Gets the determinant of a 2x2 matrix
 */
int Key::getDeterminant(vector< vector<int> > v)
{
	int determinant = ((v[0][0] * v[1][1]) - (v[0][1] * v[1][0]));
	return determinant;
}

/*		setInverseKey func
 *
 *		Inverts the key matrix for decryption
 */
vector< vector<int> > Key::setInverseKey(vector < vector<int> > v)
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


/*		checkMatrixIsInvertible func
 *
 *		 Checks whether a matrix is invertible or not
 */
bool Key::checkMatrixIsInvertible(vector< vector<int> > v)
{
	int det = getDeterminant(v);

	if (det >= 1 && det <= 127 && det % 2 != 0) {
		return true;
	}
	else {
		return false;
	}
}