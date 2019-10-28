#include <iostream>
#include "ASoperator.h"

namespace toyc
{
	ASoperator::ASoperator(enum operType t)
	{
		type = t;

	}

	enum operType ASoperator::getType() { return type; }
	void ASoperator::setType(enum operType t) { type = t; }
	std::string ASoperator::toString()
	{
		std::string s;
		switch (type)
		{
			case ADDoper:		s = " + ";			break;
			case SUBoper:		s = " - ";			break;
			case MULoper:		s = " * ";			break;
			case DIVoper:		s = " / ";			break;
			case MODoper:		s = " % ";			break;
			case ORoper:		s = " || ";			break;
			case ANDoper:		s = " && ";			break;
			case LTEToper:		s = " <= ";			break;
			case LToper:		s = " < ";			break;
			case EQoper:		s = " == ";			break;
			case GToper:		s = " > ";			break;
			case GTEToper:		s = " >= ";			break;
			case NEQoper:		s = " != ";			break;
			case ASSIGNoper:	s = " = ";			break;
			default:			s = "error";		break;
		}
		return s;
	}
	std::string ASoperator::toTypeString(enum operType)
	{
		std::string s;
		switch (type)
		{
			case ADDoper:		s = "ADDoper";			break;
			case SUBoper:		s = "SUBoper";			break;
			case MULoper:		s = "MULoper";			break;
			case DIVoper:		s = "DIVoper";			break;
			case MODoper:		s = "MODoper";			break;
			case ORoper:		s = "ORoper";			break;
			case ANDoper:		s = "ANDoper";			break;
			case LTEToper:		s = "LTEToper";			break;
			case LToper:		s = "LToper";			break;
			case EQoper:		s = "EQoper";			break;
			case GToper:		s = "GToper";			break;
			case GTEToper:		s = "GTEToper";			break;
			case NEQoper:		s = "NEQoper";			break;
			case ASSIGNoper:	s = "ASSIGNoper";		break;
			default:			s = "error";			break;
		}
		return s;
	}
}
