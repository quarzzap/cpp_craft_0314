#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	namespace tests_
	{
		void test_stock_data();
	}
	template< class T >
	void read_binary( std::ifstream& in, T& t, const size_t len = sizeof( T ) )
	{
		in.read( reinterpret_cast< char* >( &t ), len );
	}
	template< class T >
	void write_binary( std::ofstream& out, const T& t, const size_t len = sizeof( T ) )
	{
		out.write( reinterpret_cast< const char* >( &t ), len );
	}
	//
	class stock_data
	{
		friend void tests_::test_stock_data();
	protected:
		char stock_name_[8];
		char date_time_[8];
		double price_;
		double vwap_;
		boost::uint32_t volume_;
		double f1_;
		double t1_;
		double f2_;
		double f3_;
		double f4_;

	public:
		explicit stock_data( std::ifstream& in );
		explicit stock_data( const char* stock_name = NULL,
							const char* date_time = NULL,
							const double price = 0,
							const double vwap = 0,
							const boost::uint32_t volume = 0,
							const double f1 = 0,
							const double t1 = 0,
							const double f2 = 0,
							const double f3 = 0,
							const double f4 = 0 );		
		stock_data ( const stock_data& datum );
		~stock_data();
		//
		void write( std::ofstream& out )const;
		void write_raw( std::ofstream& out )const;

		const char* stock_name()const;
		const char* date_time()const;
		double price()const;
		double vwap()const;
		boost::uint32_t volume()const;
		double f1()const;
		double t1()const;
		double f2()const;
		double f3()const;
		double f4()const;
	};
}

#endif // _BINARY_READER_STOCK_DATA_H_

