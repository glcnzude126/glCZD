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

//���ﲻ��ֱ��delete pExport����Ϊû�а�IExport��������������Ϊ�麯��
SPFACEREC_API void  APIENTRY DestroyExportObj(IExport* pExport)
{
	pExport->Release();
}

// Start---HWAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////

//���ذ汾��
//strVer[input] 16�ֽڿռ�.������汾��.
SPFACEREC_API long APIENTRY SPGetSDKVersion(char *strVer)
{
	return 0L;
}

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
SPFACEREC_API long APIENTRY SPInitial(SP_HANDLE *pHandle, char *strName)
{
	return 0L;
}

//�ͷ�Handle
//pHandle [input]ָ��SPInitial��ʼ���õ�Handle
SPFACEREC_API long APIENTRY SPRelease(SP_HANDLE *pHandle)
{
	return 0L;
}

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
SPFACEREC_API long APIENTRY SPDetectFaceKeyPoints(SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo)
{
	return 0L;
}

//���ô�������С������С��
//return: S_OK, S_FAIL
SPFACEREC_API long APIENTRY SPSetMinFace(SP_HANDLE Handle, int iMinFace)
{
	return 0L;
}

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
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPGetFaceQuality(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, SPQualityScore *pScore)
{
	return 0L;
}

/**************************************************
�����ͱȶ�
*************************************************/
//Handle [input] SPInitial��ʼ���õ�Handle
//piFtrSize [output] ��������ֽڸ���
//return: S_OK, S_FAIL
SPFACEREC_API long APIENTRY SPGetFeatureSize(SP_HANDLE Handle, int *piFtrSize)
{
	return 0L;
}

//��ȡ������
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����ͼƬ�Ҷ���Ϣ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и����صĻҶ�ֵ
//nImgWidth, nImgHeight[input] ͼƬ�Ŀ�ȸ߶�
//pFaceInfo   [input] һ��������Ϣ
//pOutFeature [output]��������������������ȼ�SPGetFeatureSize�� ��Ҫ�ⲿ����á�
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPExtractFeature(SP_HANDLE Handle,
                          const unsigned char* pImg, int nImgWidth, int nImgHeight,
						  SPFaceInfo *pFaceInfo, unsigned char *pOutFeature)
{
	return 0L;
}

//��ȡ������
//Handle [input] SPInitial��ʼ���õ�Handle
//pImg   [input] ����ͼƬ�Ҷ���Ϣ����������:ͼƬ�����ϵ����£����� ÿ�д�����������и����صĻҶ�ֵ
//nImgWidth, nImgHeight[input] ͼƬ�Ŀ�ȸ߶�
//pFaceInfo   [input] ����������Ϣ
//nFaceNum	 [input] ������Ŀ
//pOutFeature [output] ���������������������˳���pFaceInfo��Ӧ������˳��һ�¡�
//                     ÿ�����������ȼ�SPGetFeatureSize�� ��Ҫ�ⲿ����á�
//return : S_OK. other failed
SPFACEREC_API long APIENTRY SPExtractFeature_N(SP_HANDLE Handle,
	const unsigned char* pImg, int nImgWidth, int nImgHeight,
	SPFaceInfo *pFaceInfo, int nFaceNum,
	unsigned char *pOutFeature)
{
	return 0L;
}

//���ڵ����Ƚ�����ͼƬ�������������ԡ�
//Handle [input] SPInitial��ʼ���õ�Handle
//pFeaA  [input] ������
//pFeaB  [input] ������
//fScore [output] �����Զ���ֵ��0~1.0 ��Խ��Խ���ơ�
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

// ע�ắ��
SPFACEREC_API bool APIENTRY RegisterDll(const char* pDllPath)
{
	return true;
}

// ��ע�ắ��
SPFACEREC_API void APIENTRY UnRegisterDll()
{

}

//////////////////////////////////////////////////////////////////////////
// �Ľ��ӿ� 2020-02-18

// ----------------------�ڴ����ӿ�------------------------------
// �ڴ�ռ���亯��
SPFACEREC_API unsigned char* APIENTRY FreMalloc(SP_HANDLE pHandle, unsigned int nSize)
{
	return NULL;
}

// �ڴ�ռ��ͷź���
SPFACEREC_API void APIENTRY FreFree(SP_HANDLE pHandle, unsigned char *pBuffer)
{

}

// --------------------------�������ӿ�----------------------------
// ��ָ���ĵ���ͼ�����ݽ���������⣬�����������������������С�
SPFACEREC_API bool APIENTRY SingleFaceDetect(SP_HANDLE pHandle, FreImageList* plstFace, FreImageList* pZoomPicList, FacePosList* plstFacePos, FreImage SrcPicture, int *piFaceCount, int f_Zoom/* = 1*/, int b_Zoom/* = 1*/)
{
	return true;
}

// -----------����ģ�����ݡ�ͼ�����ݺ��������������������ͷŵĽӿ�-------
// FaceTemplateList��ش�����
// ��������ģ����������
SPFACEREC_API FaceTemplateList* APIENTRY FreCreateFaceTemplateList(SP_HANDLE pHandle)
{
	return NULL;
}

// �������ģ�����������е���������
SPFACEREC_API void APIENTRY FreClearFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList)
{

}

// �������ģ�����������е���������,��ɾ���ͷ�����ģ����������
SPFACEREC_API void APIENTRY FreDeleteFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList * pList)
{

}

// ����������һ������ģ�����ݽڵ�
SPFACEREC_API void APIENTRY FreInsertFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, SFaceTemplate *pFaceTempNode)
{

}

// ��������ɾ��ָ�����Ƶ�����ģ�����ݽڵ�
SPFACEREC_API void APIENTRY FreRemoveFaceTemplateList(SP_HANDLE pHandle, FaceTemplateList *pList, char *pFaceTempName)
{

}

// FreImageList��ش�����
// ����ͼ����������
SPFACEREC_API FreImageList* APIENTRY FreCreateFreImageList(SP_HANDLE pHandle)
{
	return NULL;
}

// ���ͼ�����������е���������
SPFACEREC_API void APIENTRY FreClearFreImageList(SP_HANDLE pHandle, FreImageList* pList)
{

}

// ���ͼ�����������е���������,��ɾ���ͷ�ͼ����������
SPFACEREC_API void APIENTRY FreDeleteFreImageList (SP_HANDLE pHandle, FreImageList* pList)
{

}

// ����������һ��ͼ�����ݽڵ�
SPFACEREC_API void APIENTRY FreInsertFreImageList(SP_HANDLE pHandle, FreImageList *pList, FreImage *pNode)
{

}

// ��������ɾ��ָ�����Ƶ�ͼ�����ݽڵ�
SPFACEREC_API void APIENTRY FreRemoveFreImageList(SP_HANDLE pHandle, FreImageList *pList, char *pName)
{

}

// FacePosList��ش�����
// ��������������Ϣ����
SPFACEREC_API FacePosList* APIENTRY FreCreateFacePosList (SP_HANDLE pHandle)
{
	return NULL;
}

// �������������Ϣ�����е���������
SPFACEREC_API void APIENTRY FreClearFacePosList(SP_HANDLE pHandle, FacePosList* pList)
{

}

// �������������Ϣ�е���������,��ɾ���ͷ�����������Ϣ����
SPFACEREC_API void APIENTRY FreDeleteFacePosList(SP_HANDLE pHandle, FacePosList* pList)
{

}

// ����������һ������������Ϣ�ڵ�
SPFACEREC_API void APIENTRY FreInsertFacePosList(SP_HANDLE pHandle, FacePosList *pList, FacePos *pNode)
{

}

// ��������ɾ��ָ�����Ƶ�����������Ϣ�ڵ�
SPFACEREC_API void APIENTRY FreRemoveFacePosList(SP_HANDLE pHandle, FacePosList *pList, char *pName)
{

}

// -------------------------����ģ�����ӿ�-------------------------
// ��Ե���ͼƬ�ļ���ⴴ������ģ�壬ģ�����ݱ��浽�ڴ�����
SPFACEREC_API bool APIENTRY FaceTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, FreImageList* plstFtFace, FreImage SrcPicture, int *pTemplateCount, int f_Zoom/* = 1*/, int b_Zoom/* = 1*/)
{
	return true;
}

// ������ģ���ڴ�������ɾ��ָ�����Ƶ�ģ������
SPFACEREC_API bool APIENTRY DeleteTemplate(SP_HANDLE pHandle, FaceTemplateList* plstFt, char *pTemplateName)
{
	return true;
}

// ----------------------------����ʶ�����ӿ�----------------------
// ��������ʶ��������������
SPFACEREC_API FaceRecogList* APIENTRY FreCreateFaceRecogList(SP_HANDLE pHandle)
{
	return NULL;
}

// �������в���һ��ʶ������¼
SPFACEREC_API void APIENTRY FreInsertFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList, FaceRecogNode *pNode)
{

}

// ��������е��������ݣ����ǲ�ɾ������
SPFACEREC_API void APIENTRY FreClearFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList)
{

}

// ��������е��������ݣ���ɾ������
SPFACEREC_API void APIENTRY FreDeleteFaceRecogList(SP_HANDLE pHandle, FaceRecogList *pList)
{

}

// ɾ�����ƶ���Ϣ����
SPFACEREC_API void APIENTRY DeleteSimlarInfo(SP_HANDLE pHandle, SimlarInfo *pSimlarInfo)
{

}

// ������Ϣstring�ַ���ɾ������
SPFACEREC_API void APIENTRY DeleteString(SP_HANDLE pHandle, std::string *pStr)
{

}

// ͼ�����ź����ӿ�
SPFACEREC_API bool APIENTRY ZoomImage(SP_HANDLE pHandle, FreImage *pSrcImg, int iZoomSize, FreImage *pZoomImg)
{
	return true;
}

// ģ��ת��
SPFACEREC_API bool APIENTRY FaceTemplateCvt(SP_HANDLE pHandle, SFaceTemplate *ft)
{
	return true;
}

// �Ե�������ͼƬ�����ڴ�ģ�����ݽӿ�
SPFACEREC_API bool APIENTRY SinFaceTemplate(SP_HANDLE pHandle, SFaceTemplate* pSinFt, const FreImage *FacePicture, int f_Zoom/* = 1*/)
{
	return true;
}

// ��������ģ�����ƶȽӿ�
SPFACEREC_API float APIENTRY FaceMatch(SP_HANDLE pHandle, const SFaceTemplate *ft1, const SFaceTemplate *ft2)
{
	return 0.0f;
}

// End---SPAPI-Export-Interface
////////////////////////////////////////////////////////////////////////////////////////////////////
