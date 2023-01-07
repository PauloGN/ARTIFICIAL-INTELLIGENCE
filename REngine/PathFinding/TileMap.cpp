#include "TileMap.h"

namespace
{

	const float tileSize = 32.f;

	//instance of sigletom
	std::unique_ptr<TileMap> tileMapInstance;

}

void TileMap::StaticInitialize()
{
	assert(tileMapInstance == nullptr, "TileMap already initialized...");
	tileMapInstance = std::make_unique<TileMap>();
}

void TileMap::StaticTerminate()
{
	tileMapInstance.reset();
}

TileMap& TileMap::Get()
{
	assert(tileMapInstance != nullptr, "TileMap not created yet must call StaticInitialize() first.");
	return *tileMapInstance;
}

void TileMap::Load(const char* mapName, const char* TileCollectionName)
{
	LoadTileMap(mapName);
	LoadTilesTexture(TileCollectionName);
}

void TileMap::Unload()
{

	mColumns = 0;
	mRows = 0;
	mMap.reset();

	mMap = nullptr;
	mTiles.clear();
}

void TileMap::Update(float DeltaTime)
{
	//1h.2 empty for now
}

void TileMap::Render()
{
	//looping from top to bottom
	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];
			const Texture2D texture = mTiles[tileIndex];

			const REng::Math::Vector2 textPos = {x * tileSize , y * tileSize};

			DrawTexture(texture, textPos.x, textPos.y, WHITE);
		}
	}

}

void TileMap::LoadTileMap(const char* mapName)
{

	if (mMap)
	{
		mMap.reset();
	}

	FILE* file = nullptr;

	fopen_s(&file, mapName, "r");

	if (file != 0)
	{
		fscanf_s(file, "Columns: %d\n", &mColumns);
		fscanf_s(file, "Rows: %d\n", &mRows);

		//Create a smartpointer dimention Columns * Rows
		mMap = std::make_unique<int[]>(mColumns * mRows);

		//Loop through rows and Columns
		for (int y = 0; y < mRows; y++)
		{
			for (int x = 0; x < mColumns; x++)
			{
				const int index = GetIndex(x, y);
				mMap[index] = fgetc(file) - '0';
			}
			fgetc(file);
		}

		fclose(file);
	}

}

void TileMap::LoadTilesTexture(const char* TileCollectionName)
{
	mTiles.clear();//prevents to get an old vector full of informations

	FILE* file = nullptr;
	fopen_s(&file, TileCollectionName, "r");

	if (file != 0)
	{
		int count = 0;// range of the loop
		fscanf_s(file, "Count: %d\n", &count);

		for (int i = 0; i < count; i++)
		{
			std::string fullpath;
			char buffer[256];
			fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));
			REng::ResourcesFullPath(buffer, fullpath);

			mTiles.push_back(LoadTexture(fullpath.c_str()));

			//Load Tiles textures Exemple

			//std::string fullpath;
			//REng::ResourcesFullPath("wall.png", fullpath);
			//mTiles.push_back(LoadTexture(fullpath.c_str()));
		}

		fclose(file);
	}

}

bool TileMap::IsCollisdingWith(REng::Math::LineSegment & lineSegment) const
{
	return false;
}

Rectangle TileMap::GetBound() const
{
	// Rectangle, 4 components
	//	float x;                // Rectangle top-left corner position x
	//	float y;                // Rectangle top-left corner position y
	//	float width;            // Rectangle width
	//	float height;           // Rectangle height

	Rectangle bound;

	bound.x = 0.0f;
	bound.y = 0.0f;
	bound.width = mColumns * tileSize;
	bound.height = mRows * tileSize;

	return bound;
}

int TileMap::GetIndex(int column, int row) const
{
	//Exemplo: Column 1, row 3 with 10 total
	//index = 1 + (3 * 10): result would be 31
	return column + (row * mColumns);
}
