//2019.10.18
//@glCnZuDe
//人脸识别(Seate V2)dll导出类
//dll跟其使用者共用的头文件

/*
CreateExportObj @ 1
DestroyExportObj @ 2

SPGetSDKVersion @ 3
SPInitial @ 4
SPRelease @ 5
SPDetectFaceKeyPoints @ 6
SPSetMinFace @ 7
SPGetFaceQuality @ 8
SPGetFeatureSize @ 9
SPExtractFeature @ 10
SPExtractFeature_N @ 11
SPCompareFeature @ 12

RegisterDll @ 13
UnRegisterDll @ 14
FreMalloc @ 15
FreFree @ 16

SingleFaceDetect @ 17

FreCreateFaceTemplateList @ 18
FreClearFaceTemplateList @ 19
FreDeleteFaceTemplateList @ 20
FreInsertFaceTemplateList @ 21
FreRemoveFaceTemplateList @ 22

FreCreateFreImageList @ 23
FreClearFreImageList @ 24
FreDeleteFreImageList @ 25
FreInsertFreImageList @ 26
FreRemoveFreImageList @ 27
FreCreateFacePosList @ 28
FreClearFacePosList @ 29
FreDeleteFacePosList @ 30
FreInsertFacePosList @ 31
FreRemoveFacePosList @ 32

FaceTemplate @ 33
DeleteTemplate @ 34

FreCreateFaceRecogList @ 35
FreInsertFaceRecogList @ 36
FreClearFaceRecogList @ 37
FreDeleteFaceRecogList @ 38

DeleteSimlarInfo @ 39
DeleteString @ 40
ZoomImage @ 41

FaceTemplateCvt @ 42
SinFaceTemplate @ 43
FaceMatch @ 44
*/

#pragma  once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MATUREAPPROACH_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SPFACEREC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


#ifdef SPFACEREC_EXPORTS
#define SPFACEREC_API __declspec(dllexport)
#else
#define SPFACEREC_API __declspec(dllimport)
#endif

#include <string>
#include <list>
#include <map>

#include "CommonDef.h"

class IExport 
{
public:
	virtual void Hi() = 0;
	virtual void Test() = 0; 
	virtual void Release() = 0;

};


extern "C" SPFACEREC_API IExport* _stdcall CreateExportObj();
extern "C" SPFACEREC_API void _stdcall DestroyExportObj(IExport* pExport);

// start---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

//返回版本号
//strVer[input] 16字节空间.输出填充版本号.
extern "C" SPFACEREC_API long _stdcall SPGetSDKVersion(char *strVer);

//初始化一个HANDLE . 多线程情况下各个线程初始化各自的Handle,
//pHandle [output]输出指向初始化好的Handle
//strName [input]存放SPDataV32.bin的路径。以及对GPU 显卡的选择。在哪个GPU卡上运行。
//               先后放两个字符串。两字符串中间是第一个串的结束符'\0'隔开(即字节值为0)。整个结束为'\0\0'连续两个'\0'
//               第一个字符串是路径，第二个字符串是GPU编号（ASCII码 '0'到'9'最大为'9')
//               例子: "D:\\Exam\00\0\0"路径为"D:\\Exam",用GPU 0
//                     "D:\\Exam\01\0\0"路径为"D:\\Exam",用GPU 1
//                     "D:\\Exam\0\0"路径为"D:\\Exam",默认用GPU 0
//               如果没有第二个字符串，第一个串结束后两个'\0',则核心采用默认GPU 0
//
//               该串生成方法例子:
//               char strInput[256] = {0};//目标参数串。
//               char strPath = "D:\\Exam";
//               char *pch;
//               strcpy( strInput, strPath);
//               pch = &strInput[ strlen(strInput)]; //pch-> 指向第一个字符串的结尾'\0'标记。
//               pch[1] = 0x30;                      //紧接着，ASCII码 0x30 表示GPU 0号，  0x31表示 GPU 1号,以此类推。
//               pch[2] = pch[3] = 0;                //整个串结尾 两个'\0'标记。
//               这样就指定了显卡了。
//               如果pch[1] = 0; 就在第一个串后面多加一个'\0'，程序默认用GPU 0号.
//linux上测试如果一个进程生成两个Handle占两个卡可能会CUDA报错。
//可以两个进程,各在一个卡上运行。
//return: S_OK, S_FAIL
extern "C" SPFACEREC_API long _stdcall SPInitial(SP_HANDLE *pHandle, char *strName);

//释放Handle
//pHandle [input]指向SPInitial初始化好的Handle
extern "C" SPFACEREC_API long _stdcall SPRelease(SP_HANDLE *pHandle);

//return: S_OK, S_FAIL
extern "C" SPFACEREC_API long _stdcall SPDetectFaceKeyPoints(
	SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo);

//设置待检测的最小人脸大小。
//return: S_OK, S_FAIL
extern "C" SPFACEREC_API long _stdcall SPSetMinFace(
	SP_HANDLE Handle, 
	int iMinFace);	

/**************************************************
	质量判断
***************************************************/
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入图片灰度信息。数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素的灰度值
//nImgWidth, nImgHeight[input] 图片的宽度高度
//pFaceInfo   [input] 一个人脸信息
//pQualityScore	[output]输出质量特征串
//	int nIlluminationScore; //人脸光照适宜度打分。0~100 . 建议亮度小于80时只抓拍不识别
//	int nSharpnessScore;    //人脸清晰程度打分.   0~100 . 建议清晰度小于30时只抓拍不识别
//	float fRoll;            //左右歪头角度
//	float fYaw;             //左右侧脸角度。建议小于-20度和大于20度时只抓拍不识别
//	float fPitch;           //俯仰角度。建议小于-25度和大于40度时只抓拍不识别
//	int nSunGlassesScore;	//戴墨镜打分，功能还没完成
//	int nMaskScore;			//戴口罩得分，功能还没完成
//  int nAlignmentScore;	//关键点对齐得分。建议小于60时只抓拍不识别
//return : S_OK. other failed
extern "C" SPFACEREC_API long _stdcall SPGetFaceQuality(
	SP_HANDLE Handle,
	const unsigned char* pImg, 
	int nImgWidth, 
	int nImgHeight,
	SPFaceInfo *pFaceInfo, 
	SPQualityScore *pScore);

/**************************************************
    特征和比对
*************************************************/
//Handle [input] SPInitial初始化好的Handle
//piFtrSize [output] 输出特征字节个数
//return: S_OK, S_FAIL
extern "C" SPFACEREC_API long _stdcall SPGetFeatureSize(
	SP_HANDLE Handle, 
	int *piFtrSize);


//return : S_OK. other failed
extern "C" SPFACEREC_API long _stdcall SPExtractFeature(
	SP_HANDLE Handle,
    const unsigned char* pImg, 
	int nImgWidth, 
	int nImgHeight,						  
	SPFaceInfo *pFaceInfo, 
	unsigned char *pOutFeature);

//提取特征。
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入图片灰度信息。数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素的灰度值
//nImgWidth, nImgHeight[input] 图片的宽度高度
//pFaceInfo   [input] 一个人脸信息
//pOutFeature [output]输出特征串。特征串长度见SPGetFeatureSize， 需要外部申请好。
//return : S_OK. other failed
extern "C" SPFACEREC_API long _stdcall SPExtractFeature_N(
	SP_HANDLE Handle,
	const unsigned char* pImg, 
	int nImgWidth,
	int nImgHeight,
	SPFaceInfo *pFaceInfo, 
	int nFaceNum,
	unsigned char *pOutFeature);

//用于单独比较两张图片的特征串相似性。
//Handle [input] SPInitial初始化好的Handle
//pFeaA  [input] 特征串
//pFeaB  [input] 特征串
//fScore [output] 相似性度量值，0~1.0 ，越大越相似。
//return : S_OK. other failed
extern "C" SPFACEREC_API long _stdcall SPCompareFeature(
	SP_HANDLE Handle,
	const unsigned char *pFeaA,
	const unsigned char *pFeaB,
    float *fScore);

// End---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

// Start---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

// 注册函数
extern "C" SPFACEREC_API bool _stdcall RegisterDll(const char* pDllPath);

// 反注册函数
extern "C" SPFACEREC_API void _stdcall UnRegisterDll();

//////////////////////////////////////////////////////////////////////////
// 创建接口 2019-10-18

// ----------------------内存分配接口------------------------------
// 内存空间分配函数
extern "C" SPFACEREC_API unsigned char* _stdcall FreMalloc(SP_HANDLE pHandle, unsigned int nSize);

// 内存空间释放函数
extern "C" SPFACEREC_API void _stdcall FreFree(SP_HANDLE pHandle, unsigned char *pBuffer);

// --------------------------人脸检测接口----------------------------
// 对指定的单张图像数据进行人脸检测，检测结果输出到人脸数据容器中。
extern "C" SPFACEREC_API bool _stdcall SingleFaceDetect(SP_HANDLE pHandle, FreImageList* plstFace, FreImageList* pZoomPicList, FacePosList* plstFacePos, FreImage SrcPicture, int *piFaceCount, int f_Zoom = 1, int b_Zoom = 1);

// -----------人脸模板数据、图像数据和坐标数据容器创建和释放的接口-------
// FaceTemplateList相关处理函数
// 创建人脸模板数据容器
extern "C" SPFACEREC_API FaceTemplateList* _stdcall FreCreateFaceTemplateList(SP_HANDLE pHandle);

// 清空人脸模板数据容器中的所有数据
extern "C" SPFACEREC_API void _stdcall FreClearFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList);

// 清空人脸模板数据容器中的所有数据,并删除释放人脸模板数据容器
extern "C" SPFACEREC_API void _stdcall FreDeleteFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList);

// 向容器插入一个人脸模板数据节点
extern "C" SPFACEREC_API void _stdcall FreInsertFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, SFaceTemplate *pFaceTempNode);

// 从容器中删除指定名称的人脸模板数据节点
extern "C" SPFACEREC_API void _stdcall FreRemoveFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, char *pFaceTempName);

// FreImageList相关处理函数
// 创建图像数据容器
extern "C" SPFACEREC_API FreImageList* _stdcall FreCreateFreImageList(SP_HANDLE pHandle);

// 清空图像数据容器中的所有数据
extern "C" SPFACEREC_API void _stdcall FreClearFreImageList(SP_HANDLE pHandle, FreImageList* pList);

// 清空图像数据容器中的所有数据,并删除释放图像数据容器
extern "C" SPFACEREC_API void _stdcall FreDeleteFreImageList(SP_HANDLE pHandle, FreImageList* pList);

// 向容器插入一个图像数据节点
extern "C" SPFACEREC_API void _stdcall FreInsertFreImageList(SP_HANDLE pHandle, FreImageList *pList, FreImage *pNode);

// 从容器中删除指定名称的图像数据节点
extern "C" SPFACEREC_API void _stdcall FreRemoveFreImageList(SP_HANDLE pHandle, FreImageList *pList, char *pName);

// FacePosList相关处理函数
// 创建人脸坐标信息容器
extern "C" SPFACEREC_API FacePosList* _stdcall FreCreateFacePosList (SP_HANDLE pHandle);

// 清空人脸坐标信息容器中的所有数据
extern "C" SPFACEREC_API void _stdcall FreClearFacePosList(SP_HANDLE pHandle, FacePosList* pList);

// 清空人脸坐标信息中的所有数据,并删除释放人脸坐标信息容器
extern "C" SPFACEREC_API void _stdcall FreDeleteFacePosList(SP_HANDLE pHandle, FacePosList* pList);

// 向容器插入一个人脸坐标信息节点
extern "C" SPFACEREC_API void _stdcall FreInsertFacePosList(SP_HANDLE pHandle, FacePosList *pList, FacePos *pNode);

// 从容器中删除指定名称的人脸坐标信息节点
extern "C" SPFACEREC_API void _stdcall FreRemoveFacePosList(SP_HANDLE pHandle, FacePosList *pList, char *pName);

// -------------------------人脸模板管理接口-------------------------
// 针对单个图片文件检测创建人脸模板，模板数据保存到内存容器
extern "C" SPFACEREC_API bool _stdcall FaceTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, FreImageList* plstFtFace, FreImage SrcPicture, int *pTemplateCount, int f_Zoom = 1, int b_Zoom = 1);

// 从人脸模板内存容器中删除指定名称的模板数据
extern "C" SPFACEREC_API bool _stdcall DeleteTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, char *pTemplateName);

// ----------------------------人脸识别分组接口----------------------
// 创建人脸识别分组结果输出容器
extern "C" SPFACEREC_API FaceRecogList* _stdcall FreCreateFaceRecogList(SP_HANDLE pHandle);

// 向容器中插入一条识别结果记录
extern "C" SPFACEREC_API void _stdcall FreInsertFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList, FaceRecogNode *pNode);

// 清空容器中的所有数据，但是不删除容器
extern "C" SPFACEREC_API void _stdcall FreClearFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList);

// 清空容器中的所有数据，并删除容器
extern "C" SPFACEREC_API void _stdcall FreDeleteFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList);

// 删除相似度信息容器
extern "C" SPFACEREC_API void _stdcall DeleteSimlarInfo(SP_HANDLE pHandle, SimlarInfo *pSimlarInfo);

// 分组信息string字符串删除函数
extern "C" SPFACEREC_API void _stdcall DeleteString(SP_HANDLE pHandle, std::string *pStr);

// 图像缩放函数接口
extern "C" SPFACEREC_API bool _stdcall ZoomImage(SP_HANDLE pHandle, FreImage *pSrcImg, int iZoomSize, FreImage *pZoomImg);

// 模板转换
extern "C" SPFACEREC_API bool _stdcall FaceTemplateCvt(SP_HANDLE pHandle, SFaceTemplate *ft);

// 对单个人脸图片创建内存模版数据接口
extern "C" SPFACEREC_API bool _stdcall SinFaceTemplate(SP_HANDLE pHandle, SFaceTemplate* pSinFt, const FreImage *FacePicture, int f_Zoom = 1);

// 计算两个模版相似度接口
extern "C" SPFACEREC_API float _stdcall FaceMatch(SP_HANDLE pHandle, const SFaceTemplate *ft1, const SFaceTemplate *ft2);

// End---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////
