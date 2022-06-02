// CInfoDialog.cpp: 구현 파일
//

#include "pch.h"
#include "00TermProject.h"
#include "CInfoDialog.h"
#include "afxdialogex.h"


// CInfoDialog 대화 상자

IMPLEMENT_DYNAMIC(CInfoDialog, CDialog)

CInfoDialog::CInfoDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CInfoDialog::~CInfoDialog()
{
}

void CInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoDialog, CDialog)
END_MESSAGE_MAP()


// CInfoDialog 메시지 처리기


void CInfoDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialog::OnCancel();
}
