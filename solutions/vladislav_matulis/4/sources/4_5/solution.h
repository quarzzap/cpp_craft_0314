#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>
namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;
	typedef std::vector< int > iVec;
	class solution
	{
		const data_type data_;
		int min_, max_;
		size_t size_;
		size_t number;
		boost::mutex mtx;
		iVec minArray, maxArray;
		void process();
		void peekToThread( const size_t );
		const size_t getID();
		bool check( const size_t );
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

