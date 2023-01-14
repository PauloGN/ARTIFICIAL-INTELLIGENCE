#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;


void GridBasedGraph::Initialize(int Columns, int Rows)
{
	//TODO
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
	//TODO
	int maxLimit = (mRows * mColumns);
	int index = GetIndex(x, y);
	return &mNodes[index];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	//TODO
	const int maxLimit = (mRows * mColumns);
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

int GridBasedGraph::GetIndex(int x, int y) const
{
	return x + (y * mColumns);
}
