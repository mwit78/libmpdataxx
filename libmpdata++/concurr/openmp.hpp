/** @file
 * @copyright University of Warsaw
 * @section LICENSE
 * GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
 */

#pragma once

#include <libmpdata++/concurr/detail/concurr_common.hpp>

#ifdef _OPENMP
# include <omp.h>
#endif

namespace libmpdataxx
{
  namespace concurr
  {
    template <
      class solver_t,
      bcond::bcond_e bcx,
      bcond::bcond_e bcy = bcond::null,
      bcond::bcond_e bcz = bcond::null
    >
    class openmp : public detail::concurr_common<solver_t, bcx, bcy, bcz>
    {
      using parent_t = detail::concurr_common<solver_t, bcx, bcy, bcz>;
 

      struct mem_t : parent_t::mem_t
      {
        int rank()
        {
#if defined(_OPENMP)
          return omp_get_thread_num();
#else
          return 0;
#endif
        }

	static int size() 
	{
#if defined(_OPENMP)
	  return omp_get_max_threads();
#else
	  return 1;
#endif
	}

        void barrier()
        {
#pragma omp barrier
        }

        // ctors
        mem_t(const int &n_eqs, const std::array<int, solver_t::n_dims> &span) : parent_t::mem_t(n_eqs, span, size()) {};
        //mem_t(const int n_eqs, const int s0, const int s1) : parent_t::mem_t(n_eqs, s0, s1, size()) {};
        //mem_t(const int n_eqs, const int s0, const int s1, const int s2) : parent_t::mem_t(n_eqs, s0, s1, s2, size()) {};
      };

      void solve(int nt)
      {
        int i = 0;
#pragma omp parallel private(i)
        {
#if defined(_OPENMP)
          i = omp_get_thread_num();
#endif
          this->algos[i].solve(nt);
        } 
      }

      public:

      // ctor
      openmp(const typename solver_t::params_t &p) : 
        parent_t(p, new mem_t(p.n_eqs, p.span), mem_t::size())
      {}

    };
  }; // namespace concurr
}; // namespace libmpdataxx
