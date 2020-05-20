#ifndef _SQLCONSTANTS_H_
#define _SQLCONSTANTS_H_
/**************************************************
* File: sqlConstants.h.
* Desc: Definitions of the constants values used in SQL terms.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation..
**************************************************/

class JCSqlConstants : public AkObject {
  public:
    enum SetQuantifier {
	noSetQuantifier, distinctElements, allElements,
	some, any
    };
    enum TruthValues {
	tvTrue, tvFalse, tvUnknown
    };
    enum SortOrder {
	ascending, descending
    };
    enum FetchOrder {
	foNatural, foNext, foPrior, foFirst, foLast, foAbsolute, foRelative
    };

};


#endif		/* _SQLCONSTANTS_H_ */
