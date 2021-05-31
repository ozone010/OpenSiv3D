//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	class CRenderer_Null final : public ISiv3DRenderer
	{
	private:

	public:

		CRenderer_Null();

		~CRenderer_Null() override;

		EngineOption::Renderer getRendererType() const noexcept override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		void captureScreenshot() override;

		const Image& getScreenCapture() const override;

		void setSceneResizeMode(ResizeMode resizeMode) override;

		ResizeMode getSceneResizeMode() const noexcept override;

		void setSceneBufferSize(Size size) override;

		Size getSceneBufferSize() const noexcept override;

		void setSceneTextureFilter(TextureFilter textureFilter) override;

		TextureFilter getSceneTextureFilter() const noexcept override;

		void setBackgroundColor(const ColorF& color) override;

		const ColorF& getBackgroundColor() const noexcept override;

		void setLetterboxColor(const ColorF& color) override;

		const ColorF& getLetterboxColor() const noexcept override;

		std::pair<float, RectF> getLetterboxComposition() const noexcept override;

		void updateSceneSize() override;
	};
}
