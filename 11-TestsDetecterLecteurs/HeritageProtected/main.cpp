#include <iostream>

using namespace std;

class Father
{
	protected:
		void father() { cout << "Father::father" << endl; }
};

class Son : protected Father
{
	protected:
		void son() { cout << "Son::son()" << endl; }
};

class Grandson : public Son
{
	public:
		void grandson() { cout << "Grandson::grandson()" << endl; son(); father(); }
};

int main()
{
	Grandson grandson;
	grandson.grandson();

	return 0;
}
