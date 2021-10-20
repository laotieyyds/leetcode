#include<iostream>
#include "super_point.h"
#include"super_point_onnx_mem.h"
//void GetKeypoints(const cv::Mat& image, vector<cv::KeyPoint>&points, cv::Mat&des) {
//	
//}

void FindInlierMatch(const vector<cv::DMatch>& matches, const vector<cv::KeyPoint> trainkp,
	const vector<cv::KeyPoint> querykp, vector<cv::DMatch>& inlier_match, vector<cv::DMatch>& in_inlier_match)
{
	if (matches.size() <= 0) {
		//INFO("ComputeHomography::FindInlierMatch*** matches is empty\n");
		return;
	}
	vector<cv::Point2f> pts1, pts2;
	for (int i = 0; i < matches.size(); i++)
	{
		pts1.push_back(trainkp[matches[i].trainIdx].pt);
		pts2.push_back(querykp[matches[i].queryIdx].pt);
	}
	vector<uchar> inliers;
	cv::Mat H = cv::findHomography(pts1, pts2, cv::RHO, 10, inliers);
	for (int i = 0; i < inliers.size(); i++)
	{
		if (inliers[i])
		{
			inlier_match.push_back(matches[i]);
		}
	}
	if (inlier_match.size() < 30) return;
	vector<cv::Point2f> pts1_inlier, pts2_inlier;
	for (int i = 0; i < inlier_match.size(); i++)
	{
		pts1_inlier.push_back(trainkp[inlier_match[i].trainIdx].pt);
		pts2_inlier.push_back(querykp[inlier_match[i].queryIdx].pt);
	}
	vector<uchar> in_inliers;
	cv::Mat in_H = cv::findHomography(pts1_inlier, pts2_inlier, cv::RHO, 3, in_inliers);
	for (int i = 0; i < in_inliers.size(); i++)
	{
		if (in_inliers[i])
		{
			in_inlier_match.push_back(inlier_match[i]);
		}
	}
	return;
}



int main() {
	cv::Ptr<SuperPoint> sp = SuperPoint::create();

	vector<cv::KeyPoint> points1, points2;
	cv::Mat desc1, desc2;
	cv::Mat image1 = cv::imread("D:/learning/keypoints_and_descriptor/superpoint/super_matching/data/candidates/01.png");
	cv::Mat image2 = cv::imread("D:/learning/keypoints_and_descriptor/superpoint/super_matching/data/candidates/02.png");
	cv::TickMeter tm;
	for (int i = 0; i < 1; i++) {
		tm.start();
		sp->detectAndCompute(image1, cv::Mat(), points1, desc1);
		tm.stop();

	}
	cout << "Average time per iteration in seconds: " << tm.getAvgTimeSec() << endl;
	cout << "Average FPS: " << tm.getFPS() << endl;
	sp->detectAndCompute(image2, cv::Mat(), points2, desc2);
	cv::Mat image1_gray;
	cv::Mat image2_gray;
	cv::cvtColor(image1, image1_gray, cv::COLOR_RGB2GRAY);
	cv::cvtColor(image2, image2_gray, cv::COLOR_RGB2GRAY);

	cv::Mat show_image1, show_image2;
	cv::drawKeypoints(image1, points1, show_image1, cv::Scalar(255, 125, 0));
	cv::drawKeypoints(image2, points2, show_image2, cv::Scalar(255, 125, 0));

	cv::namedWindow("img1", 1);
	cv::imshow("img1", show_image1);
	cv::namedWindow("img2", 1);
	cv::imshow("img2", show_image2);

	cv::Ptr<cv::BFMatcher> matcher = cv::makePtr<cv::BFMatcher>(cv::NORM_L2, true);
	vector<cv::DMatch> matchs, inlier_match, in_inlier_match;
	matcher->clear();
	matcher->add(desc1);
	matcher->train();
	matcher->match(desc2, matchs);
	cv::Mat image_match, inlier_image_match;
	cv::drawMatches(show_image2, points2, show_image1, points1, matchs, image_match, cv::Scalar(125, 125, 0));
	cv::namedWindow("match", 1);
	cv::imshow("match", image_match);
	FindInlierMatch(matchs, points1, points2, inlier_match, in_inlier_match);
	cv::drawMatches(show_image2, points2, show_image1, points1, inlier_match, inlier_image_match, cv::Scalar(125, 125, 0));
	cv::namedWindow("inlier match", 1);
	cv::imshow("inlier match", inlier_image_match);
	cv::waitKey(0);

	return 0;

}