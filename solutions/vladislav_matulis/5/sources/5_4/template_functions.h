#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <boost/foreach.hpp>
#include <vector>
#include <map>

namespace task5_4
{
	template< bool delete_first, typename Container >
	class eraser
	{
	public:
		void operator() ( Container& ) {}
	};

	template< typename Container >
	class eraser< true, Container >
	{
	public:
		void operator() ( Container& cont )
		{
			BOOST_FOREACH( const auto& val, cont )
			{
				delete val;
			}
		}
	};

	template< bool delete_first, bool delete_second, typename Container >
	class eraser2
	{
	public:
		void operator() ( Container& ) {}
	};

	template< typename Container >
	class eraser2< true, true, Container >
	{
	public:
		void operator() ( Container& cont )
		{
			BOOST_FOREACH( const auto& val, cont )
			{
				delete val.first;
				delete val.second;
			}
		}
	};

	template< typename Container >
	class eraser2< false, true, Container >
	{
	public:
		void operator() ( Container& cont )
		{
			BOOST_FOREACH( const auto& val, cont )
			{
				delete val.second;
			}
		}
	};

	template< typename Container >
	class eraser2< true, false, Container >
	{
	public:
		void operator() ( Container& cont )
		{
			BOOST_FOREACH( const auto& val, cont )
			{
				delete val.first;
			}
		}
	};

	template< bool delete_first, typename Container >
	void clear_container( Container& cont )
	{
		eraser< delete_first, Container > er; 
		er( cont );
		cont.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& cont )
	{
		eraser2< delete_first, delete_second, Container > er;
		er( cont );
		cont.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

