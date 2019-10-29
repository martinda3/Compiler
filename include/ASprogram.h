/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASPROGRAM_H
#define ASPROGRAM_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum progType
	{
		PROGprog // This probably has no reason to exist, but i am keeping it anyway
	};

	class ASprogram : public ASabstractSyntax
	{
	public:
		virtual std::string toString() = 0;

		enum progType getType();

		void setType(enum progType);

		std::string toTypeString(enum progType);

	private:
		enum progType type;
	};

}
#endif
