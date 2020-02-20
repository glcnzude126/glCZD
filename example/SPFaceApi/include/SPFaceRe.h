/***************************************************************
**
**  
**  filename: Facere.h
**
**  description:  人脸识别库导出函数接口
**
**************************************************************/

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 FACERE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// FACERE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef _FACERE_H_
#define _FACERE_H_

#include <string>
#include <list>
#include <map>
#ifdef FACERE_EXPORTS
#define FACERE_API __declspec(dllexport)
#else
#define FACERE_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
// 接口更新 2012-07-28

//图像名称、人脸模板文件名称的最大长度
#define MAX_NAME_LEN 260

#pragma pack(push, 1)

// 输入图像数据，输出人脸图像数据存储结构
typedef struct _FreImage
{
    int  nSize;               // FreImage 结构大小，即sizeof(FreImage)
    int  width;               // 图像像素宽 
    int  height;              // 图像像素高
    int  imageSize;           // 图像数据大小
    unsigned char *imageData; //imageData数据的字节大小unsigned char *imageData;  图像数据指针，数据格式为jpeg格式。此数据内存空间通过调用FreMalloc函数类分配，调用FreFree函数进行释放。
    char imageName[MAX_NAME_LEN]; // 图像名称，图像名称字节个数最大不能超过(MAX_NAME_LEN-1）个。
}FreImage;

//   人脸模板数据存储结构
typedef struct _FaceTemplate
{
    int  nSize;          		    // FaceTemplate结构大小，即sizeof(FaceTemplate)
    unsigned char *FtData;       	// 模板数据指针，此的数据内存空间通过调用FreMalloc函数类分配，调用FreFree函数进行释放
    int  FtSize;        			// 模板数据大小,即FtData数据大小
    char FtName[MAX_NAME_LEN];      // 人脸模板名称，人脸模板名称字节个数最大不能超过（MAX_NAME_LEN-1）个
	double simlar;
}SFaceTemplate;

// 用于存储人脸在在对应图像中的坐标信息
typedef struct _FacePos
{
    int  center_x;          // 人脸图片中心在对应图像中的x坐标
    int  center_y;          // 人脸图片中心在对应图像中的y坐标
    int  width;             // 人脸图片像素宽
    int  height;            // 人脸图片像素高
    char faceName[MAX_NAME_LEN]; // 图像中的人脸名称，图像中的人脸名称字节个数最大不能超过（MAX_NAME_LEN-1）个。
}FacePos;

// 每个人脸模板文件能存放的最大模板个数
#define MAX_FACETEMP_COUNT 50000

#define FACETEMPLATE_FILE_KEY 0x45544146

// 用于保存人脸模板数据头信息
typedef struct _FaceTempNode
{
    unsigned char bDelete;  // 标识此节点是否可用，即此人脸模板数据是否已删除
    char FtName[MAX_NAME_LEN];// 人脸模板名称
    unsigned int size;		// 人脸模板数据大小
    //unsigned char data[];	// 人脸模板数据
}FaceTempNode;

// 人脸模板文件头结构
typedef struct _FaceTemplateFileHead
{
    DWORD dwKey;        // 人脸模板文件标致
    DWORD dwCurNum;     // 文件中有效模板个数
    DWORD dwTotalNum;   // 文件中总的模板个数
}FaceTemplateFileHead, *PFaceTemplateFileHead;

// 图像名称结构
typedef struct _SImgName
{
    char szImgName[MAX_NAME_LEN];
}SImgName, *PSImgName;

inline bool operator<(const SImgName & name1, const SImgName &name2)
{
    return (0 > strcmp(name1.szImgName, name2.szImgName));
}
typedef struct _SimlarNode
{
    char szImgName[MAX_NAME_LEN];
    float fSimlar;
}SimlarNode, *PSimlarNode;

// FaceID接口识别结果的存放容器相关结构
typedef struct _UnFaceLibResult
{
    char szFaceName[MAX_NAME_LEN];
    BYTE *pFaceData;
    int nFaceSize;
}UnFaceLibResult;

typedef struct _FaceLibResult
{
    char szFaceName[MAX_NAME_LEN];  // 原始人脸名称，便于文件查找，不包括扩展名.jpg
    UINT nGroupId;                  // 分组id
    int iSortId;                    // 针对单张图片进行人脸识别时，此人脸数据的相似度排序序号，排序号起始为1
}FaceLibResult;

typedef struct _FaceRecogNode
{
    BOOL bInFaceLib;    // 人脸数据是否属于已知的模板库对应的人脸文件
    union 
    {
        FaceLibResult sFaceInLib;   // 属于已知人脸库中的人脸，存放“原始人脸名称”和所属的分组号id
        UnFaceLibResult sFaceOutLib;// 属于待识别的图片中检测出来的人脸，存放“分组后的人脸名称”(分组号_原始人脸名称)、人脸数据、人脸数据大小
    }u;
}FaceRecogNode;

#pragma pack(pop)

// 人脸模板数据容器
typedef std::list<SFaceTemplate> FaceTemplateList;

// 图像数据容器
typedef std::list<FreImage> FreImageList;

// 人脸坐标数据容器
typedef std::list<FacePos> FacePosList;

// 人脸相似度顺序链表，相似度从大到小排列
typedef std::list<SimlarNode> SimlarSortList;

// 存放所有待识别图像识别后的相似度数据信息容器
typedef std::map<SImgName, SimlarSortList*> SimlarInfo;

// FaceID存放识别结果的容器
typedef std::list<FaceRecogNode> FaceRecogList;

#ifdef __cplusplus
extern "C" {
#endif

FACERE_API BOOL RegisterDll(const char* pDllPath);

FACERE_API void UnRegisterDll();

//////////////////////////////////////////////////////////////////////////
// 改进接口 2012-07-28

// ----------------------内存分配接口------------------------------
// 内存空间分配函数
FACERE_API unsigned char* FreMalloc(unsigned int nSize);

// 内存空间释放函数
FACERE_API void FreFree(unsigned char *pBuffer);


// --------------------------人脸检测接口----------------------------
// 对指定的单张图像数据进行人脸检测，检测结果输出到人脸数据容器中。
FACERE_API BOOL SingleFaceDetect(FreImageList* plstFace, FreImageList* pZoomPicList, FacePosList* plstFacePos, FreImage SrcPicture, int *piFaceCount, int f_Zoom = 1, int b_Zoom = 1);

// -----------人脸模板数据、图像数据和坐标数据容器创建和释放的接口-------
// FaceTemplateList相关处理函数
// 创建人脸模板数据容器
FACERE_API FaceTemplateList * FreCreateFaceTemplateList();

// 清空人脸模板数据容器中的所有数据
FACERE_API void FreClearFaceTemplateList(FaceTemplateList * pList);

// 清空人脸模板数据容器中的所有数据,并删除释放人脸模板数据容器
FACERE_API void FreDeleteFaceTemplateList(FaceTemplateList * pList);

// 向容器插入一个人脸模板数据节点
FACERE_API void FreInsertFaceTemplateList(FaceTemplateList *pList, SFaceTemplate *pFaceTempNode);

// 从容器中删除指定名称的人脸模板数据节点
FACERE_API void FreRemoveFaceTemplateList(FaceTemplateList *pList, char *pFaceTempName);


// FreImageList相关处理函数
// 创建图像数据容器
FACERE_API FreImageList* FreCreateFreImageList();

// 清空图像数据容器中的所有数据
FACERE_API void FreClearFreImageList(FreImageList* pList);

// 清空图像数据容器中的所有数据,并删除释放图像数据容器
FACERE_API void FreDeleteFreImageList (FreImageList* pList);

// 向容器插入一个图像数据节点
FACERE_API void FreInsertFreImageList(FreImageList *pList, FreImage *pNode);

// 从容器中删除指定名称的图像数据节点
FACERE_API void FreRemoveFreImageList(FreImageList *pList, char *pName);


// FacePosList相关处理函数
// 创建人脸坐标信息容器
FACERE_API FacePosList* FreCreateFacePosList ();

// 清空人脸坐标信息容器中的所有数据
FACERE_API void FreClearFacePosList(FacePosList* pList);

// 清空人脸坐标信息中的所有数据,并删除释放人脸坐标信息容器
FACERE_API void FreDeleteFacePosList(FacePosList* pList);

// 向容器插入一个人脸坐标信息节点
FACERE_API void FreInsertFacePosList(FacePosList *pList, FacePos *pNode);

// 从容器中删除指定名称的人脸坐标信息节点
FACERE_API void FreRemoveFacePosList(FacePosList *pList, char *pName);


// -------------------------人脸模板管理接口-------------------------
// 针对单个图片文件检测创建人脸模板，模板数据保存到内存容器
FACERE_API BOOL FaceTemplate(FaceTemplateList* plstFt, FreImageList* plstFtFace, FreImage SrcPicture, int *pTemplateCount, int f_Zoom = 1, int b_Zoom = 1);

// 从人脸模板内存容器中删除指定名称的模板数据
FACERE_API BOOL DeleteTemplate(FaceTemplateList* plstFt, char *pTemplateName);

// ----------------------------人脸识别分组接口----------------------
// 创建人脸识别分组结果输出容器
FACERE_API FaceRecogList *FreCreateFaceRecogList();

// 向容器中插入一条识别结果记录
FACERE_API void FreInsertFaceRecogList(FaceRecogList *pList, FaceRecogNode *pNode);

// 清空容器中的所有数据，但是不删除容器
FACERE_API void FreClearFaceRecogList(FaceRecogList *pList);

// 清空容器中的所有数据，并删除容器
FACERE_API void FreDeleteFaceRecogList(FaceRecogList *pList);

// 删除相似度信息容器
FACERE_API void DeleteSimlarInfo(SimlarInfo *pSimlarInfo);

// 分组信息string字符串删除函数
FACERE_API void DeleteString(std::string *pStr);

// 图像缩放函数接口
FACERE_API BOOL ZoomImage(FreImage *pSrcImg, int iZoomSize, FreImage *pZoomImg);

// 模板转换
FACERE_API BOOL FaceTemplateCvt(SFaceTemplate *ft);

// 对单个人脸图片创建内存模版数据接口
FACERE_API BOOL SinFaceTemplate(SFaceTemplate* pSinFt, const FreImage *FacePicture, int f_Zoom = 1);

// 计算两个模版相似度接口
FACERE_API float FaceMatch(const SFaceTemplate *ft1, const SFaceTemplate *ft2);
#ifdef __cplusplus
}
#endif


#endif