#ifndef YL_FACEREMULDLLINTERFACE_H
#define YL_FACEREMULDLLINTERFACE_H

//////////////////////////////////////////////////////////////////////////
// ����Facere.h�ж�Ӧ�Ľӿڣ� ��̬����Facere.dllʹ��
// Last updated 2013-08-13 by dh 
//

typedef BOOL (*AddRegisterDll)(const char* pDllPath);   // upaate 20130813
// �ڴ�ռ���亯��
typedef unsigned char* (*AddFreMalloc)(unsigned int);
// �ڴ�ռ��ͷź���
typedef void (*AddFreFree)(unsigned char*);
// ��ָ���ĵ���ͼ�����ݽ���������⣬�����������������������С�
typedef BOOL (*AddSingleFaceDetect)(FaceTemplateList*, FreImageList* ,FacePosList*, FreImage, int*, int, int);
// ��������ģ����������
typedef FaceTemplateList* (*AddFreCreateFaceTemplateList)();
// �������ģ�����������е���������
typedef void (*AddFreClearFaceTemplateList)(FaceTemplateList*);
// �������ģ�����������е���������,��ɾ���ͷ�����ģ����������
typedef void (*AddFreDeleteFaceTemplateList)(FaceTemplateList*);
// ����������һ������ģ�����ݽڵ�
typedef void (*AddFreInsertFaceTemplateList)(FaceTemplateList*, SFaceTemplate*);
// ��������ɾ��ָ�����Ƶ�����ģ�����ݽڵ�
typedef void (*AddFreRemoveFaceTemplateList)(FaceTemplateList*, char*);
// ����ͼ����������
typedef FreImageList* (*AddFreCreateFreImageList)();
// ���ͼ�����������е���������
typedef void (*AddFreClearFreImageList)(FreImageList*);
// ���ͼ�����������е���������,��ɾ���ͷ�ͼ����������
typedef void (*AddFreDeleteFreImageList)(FreImageList*);
// ����������һ��ͼ�����ݽڵ�
typedef void (*AddFreInsertFreImageList)(FreImageList*, FreImage*);
// ��������ɾ��ָ�����Ƶ�ͼ�����ݽڵ�
typedef void (*AddFreRemoveFreImageList)(FreImageList*, char*);
// ��������������Ϣ����
typedef FacePosList* (*AddFreCreateFacePosList)();
// �������������Ϣ�����е���������
typedef void (*AddFreClearFacePosList)(FacePosList*);
// �������������Ϣ�е���������,��ɾ���ͷ�����������Ϣ����
typedef void (*AddFreDeleteFacePosList)(FacePosList*);
// ����������һ������������Ϣ�ڵ�
typedef void (*AddFreInsertFacePosList)(FacePosList*, FacePos*);
// ��������ɾ��ָ�����Ƶ�����������Ϣ�ڵ�
typedef void (*AddFreRemoveFacePosList)(FacePosList*, char*);
// ������ģ���ڴ�������ɾ��ָ�����Ƶ�ģ������
typedef BOOL (*AddDeleteTemplate)(FaceTemplateList*, char*);
// �Ե�������ͼƬ�����ڴ�ģ�����ݽӿ�
typedef BOOL (*AddSinFaceTemplate)(SFaceTemplate*, const FreImage*, int f_Zoom);
// ��������ʶ��������������
typedef FaceRecogList* (*AddFreCreateFaceRecogList)();
// �������в���һ��ʶ������¼
typedef void (*AddFreInsertFaceRecogList)(FaceRecogList*, FaceRecogNode*);
// ��������е��������ݣ����ǲ�ɾ������
typedef void (*AddFreClearFaceRecogList)(FaceRecogList*);
// ��������е��������ݣ���ɾ������
typedef void (*AddFreDeleteFaceRecogList)(FaceRecogList*);
// ɾ�����ƶ���Ϣ����
typedef void (*AddDeleteSimlarInfo)(SimlarInfo*);
// ������Ϣstring�ַ���ɾ������
typedef void (*AddDeleteString)(std::string*);
// ����ʶ����飬������������ڴ�����
typedef BOOL (*AddFaceID)(FaceTemplateList*, FreImageList*, FaceRecogList*, std::string **, int, SimlarInfo **, int*, float, int f_Zoom, int b_Zoom);
// ��������ģ�����ƶȽӿ�
typedef float (*AddFaceMatch)(const SFaceTemplate *, const SFaceTemplate *);
typedef void (*AddUnRegisterDll)();
typedef BOOL (*AddFaceTemplateCvt)(SFaceTemplate *ft);

typedef int (*AddPRRegisterDll)(char *);
typedef int (*AddPRDetect)(unsigned char *, RECT *, int , int ,char *, RECT *, int *);
typedef int (*AddPRUnRegisterDll)();
#endif
