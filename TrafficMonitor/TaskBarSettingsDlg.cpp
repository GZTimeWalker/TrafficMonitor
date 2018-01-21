// TaskBarSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "TaskBarSettingsDlg.h"
#include "afxdialogex.h"


// CTaskBarSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CTaskBarSettingsDlg, CDialogEx)

CTaskBarSettingsDlg::CTaskBarSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TASKBAR_SETTINGS_DIALOG, pParent)
{

}

CTaskBarSettingsDlg::~CTaskBarSettingsDlg()
{
}

void CTaskBarSettingsDlg::DrawStaticColor()
{
	CCommon::FillStaticColor(m_text_color_static, m_data.text_color);
	CCommon::FillStaticColor(m_back_color_static, m_data.back_color);
}

void CTaskBarSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC1, m_text_color_static);
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC2, m_back_color_static);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTaskBarSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SET_FONT_BUTTON1, &CTaskBarSettingsDlg::OnBnClickedSetFontButton1)
	ON_BN_CLICKED(IDC_SET_COLOR_BUTTON2, &CTaskBarSettingsDlg::OnBnClickedSetColorButton2)
	ON_BN_CLICKED(IDC_SET_COLOR_BUTTON3, &CTaskBarSettingsDlg::OnBnClickedSetColorButton3)
	ON_EN_CHANGE(IDC_UPLOAD_EDIT1, &CTaskBarSettingsDlg::OnEnChangeUploadEdit1)
	ON_EN_CHANGE(IDC_DOWNLOAD_EDIT1, &CTaskBarSettingsDlg::OnEnChangeDownloadEdit1)
	ON_EN_CHANGE(IDC_CPU_EDIT1, &CTaskBarSettingsDlg::OnEnChangeCpuEdit1)
	ON_EN_CHANGE(IDC_MEMORY_EDIT1, &CTaskBarSettingsDlg::OnEnChangeMemoryEdit1)
	ON_BN_CLICKED(IDC_SET_DEFAULT_BUTTON1, &CTaskBarSettingsDlg::OnBnClickedSetDefaultButton1)
	ON_BN_CLICKED(IDC_SWITCH_UP_DOWN_CHECK1, &CTaskBarSettingsDlg::OnBnClickedSwitchUpDownCheck1)
	ON_BN_CLICKED(IDC_TASKBAR_WND_ON_LEFT_CHECK, &CTaskBarSettingsDlg::OnBnClickedTaskbarWndOnLeftCheck)
END_MESSAGE_MAP()


// CTaskBarSettingsDlg ��Ϣ��������


BOOL CTaskBarSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(255, 255, 255));

	//��ʼ�����ؼ�״̬
	SetDlgItemText(IDC_FONT_NAME_EDIT1, m_data.font_name);
	wchar_t buff[16];
	swprintf_s(buff, L"%d", m_data.font_size);
	SetDlgItemText(IDC_FONT_SIZE_EDIT1, buff);

	SetDlgItemText(IDC_UPLOAD_EDIT1, m_data.up_string.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT1, m_data.down_string.c_str());
	SetDlgItemText(IDC_CPU_EDIT1, m_data.cpu_string.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT1, m_data.memory_string.c_str());

	((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK1))->SetCheck(m_data.swap_up_down);
	((CButton*)GetDlgItem(IDC_TASKBAR_WND_ON_LEFT_CHECK))->SetCheck(m_data.tbar_wnd_on_left);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTaskBarSettingsDlg::OnBnClickedSetFontButton1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CFont font;
	font.CreatePointFont(m_data.font_size * 10, m_data.font_name);
	LOGFONT lf{};             //LOGFONT����
	font.GetLogFont(&lf);
	CFontDialog fontDlg(&lf);	//��������Ի��򣬳�ʼѡ������Ϊ֮ǰ����
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���
	{
		//��ȡ������Ϣ
		m_data.font_name = fontDlg.GetFaceName();
		m_data.font_size = fontDlg.GetSize() / 10;
		//��������Ϣ��ʾ����
		SetDlgItemText(IDC_FONT_NAME_EDIT1, m_data.font_name);
		wchar_t buff[16];
		swprintf_s(buff, L"%d", m_data.font_size);
		SetDlgItemText(IDC_FONT_SIZE_EDIT1, buff);
	}
}

//�����ı���ɫ
void CTaskBarSettingsDlg::OnBnClickedSetColorButton2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CColorDialog colorDlg(m_data.text_color, 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_data.text_color = colorDlg.GetColor();
		if (m_data.back_color == m_data.text_color)
			MessageBox(_T("���棺������ɫ�ͱ���ɫ��ͬ��"), NULL, MB_ICONWARNING);
		DrawStaticColor();
	}
}

//���ñ�����ɫ
void CTaskBarSettingsDlg::OnBnClickedSetColorButton3()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CColorDialog colorDlg(m_data.back_color, 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_data.back_color = colorDlg.GetColor();
		if (m_data.back_color == m_data.text_color)
			MessageBox(_T("���棺����ɫ��������ɫ��ͬ��"), NULL, MB_ICONWARNING);
		DrawStaticColor();
	}
}


void CTaskBarSettingsDlg::OnEnChangeUploadEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_UPLOAD_EDIT1, tmp);
	m_data.up_string = tmp;
}


void CTaskBarSettingsDlg::OnEnChangeDownloadEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_DOWNLOAD_EDIT1, tmp);
	m_data.down_string = tmp;
}


void CTaskBarSettingsDlg::OnEnChangeCpuEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_CPU_EDIT1, tmp);
	m_data.cpu_string = tmp;
}


void CTaskBarSettingsDlg::OnEnChangeMemoryEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_MEMORY_EDIT1, tmp);
	m_data.memory_string = tmp;
}


void CTaskBarSettingsDlg::OnBnClickedSetDefaultButton1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.up_string = L"��: ";
	m_data.down_string = L"��: ";
	m_data.cpu_string = L"CPU: ";
	m_data.memory_string = L"�ڴ�: ";
	SetDlgItemText(IDC_UPLOAD_EDIT1, m_data.up_string.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT1, m_data.down_string.c_str());
	SetDlgItemText(IDC_CPU_EDIT1, m_data.cpu_string.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT1, m_data.memory_string.c_str());
}


void CTaskBarSettingsDlg::OnBnClickedSwitchUpDownCheck1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.swap_up_down = (((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK1))->GetCheck() != 0);
}


void CTaskBarSettingsDlg::OnBnClickedTaskbarWndOnLeftCheck()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.tbar_wnd_on_left = (((CButton*)GetDlgItem(IDC_TASKBAR_WND_ON_LEFT_CHECK))->GetCheck() != 0);
}