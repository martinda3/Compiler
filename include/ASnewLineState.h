/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASNEWLINESTATE_H
#define ASNEWLINESTATE_H

#include "ASstatement.h"

namespace toyc
{

	class ASnewLineState :public ASstatement
	{
	public:
		ASnewLineState();
		std::string toString();
	};

}
#endif
