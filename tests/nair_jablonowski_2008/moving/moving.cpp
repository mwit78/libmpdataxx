#include <libmpdata++/solvers/mpdata.hpp>
using namespace libmpdataxx;

#include "../common/convergence.hpp"
#include "../../mp3_paper_JCP/moving_vort/test_def.hpp"

int main()
{
  const bool var_dt = true;
  const T max_cfl = 0.99;
  {
    enum { opts = opts::nug };
    const int opts_iters = 2;
    convergence(test<var_dt, opts, opts_iters>, "nug_i2", max_cfl);
  }
  
  {
    enum { opts = opts::nug | opts::iga | opts::fct};
    const int opts_iters = 2;
    convergence(test<var_dt, opts, opts_iters>, "nug_iga_fct_i2", max_cfl);
  }
}

