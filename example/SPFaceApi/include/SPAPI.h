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

#ifdef __cplusplus
extern "C"
{
#endif

//���ذ汾��
//strVer[input] 16�ֽڿռ�.������汾��.
 SPRESULT SPGetSDKVersion(char *strVer);



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
 SPRESULT SPDetectFaceKeyPoints(SP_HANDLE Handle,
	const unsigned char*pImg,
	const unsigned char*pImgRGB,
	int nImgWidth, int nImgHeight,
	int* pnMaxFace,
	SPFaceInfo *pFaceInfo);



//���ô�������С������С��
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




 SPRESULT  SPCompareFeature(SP_HANDLE Handle,
							const unsigned char *pFeaA,
							const unsigned char *pFeaB,
                            float *fScore);



#ifdef __cplusplus
}
#endif

#endif //SPFACERECSDK_H
