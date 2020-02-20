/***************************************************************
**
**  
**  filename: Facere.h
**
**  description:  ����ʶ��⵼�������ӿ�
**
**************************************************************/

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� FACERE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// FACERE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
// �ӿڸ��� 2012-07-28

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

#ifdef __cplusplus
extern "C" {
#endif

FACERE_API BOOL RegisterDll(const char* pDllPath);

FACERE_API void UnRegisterDll();

//////////////////////////////////////////////////////////////////////////
// �Ľ��ӿ� 2012-07-28

// ----------------------�ڴ����ӿ�------------------------------
// �ڴ�ռ���亯��
FACERE_API unsigned char* FreMalloc(unsigned int nSize);

// �ڴ�ռ��ͷź���
FACERE_API void FreFree(unsigned char *pBuffer);


// --------------------------�������ӿ�----------------------------
// ��ָ���ĵ���ͼ�����ݽ���������⣬�����������������������С�
FACERE_API BOOL SingleFaceDetect(FreImageList* plstFace, FreImageList* pZoomPicList, FacePosList* plstFacePos, FreImage SrcPicture, int *piFaceCount, int f_Zoom = 1, int b_Zoom = 1);

// -----------����ģ�����ݡ�ͼ�����ݺ��������������������ͷŵĽӿ�-------
// FaceTemplateList��ش�����
// ��������ģ����������
FACERE_API FaceTemplateList * FreCreateFaceTemplateList();

// �������ģ�����������е���������
FACERE_API void FreClearFaceTemplateList(FaceTemplateList * pList);

// �������ģ�����������е���������,��ɾ���ͷ�����ģ����������
FACERE_API void FreDeleteFaceTemplateList(FaceTemplateList * pList);

// ����������һ������ģ�����ݽڵ�
FACERE_API void FreInsertFaceTemplateList(FaceTemplateList *pList, SFaceTemplate *pFaceTempNode);

// ��������ɾ��ָ�����Ƶ�����ģ�����ݽڵ�
FACERE_API void FreRemoveFaceTemplateList(FaceTemplateList *pList, char *pFaceTempName);


// FreImageList��ش�����
// ����ͼ����������
FACERE_API FreImageList* FreCreateFreImageList();

// ���ͼ�����������е���������
FACERE_API void FreClearFreImageList(FreImageList* pList);

// ���ͼ�����������е���������,��ɾ���ͷ�ͼ����������
FACERE_API void FreDeleteFreImageList (FreImageList* pList);

// ����������һ��ͼ�����ݽڵ�
FACERE_API void FreInsertFreImageList(FreImageList *pList, FreImage *pNode);

// ��������ɾ��ָ�����Ƶ�ͼ�����ݽڵ�
FACERE_API void FreRemoveFreImageList(FreImageList *pList, char *pName);


// FacePosList��ش�����
// ��������������Ϣ����
FACERE_API FacePosList* FreCreateFacePosList ();

// �������������Ϣ�����е���������
FACERE_API void FreClearFacePosList(FacePosList* pList);

// �������������Ϣ�е���������,��ɾ���ͷ�����������Ϣ����
FACERE_API void FreDeleteFacePosList(FacePosList* pList);

// ����������һ������������Ϣ�ڵ�
FACERE_API void FreInsertFacePosList(FacePosList *pList, FacePos *pNode);

// ��������ɾ��ָ�����Ƶ�����������Ϣ�ڵ�
FACERE_API void FreRemoveFacePosList(FacePosList *pList, char *pName);


// -------------------------����ģ�����ӿ�-------------------------
// ��Ե���ͼƬ�ļ���ⴴ������ģ�壬ģ�����ݱ��浽�ڴ�����
FACERE_API BOOL FaceTemplate(FaceTemplateList* plstFt, FreImageList* plstFtFace, FreImage SrcPicture, int *pTemplateCount, int f_Zoom = 1, int b_Zoom = 1);

// ������ģ���ڴ�������ɾ��ָ�����Ƶ�ģ������
FACERE_API BOOL DeleteTemplate(FaceTemplateList* plstFt, char *pTemplateName);

// ----------------------------����ʶ�����ӿ�----------------------
// ��������ʶ��������������
FACERE_API FaceRecogList *FreCreateFaceRecogList();

// �������в���һ��ʶ������¼
FACERE_API void FreInsertFaceRecogList(FaceRecogList *pList, FaceRecogNode *pNode);

// ��������е��������ݣ����ǲ�ɾ������
FACERE_API void FreClearFaceRecogList(FaceRecogList *pList);

// ��������е��������ݣ���ɾ������
FACERE_API void FreDeleteFaceRecogList(FaceRecogList *pList);

// ɾ�����ƶ���Ϣ����
FACERE_API void DeleteSimlarInfo(SimlarInfo *pSimlarInfo);

// ������Ϣstring�ַ���ɾ������
FACERE_API void DeleteString(std::string *pStr);

// ͼ�����ź����ӿ�
FACERE_API BOOL ZoomImage(FreImage *pSrcImg, int iZoomSize, FreImage *pZoomImg);

// ģ��ת��
FACERE_API BOOL FaceTemplateCvt(SFaceTemplate *ft);

// �Ե�������ͼƬ�����ڴ�ģ�����ݽӿ�
FACERE_API BOOL SinFaceTemplate(SFaceTemplate* pSinFt, const FreImage *FacePicture, int f_Zoom = 1);

// ��������ģ�����ƶȽӿ�
FACERE_API float FaceMatch(const SFaceTemplate *ft1, const SFaceTemplate *ft2);
#ifdef __cplusplus
}
#endif


#endif