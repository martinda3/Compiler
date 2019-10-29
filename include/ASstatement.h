/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASSTATEMENT_H
#define ASSTATEMENT_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum stateType
	{
		EXPRstate, BREAKstate, BLOCKstate, IFstate,
		NULLstate, RETURNstate, WHILEstate, READstate,
		WRITEstate, NEWLINEstate, EMPTYstate
	};

	class ASstatement : public ASabstractSyntax
	{
	public:
		ASstatement();
		virtual std::string toString();

		enum stateType getType();

		void setType(enum stateType);

		std::string toTypeString(enum stateType);

	private:
		enum stateType type;
	};

}
#endif
