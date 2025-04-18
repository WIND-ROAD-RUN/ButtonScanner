#pragma once

#include <utility>
#include<string>

namespace rw
{
	namespace imest
	{
		using Point = std::pair<int, int>;

		struct ProcessRectanglesResultST
		{
			Point left_top;							//左上角坐标
			Point right_bottom;						//右下角坐标
			int classId;							//0外径 1是孔
			int track_id;							//跟踪id
			int label_len;							//名称长度
			int mask_b;								//b分类值
			int mask_g;								//g分量值
			int mask_r;								//r分量值
			double score;							//得分
			std::string label_text;					//名称
		};
	}
}
