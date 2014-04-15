#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	read_binary( in, stock_name_ );
	read_binary( in, date_time_ );
	read_binary( in, price_ );
	read_binary( in, vwap_ );
	read_binary( in, volume_ );
	read_binary( in, f1_ );
	read_binary( in, t1_ );
	read_binary( in, f2_ );
	read_binary( in, f3_ );
	read_binary( in, f4_ );
}
binary_reader::stock_data::stock_data( const char* stock_name,
							const char* date_time,
							const double price,
							const double vwap,
							const boost::uint32_t volume,
							const double f1,
							const double t1,
							const double f2,
							const double f3,
							const double f4 )
	: price_( price )
	, vwap_( vwap )
	, volume_( volume )
	, f1_( f1 )
	, t1_( t1 )
	, f2_( f2 )
	, f3_( f3 )
	, f4_( f4 )
{
	memcpy( stock_name_, stock_name, sizeof( stock_name_ ) );
	memcpy( date_time_, date_time, sizeof( date_time_ ) );
}

binary_reader::stock_data::stock_data( const binary_reader::stock_data &datum )
	: price_( datum.price_ )
	, vwap_( datum.vwap_ )
	, volume_( datum.volume_ )
	, f1_( datum.f1_ )
	, t1_( datum.t1_ )
	, f2_( datum.f2_ )
	, f3_( datum.f3_ )
	, f4_( datum.f4_ )
{
	memcpy( stock_name_, datum.stock_name_, sizeof( stock_name_ ) );
	memcpy( date_time_, datum.date_time_, sizeof( date_time_ ) );
}

binary_reader::stock_data::~stock_data()
{
}
void binary_reader::stock_data::write( std::ofstream& out )const
{
	boost::uint32_t date = 0;
	int month;
	int day;
	int year;
	std::sscanf( date_time_, "%4d%2d%2d", &year, &month, &day );
    date = ( year - 1 ) * 372 +  ( month  - 1 )* 31 + day;

	static char stock_name[ 9 ];
	memcpy( stock_name, stock_name_, sizeof( stock_name_ ) );
	write_binary( out, stock_name );
	write_binary( out, date );
	write_binary( out, vwap_ );
	write_binary( out, volume_ );
	write_binary( out, f2_ );	
}
void binary_reader::stock_data::write_raw( std::ofstream& out )const
{	
	write_binary( out, stock_name_ );
	write_binary( out, date_time_ );
	write_binary( out, price_ );
	write_binary( out, vwap_ );
	write_binary( out, volume_ );
	write_binary( out, f1_ );
	write_binary( out, t1_ );
	write_binary( out, f2_ );
	write_binary( out, f3_ );
	write_binary( out, f4_ );	
}

const char* binary_reader::stock_data::stock_name()const
{
	return stock_name_;
}

const char* binary_reader::stock_data::date_time()const
{
	return date_time_;
}

double binary_reader::stock_data::price()const
{
	return price_;
}

double binary_reader::stock_data::vwap()const
{
	return vwap_;
}

boost::uint32_t binary_reader::stock_data::volume()const
{
	return volume_;
}

double binary_reader::stock_data::f1()const
{
	return f1_;
}

double binary_reader::stock_data::t1()const
{
	return t1_;
}

double binary_reader::stock_data::f2()const
{
	return f2_;
}

double binary_reader::stock_data::f3()const
{
	return f3_;
}

double binary_reader::stock_data::f4()const
{
	return f4_;
}