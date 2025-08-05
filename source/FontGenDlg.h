// ---------------------------------------------------------------------------------------------------------------------------------
//  ______             _    _____            _____  _           _     
// |  ____|           | |  / ____|          |  __ \| |         | |    
// | |__    ___  _ __ | |_| |  __  ___ _ __ | |  | | | __ _    | |__  
// |  __|  / _ \| '_ \| __| | |_ |/ _ \ '_ \| |  | | |/ _` |   | '_ \ 
// | |    | (_) | | | | |_| |__| |  __/ | | | |__| | | (_| | _ | | | |
// |_|     \___/|_| |_|\__|\_____|\___|_| |_|_____/|_|\__, |(_)|_| |_|
//                                                     __/ |          
//                                                    |___/           
//
// Font generation (from true-type fonts) utility
//
// Best viewed with 8-character tabs and (at least) 132 columns
//
// ---------------------------------------------------------------------------------------------------------------------------------
//
// Originally released under a custom license.
// This historical re-release is provided under the MIT License.
// See the LICENSE file in the repo root for details.
//
// https://github.com/nettlep
//
// ---------------------------------------------------------------------------------------------------------------------------------
// Originally created on 12/18/2000 by Paul Nettle
//
// Copyright 2000, Fluid Studios, Inc., all rights reserved.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef	_H_FONTGENDLG
#define	_H_FONTGENDLG

// -------------------------------------------------------------------------------------------------------------------------------

class	FontGenDlg : public CDialog
{
public:
				FontGenDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(FontGenDlg)
	enum { IDD = IDD_FONTGEN_DIALOG };
	CProgressCtrl	progressControl;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(FontGenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
		enum		{FONT_MAX_SIZE = 256};

		HICON		m_hIcon;
		LOGFONT		logfont;
		CString		fontFaceName;
		CString		fontStyleName;
		int		fontSize;
		COLORREF	fontColor;
		int		fontWeight;
		BOOL		fontStrikeout;
		BOOL		fontUnderline;
		BOOL		fontBold;
		BOOL		fontItalic;

		void		setFontName(const char *name);
		BOOL		grabIt(const BITMAP &bm, const char *bits, CRect &rect, const unsigned int backColor);
		BOOL		isRowEmpty(const BITMAP &bm, const char *bits, const int row, const unsigned int backColor);
		BOOL		isColumnEmpty(const BITMAP &bm, const char *bits, const int col, const unsigned int backColor);
		unsigned int	getReversePixel(const BITMAP &bm, const char *bits, const int x, const int y);
		unsigned int	getPixel(const BITMAP &bm, const char *bits, const int x, const int y);

	//{{AFX_MSG(FontGenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPickFont();
	afx_msg void OnPickDest();
	afx_msg void OnGo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // _H_FONTGENDLG
// ---------------------------------------------------------------------------------------------------------------------------------
// FontGenDlg.h - End of file
// ---------------------------------------------------------------------------------------------------------------------------------

