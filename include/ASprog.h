/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASPROG_H
#define ASPROG_H

#include "ASabstractSyntax.h"
#include "ASprogram.h"
#include "ASprog.h"
#include "ASdefinition.h"
#include "TCtoken.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASprog :public ASprogram
	{
	public:
		ASprog(std::string, ASdefinition* [], int);
		std::string toString();

		ASdefinition* getDefinition(int);
        ASdefinition **getDefinition();
        std::string getName();
		int getNumDefinitions();

	private:
		ASdefinition* definitionList[MAX_STATEMENTS];
		int numDefinitions;
		std::string name;
	};

}
#endif
