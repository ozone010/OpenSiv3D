﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/DynamicTexture.hpp>
# include "../Siv3DEngine.hpp"
# include "../Texture/ITexture.hpp"

namespace s3d
{
	DynamicTexture::DynamicTexture(const size_t width, const size_t height, TextureFormat format)
		: Texture(Texture::Dynamic{}, width, height, nullptr, 0, format)
	{

	}

	DynamicTexture::DynamicTexture(const size_t width, const size_t height, const ColorF& color, TextureFormat format)
		: Texture(Texture::Dynamic{}, width, height, color, format)
	{

	}

	DynamicTexture::DynamicTexture(const Image& image, TextureFormat format)
		: Texture(Texture::Dynamic{}, image.width(), image.height(), image.data(), image.stride(), format)
	{

	}
}
