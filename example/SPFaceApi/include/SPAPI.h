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

#ifdef __cplusplus
extern "C"
{
#endif

//返回版本号
//strVer[input] 16字节空间.输出填充版本号.
 SPRESULT SPGetSDKVersion(char *strVer);



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
 SPRESULT SPDetectFaceKeyPoints(SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo);



//设置待检测的最小人脸大小。
//return: S_OK, S_FAIL
 SPRESULT SPSetMinFace(SP_HANDLE Handle, int iMinFace);	



 SPRESULT SPGetFaceQuality(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, SPQualityScore *pScore);



//return: S_OK, S_FAIL
 SPRESULT SPGetFeatureSize(SP_HANDLE Handle, int *piFtrSize);



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




 SPRESULT  SPCompareFeature(SP_HANDLE Handle,
							const unsigned char *pFeaA,
							const unsigned char *pFeaB,
                            float *fScore);



#ifdef __cplusplus
}
#endif

#endif //SPFACERECSDK_H
