#ifndef ASEXPRSTATE_H
#define ASEXPRSTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{
	class ASexprState : public ASstatement
	{
	public:
		ASexprState(ASexpression*);
		std::string toString();

		ASexpression* getOp();

	private:
		ASexpression* op;
		std::string s;
	};

}
#endif
