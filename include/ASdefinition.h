/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Modifed By: Dajion Martin

 */

#ifndef ASDEFINITION_H
#define ASDEFINITION_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum defType
	{
		FUNCdef, VARdef
	};

	class ASdefinition : public ASabstractSyntax
	{
	public:
		virtual std::string toString() = 0;

		enum defType getType();

		void setType(enum defType);

		std::string toTypeString();

	private:
		enum defType type;
	};

}
#endif
