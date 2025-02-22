#include <stdexcept>    // std::length_error

#include <boost/iostreams/filtering_stream.hpp>

namespace boost { namespace iostreams { 

class indent_zero_error: public std::runtime_error
{
public:
  indent_zero_error(): std::runtime_error("Can't dec zero indent.") {}
};
    
class indenting_output_filter : public output_filter {
public:
  explicit indenting_output_filter(unsigned int indent_size = 2)
      : indent_size_(indent_size)
      , indent_level_(0)
      , handle_command_token_(false)
  { }

  template<typename Sink>
  bool put(Sink& dest, int c)
  {
    if (c == '\0')
    {
      handle_command_token_ = true;
      return true;
    }
    if (handle_command_token_)
    {
      assert(c == 'i' || c == 'd');
      if (c == 'i') // increment
	++indent_level_;
      if (c == 'd') // decrement
      {
	assert(indent_level_ > 0); // in debug mode alert of decrementing zero indents
	if (indent_level_ > 0)     // in release mode swallow zero indents silently
	  --indent_level_;
      }
      handle_command_token_ = false;
      return true;
    }
    if (c == '\n')
    {
      // insert indent
      iostreams::put(dest, '\n'); // insert newline
      for (unsigned int indent_level = 0; indent_level < indent_level_; ++indent_level)
	for (unsigned int space = 0; space < indent_size_; ++space)
	  iostreams::put(dest, ' '); // insert space

      return true;
    } 

    return iostreams::put(dest, c);
  }
    
private:
  unsigned int indent_size_;
  unsigned int indent_level_;
  bool handle_command_token_;
};

inline std::ostream& inc( std::ostream &o ) {
  return o << '\0' << 'i'; //"\33[31m";
}

inline std::ostream& dec( std::ostream &o ) {
  return o << '\0' << 'd'; //"\33[31m";
}

inline std::ostream& incn( std::ostream &o ) {
  return o << '\0' << 'i' << '\n';
}

inline std::ostream& decn( std::ostream &o ) {
  return o << '\0' << 'd' << '\n';
}

} } // End namespace boost::iostreams

