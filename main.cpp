#include"StereoRectify.h"
#include<string.h>
#include "opencv2/cudaarithm.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;
//usage ./ImageRectify input_video1 input_video2 output_video1 output_video2 inv_flag
//need "./intrinsics.yml","./extrinsics.yml"
int main(int argc, char** argv)
{
    char* file = argv[1];
    char* file2 = argv[2];
    cv::VideoWriter video(argv[3], cv::VideoWriter::fourcc('D','I','V','X'), 5, Size(4112, 3008));
    cv::VideoWriter video2(argv[4], cv::VideoWriter::fourcc('D','I','V','X'), 5, Size(4112, 3008));
    StereoRectify img_rectify;
    cv::cuda::GpuMat src1;
    cv::cuda::GpuMat dst1;
    cv::cuda::GpuMat src2;
    cv::cuda::GpuMat dst2;
    VideoCapture cap;
	VideoCapture cap2;
	cap.open(file);
	cap2.open(file2);
	if (!cap.isOpened() || !cap2.isOpened())
	{
		cerr << "can not open camera or video file" << endl;
		return -1;
	}
    Mat img_m;
    Mat img_s;
    Mat img_m_;
    Mat img_s_;
    int count = 0;
    for(;;)
    {
        cap>>img_m;
        cap2>>img_s;
        if(img_m.empty())
            break;
        if(count == 0)
        {
            img_rectify.init("./intrinsics.yml","./extrinsics.yml",img_m.size());
        }
        if(atoi(argv[5]) == 1)
        {
            src1.upload(img_s);
            src2.upload(img_m);
        }
        else
        {
            src1.upload(img_m);
            src2.upload(img_s);
        }
        img_rectify.rectify(src1,dst1,src2,dst2);
        
        dst1.download(img_m_);
        dst2.download(img_s_);

        if(atoi(argv[5]) == 1)
        {
            video << img_m_;
            video2 << img_s_;
        }
        else
        {
            video << img_m_;
            video2 << img_s_;
        }
        std::cout<<"finish frame"<<count<<std::endl;
        count = count + 1;
    }
    // std::vector<cv::String> fn;
    
    // cv::glob("./imgs/",fn);
    // char buffer[50];
    // char buffer1[200];
    // char buffer2[200];
    // cv::cuda::GpuMat src1;
    // cv::cuda::GpuMat dst1;
    // cv::cuda::GpuMat src2;
    // cv::cuda::GpuMat dst2;
    // Mat img_m_;
    // Mat img_s_;
    // Mat img_m;
    // Mat img_s;
    // for(size_t i = 0; i < fn.size(); i++)
    // {
    //     sprintf(buffer,"%05d.jpg",(int)i);
    //     sprintf(buffer1,"%s%s",argv[1],buffer);
    //     sprintf(buffer2,"%s%s",argv[2],buffer);
    //     cout<<buffer1<<endl;
    //     cout<<buffer2<<endl;
    //     img_m = imread(buffer1);
    //     img_s = imread(buffer2);
    //     if(i == 0)
    //         img_rectify.init("./intrinsics.yml","./extrinsics.yml",img_m.size());
    //     memset(buffer,0,sizeof(buffer));
    //     memset(buffer1,0,sizeof(buffer1));
    //     memset(buffer2,0,sizeof(buffer2));
    //     if(atoi(argv[3]) == 1)
    //     {
    //         src1.upload(img_s);
    //         src2.upload(img_m);
    //     }
    //     else
    //     {
    //         src1.upload(img_m);
    //         src2.upload(img_s);
    //     }
    //     img_rectify.rectify(src1,dst1,src2,dst2);
        
    //     dst1.download(img_m_);
    //     dst2.download(img_s_);
    //     sprintf(buffer1,"./res/m%d.png",(int)i);
    //     sprintf(buffer2,"./res/s%d.png",(int)i);
    //     if(atoi(argv[3]) == 1)
    //     {
    //         cv::imwrite(buffer1,img_s_);
    //         cv::imwrite(buffer2,img_m_);
    //     }
    //     else
    //     {
    //         cv::imwrite(buffer1,img_m_);
    //         cv::imwrite(buffer2,img_s_);
    //     }

    //     memset(buffer1,0,sizeof(buffer1));
    //     memset(buffer2,0,sizeof(buffer2)); 
    //     std::cout<<"finished "<<i<<std::endl;

    // }
    return 0;
    
    


}