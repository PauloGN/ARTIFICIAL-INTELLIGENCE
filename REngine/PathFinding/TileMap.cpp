#include "TileMap.h"

namespace
{
	//by standard tile size should be 32 bits
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
	bShouldDraw = false;
	LoadTilesTexture(TileCollectionName);
	LoadTileMap(mapName);
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

	if (IsKeyPressed(KeyboardKey::KEY_L))
	{
		bShouldDraw = !bShouldDraw;
	}

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

			//TODO Drawline()
			//draw line for every node that is connected

			//TEST DRAW
			if (bShouldDraw)
			{
				if (mTiles[tileIndex].weight < 11)
				{
					DrawDebugLine(x, y);
				}
			}
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

	//TODO
	//Initialize mGridBasedGraph;

	mGridBasedGraph.Initialize(mColumns, mRows);

	//TODO
	//for
	//for
	//Conect the nodes to its neighbors
	//hint
	// if (condition of weight allowed) {connect nodes}
	//mGridBasedGraph.GetNode(4, 5)->neighbors[AI::GridBasedGraph::East] = mGridBasedGraph.GetNode(5,5);

	LoadGridBaseGraphNeighbors();
}

void TileMap::LoadTilesTexture(const char* TileCollectionName)
{
	//prevents to get an old vector full of informations
	mTiles.clear();

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

			//load textures
			REng::ResourcesFullPath(buffer, fullpath);
			const int weight = ChargeWeight(fullpath);
			const Tiles tiles(LoadTexture(fullpath.c_str()), weight);

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

int TileMap::ChargeWeight(std::string& tileName)
{
	int Weight{0};
	
	if (!tileName.empty())
	{
		Weight = tileName[tileName.length() - 1];
		tileName.pop_back();
		tileName.pop_back();
	}

	return Weight - '0';
}

void TileMap::DrawDebugLine(const int& x, const int& y)
{
		
	const int startX = static_cast<int>(x * tileSize);
	const int startY = static_cast<int>(y * tileSize);
	
	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::North])
	{
		const int endX = static_cast<int>(x * tileSize);
		const int endY = static_cast<int>(tileSize * (y - 1));
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::South])
	{
		const int endX = static_cast<int>(x * tileSize);
		const int endY = static_cast<int>(tileSize * (y + 1));
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::East])
	{
		const int endX = static_cast<int>((x + 1) * tileSize);
		const int endY = static_cast<int>(tileSize * y);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::West])
	{
		const int endX = static_cast<int>((x - 1) * tileSize);
		const int endY = static_cast<int>(tileSize * y);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::NorthEast])
	{
		const int endX = static_cast<int>((x + 1) * tileSize);
		const int endY = static_cast<int>(tileSize * (y - 1));
		DrawLine(startX, startY, endX, endY, WHITE);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::NorthWest])
	{
		const int endX = static_cast<int>((x - 1) * tileSize);
		const int endY = static_cast<int>(tileSize * (y - 1));
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::SouthEast])
	{
		const int endX = static_cast<int>((x + 1)* tileSize);
		const int endY = static_cast<int>(tileSize * (y + 1));
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::SouthWest])
	{
		const int endX = static_cast<int>((x - 1) * tileSize);
		const int endY = static_cast<int>(tileSize * (y + 1));
		DrawLine(startX, startY, endX, endY, RED);
	}

}

void TileMap::LoadGridBaseGraphNeighbors()
{
	for (int y = 0; y < mGridBasedGraph.GetRows(); y++)
	{
		for (int x = 0; x < mGridBasedGraph.GetColumns(); x++)
		{
			AI::GridBasedGraph::Node* node = mGridBasedGraph.GetNode(x, y);
			int gridIndex = GetIndex(node->column, node->row);



			int tileIndex = mMap[gridIndex];
			if (mTiles[tileIndex].weight < 5)
			{

				bool has8Neighbors = x > 0 && x < mColumns&& y > 0 && y < mRows;
				if (has8Neighbors)
				{
					LoadNorthNeigbors(x, y);
					LoadSouthNeigbors(x, y);
					LoadEastNeigbors(x, y);
					LoadWestNeigbors(x, y);
					LoadNorthEastNeigbors(x, y);
					LoadNortWesthNeigbors(x, y);
					LoadSouthEastNeigbors(x, y);
					LoadSouthWestNeigbors(x, y);
				}
				else
				{
					if (x == 0 && y == 0)
					{
						LoadSouthNeigbors(x, y);
						LoadEastNeigbors(x, y);
						LoadSouthEastNeigbors(x, y);
					}

					if (x >= mColumns - 1 && y > 0 && y <= mRows - 1)
					{
						LoadNorthNeigbors(x, y);
						LoadSouthNeigbors(x, y);
						LoadWestNeigbors(x, y);
						LoadNortWesthNeigbors(x, y);
						LoadSouthWestNeigbors(x, y);
					}

					if (x >= mColumns - 1 && y == 0)
					{
						LoadSouthNeigbors(x, y);
						LoadWestNeigbors(x, y);
						LoadSouthWestNeigbors(x, y);
					}

				}
			}
		}
	}
}

void TileMap::LoadNorthNeigbors(const int x, const int y)
{
	int index = GetIndex(x, y - 1);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::North] = mGridBasedGraph.GetNode(x, y - 1);
	}
}

void TileMap::LoadSouthNeigbors(const int x, const int y)
{
	int index = GetIndex(x, y + 1);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::South] = mGridBasedGraph.GetNode(x, y + 1);
	}
}

void TileMap::LoadEastNeigbors(const int x, const int y)
{
	int index = GetIndex(x + 1, y);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::East] = mGridBasedGraph.GetNode(x + 1, y);
	}
}

void TileMap::LoadWestNeigbors(const int x, const int y)
{
	int index = GetIndex(x - 1, y);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::West] = mGridBasedGraph.GetNode(x - 1, y);
	}
}
	
void TileMap::LoadNorthEastNeigbors(const int x, const int y)
{
	int index = GetIndex(x + 1, y - 1);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}
	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::NorthEast] = mGridBasedGraph.GetNode(x + 1, y - 1);
	}
}

void TileMap::LoadNortWesthNeigbors(const int x, const int y)
{
	int index = GetIndex(x - 1, y - 1);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::NorthWest] = mGridBasedGraph.GetNode(x - 1, y - 1);
	}
}

void TileMap::LoadSouthEastNeigbors(const int x, const int y)
{
	int index = GetIndex(x + 1, y + 1);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::SouthEast] = mGridBasedGraph.GetNode(x + 1, y + 1);
	}
}

void TileMap::LoadSouthWestNeigbors(const int x, const int y)
{
	int index = GetIndex(x - 1, y + 1);

	if (index < 0 || index >= mRows * mColumns)
	{
		return;
	}

	int tileIndex = mMap[index];
	if (mTiles[tileIndex].weight < 5)
	{
		mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::SouthWest] = mGridBasedGraph.GetNode(x - 1, y + 1);
	}
}

