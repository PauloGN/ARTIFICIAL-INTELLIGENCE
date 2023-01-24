#pragma once
#include "GridBasedGraph.h"


namespace AI
{
	using NodeList = std::list<GridBasedGraph::Node*>;
	class DFS
	{

	public:

		//if the node if found return true
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY);

		const NodeList& GetClosedList()const { return mClosedList; }

	private:

		NodeList mOpenList;
		NodeList mClosedList;

	};
}

