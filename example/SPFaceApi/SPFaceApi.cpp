// MatureApproach.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SPFaceApi.h"
#include "SPFaceClassImpl.h"

#pragma warning(disable: 4819)

#include "FaceDetector.h"
#include "FaceRecognizer.h"

//#include "Struct_cv.h"
#include "Struct.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <array>
#include <map>
#include <iostream>

#ifdef _MANAGED
#pragma managed(push, off)
#endif

bool APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

SPFACEREC_API IExport* APIENTRY CreateExportObj()
{
	return new ExportImpl;
}

//这里不能直接delete pExport，因为没有把IExport的析构函数定义为虚函数
SPFACEREC_API void  APIENTRY DestroyExportObj(IExport* pExport)
{
	pExport->Release();
}

// Start---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

//返回版本号
//strVer[input] 16字节空间.输出填充版本号.
SPFACEREC_API long APIENTRY SPGetSDKVersion(char *strVer)
{
	return 0L;
}

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
SPFACEREC_API long APIENTRY SPInitial(SP_HANDLE *pHandle, char *strName)
{
	return 0L;
}

//释放Handle
//pHandle [input]指向SPInitial初始化好的Handle
SPFACEREC_API long APIENTRY SPRelease(SP_HANDLE *pHandle)
{
	return 0L;
}

/**************************************************
人脸定位
*************************************************/

//人脸定位
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入灰度图像，数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素
//pImgRGB[input] 输入彩色图像，像素排列从左上到右下，逐行 每行从左到右逐点排列各像素.
//               每个像素依次存储R G B 三个分量。 注意有的图像格式排列是 B G R 的，需要调整字节顺序。
//               RGB 顺序不符将影响定位结果。
//               如果输入NULL,内部作灰度图处理 
//nImgWidth nImgHeight [input] 图片的宽度高度
//pnMaxFace [input] 输入 *pnMaxFace 需要定位最多人脸个数 
//          [output] *pnMaxFace 为实际定位的人脸个数
//pFaceInfo [output] 输出每个人脸定位信息。 需要外部申请*pnMaxFace个 SPFaceInfo空间。
//pFaceInfo.m_KeyPos.face.confi为得分信息，建议5分以下的人脸不进行抓拍
//return: S_OK, S_FAIL
SPFACEREC_API long APIENTRY SPDetectFaceKeyPoints(SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo)
{
	return 0L;
}

//设置待检测的最小人脸大小。
//return: S_OK, S_FAIL
SPFACEREC_API long APIENTRY SPSetMinFace(SP_HANDLE Handle, int iMinFace)
{
	return 0L;
}

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
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPGetFaceQuality(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, SPQualityScore *pScore)
{
	return 0L;
}

/**************************************************
特征和比对
*************************************************/
//Handle [input] SPInitial初始化好的Handle
//piFtrSize [output] 输出特征字节个数
//return: S_OK, S_FAIL
SPFACEREC_API long APIENTRY SPGetFeatureSize(SP_HANDLE Handle, int *piFtrSize)
{
	return 0L;
}

//提取特征。
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入图片灰度信息。数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素的灰度值
//nImgWidth, nImgHeight[input] 图片的宽度高度
//pFaceInfo   [input] 一个人脸信息
//pOutFeature [output]输出特征串。特征串长度见SPGetFeatureSize， 需要外部申请好。
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPExtractFeature(SP_HANDLE Handle,
                          const unsigned char* pImg, int nImgWidth, int nImgHeight,
						  SPFaceInfo *pFaceInfo, unsigned char *pOutFeature)
{
	return 0L;
}

//提取特征。
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入图片灰度信息。数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素的灰度值
//nImgWidth, nImgHeight[input] 图片的宽度高度
//pFaceInfo   [input] 几个人脸信息
//nFaceNum	 [input] 人脸数目
//pOutFeature [output] 几个人脸的输出特征串。顺序和pFaceInfo对应的人脸顺序一致。
//                     每个特征串长度见SPGetFeatureSize， 需要外部申请好。
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPExtractFeature_N(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, int nFaceNum,
	unsigned char *pOutFeature)
{
	return 0L;
}

//用于单独比较两张图片的特征串相似性。
//Handle [input] SPInitial初始化好的Handle
//pFeaA  [input] 特征串
//pFeaB  [input] 特征串
//fScore [output] 相似性度量值，0~1.0 ，越大越相似。
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPCompareFeature(SP_HANDLE Handle,
							const unsigned char *pFeaA,
							const unsigned char *pFeaB,
                            float *fScore)
{
	return 0L;
}

// End---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

// Start---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

// 注册函数
SPFACEREC_API bool APIENTRY RegisterDll(const char* pDllPath)
{
	return true;
}

// 反注册函数
SPFACEREC_API void APIENTRY UnRegisterDll()
{

}

//////////////////////////////////////////////////////////////////////////
// 改进接口 2020-02-18

// ----------------------内存分配接口------------------------------
// 内存空间分配函数
SPFACEREC_API unsigned char* APIENTRY FreMalloc(SP_HANDLE pHandle, unsigned int nSize)
{
	return NULL;
}

// 内存空间释放函数
SPFACEREC_API void APIENTRY FreFree(SP_HANDLE pHandle, unsigned char *pBuffer)
{

}

// --------------------------人脸检测接口----------------------------
// 对指定的单张图像数据进行人脸检测，检测结果输出到人脸数据容器中。
SPFACEREC_API bool APIENTRY SingleFaceDetect(SP_HANDLE pHandle, FreImageList* plstFace, FreImageList* pZoomPicList, FacePosList* plstFacePos, FreImage SrcPicture, int *piFaceCount, int f_Zoom/* = 1*/, int b_Zoom/* = 1*/)
{
	return true;
}

// -----------人脸模板数据、图像数据和坐标数据容器创建和释放的接口-------
// FaceTemplateList相关处理函数
// 创建人脸模板数据容器
SPFACEREC_API FaceTemplateList* APIENTRY FreCreateFaceTemplateList(SP_HANDLE pHandle)
{
	return NULL;
}

// 清空人脸模板数据容器中的所有数据
SPFACEREC_API void APIENTRY FreClearFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList)
{

}

// 清空人脸模板数据容器中的所有数据,并删除释放人脸模板数据容器
SPFACEREC_API void APIENTRY FreDeleteFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList)
{

}

// 向容器插入一个人脸模板数据节点
SPFACEREC_API void APIENTRY FreInsertFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, SFaceTemplate *pFaceTempNode)
{

}

// 从容器中删除指定名称的人脸模板数据节点
SPFACEREC_API void APIENTRY FreRemoveFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, char *pFaceTempName)
{

}

// FreImageList相关处理函数
// 创建图像数据容器
SPFACEREC_API FreImageList* APIENTRY FreCreateFreImageList(SP_HANDLE pHandle)
{
	return NULL;
}

// 清空图像数据容器中的所有数据
SPFACEREC_API void APIENTRY FreClearFreImageList(SP_HANDLE pHandle, FreImageList* pList)
{

}

// 清空图像数据容器中的所有数据,并删除释放图像数据容器
SPFACEREC_API void APIENTRY FreDeleteFreImageList (SP_HANDLE pHandle, FreImageList* pList)
{

}

// 向容器插入一个图像数据节点
SPFACEREC_API void APIENTRY FreInsertFreImageList(SP_HANDLE pHandle, FreImageList *pList, FreImage *pNode)
{

}

// 从容器中删除指定名称的图像数据节点
SPFACEREC_API void APIENTRY FreRemoveFreImageList(SP_HANDLE pHandle, FreImageList *pList, char *pName)
{

}

// FacePosList相关处理函数
// 创建人脸坐标信息容器
SPFACEREC_API FacePosList* APIENTRY FreCreateFacePosList (SP_HANDLE pHandle)
{
	return NULL;
}

// 清空人脸坐标信息容器中的所有数据
SPFACEREC_API void APIENTRY FreClearFacePosList(SP_HANDLE pHandle, FacePosList* pList)
{

}

// 清空人脸坐标信息中的所有数据,并删除释放人脸坐标信息容器
SPFACEREC_API void APIENTRY FreDeleteFacePosList(SP_HANDLE pHandle, FacePosList* pList)
{

}

// 向容器插入一个人脸坐标信息节点
SPFACEREC_API void APIENTRY FreInsertFacePosList(SP_HANDLE pHandle, FacePosList *pList, FacePos *pNode)
{

}

// 从容器中删除指定名称的人脸坐标信息节点
SPFACEREC_API void APIENTRY FreRemoveFacePosList(SP_HANDLE pHandle, FacePosList *pList, char *pName)
{

}

// -------------------------人脸模板管理接口-------------------------
// 针对单个图片文件检测创建人脸模板，模板数据保存到内存容器
SPFACEREC_API bool APIENTRY FaceTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, FreImageList* plstFtFace, FreImage SrcPicture, int *pTemplateCount, int f_Zoom/* = 1*/, int b_Zoom/* = 1*/)
{
	return true;
}

// 从人脸模板内存容器中删除指定名称的模板数据
SPFACEREC_API bool APIENTRY DeleteTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, char *pTemplateName)
{
	return true;
}

// ----------------------------人脸识别分组接口----------------------
// 创建人脸识别分组结果输出容器
SPFACEREC_API FaceRecogList* APIENTRY FreCreateFaceRecogList(SP_HANDLE pHandle)
{
	return NULL;
}

// 向容器中插入一条识别结果记录
SPFACEREC_API void APIENTRY FreInsertFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList, FaceRecogNode *pNode)
{

}

// 清空容器中的所有数据，但是不删除容器
SPFACEREC_API void APIENTRY FreClearFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList)
{

}

// 清空容器中的所有数据，并删除容器
SPFACEREC_API void APIENTRY FreDeleteFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList)
{

}

// 删除相似度信息容器
SPFACEREC_API void APIENTRY DeleteSimlarInfo(SP_HANDLE pHandle, SimlarInfo *pSimlarInfo)
{

}

// 分组信息string字符串删除函数
SPFACEREC_API void APIENTRY DeleteString(SP_HANDLE pHandle, std::string *pStr)
{

}

// 图像缩放函数接口
SPFACEREC_API bool APIENTRY ZoomImage(SP_HANDLE pHandle, FreImage *pSrcImg, int iZoomSize, FreImage *pZoomImg)
{
	return true;
}

// 模板转换
SPFACEREC_API bool APIENTRY FaceTemplateCvt(SP_HANDLE pHandle, SFaceTemplate *ft)
{
	return true;
}

// 对单个人脸图片创建内存模版数据接口
SPFACEREC_API bool APIENTRY SinFaceTemplate(SP_HANDLE pHandle, SFaceTemplate* pSinFt, const FreImage *FacePicture, int f_Zoom/* = 1*/)
{
	return true;
}

// 计算两个模版相似度接口
SPFACEREC_API float APIENTRY FaceMatch(SP_HANDLE pHandle, const SFaceTemplate *ft1, const SFaceTemplate *ft2)
{
	return 0.0f;
}

// End---SPAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////
