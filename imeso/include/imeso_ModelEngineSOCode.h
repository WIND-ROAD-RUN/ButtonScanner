#pragma once
#include<string>

namespace rw
{
	namespace imeso
	{

		using Point = std::pair<float, float>;

		struct ProcessRectanglesResultSO
		{
			Point left_top;
			Point right_bottom;
			int classID;							//类别id
			int track_id;							//跟踪id
			int label_len;							//名称长度
			int mask_id;							//maskid
			double score;							//得分
			std::string label_text;					//名称
		};
	}
}