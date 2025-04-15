#pragma once

#include<string>

namespace rw
{
	namespace imeot
	{
		using Point = std::pair<float, float>;

		struct ProcessRectanglesResultOT
		{
			Point left_top;
			Point right_bottom;
			int center_x;							//旋转矩形中心点坐标x
			int center_y;							//旋转矩形中心点坐标y
			int width;								//旋转矩形框宽度
			int height;								//旋转矩形框高度
			double angle;							//旋转矩形框角度
			int classID;							//类别id
			int label_len;							//名称长度
			double score;							//得分
			std::string label_text;
		};
	}
}
