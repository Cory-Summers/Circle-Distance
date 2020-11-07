#include "application-class.hpp"

Application::Application(int argc, char* argv[])
  : m_point_count(std::strtoul(argv[1], nullptr, 10))
  , m_generator(std::random_device{}()) //Initialize generator from the hardware PRNG
{

}
