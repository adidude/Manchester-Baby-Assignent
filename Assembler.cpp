/*
	Name: Aditya Kumar Menon
	Matriculation Number: 170025886
	Module: AC21009
*/

#include "Structures.h"

int main() 
{

	ifstream yolo = getFile();
	string line;
	for (int i = 0; i < 3; ++i)
	{
		getline(yolo, line);
		for (unsigned int j = 0; j < line.size(); ++j)
		{
			cout << line[j] << endl;
		}	
	}
	yolo.close();

	return 0;
}