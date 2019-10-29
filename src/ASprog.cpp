/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASprog.h"
#include "TCoutput.h"

namespace toyc
{
	ASprog::ASprog(std::string n, ASdefinition* definitions[], int num)
	{
		for (int i = 0; i < num; i++)
		{
			definitionList[i] = definitions[i];
		}
		numDefinitions = num;
		name = n;
		setType(PROGprog);
	}

	std::string ASprog::toString()
	{
		if (numDefinitions == 0) return "program([])";
		std::string s = "<< Abstract Syntax >>\nprogram(\n";
		indent();
		s += spaces() + "sourceCodeFile(" + name + "),\n";
		s += spaces() + "[\n";
		indent();
		if (numDefinitions > 0)
		{
			s += (definitionList[0]->toString());
			for (int i = 1; i < numDefinitions; i++)
			{
				s += "\n" + definitionList[i]->toString();
			}
		}
		outdent();
		s += "\n" + spaces() + "]\n";
		outdent();
		s += ")\n<< Abstract Syntax >>\n";
		return s;
	}

	ASdefinition* ASprog::getDefinition(int num)
	{
		return definitionList[num];
	}
	int ASprog::getNumDefinitions()
	{
		return numDefinitions;
	}
}