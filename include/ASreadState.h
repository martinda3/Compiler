#ifndef ASWRITESTATE_H
#define ASWRITESTATE_H

#include "ASstatement.h"
#include "ASsimpleExpr.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASreadState : public ASstatement
	{
	public:
		ASreadState(ASsimpleExpr* [], int);

		ASsimpleExpr* getIdentifier(int);
		std::string toString();
		int getNumIdentifiers();

	private:
		ASsimpleExpr* identifierList[MAX_STATEMENTS];
		int numIdentifiers;
	};

}
#endif
