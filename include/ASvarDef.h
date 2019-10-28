#ifndef ASVARDEF_H
#define ASVARDEF_H

#include "ASdefinition.h"
#include "ASsimpleExpr.h"
#include "AStype.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASvarDef : public ASdefinition
	{
	public:
		ASvarDef(ASsimpleExpr* [], int, AStype*);

		ASsimpleExpr* getIdentifier(int);
		AStype* getType();
		std::string toString();
		int getNumIdentifiers();

	private:
		ASsimpleExpr* identifierList[MAX_STATEMENTS];
		int numIdentifiers;
		AStype* type;
	};

}
#endif
