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
    Rect  m_FaceRect;			//������λ��
    float m_afKeyPoint[81 * 2];	//�ؼ���
    KeyPos m_KeyPos;			//����
}SPFaceInfo;
#endif

#ifndef SP_QUALITY_SCORE
#define SP_QUALITY_SCORE
typedef struct tagQualityScore 
{
	int nIlluminationScore; //�����������˶ȴ�֡�0~100 . ����������÷ֶ��Ƚϵ�
	int nSharpnessScore;    //���������̶ȴ�֡�0~100 . Խ�����÷�Խ��
	float fRoll;            //������ͷ�Ƕ�
	float fYaw;             //���Ҳ����Ƕ�
	float fPitch;           //�����Ƕ�
	int nSunGlassesScore;	//��ī�����
	int nMaskScore;			//�����ֵ÷�
	int nAlignmentScore;	//�ؼ������÷֡�0~100���ؼ���Խ��������һ��÷�Խ��
}SPQualityScore;
#endif

//ͼ�����ơ�����ģ���ļ����Ƶ���󳤶�
#define MAX_NAME_LEN 260

#pragma pack(push, 1)

// ����ͼ�����ݣ��������ͼ�����ݴ洢�ṹ
typedef struct _FreImage
{
    int  nSize;               // FreImage �ṹ��С����sizeof(FreImage)
    int  width;               // ͼ�����ؿ� 
    int  height;              // ͼ�����ظ�
    int  imageSize;           // ͼ�����ݴ�С
    unsigned char *imageData; //imageData���ݵ��ֽڴ�Сunsigned char *imageData;  ͼ������ָ�룬���ݸ�ʽΪjpeg��ʽ���������ڴ�ռ�ͨ������FreMalloc��������䣬����FreFree���������ͷš�
    char imageName[MAX_NAME_LEN]; // ͼ�����ƣ�ͼ�������ֽڸ�������ܳ���(MAX_NAME_LEN-1������
}FreImage;

//   ����ģ�����ݴ洢�ṹ
typedef struct _FaceTemplate
{
    int  nSize;          		    // FaceTemplate�ṹ��С����sizeof(FaceTemplate)
    unsigned char *FtData;       	// ģ������ָ�룬�˵������ڴ�ռ�ͨ������FreMalloc��������䣬����FreFree���������ͷ�
    int  FtSize;        			// ģ�����ݴ�С,��FtData���ݴ�С
    char FtName[MAX_NAME_LEN];      // ����ģ�����ƣ�����ģ�������ֽڸ�������ܳ�����MAX_NAME_LEN-1����
	double simlar;
}SFaceTemplate;

// ���ڴ洢�������ڶ�Ӧͼ���е�������Ϣ
typedef struct _FacePos
{
    int  center_x;          // ����ͼƬ�����ڶ�Ӧͼ���е�x����
    int  center_y;          // ����ͼƬ�����ڶ�Ӧͼ���е�y����
    int  width;             // ����ͼƬ���ؿ�
    int  height;            // ����ͼƬ���ظ�
    char faceName[MAX_NAME_LEN]; // ͼ���е��������ƣ�ͼ���е����������ֽڸ�������ܳ�����MAX_NAME_LEN-1������
}FacePos;

// ÿ������ģ���ļ��ܴ�ŵ����ģ�����
#define MAX_FACETEMP_COUNT 50000

#define FACETEMPLATE_FILE_KEY 0x45544146

// ���ڱ�������ģ������ͷ��Ϣ
typedef struct _FaceTempNode
{
    unsigned char bDelete;  // ��ʶ�˽ڵ��Ƿ���ã���������ģ�������Ƿ���ɾ��
    char FtName[MAX_NAME_LEN];// ����ģ������
    unsigned int size;		// ����ģ�����ݴ�С
    //unsigned char data[];	// ����ģ������
}FaceTempNode;

// ����ģ���ļ�ͷ�ṹ
typedef struct _FaceTemplateFileHead
{
    DWORD dwKey;        // ����ģ���ļ�����
    DWORD dwCurNum;     // �ļ�����Чģ�����
    DWORD dwTotalNum;   // �ļ����ܵ�ģ�����
}FaceTemplateFileHead, *PFaceTemplateFileHead;

// ͼ�����ƽṹ
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

// FaceID�ӿ�ʶ�����Ĵ��������ؽṹ
typedef struct _UnFaceLibResult
{
    char szFaceName[MAX_NAME_LEN];
    BYTE *pFaceData;
    int nFaceSize;
}UnFaceLibResult;

typedef struct _FaceLibResult
{
    char szFaceName[MAX_NAME_LEN];  // ԭʼ�������ƣ������ļ����ң���������չ��.jpg
    UINT nGroupId;                  // ����id
    int iSortId;                    // ��Ե���ͼƬ��������ʶ��ʱ�����������ݵ����ƶ�������ţ��������ʼΪ1
}FaceLibResult;

typedef struct _FaceRecogNode
{
    BOOL bInFaceLib;    // ���������Ƿ�������֪��ģ����Ӧ�������ļ�
    union 
    {
        FaceLibResult sFaceInLib;   // ������֪�������е���������š�ԭʼ�������ơ��������ķ����id
        UnFaceLibResult sFaceOutLib;// ���ڴ�ʶ���ͼƬ�м���������������š��������������ơ�(�����_ԭʼ��������)���������ݡ��������ݴ�С
    }u;
}FaceRecogNode;

#pragma pack(pop)

// ����ģ����������
typedef std::list<SFaceTemplate> FaceTemplateList;

// ͼ����������
typedef std::list<FreImage> FreImageList;

// ����������������
typedef std::list<FacePos> FacePosList;

// �������ƶ�˳���������ƶȴӴ�С����
typedef std::list<SimlarNode> SimlarSortList;

// ������д�ʶ��ͼ��ʶ�������ƶ�������Ϣ����
typedef std::map<SImgName, SimlarSortList*> SimlarInfo;

// FaceID���ʶ����������
typedef std::list<FaceRecogNode> FaceRecogList;

/*
#ifdef __cplusplus
extern "C"
{
#endif

//���ذ汾��
//strVer[input] 16�ֽڿռ�.������汾��.
SPRESULT SPGetSDKVersion(char *strVer);


//��ʼ��һ��HANDLE . ���߳�����¸����̳߳�ʼ�����Ե�Handle,
//pHandle [output]���ָ���ʼ���õ�Handle
//strName [input]���SPDataV32.bin��·�����Լ���GPU �Կ���ѡ�����ĸ�GPU�������С�
//               �Ⱥ�������ַ��������ַ����м��ǵ�һ�����Ľ�����'\0'����(���ֽ�ֵΪ0)����������Ϊ'\0\0'��������'\0'
//               ��һ���ַ�����·�����ڶ����ַ�����GPU��ţ�ASCII�� '0'��'9'���Ϊ'9')
//               ����: "D:\\Exam\00\0\0"·��Ϊ"D:\\Exam",��GPU 0
//                     "D:\\Exam\01\0\0"·��Ϊ"D:\\Exam",��GPU 1
//                     "D:\\Exam\0\0"·��Ϊ"D:\\Exam",Ĭ����GPU 0
//               ���û�еڶ����ַ�������һ��������������'\0',����Ĳ���Ĭ��GPU 0
//
//               �ô����ɷ�������:
//               char strInput[256] = {0};//Ŀ���������
//               char strPath = "D:\\Exam";
//               char *pch;
//               strcpy( strInput, strPath);
//               pch = &strInput[ strlen(strInput)]; //pch-> ָ���һ���ַ����Ľ�β'\0'��ǡ�
//               pch[1] = 0x30;                      //�����ţ�ASCII�� 0x30 ��ʾGPU 0�ţ�  0x31��ʾ GPU 1��,�Դ����ơ�
//               pch[2] = pch[3] = 0;                //��������β ����'\0'��ǡ�
//               ������ָ�����Կ��ˡ�
//               ���pch[1] = 0; ���ڵ�һ����������һ��'\0'������Ĭ����GPU 0��.
//linux�ϲ������һ��������������Handleռ���������ܻ�CUDA����
//������������,����һ���������С�
//return: S_OK, S_FAIL
 SPRESULT SPInitial(SP_HANDLE *pHandle, char *strName);


//�ͷ�Handle
//pHandle [input]ָ��SPInitial��ʼ���õ�Handle
 SPRESULT SPRelease(SP_HANDLE *pHandle);

/**************************************************

������λ

*************************************************/

//������λ
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����Ҷ�ͼ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и�����
//pImgRGB[input] �����ɫͼ���������д����ϵ����£����� ÿ�д�����������и�����.
//               ÿ���������δ洢R G B ���������� ע���е�ͼ���ʽ������ B G R �ģ���Ҫ�����ֽ�˳��
//               RGB ˳�򲻷���Ӱ�춨λ�����
//               �������NULL,�ڲ����Ҷ�ͼ���� 
//nImgWidth nImgHeight [input] ͼƬ�Ŀ�ȸ߶�
//pnMaxFace [input] ���� *pnMaxFace ��Ҫ��λ����������� 
//          [output] *pnMaxFace Ϊʵ�ʶ�λ����������
//pFaceInfo [output] ���ÿ��������λ��Ϣ�� ��Ҫ�ⲿ����*pnMaxFace�� SPFaceInfo�ռ䡣
//pFaceInfo.m_KeyPos.face.confiΪ�÷���Ϣ������5�����µ�����������ץ��
//return: S_OK, S_FAIL
 /*SPRESULT SPDetectFaceKeyPoints(SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo);



//���ô�������С������С��
//
//return: S_OK, S_FAIL
 SPRESULT SPSetMinFace(SP_HANDLE Handle, int iMinFace);	


/**************************************************

	�����ж�

***************************************************/
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����ͼƬ�Ҷ���Ϣ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и����صĻҶ�ֵ
//nImgWidth, nImgHeight[input] ͼƬ�Ŀ�ȸ߶�
//pFaceInfo   [input] һ��������Ϣ
//pQualityScore	[output]�������������
//	int nIlluminationScore; //�����������˶ȴ�֡�0~100 . ��������С��80ʱֻץ�Ĳ�ʶ��
//	int nSharpnessScore;    //���������̶ȴ��.   0~100 . ����������С��30ʱֻץ�Ĳ�ʶ��
//	float fRoll;            //������ͷ�Ƕ�
//	float fYaw;             //���Ҳ����Ƕȡ�����С��-20�Ⱥʹ���20��ʱֻץ�Ĳ�ʶ��
//	float fPitch;           //�����Ƕȡ�����С��-25�Ⱥʹ���40��ʱֻץ�Ĳ�ʶ��
//	int nSunGlassesScore;	//��ī����֣����ܻ�û���
//	int nMaskScore;			//�����ֵ÷֣����ܻ�û���
//  int nAlignmentScore;	//�ؼ������÷֡�����С��60ʱֻץ�Ĳ�ʶ��
//return : S_OK. other failed
/* SPRESULT SPGetFaceQuality(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, SPQualityScore *pScore);


/**************************************************

    �����ͱȶ�

*************************************************/
//Handle [input] SPInitial��ʼ���õ�Handle
//piFtrSize [output] ��������ֽڸ���
//return: S_OK, S_FAIL
/* SPRESULT SPGetFeatureSize(SP_HANDLE Handle, int *piFtrSize);


//��ȡ������
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����ͼƬ�Ҷ���Ϣ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и����صĻҶ�ֵ
//nImgWidth, nImgHeight[input] ͼƬ�Ŀ�ȸ߶�
//pFaceInfo   [input] һ��������Ϣ
//pOutFeature [output]��������������������ȼ�SPGetFeatureSize�� ��Ҫ�ⲿ����á�
//return : S_OK. other failed
 SPRESULT SPExtractFeature(SP_HANDLE Handle,
                          const unsigned char* pImg, int nImgWidth, int nImgHeight,
						  SPFaceInfo *pFaceInfo, unsigned char *pOutFeature);



//��ȡ������
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����ͼƬ�Ҷ���Ϣ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и����صĻҶ�ֵ
//nImgWidth, nImgHeight[input] ͼƬ�Ŀ�ȸ߶�
//pFaceInfo   [input] ����������Ϣ
//nFaceNum	 [input] ������Ŀ
//pOutFeature [output] ���������������������˳���pFaceInfo��Ӧ������˳��һ�¡�
//                     ÿ�����������ȼ�SPGetFeatureSize�� ��Ҫ�ⲿ����á�
//return : S_OK. other failed
SPRESULT SPExtractFeature_N(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, int nFaceNum,
	unsigned char *pOutFeature);



//���ڵ����Ƚ�����ͼƬ�������������ԡ�
//Handle [input] SPInitial��ʼ���õ�Handle
//pFeaA  [input] ������
//pFeaB  [input] ������
//fScore [output] �����Զ���ֵ��0~1.0 ��Խ��Խ���ơ�
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
