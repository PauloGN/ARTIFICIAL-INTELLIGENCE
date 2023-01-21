#pragma once
#include <REngine.h>
#include <iostream>
#include <string>
#include <vector>
#include <AI.h>

enum class DrawLineType : uint16_t
{
	DLT_DebugLine,
	DLT_BFS,
	DLT_DFS,
	DLT_NONE
};

struct Tiles 
{
	Texture2D texture;
	int16_t weight;
};

class TileMap
{
public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static TileMap& Get();

	void Load(const char* mapName, const char* TileCollectionName);
	void Unload();
	void Update(float DeltaTime);
	void Render();

	void LoadTileMap(const char* mapName);
	void LoadTilesTexture(const char* TileCollectionName);

	bool IsCollisdingWith(REng::Math::LineSegment& lineSegment) const;
	Rectangle GetBound()const;

	//FIND PATH *****************  WEEK 03

	std::vector<REng::Math::Vector2> FindPath(int startX, int startY, int endX, int EndY);


private:

	//litle math to get index simulating bidimentional array
	int GetIndex(int column, int row) const;
	//Get weight from the tile list
	int ChargeWeight(std::string& tileName);

	//update DrawLine type

	void UpdateDrawLineType();

private:

	//map positions
	std::unique_ptr<int[]> mMap = nullptr;
	int mColumns = 0;
	int mRows = 0;

	//individual tiles
	std::vector<Tiles> mTiles;

	//GridBase AI Section
	AI::GridBasedGraph mGridBasedGraph;

	void DrawDebugLine(const int& x, const int& y);

	void LoadGridBaseGraphNeighbors();
	void LoadNodeNeighbors(AI::GridBasedGraph::Node* currentNode, const int x , const int y);
	

	//********************* WEEK 03

	bool bMakeSearch = false;
	DrawLineType mDrawLineType;
	std::vector<REng::Math::Vector2> mPath;
	REng::Math::Vector2 GetPixelPosition(int x, int y) const;
	REng::Math::Vector2 GetIndexPositionByPixel(int x, int y) const;
	std::list<AI::GridBasedGraph::Node*> mClosedList;
	void SearchAndDraw(int startX, int startY, int endX, int endY);
};

