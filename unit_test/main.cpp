#define BOOST_TEST_MODULE indented_output_stream_tests
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <boost/iostreams/filtering_stream.hpp>
#include "indented_output_stream.hpp"

namespace io = boost::iostreams;

BOOST_AUTO_TEST_CASE(no_indent)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter()); // add indentation filter
  std::ostringstream ostr;
  out.push(ostr);

  out << "\nTestString";
  out.flush();
  BOOST_CHECK(ostr.str() == "\nTestString");
}

BOOST_AUTO_TEST_CASE(one_indent)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter()); // add indentation filter
  std::ostringstream ostr;
  out.push(ostr);

  out << io::inc << "\nTestString";
  out.flush();
  BOOST_CHECK(ostr.str() == "\n  TestString");
}

BOOST_AUTO_TEST_CASE(double_indent)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter()); // add indentation filter
  std::ostringstream ostr;
  out.push(ostr);

  out << io::inc << io::inc << "\nTestString";
  out.flush();
  BOOST_CHECK(ostr.str() == "\n    TestString");
}

#if NDEBUG // only in release insert a dec on zero indent filter
BOOST_AUTO_TEST_CASE(decrement_0_level_swallow)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter()); // add indentation filter
  std::ostringstream ostr;
  out.push(ostr);
  out << io::dec;
  out.flush();
}
#endif

BOOST_AUTO_TEST_CASE(indent_size)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter(3)); // add indentation filter with indent size 3 (spaces)
  std::ostringstream ostr;
  out.push(ostr);

  out << io::inc << "\nTestString";
  out.flush();
  BOOST_CHECK(ostr.str() == "\n   TestString");
}

BOOST_AUTO_TEST_CASE(inc_dec_multi_line)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter());
  std::ostringstream ostr;
  out.push(ostr);

  out << "TestString" << io::inc << '\n'
      << "TestString" << io::inc << '\n'
      << "TestString" << io::inc << '\n'
      << "TestString" << io::dec << '\n'
      << "TestString" << io::inc << '\n'
      << "TestString" << io::dec << io::dec << '\n'
      << "TestString" << io::dec << '\n'
      << "TestString" << std::endl;
  out.flush();
  BOOST_CHECK(ostr.str() ==
	      "TestString\n"
	      "  TestString\n"
	      "    TestString\n"
	      "      TestString\n"
	      "    TestString\n"
	      "      TestString\n"
	      "  TestString\n"
	      "TestString\n");
}

BOOST_AUTO_TEST_CASE(incn_decn_multi_line)
{
  io::filtering_ostream out;
  out.push(io::indenting_output_filter());
  std::ostringstream ostr;
  out.push(ostr);

  out << "TestString" << io::incn
      << "TestString" << io::incn
      << "TestString" << io::incn
      << "TestString" << io::decn
      << "TestString" << io::incn
      << "TestString" << io::dec << io::decn
      << "TestString" << io::decn
      << "TestString" << std::endl;
  out.flush();
  std::cerr << ostr.str() << std::endl;
  BOOST_CHECK(ostr.str() ==
	      "TestString\n"
	      "  TestString\n"
	      "    TestString\n"
	      "      TestString\n"
	      "    TestString\n"
	      "      TestString\n"
	      "  TestString\n"
	      "TestString\n");
}

