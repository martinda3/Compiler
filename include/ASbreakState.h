/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASBREAKSTATE_H
#define ASBREAKSTATE_H

#include "ASstatement.h"

namespace toyc
{

	class ASbreakState :public ASstatement
	{
	public:
		ASbreakState();
		std::string toString();
	};

}
#endif
