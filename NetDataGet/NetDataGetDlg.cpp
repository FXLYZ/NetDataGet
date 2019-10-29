
// NetDataGetDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NetDataGet.h"
#include "NetDataGetDlg.h"
#include "afxdialogex.h"
#include "pcap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetDataGetDlg 对话框



CNetDataGetDlg::CNetDataGetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETDATAGET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetDataGetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, DataContent);
	DDX_Control(pDX, IDC_LIST1, NetWorkCardBox);
	DDX_Control(pDX, IDC_EDIT2, NetWorkCardInfo);
	DDX_Control(pDX, IDC_BUTTON1, StartCatch);
	DDX_Control(pDX, IDC_BUTTON3, StopCatch);
}

BEGIN_MESSAGE_MAP(CNetDataGetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNetDataGetDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON3, &CNetDataGetDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CNetDataGetDlg 消息处理程序

BOOL CNetDataGetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	pcap_if_t* alldevs; 	               //指向设备链表首部的指针
	pcap_if_t* d;
	//pcap_addr_t* a;
	char		errbuf[PCAP_ERRBUF_SIZE];	//错误信息缓冲区
	//获得本机的设备列表
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, 	//获取本机的接口设备
		NULL,			       //无需认证
		&alldevs, 		       //指向设备列表首部
		errbuf			      //出错信息保存缓存区
	) == -1)
	{
		//错误处理      }
		int count = 0;
		for (d = alldevs; d != NULL; d = d->next)      //显示接口列表
		{
			//利用d->name获取该网络接口设备的名字
			dnames[count] = d->name;
			dinfos[count] = d->description;
			NetWorkCardBox.InsertString(count + 1, dnames[count]);
			count++;
			//利用d->description获取该网络接口设备的描述信息
			//获取该网络接口设备的IP地址信息
			//for (a = d->addresses; a != NULL; a = a->next)
			//	if (a->addr->sa_family == AF_INET)  //判断该地址是否IP地址
			//	{
			//		//利用a->addr获取IP地址
			//		//利用a->netmask获取网络掩码
			//		//利用a->broadaddr获取广播地址
			//		//利用a->dstaddr)获取目的地址
			//	}
		}
		pcap_freealldevs(alldevs); //释放设备列表
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNetDataGetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNetDataGetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNetDataGetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetDataGetDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	pcap_if_t* alldevs; 	               //指向设备链表首部的指针
	pcap_if_t* d;
	pcap_t* adhandle;
	int res;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct tm* ltime;
	char timestr[16];
	struct pcap_pkthdr* header;
	const u_char* pkt_data;
	time_t local_tv_sec;
	//获得本机的设备列表
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, 	//获取本机的接口设备
		NULL,			       //无需认证
		&alldevs, 		       //指向设备列表首部
		errbuf			      //出错信息保存缓存区
	) == -1)
	{
		DataContent.SetWindowTextA("获取网卡失败");
		return;
	}

	//抓包
	int index=NetWorkCardBox.GetCurSel();
	int i;
	for (d = alldevs, i = 0; i < index - 1; d = d->next, i++);

	if ((adhandle = pcap_open(d->name,          // 设备名
		65536,            // 要捕捉的数据包的部分 
						  // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,    // 混杂模式
		1000,             // 读取超时时间
		NULL,             // 远程机器验证
		errbuf            // 错误缓冲池
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* 释放设列表 */
		pcap_freealldevs(alldevs);
		return;
	}
	NetWorkCardInfo.SetWindowTextA(d->description);
	pcap_freealldevs(alldevs);
	while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0) {

		if (res == 0)
			/* 超时时间到 */
			continue;

		/* 将时间戳转换成可识别的格式 */
		local_tv_sec = header->ts.tv_sec;
		ltime = localtime(&local_tv_sec);
		strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
		CString temp,data;
		DataContent.GetWindowTextA(temp);
		data.Format("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
		//printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
		DataContent.SetWindowTextA(temp + data);
	}

	if (res == -1) {
		CString temp, data;
		DataContent.GetWindowTextA(temp);
		data.Format("Error reading the packets: %s\n", pcap_geterr(adhandle));
		//printf("Error reading the packets: %s\n", pcap_geterr(adhandle));
		return;
	}


	//显示
	//Data_t* IPPacket;
	//ULONG		SourceIP, DestinationIP;
	//IPPacket = (Data_t*)pkt_data;
	//SourceIP = ntohl(IPPacket->IPHeader.SrcIP);
	//DestinationIP = ntohl(IPPacket->IPHeader.DstIP);


}


void CNetDataGetDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	//停止抓包
}
