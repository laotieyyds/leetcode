#ifndef SUPER_POINT_H_
#define SUPER_POINT_H_

#include <opencv2/opencv.hpp>
#include <iostream>

using cv::Mat;
using cv::KeyPoint;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class SuperPoint : public cv::Feature2D
{
public:	
	static cv::Ptr<SuperPoint> create(float scale_factor = 1.0f, int num_levels = 1, int first_level = 0, float conf_thresh = 0.015);
	void detectAndCompute(cv::InputArray image, cv::InputArray mask, std::vector<KeyPoint>& keypoints, cv::OutputArray desc, bool use_provided_keypoints = false);

	SuperPoint(float scale_factor = 1.0f, int num_levels = 1, int first_level = 0, float conf_thresh = 0.015);
	~SuperPoint();

private:
	void BuildPyrimid(cv::Mat img);
	void SetScale(float scale_factor = 1.5f, int num_levels = 3, int first_level = -1);

private:
	float conf_thresh_;
	int cell_;
	int dist_thresh_;
	int border_remove_;

	float scale_factor_;
	int num_levels_;
	int first_level_;
	std::vector<cv::Mat> pyrimid_;
	
	cv::dnn::CV__DNN_INLINE_NS::Net net_;


};
#endif
