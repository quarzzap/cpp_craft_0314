#include "a_message.h"
#include <string>
#include <stdexcept>

task4_4::a_message::a_message( std::istream& inp )
{
	inp.read( content_, content_size );
	if ( inp.eof() )
		throw std::logic_error("bad input stream, a_message cannot be readed");
}

task4_4::message_ptr task4_4::a_message::create_message( std::istream& inp )
{
	return message_ptr( new a_message( inp ) );
}

task4_4::a_message::~a_message()
{
}
//
const char task4_4::a_message::type() const
{
	return 'A';
}
const std::string task4_4::a_message::str() const
{
	std::string s = "a_message(";
	char* buf = new char[ content_size + 1 ];
	memcpy( buf, content_, content_size );
	buf[ content_size ] = 0;
	s.append( buf );
	delete[] buf;
	s.append( ")" );
	return s;
}
