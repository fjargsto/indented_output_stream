#include <iostream>  // cin, cout

#include "indented_output_stream.hpp"

namespace io = boost::iostreams;

struct Vector
{
  float x;
  float y;
  float z;

};

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
  out << '[' << v.x << ", " << v.y << ", " << v.z << ']';

  return out;
}

struct AABB
{
  Vector min;
  Vector max;
};

std::ostream& operator<<(std::ostream& out, const AABB& bbox)
{
  out << "min = " << bbox.min << '\n';
  out << "max = " << bbox.max;

  return out;
}

int main()
{
  using namespace std;

  io::filtering_ostream out;
  out.push(io::indenting_output_filter()); // add indentation filter
  out.push(std::cout); // use cout

  // write to out using std::ostream interface
  Vector v = {0.1f, 0.2f, 0.3f};
  out << "v = " << v << "\n\n";

  AABB bbox = {v, {1.0f, 2.0f, 3.0f}};
  out << "bbox = {" << io::inc << '\n'
      << bbox << io::dec << '\n'
      << '}' << endl;

  return 0;
}
