#pragma once
#include<cstdlib>
namespace memory {
  constexpr std::size_t k_cache_line_w = 64ull;
  inline void* AlignedAlloc(std::size_t size, std::size_t alignment = k_cache_line_w)
  {
  #ifdef _WIN32
    return _aligned_malloc(alignment, size);
  #else
    return aligned_alloc(alignment, size);
  #endif
  }
  inline void AlignedFree(void* ptr)
  {
  #ifdef _WIN32
    _aligned_free(ptr);
  #else
    free(ptr);
  #endif
  }
}