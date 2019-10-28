#ifndef ASVARDEF_H
#define ASVARDEF_H

#include "ASdefinition.h"
#include "ASexpression.h"
#include "AStype.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASvarDef : public ASdefinition
	{
	public:
		ASvarDef(ASexpression* [], int, AStype*);

		ASexpression* getIdentifier(int);
		AStype* getType();
		std::string toString();
		int getNumIdentifiers();

	private:
		ASexpression* identifierList[MAX_STATEMENTS];
		int numIdentifiers;
		AStype* type;
	};

}
#endif
