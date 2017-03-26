
// ProgressDialog.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CProgressDialogApp:
// このクラスの実装については、ProgressDialog.cpp を参照してください。
//

class CProgressDialogApp : public CWinApp
{
public:
	CProgressDialogApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CProgressDialogApp theApp;