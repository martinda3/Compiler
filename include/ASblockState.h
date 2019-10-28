#ifndef ASBLOCKSTATE_H
#define ASBLOCKSTATE_H

#include "ASstatement.h"
#include "ASsimpleExpr.h"
#include "AStype.h"
#include "ASvarDef.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASblockState : public ASstatement
	{
	public:
		ASblockState(ASvarDef* [], int, ASstatement* [], int);

		ASvarDef* getVarDef(int);
		ASstatement* getStatement(int);
		std::string toString();
		int getNumVarDef();
		int getNumStatement();

	private:
		ASvarDef* varDefList[MAX_STATEMENTS];
		int numVarDef;
		ASstatement* statementList[MAX_STATEMENTS];
		int numStatements;
	};

}
#endif
