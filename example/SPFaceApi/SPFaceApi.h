//2019.10.18
//@glCnZuDe
//����ʶ��(Seate V2)dll������
//dll����ʹ���߹��õ�ͷ�ļ�

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

//���ذ汾��
//strVer[input] 16�ֽڿռ�.������汾��.
extern "C" SPFACEREC_API long _stdcall SPGetSDKVersion(char *strVer);

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
extern "C" SPFACEREC_API long _stdcall SPInitial(SP_HANDLE *pHandle, char *strName);

//�ͷ�Handle
//pHandle [input]ָ��SPInitial��ʼ���õ�Handle
extern "C" SPFACEREC_API long _stdcall SPRelease(SP_HANDLE *pHandle);

//return: S_OK, S_FAIL
extern "C" SPFACEREC_API long _stdcall SPDetectFaceKeyPoints(
	SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo);

//���ô�������С������С��
//return: S_OK, S_FAIL
extern "C" SPFACEREC_API long _stdcall SPSetMinFace(
	SP_HANDLE Handle, 
	int iMinFace);	

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
extern "C" SPFACEREC_API long _stdcall SPGetFaceQuality(
	SP_HANDLE Handle,
	const unsigned char* pImg, 
	int nImgWidth, 
	int nImgHeight,
	SPFaceInfo *pFaceInfo, 
	SPQualityScore *pScore);

/**************************************************
    �����ͱȶ�
*************************************************/
//Handle [input] SPInitial��ʼ���õ�Handle
//piFtrSize [output] ��������ֽڸ���
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

//��ȡ������
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����ͼƬ�Ҷ���Ϣ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и����صĻҶ�ֵ
//nImgWidth, nImgHeight[input] ͼƬ�Ŀ�ȸ߶�
//pFaceInfo   [input] һ��������Ϣ
//pOutFeature [output]��������������������ȼ�SPGetFeatureSize�� ��Ҫ�ⲿ����á�
//return : S_OK. other failed
extern "C" SPFACEREC_API long _stdcall SPExtractFeature_N(
	SP_HANDLE Handle,
	const unsigned char* pImg, 
	int nImgWidth,
	int nImgHeight,
	SPFaceInfo *pFaceInfo, 
	int nFaceNum,
	unsigned char *pOutFeature);

//���ڵ����Ƚ�����ͼƬ�������������ԡ�
//Handle [input] SPInitial��ʼ���õ�Handle
//pFeaA  [input] ������
//pFeaB  [input] ������
//fScore [output] �����Զ���ֵ��0~1.0 ��Խ��Խ���ơ�
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

// ע�ắ��
extern "C" SPFACEREC_API bool _stdcall RegisterDll(const char* pDllPath);

// ��ע�ắ��
extern "C" SPFACEREC_API void _stdcall UnRegisterDll();

//////////////////////////////////////////////////////////////////////////
// �����ӿ� 2019-10-18

// ----------------------�ڴ����ӿ�------------------------------
// �ڴ�ռ���亯��
extern "C" SPFACEREC_API unsigned char* _stdcall FreMalloc(SP_HANDLE pHandle, unsigned int nSize);

// �ڴ�ռ��ͷź���
extern "C" SPFACEREC_API void _stdcall FreFree(SP_HANDLE pHandle, unsigned char *pBuffer);

// --------------------------�������ӿ�----------------------------
// ��ָ���ĵ���ͼ�����ݽ���������⣬�����������������������С�
extern "C" SPFACEREC_API bool _stdcall SingleFaceDetect(SP_HANDLE pHandle, FreImageList* plstFace, FreImageList* pZoomPicList, FacePosList* plstFacePos, FreImage SrcPicture, int *piFaceCount, int f_Zoom = 1, int b_Zoom = 1);

// -----------����ģ�����ݡ�ͼ�����ݺ��������������������ͷŵĽӿ�-------
// FaceTemplateList��ش�����
// ��������ģ����������
extern "C" SPFACEREC_API FaceTemplateList* _stdcall FreCreateFaceTemplateList(SP_HANDLE pHandle);

// �������ģ�����������е���������
extern "C" SPFACEREC_API void _stdcall FreClearFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList);

// �������ģ�����������е���������,��ɾ���ͷ�����ģ����������
extern "C" SPFACEREC_API void _stdcall FreDeleteFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList);

// ����������һ������ģ�����ݽڵ�
extern "C" SPFACEREC_API void _stdcall FreInsertFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, SFaceTemplate *pFaceTempNode);

// ��������ɾ��ָ�����Ƶ�����ģ�����ݽڵ�
extern "C" SPFACEREC_API void _stdcall FreRemoveFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, char *pFaceTempName);

// FreImageList��ش�����
// ����ͼ����������
extern "C" SPFACEREC_API FreImageList* _stdcall FreCreateFreImageList(SP_HANDLE pHandle);

// ���ͼ�����������е���������
extern "C" SPFACEREC_API void _stdcall FreClearFreImageList(SP_HANDLE pHandle, FreImageList* pList);

// ���ͼ�����������е���������,��ɾ���ͷ�ͼ����������
extern "C" SPFACEREC_API void _stdcall FreDeleteFreImageList(SP_HANDLE pHandle, FreImageList* pList);

// ����������һ��ͼ�����ݽڵ�
extern "C" SPFACEREC_API void _stdcall FreInsertFreImageList(SP_HANDLE pHandle, FreImageList *pList, FreImage *pNode);

// ��������ɾ��ָ�����Ƶ�ͼ�����ݽڵ�
extern "C" SPFACEREC_API void _stdcall FreRemoveFreImageList(SP_HANDLE pHandle, FreImageList *pList, char *pName);

// FacePosList��ش�����
// ��������������Ϣ����
extern "C" SPFACEREC_API FacePosList* _stdcall FreCreateFacePosList (SP_HANDLE pHandle);

// �������������Ϣ�����е���������
extern "C" SPFACEREC_API void _stdcall FreClearFacePosList(SP_HANDLE pHandle, FacePosList* pList);

// �������������Ϣ�е���������,��ɾ���ͷ�����������Ϣ����
extern "C" SPFACEREC_API void _stdcall FreDeleteFacePosList(SP_HANDLE pHandle, FacePosList* pList);

// ����������һ������������Ϣ�ڵ�
extern "C" SPFACEREC_API void _stdcall FreInsertFacePosList(SP_HANDLE pHandle, FacePosList *pList, FacePos *pNode);

// ��������ɾ��ָ�����Ƶ�����������Ϣ�ڵ�
extern "C" SPFACEREC_API void _stdcall FreRemoveFacePosList(SP_HANDLE pHandle, FacePosList *pList, char *pName);

// -------------------------����ģ�����ӿ�-------------------------
// ��Ե���ͼƬ�ļ���ⴴ������ģ�壬ģ�����ݱ��浽�ڴ�����
extern "C" SPFACEREC_API bool _stdcall FaceTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, FreImageList* plstFtFace, FreImage SrcPicture, int *pTemplateCount, int f_Zoom = 1, int b_Zoom = 1);

// ������ģ���ڴ�������ɾ��ָ�����Ƶ�ģ������
extern "C" SPFACEREC_API bool _stdcall DeleteTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, char *pTemplateName);

// ----------------------------����ʶ�����ӿ�----------------------
// ��������ʶ��������������
extern "C" SPFACEREC_API FaceRecogList* _stdcall FreCreateFaceRecogList(SP_HANDLE pHandle);

// �������в���һ��ʶ������¼
extern "C" SPFACEREC_API void _stdcall FreInsertFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList, FaceRecogNode *pNode);

// ��������е��������ݣ����ǲ�ɾ������
extern "C" SPFACEREC_API void _stdcall FreClearFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList);

// ��������е��������ݣ���ɾ������
extern "C" SPFACEREC_API void _stdcall FreDeleteFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList);

// ɾ�����ƶ���Ϣ����
extern "C" SPFACEREC_API void _stdcall DeleteSimlarInfo(SP_HANDLE pHandle, SimlarInfo *pSimlarInfo);

// ������Ϣstring�ַ���ɾ������
extern "C" SPFACEREC_API void _stdcall DeleteString(SP_HANDLE pHandle, std::string *pStr);

// ͼ�����ź����ӿ�
extern "C" SPFACEREC_API bool _stdcall ZoomImage(SP_HANDLE pHandle, FreImage *pSrcImg, int iZoomSize, FreImage *pZoomImg);

// ģ��ת��
extern "C" SPFACEREC_API bool _stdcall FaceTemplateCvt(SP_HANDLE pHandle, SFaceTemplate *ft);

// �Ե�������ͼƬ�����ڴ�ģ�����ݽӿ�
extern "C" SPFACEREC_API bool _stdcall SinFaceTemplate(SP_HANDLE pHandle, SFaceTemplate* pSinFt, const FreImage *FacePicture, int f_Zoom = 1);

// ��������ģ�����ƶȽӿ�
extern "C" SPFACEREC_API float _stdcall FaceMatch(SP_HANDLE pHandle, const SFaceTemplate *ft1, const SFaceTemplate *ft2);

// End---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////
