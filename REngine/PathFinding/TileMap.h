#pragma once
#include <REngine.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>


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


private:

	int GetIndex(int column, int row) const;

private:


	//map positions
	std::unique_ptr<int[]> mMap = nullptr;
	int mColumns = 0;
	int mRows = 0;

	//individual tiles
	std::vector<Texture2D> mTiles;


	//std::vector<int> mTileMap;
	//std::vector<Texture2D> mTiles;
	//int mColumns = 0;
	//int mRows = 0;
	//int tileSize

};

