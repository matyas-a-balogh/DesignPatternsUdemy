
// AdapterVisualDlg.h : header file
// we added geometry.h to hacve lines, not just points

#pragma once
#include <vector>
#include "Geometry.h"

// CAdapterVisualDlg dialog
class CAdapterVisualDlg : public CDialogEx
{
// Construction
public:
	CAdapterVisualDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADAPTERVISUAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

  void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end)
  {
    for (auto i = start; i != end; ++i)
      // this is good, but what if i dont have points
      dc.SetPixel(i->x, i->y, 0);
  }

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
