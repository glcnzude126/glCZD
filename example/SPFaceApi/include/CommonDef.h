#ifndef SPFACERECSDK_H
#define SPFACERECSDK_H

#ifndef __SP_HANDLE
#define __SP_HANDLE
typedef void*  SP_HANDLE;
#endif

#ifndef __SPRESULT
#define __SPRESULT
typedef long SPRESULT;
#endif

#define S_OK    0
#define S_FAIL  1
#define S_LOW_MEM 2

#ifndef  __RECT
#define  __RECT
typedef struct tagARect
{
	int top;
	int bottom;
	int left;
	int right;
}Rect;
#endif

#ifndef __POS
#define __POS
typedef struct  tagPos
{
	int col;
	int row;
	int width;
	int confi;
}Pos;
#endif

#ifndef __KEYPOS
#define __KEYPOS
typedef struct tagKeyPos
{
	Pos face;
	Pos leftEye;
	Pos rightEye;
	Pos leftUpperEye;
	Pos rightUpperEye;
	Pos leftleftEye;
	Pos leftrightEye;
	Pos rightleftEye;
	Pos rightrightEye;
	Pos leftNostril;
	Pos rightNostril;
	Pos nosePoint;
	Pos leftMouth;
	Pos rightMouth;
}KeyPos;
#endif

#ifndef SP_FACE_INFO
#define SP_FACE_INFO
typedef struct tagSPFaceInfo
{
    Rect  m_FaceRect;			//人脸定位框
    float m_afKeyPoint[81 * 2];	//关键点
    KeyPos m_KeyPos;			//保留
}SPFaceInfo;
#endif

#ifndef SP_QUALITY_SCORE
#define SP_QUALITY_SCORE
typedef struct tagQualityScore 
{
	int nIlluminationScore; //人脸光照适宜度打分。0~100 . 过亮或过暗得分都比较低
	int nSharpnessScore;    //人脸清晰程度打分。0~100 . 越清晰得分越高
	float fRoll;            //左右歪头角度
	float fYaw;             //左右侧脸角度
	float fPitch;           //俯仰角度
	int nSunGlassesScore;	//戴墨镜打分
	int nMaskScore;			//戴口罩得分
	int nAlignmentScore;	//关键点对齐得分。0~100，关键点越完整清晰一般得分越高
}SPQualityScore;
#endif

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

/*
#ifdef __cplusplus
extern "C"
{
#endif

//返回版本号
//strVer[input] 16字节空间.输出填充版本号.
SPRESULT SPGetSDKVersion(char *strVer);


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
 SPRESULT SPInitial(SP_HANDLE *pHandle, char *strName);


//释放Handle
//pHandle [input]指向SPInitial初始化好的Handle
 SPRESULT SPRelease(SP_HANDLE *pHandle);

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
 /*SPRESULT SPDetectFaceKeyPoints(SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo);



//设置待检测的最小人脸大小。
//
//return: S_OK, S_FAIL
 SPRESULT SPSetMinFace(SP_HANDLE Handle, int iMinFace);	


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
/* SPRESULT SPGetFaceQuality(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, SPQualityScore *pScore);


/**************************************************

    特征和比对

*************************************************/
//Handle [input] SPInitial初始化好的Handle
//piFtrSize [output] 输出特征字节个数
//return: S_OK, S_FAIL
/* SPRESULT SPGetFeatureSize(SP_HANDLE Handle, int *piFtrSize);


//提取特征。
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入图片灰度信息。数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素的灰度值
//nImgWidth, nImgHeight[input] 图片的宽度高度
//pFaceInfo   [input] 一个人脸信息
//pOutFeature [output]输出特征串。特征串长度见SPGetFeatureSize， 需要外部申请好。
//return : S_OK. other failed
 SPRESULT SPExtractFeature(SP_HANDLE Handle,
                          const unsigned char* pImg, int nImgWidth, int nImgHeight,
						  SPFaceInfo *pFaceInfo, unsigned char *pOutFeature);



//提取特征。
//Handle [input] SPInitial初始化好的Handle
//pImg   [input] 输入图片灰度信息。数据内容:图片从左上到右下，逐行 每行从左到右逐点排列各像素的灰度值
//nImgWidth, nImgHeight[input] 图片的宽度高度
//pFaceInfo   [input] 几个人脸信息
//nFaceNum	 [input] 人脸数目
//pOutFeature [output] 几个人脸的输出特征串。顺序和pFaceInfo对应的人脸顺序一致。
//                     每个特征串长度见SPGetFeatureSize， 需要外部申请好。
//return : S_OK. other failed
SPRESULT SPExtractFeature_N(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, int nFaceNum,
	unsigned char *pOutFeature);



//用于单独比较两张图片的特征串相似性。
//Handle [input] SPInitial初始化好的Handle
//pFeaA  [input] 特征串
//pFeaB  [input] 特征串
//fScore [output] 相似性度量值，0~1.0 ，越大越相似。
//return : S_OK. other failed
 SPRESULT  SPCompareFeature(SP_HANDLE Handle,
							const unsigned char *pFeaA,
							const unsigned char *pFeaB,
                            float *fScore);


#ifdef __cplusplus
}
#endif
*/
#endif //SPFACERECSDK_H
