# if _MSC_VER >= 1000
#   pragma once
# endif // _MSC_VER >= 1000

//  XXX: bad code to fix.
# if defined (__INL_PANE_ENABLE)

typedef CWinTraits<WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VSCROLL|WS_HSCROLL,WS_EX_STATICEDGE>    CViewDS_EffectsFlangerBaseTraits;

// # include "CDirectDraw.hxx"
class CViewDS_EffectsFlangerBase:public CWindowImpl<CViewDS_EffectsFlangerBase,CWindow,CViewDS_EffectsFlangerBaseTraits>,
    public CScrollImpl<CViewDS_EffectsFlangerBase>
{
public :
  //  fixed min size
  //  some settings 
  static  const  int width = 372;
  static  const  int height = 259;
  static  const  COLORREF background_color = 0xF0F0F0;

  typedef    CWindowImpl<CViewDS_EffectsFlangerBase,CWindow,CViewDS_EffectsFlangerBaseTraits> baseClass;
  typedef    CScrollImpl<CViewDS_EffectsFlangerBase> baseClass2;
  typedef CViewDS_EffectsFlangerBase  thisClass;
  
  // attach DirectMusic Object.
  CDirectMusic2 *m_DirectMusic;  

  // ctrl .
  CEdit m_GuiET_TryMix;
  CEdit m_GuiET_Depth;
  CEdit m_GuiET_Feedback;
  CEdit m_GuiET_Freq;
  CEdit m_GuiET_Delay;
  
  CTrackBarCtrl m_GuiTK_TryMix;
  CTrackBarCtrl m_GuiTK_Depth;
  CTrackBarCtrl m_GuiTK_Feedback;
  CTrackBarCtrl m_GuiTK_Freq;
  CTrackBarCtrl m_GuiTK_Delay;

  CComboBox m_GuiCB_Waveform;
  CComboBox m_GuiCB_Phase;
  
  CButton m_GuiCK_Enable;

  DSFXFlanger m_FlangerParam;

  CViewDS_EffectsFlangerBase (void)  {
    m_FlangerParam.fWetDryMix = 50.0;
    m_FlangerParam.fDepth = 100.0;
    m_FlangerParam.fFeedback = 50.0;
    m_FlangerParam.fFrequency = 0.25;
    m_FlangerParam.fDelay = 2.0;
    m_FlangerParam.lWaveform = DSFXFLANGER_WAVE_SIN;
    m_FlangerParam.lPhase = DSFXFLANGER_PHASE_ZERO;

    m_DirectMusic = NULL;
  }

  DECLARE_WND_CLASS(_T ("CViewDS_EffectsFlangerBase"))

  BEGIN_MSG_MAP(thisClass)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_HSCROLL, OnSlider)
    COMMAND_HANDLER2 (m_GuiCK_Enable, BN_CLICKED, OnSetEnable)
    COMMAND_HANDLER2 (m_GuiCB_Waveform, CBN_SELCHANGE, OnSelCOmboItem)
    COMMAND_HANDLER2 (m_GuiCB_Phase, CBN_SELCHANGE, OnSelCOmboItem)
    CHAIN_MSG_MAP(baseClass2)
  END_MSG_MAP()

  LRESULT OnSetEnable (WORD code, WORD /*wID*/, HWND hWindow, BOOL& /*bHandled*/) {
    int status = :: SendMessage (hWindow, BM_GETCHECK, 0, 0);
    if (status == BST_UNCHECKED)   {
      // cancel effects.
      m_DirectMusic->SetEffectEnable (CDirectMusic2 ::IDIRECTEFFECTS_POS_FLANGER, FALSE);
    } else  {
      // set  effects .
      m_DirectMusic->SetEffectEnable (CDirectMusic2 ::IDIRECTEFFECTS_POS_FLANGER, TRUE);
      m_DirectMusic->SetEffectDesc (CDirectMusic2 ::IDIRECTEFFECTS_POS_FLANGER, (CDirectMusic2::DSFX_desc *)& m_FlangerParam);
    }
    return 0;
  }

  void SetAttach (CDirectMusic2 *cmusic) {
    m_DirectMusic = cmusic;
  }
  void DoPaint (CDCHandle dc) {
    CRect t;
    GetClientRect (t);
    t.OffsetRect ( m_ptOffset);
    dc.FillSolidRect (& t, background_color);
  }

  LRESULT OnSelCOmboItem (WORD code, WORD /*wID*/, HWND hWindow, BOOL& bHandled) {
    if (hWindow == m_GuiCB_Phase)  {
      switch (m_GuiCB_Phase.GetCurSel ()) {
      case  0:  m_FlangerParam.lPhase = DSFXFLANGER_PHASE_NEG_180; break;
      case  1:  m_FlangerParam.lPhase = DSFXFLANGER_PHASE_NEG_90; break;
      case  2:  m_FlangerParam.lPhase = DSFXFLANGER_PHASE_ZERO; break;
      case  3:  m_FlangerParam.lPhase = DSFXFLANGER_PHASE_90; break;
      case  4:  m_FlangerParam.lPhase = DSFXFLANGER_PHASE_180; break;
      default :  ATLASSERT (FALSE);
        break  ;
      }
    } else if (hWindow == m_GuiCB_Waveform)  {
      switch (m_GuiCB_Waveform.GetCurSel ()) {
      case  0:  m_FlangerParam.lWaveform = DSFXFLANGER_WAVE_TRIANGLE; break;
      case  1:  m_FlangerParam.lWaveform = DSFXFLANGER_WAVE_SIN; break;
      default :  ATLASSERT (FALSE);
        break  ;
      }
    } else  {
      bHandled = FALSE;
      return 0;
    }
    if  ( m_GuiCK_Enable.GetCheck () == BST_CHECKED)
      m_DirectMusic->SetEffectDesc (CDirectMusic2 ::IDIRECTEFFECTS_POS_FLANGER, (CDirectMusic2::DSFX_desc *)& m_FlangerParam);
    return 0;
  }
  LRESULT OnSlider(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    int code = LOWORD (wParam);
    if (code == TB_ENDTRACK || code == TB_THUMBTRACK)  {
      CString s;
      BOOL bSet = TRUE;
      HWND hWindow = (HWND) lParam;

      if  ( hWindow == m_GuiTK_TryMix)  {
        int pos = m_GuiTK_TryMix.GetPos ();
        float c = ((float)pos) / 1000.0f;
        float b = c * (DSFXFLANGER_WETDRYMIX_MAX - DSFXFLANGER_WETDRYMIX_MIN);
        m_FlangerParam.fWetDryMix =b+ DSFXFLANGER_WETDRYMIX_MIN;
        if  ( m_FlangerParam.fWetDryMix > DSFXFLANGER_WETDRYMIX_MAX)
          m_FlangerParam.fWetDryMix = DSFXFLANGER_WETDRYMIX_MAX;
        if  ( m_FlangerParam.fWetDryMix < DSFXFLANGER_WETDRYMIX_MIN)
          m_FlangerParam.fWetDryMix = DSFXFLANGER_WETDRYMIX_MIN;
        s.Format (_T ("%f"), m_FlangerParam.fWetDryMix);
        m_GuiET_TryMix.SetWindowText (s);
      } else if  ( hWindow == m_GuiTK_Depth)  {
        int pos = m_GuiTK_Depth.GetPos ();
        float c = ((float)pos) / 1000.0f;
        float b = c * (DSFXFLANGER_DEPTH_MAX - DSFXFLANGER_DEPTH_MIN);
        m_FlangerParam.fFeedback =b+ DSFXFLANGER_DEPTH_MIN;
        if  ( m_FlangerParam.fFeedback > DSFXFLANGER_DEPTH_MAX)
          m_FlangerParam.fFeedback = DSFXFLANGER_DEPTH_MAX;
        if  ( m_FlangerParam.fFeedback < DSFXFLANGER_DEPTH_MIN)
          m_FlangerParam.fFeedback = DSFXFLANGER_DEPTH_MIN;
        s.Format (_T ("%f"), m_FlangerParam.fFeedback);
        m_GuiET_Depth.SetWindowText (s);
      } else  if  ( hWindow == m_GuiTK_Feedback)  {
        int pos = m_GuiTK_Feedback.GetPos ();
        float c = ((float)(pos)) / 1980.0f;
        float b = c * (DSFXFLANGER_FEEDBACK_MAX - DSFXFLANGER_FEEDBACK_MIN);
        m_FlangerParam.fFeedback =b+ DSFXFLANGER_FEEDBACK_MIN;
        if  ( m_FlangerParam.fFeedback > DSFXFLANGER_FEEDBACK_MAX)
          m_FlangerParam.fFeedback = DSFXFLANGER_FEEDBACK_MAX;
        if  ( m_FlangerParam.fFeedback < DSFXFLANGER_FEEDBACK_MIN)
          m_FlangerParam.fFeedback = DSFXFLANGER_FEEDBACK_MIN;
        s.Format (_T ("%f"), m_FlangerParam.fFeedback);
        m_GuiET_Feedback.SetWindowText (s);
      } else if  ( hWindow == m_GuiTK_Freq)  {
        int pos = m_GuiTK_Freq.GetPos ();
        float c = ((float)(pos)) / 100.0f;
        float b = c * (DSFXFLANGER_FREQUENCY_MAX - DSFXFLANGER_FREQUENCY_MIN);
        m_FlangerParam.fFrequency =b+ DSFXFLANGER_FREQUENCY_MIN;
        if  ( m_FlangerParam.fFrequency > DSFXFLANGER_FREQUENCY_MAX)
          m_FlangerParam.fFrequency = DSFXFLANGER_FREQUENCY_MAX;
        if  ( m_FlangerParam.fFrequency < DSFXFLANGER_FREQUENCY_MIN)
          m_FlangerParam.fFrequency = DSFXFLANGER_FREQUENCY_MIN;
        s.Format (_T ("%f"), m_FlangerParam.fFrequency);
        m_GuiET_Freq.SetWindowText (s);
      } else if  ( hWindow == m_GuiTK_Delay)  {
        int pos = m_GuiTK_Delay.GetPos ();
        float c = ((float)(pos)) / 40.0f;
        float b = c * (DSFXFLANGER_DELAY_MAX - DSFXFLANGER_DELAY_MIN);
        m_FlangerParam.fDelay =b+ DSFXFLANGER_DELAY_MIN;
        if  ( m_FlangerParam.fDelay > DSFXFLANGER_DELAY_MAX)
          m_FlangerParam.fDelay = DSFXFLANGER_DELAY_MAX;
        if  ( m_FlangerParam.fDelay < DSFXFLANGER_DELAY_MIN)
          m_FlangerParam.fDelay = DSFXFLANGER_DELAY_MIN;
        s.Format (_T ("%f"), m_FlangerParam.fDelay);
        m_GuiET_Delay.SetWindowText (s);
      } else  {
        bHandled = FALSE;
        return 0;
      }
      if  ( m_GuiCK_Enable.GetCheck () == BST_CHECKED)
        m_DirectMusic->SetEffectDesc (CDirectMusic2 ::IDIRECTEFFECTS_POS_FLANGER, (CDirectMusic2::DSFX_desc *)& m_FlangerParam);
      return 0;
    }
    bHandled = FALSE;
    return 0;
  }

  LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
    
    SetClassLongPtr (m_hWnd, GCLP_HBRBACKGROUND, (LONG_PTR) GetStockObject (NULL_BRUSH)) ;
    HINSTANCE hInst = _Module.GetModuleInstance ();
    HWND hWindow = m_hWnd;

    HFONT hFont = CreateFont(-11, 0, 0, 0, 400, FALSE, FALSE, FALSE, 1, 400, 0, 0, 0, _T ("MS Shell Dlg"));
    
    // static  Group.
    HWND T = CreateWindowEx (0, WC_STATIC, _T ("Wet/Try Mix(%)"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 47, 75, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (WS_EX_TRANSPARENT, WC_BUTTON, _T ("IDirectSound8 Effects - Flanger Settings"), WS_VISIBLE | WS_CHILD | 0x00000007, 8, 5, 350, 241, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (0, WC_STATIC, _T ("WaveForm"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 185, 54, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (0, WC_STATIC, _T ("Depth(%)"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 73, 45, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (0, WC_STATIC, _T ("Feedback(%)"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 99, 63, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (0, WC_STATIC, _T ("Frequency(hz)"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 125, 69, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (0, WC_STATIC, _T ("Delay(ms)"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 156, 48, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);
    T = CreateWindowEx (0, WC_STATIC, _T ("Phase"), WS_VISIBLE | WS_CHILD | WS_GROUP | SS_LEFT, 18, 213, 32, 15, hWindow, (HMENU)-1, hInst, 0);
    SendMessage (T, WM_SETFONT, (WPARAM)hFont, FALSE);

    // CEdit Group.
    m_GuiET_TryMix = CreateWindowEx (0, WC_EDIT, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, 104, 46, 65, 20, hWindow, (HMENU)-1, hInst, 0);
    m_GuiET_TryMix.SetFont (hFont, FALSE);
    m_GuiET_Depth = CreateWindowEx (0, WC_EDIT, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, 104, 72, 65, 20, hWindow, (HMENU)-1, hInst, 0);
    m_GuiET_Depth.SetFont (hFont, FALSE);
    m_GuiET_Feedback = CreateWindowEx (0, WC_EDIT, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, 104, 99, 65, 20, hWindow, (HMENU)-1, hInst, 0);
    m_GuiET_Feedback.SetFont (hFont, FALSE);
    m_GuiET_Freq = CreateWindowEx (0, WC_EDIT, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, 104, 124, 65, 20, hWindow, (HMENU)-1, hInst, 0);
    m_GuiET_Freq.SetFont (hFont, FALSE);
    m_GuiET_Delay = CreateWindowEx (0, WC_EDIT, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, 104, 154, 65, 20, hWindow, (HMENU)-1, hInst, 0);
    m_GuiET_Delay.SetFont (hFont, FALSE);

    // CSlider Ctrl.
    m_GuiTK_TryMix = CreateWindowEx(0, TRACKBAR_CLASS, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | TBS_BOTH | TBS_NOTICKS, 174, 42, 180, 26, hWindow, (HMENU)-1, hInst, 0);
    m_GuiTK_TryMix.SetFont (hFont, FALSE);
    m_GuiTK_Depth = CreateWindowEx(0, TRACKBAR_CLASS, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | TBS_BOTH | TBS_NOTICKS, 174, 68, 180, 26, hWindow, (HMENU)-1, hInst, 0);
    m_GuiTK_Depth.SetFont (hFont, FALSE);
    m_GuiTK_Feedback = CreateWindowEx(0, TRACKBAR_CLASS, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | TBS_BOTH | TBS_NOTICKS, 174, 96, 180, 26, hWindow, (HMENU)-1, hInst, 0);
    m_GuiTK_Feedback.SetFont (hFont, FALSE);
    m_GuiTK_Freq = CreateWindowEx(0, TRACKBAR_CLASS, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | TBS_BOTH | TBS_NOTICKS, 174, 122, 180, 26, hWindow, (HMENU)-1, hInst, 0);
    m_GuiTK_Freq.SetFont (hFont, FALSE);
    m_GuiTK_Delay = CreateWindowEx(0, TRACKBAR_CLASS, _T (""), WS_VISIBLE | WS_CHILD | WS_TABSTOP | TBS_BOTH | TBS_NOTICKS, 174, 151, 180, 26, hWindow, (HMENU)-1, hInst, 0);
    m_GuiTK_Delay.SetFont (hFont, FALSE);

    // Check 
    m_GuiCK_Enable = CreateWindowEx (0, WC_BUTTON, _T ("Enable Flanger Effects"), WS_VISIBLE | WS_CHILD | WS_TABSTOP | 0x00000003, 18, 24, 129, 13, hWindow, (HMENU)-1, hInst, 0);
    m_GuiCK_Enable.SetFont (hFont, FALSE);

    // Combo 
    m_GuiCB_Waveform = CreateWindowEx (0, WC_COMBOBOX, _T (""), WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 104, 182, 243, 21, hWindow, (HMENU)-1, hInst, 0);
    m_GuiCB_Waveform.SetFont (hFont, FALSE);
    m_GuiCB_Phase = CreateWindowEx (0, WC_COMBOBOX, _T (""), WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 104, 210, 243, 21, hWindow, (HMENU)-1, hInst, 0);
    m_GuiCB_Phase.SetFont (hFont, FALSE);

    CString str[5];
    str[0].Format ( _T ("%f"), m_FlangerParam.fWetDryMix);
    str[1].Format ( _T ("%f"), m_FlangerParam.fDepth);
    str[2].Format ( _T ("%f"), m_FlangerParam.fFeedback);
    str[3].Format ( _T ("%f"), m_FlangerParam.fFrequency);
    str[4].Format ( _T ("%f"), m_FlangerParam.fDelay);

    m_GuiTK_TryMix.SetRange (0, 1000);
    m_GuiTK_TryMix.SetPos ( (int) (m_FlangerParam.fWetDryMix / DSFXFLANGER_WETDRYMIX_MAX * 1000.0f ));
    m_GuiTK_Depth.SetRange (0, 1000);
    m_GuiTK_Depth.SetPos ( (int) (m_FlangerParam.fDepth / DSFXFLANGER_DEPTH_MAX * 1000.0f ));
    m_GuiTK_Feedback.SetRange (0, 1980);
    m_GuiTK_Feedback.SetPos ( (int) (( (int) (m_FlangerParam.fFeedback - DSFXFLANGER_FEEDBACK_MIN) / (DSFXFLANGER_FEEDBACK_MAX - DSFXFLANGER_FEEDBACK_MIN) * 1980.0f )));
    m_GuiTK_Freq.SetRange (0, 100);
    m_GuiTK_Freq.SetPos ( (int) (m_FlangerParam.fFrequency / DSFXFLANGER_FREQUENCY_MAX * 100.0f ));
    m_GuiTK_Delay.SetRange (0, 40);
    m_GuiTK_Delay.SetPos ( (int) (m_FlangerParam.fDelay / DSFXFLANGER_DELAY_MAX * 40.0f ));

    // add combo 
    m_GuiCB_Phase.Clear ();
    m_GuiCB_Phase.InsertString (-1, _T ("Phase NEG 180"));
    m_GuiCB_Phase.InsertString (-1, _T ("Phase NEG 90"));
    m_GuiCB_Phase.InsertString (-1, _T ("Phase 0"));
    m_GuiCB_Phase.InsertString (-1, _T ("Phase 90"));
    m_GuiCB_Phase.InsertString (-1, _T ("Phase 180"));
    m_GuiCB_Phase.SetCurSel (2);

    m_GuiCB_Waveform.Clear ();
    m_GuiCB_Waveform.InsertString (-1, _T ("Triangular wave"));
    m_GuiCB_Waveform.InsertString (-1, _T ("Sine wave"));
    m_GuiCB_Waveform.SetCurSel (1);

    m_GuiET_TryMix.SetWindowText (str[0]);
    m_GuiET_Depth.SetWindowText (str[1]);
    m_GuiET_Feedback.SetWindowText (str[2]);
    m_GuiET_Freq.SetWindowText (str[3]);
    m_GuiET_Delay.SetWindowText (str[4]);

    return 0;
  }
};

# endif // !defined(_CVIEWDS_EFFECTSFLANGER_INCLUED_HEADER_CXX_