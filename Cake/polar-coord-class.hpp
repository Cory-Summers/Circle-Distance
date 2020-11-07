#pragma once
namespace math {
  template<typename value_type>
  struct PolarCoord
  {
    PolarCoord(value_type const&, value_type const&);
    value_type rho;
    value_type theta;
  };

  template<typename value_type>
  inline PolarCoord<value_type>::PolarCoord(value_type const& rho, value_type const& theta)
    : rho(rho), theta(theta)
  {
  }
}