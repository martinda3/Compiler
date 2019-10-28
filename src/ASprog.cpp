#include <iostream>

#include "ASprog.h"
#include "TCoutput.h"

namespace toyc
{
	ASprog::ASprog(ASdefinition* definitions[], int num)
	{
		for (int i = 0; i < num; i++)
		{
			definitionList[i] = definitions[i];
		}
		numDefinitions = num;
		setType(PROGprog);
	}

	std::string ASprog::toString() // stole this from Toycalc (ASprogram.cpp), hope it works
	{
		if (numDefinitions == 0) return "prog([])";
		std::string s = "prog(\n";
		indent();
		//s += spaces() + name + ",\n";
		s += spaces() + "[\n";
		indent();
		if (numDefinitions > 0)
		{
			s += (spaces() + definitionList[0]->toString());
			for (int i = 1; i < numDefinitions; i++)
				s += ",\n" + spaces() + definitionList[i]->toString();
		}
		outdent();
		s += "\n" + spaces() + "]\n";
		outdent();
		s += spaces() + ")\n";
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