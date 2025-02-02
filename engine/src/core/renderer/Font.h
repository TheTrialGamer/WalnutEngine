#pragma once

#include "Engine.h"
#include "utility.h"

#include "renderer/Texture.h"

#include "renderer/MSDFData.h"

#include <filesystem>

namespace Paper
{
	class Font
	{
	public:
		Font(const std::filesystem::path& path);
		~Font();

		MSDFData* GetMSDFData() const { return data; };
		Shr<Texture> GetAtlasTexture() const { return atlasTexture; };

		std::string GetFilePath() const { return fontPath.string(); }
		std::string GetFontName() const { return fontPath.filename().string(); }

	private:
		MSDFData* data;
		std::filesystem::path fontPath;
		Shr<Texture> atlasTexture;
	};

};