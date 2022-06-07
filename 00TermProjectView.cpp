// 00TermProjectView.cpp: CMy00TermProjectView 클래스의 구현
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "00TermProject.h"
#endif

#include "00TermProjectDoc.h"
#include "00TermProjectView.h"
#include "CMyDialog.h"
#include "CInfoDialog.h"
#include <vtkLight.h>
#include <vtkSTLReader.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CMy00TermProjectView
#define setting 'x64' // 디버깅 설정에 따라 경로 설정\
// 메인 이미지(장) 스케일링 21, 18
#define main_img_x 21 
#define main_img_y 18
// 서브 이미지(글자정보, 선택글자) 스케일링 2
#define sub_img 2
IMPLEMENT_DYNCREATE(CMy00TermProjectView, CFormView)

BEGIN_MESSAGE_MAP(CMy00TermProjectView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMy00TermProjectView::OnBnClickedButtonOpen)
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CLICK, IDC_LIST_CHARS, &CMy00TermProjectView::OnNMClickListChars)
	ON_BN_CLICKED(IDC_BUTTON_KOREA, &CMy00TermProjectView::OnBnClickedButtonKorea)
END_MESSAGE_MAP()

// CMy00TermProjectView 생성/소멸
CMy00TermProjectView::CMy00TermProjectView() noexcept
	: CFormView(IDD_MY00TERMPROJECT_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// Gdi+ start
	GdiplusStartupInput GdiplusStartupInput;
	GdiplusStartup(&g_GdiPulsTokenData, &GdiplusStartupInput, NULL);
}

CMy00TermProjectView::~CMy00TermProjectView()
{
	// Gdi+ shutdown
	GdiplusShutdown(g_GdiPulsTokenData);
}

void CMy00TermProjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK_TEXT, m_book_text);
	DDX_Control(pDX, IDC_BOOK_KIND, m_book_kind);
	DDX_Control(pDX, IDC_STATIC_SHEETS, m_static_sheet);
	DDX_Control(pDX, IDC_BOOK_TYPE, m_book_type);
	DDX_Control(pDX, IDC_SHEET_TEXT, m_sheet_text);
	DDX_Control(pDX, IDC_SHEET_KINDS, m_sheet_kind);
	DDX_Control(pDX, IDC_SHEET_TYPE, m_sheet_type);
	DDX_Control(pDX, IDC_SPIN_SHEET, m_spin_sheet);
	DDX_Control(pDX, IDC_MAIN_PIC, m_main_pic);
	DDX_Control(pDX, IDC_PIC_INFO, m_pic_info);
	DDX_Control(pDX, IDC_PIC_TYPE, m_pic_type);
	DDX_Control(pDX, IDC_TEXT_CHAR, m_text_char);
	DDX_Control(pDX, IDC_TEXT_INFO, m_text_info);
	DDX_Control(pDX, IDC_SPIN_TYPE, m_spin_type);
	DDX_Control(pDX, IDC_LIST_CHARS, m_list);
	DDX_Control(pDX, IDC_STATIC_TYPE, m_static_type);
	DDX_Control(pDX, IDC_EDIT_BOOKNAME, m_edit_bookname);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_find);
	DDX_Control(pDX, IDC_BUTTON_KOREA, m_koreatech);
}

BOOL CMy00TermProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMy00TermProjectView::OnInitialUpdate()
{
	if (this->GetDlgItem(IDC_3D))
	{
		this->InitVtkWindow(this->GetDlgItem(IDC_3D)->GetSafeHwnd());
		this->ResizeVtkWindow();
	}
	CFormView::OnInitialUpdate();
	m_find.LoadBitmaps(IDB_FIND_IMG, IDB_FIND_IMG, NULL, NULL);
	m_find.SizeToContent();
	m_koreatech.LoadBitmaps(IDB_KOREATECH, IDB_KOREATECH, NULL, NULL);
	m_koreatech.SizeToContent();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("   장"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T("  sx"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, _T("  sy"), LVCFMT_LEFT, 50);
}

// CMy00TermProjectView 인쇄

BOOL CMy00TermProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy00TermProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy00TermProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy00TermProjectView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
	
}


// CMy00TermProjectView 진단

#ifdef _DEBUG
void CMy00TermProjectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy00TermProjectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy00TermProjectDoc* CMy00TermProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy00TermProjectDoc)));
	return (CMy00TermProjectDoc*)m_pDocument;
}
#endif //_DEBUG

void CMy00TermProjectView::InitVtkWindow(void* hWnd)
{
	if (m_vtkWindow == NULL)
	{
		vtkSmartPointer<vtkRenderWindowInteractor> interactor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();

		interactor->SetInteractorStyle(
			vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());

		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
		renderer->SetBackground(0.94, 0.94, 0.94); // 화면 초기값 : 회색

		m_vtkWindow = vtkSmartPointer<vtkRenderWindow>::New();
		m_vtkWindow->SetParentId(hWnd);
		m_vtkWindow->SetInteractor(interactor);
		m_vtkWindow->AddRenderer(renderer);
		m_vtkWindow->Render();
	}
}
void CMy00TermProjectView::ResizeVtkWindow()
{
	CRect rc;
	//CWnd* pWnd = GetDlgItem(IDC_3D);
	CWnd* pWnd = GetDlgItem(IDC_3D);
	if (pWnd)
	{
		pWnd->GetClientRect(rc);
		m_vtkWindow->SetSize(rc.Width(), rc.Height());
	}
}
// 3D 출력
void CMy00TermProjectView::Print_3D(char* path)
{
	vtkSmartPointer<vtkSTLReader> pSTLReader =
		vtkSmartPointer<vtkSTLReader>::New();
	pSTLReader->SetFileName(path);
	pSTLReader->Update();

	vtkSmartPointer<vtkPolyData> pPolyData =
		pSTLReader->GetOutput();

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(pPolyData);
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.94, .94, .94);
	renderer->ResetCamera();

	vtkSmartPointer<vtkLight> newLight = vtkSmartPointer<vtkLight>::New();
	newLight->SetColor(.5, .5, .5);
	newLight->SetFocalPoint(0, 0, 0);
	newLight->SetPosition(3, 0, 5);

	vtkSmartPointer<vtkLight> newLight2 = vtkSmartPointer<vtkLight>::New();
	newLight2->SetColor(.5, .5, .5);
	newLight2->SetFocalPoint(0, 0, 0);
	newLight2->SetPosition(3, 0, 5);

	renderer->AddLight(newLight);
	renderer->AddLight(newLight2);

	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}
BOOL  CTypeDB::ReadCSVFile(CString file_name)
{
	string str_buf;
	fstream fs;
	CString str;
	int count = 0;
	SCharInfo info;
	fs.open(file_name, ios::in);
	if (!fs.is_open())
	{
		MessageBox(NULL, _T("could not open csv file!"), _T("error"), MB_ICONERROR);
		return FALSE;
	}
	//CSV파일의 첫 줄은 무시한다.
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf, ',');
	getline(fs, str_buf);
	
	while (!fs.eof()) {
		m_Chars.Add(info);
		getline(fs, str_buf, ',');
		if (str_buf == "") break; // 만약 한칸 더 불러오면 바로 종료
		info.m_char = str_buf.c_str();
		getline(fs, str_buf, ',');
		info.m_type = stoi(str_buf);
		getline(fs, str_buf, ',');
		info.m_sheet = stoi(str_buf);
		getline(fs, str_buf, ',');
		info.m_sx = stoi(str_buf);
		getline(fs, str_buf, ',');
		info.m_sy = stoi(str_buf);
		getline(fs, str_buf, ',');
		info.m_line = stoi(str_buf);
		getline(fs, str_buf, ',');
		info.m_order = stoi(str_buf);
		getline(fs, str_buf, ',');
		info.m_width = stoi(str_buf);
		getline(fs, str_buf);
		info.m_height = stoi(str_buf);
	} 
	fs.close();
	m_nChar = m_Chars.GetSize() - 1;
	for (int i = 1; i < m_nChar; i++)
	{
		m_nSheet = max(m_Chars.GetAt(i).m_sheet, m_Chars.GetAt(i + 1).m_sheet); // 제일 큰 값이 장의 수
	}
	return TRUE;
}
//CSV 파일 찾기 오류 시
void CMy00TermProjectView::CSVError()
{
	for (int i = m_spin_type.GetRange(); i >= 0; i--)
	{
		m_list.DeleteItem(i);
	}
	m_spin_sheet.SetRange(0, 0);
	m_spin_type.SetRange(0, 0);
	m_spin_sheet.SetPos(0);
	m_spin_type.SetPos(0);
	m_static_type.SetWindowText(_T("/ 0개"));
	m_static_sheet.SetWindowText(_T("/ 0개"));
	m_text_char.SetWindowText(_T("..."));
	m_text_info.SetWindowText(_T("..."));
	m_edit_bookname.SetWindowText(_T(""));
	m_book_text.SetWindowText(_T("0"));
	m_book_type.SetWindowText(_T("0"));
	m_book_kind.SetWindowText(_T("0"));
	m_sheet_text.SetWindowText(_T("0"));
	m_sheet_type.SetWindowText(_T("0"));
	m_sheet_kind.SetWindowText(_T("0"));
	Print_3D(NULL);
	search = 0;
	Invalidate();
}
// CMy00TermProjectView 메시지 처리기
CTypeDB::CTypeDB()
{
	m_nSheet = 0;
	m_nChar = 0;
}

CTypeDB::~CTypeDB()
{
}
// 폴더 수 계산 알고리즘
int CMy00TermProjectView::Find_kind(LPCTSTR pstr, bool mode = 0)
{
	CFileFind finder;
	int cnt_folder = 0;
	CString strWildcard(pstr);
	strWildcard += _T("/*");
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			cnt_folder++;
		}
	}
	finder.Close();
	return cnt_folder;
}
// 폴더 속 폴더 개수 찾는 알고리즘, 동일한 활자 수 찾기
int CMy00TermProjectView::Find_type(LPCTSTR pstr)
{
	CFileFind finder;
	int cnt_folder = 0;
	CString strWildcard(pstr);
	strWildcard += _T("/*");
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			cnt_folder++;
			cnt_folder = cnt_folder + Find_type(str);
		}
	}
	finder.Close();
	return cnt_folder;
}
//폴더 속 폴더인데 활자 수 세는 것도 추가
int CMy00TermProjectView::Find_type_sheet(LPCTSTR pstr, int num)
{
	CFileFind finder;
	
	CString strWildcard(pstr);
	strWildcard += _T("/*");
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			Find_type_sheet(str, num);
		} 
		else
		{
			CString type = finder.GetFileName();
			CString compare;
			compare.Format(_T("%d"), num);
			if (type.Left(2) == compare + _T("_"))
				cnt_file++;
		}
	}
	finder.Close();
	return cnt_file;
}
// 폴더 속 폴더 원하는 이미지 경로 찾는 알고리즘
void CMy00TermProjectView::Find_Img_Path(int sheet_num, LPCTSTR pstr, CString sx = 0, CString sy = 0)
{
	CFileFind finder;
	CString strWildcard(pstr), path, sheet_path;
	sheet_path.Format(_T("%d"), sheet_num);
	strWildcard += _T("/*");
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			Find_Img_Path(sheet_num, str, sx, sy);
		}
		else {
			CString img_name = finder.GetFileName();
			if (img_name.Right(15) == sheet_path + _T("_") + sx + _T("_") + sy + _T(".png")) {
				img_path = finder.GetFilePath();
			}else if (img_name.Right(16) == sheet_path + _T("_") + sx + _T("_") + sy + _T(".png")) {
				img_path = finder.GetFilePath();
			}
			else if (img_name.Right(5) ==  sheet_path + _T(".jpg")) {
				img_path = finder.GetFilePath();
			}
		}
	}
	finder.Close();
}
char* ConvertUnicodeToMultybyte(CString strUnicode)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);

	char* pMultibyte = new char[nLen];
	memset(pMultibyte, 0x00, (nLen) * sizeof(char));

	WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, pMultibyte, nLen, NULL, NULL);
	return pMultibyte;
}
//이미지 불러오기 알고리즘, sheet_num으로 장 번호만 불러온다.
void CMy00TermProjectView::Draw_Img(int sheet_num)
{
	
	//초기값 경로 불러오기
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	CString f_path(chFilePath);
	f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title;
	CString path_3d; // vtk 출력용
	path_3d = f_path.Left(f_path.ReverseFind(setting));
	CString book_text, sheet, book_kind, book_type;
	CString sheet_text, sheet_kind, sheet_type;
	CString str;
	CClientDC dc(this);

	CDC dcmem;
	CBitmap bm_main, bm_text, bm_type;
	CString str_sheet, str_line, str_order;
	WINDOWPLACEMENT placement;

	// 메인 그림 띄우기
	m_main_pic.GetWindowPlacement(&placement);
	dcmem.CreateCompatibleDC(&dc);
	bm_main.CreateCompatibleBitmap(&dc, 9921, 7015);
	dcmem.SelectObject(bm_main);
	Graphics gr(dcmem);
	Find_Img_Path(sheet_num ,f_path, 0, 0);
	Image* pImg = ::new Image(img_path);
	gr.DrawImage(pImg, 0, 0, pImg->GetWidth() / main_img_y, pImg->GetHeight() / main_img_x);
	Pen pen_green(Color(255, 0, 255, 0), 1);
	Pen pen_red(Color(255, 255, 0, 0), 1);
	for (int i = 1; i < data.m_Chars.GetSize(); i++)
	{
		if (data.m_Chars.GetAt(i).m_sheet == sheet_num) {
			if (data.m_Chars.GetAt(i).m_line == 1 && data.m_Chars.GetAt(i).m_order == 1) {
				gr.DrawRectangle(&pen_red, data.m_Chars.GetAt(i).m_sx / main_img_y, data.m_Chars.GetAt(i).m_sy / main_img_x, data.m_Chars.GetAt(i).m_width / main_img_y, data.m_Chars.GetAt(i).m_height / main_img_x);
				m_text_char.SetWindowText(data.m_Chars.GetAt(i).m_char);
				str_sheet.Format(_T("%d"), data.m_Chars.GetAt(i).m_sheet);
				str_line.Format(_T("%d"), data.m_Chars.GetAt(i).m_line);
				str_order.Format(_T("%d"), data.m_Chars.GetAt(i).m_order);
				type_folder.Format(_T("%d"), data.m_Chars.GetAt(i).m_type);
				m_text_char.SetWindowText(data.m_Chars.GetAt(i).m_char);
				m_text_info.SetWindowText(str_sheet + _T("장 ") + str_line + _T("행 ") + str_order + _T("번 "));
			}
			else {
				gr.DrawRectangle(&pen_green, data.m_Chars.GetAt(i).m_sx / main_img_y, data.m_Chars.GetAt(i).m_sy / main_img_x, data.m_Chars.GetAt(i).m_width / main_img_y, data.m_Chars.GetAt(i).m_height / main_img_x);
			}
		}
	}
	dc.BitBlt(placement.rcNormalPosition.left, placement.rcNormalPosition.top, pImg->GetWidth() / main_img_y, pImg->GetHeight() / main_img_x, &dcmem, 0, 0, SRCCOPY);
	dcmem.DeleteDC();
	bm_main.DeleteObject();
	// 글자 정보 그림
	m_pic_info.GetWindowPlacement(&placement);
	dcmem.CreateCompatibleDC(&dc);
	bm_text.CreateCompatibleBitmap(&dc, 128, 128);
	dcmem.SelectObject(bm_text);
	Graphics gr2(dcmem);
	CString init_sx, init_sy, init_char, init_type; // 메인 그림의 1번째 글자의 sx, sy, type
	for (int i = 1; i < data.m_Chars.GetSize(); i++)
	{
		if (data.m_Chars.GetAt(i).m_sheet == sheet_num) {
			if (data.m_Chars.GetAt(i).m_line == 1 && data.m_Chars.GetAt(i).m_order == 1) {
				init_sx.Format(_T("%d"), data.m_Chars.GetAt(i).m_sx);
				init_sy.Format(_T("%d"), data.m_Chars.GetAt(i).m_sy);
				init_char = data.m_Chars.GetAt(i).m_char;
				init_type.Format(_T("%d"), data.m_Chars.GetAt(i).m_type);
			}
		}
	}
	Find_Img_Path(sheet_num, f_path, init_sx, init_sy);
	Image* pImg2 = ::new Image(img_path);
	gr2.DrawImage(pImg2, 0, 0, pImg2->GetWidth() / sub_img, pImg2->GetHeight() / sub_img);
	dc.BitBlt(placement.rcNormalPosition.left, placement.rcNormalPosition.top, pImg2->GetWidth() / sub_img, pImg2->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);
	dcmem.DeleteDC();
	bm_text.DeleteObject();
	// 활자 정보 그림
	m_pic_type.GetWindowPlacement(&placement);
	dcmem.CreateCompatibleDC(&dc);
	bm_type.CreateCompatibleBitmap(&dc, 128, 128);
	dcmem.SelectObject(bm_type);
	Graphics gr3(dcmem);

	Image* pImg3 = ::new Image(img_path);
	gr3.DrawImage(pImg3, 0, 0, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img);
	
	dc.BitBlt(placement.rcNormalPosition.left, placement.rcNormalPosition.top, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);
	dcmem.DeleteDC();
	bm_type.DeleteObject();

	//VTK 띄우기
	path_3d = path_3d + _T("04_3d/") + init_char + _T("_") + init_type + _T(".stl");
	char* pMultibyte = ConvertUnicodeToMultybyte(path_3d);
	Print_3D(pMultibyte);
	delete(pMultibyte);
}
int compare_ary(CString a, CString b) // name_ary용
{
	return a < b;
}
int compare_list(CString a, CString b) // name_list용
{
	if (a.Left(2).Right(1) == '_')
		a = _T("0") + a.Left(1);
	else a = a.Left(2);
	if (b.Left(2).Right(1) == '_')
		b = _T("0") + b.Left(1);
	else b = b.Left(2);
	return a < b;
}
// 동일 활자 수 파악하기 및 활자 순서 출력 + 리스트 다루기
void CMy00TermProjectView::TypeBox(CString id, int type, int sheet_num = 0)
{
	int count = m_list.GetItemCount(); //리스트 컨트롤의 모든 항목 수를 얻어옵니다.
	for (int i = count; i >= 0; i--)
	{
		m_list.DeleteItem(i); // 리스트 컨트롤 초기화하기
	}
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	CString f_path(chFilePath), str_type, str_sheet;
	str_sheet.Format(_T("%d"), sheet_num);
	str_type.Format(_T("%d"), type);
	f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title;
	vector<CString> name_ary, name_list;
	CFileFind finder;
	CString strWildcard(f_path);
	strWildcard += _T("/03_type/") + id + _T("/") + str_type;
	BOOL bWorking = finder.FindFile(strWildcard + _T("/*"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots() || finder.IsDirectory())
			continue;
		CString img_name = finder.GetFileName(), temp; // 폴더를 제외한 이미지 파일이 나올 시
		temp = img_name;
		// 몇번째 활자인지 확인(소팅을 사용함)
		if (img_name.Left(2).Right(1) == '_')
			img_name = _T("0") + img_name.Left(1);
		else img_name = img_name.Left(2);
		name_list.push_back(temp);
		name_ary.push_back(img_name);
	}
	finder.Close();
	
	sort(name_ary.begin(), name_ary.end(), compare_ary);
	sort(name_list.begin(), name_list.end(), compare_list);

	//구성 리스트 작성
	for (int i = 0; i < name_ary.size(); i++)
	{
		if (name_ary.at(i).Left(1) == _T("0"))
			name_ary.at(i) = name_ary.at(i).Right(1);
		m_list.InsertItem(m_list.GetItemCount(), name_ary.at(i));
		m_list.SetItemText(i, 1, name_list.at(i).Right(13).Left(4));
		m_list.SetItemText(i, 2, name_list.at(i).Right(8).Left(4));
	}
}
// 활자 정보 스핀 컨트롤 다루기
void CMy00TermProjectView::TypeInfo(CString id, int sheet_num, int type_num)
{
	int cnt_type = 0; // 스핀 컨트롤 최댓값
	int type = 0;
	int spin_type = 0; // 현재 선택한 활자 번호
	SCharInfo info;
	type_info.RemoveAll();// 초기화
	//폴더 불러오기
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	CString f_path(chFilePath);
	f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title;

	for (int i = 1; i < data.m_Chars.GetSize(); i++)
	{
		if (data.m_Chars.GetAt(i).m_char == id && data.m_Chars.GetAt(i).m_sheet == sheet_num)
		{
			cnt_type++;
			type++;
			info.m_char = data.m_Chars.GetAt(i).m_char;
			info.m_height = data.m_Chars.GetAt(i).m_height;
			info.m_line = data.m_Chars.GetAt(i).m_line;
			info.m_order = data.m_Chars.GetAt(i).m_order;
			info.m_sheet = data.m_Chars.GetAt(i).m_sheet;
			info.m_sx = data.m_Chars.GetAt(i).m_sx;
			info.m_sy = data.m_Chars.GetAt(i).m_sy;
			info.m_type = data.m_Chars.GetAt(i).m_type;
			info.m_width = data.m_Chars.GetAt(i).m_width;
			type_info.Add(info);
			if (data.m_Chars.GetAt(i).m_type == type_num)
			{
				spin_type = type;
			}
		}
	}
	CString str_cnt_type;
	str_cnt_type.Format(_T(" /%d개"), cnt_type);
	m_static_type.SetWindowText(str_cnt_type);
	m_spin_type.SetRange(1, cnt_type);
	m_spin_type.SetPos(spin_type);
}

void CMy00TermProjectView::OnBnClickedButtonOpen()
 {
	//이전 데이터 초기화
	data.m_Chars.RemoveAll();
	data.m_nSheet = 0;
	data.m_nChar = 0;
	type_info.RemoveAll();
	//대화상자 띄우기
	CMyDialog dlg;
	dlg.title = title;
	int result = dlg.DoModal();
	if (result == IDOK) {
		title = dlg.title;
		m_edit_bookname.SetWindowText(dlg.title);
	}
	BeginWaitCursor(); // 실행시간이 길 때, 마우스 커서 모래시계
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cnt_file = 0;
	search = 1;
	//현재 프로젝트 경로만 가져오기
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	CString f_path(chFilePath);
	f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title;
	CString book_text, book_kind, book_type;
	CString sheet_text, sheet_kind, sheet_type;
	CString str, sheet, type;

	if (!data.ReadCSVFile(f_path + _T("/typeDB.csv"))) {
		CSVError();
		return;
	}
	// 스핀 컨트롤 건들기
	m_spin_sheet.SetRange(1, data.m_nSheet);
	m_spin_sheet.SetPos(1);
	// 스핀 끝
	// 여기부터는 책 전부에 대한 내용입니당
	//한글 총 글자 수 파악
	book_text.Format(_T("%d"), data.m_nChar);
	m_book_text.SetWindowText(book_text);
	// 장 수 파악
	sheet.Format(_T("/ %d장"), data.m_nSheet);
	m_static_sheet.SetWindowText(sheet);
	// 활자 종류 수 파악
	for (int i = 1; i < data.m_Chars.GetSize(); i++)
	{
		if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
			if (data.m_Chars.GetAt(i).m_line == 1 && data.m_Chars.GetAt(i).m_order == 1) {
				TypeBox(data.m_Chars.GetAt(i).m_char, data.m_Chars.GetAt(i).m_type);
				TypeInfo(data.m_Chars.GetAt(i).m_char, data.m_Chars.GetAt(i).m_sheet, data.m_Chars.GetAt(i).m_type);
			}
		}
	}
	int book_kind_num = Find_kind(f_path + _T("/03_type"));
	book_kind.Format(_T("%d"), book_kind_num);
	m_book_kind.SetWindowText(book_kind);
	// 한글 활자 수 계산 알고리즘
	int book_type_num = 0;
	f_path = f_path + _T("/03_type");
	book_type_num = Find_type(f_path) - book_kind_num; 
	// 03_type 안에 있는 전체 폴더 수 - 글자 종류 수 = 513 - 183 = 330
	book_type.Format(_T("%d"), book_type_num);
	m_book_type.SetWindowText(book_type);
	// 여기 부터는 장에 대한 내용입니다
	// 한글 총 글자 수
	int sheet_text_num = 0;
	for (int i = 1; i < data.m_Chars.GetSize(); i++)
	{
		if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos())
			sheet_text_num++;
	}
	sheet_text.Format(_T("%d"), sheet_text_num);
	m_sheet_text.SetWindowText(sheet_text);
	// 알고리즘 끝
	//한글 글자 종류 계산 알고리즘(CSV폴더 안의 정보를 사용한다.)
	bool chk_sheet_kind[3000] = { false, };
	int sheet_kind_num = 0;
	for (int i = 1; i < data.m_Chars.GetSize(); i++)
	{
		if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
			if (chk_sheet_kind[i]) continue;
			sheet_kind_num++;

			for (int j = i; j < data.m_Chars.GetSize(); j++)
			{
				if (data.m_Chars.GetAt(i).m_char == data.m_Chars.GetAt(j).m_char)	chk_sheet_kind[j] = true;
			}
		}
	}
	sheet_kind.Format(_T("%d"), sheet_kind_num);
	m_sheet_kind.SetWindowText(sheet_kind);
	// 여기까지 알고리즘 끝
	// 한글 활자 종류
	int sheet_type_num = Find_type_sheet(f_path, m_spin_sheet.GetPos());
	sheet_type.Format(_T("%d"), sheet_type_num);
	m_sheet_type.SetWindowText(sheet_type);
	//책 그림 띄우기
	Draw_Img(m_spin_sheet.GetPos());
	EndWaitCursor();
}

void CMy00TermProjectView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (search) {
		// 장번호 스핀 컨트롤을 건들 시
		if (pScrollBar->GetSafeHwnd() == m_spin_sheet.GetSafeHwnd()) { 
			BeginWaitCursor(); // 실행시간이 길 때, 마우스 커서 모래시계
			CString sheet_text, sheet_kind, sheet_type;
			// 다시 불러오기
			TCHAR chFilePath[256] = { 0, };
			GetModuleFileName(NULL, chFilePath, 256);
			CString f_path(chFilePath);
			f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title;
			// 여기 부터는 장에 대한 내용입니다
			// 한글 총 글자 수
			int sheet_text_num = 0;

			for (int i = 1; i < data.m_Chars.GetSize(); i++)
			{
				if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos())
					sheet_text_num++;
			}
			sheet_text.Format(_T("%d"), sheet_text_num);
			m_sheet_text.SetWindowText(sheet_text);
			// 알고리즘 끝
			//한글 글자 종류 계산 알고리즘
			bool chk_sheet_kind[3000] = { false, };
			int sheet_kind_num = 0;
			for (int i = 1; i < data.m_Chars.GetSize(); i++)
			{
				if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
					if (chk_sheet_kind[i]) continue;
					sheet_kind_num++;

					for (int j = i; j < data.m_Chars.GetSize(); j++)
					{
						if (data.m_Chars.GetAt(i).m_char == data.m_Chars.GetAt(j).m_char)	chk_sheet_kind[j] = true;
					}
				}
			}
			sheet_kind.Format(_T("%d"), sheet_kind_num);
			m_sheet_kind.SetWindowText(sheet_kind);
			// 여기까지 알고리즘 끝
			// 한글 활자 종류
			cnt_file = 0;
			int sheet_type_num = Find_type_sheet(f_path + _T("/03_type"), m_spin_sheet.GetPos());
			sheet_type.Format(_T("%d"), sheet_type_num);
			m_sheet_type.SetWindowText(sheet_type);
			// 활자 종류 수 파악
			CString type;
			for (int i = 1; i < data.m_Chars.GetSize(); i++)
			{
				if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
					if (data.m_Chars.GetAt(i).m_line == 1 && data.m_Chars.GetAt(i).m_order == 1) {
						TypeBox(data.m_Chars.GetAt(i).m_char, data.m_Chars.GetAt(i).m_type);
						TypeInfo(data.m_Chars.GetAt(i).m_char, data.m_Chars.GetAt(i).m_sheet, data.m_Chars.GetAt(i).m_type);
					}
				}
			}
			//이미지 다시 불러오기
			Draw_Img(m_spin_sheet.GetPos());
			EndWaitCursor();
		}
		// 활자 정보 스핀 컨트롤을 건들 시
		else if (pScrollBar->GetSafeHwnd() == m_spin_type.GetSafeHwnd()) {
			CString str_sheet, str_line, str_order, str_sx, str_sy, str_char; // 사진 찾기
			CString c_char, c_type; // vtk용
			int num = m_spin_type.GetPos() - 1; // 스핀 컨트롤 번호
			//글자 정보 갱신
			str_sheet.Format(_T("%d"), type_info.GetAt(num).m_sheet);
			str_line.Format(_T("%d"), type_info.GetAt(num).m_line);
			str_order.Format(_T("%d"), type_info.GetAt(num).m_order);
			m_text_info.SetWindowText(str_sheet + _T("장 ") + str_line + _T("행 ") + str_order + _T("번 "));
			// 이미지 설정
			CClientDC dc(this);
			Graphics gr_sel(dc), gr(dc);
			Pen pen_red(Color(255, 255, 0, 0), 1);
			Pen pen_green(Color(255, 0, 255, 0), 1);
			CDC dcmem;
			CBitmap bm_text, bm_type;
			TCHAR chFilePath[256] = { 0, };
			GetModuleFileName(NULL, chFilePath, 256);
			CString f_path(chFilePath);
			f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title; // app이 있는 debug파일로 가기에 그 전에 끊어준다.
			CString path_3d; // vtk 출력용
			path_3d = f_path.Left(f_path.ReverseFind(setting));
			//위치 정해주기
			WINDOWPLACEMENT placement;
			m_main_pic.GetWindowPlacement(&placement);
			// 바운더리 박스 갱신
			for (int i = 1; i < data.m_Chars.GetSize(); i++)
			{
				if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
					gr.DrawRectangle(&pen_green, placement.rcNormalPosition.left + data.m_Chars.GetAt(i).m_sx / main_img_y,
						placement.rcNormalPosition.top + data.m_Chars.GetAt(i).m_sy / main_img_x,
						data.m_Chars.GetAt(i).m_width / main_img_y, data.m_Chars.GetAt(i).m_height / main_img_x);
				}
			}
			gr_sel.DrawRectangle(&pen_red, placement.rcNormalPosition.left + type_info.GetAt(num).m_sx / main_img_y,
				placement.rcNormalPosition.top + type_info.GetAt(num).m_sy / main_img_x,
				type_info.GetAt(num).m_width / main_img_y, type_info.GetAt(num).m_height / main_img_x);
			str_sx.Format(_T("%d"), type_info.GetAt(num).m_sx);
			str_sy.Format(_T("%d"), type_info.GetAt(num).m_sy);
			type_folder.Format(_T("%d"), type_info.GetAt(num).m_type);
			c_char = type_info.GetAt(num).m_char;
			c_type = type_folder;
			// 글자 정보 리스트 갱신
			TypeBox(type_info.GetAt(num).m_char, type_info.GetAt(num).m_type);
			// 이미지 갱신
			m_pic_info.GetWindowPlacement(&placement);
			dcmem.CreateCompatibleDC(&dc);
			bm_text.CreateCompatibleBitmap(&dc, 128, 128);
			dcmem.SelectObject(bm_text);
			Graphics gr2(dcmem);
			//다시 경로 찾기
			Find_Img_Path(m_spin_sheet.GetPos(), f_path, str_sx, str_sy);
			//글자 정보 그림
			Image* pImg2 = ::new Image(img_path);
			gr2.DrawImage(pImg2, 0, 0, pImg2->GetWidth() / sub_img, pImg2->GetHeight() / sub_img);
			dc.BitBlt(placement.rcNormalPosition.left + 1, placement.rcNormalPosition.top + 1, pImg2->GetWidth() / sub_img, pImg2->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);
			dcmem.DeleteDC();
			bm_text.DeleteObject();
			// 활자 정보 그림
			m_pic_type.GetWindowPlacement(&placement);
			dcmem.CreateCompatibleDC(&dc);
			bm_type.CreateCompatibleBitmap(&dc, 128, 128);
			dcmem.SelectObject(bm_type);
			Graphics gr3(dcmem);
			Image* pImg3 = ::new Image(img_path);
			gr3.DrawImage(pImg3, 0, 0, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img);
			dc.BitBlt(placement.rcNormalPosition.left, placement.rcNormalPosition.top, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);
			dcmem.DeleteDC();
			bm_type.DeleteObject();
			//vtk
			path_3d = path_3d + _T("04_3d/") + c_char + _T("_") + c_type + _T(".stl");
			char* pMultibyte = ConvertUnicodeToMultybyte(path_3d);
			Print_3D(pMultibyte);
			delete(pMultibyte);
		}
	}
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMy00TermProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (search) {
		CClientDC dc(this);
		dc.DPtoLP(&point); // 장치 좌표를 논리 좌표로 변환한다.
		CString str_sheet, str_line, str_order, str_sx, str_sy, str_char; // 사진 찾기
		CString type;
		CString c_char, c_type;
		int int_type;
		Graphics gr_sel(dc), gr(dc);
		Pen pen_red(Color(255, 255, 0, 0), 1);
		Pen pen_green(Color(255, 0, 255, 0), 1);
		CDC dcmem;
		CBitmap bm_text, bm_type;
		TCHAR chFilePath[256] = { 0, };
		GetModuleFileName(NULL, chFilePath, 256);
		CString f_path(chFilePath);
		f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title; // app이 있는 debug파일로 가기에 그 전에 끊어준다.
		CString path_3d; // vtk 출력용
		path_3d = f_path.Left(f_path.ReverseFind(setting));
		//위치 정해주기
		WINDOWPLACEMENT placement;
		m_main_pic.GetWindowPlacement(&placement);
		for (int i = 1; i < data.m_Chars.GetSize(); i++)
		{
			if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
				if (point.x >= placement.rcNormalPosition.left + data.m_Chars.GetAt(i).m_sx / main_img_y
					&& point.y >= placement.rcNormalPosition.top + data.m_Chars.GetAt(i).m_sy / main_img_x
					&& point.x <= placement.rcNormalPosition.left + data.m_Chars.GetAt(i).m_sx / main_img_y + data.m_Chars.GetAt(i).m_width / main_img_y
					&& point.y <= placement.rcNormalPosition.top + data.m_Chars.GetAt(i).m_sy / main_img_x + data.m_Chars.GetAt(i).m_height / main_img_x)
				{
					for (int i = 1; i < data.m_Chars.GetSize(); i++)
					{
						if (data.m_Chars.GetAt(i).m_sheet == m_spin_sheet.GetPos()) {
							gr.DrawRectangle(&pen_green, placement.rcNormalPosition.left + data.m_Chars.GetAt(i).m_sx / main_img_y,
								placement.rcNormalPosition.top + data.m_Chars.GetAt(i).m_sy / main_img_x,
								data.m_Chars.GetAt(i).m_width / main_img_y, data.m_Chars.GetAt(i).m_height / main_img_x);
						}
					}
					//마우스가 범위 안에 왔을 때 코드
					gr_sel.DrawRectangle(&pen_red, placement.rcNormalPosition.left + data.m_Chars.GetAt(i).m_sx / main_img_y,
						placement.rcNormalPosition.top + data.m_Chars.GetAt(i).m_sy / main_img_x,
						data.m_Chars.GetAt(i).m_width / main_img_y, data.m_Chars.GetAt(i).m_height / main_img_x);
					str_sx.Format(_T("%d"), data.m_Chars.GetAt(i).m_sx);
					str_sy.Format(_T("%d"), data.m_Chars.GetAt(i).m_sy);
					str_sheet.Format(_T("%d"), data.m_Chars.GetAt(i).m_sheet);
					str_line.Format(_T("%d"), data.m_Chars.GetAt(i).m_line);
					str_order.Format(_T("%d"), data.m_Chars.GetAt(i).m_order);
					type_folder.Format(_T("%d"), data.m_Chars.GetAt(i).m_type);
					c_char = data.m_Chars.GetAt(i).m_char;
					c_type = type_folder;
					str_char = data.m_Chars.GetAt(i).m_char;
					int_type = data.m_Chars.GetAt(i).m_type;
					TypeBox(data.m_Chars.GetAt(i).m_char, data.m_Chars.GetAt(i).m_type);
					TypeInfo(data.m_Chars.GetAt(i).m_char, data.m_Chars.GetAt(i).m_sheet, data.m_Chars.GetAt(i).m_type);
					m_text_char.SetWindowText(data.m_Chars.GetAt(i).m_char);
					m_text_info.SetWindowText(str_sheet + _T("장 ") + str_line + _T("행 ")+ str_order + _T("번 "));
					m_pic_info.GetWindowPlacement(&placement);
					dcmem.CreateCompatibleDC(&dc);
					bm_text.CreateCompatibleBitmap(&dc, 128, 128);
					dcmem.SelectObject(bm_text);
					Graphics gr2(dcmem);
					//다시 경로 찾기
					Find_Img_Path(m_spin_sheet.GetPos(),f_path, str_sx, str_sy);
					Image* pImg2 = ::new Image(img_path);
					gr2.DrawImage(pImg2, 0, 0, pImg2->GetWidth() / sub_img, pImg2->GetHeight() / sub_img);
					dc.BitBlt(placement.rcNormalPosition.left +1, placement.rcNormalPosition.top +1, pImg2->GetWidth() / sub_img, pImg2->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);
					dcmem.DeleteDC();
					bm_text.DeleteObject();
					// 활자 정보 그림
					m_pic_type.GetWindowPlacement(&placement);
					dcmem.CreateCompatibleDC(&dc);
					bm_type.CreateCompatibleBitmap(&dc, 128, 128);
					dcmem.SelectObject(bm_type);
					Graphics gr3(dcmem);

					Image* pImg3 = ::new Image(img_path);
					gr3.DrawImage(pImg3, 0, 0, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img);

					dc.BitBlt(placement.rcNormalPosition.left, placement.rcNormalPosition.top, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);
					dcmem.DeleteDC();
					bm_type.DeleteObject();

					//VTK
					path_3d = path_3d + _T("04_3d/") + c_char + _T("_") + c_type + _T(".stl");
					char* pMultibyte = ConvertUnicodeToMultybyte(path_3d);
					Print_3D(pMultibyte);
					delete(pMultibyte);
				}
			}
		}
		CFormView::OnLButtonDown(nFlags, point);
	}
}

void CMy00TermProjectView::OnNMClickListChars(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (search) {
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
		int index = pNMView->iItem;
		// 활자 정보 그림
		CClientDC dc(this);
		CDC dcmem;
		CBitmap bm_type;
		WINDOWPLACEMENT placement;
		m_pic_type.GetWindowPlacement(&placement);
		dcmem.CreateCompatibleDC(&dc);
		bm_type.CreateCompatibleBitmap(&dc, 128, 128);
		dcmem.SelectObject(bm_type);
		Graphics gr3(dcmem);
		TCHAR chFilePath[256] = { 0, };
		GetModuleFileName(NULL, chFilePath, 256);
		CString f_path(chFilePath);
		f_path = f_path.Left(f_path.ReverseFind(setting)) + _T("책/") + title; // app이 있는 debug파일로 가기에 그 전에 끊어준다.
		CString path_3d; // vtk 출력용
		path_3d = f_path.Left(f_path.ReverseFind(setting));
		CString c_char, c_type;
		CString str;
		m_text_char.GetWindowText(str);
		f_path = f_path + _T("/03_type/") + str + _T("/") + type_folder + _T("/") + m_list.GetItemText(index, 0)
			+ _T("_") + m_list.GetItemText(index, 1) + _T("_") + m_list.GetItemText(index, 2) + _T(".png");
		Image* pImg3 = ::new Image(f_path);
		gr3.DrawImage(pImg3, 0, 0, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img);

		dc.BitBlt(placement.rcNormalPosition.left, placement.rcNormalPosition.top, pImg3->GetWidth() / sub_img, pImg3->GetHeight() / sub_img, &dcmem, 0, 0, SRCCOPY);

		dcmem.DeleteDC();
		bm_type.DeleteObject();
		//VTK
		c_type = type_folder;
		c_char = str;
		path_3d = path_3d + _T("04_3d/") + c_char + _T("_") + c_type + _T(".stl");
		char* pMultibyte = ConvertUnicodeToMultybyte(path_3d);
		Print_3D(pMultibyte);
		delete(pMultibyte);
	}
	*pResult = 0;
}

void CMy00TermProjectView::OnBnClickedButtonKorea()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInfoDialog dlg;
	int result = dlg.DoModal();
	if (result == IDCANCEL) {
		MessageBox(_T("응용프로그래밍 고생하셨습니다!!!"));
	}
}
