
#pragma once



namespace static_assert {

	template <bool> class compile_time_error;
	template <> class compile_time_error<true> { };

}



#define static_assert(expr)				{ static_assert::compile_time_error<((expr) != 0)> ERROR_STATIC_ASSERT; (void) ERROR_STATIC_ASSERT; }
#define static_assert_msg(expr, msg)	{ static_assert::compile_time_error<((expr) != 0)> ERROR_##msg; (void) ERROR_##msg; }
