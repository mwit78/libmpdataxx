/** 
 * @file
 * @copyright University of Warsaw
 * @section LICENSE
 * GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
 */

// (<> should be used instead of "" in normal usage)
//#include "advoocat/mpdata_3d.hpp"
#include "advoocat/solvers/donorcell_3d.hpp"
#include "advoocat/bcond/cyclic_3d.hpp"
#include "advoocat/concurr/openmp.hpp"

enum {x, y, z};

int main() 
{
  using namespace advoocat;

  int n[] = {24, 24, 24};
  {
    concurr::openmp<
      advoocat::solvers::donorcell_3d<sharedmem_3d<>>,
      bcond::cyclic,
      bcond::cyclic,
      bcond::cyclic
    > slv(n[x], n[y], n[z]);
  } 
  // TODO: test mpdata
}
