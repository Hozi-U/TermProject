
// 00TermProjectView.h: CMy00TermProjectView 클래스의 인터페이스
//

#pragma once
struct SCharInfo {
	CString m_char;
	int m_type;
	int m_sheet;
	int m_sx;
	int m_sy;
	int m_line;
	int m_order;
	int m_width;
	int m_height;
};


class CTypeDB
{
public:
	int m_nSheet;
	int m_nChar;
	CArray<SCharInfo, SCharInfo&> m_Chars;
	BOOL ReadCSVFile(CString str);
	CTypeDB();
	~CTypeDB();
};
class CMy00TermProjectView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMy00TermProjectView() noexcept;
	DECLARE_DYNCREATE(CMy00TermProjectView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY00TERMPROJECT_FORM };
#endif

// 특성입니다.
public:
	
	CMy00TermProjectDoc* GetDocument() const;
	bool search = 0; // 책을 불러오면 동작하도록 설정한다.
	int cnt_file;
	CString type_folder; // 타입 폴더명
// 작업입니다.
public:
	// 책 정보 저장
	CTypeDB data;
	//vtk용
	vtkSmartPointer<vtkRenderWindow> m_vtkWindow;
	void InitVtkWindow(void* hWnd);
	void ResizeVtkWindow();
	void Print_3D(char* path); // 3D 출력
	//GDI+용
	ULONG_PTR g_GdiPulsTokenData;
	//한글 총 종류 수 파악
	int CMy00TermProjectView::Find_kind(LPCTSTR pstr, bool mode);
	//한글 총 활자 수 파악(폴더 수)
	int Find_type(LPCTSTR pstr);
	//한글 장 활자 수 파악
	int CMy00TermProjectView::Find_type_sheet(LPCTSTR pstr, int num);
	// 폴더 속 폴더 원하는 이미지 찾는 알고리즘
	void CMy00TermProjectView::Find_Img_Path(int sheet_num, LPCTSTR pst, CString sx, CString sy);
	CString img_path;
	CString title; // 책 제목
	// 이미지 불러오기 알고리즘
	void CMy00TermProjectView::Draw_Img(int sheet_num);
	// 동일 활자 수 파악하기 + 리스트 다루기
	void CMy00TermProjectView::TypeBox(CString id, int type, int sheet_num);
	// CSV 찾기 오류 시
	void CMy00TermProjectView::CSVError();
	// 활자 정보 스핀 컨트롤 갱신하기
	void CMy00TermProjectView::TypeInfo(CString id, int sheet_num, int type_num);
	CArray<SCharInfo, SCharInfo&> type_info;
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy00TermProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButtonOpen();
	CStatic m_book_text;
	CStatic m_book_kind;
	CStatic m_static_sheet;
	CStatic m_book_type;
	CStatic m_sheet_text;
	CStatic m_sheet_kind;
	CStatic m_sheet_type;
	CSpinButtonCtrl m_spin_sheet;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_main_pic;
	CStatic m_pic_info;
	CStatic m_pic_type;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CStatic m_text_char;
	CStatic m_text_info;
	CSpinButtonCtrl m_spin_type;
	CListCtrl m_list;
	afx_msg void OnNMClickListChars(NMHDR* pNMHDR, LRESULT* pResult);
	CStatic m_static_type;
	CEdit m_edit_bookname;
	CBitmapButton m_find;
	CBitmapButton m_koreatech;
	afx_msg void OnBnClickedButtonKorea();
};

#ifndef _DEBUG  // 00TermProjectView.cpp의 디버그 버전
inline CMy00TermProjectDoc* CMy00TermProjectView::GetDocument() const
   { return reinterpret_cast<CMy00TermProjectDoc*>(m_pDocument); }
#endif

