#pragma once

#include <utility>
#include<string>

namespace rw
{
    namespace ime //image model engine
    {
        using Point = std::pair<int, int>;

        struct ProcessRectanglesResult
        {
            Point left_top;							//���Ͻ�����
			Point right_bottom;						//���½�����
			int classId;
			int track_id;							//����id
			int label_len;							//���Ƴ���
			int mask_b;								//b����ֵ
			int mask_g;								//g����ֵ
			int mask_r;								//r����ֵ
			double score;							//�÷�
			std::string label_text;					//����
        };


    }
}
