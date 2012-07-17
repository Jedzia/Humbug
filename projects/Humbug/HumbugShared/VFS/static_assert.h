#ifndef HUMBUGSHARED_VFS_STATICASSERT_H
#define HUMBUGSHARED_VFS_STATICASSERT_H

/*
namespace static_assert_l {

	template <bool> class compile_time_error;
	template <> class compile_time_error<true> { };

}

#define static_assert_l(expr)				{ static_assert_l::compile_time_error<((expr) != 0)> ERROR_static_assert_l; (void) ERROR_static_assert_l; }
#define static_assert_l_msg(expr, msg)	{ static_assert_l::compile_time_error<((expr) != 0)> ERROR_##msg; (void) ERROR_##msg; }
*/



#define static_assert_l(expr)				
#define static_assert_l_msg(expr, msg)	

#endif // HUMBUGSHARED_VFS_STATICASSERT_H guard
