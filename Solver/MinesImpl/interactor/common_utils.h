#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <iostream>

#include "const.h"
#define m_assert(expr, msg) if (! (expr) ) {std :: cerr << #msg << std :: endl << __FILE__ << ", line #" << __LINE__ << std :: endl; exit(1);}

namespace is_interactor {

void writeField (const t_field&, std :: ostream& = std :: cout);
t_field readField (std :: istream& = std :: cin);

} // is_interactor

#endif
