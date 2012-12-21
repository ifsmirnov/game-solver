#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <utility>
#include <set>

#include "const.h"
#define m_assert(expr, msg) if (! (expr) ) {std :: cerr << #msg << std :: endl << __FILE__ << ", line #" << __LINE__ << std :: endl; exit(1);}

namespace is_interactor {

typedef std :: set<std :: pair<int, int> > t_cells_list;
typedef unsigned t_coord;

std :: pair<bool, std :: pair<t_cells_list, t_cells_list> > determine (t_field, int);
std :: pair<int, int> getFreeNearby(const t_field&, t_coord, t_coord);

} // is_interactor

#endif
