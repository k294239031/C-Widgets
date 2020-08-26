/***
#include <vector>
#include <string>
#include <fstream>


*@brief 遍历所有文件夹
*@param path 路径
*@param [out] folder 存储向量
*@retval
*@note by zenghai@orbbec.com
*/
void GetFolder(string path, vector<string>& folder)
{
	intptr_t handle_file = 0;
	struct _finddata_t file_info;
	string p;
	if ((handle_file = _findfirst(p.assign(path).append("\\*").c_str(), &file_info)) != -1)
	{
		do
		{
			//如果是目录，存入列表
			if ((file_info.attrib & _A_SUBDIR))
			{

				if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0)
					folder.push_back(p.assign(path).append("/").append(file_info.name));
			}
			else
			{
				continue;

			}
		} while (_findnext(handle_file, &file_info) == 0);
	}
	_findclose(handle_file);
}
/***
*@brief 遍历所有文件
*@param path 路径
*@param [out] files 存储向量
*@param file_type 文件格式 
*@retval
*@note by zenghai@orbbec.com
*/
void GetAllFiles(string path, vector<string>& files, string file_type)
{
	// 文件句柄
	intptr_t handle_file = 0;
	// 文件信息
	struct _finddata_t file_info;
	string p;
	if ((handle_file = _findfirst(p.assign(path).append("/*" + file_type).c_str(), &file_info)) != -1) {
		do {
			// 保存文件的全路径
			files.push_back(p.assign(path).append("/").append(file_info.name));

		} while (_findnext(handle_file, &file_info) == 0);  //寻找下一个，成功返回0，否则-1

		_findclose(handle_file);
	}
}

int main(int argc, char ** argv)
{
if (4 > argc)
	{
		fprintf(stderr, "version:%s\n", ToFDepthVersion());
		fprintf(stderr, "usage: folder_path param.bin log.ini [hign nshfl] [hign shfl] [low nshfl] [low shfl]");
		return -1;
	}
	
char * path = argv[1];

///遍历子文件夹
		vector<string> folder;
		GetFolder(path, folder);
		for (int i = 0; i < folder.size(); i++)
		{
			///遍历文件名
			fprintf(stdout, "\nfolder path:%s\n", folder[i].c_str());
			fprintf(log, "\nfolder path:%s\n", folder[i].c_str());
			vector<string> file_name;
			GetAllFiles(folder[i], file_name, ".png");
			}
			
			}
