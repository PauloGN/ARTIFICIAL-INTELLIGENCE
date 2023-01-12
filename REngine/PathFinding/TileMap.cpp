#include "TileMap.h"

namespace
{

	//by standard tile size should be 32
	const float tileSize = 32.f;

	//instance of Singleton
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
			const Texture2D texture = mTiles[tileIndex].texture;

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
		fscanf_s(file, "Columns: %d\n", &mColumns);//read and go next
		fscanf_s(file, "Rows: %d\n", &mRows);//read and go next

		//Create a smartpointer array dimention Columns * Rows
		mMap = std::make_unique<int[]>(mColumns * mRows);

		//Loop through rows and Columns
		for (int y = 0; y < mRows; y++)
		{
			for (int x = 0; x < mColumns; x++)
			{
				const int index = GetIndex(x, y);
				mMap[index] = fgetc(file) - '0';
			}
			//go next
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
		int count = 0;// range of the loop how many assets are going to be loaded 
		fscanf_s(file, "Count: %d\n", &count);

		for (int i = 0; i < count; i++)
		{
			std::string fullpath;
			char buffer[256];
			fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));
			REng::ResourcesFullPath(buffer, fullpath);

			//load textures
			const Tiles tiles(LoadTexture(fullpath.c_str()), 0);

			mTiles.push_back(tiles);

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

	const int startX = static_cast<int>(lineSegment.from.x / tileSize);
	const int startY = static_cast<int>(lineSegment.from.y / tileSize);
	const int endX	 = static_cast<int>(lineSegment.to.x / tileSize);
	const int endY	 = static_cast<int>(lineSegment.to.y / tileSize);

	//checking if it is out of Bound the Map

	if (startX < 0 || startX >= mColumns ||
		startY < 0 || startY >= mRows ||
		endX < 0 || endX >= mColumns ||
		endY < 0 || endY >= mRows)
	{
		return true;
	}

	for (int y = startY; y <= endY; y++)
	{
		for (int x = startY; x <= endX; x++)
		{
			const int index = GetIndex(x, y);
			if (mMap[index] > 27)
			{
				return true;
			}
		}
	}

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

	bound.x = 0.0f;						//left
	bound.y = 0.0f;						//top
	bound.width = mColumns * tileSize;	//right
	bound.height = mRows * tileSize;	//bottom

	return bound;
}

int TileMap::GetIndex(int column, int row) const
{
	//Exemplo: Column 1, row 3 with 10 total
	//index = 1 + (3 * 10): result would be 31
	return column + (row * mColumns);
}
