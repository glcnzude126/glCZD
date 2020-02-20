#ifndef YL_FACEREMULDLLINTERFACE_H
#define YL_FACEREMULDLLINTERFACE_H

//////////////////////////////////////////////////////////////////////////
// 定义Facere.h中对应的接口， 动态加载Facere.dll使用
// Last updated 2013-08-13 by dh 
//

typedef BOOL (*AddRegisterDll)(const char* pDllPath);   // upaate 20130813
// 内存空间分配函数
typedef unsigned char* (*AddFreMalloc)(unsigned int);
// 内存空间释放函数
typedef void (*AddFreFree)(unsigned char*);
// 对指定的单张图像数据进行人脸检测，检测结果输出到人脸数据容器中。
typedef BOOL (*AddSingleFaceDetect)(FaceTemplateList*, FreImageList* ,FacePosList*, FreImage, int*, int, int);
// 创建人脸模板数据容器
typedef FaceTemplateList* (*AddFreCreateFaceTemplateList)();
// 清空人脸模板数据容器中的所有数据
typedef void (*AddFreClearFaceTemplateList)(FaceTemplateList*);
// 清空人脸模板数据容器中的所有数据,并删除释放人脸模板数据容器
typedef void (*AddFreDeleteFaceTemplateList)(FaceTemplateList*);
// 向容器插入一个人脸模板数据节点
typedef void (*AddFreInsertFaceTemplateList)(FaceTemplateList*, SFaceTemplate*);
// 从容器中删除指定名称的人脸模板数据节点
typedef void (*AddFreRemoveFaceTemplateList)(FaceTemplateList*, char*);
// 创建图像数据容器
typedef FreImageList* (*AddFreCreateFreImageList)();
// 清空图像数据容器中的所有数据
typedef void (*AddFreClearFreImageList)(FreImageList*);
// 清空图像数据容器中的所有数据,并删除释放图像数据容器
typedef void (*AddFreDeleteFreImageList)(FreImageList*);
// 向容器插入一个图像数据节点
typedef void (*AddFreInsertFreImageList)(FreImageList*, FreImage*);
// 从容器中删除指定名称的图像数据节点
typedef void (*AddFreRemoveFreImageList)(FreImageList*, char*);
// 创建人脸坐标信息容器
typedef FacePosList* (*AddFreCreateFacePosList)();
// 清空人脸坐标信息容器中的所有数据
typedef void (*AddFreClearFacePosList)(FacePosList*);
// 清空人脸坐标信息中的所有数据,并删除释放人脸坐标信息容器
typedef void (*AddFreDeleteFacePosList)(FacePosList*);
// 向容器插入一个人脸坐标信息节点
typedef void (*AddFreInsertFacePosList)(FacePosList*, FacePos*);
// 从容器中删除指定名称的人脸坐标信息节点
typedef void (*AddFreRemoveFacePosList)(FacePosList*, char*);
// 从人脸模板内存容器中删除指定名称的模板数据
typedef BOOL (*AddDeleteTemplate)(FaceTemplateList*, char*);
// 对单个人脸图片创建内存模版数据接口
typedef BOOL (*AddSinFaceTemplate)(SFaceTemplate*, const FreImage*, int f_Zoom);
// 创建人脸识别分组结果输出容器
typedef FaceRecogList* (*AddFreCreateFaceRecogList)();
// 向容器中插入一条识别结果记录
typedef void (*AddFreInsertFaceRecogList)(FaceRecogList*, FaceRecogNode*);
// 清空容器中的所有数据，但是不删除容器
typedef void (*AddFreClearFaceRecogList)(FaceRecogList*);
// 清空容器中的所有数据，并删除容器
typedef void (*AddFreDeleteFaceRecogList)(FaceRecogList*);
// 删除相似度信息容器
typedef void (*AddDeleteSimlarInfo)(SimlarInfo*);
// 分组信息string字符串删除函数
typedef void (*AddDeleteString)(std::string*);
// 人脸识别分组，保存分组结果到内存容器
typedef BOOL (*AddFaceID)(FaceTemplateList*, FreImageList*, FaceRecogList*, std::string **, int, SimlarInfo **, int*, float, int f_Zoom, int b_Zoom);
// 计算两个模版相似度接口
typedef float (*AddFaceMatch)(const SFaceTemplate *, const SFaceTemplate *);
typedef void (*AddUnRegisterDll)();
typedef BOOL (*AddFaceTemplateCvt)(SFaceTemplate *ft);

typedef int (*AddPRRegisterDll)(char *);
typedef int (*AddPRDetect)(unsigned char *, RECT *, int , int ,char *, RECT *, int *);
typedef int (*AddPRUnRegisterDll)();
#endif
