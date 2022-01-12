
// MFCWinRTButtonView.cpp : CMFCWinRTButtonView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MFCWinRTButton.h"
#endif

#include "MFCWinRTButtonDoc.h"
#include "MFCWinRTButtonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCWinRTButtonView

IMPLEMENT_DYNCREATE(CMFCWinRTButtonView, CView)

BEGIN_MESSAGE_MAP(CMFCWinRTButtonView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCWinRTButtonView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCWinRTButtonView コンストラクション/デストラクション

CMFCWinRTButtonView::CMFCWinRTButtonView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CMFCWinRTButtonView::~CMFCWinRTButtonView()
{
}

BOOL CMFCWinRTButtonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CMFCWinRTButtonView 描画

void CMFCWinRTButtonView::OnDraw(CDC* /*pDC*/)
{
	CMFCWinRTButtonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CMFCWinRTButtonView の印刷


void CMFCWinRTButtonView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCWinRTButtonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CMFCWinRTButtonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMFCWinRTButtonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CMFCWinRTButtonView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCWinRTButtonView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCWinRTButtonView の診断

#ifdef _DEBUG
void CMFCWinRTButtonView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCWinRTButtonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCWinRTButtonDoc* CMFCWinRTButtonView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCWinRTButtonDoc)));
	return (CMFCWinRTButtonDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCWinRTButtonView メッセージ ハンドラー


int CMFCWinRTButtonView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ハンドルを取得
	auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();

	// ウインドウへアタッチ
	winrt::check_hresult(interop->AttachToWindow(this->m_hWnd));

	//XAML用のHWNDを取得
	HWND hWndXamlIsland = nullptr;
	interop->get_WindowHandle(&hWndXamlIsland);

	//ボタンの作成
	winrt::Windows::UI::Xaml::Controls::Button button;
	button.Content(winrt::box_value(winrt::hstring(L"Button")));

	//XAML contentの作成。ここにコントロールを追加して行きます
	winrt::Windows::UI::Xaml::Controls::StackPanel xamlContainer;

	//StackPanelへコントロール（ボタン）を登録して、StackPanelをXamlSourceへ追加
	xamlContainer.Children().Append(button);
	desktopSource.Content(xamlContainer);

	//イベントハンドラの登録
	buttonRevoker = button.Click(winrt::auto_revoke, { this, &CMFCWinRTButtonView::OnXamlButtonClick });

	//今回はウインドウの(0,0)～(500,500)の正方形の領域にXAMLを表示しています。
	//画面全体に表示させたい場合はGetWindowRectでウインドウの大きさを取得して,それを指定してください。
	//サイズ変更に対応する場合は、OnSize()を追加して、ハンドルを取得して、StackPanelの大きさを指定してください。
	::SetWindowPos(hWndXamlIsland, NULL, 0, 0, 500, 500, SWP_SHOWWINDOW);
	xamlContainer.UpdateLayout();

	return 0;
}

void CMFCWinRTButtonView::OnXamlButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
	auto msgdlg = winrt::Windows::UI::Popups::MessageDialog(L"Button Click!!");
	msgdlg.as<IInitializeWithWindow>()->Initialize(m_hWnd);
	msgdlg.Content(L"Button Click!!");
	msgdlg.ShowAsync();
}
