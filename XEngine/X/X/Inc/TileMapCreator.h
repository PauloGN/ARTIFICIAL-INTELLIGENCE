#pragma once
#include "XEngine.h"

namespace X
{
	class TileMapCreator
	{
	private:

		int mColumns = 0;
		int mRows = 0;
		float tileSize = 32.0f;
		std::vector<X::TextureId> mTiles;

		void LoadMap(const std::filesystem::path& MapName);
		void LoadTextures(const std::filesystem::path& TextureName);

	public:

		std::unique_ptr<int[]> mMap = nullptr;

		//this function will call both load map and load textures
		void Load(const std::filesystem::path& MapName, const std::filesystem::path& TileSetName);

		void Unload();
		void Update(const float& deltaTime);
		void Render();
		int GetIndex(int colum, int row) const;
		X::Math::Rect GetBounds()const;

	public:

		//Singleton Functions
		static void StaticInitialize();
		static void StaticTerminate();
		static TileMapCreator& Get();
	};
}
