// Base64Util.h: interface for the CBase64Util class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64UTIL_H__DA02957C_D1D3_4198_947E_66F36ABF03BD__INCLUDED_)
#define AFX_BASE64UTIL_H__DA02957C_D1D3_4198_947E_66F36ABF03BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>

//#include "UtilLib.h"
using namespace std;


namespace HZP
{

class /*HZP_LIB_API*/ CBase64Util  
{
	
	static int CharToData(char c);
	static string RemoveAppendData(const string &inData);
public:
	
	/************************************************************************
	* ����:
			����Base64����

		����:
			const char * inData, Ҫ���������
			const int inLen   ���ݳ���
			,char * outData  �����ĳ���

		����ֵ:
			���outDataΪNULL,���ط����ַ�����Ҫ�Ŀռ�,
			���outData��ΪNULL,���ر�������δ�����

	*
	************************************************************************/
	static int  Encode(const char * inData,const int inLen,char * outData);

	/************************************************************************
	* ����:
			����Base64����

		����:
			const string & inData  Ҫ���������
			int *outData  ����������

		����ֵ:
			���outDataΪNULL,���ط����ַ�����Ҫ�Ŀռ�,
			���outData��ΪNULL,���ؽ�������δ�����
	*
	************************************************************************/
	static int Decode(const string & inData,char *outData);
	
	CBase64Util();
	virtual ~CBase64Util();

};

}
#endif // !defined(AFX_BASE64UTIL_H__DA02957C_D1D3_4198_947E_66F36ABF03BD__INCLUDED_)
