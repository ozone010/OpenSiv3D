﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr Quad::Quad(const value_type x0, const value_type y0, const value_type x1, const value_type y1, const value_type x2, const value_type y2, const value_type x3, const value_type y3) noexcept
		: p0(x0, y0)
		, p1(x1, y1)
		, p2(x2, y2)
		, p3(x3, y3) {}

	inline constexpr Quad::Quad(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept
		: p0(_p0)
		, p1(_p1)
		, p2(_p2)
		, p3(_p3) {}



	inline size_t Quad::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
