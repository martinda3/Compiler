/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASNULLSTATE_H
#define ASNULLSTATE_H

#include "ASstatement.h"

namespace toyc
{

	class ASnullState :public ASstatement
	{
	public:
		ASnullState();
		std::string toString();
	};

}
#endif
