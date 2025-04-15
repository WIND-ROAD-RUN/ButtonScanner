#include"imest_ModelEngineST.h"

#include "yolov5v6_seg_trt.h"

namespace rw
{
	namespace imest
	{
        ProcessRectanglesResult ConvertPyRecMaskResultToProcessRectanglesResult(PyRecMaskResult& pyRecMaskResult)
        {
            ProcessRectanglesResult processRectanglesResult;
            processRectanglesResult.left_top = std::make_pair(pyRecMaskResult.left, pyRecMaskResult.top);
            processRectanglesResult.right_bottom = std::make_pair(pyRecMaskResult.right, pyRecMaskResult.bottom);
            processRectanglesResult.classId = pyRecMaskResult.classID;
            processRectanglesResult.track_id = pyRecMaskResult.track_id;
            processRectanglesResult.label_len = pyRecMaskResult.label_len;
            processRectanglesResult.mask_b = pyRecMaskResult.mask_b;
            processRectanglesResult.mask_g = pyRecMaskResult.mask_g;
            processRectanglesResult.mask_r = pyRecMaskResult.mask_r;
            processRectanglesResult.score = pyRecMaskResult.score;
            processRectanglesResult.label_text = std::string(pyRecMaskResult.label_text);
            return processRectanglesResult;
        }

		ModelEngine::ModelEngine(std::string modelPath, std::string nameFilePath)
		{
		}
	}
}
