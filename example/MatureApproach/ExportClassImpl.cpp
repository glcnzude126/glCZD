#include "stdafx.h"
#include "ExportClassImpl.h"

void ExportImpl::Hi()
{
	wcout << L"Hello World" << endl;
}

void ExportImpl::Test()
{
	wcout << L"Hi MyglCZD" << endl;
}

void ExportImpl::Release()
{
	delete this;
}

ExportImpl::~ExportImpl()
{
	cout << "Release OK" << endl;
}