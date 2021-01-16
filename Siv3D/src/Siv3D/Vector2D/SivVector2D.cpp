﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/2DShapes.hpp>

namespace s3d
{
	template <>
	Circle Vector2D<float>::asCircle(const double r) const noexcept
	{
		return{ *this, r };
	}

	template <>
	Circle Vector2D<double>::asCircle(const double r) const noexcept
	{
		return{ *this, r };
	}

	template <>
	void Vector2D<double>::_Formatter(FormatData& formatData, const Vector2D<double>& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}

	template <>
	void Vector2D<float>::_Formatter(FormatData& formatData, const Vector2D<float>& value)
	{
		Vector2D<double>::_Formatter(formatData, value);
	}

	template struct Vector2D<float>;
	template struct Vector2D<double>;
}
