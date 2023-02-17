#pragma once
#include <REngine.h>
#include <iostream>
#include <string>
#include <vector>
#include <AI.h>

enum class DrawLineType : uint8_t
{
	DLT_DebugLine,
	DLT_BFS,
	DLT_DFS,
	DLT_Dijktra,
	DLT_AStar,
	DLT_NONE
};

enum class HeuristicsType : uint8_t
{
	HT_ManHattan,
	HT_Euclidean,
	HT_Diagonal
};

struct Tiles 
{
	Texture2D texture;
	int weight;
	Tiles(Texture2D t, int w):texture(t), weight(w){}
};

class TileMap
{
public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static TileMap& Get();

	//GameTile states
	void Load(const char* mapName, const char* TileCollectionName);
	void Unload();
	void Update(float DeltaTime);
	void Render();

	void LoadTileMap(const char* mapName);
	void LoadTilesTexture(const char* TileCollectionName);

	bool IsCollisdingWith(REng::Math::LineSegment& lineSegment) const;
	Rectangle GetBound()const;

	//FIND PATH *****************  WEEK 03
	std::vector<REng::Math::Vector2> FindPath(int startX, int startY, int endX, int EndY);//Given a initial position and destination find a path


	//WEEK 04 DIJKSTRA AND A*

	float GetCost(const AI::GridBasedGraph::Node* node) const;
	float GetHeuristics(const AI::GridBasedGraph::Node* nodeA, const AI::GridBasedGraph::Node* nodeB) const;
	std::vector<REng::Math::Vector2> FindPathDijkistra(int startX, int startY, int endX, int EndY);
	std::vector<REng::Math::Vector2> FindPathAStar(int startX, int startY, int endX, int EndY);

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
	void DrawParentLine(AI::GridBasedGraph::Node* node);

	void LoadGridBaseGraphNeighbors();
	void LoadNodeNeighbors(AI::GridBasedGraph::Node* currentNode, const int x , const int y);

	//********************* WEEK 03

	bool bMakeSearch = false;
	DrawLineType mDrawLineType = DrawLineType::DLT_NONE;
	std::vector<REng::Math::Vector2> mPath;
	REng::Math::Vector2 GetPixelPosition(int x, int y) const;
	REng::Math::Vector2 GetIndexPositionByPixel(int x, int y) const;
	std::list<AI::GridBasedGraph::Node*> mClosedList;
	void SearchAndDraw(int startX, int startY, int endX, int endY);

	//****************** WEEK 04

	HeuristicsType mHeuristicsType = HeuristicsType::HT_ManHattan;

	//UI
	std::string mAlgorithmText = "";
	std::string mHeuristicsText = "Heuristics: ManHanttan";;
	void RenderUI();
	int8_t mModuleID = 0;

};

