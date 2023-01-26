#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;


void GridBasedGraph::Initialize(int Columns, int Rows)
{
	//Resize mNodes to the matching dimention
	//for each node, set its atributes (row / column)

	mRows = Rows;
	mColumns = Columns;

	if (mNodes)
	{
		mNodes.reset();
		mNodes = nullptr;
	}

	//Initialize
	mNodes = std::make_unique<Node[]>(mColumns * mRows);

	//Loop through rows and Columns
	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int index = GetIndex(x, y);
			mNodes[index].column = x;
			mNodes[index].row = y;
		}
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return nullptr;
	}

	const int index = GetIndex(x, y);
	return &mNodes[index];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return nullptr;
	}

	const int index = GetIndex(x, y);
	return &mNodes[index];
}

int GridBasedGraph::GetColumns() const
{
	return mColumns;
}

int GridBasedGraph::GetRows() const
{
	return mRows;
}

void AI::GridBasedGraph::ResetSearchParam()
{
	if (mNodes == nullptr)
	{
		return;
	}

	for (int i = 0; i < mRows * mColumns; i++)
	{
		mNodes[i].parent = nullptr;
		mNodes[i].bOpened = false;
		mNodes[i].bClosed = false;
		mNodes[i].g = 0.0f;
	}
}

int GridBasedGraph::GetIndex(int x, int y) const
{
	return x + (y * mColumns);
}
