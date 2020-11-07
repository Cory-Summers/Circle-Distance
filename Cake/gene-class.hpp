#pragma once
#include <array>
#include <memory>
#include <random>
#include <vector>

#include "polar-coord-class.hpp"
class Gene
{
  using generator = std::mt19937;
  using fitness_type = double;
  using polar_type   = math::PolarCoord<double>;
public:
  Gene();
private:
  polar_type   m_polar;
  fitness_type m_fitness;
};

