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

# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "VertexShader.hpp"
# include "VertexShaderAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class VertexShaderAsset : public VertexShader
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAsset(AssetNameView name);

		static bool Register(const AssetName& name, FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		static bool Register(const AssetName& name, const s3d::HLSL& hlsl);

		static bool Register(const AssetName& name, const s3d::GLSL& glsl);

		static bool Register(const AssetName& name, const s3d::MSL& msl);

		static bool Register(const AssetName& name, const s3d::ESSL& essl);

		static bool Register(const AssetName& name, const ShaderGroup& shaderGroup);

		static bool Register(const AssetName& name, std::unique_ptr<VertexShaderAssetData>&& data);


		static bool Register(const AssetNameAndTags& nameAndTags, FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::HLSL& hlsl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::GLSL& glsl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::MSL& msl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::ESSL& essl);

		static bool Register(const AssetNameAndTags& nameAndTags, const ShaderGroup& shaderGroup);


		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);

		static bool Load(AssetNameView name);

		//static void LoadAsync(AssetNameView name);

		//static void Wait(AssetNameView name);

		[[nodiscard]]
		static bool IsReady(AssetNameView name);

		static void Release(AssetNameView name);

		static void ReleaseAll();

		static void Unregister(AssetNameView name);

		static void UnregisterAll();

		[[nodiscard]]
		static HashTable<AssetName, AssetInfo> Enumerate();
	};
}
