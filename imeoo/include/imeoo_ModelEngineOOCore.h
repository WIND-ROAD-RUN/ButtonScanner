#pragma once

#include <utility>
#include<string>

namespace rw
{
	namespace imeoo
	{
		using Point = std::pair<int, int>;

		struct ProcessRectanglesResultOO
		{
			Point left_top;
			Point right_bottom;
			int classID;
			int track_id;
			double score;
			std::string label_text;
		};
	}
}
