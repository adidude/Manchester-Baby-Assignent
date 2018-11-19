/*
	Name: Aditya Kumar Menon
	Matriculation Number: 170025886
	Module: AC21009
*/

#include "Structures.h"

void translate()
{
	SymblTable table;
	table.initTable();
    table.convertToEndian();
}

int main() 
{
	translate();

	return 0;
}