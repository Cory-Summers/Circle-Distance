#pragma once
#include <vector>

#include "data-pool.hpp"
#include "gene-class.hpp"
class GenePool
{
public:
  GenePool();
  GenePool(std::size_t const& size);
  void CalcDistances();
private:
  std::vector<Gene> m_genes;
  //SIMD performance
  memory::DataPool<float, 3> m_value_pool;
  memory::DataPool<float, 1> m_distance_pool;
};

