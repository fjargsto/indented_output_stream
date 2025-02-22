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
  out << '{' << io::incn
      << "min = " << bbox.min << '\n'
      << "max = " << bbox.max << io::decn
      << '}';

  return out;
}

struct Sphere
{
  Vector center;
  float  radius;
  AABB aabb() const
  {
    return {{center.x - radius, center.y - radius, center.z - radius},
	    {center.x + radius, center.y + radius, center.z + radius}};
  }
};

std::ostream& operator<<(std::ostream& out, const Sphere& sphere)
{
  out << '{' << io::incn
      << "center = " << sphere.center << '\n'
      << "radius = " << sphere.radius << '\n'
      << "aabb = " << sphere.aabb() << io::decn
      << '}';

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
  out << "bbox = " << bbox << "\n\n";

  Sphere sphere = {{5.0f, 10.0f, 15.0f}, 1.0f};
  out << "sphere = " << sphere << std::endl;

  return 0;
}
