#include "TileMap.h"
#include "Character.h"

namespace
{
	//by standard tile size should be 32 bits if it is not it will be updated on Load func
	float tileSize = 32.f;
	float tileHalthWidth = tileSize * .5f;
	float tileHalthHeight = tileSize * .5f;
	//instance of Singleton
	std::unique_ptr<TileMap> tileMapInstance;

	REng::Math::Vector2 endPos(9.f, 13.f);
	uint16_t weightOfBlocking = 5;
	void UpdateEndSearchPoint(int maxX, int maxY)
	{
		const float speed = 10 * GetFrameTime();
		if (IsKeyDown(KeyboardKey::KEY_KP_4))
		{
			endPos.x -= speed;
			if (endPos.x - speed <= 0)
			{
				endPos.x = 0;
			}
		}

		if (IsKeyDown(KeyboardKey::KEY_KP_6))
		{
			endPos.x += speed;
			if (endPos.x - speed >= maxX)
			{
				endPos.x = maxX -1;
			}
		}

		if (IsKeyDown(KeyboardKey::KEY_KP_8))
		{
			endPos.y -= speed;
			if (endPos.y - speed < 0.f)
			{
				endPos.y = 0;
			}
		}

		if (IsKeyDown(KeyboardKey::KEY_KP_2))
		{
			endPos.y += speed;
			if (endPos.y - speed > maxY)
			{
				endPos.y = maxY -1;
			}
		}
	}
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
	mDrawLineType = DrawLineType::DLT_NONE;//define the type of search to be made and drew
	weightOfBlocking = 5;
	LoadTilesTexture(TileCollectionName);
	// Getting tilesize and calculating its halth size
	if (mTiles.size() > 0)
	{
		tileSize = mTiles[0].texture.height;
		tileHalthWidth = mTiles[0].texture.width * .5f;
		tileHalthHeight = mTiles[0].texture.height * .5f;
	}
	LoadTileMap(mapName);
	mHeuristicsType = HeuristicsType::HT_ManHattan;
	mHeuristicsText = "Heuristics: ManHanttan";
}

void TileMap::Unload()
{
	mDrawLineType = DrawLineType::DLT_NONE;
	mColumns = 0;
	mRows = 0;
	mMap.reset();
	mMap = nullptr;
	mTiles.clear();
	bMakeSearch = false;
}

void TileMap::Update(float DeltaTime)
{

	//Sets to true that a search needs to happen and how it will be drawn.
	UpdateDrawLineType();
	UpdateEndSearchPoint(mColumns, mRows);
	//1h.2 OBS
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
			const Texture2D& texture = mTiles[tileIndex].texture;

			//getting position to draw
			const REng::Math::Vector2 textPos = {x * tileSize , y * tileSize};

			DrawTexture(texture, textPos.x, textPos.y, WHITE);

			//draw line for every node that is connected
			if (mDrawLineType == DrawLineType::DLT_DebugLine)
			{
				if (mTiles[tileIndex].weight < weightOfBlocking)
				{
					DrawDebugLine(x, y);
				}
			}
		}
	}

	//BFS//DFS
	REng::Math::Vector2 endposition =  GetPixelPosition(endPos.x, endPos.y);
	const REng::Math::Vector2 StartPos = GetIndexPositionByPixel(Character::Get().GetPlayerPos().x, Character::Get().GetPlayerPos().y);
	SearchAndDraw(StartPos.x,StartPos.y, endPos.x, endPos.y);

	//Draw End Point position
	DrawCircle(endposition.x, endposition.y, 10.f, RED);

	//Render UI
	RenderUI();

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
		//once the mMap is totally loaded
		fclose(file);
	}

	//Initialize mGridBasedGraph;
	mGridBasedGraph.Initialize(mColumns, mRows);

	//Conect the nodes to its neighbors
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
			int weight = ChargeWeight(fullpath);
			Tiles tiles({ LoadTexture(fullpath.c_str()), weight });

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

std::vector<REng::Math::Vector2> TileMap::FindPath(int startX, int startY, int endX, int endY)
{
	mClosedList.clear();
	std::vector<REng::Math::Vector2> path;
	AI::NodeList closedList;
	path.clear();

	switch (mDrawLineType)
	{
	case DrawLineType::DLT_BFS:
	{
		AI::BFS bfs;
		if (bfs.Run(mGridBasedGraph, startX, startY, endX, endY))
		{
			closedList = bfs.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->column, node->row));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
		}

		mClosedList = bfs.GetClosedList();
	}
		break;
	case DrawLineType::DLT_DFS:
	{
		AI::DFS dfs;
		if (dfs.Run(mGridBasedGraph, startX, startY, endX, endY))
		{
			closedList = dfs.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->column, node->row));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
		}

		mClosedList = dfs.GetClosedList();
	}
		break;
	case DrawLineType::DLT_Dijktra:

		path = FindPathDijkistra(startX, startY, endX, endY);

		break;
	case DrawLineType::DLT_AStar:

		path = FindPathAStar(startX, startY, endX, endY);

		break;
	case DrawLineType::DLT_NONE:
		break;
	default:
		break;
	}

	return path;
}

//Dijkstra																WEEK 4*****
float TileMap::GetCost(const AI::GridBasedGraph::Node* node) const
{
	if (node == nullptr)
	{
		return 0.0f;
	}
	const int mapIndex = GetIndex(node->column, node->row);
	const int tileIndex = mMap[mapIndex];

	return static_cast<float>(mTiles[tileIndex].weight);
}

float TileMap::GetHeuristics(const AI::GridBasedGraph::Node* nodeA, const AI::GridBasedGraph::Node* nodeB) const
{

	if (nodeA == nullptr || nodeB == nullptr)
	{
		return 0.0f;
	}

	float distance = 0.0f;
	float dif_X = 0.0f;
	float dif_Y = 0.0f;
		const int D = 1;
		const int D2 = 1;

	switch (mHeuristicsType)
	{


	case HeuristicsType::HT_ManHattan:

		dif_X = abs(nodeA->column - nodeB->column);
		dif_Y = abs(nodeA->row - nodeB->row);
		distance = D * dif_X + dif_Y;

		break;
	case HeuristicsType::HT_Euclidean://pitagoras

		dif_X = nodeA->column - nodeB->column;
		dif_Y = nodeA->row - nodeB->row;
		distance = D * sqrt(dif_X * dif_X + dif_Y * dif_Y);

		break;
	case HeuristicsType::HT_Diagonal:

		dif_X = abs(nodeA->column - nodeB->column);
		dif_Y = abs(nodeA->row - nodeB->row);
		distance = D * (dif_X + dif_Y) + (D2  - 2 * D) * std::min(dif_X, dif_Y);

		break;
	default:
		break;
	}

	return distance;
}

std::vector<REng::Math::Vector2> TileMap::FindPathDijkistra(int startX, int startY, int endX, int endY)
{

	mClosedList.clear();
	std::vector<REng::Math::Vector2> path;
	AI::NodeList closedList;

		AI::Dijkstra dijkstra;
		//Wrapper function
		auto getCostWrapper = [&](const AI::GridBasedGraph::Node* nodeToGetCost)
		{
			return GetCost(nodeToGetCost);
		};

		if (dijkstra.Run(mGridBasedGraph, startX, startY, endX, endY, getCostWrapper))
		{
			closedList = dijkstra.GetClosedList();
			auto node = closedList.back();
			while (node != nullptr)
			{
				path.push_back(GetPixelPosition(node->column, node->row));
				node = node->parent;
			}
			std::reverse(path.begin(), path.end());
		}

		mClosedList = dijkstra.GetClosedList();

	return path;
}

std::vector<REng::Math::Vector2> TileMap::FindPathAStar(int startX, int startY, int endX, int endY)
{
	mClosedList.clear();
	std::vector<REng::Math::Vector2> path;
	AI::NodeList closedList;

	AI::AStar aStar;
	//Wrapper function
	auto getCostWrapper = [&](const AI::GridBasedGraph::Node* nodeToGetCost)
	{
		return GetCost(nodeToGetCost);
	};


	auto getHeuristic = [&](const AI::GridBasedGraph::Node* nodeA, const AI::GridBasedGraph::Node* nodeB)
	{
		return GetHeuristics(nodeA, nodeB);
	};

	if (aStar.Run(mGridBasedGraph, startX, startY, endX, endY, getCostWrapper, getHeuristic))
	{
		closedList = aStar.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}

	mClosedList = aStar.GetClosedList();

	return path;
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

void TileMap::UpdateDrawLineType()
{
	
	if (IsKeyPressed(KeyboardKey::KEY_F1))
	{
		mDrawLineType = DrawLineType::DLT_BFS;
		bMakeSearch = true;
		mAlgorithmText = "BFS Search";
	}
	else if (IsKeyPressed(KeyboardKey::KEY_F2))
	{
		mDrawLineType = DrawLineType::DLT_DFS;
		bMakeSearch = true;
		mAlgorithmText = "DFS Search";
	}
	else if (IsKeyPressed(KeyboardKey::KEY_F3))
	{
		mDrawLineType = DrawLineType::DLT_DebugLine;
		mAlgorithmText = "Draw debug lines";
	}
	else if (IsKeyPressed(KeyboardKey::KEY_F4))
	{
		mDrawLineType = DrawLineType::DLT_Dijktra;
		bMakeSearch = true;
		mAlgorithmText = "Dijkstra Search";
	}
	else if (IsKeyPressed(KeyboardKey::KEY_F5))
	{
		mDrawLineType = DrawLineType::DLT_AStar;
		bMakeSearch = true;
		mAlgorithmText = "A* Search";
	}
	else if(IsKeyPressed(KeyboardKey::KEY_N))
	{
		mDrawLineType = DrawLineType::DLT_NONE;
		mAlgorithmText = "";
	}

	//Modules

	if (IsKeyPressed(KeyboardKey::KEY_KP_5))
	{
		mModuleID++;
		if (mModuleID > 2)
		{
			mModuleID = 0;
		}
		switch (mModuleID)
		{
		case 0:
		{
			mHeuristicsType = HeuristicsType::HT_ManHattan;
			mHeuristicsText = "Heuristics: ManHanttan";
			break;
		}
		case 1:
		{
			mHeuristicsType = HeuristicsType::HT_Euclidean;
			mHeuristicsText = "Heuristics: Euclidean";
		break;
		}
		case 2:
		{
			mHeuristicsType = HeuristicsType::HT_Diagonal;
			mHeuristicsText = "Heuristics: Diagonal";
			break;
		}
		default:
			mHeuristicsType = HeuristicsType::HT_ManHattan;
			mHeuristicsText = "Heuristics: ManHanttan";
			break;
		}
	}
}

//AI Section

void TileMap::DrawDebugLine(const int& x = 0, const int& y = 0)
{
		
	const int startX = static_cast<int>(x * tileSize + tileHalthWidth);
	const int startY = static_cast<int>(y * tileSize + tileHalthHeight);
	
	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::North])
	{
		const int endX = static_cast<int>(x * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * (y - 1) + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::South])
	{
		const int endX = static_cast<int>(x * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * (y + 1) + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::East])
	{
		const int endX = static_cast<int>((x + 1) * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * y + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::West])
	{
		const int endX = static_cast<int>((x - 1) * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * y + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::NorthEast])
	{
		const int endX = static_cast<int>((x + 1) * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * (y - 1) + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, WHITE);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::NorthWest])
	{
		const int endX = static_cast<int>((x - 1) * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * (y - 1) + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::SouthEast])
	{
		const int endX = static_cast<int>((x + 1)* tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * (y + 1) + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

	if (mGridBasedGraph.GetNode(x, y)->neighbors[AI::GridBasedGraph::SouthWest])
	{
		const int endX = static_cast<int>((x - 1) * tileSize + tileHalthWidth);
		const int endY = static_cast<int>(tileSize * (y + 1) + tileHalthHeight);
		DrawLine(startX, startY, endX, endY, RED);
	}

}

void TileMap::DrawParentLine(AI::GridBasedGraph::Node* node)
{
	if (node->parent != nullptr)
	{
		const REng::Math::Vector2 StartPos = GetPixelPosition(node->column, node->row);
		const REng::Math::Vector2 EndPos = GetPixelPosition(node->parent->column, node->parent->row);
		
		DrawLine((int)StartPos.x, (int)StartPos.y, (int)EndPos.x, (int)EndPos.y, RED);
	}
}

void TileMap::LoadGridBaseGraphNeighbors()
{
	for (int y = 0; y < mGridBasedGraph.GetRows(); y++)
	{
		for (int x = 0; x < mGridBasedGraph.GetColumns(); x++)
		{
			AI::GridBasedGraph::Node* node = mGridBasedGraph.GetNode(x, y);
			
			LoadNodeNeighbors(node, x, y - 1);
			LoadNodeNeighbors(node, x, y + 1);
			LoadNodeNeighbors(node, x + 1, y);
			LoadNodeNeighbors(node, x - 1, y);
			LoadNodeNeighbors(node, x + 1, y -1);
			LoadNodeNeighbors(node, x + 1, y + 1);
			LoadNodeNeighbors(node, x - 1, y - 1);
			LoadNodeNeighbors(node, x - 1, y + 1);
		}
	}
}

void TileMap::LoadNodeNeighbors(AI::GridBasedGraph::Node* currentNode, const int x, const int y)
{
	int index = GetIndex(x, y);

	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return;
	}

	const int tileIndex = mMap[index];
	const int weight = mTiles[tileIndex].weight;

	if (weight > weightOfBlocking)
	{
		return;
	}

	AI::GridBasedGraph::Node* neighbourNode = mGridBasedGraph.GetNode(x, y);

	//West side
	if (x < currentNode->column)
	{
		if (y < currentNode->row)
		{
			currentNode->neighbors[AI::GridBasedGraph::NorthWest] = neighbourNode;
		}
		else if (y > currentNode->row)
		{
			currentNode->neighbors[AI::GridBasedGraph::SouthWest] = neighbourNode;
		}
		else
		{
			currentNode->neighbors[AI::GridBasedGraph::West] = neighbourNode;
		}
	}

	//East side
	if (x > currentNode->column)
	{
		if (y < currentNode->row)
		{
			currentNode->neighbors[AI::GridBasedGraph::NorthEast] = neighbourNode;
		}
		else if (y > currentNode->row)
		{
			currentNode->neighbors[AI::GridBasedGraph::SouthEast] = neighbourNode;
		}
		else
		{
			currentNode->neighbors[AI::GridBasedGraph::East] = neighbourNode;
		}
	}

	//North and South side
	if (x == currentNode->column)
	{
		if (y < currentNode->row)
		{
			currentNode->neighbors[AI::GridBasedGraph::North] = neighbourNode;
		}
		else
		{
			currentNode->neighbors[AI::GridBasedGraph::South] = neighbourNode;
		}
	}
}

REng::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
	return
	{
		(x + 0.5f) * tileSize,
		(y + 0.5f) * tileSize
	};
}

REng::Math::Vector2 TileMap::GetIndexPositionByPixel(int x, int y) const
{
	return
	{
		(x + 32.5f) / tileSize,
		(y + 32.5f) / tileSize
	};
}

void TileMap::SearchAndDraw(int startX, int startY, int endX, int endY)
{
	switch (mDrawLineType)
	{
	case DrawLineType::DLT_DebugLine:
		break;
	case DrawLineType::DLT_BFS:
	case DrawLineType::DLT_DFS:

		if (bMakeSearch)
		{
			mPath = FindPath(startX, startY, endX, endY);
			bMakeSearch = !bMakeSearch;
		}

		for(auto node : mClosedList)
		{
			DrawParentLine(node);
		}

		for (size_t i = 0; i < mPath.size(); i++)
		{
			if (i == 0)
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, DARKGREEN);
			}
			else if (i < mPath.size() - 1)
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, YELLOW);
			}
			else
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, RED);
			}
		}
		break;
	case DrawLineType::DLT_Dijktra:


		if (bMakeSearch)
		{
			mPath = FindPath(startX, startY, endX, endY);
			bMakeSearch = !bMakeSearch;
		}

		for (auto node : mClosedList)
		{
			DrawParentLine(node);
		}

		for (size_t i = 0; i < mPath.size(); i++)
		{
			if (i == 0)
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, DARKGREEN);
			}
			else if (i < mPath.size() - 1)
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, YELLOW);
			}
			else
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, RED);
			}
		}

		break;

	case DrawLineType::DLT_AStar:


		if (bMakeSearch)
		{
			mPath = FindPath(startX, startY, endX, endY);
			bMakeSearch = !bMakeSearch;
		}

		for (auto node : mClosedList)
		{
			DrawParentLine(node);
		}

		for (size_t i = 0; i < mPath.size(); i++)
		{
			if (i == 0)
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, DARKGREEN);
			}
			else if (i < mPath.size() - 1)
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, YELLOW);
			}
			else
			{
				DrawCircle(mPath[i].x, mPath[i].y, 10, RED);
			}
		}

		break;

	default:
		break;
	}
}

void TileMap::RenderUI()
{
	
	const int xAlgPos = static_cast<int>(400);
	const int yAlgPos = static_cast<int>(25.0f);

	DrawText(TextToUpper(mAlgorithmText.c_str()), xAlgPos, yAlgPos, 22 ,WHITE);

	if (mDrawLineType == DrawLineType::DLT_AStar)
	{
		const int xHeuristicPos = mAlgorithmText.length() * tileSize + xAlgPos;
		DrawText(TextToUpper(mHeuristicsText.c_str()), xHeuristicPos, yAlgPos, 22, WHITE);
	}

}

