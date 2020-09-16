#include <opencv2/opencv.hpp>
#include <iostream>
#include <conio.h>
#include <direct.h>
#include <io.h>

using namespace std;

bool getAllFiles(string path, vector<string>& files, string file_type)
{
	// 文件句柄
	intptr_t handle_file = 0;
	// 文件信息
	struct _finddata_t file_info;
	string p;
	int getch;
	if ((handle_file = _findfirst(p.assign(path).append("/*." + file_type).c_str(), &file_info)) != -1) {
		do {
			// 保存文件的全路径
			files.push_back(p.assign(path).append("/").append(file_info.name));

		} while (_findnext(handle_file, &file_info) == 0);  //寻找下一个，成功返回0，否则-1

		_findclose(handle_file);
		std::cout << std::endl
			<< "图片获取成功，共获取到"
			<< file_type
			<< "格式，图片共"
			<< files.size()
			<< "张"
			<< std::endl;
		return true;
	}
	else
	{
		std::cout << std::endl << "图片获取失败" << std::endl;
		std::cout << "输入回车退出..." << std::endl;
		getch = _getch();
		return false;
	}
}

int main()
{
	string source_path, target_path, file_type;
	source_path = "F:/DIC图片/0908-2-6/105ND750";
	file_type = "JPG";
	vector<string> file_name, file_name2;
	//获取文件名
	if (!getAllFiles(source_path, file_name, file_type))
	{
		return 0;
	}

	//创建文件夹
	target_path = source_path;
	target_path.append("/changImageType");
	if (0 != _access(target_path.c_str(), 0))
	{	// if this folder not exist, create a new one.
		int a=_mkdir(target_path.c_str());   // 返回 0 表示创建成功，-1 表示失败(头文件<direct.h>)
		cout << "文件夹创建成功" << endl;
	}

	for (int i = 0; i < file_name.size(); ++i)
	{
		//读取图片
		cv::Mat img = cv::imread(file_name[i], cv::IMREAD_UNCHANGED);
		cv::Rect roi(2300,600,1600,3100);
		img = img(roi);

		//获取保存路径
		string temp = file_name[i];
		temp.erase(0, source_path.size() + 1);
		temp.erase(temp.end()-3,temp.end());
		file_name2.push_back(source_path);
		file_name2[i].append("/changImageType/").append(temp);
			
		//保存指定格式图片
		//vector<int> compression_params;
		//compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);  //选择jpeg
		//compression_params.push_back(100); //在这个填入你要的图片质量
		cv::imwrite(file_name2[i].append("bmp"), img);
		std::cout << "第" << i + 1 << "张图片存储完成" << std::endl;
	}
	
	return 0;
}
