//2011.10.6
//cswuyg
//dll导出类
// 实现类
#pragma once

#include "SPFaceApi.h"

class ExportImpl : public IExport
{
public:
	virtual void Hi();
	virtual void Test();
	virtual void Release();
	~ExportImpl();

private:

};