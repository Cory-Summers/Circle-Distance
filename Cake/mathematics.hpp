#pragma once
#include <cmath>
#include "polar-coord-class.hpp"
namespace math
{
  //Constexpr Variables
  constexpr double k_pi  = 3.141592653589793238462643383279502884e+00;
  constexpr double k_tau = k_pi * 2.0;
  //Declarations 
  template<typename value_type>
  value_type PolarDistance(PolarCoord<value_type> const &, PolarCoord<value_type> const &);
  template<typename value_type>
  constexpr inline value_type QSquare(value_type const& x) { return x * x; }

  //Definitions
  template<typename value_type>
  value_type PolarDistance(PolarCoord<value_type> const& l, PolarCoord<value_type> const& r)
  {
    const value_type theta_diff = std::cos(l.theta - r.theta);
    const value_type multi_rho  = static_cast<value_type>(2) * l.rho * r.rho;
    value_type comb_r = QSquare(l.rho) + QSquare(r.rho);
    comb_r -= multi_rho * theta_diff;
    return std::sqrt(comb_r);

  }
}