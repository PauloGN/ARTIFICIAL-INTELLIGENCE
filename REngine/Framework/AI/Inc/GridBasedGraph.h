#pragma once

namespace AI 
{
	class GridBasedGraph
	{
	public:

		enum Directions
		{
			North,
			South,
			East,
			West,
			NorthEast,
			NorthWest,
			SouthEast,
			SouthWest
		};

		//Node Declaration
		struct Node
		{
			std::array<Node*, 8> neighbors = {};
			//Witch Rows and Column this node is at the moment
			int row = 0;
			int column = 0;
		};

		//
		void Initialize(int Columns, int Rows);


		Node* GetNode(int x, int y);//allow modify the node 
		const Node* GetNode(int x, int y)const;// do not allow modifications 

		int GetColumns() const;
		int GetRows() const;

	private:

		//Total number of columns and rows
		int mRows = 0;
		int mColumns = 0;

		//vector of nodes
		std::unique_ptr<Node[]> mNodes = nullptr;

		int GetIndex(int x, int y) const;

	};
}