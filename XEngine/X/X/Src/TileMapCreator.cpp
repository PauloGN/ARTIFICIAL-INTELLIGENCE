#include "Precompiled.h"
#include "TileMapCreator.h"

using namespace X;
#pragma warning(disable: 4996)
namespace
{
	// pointer to the object of the class
	std::unique_ptr<TileMapCreator> tileMapInstance;
	int tileIndex = 0;
}

void TileMapCreator::LoadMap(const std::filesystem::path& MapName)
{
	//prevent to call the load map twice
	if (mMap)
	{
		mMap.reset();
	}

	//create the file
	FILE* file = nullptr;
	// open the file through the file name, convert to u8string and character chain, "r" read
	fopen_s(&file, MapName.u8string().c_str(), "r"); 
	// Inside the file get the value based on the str token and assign into the variable
	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows); 

	// Now we have the size of columns and rows we can create the array map that will be rendered on screen
	mMap = std::make_unique<int[]>(mColumns * mRows);

	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			// first iteration           0 + (0 * mColumns);
			// second iteration         1 + (0 * mColumns);
			// function GetTndex returns x + (y * mColumns);
			const int index = GetIndex(x, y);	
												
			mMap[index] = fgetc(file) - '0';
			/*
				representation of number in character regarding Ascii table is

				(0 = 48, 1 = 49, 2 = 50,..... 9 = 57)

				then to convert a char to the correspondent int number, we subtract the char '0' which is 48 from any char (from '0' to '9')
				and it will return the corespondent int.
			*/
		}

		fgetc(file);//read '/n' and jump to the next row
	}

	fclose(file);
}

void TileMapCreator::LoadTextures(const std::filesystem::path& TextureName)
{
	//prevents to get an old vector full of information
	mTiles.clear();

	FILE* file = nullptr;
	fopen_s(&file, TextureName.u8string().c_str(), "r");
	// range of the loop
	unsigned count = 0;

	fscanf_s(file, "Count: %d\n", &count);

	for (unsigned i = 0; i < count; ++i)
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));
		mTiles.push_back(X::LoadTexture(buffer));
	}

	fclose(file);
}

void TileMapCreator::Load(const std::filesystem::path& MapName, const std::filesystem::path& TileSetName)
{
	//to keep things nice and clean this function call both =>
	LoadMap(MapName);
	LoadTextures(TileSetName);
}

void TileMapCreator::Unload()
{
	mColumns = 0;
	mRows = 0;
	mMap.reset();
	mMap = nullptr;
	mTiles.clear();
}

void TileMapCreator::Update(const float& deltaTime)
{
	//Empty
	if(deltaTime < 0.0f)
	{
		
	}
}

void TileMapCreator::Render()
{
	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int mapIndex = GetIndex(x, y);
			tileIndex = mMap[mapIndex];//mMap is an array that maps all the screen positions to render the appropriate image.
			const X::TextureId textureId = mTiles.at(tileIndex);// tileIndex got the number of the object that will be rendered on screen

			const X::Math::Vector2 worldPosition = { x * tileSize, y * tileSize };
			//const X::Math::Vector2 screenPosition = XCamera::Get().ConvertToScreenPosition(worldPosition);

			X::DrawSprite(textureId, worldPosition, X::Pivot::Left);
		}
	}
}

int TileMapCreator::GetIndex(int colum, int row) const
{
	//Example: 
	//if looking for column 1 and row 3 with 10 total columns 
	// index = 1 + (3 * 10)	
	// index = 31;
	return colum + (row * mColumns);
}

X::Math::Rect TileMapCreator::GetBounds() const
{
	//return X::Math::Rect();
	return
	{
		0.0f,				// left
		0.0f,				// top
		static_cast<float>(mColumns) * tileSize,// right
		static_cast<float>(mRows) * tileSize	// bottom
	};
}

void TileMapCreator::StaticInitialize()
{
	//prevent more than one initialization
	XASSERT(tileMapInstance == nullptr, "WRONG!!! Tile map has already been initialized");
	tileMapInstance = std::make_unique<TileMapCreator>();//instantiate the object
}

void TileMapCreator::StaticTerminate()
{
	//Resets unique pointer that points to the object of the class
	tileMapInstance.reset();
}

TileMapCreator& TileMapCreator::Get()
{
	//Prevent to get an empty object
	XASSERT(tileMapInstance != nullptr, "WRONG!!! objec not initialized yet...");
	//return a pointer to the object internally instantiated
	return *tileMapInstance;
}
