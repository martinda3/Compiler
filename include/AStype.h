#ifndef ASTYPE_H
#define ASTYPE_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum typeType // well this name is dumb :)
	{
		INTtype, CHARtype
	};

	class AStype : public ASabstractSyntax
	{
	public:
		AStype(enum typeType);
		std::string toString();
		enum typeType getType();
		void setType(enum typeType);
		std::string toTypeString(enum typeType);
	private:
		enum typeType type;

	};

}
#endif
