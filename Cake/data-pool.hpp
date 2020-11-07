#pragma once
#include <array>
#include <cmath>
#include <immintrin.h>
#include "sys_dep.h"
namespace memory {
  //Helper Class to improve performance through SIMD accessable arrays of data
  //Will cause decrease speed of individal access to elements but should overall improve speed
  template<typename T, std::size_t partitions = 1>  //Partitions can't be zero
  class DataPool
  {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
  public:
    DataPool();
    DataPool(size_type const& elements);
    constexpr value_type * operator[](size_type const& idx) { return m_partition_head[idx]; }
    template<size_type idx> 
    pointer get() { return (m_pool + idx * m_size); };
    void SwapElements(size_type const& aidx, size_type const & bidx);
    ~DataPool();
  private:
    constexpr std::size_t PerCacheLine() { return k_cache_line_w / sizeof(value_type); }
    constexpr std::size_t AlignPartition(std::size_t const & elements) { 
      return static_cast<std::size_t>(std::ceil(static_cast<float>(elements) / PerCacheLine()) * PerCacheLine());  
     }
    void _Allocate();
    void _Resize(size_type const &);
    pointer m_pool;
    std::array<pointer, partitions> m_partition_head;
    size_type m_size;
    size_type m_partition_size;
  };
  template<typename T, std::size_t partitions>
  inline DataPool<T, partitions>::DataPool()
    : m_pool(nullptr)
    , m_partition_head()
    , m_size()
    , m_partition_size()
  {
    m_partition_head.fill(nullptr);
  }
  template<typename T, std::size_t partitions>
  inline DataPool<T, partitions>::DataPool(size_type const& elements)
    : m_pool()
    , m_partition_head()
    , m_size(elements)
    , m_partition_size(AlignPartition(elements))
  {
    _Allocate();
  }
  template<typename T, std::size_t partitions>
  inline void DataPool<T, partitions>::SwapElements(size_type const& aidx, size_type const& bidx)
  {

    for (size_type i = 0; i < partitions; ++i)
    {
      std::swap(*(m_partition_head[i] + aidx), *(m_partition_head[i] + bidx));
    }
  }
  template<typename T, std::size_t partitions>
  inline DataPool<T, partitions>::~DataPool()
  {
    AlignedFree(m_pool);
  }
  template<typename T, std::size_t partitions>
  inline void DataPool<T, partitions>::_Allocate()
  {
    m_pool = (pointer)AlignedAlloc(m_partition_size * partitions);
    for (size_type i = 0; i < partitions; ++i)
    {
      m_partition_head[0] = m_pool + m_partition_size * i;
    }
  }
  template<typename T, std::size_t partitions>
  inline void DataPool<T, partitions>::_Resize(size_type const& size)
  {
    std::size_t temp_part_size = AlignPartition(size);
    pointer     temp_pool      = (pointer)AlignedAlloc(m_partition_size * partitions);
    for (std::size_t i = 0; i < partitions; ++i)
    {
      std::copy(m_partition_head[i], m_partition_head[i] + m_size, temp_pool + temp_part_size * i);
      m_partition_head[i] = temp_pool + temp_part_size * i;
    }
    m_size           = size;
    m_pool           = temp_pool;
    m_partition_size = temp_part_size;
  }
}

