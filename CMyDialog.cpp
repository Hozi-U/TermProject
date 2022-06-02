// CMyDialog.cpp: 구현 파일
//

#include "pch.h"
#include "00TermProject.h"
#include "CMyDialog.h"
#include "afxdialogex.h"


// CMyDialog 대화 상자
#define setting 'x64' // 디버깅 설정에 따라 경로 설정
IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOKNAME, m_title);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
END_MESSAGE_MAP()


// CMyDialog 메시지 처리기


BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	CString f_path(chFilePath);
	f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/");
	CFileFind finder;
	CString strWildcard(f_path);
	strWildcard += _T("/*");
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
				m_title.AddString(finder.GetFileName());
		}
	}
	finder.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMyDialog::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItemText(IDC_BOOKNAME, title);
	CDialog::OnOK();
}
