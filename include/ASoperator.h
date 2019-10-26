#ifndef ASOPERATOR_H
#define ASOPERATOR_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum operType
	{
		ADDoper, SUBoper, MULoper, DIVoper,
		MODoper, ORoper, ANDoper, LTEToper,
		LToper, EQoper, GToper, GTEToper,
		NEQoper, ASSIGNoper
	};

	class ASoperator :public ASabstractSyntax
	{
	public:
		std::string toString();
		enum operType getType();
		void setType(enum operType);
		std::string toTypeString(enum operType);
	private:
		enum operType type;
	};

}
#endif
