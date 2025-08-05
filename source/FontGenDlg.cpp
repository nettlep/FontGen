// ---------------------------------------------------------------------------------------------------------------------------------
//  ______             _    _____            _____  _                            
// |  ____|           | |  / ____|          |  __ \| |                           
// | |__    ___  _ __ | |_| |  __  ___ _ __ | |  | | | __ _      ___ _ __  _ __  
// |  __|  / _ \| '_ \| __| | |_ |/ _ \ '_ \| |  | | |/ _` |    / __| '_ \| '_ \ 
// | |    | (_) | | | | |_| |__| |  __/ | | | |__| | | (_| | _ | (__| |_) | |_) |
// |_|     \___/|_| |_|\__|\_____|\___|_| |_|_____/|_|\__, |(_) \___| .__/| .__/ 
//                                                     __/ |        | |   | |    
//                                                    |___/         |_|   |_|    
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

#include "stdafx.h"
#include "FontGen.h"
#include "FontGenDlg.h"

// ---------------------------------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ---------------------------------------------------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(FontGenDlg, CDialog)
	//{{AFX_MSG_MAP(FontGenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PICK_FONT, OnPickFont)
	ON_BN_CLICKED(IDC_PICK_DEST, OnPickDest)
	ON_BN_CLICKED(IDC_GO, OnGo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ---------------------------------------------------------------------------------------------------------------------------------

	FontGenDlg::FontGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FontGenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(FontGenDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// ---------------------------------------------------------------------------------------------------------------------------------

void	FontGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FontGenDlg)
	DDX_Control(pDX, IDC_PROGRESS, progressControl);
	//}}AFX_DATA_MAP
}

// ---------------------------------------------------------------------------------------------------------------------------------

BOOL	FontGenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	setFontName("No font selected");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// ---------------------------------------------------------------------------------------------------------------------------------

void	FontGenDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

HCURSOR	FontGenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void	FontGenDlg::OnPickFont() 
{
	CFontDialog	fontdlg;

	if (fontdlg.DoModal() == TRUE)
	{
		fontdlg.GetCurrentFont(&logfont);
		fontFaceName = fontdlg.GetFaceName();
		fontStyleName = fontdlg.GetStyleName();
		fontSize = fontdlg.GetSize();
		fontColor = fontdlg.GetColor();
		fontWeight = fontdlg.GetWeight();
		fontStrikeout = fontdlg.IsStrikeOut();
		fontUnderline = fontdlg.IsUnderline();
		fontBold = fontdlg.IsBold();
		fontItalic = fontdlg.IsItalic();

		setFontName((LPCTSTR) fontFaceName);
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

void	FontGenDlg::setFontName(const char *name)
{
	char disp[90];
	sprintf( disp, "%s", name);
	SetDlgItemText(IDC_FONT_NAME, disp);
}

// ---------------------------------------------------------------------------------------------------------------------------------

void	FontGenDlg::OnPickDest() 
{
	char		fname[_MAX_PATH] = "";
	char		filters[] = "Font files (*.f)" "\0" "*.f" "\0" "All files (*.*)" "\0" "*.*" "\0" "\0";
	OPENFILENAME	of;

	memset(&of, 0, sizeof(OPENFILENAME));

	of.lStructSize  = sizeof(OPENFILENAME);
	of.hwndOwner    = GetSafeHwnd();
	of.lpstrFilter  = filters;
	of.nFilterIndex = 1;
	of.lpstrFile    = fname;
	of.nMaxFile     = 256;
	of.lpstrTitle   = "Browse for destination font file";
	of.Flags        = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	of.lpstrDefExt  = "f";

	if (GetOpenFileName(&of))
	{
		SetDlgItemText(IDC_FILENAME, fname);
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

void	FontGenDlg::OnGo() 
{
	VERIFY(UpdateData());

	progressControl.SetRange(0, 255);

	// Get the font name

	char	fileName[256];
	GetDlgItemText(IDC_FILENAME, fileName, 255);

	// Open the file

	FILE	*pFile = fopen(fileName, "wb");

	if (!pFile)
	{
		AfxMessageBox("Unable to open file");
		return;
	}

	// Go get that font data

	CBitmap	bm;
	bm.CreateBitmap(FONT_MAX_SIZE, FONT_MAX_SIZE, 1, GetDC()->GetDeviceCaps(BITSPIXEL), NULL);

	CDC	bdc;
	bdc.CreateCompatibleDC(NULL);
	bdc.SelectObject(&bm);

	CFont	font;
	font.CreateFontIndirect(&logfont);
	bdc.SelectObject(&font);

	unsigned int	backColor = 0;
	bdc.SetBkColor((COLORREF) backColor);
	bdc.SetTextColor((COLORREF) 0xffffff);
	bdc.SetTextAlign(TA_BASELINE | TA_LEFT | TA_NOUPDATECP);

	// Get our bitmap bits

	BITMAP	bmi;
	bm.GetBitmap(&bmi);

	char	*bits = new char[bmi.bmWidthBytes * bmi.bmHeight];

	if (!bits)
	{
		AfxMessageBox("Unable to allocate bitmap bits");
		fclose(pFile);
		return;
	}

	int	largest = 0;

	for (int i = 0; i < 256; i++)
	{
		progressControl.SetPos(i);

		// This is our single-character string

		char	string[2];string[0] = i;string[1] = 0;

		// Find out how big this sucker is

		CSize	extents = bdc.GetTextExtent(string, 1);

		// Draw it to the context

		int	centerX = FONT_MAX_SIZE / 2;
		int	centerY = FONT_MAX_SIZE / 2;
		CRect	r(centerX, centerY, FONT_MAX_SIZE, FONT_MAX_SIZE);
		CRect	clientRect(0, 0, FONT_MAX_SIZE, FONT_MAX_SIZE);
		bdc.FillSolidRect(clientRect, (COLORREF) backColor);
		bdc.DrawText(string, 1, r, DT_NOCLIP | DT_SINGLELINE | DT_NOPREFIX);
		bm.GetBitmapBits(bmi.bmWidthBytes * bmi.bmHeight, bits);

		// Go grab it from the bitmap

		CRect	charRect;

		if (grabIt(bmi, bits, charRect, backColor))
		{
			int	byteWidth  = charRect.right  - charRect.left + 1;
			int	byteHeight = charRect.bottom - charRect.top  + 1;
			int	xOffset = charRect.left - centerX;
			int	yOffset = charRect.top - centerY;
			int	pixelWidth = extents.cx;
			int	pixelHeight = extents.cy;

			fwrite(&byteWidth,   sizeof(byteWidth  ), 1, pFile);
			fwrite(&byteHeight,  sizeof(byteHeight ), 1, pFile);
			fwrite(&xOffset,     sizeof(xOffset    ), 1, pFile);
			fwrite(&yOffset,     sizeof(yOffset    ), 1, pFile);
			fwrite(&pixelWidth,  sizeof(pixelWidth ), 1, pFile);
			fwrite(&pixelHeight, sizeof(pixelHeight), 1, pFile);

			for (int y = charRect.top; y <= charRect.bottom; y++)
			{
				for (int x = charRect.left; x <= charRect.right; x++)
				{
					int	col = getReversePixel(bmi, bits, x, y);
					char	temp = col & 0xff;
					fwrite(&temp, 1, 1, pFile);
				}
			}
		}
		else
		{
			int	temp = 0;

			fwrite(&temp,   sizeof(temp), 1, pFile);
			fwrite(&temp,   sizeof(temp), 1, pFile);
			fwrite(&temp,   sizeof(temp), 1, pFile);
			fwrite(&temp,   sizeof(temp), 1, pFile);
			fwrite(&temp,   sizeof(temp), 1, pFile);
			fwrite(&temp,   sizeof(temp), 1, pFile);
		}
	}

	// Cleanup

	delete bits;
	fclose(pFile);

	progressControl.SetPos(0);

	UpdateWindow();
	Beep(500, 150);
}

// ---------------------------------------------------------------------------------------------------------------------------------

BOOL	FontGenDlg::grabIt(const BITMAP &bm, const char *bits, CRect &rect, const unsigned int backColor)
{
	// Find the top extent

	for (int y0 = 0; y0 < bm.bmHeight; y0++)
	{
		if (!isRowEmpty(bm, bits, y0, backColor)) break;
	}

	// Make sure we got a character in here

	if (y0 == bm.bmHeight) return FALSE;

	// Find the bottom extent

	for (int y1 = bm.bmHeight - 1; y1 >= 0; y1--)
	{
		if (!isRowEmpty(bm, bits, y1, backColor)) break;
	}

	// Find the left extent

	for (int x0 = 0; x0 < bm.bmWidth; x0++)
	{
		if (!isColumnEmpty(bm, bits, x0, backColor)) break;
	}

	// Find the right extent

	for (int x1 = bm.bmWidth - 1; x1 >= 0; x1--)
	{
		if (!isColumnEmpty(bm, bits, x1, backColor)) break;
	}

	rect = CRect(x0, y0, x1, y1);

	return TRUE;
}

// ---------------------------------------------------------------------------------------------------------------------------------

BOOL	FontGenDlg::isRowEmpty(const BITMAP &bm, const char *bits, const int row, const unsigned int backColor)
{
	for (int x = 0; x < bm.bmWidth; x++)
		if (getPixel(bm, bits, x, row) != backColor) return FALSE;

	return TRUE;
}

// ---------------------------------------------------------------------------------------------------------------------------------

BOOL	FontGenDlg::isColumnEmpty(const BITMAP &bm, const char *bits, const int col, const unsigned int backColor)
{
	for (int y = 0; y < bm.bmHeight; y++)
		if (getPixel(bm, bits, col, y) != backColor) return FALSE;

	return TRUE;
}

// ---------------------------------------------------------------------------------------------------------------------------------

unsigned int	FontGenDlg::getReversePixel(const BITMAP &bm, const char *bits, const int x, const int y)
{
	unsigned int	color = getPixel(bm, bits, x, y);

	return ((color & 0xff) << 16) | (color & 0xff00) | ((color & 0xff0000) >> 16);
}

// ---------------------------------------------------------------------------------------------------------------------------------

unsigned int	FontGenDlg::getPixel(const BITMAP &bm, const char *bits, const int x, const int y)
{
	switch(bm.bmBitsPixel)
	{
		case 15:
		{
			short	*temp = (short *) &bits[y * bm.bmWidthBytes];
			unsigned int	r = ((temp[x] >> 10) & 0x1f) << 19;
			unsigned int	g = ((temp[x] >>  5) & 0x1f) << 11;
			unsigned int	b = ((temp[x] >>  0) & 0x1f) <<  3;
			return r|g|b;
			break;
		}

		case 16:
		{
			short	*temp = (short *) &bits[y * bm.bmWidthBytes];
			unsigned int	r = ((temp[x] >> 11) & 0x1f) << 19;
			unsigned int	g = ((temp[x] >>  5) & 0x3f) << 10;
			unsigned int	b = ((temp[x] >>  0) & 0x1f) <<  3;
			return r|g|b;
			break;
		}

		case 24:
		{
			const unsigned char *temp = (unsigned char *) &bits[y * bm.bmWidthBytes + x * 3];
			return (unsigned int) ((temp[0] << 16) | (temp[1] << 8) | temp[2]);
			break;
		}

		case 32:
		{
			const unsigned char *temp = (unsigned char *) &bits[y * bm.bmWidthBytes + x * 4];
			return (unsigned int) ((temp[0] << 16) | (temp[1] << 8) | temp[2]);
			break;
		}
		default:
		{
			AfxMessageBox("Invalid bit depth");
			return 0;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------
// FontGenDlg.cpp - End of file
// ---------------------------------------------------------------------------------------------------------------------------------

