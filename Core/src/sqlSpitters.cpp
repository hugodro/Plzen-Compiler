/**************************************************
* File: sqlSpitters.cc.
* Desc: Definition of the spitters tools.
* Module: AkraLog : JavaKit.
* Rev: 21 mai 1998 : REV 0 : Hugo DesRosiers : Creation..
**************************************************/

#include "sqlSpitters.h"


/**************************************************
* Implementation: JCSqlTokens.
**************************************************/

JCSqlTokens::Tokens JCSqlTokens::mapOperToToken(JCSqlOperExpr::Operators anOper)
{
    switch(anOper) {
	case JCSqlOperExpr::add:
	    return addOp;
	    break;
	case JCSqlOperExpr::andOp:
	    return andOp;
	    break;
	case JCSqlOperExpr::between:
	    return betweenOp;
	    break;
	case JCSqlOperExpr::divide:
	    return divideOp;
	    break;
	case JCSqlOperExpr::eqAll:
	    return eqAllOp;
	    break;
	case JCSqlOperExpr::eqAny:
	    return eqAnyOp;
	    break;
	case JCSqlOperExpr::eqSome:
	    return eqSomeOp;
	    break;
	case JCSqlOperExpr::equal:
	    return equalOp;
	    break;
	case JCSqlOperExpr::escape:
	    return escapeOp;
	    break;
	case JCSqlOperExpr::exists:
	    return existsOp;
	    break;
	case JCSqlOperExpr::ge:
	    return geOp;
	    break;
	case JCSqlOperExpr::geAll:
	    return geAllOp;
	    break;
	case JCSqlOperExpr::geAny:
	    return geAnyOp;
	    break;
	case JCSqlOperExpr::geSome:
	    return geSomeOp;
	    break;
	case JCSqlOperExpr::gt:
	    return gtOp;
	    break;
	case JCSqlOperExpr::gtAll:
	    return gtAllOp;
	    break;
	case JCSqlOperExpr::gtAny:
	    return gtAnyOp;
	    break;
	case JCSqlOperExpr::gtSome:
	    return gtSomeOp;
	    break;
	case JCSqlOperExpr::in:
	    return inOp;
	    break;
	case JCSqlOperExpr::is:
	    return isOp;
	    break;
	case JCSqlOperExpr::isnot:
	    return isnotOp;
	    break;
	case JCSqlOperExpr::le:
	    return leOp;
	    break;
	case JCSqlOperExpr::leAll:
	    return leAllOp;
	    break;
	case JCSqlOperExpr::leAny:
	    return leAnyOp;
	    break;
	case JCSqlOperExpr::leSome:
	    return leSomeOp;
	    break;
	case JCSqlOperExpr::like:
	    return likeOp;
	    break;
	case JCSqlOperExpr::lt:
	    return ltOp;
	    break;
	case JCSqlOperExpr::ltAll:
	    return ltAllOp;
	    break;
	case JCSqlOperExpr::ltAny:
	    return ltAnyOp;
	    break;
	case JCSqlOperExpr::ltSome:
	    return ltSomeOp;
	    break;
	case JCSqlOperExpr::match:
	    return matchOp;
	    break;
	case JCSqlOperExpr::matchFull:
	    return matchFullOp;
	    break;
	case JCSqlOperExpr::matchPartial:
	    return matchPartialOp;
	    break;
	case JCSqlOperExpr::matchUniFull:
	    return matchUniFullOp;
	    break;
	case JCSqlOperExpr::matchUniPartial:
	    return matchUniPartialOp;
	    break;
	case JCSqlOperExpr::matchUnique:
	    return matchUniqueOp;
	    break;
	case JCSqlOperExpr::multiply:
	    return multiplyOp;
	    break;
	case JCSqlOperExpr::neAll:
	    return neAllOp;
	    break;
	case JCSqlOperExpr::neAny:
	    return neAnyOp;
	    break;
	case JCSqlOperExpr::neSome:
	    return neSomeOp;
	    break;
	case JCSqlOperExpr::negate:
	    return negateOp;
	    break;
	case JCSqlOperExpr::notOp:
	    return notOp;
	    break;
	case JCSqlOperExpr::notBetween:
	    return notBetweenOp;
	    break;
	case JCSqlOperExpr::notEqual:
	    return notEqualOp;
	    break;
	case JCSqlOperExpr::notIn:
	    return notInOp;
	    break;
	case JCSqlOperExpr::notLike:
	    return notLikeOp;
	    break;
	case JCSqlOperExpr::orOp:
	    return orOp;
	    break;
	case JCSqlOperExpr::overlaps:
	    return overlapsOp;
	    break;
	case JCSqlOperExpr::parenthesis:
	    return parenthesisOp;
	    break;
	case JCSqlOperExpr::posate:
	    return posateOp;
	    break;
	case JCSqlOperExpr::substract:
	    return substractOp;
	    break;
	case JCSqlOperExpr::unique:
	    return uniqueOp;
	    break;
	case JCSqlOperExpr::userDefined:
	    return userDefinedOp;
	    break;
    }

    return userDefinedOp;	// This should not happen...
}

