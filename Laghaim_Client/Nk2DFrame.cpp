#include "stdafx.h"
#define D3D_OVERLOADS

#include <ddraw.h>
#include <tchar.h>
#include <process.h>
#include <boost/format.hpp>
#include "Nk2DFrame.h"
#include "ddutil.h"
#include "dxutil.h"
#include "d3dmath.h"
#include "main.h"
#include "D3DEnum.h"
#include "MsgPopUp.h"
#include "country.h"
#include "TextOutBox.h"
#include "ControlLetter.h"
#include "Sprite.h"
#include "ControlUpgrade.h"
#include "WebCtrl.h"
#include "Capsyong.h"
#include "IndexedTexture.h"
#include "tcpipcon.h"
#include "Sheet.h"
#include "ControlTop.h"
#include "ControlStatus.h"
#include "ControlBottom.h"
#include "ControlInven.h"
#include "ControlSocial.h"
#include "ControlGate.h"
#include "ControlMap.h"
#include "ControlSkill.h"
#include "ControlShop.h"
#include "ItemProto.h"
#include "ItemRender.h"
#include "ControlScore.h"
#include "WarTax.h"
#include "matlist.h"
#include "Help.h"
#include "TextOutBox.h"
#include "scroll.h"
#include "AlphaPopup.h"
#include "BasicMenu.h"
#include "skill.h"
#include "controlhelp.h"
#include "controlexchange.h"
#include "interchange.h"
#include "controlparty.h"
#include "mouse.h"
#include "gamble.h"

#include "LockSmith.h"

#include "refine.h"
#include "Land.h"
#include "uimgr.h"
#include "NkMob.h"
#include "NkPet.h"
#include "NkMyPet.h"
#include "RShiftMenu.h"
#include "LShiftMenu.h"
#include "controlwarehouse.h"
#include "controlusershop.h" ///���λ���
#include "ControlCashShop.h" ///�������
#include "controlpetstatus.h"
#include "controlpeiceshop.h"
#include "product.h"
#include "PetProduct.h"
#include "Event_Ancient.h"
#include "QuestData.h"
#include "Pet_Level.h"
#include "platinum.h"
#include "SummerEvent.h"
#include "GuildPK.h"
#include "AutoMouse.h"
#include "g_stringmanager.h"
#include "Process.h"
#include "ControlDocument.h"
#include "WorldCupStart.h"
#include "ControlHelper.h"
#include "SpiritMode.h"
#include "headers.h"
#include "AutoNotice.h"	// ����� ��û : 10�� ���� ���� �޽��� ���
#include "PremiumExchange.h"
#include "ControlGuildSHouse.h"
#include "s_guild_manager.h"
#include "ControlGuildT.h"
#include "ControlGuildM.h"
#include "window_resource.h"
#include "WindowMgr.h"
#include "guild_data.h"
#include "guild_battle.h"

#include "ControlNotice.h" ///�����˾�â
#include "ControlHelpPet.h" ///�굵��

#include "WindowMgr.h"

#include "PVPWidget.h"

#include "DmitronBattle.h"
#include "DmitronBattleTax.h"
#include "DmitronBattleStatus.h"

#include "ControlBossRaidInfo.h"

#include "ControlHeroFinalRank.h"

#include "ControlHeroList.h"
#include "ControlHeroPrivilege.h"

#include "ControlPremiumServiceChaMove.h"

#include "ControlYutboard.h"
#include "ControlFishing.h"
#include "ControlFishingReward.h"

#include "AutoPlay_test.h"
#include "GuildHunt.h"


#include "ControlSelectMenu.h"

#include "LHUI_OpEvent.h"

#include "LHUI_TakeBox.h"

#include "LHUI_Gate.h"

#include "LHUI_Define.h"

#include "UIFriend.h"

#include "UI_BuffItem.h"
#include "BuffItemMgr.h"
#include "DevTestGmCommand.h"

#include "CommonConfig.h"

#include "ControlDecardiBattle.h"
#include "ControlLotto.h"

#include "PacketSend.h"

#include "ShoutChatMgr.h"

#include "ControlBingo.h"
#include "ControlLetterWindow.h"
#include "ControlLetterSend.h"
#include "ControlLetterRecv.h"
#include "ControlBaseball.h"
#include "ControlBaseballReward.h"
#include "ControlLottery.h"
#include "ControlDiceGame.h"
#include "ControlDiceGameReward.h"
#include "ItemInfoScaleMgr.h"

CNk2DFrame * g_pNk2DFrame = NULL;

extern int	g_nServerIndex;		// ���� �ε��� ( ���� �ý��� )
extern BOOL	   g_bAdmin;



extern float g_fTimeKey;
extern BOOL g_bRestart;

extern DWORD g_dwClientCountry;
extern DWORD g_dwLangType;
extern BOOL g_bUseCashShop; ///�������
extern BOOL g_bGlobalMatrix; ///���������� �� Ŭ���̾�Ʈ ���� ����.

extern void LoadSkills();
extern void DeleteSkills();

extern void SendAddFriend(const int& order, const std::string& name);
extern bool MobData_IsShop(int vnum);

char commOutBuf[512];
POINT g_CursorPoint;
//=============================
// nate 2004 - 4 : CastleWar
CSurface *g_pImgKing1 = NULL;
CSurface *g_pImgKing2 = NULL;
CSurface *g_pImgKing3 = NULL;
CSurface *g_pImgKing4 = NULL;
//=============================

CSurface *g_pPK = NULL;
CSurface *g_pNonPK = NULL;
CSurface *g_pMatrixKor = NULL; ///���������� ���� ���� �� �̹���

CSurface *g_pMatrixJpn = NULL; ///���������� ���� ���� �� �̹���

CSurface *g_pNvNWin = NULL; ///�������¸� ��ũ

// nate : �븸 �� ����


CSurface *g_pMedal = NULL;
CSurface *g_pGuildpk = NULL;

#define MSGPOPUP_NOT_EXIST  0
#define MSGPOPUP_EXIST  1

extern void SendEventMadCharName(const std::string& charName);
extern void SendMasterDelegation(const bool confirm);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//=============================================================================
//	Name : CNk2DFrame
//=============================================================================
CNk2DFrame::CNk2DFrame()
	: m_bLShift(FALSE)
	, m_bStatus(FALSE)
	, m_InfoTime(0)
	, m_InfoFrame(0)
	, m_InfoTime2(0)
	, m_InfoFrame2(0)
	, m_Slot_Num(0)
	, m_bLoadingNow(false)
	, m_bLoadingGoWorldNow(false)
{
	memset(m_strCheckWareHouse, 0, sizeof(m_strCheckWareHouse));
	memset(m_strRShiftName, 0, sizeof(m_strRShiftName));

	m_pControlMenu = NULL;
	m_pControlBottom = NULL;
	m_pControlTop = NULL;
	m_pControlStatus = NULL;
	m_pRShiftMenu = NULL;
	m_pLShiftMenu = NULL;
	m_pAutoMouse = NULL;
	m_pControlInven = NULL;
	m_bAllLoaded = FALSE;

	m_pControlSkill = NULL;
	m_pControlShop = NULL;
	m_pControlExchange = NULL;
	m_pControlWareHouse = NULL;
	m_pControlGStoreHouse	= NULL;
	m_pGuildManager			= NULL;
	m_pControlGuild			= NULL;
	m_pControlGuildManager	= NULL;
	m_pControlGuildBattle	= NULL;
	m_pGuildRankWarBattleCount = NULL;
	m_pControlUserShop = NULL; ///���λ���
	m_pControlCashShop = NULL; ///�������
	m_pCashShopIntro = NULL; ///�������
	m_pInterchange = NULL;
	m_pProduct = NULL;
	m_pPetProduct = NULL;
	m_pControlHelp = NULL;
	m_pControlParty = NULL;
	m_pControlPetStatus = NULL;
	m_pControlPeiceShop = NULL;
	m_pGamble = NULL;

	m_pLockSmith = NULL;
	m_pRefine = NULL;
	m_pUpgrade = NULL; ///�Ź���ȭ�ý���
	m_pControlNotice = NULL; ///�����˾�â
	m_pUserShopSearch = NULL; ///���λ����˻�

	m_pControlHelper = NULL;	//�İ���
	m_pControlHelpPet = NULL;	///�굵��

	m_pEventAncient = NULL;
	m_pPlatinum = NULL;
	m_pSummerEvent = NULL;
	m_pPet_Level = NULL;
	m_pGuildPK   = NULL;
	m_pStartSheet = NULL;
	m_pProcess = NULL;		//����

	m_pSpiritMode = NULL;

	m_pWorldCup = NULL;


	m_ui_takebox = NULL;
	m_dwTakeBox_Time = 0;

	m_ui_gate = NULL;

	m_pAutoNotice = NULL;	// ����� ��û : 10�� ���� ���� �޽��� ���

	m_bLetter = FALSE;
	m_GraphicMode = NKGRAPHIC2D;
	m_bMenu = FALSE;
	m_bShop = FALSE;
	m_bShowExchange = FALSE;
	m_bInterchange = FALSE;
	m_bProduct = FALSE;
	m_bPetProduct = FALSE;
	m_bInven = FALSE;
	m_bPetStatus = FALSE;
	m_bSkill = FALSE;
	m_bHelp = FALSE;
	m_bParty = FALSE;
	m_bViewTop = TRUE;
	m_bRShift = FALSE;
	m_bShowWareHouse = FALSE;

	m_bShowGStoreHouse = FALSE;
	m_bShowGuildManager = FALSE;
	m_bShowControlGuild = FALSE;
	m_bShowControlGuildManage = FALSE;

	m_bShowUserShop = FALSE; ///���λ���
	m_bPeiceShop = FALSE;
	m_bAutoMouse = FALSE;
	m_bPetLevel = FALSE;
	m_bZone      = FALSE;
	m_bWorldCup = FALSE;
	m_bHelper = FALSE;
	m_bHelpPet = FALSE; ///�굵��
	m_bSpiritStart = FALSE;

	m_dpChaCapsyong = NULL;
	m_pInfoBox = NULL;
	m_pInfoBox2 = NULL;
	m_PartyReadyIndex = -1;
	m_pNkCha = NULL;
	m_bShowGamble = FALSE;

	m_bLockSmith = FALSE;

	m_bShowRefine = FALSE;
	m_bShowUpgrade = FALSE;	///�Ź���ȭ�ý���
	m_bShowNotice = FALSE;	///�����˾�â
	m_bShowUserShopSearch = FALSE; ///���λ����˻�

	m_bShowCashShop = FALSE; ///�������
	m_bShowCashShopIntro = FALSE; ///�������
	m_bShowEventAncient	= FALSE;
	m_bShowPlatinum = FALSE;
	m_bShowSummerEvent = FALSE;
	m_bShowProcess = FALSE;
	m_Popup = NULL;
	m_iQuicSlotNum = -1;
	m_nDocument = 0;

	// [3/5/2007 Theodoric] ������ ����� ���� �ʱ�ȭ
	m_strConnectServerName = NULL;

	m_pUIWindow		= NULL;
	m_pWindowRes	= NULL;

	m_pControlMenu = NULL;
	m_pControlTop = NULL;
	m_pControlStatus = NULL;
	m_pRShiftMenu = NULL;
	m_pLShiftMenu = NULL;
	m_pControlBottom = NULL;
	m_pControlShop = NULL;
	m_pControlPeiceShop = NULL;
	m_pControlExchange = NULL;
	m_pControlWareHouse = NULL;
	m_pControlGStoreHouse = NULL;
	m_pGuildManager = NULL;

	m_pControlUserShop = NULL;
	m_pControlCashShop = NULL;
	m_pCashShopIntro = NULL;

	m_pInterchange = NULL;
	m_pProduct = NULL;
	m_pAutoMouse = NULL;
	m_pPetProduct = NULL;
	m_pControlInven = NULL;
	m_pControlSkill = NULL;
	m_pControlHelp = NULL;
	m_pControlParty = NULL;
	m_pControlPetStatus = NULL;
	m_pControlLetter = NULL;
	m_pPet_Level = NULL;
	m_pItemRender = NULL;
	m_pWorldCup = NULL;
	m_pControlHelper = NULL;
	m_pControlGuild = NULL;
	m_pControlGuildManager = NULL;
	m_pControlGuildBattle = NULL;
	m_pGuildRankWarBattleCount = NULL;
	m_pSpiritMode = NULL;
	m_pAutoNotice = NULL;

	m_pUIWindow = NULL;
	m_pWindowRes = NULL;
	m_pTgaUIWindow	= NULL;

	m_bShowPVPWidget = FALSE;
	m_pPVPWidget = NULL;

	m_bShowDmitronBattleStatus = TRUE;
	m_pDmitronBattleStatus = NULL;

	m_pBossraidInfo = NULL;
	m_bBossraidInfo = FALSE;

	m_pHeroFinalRank = NULL;
	m_bHeroFinalRank = FALSE;

	m_pHeroPrivilege = NULL;
	m_bHeroPrivilege = FALSE;
	m_pHeroRankList = NULL;
	m_bHeroRankList = FALSE;

	m_pPremiumExchange = NULL;
	m_bShowPremiumExchange = FALSE;


	LoadSkills();

	m_bProcLock = FALSE;
	m_pPremiumChaMove = NULL;
	m_bShowPremiumChaMove = FALSE;

	m_pControlSelMenu = NULL;
	m_bShowControlSelMenu = FALSE;

	m_ui_op_event = NULL;

	m_ui_takebox = NULL;
	m_dwTakeBox_Time = 0;

	m_pInterface = new CBaseInterface*[MAX_NUM];
	m_bInterface = new bool[MAX_NUM];
	for( int i = 0 ; i < MAX_NUM ; i ++ )
	{
		m_pInterface[ i ] = NULL;
		m_bInterface[ i ] = false;
	}

	m_ui_friend = NULL;
	m_ui_buffitem = NULL;
	m_ui_decardibattle = NULL;

	m_pStartSheet = new CSheet();
	m_pControlMenu = new CControlMenu();
	m_pControlTop = new CControlTop();
	m_pControlStatus = new CControlStatus();
	m_pRShiftMenu = new CRShiftMenu();
	m_pLShiftMenu = new CLShiftMenu();
	m_pControlBottom = new CControlBottom();
	m_pControlShop = new CControlShop();
	m_pControlPeiceShop = new CControlPeiceShop();
	m_pControlExchange = new CControlExchange();
	m_pControlWareHouse = new CControlWareHouse();
	m_pControlGStoreHouse = new CControlGuildSHouse();
	m_pGuildManager		  = CGuildSystemManager::Create();
	m_pControlUserShop = new CControlUserShop();  ///���λ���
	if( g_bUseCashShop )
	{
		m_pControlCashShop = new CControlCashShop();  ///�������
		m_pCashShopIntro = new CCashShopIntro();  ///�������
	}

	m_pInterchange = new CInterchange();
	m_pProduct = new CProduct();
	m_pAutoMouse  = new CAutoMouse();
	m_pPetProduct = new CPetProduct();
	m_pControlInven = new CControlInven();
	m_pInterface[SCORE] = new CControlScore();
	m_pInterface[GATE] = new CControlGate();
	m_pInterface[SOCIAL] = new CControlSocial();
	m_pInterface[QUEST] = new CQuestData();
	m_pInterface[MAP] = new CControlMap();
	m_pInterface[DOCUMENT] = new CControlDocument();
	m_pInterface[YUTBOARD] = new ControlYutboard();
	m_pInterface[FISHING] = new ControlFishing();
	m_pInterface[FISHING_REWARD] = new ControlFishingReward();
	m_pInterface[BASEBALL] = new ControlBaseball();
	m_pInterface[BASEBALL_REWARD] = new ControlBaseballReward();
	m_pInterface[LOTTO] = new ControlLotto();
	m_pInterface[BINGO] = new ControlBingo();
	m_pInterface[LETTER_WINDOW] = new ControlLetterWindow();
	m_pInterface[LETTER_SEND] = new ControlLetterSend();
	m_pInterface[LETTER_RECV] = new ControlLetterRecv();
	m_pInterface[LOTTERY] = new ControlLottery();
	m_pInterface[DICEGAME] = new ControlDiceGame();
	m_pInterface[DICEGAME_REWARD] = new ControlDiceGameReward();

	m_pControlSkill = new CControlSkill();
	m_pControlHelp  = new CControlHelp();
	m_pControlParty = new CControlParty();
	m_pControlPetStatus = new CControlPetStatus();
	m_pPet_Level = new CPetLevel();
	m_pItemRender = new CItemRender();
	m_pWorldCup = new CWorldCupStart();
	m_pControlHelper = new CControlHelper();
	m_pControlGuild = new CControlGuild();
	m_pControlGuildManager = new CControlGuildManage();
	m_pControlGuildBattle = new CControlGuildBattle();
	m_pGuildRankWarBattleCount = new CGuildRankWarBattleCount();
	m_pSpiritMode = new CSpiritMode();
	m_pUIWindow = new CWindowMgr;
	m_pWindowRes = CWINDOWUI::Create();
	m_pTgaUIWindow = new CWindowTgaMgr;
	m_pPVPWidget = new CPVPWidget;
	m_pDmitronBattleStatus = new CDmitronBattleStatus;
	m_pBossraidInfo = new CControlBossraidInfo;
	m_pHeroFinalRank = new CControlHeroFinalRank;
	m_pHeroPrivilege = new CControlHeroPrivilege;
	m_pHeroRankList = new CControlHeroRankList;
	m_pPremiumExchange = new CPremiumExchange;
	
	LoadSkills();
	
	m_pPremiumChaMove = new CControlPremiumChaMove;
	m_pControlSelMenu = new CControlSelectMenu;

	m_ui_op_event = NULL;
	m_ui_takebox = NULL;
	m_dwTakeBox_Time = 0;

	m_exp_init = false;
	InitExpTable();

	m_force_exit = false;
	m_force_exit_tick = 0;
}

//=============================================================================
//	Name : ~CNk2DFrame
//=============================================================================
CNk2DFrame::~CNk2DFrame()
{
	if (GetControlExchange() && GetControlExchange()->IsExch())
	{
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage("exch cancel\n", TRUE);
	}

	if (GetRefine() && GetRefine()->IsRefineConnection())
	{
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage("ms reject\n", TRUE);
	}

	SAFE_DELETE(m_pPremiumExchange);


	SAFE_DELETE(m_pDmitronBattleStatus);

	SAFE_DELETE(m_pPremiumChaMove);

	SAFE_DELETE(m_pControlMenu);
	SAFE_DELETE(m_pStartSheet);
	SAFE_DELETE(m_pControlTop);
	SAFE_DELETE(m_pControlStatus);
	SAFE_DELETE(m_pRShiftMenu);
	SAFE_DELETE(m_pLShiftMenu);
	SAFE_DELETE(m_pControlBottom);
	SAFE_DELETE(m_pControlShop);
	SAFE_DELETE(m_pControlPeiceShop);
	SAFE_DELETE(m_pControlExchange);
	SAFE_DELETE(m_pControlWareHouse);
	SAFE_DELETE(m_pControlGStoreHouse);
	SAFE_DELETE(m_pGuildManager);
	SAFE_DELETE(m_pControlGuild);
	SAFE_DELETE(m_pControlGuildManager);
	SAFE_DELETE(m_pControlGuildBattle);

	SAFE_DELETE(m_pUIWindow);
	SAFE_DELETE(m_pWindowRes);

	SAFE_DELETE(m_pGuildRankWarBattleCount);

	SAFE_DELETE(m_pTgaUIWindow);

	SAFE_DELETE(m_pPVPWidget);

	SAFE_DELETE(m_pControlUserShop); ///���λ���
	SAFE_DELETE(m_pControlCashShop); ///�������
	SAFE_DELETE(m_pCashShopIntro); ///�������
	SAFE_DELETE(m_pInterchange);
	SAFE_DELETE(m_pProduct);
	SAFE_DELETE(m_pAutoMouse);
	SAFE_DELETE(m_pPetProduct);
	SAFE_DELETE(m_pControlInven);
	SAFE_DELETE(m_pInterface[SCORE]);
	SAFE_DELETE(m_pInterface[GATE]);
	SAFE_DELETE(m_pInterface[SOCIAL]);
	SAFE_DELETE(m_pInterface[QUEST]);
	SAFE_DELETE(m_pInterface[MAP]);
	SAFE_DELETE(m_pInterface[DOCUMENT]);
	SAFE_DELETE(m_pInterface[YUTBOARD]);
	SAFE_DELETE(m_pInterface[FISHING]);
	SAFE_DELETE(m_pInterface[FISHING_REWARD]);
	SAFE_DELETE(m_pInterface[BASEBALL]);
	SAFE_DELETE(m_pInterface[BASEBALL_REWARD]);
	SAFE_DELETE(m_pInterface[LOTTO]);
	SAFE_DELETE(m_pInterface[BINGO]);
	SAFE_DELETE(m_pInterface[LETTER_WINDOW]);
	SAFE_DELETE(m_pInterface[LETTER_SEND]);
	SAFE_DELETE(m_pInterface[LETTER_RECV]);
	SAFE_DELETE(m_pInterface[LOTTERY]);
	SAFE_DELETE(m_pInterface[DICEGAME]);
	SAFE_DELETE(m_pInterface[DICEGAME_REWARD]);
	SAFE_DELETE( m_ui_gate );
	SAFE_DELETE(m_pControlSkill);
	SAFE_DELETE(m_pControlHelp);
	SAFE_DELETE(m_pControlParty);
	SAFE_DELETE(m_pControlPetStatus);
	SAFE_DELETE(m_pWorldCup);
	SAFE_DELETE(m_pControlHelper);
	SAFE_DELETE(m_pSpiritMode);


	SAFE_DELETE(m_ui_takebox);

	DeleteObjects();

	// [12/18/2008 D.K ] : find memory leak .
	SAFE_DELETE_ARRAY( m_pInterface );
	SAFE_DELETE(m_pControlLetter);
	SAFE_DELETE(m_pItemRender);
	SAFE_DELETE(m_pInfoBox);
	SAFE_DELETE(m_pInfoBox2);

	DeleteSkills();

	if(m_pGamble)
	{
		delete m_pGamble;
		m_pGamble = NULL;
		m_bShowGamble = false;
	}

	if(m_pLockSmith)
	{
		delete m_pLockSmith;
		m_pLockSmith = NULL;
		m_bLockSmith = false;
	}

	if(m_pEventAncient)
	{
		delete	m_pEventAncient;
		m_pEventAncient = NULL;
		m_bShowEventAncient	= FALSE;
	}
	if(m_pPlatinum)
	{
		delete	m_pPlatinum;
		m_pPlatinum = NULL;
		m_bShowPlatinum	= FALSE;
	}
	if(m_pSummerEvent)
	{
		delete m_pSummerEvent;
		m_pSummerEvent = NULL;
		m_bShowSummerEvent = FALSE;
	}
	if(m_pRefine)
	{
		delete m_pRefine;
		m_pRefine = NULL;
		m_bShowRefine = false;
	}
	if( m_pUpgrade )	 ///�Ź���ȭ�ý���
	{
		delete m_pUpgrade;
		m_pUpgrade = NULL;
		m_bShowUpgrade = false;
	}
	if( m_pControlNotice ) ///�����˾�â
	{
		delete m_pControlNotice;
		m_pControlNotice = NULL;
		m_bShowNotice = false;
	}
	if( m_pUserShopSearch ) ///���λ����˻�


	{
		delete m_pUserShopSearch;
		m_pUserShopSearch = NULL;
		m_bShowUserShopSearch = false;
	}
	if(m_pProcess)	//����


	{
		delete m_pProcess;
		m_pProcess = NULL;
		m_bShowProcess = false;
	}

	// [3/5/2007 Theodoric] ������ ����� ���� �޸� ����
	SAFE_DELETE_ARRAY(m_strConnectServerName);

	SAFE_DELETE(m_pGuildPK); // ����� ����
	SAFE_DELETE(m_pPet_Level);

	SAFE_DELETE(m_pBossraidInfo);
	m_bBossraidInfo = FALSE;

	SAFE_DELETE(m_pHeroFinalRank);
	m_bHeroFinalRank = FALSE;

	SAFE_DELETE( m_pHeroPrivilege );
	m_bHeroPrivilege = FALSE;
	SAFE_DELETE( m_pHeroRankList );
	m_bHeroRankList = FALSE;

	SAFE_DELETE_ARRAY( m_bInterface );

	SAFE_DELETE(m_pControlSelMenu);

	SAFE_DELETE( m_ui_op_event );

	SAFE_DELETE(m_ui_friend);


	SAFE_DELETE(m_ui_buffitem);
	SAFE_DELETE(m_ui_decardibattle);

	SAFE_DELETE(m_ui_takebox);

	SAFE_DELETE( m_ui_gate );

	DeleteAllPopup();
}

HRESULT CNk2DFrame::RestoreSurfaces()
{
	if (m_GraphicMode == NKGRAPHIC3D) // �̰� �˻�����༭ �α���ȭ���� ȭ����ȯ�ϸ� ƨ���.(06-01-05 ����)
	{
		if( IsExchangeVisible() )
			ShowExchangeWindow(FALSE, FALSE);

		if( m_ui_friend )			m_ui_friend->RestoreSurfaces();
		if( m_pControlInven	)		m_pControlInven->RestoreSurfaces();
		if( m_pControlStatus )		m_pControlStatus->RestoreSurfaces();
		if (m_pControlMenu)			m_pControlMenu->RestoreSurfaces();
		if (m_pControlBottom)		m_pControlBottom->RestoreSurfaces();
		if (m_pInterface[SCORE])	((CControlScore*)m_pInterface[SCORE])->RestoreSurfaces();
		if (m_pControlSkill)		m_pControlSkill->RestoreSurfaces();
		if (m_pControlPetStatus)	m_pControlPetStatus->RestoreSurfaces();
		if (m_pControlParty)		m_pControlParty->RestoreSurfaces();	///��Ƽ����.
		if (m_pInterface[QUEST])	((CQuestData*)m_pInterface[QUEST])->RestoreSurfaces();
		if (m_pInterface[YUTBOARD]) ((ControlYutboard*)m_pInterface[YUTBOARD])->RestoreSurfaces();
		if (m_pInterface[FISHING])  ((ControlFishing*)m_pInterface[FISHING])->RestoreSurfaces();
		if (m_pInterface[FISHING_REWARD])	((ControlFishingReward*)m_pInterface[FISHING_REWARD])->RestoreSurfaces();
		if (m_pInterface[BASEBALL])	((ControlBaseball*)m_pInterface[BASEBALL])->RestoreSurfaces();
		if (m_pInterface[BASEBALL_REWARD])	((ControlBaseballReward*)m_pInterface[BASEBALL_REWARD])->RestoreSurfaces();
		if (m_pInterface[LOTTO])	((ControlLotto*)m_pInterface[LOTTO])->RestoreSurfaces();
		if (m_pInterface[BINGO])	((ControlBingo*)m_pInterface[BINGO])->RestoreSurfaces();
		if (m_pInterface[LETTER_WINDOW]) ((ControlLetterWindow*)m_pInterface[LETTER_WINDOW])->RestoreSurfaces();
		if (m_pInterface[LETTER_SEND]) ((ControlLetterSend*)m_pInterface[LETTER_SEND])->RestoreSurfaces();
		if (m_pInterface[LETTER_RECV]) ((ControlLetterRecv*)m_pInterface[LETTER_RECV])->RestoreSurfaces();
		if (m_pInterface[LOTTERY]) ((ControlLottery*)m_pInterface[LOTTERY])->RestoreSurfaces();
		if (m_pInterface[DICEGAME]) ((ControlDiceGame*)m_pInterface[DICEGAME])->RestoreSurfaces();
		if (m_pInterface[DICEGAME_REWARD]) ((ControlDiceGameReward*)m_pInterface[DICEGAME_REWARD])->RestoreSurfaces();
		if( m_pControlUserShop && m_pControlUserShop->m_bResLoad ) ///���λ��� // ���λ����� �ѹ� �������� ���ҽ��� �ε��صд�. �׷��Ƿ� �÷��׸� Ȯ���ϰ� �÷��׸� �ʱ�ȭ ���ִ� ��ƾ�� �ʿ��ϴ�.
		{
			// �ε��� �߾����ٸ�....
			m_pControlUserShop->m_bResLoad = FALSE; // �� �÷��׸� ����� �ٽ� �ε��� �� �ִ�.
			m_pControlUserShop->RestoreSurfaces();
		}
		if( m_pControlCashShop && m_pControlCashShop->m_bResLoad ) ///������� // ��������� �ѹ� �������� ���ҽ��� �ε��صд�. �׷��Ƿ� �÷��׸� Ȯ���ϰ� �÷��׸� �ʱ�ȭ ���ִ� ��ƾ�� �ʿ��ϴ�.
		{
			// �ε��� �߾����ٸ�....
			m_pControlCashShop->m_bResLoad = FALSE; // �� �÷��׸� ����� �ٽ� �ε��� �� �ִ�.
			m_pControlCashShop->RestoreSurfaces();
		}
		if (m_pCashShopIntro)
			m_pCashShopIntro->RestoreSurfaces();	///�������

		{
			if(m_pControlGuild)
				m_pControlGuild->Restore();

			if(m_pControlGuildManager)
				m_pControlGuildManager->Restore();

			if(m_pUIWindow)
				m_pUIWindow->RestoreSurface();
		}

		if( g_SvrType == ST_ADULT_ONLY)
		{
			if(m_pTgaUIWindow)
				m_pTgaUIWindow->RestoreSurface();
		}

		if( m_pItemRender )
		{
			m_pItemRender->Restore();
		}

		if( m_pPet_Level )
		{
			m_pPet_Level->Restore();
		}

		RestorePopups();
	}
	else if( m_GraphicMode == NKGRAPHIC2D )
	{
		if( m_pStartSheet )
			m_pStartSheet->Restore();
	}

	return S_OK;
}

void CNk2DFrame::Init(int right, int bottom)
{
	if( g_pDisplay )
	{
		g_pDisplay->SetDirectDraw(GET_DD7());
		g_pDisplay->SetBackBuffer(GET_DDSRT());
		g_pDisplay->Clear();
	}
	m_ptCliSize.x = right;
	m_ptCliSize.y = bottom;
}

void CNk2DFrame::SetChaSet(CCapsyong **dpChaCapsyong, IndexedTexture *pChaTexture)
{
	m_dpChaCapsyong = dpChaCapsyong;

	if (m_pStartSheet)
		m_pStartSheet->SetChaSet(m_dpChaCapsyong, g_pCapsyongTexture);
}

void CNk2DFrame::SetEventType(int nType, int flag) ///�̺�Ʈ����ǥ��
{
	m_ui_op_event->SetEvent( nType , flag );
}

void CNk2DFrame::SetHwnd(HWND hwnd)
{
	if( g_pDisplay )
		g_pDisplay->SetHwnd(hwnd);
}

void CNk2DFrame::SetFocus()
{
	if(m_pAutoMouse && m_bAutoMouse)
	{
		m_pAutoMouse->SetTextInFocus();
		return;
	}
	else if( GetUIWindow()->IsOpenWindow(WINDOW_GUILD_BATTLE_INVASION) )
	{
		CBattleInvasionAttack * wnd = (CBattleInvasionAttack*)GetUIWindow()->GetWindow(WINDOW_GUILD_BATTLE_INVASION);
		if( wnd && wnd->IsTextBoxFocus() )
		{
			if(m_pControlBottom && m_pControlBottom)
				m_pControlBottom->LostFocus();
			return;
		}
	}

	if(m_pControlBottom && m_pControlBottom)
		m_pControlBottom->SetFocus();
}

BOOL CNk2DFrame::Load2DResources()
{
	// ���� ������ �޴�ȭ��.
	if (m_pStartSheet && m_GraphicMode == NKGRAPHIC2D)
		m_pStartSheet->LoadRes();


	if (m_GraphicMode == NKGRAPHIC2D && g_bRestart == FALSE)
		pCMyApp->InitProgress(2);

	if (m_GraphicMode == NKGRAPHIC3D)
		Load2DResourcesInGame();

	m_bAllLoaded = TRUE;
	return TRUE;
}

BOOL CNk2DFrame::Load2DResourcesInGame()
{
	if (m_GraphicMode == NKGRAPHIC3D)
	{
		if(m_pItemRender)			m_pItemRender->Init();
		if(m_pControlBottom)		m_pControlBottom->LoadRes();
		if(m_pControlTop)			m_pControlTop->LoadRes();
		if(m_pControlStatus)		m_pControlStatus->LoadRes();
		if(m_pPremiumExchange)		m_pPremiumExchange->LoadRes();
		if(m_pPremiumChaMove)		m_pPremiumChaMove->LoadRes();
		if(m_pRShiftMenu)			m_pRShiftMenu->LoadRes();
		if(m_pLShiftMenu)			m_pLShiftMenu->LoadRes();
		if(m_pControlShop)			m_pControlShop->LoadRes();
		if(m_pControlPeiceShop)		m_pControlPeiceShop->LoadRes();
		if(m_pControlExchange)		m_pControlExchange->LoadRes();
		if(m_pControlWareHouse)		m_pControlWareHouse->LoadRes();
		if(m_pControlGStoreHouse)	m_pControlGStoreHouse->LoadRes();
		if(m_pControlGuild)			m_pControlGuild->LoadRes();
		if(m_pControlGuildManager)	m_pControlGuildManager->LoadRes();
		if(m_pWindowRes)			m_pWindowRes->LoadResource();
		if(m_pInterchange)			m_pInterchange->LoadRes();
		if(m_pProduct)				m_pProduct->LoadRes();
		if(m_pPetProduct)			m_pPetProduct->LoadRes();
		if(m_pControlInven)			m_pControlInven->LoadRes();
		if(m_pControlSkill)			m_pControlSkill->LoadRes();
		if(m_pControlHelp)			m_pControlHelp->LoadRes();
		if(m_pControlParty)			m_pControlParty->LoadRes();
		if(m_pControlPetStatus)		m_pControlPetStatus->LoadRes();
		if(m_pPet_Level)			m_pPet_Level->LoadRes();
		if(m_pControlLetter)		m_pControlLetter->LoadRes();
		if(m_pCashShopIntro)		m_pCashShopIntro->LoadRes(); ///�������
		if(m_pWorldCup)				m_pWorldCup->LoadRes();
		if(m_pControlHelper)		m_pControlHelper->LoadRes();
		if(m_pSpiritMode)			m_pSpiritMode->LoadRes();		
		if(m_pInterface[MAP])		m_pInterface[MAP]->LoadRes();
		if(m_pInterface[SCORE] )	m_pInterface[SCORE]->LoadRes();
		if(m_pInterface[GATE])		m_pInterface[GATE]->LoadRes();
		if(m_pInterface[SOCIAL])	m_pInterface[SOCIAL]->LoadRes();
		if(m_pInterface[QUEST])		m_pInterface[QUEST]->LoadRes();
		if(m_pInterface[DOCUMENT])		m_pInterface[DOCUMENT]->LoadRes();
		if(m_pInterface[YUTBOARD])	m_pInterface[YUTBOARD]->LoadRes();
		if(m_pInterface[FISHING])	m_pInterface[FISHING]->LoadRes();		
		if(m_pInterface[FISHING_REWARD])	m_pInterface[FISHING_REWARD]->LoadRes();
		if(m_pInterface[BASEBALL])	m_pInterface[BASEBALL]->LoadRes();
		if(m_pInterface[BASEBALL_REWARD])	m_pInterface[BASEBALL_REWARD]->LoadRes();
		if(m_pInterface[LOTTO])		m_pInterface[LOTTO]->LoadRes();
		if(m_pInterface[BINGO])		m_pInterface[BINGO]->LoadRes();
		if(m_pInterface[LETTER_WINDOW])	m_pInterface[LETTER_WINDOW]->LoadRes();
		if(m_pInterface[LETTER_SEND])	m_pInterface[LETTER_SEND]->LoadRes();
		if(m_pInterface[LETTER_RECV])	m_pInterface[LETTER_RECV]->LoadRes();
		if(m_pInterface[LOTTERY])	m_pInterface[LOTTERY]->LoadRes();
		if(m_pInterface[DICEGAME])	m_pInterface[DICEGAME]->LoadRes();
		if(m_pInterface[DICEGAME_REWARD])	m_pInterface[DICEGAME_REWARD]->LoadRes();
		if(m_pPVPWidget)			m_pPVPWidget->LoadRes();
		if(m_pDmitronBattleStatus)	m_pDmitronBattleStatus->LoadRes();
		if( m_pBossraidInfo )	m_pBossraidInfo->LoadRes();
		if( m_pHeroFinalRank)	m_pHeroFinalRank->LoadRes();
		if(m_pHeroPrivilege)	m_pHeroPrivilege->LoadRes();
		if(m_pHeroRankList)		m_pHeroRankList->LoadRes();
		if( m_pControlSelMenu)	m_pControlSelMenu->LoadRes();

		if(!m_pGamble)
			m_pGamble = new CGamble();

		if(!m_pLockSmith)
			m_pLockSmith = new CLockSmith();
		if(!m_pRefine)
			m_pRefine = new CRefine();
		if( !m_pUpgrade )	///�Ź���ȭ�ý���
			m_pUpgrade = new CControlUpgrade(); // �� �������̽��� �޸𸮸� â�� ���� �����ϰ� ���� �����ϴ� ������� �غ�.(���� �޸𸮸� ���̱� ����.)
		if( !m_pUserShopSearch )	///���λ����˻�


			m_pUserShopSearch = new CControlUShopSearch(); // �� �������̽��� �޸𸮸� â�� ���� �����ϰ� ���� �����ϴ� ������� �غ�.(���� �޸𸮸� ���̱� ����.)
		if(!m_pEventAncient)
			m_pEventAncient = new CEventAncient();
		if(!m_pPlatinum)
			m_pPlatinum = new Cplatinum();
		if(!m_pSummerEvent)
			m_pSummerEvent = new CSummerEvent();
		if(!m_pProcess)
			m_pProcess = new CProcess();

		//==========================================
		// nate 2004-4 : CastleWar - ���� �հ� ����
		SAFE_DELETE( g_pImgKing1 );
		SAFE_DELETE( g_pImgKing2 );
		SAFE_DELETE( g_pImgKing3 );
		SAFE_DELETE( g_pImgKing4 );
		g_pDisplay->CreateSurfaceFromBitmap( &g_pImgKing1, "interface/war_tax/king.bmp" );
		if( g_pImgKing1 )
			g_pImgKing1->SetColorKey( RGB( 0, 0, 0 ) );
		g_pDisplay->CreateSurfaceFromBitmap( &g_pImgKing2, "interface/war_tax/king2.bmp" );
		if( g_pImgKing2 )
			g_pImgKing2->SetColorKey( RGB( 0, 0, 0 ) );
		g_pDisplay->CreateSurfaceFromBitmap( &g_pImgKing3, "interface/war_tax/king3.bmp" );
		if( g_pImgKing3 )
			g_pImgKing3->SetColorKey( RGB( 0, 0, 0 ) );
		g_pDisplay->CreateSurfaceFromBitmap( &g_pImgKing4, "interface/war_tax/d_king.bmp" );
		if( g_pImgKing4 )
			g_pImgKing4->SetColorKey( RGB( 0, 0, 0 ) );
		//==========================================
		SAFE_DELETE(g_pPK);
		g_pDisplay->CreateSurfaceFromBitmap (&g_pPK, "interface/war_tax/pk.bmp");
		if (g_pPK)
			g_pPK->SetColorKey(RGB(0, 0, 0));

		SAFE_DELETE(g_pNonPK);
		g_pDisplay->CreateSurfaceFromBitmap (&g_pNonPK, "interface/war_tax/peace.bmp");
		if (g_pNonPK)
			g_pNonPK->SetColorKey(RGB(0, 0, 0));

		SAFE_DELETE(g_pGuildpk);
		g_pDisplay->CreateSurfaceFromBitmap(&g_pGuildpk,"inderface/war_tax/guildpk.bmp");
		if(g_pGuildpk)
			g_pGuildpk->SetColorKey(RGB(0,0,0));

		// nate : �븸 �Ŵ� ����
		if( g_dwClientCountry == CTRY_TWN )
		{
			SAFE_DELETE(g_pMedal);
			g_pDisplay->CreateSurfaceFromBitmap (&g_pMedal, "interface/top/hi_shield.bmp");
			if (g_pMedal)
				g_pMedal->SetColorKey(RGB(0, 0, 0));
		}


		if( g_bGlobalMatrix )
		{
			SAFE_DELETE( g_pMatrixKor );
			g_pDisplay->CreateSurfaceFromBitmap (&g_pMatrixKor, "interface/war_tax/nation_KR.bmp");			

			SAFE_DELETE( g_pMatrixJpn );
			g_pDisplay->CreateSurfaceFromBitmap (&g_pMatrixJpn, "interface/war_tax/nation_JP.bmp");			
		}

		SAFE_DELETE(g_pNvNWin);
		g_pDisplay->CreateSurfaceFromBitmap (&g_pNvNWin, "interface/war_tax/mobius_medal.bmp");
		if (g_pNvNWin)
			g_pNvNWin->SetColorKey(RGB(255, 0, 255));


		m_ui_op_event = new LHUI_OpEvent;

		if( CommonConfig::Instance()->GetFriendSystem() == true )
		{
			m_ui_friend = new CUIFriend;
		}
		
		m_ui_buffitem = new UI_BuffItem;
		m_ui_decardibattle = new ControlDecardiBattle;

		return TRUE;
	}
	return FALSE;
}

void CNk2DFrame::DeleteObjects()
{
	m_bAllLoaded = FALSE;

	SAFE_DELETE_RES(m_pPremiumChaMove);
	SAFE_DELETE_RES(m_pPremiumExchange);
	SAFE_DELETE_RES(m_pControlMenu);
	SAFE_DELETE_RES(m_pControlTop);
	SAFE_DELETE_RES(m_pControlStatus );
	SAFE_DELETE_RES(m_pUpgrade);
	SAFE_DELETE_RES(m_pRShiftMenu);
	SAFE_DELETE_RES(m_pLShiftMenu);
	SAFE_DELETE_RES(m_pItemRender);
	SAFE_DELETE_RES(m_pControlBottom);
	SAFE_DELETE_RES(m_pControlShop);
	SAFE_DELETE_RES(m_pControlPeiceShop);
	SAFE_DELETE_RES(m_pControlExchange);
	SAFE_DELETE_RES(m_pControlWareHouse);

	SAFE_DELETE_RES(m_pControlGStoreHouse);
	SAFE_DELETE_RES(m_pControlGuild);
	SAFE_DELETE_RES(m_pControlGuildManager);
	SAFE_DELETE_RES(m_pUIWindow);
	SAFE_DELETE_RES(m_pWindowRes);
	SAFE_DELETE_RES(m_pGuildRankWarBattleCount);

	if( g_SvrType == ST_ADULT_ONLY )
	{
		SAFE_DELETE_RES(m_pTgaUIWindow);
	}

	SAFE_DELETE_RES(m_pPVPWidget);
	SAFE_DELETE_RES(m_pDmitronBattleStatus);
	SAFE_DELETE_RES(m_pBossraidInfo );

	SAFE_DELETE_RES(m_pHeroFinalRank);

	SAFE_DELETE_RES(m_pHeroPrivilege);
	SAFE_DELETE_RES(m_pHeroRankList);

	SAFE_DELETE_RES(m_pControlUserShop);
	SAFE_DELETE_RES(m_pControlCashShop);
	SAFE_DELETE_RES(m_pCashShopIntro);
	SAFE_DELETE_RES(m_pInterchange);
	SAFE_DELETE_RES(m_pProduct);
	SAFE_DELETE_RES(m_pAutoMouse);
	SAFE_DELETE_RES(m_pPetProduct);
	SAFE_DELETE_RES(m_pControlInven);
	SAFE_DELETE_RES(m_pControlSkill);
	SAFE_DELETE_RES(m_pControlHelp);
	SAFE_DELETE_RES(m_pControlParty);
	SAFE_DELETE_RES(m_pControlPetStatus);
	SAFE_DELETE_RES(m_pControlLetter);
	SAFE_DELETE_RES(m_pPet_Level);
	SAFE_DELETE_RES(m_pWorldCup);
	SAFE_DELETE_RES(m_pControlHelper);
	SAFE_DELETE_RES(m_pSpiritMode );
	SAFE_DELETE_RES(m_pInterface[QUEST]);
	SAFE_DELETE_RES(m_pInterface[SCORE]);
	SAFE_DELETE_RES(m_pInterface[GATE]);
	SAFE_DELETE_RES(m_pInterface[SOCIAL]);
	SAFE_DELETE_RES(m_pInterface[MAP]);
	SAFE_DELETE_RES(m_pInterface[DOCUMENT]);
	SAFE_DELETE_RES(m_pInterface[YUTBOARD]);
	SAFE_DELETE_RES(m_pInterface[FISHING]);
	SAFE_DELETE_RES(m_pInterface[FISHING_REWARD]);
	SAFE_DELETE_RES(m_pInterface[BASEBALL]);
	SAFE_DELETE_RES(m_pInterface[BASEBALL_REWARD]);
	SAFE_DELETE_RES(m_pInterface[LOTTO]);
	SAFE_DELETE_RES(m_pInterface[BINGO]);
	SAFE_DELETE_RES(m_pInterface[LETTER_WINDOW]);
	SAFE_DELETE_RES(m_pInterface[LETTER_SEND]);
	SAFE_DELETE_RES(m_pInterface[LETTER_RECV]);
	SAFE_DELETE_RES(m_pInterface[LOTTERY]);
	SAFE_DELETE_RES(m_pInterface[DICEGAME]);
	SAFE_DELETE_RES(m_pInterface[DICEGAME_REWARD]);

	if(m_pGamble)
	{
		delete m_pGamble;
		m_pGamble = NULL;
		if(IsGambleVisible())
			ShowGambleWindow(false);
	}

	if(m_pLockSmith)
	{
		delete m_pLockSmith;
		m_pLockSmith = NULL;
		if(IsLockSmith())
			ShowLockSmithWindow(false);
	}

	if(m_pEventAncient)
	{
		delete m_pEventAncient;
		m_pEventAncient = NULL;
		if(IsEventAncientVisible())
			ShowEventAncientWindow(false);
	}
	if(m_pPlatinum)
	{
		delete m_pPlatinum;
		m_pPlatinum = NULL;
		if(IsPlatinumVisible())
			ShowPlatinumWindow(false);
	}
	if(m_pSummerEvent)
	{
		delete m_pSummerEvent;
		m_pSummerEvent = NULL;
		if(IsSummerEventVisible())
			ShowSummerEventWindow(false);
	}
	if(m_pRefine)
	{
		delete m_pRefine;
		m_pRefine = NULL;
		if(IsRefineVisible())
			ShowRefineWindow(false);
	}
	if( m_pUpgrade ) ///�Ź���ȭ�ý���
	{
		delete m_pUpgrade;
		m_pUpgrade = NULL;
		if( IsUpgradeVisible() )
			ShowUpgradeWindow( false );	// �̰� ���� Toggle�� �Ȳ��൵ �ȴ�. �����͸� ����� ���ҽ� ���� �ϴϱ�.
	}
	if( m_pControlNotice ) ///�����˾�â
	{
		delete m_pControlNotice;
		m_pControlNotice = NULL;
		m_bShowNotice = false;
	}
	if( m_pUserShopSearch ) ///���λ����˻�


	{
		delete m_pUserShopSearch;
		m_pUserShopSearch = NULL;
		if( IsUserShopSearchVisible() )
			ShowUserShopSearchWindow( false );	// �̰� ���� Toggle�� �Ȳ��൵ �ȴ�. �����͸� ����� ���ҽ� ���� �ϴϱ�.
	}
	if(m_pProcess)
	{
		delete m_pProcess;
		m_pProcess = NULL;
		if(IsProcessVisible())
			ShowProcessWindow(false);
	}
	// ��ŸƮ ȭ��


	SAFE_DELETE_RES(m_pStartSheet);

//	else
	{
		SAFE_DELETE( g_pNvNWin ); ///�������¸� ��ũ

//==============================================
		// nate 2004 - 4 : CastleWar
		SAFE_DELETE( g_pImgKing1 );
		SAFE_DELETE( g_pImgKing2 );
		SAFE_DELETE( g_pImgKing3 );
		SAFE_DELETE( g_pImgKing4 );
//==============================================
		SAFE_DELETE(g_pPK);
		SAFE_DELETE(g_pNonPK);
		SAFE_DELETE(g_pGuildpk);

		if( g_bGlobalMatrix ) ///����������

		{
			SAFE_DELETE( g_pMatrixKor );
			SAFE_DELETE( g_pMatrixJpn );
		}

		// nate : �븸 �Ŵް���
		if( g_dwClientCountry == CTRY_TWN )
			SAFE_DELETE( g_pMedal );
	}

	SAFE_DELETE(m_pInfoBox);
	SAFE_DELETE(m_pInfoBox2);

	SAFE_DELETE_RES(m_pControlSelMenu);

}

void CNk2DFrame::DeleteStartSheet()
{
	SAFE_DELETE(m_pStartSheet);
}

BOOL CNk2DFrame::UpdateFrame()
{
	static int nSleep = 0;

	if (m_GraphicMode == NKGRAPHIC2D)
	{
		if( g_pDisplay )
			g_pDisplay->Clear();
		if (m_pStartSheet)
			m_pStartSheet->Draw();
	}
	else if (m_GraphicMode == NKGRAPHIC3D)
	{
		if( !pCMyApp->m_bWaitingAt
				&& !pCMyApp->m_bBeforeTrans
				&& !pCMyApp->m_bBeforeGoWorld )
			SendTickTime();

		GetCursorPos(&g_CursorPoint);
		ScreenToClient(g_pDisplay->GetHWnd(), &g_CursorPoint);


		if( m_ui_op_event->IsActivate() )
			m_ui_op_event->Draw();

		if (m_ui_friend && m_ui_friend->IsVisible())
			m_ui_friend->Draw();

		if( m_ui_buffitem )
			m_ui_buffitem->Draw();

		if( m_ui_decardibattle )
		{
			m_ui_decardibattle->Update();
			m_ui_decardibattle->Draw();
		}


		int over_skill = SKILL_UNSELECTED;
		int over_skill2 = SKILL_UNSELECTED;
		CItem *pInvenOverItem = NULL;
		CItem *pExchangeOverItem = NULL;
		CItem *pWareOverItem = NULL;
		CItem *pUserShopOverItem = NULL; ///���λ���
		CItem *pBottomOverItem = NULL;
		CItem *pShopOverItem = NULL;
		CItem *pInterchangeOverItem = NULL;
		CItem *pProductOverItem = NULL;
		CItem *pPetProductOverItem = NULL;
		CItem *pGambleOverItem = NULL;

		CItem *pLockSmithOverItem = NULL;

		CItem *pRefineOverItem = NULL;
		CItem *pUpgradeOverItem = NULL;	///�Ź���ȭ�ý���
		CItem *pPieceShopOverItem = NULL;
		CItem *pEventAncientOverItem = NULL;
		CItem *pPlatinumOverItem = NULL;
		CItem *pSummerEventOverItem = NULL;
		CItem *pProcessOverItem = NULL;
		CItem *pGuildStoreItem = NULL;
		CItem *pPremiumChaMoveItem = NULL;
		CItem *pPetEquipOverItem = NULL;

		if (m_pPremiumExchange && m_bShowPremiumExchange)
			m_pPremiumExchange->Draw();


		if( m_pUIWindow )
			m_pUIWindow->Draw();

		if(m_pTgaUIWindow && g_SvrType == ST_ADULT_ONLY) m_pTgaUIWindow->Draw();


		if( !CheckFullScreenInterface() && 
				( m_bViewTop ||		m_bInven ||			m_bInterface[SCORE]	||		m_bInterface[MAP] ||
				  m_bSkill ||			m_bHelp ||			m_bParty ||					m_bPetStatus ||
				  m_bInterface[QUEST] || m_bInterface[DOCUMENT] || m_bHelper
				  || m_bShowControlGuild 	|| m_bShowControlGuildManage
				  || m_bHeroFinalRank
				))
		{
			if( m_pControlTop )
				m_pControlTop->Draw();

			if( m_pControlStatus )
				m_pControlStatus->Draw();

			if( g_bAdmin )
			{
				if( m_pControlBottom )
				{
					over_skill2 = m_pControlBottom->Draw(&pBottomOverItem);
					m_pControlBottom->Draw_Chatting();
				}
			}
		}

		if( !g_bAdmin )
		{
			if( !CheckFullScreenInterface() ) // Ǯ��ũ�� �������̽����������� bottom�� �ȱ׸���. ///�������.
			{
				if( m_pControlBottom )
				{
					over_skill2 = m_pControlBottom->Draw(&pBottomOverItem);
					m_pControlBottom->Draw_Chatting();
				}
			}
		}
		if( m_pControlSelMenu && m_bShowControlSelMenu )
			m_pControlSelMenu->Draw();

		if( m_bShowDmitronBattleStatus && m_pDmitronBattleStatus)
		{
			m_pDmitronBattleStatus->Draw();
		}
		/***************************************************************************************/
		//- ž �޴� ���� ������



		if (m_bMenu)
			m_pControlMenu->Draw();

		// �������
		if( m_bShowCashShop )
			m_pControlCashShop->Draw();

		if (m_bShop)
			pShopOverItem = m_pControlShop->Draw();

		if (m_bPeiceShop)
			pPieceShopOverItem = m_pControlPeiceShop->Draw();

		// â��

		if (m_bShowWareHouse)
			pWareOverItem = m_pControlWareHouse->Draw();

		// ���λ���
		if( m_bShowUserShop)
			pUserShopOverItem = m_pControlUserShop->Draw();

		// �κ�
		if( m_bInven)
			pInvenOverItem = m_pControlInven->Draw();

		// ��
		if( m_bPetStatus)
			pPetEquipOverItem = m_pControlPetStatus->Draw();

		// ����
		if( m_bHelp)
			m_pControlHelp->Draw();

		// ��ų
		if( m_bSkill)
			over_skill = m_pControlSkill->Draw();

		// ��Ƽ
		if (m_bParty)
			m_pControlParty->Draw();

		// �İ���
		if (m_bHelper&&m_pControlHelper)
			m_pControlHelper->Draw();



		if( m_bInterface[SOCIAL])
			m_pInterface[SOCIAL]->Draw();

		if( m_bInterface[GATE])
			m_pInterface[GATE]->Draw();

		if( GetGate() )
			GetGate()->Draw();


		if( m_bInterface[SCORE])
			m_pInterface[SCORE]->Draw();

		// ����
		if( m_bInterface[MAP])
			m_pInterface[MAP]->Draw();

		if( m_bInterface[DOCUMENT])
			m_pInterface[DOCUMENT]->Draw();

		// ����Ʈ
		if (m_bInterface[QUEST])
			m_pInterface[QUEST]->Draw();
// 		else
// 			((CQuestData*)m_pInterface[QUEST])->CloseRes();

		if( m_bInterface[YUTBOARD] )
			m_pInterface[YUTBOARD]->Draw();

		if( m_pInterface[FISHING] )
			m_pInterface[FISHING]->Update();
		if( m_bInterface[FISHING] )
			m_pInterface[FISHING]->Draw();

		if( m_bInterface[FISHING_REWARD] )
			m_pInterface[FISHING_REWARD]->Draw();

		if( m_pInterface[BASEBALL] )
			m_pInterface[BASEBALL]->Update();
		if( m_bInterface[BASEBALL] )
			m_pInterface[BASEBALL]->Draw();
						 
		if( m_bInterface[BASEBALL_REWARD] )
			m_pInterface[BASEBALL_REWARD]->Draw();

		if( m_pInterface[LOTTO] )
			m_pInterface[LOTTO]->Update();
		if( m_bInterface[LOTTO] )
			m_pInterface[LOTTO]->Draw();

		if( m_pInterface[BINGO] )
			m_pInterface[BINGO]->Update();
		if( m_bInterface[BINGO] )
			m_pInterface[BINGO]->Draw();

		if( m_pInterface[LETTER_WINDOW] )
			m_pInterface[LETTER_WINDOW]->Update();
		if( m_bInterface[LETTER_WINDOW] )
			m_pInterface[LETTER_WINDOW]->Draw();

		if( m_pInterface[LETTER_SEND] )
			m_pInterface[LETTER_SEND]->Update();
		if( m_bInterface[LETTER_SEND] )
			m_pInterface[LETTER_SEND]->Draw();

		if( m_pInterface[LETTER_RECV] )
			m_pInterface[LETTER_RECV]->Update();
		if( m_bInterface[LETTER_RECV] )
			m_pInterface[LETTER_RECV]->Draw();

		if( m_pInterface[LOTTERY] )
			m_pInterface[LOTTERY]->Update();
		if( m_bInterface[LOTTERY] )
			m_pInterface[LOTTERY]->Draw();

		if( m_pInterface[DICEGAME] )
			m_pInterface[DICEGAME]->Update();
		if( m_bInterface[DICEGAME] )
			m_pInterface[DICEGAME]->Draw();
						 
		if( m_bInterface[DICEGAME_REWARD] )
			m_pInterface[DICEGAME_REWARD]->Draw();

		// �÷�Ƽ��
		if(m_bShowPlatinum)
			pPlatinumOverItem = m_pPlatinum->Draw();

		//
		if(m_bShowRefine)
			pRefineOverItem = m_pRefine->Draw();

		//
		if( m_bShowUpgrade )	///�Ź���ȭ�ý���
			pUpgradeOverItem = m_pUpgrade->Draw();

		// ���� ���� �˻�

		if( m_bShowUserShopSearch )	///���λ����˻�

			m_pUserShopSearch->Draw();



		{
			// �ñԼ��� ��� â��

			if(m_bShowGStoreHouse )
				pGuildStoreItem = m_pControlGStoreHouse->Draw();

			if (m_bShowControlGuild && m_pControlGuild)
				m_pControlGuild->Draw();		// ���


			if(m_bShowControlGuildManage && m_pControlGuildManager)
				m_pControlGuildManager->Draw();

			if( m_bHeroFinalRank && m_pHeroFinalRank )
				m_pHeroFinalRank->Draw();

		}
		/***************************************************************************************/

		if( m_bShowPVPWidget && m_pPVPWidget )
			m_pPVPWidget->Draw();

		if (m_bLetter)
			m_pControlLetter->Draw();

		if (m_bShowExchange)
			pExchangeOverItem = m_pControlExchange->Draw();
		if (m_bInterchange)
			pInterchangeOverItem = m_pInterchange->Draw();
		if (m_bProduct)
			pProductOverItem = m_pProduct->Draw();
		if(m_bPetProduct)
			pPetProductOverItem = m_pPetProduct->Draw();
		if(m_bShowGamble)
			pGambleOverItem = m_pGamble->Draw();

		if(m_bLockSmith)
			pLockSmithOverItem = m_pLockSmith->Draw();


		if(m_bShowEventAncient)
			pEventAncientOverItem = m_pEventAncient->Draw();

		if(m_bShowSummerEvent)
			pSummerEventOverItem = m_pSummerEvent->Draw();

		if( m_bShowProcess )	//����
			pProcessOverItem = m_pProcess->Draw();


		if( m_ui_takebox )
			m_ui_takebox->Draw();


		if (m_bRShift)
			m_pRShiftMenu->Draw();
		if (m_bLShift && m_pLShiftMenu)
			m_pLShiftMenu->Draw();
		if (m_bPetLevel && m_pPet_Level)
			m_pPet_Level->Draw();
		if(m_pControlInven && m_pControlInven->m_plus5Message.m_bActive)
			m_pControlInven->m_plus5Message.Draw();

		if (m_bWorldCup)
		{
			m_pWorldCup->Draw();
			m_pWorldCup->DrawScore();
		}

		// [5/6/2008 �����] ����� ��û. ä�� �۾��� ������� â ������ �׷�����.
		if( m_bShowCashShop ) ///�������
			m_pControlCashShop->Draw();
		if( m_bShowCashShopIntro ) ///�������
			m_pCashShopIntro->Draw();

//========================================================================
// ������ ���� ���
		if( m_pControlCashShop && m_pControlCashShop->m_pInvenOverItem ) // �κ�â�� DrawItemInfo �� ���⼭ ����� ����� ��������. ///�������
			m_pControlInven->DrawItemInfo(m_pControlCashShop->m_pInvenOverItem, ITEM_INFO_INVEN);
		else if (pInvenOverItem)
			m_pControlInven->DrawItemInfo(pInvenOverItem, ITEM_INFO_INVEN);
		else if (pPetEquipOverItem)
			m_pControlInven->DrawItemInfo(pPetEquipOverItem, ITEM_INFO_INVEN);
		else if (pExchangeOverItem)
			m_pControlInven->DrawItemInfo(pExchangeOverItem, ITEM_INFO_EXCHANGE);
		else if (pInterchangeOverItem)
			m_pControlInven->DrawItemInfo(pInterchangeOverItem, ITEM_INFO_INTERCHANGE);
		else if (pProductOverItem)
			m_pControlInven->DrawItemInfo(pProductOverItem, ITEM_INFO_PRODUCT);
		else if(pPetProductOverItem)
			m_pControlInven->DrawItemInfo(pPetProductOverItem, ITEM_INFO_PETPRODUCT);
		else if (pBottomOverItem)
			m_pControlInven->DrawItemInfo(pBottomOverItem, ITEM_INFO_BOTTOM);
		else if (pShopOverItem)
			m_pControlInven->DrawItemInfo(pShopOverItem, ITEM_INFO_SHOP);
		else if (pWareOverItem)
			m_pControlInven->DrawItemInfo(pWareOverItem, ITEM_INFO_WAREHOUSE);
		else if (pUserShopOverItem) ///���λ���
			m_pControlInven->DrawItemInfo(pUserShopOverItem, ITEM_INFO_USERSHOP);
		else if(pGambleOverItem)
			m_pControlInven->DrawItemInfo(pGambleOverItem, ITEM_INFO_INTERCHANGE);

		else if(pLockSmithOverItem)
			m_pControlInven->DrawItemInfo(pLockSmithOverItem, ITEM_INFO_INTERCHANGE);
		else if(pEventAncientOverItem)
			m_pControlInven->DrawItemInfo(pEventAncientOverItem, ITEM_INFO_INTERCHANGE);
		else if(pPlatinumOverItem)
			m_pControlInven->DrawItemInfo(pPlatinumOverItem,ITEM_INFO_INTERCHANGE);	/// ITEM_INFO_PLATINUM ���� ����


		else if(pSummerEventOverItem)
			m_pControlInven->DrawItemInfo(pSummerEventOverItem,ITEM_INFO_INTERCHANGE);
		else if(pRefineOverItem)
			m_pControlInven->DrawItemInfo(pRefineOverItem, ITEM_INFO_INTERCHANGE);
		else if(pUpgradeOverItem) ///�Ź���ȭ�ý���
			m_pControlInven->DrawItemInfo(pUpgradeOverItem, ITEM_INFO_INTERCHANGE);
		else if (pPieceShopOverItem)
			m_pControlInven->DrawItemInfo(pPieceShopOverItem, ITEM_INFO_PIECESHOP);
		else if(pProcessOverItem)
			m_pControlInven->DrawItemInfo(pProcessOverItem, ITEM_INFO_INTERCHANGE);

		if( m_pSpiritMode && m_bSpiritStart ) ///�굵�� �ÿ� ��ġ�ű�.
			m_pSpiritMode->Draw();

		if( m_bHelpPet && m_pControlHelpPet ) ///�굵��
		{
			m_pControlHelpPet->FrameMove();		// ��ġ ������ ����!
			m_pControlHelpPet->Draw();		// ��ġ ������ ����!
		}

		if( m_bAutoMouse )//(m_bAutoMouse && m_bAutoMouse) ///07-04-12 ����Ȯ�� �ý��� Ÿ �������̽��� �Բ� �� �� �ְ� ����.
		{
//			m_pControlBottom->m_CurTextView = 13;//TEXTVIEW_EXP(ê��â ��ư �÷���)
//			m_pControlBottom->m_bAct = TRUE; // ê��â ũ�� �÷���
			m_pAutoMouse->Draw();
		}

		if( m_pControlInven && !m_Popup )
			m_pControlInven->DrawExtra();

		if( !CheckFullScreenInterface() )
		{
			if( m_pControlSkill )
			{
				if (over_skill != SKILL_UNSELECTED)
					m_pControlSkill->DrawSkillInfo(over_skill);
				else if (over_skill2 != SKILL_UNSELECTED)
					m_pControlSkill->DrawSkillInfo(over_skill2);
			}
		}

		/// ������ ǳ������ �׸����� ����.DrawItemInfo�� �ϰ� �ִٸ� �׸��� �ʴ´�.
		if( m_pControlBottom )
		{
			if (pBottomOverItem)
				m_pControlBottom->m_bDrawQuick = FALSE;
			else
				m_pControlBottom->m_bDrawQuick = TRUE;
		}

		if( m_bBossraidInfo && m_pBossraidInfo )
			m_pBossraidInfo->Draw();

		if( m_bHeroPrivilege && m_pHeroPrivilege )
			m_pHeroPrivilege->Draw();

		if( m_bHeroRankList && m_pHeroRankList )
			m_pHeroRankList->Draw();

		if( m_bShowNotice )	///�����˾�â
			m_pControlNotice->Draw();

		if( m_bShowPremiumChaMove )
			pPremiumChaMoveItem = m_pPremiumChaMove->Draw();

		if(pPremiumChaMoveItem)
			m_pControlInven->DrawItemInfo(pPremiumChaMoveItem, ITEM_INFO_INVEN);

//========================================================================
		if( m_Popup )		// nate 2006-02-28 : ���� ������ �˾��� �׸���.
			m_Popup->pMsg_Popup.Draw();



		// ����� exchange item ������ �����ִ� �Լ��� ȣ��.
		if (m_pInfoBox && pCMyApp->m_pUIMgr->IsEventScenePlaying() != 1 ) // �̺�Ʈ �� �÷��� �߿� �����޼��� �ȶߵ���... ///�δ�1�� �߰� ///Ʃ�丮��� ���� ����

		{
			DWORD curTime = timeGetTime();
			if (curTime > m_InfoTime + 500)
			{
				m_InfoTime = curTime;
				m_InfoFrame++;
			}
			if( m_InfoFrame % 3 )
				m_pInfoBox->Draw();

			if (m_InfoFrame > 20)
			{
				SAFE_DELETE(m_pInfoBox);
				if( m_InfoNextString.length() > 0)
				{
					AddChatStr((char*)m_InfoNextString.c_str(), 4);
					SetInfoBox((char*)m_InfoNextString.c_str(), false);
					m_InfoNextString = "";
				}
			}
		}
		if (m_pInfoBox2 && pCMyApp->m_pUIMgr->IsEventScenePlaying() != 1 ) // �̺�Ʈ �� �÷��� �߿� �����޼��� �ȶߵ���... ///�δ�1�� �߰� ///Ʃ�丮��� ���� ����

		{
			DWORD curTime = timeGetTime();
			if (curTime > m_InfoTime2 + 500)
			{
				m_InfoTime2 = curTime;
				m_InfoFrame2++;
			}
			if( m_InfoFrame2 % 3 )
				m_pInfoBox2->Draw();

			if (m_InfoFrame2 > 20)
			{
				SAFE_DELETE(m_pInfoBox2);

				if( m_InfoNextString2.length() > 0)
				{
					AddChatStr((char*)m_InfoNextString2.c_str(), 4);
					SetInfoBox2((char*)m_InfoNextString2.c_str(), RGB(255, 0, 255), RGB(100, 100, 250));					
					m_InfoNextString2 = "";
				}
			}
		}
	}
	else if (m_GraphicMode == NKGRAPHICLOADING)
	{	
		if ( nSleep < 100 )
		{
			if( g_pDisplay )
				g_pDisplay->Clear(0);
			nSleep++;
		}
		else
		{
			if (m_pStartSheet->IsStarting() == START_GAME)
				pCMyApp->StartGame();			
		}
	}	

	BuffItemMgr::GetInstance()->Update();

	return TRUE;
}

void CNk2DFrame::SetInfoBox(char *msg, bool removeInfo2)
{
	int font_size = 16;
	int len;

	SAFE_DELETE(m_pInfoBox);
	if( removeInfo2 == true )
	{
		SAFE_DELETE(m_pInfoBox2);
	}	

	if ((len = strlen(msg)) <= 0)
		return;

	m_pInfoBox = new CTextOutBox;
	if( m_pInfoBox )
	{
		m_pInfoBox->Init(font_size, RGB(255, 0, 255), (GetClientWidth()-len*(font_size/2)) / 2, 100);
		m_pInfoBox->SetString_withOutLine( msg, RGB(255, 255, 255), RGB(100, 100, 250) ); // ���� : ��, ���ڻ�, �ܰ��� ��
	}
	m_InfoTime = timeGetTime();
	m_InfoFrame = 0;

	m_InfoNextString = "";
}

void CNk2DFrame::SetInfoBox2(char *msg, COLORREF fontColor, COLORREF outlineColor) // ��Ʈ���� ���ְ� ���� ��¿�. (��� �����ʹ� ��ġ�� ������ �ٸ���.) (by ����)
{
	int font_size = 16;
	int len;

	SAFE_DELETE(m_pInfoBox2);	

	if ((len = strlen(msg)) <= 0)
		return;

	m_pInfoBox2 = new CTextOutBox;
	if( m_pInfoBox2 )
	{
		m_pInfoBox2->Init(font_size, fontColor, (GetClientWidth()-len*(font_size/2)) / 2, 120);
		m_pInfoBox2->SetString_withOutLine( msg, RGB(255, 255, 255), outlineColor ); // ���� : ��, ���ڻ�, �ܰ��� ��
	}
	m_InfoTime2 = timeGetTime();
	m_InfoFrame2 = 0;

	m_InfoNextString2 = "";
}

void CNk2DFrame::SetInfoBox_NextString(const std::string& strMsg)
{
	m_InfoNextString = strMsg;
}

void CNk2DFrame::SetInfoBox_NextString2(const std::string& strMsg)
{
	m_InfoNextString2 = strMsg;
}

//---------------------------------------------------------------------
// AddChatStr()
//---------------------------------------------------------------------
void CNk2DFrame::AddChatStr(char *str, int say_type)
{
	if( m_pControlBottom )
		m_pControlBottom->AddStrQlist(str, say_type);
}

void CNk2DFrame::AddChatStr(int index, int say_type)
{
	// index ��!!!
	AddChatStr((char*)G_STRING(index), say_type);
}

void CNk2DFrame::AddChatStr_ExtraInfo(char* str, int say_type, int infoType, int infoVnum)
{
	if( m_pControlBottom )
		m_pControlBottom->AddStrQlist_ExtraInfo(str, say_type, infoType, infoVnum);
}

void CNk2DFrame::AddChatShoutStr(char* str)
{
	if( m_pControlBottom )
		m_pControlBottom->AddStrShoutList(str);
}

void CNk2DFrame::SetNkCha(CNkCharacter *pNkCha)
{
	if( m_pControlBottom )		m_pControlBottom->SetNkCha(pNkCha);
	if( m_pControlShop )		m_pControlShop->SetNkCha(pNkCha);
	if( m_pControlExchange )	m_pControlExchange->SetNkCha(pNkCha);
	if( m_pControlWareHouse )	m_pControlWareHouse->SetNkCha(pNkCha);
	if( m_pControlUserShop )	m_pControlUserShop->SetNkCha(pNkCha); ///���λ���
	if( m_pInterchange )		m_pInterchange->SetNkCha(pNkCha);
	if( m_pProduct )			m_pProduct->SetNkCha(pNkCha);
	if( m_pPetProduct )			m_pPetProduct->SetNkCha(pNkCha);
	if( m_pControlInven )		m_pControlInven->SetNkCha(pNkCha);
	if( m_pInterface[SCORE] )	g_pRoh->SetScoreWnd((CControlScore*)m_pInterface[SCORE]);
	if( m_pInterface[SCORE] )	((CControlScore*)m_pInterface[SCORE])->SetAllScore();
	if( m_pControlSkill )		m_pControlSkill->SetNkCha(pNkCha);
	if( m_pControlPeiceShop )	m_pControlPeiceShop->SetNkCha(pNkCha);

	{
		if( m_pControlGStoreHouse)	m_pControlGStoreHouse->SetNkCha(pNkCha);
	}

	m_pNkCha = pNkCha;

}



void CNk2DFrame::ShowControlSelMenu(BOOL bShow )
{
	if( !CloseAllWindow(FALSE) )
		return;

	if( m_pControlSelMenu )
		m_bShowControlSelMenu = bShow;

	if( bShow)
		pCMyApp->StopHero();
}

BOOL CNk2DFrame::ControlSelmenuSetMetuList(int type, char * arg )
{
	return m_pControlSelMenu->SetMenuList(type, arg);
}
void CNk2DFrame::ControlSelmenuAddStart()
{
	m_pControlSelMenu->AddMenuStart();
}

void CNk2DFrame::ControlSelmenuAddPush(int vnum)
{
	m_pControlSelMenu->AddMenuPush(vnum);
}

void CNk2DFrame::ControlSelmenuAddEnd()
{
	m_pControlSelMenu->AddMenuEnd();
}


void CNk2DFrame::ShowLetterWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( m_pControlLetter )
	{
		m_pControlLetter->LetterListMessage(g_nServerIndex,g_pRoh->m_pstrName,g_pRoh->m_nUserIndex,1);
		m_pControlLetter->PutList();
	}

	if( bShow )
	{
		m_bLetter = bShow; // �ʿ��� �͸� Ų��.

		if( m_pControlInven )
			m_pControlInven->ResetItemInfo();

		if( m_pControlLetter )
			m_pControlLetter->m_bActive = true;
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

void CNk2DFrame::ShowShopWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( GetControlShop() )
		GetControlShop()->SetLpShopFlag(FALSE);

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShop = bShow;

		if( m_pControlInven )
			m_pControlInven->ResetItemInfo();

		pCMyApp->StopHero();
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}


void CNk2DFrame::ShowPeiceShopWindow (BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		if ( m_pControlPeiceShop )
			m_pControlPeiceShop->LoadShopItems(); // ��ȭ �۾��� ���� ������ ��� Ÿ�̹��� �������̽� ������ �ű�.

		m_bPetStatus = TRUE;
		m_bPeiceShop = bShow;

		if( m_pControlInven )
			m_pControlInven->ResetItemInfo();

		pCMyApp->StopHero();
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}


void CNk2DFrame::ShowWareHouseWindow(BOOL bShow)  ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	// ����  â�� ��ǰ ����Ʈ�� �� �����ش����� â�� �̹����� �����ش�.
	//m_bShowWareHouse = bShow; // (�̰� �������̽� Ŭ���� ó�� �Լ�ȭ �߿� �ּ��ܰ� �ƴ�.)
	if (bShow)
	{
		m_bInven = TRUE;
		m_pControlWareHouse->ActivateWareHouse(TRUE);

		pCMyApp->StopHero();
	}
	else
	{
	}
}

void CNk2DFrame::ShowGStoreHouseWindow(BOOL bShow)
{
	if( !CloseAllWindow(FALSE) )
		return;

	if (bShow)
	{
		m_bInven = TRUE;
		m_pControlGStoreHouse->ActivateGStoreHouse(TRUE, g_pRoh->GetGuildLevel());
		pCMyApp->StopHero();
	}
	else
	{
	}
}

void CNk2DFrame::ToggleGambleWindow(int type) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if (m_pGamble && m_pGamble->IsOnGamble() == TRUE)
		return;
	if(Check_All_MsgPopUp())
		return;

	ShowGambleWindow(!m_bShowGamble);
	if(IsGambleVisible())
	{
		SAFE_DELETE_RES(m_pGamble);
		ShowGambleWindow(false);

		m_pGamble->LoadRes(type, m_pItemRender);
		m_pGamble->SetNkCha(m_pNkCha);
		ShowGambleWindow(true);
		m_pGamble->m_nMoney = g_pRoh->m_Money;

		pCMyApp->StopHero();
	}
	else
	{
		if(m_pGamble)
			if(m_pGamble->m_bReceiveMsg)
				m_pGamble->ForcingCloseGamble();
	}
}

void CNk2DFrame::ToggleLockSmithWindow(void) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if (m_pLockSmith && IsLockSmith() )
		return;

	if(Check_All_MsgPopUp())
		return;

	ShowLockSmithWindow(!m_bLockSmith);
	if( IsLockSmith() )
	{
		SAFE_DELETE_RES(m_pLockSmith);
		ShowLockSmithWindow(false);

		m_pLockSmith->LoadRes( m_pItemRender);
		ShowLockSmithWindow(true);

		pCMyApp->StopHero();
	}
}

void CNk2DFrame::ShowLockSmithWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
// ���� �����츦 �����ش�.
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bLockSmith = bShow;
	}
	else
	{
		m_bInven = FALSE;
		m_bLockSmith = bShow;
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}


//0120
void CNk2DFrame::ToggleEventAncientWindow(int type)
{
	if (m_pGamble && m_pGamble->IsOnGamble() == TRUE)
		return;

	if(Check_All_MsgPopUp())
		return;

	ShowEventAncientWindow(!m_bShowEventAncient);
	if(IsEventAncientVisible())
	{
		SAFE_DELETE_RES(m_pEventAncient);
		ShowEventAncientWindow(false);

		m_pEventAncient->LoadRes(type, m_pItemRender);
		m_pEventAncient->SetNkCha(m_pNkCha);
		ShowEventAncientWindow(true);

		pCMyApp->StopHero();
	}
}

void CNk2DFrame::ToggleRefineWindow(int type)
{
	if (m_pGamble && m_pGamble->IsOnGamble() == TRUE)
		return;

	if(Check_All_MsgPopUp())
		return;

	ShowRefineWindow(!m_bShowRefine);
	if(IsRefineVisible())
	{
		SAFE_DELETE_RES(m_pRefine);
		ShowRefineWindow(false);
		m_pRefine->LoadRes(type, m_pItemRender);
		m_pRefine->SetNkCha(m_pNkCha);
		ShowRefineWindow(true);

		pCMyApp->StopHero();
	}
	else
	{
		if(m_pRefine)
		{
			if (m_pRefine->IsRefineConnection())
				m_pRefine->CloseConnection();
		}
	}
}

//  nate
void CNk2DFrame::ShowGambleWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
// ���� �����츦 �����ش�.
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShowGamble = bShow;

		pCMyApp->StopHero();
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

//0120
void CNk2DFrame::ShowEventAncientWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShowEventAncient = bShow;

		pCMyApp->StopHero();
	}
	else // ������ 07-01-15 �߰�
		pCMyApp->ConvertImmStatus(); // �̰������ ������ �ݾ����� Ǯ���ִ� ��.(�̰� �����ָ� �Ϻ� �������� �Է��ߵ�ÿ� ������ ����)

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

// nate
void CNk2DFrame::ShowRefineWindow(BOOL bShow, int type) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
// ����â �ٿ��


{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	// ����â�� ���ִ��� Ȯ��
	if( bShow )
	{
		if( m_pRefine )
		{
			m_pRefine->LoadRes(type, m_pItemRender);
			m_pRefine->SetNkCha(m_pNkCha);

			pCMyApp->StopHero();
		}

		m_bInven = TRUE;
		m_bShowRefine = bShow;

	}
	else
	{
		if(m_pRefine)
		{
			if (m_pRefine->IsRefineConnection())
				m_pRefine->CloseConnection();

			SAFE_DELETE_RES(m_pRefine);
		}
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

void CNk2DFrame::SetShowWareHouseFlag(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bShowWareHouse = bShow;
		m_bInven = TRUE;

		pCMyApp->StopHero();
	}
}


void CNk2DFrame::SetShowGStoreHouseFlag(BOOL bShow)
{
	if( !CloseAllWindow(FALSE) )
		return;

	if( bShow )
	{
		m_bShowGStoreHouse = bShow;
		m_bInven = TRUE;

		pCMyApp->StopHero();
	}
}

void CNk2DFrame::ShowExchangeWindow(BOOL bShow, BOOL bExch) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;				// shop�� inven�� ������ �߿��ϴ�.
		m_bShowExchange = bShow;
	}

	if (m_bShowExchange && bExch == TRUE)
		m_pControlExchange->ActivateExch(bExch);
	else if (m_bShowExchange == FALSE && bExch == FALSE)
		m_pControlExchange->ActivateExch(FALSE);
	else if (m_bShowExchange == FALSE && bExch == TRUE)
		return;
	else
		m_pControlExchange->ActivateExch(FALSE);
}

void CNk2DFrame::ShowInterchangeWindow(BOOL bShow, BOOL bInter) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;				// shop�� inven�� ������ �߿��ϴ�.
		m_bInterchange = bShow;

		pCMyApp->StopHero();
	}

	if (m_bInterchange && bInter)
		m_pInterchange->ActivateExch(TRUE);
	else
		m_pInterchange->ActivateExch(FALSE);
}


void CNk2DFrame::ShowProductWindow(BOOL bShow, BOOL bAct) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;				// shop�� inven�� ������ �߿��ϴ�.
		m_bProduct = bShow;

		pCMyApp->StopHero();
	}

	if (m_bProduct && bAct)
		m_pProduct->ActivateExch(TRUE);
	else
		m_pProduct->ActivateExch(FALSE);
}

void CNk2DFrame::ShowInvenWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = bShow;
	}
}


void CNk2DFrame::ShowInterfaceWindow(bool bShow, int nNum, int nCurWorldNum, int nSlot_num) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
// by evilkiki 2009.11.05 ��巩ŷ�� : ����Ʈ ��Ż �ȿ�������
	if( g_SvrType == ST_GUILD_RANK && nNum == GATE )
		return;

	if( !CloseAllWindow(FALSE, (nNum==GATE?true:false)) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		if( nNum == GATE )
		{
			((CControlGate*)m_pInterface[GATE])->SetCurWorld(nCurWorldNum);
		}
		if( nNum == DOCUMENT )
		{
			((CControlDocument*)m_pInterface[DOCUMENT])->SetDocument(nCurWorldNum);
			m_iQuicSlotNum = nSlot_num;
		}

		if( nNum == MAP || nNum == QUEST || nNum == SCORE || nNum == YUTBOARD || nNum == FISHING || nNum == FISHING_REWARD ||
			nNum == LOTTO || nNum == BINGO || nNum == LETTER_WINDOW || nNum == LETTER_SEND || nNum == LETTER_RECV || 
			nNum == BASEBALL || nNum == BASEBALL_REWARD || nNum == LOTTERY ||
			nNum == DICEGAME || nNum == DICEGAME_REWARD)
		{
		}
		else
		{
			pCMyApp->StopHero();
		}
	}
	m_bInterface[nNum] = bShow;
}

void CNk2DFrame::SetVisibleInterface(bool bVisible, int nNum)
{
	m_bInterface[nNum] = bVisible;
}

void CNk2DFrame::ShowPetStatusWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bPetStatus = bShow;
	}
}


void CNk2DFrame::ShowSkillWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bSkill = bShow;
	}
}


void CNk2DFrame::ShowHelpWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bHelp = bShow;
	}
	else
	{
		m_pControlHelp->SelectDeleteRes();
	}
}

void CNk2DFrame::ShowPartyWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bParty = bShow;
	}
}

static char * spChar_jpn = "`��������������?����������������������������������������������?@";

static bool IsTowByte(char str)
{
	bool bTwobyte = false;

	// ASCII ..
	if((unsigned char)str  >= 0x20 && (unsigned char)str  <=0x7E)
	{
		bTwobyte = false;
	}
	// 2BYTE STRING (HANJA first byte / kata(JUN GAK) / hira)
	else if((unsigned char)str  >= 0x81 && (unsigned char)str  <=0x9F)
	{
		bTwobyte = true;
	}
	// 2BYTE STING (HANJA first byte)
	else if((unsigned char)str  >= 0xE0 && (unsigned char)str  <=0xEF)
	{
		bTwobyte = true;
	}
	// 1BYTE STRING
	else
		bTwobyte = false;

	return bTwobyte;
}


static char *ExamSpChar_for_jpn(char *str)
{
	static char found_sp[3];
	found_sp[0] = '\0';

	int len = strlen(str);
	int splen;

	splen = strlen(spChar_jpn);

	bool input_str_byte = false;
	bool list_str_byte = false;
	int z;
	for (int pos = 0; pos < len; pos++)
	{
		input_str_byte = IsTowByte(str[pos]);

		for (int sp_pos = 0; sp_pos < splen; sp_pos++)
		{
			list_str_byte = IsTowByte(spChar_jpn[sp_pos]);

			if(input_str_byte == list_str_byte)
			{

				list_str_byte ? z = 2 : z = 1;

				if (!strncmp(str+pos, spChar_jpn+sp_pos, z))
				{

					if(!list_str_byte)
					{
						found_sp[0] = spChar_jpn[sp_pos];
						found_sp[1] = '\0';
					}
					else
					{
						found_sp[0] = spChar_jpn[sp_pos];
						found_sp[1] = spChar_jpn[sp_pos+1];
						found_sp[2] = '\0';
					}

					return found_sp;
				}
			}
			if(list_str_byte)
				sp_pos++;

		}
		if(input_str_byte)
			pos++;
	}
	return NULL;

}


LRESULT CNk2DFrame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL bDblClk)
{
	if (!m_bAllLoaded)
		return 0;
	
	if (m_GraphicMode == NKGRAPHIC2D && m_pStartSheet)
	{
		m_pStartSheet->MsgProc(hWnd, msg, wParam, lParam);
		if (m_pStartSheet->IsStarting() == START_GAME)
		{
			m_GraphicMode = NKGRAPHICLOADING;
		}
	}
	else if (m_GraphicMode == NKGRAPHIC3D )
	{
		if( g_dwClientCountry == CTRY_BRA && m_pAutoNotice ) // ����� ��û : 10�� ���� ���� �޽��� ���
			m_pAutoNotice->MsgProc();

		if( m_Popup )
		{
			if( m_force_exit )
			{
				DWORD tick = GetTickCount();
				if( m_force_exit_tick == 0 )
					m_force_exit_tick = tick;

				if( m_force_exit_tick + 10000 < tick )
				{
					exit(1);
					return 1;
				}
			}
			return PopupMsgProc(hWnd, msg, wParam, lParam);
		}

		if( m_pPremiumChaMove && m_bShowPremiumChaMove )
			return m_pPremiumChaMove->MsgProc( hWnd, msg, wParam, lParam );

		if (m_bHelpPet && m_pControlHelpPet )	///�굵�� �켱������ ����.
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;
			int ret = m_pControlHelpPet->MsgProc(hWnd, msg, wParam, lParam);
			if(bDblClk)
				msg = WM_LBUTTONDOWN;
			if(ret)
				return 1;
		}

		if (m_pPremiumExchange && m_bShowPremiumExchange)
		{
			if (m_pPremiumExchange->MsgProc(hWnd, msg, wParam, lParam))
				return 1;
		}


		if( m_bShowNotice && m_pControlNotice ) ///�����˾�â
		{
			if( m_pControlNotice->MsgProc( hWnd, msg, wParam, lParam ) )
				return 1;
		}

		if ( m_bShowCashShop && m_pControlCashShop ) ///������� �� �������̽� ������� ������� ��µǾ��Ѵ�.
			return m_pControlCashShop->MsgProc(hWnd, msg, wParam, lParam); // ��������� Ű�� ���������.�켱 ������ �����Ұ�. ControlBottom  qhekeh dntjsehldigksek.

		if ( m_bShowCashShopIntro && m_pCashShopIntro ) ///������� �� �������̽� ������� ������� ��µǾ��Ѵ�.
			return m_pCashShopIntro->MsgProc(hWnd, msg, wParam, lParam); // ��������� Ű�� ���������.�켱 ������ �����Ұ�. ControlBottom  qhekeh dntjsehldigksek.

		if (m_bInterface[GATE] && m_pInterface[GATE] && m_pInterface[GATE]->MsgProc(hWnd, msg, wParam, lParam))
		{
			if( g_dwClientCountry == CTRY_JPN )
			{
				return 0;
			}
			else
			{
				// tick �� ����!
				return 1;
			}
		}

		if( GetGate() && GetGate()->IsActivate() )
		{
			if( 2 == GetGate()->MsgProc(hWnd , msg, wParam ,lParam) )
			{
				ShowGateWindow(false,-1,false);
			}
			return 1;
		}


		{
			if (m_bShowControlGuild && m_pControlGuild && m_pControlGuild->MsgProc(hWnd, msg, wParam, lParam))
				return 1;

			if (m_bShowControlGuildManage && m_pControlGuildManager && m_pControlGuildManager->MsgProc(hWnd, msg, wParam, lParam))
				return 1;
		}

		if ( (m_bViewTop || m_bInven || m_bInterface[SCORE]
				|| m_bInterface[MAP] || m_bSkill || m_bParty
				|| m_bHelp
				|| m_bPetStatus
				|| m_bInterface[QUEST]
				|| m_bInterface[DOCUMENT]
				|| m_bHelper
				|| m_bShowControlGuild
				|| m_bShowControlGuildManage
				|| m_bHeroFinalRank
			 )
				&& !(m_bShowPVPWidget)
		   )
		{
			// ���ӳ��� ����ϴ� �޼���â�� �ϳ��� �ִ°�� "ž�޴�"�� ����� �� ����
			if(Check_All_MsgPopUp() == MSGPOPUP_NOT_EXIST && pCMyApp->m_pUIMgr && !pCMyApp->m_pUIMgr->m_bIsDelivBox)
			{
				if (m_pControlTop && m_pControlTop->MsgProc(hWnd, msg, wParam, lParam))
				{
					return 1;
				}
			}
		}

		if( m_pControlSelMenu && m_bShowControlSelMenu )
		{
			if( m_pControlSelMenu->MsgProc(hWnd, msg, wParam, lParam ) )
				return 1;
			else
				return 0;
		}


		if( m_pBossraidInfo && m_bBossraidInfo )
		{
			if( m_pBossraidInfo->MsgProc(hWnd, msg, wParam, lParam ) )
				return 1;
		}

		if( m_pHeroPrivilege && m_bHeroPrivilege )
		{
			if( m_pHeroPrivilege->MsgProc(hWnd, msg, wParam, lParam ) )
				return 1;
		}

		if( m_pHeroRankList && m_bHeroRankList )
		{
			if( m_pHeroRankList->MsgProc(hWnd, msg, wParam, lParam ) )
				return 1;
		}

		if (m_bLetter && m_pControlLetter->MsgProc(hWnd, msg, wParam, lParam))
			return 1;

		if (m_bMenu && m_pControlMenu)
		{
			if (m_pControlMenu->MsgProc(hWnd, msg, wParam,lParam))
				return 1;
		}
		if (m_bRShift && m_pRShiftMenu)
		{
			if (m_pRShiftMenu->MsgProc(hWnd, msg, wParam,lParam))
				return 1;
		}
		if (m_bLShift && m_pLShiftMenu)
		{
			if(m_pLShiftMenu->MsgProc(hWnd, msg, wParam, lParam))
				return 1;
		}
		if(m_bAutoMouse && m_pAutoMouse)
		{
			if(m_pAutoMouse->MsgProc(hWnd,msg,wParam,lParam))
				return 1;
		}
		if (m_bPetLevel && m_pPet_Level)
		{
			if (m_pPet_Level->MsgProc(hWnd, msg, wParam,lParam))
				return 1;
		}
		if ( m_bShowCashShop && m_pControlCashShop && m_pControlCashShop->MsgProc(hWnd, msg, wParam, lParam) ) ///�������
			return 1;
		if ( m_bShowCashShopIntro && m_pCashShopIntro && m_pCashShopIntro->MsgProc(hWnd, msg, wParam, lParam) ) ///�������
			return 1;
		if (m_bShop && m_pControlShop)
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;
			int ret = m_pControlShop->MsgProc(hWnd, msg, wParam, lParam);
			if (bDblClk)
				msg = WM_LBUTTONDOWN;
			if (ret)
				return 1;
		}
		if (m_bPeiceShop && m_pControlPeiceShop)
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;

			int ret = m_pControlPeiceShop->MsgProc(hWnd, msg, wParam, lParam);

			if (bDblClk)
				msg = WM_LBUTTONDOWN;

			if(ret)
				return 1;
		}
		if (m_bProduct && m_pProduct)
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;

			int ret = m_pProduct->MsgProc(hWnd, msg, wParam, lParam);

			if (bDblClk)
				msg = WM_LBUTTONDOWN;

			if (ret)
				return 1;
		}
		if(m_bPetProduct && m_pPetProduct)
		{
			if(bDblClk)
				msg = WM_LBUTTONDBLCLK;
			int ret = m_pPetProduct->MsgProc(hWnd, msg, wParam, lParam);
			if(bDblClk)
				msg = WM_LBUTTONDOWN;
			if(ret)
				return 1;
		}
		if(m_bShowGamble && m_pGamble)
		{
			int ret = m_pGamble->MsgProc(hWnd, msg, wParam, lParam);
			if (ret)
				return 1;
		}

		if(m_bLockSmith && m_pLockSmith)
		{
			if( m_pLockSmith->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}
		if(m_bShowEventAncient && m_pEventAncient)
		{
			if( m_pEventAncient->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}
		if(m_bShowPlatinum && m_pPlatinum)
		{
			if( m_pPlatinum->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}
		if(m_bShowSummerEvent && m_pSummerEvent)
		{
			if( m_pSummerEvent->MsgProc(hWnd,msg,wParam,lParam) )
				return 1;
		}
		if (m_bInterface[QUEST] && m_pInterface[QUEST] && m_pInterface[QUEST]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bPetStatus && m_pControlPetStatus && m_pControlPetStatus->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if(m_bShowRefine && m_pRefine)
		{
			if( m_pRefine->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}
		if( m_bShowUpgrade && m_pUpgrade ) ///�Ź���ȭ�ý���
		{
			if( m_pUpgrade->MsgProc( hWnd, msg, wParam, lParam ) )
				return 1;
		}
		if( m_bShowUserShopSearch && m_pUserShopSearch ) ///���λ����˻�


		{
			if( m_pUserShopSearch->MsgProc( hWnd, msg, wParam, lParam ) )
				return 1;
		}
		if(m_bShowProcess && m_pProcess)	//����


		{
			if( m_pProcess->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}
		if (m_bShowExchange && m_pControlInven && (!m_pControlInven->m_plus5Message.m_bActive))
		{
			if( m_pControlExchange->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}
		if (m_bShowWareHouse && m_pControlInven && (!m_pControlInven->m_plus5Message.m_bActive))
		{

			if( m_pControlWareHouse->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}

		if (m_bShowGStoreHouse && m_pControlInven && (!m_pControlInven->m_plus5Message.m_bActive))
		{
			if( m_pControlGStoreHouse->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}

		if( m_pHeroFinalRank && m_bHeroFinalRank )
		{
			if( m_pHeroFinalRank->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}

		if (m_bShowUserShop && m_pControlInven /*&& (!m_pControlInven->m_plus5Message.m_bActive && !m_pControlInven->m_MsgPopUp.m_bActive)*/) ///���λ���
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;
			int ret = m_pControlUserShop->MsgProc(hWnd, msg, wParam, lParam);
			if (bDblClk)
				msg = WM_LBUTTONDOWN;
			if (ret)
				return 1;
		}
		if (m_bInterchange && m_pControlInven)
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;


			if(!m_pControlInven->m_plus5Message.m_bActive)
			{
				int ret = m_pInterchange->MsgProc(hWnd, msg, wParam, lParam);
				if (bDblClk)
					msg = WM_LBUTTONDOWN;
				if (ret)
					return 1;
			}
		}
				
		
		if(m_pUIWindow)
		{
			if( m_pUIWindow->WindowMsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}		

		if( g_SvrType == ST_ADULT_ONLY )
		{
			if(m_pTgaUIWindow && m_pTgaUIWindow->WindowMsgProc(hWnd, msg, wParam, lParam))
				return 1;
		}


		if (m_pControlInven && m_pControlInven->MsgProc(hWnd, msg, wParam, lParam, m_bInven
				, m_bInven || m_bInterface[SCORE] || m_bInterface[MAP] || m_bSkill || m_bParty || m_bHelp || m_bPetStatus || m_bInterface[QUEST] || m_bInterface[DOCUMENT] || m_bHelper
				|| m_bShowControlGuild
				|| m_bShowControlGuildManage
													   ))
			return 1;

		if (m_bInterface[SCORE] && m_pInterface[SCORE] && m_pInterface[SCORE]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bPetStatus && m_pControlPetStatus && m_pControlPetStatus->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[SOCIAL] && m_pInterface[SOCIAL] && m_pInterface[SOCIAL]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;

		if (m_bInterface[MAP]&& m_pInterface[MAP] && m_pInterface[MAP]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[DOCUMENT] && m_pInterface[DOCUMENT] && m_pInterface[DOCUMENT]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[YUTBOARD] && m_pInterface[YUTBOARD] && m_pInterface[YUTBOARD]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[FISHING] && m_pInterface[FISHING] && m_pInterface[FISHING]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[FISHING_REWARD] && m_pInterface[FISHING_REWARD] && m_pInterface[FISHING_REWARD]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[BASEBALL] && m_pInterface[BASEBALL] && m_pInterface[BASEBALL]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[BASEBALL_REWARD] && m_pInterface[BASEBALL_REWARD] && m_pInterface[BASEBALL_REWARD]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[LOTTO] && m_pInterface[LOTTO] && m_pInterface[LOTTO]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[BINGO] && m_pInterface[BINGO] && m_pInterface[BINGO]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;		
		if (m_bInterface[LETTER_SEND] && m_pInterface[LETTER_SEND] && m_pInterface[LETTER_SEND]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[LETTER_RECV] && m_pInterface[LETTER_RECV] && m_pInterface[LETTER_RECV]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[LOTTERY] && m_pInterface[LOTTERY] && m_pInterface[LOTTERY]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[DICEGAME] && m_pInterface[DICEGAME] && m_pInterface[DICEGAME]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[DICEGAME_REWARD] && m_pInterface[DICEGAME_REWARD] && m_pInterface[DICEGAME_REWARD]->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bInterface[LETTER_WINDOW] && m_pInterface[LETTER_WINDOW] )
		{
			if(bDblClk)
				msg = WM_LBUTTONDBLCLK;
			int ret = m_pInterface[LETTER_WINDOW]->MsgProc(hWnd, msg, wParam, lParam);
			if(bDblClk)
				msg = WM_LBUTTONDOWN;
			if( ret )
				return 1;
		}
		if (m_bSkill && m_pControlSkill && m_pControlSkill->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bHelp && m_pControlHelp && m_pControlHelp->MsgProc(hWnd, msg, wParam, lParam))
			return 1;
		if (m_bParty && m_pControlParty && m_pControlParty->MsgProc(hWnd, msg, wParam, lParam))
			return 1;

		if (m_bHelper && m_pControlHelper )	//�İ���
		{
			if (bDblClk)
				msg = WM_LBUTTONDBLCLK;
			int ret = m_pControlHelper->MsgProc(hWnd, msg, wParam, lParam);
			if(bDblClk)
				msg = WM_LBUTTONDOWN;
			if(ret)
				return 1;
		}

		if( m_pSpiritMode && m_bSpiritStart )
		{
			if( m_pSpiritMode->MsgProc(hWnd,msg,wParam,lParam) )
				return 1;
		}
//		if (m_bQuest && m_pQuestData && m_pQuestData->MsgProc(hWnd, msg, wParam, lParam))
//			return 1;


		if (m_pControlBottom && m_pControlBottom->MsgProc(hWnd, msg, wParam, lParam))
			return 1;

		if (m_ui_takebox )
		{
			int rv = m_ui_takebox->MsgProc(hWnd, msg, wParam, lParam);
			if( rv )
			{
				if( rv == 2 )
				{
					ShowTakeboxWindow(false,0);
					return 1;
				}
				else
				{
					return 1;
				}
			}

			return 0;
		}

		if (m_ui_friend && m_ui_friend->IsVisible())
		{
			if( m_ui_friend->MsgProc(hWnd, msg, wParam, lParam) )
				return 1;
		}

		if( m_ui_buffitem &&
				m_ui_buffitem->MsgProc(hWnd, msg, wParam, lParam) )
		{
			return 1;
		}

	}

	return 0L;
}

#include "resource.h"

void CNk2DFrame::SendTickTime()
{
	static DWORD lastTickTime = 0;
	DWORD curTickTime = timeGetTime();
	if (curTickTime >= lastTickTime + 60000)
	{
		// 1�п� �ѹ��� ��������!!
		if (g_pRoh)
		{
			if (g_pRoh->m_Wearing[WEARING_WEAPON])
			{
				CItem *pItem = g_pRoh->m_Wearing[WEARING_WEAPON];
				sprintf(commOutBuf, "pulse %d, %d, %d, %d, %d\n", curTickTime/1000, pItem->m_Vnum, pItem->m_Index, pItem->m_Speed, GET_ATT_RANGE(pItem));
			}
			else
				sprintf(commOutBuf, "pulse %d, -1, 0, 0, 0\n", curTickTime/1000);
		}
		else
			sprintf(commOutBuf, "pulse %d, -1, 0, 0, 0\n", curTickTime/1000);

		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage(commOutBuf);

		if( g_pTcpIp && 
			pCMyApp->m_pUIMgr->m_AutoPlay &&
			pCMyApp->m_pUIMgr->m_bAutoHunt )
		{
			g_pTcpIp->SendNetMessage( "lr check\n" );
		}

		lastTickTime = curTickTime;
	}
}

void CNk2DFrame::DeleteVoiceChat()
{
}

// nate
BOOL CNk2DFrame::Check_All_MsgPopUp()
// ���� ���õǾ��ִ� �޼��� �ڽ��� �ִ��� Ȯ��
{
	if( m_Popup )
		return MSGPOPUP_EXIST;

	// �޼��� â�� �� ���� ���

	if( m_pControlInven && m_pControlLetter )
	{
		if(	m_pControlInven->m_plus5Message.m_bActive ||
				m_pControlLetter->m_bActive ||
				pCMyApp->m_MsgPopUp.m_bActive )
			return MSGPOPUP_EXIST;
	}

	return MSGPOPUP_NOT_EXIST;
}


BOOL CNk2DFrame::All_Kill_MsgPopUp()
{
	if( m_pControlInven )
	{
		if(m_pControlInven->m_plus5Message.m_bActive)
			m_pControlInven->m_plus5Message.m_bActive = FALSE;
		if(pCMyApp->m_MsgPopUp.m_bActive)
			pCMyApp->m_MsgPopUp.m_bActive = FALSE;
	}

	DeleteAllPopup();
	return TRUE;
}



void CNk2DFrame::ShowRShiftMenu(CNkCharacter *pCha)
{
//	if(m_bAutoMouse) ///07-04-12 ����Ȯ�� �ý��� Ÿ �������̽��� �Բ� �� �� �ְ� ����.
//		return;
	HRESULT hr;
	D3DVIEWPORT7 vp;

	D3DMATRIX matPipe;
	D3DVECTOR vScr, vWorld;

	if (pCha != NULL)
	{
		m_bRShift = TRUE;

		vWorld = D3DVECTOR(pCha->m_wx, pCha->m_wy, pCha->m_wz);

		// ȭ�� ��ǥ ���.
		pCMyApp->GetLandPtr()->GetPipelineMatrix(matPipe);
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		if (m_pRShiftMenu)
		{
			if (FAILED(hr = pCMyApp->GetDevice()->GetViewport( &vp ))) return ;

			// viewport�� ũ�� Ȯ��
			int cx, cy;
			cx =230, cy = 67; // 06-04-19 cx�� ũ�⸦ 185���� 230���� ����. ��ư�� ��ĭ �߰��Ǿ���.
			vScr.x = vScr.x - 230/2;

			if((vScr.x+cx) > (vp.dwX+vp.dwWidth))
				vScr.x = vp.dwX+vp.dwWidth-cx;
			if(vScr.x <0)
				vScr.x = 0;
			if(vScr.y < 0)
				vScr.y = 0;
			if((vScr.y+cy) > (vp.dwY+vp.dwHeight))
				vScr.y = vp.dwY+vp.dwHeight-cy;

			m_pRShiftMenu->SetXPos(vScr.x);
			m_pRShiftMenu->SetYPos(vScr.y);
			m_pRShiftMenu->SetCurRace(pCha->m_Race);
			m_pRShiftMenu->SetUserName(pCha->m_pstrName);
		}
	}
}


void CNk2DFrame::ShowLShiftMenu()
{
//	if(m_bAutoMouse) ///07-04-12 ����Ȯ�� �ý��� Ÿ �������̽��� �Բ� �� �� �ְ� ����.
//		return;
	HRESULT hr;
	D3DVIEWPORT7 vp;

	D3DMATRIX matPipe;
	D3DVECTOR vScr, vWorld;

	CNkMyPet *pPet = pCMyApp->m_pMyPet;

	if (pPet != NULL)
	{
		m_bLShift = TRUE;

		vWorld = D3DVECTOR(pPet->m_wx, pPet->m_wy, pPet->m_wz);

		// ȭ�� ��ǥ ���.
		pCMyApp->GetLandPtr()->GetPipelineMatrix(matPipe);
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		if (m_pLShiftMenu)
		{
			if (FAILED(hr = pCMyApp->GetDevice()->GetViewport( &vp ))) return ;

			// viewport�� ũ�� Ȯ��
			//pCMyApp->
			int cx, cy;
			cx = 279, cy = 122;  //�˾� �޴��� Ŭ���� ĳ���� �ϴ��߾ӿ� ��ġ�ϰ� ��.
			vScr.x = vScr.x - 230/2;

			if((vScr.x+cx) > (vp.dwX+vp.dwWidth))
				vScr.x = vp.dwX+vp.dwWidth-cx;
			if(vScr.x <0)
				vScr.x = 0;
			if(vScr.y < 0)
				vScr.y = 0;
			if((vScr.y+cy) > (vp.dwY+vp.dwHeight))
				vScr.y = vp.dwY+vp.dwHeight-cy;

			m_pLShiftMenu->SetPos(vScr.x, vScr.y);
			m_pLShiftMenu->SetCurRace(0);
			m_pLShiftMenu->SetUserName(pPet->m_strName);
			m_pLShiftMenu->m_bMacroEditing = FALSE; // ���� ������ �̰� �׻� �ʱ�ȭ �Ǿ���Ѵ�.
		}
	}
}

void CNk2DFrame::ShowPetLevelMenu()
{
//	if(m_bAutoMouse) ///07-04-12 ����Ȯ�� �ý��� Ÿ �������̽��� �Բ� �� �� �ְ� ����.
//		return;

	HRESULT hr;
	D3DVIEWPORT7 vp;

	D3DMATRIX matPipe;
	D3DVECTOR vScr, vWorld;

	HWND m_hWnd;
	RECT ClientRc;
	m_hWnd =  g_pDisplay->GetHWnd();
	GetClientRect(m_hWnd, &ClientRc);

	m_bPetLevel = TRUE;
	if (m_pPet_Level)
	{
		if (FAILED(hr = pCMyApp->GetDevice()->GetViewport( &vp ))) return ;

		vScr.x=ClientRc.right/2-200;  //��� ��ġ.
		vScr.y=ClientRc.bottom/2-129;

		m_pPet_Level->Init();
		m_pPet_Level->SetXPos(vScr.x);
		m_pPet_Level->SetYPos(vScr.y);
		m_pPet_Level->SetMoney(g_pRoh->m_Money);
	}
}

BOOL CNk2DFrame::CloseAllWindow( BOOL bAdjustVP, bool bTap ) // ����Ʈ ������ �ϴ��� �����ĸ� ���ڷ� ����. �� �Լ��� �ٸ� �������̽��� Show�迭 �Լ����� ���ɶ��� ����Ʈ ������ ���ϱ� ���� ���.(05-09-30 ����) ///�Ź���ȭ�ý���
{
	// �� �Լ��� Ư¡�� �Ժη� ���� �ȵǴ� ��츦 ����ؾ� �Ѵ�.
	// �� ���� �ٷ� �׺����� �׺������쳪 ���丶�콺 â�̴�.
	// �̷��༮���� �Ժη� ���⿡ ������ �ȵȿ� ����! (����)

	/////////////////////////////////////////////////////
	// �������̽� ���� ���� üũ.
	// Ư�� �������̽����� �۵����϶� �ٸ� �������̽��� Ȱ��ȭ�� ���´�.
	// �̰͵鵵 �켱������ �� �����ؾ��Ѵ�.
	if( m_pGamble && m_pGamble->IsOnGamble() == TRUE )
		return FALSE;

	if( m_pLockSmith && m_pLockSmith->IsProcess() == true )
		return FALSE;

	if( IsGambleVisible() && GetGamble() && GetGamble()->m_bExchange ) return FALSE;

	if( m_pControlUserShop && m_pControlUserShop->m_States != -1 && m_pControlUserShop->m_States != 2 ) // ���λ��� �����ִ� �߿� �Ժη� ���ݰ� ó��.(���̵� �߿� �������.) ///���λ���
		return FALSE;


	m_bLockSmith = FALSE;

	if (m_bShop)
	{
		m_bShop = FALSE;
		if( m_pControlShop )
			m_pControlShop->RemoveAllItems();
	}

	if (m_bShowExchange)
	{
		m_bShowExchange = FALSE;
		if( m_pControlExchange && m_pControlExchange->IsExch() )
			m_pControlExchange->ActivateExch(FALSE);	// ��Ʈ�� �޽����� ������.
	}
	if (m_bShowWareHouse)
	{
		m_bShowWareHouse = FALSE;
		if( m_pControlWareHouse && m_pControlWareHouse->IsActivate() )
			m_pControlWareHouse->ActivateWareHouse(FALSE);
	}

	if( m_bShowGStoreHouse )
	{
		m_bShowGStoreHouse = FALSE;
		if( m_pControlGStoreHouse && m_pControlGStoreHouse->IsActivate() )
			m_pControlGStoreHouse->ActivateGStoreHouse(FALSE);
	}

	if (m_bInterchange)
	{
		m_bInterchange = FALSE;
	}

	m_bInven = FALSE;
	if( m_pControlInven && m_pControlInven->m_bAct_Masuk )
	{
		m_pControlInven->Close_Masuk();
	}

	if( m_bMenu ) // �޴��������̽��� �����־��ٸ�...
	{
		m_bMenu = FALSE;
		SAFE_DELETE_RES( m_pControlMenu );
	}

	if( !bTap )
	{
		if(pCMyApp->m_pUIMgr)
			pCMyApp->m_pUIMgr->m_bMoveKit=FALSE; // �� �̵���ġ�� ��� ����. ShowGateWindow������ ���������� ���� ����صξ��� �����Ѵ�.
	}
	else
	{
	}
	m_bInterface[SCORE] = false;
	m_bInterface[GATE] = false;
	m_bInterface[SOCIAL] = false;
	m_bInterface[QUEST] = false;
	m_bInterface[MAP] = false;
	m_bInterface[DOCUMENT] = false;
	m_bInterface[YUTBOARD] = false;
	m_bInterface[FISHING] = false;
	m_bInterface[FISHING_REWARD] = false;
	m_bInterface[BASEBALL] = false;
	m_bInterface[BASEBALL_REWARD] = false;
	m_bInterface[LOTTO] = false;
	m_bInterface[BINGO] = false;
	m_bInterface[LETTER_WINDOW] = false;
	m_bInterface[LETTER_SEND] = false;
	m_bInterface[LETTER_RECV] = false;
	m_bInterface[LOTTERY] = false;
	m_bInterface[DICEGAME] = false;
	m_bInterface[DICEGAME_REWARD] = false;
	m_bParty = FALSE;
	m_bHelper = FALSE;	//�İ���

	{

		m_bHeroFinalRank = FALSE;
		m_bShowControlGuild = FALSE;
		m_bShowControlGuildManage = FALSE;
		m_bShowGuildManager = FALSE;
		//m_pUIWindow->AllCloseWindow();
	}

	m_bSkill = FALSE;
	m_bHelp = FALSE;
	m_bShowGamble = FALSE;
	m_bShowEventAncient = FALSE;
	m_bShowPlatinum = FALSE;
	m_bShowSummerEvent = FALSE;
	m_bRShift = FALSE;
//kwon
	m_bPetLevel = FALSE;

	m_bPetStatus = FALSE;

	m_bPeiceShop = FALSE; // �̰� ������ ������ "///�Ź���ȭ�ý���" �����鼭 �߰� ����. ���� ���濩���� ������ ������ �� ��.(05-10-04 ����)
	m_bProduct = FALSE; // �̰� ������ ������ "///�Ź���ȭ�ý���" �����鼭 �߰� ����. ���� ���濩���� ������ ������ �� ��.(05-10-04 ����)
	m_bPetProduct = FALSE; // 05-11-09 �߰�

	if( m_bShowUpgrade ) // ��ȭ �迭 �������̽��� �����־��ٸ�...
	{
		m_bShowUpgrade = FALSE; ///�Ź���ȭ�ý���
		SAFE_DELETE_RES( m_pUpgrade );

	}

	if( m_bShowUserShopSearch ) // �ؽ�Ʈ �Է� �޴� �������̽��� ���� ConvertImmStatus() �� ������Ѵ�.
	{
		m_bShowUserShopSearch = FALSE; ///���λ����˻�

		pCMyApp->ConvertImmStatus(); // �̰������ ������ �ݾ����� Ǯ���ִ� ��.(�̰� �����ָ� �Ϻ� �������� �Է��ߵ�ÿ� ������ ����)
	}

	if( m_bShowCashShop ) ///�������
	{
		m_bShowCashShop = FALSE;

		if( m_pControlCashShop )
			m_pControlCashShop->ClearDta(); // Dta�� ���� ���� ���� �ε�.(�޸� ������ ����)
	}

	if( m_bShowCashShopIntro ) ///�������
	{
		m_bShowCashShopIntro = FALSE;

		if( m_pCashShopIntro )
		{
			m_pCashShopIntro->Close(); // �� ������ �����츦 �����ش�.
		}
	}


	m_bShowRefine = FALSE; // �������� ���� ��ó�� �Լ��� ȣ���ؼ� ���µ� �������̽� ���� �ϰ�ȭ �۾��߿� �� �Լ��� ���� ������ �߻��ߴ�. �׷��� �÷��׸� ��.(�����Ͽ� �ٸ� ������ ����������� ����.)(05-11-02 ����)
	m_bShowProcess = FALSE;
	m_bWorldCup = FALSE;
	m_bHelper = FALSE;		//�İ���

	if( bAdjustVP ) ///�Ź���ȭ�ý���
	{
	}

	if( pCMyApp->m_pMouse->GetMouseType() == M_REPAIR )
	{
		pCMyApp->m_pMouse->SetMouseType(M_REPAIR);
	}

	if( m_bBossraidInfo )
	{
		m_bBossraidInfo = FALSE;
	}

	if( m_bHeroPrivilege )
	{
		m_bHeroPrivilege = FALSE;
	}

	if( m_bHeroRankList )
	{
		m_bHeroRankList = FALSE;
	}

	if(m_pPremiumChaMove)
	{
		m_bShowPremiumChaMove = FALSE;
	}

	pCMyApp->m_pUIMgr->m_bIsTeleportItem = FALSE;

	if( m_pControlSelMenu )
		m_bShowControlSelMenu = FALSE;

	if( GetTakeOutBox() )
	{
		SAFE_DELETE(m_ui_takebox);
	}

	return TRUE;
}

void CNk2DFrame::UpdateDrawInfo()
{
	if( m_pControlInven == NULL )
		return;

	m_pControlInven->m_bDrawInfoUpdate = TRUE;
}

void CNk2DFrame::ShowUI(int ui_type, int sub_type)
{
	if (m_pGamble && m_pGamble->IsOnGamble() == TRUE)
		return;

	switch(ui_type)
	{
	case LHUI_Type__Letter:
		break;
	case LHUI_Type__Shop:
		break;
	case LHUI_Type__PieceShop:
		break;
	case LHUI_Type__Exchange:
		break;
	case LHUI_Type__Interchange:
		break;
	case LHUI_Type__Inven:
		break;
	case LHUI_Type__Gate:
		break;
	case LHUI_Type__PetStatus:
		break;
	case LHUI_Type__Skill:
		break;
	case LHUI_Type__Help:
		break;
	case LHUI_Type__Party:
		break;
	case LHUI_Type__Product:
		break;
	case LHUI_Type__PetProduct:
		break;
	case LHUI_Type__Gamble:
		break;
	case LHUI_Type__LockSmith:
		break;
	case LHUI_Type__EventAncient:
		break;
	case LHUI_Type__Platinum:
		break;
	case LHUI_Type__SummerEvent:
		break;
	case LHUI_Type__Refine:
		break;
	case LHUI_Type__Upgrade:
		break;
	case LHUI_Type__TitleSystem:
		break;
	case LHUI_Type__Notice:
		break;
	case LHUI_Type__Warehouse:
		break;
	case LHUI_Type__GStoreHouse:
		break;
	case LHUI_Type__Guild_Battle:
		break;
	case LHUI_Type__Guild:
		break;
	case LHUI_Type__GuildManager:
		break;
	case LHUI_Type__UserShop:
		break;
	case LHUI_Type__UserShop_Search:
		break;
	case LHUI_Type__CashShop:
		break;
	case LHUI_Type__CashShop_Intro:
		break;
	case LHUI_Type__Process:
		break;
	case LHUI_Type__Helper:
		break;
	case LHUI_Type__PetHelp:
		break;
	case LHUI_Type__RShift:
		break;
	case LHUI_Type__LShift:
		break;
	case LHUI_Type__PetLevel:
		break;
	case LHUI_Type__PVP:
		break;
	case LHUI_Type__Dmitron_Status:
		break;
	case LHUI_Type__PremiumExchange:
		break;
	case LHUI_Type__Password_Check:
		break;
	case LHUI_Type__TakeBox:
		break;
	default: // LHUI_Type__EndOfEnum
		break;
	}
}

void CNk2DFrame::CloseUI(int ui_type)
{
	switch(ui_type)
	{
	case LHUI_Type__Letter:
		break;
	case LHUI_Type__Shop:
		break;
	case LHUI_Type__PieceShop:
		break;
	case LHUI_Type__Exchange:
		break;
	case LHUI_Type__Interchange:
		break;
	case LHUI_Type__Inven:
		break;
	case LHUI_Type__Gate:
		break;
	case LHUI_Type__PetStatus:
		break;
	case LHUI_Type__Skill:
		break;
	case LHUI_Type__Help:
		break;
	case LHUI_Type__Party:
		break;
	case LHUI_Type__Product:
		break;
	case LHUI_Type__PetProduct:
		break;
	case LHUI_Type__Gamble:
		break;
	case LHUI_Type__LockSmith:
		break;
	case LHUI_Type__EventAncient:
		break;
	case LHUI_Type__Platinum:
		break;
	case LHUI_Type__SummerEvent:
		break;
	case LHUI_Type__Refine:
		break;
	case LHUI_Type__Upgrade:
		break;
	case LHUI_Type__TitleSystem:
		break;
	case LHUI_Type__Notice:
		break;
	case LHUI_Type__Warehouse:
		break;
	case LHUI_Type__GStoreHouse:
		break;
	case LHUI_Type__Guild_Battle:
		break;
	case LHUI_Type__Guild:
		break;
	case LHUI_Type__GuildManager:
		break;
	case LHUI_Type__UserShop:
		break;
	case LHUI_Type__UserShop_Search:
		break;
	case LHUI_Type__CashShop:
		break;
	case LHUI_Type__CashShop_Intro:
		break;
	case LHUI_Type__Process:
		break;
	case LHUI_Type__Helper:
		break;
	case LHUI_Type__PetHelp:
		break;
	case LHUI_Type__RShift:
		break;
	case LHUI_Type__LShift:
		break;
	case LHUI_Type__PetLevel:
		break;
	case LHUI_Type__PVP:
		break;
	case LHUI_Type__Dmitron_Status:
		break;
	case LHUI_Type__PremiumExchange:
		break;
	case LHUI_Type__Password_Check:
		break;
	case LHUI_Type__TakeBox:
		break;
	default: // LHUI_Type__EndOfEnum
		break;
	}
}

void CNk2DFrame::ShowBossraidInfoWindow(BOOL bShow)
{
	if( !CloseAllWindow(FALSE) )
		return;

	m_bBossraidInfo = bShow;

	if(bShow)
		pCMyApp->StopHero();
}

void CNk2DFrame::SetBossRaidInfo(int BossZoneNum, int bossNum, BOOL KillFlag)
{
	m_pBossraidInfo->SetBossraidKillFlag(BossZoneNum, bossNum, KillFlag);
}

void CNk2DFrame::InitBossRaidKillCount()
{
	m_pBossraidInfo->InitKillCount();
}

void CNk2DFrame::ShowHeroPrivilegeWindow(BOOL bShow)
{
	m_bHeroRankList = bShow;

	if( !CloseAllWindow(FALSE))
		return;

	if( bShow )
		pCMyApp->StopHero();

	m_bHeroPrivilege = bShow;
}

void CNk2DFrame::SetHeroPrivilege(int heroPrivilege)
{
	m_pHeroPrivilege->SetHeroPrivilege( heroPrivilege );
}


void CNk2DFrame::ShowHeroRankListWindow(BOOL bShow, int race )
{
	m_bHeroRankList = bShow;

	if( !CloseAllWindow(FALSE))
		return;

	m_bHeroRankList = bShow;

	if(m_pHeroRankList && bShow )
	{
		m_pHeroRankList->SetRace( race );
		m_pHeroRankList->SendMsgPage();
	}


}

void CNk2DFrame::SetHeroRankList(char* buf)
{
	if( m_pHeroRankList )
		m_pHeroRankList->SetHeroRankLsit( buf );
}



void CNk2DFrame::ShowHeroFinalRankWindow(BOOL bShow)
{
	if( !CloseAllWindow(FALSE) )
		return;

	m_bHeroFinalRank = bShow;
}

void CNk2DFrame::SetHeroFinalRank(char* buf)
{
	m_pHeroFinalRank->SetHeroRank(buf);
}


void CNk2DFrame::ShowPetProductWindow(BOOL bShow, BOOL bAct) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bPetProduct = bShow;

		pCMyApp->StopHero();
	}

	if (m_bPetProduct && bAct)
		m_pPetProduct->ActivateExch(TRUE);
	else
		m_pPetProduct->ActivateExch(FALSE);
}

void CNk2DFrame::TogglePlatinumExchWindow(int type)
{
	if(Check_All_MsgPopUp())
		return;

	ShowPlatinumWindow(!m_bShowPlatinum);
	if(IsPlatinumVisible())
	{
		pCMyApp->StopHero();

		SAFE_DELETE_RES(m_pPlatinum);
		ShowPlatinumWindow(false);

		m_pPlatinum->LoadRes(type, m_pItemRender);
		m_pPlatinum->SetNkCha(m_pNkCha);

		ShowPlatinumWindow(true);
	}
}

// �÷�Ƽ�� ���� �Լ�


void CNk2DFrame::ShowPlatinumWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShowPlatinum = bShow;
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

void CNk2DFrame::ShowSummerEventWindow(BOOL bShow) ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShowSummerEvent = bShow;
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}



void CNk2DFrame::ToggleSummerEventWindow(int type)
{
	if(Check_All_MsgPopUp())
		return;

	ShowSummerEventWindow(!m_bShowSummerEvent);
	if(IsSummerEventVisible())
	{
		pCMyApp->StopHero();

		SAFE_DELETE_RES(m_pSummerEvent);
		ShowSummerEventWindow(false);
		m_pSummerEvent->LoadRes(type, m_pItemRender);
		m_pSummerEvent->SetNkCha(m_pNkCha);
		ShowSummerEventWindow(true);
	}
}

void CNk2DFrame::ShowPremiumChaMove(BOOL bShow, int slot)
{
	if( !CloseAllWindow(TRUE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	m_bShowPremiumChaMove = bShow;
	if( m_bShowPremiumChaMove == FALSE )
	{
		m_pPremiumChaMove->SetStep();
	}

	m_pPremiumChaMove->SetSlot(slot);
}

void CNk2DFrame::ShowAutoMouseWindow(BOOL bShow,int Type) ///QnA ///�������̽� Ŭ���� ó�� �Լ�ȭ(05-09-30 ����)
{
//	CloseAllWindow(FALSE); // �� �༮�� ���������� Ŭ���� �����ص� ó�����ش�.(�ֳĸ� �̳༮�� ���� ���� �� �ϳ��ϱ� -_-;) (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)

	if( !m_pAutoMouse )
		return;

	m_bAutoMouse = bShow; // �����Է½ý����� ���������� ���⼭ ���� �ݾ�����Ѵ�.(�Ժη� ������ �ȵǴϱ� ���� CloseAllWindow���� ���� �ʴ´�.)
	SAFE_DELETE_RES(m_pAutoMouse);

	if( bShow ) // ����
		m_pAutoMouse->LoadRes(Type ); // ���ҽ��� �ٽ� �ε�.
}

void CNk2DFrame::GuildPK(int sub_type, char *GuildName1, char *GuildName2, int PKstate)
{
	SAFE_DELETE(m_pGuildPK);
	m_pGuildPK = new CGuildPK();

	switch(sub_type)
	{
	case 0: // ����� ��û(request)
		{
			m_pGuildPK->AskGPK(GuildName1);
		}
		break;
	case 1: // �׺�(surrender)
		{
			m_pGuildPK->Surrender(GuildName1,GuildName2);
		}
		break;
	default:
		break;
	}
}

void CNk2DFrame::ShowUpgradeWindow( BOOL bShow ) ///�Ź���ȭ�ý���
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShowUpgrade = bShow;
	}
	else // (06-01-18 ��� ������ â�� ���� ��� �޼��� �ڽ� ��µǵ���.
	{
		if( m_pUpgrade == NULL )
			return;

		if( m_pUpgrade->m_Result != 0 ) // ����� �����ִٸ�...�޼��� �ڽ��� ����� ǥ�����ش�.
		{
			if( m_pUpgrade->m_iType == INTERFACE_TYPE_UPARMOR || m_pUpgrade->m_iType == INTERFACE_TYPE_UPWEAPON ) // Ÿ�Ե��� �޼����� �ٲ��� �Ѵ�.
			{
				switch( m_pUpgrade->m_Result )
				{
				case UPGRADE_ANI_SUCCESS:
					//-- IDS_UIMGR_SUCCEED_UPGRADE : �� ��� ���׷��̵忡 �����߽��ϴ�
					pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_UIMGR_SUCCEED_UPGRADE) );
					break;

				case UPGRADE_ANI_FAIL:
					//-- IDS_UIMGR_FAIL_UPGRADE : �� ��� ���׷��̵忡 �����߽��ϴ�.
					pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_UIMGR_FAIL_UPGRADE) );
					break;

				case UPGRADE_ANI_BROKEN:
					//-- IDS_UIMGR_REMOVE_UPGRADE : �� ��� �Ҹ�Ǿ����ϴ�.
					pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_UIMGR_REMOVE_UPGRADE) );

					break;
				}
			}
			else if( m_pUpgrade->m_iType == INTERFACE_TYPE_CONVERSION ) // Ÿ�Ե��� �޼����� �ٲ��� �Ѵ�.
			{
				switch( m_pUpgrade->m_Result )
				{
				case UPGRADE_ANI_SUCCESS:
					//-- IDS_CONVERSION_SUCC : �������� �����Ͽ����ϴ�.
					pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_CONVERSION_SUCC) );
					break;

				case UPGRADE_ANI_FAIL:
					//-- IDS_CONVERSION_FAIL : �������� �����Ͽ����ϴ�.
					pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_CONVERSION_FAIL) );
					break;
				}
			}
			else if( m_pUpgrade->m_iType == INTERFACE_TYPE_CONFUSION ) // ���� �ٽ� ������
			{
				// �̳༮�� ������ �����̴�.
				//-- IDS_EQUIP_STATUS_RESET : ����� ��ġ�� ������ ����Ǿ����ϴ�.
				pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_EQUIP_STATUS_RESET) );
			}

		}
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

void CNk2DFrame::ToggleUpgradeWindow( int type, BOOL ForceClose ) ///�Ź���ȭ�ý��� //Ÿ���� �Ŀ� ������ ���. ���� �Ⱦ���.
{
	if( Check_All_MsgPopUp() )
		return;

	if( ForceClose ) // ������ �������� �༮. ShowUpgradeWindow( FALSE )�� �Ⱦ��� ������ �� �༮�� ������ �޸𸮸� �����ϰ� �;..(�������� �ٽ� �ε���Ų��. ���� �޸𸮸� ���ϼ����� ��.)
	{
		m_bShowUpgrade = TRUE;
	}

	ShowUpgradeWindow( !m_bShowUpgrade );
	if( IsUpgradeVisible() )
	{
		m_pUpgrade->LoadRes(type, m_pItemRender); // �������� �ε��Ų��.(�� ��� �������� ���� ���� �޸� ������ ���ֹǷ� ���ָ޸𸮸� ���ϼ����� ���̴�.)
		m_pUpgrade->SetNkCha(m_pNkCha);
	}
}

void CNk2DFrame::ShowControlNoticeWindow( BOOL bShow, int Type, char *String ) // �������̽��� ���� â ///�����˾�â
{
	// �� �༮�� ���� ó���� Ư���ϴ�. 3D�� �������̽��� �ٸ� �������̽��� ���� �ʴ´�.
	if( !bShow ) // ���� ���..
	{
		SAFE_DELETE( m_pControlNotice );
		m_bShowNotice = false;
	}
	else // Ű�� ���. Ÿ�Ժ��� ������Ѵ�.
	{
		// ų ���� ������ �������մ� ���¿��� ���� ������ ���� ������ �����ִ� ���¿��� ��Ʈ���� �߰��Ǵ� ��츦 ������� �Ѵ�.
		if( m_pControlNotice ) // ������ â�� ���ִ� ���.
		{
			m_pControlNotice->SetContents( String ); // ������ ������ �߰�.

			if( m_pControlNotice->m_nState == NOTICE_STATE_MINI ) // �ּ�ȭ �����϶���
				m_pControlNotice->m_bNewMessage = TRUE; // ���� �޼����� ������ �˷�����Ѵ�.
		}
		else // ���� â�� ���� ���.
		{
			m_pControlNotice = new CControlNotice;
			if( !m_pControlNotice )
				return;
			m_pControlNotice->LoadRes();

			// Ÿ�Կ� ���� Ÿ��Ʋ�� �ڵ����� �ٿ�����.
			m_pControlNotice->SetType( Type );

			m_pControlNotice->SetContents( String ); // ������ �߰�.

			m_pControlNotice->m_bNewMessage = TRUE; // ���� �޼����� ������ �˷�����Ѵ�.
		}

		m_bShowNotice = true;
	}
}
void CNk2DFrame::ShowUserShopWindow( BOOL bShow ) ///���λ���
{
	CloseAllWindow(FALSE); // �̳༮�� ���������� �����ص� ó���� �Ǿ���Ѵ�.. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)

	m_bShowUserShop = bShow; // CloseAllWindow() ���н� ó���� �� ���� �������� �༮���� ������ �̰� ����������Ѵ�.

	if( bShow )
	{
		m_bInven = TRUE;
		m_pControlUserShop->m_States = USHOP_STATES_NORMAL; // ������ �ô� �븻 ����.
	}
	else
	{
		m_pControlUserShop->m_States = USHOP_STATES_NOTOPEN; // ���� �������� �̰ɷε� ǥ��������.
		pCMyApp->ConvertImmStatus(); // �̰������ ������ �ݾ����� Ǯ���ִ� ��.(�̰� �����ָ� �Ϻ� �������� �Է��ߵ�ÿ� ������ ����)
	}
}

void CNk2DFrame::ToggleUserShopWindow( int index, int type, int grade ) // type�� ������������ ���λ�������, grade�� ���� ������. ///���λ���
{
//	if( Check_All_MsgPopUp() )
//		return;
//	if( m_bAutoMouse )
//		return;

	if( !m_pControlUserShop ) // Ȥ�ö� �������


		return;

	ShowUserShopWindow( !m_bShowUserShop );
	if( IsUserShopVisible() )
	{
		char strTemp1[100]; // �̸� �����.
		char strTemp2[256]; // ��Ʈ �����.

		if( !m_pControlUserShop->m_bResLoad ) // ���ҽ� �ε尡 ���� �ȵǾ��ٸ�...
		{
			m_pControlUserShop->LoadRes( m_pItemRender); // ó�� ���������� �ε�


			m_pControlUserShop->SetNkCha(m_pNkCha);
//			m_pControlUserShop->SetTcpIp(g_pTcpIp);
		}

		if( type == 0 ) // ���� �����̸�...
		{
			//-- IDS_WHOS_USERSHOP : %s�� ���λ���
			sprintf( strTemp2, "%s", (char*)G_STRING(IDS_WHOS_USERSHOP) );

			if( index == -1 ) // �ڱ� �ڽ��� ������ ���� �����Ϸ��� �����ϴ� ���.
			{
				sprintf( strTemp1, strTemp2, g_pRoh->m_pstrName ); // �ڱ� �̸�.
				ZeroMemory( strTemp2, sizeof(strTemp2) ); // ��Ʈ �δ� ����д�.

				type = 0; // type ������ ������,�Ǹ���,������ ��带 ǥ�����ֵ��� ��ȯ�Ѵ�.(���⼭ ���ڷ� ������ ����,���� ���δ� ���� ��Ʈ�� ���ÿ����� �ʿ��ϱ⶧����.)
			}
			else // �ٸ� ����� ������ ���� �������� �� ���.
			{
				///�������� �� �۾�.
				CNkCharacter *pCha = NULL;

				pCha = pCMyApp->m_pUIMgr->FindChaById( index, FALSE );
				if( pCha )
				{
					sprintf( strTemp1, strTemp2, pCha->m_pstrName ); // �ڱ� �̸�.
					sprintf( strTemp2, "%s", pCha->m_strUserShopMent ); // ��Ʈ
				}
				else
				{
					ShowUserShopWindow( FALSE ); // ��� �ݾ�����Ѵ�.

					return; // ���� �̻��� ����. �������� ����.
				}

				type = 1; // type ������ ������,�Ǹ���,������ ��带 ǥ�����ֵ��� ��ȯ�Ѵ�.(���⼭ ���ڷ� ������ ����,���� ���δ� ���� ��Ʈ�� ���ÿ����� �ʿ��ϱ⶧����.)
			}

		}
		else if( type == 1 ) // ���� �����̸�...
		{
			//-- IDS_WHOS_USHOP2 : %s�� ��������
			sprintf( strTemp2, "%s", (char*)G_STRING(IDS_WHOS_USHOP2) );

			if( index == -1 ) // �ڱ� �ڽ��� ������ ���� �����Ϸ��� �����ϴ� ���.
			{
				sprintf( strTemp1, strTemp2, g_pRoh->m_pstrName ); // �ڱ� �̸�.
				ZeroMemory( strTemp2, sizeof(strTemp2) ); // ��Ʈ �δ� ����д�.

				type = 3; // ���� �����ε� �� ���� �߰��� ������ ���ؼ� ���� �ƴ϶� ó�� ���� �����̴�.
			}
			else
			{
				CUserShopNpc *TempUShopNpc = pCMyApp->m_pUIMgr->FindUShopNpcById( index );

				if( TempUShopNpc )
				{
					sprintf( strTemp1, strTemp2, TempUShopNpc->m_strMasterName ); // ���� �̸�.
					sprintf( strTemp2, "%s", TempUShopNpc->m_strUserShopMent ); // ��Ʈ

					if( TempUShopNpc->m_MasterIndex == g_pRoh->m_nCharIndex ) // �ڱ� �ڽ� ���������̸�...
					{
						type = 2; // type ������ ������,�Ǹ���,������ ��带 ǥ�����ֵ��� ��ȯ�Ѵ�.(���⼭ ���ڷ� ������ ����,���� ���δ� ���� ��Ʈ�� ���ÿ����� �ʿ��ϱ⶧����.)
					}
					else
					{
						type = 1; // type ������ ������,�Ǹ���,������ ��带 ǥ�����ֵ��� ��ȯ�Ѵ�.(���⼭ ���ڷ� ������ ����,���� ���δ� ���� ��Ʈ�� ���ÿ����� �ʿ��ϱ⶧����.)
					}
				}
				else
				{
					ShowUserShopWindow( FALSE ); // ��� �ݾ�����Ѵ�.

					return; // ���� �̻��� ����. �������� ����.
				}
			}
		}

		m_pControlUserShop->Open( type, grade, strTemp1, strTemp2 ); // ��Ʈ�� �̸��� ���� ���λ��� ����Ʈ�� ���� �˻��Ͽ� �־�����.
	}
}

void CNk2DFrame::ShowUserShopSearchWindow( BOOL bShow ) ///���λ����˻�
{
	if( !CloseAllWindow(FALSE) ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( bShow )
	{
		m_bInven = TRUE;
		m_bShowUserShopSearch = bShow;
	}
	else // ������ 07-01-15 �߰�
		pCMyApp->ConvertImmStatus(); // �̰������ ������ �ݾ����� Ǯ���ִ� ��.(�̰� �����ָ� �Ϻ� �������� �Է��ߵ�ÿ� ������ ����)
}

void CNk2DFrame::ToggleUserShopSearchWindow( BOOL ForceClose ) ///���λ����˻�
{
	if( ForceClose ) // ������ �������� �༮. ������ �޸𸮸� �����ϰ� �;..(�������� �ٽ� �ε���Ų��. ���� �޸𸮸� ���ϼ����� ��.)
		m_bShowUserShopSearch = TRUE;

	ShowUserShopSearchWindow( !m_bShowUserShopSearch );
	if( IsUserShopSearchVisible() )
		m_pUserShopSearch->LoadRes( m_pItemRender ); // �������� �ε��Ų��.(�� ��� �������� ���� ���� �޸� ������ ���ֹǷ� ���ָ޸𸮸� ���ϼ����� ���̴�.)
}

void CNk2DFrame::ShowControlMenuWindow( BOOL bShow, int Type, const char *NpcName ) // Ÿ���� � ����� �޴��ΰ�...(�̳༮�� ��� �Լ��� �ʿ����.) ///�޴��������̽�
{
	if( !CloseAllWindow() ) // Ŭ���� ���нÿ� ������ �ʰ� ó��. (05-11-19 ����) // �ϴ��� ���� ���� ��. (����Ʈ ���� �÷��׸� FALSE�� �ܿ� ����. ����Ʈ ������ �� �Լ� �������� ���־���Ѵ�.)
		return;

	if( !bShow ) // ���� ���..
	{
		if( m_pControlMenu )
			SAFE_DELETE_RES(m_pControlMenu);
	}
	else // Ű�� ���. Ÿ�Ժ��� ������Ѵ�.
	{
		pCMyApp->StopHero();

		CMultiScrollText *TempScrollText = NULL;

		switch( Type )
		{
		case MENU_TYPE_USERSHOP: // ���λ��� ȸ��,�˻�.

			// �ʿ��� ������� ��� ��ġ�� ��.
			m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 ); // ��� ����. ��ġ�� -1�̸� �ڵ� �߾� ��ġ��.
			if( NpcName && NpcName[0] ) // Npc���� ����� ���Դٸ�...
				m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ

			m_pControlMenu->AddButton( "Menu/btn_search", 57, 230, MENU_ACTION_USERSHOP_SEARCH ); // �˻�

			m_pControlMenu->AddButton( "Menu/btn_regain", 114, 230, MENU_ACTION_USERSHOP_RECEIVE ); // ȸ��

			m_pControlMenu->AddButton( "Menu/btn_cancel", 171, 230, MENU_ACTION_CLOSE ); // �ݱ�



			TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)
			// by evilkiki 2009.09.03 �̵�
			TempScrollText->LoadString( "data/menu/String1.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.

			m_pControlMenu->LoadRes( ); // �ʿ��� ���ҽ��� �ε��Ѵ�.

			break;

		case MENU_TYPE_NPCUPGRADE:

			// �ʿ��� ������� ��� ��ġ�� ��.
			m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 ); // ��� ����. ��ġ�� -1�̸� �ڵ� �߾� ��ġ��.
			if( NpcName && NpcName[0] ) // Npc���� ����� ���Դٸ�...
				m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ

			if( g_dwClientCountry == CTRY_JPN )
			{
				m_pControlMenu->AddButton( "Menu/btn_upgrade", 20, 225, MENU_ACTION_NPCUPGRADE_UPGRADE ); // ��ȭ
				m_pControlMenu->AddButton( "Menu/btn_process", 75, 225, MENU_ACTION_NPCUPGRADE_REFORM ); // ����
				m_pControlMenu->AddButton( "Menu/btn_conv", 130, 225, MENU_ACTION_NPCUPGRADE_CONVERSION ); // ������
				m_pControlMenu->AddButton( "Menu/btn_conf", 200, 225, MENU_ACTION_NPCUPGRADE_CONFUSION ); // ��ǻ��
				m_pControlMenu->AddButton( "Menu/btn_cancel", 113, 250, MENU_ACTION_CLOSE ); // �ݱ�

			}
			else
			{
				m_pControlMenu->AddButton( "Menu/btn_upgrade", 20, 225, MENU_ACTION_NPCUPGRADE_UPGRADE ); // ��ȭ
				m_pControlMenu->AddButton( "Menu/btn_armor400", 70, 225, MENU_ACTION_NPCUPGRADE_ARMOR400 ); // ����ȭ400lv
				m_pControlMenu->AddButton( "Menu/btn_process", 120, 225, MENU_ACTION_NPCUPGRADE_REFORM ); // ����
				m_pControlMenu->AddButton( "Menu/btn_conv", 170, 225, MENU_ACTION_NPCUPGRADE_CONVERSION ); // ������
				m_pControlMenu->AddButton( "Menu/btn_conf", 220, 225, MENU_ACTION_NPCUPGRADE_CONFUSION ); // ��ǻ��
				m_pControlMenu->AddButton( "Menu/btn_cancel", 113, 250, MENU_ACTION_CLOSE ); // �ݱ�
			}


			TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)

			TempScrollText->LoadString( "data/menu/String2.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.

			m_pControlMenu->LoadRes(); // �ʿ��� ���ҽ��� �ε��Ѵ�.



			break;

		case MENU_TYPE_BPSHOP: // �� �༮�� Ư���ϰ� ���⼭ AddButton()�� LoadRes()�� ���� �ʴ´�. �� �༮�� ȣ���� CmdBpShopList() ���� ���ش�.

			// �ʿ��� ������� ��� ��ġ�� ��.
			m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 ); // ��� ����. ��ġ�� -1�̸� �ڵ� �߾� ��ġ��.
			if( NpcName && NpcName[0] ) // Npc���� ����� ���Դٸ�...
				m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ
			TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)
			TempScrollText->LoadString( "data/menu/String3.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.
			break;

		case MENU_TYPE_ENCHANT:
			if( g_SvrType == ST_ADULT_ONLY ) // [2/27/2007 Theodoric] ��þƮ : ���� �˾�â ����

			{
				// �ʿ��� ������� ��� ��ġ�� ��.
				m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 ); // ��� ����. ��ġ�� -1�̸� �ڵ� �߾� ��ġ��.
				if( NpcName && NpcName[0] ) // Npc���� ����� ���Դٸ�...
					m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ

				m_pControlMenu->AddButton( "Menu/btn_upgrade", 20, 230, MENU_ACTION_ENCHANT_UPGRADE ); // ��ȭ
				m_pControlMenu->AddButton( "Menu/btn_make", 79, 230, MENU_ACTION_ENCHANT_MAKE ); //  �÷�Ƽ�� ����
				m_pControlMenu->AddButton( "Menu/btn_init", 139, 230, MENU_ACTION_ENCHANT_INIT ); // �ʱ�ȭ
				m_pControlMenu->AddButton( "Menu/btn_cancel", 193, 230, MENU_ACTION_CLOSE ); // �ݱ�


				TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)

				TempScrollText->LoadString( "data/menu/String4.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.
				m_pControlMenu->LoadRes( ); // �ʿ��� ���ҽ��� �ε��Ѵ�.
			}
			break;

		case MENU_TYPE_LPSHOP:
			// �� �༮�� Ư���ϰ� ���⼭ AddButton()�� LoadRes()�� ���� �ʴ´�. �� �༮�� ȣ���� CmdLPShopList() ���� ���ش�.

			// �ʿ��� ������� ��� ��ġ�� ��.
			m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 ); // ��� ����. ��ġ�� -1�̸� �ڵ� �߾� ��ġ��.

			if( NpcName && NpcName[0] ) // Npc���� ����� ���Դٸ�...
				m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ


			TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)

			TempScrollText->LoadString( "data/menu/String5.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.
			break;

		case MENU_TYPE_NEW_NPCUPGRADE: 	// [2008/12/19 Theodoric] 300���� �̻� ���� ��ȭ
			m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 ); // ��� ����. ��ġ�� -1�̸� �ڵ� �߾� ��ġ��.

			if( NpcName && NpcName[0] ) // Npc���� ����� ���Դٸ�...
				m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ

			if( CommonConfig::Instance()->GetGodWeapon() == true )
			{
				m_pControlMenu->AddButton( "Menu/btn_godup", 20, 225, MENU_ACTION_GODWEAPON_UP ); // ���ǹ��Ⱝȭ
				m_pControlMenu->AddButton( "Menu/btn_conv2", 80, 225, MENU_ACTION_NEW_NPCUPGRADE_CONVERSION ); // ������
				m_pControlMenu->AddButton( "Menu/btn_upgrade", 140, 225, MENU_ACTION_NEW_NPCUPGRADE_UPGRADE ); // ���׷��̵�
				m_pControlMenu->AddButton( "Menu/btn_godpow", 200, 225, MENU_ACTION_NEW_NPCUPGRADE_EXCHANGE ); // ��ȯ
				m_pControlMenu->AddButton( "Menu/btn_cancel", 113, 250, MENU_ACTION_CLOSE ); // �ݱ�
			}
			else
			{
				m_pControlMenu->AddButton( "Menu/btn_conv2", 50, 230, MENU_ACTION_NEW_NPCUPGRADE_CONVERSION ); // ������
				m_pControlMenu->AddButton( "Menu/btn_upgrade", 100, 230, MENU_ACTION_NEW_NPCUPGRADE_UPGRADE ); // ���׷��̵�
				m_pControlMenu->AddButton( "Menu/btn_godpow", 150, 230, MENU_ACTION_NEW_NPCUPGRADE_EXCHANGE ); // ��ȯ
				m_pControlMenu->AddButton( "Menu/btn_cancel", 200, 230, MENU_ACTION_CLOSE ); // �ݱ�
			}

			TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)
			TempScrollText->LoadString( "data/menu/String6.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.

			m_pControlMenu->LoadRes( ); // �ʿ��� ���ҽ��� �ε��Ѵ�.
			break;

		case MENU_TYEP_ITEMMAKE:
			m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 );
			m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ

			//���� ���� ���
			m_pControlMenu->AddButton( "Menu/btn_production", 57, 230, MENU_ACTION_ITEMMAKE ); // ����
			m_pControlMenu->AddButton( "Menu/btn_disassemble", 114, 230, MENU_ACTION_ITEMSEPARATE ); // ����
			m_pControlMenu->AddButton( "Menu/btn_cancel", 171, 230, MENU_ACTION_CLOSE ); // �ݱ�

			TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)

			TempScrollText->LoadString( "data/menu/String7.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.
			m_pControlMenu->LoadRes( ); // �ʿ��� ���ҽ��� �ε��Ѵ�.
			break;

		case MENU_TYPE_BUFFMAKE:
			{
				m_pControlMenu->AddBackGround( "interface/Menu/MenuBack1.bmp", -1, -1, 300, 300 );
				m_pControlMenu->AddString( NpcName, 137, 12, TRUE ); // Ÿ��Ʋ
				
				m_pControlMenu->AddButton( "Menu/btn_production", 50, 230, MENU_ACTION_BUFFMAKE_MAKE ); // ����
				m_pControlMenu->AddButton( "Menu/btn_gatcha", 100, 230, MENU_ACTION_BUFFMAKE_GATCHA ); // ��í
				m_pControlMenu->AddButton( "Menu/btn_medal", 150, 230, MENU_ACTION_BUFFMAKE_MEDAL ); // �޴�
				m_pControlMenu->AddButton( "Menu/btn_cancel", 200, 230, MENU_ACTION_CLOSE ); // �ݱ�

				TempScrollText = m_pControlMenu->AddScrollText( 25, 50, 256, 162, 256-8, 50, 162 , "common/scroll_up_t01", "common/scroll_dn_t01", "interface/common/scroll_thumb.bmp" ); // ����. (x,y,width,height)

				TempScrollText->LoadString( "data/menu/String8.txt" ); // �ؽ�Ʈ ���Ϸ� ���� �о��.
				m_pControlMenu->LoadRes( ); // �ʿ��� ���ҽ��� �ε��Ѵ�.
			}
			break;

		default: // ��� �ȵ� Ÿ���� �������̽��� Ű�� �ʴ´�.
			return;
		}

		m_bMenu = TRUE;
	}

}

void CNk2DFrame::ShowProcessWindow(BOOL bShow, int type) // ����â �ٿ��
{
	if( !CloseAllWindow(FALSE) )
		return;

	if( bShow )
	{
		if( m_pProcess )
		{
			m_pProcess->LoadRes(type, m_pItemRender);
			m_pProcess->SetNkCha(m_pNkCha);
		}

		m_bInven = TRUE;
		m_bShowProcess = bShow;

	}
	else
	{
		if(m_pProcess)
		{
			if (m_pProcess->IsProcessConnection())
				m_pProcess->CloseConnection();

			SAFE_DELETE_RES(m_pProcess);
		}
	}

	if( m_pControlInven )
		m_pControlInven->ResetItemInfo();
}

void CNk2DFrame::ToggleProcessWindow(int type)
{
	if (m_pGamble && m_pGamble->IsOnGamble() == TRUE)
		return;

	if(Check_All_MsgPopUp())
		return;

	ShowProcessWindow(!m_bShowProcess);
	if(IsProcessVisible())
	{
		SAFE_DELETE_RES(m_pProcess);
		ShowProcessWindow(false);
		m_pProcess->LoadRes(type, m_pItemRender);
		m_pProcess->SetNkCha(m_pNkCha);
		m_pProcess->SetTcpIp(g_pTcpIp);
		ShowProcessWindow(true);
	}
	else
	{
		if(m_pProcess)
		{
			if (m_pProcess->IsProcessConnection())
				m_pProcess->CloseConnection();
		}
	}
}

// nate 2006-02-24 : ��� �˾� ����
// ���ؿ� ���� ��� �˾��� ���������� �����Ѵ�.
void CNk2DFrame::DeleteAllPopup()
{
	if( !m_Popup )
		return;

	POPUP* pTail = NULL;
	do
	{
		pTail = m_Popup->pNext;		// ���� ����


		delete m_Popup;				// ������ ����
		m_Popup = pTail;			// ������ �����̷� ����


	}
	while( m_Popup );
	m_Popup = NULL;
}

// nate 2006-02-24 : ���� ���� �˾� ����
// ���ر����̹Ƿ� �������� ���ŵ�
void CNk2DFrame::DeletePopup()
{
	if( !m_Popup )
		return;

	POPUP* pTemp = m_Popup->pNext;	// ���� ������ �˾� ����
	delete m_Popup;
	m_Popup = pTemp;
}

// nate 2006-02-24 : ���ؿ� �˾� ����


// �˾��� ���ؾ˰������� �����Ѵ�.
void CNk2DFrame::InsertPopup( char* arg, int nType, int nProcess, int nLimit, int nDocument, void* pArgs )
{
	POPUP** pTemp = &m_Popup;
	while( *pTemp )					// ������ �˾��� ã�´�
		pTemp = &((*pTemp)->pNext);

	(*pTemp) = new POPUP;

	if( !(*pTemp) ) // 07-01-24 ����ó�� �߰�
		return;

	(*pTemp)->nProcess = nProcess;				// �޼��� ó�� �з�
	(*pTemp)->pArgs = pArgs;				// ���Ʈ�� ������
	(*pTemp)->pMsg_Popup.Init( nType );		// �˾� ���� ����
	(*pTemp)->pMsg_Popup.LoadRes();
	(*pTemp)->pMsg_Popup.m_StrLimit = nLimit;
	(*pTemp)->pMsg_Popup.PutString( arg );		// ���� �Է�
	m_nDocument = nDocument;
	if( pCMyApp->m_pMouse )
		pCMyApp->m_pMouse->SetMouseType(M_NORMAL);
}

// nate 2006-02-28 : �˾� �˻�


CMsgPopUp* CNk2DFrame::FindPopup( int nProcess )
{
	POPUP** pTemp = &m_Popup;
	while( *pTemp )					// ������ �˾��� ã�´�
	{
		if( (*pTemp)->nProcess == nProcess )
			return &((*pTemp)->pMsg_Popup);

		pTemp = &((*pTemp)->pNext);
	}

	return NULL;
}

HRESULT CNk2DFrame::RestorePopups()
{
	POPUP** pTemp = &m_Popup;
	while( *pTemp )					// ������ �˾��� ã�´�
	{
		((*pTemp)->pMsg_Popup).RestoreAll();

		pTemp = &((*pTemp)->pNext);
	}

	return S_OK;
}

// nate 2006-02-24 : �˾� �޼��� ó��
LRESULT CNk2DFrame::PopupMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL bStartExchange = FALSE;
	static BOOL bStartParty = FALSE;
	static BOOL bStartRefine = FALSE;
	static BOOL bStartProcess = FALSE;
	static BOOL bStartAddFriend = FALSE;
	static DWORD lastTickTime = timeGetTime();

	// [11/19/2008 D.K ] : ���� ���� �׾����� ��Ȱ�̶� ��Ÿ ��� �ɼ� ������ �ʿ��� �κ�.
	int nMsg;

	if( m_Popup->nProcess == POPUP_RESURRECTION )
	{
		if( pCMyApp->m_pUIMgr->m_AutoPlay &&
			pCMyApp->m_pUIMgr->m_AutoPlay->IsRun() &&
			pCMyApp->m_pUIMgr->m_AutoPlay->m_dwGameMode == GAMEMODE_FULL_PACKAGE )
			return 1;

	}

	// ��Ȱ �˾��� ä�ð����ϰ� ����. 07-08-16
	if( (m_Popup->nProcess == POPUP_RESURRECTION || m_Popup->nProcess == POPUP_RECYCLE_ITEM)
			&& ( msg == WM_KEYDOWN || msg == WM_CHAR || msg == WM_IME_STARTCOMPOSITION
				 || msg == WM_IME_COMPOSITION || msg == WM_IME_ENDCOMPOSITION || msg == WM_IME_CHAR
				 || msg == WM_IME_NOTIFY
			   )
	  )
	{
		m_pControlBottom->MsgProc(hWnd, msg, wParam, lParam); // ���Ƿ� ä���� �����ϵ��� ���ν��� ����ó��...

		if( msg == WM_KEYDOWN && (int)wParam == VK_RETURN ) // ���͸� ��Ŀ�� ó��.(���� Ŭ���� �����ؼ� ó�����Ѵ�.���ͷθ� ��Ŀ��..)
		{
			SetFocus(); // �ȿ��� �˾Ƽ� ������������ ó������.
		}

		return 1; // �˾��ʿ��� �����ϵ���.
	}
	else
	{
		nMsg = m_Popup->pMsg_Popup.MsgProc(hWnd, msg, wParam, lParam);	// �׼� �� ������

	}

	if(m_Popup->nProcess == POPUP_EVOLUTIONBALL_USE)
	{
		if( nMsg != 0)
		{
			int Page = atoi(m_Popup->pMsg_Popup.m_InputValue1.GetStrBuf());
			int Time = atoi(m_Popup->pMsg_Popup.m_InputValue2.GetStrBuf());
			char str[128] = {0,};

			if( nMsg == 1)
			{
				//�κ���  �������� ���� �ִ��� ã��
				CItem *pItem = g_pRoh->FindItemByVnumFromAll(2225);
				if( pItem )
				{
					// Ŭ�󿡼� �������� ���� �����ϰ� ���������� ������ ���� �ε��� ���� �����ش�.
					sprintf( str, "gh req %d 1 1 %d %d\n", Page, pItem->m_Index, Time );
					g_pRoh->RemoveByIndex(pItem->m_Index);
					pItem = NULL;
				}
				else
					sprintf( str, "gh req %d 1 0 0 %d\n", Page, Time );
			}
			else if (nMsg == -1 )
				sprintf( str, "gh req %d 1 0 0 %d\n",Page, Time );

			g_pTcpIp->SendNetMessage(str);
		}
	}

	if( m_Popup->nProcess == POPUP_CHANGE_CHAR_NAME )
	{
		if( nMsg == 1 )
		{
			if( GetPremiumExchange() )
			{
				GetPremiumExchange()->SendChangeCharName();
			}
		}
	}

	switch( m_Popup->nProcess)
	{
	case POPUP_LAGRUSH_START:
		if( nMsg == 1)
		{
			pCMyApp->m_pUIMgr->m_AutoPlay->StartProc(GAMEMODE_AUTO);
			GetControlTop()->m_iConAutoOnBtn.SetState( BTN_DISABLE );
			DeletePopup();
			return 1;
		}
		break;
	case POPUP_PREMIUM_CHA_MOVE_FROM:
		if( nMsg == 1)
		{
			GetPremmiumChaMove()->SetStep(FROM, 1);
			if( !IsPremiumChaMove() )
				ShowPremiumChaMove(TRUE);
			DeletePopup();
			SetProcLock(TRUE);
			return 1;
		}
		break;

	case POPUP_PREMIUM_CHA_MOVE_TO:
		if( nMsg == 1)
		{
			GetPremmiumChaMove()->SetStep(TO, 1);
			if( !IsPremiumChaMove() )
				ShowPremiumChaMove(TRUE);

			DeletePopup();
			return 1;
		}
		else if( nMsg == -1 )
		{
			g_pTcpIp->SendNetMessage("premium chmove_req_stop\n");
			// IDS_PREMIUM_MSG_21 ĳ���� �̵��� ����Ǿ����ϴ�.
			InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_21), TYPE_NOR_OK );
			DeletePopup();
			SetProcLock(FALSE);
			return 1;
		}

		break;

	case POPUP_PREMIUM_CHA_MOVE_NAME_INPUT:
		if( nMsg == 1)
		{
			if( !strncmp( m_Popup->pMsg_Popup.m_InputLine.GetStrBuf(), g_pRoh->m_pstrName ,  strlen(g_pRoh->m_pstrName) )  )
			{
				DeletePopup();
				// IDS_PREMIUM_MSG_22 ���� �������� �̵��� �� �����ϴ�.
				InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_22), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				// g_pNk2DFrame->ShowPremiumChaMove(FALSE)	;
				OnClosePremiumChaMove();
				return 1;
			}
			else if( strlen(m_Popup->pMsg_Popup.m_InputLine.GetStrBuf() ) == 0	)
			{
				DeletePopup();
				// InsertPopup("  ",TYPE_PREMIUM_CHA_MOVE_NAME_INPUT, POPUP_PREMIUM_CHA_MOVE_NAME_INPUT);
				InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_04), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				OnClosePremiumChaMove();
				return 1;
			}

			char str[128] = {0,};
			sprintf(str,"premium chmove_req_step 1 %s\n", m_Popup->pMsg_Popup.m_InputLine.GetStrBuf() );
			g_pTcpIp->SendNetMessage(str);
			DeletePopup();
			return 1;
		}
		else if( nMsg == -1)
		{
			OnClosePremiumChaMove();
			SetProcLock(FALSE);
			DeletePopup();
			return 1;
		}

		break;

	case POPUP_PREMIUM_CHA_MOVE_FAIL:
		if( nMsg == 1)
		{
			OnClosePremiumChaMove();
			SetProcLock(FALSE);
			DeletePopup();
			return 1;
		}

		break;
	case POPUP_PREMIUM_CHA_MOVE_WAIT:
		return 1;
		break;
	case POPUP_PREMIUM_CHA_MOVE_SUC_EXIT:
		if( nMsg == 1 )
		{
			OnClosePremiumChaMove();
			SetProcLock(FALSE);
			DeletePopup();
			exit(1);
			return 1;
		}
		break;
	}

	//==========================================================================
	// �ð��� ������ �ڵ����� ������� �˾� ó��
	if( m_Popup->nProcess == POPUP_EXCHANGE )
	{
		if(!bStartExchange)
		{
			lastTickTime = timeGetTime();
			bStartExchange = TRUE;
		}
		else
		{
			if (timeGetTime() >= lastTickTime + 30000) // 30��
				nMsg = -1;
		}
	}
	else if( m_Popup->nProcess == POPUP_FRIEND_ADD_REQ )
	{
		if(!bStartAddFriend)
		{
			lastTickTime = timeGetTime();
			bStartAddFriend = TRUE;
		}
		else
		{
			if(timeGetTime() >= lastTickTime + 30000)
				nMsg = -1;
		}
	}
	else if( m_Popup->nProcess == POPUP_PARTY )
	{
		if(!bStartParty)
		{
			lastTickTime = timeGetTime();
			bStartParty = TRUE;
		}
		else
		{
			if (timeGetTime() >= lastTickTime + 30000)
				nMsg = -1;
		}
	}
	else if( m_Popup->nProcess == POPUP_REFINE )
	{
		if(!bStartRefine)
		{
			lastTickTime = timeGetTime();
			bStartRefine = TRUE;
		}
		else
		{
			if (timeGetTime()>= lastTickTime + 30000)
				nMsg = -1;
		}
	}
	else if( m_Popup->nProcess == POPUP_PROCESS )
	{
		if(!bStartProcess)
		{
			lastTickTime = timeGetTime();
			bStartProcess = TRUE;
		}
		else
		{
			if (timeGetTime() >= lastTickTime + 30000)
				nMsg = -1;
		}
	}
	//==========================================================================

	//==========================================================================
	// �� �˾��� �޼��� ó��
	if( nMsg != 0 )	// �˾��� Ȯ�� �Ǵ� ��ҹ�ư�� ���� ���

	{
		{
			switch( m_Popup->nProcess )
			{
			case POPUP_MONEYGUILDSTOREHOUSE:
				m_pControlGStoreHouse->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
				break;

			case POPUP_GUILD_CREATE:
				break;

			case POPUP_GUILD_NAMEINPUT:
			case POPUP_GUILD_CONFIRM_REQUEST:
				m_pGuildManager->guild_popMsgproc(hWnd, msg, wParam, lParam, nMsg, m_Popup->nProcess, m_Popup->pMsg_Popup.GetCheckPW());
				break;

			case POPUP_GUILD_MONEYEXCHANGE:
				GetControlGStorehouse()->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
				break;

			case POPUP_GUILD_INVASION_FINISH_RES_OK:
				GetUIWindow()->OnOpenWindow(WINDOW_GUILD_BATTLE_INVASION_INFO);
				break;

			case POPUP_GUILD_RANKWAR_INVITE:
				if( nMsg == 1)
					pCMyApp->m_pUIMgr->PrepareChangeWorld(TRUE, WORLD_GUILD_WAR, 0);

				if( nMsg == -1 )
					return 0;

				break;
			default:

				if(m_pGuildManager)
					m_pGuildManager->guild_popMsgproc(hWnd, msg, wParam, lParam, nMsg, m_Popup->nProcess,  m_Popup->pMsg_Popup.GetCheckPW());
				break;
			}
		}


		if( m_Popup->nProcess == 1 )	// Ȯ�� �˾�

		{}
		else if( m_Popup->nProcess == POPUP_GUILDOUT )	// Ȯ��,��� �˾�

		{
			if( nMsg == 1 && g_pTcpIp )
				g_pTcpIp->SendNetMessage("mg leave\n");	// ��� Ż�� ����
		}
		else if( m_Popup->nProcess == POPUP_WINDOW_CLOSE )
		{
			SendMessage( hWnd, WM_CLOSE, 0, 0 );
			return 1;
			//	return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		else if( m_Popup->nProcess == POPUP_SHOP && m_pControlShop )
		{
			if( nMsg == 1 )
				m_pControlShop->WarningPopup(hWnd, msg, wParam, lParam);
			else if( nMsg == -1 )
				pCMyApp->m_bInverseReturn = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_USESHOP_YESNO )
			m_pControlUserShop->PopupMsg(hWnd, msg, wParam, lParam, nMsg, &m_Popup->pMsg_Popup);
		else if( m_Popup->nProcess == POPUP_EVENTANCIENT )
			m_pEventAncient->PopupMsg(hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_GUILDPK )
			m_pGuildPK->MsgProc( hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_INTERCHANGE )
			m_pInterchange->PopupMsg( hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_EXCHANGE )
		{
			m_pControlExchange->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
			bStartExchange = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_PARTY )
		{
			m_pControlParty->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
			bStartParty = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_REFINE )
		{
			if (nMsg == 1 && m_bShowRefine)
				return 1;

			m_pRefine->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
			bStartRefine = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_PROCESS )
		{
			if (nMsg == 1 && m_bShowProcess)
				return 1;

			m_pProcess->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
			bStartProcess = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_QUEST )
			((CQuestData*)m_pInterface[QUEST])->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_GATE )
		{
			((CControlGate*)m_pInterface[GATE])->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
			pCMyApp->m_pUIMgr->m_bNextGoto = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_MONEYEXCHANGE )
			m_pControlExchange->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		else if( m_Popup->nProcess == POPUP_REQUESTPARTY )
		{
			m_pControlParty->ReQuestPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
			if (g_dwLangType == 1)
				m_Popup->pMsg_Popup.m_InputLine.CloseIMC();
		}
		else if( m_Popup->nProcess == POPUP_MONEYUSERSHOP )
			m_pControlUserShop->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, &m_Popup->pMsg_Popup);
		else if( m_Popup->nProcess == POPUP_MONEYWAREHOUSE )
			m_pControlWareHouse->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		else if( m_Popup->nProcess == POPUP_MONEYPROCESS )
			m_pProcess->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		else if( m_Popup->nProcess == POPUP_MONEYREFINE )
			m_pRefine->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		else if( m_Popup->nProcess == POPUP_PETNAME )
		{
			m_pControlPetStatus->NamePopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
			if( g_dwLangType == 1 )
			{
				char *found_sp = NULL;
				if((found_sp = ExamSpChar_for_jpn(m_Popup->pMsg_Popup.GetCheckPW())) != NULL)
				{
					char msgStr[100] = "";
					//-- IDS_CRECHA_UNABLE_STRING_02 : ĳ���� �̸��� "%s" �� ������� �ʽ��ϴ�
					sprintf(msgStr, G_STRING(IDS_CRECHA_UNABLE_STRING_02), found_sp);
					InsertPopup( msgStr, TYPE_EXCHANGE, 22 );
				}
			}
		}
		else if( m_Popup->nProcess == POPUP_MONEYWARTEX )	// �������̽��� ui�� �ƴ϶� nk2dframe�� �־�� �Ѵ�..������ ���� �ּ���


		{
			if( pCMyApp->m_pUIMgr->m_pWarTax )
				pCMyApp->m_pUIMgr->m_pWarTax->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		}
		else if( m_Popup->nProcess == POPUP_PASSMATLIST )	// �������̽��� ui�� �ƴ϶� nk2dframe�� �־�� �Ѵ�..������ ���� �ּ���


		{
			if( pCMyApp->m_pUIMgr->m_pMatList )
				pCMyApp->m_pUIMgr->m_pMatList->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		}
		else if( m_Popup->nProcess == POPUP_WARNINGINVEN )
			m_pControlInven->WarningPopupMsg(hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_DOCUMENT )	// Ȯ��,��� �˾�


			((CControlDocument*)m_pInterface[DOCUMENT])->PopupMsgProc(hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_TIMEITEM )	// �ð��� ������ ������ Ȯ��,��� �˾�

		{
			if( nMsg == 1 && g_pTcpIp )
			{
				g_pTcpIp->SendNetMessage("drop 1\n");
				SAFE_DELETE(g_pRoh->m_ExtraSlot);
			}
		}
		else if( m_Popup->nProcess == POPUP_CASHSHOP_BUY ) ///�������
			m_pControlCashShop->BuyPopupMsg(hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_NPCUPGRADE_BROKEN ) // ��ȭ�� ���� ���.
			m_pUpgrade->BrokenPopupMsg(hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_PET_UPGRADE ) // �� ��ȭ,��ų�� Ȯ�� â.
			m_pPet_Level->PopupMsg(hWnd, msg, wParam, lParam, nMsg);
		else if( m_Popup->nProcess == POPUP_NPCUPGRADE_BROKEN_CHECK ) // ��ȭ�� ���� ���.(���� üũ)
		{
			if( nMsg != 1 ) // Ȯ���� �ƴϸ�
			{
				g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_Result = 0; // ����� �ʱ�ȭ...
			}
			else
			{
				g_pTcpIp->SendNetMessage("npc_up armor_check\n");
			}
		}
		else if( m_Popup->nProcess == POPUP_NPCUPGRADE_RESULT ) // ��ȭ�� ��� â. Ȯ�ι�ư�� �ִ� Ÿ�������� Ű����� ������ �ʰ� �ϱ����� ���� ó��.
		{
			if( nMsg != 1 ) // Ȯ���� ������ �ƴϸ�

				return 1; // �˾� ���Ÿ� ��ġ�� �ʰ� �Լ��� ����������.
			else
				pCMyApp->m_bInverseReturn = FALSE; // ������ �������� �����ߴ� ������ �������� �����ش�.
		}
		else if( m_Popup->nProcess == POPUP_HELPER && m_pControlHelper )  //�İ���
		{
			m_pControlHelper->PopupMsgProc( hWnd, msg, wParam, lParam, nMsg);
			m_bHelper = FALSE;
		}
		else if( m_Popup->nProcess == POPUP_TRAINEEGIVEUP )  //�İ���
		{
			if( nMsg == 1 && g_pTcpIp )
				g_pTcpIp->SendNetMessage( "support disband\n" );
		}
		else if( m_Popup->nProcess == POPUP_HELPER_REJECT && m_pControlHelper )  //�İ��� ���� ����

		{
			m_pControlHelper->PopupMsgProc2( hWnd, msg, wParam, lParam, nMsg);
		}

		else if( m_Popup->nProcess == POPUP_RESURRECTION )
		{
			if( nMsg == 1 && g_pTcpIp )
			{
				g_pTcpIp->SendNetMessage( "revival\n" );
				g_pRoh->m_DeadFrame = -1;
			}
			else if( nMsg == -1 ) // ��Ȱ Ȯ���� ��Ұ� ����.(ESC�� ������ �� ���� ���� �� ������ �̶� �˾��� ����� �ȵȴ�. // 07-03-26 ���� �߰�.
				return 1; // �˾� ���Ÿ� ��ġ�� �ʰ� �Լ��� ����������.
		}
		else if( m_Popup->nProcess == POPUP_GO_DEKAREN1 )	// ��ī��1�� ������ ����°�.
		{
			if( nMsg == 1 && g_pTcpIp )
			{
				pCMyApp->SetTransTime();
				g_pTcpIp->SendNetMessage( "go_inst in 1\n" ); // 1������ ���ڴٰ� �������� �˸�.
			}
		}
		else if( m_Popup->nProcess == POPUP_GO_DEKAREN2 )	// ��ī��2�� �����İ� ����°�.
		{
			if( nMsg == 1 && g_pTcpIp )
			{
				pCMyApp->SetTransTime();
				g_pTcpIp->SendNetMessage( "go_inst in 2\n" ); // 2������ ���ڴٰ� �������� �˸�.
			}
		}
		else if( m_Popup->nProcess == POPUP_GO_DEKAREN3 )	// 1������ ���ǰ���

		{
			if( nMsg == 1 && g_pTcpIp )
			{
				pCMyApp->SetTransTime();
				g_pTcpIp->SendNetMessage( "go_inst out\n" ); // �������� ���ڴٰ� �������� �˸�.
			}
		}
		else if( m_Popup->nProcess == POPUP_LETS_PVP )	///�������
		{
			if( g_pTcpIp )
			{
				if( nMsg == 1 )
					g_pTcpIp->SendNetMessage( "pvp 2 1\n" ); // �³�
				else
					g_pTcpIp->SendNetMessage( "pvp 2 0\n" ); // ����
			}
		}
		else if( m_Popup->nProcess == POPUP_MULTI_SALE )	///�����Ǹ�
		{
			if( nMsg == 1 && g_pTcpIp )
			{
				g_pTcpIp->SendNetMessage( m_pControlInven->m_MultiSaleString ); // ��Ŷ ��ü�� ��Ʈ���� ����ϰ� ����.
			}
		}
		else if( m_Popup->nProcess == POPUP_MULTI_SALE_WARRING ) // ���� �Ǹ��ε� ����� ������ ���̶� ��� ������ϴ� ���.	///�����Ǹ�
		{
			if( nMsg == 1 && g_pTcpIp ) // ��� ���� Ȯ���̹Ƿ� �ٽ� ���� �Ǹ� �޼����� ������Ѵ�.
			{
				// �������� �����ص� �޼����� ���� ã�Ƴ���.
				CItem *pItem = NULL;
				int SlotX, SlotY;
				int keeper, pack, Count;
				char strTemp[256] = "";

				sscanf( m_pControlInven->m_MultiSaleString, "%s %d %d %d %d %d", strTemp, &keeper, &pack, &Count, &SlotX, &SlotY ); // �����ص� ��Ŷ���κ��� ���� ó�� ���� x,y�� ���´�.

				if( pack == g_pRoh->m_CurPackNum ) // Ȥ�� �𸣴� üũ.
				{
					pItem = g_pRoh->FindItemByIndexFromAll( g_pRoh->GetSlotIndex(SlotX, SlotY) ); // �������� ���� �������� ã�´�.
				}

				if( pItem )
				{
					std::string str = boost::str(boost::format(G_STRING(IDS_MULTI_SALE)) % GET_ITEM_NAME_VNUM(pItem->m_Vnum) % Count);
					sprintf(strTemp, "%s", str.c_str());

					InsertPopup( strTemp,TYPE_NOR_OKCANCLE, POPUP_MULTI_SALE );
				}
			}
		}
		else if( m_Popup->nProcess == POPUP_WAREHOUSE_CHECK ) //  [11/19/2007 �����] : �Ϻ� ���� ��û����-�Ⱓ�� �������϶� ���� �޼���

		{
			if( nMsg == 1 )
			{
				if( strcmp( m_strCheckWareHouse, "" ) != 0 )
				{
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage( m_strCheckWareHouse );
				}
			}
		}

		else if( m_Popup->nProcess == POPUP_DMITRON_BATTLE_REQUEST )
		{
			if( nMsg == 1 && g_pTcpIp )
			{
				char Buf[256];
				CDmitronInfo::SelectZone( (int)m_Popup->pArgs );
				sprintf(Buf, "occp bt req %d\n", (int)m_Popup->pArgs);
				g_pTcpIp->SendNetMessage(Buf);
			}

		}
		else if( m_Popup->nProcess == POPUP_DMITRON_TAX_PAYMENT )
		{
			CDmitronBattleTax* pTax = (CDmitronBattleTax*)GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE_TAX);
			if( pTax ) pTax->MoneyPopupMsgProc( hWnd, msg, wParam, lParam, nMsg, m_Popup->pMsg_Popup.GetCheckPW());
		}
		else if (m_Popup->nProcess == POPUP_STASH_FROM_WAREHOUSE_PROC)
		{
			m_pControlWareHouse->PopupMsgProc(hWnd, msg, wParam, lParam, nMsg);
		}
		else if (m_Popup->nProcess == POPUP_STASH_FROM_INVEN_PROC)
		{
			m_pControlInven->PopupMsgProc(hWnd, msg, wParam, lParam, nMsg);
		}
		else if( m_Popup->nProcess == POPUP_FRIEND_ADD_REQ )
		{
			bStartAddFriend = FALSE;
			if( nMsg == 1 )
			{
				SendAddFriend(2, (char*)m_Popup->pArgs);
				SAFE_DELETE_ARRAY(m_Popup->pArgs);
			}
			else if( nMsg == -1 )
			{
				SendAddFriend(3, (char*)m_Popup->pArgs);
				SAFE_DELETE_ARRAY(m_Popup->pArgs);
			}
		}

		else if( m_Popup->nProcess == POPUP_RECYCLE_ITEM )
		{
			int itemIndex = (int)m_Popup->pArgs;
			if( nMsg == 1 )
			{
				g_pTcpIp->SendNetMessage("r_mov\n");
			}
		}

		else if( m_Popup->nProcess == POPUP_GMCOMMAND_LOADITEM )
		{
			if( nMsg == 1 )
			{
				char buf[MAX_PATH] = {0,};
				int itemIndex = (int)m_Popup->pArgs;
				sprintf(buf, "load %d\n", itemIndex);
				g_pTcpIp->SendNetMessage(buf);
			}
		}
		else if( m_Popup->nProcess == POPUP_GMCOMMAND_LOADITEM_10)
		{
			if( nMsg == 1 )
			{
				char buf[MAX_PATH] = {0,};
				int itemIndex = (int)m_Popup->pArgs;
				sprintf(buf, "load %d 10\n", itemIndex);
				g_pTcpIp->SendNetMessage(buf);
			}
		}
		else if( m_Popup->nProcess == POPUP_GMCOMMAND_GOMOB )
		{
			if( nMsg == 1 )
			{
				char buf[MAX_PATH] = {0,};
				int mobVnum = (int)m_Popup->pArgs;
				sprintf(buf, "gomob %d", mobVnum);
				DevTestGmCommand::GetInstance()->run(buf);
			}
		}
		else if( m_Popup->nProcess == POPUP_GMCOMMAND_GONPC )
		{
			if( nMsg == 1 )
			{
				char buf[MAX_PATH] = {0,};
				int mobVnum = (int)m_Popup->pArgs;
				sprintf(buf, "gonpc %d", mobVnum);
				DevTestGmCommand::GetInstance()->run(buf);
			}
		}
		else if( m_Popup->nProcess == POPUP_CHECK_SUMMON_NPC_NOTIFY )
		{
			if( nMsg == 1 )
			{
				int itemIndex = (int)m_Popup->pArgs;
				CItem* pItem = g_pRoh->FindItemByIndexFromAll(itemIndex);
				if( pItem != NULL )
				{
					pCMyApp->m_pUIMgr->Send_UseQuickItem(pItem);
				}
			}
		}
		else if( m_Popup->nProcess == POPUP_EVENT_MAD_INPUT )
		{	
			if( nMsg == 1 )
			{
				char* name = m_Popup->pMsg_Popup.m_InputLine.GetStrBuf();
				char* temp = new char[MAX_PATH];
				memset(temp, 0, MAX_PATH);
				strcpy(temp, name);

				char buf[MAX_PATH] = {0};
				sprintf(buf, (char*)G_STRING(IDS_EVENT_MAD_SURE), name);

				InsertPopup(buf, TYPE_NOR_OKCANCLE, POPUP_EVENT_MAD_SURE, 30, 0, temp);
			}
		}
		else if( m_Popup->nProcess == POPUP_EVENT_MAD_SURE )
		{
			if( nMsg == -1 )
			{
				InsertPopup((char*)G_STRING(IDS_EVENT_MAD_INPUT), TYPE_EXCHANGE, POPUP_EVENT_MAD_INPUT);
			}
			else if( nMsg == 1 )
			{
				if( m_Popup->pArgs )
				{
					std::string charName = (char*)m_Popup->pArgs;
					SendEventMadCharName(charName);
				}
			}

			SAFE_DELETE_ARRAY(m_Popup->pArgs);
		}
		else if( m_Popup->nProcess == POPUP_EVENT_MAD_ERROR )
		{
			if( nMsg == 1 )
			{
				InsertPopup((char*)G_STRING(IDS_EVENT_MAD_INPUT), TYPE_EXCHANGE, POPUP_EVENT_MAD_INPUT);
			}
		}
		else if( m_Popup->nProcess == POPUP_MASTER_DELEGATION )
		{
			bool bConfirm = false;			
			if( nMsg == 1 )
			{
				bConfirm = true;
			}

			SendMasterDelegation(bConfirm);
		}
		else if( m_Popup->nProcess == POPUP_CHAT_SHOUT )
		{
			if( nMsg == 1 )
			{
				char* msg_shout = m_Popup->pMsg_Popup.m_InputLine.GetStrBuf();
				if( strlen(msg_shout) > 100 )
				{
					InsertPopup((char*)G_STRING(IDS_SHOUT_OVERLENGTH), TYPE_NOR_OK);
					DeletePopup();
					return 1;
				}
				else if( strlen(msg_shout) <= 0 )
				{
					InsertPopup((char*)G_STRING(IDS_SHOUT_UNDERLENGTH), TYPE_NOR_OK);
					DeletePopup();
					return 1;
				}

				int slot_num = (int)m_Popup->pArgs;
				if( slot_num < 0 || slot_num >= QUICK_SLOT_NUM*QUICK_SLOT_PAGE )
				{					
					InsertPopup((char*)G_STRING(IDS_SHOUT_NOITEM), TYPE_NOR_OK);
					DeletePopup();
					return 1;
				}
				CItem* pItem = g_pRoh->m_QuickSlot[slot_num];
				if( pItem == NULL )
				{
					InsertPopup((char*)G_STRING(IDS_SHOUT_NOITEM), TYPE_NOR_OK);
					DeletePopup();
					return 1;
				}

				int type = GET_SHAPE(pItem);				
				int index = pItem->m_Index;				

				ShoutChatMgr* shoutMgr = ShoutChatMgr::GetInstance();
				shoutMgr->Clear();
				shoutMgr->SetSlotNum(slot_num);
				shoutMgr->SetItemType(type);
				shoutMgr->SetItemIndex(index);
				shoutMgr->SetMessage(msg_shout);

				InsertPopup((char*)G_STRING(IDS_SHOUT_CONFIRM), TYPE_NOR_OKCANCLE, POPUP_CHAT_SHOUT_CONFIRM);
			}
		}
		else if( m_Popup->nProcess == POPUP_CHAT_SHOUT_CONFIRM )
		{
			if( nMsg == 1 )
			{
				ShoutChatMgr* shoutMgr = ShoutChatMgr::GetInstance();
				int slotNum = shoutMgr->GetSlotNum();
				int itemType = shoutMgr->GetItemType();
				int itemIndex = shoutMgr->GetItemIndex();
				std::string strMessage = shoutMgr->GetMessage();

				SendShout(itemType, slotNum, itemIndex, strMessage);
			}
		}		
		else if( m_Popup->nProcess == POPUP_BATTLELEAGUE )
		{
			if( nMsg == 1 )
			{
				SendPromotion();
			}
		}
		else if( m_Popup->nProcess == POPUP_BINGO_TEN_TIME )
		{
			if( nMsg == 1 )
			{
				ControlBingo* pBingo = (ControlBingo*)m_pInterface[BINGO];				
				pBingo->ActionRegist(eBingoRegType_Many);
			}
		}
		else if( m_Popup->nProcess == POPUP_GIFTTIME )
		{
			if( nMsg == 1 )
			{
				SendGiftTime();
			}
		}
		else if( m_Popup->nProcess == POPUP_PET_EQUIP )
		{
			if( nMsg == 1 )
			{
				int pack = -1;
				CItem* pItem = g_pRoh->FindItemAndPackByIndexFromAll((int)m_Popup->pArgs, pack);
				if(pItem != NULL && pack != -1)
				{
					SendPetEquip(pack, pItem->m_SlotX, pItem->m_SlotY);
				}				
			}
		}

		DeletePopup();	// Ȯ���̵� ��ҵ� ������ �˾� ����
		return 1;
	}
	else
	{
		{
			if(m_Popup->nProcess == POPUP_GUILD_RECOMMAND)
				return 1;

			if(m_Popup->nProcess == POPUP_GUILD_NAMEINPUT)
				return 1;
			if(m_Popup->nProcess == POPUP_REQUESTPARTY)
				return 1;
			if(m_Popup->nProcess == POPUP_GUILD_RECOM_MEMBER)
				return 1;
		}
	}
	//==========================================================================

	return 0; // 06-10-02 ����Ʈ ���ϰ� 1���� 0���� �ٲ�.(����) , �̰� 1�̸� �ڿ� �޼������� ���õǼ� â�̵����� �޼����� ���������� ó���ȵǴ� ������ �־���. �׷��� �̰� 0���� �ٲ������� �޼��� �˾��� ���۵��� ���ɼ��� ������ ����!
}


bool CNk2DFrame::IsPopUpTyping() // �˾� �Է��� �ް� �ִ����� ���� üũ�Լ�.
{
	if( !m_Popup ) // �˾��� ������ �ǹ� ����.
		return FALSE;

	if( m_Popup->nProcess == POPUP_MONEYUSERSHOP
			|| m_Popup->nProcess == POPUP_MONEYEXCHANGE
			|| m_Popup->nProcess == POPUP_MONEYWAREHOUSE
			|| m_Popup->nProcess == POPUP_MONEYPROCESS
			|| m_Popup->nProcess == POPUP_MONEYREFINE
			|| m_Popup->nProcess == POPUP_PETNAME
			|| m_Popup->nProcess == POPUP_MONEYWARTEX
			|| m_Popup->nProcess == POPUP_GUILD_MONEYEXCHANGE
	  ) // �Է±���� �ִ� �˾� ��������..
	{
		if( m_Popup->pMsg_Popup.m_InputLine.GetEnable()
				|| m_Popup->pMsg_Popup.m_InputValue1.GetEnable()
				|| m_Popup->pMsg_Popup.m_InputValue2.GetEnable()
				|| m_Popup->pMsg_Popup.m_InputValue3.GetEnable()
		  )
			return TRUE;
	}

	// �Է±���� ������ �������.
	return FALSE;
}

void CNk2DFrame::ShowCashShopWindow( BOOL bShow ) ///�������
{
	if(Check_All_MsgPopUp()) // 2006 ���� ���� ó���� �ణ �޶�����.
		return;
//	if(m_bAutoMouse) ///07-04-12 ����Ȯ�� �ý��� Ÿ �������̽��� �Բ� �� �� �ְ� ����.
//		return;

	CloseAllWindow();

	m_bShowCashShop = bShow; // CloseAllWindow() ���н� ó���� �� ���� �������� �༮���� ������ �̰� ����������Ѵ�.

	if( bShow )
	{
		if( m_bShowCashShopIntro ) ///�������
		{
			ShowCashShopIntroWindow( FALSE );
		}
	}
	else // ����..
	{
		if( m_pControlCashShop )
		{
			m_pControlCashShop->ClearDta(); // Dta�� ���� ���� ���� �ε�.(�޸� ������ ����)
		}
	}
}

void CNk2DFrame::ToggleCashShopWindow( int type ) // type���� �پ��� �������� ����Ҽ��ֵ���.... ///�������
{
	if( !m_pControlCashShop ) // Ȥ�ö� �������
		return;

	if( g_pRoh->m_HaveCash <= 0 )
	{	
		return;
	}

	ShowCashShopWindow( !m_bShowCashShop );

	if( IsCashShopVisible() )
	{
		if( !m_pControlCashShop->m_bResLoad )
		{
			m_pControlCashShop->LoadRes();

		}

		m_pControlCashShop->m_iShopKind = type;

		if( type == CASHSHOP_TYPE_NORMAL )
		{
			m_pControlCashShop->ClearDta();

			m_pControlCashShop->ReadDta( type, "./data/CashShop.dta" );

			if( !m_pControlCashShop->m_DtaData[type].m_bImageLoad )
			{
				m_pControlCashShop->LoadFromDta( type );
			}
		}

		m_pControlCashShop->OpenInit(); // ���������� �ʱ�ȭ���� �༮��.
	}
	else
	{

	}
}

void CNk2DFrame::ShowCashShopIntroWindow( BOOL bShow ) ///�������
{
	if(Check_All_MsgPopUp()) // 2006 ���� ���� ó���� �ణ �޶�����.
		return;
//	if(m_bAutoMouse) ///07-04-12 ����Ȯ�� �ý��� Ÿ �������̽��� �Բ� �� �� �ְ� ����.
//		return;

	CloseAllWindow();

	m_bShowCashShopIntro = bShow; // CloseAllWindow() ���н� ó���� �� ���� �������� �༮���� ������ �̰� ����������Ѵ�.

	if( bShow )
	{
		if( m_bShowCashShop ) ///�������
			ShowCashShopWindow( FALSE );
	}
	else // ����..
	{
		if( m_pCashShopIntro )
			m_pCashShopIntro->Close(); // �� ������ �����츦 �����ش�.
	}
}

void CNk2DFrame::ToggleCashShopIntroWindow( int type ) // type���� �پ��� �������� ����Ҽ��ֵ���.... ///�������
{
	if( !m_pCashShopIntro ) // Ȥ�ö� �������

		return;

	if( GetClientWidth() == 640 ) // 640*480 ��忡���� �ϴ� ĳ������ ����������...
	{
		//-- IDS_NOT_SURRPOT_DISPLAY : ���� ���� �ػ󵵿����� �������� �ʽ��ϴ�
		pCMyApp->m_pUIMgr->CmdErrorMsg( (char*)G_STRING(IDS_NOT_SURRPOT_DISPLAY) );
	}

	ShowCashShopIntroWindow( !m_bShowCashShopIntro );
	if( IsCashShopIntroVisible() )
	{
		m_pCashShopIntro->Open();

		sprintf(commOutBuf, "multi_shop cash\n" ); // ĳ�� ���� ��û ��Ŷ�� �ѹ� ������.(�±� ��ī�� ĳ����붧���� �ʿ�..)
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage(commOutBuf);
	}
}

BOOL CNk2DFrame::CheckFullScreenInterface() // ȭ���� ���������� ����ϴ� �������̽��� �����ִ��� üũ�ϴ� �Լ�. ///��������� �߰�
{
	// �ػ� ���� ������.
	switch( GetClientWidth() )
	{
	case 640:
		break;
	case 800:

		if( IsCashShopVisible() ) // �������
			return TRUE;

		if( IsCashShopIntroVisible() ) // ������� ��Ʈ��
			return TRUE;

		break;
	case 1024:
		break;
	}

	return FALSE;
}

void CNk2DFrame::ShowHelperWindow(BOOL bShow) //�İ���
{
	if( !CloseAllWindow(FALSE) )
		return;

	if( bShow )
	{
		m_bHelper = bShow;
	}
}

void CNk2DFrame::ShowHelpPetWindow( BOOL bShow, int Type ) ///�굵��
{
	// �� �༮�� ���� ó���� Ư���ϴ�. 3D�� �������̽��� �ٸ� �������̽��� ���� �ʴ´�.
	if( !bShow ) // ���� ���..
	{
		// �׳� �޸� ������ ������.
		if( m_pControlHelpPet )
		{
			SAFE_DELETE( m_pControlHelpPet );
		}

		m_bHelpPet = false;

		///�굵��Ȯ��

		FILE *fp;
		fp = fopen( "data/etc/OnOff.txt", "wt" ); // �׾����� �������� ����.
		fprintf( fp, "0\n" ); // ����.
		fclose( fp );
	}
	else // Ű�� ���.
	{
		SAFE_DELETE( m_pControlHelpPet );

		m_pControlHelpPet = new CControlHelpPet;
		if( !m_pControlHelpPet )
			return;
		m_pControlHelpPet->LoadRes( Type );

		m_pControlHelpPet->SetPetAnimation( HELPPET_ANI_NORMAL ); // �ʱ�ȭ

		// ���� ���.
		if( g_pRoh->m_Chaotic_Grade ) // �̰� 0�� �ƴϸ� ī�����´�.
			// IDS_PETHELP_GREET_CHAO : �� �� ������ �������� �˾Ƽ� �ϸ� �ȵǰڴ�?
			m_pControlHelpPet->ExcuteHelpTalk( (char *)G_STRING(IDS_PETHELP_GREET_CHAO) );  // �λ� ��縦 �־��ش�.
		else
			// IDS_PETHELP_GREET_PEACE : ������� ��ȹ�ڵ鵵 ������ �� ��׹ڻ�\\n ��񿡰� � �����������

			m_pControlHelpPet->ExcuteHelpTalk( (char *)G_STRING(IDS_PETHELP_GREET_PEACE) ); // �λ� ��縦 �־��ش�.

		m_bHelpPet = true;

		///�굵��Ȯ��

		// by evilkiki 2009.09.17
		FILE *fp;
		fp = fopen( "data/etc/OnOff.txt", "wt" ); // �׾����� �������� ����.
		fprintf( fp, "1\n" ); // �״�.
		fclose( fp );
	}
}


void CNk2DFrame::ShowControlGuild(BOOL bShow)
{

	if( !CloseAllWindow(FALSE) )
		return;

	if( bShow )
	{
		m_bShowControlGuild = bShow;

		if(g_pRoh->GetMyGuildData() != NULL)
		{
			m_pControlGuild->Set_btn_status(TRUE, g_pRoh->GetMyGuildLevel());

			m_pControlGuild->set_revision(g_pRoh->GetMyGuildRevisionTime());
		}
		else
			m_pControlGuild->Set_btn_status(FALSE, -1);
	}
	else
		m_pControlGuildManager->HookClose();
}

void CNk2DFrame::ShowControlGuildManage(BOOL bShow)
{
	if( !CloseAllWindow(FALSE) )
		return;

	if( bShow )
	{
		m_bShowControlGuildManage = bShow;

		if(g_pRoh->GetMyGuildData() != NULL)
		{
			if(g_pRoh->GetMyGuildLevel() == JOB_MASTER)	m_pControlGuildManager->set_btn_status(TRUE);

			if(g_pRoh->GetMyGuildLevel() == JOB_ASSISTANTMASTER) m_pControlGuildManager->set_btn_status(FALSE);
		}
	}
	else
		m_pControlGuildManager->HookClose();
}

void CNk2DFrame::ShowControlGuildBattle(BOOL bShow)
{

	if( bShow )
	{
		GetControlGuildBattle()->LoadResource();
		GetControlGuildBattle()->SetActive(true);
	}
	else
	{
		SAFE_DELETE_RES(GetControlGuildBattle());
		GetControlGuildBattle()->SetActive(false);
	}
}


void CNk2DFrame::ShowPVPWidget( BOOL bShow )
{
	m_bShowPVPWidget = bShow;

	if (m_pPVPWidget)
	{
		if (bShow == TRUE)
			m_pPVPWidget->InitVariables();
	}

}

BOOL CNk2DFrame::IsItemMultiMoveEnable() // �κ� ������ ����Ŭ���� �����̵� ����� ����ϴ� â�� ���ֳ� üũ���ִ� �Լ�. ���� �κ����� ���� ��� üũ�ѹ� ���ֵ��� �߰�(07-02-20 ����)
{
	// ��ȯâ. ���� �������� ���������� �κ� ������ Ŭ������ ��� ���ϰ�
	if( IsUserShopVisible() || GetControlWareHouse()->IsActivate()
			|| IsExchangeVisible() || IsUpgradeVisible() || IsEventAncientVisible()
			|| ( IsGambleVisible() && GetGamble()->m_bType == 0 ) ) // ������ ����Ŭ������ �����̵���Ű�� â���� ��������...
		return TRUE;

	return FALSE;
}


// [3/5/2007 Theodoric] �������� ������ ����

void CNk2DFrame::SetConnectServerName(char *str)
{
	int strSize = strlen(str)+1;
	SAFE_DELETE_ARRAY(m_strConnectServerName);
	m_strConnectServerName = new char[strSize];
	ZeroMemory(m_strConnectServerName, strSize);
	memcpy(m_strConnectServerName, str, strSize );
}

void CNk2DFrame::InitDmitronInfo()
{
	m_pDmitronBattleStatus->Init();
}

void CNk2DFrame::SetDmitronInfo1(int index, int status)
{
	m_pDmitronBattleStatus->SetDmitronInfo1(index, status);
}

void CNk2DFrame::SetDmitronInfo2(int index, int status, char* myGuildName, int myGuildPoint,
								 char* topGuildName, int topGuildPoint, int lastTime, int elapsedTime)
{
	m_pDmitronBattleStatus->SetDmitronInfo2(index, status, myGuildName, myGuildPoint,
											topGuildName, topGuildPoint, lastTime, elapsedTime);
}

void CNk2DFrame::DisplayDmitronInfo()
{
	m_pDmitronBattleStatus->MakeDrawPopup();
}

void CNk2DFrame::ShowPremiumExchange(int type, int nSlot)
{
	m_bShowPremiumExchange = TRUE;
	m_pPremiumExchange->SetInfo(type, nSlot);
}

void CNk2DFrame::HidePremiumExchange()
{
	m_bShowPremiumExchange = FALSE;
}

BOOL CNk2DFrame::CheckPremiumChaMoveInfo()
{
	if( CheckPremiumChamoveScroll() == FALSE )
	{
		return FALSE;
	}


	return TRUE;
}


BOOL CNk2DFrame::CheckPremiumChamoveScroll()
{
	int i,j;//,p;

	if(!g_pRoh)
		return FALSE;

	// �̺�Ʈ �ǻ� �˻�
	for(i=0; i<WEARING_NUM; i++)
	{
		if( g_pRoh->m_EventWearing[i] != NULL)
		{
			// IDS_PREMIUM_MSG_23 �̺�Ʈ �ǻ��� ����ּ���.
			InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_23), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
			return FALSE;
		}
	}

	// ���콺�� ��� �ִ��� �˻�

	if( g_pRoh->m_ExtraSlot != NULL)
	{
		// IDS_PREMIUM_MSG_24 ���콺�� ��� �ִ� �������� ������մϴ�.
		InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_24), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
		return FALSE;
	}

	if( m_pControlExchange )
	{
		for( i=0; i<EXG_SLOT_X_NUM; i++)
			for( j=0; j<EXG_SLOT_Y_NUM; j++)
			{
				if( m_pControlExchange->m_ExgOppSlot[i][j] != -1)
				{
					// IDS_PREMIUM_MSG_25 ��ȯâ�� ����ּ���.
					InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_25), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
					return FALSE;
				}
			}
	}

	for(i=0; i<QUICK_SLOT_NUM*QUICK_SLOT_PAGE; i++)
	{
		if( g_pRoh->m_QuickSlot[i] )
		{
			if(g_pRoh->m_QuickSlot[i]->m_Vnum != 2101)
			{
				// IDS_PREMIUM_MSG_26 �����Կ� ĳ���� �̵� �����縦 ������ �ٸ� �������� ��� ����ּ���.
				InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_26), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CNk2DFrame::CheckPremiumLetter()
{
	BOOL result;

	result = m_pControlLetter->LetterListMessage(g_nServerIndex,g_pRoh->m_pstrName,g_pRoh->m_nUserIndex,1);
	if( result == FALSE)
	{
		// IDS_PREMIUM_MSG_27 ���� ��� �� ������ ��� ����ּ���

		InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_27), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
		return FALSE;
	}

	result = m_pControlLetter->LetterFriendListMessage(g_nServerIndex,pCMyApp->m_strLetterUserId,g_pRoh->m_nUserIndex);
	if( result == FALSE)
	{
		// IDS_PREMIUM_MSG_28 ���� ģ�� ����Ʈ�� ��� ����ּ���

		InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_28), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
		return FALSE;
	}

	result = m_pControlLetter->LetterBlockListMessage(g_nServerIndex,g_pRoh->m_pstrName);
	if( result == FALSE)
	{
		// IDS_PREMIUM_MSG_29 ���� �ź� ����Ʈ�� ��� ����ּ���.
		InsertPopup((char*)G_STRING(IDS_PREMIUM_MSG_29), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
		return FALSE;
	}


	return TRUE;
}

BOOL CNk2DFrame::OnClosePremiumChaMove()
{
	// â�� ���� �ִٸ� �ݾ�����.
	if( m_bShowPremiumChaMove )
		ShowPremiumChaMove(FALSE);

	SetProcLock( FALSE );

	return  ClossePremiumMsgBox();

}


BOOL CNk2DFrame::ClossePremiumMsgBox()
{
	if( m_Popup == NULL)
		return TRUE;

	// ����Ʈ �˾��� �� �ִٸ� �׳� ��������.
	POPUP *pPopup = m_Popup;

	switch( pPopup->nProcess )
	{
	case POPUP_PREMIUM_CHA_MOVE_FROM:
	case POPUP_PREMIUM_CHA_MOVE_TO:
	case POPUP_PREMIUM_CHA_MOVE_WAIT:
	case POPUP_PREMIUM_CHA_MOVE_NAME_INPUT:
		m_Popup = pPopup->pNext;
		pPopup->pNext = NULL;
		delete pPopup;
		break;
	}
	pPopup = NULL;

	return TRUE;

}

void CNk2DFrame::PremiumChaMoveWear(int where, int index, int vnum, int gem_num, int special, int special2,
									int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur) ///�Ź���ȭ�ý���
{
	m_pPremiumChaMove->Wear(where, index, vnum, gem_num, special, special2, UpEndur, MaxUpdEndur, Endur, MaxEndur);
}

void CNk2DFrame::WareHouseStrCopy(char *str)
{
	if( strcmp( str, "" ) == 0 )
		return;

	memcpy(m_strCheckWareHouse, str, strlen(str));
}


bool CNk2DFrame::IsInPopup(int x, int y)
{
	// top , compas , chatting Ŭ���� ��� �ұ��?
	if( !GetControlInven() || !GetControlBottom() )
		return false;

	if( GetControlInven()->IsInside( x, y ) || GetControlBottom()->IsInside( x, y ) )
		return true;

	return false;
}

void CNk2DFrame::SetMyMoney(int money)
{
	if (m_bShop)
		GetControlShop()->SetMoney();

	if( m_bPetLevel )
		GetPetLevel()->SetMoney(money);
}

void CNk2DFrame::InitExpTable()
{	
	m_exp_require[0] = 150;
	m_exp_accumulate[0] = 150;

	for( int i=1 ; i<249 ; i++ ) // 2~249
	{
		if( CommonConfig::Instance()->GetKorFlag() == true )
		{
			m_exp_accumulate[i] = ((UINT64)i*i*i*i/2) + ((UINT64)i*i*i) + ((UINT64)250*i*i) - ((UINT64)3*i) + 352;
		}
		else if( CommonConfig::Instance()->GetThaFlag() == true )
		{
			m_exp_accumulate[i] = ( ((UINT64)i*i*i*i/2) + ((UINT64)i*i*i) + ((UINT64)250*i*i) - ((UINT64)3*i) + 352 ) / 2;
		} 
		else
		{
			m_exp_accumulate[i] = ((UINT64)i*i*i*i/2) + ((UINT64)i*i*i) + ((UINT64)250*i*i) - ((UINT64)3*i) + 352;
		}

		m_exp_require[i] = (UINT64)m_exp_accumulate[i] - (UINT64)m_exp_accumulate[i-1];
		_asm nop;
	}

	//
	for( int i=249 ; i< 259 ; i++ ) // 250~259
	{
		m_exp_require[i] = (UINT64)100000000 * ( (UINT64)(i+1-250) / 10 + 1) ;
		m_exp_accumulate[i] = (UINT64)m_exp_accumulate[i-1] + (UINT64)m_exp_require[i];
		_asm nop;
	}
	for( int i=259 ; i< 339 ; i++ ) // 260~339
	{
		m_exp_require[i] = (UINT64)100000000 * ( ( (UINT64)(i+1-250) / 10 + 1) + ( (i+1-260) / 10 ) );
		m_exp_accumulate[i] = (UINT64)m_exp_accumulate[i-1] + (UINT64)m_exp_require[i];
		_asm nop;
	}

	for( int i=339 ; i<LH_MAX_LEVEL ; i++ ) // 340~400
	{
		m_exp_require[i] = (UINT64)m_exp_require[i-1] + (UINT64)(i+1)*10000000;
		m_exp_accumulate[i] =(UINT64)m_exp_accumulate[i-1] + (UINT64)m_exp_require[i];
		_asm nop;
	}

	m_exp_init = true;
}


//
UINT64 CNk2DFrame::GetExpAccumulate()
{
	if( !m_exp_init || !g_pRoh )
		return 0;

	if( g_pRoh->m_Level < 250 )
		return g_pRoh->m_Exp;

	return m_exp_accumulate[g_pRoh->m_Level-1] + (UINT64)g_pRoh->m_Exp;
}


// ���緹������ �ʿ��� ����ġ
UINT64 CNk2DFrame::GetExpRequire()
{
	if( !m_exp_init || !g_pRoh )
		return 0;

	return (UINT64)m_exp_require[g_pRoh->m_Level-1];
}

// ���緹������ ���� ����ġ
UINT64 CNk2DFrame::GetExpRemain()
{
	if( !m_exp_init || !g_pRoh )
		return 0;

	return (UINT64)g_pRoh->m_NeedExp;
}


UINT64 CNk2DFrame::GetExpGet()
{
	if( !m_exp_init || !g_pRoh )
		return 0;

	if( g_pRoh->m_Level == 1 )
		return g_pRoh->m_Exp;
	else if( g_pRoh->m_Level < 250 )
		return g_pRoh->m_Exp - m_exp_accumulate[g_pRoh->m_Level-2];

	return m_exp_require[g_pRoh->m_Level-1] - g_pRoh->m_NeedExp;
}

int CNk2DFrame::GetRSkill()
{
	if( !GetControlBottom() )
		return -1;

	return GetControlBottom()->GetRSkill()->GetCurSkill();
}

int CNk2DFrame::GetLSkill()
{
	if( !GetControlBottom() )
		return -1;

	return GetControlBottom()->GetLSkill()->GetCurSkill();
}

void CNk2DFrame::SetRSkill(int index)
{
	if( GetControlBottom() )
		GetControlBottom()->GetRSkill()->SetCurSkill(index);
}

void CNk2DFrame::SetLSkill(int index)
{
	if( GetControlBottom() )
		GetControlBottom()->GetLSkill()->SetCurSkill(index);
}

bool CNk2DFrame::CreateLHUI(int ui, int param)
{
	enum CreateUIType
	{
		CreateUIType__TakeOutBox = 0,

		CreateUIType__EndOfNum
	};

	switch( (CreateUIType)ui )
	{
	case CreateUIType__TakeOutBox:
		SAFE_DELETE(m_ui_takebox);
		m_ui_takebox = new LHUI_TakeBox((TakeBox_Type)param);
		break;

	default:
		return false;
	}
	return true;
}

void CNk2DFrame::ShowGateWindow(bool show , int gate_value , bool direct)
{
	CloseAllWindow();

	if( show )
	{
		if( GetGate() )
		{
			GetGate()->ResetAll();
			GetGate()->LoadRes();
		}
		else
			m_ui_gate = new LHUI_Gate();

		m_ui_gate->SetZoneList(gate_value , direct);
	}
	else
	{
		if( GetGate() )
			GetGate()->ResetAll();
	}
}


BOOL CNk2DFrame::IsVisibleTakebox()
{
	if( GetTakeOutBox() )
		return GetTakeOutBox()->_GetVisible();

	return false;
}

bool CNk2DFrame::ShowTakeboxWindow( BOOL bShow , int type)
{
	if( bShow )
	{
		pCMyApp->StopHero();

		if( m_dwTakeBox_Time != 0 && GetTickCount() - m_dwTakeBox_Time < 3000 )
		{
			AddChatStr( "��ø� ��ٷ� �ֽʽÿ�." , -1 );
			return false;
		}

		if( GetTakeOutBox() )
			SAFE_DELETE(m_ui_takebox);

		m_ui_takebox = new LHUI_TakeBox((TakeBox_Type)type);
		m_ui_takebox->m_send_delay = m_dwTakeBox_Time;
		m_ui_takebox->Request_List();

		m_dwTakeBox_Time = GetTickCount();
	}
	else
	{
		SAFE_DELETE(m_ui_takebox);
	}

	return true;
}

bool CNk2DFrame::IsScroll(CItem* pItem)
{
	return (GET_TYPE(pItem) == ITYPE_ETC && GET_SHAPE(pItem) == IETC_SCROLL)?true:false;

}


void CNk2DFrame::RenderItemInUI(int x, int y, CItem* pItem, BOOL over, BOOL bMove,BOOL ignore_size, BOOL begin_end, float fScale)
{
	if( !GetItemRender() || !pItem )
		return;

	DWORD ambient = 0x00808080;
	ambient = 0x00cccccc;

	if( over )
	{
		ambient = 0x00ffffff;
	}
	else

	{
// 		if(  IsScroll(pItem)
// 			|| pItem->m_Vnum == 1251
// 			|| pItem->m_Vnum == 1308
// 			|| pItem->m_Vnum == 1286
// 			|| ( pItem->m_Vnum >= 1598 && pItem->m_Vnum <= 1695 )
// 			|| pItem->m_Vnum == 1287 )
// 			ambient = 0x00cccccc;
// 		else
		if (pItem->m_PlusNum > 0)
			ambient = UPGRADE_ITEM_COLOR;
	}

	if( ItemInfoScaleMgr::GetInstance()->IsNoScale(pItem->m_Vnum) == true )
	{
		if( ignore_size == TRUE )
		{
			fScale = 1.0f;
		}
		else
		{
			fScale = 0.5f;
		}
	}

	GetItemRender()->RenderLolo(x, y , GET_LOLO(pItem), GET_LOLOTEXTR_NUM(pItem), ambient, bMove, GET_ITEM_WIDTH_S(pItem), GET_ITEM_HEIGHT_S(pItem), begin_end, -1, -1, ignore_size, fScale);
}

void CNk2DFrame::RenderItemInUIWithSize(int vnum, int x, int y, int sizeX, int sizeY)
{
	int protoNum = g_ItemList.FindItem(vnum);

	if( !GetItemRender() || GET_LOLOC(protoNum) == NULL )
		return;

	DWORD ambient = 0x00cccccc;

	GetItemRender()->RenderLolo(x, y , GET_LOLOC(protoNum), -1, ambient, FALSE, -1, -1, TRUE, sizeX, sizeY, TRUE);
}

BOOL CNk2DFrame::IsFriendVisible()
{
	if( m_ui_friend == NULL )
		return false;

	return m_ui_friend->IsVisible();
}

void CNk2DFrame::ShowFriend( BOOL bShow )
{
	if( m_ui_friend )
		m_ui_friend->SetVisible(bShow);

	return;
}

void CNk2DFrame::ToggleFriend()
{
	if( m_ui_friend == NULL )
		return;

	ShowFriend( ! m_ui_friend->IsVisible() );
}

unsigned __stdcall CNk2DFrame::ThreadLoading(void* pParam )
{
	CMyD3DApplication* app = (CMyD3DApplication*)pParam;
	app->StartGame();

	return 1;
}

unsigned __stdcall CNk2DFrame::ThreadGoWorldLoading( void* pParam )
{
	CMyD3DApplication* app = (CMyD3DApplication*)pParam;
	app->GoWorldLoading();

	return 1;
}
