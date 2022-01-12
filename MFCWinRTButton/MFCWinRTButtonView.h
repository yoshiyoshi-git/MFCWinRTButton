
// MFCWinRTButtonView.h : CMFCWinRTButtonView クラスのインターフェイス
//

#pragma once


class CMFCWinRTButtonView : public CView
{
	//XamlSourceの追加
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;

protected: // シリアル化からのみ作成します。
	CMFCWinRTButtonView() noexcept;
	DECLARE_DYNCREATE(CMFCWinRTButtonView)

// 属性
public:
	CMFCWinRTButtonDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CMFCWinRTButtonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:

	//Revokerとイベントハンドラの追加
	winrt::Windows::UI::Xaml::Controls::Button::Click_revoker buttonRevoker;
	void OnXamlButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&);
};

#ifndef _DEBUG  // MFCWinRTButtonView.cpp のデバッグ バージョン
inline CMFCWinRTButtonDoc* CMFCWinRTButtonView::GetDocument() const
   { return reinterpret_cast<CMFCWinRTButtonDoc*>(m_pDocument); }
#endif

