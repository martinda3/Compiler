/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASRETURNSTATE_H
#define ASRETURNSTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{
	class ASreturnState : public ASstatement
	{
	public:
		ASreturnState(ASexpression*);
		ASreturnState();
		std::string toString();

		ASexpression* getOp();

	private:
		ASexpression* op;
		std::string s;
		bool hasop;
	};

}
#endif
