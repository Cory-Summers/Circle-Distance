#pragma once
#include <iostream>
#include <random>
#include "mathematics.hpp"
#include "gene-class.hpp"
class Application
{
public:
  Application(int argc, char* arg[]);
  int Execute();
  //Function to shake up stagnant pool

private:
  std::mt19937 m_generator;
  std::size_t  m_point_count;
  std::vector<Gene> m_gene_pool;
};

