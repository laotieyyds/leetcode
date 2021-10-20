#include "super_point.h"
#define MIN_IMAGE_WIDTH 160
#define MIN_IMAGE_HEIGHT 120
#include "super_point_onnx_mem.h"
#define MAT cv::Mat
#define MAT_W(x) x.size[3]
#define MAT_H(x) x.size[2]
#define MAT_C(x) x.size[1]
//src size is [w x h x c]
//softmax normalization on channel
//reshape to dst [w*sw x h*sh]


static int PostProcess(float *src, int w, int h, int c, int sw, int sh, float *dst)
{
	if (c < sw * sh)
	{
		cout << "tensor size insuffienct!\n" << endl;
		return -1;
	}
	float* src_data = NULL;
	float* sum_data = NULL;
	int channel_size = w * h;
	int dst_w = w * sw;

	//compute exp & sum
	cv::Mat sum = cv::Mat::zeros(h, w, CV_32F);
	sum_data = (float*)sum.data; 
	src_data = src;
	for (int i = 0; i < c; i++, src_data += channel_size)
	{
		for (int j = 0; j < channel_size; j++)
		{
			src_data[j] = exp(src_data[j]);
			sum_data[j] += src_data[j];
		}
	}
	for (int j = 0; j < channel_size; j++) sum_data[j] = 1.0f / sum_data[j];

	//reshape & softmax normalization
	src_data = src;
	for (int i = 0; i < sw * sh; i++, src_data += channel_size)
	{
		int start_row = i / sw;
		int start_col = i % sw;
		int dst_start_idx = start_row * dst_w + start_col;
		float* dst_data = dst + dst_start_idx;

		int pixel_idx = 0;
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++, pixel_idx++)
			{
				dst_data[sw * k] = src_data[pixel_idx] * sum_data[pixel_idx];
			}
			dst_data += sh * dst_w;
		}
	}
	return 0;
}

static vector<KeyPoint> NMS(const vector<KeyPoint>& src_keypoints, int h, int w, int dist_thresh, int border_remove)
{
	int level = src_keypoints[0].octave;
	Mat grid = Mat::zeros(h, w, CV_32F);
	for (int i = 0; i < src_keypoints.size(); i++)
		grid.at<float>(src_keypoints[i].pt.y, src_keypoints[i].pt.x) = src_keypoints[i].response;
	Mat dilated;
	Mat elememt = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(dist_thresh, dist_thresh));
	dilate(grid, dilated, elememt);
	Mat local_max;
	compare(grid, dilated, local_max, cv::CMP_EQ);
	vector<KeyPoint> dst_keypoints;
	for (int i = border_remove; i < local_max.rows - border_remove; i++)
		for (int j = border_remove; j < local_max.cols - border_remove; j++)
		{
			if (grid.at<float>(i, j) == 0)
				continue;
			if (local_max.at<uchar>(i, j) == 255)
			{
				KeyPoint cur;
				cur.octave = level;
				cur.pt.x = j;
				cur.pt.y = i;
				cur.response = grid.at<float>(i, j);
				dst_keypoints.push_back(cur);
			}
		}
	return dst_keypoints;
}

static void RefineWidthHeight(int& low, int& high, int dst, int boundary)
{
	int center = (high + low) / 2;
	int low_temp = center - dst / 2;
	int high_temp = center + dst / 2;
	if (low_temp < 0)
	{
		low = 0;
		high = MIN(dst, boundary);
		return;
	}
	else if (high_temp > boundary)
	{
		high = boundary;
		low = MAX(0, high - dst);
		return;
	}
	else
	{
		low = low_temp;
		high = high_temp;
	}
}

SuperPoint::SuperPoint(float scale_factor, int num_levels, int first_level, float conf_thresh)
{
	conf_thresh_ = conf_thresh;
	cell_ = 8;
	dist_thresh_ = 4;
	border_remove_ = 4;
	SetScale(scale_factor, num_levels, first_level);
	net_ = cv::dnn::CV__DNN_INLINE_NS::readNetFromONNX((char *)super_point_onnx_mem, ONNX_BUF_SIZE);
	net_.setPreferableBackend(cv::dnn::CV__DNN_INLINE_NS::DNN_BACKEND_OPENCV);
	net_.setPreferableTarget(cv::dnn::CV__DNN_INLINE_NS::DNN_TARGET_CPU);
	return;
}

SuperPoint::~SuperPoint()
{
}

void SuperPoint::SetScale(float scale_factor, int num_levels, int first_level)
{
	scale_factor_ = scale_factor;
	num_levels_ = num_levels;
	first_level_ = first_level;
}

cv::Ptr<SuperPoint> SuperPoint::create(float scale_factor, int num_levels, int first_level, float conf_thresh)
{
	return cv::makePtr<SuperPoint>(scale_factor, num_levels, first_level, conf_thresh);
}

void SuperPoint::detectAndCompute(cv::InputArray img, cv::InputArray mask, std::vector<KeyPoint>& keypoints, cv::OutputArray descriptors, bool use_provided_keypoints)
{
	keypoints.clear();
	cv::Mat image = img.getMat();
	if (image.channels() > 1) cvtColor(image, image, cv::COLOR_BGR2GRAY);

	//get min rect of mask
	int min_x = 0;
	int min_y = 0;
	int max_x = image.cols;
	int max_y = image.rows;
	if (!mask.empty() && num_levels_ == 1)  //train with original image size gets better result
	{
		cv::Mat mask_r, mask_c;
		cv::reduce(mask, mask_r, 1, cv::REDUCE_MAX);
		cv::reduce(mask, mask_c, 0, cv::REDUCE_MAX);
		for (min_y = 0; min_y < mask_r.rows; min_y++) if (mask_r.data[min_y]) break;
		for (max_y = mask_r.rows; max_y > 0; max_y--) if (mask_r.data[max_y - 1]) break; 
		for (min_x = 0; min_x < mask_c.cols; min_x++) if (mask_c.data[min_x]) break;
		for (max_x = mask_c.cols; max_x > 0; max_x--) if (mask_c.data[max_x - 1]) break; 
	}
	if (max_y - min_y < MIN_IMAGE_HEIGHT)
		RefineWidthHeight(min_y, max_y, MIN_IMAGE_HEIGHT, image.rows);
	if (max_x - min_x < MIN_IMAGE_WIDTH)
		RefineWidthHeight(min_x, max_x, MIN_IMAGE_WIDTH, image.cols);
	
	cv::Mat roi_img = image.rowRange(min_y, max_y).colRange(min_x, max_x).clone();
	BuildPyrimid(roi_img);

	cv::Mat desc;
	for (int level = 0; level < num_levels_; level++)
	{
		int w = pyrimid_[level].cols;
		int h = pyrimid_[level].rows;

		float scale = 1.0f * w / roi_img.cols;
		float inv_scale = 1.0f * roi_img.cols / w;

		w = w & 0xfffffff0;
		h = h & 0xfffffff0;
		cv::Mat input_image = pyrimid_[level].rowRange(0, h).colRange(0, w).clone();
		float inv_255 = 1.0f / 255;

		printf("superpoint input size %d x %d\n", w, h);

		MAT input_blob;
		MAT tensor_heatmap, tensor_desc;

		{
			//ScopeTimer sp_timer("net inference");
			input_blob = cv::dnn::CV__DNN_INLINE_NS::blobFromImage(input_image, inv_255);
			net_.setInput(input_blob);
			std::vector<std::string> blob_names{ "output_kps", "output_des" };
			std::vector<cv::Mat> output_blobs;
			net_.forward(output_blobs, blob_names);
			tensor_heatmap = output_blobs[0];
			tensor_desc = output_blobs[1];
		}

		int heatmap_c = MAT_C(tensor_heatmap);// output_blobs[0].size[1];
		int heatmap_h = MAT_H(tensor_heatmap);
		int heatmap_w = MAT_W(tensor_heatmap);
		cv::Mat heatmap = cv::Mat::zeros(heatmap_h * cell_, heatmap_w * cell_, CV_32F);
		if (0 != PostProcess((float*)tensor_heatmap.data, heatmap_w, heatmap_h, heatmap_c, cell_, cell_, (float*)heatmap.data)) continue;

		//find keypoints
		vector<KeyPoint> raw_keypoints;
		float* heatmap_data = (float*)heatmap.data;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++, heatmap_data++)
			{
				if (*heatmap_data <= conf_thresh_) continue;
				raw_keypoints.push_back(KeyPoint());
				KeyPoint& cur = raw_keypoints.back();
				cur.octave = level;
				cur.pt.x = j;
				cur.pt.y = i;
				cur.response = *heatmap_data;
			}
		}
		if (raw_keypoints.empty()) continue;
		raw_keypoints = NMS(raw_keypoints, h, w, dist_thresh_, border_remove_);		

		//transform to org image
		for (int i = 0; i < raw_keypoints.size(); i++)
		{
			raw_keypoints[i].pt.x = raw_keypoints[i].pt.x * inv_scale + min_x;
			raw_keypoints[i].pt.y = raw_keypoints[i].pt.y * inv_scale + min_y;
		}
		if(!mask.empty())
			cv::KeyPointsFilter::runByPixelsMask(raw_keypoints, mask.getMat());

		//descriptors interpolation 
		int feature_dim = MAT_C(tensor_desc);
		int desc_h = MAT_H(tensor_desc);
		int desc_w = MAT_W(tensor_desc);
		Mat raw_desc = Mat::zeros(raw_keypoints.size(), feature_dim, CV_32F);
		int channel_size = desc_w * desc_h;
		for (int i = 0; i < raw_keypoints.size(); i++)
		{
			float x = (float)(raw_keypoints[i].pt.x - min_x) * scale / cell_;
			float y = (float)(raw_keypoints[i].pt.y - min_y) * scale / cell_;
			int x1 = int(x);
			int y1 = int(y);
			float dx = x - x1;
			float dy = y - y1;
			float dxy = dx * dy;

			float w11 = 1 - dx - dy + dxy;// (1 - dx)* (1 - dy);
			float w12 = dy - dxy;// (1 - dx)* dy;
			float w21 = dx - dxy;// dx* (1 - dy);
			float w22 = dxy;// dx* dy;
			int idx11 = y1 * desc_w + x1;
			int idx12 = idx11 + desc_w;
			int idx21 = idx11 + 1;
			int idx22 = idx21 + 1;
			Mat cur_desc = Mat(1, feature_dim, CV_32F);
			float* cur_desc_array = (float*)cur_desc.data;

			float* channel_data = (float *)tensor_desc.data;
			for (int j = 0; j < feature_dim; j++, channel_data += channel_size)
			{
				cur_desc_array[j] = w11 * channel_data[idx11] + w12 * channel_data[idx12] + w21 * channel_data[idx21] + w22 * channel_data[idx22];
			}
			normalize(cur_desc, raw_desc.row(i));
		}
		keypoints.insert(keypoints.end(), raw_keypoints.begin(), raw_keypoints.end());
		desc.push_back(raw_desc);
	}
	descriptors.assign(desc);
}

void SuperPoint::BuildPyrimid(cv::Mat img)
{
	int min_level = first_level_;
	int max_level = min_level + num_levels_ - 1;
	float inv_scale_factor = floor(1.0f / scale_factor_ * 10 + 0.5) / 10;
	pyrimid_.resize(num_levels_);
	if (min_level > 0)
	{
		float scale = pow(inv_scale_factor, min_level);
		resize(img, pyrimid_[0], cv::Size(0, 0), scale, scale, cv::INTER_LINEAR);
		for (int i = 1; i < num_levels_; i++)
			resize(pyrimid_[i - 1], pyrimid_[i], cv::Size(0, 0), inv_scale_factor, inv_scale_factor, cv::INTER_LINEAR);
	}
	else if (max_level < 0)
	{
		float scale = pow(inv_scale_factor, max_level);
		resize(img, pyrimid_[num_levels_ - 1], cv::Size(0, 0), scale, scale, cv::INTER_LINEAR);
		for (int i = num_levels_ - 2; i >= 0; i++)
			resize(pyrimid_[i + 1], pyrimid_[i], cv::Size(0, 0), scale_factor_, scale_factor_, cv::INTER_LINEAR);
	}
	else
	{
		pyrimid_[0] = img.clone();
		int i = 0;
		for (i = 1; i <= max_level; i++)
			resize(pyrimid_[i - 1], pyrimid_[i], cv::Size(0, 0), inv_scale_factor, inv_scale_factor, cv::INTER_LINEAR);

		if (i < num_levels_)
			resize(pyrimid_[0], pyrimid_[i], cv::Size(0, 0), scale_factor_, scale_factor_, cv::INTER_LINEAR);

		for (i = i + 1; i < num_levels_; i++)
			resize(pyrimid_[i - 1], pyrimid_[i], cv::Size(0, 0), scale_factor_, scale_factor_, cv::INTER_LINEAR);
	}
#pragma omp parallel for
	for (int level = 1; level < num_levels_; ++level)  //original image level do not need Gaussian blur
	{
		cv::GaussianBlur(pyrimid_[level], pyrimid_[level], cv::Size(3, 3), 1, 1);  //Size(3,3) better than Size(5,5)
	}
}
