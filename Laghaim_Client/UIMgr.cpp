#include "stdafx.h"
#include <wingdi.h>
#include <winuser.h>
#include <time.h>
#include <direct.h>
#include <assert.h>
#include <list>
#include <boost/tokenizer.hpp>
#include <Process.h>
#include "main.h"
#include "Land.h"
#include "Nk2DFrame.h"
#include "NkCharacter.h"
#include "NkMob.h"
#include "ItemProto.h"
#include "Item.h"
#include "ItemRender.h"
#include "UIMgr.h"
#include "Tcpipcon.h"
#include "TcpUtil.h"
#include "resource.h"
#include "LoginDlg.h"
#include "GUtil.h"
#include "DecoObj.h"
#include "Frustum.h"
#include "D3DMath.h"
#include "WeatherMgr.h"
#include "NkKeyboard.h"
#include "ControlBottom.h"
#include "ControlShop.h"
#include "NkPet.h"
#include "ControlExchange.h"
#include "Interchange.h"
#include "ControlInven.h"
#include "ControlParty.h"
#include "ControlMap.h"
#include "ChaAct.h"
#include "ChaSta.h"
#include "DirtSnd.h"
#include "LoadEffectSound.h"
#include "ImageDefine.h"
#include "FxSet.h"
#include "MsgPopUp.h"
#include "Skill.h"
#include "AlphaPopup.h"
#include "controlwarehouse.h"
#include "Path.h"
#include "Gamble.h"
#include "Refine.h"
#include "Compas.h"
#include "Cmd.h"
#include "Mouse.h"
#include "scrollbox.h"
#include "headers.h"
#include "BasicMenu.h"
#include "WarInfo.h"
#include "SpecialItem.h"
#include "ijl.h"
#include "changehair.h"
#include "wartax.h"
#include "guardtower.h"
#include "warrequest.h"
#include "NkMyPet.h"
#include "ControlPetShop2.h"
#include "lshiftmenu.h"
#include "ControlPetKeep.h"
#include "guildwar.h"
#include "product.h"
#include "PetProduct.h"
#include "ControlScore.h"
#include "pet_level.h"
#include "Event_Ancient.h"
#include "platinum.h"
#include "SummerEvent.h"
#include "ClrAlloc.h"
#include "questdata.h"
#include "matlist.h"
#include "matmakeroom.h"
#include "listbox.h"
#include "newlistbox.h"
#include "matbattleUI.h"
#include "matsurvivalUI.h"
#include "Country.h"
#include "AutoMouse.h"
#include "ControlTeleportItem.h"
#include "WebWorld.h"
#include "NKObjQuadNode.h"
#include "ControlLowGuildMaster.h"
#include "g_devlogbox.h"
#include "g_stringmanager.h"
#include "AutoPlay_test.h"
#include "ControlTop.h"
#include "ShadowRect.h"
#include "GuildHunt.h"
#include "DmitronBattle.h"
#include "DmitronBattleTax.h"
#include "ReservationWindow.h"
#include "ControlUserShop.h" ///���λ���
#include "Process.h"
#include "ControlGate.h"
#include "FxFollow.h" ///��
#include "FxParticle.h" ///��Ʈ�ε�
#include "WorldCupStart.h"
#include "ControlHelper.h"
#include "ControlHelpPet.h" ///�굵��
#include "s_guild_manager.h"
#include "ControlGuildSHouse.h"
#include "ControlGuildM.h"
#include "WindowMgr.h"
#include "guild_battle.h"
#include "guild_search.h"
#include "guild_promotion.h"
#include "s_notice_control.h"
#include "s_Job_control.h"
#include "s_grade_control.h"
#include "Fx_BossRaid_bulkan2_02.h"
#include "Fx_BossRaid_Human2_02.h"
#include "Fx_BossRaid_Human2_03.h"
#include "Fx_BossRaid_Aidia2_03.h"
#include "Fx_BossRaid_LastBoss_02.h"
#include "Fx_BossRaid_LastBoss_03.h"
#include "Fx_BossRaid_LastBoss_04.h"
#include "PremiumExchange.h"
#include "LHUI_OpEvent.h"
#include "guild_mark.h"
#include "InterFileConnection.h"
#include "WindowMgr.h"
#include "EventScriptActor.h" ////Ʃ�丮��
#include "NPC_Define.h"
#include "LHUI_TakeBox.h"
#include "ControlPetStatus.h"
#include "ControlDocument.h"
#include "LHUI_Gate.h"
#include "ControlUpgrade.h"
#include "UIFriend.h"
#include "UI_GmMacro.h"
#include "packet_header.h"
#include "RecvPacketMgr.h"
#include "CommonConfig.h"
#include "SpeedCheck.h"
#include "DecardiBattleManager.h"
#include "rnpacket.h"
#include "PacketProc.h"
#include "PacketSend.h"
#include "ControlLotto.h"
#include "ControlLetterSend.h"

extern float				g_fDSDistance;
extern CClrAlloc			*g_ClrAlloc;
extern DWORD				g_dwClientCountry;
extern DWORD				g_dwLangType;
extern CCapsyong			*g_pBodyList[];


extern BOOL g_bGlobalMatrix; ///���������� �� Ŭ���̾�Ʈ ���� ����.

extern int g_nMapCellWidth;
extern int g_nMapCellHeight;
extern int g_nMapCellWidthCount;
extern int g_nMapCellHeightCount;
extern list<CDecoObj *> g_listDecoObj[MAP_CELL_HEIGHT_COUNT][MAP_CELL_WIDTH_COUNT];


extern CChaAct		g_ChaActList[2][MAX_CHA_ACT_NUM];

extern CDecoObjSet	*g_pDecoObjSet;
extern int			g_EffectSound[];


//extern CChaAct	g_ChaBpdList[MAX_CHA_ACT_NUM];
//extern int g_ChaBpdIndex[ NUM_RACE*NUM_SEX ][ CHA_ACT_INDEX_NUM ];


// ����� ���� ��������
extern int	g_nMobRenNum;
extern int	g_nMobInNum;
extern int	g_nMobListNum;
extern int	g_nPlRenNum;
extern int	g_nPlInNum;
extern int	g_nPlListNum;
extern int	g_nItemListNum;
extern int	g_nPetRenNum;
extern int	g_nPetInNum;
extern int	g_nPetListNum;

extern BOOL g_bNewLetter;//������ �ִ°�
extern int	g_nServerIndex;		// ���� �ε��� ( ���� �ý��� )



// ���� ������ �Ǵ� Decoration Objects list
list<WORD> g_listRenderedDecoColor;
list<CDecoObj *> g_listRenderedDeco;
list<CDecoObj *> g_listAlphaDeco;
list<CDecoObj *> g_listLastDeco;
list<CDecoObj *> g_listFarDeco;

extern BOOL g_bDungeon;	// ����.
extern BOOL g_bNewTerrainDungeon;	//wan:2004-11 - Whitehorn Dungeon
extern BOOL	g_bFFullMode;
extern BOOL g_bAdmin;
extern BOOL g_bAdmin2;
// ���� �޽��� �÷���.
extern BOOL g_bDummyMsg;
extern BOOL g_bNewDungeon;
extern int	g_nCurWorldIdx;
extern int GetMagicDistance(int skill_level);
extern int GetSnifingRange(int skill_level);
// ���� Ư�� ������Ʈ.
extern CDecoObj	*g_pGuildGateClosed;				// ���� - Ư���� ���� ����.
extern CDecoObj *g_pGuildGate2Opened;
extern BOOL g_bPath;
extern BOOL g_bNc;
extern BOOL g_bGhost;
extern int g_MatrixSvr;
BOOL g_bAutomouse = FALSE;
BOOL g_bActivePackage = FALSE;	// ��Ű�� ���� ���� �÷��� ( �븸 )

extern BOOL				g_bNewTerrain;
extern CNKObjQuadNode*	g_pObjTree;

BOOL g_OutsideDoorOpen[8] = {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};
extern float g_OutsideDoorX[], g_OutsideDoorZ[];
// nate 2004 - 11 : ���Ϸ� ��ȣ�� ��ǥ
extern float g_fGuardTowerX[], g_fGuardTowerZ[];
// nate 2005-03-23 : Matrix - G.P.Stone �����Ҽ� �հ� ��ǥ����
extern float g_fGPStoneX[], g_fGPStoneZ[];
extern float g_fGPStone2009X1[], g_fGPStone2009Z1[], g_fGPStone2009X2[], g_fGPStone2009Z2[];
extern char* g_commOut;
extern int					g_MatrixSvr;


extern int		gMapWidth;
extern int		gMapHeight;
extern int		gMapExtention;

//�߰���ų Ŭ���̾�Ʈ ������
#define HELLCRYDELAY 3000
#define TORNADORUINDELAY 3000
#define AIRRAIDDELAY 3000
#define FISSIONDELAY 3000

// NetWork Message Log â�� ������ ���θ� ����
extern bool g_bWndNetMessage ;

// nate 2004 - 4 : CastleWar - ��ī���� ������ ��ȣž ��ġ
#define	DECWAR_LAND_ATT_COUNT	8 // �̸� �ٲٰ� �ϳ� �ø�.(������ �������� ���� ũ����Ż Ÿ���� ���� �߰�).(by ����) //DEC_TOWER
extern BOOL CheckCanNpcUpgradeItem( CItem *pItem ); // ��ȭ�� ������ ������������ üũ��. ///�Ź���ȭ�ý���
// 7��° ��ǥ �������� ����(����) 8��° ��ǥ�� ũ����Ż Ÿ��(����).(by ����) //DEC_TOWER
float g_fDecardi_Protect_Tower_Left_X[ DECWAR_LAND_ATT_COUNT ] = { 5800, 5900, 6070, 6090, 6050, 5860, 5920, 5955 };
float g_fDecardi_Protect_Tower_Bottom_Z[ DECWAR_LAND_ATT_COUNT ] = { 5700, 5670, 5690, 5810, 5900, 5910, 5790, 5800 };
float g_fDecardi_Protect_Tower_Right_X[ DECWAR_LAND_ATT_COUNT ] = { 5870, 5970, 6130, 6160, 6140, 5950, 6020, 5995 };
float g_fDecardi_Protect_Tower_Top_Z[ DECWAR_LAND_ATT_COUNT ] = { 5850, 5730, 5750, 5880, 5980, 5990, 5880, 5840 };

// ���� �� ��ǥ
float g_fDecardi_Wine_Door_Left_X = 6010;
float g_fDecardi_Wine_Door_Bottom_Z = 6730;
float g_fDecardi_Wine_Door_Right_X = 6050;
float g_fDecardi_Wine_Door_Top_Z = 6740;

// ������ : ��ȣž.
// nate 2004 - 11 : ��ȣž �Ӽ��� ���ۼ�
float guild_castle_top_left_x[] = {2880, 3480, 3880, 2480};
float guild_castle_top_left_z[] = {10480, 10480, 10080, 10080};
float guild_castle_top_right_x[] = {2920, 3520, 3920, 2520};
float guild_castle_top_right_z[] = {10520, 10520, 10120, 10120};

// �����
float guild_control_left_x[] = {7279,7480, 3595, 2672};
float guild_control_left_z[] = {11111, 11111, 10035, 10046};
float guild_control_right_x[] = {7304, 7503, 3615, 2697};
float guild_control_right_z[] = {11131, 11133, 10055, 10067};

float whitehorn_outsidedoor_left_x[] = {10105, 11745, 9965, 11475,
										10315, 11395, 10315, 11525
									   };
float whitehorn_outsidedoor_right_x[] = {10145, 11795, 10015, 11515,
										 10355, 11435, 10355, 11565
										};
float whitehorn_outsidedoor_top_z[] = {7135, 6935, 4875, 4695,
									   6745, 6755, 5065, 5075
									  };
float whitehorn_outsidedoor_bottom_z[] = {7095, 6895, 4835, 4645,
										  6695, 6705, 5025, 5035
										 };

float whitehorn_control_left_x[] = {9415,9415, 9515, 9515};
float whitehorn_control_left_z[] = {7685, 7895, 5685, 5965};
float whitehorn_control_right_x[] = {9435, 9435, 9535, 9535};
float whitehorn_control_right_z[] = {7705, 7915, 5705, 5985};

float crystal_tower_left_x = 10985;
float crystal_tower_right_x = 11005;
float crystal_tower_top_z = 5835;
float crystal_tower_bottom_z = 5805;

float whitehorn_castle_gate_left_x = 9735;
float whitehorn_castle_gate_right_x = 9765;
float whitehorn_castle_gate_top_z = 5845;
float whitehorn_castle_gate_bottom_z = 5805;


// by evilkiki 2009.07.29
const DWORD USE_FIREWORK_TIME = 3000;


extern void SendDecardiBattleReq();

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;              
static boost::char_separator<char> sep("\n", NULL, boost::drop_empty_tokens);

void PReadLine2(PFILE *fp, char *str)
{
	char ch;
	int read_byte;

	// ���๮�� �ǳʶ�.
	do
	{
		read_byte = pfread(&ch, 1, 1, fp);
	}
	while ((ch == '\n' || ch == '\r' || ch == '\t') && read_byte > 0);
	*(str++) = ch;

	// ���๮�ڱ��� ���� ����.
	while (ch != '\n' && ch != '\r' && ch != '\t' && read_byte > 0)
	{
		read_byte = pfread(&ch, 1, 1, fp);
		*(str++) = ch;
	}

	*(str-1) = '\0';
}

void ReadLine2(FILE *fp, char *str)
{
	char ch;
	int read_byte;

	// ���๮�� �ǳʶ�.
	do
	{
		read_byte = fread(&ch, 1, 1, fp);
	}
	while ((ch == '\n' || ch == '\r' || ch == '\t') && read_byte > 0);
	*(str++) = ch;

	// ���๮�ڱ��� ���� ����.
	while (ch != '\n' && ch != '\r' && ch != '\t' && read_byte > 0)
	{
		read_byte = fread(&ch, 1, 1, fp);
		*(str++) = ch;
	}

	*(str-1) = '\0';
}

CUIMgr::CUIMgr()
	: m_hWnd(NULL)
	, m_DeviceId(0)
	, m_wColor(0)
	, m_dwElapsedTime(0)
	, m_dwRbuttonElapsedTime(0)
	, m_nCurFloor(0)
	, m_bExch(FALSE)
	, m_cal_item_x(0)
	, m_cal_item_y(0)
	, m_MainTime(0)
	, m_BoxTime(0)
	, m_TextTime(0)
	, m_AngelTime(0)
	, m_iTextFFrameCnt(0)
	, m_iTextEFrameCnt(0)
	, m_ScreenWidth(0)
	, m_ScreenHeight(0)
	, m_iMainXpos(0)
	, m_iMainYpos(0)
	, m_iStartX(0)
	, m_iStartY(0)
	, m_iCnt(0)
	, m_bAngelSta(FALSE)
	, m_bAngelAniActive(FALSE)
	, m_bShowAngel(FALSE)
	, m_iCurMode(0)
	, m_timeSummonLock(0)
	, bControlKey(FALSE)
	, m_nNowPlayingEvent(0)
	, m_dwEventStartTime(0)
	, m_AutoPlay(NULL)
	, m_nServerIndex(0)
	, m_ThreadID(0)
	, m_hThread(NULL)
	, m_BoxFrameCnt(0)
	, m_AngelFrameCnt(0)	
{
	memset(m_oneSentence, 0, sizeof(m_oneSentence));
	memset(&m_Action, 0, sizeof(m_Action));
	memset(m_strExchPlayerName, 0, sizeof(m_strExchPlayerName));
	memset(m_strMsPlayerName, 0, sizeof(m_strMsPlayerName));
	memset(m_strProcessPlayerName, 0, sizeof(m_strProcessPlayerName));

	m_pLand = NULL;
	m_commIn[0] = NULL;
	m_commOut[0] = NULL;
	m_commInTmp[0] = NULL;
	m_pFrustum = NULL;
	m_bShowName = FALSE;
	m_nShowNameType = 1;
	m_ShowVitalId = -1;
	m_wPrevName = 0;
	m_pNkKeyboard = new CNkKeyboard;
	m_bMouseDown = FALSE;
	m_bNextAction = FALSE;
	m_bPickLock = FALSE; // pick �� ���� ���ÿ� �κ� ������ ������ �κ� ������ ������� ���� ������ �÷���. ///pick_bug
	m_pOpenDeco	= NULL;
	m_bAdjustingCamera = FALSE;
	m_pPetVitalFront = NULL;
	m_pVitalFront = NULL;
	m_pManaFront = NULL;
	m_pStamFront = NULL;
	m_pEpowerFront = NULL;
	m_pVitalBack = NULL;
	m_pVitalBack_E = NULL;
	m_Vital = 100;

	m_pCmd = new CCmd(this);

	m_bMsg = FALSE;
	m_bModal = FALSE;
	m_bAlt   = FALSE;
	m_nChangeWorldIdx = -1;
	m_nChangeLocalIdx = 0;			// �ʵ��� �����������.. �ʿ� ���� ������ �� ���� ����.
	m_lastMoveTime = timeGetTime();
	m_dwRClickDelay = timeGetTime();
	// ��ũ�� �˾������� ..
	m_pScrollBox = NULL;
	m_pDelivBox = NULL;
	m_pChSexBox = NULL;
	m_bIsScrollBox = FALSE;
	m_bIsDelivBox = FALSE;
	m_bIsChSexBox = FALSE;
	m_bIsChangeHair = FALSE;
	m_bIsWarTax     = FALSE;
	m_bIsTower		= FALSE;
	m_bIsPetShop	= FALSE;
	m_bIsPetKeep	= FALSE;
	m_bIsWarReq     = FALSE;
	m_bIsGuildWar   = FALSE;
	m_bIsMatList	= FALSE;
	m_bIsMatMakeRoom = FALSE;
	m_bIsMatBattle = FALSE;
	m_bIsMatDeath = FALSE;
	m_bIsMatSurvival = FALSE;
	m_bIsMatSurvivalMon = FALSE;
	m_bIsMatChat = FALSE;
	m_bIsTeleportItem = FALSE;
	m_bIsLowGuildMaster = FALSE;
	m_iQuickSlotNum = 0;
	m_iCurDelivState = 0;
	m_pChangeHair = NULL;
	m_pWarTax     = NULL;
	m_pTower	  = NULL;
	m_pPetShop		= NULL;
	m_pPetKeep		= NULL;
	m_pWarReq     = NULL;
	m_pGuildWar   = NULL;
	m_pMatList	  = NULL;
	m_pMatMakeRoom = NULL;
	m_pBattleUI = NULL;
	m_pSurvivalUI = NULL;
	m_pTeleportItem	= NULL;
	m_pGmMacro = NULL;
	m_pLowGuildMaster = NULL;
	// nate 2004 - 9 : GuildHunt
	m_pGuildHunt = NULL;
	m_pReservationWindow = NULL;
	m_bIsGuildHunt = FALSE;
	m_bIsReservationWindow = FALSE;
	m_byDoorOpen = 0;

	for(int i=0; i<MAX_PRESENT_BOX; i++)
		m_pPresentBox[i] = NULL;

	for( int i=0; i<MAX_ANGEL_CNT; i++)
		m_pAngel[i] = NULL;

	m_pPresentText = NULL;
	m_bShowPresentBox = FALSE;
	init_queue();
	m_bF11 = false;
//-------------------------------------
// ���� �˸� ���
	for(int j=0; j<MAX_LETTER_MSG_BOX; j++)
		m_pLetterMsgBox[j] = NULL;

	m_bShowLetterMsgBox = FALSE;
	m_LetterTime =0;
	m_LetterFrameCnt=0;
	m_iMove =0;
	isFirstNewLetter = TRUE;
//-------------------------------------
	m_nCastleDoorState = 1;
	m_bOnBattle = FALSE;
	m_pWarInfo = NULL;
	m_bWarInfo = TRUE;	
	m_whichShift = 0;
//=================================
	// nate 2004 - 4
	// CastleWar
	m_MasterGuild1[0] = '\0';
	m_MasterGuild2[0] = '\0';
	m_MasterGuild3[0] = '\0';
	m_MasterZone1 = -1;
	m_MasterZone2 = -1;
	m_MasterZone3 = -1;
	m_byEndDecardiCastleWar = 0;
	m_byOnBattleDecardi = 0;
	m_szDecardiGuildGamma = NULL;
	m_szDecardiGuildDelta = NULL;
//=================================
	m_SubGuild[0][0] = '\0';
	m_SubGuild[1][0] = '\0';
	m_SubGuild[2][0] = '\0';
	m_SubGuild[3][0] = '\0';
	//// ����� score..
	m_pBack_Score = NULL;
	m_pTextScoreA = NULL;
	m_pTextScoreB = NULL;
	m_pTextTeamNameA = NULL;
	m_pTextTeamNameB = NULL;
	m_bShowScore = FALSE;
	m_bOnTeamBattle = FALSE;
	m_bSummonLock=FALSE;
	m_bSubAttack=FALSE;
	m_SummonMobControl = FALSE;
	m_F1_Help = TRUE;
	m_QuickKeyUnlock = FALSE;
	m_bRMouseDown = FALSE;
	m_bTeleport = FALSE;
	m_bMultiAttack = FALSE;
	m_bMoveKit=FALSE;
	m_bParosKit = FALSE;
	m_bDmitron = FALSE;
	m_bMarboden = FALSE; // [2008/6/23 Theodoric] �������� �̵���ġ
	m_dwVk1KeyTime = 0;
	isFirstViewGuildMsg = FALSE;
	m_byQuest2Start = 0;	// nate 2004 - 4 : quest - ����Ʈ ������ üũ
	m_b_Attack = false;
	m_b_SecAttack = false;
	m_b_MovingForAttack = false;
	m_b_MotionForAttack = false;
	m_b_QuickAttack = false;
	m_bChakramAtt = FALSE;
	m_bChakram = FALSE;
	m_ChakramSlotNum = -1;
	m_bBookSpell= FALSE;
	m_bBookSpellAtt = FALSE;
	m_BookSlotNum = -1;
	m_bBossGateClosedRender = TRUE;	//wan:2004-12 : whitehorn dungeon - ������ ����Ʈ �÷��� TRUE:����,FALSE:����
	// nate 2005-03-10 - Matrix
	m_nWarpGateIndex = 0;
	m_pMatrixMark = NULL;
	CreateMatrixMark();

	for( int i = 0 ; i < 12 ; i ++ )
	{
		if( g_MatrixSvr == 1)
		{
			if( i < 9 )
			{
				m_nStoneState[i]  = 1;
				m_nStoneState2[i] = 1;
			}
			else
			{
				m_nStoneState[i]  = 0;
				m_nStoneState2[i] = 0;
			}
		}
		else
		{
			if( i < 4 )
			{
				m_nStoneState[i]  = 1;
				m_nStoneState2[i] = 1;
			}
			else
			{
				m_nStoneState[i]  = 0;
				m_nStoneState2[i] = 0;
			}
		}
	}

	for( int i=0; i<4; i++)
		m_nStoneState2[i] = 1;

	m_nClickTimeCheck = 0;	//mungmae-2005/04/11 : ��ĭ �޺� Ŭ�� Ÿ�� üũ
	m_bNextGoto = TRUE;
	m_nExchCharId = -1;	// nate 2005-06-07 : ��ȯ�� �ĺ�
	m_dwRevivalAccTime = 0;	 // mungmae 2005/06/23: ����콺 ����Ÿ�� ����

	for( int i=0; i<3; i++ )
		m_nGuildPoint[ i ] = 0;

	m_bRClickDown = 0; //mungmae-2005/07/04 : ���콺 ����
	m_bSendMessage = FALSE;
	m_byCheckHellDown = 1;	//  0 : Useing HellDown
	m_dwUseQuickItemTime = 0L;	// nate 2005-08-23 : ���� ��� ������ Ÿ��
	m_dwUseFireworkTick = 0L;
	for( int i = 0 ; i < QUICK_SLOT_NUM ; i ++ )
		m_bCanUsePower[ i ] = TRUE; // nate 2005-08-29 : ���� ����� �������� üũ
	// nate 2004 - 6 : ��ī���� ĳ���� ���� ��Ÿ �� ���� �ٴ� ����
	m_pNamPlane = NULL;	// �� ���� �ٴڿ���
	for( int i = 0 ; i < 2 ; i ++ )
		m_pSummonMob[i] = NULL;	// nate 2005-11-28 : ���̵�� ��ȯ��������
	dwDelayTime = 0L;

	m_dwUseQuickTick = 0;
	m_bWorldCupDash = FALSE;
	m_bWorldCupDashReady = TRUE;
	m_dwDashUseTime = 0;
	m_bOneTime = FALSE;

	m_bAutoHunt = FALSE;

	// [5/7/2008 �����] �±� ���� ���� �̺�Ʈ �Ҿƹ��� Ŭ�� üũ
	m_bPocketPapa_Click = FALSE;
	m_papaClickTime = 0.0f;

	m_GuildMarkList.clear();
	m_bIsThread = FALSE;
	m_phttpConnection = NULL;

	m_hWaitObject = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	m_pEvent_LegKnock_Appear = NULL; // ��ī�� ���� ���׳��� ����� �̺�Ʈ. ///Ʃ�丮�� �� �̰� �ʱ�ȭ �߰�.
	m_pEventScript = NULL; // �̺�Ʈ ��ũ��Ʈ ///Ʃ�丮�� �� �߰�

	m_AutoItemTakeDelayTime = 0;

	m_AutoPlay = NULL;

	m_pMatrixWarMsg = new CMatrixWarMessage;

	m_bPaymentLagrush = FALSE;

	m_pVitalBack_Center		= NULL;
	m_pVitalFront_Center	= NULL;

	m_edit_autopath = false;

	m_strGuildMarkURL = "http://mark.laghaim.com/lh_guild_mark/%d/%d_%d.bmp";
	LoadGuildMarkURL();
}

CUIMgr::~CUIMgr()
{
	thread_finish();
	CloseHandle(m_hWaitObject);

	DeleteRes();

	SAFE_DELETE( m_pNkKeyboard );
	SAFE_DELETE( m_pCmd );

	delete_queue_ptr();
	SAFE_DELETE( m_pWarInfo );
	SAFE_DELETE( m_pBack_Score );
	SAFE_DELETE( m_pTextScoreA );
	SAFE_DELETE( m_pTextScoreB );
	SAFE_DELETE( m_pTextTeamNameA );
	SAFE_DELETE( m_pTextTeamNameB );
	SAFE_DELETE_ARRAY( m_szDecardiGuildGamma );
	SAFE_DELETE_ARRAY( m_szDecardiGuildDelta );
	SAFE_DELETE( m_pMatrixMark );

	SAFE_DELETE( m_AutoPlay );

	SAFE_DELETE(m_pMatrixWarMsg);

	EraseAllList();

	ReleaseEventScene(); // �̺�Ʈ�� ����. ///�δ�1 �� �߰�

	SAFE_DELETE(m_pCmd);
}

BOOL CUIMgr::InitSocket()
{
	WORD      wVersionRequested;
	WSADATA   wsaData;

	wVersionRequested = MAKEWORD(1,1);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}

void CUIMgr::ChangeEnvironment()
{
	if (g_pNk2DFrame)
	{
		m_NameBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, 0, 0);
		m_NameBox.SetVisible(TRUE);

		SAFE_DELETE(m_pPetVitalFront);
		SAFE_DELETE(m_pVitalFront);
		SAFE_DELETE(m_pManaFront);
		SAFE_DELETE(m_pStamFront);
		SAFE_DELETE(m_pEpowerFront);
		SAFE_DELETE(m_pVitalBack);
		SAFE_DELETE(m_pVitalBack_E);
		SAFE_DELETE(m_pVitalBack_Center);
		SAFE_DELETE(m_pVitalFront_Center);

		g_pDisplay->CreateSurfaceFromBitmap(&m_pPetVitalFront, "interface/warinfo/p_vital_f.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalFront, "interface/warinfo/m_vital_f.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pManaFront, "interface/warinfo/m_mana_f.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pStamFront, "interface/warinfo/m_stam_f.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pEpowerFront, "interface/warinfo/m_epower_f.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalBack, "interface/warinfo/m_vital_b.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalBack_E, "interface/warinfo/m_vital_b_e.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalBack_Center, "interface/warinfo/m_vital_b_c.bmp");
		g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalFront_Center, "interface/warinfo/m_vital_f_c.bmp");

		m_pVitalBack_Center->SetColorKey(TRANS_COLOR);
		m_pVitalFront_Center->SetColorKey(TRANS_COLOR);

		init_queue();
	}

	m_bMsg = TRUE;

	CItemInfo *pItemInfo = NULL;
	LHItemInfoMap_it prItemInfo = m_iteminfo_map.begin();
	for ( ; prItemInfo != m_iteminfo_map.end(); prItemInfo++)
	{
		pItemInfo = (*prItemInfo).second;

		pItemInfo->m_TextOutBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, (int) 0, (int) 0, -1, -1, TRUE);
		pItemInfo->m_TextOutBox.SetVisible(TRUE);

		pItemInfo->m_TextOutBox_Active.Init(PLAYERNAME_FONTSIZE, NAME_ACTIVECOLOR, (int) 0, (int) 0, -1, -1, TRUE);
		pItemInfo->m_TextOutBox_Active.SetVisible(TRUE);

		pItemInfo->m_bActive = FALSE;

		if( GET_TYPE_REF(pItemInfo->m_Item) == ITYPE_SUB )
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName);
			pItemInfo->m_TextOutBox_Active.SetString(strName);
		}
		else if( GET_TYPE_REF(pItemInfo->m_Item) == ITYPE_ETC
				 && ( GET_SHAPE_REF(pItemInfo->m_Item) == IETC_RECOVERY
					  || GET_SHAPE_REF(pItemInfo->m_Item) == IETC_BUFF )
			   )
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName);
			pItemInfo->m_TextOutBox_Active.SetString(strName);
		}
		else if (pItemInfo->m_Item.m_PlusNum > 0)
		{
			char strName[50];

			sprintf(strName, "%s +%d", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum),
					pItemInfo->m_Item.m_PlusNum);
			pItemInfo->m_TextOutBox.SetString(strName, UPGRADE_ITEM_COLOR_REF);
			pItemInfo->m_TextOutBox_Active.SetString(strName, NAME_ACTIVECOLOR);
			//m_AltNameBox[m_DropItemAllCnt]->SetString(strName, UPGRADE_ITEM_COLOR_REF);
		}
		else if (pItemInfo->m_Item.m_Special)
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName, NAME_ACTIVECOLOR);
			pItemInfo->m_TextOutBox_Active.SetString(strName, NAME_ACTIVECOLOR);
		}
		else if (pItemInfo->m_Item.m_Special2 > 0)
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName, SPECIAL_ITEM_COLOR_REF);
			pItemInfo->m_TextOutBox_Active.SetString(strName, NAME_ACTIVECOLOR);
		}
		else
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName);
			pItemInfo->m_TextOutBox_Active.SetString(strName);
		}
	}

	// ����Ʋ �������̽� ���� �����̹� ��� ���������̽��� ��ε�.
	if (m_pBattleUI)
		m_pBattleUI->LoadRes();

	if (m_pSurvivalUI)
		m_pSurvivalUI->LoadRes();
}


void CUIMgr::Init(HWND hwnd, CLand *pLand)
{
	SetHwnd(hwnd);
	SetLandPtr(pLand);
	SetEnergyBar();

	if( CommonConfig::Instance()->GetLagrush() == true )
	{
		m_AutoPlay = new CAutoPlay_EX();
	}
}

void CUIMgr::SetEnergyBar()
{
	m_NameBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, 0, 0);
	m_NameBox.SetVisible(TRUE);

	SAFE_DELETE(m_pPetVitalFront);
	SAFE_DELETE(m_pVitalFront);
	SAFE_DELETE(m_pManaFront);
	SAFE_DELETE(m_pStamFront);
	SAFE_DELETE(m_pEpowerFront);
	SAFE_DELETE(m_pVitalBack);
	SAFE_DELETE(m_pVitalBack_E);
	SAFE_DELETE(m_pVitalBack_Center);
	SAFE_DELETE(m_pVitalFront_Center);

	g_pDisplay->CreateSurfaceFromBitmap(&m_pPetVitalFront, "interface/warinfo/p_vital_f.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalFront, "interface/warinfo/m_vital_f.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pManaFront, "interface/warinfo/m_mana_f.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pStamFront, "interface/warinfo/m_stam_f.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pEpowerFront, "interface/warinfo/m_epower_f.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalBack, "interface/warinfo/m_vital_b.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalBack_E, "interface/warinfo/m_vital_b_e.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalBack_Center, "interface/warinfo/m_vital_b_c.bmp");
	g_pDisplay->CreateSurfaceFromBitmap(&m_pVitalFront_Center, "interface/warinfo/m_vital_f_c.bmp");

	m_pVitalBack_Center->SetColorKey(TRANS_COLOR);
	m_pVitalFront_Center->SetColorKey(TRANS_COLOR);

	m_bMsg = TRUE;
}

void CUIMgr::DeleteRes()
{
	m_bMsg = FALSE;

	m_NameBox.DeleteRes();

	SAFE_DELETE(m_pScrollBox);
	SAFE_DELETE(m_pDelivBox);
	SAFE_DELETE(m_pChSexBox);
	SAFE_DELETE(m_pChangeHair);
	SAFE_DELETE(m_pWarTax);
	SAFE_DELETE(m_pTower);
	SAFE_DELETE(m_pPetShop);
	SAFE_DELETE(m_pPetKeep);
	SAFE_DELETE(m_pWarReq);
	SAFE_DELETE(m_pGuildWar);
	SAFE_DELETE(m_pMatList);
	SAFE_DELETE(m_pMatMakeRoom);
	SAFE_DELETE(m_pBattleUI);
	SAFE_DELETE(m_pSurvivalUI);
	SAFE_DELETE(m_pTeleportItem);
	SAFE_DELETE(m_pGmMacro);
	SAFE_DELETE(m_pLowGuildMaster);
	SAFE_DELETE( m_pGuildHunt );

	SAFE_DELETE(m_pWarInfo);

	SAFE_DELETE(m_pPetVitalFront);
	SAFE_DELETE(m_pVitalFront);
	SAFE_DELETE(m_pManaFront);
	SAFE_DELETE(m_pStamFront);
	SAFE_DELETE(m_pEpowerFront);
	SAFE_DELETE(m_pVitalBack);
	SAFE_DELETE(m_pVitalBack_E);
	SAFE_DELETE(m_pVitalBack_Center);
	SAFE_DELETE(m_pVitalFront_Center);

	m_bIsScrollBox = FALSE;
	m_bIsDelivBox = FALSE;
	m_bIsChSexBox = FALSE;
	m_bIsChangeHair = FALSE;
	m_bIsWarTax = FALSE;
	m_bIsTower = FALSE;
	m_bIsPetShop = FALSE;
	m_bIsPetKeep = FALSE;
	m_bIsWarReq = FALSE;
	m_bIsGuildWar = FALSE;
	m_bIsMatList = FALSE;
	m_bIsMatMakeRoom = FALSE;
	m_bIsMatSurvival = FALSE;
	m_bIsMatChat = FALSE;
	m_bIsMatSurvivalMon = FALSE;
	m_bIsTeleportItem = FALSE;

	m_bIsLowGuildMaster = FALSE;
	m_bIsGuildHunt = FALSE;

	DeleteAllPresent();
	DeleteLetterMsgBox();



	CNkCharacter *pCha;
	LHCharacterMap_it pr;
	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;
		pCha->m_pChatPopup->DeleteRes();
		pCha->m_pUserShopPopup->DeleteRes(); ///���λ���
	}
	if (g_pRoh)
	{
		g_pRoh->m_pChatPopup->DeleteRes();
		g_pRoh->m_pUserShopPopup->DeleteRes(); ///���λ���
	}
	CNkMob *pMob;
	LHMobMap_it prMob;
	for (prMob = m_mob_map.begin(); prMob != m_mob_map.end(); prMob++)
	{
		pMob = (*prMob).second;
		pMob->m_pMobChatPopup->DeleteRes();
	}

	CItemInfo *pItemInfo = NULL;
	LHItemInfoMap_it prItemInfo;

	prItemInfo = m_iteminfo_map.begin();
	for ( ; prItemInfo != m_iteminfo_map.end(); prItemInfo++)
	{
		pItemInfo = (*prItemInfo).second;

		pItemInfo->m_TextOutBox.DeleteRes();
		pItemInfo->m_TextOutBox_Active.DeleteRes();
	}

	DestroyScore();
}

static POINT ptOld = {0, 0};

//--------------------------------------------------------------------------
// Message
//--------------------------------------------------------------------------
// ���� ��� Winodw Message �� ó���ϴ� ���̴�.
// ����.. ����ȭ�� ������ ���������� �ʿ��� ���̴�.
int CUIMgr::Message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int mx, my;
	static short zDelta;
	static int startPosX, startPosZ;
	static DWORD dwLastTabTime = 0, dwLastWeaponSwapTime = 0; // ���� �ٲٱ� �����̿�.(by ����)
	static DWORD dwUseModeTime = 0;	// ���� ��� ���� �����̿�.
	static DWORD dwDashModeTime = 0;
	float ShortestDistance = 10000.0f;
	float ItemDistance = 1000.0f;
	const float limitDistance = 5000.0f;
	if (!m_bMsg)
		return 1;

	if( g_pNk2DFrame->IsProcLock() )
	{
		return 1;
	}

	if( pCMyApp->GetCurWorld() == WORLD_MATRIX || pCMyApp->GetCurWorld() == WORLD_MATRIX_2009 )
		m_pMatrixWarMsg->MsgProc();

	if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� ĵ�� ���δ�. ���⸦ ĵ���Կ��� ä���� �� �Ŵ�. ///�δ�1 �� �߰�
	{
		if( pCMyApp->m_pUIMgr->EventSceneMsgProc( g_pDisplay->GetHWnd(), uMsg, wParam, lParam) ) // �̰� TRUE�� �ٸ� �޼����� ���� �ʴ´�. ///Ʃ�丮��.
			return 0;
	}


	if( !g_MatrixSvr )
	{
		if( m_AutoPlay && m_AutoPlay->MsgProc( uMsg, wParam, lParam ) )
			return 0;
	}

	int i, res;
	char data[20];
	int mode;
	int cur_skill = g_pNk2DFrame->GetRSkill();

	HWND	hWnd;
	hWnd =  g_pDisplay->GetHWnd();

	if( timeGetTime() - m_dwDashUseTime > 3000 && m_bOneTime) // mungmae-2006/06/13 : ���ǵ�� ��� 3�ʰ� ������ FALSE
	{
		m_bWorldCupDash = FALSE;
		sprintf(m_commOut, "use_effect %d %d\n", 1, FALSE);
		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage(m_commOut);
		m_bOneTime = FALSE;
	}

	if( m_pGmMacro )
	{
		if( 0 != m_pGmMacro->MsgProc(hWnd, uMsg, wParam, lParam) )
			return 1;
	}

	if( g_pNk2DFrame->m_Popup )
	{
		return 0;
	}

	switch(uMsg)
	{
	case WM_MOUSEWHEEL:

//			if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� ĵ�� ���δ�. ///�δ�1 �� �߰�
//				return 0; ///Ʃ�丮��� ����

		zDelta = HIWORD(wParam);

		// zDelta�� ���� �����ΰ� ����ΰ��� �Ǵ��Ͽ� ���� �������� ȸ���ߴ°� �������� ȸ���ߴ°� Ȯ���Ѵ�.
		if (zDelta > 0)
			pCMyApp->ForwardCamDirection();
		else
			pCMyApp->BackwardCamDirection();

		return 0;

//======================================================
	// nate 2004 - 6
	// �ٸ��콺 ī�޶� ��ŷ
	case WM_MBUTTONDOWN:

//			if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� ĵ�� ���δ�. ///�δ�1 �� �߰�
//				return 0; ///Ʃ�丮��� ����

		mx = LOWORD (lParam);
		my = HIWORD (lParam);

		pCMyApp->StartRotateCamera(mx, my);
		return 1;
	case WM_MBUTTONUP:
//			if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� ĵ�� ���δ�. ///�δ�1 �� �߰�
//				return 0; ///Ʃ�丮��� ����
		pCMyApp->EndRotateCamera();
		return 1;
	case WM_MBUTTONDBLCLK:
//			if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� ĵ�� ���δ�. ///�δ�1 �� �߰�
//				return 0; ///Ʃ�丮��� ����
		pCMyApp->RotateCameraPI();
		return 1;
//======================================================
	case WM_LBUTTONDOWN:
		{

			mx = LOWORD (lParam);
			my = HIWORD (lParam);

			if (m_pScrollBox && m_bIsScrollBox )
			{
				res = m_pScrollBox->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res == 0)
				{
					m_bIsScrollBox = false;
					return 1;
				}
				else
					return 1;
			}

			if(m_pChSexBox)
			{
				res = m_pChSexBox->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res != 0)
					return 1;
				else if(res==0)
				{
					// �ڽ� �̿��� ������ Ŭ���� �Ȱ��
					if(m_pChSexBox)
					{
						delete m_pChSexBox;
						m_pChSexBox = NULL;
						m_bIsChSexBox = FALSE;
						return 1;
					}
				}
			}

			if (m_pDelivBox)
			{
				res = m_pDelivBox->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res != 0)
					return 1;

			}

			if(m_pChangeHair)
			{
				res = m_pChangeHair->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
				else if(res == 0)
				{
					if(m_pChangeHair)
					{
						delete m_pChangeHair;
						m_pChangeHair = NULL;
						m_bIsChangeHair = FALSE;
						return 1;
					}
				}
			}
			if(m_pWarTax)
			{
				res = m_pWarTax->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			if(m_pTower)
			{
				res = m_pTower->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			if(m_pPetShop)
			{
				res = m_pPetShop->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res ==1)
					return 1;
				else if(res == 2)
				{
					if(m_pPetShop)
					{
						SAFE_DELETE(m_pPetShop);
					}
					m_bIsPetShop = FALSE;
					return 1;
				}

			}
			if(m_pPetKeep)
			{
				res = m_pPetKeep->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			if(m_pWarReq)
			{
				res = m_pWarReq->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			if(m_pGuildWar)
			{
				res = m_pGuildWar->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			if(m_pMatList)
			{
				res = m_pMatList->MsgProc(hWnd, uMsg, wParam, lParam);
				if (res != 0) return 1;
			}
			if (m_pMatMakeRoom)
			{
				res = m_pMatMakeRoom->MsgProc(hWnd, uMsg, wParam, lParam);
				if (res != 0) return 1;
			}
			if (m_pBattleUI)
			{
				res = m_pBattleUI->MsgProc(hWnd, uMsg, wParam, lParam);
				if (res != 2) return 0;
			}
			if(m_pSurvivalUI)
			{
				res = m_pSurvivalUI->MsgProc(hWnd, uMsg, wParam, lParam);
				if (res != 2) return 1;
			}
			if(m_pTeleportItem)
			{
				res = m_pTeleportItem->MsgProc(hWnd, uMsg, wParam, lParam);

				if(res ==1)
					return 1;
				else if(res == 2)
				{
					g_pRoh->m_bQuickSlotLock[m_pTeleportItem->m_iQuickSlotNum] = FALSE;
					delete m_pTeleportItem;
					m_pTeleportItem = NULL;
					m_bIsTeleportItem = FALSE;
					return 1;
				}

			}
			if(m_pLowGuildMaster)
			{
				res = m_pLowGuildMaster->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}

			//=====================================================================================
			// nate 2004 - 8
			// GuildHunt
			if( m_pGuildHunt )
			{
				res = m_pGuildHunt->MsgProc( hWnd, uMsg, wParam, lParam );

				if( res == 1 )
					return 1;
				else if( res == 2 )
				{
					SAFE_DELETE( m_pGuildHunt );
					m_bIsGuildHunt = FALSE;
					return 1;
				}
				else if( res == 3 )
				{
					// ���� ������ ����
					if( g_pRoh->m_pstrGuildName )
					{
						m_bIsReservationWindow = TRUE;

						if( m_pReservationWindow )
							SAFE_DELETE( m_pReservationWindow );

						m_pReservationWindow = new CReservationWindow();
						m_pReservationWindow->LoadRes();
						m_pReservationWindow->SetReservInfo( m_pGuildHunt->GetCurrentPage()
															 , m_pGuildHunt->GetSelectGuildHuntIndex()
															 , m_pGuildHunt->GetGuildHuntDate()
															 , g_pRoh->m_pstrGuildName
															 , g_pRoh->m_pstrName );
					}

					SAFE_DELETE( m_pGuildHunt );
					m_bIsGuildHunt = FALSE;

					return 1;
				}
			}

			if( m_pReservationWindow )
			{
				res = m_pReservationWindow->MsgProc( hWnd, uMsg, wParam, lParam );

				if( res == 1 )
					return 1;
				else if( res == 2 )
				{
					// nate 2004 - 10
					m_bIsReservationWindow = FALSE;
					SAFE_DELETE( m_pReservationWindow );
					return 1;
				}
				else if( res == 3 )
				{
					m_pReservationWindow->SendQuestApplyMsg( 2 );	// GUILDHUNT_CLOSE : 2
					m_bIsReservationWindow = FALSE;
					SAFE_DELETE( m_pReservationWindow );
					return 1;
				}
			}


			{
				if( g_pNk2DFrame->GetUIWindow() && g_pNk2DFrame->GetUIWindow()->IsOpenWindow() )
				{
					if( g_pNk2DFrame->GetUIWindow()->IsMouseUpperWindow(mx, my) )
						return 1;
				}
			}
			if( g_SvrType == ST_ADULT_ONLY )
			{
				if( g_pNk2DFrame->GetTgaUIWindow() && g_pNk2DFrame->GetTgaUIWindow()->IsOpenWindow() )
				{
					if( g_pNk2DFrame->GetTgaUIWindow()->IsMouseUpperWindow(mx, my) )
						return 1;
				}
			}

			return MouseDown(mx, my, wParam, BUTTON_LEFT);
		}


	case WM_LBUTTONUP:

		mx = LOWORD (lParam);
		my = HIWORD (lParam);

		pCMyApp->SetSelTile(FALSE);
		ReleaseCapture();

		if(m_pScrollBox)
		{
			res = m_pScrollBox->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
			{
				// �������� ��� ������ �ּ���
				if( g_pRoh->IsEquiped() )
				{
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_LHSTRING1838), -1 );
					return 1;
				}

				strcpy(data, m_pScrollBox->m_pInBox->GetString());
				for(i=0; i<strlen(data); i++)
				{
					// ��Ʈ���� �˻��ؾ��Ѵ�.
				}
				char temp[100];
				strcpy(temp, "npc_init ");
				strcat(temp, data);
				strcat(temp, "\n");
				if( g_pTcpIp )
					g_pTcpIp->SendNetMessage(temp);
				m_bIsScrollBox = false;
				if(m_pScrollBox)
					SAFE_DELETE(m_pScrollBox);
				return 1;
			}
			else if(res ==2)
			{
				m_bIsScrollBox = false;
				if(m_pScrollBox)
					SAFE_DELETE(m_pScrollBox);
				return 1;
			}
			if(res != 0)
				return 1;
		}

		else if(m_pDelivBox)
		{
			res = m_pDelivBox->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
			{
				if(m_iCurDelivState == _DELIV_OPEN)
				{
					char temp[20];
					if (CheckCarnationExist())
					{
						g_pRoh->m_bExgLock = TRUE;
						strcpy(temp, "deliv_open\n");
						if( g_pTcpIp )
							g_pTcpIp->SendNetMessage(temp);
					}
					else
						CheckCarnation(_DELIV_FAIL);
				}
				else
				{
					m_bIsDelivBox = false;
					if(m_pDelivBox)
						SAFE_DELETE(m_pDelivBox);
				}
				return 1;
			}
			else if(res ==2)
			{
				m_bIsDelivBox = false;
				if(m_pDelivBox)
					SAFE_DELETE(m_pDelivBox);
				return 1;
			}
			if(res != 0)
				return 1;
		}
		else if(m_pChSexBox)
		{
			res = m_pChSexBox->MsgProc(hWnd, uMsg, wParam, lParam);

			char temp[20];
			if(res == 1)// "Ȯ��" �� �������
			{
				// ch_sex �� ������ ������.
				strcpy(temp, "ch_sex\n");
				if( g_pTcpIp )
					g_pTcpIp->SendNetMessage(temp);

				if(m_pChSexBox)
				{
					SAFE_DELETE(m_pChSexBox);
					m_bIsChSexBox = FALSE;
				}
				return 1;

			}
			else if( res == 2)
			{
				// "���" �� �������
				if(m_pChSexBox)
				{
					SAFE_DELETE(m_pChSexBox);
					m_bIsChSexBox = FALSE;
				}
				return 1;
			}
		}
		else if(m_pChangeHair)
		{
			res = m_pChangeHair->MsgProc(hWnd, uMsg, wParam, lParam);

			char temp[20];
			if(res ==1)
			{
				if(m_pChangeHair->m_iCurIcon  > 4)
					m_pChangeHair->m_iCurIcon = 9+m_pChangeHair->m_iCurIcon - 4;

				sprintf(temp, "ch_hair %d\n", m_pChangeHair->m_iCurIcon);
				if( g_pTcpIp )
					g_pTcpIp->SendNetMessage(temp);
				if (m_pChangeHair)
				{
					delete m_pChangeHair;
					m_pChangeHair = NULL;
				}
				m_bIsChangeHair = FALSE;
				return 1;
			}
			else if(res == 2)
			{
				if (m_pChangeHair)
				{
					delete m_pChangeHair;
					m_pChangeHair = NULL;
				}
				m_bIsChangeHair = FALSE;
				return 1;
			}

			else if(res == 4)
				return 1;
		}
		else if(m_pWarTax)
		{
			res = m_pWarTax->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
			{
			}
			else if(res == 2)
			{
				if(m_pWarTax)
				{
					delete m_pWarTax;
					m_pWarTax = NULL;
				}
				m_bIsWarTax = FALSE;
				return 1;
			}
		}
		else if(m_pTower)
		{
			res = m_pTower->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
			{
			}
			else if(res == 2)
			{
				if(m_pTower)
				{
					delete m_pTower;
					m_pTower = NULL;
				}
				m_bIsTower = FALSE;
				return 1;
			}
		}
		else if(m_pGuildWar)
		{
			res = m_pGuildWar->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res ==1)
			{
			}
			else if(res ==2)
			{
				if(m_pGuildWar)
				{
					delete m_pGuildWar;
					m_pGuildWar = NULL;
				}
				m_bIsGuildWar = FALSE;
				return 1;
			}
		}
		else if (m_pMatList)
		{
			res = m_pMatList->MsgProc(hWnd, uMsg, wParam, lParam);
			if (res == 1)
			{
			}
			else if (res == 2)
			{
				if (m_pMatList)
				{
					delete m_pMatList;
					m_pMatList = NULL;
				}
				m_bIsMatList = FALSE;
				return 1;
			}
		}
		else if (m_pMatMakeRoom)
		{
			res = m_pMatMakeRoom->MsgProc(hWnd, uMsg, wParam, lParam);
			if (res == 1)
			{
			}
			else if (res == 2)
			{
				if (m_pMatMakeRoom)
				{
					delete m_pMatMakeRoom;
					m_pMatMakeRoom = NULL;
				}
				m_bIsMatMakeRoom = FALSE;
				return 1;
			}
		}
		else if (m_pBattleUI)
		{
			res = m_pBattleUI->MsgProc(hWnd, uMsg, wParam, lParam);
			if (res == 1)
			{
			}
			else if (res == 2)
			{
				if (m_pBattleUI)
				{
					delete m_pBattleUI;
					m_pBattleUI = NULL;
				}
				m_bIsMatBattle = FALSE;
				m_bIsMatDeath = FALSE;
				return 1;
			}
			return 0;

		}
		else if (m_pSurvivalUI)
		{
			res = m_pSurvivalUI->MsgProc(hWnd, uMsg, wParam, lParam);
			if (res == 1)
			{
			}
			else if (res == 2)
			{
				if (m_pSurvivalUI)
				{
					delete m_pSurvivalUI;
					m_pSurvivalUI = NULL;
				}
				m_bIsMatSurvival = FALSE;
				m_bIsMatSurvivalMon = FALSE;
				m_bIsMatChat = FALSE;
				return 1;
			}
			return 0;

		}
		else if(m_pPetShop)
		{
			res = m_pPetShop->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
				return 1;
			else if(res == 2)
			{
				if(m_pPetShop)
				{
					SAFE_DELETE(m_pPetShop);
				}
				m_bIsPetShop = FALSE;
				return 1;
			}
		}
		else if(m_pPetKeep)
		{
			res = m_pPetKeep->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
			{
			}
			else if(res == 2)
			{
				if(m_pPetKeep)
				{
					delete m_pPetKeep;
					m_pPetKeep = NULL;
				}
				m_bIsPetKeep = FALSE;
				return 1;
			}
		}
		else if(m_pWarReq)
		{
			res = m_pWarReq->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
			{
			}
			else if(res == 2)
			{
				if(m_pWarReq)
				{
					delete m_pWarReq;
					m_pWarReq = NULL;
				}
				m_bIsWarReq = FALSE;
				return 1;
			}
		}
		else if(m_pTeleportItem)
		{
			res = m_pTeleportItem->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
				return 1;
			else if(res == 2)
			{
				g_pRoh->m_bQuickSlotLock[m_pTeleportItem->m_iQuickSlotNum] = FALSE;
				delete m_pTeleportItem;
				m_pTeleportItem = NULL;
				m_bIsTeleportItem = FALSE;
				return 1;
			}
		}
		else if(m_pLowGuildMaster)
		{
			res = m_pLowGuildMaster->MsgProc(hWnd, uMsg, wParam, lParam);

			if(res ==1)
				return 1;
			else if(res == 2)
			{
				if(m_pLowGuildMaster)
				{
					delete m_pLowGuildMaster;
					m_pLowGuildMaster = NULL;
				}
				m_bIsLowGuildMaster = FALSE;
				return 1;
			}
		}
		//=====================================================================================
		// nate 2004 - 8
		// GuildHunt
		else if( m_pGuildHunt )
		{
			res = m_pGuildHunt->MsgProc( hWnd, uMsg, wParam, lParam );

			if( res == 1 )
				return 1;
			else if( res == 2 )
			{
				SAFE_DELETE( m_pGuildHunt );
				m_bIsGuildHunt = FALSE;
				return 1;
			}
			else if( res == 3 )
			{
				if( g_pRoh->m_pstrGuildName )
				{
					m_bIsReservationWindow = TRUE;

					if( m_pReservationWindow )
						SAFE_DELETE( m_pReservationWindow );

					m_pReservationWindow = new CReservationWindow();
					m_pReservationWindow->LoadRes();
					m_pReservationWindow->SetReservInfo( m_pGuildHunt->GetCurrentPage()
														 , m_pGuildHunt->GetSelectGuildHuntIndex()
														 , m_pGuildHunt->GetGuildHuntDate()
														 , g_pRoh->m_pstrGuildName
														 , g_pRoh->m_pstrName );
				}

				SAFE_DELETE( m_pGuildHunt );
				m_bIsGuildHunt = FALSE;

				return 1;
			}
		}
		else if( m_pReservationWindow )
		{
			res = m_pReservationWindow->MsgProc( hWnd, uMsg, wParam, lParam );

			if( res == 1 )
				return 1;
			else if( res == 2 )
			{
				m_bIsReservationWindow = FALSE;
				SAFE_DELETE( m_pReservationWindow );
				return 1;
			}
			else if( res == 3 )
			{
				m_pReservationWindow->SendQuestApplyMsg( 2 );	// GUILDHUNT_CLOSE : 2
				m_bIsReservationWindow = FALSE;
				SAFE_DELETE( m_pReservationWindow );
				return 1;
			}
		}
		//=====================================================================================

		return 1;


	case WM_RBUTTONDOWN:
		{
			mx = LOWORD (lParam);
			my = HIWORD (lParam);

			if( pCMyApp->DrawCasting && m_bRClickDown == 2)
			{
				g_pRoh->HellDownFail( g_pRoh, NULL );
			}

			if( g_pRoh->m_Race == RACE_KAILIPTON
					&& g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_C_HELLDOWN
					&& timeGetTime() > m_dwRClickDelay + 1000)
			{
				m_bRClickDown = 1;
				m_bSendMessage = FALSE;
				m_dwRClickDelay = timeGetTime();
			}
			else
			{
				m_bRClickDown = 0;
			}

			// ���콺 ��Ŭ�� ������ ���� ó��..�κ�..
			int nCurrNum = g_pNk2DFrame->GetControlBottom()->GetCurQuickSlotNum();
			if (nCurrNum >= 0 && nCurrNum < QUICK_SLOT_NUM)
			{
				if( IsInvenLock() )
					return 1;

				UseQuickItem(nCurrNum);
				return 1;
			}

			if(m_bIsDelivBox)
			{
				m_pDelivBox->MsgProc(hWnd, uMsg, wParam, lParam);
				return 1;
			}
			else if(m_pWarTax)
			{
				res = m_pWarTax->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pTower)
			{
				res = m_pTower->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pPetShop)
			{
				res = m_pPetShop->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pPetKeep)
			{
				res = m_pPetKeep->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pWarReq)
			{
				res = m_pWarReq->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pGuildWar)
			{
				res = m_pGuildWar->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pMatList)
			{
				res = m_pMatList->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pMatMakeRoom)
			{
				res = m_pMatMakeRoom->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pBattleUI)
			{
				res = m_pBattleUI->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pSurvivalUI)
			{
				res = m_pSurvivalUI->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pTeleportItem)
			{
				res = m_pTeleportItem->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pLowGuildMaster)
			{
				res = m_pLowGuildMaster->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			//=====================================================================================
			// nate 2004 - 8
			// GuildHunt
			else if( m_pGuildHunt )
			{
				res = m_pGuildHunt->MsgProc( hWnd, uMsg, wParam, lParam );
				if( res != 0 )
					return 1;
			}
			else if( m_pReservationWindow )
			{
				res = m_pReservationWindow->MsgProc( hWnd, uMsg, wParam, lParam );
				if( res != 0 )
					return 1;
			}
		}
//=====================================================================================
		return MouseDown(LOWORD (lParam), HIWORD (lParam), wParam, BUTTON_RIGHT);

	case WM_RBUTTONUP:

		{
			mx = LOWORD (lParam);
			my = HIWORD (lParam);

			//mungmae-2005/07/04 ��ٿ�� ���콺 �� ����
			if( g_pRoh->m_Race == RACE_KAILIPTON && g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_C_HELLDOWN )
			{
				m_bRClickDown = 2;
				m_bSendMessage = FALSE;
				//		pCMyApp->DrawCasting = FALSE;
				pCMyApp->m_dPressTime = 0L;
				m_dwRClickDelay = timeGetTime();
			}
			else
				m_bRClickDown = 0;

			pCMyApp->EndRotateCamera();
			ReleaseCapture();					// ī�޶� ȸ�� �� ���콺ĸ�� ���� ���� by. Sol9 [2012.07.10]
			m_bRMouseDown = FALSE;  //1118 ��Ŭ�� ���� ����...
			//			if(g_pRoh->m_DoubleAttack)//1122
			//				g_pRoh->m_DoubleAttack=FALSE;
		}
		return 1;

	case WM_MOUSEMOVE:

		{
			mx = LOWORD (lParam);
			my = HIWORD (lParam);

			if ( MK_CONTROL & wParam )
				m_SummonMobControl = TRUE;
			else
				m_SummonMobControl = FALSE;

			IsInside_MouseMove_Itm_Namebox(mx, my);

			//if(m_bIsScrollBox){
			if(m_pScrollBox)
				m_pScrollBox->MsgProc(hWnd, uMsg, wParam, lParam);
			else if(m_pDelivBox)
				m_pDelivBox->MsgProc(hWnd, uMsg, wParam, lParam);
			else if(m_pChSexBox)
				m_pChSexBox->MsgProc(hWnd, uMsg, wParam, lParam);
			else if(m_pChangeHair)
				m_pChangeHair->MsgProc(hWnd, uMsg, wParam, lParam);
			else if(m_pWarTax)
			{
				res = m_pWarTax->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pTower)
			{
				res = m_pTower->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pPetShop)
			{
				res = m_pPetShop->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pPetKeep)
			{
				res = m_pPetKeep->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pWarReq)
			{
				res = m_pWarReq->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pGuildWar)
			{
				res = m_pGuildWar->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pMatList)
			{
				res = m_pMatList->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pMatMakeRoom)
			{
				res = m_pMatMakeRoom->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pBattleUI)
			{
				res = m_pBattleUI->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pSurvivalUI)
			{
				res = m_pSurvivalUI->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res!=0)
					return 1;
			}
			else if(m_pTeleportItem)
			{
				res = m_pTeleportItem->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			else if(m_pLowGuildMaster)
			{
				res = m_pLowGuildMaster->MsgProc(hWnd, uMsg, wParam, lParam);
				if(res !=0)
					return 1;
			}
			//=====================================================================================
			// nate 2004 - 8
			// GuildHunt
			else if( m_pGuildHunt )
			{
				res = m_pGuildHunt->MsgProc( hWnd, uMsg, wParam, lParam );
				if( res != 0 )
					return 1;
			}
			else if( m_pReservationWindow )
			{
				res = m_pReservationWindow->MsgProc( hWnd, uMsg, wParam, lParam );
				if( res != 0 )
					return 1;
			}
			//=====================================================================================

			{
				if( g_pNk2DFrame->GetUIWindow() && g_pNk2DFrame->GetUIWindow()->IsMouseUpperWindow( mx, my) )
					return 1;

			}
			if( g_SvrType == ST_ADULT_ONLY )
			{
				if( g_pNk2DFrame->GetTgaUIWindow() && g_pNk2DFrame->GetTgaUIWindow()->IsMouseUpperWindow( mx, my) )
					return 1;
			}

			m_bShowName = FALSE;
			m_ShowVitalId = -1;
			// ���� ���콺�� ��ġ�� ������Ʈ�� �ִ°� ���캻��.
			if ( (m_wColor = WhatColorOnPick(mx, my)) > 0)
			{
				// ���콺�� �÷��̾��� ���� �ִ����� Ȯ���ϰ� �ִٸ� �̸��� �����ش�.
				int target_idx = -1;
				int whichName = ShowName(target_idx);
				bControlKey = FALSE;
				static D3DVECTOR ptVec;
				switch (whichName)
				{
				case 1: // �÷��̾�
					{
						//=====================================================
						// nate 2004 - 4
						// CastleWar
						if( (m_bOnBattle
								&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
									 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN
									 || pCMyApp->GetCurWorld() == WORLD_FIELD
									 || IsMatrix()
								   ) ) ||
								(g_pNk2DFrame->IsPVPVisible() == TRUE) )
							//=====================================================
						{
							bControlKey = TRUE;
						}

						if( MK_CONTROL & wParam )
						{
							// ���ΰ� �̸� ���̰� �ϱ�
							//if( m_wColor != g_pRoh->m_wColorIdx )
							bControlKey = TRUE;
						}

						CNkCharacter* pCha = GetCharacterByColorKey( m_wColor );
						// ����... ���� ������ ���õ� ĳ���Ͱ� ħ������ ���õ� ��� ����� ���콺 �����͸� ���� �������..
						if(
							pCha != NULL &&
							g_pRoh->GetMyGuildData() != NULL &&
							g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCha->m_GuildIndex )  &&
							!(pCMyApp->GetCurWorld() == 4 &&
							  pCMyApp->IsInsideRect(pCha->m_wx, pCha->m_wz, 6800, 5450, 7250, 5000)) )
						{
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
						}
						else if(	pCha != NULL &&
									(pCMyApp->GetCurWorld() == WORLD_GUILD_WAR ||
									 pCMyApp->GetCurWorld() == WORLD_DMITRON_BATTLE) &&
									pCha->m_GuildIndex != g_pRoh->m_GuildIndex )
						{
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
						}
						else if( pCMyApp->GetCurWorld() == WORLD_FIELD &&
								 DecardiBattleManager::GetInstance()->IsStart() == true &&
								 DecardiBattleManager::GetInstance()->IsSameTeam(g_pRoh->m_nCharIndex, pCha->m_nCharIndex) == false )
						{
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
						}
						else if(m_bBookSpell)//1028
						{
							pCMyApp->m_pMouse->SetMouseType(M_MAGIC_BOOK);
						}
						else if(m_bChakram) // Lyul
						{
							pCMyApp->m_pMouse->SetMouseType(M_CHAKRAM);
						}
						


						if(bControlKey)
						{
							if(m_bBookSpell)
								pCMyApp->m_pMouse->SetMouseType(M_MAGIC_BOOK);
							else if(m_bChakram) // Lyul
								pCMyApp->m_pMouse->SetMouseType(M_CHAKRAM);
							else if (g_pRoh->m_Wearing[WEARING_WEAPON])
							{
								/////////1002
								if (GET_SHAPE(g_pRoh->m_Wearing[WEARING_WEAPON]) == IWEAPON_GUN)
									pCMyApp->m_pMouse->SetMouseType(M_ATTACT_GUN);
								else
									pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
							}
							else
								pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
						}
						m_nShowNameType = 1;

					}
					break;
				case 2: // ����
					if(m_bBookSpell)
						pCMyApp->m_pMouse->SetMouseType(M_MAGIC_BOOK);
					else if(m_bChakram) //Lyul
						pCMyApp->m_pMouse->SetMouseType(M_CHAKRAM);
					else if (g_pRoh->m_Wearing[WEARING_WEAPON])
					{
						if (GET_SHAPE(g_pRoh->m_Wearing[WEARING_WEAPON]) == IWEAPON_GUN)
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT_GUN);
						else
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
					}
					else
					{
						pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
					}
					m_nShowNameType = 2;
					m_ShowVitalId = target_idx;
					break;
				case 3: // NPC
					pCMyApp->m_pMouse->SetMouseType(M_TALK);
					m_nShowNameType = 3;
					break;
				case 4: // ������
					pCMyApp->m_pMouse->SetMouseType(M_HOLD);
					m_nShowNameType = 4;
					break;
				case 5: // �ֿϵ���
					pCMyApp->m_pMouse->SetMouseType(M_NORMAL);
					m_nShowNameType = 5;
					break;
				case 6: ///�������� NPC
					if( (GetKeyState(VK_RSHIFT) & 0x80) ) // �̰� ������ ����Ʈ�� �����ϵ���...
						pCMyApp->m_pMouse->SetMouseType(M_TALK);
					else
						pCMyApp->m_pMouse->SetMouseType(M_NORMAL);

					m_nShowNameType = 3;
					break;
				case 7: // ���Ʈ�� �̵�����Ʈ
					pCMyApp->m_pMouse->SetMouseType(M_DOOR);
					m_nShowNameType = 7;
					break;
				default:
					// �̵�����Ʈ �Ǵ� �� ���⼭..
					if (m_pLand->PickPoint(ptVec, mx, my) == TRUE)
					{
						int result = IsPortal(ptVec);
						switch( result )
						{
						case 1:
							pCMyApp->m_pMouse->SetMouseType(M_DOOR);
							return 1;
						case 2:
							pCMyApp->m_pMouse->SetMouseType(M_HOLD);
							return 1;
						}
					}
					else
					{
						pCMyApp->m_pMouse->SetMouseType(M_NORMAL);

					}
					break;
				}
			}
			else
			{
				if(m_bBookSpell)
					pCMyApp->m_pMouse->SetMouseType(M_MAGIC_BOOK);
				else if(m_bChakram) // Lyul
					pCMyApp->m_pMouse->SetMouseType(M_CHAKRAM);
				else if( g_bGhost )
					pCMyApp->m_pMouse->SetMouseType(M_GHOST);
				else

					pCMyApp->m_pMouse->SetMouseType(M_NORMAL);

			}

		}
		return 1;

	case WM_TIMER:
		{
			if (wParam == 6 && pCMyApp->m_bPlaying)
			{
				//	HWND hwnd = FindWindow("TSub_f", "");

				RECT rect;

				HWND hwnd = FindWindow("tooltips_class32", "1");
				if(hwnd)
				{
					GetWindowRect(hwnd,&rect);
					if((rect.right-rect.left==301)&&(rect.bottom-rect.top==369))
						g_bAutomouse = TRUE;
				}

				if(!hwnd)
					g_bAutomouse = FALSE;
			}
		}
		break;

	case WM_KEYUP:
		{
			switch( (int) wParam)
			{
			case VK_CONTROL:
				// ��Ʈ�� Ű�� �������� ������ �����Ѱ� Ȯ��.
				if (m_bShowName)
				{
					if (m_nShowNameType == 1)
						pCMyApp->m_pMouse->SetMouseType(M_NORMAL);
				}
				break;

			case VK_SNAPSHOT:
				if (wParam)
					//				 	if(wParam != VK_COMMA)
					Save_Screen_Shot(hWnd);
				break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7' :
			case '8' :
			case '9' :
			case '0' :
			case VK_OEM_MINUS :		// '-'
			case VK_OEM_PLUS :		// '+'
				{
					int index;
					if (wParam >= '1' && wParam <= '9')							// 1, 2, 3, 4, 5, 6, 7, 8, 9
						index = wParam - '1';
					else if (wParam == '0')				// 0
						index = 9;
					else if (wParam == VK_OEM_MINUS)	// -
						index = 10;
					else if (wParam == VK_OEM_PLUS)			// =
						index = 11;

					if( g_pNk2DFrame->GetControlBottom() && g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable() )
						return 1;
					if( IsInvenLock() )
						return 1;

					m_bCanUsePower[index] = TRUE;
					break;
				}
			}
		}
		break;

	case WM_KEYDOWN:
		if( !m_bWorldCupDash && timeGetTime() > dwDashModeTime + 13000)
		{
			m_bWorldCupDashReady = TRUE;
			dwDashModeTime = timeGetTime();
		}
		// ������ �� ���� ó��
		if( g_pRoh->GetMotionState()==CHA_SOCIAL && g_pRoh->GetActNum() >= 153 && g_pRoh->GetActNum() <= 158 )
		{
			if( (int)wParam == VK_SPACE )
			{
				if( g_pRoh->Get_m_CurFrame() >= g_ChaBpdList[g_ChaBpdIndex[g_pRoh->m_Race][g_pRoh->GetActNum()]].m_pBiped->m_AnimCount - 20 ) // ������ �� �����ӿ� ������ ������
				{
					if( g_pRoh->GetActNum() == 153 ) // ������ �� �غ��� �ٸ�����
					{
						g_pRoh->m_byBurningStep = 0; // ���� ����� ������ȯ 4ȸ �ݺ��� ���ؼ� �� �༮�� �ʱ�ȭ���ش�.
						g_pRoh->SetMotionState( CHA_SOCIAL, 154 );
					}
					else if( g_pRoh->GetActNum() == 154 ) // ������ �� 1�� ��Ʈ ���� ���б�
					{
						if(	g_pRoh->m_byBurningStep == 4 ) // 4���� ° �������� ���� �������...
						{
							g_pRoh->m_byBurningStep = 0; // Ȥ�� �𸣴� �ʱ�ȭ.
							g_pRoh->SetMotionState( CHA_SOCIAL, 156 );
						}
						else
							g_pRoh->SetMotionState( CHA_SOCIAL, 155 );
					}
					else if( g_pRoh->GetActNum() == 155 ) // ������ �� 1�� ��Ʈ ����
					{
						if( g_pTcpIp )
						{
							sprintf(m_commOut, "rotate c %d %f\n", g_pRoh->m_nCharIndex, g_pRoh->m_toDir+g_PI_DIV_2 ); // 90�� �ʹ�.
							g_pTcpIp->SendNetMessage( m_commOut );
						}

						g_pRoh->SetMotionState( CHA_SOCIAL, 154 ); // �ٽ� ����� ������.
						++g_pRoh->m_byBurningStep;
					}
					else if( g_pRoh->GetActNum() == 156 ) // ������ �� 2�� ��Ʈ �ڼ�ġ��
						g_pRoh->SetMotionState( CHA_SOCIAL, 157 );
					else if( g_pRoh->GetActNum() == 157 ) // ������ �� 2�� ��Ʈ ������ ����
						g_pRoh->SetMotionState( CHA_SOCIAL, 158 );

					// ���⼭ �Ҽ� ��Ʈ ���� ��Ŷ���� ��������Ѵ�.
					if( g_pTcpIp )
					{
						sprintf(m_commOut, "social %d\n", g_pRoh->GetActNum() );
						g_pTcpIp->SendNetMessage( m_commOut );
					}
				}
				else // Ÿ�̹� Ʋ������ ĵ��
				{
					g_pRoh->SetMotionState( CHA_STAND );
					if( g_pTcpIp ) // ��ž ��Ŷ�� ������ �ٸ� ȭ�鿡���� �����ش�.
					{
						sprintf( m_commOut, "stop %.0f %.0f %.0f %.0f\n", g_pRoh->m_wx, g_pRoh->m_wz,
								 g_pRoh->m_wy, (g_pRoh->m_toDir) * 10000 );
						g_pTcpIp->SendNetMessage(m_commOut);
					}
				}

				return 1; // ������ �߿� �����̽� ������ ���� ����.
			}
		}

		if(m_pGuildWar)
		{
			res = m_pGuildWar->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}

		if(m_pWarTax)
		{
			m_pWarTax->MsgProc(hWnd, uMsg, wParam, lParam);
			return 1;
		}

		if (m_pMatMakeRoom)
		{
			res = m_pMatMakeRoom->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}

		if (m_pBattleUI)
		{
			res = m_pBattleUI->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}

		if (m_pSurvivalUI)
		{
			res = m_pSurvivalUI->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}

		if (m_pMatList)
		{
			res = m_pMatList->MsgProc(hWnd, uMsg, wParam, lParam);
			if (res == 2)
			{
				if (m_pMatList)
				{
					delete m_pMatList;
					m_pMatList = NULL;
				}
				m_bIsMatList = FALSE;
			}
			if(res !=0 )
				return 1;
		}

		switch((int)wParam)
		{
		case VK_UP:
			pCMyApp->ForwardCamDirection();
			return 1;

		case VK_DOWN:
			pCMyApp->BackwardCamDirection();
			return 1;

		case VK_LEFT:
			return 1;

		case VK_RIGHT:
			return 1;

		case VK_BACK: // for.. tw/cn        backspace
			if(m_bIsScrollBox)
			{
				m_pScrollBox->MsgProc(hWnd, uMsg, wParam, lParam);
				return 1;
			}
			return 1;

		case VK_RETURN:
			{
				// ��� ��Ʋ�߿� ��Ŀ��?
				g_pNk2DFrame->SetFocus();			// ������ �ʿ��ұ�? ��..
			}
			return 1;

		case VK_F1:
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return 1;

			if(m_F1_Help) //1030
				g_pNk2DFrame->ToggleHelpWindow();
			else if(m_QuickKeyUnlock)
			{
				m_F1_Help=TRUE;
				m_QuickKeyUnlock=FALSE;
			}

			return 1;

		case VK_F2:
			{	
			}
			break;

		case VK_F9:

			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return 1;

			g_pNk2DFrame->ToggleTopWindow();
			ToggleWarInfo();
			return 1;

		case VK_F11:
			m_bF11 ? m_bF11 = FALSE : m_bF11 = TRUE;
			if(m_bShowPresentBox && m_bF11)
			{
				DeleteAllPresent();
				clear_queue();

			}
			if(m_bF11)
				// IDS_UIMGR_GIFTBOX_OFF : �̺�Ʈâ �ɼ��� �������ϴ�.
				g_pNk2DFrame->GetControlBottom()->AddStrQlist((char*)G_STRING(IDS_UIMGR_GIFTBOX_OFF), -1);
			else
				// IDS_UIMGR_GIFTBOX_ON : �̺�Ʈâ �ɼ��� �������ϴ�.
				g_pNk2DFrame->GetControlBottom()->AddStrQlist((char*)G_STRING(IDS_UIMGR_GIFTBOX_ON), -1);

			m_bShowPresentBox = FALSE;

			return 1;

		case VK_F12:
			pCMyApp->m_nShowRohEnerge ++;
			if (pCMyApp->m_nShowRohEnerge > 6)
			{
				pCMyApp->m_nShowRohEnerge = -1;
			}
			break;

		case VK_DIVIDE :
			if (m_bAdjustingCamera == FALSE)
			{
				m_bAdjustingCamera = FixCameraPos();
			}
			return 1;

		case VK_CONTROL:
			// ��Ʈ�� Ű�� �������� ������ �����Ѱ� Ȯ��.
			if (m_bShowName)
			{
				if (m_nShowNameType == 1)
				{
					if (g_pRoh->m_Wearing[WEARING_WEAPON])
					{
						if (GET_SHAPE(g_pRoh->m_Wearing[WEARING_WEAPON]) == IWEAPON_GUN)
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT_GUN);
						else
							pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
					}
					else
					{
						pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
					}
					//pCMyApp->m_pMouse->SetMouseType(M_ATTACT);
				}
			}

			break;

		case VK_SHIFT:
			if ((lParam >> 16) == 42)   // ���� ����Ʈ
			{
				m_whichShift= 0;
			}
			else if ((lParam >> 16) == 54)     // ������ ����Ʈ
			{
				m_whichShift= 1;
			}

			break;
			
		case VK_INSERT :
		case VK_HOME :
		case VK_PRIOR :
		case VK_DELETE :
		case VK_END :
		case VK_NEXT :
			if (pCMyApp->m_pMyPet)
			{
				switch (wParam)
				{
				case VK_INSERT :
					mode = MYPET_MODE_COMBAT;
					break;
				case VK_HOME :
					mode = MYPET_MODE_FOLLOW;
					break;
				case VK_PRIOR :
					mode = MYPET_MODE_PICKUP;
					break;
				case VK_DELETE :
					mode = MYPET_MODE_WIMPY;
					break;
				case VK_END :
					mode = MYPET_MODE_SUPP;
					break;
				case VK_NEXT :
					mode = MYPET_MODE_RANGECOMBAT;
					break;
				}
				g_MyPetStatus.SetMode(mode);

				if (g_pTcpIp && timeGetTime() > dwUseModeTime + 1000 )
				{
					sprintf(m_commOut, "p_mode %d\n", mode);
					g_pTcpIp->SendNetMessage(m_commOut);
					dwUseModeTime = timeGetTime();
				}
				g_MyPetStatus.m_bUseMacroMode = FALSE; // �ٸ� ���� ����� �� ��ũ�� ��带 ����.(���� ��ũ�ΰ� ������ �Ŷ�� �� ���� �ٽ� TRUE�� ����������Ѵ�.)
			}
			return 1;

		case '1':
// [4/21/2009 D.K ] : ������ ���� ������ ���� ����.
// 				if (!IsVk1Pressed())
// 					return 1;
			if (g_bAutomouse)
				return 1;
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7' :
		case '8' :
		case '9' :
		case '0' :
		case VK_OEM_MINUS :		// '-'
		case VK_OEM_PLUS :		// '+'
			{

				// [6/7/2007 Theodoric] ������ ����� ����.
				if( !IsQuickSlotUsed() )
					break;

				int index = 0;
				if (wParam >= '1' && wParam <= '9')							// 1, 2, 3, 4, 5, 6, 7, 8, 9
					index = wParam - '1';
				else if (wParam == '0')				// 0
					index = 9;
				else if (wParam == VK_OEM_MINUS)	// -
					index = 10;
				else if (wParam == VK_OEM_PLUS)			// =
					index = 11;

				//if( !m_bCanUsePower[ wParam - ((wParam < VK_NUMPAD1)?'1':VK_NUMPAD1) ] )
				//	break;
				if( !m_bCanUsePower[index] )
					break;

				// nate 2005-08-29 : Ű�� ���� ��븦 �����Ͽ� �ڵ� Ű�Է� ����
				//m_bCanUsePower[ wParam - ((wParam < VK_NUMPAD1)?'1':VK_NUMPAD1) ] = FALSE;
				m_bCanUsePower[index] = FALSE;

				if(!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable())
				{
					//					if (!g_bAutomouse)
					UseQuickItem(index);
				}
				return 1;
			}
			break;


		case 219: // VK_OPEN_BRACKET // ���� ��� ���.
			if (pCMyApp->m_pMyPet)
			{
				if( g_MyPetStatus.m_Class ) // �⺻ ������ ��������. (�̰� ����Ű�δ� ���� üũ�� ���Ծ ����Ű�� ���뿡�� �����ִ� ���װ� �־���. 07-07-12 ���� ����.)
				{
					g_MyPetStatus.SetMode(MYPET_MODE_GUARD);
					if (g_pTcpIp && timeGetTime() > dwUseModeTime + 1000 )
					{
						sprintf(m_commOut, "p_mode %d\n", MYPET_MODE_GUARD);
						g_pTcpIp->SendNetMessage(m_commOut);
						dwUseModeTime = timeGetTime();
					}

					g_MyPetStatus.m_bUseMacroMode = FALSE; // �ٸ� ���� ����� �� ��ũ�� ��带 ����.(���� ��ũ�ΰ� ������ �Ŷ�� �� ���� �ٽ� TRUE�� ����������Ѵ�.)
				}
				else
				{
					//-- IDS_ITCAN_EVOLPET : ��ȭ�� ���븸 �����մϴ�.
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_ITCAN_EVOLPET), TYPE_NOR_OK, 1 );
				}
			}

			return 1;

		case 221: // VK_CLOSE_BRACKET // ���� ��ũ�� ���.
			if( pCMyApp->m_pMyPet && g_pNk2DFrame && g_pNk2DFrame->GetLShiftMenu() && g_pNk2DFrame->GetLShiftMenu()->m_pControlMacro )
			{
				if( g_MyPetStatus.m_Class ) // �⺻ ������ ��������. (�̰� ����Ű�δ� ���� üũ�� ���Ծ ����Ű�� ���뿡�� �����ִ� ���װ� �־���. 07-07-12 ���� ����.)
				{
					if (g_pTcpIp && timeGetTime() > dwUseModeTime + 1000 )
					{
						g_pNk2DFrame->ShowLShiftMenu();
						g_pNk2DFrame->GetLShiftMenu()->m_bMacroEditing = TRUE; // ��ũ�� ���� ���� LShiftMenu�� �����ش�.

						//						g_pNk2DFrame->GetLShiftMenu()->m_pControlMacro->StartMacroMode();

						dwUseModeTime = timeGetTime();
					}
				}
				else
				{
					//-- IDS_ITCAN_EVOLPET : ��ȭ�� ���븸 �����մϴ�.
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_ITCAN_EVOLPET), TYPE_NOR_OK, 1 );
				}
			}
			return 1;


		default:
			break;
		}

	case WM_SYSKEYDOWN :
		switch((int)wParam)
		{
		case VK_MENU:
			m_bAlt = TRUE;
			//GetAllDropItemInfo();
			return 1;
		}
		break;

	case WM_SYSCHAR:
// /*       // 06-09-07 �̺κ� 2005 06 �������� Ǯ���ִٰ� 2005 10�� �������� �ּ����� ���Ƶξ�����.
		// �̰� ������ ä���� ALT_����Ű �������� ������ ����� �ȵǼ� �ٽ� ǰ.(Ȥ�� ���� ������ �������� �ٸ� ������� ���ĺ���.)
		// ( ����ũ������ ���� ���԰� �ϴ°� ������ ���������� �𸣰ڴ�...����...�׷��� ������ UseQuick ���ῡ�� �ѹ��� ���Ƴ���. ) by ����

		switch((int) wParam)
		{
		case '1':
			{
				if (!IsVk1Pressed())
					return 1;
				if (g_bAutomouse)
					return 1;
			}
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7' :
		case '8' :
		case '9' :
		case '0' :
		case VK_OEM_MINUS :		// '-'
		case VK_OEM_PLUS :		// '+'
//					if (!g_bAutomouse)

			int index = 0;
			if (wParam >= '1' && wParam <= '9')							// 1, 2, 3, 4, 5, 6, 7, 8, 9
				index = wParam - '1';
			else if (wParam == '0')				// 0
				index = 9;
			else if (wParam == VK_OEM_MINUS)	// -
				index = 10;
			else if (wParam == VK_OEM_PLUS)			// =
				index = 11;

			UseQuickItem(index);
			return 1;
		}
		break;

	case WM_SYSKEYUP :
		switch((int)wParam)
		{
		case VK_MENU:
			m_bAlt = FALSE;
			//DeleteDropItemInfo();
			return 1;
		}
		break;
// */ // ���� �ּ� Ǯ���� ������� �ּ��Ǿ��־���.
	/*
			case WM_SYSKEYUP :
				switch((int)wParam)
				{
				case VK_MENU:
					m_bAlt = FALSE;
					return 1;
				}
				break;
	*/
	case WM_CHAR:
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_COMPOSITION:
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_CHAR:
	case WM_IME_NOTIFY:
		if( pCMyApp->IsSoccerZone() && m_bWorldCupDashReady )	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
		{
			switch((int)wParam)
			{
			case 'w':
				if (pCMyApp->m_bFastMove && g_bAdmin2)
					pCMyApp->GoForward();
				return 1;
			case 's':
				if (pCMyApp->m_bFastMove && g_bAdmin2)
					pCMyApp->GoBackward();
				return 1;
			case 'd':
				m_bOneTime = TRUE;
				m_bWorldCupDash = TRUE;
				m_bWorldCupDashReady = FALSE;
				m_dwDashUseTime = timeGetTime();
				return 1;
			}
			return 1;
		}

		if(m_pGuildWar)
		{
			res = m_pGuildWar->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}
		if(m_pMatMakeRoom)
		{
			res = m_pMatMakeRoom->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}

		if(m_pBattleUI)
		{
			res = m_pBattleUI->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}

		if(m_pSurvivalUI)
		{
			res = m_pSurvivalUI->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}
		if(m_pMatList)
		{
			res = m_pMatList->MsgProc(hWnd, uMsg, wParam, lParam);
			if(res !=0)
				return 1;
		}
		if(m_bIsScrollBox && m_pScrollBox)
		{
			m_pScrollBox->MsgProc(hWnd, uMsg, wParam, lParam);
			return 1;
		}
		if(m_pWarTax)
		{
			m_pWarTax->MsgProc(hWnd, uMsg, wParam, lParam);
			return 1;
		}
//			if(g_pNk2DFrame->GetGamble()->m_bGambleStart)//0121
//				return 1;

		// �����Է��� ����Ű �νľȵǰ� ó��...(07-07-13 ����)
		if( g_pNk2DFrame->IsAutoMouseVisible() && g_pNk2DFrame->GetAutoMouse()->m_pTextIn->GetEnable() )
			return false;

		if( g_pNk2DFrame->m_Popup != NULL
				&& (g_pNk2DFrame->m_Popup->pMsg_Popup.m_InputLine.GetEnable()
					|| g_pNk2DFrame->m_Popup->pMsg_Popup.m_InputValue1.GetEnable()
					|| g_pNk2DFrame->m_Popup->pMsg_Popup.m_InputValue2.GetEnable()
					|| g_pNk2DFrame->m_Popup->pMsg_Popup.m_InputValue3.GetEnable()))
			return false;

		if( !IsCheckKeyUsed() )
			return false;

		switch((int)wParam)
		{
		case 'f':
		case 'F':

			{
				int cm = g_pRoh->GetMotionState();
				if( !(cm==0 || cm==1 || cm==2 || cm== 4 || cm==5) )
					break;
			}

			if( g_pRoh->m_HideStatus == HIDE_HIDDEN	|| g_pRoh->m_HideStatus == HIDE_HIDING) 	// �޸� �ẹ�� ���� üũ
				break;

			if( g_pRoh->GetMotionState() >= CHA_STAND && g_pRoh->GetMotionState() <= CHA_ATTACK) //  [12/19/2008 ppmmjj83] �⺻������ ������ ��Ƕ��� �ڵ����Ⱑ �ʵǵ���
				AutoItemTake( 150.0f );  // [4/12/2007 Theodoric] ������ �ڵ� ����
			return 1;

		case 'w':
			if (pCMyApp->m_bFastMove && g_bAdmin2)
				pCMyApp->GoForward();

			return 1;
		case 's':
			if (pCMyApp->m_bFastMove && g_bAdmin2)
				pCMyApp->GoBackward();
			return 1;
		case 'a':
			if(!pCMyApp->IsSoccerZone())
				pCMyApp->RotateLeft();
			return 1;

		case 'd':
			if(!pCMyApp->IsSoccerZone())
				pCMyApp->RotateRight();
			return 1;

		case 'Q':
		case 'q':
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return 1;
			if (g_pNk2DFrame->IsLShiftVisible())
				g_pNk2DFrame->SetShowLShiftFlag(FALSE);
			else
				ShowLShiftMenu();
			//AddPet(-1, g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_dir, 100,
			//	576, 577, 578, 579, 580, 581);
			return 1;
		case '[': // Room�� �����Ŀ��� RoomList�� ��Ÿ����
			////// ����� �ӽ� �׽�Ʈ ///////////////////////////////////////////////
			//if (g_bAdmin2)
			//{
			//	SendMessage(hWnd, WM_LBUTTONDOWN, 0, MAKELPARAM(400, 268));
			//	SendMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(400, 268));
			//}
			////////////////////////////////////////////////////////////////////////////
			return 1;

		case ']':
			// �÷�Ƽ�� �׽�Ʈ ����
			return 0;		// 2004 modify

		case 'x':
		case 'X':
			/// CanSwapWeapon()�� ���� by.Sol9 [2012.05.09] /////////////
			//if( !g_pRoh->m_bSwapWeapon )	//mungmae-2006/06/21 �������� �߿� ���� �ٲٱ� �ȵǰ� ����.
			//	return 1;
			//////////////////////////////////////////////////////////////////////////
			if ( !g_pRoh->CanSwapWeapon() )		// ���� ��ü�� ������ �������� üũ by.Sol9 [2012.05.09]
				return 1;
			// ����ٲٱ� 2�� ������ ����. ( by ���� )
			if (g_pRoh && timeGetTime() - dwLastWeaponSwapTime > 2000  )
			{
				g_pRoh->SwapWeapon();
				dwLastWeaponSwapTime = timeGetTime();
			}
			break;
		case 'z':
		case 'Z':
			if( g_dwClientCountry == CTRY_JPN )
			{
				if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_FINALBOSS  )
				{
					return 1;
				}
				if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
					return 1;
				if (g_pNk2DFrame->IsPVPVisible() == TRUE)
					return 1;
				if( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) &&
						(!Check_All_RealtimeBox()) &&
						(g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) )
					g_pNk2DFrame->ToggleInterfaceWindow(SOCIAL);
			}
			break;
		case '`':
			if( g_dwClientCountry != CTRY_JPN )
			{
				if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
					return 1;
				if (g_pNk2DFrame->IsPVPVisible() == TRUE)
					return 1;
				if( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) &&
						(!Check_All_RealtimeBox()) &&
						(g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) )
					g_pNk2DFrame->ToggleInterfaceWindow(SOCIAL);
			}
			break;
		case 'j':
		case 'J':
			{
				if(pCMyApp->IsSoccerZone())
					return 1;
				if (g_pNk2DFrame->IsPVPVisible() == TRUE)
					return 1;
				if( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) &&
						(!Check_All_RealtimeBox()) &&
						(g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) )
				{
					if( CommonConfig::Instance()->GetFriendSystem() == true )
					{
						g_pNk2DFrame->ToggleFriend();
					}
				}
			}
			break;
		case VK_TAB:
			if (timeGetTime() - dwLastTabTime > 500)
			{
				dwLastTabTime = timeGetTime();

				if (!(g_pRoh->IsDead()) && g_pRoh->GetMotionState() != CHA_SOCIAL
						&& !g_pNk2DFrame->IsUserShopVisible() // ���λ����� ���������� ��ȭ��� ���ٲ�. ///���λ���
						&& g_pRoh->IsShown())
				{
					g_pRoh->ToggleCombat();
					g_pRoh->ResetMotionState();
					if (g_pTcpIp)
					{
						sprintf(m_commOut, "combat %d\n", g_pRoh->GetCombat());
						g_pTcpIp->SendNetMessage(m_commOut);
					}
				}
			}
			return 1;

		case '/':
			/*
			{
				static int hour = 0;
				hour++;
				if (hour >= 30)
					hour = 0;
				pCMyApp->ChangeHour(hour);
			}
			*/
			return 1;

			return 1;

		default:
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// [6/7/2007 Theodoric] ���� �Է� ����ó��... �Ѥ�;;

bool CUIMgr::IsQuickSlotUsed()
{
	{

		if( g_pNk2DFrame->GetUIWindow()->IsOpenWindow( WINDOW_GUILD_CREATE) )
		{
			// ��� â����
			CGuildCreate* pGuildCreateWindow = (CGuildCreate*)g_pNk2DFrame->GetUIWindow()->GetWindow( WINDOW_GUILD_CREATE);

			if( pGuildCreateWindow->m_GuildName.GetEnable() )
				return false;
		}

		if( g_pNk2DFrame->GetUIWindow()->IsOpenWindow( WINDOW_GUILD_BATTLE_INVASION) )
		{
			CBattleInvasionAttack* pBIA = (CBattleInvasionAttack*)g_pNk2DFrame->GetUIWindow()->GetWindow( WINDOW_GUILD_BATTLE_INVASION);

			if( pBIA->IsTextBoxFocus() )
				return false;
		}

		if( g_pNk2DFrame->IsVisiblePremiumExchange() )
			return false;

		if ( g_pNk2DFrame->GetUIWindow()->IsOpenWindow( WINDOW_DMITRON_BATTLE_TAX ) )
			return false;
	}

	// �����Է��� ������ ����Ű �νľȵǰ� ó��...(05-10-29 ����)
	if( g_pNk2DFrame->IsAutoMouseVisible() && g_pNk2DFrame->GetAutoMouse()->m_pTextIn->GetEnable() )
		return false;

	// �Է±�� �˾��� ���������� ������ �ȴ������� ó��....(06-10-11 ����)
	if( g_pNk2DFrame->IsPopUpTyping() )
		return false;

	// ���λ��� ��Ʈ �Է½õ� ������ �Է¾ȵǵ��� ...(05-10-29 ����) ///���λ���
	if( g_pNk2DFrame->IsUserShopVisible() && g_pNk2DFrame->GetControlUserShop()->m_ShopMentText.GetEnable() ) // ��Ʈ �Է����̸�...
		return false;

	// ���λ����˻���  �Է½õ� ������ �Է¾ȵǵ��� ...(06-12-08 ����) ///���λ���
	if( g_pNk2DFrame->IsUserShopSearchVisible() && g_pNk2DFrame->GetUserShopSearch()->m_SearchNameInput.GetEnable() )
		return false;

	// ���� ��ũ�� ��忡�� ���� �Է��߿� ������ �Ƚ�������.
	if( g_pNk2DFrame->GetLShiftMenu()->m_pControlMacro && g_pNk2DFrame->GetLShiftMenu()->m_pControlMacro->m_bNowInput )
		return false;

	// �� ���� �˻��� �Է½õ� ������ �Է¾ȵǵ��� ...(07-09-03 ����) ///�굵��Ȯ��
	if( g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet()->m_SearchInput.GetEnable() ) // �Է����̸�...
		return false;

	return true;
}
/////MouseDown������ ������ ���� �Ű��
#define MAX_TARGET_MOB	10
#define MAX_TARGET_CHA	10
CNkMob* g_pTargetMob[MAX_TARGET_MOB];
CNkCharacter* g_pTargetCha[MAX_TARGET_CHA];

//--------------------------------------------------------------------------
// MouseDown
//--------------------------------------------------------------------------
// 2004.11.20
// Lyul / Remodule
// ���콺�� Ŭ���Ǹ� �´�.

// ���� �и��ߴ�
// ������ ���� ó�� ��ƾ�� ��� ���� �Ǿ���.


int CUIMgr::MouseDown(int mx, int my, WPARAM wParam, int which_button)
{
	static D3DVECTOR ptVec;
	D3DVECTOR	vMouse;
	static DWORD lastTeleportTime = timeGetTime();
	static DWORD lastFissionTime = timeGetTime();

	//�߰���ų Ŭ���̾�Ʈ ������ üũ
	static DWORD lastHellCryTime = timeGetTime();
	static DWORD lastAirRaidTime = timeGetTime();
	static DWORD lastTornadoRuinTime = timeGetTime();

	list<CDecoObj *>::iterator prDeco;
	CDecoObj *pDecoObj;

	if( g_pNk2DFrame->IsUserShopVisible() ) // ���λ��� �߿� �̵� �Ұ�ó��. ///���λ���
		return 1;

//	if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� �̵��� �ȵǰ�... ///�δ�1
//		return 1; ///Ʃ�丮�� �� ���ƺ� ó������� ���� �ٲ۴�.

	if(!pCMyApp->CanClick())
	{
		//1118 1120
		if(which_button==BUTTON_LEFT)
			return 1;
		else if(!g_pNk2DFrame->GetControlBottom()->SelectedRotate())
			return 1;
	}

	//mungmae-2005/07/15 ��ٿ� ������ ���콺 �������¿��� ���� ��ư ����
	if( m_bRClickDown == 1
			&& pCMyApp->DrawCasting
			&& which_button==BUTTON_LEFT)
		return 0;
	if(pCMyApp->m_bEquipLock==1)//������� ��.1009
		return 1;
	if(pCMyApp->m_bRingLock==1)//���� ��. 0407
		return 1;

	// �ɾ� �ְų� �Ӹ� ������� => �Ͼ�� ���ؼ�.
	if (g_pRoh->GetActNum() == 68 || g_pRoh->GetActNum() == 69)
	{
		g_pRoh->SetMotionState(CHA_SOCIAL, 70);
		if (g_pTcpIp)
		{
			strcpy(m_commOut, "social 70\n");
			g_pTcpIp->SendNetMessage(m_commOut);
		}
		return 1;
	}
	else if (g_pRoh->GetActNum() == 88)
	{
		g_pRoh->SetMotionState(CHA_SOCIAL, 89);
		if (g_pTcpIp)
		{
			strcpy(m_commOut, "social 89\n");
			g_pTcpIp->SendNetMessage(m_commOut);
		}
		return 1;
	}
	else if( g_pRoh->GetActNum() >= 153 && g_pRoh->GetActNum() <= 158 ) // ������ �� �� ĵ�� ó��
	{
		g_pRoh->SetMotionState( CHA_STAND );
		if( g_pTcpIp ) // ��ž ��Ŷ�� ������ �ٸ� ȭ�鿡���� �����ش�.
		{
			sprintf( m_commOut, "stop %.0f %.0f %.0f %.0f\n", g_pRoh->m_wx, g_pRoh->m_wz,
					 g_pRoh->m_wy, (g_pRoh->m_toDir) * 10000 );
			g_pTcpIp->SendNetMessage(m_commOut);
		}
		return 1;
	}

	// ī�޶� ȸ���� ���� ��.
	if (which_button == BUTTON_RIGHT)
	{
		m_bChakramAtt = FALSE;
		m_bChakram = FALSE;
		m_bBookSpellAtt = FALSE;
		m_bBookSpell = FALSE;
		// ������ ���콺 ��ư ����� ȸ������ �Ǿ� �ִ°�?
		if (g_pNk2DFrame->GetControlBottom()->SelectedRotate())
			pCMyApp->StartRotateCamera(mx, my);
	}

	SetCapture(m_hWnd);
	/////2003 0925 ������¶�� ���� ���ϰ� �ϱ�.
	//------------------------------------------------------------------------
	// ��ų ��� �� ����
	//------------------------------------------------------------------------
	int bClickProcess = 0;
	// nate 2004 - 5
	// �� ���� �ۿ��� �����ϴ� ���� ����
	// �� ���� ������ ������ ������ ���� ���� ��û���� ��������
	if( pCMyApp->IsInsideMap( g_pRoh->m_wx, g_pRoh->m_wz ) )
		bClickProcess = CmdClick(which_button, wParam, mx, my);

	// �������̸�... Ŭ�� ����� �����Ѵ�. -> �� �ѹ� �� �ߴ�.
	if (m_b_Attack)
		return 1;

	//  ������ �� ���ų� ������ �ʴ� ���¶�� return 1
	if (g_pRoh->IsCantMove() || !(g_pRoh->IsShown()))
		return 1;

	if ( !(pCMyApp->GetHeroSwimming())
			&& (m_wColor = WhatColorOnPick(mx, my)) > 0 )
	{
		// ���� ����ƮŰ�� ���� ���콺 ��ư �̺�Ʈ.
		if (which_button == BUTTON_LEFT
				&& (GetKeyState(VK_SHIFT) & 0x80))
		{
			if (m_whichShift == 1)
				if (CmdRShift())
					return 1;
		}


		// ������ �ִ� ���� ������ϱ�.. �̺�Ʈ�� Ȯ���Ѵ�.
		if (which_button == BUTTON_LEFT)
		{
			if (!pCMyApp->IsBeforeGoWorld())
			{
				if (m_pLand->PickPoint(ptVec, mx, my) == TRUE && !g_pNk2DFrame->m_Popup ) // �˾� �������� ������Ʈ Ŭ���ȵǰ� ����( 06-12-07 ���� )
				{
					// ���콺�� ���� �Ϻκ��� �����.
					// not in case for using transfer gate
					int nVal, idx;
					if( ( nVal=IsChangeWorld(ptVec) ) && !pCMyApp->m_bBeforeGoWorld )
					{
						// ���� �̵� �׽�Ʈ
						if (nVal == 1)
						{
							PrepareChangeWorld(FALSE, m_nChangeWorldIdx, m_nChangeLocalIdx);
						}
						return 1;
					}

					// ��ī�� �������� �۵��ϴ� �ڵ��̴�. // ��ī�� �������� �۵��ϴ� �ڵ��̴�.
					if( pCMyApp->GetCurWorld() == WORLD_DUNGEON1) ///�δ�1
					{
						idx = 0;
						if ( (idx = CanTransFloor(WORLD_DUNGEON1)) > 0)
							TransFloor(WORLD_DUNGEON1, idx);
					}

					// ����Ʈ�������� Ư���� �ۿ�Ǵ� �ڵ��̴�.
					if( g_bDungeon
							&& pCMyApp->GetCurWorld() == WORLD_DUNGEON2)
					{
						// 2�� ����Ʈ��.
						idx = 0;
						if ( (idx = CanTransFloor(WORLD_DUNGEON2)) > 0)
							TransFloor(WORLD_DUNGEON2, idx);
					}
					///////////////////////////////////////////////////////////////////////////
					// ������ : �̿���
					// ������ : 05-03-21
					// �������� : ����콺 �Ʒ���(��Ʈ����)�� ��� ������ �������� ���� ����Ʈ ó��.
					if( g_MatrixSvr == 1 ) // ���� ����콺 �Ʒ����� ������ �ѱ��� ����.
					{
						for( prDeco = g_listRenderedDeco.begin() ; prDeco != g_listRenderedDeco.end() ; prDeco++ )
						{
							pDecoObj = *prDeco;

							if( pDecoObj->m_wColorIdx == m_wColor )
							{
								if( DistPlToPlAbs(pDecoObj->m_wx, pDecoObj->m_wz, g_pRoh->m_wx, g_pRoh->m_wz ) < 200 ) // �ʹ� �ָ��� ������ ����.
								{
									if( pDecoObj->m_nLoloId == 157 ) // PK������ ��� ������ ����.
									{
										// ������ �ٷ� ����������.
										if (g_pTcpIp)
										{
											m_bNextGoto = FALSE;
											g_pTcpIp->SendNetMessage( "mat_jump 3\n" );
										}
										return 1;
									}
									else if( pDecoObj->m_nLoloId == 190 )
									{
										if(g_pTcpIp)
										{
											m_bNextGoto = false;
											g_pTcpIp->SendNetMessage( "mat_jump 13\n" );
										}
										return 1;
									}
									else if( pDecoObj->m_nLoloId == 191 )
									{
										if(g_pTcpIp)
										{
											m_bNextGoto = false;
											g_pNk2DFrame->CloseAllWindow();
											g_pTcpIp->SendNetMessage( "mat_jump 12\n" );
										}
										return 1;
									}

									///���������� �ÿ� ��Ʈ���� ���� ����Ʈ �̵���� ����.
									if( pDecoObj->m_nLoloId == 129 || pDecoObj->m_nLoloId == 134 ) // ���� ����Ʈ��...
									{
										g_pNk2DFrame->ShowInterfaceWindow( true, GATE, 1010 ); // ����콺 ���� ���� â. �Ҵ� ��ȣ�� ���Ƿ� ũ��
										return 1;
									}
								}
							}
						}
					}
					else if( g_MatrixSvr == 2 )
					{
						for( prDeco = g_listRenderedDeco.begin() ; prDeco != g_listRenderedDeco.end() ; prDeco++ )
						{
							pDecoObj = *prDeco;

							if( pDecoObj->m_wColorIdx == m_wColor )
							{
								if( DistPlToPlAbs(pDecoObj->m_wx, pDecoObj->m_wz, g_pRoh->m_wx, g_pRoh->m_wz ) < 200 ) // �ʹ� �ָ��� ������ ����.
								{
									switch( pDecoObj->m_nLoloId )
									{
									case 211: // PK�� �̵� ����Ʈ ������ ���Ƿ� �̵�
										if (g_pTcpIp)
										{
											m_bNextGoto = FALSE;
											g_pTcpIp->SendNetMessage( "mat_jump 3\n" );
										}
										return 1;

									case 210:
									case 214:
										g_pNk2DFrame->ShowInterfaceWindow( true, GATE, 1011 );
										return 1;
									}
								}

							}

						}

					}
					///////////////////////////////////////////////////////////////////////////
					// nate 2004 - 10
					// GuildHunt
					// ���Ϸп����� �����ϴ� �ڵ��̴�.
					if( !g_bDungeon
							&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
								 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN
								 || pCMyApp->GetCurWorld() == WORLD_DMITRON
								 || pCMyApp->GetCurWorld() == WORLD_DMITRON_BATTLE) )
					{
						// list<CDecoObj *>::iterator prDeco;
						// CDecoObj *pDecoObj; // ���ʿ����� ������ �Լ� �ʹ����� �Ű���.(by ����)
						for (prDeco = g_listRenderedDeco.begin(); prDeco != g_listRenderedDeco.end(); prDeco++)
						{
							pDecoObj = *prDeco;

							if (pDecoObj->m_wColorIdx == m_wColor)
							{
								if (DistPlToPlAbs(pDecoObj->m_wx, pDecoObj->m_wz, g_pRoh->m_wx, g_pRoh->m_wz) < 100)
								{
									if( pCMyApp->GetCurWorld() == WORLD_GUILD )
									{
										if (pDecoObj->m_nLoloId == 240)
										{
											//����Ʋ
											if (g_dwClientCountry == CTRY_KOR
													|| g_dwClientCountry == CTRY_TH
													|| g_dwClientCountry == CTRY_ENG
													|| g_dwClientCountry == CTRY_TWN
													|| g_dwClientCountry == CTRY_DEU
													|| g_dwClientCountry == CTRY_DENG)
												if (g_pTcpIp)
													g_pTcpIp->SendNetMessage("gzone 0\n");
											return 1;
										}
										else if (pDecoObj->m_nLoloId == 241)
										{
											if (g_dwClientCountry == CTRY_KOR
													|| g_dwClientCountry == CTRY_TH
													|| g_dwClientCountry == CTRY_ENG
													|| g_dwClientCountry == CTRY_TWN
													|| g_dwClientCountry == CTRY_DEU
													|| g_dwClientCountry == CTRY_DENG)
												if (g_pTcpIp)
													g_pTcpIp->SendNetMessage("gzone 1\n");
											return 1;
										}
										//===========================================
										// nate 2004 - 10
										// GuildHunt
										// ���� ����Ʈ ����
										if( pDecoObj->m_nLoloId == 355 )
										{
											if( g_pTcpIp )
											{
												if( pCMyApp->IsGuildHuntArea( pDecoObj->m_wx, pDecoObj->m_wz ) )
													g_pTcpIp->SendNetMessage( "gh out\n" );
												else
													g_pTcpIp->SendNetMessage( "gh in\n" );
											}
											return 1;
										}
										//===========================================
									}
									else if( pCMyApp->GetCurWorld() == WORLD_WHITEHORN )
									{
										if( pDecoObj->m_nLoloId == 240 )
										{
											if( g_pTcpIp )
											{
												if( pCMyApp->IsGuildHuntArea( pDecoObj->m_wx, pDecoObj->m_wz ) )
													g_pTcpIp->SendNetMessage( "gh out\n" );
												else
													g_pTcpIp->SendNetMessage( "gh in\n" );
											}
											return 1;
										}
									}
									else if( pCMyApp->GetCurWorld() == WORLD_DMITRON ||
											 pCMyApp->GetCurWorld() == WORLD_DMITRON_BATTLE)
									{

										if( pDecoObj->m_nLoloId == 384 )
										{
											int nSubType = CDmitronZone::SearchPortal(pDecoObj->m_wx, pDecoObj->m_wz);

											if( g_pTcpIp && nSubType >= 0 && nSubType < 5 )
											{
												sprintf( m_commOut, "occp bt trans %d\n", nSubType );
												g_pTcpIp->SendNetMessage( m_commOut );

												CControlGate* pGate = (CControlGate*)g_pNk2DFrame->GetInterface(GATE);
												pGate->SetSubType( nSubType );
											}
											else if(nSubType == 5)
											{
												if(pCMyApp->IsAcropolis())	// IDS_MOVE_HOME : ������ �̵��մϴ�
													g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_MOVE_HOME),TYPE_NOR_OKCANCLE, 15);	// 15:POPUP_GATE
												else	// IDS_MOVE_ACROPOLICE : ����Ʈ���� ����ִ� ����� ����� �̵��մϴ�
													g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_MOVE_ACROPOLICE),TYPE_NOR_OKCANCLE, 15);	// 15:POPUP_GATE
												((CControlGate*)g_pNk2DFrame->GetInterface(GATE))->m_byPopupType = 2;	// ����� ����
												return 1;
											}
										}
									}
									else if( pCMyApp->GetCurWorld() == WORLD_DISPOSAL )
									{
									}
								}
							}// end for
						}
					}// end of if ���Ϸ�
				}// end of Landpick
			}// end of goworld
		}// end of left
	} // end of if pick

	/////2003 ��ȭ �Ǿ����� �������� ���ϰ� �ϱ�.
	if(g_pRoh->m_CancelState)
	{
		if( g_pRoh->m_ChaCondition==CONDITION_STONY ||
				g_pRoh->m_ChaCondition==CONDITION_ENTANGLE )
			return 1;
	}
	// �̵�
	if (which_button == BUTTON_LEFT)
	{
		if( CPacketControl::SendEnabled() == FALSE )
			return 1;

		if (! bClickProcess
				&& !(MK_SHIFT & wParam))
		{
			// ���콺�� ���� ������ �˾Ƴ��� �÷��̾��� ������ ���Ѵ�.
			DWORD curTime = timeGetTime();
			if (curTime >= m_lastMoveTime + 300 && g_pRoh->IsShown())
			{
				//------------------------------------------------------------------
				// ���콺�� �����ٸ�
				if (m_pLand->PickPoint(ptVec, mx, my) == TRUE && !g_pNk2DFrame->m_Popup )
				{
					if (g_bPath||m_bOnBattle) // �����̶�� �����ȴ�.
					{
						// ��ġ�� �������ش�. �� Ÿ���� ����� �����.
						int x, z;
						float fx, fz;
						fx = ptVec.x;			// ����ǥ ����.
						fz = ptVec.z;
						x = (int) (ptVec.x / 10);		// ��ǥ ����.
						z = (int) (ptVec.z / 10);
						ptVec.x = (x * 10) + 5.0f;
						ptVec.z = (z * 10) + 5.0f;

						if ( (g_pRoh->m_wx == ptVec.x)
								&& (g_pRoh->m_wz == ptVec.z) )
						{
							g_pRoh->m_toDir = (float) atan2((fz-ptVec.z),(fx-ptVec.x));
							int dY = (int) g_pRoh->m_wy;
							int dir = (int) (g_pRoh->m_toDir*10000);

							sprintf(m_commOut, "place %d %d %d %d %d\n", (int) ptVec.x, (int) ptVec.z, dY, dir, 0);
							if( g_pTcpIp )
							{
								g_pTcpIp->SendNetMessage(m_commOut);
							}

							return 1;
						}
						else
						{
							pCMyApp->MoveHeroT(ptVec.x, ptVec.z);
						}
					}
					else
					{
						pCMyApp->MoveHero(ptVec.x, ptVec.z);
					}

					m_bMouseDown = TRUE;
				}
				m_lastMoveTime = curTime;
			}
		}
		return 1;
	}
	return 1;
}

void CUIMgr::ShowRShiftMenu(CNkCharacter *pCha)
{
	if( !pCha )
		return;
	g_pNk2DFrame->ShowRShiftMenu(pCha);
}

int CUIMgr::CmdRShift()
{
	CNkCharacter *pCha = NULL;
	if( pCha = GetCharacterByColorKey( m_wColor ) )
	{
		if( pCha->m_UserShopLevel )
		{
			sprintf( m_commOut, "u_shop open c %d\n", pCha->m_nCharIndex );
			if( g_pTcpIp )
				g_pTcpIp->SendNetMessage( m_commOut );
		}
		else
			ShowRShiftMenu(pCha);

		return 1;
	}


	CUserShopNpc *pUserShopNpc = NULL;

	if( pUserShopNpc = GetUserShopNpcByColorKey(m_wColor) )
	{
		sprintf( m_commOut, "u_shop open n %d\n", pUserShopNpc->m_MasterIndex );
		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage( m_commOut );
	}

	if (pCMyApp->m_pMyPet)
	{
		if (pCMyApp->m_pMyPet->m_wColorIdx == m_wColor)
		{
			ShowLShiftMenu();

			return 1;
		}
	}

	return 0;
}


int CUIMgr::CmdLShift()
{
	return 0;
}


void CUIMgr::ShowLShiftMenu()
{
	if( g_pNk2DFrame )
		g_pNk2DFrame->ShowLShiftMenu();
}
//////////

//--------------------------------------------------------------------------
// Can Use Power
//--------------------------------------------------------------------------
// ??
// 2004.04.27
// Lyul / �����Ϸ�

// Get_Appto �� ��� ���� ���� num0 �̴�.
// num0 = 4 �̸� �̵���ġ�ε�. ���� ���� ��ġ��
// ��ȭ������ ����� �� ���ٴ� �޼����� ������ �ȵȴ�.
// Item ���� ���� ��ų ���� ���� �ٸ����̳� �������� ��� �� �� �𸥴�.
// string �� ���� �ϰ� �׳� ����

// ��Ŀ���� ������( ĳ���� �������ͽ��� ��¦��~ )

// �����Կ� �ִ� ������ �߿��� ���������� �������� �����Ҷ� ����ϴ� ��ƾ.
// �� �Լ��� ȣ���ϱ� ���� ����ó���� �ʿ��ϴ�.
void CUIMgr::UseQuickGemstone(int slot_num)
{
	char buf[20];

	CNkCharacter *pNkCha = g_pRoh;

	if( !g_pRoh )
		return;

	// �˻��׸� : ŰƮ�� ����(ŰƮ�� ������ �κ� I, II, III �� �ִ� �͸� ���)
	// ��ų�� �����ϰ� �ִ°�? (�ڵ���ų�ΰ� ���ý�ų�ΰ�..)
	if (!pNkCha->m_QuickSlot[slot_num])
		return;

	// ��ų�� �����ϰ� �ִ°� Ȯ��.
	if (!g_ChaSkill.CanUseSkill(SKILL_WORK_GEM))
	{
		// IDS_UIMGR_UNABLE_SEKONG_SKILL : �� ���� ��ų�� ����� �� �����ϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_UNABLE_SEKONG_SKILL), -1);
		return;
	}

	if (pNkCha->m_Level < GET_ITEM_LEVEL(pNkCha->m_QuickSlot[slot_num]))
	{
		// IDS_UIMGR_UNABLE_SEKONG : �� ������ ���� �����Ҽ� �����ϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_UNABLE_SEKONG), -1);
		return;
	}

	// ���� �ɷ��ִ� �������ΰ�..
	if (pNkCha->m_bQuickSlotLock[slot_num])
	{
		// IDS_UIMGR_SEKONG_WORKING : �� �������Դϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_SEKONG_WORKING), -1);
		return;
	}

	// GemStone�ΰ��� Ȯ���Ѵ�.
	if (GET_TYPE(pNkCha->m_QuickSlot[slot_num]) != ITYPE_ETC && GET_SHAPE(pNkCha->m_QuickSlot[slot_num]) != IETC_GEMSTONE)
	{
		// IDS_UIMGR_NONE_GEMSTONE : �� ������ �ƴմϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_NONE_GEMSTONE), -1);
		return;
	}

	// ŰƮ�� ���� Ȯ��.
	int NeedKitNum = GET_NEEDKIT_NUM(pNkCha->m_QuickSlot[slot_num]);
	if ( NeedKitNum > pNkCha->GetKitsCount())
	{
		// IDS_UIMGR_SCARCE_KIT : �� ŰƮ�� ���� �����մϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_SCARCE_KIT), -1);
		return;
	}

	sprintf(m_commOut, "use_quick %d", slot_num);

	// ���� ŰƮ�� �ε��� ���ϰ� �����ϱ�.
	// ��� �����ѵ��� ��ȯ�ϸ鼭 �ʿ��� ����Ŷ�� �����Ѵ�.
	int count = 0;
	CItem *pItem = NULL;
	CItem *pItemPrev = NULL;
	CItem *pDelItem = NULL;
	for (int pack_num = 0; pack_num < PACK_NUM && count < NeedKitNum; pack_num++)
	{
		pItem = pNkCha->m_Inven[pack_num];
		pItemPrev = NULL;
		pDelItem = NULL;

		while (pItem)
		{
			if (pItem->m_Vnum == 229)
			{
				// 229�� ŰƮ �ѹ�.
				if (pItemPrev)
				{
					pItemPrev->m_Next = pItem->m_Next;
				}
				else
				{
					pNkCha->m_Inven[pack_num] = pItem->m_Next;
				}
				pDelItem = pItem;
				pItem = pItem->m_Next;

				sprintf( buf, " %d %d %d", pack_num, pDelItem->m_SlotX, pDelItem->m_SlotY ); // ���� ���� ��ȣ�� 100,101,102�� ������ �ڸ����� ���̱� ���� 0,1,2�� ����, ����ŰƮ�� �ε����� ������ ���� ���� x,y�� �������� ����. (05-10-04 ����)
				strcat(m_commOut, buf);

				pNkCha->m_Slot[pack_num][pDelItem->m_SlotX][pDelItem->m_SlotY] = -1;
				SAFE_DELETE(pDelItem);		// �߰��� ŰƮ�� �����Ѵ�.

				count++;
				if (count >= NeedKitNum)
				{
					strcat(m_commOut, "\n");
					break;
				}
				else
					continue;
			}
			else
			{
				pItemPrev = pItem;
				pItem = pItem->m_Next;
			}
		}
	}

	assert(count == NeedKitNum);


	// ������ �޽��� ����.
	if (g_pTcpIp)
		g_pTcpIp->SendNetMessage(m_commOut);
	pNkCha->m_bQuickSlotLock[slot_num] = TRUE;
}


//--------------------------------------------------------------------------
// UseQuiclSubItem
//--------------------------------------------------------------------------
// �����Կ� �ִ� ���� �������� ����.
// ���Ǵ� �޼����� ������ ������.
// �� SUB�������� �������� ������ �����Ƿ� ���빫�� üũ�� ����.

// 2004.06.10
// Lyul / �����Ϸ�
// ��ũ�� ���� �غ�� ���׹̳� �Ǵ�/

// 2004.07.13
// Lyul / �����Ϸ�
// �� ���� �������� ������ ���� ��� ����Ͽ� �޼��� �߻��Ǿ� ���� �����ϴ� ����
// �ʱ⿡ ������ �Ǵ��Ͽ� ����� ������ ���� �����


void CUIMgr::UseQuickSubItem(int slot_num)
{
	// �ʱ�ȭ
	static int past_time = timeGetTime();
	// ������ �ð�
	int cur_time = timeGetTime();
	// ���� Term �̳��� ��Ÿ�� ������ �� �߻��� ������ �ȴ�.
	// �����Ѵ�. (1/10�� . ����� 1�ʿ� 10�� ġ�� ���� ģ�� ��¥ �Ѥ�)
	if( cur_time - past_time > 100)
		past_time = cur_time;
	else
		return;

	// �÷��̾��� ������ access �� Pointer
	CNkCharacter *pNkCha = g_pRoh;

	if( !g_pRoh )
		return;
	//------------------------------------------------------------------------
	// ���̵�� ��ȯ��
	if(GET_SHAPE(pNkCha->m_QuickSlot[slot_num])==ISUB_SUMMON )
		pNkCha->m_bQuickSlotLock[slot_num]=TRUE;
	//------------------------------------------------------------------------
	// ī�̸��� ��ũ��
	else if(GET_SHAPE(pNkCha->m_QuickSlot[slot_num])==ISUB_SCROLL)
	{
		//----------------------------------------------------------------------
		// �ϵ� ���� ��ũ��
		if(pNkCha->m_QuickSlot[slot_num]->m_Num3 == 1)
		{
			// �κ�üũ
			if (!pNkCha->m_Wearing[WEARING_SHIELD])
				return;
			// Ÿ�� ���� üũ
			if(!(GET_ATT_FLAG(pNkCha->m_Wearing[WEARING_SHIELD]) & IATT_SUB_WEAPON))
				return;
			// ���� üũ
			if(pNkCha->m_QuickSlot[slot_num]->m_MinLevel != pNkCha->m_Wearing[WEARING_SHIELD]->m_MinLevel)
				return;
			// ������ üũ(1�̶� �����ϸ� ����)
			if(pNkCha->m_Wearing[WEARING_SHIELD]->m_Num3 <= pNkCha->m_Wearing[WEARING_SHIELD]->m_PlusNum)
				return;
		}
		//----------------------------------------------------------------------
		// Book ���� ��ũ�� ( ��ũ���� �޸� ���� book �� quick �� ���� �� �ִ�)
		// ���� true Ż�� loop �������� �ۼ�
		// ��� ������ �����Ǹ� loop ����
		else
		{
			if( pNkCha->m_QuickSlot[slot_num]->m_Vnum != 798
					&& pNkCha->m_QuickSlot[slot_num]->m_Vnum != 799
					&& pNkCha->m_QuickSlot[slot_num]->m_Vnum != 800 ) // ��ȣ ��ũ���� ����� ���� �ܵ� ����� �����ؼ� ����ó��(by ����)
			{
				int book_scrl_idx = 0; // Book �� ����ִ� Scroll ��ȣ

				// �� ���Կ� Book�� �ִ��� �˻�
				int i = 0;
				for(i = 0; i<QUICK_SLOT_NUM*QUICK_SLOT_PAGE; i++)
				{
					// ã���� ���� �˻�
					if( pNkCha->m_QuickSlot[i] && (GET_SHAPE(pNkCha->m_QuickSlot[i])==ISUB_BOOK))
					{
						// Book �Ӽ��� ���� item Index�� �����´�.
						book_scrl_idx = pNkCha->m_QuickSlot[i]->m_Special;

						// �Ӽ�(������ index) üũ(���� ������ Ȥ�� ��� ���� ���)
						if( book_scrl_idx == pNkCha->m_QuickSlot[slot_num]->m_Vnum
								|| book_scrl_idx ==0 )
						{
							// Level üũ
							if(pNkCha->m_QuickSlot[slot_num]->m_MinLevel <= pNkCha->m_QuickSlot[i]->m_Num7 )
							{
								// ������ üũ (1�̶� �����ϸ� 1�� ����)
								if(pNkCha->m_QuickSlot[i]->m_Num3 > pNkCha->m_QuickSlot[i]->m_PlusNum)
									i = 7;	// ����� �㰡 �� Loop �� Ż��
							}
						}
					}//end of if ����
				}// end of for �˻�

				// �������� ���� �����̶�� return
				if(i==6)
					return;
			}
		}

		for(int i=0 ; i<=5; i++)
			pNkCha->m_bQuickSlotLock[i]=TRUE;
	}
	//------------------------------------------------------------------------
	// ī�̸��� ����� ���
	else if(GET_SHAPE(pNkCha->m_QuickSlot[slot_num])==ISUB_BOOK)
	{
		// ����ٸ� �ź�.
		if(pNkCha->m_QuickSlot[slot_num]->m_PlusNum==0)
			return;
		else
		{
			// ���� ������,	 //[2009/4/20/ Theodoric] ��� ħ���� �� �������� ���� �� ��� ���
			if( g_pRoh->GetMyGuildData() != NULL &&
					pCMyApp->m_pHeroAttGoCha != NULL &&
					g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCMyApp->m_pHeroAttGoCha->m_GuildIndex )  &&
					!(pCMyApp->GetCurWorld() == 4 && pCMyApp->IsInsideRect(pCMyApp->m_pHeroAttGoCha->m_wx, pCMyApp->m_pHeroAttGoCha->m_wz, 6800, 5450, 7250, 5000) ) )
			{
				m_bBookSpell= TRUE;
				m_BookSlotNum = slot_num;
				return;
			}

			if(pCMyApp->IsPeaceArea())	//��ȭ�������� �� ��� ����
			{
				m_bBookSpell= FALSE;
				m_BookSlotNum = -1;
			}
			else
			{
				m_bBookSpell= TRUE;
				m_BookSlotNum = slot_num;
			}
			return;//�켱�� ����,
		}
	}
	//------------------------------------------------------------------------
	// ��ũ��
	// 2004.06.10
	// Lyul / �����Ϸ�
	// ��ũ���� ���׹̳� �� ���� �׳� ������. ���ϱ� �̰�
	else if((GET_SHAPE(pNkCha->m_QuickSlot[slot_num])==ISUB_CHAKRAM) &&
			g_pRoh->m_Stamina >= pNkCha->m_QuickSlot[slot_num]->m_Num4) // ���׹̳� ��
	{
		// ������ üũ
		if(pNkCha->m_QuickSlot[slot_num]->m_Special ==0 || pNkCha->m_QuickSlot[slot_num]->m_Special == 1)
		{
			pNkCha->m_QuickSlot[slot_num]->m_Special = 0;
			return;
		}
		else
		{
			int cur_skill = 9 ;	// üũ ��ũ�� ��ų �ε��� ��ȣ 9
			if(g_ChaSkill.m_SkillLevel[cur_skill] >= pNkCha->m_QuickSlot[slot_num]->m_MinLevel)
			{
				if(!pCMyApp->IsPeaceArea())
				{
					m_bChakram= TRUE;
					m_ChakramSlotNum = slot_num;
				}
				else
				{
					m_bChakram= FALSE;
					m_bChakramAtt = FALSE;
					m_ChakramSlotNum = -1;
				}
			}
			else
			{
				m_bChakram= FALSE;
				m_bChakramAtt = FALSE;
				m_ChakramSlotNum = -1;
			}
			return;
		}
	}
	//------------------------------------------------------------------------
	// źȯ�� ���� ���
	else
	{
		BOOL bChakram = FALSE;
		int slot = -1;
		//----------------------------------------------------------------------
		// źȯ�� ���
		if((GET_SHAPE(pNkCha->m_QuickSlot[slot_num])==IETC_SHELL))
		{
			// �κ�üũ
			if (!pNkCha->m_Wearing[WEARING_CLOAK])
				return;
			// Ÿ�� ���� üũ
			if(!(GET_ATT_FLAG(pNkCha->m_Wearing[WEARING_CLOAK])&IATT_SUB_WEAPON))
				return;
			// ��� ���� üũ ( ���� ����(����, ����,���� ��)�� ��츸 �����ϴ�.)
			if(pNkCha->m_Wearing[WEARING_CLOAK]->m_Num9 != pNkCha->m_QuickSlot[slot_num]->m_Num2)
				return;
			// ������ üũ.
			if(pNkCha->m_QuickSlot[slot_num]->m_Num3 > pNkCha->m_Wearing[WEARING_CLOAK]->m_Num3 - pNkCha->m_Wearing[WEARING_CLOAK]->m_PlusNum)
				return;
		}
		//----------------------------------------------------------------------
		// ����
		else if((GET_SHAPE(pNkCha->m_QuickSlot[slot_num])==IETC_CHARGE))
		{
			//--------------------------------------------------------------------
			// ��ũ���� ����
			if(pNkCha->m_QuickSlot[slot_num]->m_Vnum >=1005 && pNkCha->m_QuickSlot[slot_num]->m_Vnum<=1006)
			{
				// �� ���Կ� ��ũ���� �ִ��� �˻��Ѵ�.
				for(int i = 0; i<QUICK_SLOT_NUM*QUICK_SLOT_PAGE; i++)
				{
					// ã���� Flag setting
					if( pNkCha->m_QuickSlot[i] && (GET_SHAPE(pNkCha->m_QuickSlot[i])==ISUB_CHAKRAM))
					{
						bChakram = TRUE;
						slot = i;
						break;
					}
				}
				// ��ũ���� ������ ���� ���� ��� Return;
				if(slot==-1)
					return;

				// ���� ������ �������� �� ���� ȸ���� ���� ���� ���
				if(pNkCha->m_QuickSlot[slot_num]->m_Num3 > pNkCha->m_QuickSlot[slot]->m_Num3 - pNkCha->m_QuickSlot[slot]->m_Special
						&& bChakram )
					return;
			}
			// mungmae-2005/05/03-���� ������ ����
			else if(pNkCha->m_QuickSlot[slot_num]->m_Vnum == 1160)
			{
				// ����
				if(!pNkCha->m_Wearing[WEARING_CLOAK])
					return;
				// ���� GET_SHAPE(m_ExtraSlot) == ISUB_DSTONE)
				if( GET_SHAPE(pNkCha->m_Wearing[WEARING_CLOAK]) != ISUB_DSTONE)
					return;
				// ������ üũ
				if( pNkCha->m_QuickSlot[slot_num]->m_Num3 > pNkCha->m_Wearing[WEARING_CLOAK]->m_Num3 - pNkCha->m_Wearing[WEARING_CLOAK]->m_Special)
					return;
			}
			else if(pNkCha->m_QuickSlot[slot_num]->m_Vnum == 1356 )
			{
				//-- ����
				if(pNkCha->m_Wearing[WEARING_BRACELET] && pNkCha->m_Wearing[WEARING_BRACELET]->m_Vnum != 1330)
					return;
			}
			else if(pNkCha->m_QuickSlot[slot_num]->m_Vnum == 1357 )
			{
				//-- ����
				if(pNkCha->m_Wearing[WEARING_BRACELET] && pNkCha->m_Wearing[WEARING_BRACELET]->m_Vnum != 1358)
					return;
			}
			//--------------------------------------------------------------------
			// �����̾�� ����
			else
			{
				// �κ��� üũ
				if( !pNkCha->m_Wearing[WEARING_CLOAK])
					return;
				// Ÿ�� ���� üũ
				if( !(GET_ATT_FLAG(pNkCha->m_Wearing[WEARING_CLOAK])&IATT_SUB_WEAPON))
					return;
				// ������ üũ
				if( pNkCha->m_QuickSlot[slot_num]->m_Num3 > pNkCha->m_Wearing[WEARING_CLOAK]->m_Num3 - pNkCha->m_Wearing[WEARING_CLOAK]->m_Special)
					return;
			}
		}

		pNkCha->m_bQuickSlotLock[slot_num]=TRUE;//1009
	}// end of if źȯ ����

	//------------------------------------------------------------------------
	// ����� ������ ������ ��ȣ�� use_sub ����
	sprintf(m_commOut, "use_sub %d\n", slot_num);
	if (g_pTcpIp)
		g_pTcpIp->SendNetMessage(m_commOut);
}

// ����������� ������ ����� �������� ó���ϰ� ������..
void CUIMgr::UseQuickSubItem(int del_slot, int fill_slot,int plus_num, int special_num)
{
	if( !g_pRoh )
		return;

	CNkCharacter *pNkCha = g_pRoh;
	int i = 0;

	if( (del_slot>=0 && pNkCha->m_QuickSlot[del_slot] && GET_TYPE(pNkCha->m_QuickSlot[del_slot])==ITYPE_SUB)
			|| (fill_slot>=0 && pNkCha->m_QuickSlot[fill_slot] && GET_TYPE(pNkCha->m_QuickSlot[fill_slot])==ITYPE_SUB) ) // ���� Ÿ���� �����۸� ó���ؾ��ϴ� ��ƾ.(������ Ÿ��üũ�� ���߾���. ������ ���Լ��� ���� Ÿ�� �̿ܿ��� ���Ǿ�������.) 05-12-21 ����
	{


// 		else if (fill_slot>=0 && pNkCha->m_QuickSlot[fill_slot] && (GET_SHAPE(pNkCha->m_QuickSlot[fill_slot])==IETC_SUMMON))	//��ȯ��
// 		{
// 			pNkCha->m_QuickSlot[fill_slot]->m_PlusNum = plus_num;
// 			pNkCha->m_QuickSlot[fill_slot]->m_Special = special_num;	//��ȯ���� �ð�.
//
// 			if((m_pSummonMob[0] || m_pSummonMob[1]) && special_num)	// ��ȯ���� �ִ��� äũ
// 				pNkCha->m_bQuickSlotLock[fill_slot] = TRUE;
// 			else
// 				pNkCha->m_bQuickSlotLock[fill_slot] = FALSE;
// 		}

		if( pNkCha->m_QuickSlot[fill_slot] && GET_SHAPE(pNkCha->m_QuickSlot[fill_slot])==ISUB_BOOK)
		{
			if(pNkCha->m_QuickSlot[fill_slot])
			{
				pNkCha->m_QuickSlot[fill_slot]->m_PlusNum = plus_num;	//fill_slot�� ��ũ���� �� å���Թ�ȣ.
				pNkCha->m_QuickSlot[fill_slot]->m_Special = special_num;
			}

			for( i = 0 ; i <= 5 ; i++ )
				pNkCha->m_bQuickSlotLock[i]=FALSE;
		}
		else if(pNkCha->m_QuickSlot[fill_slot] && GET_SHAPE(pNkCha->m_QuickSlot[fill_slot]) == ISUB_CHAKRAM)
		{
			if(pNkCha->m_QuickSlot[fill_slot])
			{
				pNkCha->m_QuickSlot[fill_slot]->m_PlusNum = plus_num;	//fill_slot�� ��ũ���� �� å���Թ�ȣ.
				pNkCha->m_QuickSlot[fill_slot]->m_Special = special_num;
			}

			for( i = 0 ; i <= 5 ; i++ )
				pNkCha->m_bQuickSlotLock[i]=FALSE;
		}

		//==============================================================================
		// nate 2004 - 4
		// ��ȯ�� ������ �ڵ� ä��� ���
		// ��ȯ�� �ð� �ٵǾ�����.
		// ��ȯ��������϶� : -1, ������ �ѹ�, ������, ��ȯ�� �ð�
		// ��ȯ�� �ð� ������ : ������ �ѹ�, -1, ������:0, ��ȯ�� ���ð� : 0
		else if( fill_slot==-1 )
		{
			// �κ����� ������ üũ�ϰ�, ������ ��ȯ�� 1�� �����ϰ� �����Կ� ��´�
			// �����ϸ� 1��ȯ
			// �κ��� �������� ������ �������� ������ ����
			pNkCha->m_bQuickSlotLock[ del_slot ] = FALSE;
			if( CheckSummonToInven( del_slot ) )
				return;
			SAFE_DELETE(pNkCha->m_QuickSlot[ del_slot ]);
			return;
		}
		//==============================================================================
		else if(!pNkCha->m_QuickSlot[fill_slot])
			return;
	}

	for( i = 0 ; i <= 5 ; i++ )
		pNkCha->m_bQuickSlotLock[i]=FALSE;

	g_pNk2DFrame->GetControlInven()->ResetItemInfo();	///0927 ��������� ������ ���� ����.
}


/////////////////////////////////////////////////////////////////////
// Name :
// Desc :
/////////////////////////////////////////////////////////////////////
void CUIMgr::MusicStop()
{
	mciSendCommand(m_DeviceId, MCI_CLOSE, 0, NULL);
}

/////////////////////////////////////////////////////////////////////
// Name :
// Desc :
/////////////////////////////////////////////////////////////////////
void CUIMgr::MusicPlay(char* fileName)
{
	if( fileName == NULL )
		return;

	MCI_OPEN_PARMS mciOpenParms;
	MCI_PLAY_PARMS mciPlayParms;

	mciOpenParms.lpstrDeviceType = "sequencer";
	mciOpenParms.lpstrElementName = fileName;
	mciSendCommand(NULL, MCI_OPEN , MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms);

	m_DeviceId = mciOpenParms.wDeviceID;

	mciPlayParms.dwCallback = (unsigned long) m_hWnd;
	mciSendCommand(m_DeviceId, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
}

// -------------------------------------------------------------------
// Name : ShowName()
// Desc : ��ü�� �̸��� ��Ÿ���ش�.
// ------------------------------------------------------------------
COLORREF mobname_color[4] = { RGB(238, 0, 0), RGB(0, 36,216),
							  RGB(0, 239, 17), RGB(242, 245, 0)
							};


//===========================================================
// nate 2004 - 4
// Crash_Miss  ���� // [3/30/2007 Theodoric] ����� �� ǥ��
int CUIMgr::ShowName(int &target_idx)
{
	CNkCharacter	*pCha		= NULL;
	CNkMob			*pMob		= NULL;
	CNkPet			*pPet		= NULL;
	CItemInfo		*pItemInfo	= NULL;
	//static char player_name[30];

	// ���� ���콺�� ����� ���� ���� �ִ����� ����.. - �̰� �׽�Ʈ���̴�.

	if (m_wColor == g_pRoh->m_wColorIdx)
	{
		// ���⼭ �۾��� �ϰ�..
		if (m_wPrevName != m_wColor || m_bShowName == FALSE)
		{
			CalNamePos(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz, 0);
			m_NameBox.SetString(g_pRoh->m_pstrName);
			m_wPrevName = m_wColor;
		}
		return TRUE;
	}


	// ���ΰ� �̸� ���̰� �ϱ�
	if (m_wColor == g_pRoh->m_wColorIdx)
	{
		// ���⼭ �۾��� �ϰ�..
		if (m_wPrevName != m_wColor || m_bShowName == FALSE)
		{
			if (!g_pRoh->IsShowChatPopup() || g_pNk2DFrame->GetControlBottom()->IsChatWide())
			{
				CalNamePos(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz, 0);
				g_pRoh->OnChatMsg();
				m_wPrevName = m_wColor;
				return TRUE;
			}
			m_bShowName = FALSE;
		}
		return TRUE;
	}

	// �÷��̾�� Ȯ��.
	if( pCha = GetCharacterByColorKey( m_wColor ) )
	{
		if (m_wPrevName != m_wColor || m_bShowName == FALSE)
		{
			target_idx = pCha->m_nCharIndex;
			if (!pCha->IsShowChatPopup() || !g_pNk2DFrame->GetControlBottom()->m_ChatOutOpt_BalloonOnOff.GetToggleState() )
			{
				CalNamePos(pCha->m_wx, pCha->m_wy, pCha->m_wz, 0);
				pCha->OnChatMsg();
				m_wPrevName = m_wColor;
				return 1;
			}
			m_bShowName = FALSE;
		}
		return 1;
	}
//========================================
	// nate 2004 - 4
	// quest Level
	int nCharacterLevel = ComputeCharClass( g_pRoh->m_Level );
//========================================
	// ���� Ȯ��.
	// ���ʹ� Capsyng object������ ȭ�� �߾ӿ� �Ѹ���.
	if( pMob = GetMobByColorKey( m_wColor ) )
	{
		if( pMob->m_nMobNum == 603 )
		{
			m_bShowName = FALSE;
			return 7;
		}

		if( !DontShowNameMob( pMob ) ) // ���� �������� ǥ������ ���� ���͵�
		{
			if (m_wPrevName != m_wColor || m_bShowName == FALSE)
			{
				// SetString �ϱ� ���� init()���� ȣ�����־�� �Ѵ�.
				// CalPlayerPos()���� m_NameBox.init()�� ȣ����.

				if( (pMob->m_Flag & NPC_SHOPKEEPER) || (pMob->m_Flag & NPC_GUARD) )
				{
					CalNamePos(pMob->m_wx, pMob->m_wy, pMob->m_wz, 1);
				}
				else
				{
					CalNamePos(pMob->m_wx, pMob->m_wy, pMob->m_wz, 3);
					m_ShowVitalId = 2;
				}

				// [3/30/2007 Theodoric] ����� �� ǥ�� :: ���� �ִ� ������ �Լ��� �и��ߴ�.
				SetShowName( &m_NameBox, pMob );

				m_Vital = pMob->m_Vital;
				m_wPrevName = m_wColor;
				target_idx = pMob->m_nVirId;

				if ((pMob->m_Flag & NPC_SHOPKEEPER) || (pMob->m_Flag & NPC_GUARD))
				{
					m_bShowName = TRUE;
					return 3;
				}
				else if(pMob->m_nMobNum == 504) //���Ʈ�� ����Ʈ ����Ʈ �̵�
				{
					m_bShowName = FALSE;
					m_ShowVitalId = -1;
					return 7;
				}
				else
				{
					m_bShowName = FALSE;
					return 2;
				}
			}
		}
	}
	else
	{
		printf("No Mob color key : %d\n", (int)m_wColor);
	}

	if( pPet = GetPetByColorKey(m_wColor) )
	{
		if (m_wPrevName != m_wColor || m_bShowName == FALSE)
		{
			CalNamePos(pPet->m_wx, pPet->m_wy, pPet->m_wz, 1);
			m_NameBox.SetString(pPet->m_strName,  RGB(251, 218, 8));
		}
		m_wPrevName = m_wColor;
		m_bShowName = TRUE;
		return 5;
	}

	// ������ Ȯ��.
	// �������� Lolo object������ �ٿ�� �ڽ��� �̿��ؼ� ���̰� ����.
	if( pItemInfo = GetItemInfoByColorKey(m_wColor) )
	{
		{
			if (m_wPrevName != m_wColor || m_bShowName == FALSE)
			{
				CalNamePos(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_BoundVert[5].y, pItemInfo->m_Item.m_Z, 2);

				if (pItemInfo->m_Item.m_Vnum == 1014 || pItemInfo->m_Item.m_Vnum == 1239)   // ���� ������ �ѹ� 1014 ��...// ���� ������ �ѹ� 1014 ��...
				{
					m_NameBox.SetString(pItemInfo->m_TextOutBox.m_str, RGB(251, 218, 8));
				}
				else if (pItemInfo->m_Item.m_Vnum == 1307) //mungmae-2005/10/5 �°�&����Ӵ� ����
					m_NameBox.SetString(pItemInfo->m_TextOutBox.m_str, RGB(251, 218, 8));

				else if( GET_TYPE_REF(pItemInfo->m_Item) == ITYPE_SUB )
				{
					char strName[50];
					sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));
					m_NameBox.SetString(strName,  RGB(251, 218, 8));
				}
				else if( GET_TYPE_REF(pItemInfo->m_Item) == ITYPE_ETC
						 && ( GET_SHAPE_REF(pItemInfo->m_Item) == IETC_RECOVERY
							  || GET_SHAPE_REF(pItemInfo->m_Item) == IETC_BUFF )
					   )
				{
					char strName[50];
					sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

					m_NameBox.SetString(strName);
				}
				else if (pItemInfo->m_Item.m_PlusNum > 0)
				{
					char strName[50];
					sprintf(strName, "%s +%d", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum), pItemInfo->m_Item.m_PlusNum);

					m_NameBox.SetString(strName, UPGRADE_ITEM_COLOR_REF);
				}
				else if (pItemInfo->m_Item.m_Special > 0)
				{
					char strName[50];
					sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));
					m_NameBox.SetString(strName, SPECIAL_ITEM_COLOR_REF);
				}
				else if (pItemInfo->m_Item.m_Special2 > 0)
				{

					char strName[50];
					sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));
					m_NameBox.SetString(strName,  SPECIAL_ITEM_COLOR_REF);
				}
				else
				{
					char strName[50];
					sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));
					m_NameBox.SetString(strName,  RGB(251, 218, 8));
				}

				if( pItemInfo->m_Item.m_bTimeLimit ) // �ð��� ������ ���ѵ� ǥ�� �߰�( 06-05-20 ����)
				{
					char strTemp2[50];

					//-- IDS_TIMELIMIT_ITEM_TITLE : ���ѵ�
					sprintf( strTemp2, "%s %s", G_STRING(IDS_TIMELIMIT_ITEM_TITLE), m_NameBox.m_str ); // �̸� �տ� ������ �߰�.

					m_NameBox.SetString( strTemp2, RGB(230,230,230) );
				}


				m_wPrevName = m_wColor;
				m_bShowName = TRUE;
				if(m_bAlt)
					m_bShowName = false;
			}
			return 4;
		}
	}

	return 0;
}


// ���� ������ ǥ�� ���� �ʴ� ��
BOOL CUIMgr::DontShowNameMob( CNkMob *pMob )
{
	switch( pMob->m_nMobNum )
	{
	case 463: // 6�ֳ� ��� �̺�Ʈ �ɟ�
	case 465: // ��ī�� ö��
	case 466: // ��ī�� ����
	case 467: // ��ī�� ��ö��
	case 492: // ��� ������ ���̵� ��
	case 493: // ��� ������ ���� ��
	case 603: // ������ ���� �巹��ũ �� ����Ʈ
	case 613:
	case 646: // �� ������


		return TRUE;
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// [3/30/2007 Theodoric] [3/30/2007 Theodoric] ����� �� ǥ��
extern bool g_bShowIndex;
extern bool g_bShowVnum;
COLORREF CUIMgr::SetShowName( CTextOutBox *pNamebox, CNkMob *pMob )
{

	// SetString �ϱ� ���� init()���� ȣ�����־�� �Ѵ�.
	// CalPlayerPos()���� m_NameBox.init()�� ȣ����.
	char name[MAX_PATH] = {0,};
	int nCharacterLevel = ComputeCharClass( g_pRoh->m_Level );
	COLORREF rgb = RGB( 251, 218, 0 );

	if( m_byQuest2Start && !( (pMob->m_Flag & NPC_SHOPKEEPER) || (pMob->m_Flag & NPC_GUARD)) )
	{
		if( abs( nCharacterLevel - pMob->m_nLevel ) == 0 )
			rgb = RGB(251, 218, 8);
		else if( abs( nCharacterLevel - pMob->m_nLevel ) == 1 )
			rgb = RGB(58, 206, 255);
		else if( abs( nCharacterLevel - pMob->m_nLevel ) == 2 )
			rgb = RGB(0, 250, 0);
		else if( abs( nCharacterLevel - pMob->m_nLevel ) > 2 )
			rgb = RGB(251, 0, 8);
	}

	if (pMob->m_Mutant > 0 && pMob->m_Mutant <= 4 && (pMob->m_nMobNum < 179 || pMob->m_nMobNum > 187))
	{
		if( !( pMob->m_nMobNum == 327 || pMob->m_nMobNum == 328 || pMob->m_nMobNum == 329 ) ) // ������� ����Ʈ�� �̸� �ڿ� ���δ�.
		{
			strcpy(name, G_STRING(IDS_UIMGR_MUTANT));
		}
	}
	else if( ((pMob->m_Mutant==5 || pMob->m_bQuestMob) && !(pMob->m_Flag & NPC_QUEST)))
	{
		strcpy(name, G_STRING(IDS_UIMGR_CURSED));
	}
	else if( pMob->m_MobAttributeType == 100 )
	{
		strcpy(name, G_STRING(IDS_REVOLT_MOB));
	}

	strcat(name, pMob->GetMobName());

	if( g_bShowIndex )
	{
		std::string temp = name;
		sprintf(name, "%s(%d)", temp.c_str(), pMob->m_nVirId);
	}
	if( g_bShowVnum )
	{
		std::string temp = name;
		sprintf(name, "[%d]%s", pMob->m_nMobNum, temp.c_str());
	}

	pNamebox->SetString(name, rgb );

	return rgb;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//===========================================================

// -------------------------------------------------------------------
// Name : CalNamePos()
// Desc : ��ü�� �̸��� ��Ÿ�� ��ġ�� ��´�.
// ------------------------------------------------------------------
void CUIMgr::CalNamePos(float wx, float wy, float wz, int which)
{
	D3DMATRIX matPipe;
	D3DVECTOR vScr, vWorld;

	// [3/30/2007 Theodoric] ����� �� ǥ�� :: ���� ó���� ���� ����ġ ������ ����
	// 3�� ���� �κ��� �߰� �Ǿ���. 1�� NPC�κ��� �����Ǿ���.
	switch( which )
	{
	case 0: // ĳ������ ���
		vWorld = D3DVECTOR(wx, wy+23.0f, wz);

		// ���ǻ� CLand�� ����� ����.
		m_pLand->GetPipelineMatrix(matPipe);

		// �������� ���� ȭ����� ������ �ٲ۴�.
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		vScr.y -= 18;	// �ڽ��� �뷫���� ũ��.
		if (vScr.y < 0)
			vScr.y = 0;
		if (vScr.y >= g_pNk2DFrame->GetClientHeight())
		{
			vScr.y = g_pNk2DFrame->GetClientHeight() - 20;
			//MessageBox(NULL, "void CUIMgr::CalNamePos(float wx, float wy, float wz)", "Error", MB_OK);
		}
		break;

	case 1: // NPC
//		vScr.x = g_pNk2DFrame->GetClientWidth() / 2;
//		vScr.y = VITAL_BACK_HEIGHT + 1;

		vWorld = D3DVECTOR(wx, wy+25.0f, wz);

		// ���ǻ� CLand�� ����� ����.
		m_pLand->GetPipelineMatrix(matPipe);

		// �������� ���� ȭ����� ������ �ٲ۴�.
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);
		vScr.y -= 18;
		break;

	case 2: // Item
		wy = m_pLand->GetHFHeight(wx, wz) + wy;
		vWorld = D3DVECTOR(wx, wy, wz);

		// ���ǻ� CLand�� ����� ����.
		m_pLand->GetPipelineMatrix(matPipe);

		// �������� ���� ȭ����� ������ �ٲ۴�.
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		vScr.y -= 18;	// �ڽ��� �뷫���� ũ��.
		if (vScr.y < 0)
			vScr.y = 0;
		if (vScr.y >= g_pNk2DFrame->GetClientHeight())
		{
			vScr.y = g_pNk2DFrame->GetClientHeight() - 20;
			//MessageBox(NULL, "void CUIMgr::CalNamePos(float wx, float wy, float wz)", "Error", MB_OK);
		}
		break;

	case 3:
		vWorld = D3DVECTOR(wx, wy, wz);
		m_pLand->GetPipelineMatrix(matPipe);

		// �������� ���� ȭ����� ������ �ٲ۴�.
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		vScr.y += 18;
		break;

	}
	m_NameBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, (int) vScr.x, (int) vScr.y, -1, -1, TRUE);

	/*
		if (which == 0) // ĳ������ ���.
		{
			vWorld = D3DVECTOR(wx, wy+23.0f, wz);

			// ���ǻ� CLand�� ����� ����.
			m_pLand->GetPipelineMatrix(matPipe);

			// �������� ���� ȭ����� ������ �ٲ۴�.
			D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

			vScr.y -= 18;	// �ڽ��� �뷫���� ũ��.
			if (vScr.y < 0)
				vScr.y = 0;
			if (vScr.y >= g_pNk2DFrame->GetClientHeight()) {
				vScr.y = g_pNk2DFrame->GetClientHeight() - 20;
				//MessageBox(NULL, "void CUIMgr::CalNamePos(float wx, float wy, float wz)", "Error", MB_OK);
			}
		}
		else if (which == 1) // NPC
		{		// ������ ��쿡�� ȭ�� ����� �߾ӿ� ��ġ�Ѵ�.
			vScr.x = g_pNk2DFrame->GetClientWidth() / 2;
			vScr.y = VITAL_BACK_HEIGHT + 1;
		}
		else if (which == 2) // ������.
		{
			wy = m_pLand->GetHFHeight(wx, wz) + wy;
			vWorld = D3DVECTOR(wx, wy, wz);

			// ���ǻ� CLand�� ����� ����.
			m_pLand->GetPipelineMatrix(matPipe);

			// �������� ���� ȭ����� ������ �ٲ۴�.
			D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

			vScr.y -= 18;	// �ڽ��� �뷫���� ũ��.
			if (vScr.y < 0)
				vScr.y = 0;
			if (vScr.y >= g_pNk2DFrame->GetClientHeight()) {
				vScr.y = g_pNk2DFrame->GetClientHeight() - 20;
				//MessageBox(NULL, "void CUIMgr::CalNamePos(float wx, float wy, float wz)", "Error", MB_OK);
			}
		}
		else if (which == 3) // ����
		{
			vWorld = D3DVECTOR(wx, wy, wz);
			m_pLand->GetPipelineMatrix(matPipe);

			// �������� ���� ȭ����� ������ �ٲ۴�.
			D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

			vScr.y += 18;
		}else if (which == 4)
		m_NameBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, (int) vScr.x, (int) vScr.y, -1, -1, TRUE);
		*/
}


void CUIMgr::CalNamePos(CItemInfo *pItemInfo, float wx, float wy, float wz, int which)
{
	if( pItemInfo == NULL )
		return;

	D3DMATRIX matPipe;
	D3DVECTOR vScr, vWorld;

	if (which == 0)
	{
		// ĳ������ ���.
		vWorld = D3DVECTOR(wx, wy+23.0f, wz);

		// ���ǻ� CLand�� ����� ����.
		m_pLand->GetPipelineMatrix(matPipe);

		// �������� ���� ȭ����� ������ �ٲ۴�.
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		vScr.y -= 18;	// �ڽ��� �뷫���� ũ��.
		if (vScr.y < 0)
			vScr.y = 0;
		if (vScr.y >= g_pNk2DFrame->GetClientHeight())
		{
			vScr.y = g_pNk2DFrame->GetClientHeight() - 20;
			//MessageBox(NULL, "void CUIMgr::CalNamePos(float wx, float wy, float wz)", "Error", MB_OK);
		}
	}
	else if (which == 1)
	{
		// ����.
		// ������ ��쿡�� ȭ�� ����� �߾ӿ� ��ġ�Ѵ�.
		vScr.x = g_pNk2DFrame->GetClientWidth() / 2;
		vScr.y = VITAL_BACK_HEIGHT + 1;
	}
	else if (which == 2)
	{
		// ������.
		wy = m_pLand->GetHFHeight(wx, wz) + wy;
		vWorld = D3DVECTOR(wx, wy, wz);

		// ���ǻ� CLand�� ����� ����.
		m_pLand->GetPipelineMatrix(matPipe);

		// �������� ���� ȭ����� ������ �ٲ۴�.
		D3DMath_VectorMatrixMultiply(vScr, vWorld, matPipe);

		vScr.y -= 18;	// �ڽ��� �뷫���� ũ��.
		if (vScr.y < 0)
			vScr.y = 0;
		if (vScr.y >= g_pNk2DFrame->GetClientHeight())
			vScr.y = g_pNk2DFrame->GetClientHeight() - 20;

		if (pItemInfo)
		{
			pItemInfo->m_TextOutBox.m_StringPosX = vScr.x - pItemInfo->m_TextOutBox.m_pSurf->GetWidth()/2;
			pItemInfo->m_TextOutBox.m_StringPosY = vScr.y;

			pItemInfo->m_TextOutBox_Active.m_StringPosX = vScr.x - pItemInfo->m_TextOutBox.m_pSurf->GetWidth()/2;
			pItemInfo->m_TextOutBox_Active.m_StringPosY = vScr.y;
		}
	}

	//m_NameBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, (int) vScr.x, (int) vScr.y, -1, -1, TRUE);
}



//--------------------------------------------------------------------------
// AddPlayer
//--------------------------------------------------------------------------
// Room ������ ������ ĳ���� ���������� �ǹ��Ѵ�.
// cmd "in ���� ���� �޼���

// 2005.01.14 / Lyul
// Bleed ��ų ���� �߰�.
void CUIMgr::AddPlayer(int id, const char *name, int nShowMark, float x, float z, float fLevel, float dir,
					   int nRace, int nSex, int nHair, int *wearing_vnum, int nCombatState,
					   int skill, int condition,int extra, int chaotic_grade, int free_pk,
					   int fly_level, char *guild_name, char *guild_grade_name, int guild_index,
					   int guild_type
					   , int guild_idx
					  )
{
	if( name == NULL
			|| guild_name == NULL
			|| guild_grade_name == NULL )
		return;

	CNkCharacter *pCha = new CNkCharacter( g_pShadowRect, NULL, g_ClrAlloc );
	pCha->SetInitPos(x, z);
	pCha->SetLevel( fLevel );	// ĳ���� ����
	pCha->m_dir = dir;
	pCha->m_toDir = dir;
	pCha->m_GuildGradeIndex = guild_index;
	pCha->m_GuildIndex = guild_idx;
	pCha->SetInfo(id, name, guild_name, guild_grade_name);
	pCha->SetFlyLevel(fly_level);

	if (condition != 0)
	{
		pCha->SetChaCondition(condition, TRUE); //����
	}
	else
	{
		pCha->SetChaCondition(condition, FALSE); //����
	}

	//if( pCha->m_Race == RACE_AIDIA )
	pCha->SetInAidiaSkill(extra); //���̵�� ���ӽ�ų.
	//else
	//{
	//	//
	//}

	// Enchant Skill �� ó�� �κ�
	// Bleed(����) �� ��� ���� ��ƾ�� ������ �ȵȴ�.
	if(skill == SKILLF_E_BLEED)
		pCha->m_bBleed = true;
	else
		pCha->SetInSkill(skill);

	pCha->m_Chaotic_Grade = chaotic_grade;//1023
	if(free_pk==2)//0305 �������� ����
		pCha->m_bNonPK = TRUE;
	else
		pCha->m_Free_Pk = free_pk;

	// ���ϰ� ���� �����ΰ� �ƴѰ��� Ȯ���Ѵ�.
	if (g_pRoh->m_pstrGuildName)
	{
		if ( strcmp(g_pRoh->m_pstrGuildName, guild_name) == 0)
			pCha->SetMyGuild(TRUE);
		else
			pCha->SetMyGuild(FALSE);
	}
	else
		pCha->SetMyGuild(FALSE);

	if( g_MatrixSvr != 0)
		pCha->m_GuildIndex = guild_type;
	else
	{
		// ���� �����ڸ�,,
		if (guild_type == 1)
		{
			pCha->m_bCrystalOwner = TRUE;
			if (!pCha->m_bMyGuild)
			{
				pCha->SetOppGuild(TRUE);
				g_pRoh->m_bCrystalGuild = FALSE;
			}
			else
				g_pRoh->m_bCrystalGuild = TRUE;

		}
		else if (!pCha->m_bMyGuild && guild_type == 2)
		{
			pCha->SetOppGuild(TRUE);
			g_pRoh->m_bCrystalGuild = FALSE;
		}
		else if (guild_type >= 3 && guild_type <= 8)
		{
			pCha->SetOppGuild(FALSE);
			g_pRoh->m_bCrystalGuild = FALSE;
			pCha->m_nTeamMemGrade = guild_type - 2;
			//g_pRoh->m_nTeamMemGrade = guild_type - 2;
		}
		else if (guild_type == 9)
		{
			//����� ���̸�
			pCha->m_nTeamMemGrade = 9;
		}
		else if (guild_type == 10)
		{
			pCha->m_nTeamMemGrade = 10;
		}
		else if (guild_type == 11)
		{
			// ��� ������
			pCha->m_bFlagOwner[0] = TRUE;
			if(pCha->m_bMyGuild)
				g_pRoh->m_bFlagGuild[0] = TRUE;
		}
		else if (guild_type == 12)
		{
			pCha->m_bFlagOwner[1] = TRUE;
			if(pCha->m_bMyGuild)
				g_pRoh->m_bFlagGuild[1] = TRUE;
		}
		else if (guild_type == 13)
		{
			pCha->m_bFlagOwner[2] = TRUE;
			if(pCha->m_bMyGuild)
				g_pRoh->m_bFlagGuild[2] = TRUE;
		}
		else if (guild_type == 14)
		{
			pCha->m_bFlagOwner[3] = TRUE;
			if(pCha->m_bMyGuild)
				g_pRoh->m_bFlagGuild[3] = TRUE;
		}
		else if (guild_type == 15)
		{
			pCha->m_bFlagGuild[0] = TRUE;
		}
		else if (guild_type == 16)
		{
			pCha->m_bFlagGuild[1] = TRUE;
		}
		else if (guild_type == 17)
		{
			pCha->m_bFlagGuild[2] = TRUE;
		}
		else if (guild_type == 18)
		{
			pCha->m_bFlagGuild[3] = TRUE;
		}
	}

	pCha->InitChatPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight());

	pCha->MakeBasicBody(nRace, nSex, nHair);

	if (wearing_vnum)
	{
		for (int where = 0; where < WEARING_SHOW_NUM; where++)
		{
			pCha->Wear(where, -1, wearing_vnum[where]);
		}
		pCha->Wear(WEARING_WEAPON, -1, wearing_vnum[WEARING_WEAPON]);
	}

	// nCombatState 0:��ȭ���, 1:�������, 2: �ẹ���.
	if (nCombatState == 0)
	{
		pCha->SetCombat(FALSE);
		pCha->SetHideMode(HIDE_SHOWN);
		pCha->SetMotionState(CHA_STAND);
	}
	else if (nCombatState == 1)
	{
		pCha->SetCombat(TRUE);
		pCha->SetHideMode(HIDE_SHOWN);
		pCha->SetMotionState(CHA_STAND);
	}
	else if (nCombatState == 2)
	{
		pCha->SetHideMode(HIDE_HIDDEN);
		pCha->SetCombat(FALSE);
		pCha->SetMotionState(CHA_STAND);
	}
	else if (nCombatState == 67)
	{
		pCha->SetCombat(FALSE);
		pCha->SetHideMode(HIDE_SHOWN);
		pCha->SetMotionState(CHA_SOCIAL, 68);
	}
	else if (nCombatState == 87)
	{
		pCha->SetCombat(FALSE);
		pCha->SetHideMode(HIDE_SHOWN);
		pCha->SetMotionState(CHA_SOCIAL, 88);
	}
	else
	{
		pCha->SetHideMode(HIDE_SHOWN);
		pCha->SetCombat(FALSE);
		pCha->SetMotionState(CHA_STAND);
	}

	if (g_pNk2DFrame->GetControlParty()->IsMyParty(id))
		pCha->SetMyParty(TRUE);
	else
		pCha->SetMyParty(FALSE);

	pCha->ShowMatrixMark(nShowMark);

	AddCharacter(pCha);
	g_nPlInNum = m_character_map.size();

	if( pCha && pCha->m_Wearing[3] && pCha->m_Wearing[3]->m_Vnum == 1774 ) // �����̾� ���並 �����ִٸ�...
		pCMyApp->m_pUIMgr->SkillOnOff( 1, TRUE, pCha->m_nCharIndex, SKILL_VAMPIREBAT ); // ���� ����Ʈ�� �־��ش�.

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));

	ef_sort.nType = FX_WEAPONEFFECTS;
	ef_sort.pNkChaTo = pCha;
	pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
}

// -------------------------------------------------------------------
// Name : DeletePlayer()
// Desc : �÷��̾ ����Ʈ���� �����Ѵ�.
// ------------------------------------------------------------------
void CUIMgr::DeletePlayer(int id)
{
	DelCharacter(id);
}

// -------------------------------------------------------------------
// Name : AddMob()
// Desc : ���� ��Ÿ����.
// ------------------------------------------------------------------
///2003 �Լ��� ���� ����
void CUIMgr::AddMob(int mob_num, int id, float x, float z, float dir, int vital, int mutant,int attribute,int mobclass, int nLevel, int RegenType ) // ���� �÷��� �߰� ///�δ�1
//void CUIMgr::AddMob(int mob_num, int id, float x, float z, float dir, int vital, int mutant)
{
	CNkMob *pMob;

	pMob = new CNkMob_ByPool(g_ClrAlloc);
	pMob->SetInfo(mob_num, id, 0);		// 0�� stand, ���Ͱ� ������ ���Ŀ� id�� ���� �Ҵ� �ؾ� �ϰ�, �� ������ ��ġ ���� �ʿ�.
	pMob->SetInitPos(x, z, dir);
	pMob->SetMotionState(MOB_STAND);
	pMob->m_Vital = vital;
	pMob->m_AttackVital = vital;
	pMob->m_Mutant = mutant;
	//pMob->m_Mutant = 1;
//�߰� ��ų �߰� �����Ǽ� �п���
//	pMob->SetAttributeType(attribute);

///2003 ���� �迭�� �Ӽ� ���� �ֱ�
	pMob->m_MobClassType = mobclass; //
	pMob->m_MobAttributeType = attribute;//�̺�Ʈ ��(������ �ݶ�)
//=====================================
	// nate 2004 - 4
	// quest
	pMob->m_nLevel = nLevel;
//=====================================

	///�δ�1
	pMob->m_RegeningType = RegenType;
	if( RegenType == 2 ) // ���ӿ��� Ƣ����� ����� �����̸�...
	{
		int TerrainHeight = pCMyApp->GetLandPtr()->GetHFHeight(x, z);

		if( pMob->m_Height == MOB_HEIGHT_HIGH_NUM ) // ���� ���� '�ܰ�'
		{
			// ������...
			pMob->m_wy = TerrainHeight - 100.0f; // ������ Ư��ġ�� ��������.
		}
		else if( pMob->m_Height == MOB_HEIGHT_MIDDLE_NUM ) // ���� ���� '�ܰ�'
		{
			// �߰�...
			pMob->m_wy = TerrainHeight - 50.0f; // ������ Ư��ġ�� ��������.
		}
		else if( pMob->m_Height == MOB_HEIGHT_LOW_NUM ) // ���� ���� '�ܰ�'
		{
			// ����
			pMob->m_wy = TerrainHeight - 20.0f; // ������ Ư��ġ�� ��������.
		}
		pMob->m_fDash_Frame = 0.0f; // �˹�� ����ϴ� ������ �ö���� �ӵ��� ���.
		/*
					EffectSort ef_sort;
					ZeroMemory(&ef_sort, sizeof(EffectSort));
					ef_sort.nType = FX_RUNSMOKE;
					ef_sort.vPos = D3DVECTOR(pMob->m_wx, pCMyApp->GetLandPtr()->GetHFHeight(pMob->m_wx, pMob->m_wz)-7.0f, pMob->m_wz);
					pMob->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		*/
	}
	else if( RegenType == 1 ) // ������ �й��
	{
		pMob->m_RegeningType = 0; // ���ٸ� ������ �����Ƿ� �ʱ�ȭ���ش�.
	}

//========================================================================================
	// nate 2004 - 4
	// Crash_Miss
	pMob->InitCrash_MissPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight());
	pMob->InitMobChatPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight());
//========================================================================================
		
	AddMob(pMob);

	g_nMobInNum = m_mob_map.size();

	///�굵�� �ý����� Npc ������ üũ�ؾ��ϴ� ������ �˻�.
	if( pMob->m_Flag & NPC_HELPPET ) // ���� üũ�Ϸ��� ������ ���ϴϱ� ���� üũ�� �ִ� �༮�� üũ.
	{
		if( g_pNk2DFrame && g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet() )
			g_pNk2DFrame->GetControlHelpPet()->CheckHelpCondition( 4, pMob->m_nMobNum, TRUE ); // Npc ������ ������ �ִ��� üũ�Ѵ�.
	}
}

// -------------------------------------------------------------------
// Name : DeletePlayer()
// Desc : �÷��̾ ����Ʈ���� //  [1/27/2010 ppmmjj83] DelMob�Լ��� ��ü
// ------------------------------------------------------------------
// void CUIMgr::DeleteMob(int id)
// {
// 	CNkMob* temp = safe_delete_associate_colorkey(m_mob_map, id);
// 	LHColorKeyMap::iterator it = m_colorkey_map.find(temp->m_wColorIdx);
// 	if( it!=m_colorkey_map.end() )
// 	{
// 		if( (*it).second )
// 		{
// 			delete (*it).second;
// 			m_colorkey_map.erase(it);
// 		}
// 	}
// 	else
// 		printf("NO!! m_colorkey_map find fail!!!\n");
//
// 	safe_delete_associate_key(m_mob_map, id);
// 	g_nMobInNum = m_mob_map.size();
//}

void CUIMgr::AddUserShopNpc( int MasterIndex, int Vnum, int NpcIndex, float x, float z, float dir, const char *name, const char *ment ) ///��������
{
	CUserShopNpc *pUserShopNpc;

	pUserShopNpc = new CUserShopNpc( g_ClrAlloc );
	pUserShopNpc->SetInfo( Vnum, NpcIndex, 0 );		// 0�� stand, ���Ͱ� ������ ���Ŀ� id�� ���� �Ҵ� �ؾ� �ϰ�, �� ������ ��ġ ���� �ʿ�.
	pUserShopNpc->SetInitPos( x, z, dir );
	pUserShopNpc->SetMotionState( MOB_STAND );

	pUserShopNpc->m_MasterIndex = MasterIndex;
	strcpy( pUserShopNpc->m_strMasterName, name ); // ���� ���� �̸�.
	strcpy( pUserShopNpc->m_strUserShopMent, ment ); // ���� ��Ʈ

	pUserShopNpc->InitCrash_MissPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight() ); // ���� ��Ʈ ��¿����� ����.

	if( pUserShopNpc->m_pCrash_MissPopup[0] )
	{
		CMultiText multiText;
		char strTemp[100];

		//-- IDS_WHOS_USHOP2 : %s�� ��������
		sprintf( strTemp, (char*)G_STRING(IDS_WHOS_USHOP2), name );
		multiText.AddString( strTemp, RGB(180, 180, 252) );
//		multiText.AddString( strTemp, RGB(252, 180, 180) );
		// ���ڿ��� ������� ������ �����鼭 ���.
		// ���ڿ��� ���̸� 15���� 35�� �÷����� [2/21/2007 Theodoric]
		multiText.AddStringMulti( (char*)ment, 15, TRUE, RGB(255, 251, 115) );
		pUserShopNpc->m_pCrash_MissPopup[0]->PutString(&multiText, TRUE);
	}

	//========================================================================================
	//AddColorKeyMap( pUserShopNpc->m_wColorIdx ,MasterIndex , 2 , pUserShopNpc );
	AddUserShopNpc(pUserShopNpc);
}

void CUIMgr::DeleteUserShopNpc( int NpcIndex ) ///��������
{
	DelUserShopNpc(NpcIndex);
}

void CUIMgr::AddPet(int id, char *name, int pet_class, float x, float z, float dir, int vital,
					int horn, int head, int body, int wings, int legs, int tail, BOOL bMeta)
{
	if( name == NULL )
		return;

	CNkPet *pPet;

	pPet = new CNkPet(g_ClrAlloc);
	pPet->m_bPet = TRUE;
	pPet->SetMetaPet(bMeta);
	pPet->SetInitPos(x, z, dir);
	//pPet->SetInfo(-1, -1, 0);		// 0�� stand
	pPet->m_nVirId = id;
	pPet->m_PetClass = pet_class;
	pPet->m_Vital = vital;
	pPet->m_AttackVital = vital;
	pPet->SetBody(horn, head, body, wings, legs, tail);
	pPet->SetName(name);
	pPet->SetMotionState(PET_STAND);

	//AddColorKeyMap( pPet->m_wColorIdx , id ,  3, pPet );
	AddPet(pPet);
	g_nPetInNum = m_pet_map.size();
}

// -------------------------------------------------------------------
// Name : DeletePlayer()
// Desc : �÷��̾ ����Ʈ���� �����Ѵ�.
// ------------------------------------------------------------------
void CUIMgr::DeletePet(int id)
{
	DelPet(id);
	g_nPetInNum = m_pet_map.size();
}

// -------------------------------------------------------------------
// Name : AddItem()
// Desc : �������� ��Ÿ����.
// ------------------------------------------------------------------
void CUIMgr::AddItem(int item_index, int vnum, float x, float z, float dir, int gem_num, int special, int special2, BOOL bTimeItem, BOOL bDrop) ///�Ź���ȭ�ý���
{
	int proto_num = g_ItemList.FindItem(vnum);
	if (proto_num >= 0)
	{
		CItemInfo *pItemInfo;

		pItemInfo = new CItemInfo();
		pItemInfo->m_Item.SetColorAlloc(g_ClrAlloc);
		pItemInfo->m_Item.SetInitPos(x, z, dir);
		pItemInfo->m_Item.SetInfo(item_index, vnum, proto_num);
		if (gem_num > 0)
		{
			if(g_ItemList.m_ItemArray[proto_num].m_MinLevel>=181)
				pItemInfo->m_Item.SetDiaGemNum(gem_num);
			else
				pItemInfo->m_Item.SetGemNum(gem_num);
		}
		pItemInfo->m_Item.m_Special = special;
		pItemInfo->m_Item.m_Special2 = special2; ///�Ź���ȭ�ý���

		if (bDrop)
			pItemInfo->m_Item.Drop();

		pItemInfo->m_TextOutBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR, (int) 0, (int) 0, -1, -1, TRUE);
		pItemInfo->m_TextOutBox.SetVisible(TRUE);

		pItemInfo->m_TextOutBox_Active.Init(PLAYERNAME_FONTSIZE, NAME_ACTIVECOLOR, (int) 0, (int) 0, -1, -1, TRUE);
		pItemInfo->m_TextOutBox_Active.SetVisible(TRUE);

		pItemInfo->m_bActive = FALSE;

		if(pItemInfo->m_Item.m_Vnum == 1014 || pItemInfo->m_Item.m_Vnum == 1239)   // ���� ������ �ѹ� 1014 ��...// ���� ������ �ѹ� 1014 ��...
		{
			char LaimName[50] = {0,};
			sprintf(LaimName, "%d %s", pItemInfo->m_Item.m_Special, GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));
			pItemInfo->m_TextOutBox.SetString(LaimName, RGB(251, 218, 8));
			pItemInfo->m_TextOutBox_Active.SetString(LaimName, RGB(0, 255, 255));
		}
		else if(pItemInfo->m_Item.m_Vnum == 1307) //mungmae-2005/10/5 �°�&����Ӵ� ����
		{
			char strGameMoneyName[50] = {0,};
			int nGameMoneyPrice;
			nGameMoneyPrice = pItemInfo->m_Item.m_Special / 10000;
			sprintf(strGameMoneyName, G_STRING(IDS_LHSTRING1781) , GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum), nGameMoneyPrice);
			pItemInfo->m_TextOutBox.SetString(strGameMoneyName, RGB(251, 218, 8));
			pItemInfo->m_TextOutBox_Active.SetString(strGameMoneyName, RGB(0, 255, 255));
		}
		else if( GET_TYPE_REF(pItemInfo->m_Item) == ITYPE_SUB )
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName);
			pItemInfo->m_TextOutBox_Active.SetString(strName);
		}
		else if( GET_TYPE_REF(pItemInfo->m_Item) == ITYPE_ETC
				 && ( GET_SHAPE_REF(pItemInfo->m_Item) == IETC_RECOVERY
					  || GET_SHAPE_REF(pItemInfo->m_Item) == IETC_BUFF )
			   )
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName);
			pItemInfo->m_TextOutBox_Active.SetString(strName);
		}
		else if (pItemInfo->m_Item.m_PlusNum > 0)
		{
			char strName[50];
			sprintf(strName, "%s +%d", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum),
					pItemInfo->m_Item.m_PlusNum);

			pItemInfo->m_TextOutBox.SetString(strName, UPGRADE_ITEM_COLOR_REF);
			pItemInfo->m_TextOutBox_Active.SetString(strName, NAME_ACTIVECOLOR);
			//m_AltNameBox[m_DropItemAllCnt]->SetString(strName, UPGRADE_ITEM_COLOR_REF);
		}
		else if (pItemInfo->m_Item.m_Special > 0)
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName,
											  SPECIAL_ITEM_COLOR_REF);
			pItemInfo->m_TextOutBox_Active.SetString(strName,
					NAME_ACTIVECOLOR);
		}
		else if (pItemInfo->m_Item.m_Special2 > 0)
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName,
											  SPECIAL_ITEM_COLOR_REF);
			pItemInfo->m_TextOutBox_Active.SetString(strName,
					NAME_ACTIVECOLOR);
		}
		// �̰��� m_Special2 �� �������� ���ڻ��� �ٲ��ִ� ��ƾ�� �߰��ؾ��Ѵ�. �׷��� m_Special2������ �� ����ġ�� ���� üũ�ؾ���. ///�Ź���ȭ�ý���
		else
		{
			char strName[50];
			sprintf(strName, "%s", GET_ITEM_NAME_VNUM(pItemInfo->m_Item.m_Vnum));

			pItemInfo->m_TextOutBox.SetString(strName);
			pItemInfo->m_TextOutBox_Active.SetString(strName);
		}

		// �ð��� ������ �� "���ѵ� " ���ڸ� �ٿ��ش�. ���� ��ƾ�� �ִ��� �Ȱǵ帮�� ���� ��Ʈ���� �ٽ� �޾Ƽ� �ٽ� SetString�� ���ش�.
		if( bTimeItem )
		{
			pItemInfo->m_Item.m_bTimeLimit = bTimeItem;

			char strTemp2[50];

			//-- IDS_TIMELIMIT_ITEM_TITLE : ���ѵ�
			sprintf( strTemp2, "%s %s", G_STRING(IDS_TIMELIMIT_ITEM_TITLE), pItemInfo->m_TextOutBox.m_str ); // �̸� �տ� ������ �߰�.

			pItemInfo->m_TextOutBox.SetString( strTemp2, RGB(230,230,230) );
			pItemInfo->m_TextOutBox_Active.SetString( strTemp2, NAME_ACTIVECOLOR );
		}

		//AddColorKeyMap( pItemInfo->m_Item.m_wColorIdx , item_index , 4 , pItemInfo );
		AddItemInfo(pItemInfo);
		g_nItemListNum = m_iteminfo_map.size();
	}
}


// -------------------------------------------------------------------
// Name : DeleteItem()
// Desc : �������� ����Ʈ���� �����Ѵ�.
// ------------------------------------------------------------------
void CUIMgr::DeleteItem(int item_index)
{
	DelItemInfo(item_index);
	g_nItemListNum = m_iteminfo_map.size();
}

void CUIMgr::AddPlayerTest()
{
	AddMob(39, -1, g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_dir, 0);
	AddMob(40, -4, g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_dir, 0);
	AddMob(41, -3, g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_dir, 0);
	AddMob(42, -5, g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_dir, 0);
	AddMob(43, -2, g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_dir, 0);

	CNkMob *pMob = NULL;

	if( pMob = GetMobByID(-1) )
	{
		if (pMob->IsMoving() == FALSE)
		{
			pMob->SetMotionState(MOB_MOVE);
			pMob->Move(pMob->m_wx+50, pMob->m_wz-50);
		}
	}

	if( pMob = GetMobByID(-2) )
	{
		if (pMob->IsMoving() == FALSE)
		{
			pMob->SetMotionState(MOB_MOVE);
			pMob->Move(pMob->m_wx+70, pMob->m_wz);
		}
	}
}

void CUIMgr::DeletePlayerTest()
{
	DelMob(-1);
	DelMob(-2);
	DelMob(-3);
	DelMob(-4);
	DelMob(-5);
}

void CUIMgr::AttackTest()
{
	CNkMob *pMob1 = NULL, *pMob2 = NULL, *pMob;
	float dist1, dist2;

	pMob1 = GetMobByID(-1);
	pMob2 = GetMobByID(-2);

	if (pMob1 != NULL && pMob2 != NULL)
	{
		dist1 = DistPlToPl(g_pRoh->m_wx, g_pRoh->m_wz, pMob1->m_wx, pMob1->m_wz);
		dist2 = DistPlToPl(g_pRoh->m_wx, g_pRoh->m_wz, pMob2->m_wx, pMob2->m_wz);

		if (dist1 < dist2)
			pMob = pMob1;
		else
			pMob = pMob2;

		if (pMob->IsAttacking())
			pMob->SetMotionState(MOB_STAND);
		else
			pMob->Attack(g_pRoh->m_wx, g_pRoh->m_wz);
	}
}


// �������� �����Ǵ� �����쿡���� �˻��� �ǽ��Ѵ�.
// ���Ŀ� ���Ӱ� ���� Ŭ�����z ���⿡ ����ؾ� �Ѵ�..<-------------�ָ�!!
BOOL CUIMgr::Check_All_RealtimeBox()
{
	if(m_pScrollBox || m_pChSexBox  || m_pDelivBox || m_pChangeHair || m_pWarTax  || m_pWarTax || m_pPetShop
			|| m_pPetKeep || m_pWarReq    || m_pGuildWar || m_pMatList || m_pMatMakeRoom /*|| m_pBattleUI*/
			|| m_pTeleportItem || m_pLowGuildMaster || m_pGuildHunt || m_pReservationWindow )
		return TRUE;

	else
		return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// Name : ProcessFrame()
// Desc : �����Ӹ��� ��� ���۸� �а� ����� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////
void CUIMgr::ProcessFrame()
{	
	float dx, dz;

	// �񵿱� Ű���� ���� üũ.
	if (pCMyApp->IsActiveApp())
	{
		if( g_pNk2DFrame->IsProcLock() )
		{

		}
		else if( !Check_All_RealtimeBox() )
		{
			if( g_SvrType == ST_ADULT_ONLY )
			{
				if( g_pNk2DFrame && !g_pNk2DFrame->GetTgaUIWindow()->IsOpenWindow(WINDOW_TGA_WANTED_REGISTER) )
				{
					CheckKeyEvent();
				}
			}
			else
			{
				if( g_pNk2DFrame && g_pNk2DFrame->GetUIWindow()
					&& !g_pNk2DFrame->Check_All_MsgPopUp()
					&& (!g_pNk2DFrame->IsControlGuildManage()
					&&  !g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_GUILD_SEARCH)
					&&  !g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_GUILD_BATTLE_INVASION)
					&&  !g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_GUILD_BATTLE_INVASION_INFO )
					//&&  !g_pNk2DFrame->IsControlGuild())
					))
				{
					CheckKeyEvent();
				}
			}
		}

	}

	TraceMouseState();	// ���ΰ� ĳ���� �̵��� ���õ� ó��.

	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_dwVk1KeyTime = timeGetTime();
	}

	int cur_skill = g_pNk2DFrame->GetRSkill();

	// ����� ����
	if( cur_skill > 0
			&& ( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_HANDLE
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_MAGIC_MOVE
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_VANPIRE_TOUCH
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_HELL_TOUCH
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_DEEP_ATTACK
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_CHAIN_ATTACK ) )
		TraceRMouseState();//1118

	if( g_pTcpIp != NULL )
	{
		ReadMessages();
	}

	SpeedChecker::GetInstance()->FrameMove();

	if( g_bPath == TRUE && m_bOnBattle == TRUE )
	{
		RecalPath();
	}

	// �÷��̾� ��ŷ �׽�Ʈ �ڵ�.
	CNkCharacter *pCha = NULL;

	if( pCha = GetCharacterByID( -1) )
	{
		if (DistPlToPl(pCha, g_pRoh) >= 100.0f)
		{
			dx = (g_pRoh->m_wx - pCha->m_wx);
			dz = (g_pRoh->m_wz - pCha->m_wz);

			pCha->SetMotionState(CHA_WALK);
			pCha->Move(g_pRoh->m_wx-dx/5.0f, g_pRoh->m_wz-dz/5.0f);
		}
	}
	// // �÷��̾� ��ŷ �׽�Ʈ �ڵ� ��

	// �� ��ŷ �ڵ�

	CNkMob *pMob;
	if( pMob = GetMobByID(-1) )
	{
		if (DistPlToPl(pMob->m_wx, pMob->m_wz, g_pRoh->m_wx, g_pRoh->m_wz) >= 50.0f)
		{
			if (!pMob->IsMoving())
			{
				dx = (g_pRoh->m_wx - pMob->m_wx);
				dz = (g_pRoh->m_wz - pMob->m_wz);
				pMob->Move(g_pRoh->m_wx-dx/5.0f, g_pRoh->m_wz-dz/5.0f);
			}
		}
	}
	if( pMob = GetMobByID(-2) )
	{
		if (DistPlToPl(pMob->m_wx, pMob->m_wz, g_pRoh->m_wx, g_pRoh->m_wz) >= 50.0f)
		{
			if (!pMob->IsMoving())
			{
				dx = (g_pRoh->m_wx - pMob->m_wx);
				dz = (g_pRoh->m_wz - pMob->m_wz);
				pMob->Move(g_pRoh->m_wx-dx/5.0f, g_pRoh->m_wz-dz/5.0f);
			}
		}
	}

	// ��Ÿ.
	if (m_bNextAction)
	{
		if (!pCMyApp->IsHeroMoving())
		{
			m_bNextAction = FALSE;
			if (m_Action.nActionKind == 0)  	// nActionKind�� 0�̸� Send
			{
				g_pTcpIp->SendNetMessage(m_Action.strCmd);

				// ��Ŷ�� ������ ���ÿ� pick�� �õ� �ߴٴ� �÷��׸� ����( by ���� )
				m_bPickLock = TRUE; // m_Action.nActionKind == 0�̸� ������ �̵��� �ݱ⸦ �ǹ��Ѵ�. �� ������ �� �÷��׸� �����ؾ� �����̴�. ///pick_bug
			}
		}
	}
	// [5/7/2008 �����] �±� ���� ���� �̺�Ʈ �Ҿƹ��� Ŭ�� üũ
	if( m_bPocketPapa_Click )
	{
		m_papaClickTime++;
	}

	if( m_papaClickTime > 170.0f )
	{
		m_bPocketPapa_Click = FALSE;
		m_papaClickTime = 0.0f;
	}


	if( m_bAutoHunt )
		m_AutoPlay->AutoProc();
}


//////////////////////////////////////////////////////////////////////////
// [6/7/2007 Theodoric] ����Ű�� ��� ����ó�� ��ƺ���.

bool CUIMgr::IsCheckKeyUsed()
{
	// by evilkiki �ӽ�
	{
		if( g_pNk2DFrame->IsVisiblePremiumExchange())
		{
			return false;
		}

		if( g_pNk2DFrame->GetUIWindow()->IsOpenWindow( WINDOW_GUILD_CREATE) )
		{
			// ��� â����
			CGuildCreate* pGuildCreateWindow = (CGuildCreate*)g_pNk2DFrame->GetUIWindow()->GetWindow( WINDOW_GUILD_CREATE);

			if( pGuildCreateWindow->m_GuildName.GetEnable() )
				return false;
		}

		if( g_pNk2DFrame->GetUIWindow()->IsOpenWindow( WINDOW_GUILD_BATTLE_INVASION) )
		{
			CBattleInvasionAttack* pBattle_IA = (CBattleInvasionAttack*)g_pNk2DFrame->GetUIWindow()->GetWindow( WINDOW_GUILD_BATTLE_INVASION);

			if( pBattle_IA->IsTextBoxFocus() )
				return false;
		}

		if( g_pNk2DFrame->GetUIWindow()->IsOpenWindow( WINDOW_GUILD_SEARCH) )
		{
			CGuildSearch* pGuildSerch = (CGuildSearch*)g_pNk2DFrame->GetUIWindow()->GetWindow( WINDOW_GUILD_SEARCH);

			if( pGuildSerch->IsFocus() )
				return false;
		}

		if( g_pNk2DFrame->IsVisibleTakebox() == TRUE )
		{
			LHUI_TakeBox* pTakeBox = g_pNk2DFrame->GetTakeOutBox();
			
			if( pTakeBox->IsFocus() )
				return false;
		}

		if( g_pNk2DFrame->IsControlGuildManage() )
		{
			// ��� ������ ��Ŀ���� �ִٸ� (�Է����̶��) ����Ű�� ���´�.
			if( g_pNk2DFrame->GetControlGuildManage()->m_pNoticeInfo->IsFocus() )
			{
				return false;
			}

			// ��� �ӿ� ���濡 ��Ŀ���� �ִٸ� (�Է����̶��) ����Ű�� ���´�.
			else if( g_pNk2DFrame->GetControlGuildManage()->m_pJob->IsFocus() )
			{
				return false;
			}

			// ��� ��޸� ���濡 ��Ŀ���� �ִٸ� (�Է����̶��) ����Ű�� ���´�.
			else if( g_pNk2DFrame->GetControlGuildManage()->m_pGradeName->IsFocus() )
			{
				return false;
			}
		}
	}

	if (g_pNk2DFrame->GetControlBottom()->HasFocus()
			|| pCMyApp->IsSoccerZone()
			|| m_bModal)
		return false;

//	if( IsEventScenePlaying() ) // �̺�Ʈ ���� �÷������̸� ĵ�� ���δ�. ���⸦ ĵ���Կ��� ä���� �� �Ŵ�. ///�δ�1 �� �߰� ///Ʃ�丮��� ����
//		return;

	// �� ���� �˻��� �Է½õ� �Է¾ȵǵ��� ...(07-09-03 ����) ///�굵��Ȯ��
	if( g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet()->m_SearchInput.GetEnable() ) // �Է����̸�...
		return false;

	// �����Է��� ����Ű �νľȵǰ� ó��...(07-07-13 ����)
	if( g_pNk2DFrame->IsAutoMouseVisible() && g_pNk2DFrame->GetAutoMouse()->m_pTextIn->GetEnable() )
		return false;

	if(m_bIsScrollBox)
		return false;

	if( !m_pNkKeyboard )
		return false;

	// ���λ��� ��Ʈ �Է½õ� ������ �Է¾ȵǵ��� ...(05-10-29 ����) ///���λ���
	if( g_pNk2DFrame->IsUserShopVisible() && g_pNk2DFrame->GetControlUserShop()->m_ShopMentText.GetEnable() ) // ��Ʈ �Է����̸�...
		return false;

	// ���λ����˻���  �Է½õ� ������ �Է¾ȵǵ��� ...(06-12-08 ����) ///���λ���
	if( g_pNk2DFrame->IsUserShopSearchVisible() && g_pNk2DFrame->GetUserShopSearch()->m_SearchNameInput.GetEnable() )
		return false;

	// �Է±�� �˾��� ���������� ������ �ȴ������� ó��....(06-10-11 ����)
	if( g_pNk2DFrame->IsPopUpTyping() )
		return false;

	if( g_pNk2DFrame->m_Popup)
		return false;

	// ���� ��ũ�� ��忡�� ���� �Է��߿� ������ �Ƚ�������.
	if( g_pNk2DFrame->GetLShiftMenu()->m_pControlMacro && g_pNk2DFrame->GetLShiftMenu()->m_pControlMacro->m_bNowInput )
		return false;
	
	if( g_pNk2DFrame->IsFriendVisible() && g_pNk2DFrame->GetFriend()->IsFocus() )
		return false;

	if( g_pNk2DFrame->IsInterfaceVisible(LOTTO) && 
		((ControlLotto*)(g_pNk2DFrame->GetInterface(LOTTO)))->IsFocus() )
		return false;

	if( g_pNk2DFrame->IsInterfaceVisible(LETTER_SEND) && 
		((ControlLetterSend*)(g_pNk2DFrame->GetInterface(LETTER_SEND)))->IsFocus() )
		return false;

	if( m_pGmMacro && m_pGmMacro->IsVisible() )
		return false;

	return true;

}



////////////////////////////////////////////////////////////////////////////
// Name : CheckKeyEvent()
// Desc : ��� ���۸� �а� ����� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////


void CUIMgr::CheckKeyEvent()
{
	if( !IsCheckKeyUsed() )
		return;

	// �߿�.
	// Ű���� üũ Ŭ������ �����̴ϱ�..
	// ���� � Ű�� ���ȴ��� ���Ӱ� �߰��� �ҷ��� �Ѵٸ�

	// CheckUIMgrKey()�� �����Ͽ��� �Ѵ�.
	m_pNkKeyboard->CheckUIMgrKey();

	BOOL b1, b2;

	if (g_pNk2DFrame->IsPVPVisible() == FALSE) //������� �ÿ��� ����Ű�� ��Ȱ��ȭ
	{
		if ( (b1 = m_pNkKeyboard->IsPressed(NK_I)) && (b2 = m_pNkKeyboard->IsStateChanged(NK_I)))
		{
			g_pNk2DFrame->ToggleInvenWindow();
			return;
		}

		if (m_pNkKeyboard->IsPressed(NK_C) && m_pNkKeyboard->IsStateChanged(NK_C))
		{
			g_pNk2DFrame->ToggleInterfaceWindow(SCORE);
			return;
		}

		if (m_pNkKeyboard->IsPressed(NK_R) && m_pNkKeyboard->IsStateChanged(NK_R))
		{
//================================================================================
			// nate 2004 - 5
			// ��ī���� �����߿� ũ����Ż�� �����ϸ� �ȱ��� ���� �ȵ�
			// ITS #9596 ���Ϸ� ������������ ���� ���� by.Sol9 [2012.06.15]
			if( pCMyApp->m_pUIMgr->m_byOnBattleDecardi )
			{
				if( !g_pRoh->m_bCrystalOwner )
					g_pRoh->ToggleMovingState();
			}
			else
				g_pRoh->ToggleMovingState();
			return;
//================================================================================
		}

		if (m_pNkKeyboard->IsPressed(NK_T) && m_pNkKeyboard->IsStateChanged(NK_T))
		{
			g_pNk2DFrame->ToggleSkillWindow();
			return;
		}

		if (m_pNkKeyboard->IsPressed(NK_M) && m_pNkKeyboard->IsStateChanged(NK_M))
		{
			g_pNk2DFrame->ToggleInterfaceWindow(MAP);
			return;
		}

		if(m_pNkKeyboard->IsPressed(NK_G) && m_pNkKeyboard->IsStateChanged(NK_G) )
		{
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;

			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;

			if( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) && (!Check_All_RealtimeBox())
					&& (g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) && g_MatrixSvr == 0 )
				g_pNk2DFrame->ToggleControlGuildWindow();

			return;
		}

		if(m_pNkKeyboard->IsPressed(NK_H) && m_pNkKeyboard->IsStateChanged(NK_H) )
		{
			//  [4/24/2009 ppmmjj83] �Ϻ���û�� ���� �İ����� ���Ƶд�
			if( g_dwClientCountry == CTRY_JPN ) return;

			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;
			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;
			if( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) &&
					(!Check_All_RealtimeBox()) &&
					(g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) &&
					g_MatrixSvr == 0)
				g_pNk2DFrame->ToggleHelperWindow();
			//g_pNk2DFrame->ToggleWareHouseWindow();
			return;
		}
		if(m_pNkKeyboard->IsPressed(NK_E) && m_pNkKeyboard->IsStateChanged(NK_E) )
		{
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;
			//wan:2005-02	�׺��� �κ�â ���� ����
			if (g_pNk2DFrame && g_pNk2DFrame->GetGamble()->m_bGambleStart)
				return ;
			//mungmae-2005/05/12 ������ ���� ������ ���� ��ȯ��ư�� �������� 'E'����
			if (g_pNk2DFrame && g_pNk2DFrame->GetControlExchange()->m_ExgBtn2.GetState() == BTN_DOWN)
				return ;
			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;
			if ( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) &&
					(!Check_All_RealtimeBox()) &&
					(g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) )
				g_pNk2DFrame->ToggleExchangeWindow();
			return;
		}


		if(m_pNkKeyboard->IsPressed(NK_U) && m_pNkKeyboard->IsStateChanged(NK_U) )
		{
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;
			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;
			if ( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable())
					&& (!Check_All_RealtimeBox())
					&& (g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) )
			{
				((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->QuestMessage();
				g_pNk2DFrame->ToggleInterfaceWindow(QUEST);
			}
			return;
		}

		if(m_pNkKeyboard->IsPressed(NK_V) && m_pNkKeyboard->IsStateChanged(NK_V) )
		{
			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;
			if(!g_pNk2DFrame->GetControlBottom()->m_bViewFunctionList)
				g_pNk2DFrame->GetControlBottom()->m_bViewFunctionList= TRUE;
			else
				g_pNk2DFrame->GetControlBottom()->m_bViewFunctionList= FALSE;
			return;
		}

		if(m_pNkKeyboard->IsPressed(NK_P) && m_pNkKeyboard->IsStateChanged(NK_P) )
		{
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;
			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;
			if( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) &&
					(!Check_All_RealtimeBox()) &&
					(g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()))
				g_pNk2DFrame->TogglePartyWindow();
			return;
		}

		if(m_pNkKeyboard->IsPressed(NK_O) && m_pNkKeyboard->IsStateChanged(NK_O) )
		{
			if(pCMyApp->IsSoccerZone())	// nate 2006-05-15 : ��Ʈ���� ������ ����� - �������̽� ��Ȱ��ȭ
				return ;
			if (g_pNk2DFrame->IsPVPVisible() == TRUE)
				return ;
			if ( (!g_pNk2DFrame->GetControlBottom()->m_InputBox.GetEnable()) && (!Check_All_RealtimeBox())
					&& (g_pNk2DFrame && !g_pNk2DFrame->Check_All_MsgPopUp()) )
			{
				switch (g_MyPetStatus.mode)
				{
				case MYPET_MODE_NONE:
					// IDS_TOP_PET_NOTEXIST : ����� �ֿϵ����� �⸣�� ���� �ʽ��ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_TOP_PET_NOTEXIST),TYPE_NOR_OK, 1);
					break;
				case MYPET_MODE_EGG:
					// IDS_TOP_PET_NOTYET : ����� �ֿϵ����� ���� ��ȭ���� �ʽ��ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_TOP_PET_NOTYET),TYPE_NOR_OK, 1);
					break;
				case MYPET_MODE_KEEP:
					// IDS_TOP_PET_KEEPING : ����� �ֿϵ����� ���� ���������Դϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_TOP_PET_KEEPING),TYPE_NOR_OK, 1);
					break;
				case MYPET_MODE_HOLD:
					g_pNk2DFrame->TogglePetStatusWindow();
					break;
				default:
					g_pNk2DFrame->TogglePetStatusWindow();
					break;
				}
			}
			return;
		}

		if(m_pNkKeyboard->IsPressed(NK_Z) && m_pNkKeyboard->IsStateChanged(NK_Z) )
		{
			if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_FINALBOSS  ) // ������ �ȿ����� �� �� �ִ�.
				g_pNk2DFrame->ToggleHeroFinalRankWindow();
			return;
		}

	}



	if (m_pNkKeyboard->IsPressed(NK_W))
	{
	}

	if (m_pNkKeyboard->IsPressed(NK_S))
	{
	}

	if (m_pNkKeyboard->IsPressed(NK_A))
	{
	}

	if (m_pNkKeyboard->IsPressed(NK_D))
	{

	}

	if( m_pNkKeyboard->IsPressed(NK_F) )
	{

	}

	if (m_pNkKeyboard->IsArrowPressed(NK_LEFT))
	{
		//pCMyApp->RotateCloud();
		pCMyApp->RotateLeft();
	}

	if (m_pNkKeyboard->IsArrowPressed(NK_UP))
	{
	}

	if (m_pNkKeyboard->IsArrowPressed(NK_RIGHT))
	{
		//pCMyApp->RotateCloud();
		pCMyApp->RotateRight();
	}

	if (m_pNkKeyboard->IsArrowPressed(NK_DOWN))
	{
	}
}

////////////////////////////////////////////////////////////////////////////
// Name : TraceMouseState
// Desc : ĳ���Ͱ� �̵��߿� ���� ���콺�� ������ ������, �̵� ������ �ٲ� ���ΰ� ��
// ���ΰ��� ���ϴ� ��.. ����..
// ���콺�� ������ �ۿ� ������..
// ���콺�� .......
////////////////////////////////////////////////////////////////////////////
void CUIMgr::TraceMouseState()
{
	DWORD dwCurTime;
	static DWORD dwPrevTime;
	POINT pt;
	D3DVECTOR ptVec;

	dwCurTime = timeGetTime();
///2003 0925 ��ȭ�϶��� �����̸� �ȵȴ�...
	if(g_pRoh->m_CancelState)
	{
		if( g_pRoh->m_ChaCondition==CONDITION_STONY ||
				g_pRoh->m_ChaCondition==CONDITION_ENTANGLE)	//��ȭ:1
			return;
	}

	// ���콺�� LBUTTON�� ������ ���� �ʴٸ�, �����Ѵ�.
	if ( (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 0 : 1)
	{
		m_dwElapsedTime = 0;
		dwPrevTime = dwCurTime;
		m_bMouseDown = FALSE;
		return;
	}

	// m_bMouseDown �� TRUE��� ���� Viewport������ ���콺�� ���ȴٴ� ���̴�.
	if (!m_bMouseDown)
		return;

	// ���ݱ��� �帥 �ð��� Ȯ���Ѵ�.
	m_dwElapsedTime += (dwCurTime - dwPrevTime);
	dwPrevTime = dwCurTime;

	if (m_dwElapsedTime >= 500 && g_pRoh->IsShown())
	{
		// ���ΰ��� �׾��������� �̵� �޼����� ���� �ʴ´�.
		if (g_pRoh->IsDead() || g_pRoh->IsCantMove())
			return;
		GetCursorPos(&pt);
		ScreenToClient(m_hWnd, &pt);

		// ���Ӱ� �̵��� ��ġ�� ���Ѵ�.
		if (m_pLand->PickPoint(ptVec, pt.x, pt.y) == TRUE) 				// ���콺�� ���� �Ϻκ��� �����.
		{
			if (WhatColorOnPick(pt.x, pt.y) == 0)
			{
				if (g_bPath)
					pCMyApp->MoveHeroT(ptVec.x, ptVec.z);
				else
					pCMyApp->MoveHero(ptVec.x, ptVec.z);
			}
			m_dwElapsedTime = 0;
		}
	}
}

///1118  �ڵ������߿� ���콺 ��Ŭ�� ����(!)�� ������� �������� �ǰ� ��...
void CUIMgr::TraceRMouseState()
{
	DWORD dwCurTime;
	static DWORD dwPrevTime;
	//POINT pt;
	D3DVECTOR ptVec;

	dwCurTime = timeGetTime();

	// ���콺�� RBUTTON�� ������ ���� �ʴٸ�, �����Ѵ�.
	if ( (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 0 : 1)
	{
		m_dwRbuttonElapsedTime = 0;
		dwPrevTime = dwCurTime;
		m_bRMouseDown = FALSE;
		return;
	}

	if (!m_bRMouseDown)
		return;

	// ���ݱ��� �帥 �ð��� Ȯ���Ѵ�.
	m_dwRbuttonElapsedTime += (dwCurTime - dwPrevTime);
	dwPrevTime = dwCurTime;

	if (m_dwRbuttonElapsedTime >= 500 )
	{
		//�̰��� �ൿ�� ���´�.
		MouseDown(0, 0, 0, BUTTON_RIGHT);//
		m_dwRbuttonElapsedTime = 0;
	}
}

void CUIMgr::ReadMessages()
{
	int len = 0;

	if( g_pTcpIp != NULL )
	{
		len = g_pTcpIp->ReadMessage();
	}

	if( len < 0 )
	{
		if( pCMyApp->IsBeforeGoWorld() == TRUE )
		{
			return;
		}

		if( g_pNk2DFrame->FindPopup(4) == NULL )
		{
			// IDS_UIMGR_BREAK_CONNECTION : ���������� ���������ϴ�.
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_UIMGR_BREAK_CONNECTION), TYPE_NOR_OK, 4 );

			if( m_AutoPlay && m_AutoPlay->IsRun() )
			{
				m_AutoPlay->_OnInterrupt(LagRush_Interrupt__Disconnect_Server);
			}
		}
	}

	RecvPacketMgr* packMgr = RecvPacketMgr::GetInstance();
	PacketProcMgr* procMgr = PacketProcMgr::GetInstance();
	char* pp = NULL;
	char buf[MAX_RECV_BUF_LEN] = {0,};
	while( pp = packMgr->PopPacket() )
	{
		stPacketHeader* pHeader = reinterpret_cast<stPacketHeader*>(pp);

		if( pHeader->size_ > sizeof(buf) )
		{
			continue;
		}

		g_pTcpIp->decrypt(&pp[PACKET_HEADER_SIZE], pHeader->size_);

		stPacketSubHeader* pSub = reinterpret_cast<stPacketSubHeader*>(&pp[PACKET_HEADER_SIZE]);
		if( pSub->msg.type_ != 0 )
		{
			rnPacket::SP packet(new rnPacket(pHeader->size_ + PACKET_HEADER_SIZE));
			memcpy(packet->header(), pp, pHeader->size_ + PACKET_HEADER_SIZE);
			procMgr->Excute(packet);

			continue;
		}

		stPacketSubHeader shd;
		memcpy(&shd, &pp[PACKET_HEADER_SIZE], PACKET_SUB_HEADER_SIZE);

		int bodySize = pHeader->size_ - PACKET_SUB_HEADER_SIZE;

		memset(buf, 0, sizeof(buf));
		memcpy(buf, &pp[ALL_PACKET_HEADER_SIZE], bodySize);		
		buf[bodySize] = '\0';

		std::string strTok = buf;		
		tokenizer tok(strTok, sep);
		tokenizer::iterator iter = tok.begin();
		tokenizer::iterator endIter = tok.end();

		for( ; iter != endIter; ++iter)
		{
			std::string oneSentence = (*iter);
			if( oneSentence.length() <= 0 )
				continue;

			memset(buf, 0, sizeof(buf));
			memcpy(buf, oneSentence.c_str(), oneSentence.length());
			buf[oneSentence.length()] = '\0';

			if( g_bWndNetMessage )
			{
				G_DevAddLogNetwork(buf,"--");
			}

			ProcessOneSentence(buf);
		}		
	}
}

void CUIMgr::ProcessOneSentence(char *msg)
{
	static char cmd[100];

	msg = AnyOneArg(msg, cmd);
	m_pCmd->Run(cmd, msg);

	return;
}

CNkMob* CUIMgr::FindMobById(int id)
{
	return GetMobByID(id);
}

CUserShopNpc* CUIMgr::FindUShopNpcById( int id ) ///��������
{
	return GetUserShopNpcByID(id);
}

CNkPet* CUIMgr::FindPetById(int id, BOOL with_my)
{
	if (with_my && pCMyApp->m_pMyPet && pCMyApp->m_pMyPet->m_nVirId == id)
		return (CNkPet *) pCMyApp->m_pMyPet;

	return GetPetByID(id);
}

// nate
CNkCharacter* CUIMgr::FindChaById(int id, BOOL with_me)
// ���� : ĳ���� ���̵�, with_me = true �⺻����
// ����Ƽ���Ͽ� ���� ����Ƽ ĳ������ ��ȯ.
{
	// pCMyApp�� �۷ι��̴�..g_ �� �Ⱥ��̴ٴ�..��.��;;
	if (with_me && g_pRoh && g_pRoh->m_nCharIndex == id)
		return g_pRoh;

	return GetCharacterByID(id);
}

CDecoObj* CUIMgr::FindDecoObjByColorIdx(WORD colorIdx)
{
	CDecoObj *pDecoObj = NULL;
	list<CDecoObj *>::iterator prDeco;
	D3DVECTOR vPos;
	int w_pos, h_pos, h, w;

	// ȭ���� �߽�(ī�޶� ���� �ִ� ���� ã�´�.)
	pCMyApp->GetEyeAtPos(vPos);

	w_pos = (int) vPos.x;
	h_pos = (int) vPos.z;

	w_pos /= g_nMapCellWidth;
	h_pos /= g_nMapCellHeight;

	for (h = h_pos - 2; h <= h_pos+2; h++)
	{
		if (h < 0 || h >= g_nMapCellHeightCount)	// �� ������ ����°� Ȯ��.
			continue;
		for (w = w_pos-2; w <= w_pos+2; w++)
		{
			if (w < 0 || w >= g_nMapCellWidthCount)
				continue;
			for (prDeco = g_listDecoObj[h][w].begin(); prDeco != g_listDecoObj[h][w].end(); prDeco++)
			{
				pDecoObj = *prDeco;

				if (pDecoObj->m_wColorIdx == colorIdx)
					return pDecoObj;
			}
		}
	}

	return NULL;
}

// ���� �޼���
// 2005.01.26
// Lyul / �߰� / Command
// ii[5]���� �߰�. - ����ũ�� ���̽�Ʈ ������ ��� mb_haste �� ���� Render �� �ø���.
void CUIMgr::CmdAttack(char *msg)
{
	// ���Ἲ Check
	if (msg == NULL)
		return;

	int ii[9] = {0,};
	char second_arg[20] = "", third_arg[20] = "";//, first_arg[20], fourth_arg[20];
	CNkCharacter *pCha = NULL, *pCha2 = NULL;
	CNkMob *pMob = NULL;
	CNkMob *pMob2 = NULL;
	CNkPet *pPet = NULL, *pPet2 = NULL;

	// Pick Message
	sscanf(msg, "%s %d %s %d %d %d %d %d %d", second_arg, &ii[0], third_arg, &ii[1], &ii[2], &ii[3],&ii[4] ,&ii[5], &ii[6] );

	// From ĳ��
	if (!strncmp(second_arg, "c", 1))
	{
		// To ĳ��
		if (!strncmp(third_arg, "c", 1))
		{
			// player to player
			// nate 2005-06-17 : ��ƾ ���� - ĳ���� ã�¹���� �ߺ��Ǿ� �־� ���ʿ��� ���ҽ� ����
			pCha = FindChaById( ii[ 0 ] );	// ������ ĳ��
			pCha2 = FindChaById( ii[ 1 ], TRUE );	// �´� ĳ��
			if( pCha && pCha2 )
			{
				pCha->m_bhaste = ii[ 5 ];  // ���̽�Ʈ ����

				if( ii[6] == SKILL_K_POISON || ii[6] == SKILL_H_ELECTRICSHOT )
					pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz, ii[6]);
				else
					pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz);

				pCha->SetAttackChaId( pCha2->m_nCharIndex );
				pCha->SetAttackType( ii[3] );
				if( g_pRoh->m_nCharIndex != ii[ 1 ] )
					pCha2->SetAttackVital( ii[2] );

				return;
			}
		}	// end of if To ĳ��
		// To Mob
		else	// player to mob
		{
			// nate 2005-06-17 : ��ƾ ���� - ĳ���� ã�¹���� �ߺ��Ǿ� �־� ���ʿ��� ���ҽ� ����
			pCha = FindChaById( ii[ 0 ] );	// ������ ĳ��
			pMob = FindMobById( ii[ 1 ] );	// �´� ��
			if( pCha && pMob )
			{
				pCha->m_bhaste = ii[5];  // ���̽�Ʈ ����
				//mungmae-2005/05/10 Ÿ������ �� �� �������� ���̱�����
				//Ÿ������ ��ų �϶��� ���������� ���� �޼����� ���� ������.
				if( ii[6] == SKILLF_A_TIMECHARGE || ii[6] == SKILL_K_POISON || ii[6] == SKILL_H_ELECTRICSHOT )
					pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz, ii[6]);
				else
					pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz);

				pCha->SetAttackMobId(pMob->m_nVirId);
				pCha->SetAttackType(ii[3]);

				if(ii[4]==0)
					pMob->SetClassType(ii[4]);

				pMob->SetAttackVital(ii[2]);
				return;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// [8/3/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ���̺� �ҿ� :: ũ��Ƽ���� ������ ũ��Ƽ�� ���ϸ�
		if( pCha && (ii[3] == 1 || ii[3]  == 2) )
		{
			EffectSort *TempEffect = NULL;
			for(int i=0; i<3; i++)
			{
				TempEffect = pCha->FindMyFairy( SKILL_BABYSOUL_1+i);

				if(TempEffect)
				{
					bool bAction = false;
					switch( SKILL_BABYSOUL_1+i )
					{
					// ��ġ :: ũ��Ƽ��, ī��Ʈ ����
					case SKILL_BABYSOUL_1 :
						bAction = true;
						break;
					// ��ġ :: ũ��Ƽ��
					case SKILL_BABYSOUL_2 :
						if(ii[3] == 2)	bAction = true;
						break;
					// ��ġ :: ī��Ʈ ����
					case SKILL_BABYSOUL_3 :
						if(ii[3] == 1) bAction = true;
						break;
					}

					if( bAction )
					{
						TempEffect->num = FX_BABYSOUL_STATE_CRITICAL;
						TempEffect->vSortPos.y = 0.0f; // ������ �ʱ�ȭ.

						EffectSort ef_sort;
						ZeroMemory(&ef_sort, sizeof(EffectSort));

						ef_sort.nType		= FX_BABYSOUL;
						ef_sort.pNkChaTo	= pCha;// g_pRoh;
						ef_sort.vPos		= D3DVECTOR(TempEffect->vCurPos.x, TempEffect->vCurPos.y-20.0f, TempEffect->vCurPos.z);
						ef_sort.num			= 0;

						pCha->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );

						break;
					}
					continue;
				}

			}
		}
		//////////////////////////////////////////////////////////////////////////
	}
	//----------------------------------------------------------------------
	// From Pet
	//----------------------------------------------------------------------
	else if (!strncmp(second_arg, "p", 1))
	{
		if (!strncmp(third_arg, "n", 1))  		// pet to npc
		{
			if (pPet = FindPetById(ii[0]))
			{
				if (pMob = FindMobById(ii[1]))
				{
					pPet->Attack(pMob->m_wx, pMob->m_wz);
					pPet->SetAttackMobId(pMob->m_nVirId);
					pMob->SetAttackVital(ii[2]);
				}
			}
		}
		else if (!strncmp(third_arg, "c", 1))  		// pet to cha
		{
			if (pPet = FindPetById(ii[0]))
			{
				if (pCha = FindChaById(ii[1]))
				{
					pPet->Attack(pCha->m_wx, pCha->m_wz);
					pPet->SetAttackChaId(pCha->m_nCharIndex);
					if (pCha != g_pRoh)   // ���ΰ��� �˾Ƽ� ü���� �پ���.
					{
						pCha->SetAttackVital(ii[2]);
					}
				}
			}
		}
		else if (!strncmp(third_arg, "p", 1))  		// pet to pet
		{
			if (pPet = FindPetById(ii[0]))
			{
				if (pCMyApp->m_pMyPet && pCMyApp->m_pMyPet->m_nVirId == ii[1])   // Ȥ�� ������?
				{
					pPet->Attack(pCMyApp->m_pMyPet->m_wx, pCMyApp->m_pMyPet->m_wz);
					pPet->SetAttackPetId(pCMyApp->m_pMyPet->m_nVirId);
				}
				else if (pPet2 = FindPetById(ii[1]))
				{
					pPet->Attack(pPet2->m_wx, pPet2->m_wz);
					pPet->SetAttackPetId(pPet2->m_nVirId);
					pPet2->SetAttackVital(ii[2]);
				}
			}
		}
	}
	//----------------------------------------------------------------------
	// From Mob
	//----------------------------------------------------------------------
	else	// npc ����
	{
		// nate 2005-06-17 : ��ƾ ���� - ĳ���� ã�¹���� �ߺ��Ǿ� �־� ���ʿ��� ���ҽ� ����
		pMob = FindMobById( ii[ 0 ] );			// ������ ��

		if( !pMob ) // �̰� üũ �ȵǼ� ƨ��� ��� �ִ���(����ν��� ������ Ÿ�̹� ��..) ///�����޺� �� �߰�
			return;

		if( pMob->m_nMobNum == 430 || pMob->m_nMobNum == 432 )
		{
			pMob->SetAttackType(ii[ 3 ]);
			pMob->Attack(pMob->m_wx, pMob->m_wz);
			pMob->m_byInsertEffect |= INSERT_EFFECT_FIRE;
			return;
		}
		else if( pMob->m_nMobNum == 464 ) // ��ī�� �δ� ���� ///�δ�1
		{
			// �Ϲݰ��ݿ��� ����Ʈ�� �־��ش�. �����ӻ� �� Ÿ�ֿ̹� �־������.
			pCMyApp->m_pUIMgr->InsertMagic(NULL, pMob, NULL, NULL, EFFECT_SKILL_MOB_LEGKNOCK1);
			// ����Ʈ�� �ְ� ���� ��ƾ�� ���������� ó���Ѵ�.
		}

		if(!strncmp(third_arg, "c", 1))	// npc to player
		{
			pCha = FindChaById( ii[ 1 ], TRUE );	// �´� ĳ��

			if( pMob && pCha )
			{
				pMob->SetAttackType( ii[ 3 ] );
				if( ii[3] == 3 ) // 3 : ���������϶�( ����ĳ�� )
					pCha->m_Accumulate=TRUE;

				pMob->Attack( pCha->m_wx, pCha->m_wz );
				pMob->SetAttackChaId( pCha->m_nCharIndex );
				if( ii[ 1 ] != g_pRoh->m_nCharIndex ) // �̰� ������ == ���� ĳ���� �� �� ������ ���� ���̴� ���װ� �־�����. !=�� ����.(by ����)
					pCha->SetAttackVital( ii[ 2 ] );
				return;
			}

		}
		else if(!strncmp(third_arg, "p", 1))	// npc to pet
		{
			if (pMob)
			{
				if (pCMyApp->m_pMyPet && pCMyApp->m_pMyPet->m_nVirId == ii[ 1 ])	// Ȥ�� ������?
				{
					pMob->Attack(pCMyApp->m_pMyPet->m_wx, pCMyApp->m_pMyPet->m_wz);
					pMob->SetAttackPetId(pCMyApp->m_pMyPet->m_nVirId);
				}
				else if (pPet = FindPetById(ii[ 1 ]))
				{
					pMob->Attack(pPet->m_wx, pPet->m_wz);
					pMob->SetAttackPetId(pPet->m_nVirId);
					pPet->SetAttackVital(ii[ 2 ]);
				}
			}
		}
		else	// npc to npc
		{
			////2003 ���� �� �����ϱ�.���̵���� ��ȯ��
			pMob2 = FindMobById(ii[ 1 ]);//�´� ��

			if(pMob && pMob2)
			{
				pMob->SetAttackType(ii[ 3 ]);
				pMob->Attack(pMob2->m_wx, pMob2->m_wz);
				pMob->SetAttackMobId(pMob2->m_nVirId);
				pMob2->SetAttackVital(ii[ 2 ]);
			}
		}
	}
}


// 2004.12.19 / Lyul �߰�
// ���� ���߰���
// �Ʒ��� ������ �÷��̾� ������� ���� ���� �� �� ���� �޼���
// �� ���̾�Ʈ
// ��ȭ �� ���̾�Ʈ
// ���� ��ũ�ҿ�
// ȭ��Ʈȥ ���� ����
void CUIMgr::CmdMultiAttack(char *arg)
{
	if (arg == NULL)
		return;

	int ii[5] = {0,};
	char buf[256] = "";
	CNkCharacter *pCha = NULL;
	CNkMob *pMob = NULL, *pMob2 = NULL;
	CNkPet *pPet = NULL;

	//mul index(������) count(�����𰹼�) {c/n/p index ü�� style} ({}���� count ��ŭ �ݺ�)
	//ex) mul index 3 c 100 80 0 n 102 50 0 p 500 99 0

	arg = AnyOneArg(arg, buf);	// �����̾�Ʈ �ε��� or ��ȭ ����,��ũ�ҿ�
	ii[0] = atoi(buf);			// npc ���ؽ�

	if (pMob = FindMobById(ii[0]))
	{
		bool isBossStoneGolem = pMob->m_nMobNum == 879 ? true : false;

		arg = AnyOneArg(arg, buf); // ī��Ʈ. ����̳� �³�...
		ii[1] = atoi(buf);
		// nate 2005-09-26 : ���Ʈ - ����
		if( !ii[ 1 ] )
		{
			if(pMob->m_nMobNum == 416)
			{
				InsertMagic(NULL, pMob, NULL, NULL, EFFECT_DURANT_BEAM);
				pMob->SetMotionState(MOB_ATTACK);
			}
			else if( pMob->m_nMobNum == 438)
			{
				InsertMagic(NULL, pMob, NULL, NULL, EFFECT_SKILL_MOB_SNAKEBOSS3);
				pMob->SetMotionState(MOB_KNOCK);
			}
			else if( pMob->m_nMobNum == 464 ) // ��ī�� �δ� ���� ///�δ�1
			{
				pCMyApp->m_pUIMgr->InsertMagic(NULL, pMob, NULL, NULL, EFFECT_SKILL_MOB_LEGKNOCK2); // ���߰��� �ѷ� ����Ʈ.
				pMob->SetMotionState(MOB_KNOCK);
			}

			m_bMultiAttack = FALSE;
			return;
		}
		else
		{
			m_bMultiAttack = TRUE;
			for(int i = 0 ; i < ii[1] ; i++)
			{
				arg = AnyOneArg(arg, buf); // n,p,c ����

				if (!strncmp(buf, "c", 1))
				{
					// npc to player
					arg = AnyOneArg(arg, buf);
					ii[2] = atoi(buf);	//ĳ���� �ε���
					arg = AnyOneArg(arg, buf);
					ii[3] = atoi(buf);	//vital
					arg = AnyOneArg(arg, buf);
					ii[4] = atoi(buf);	//not use yet
					// �켱 ���ݸ�ǥ�� ���ΰ��ΰ� Ȯ���ϰ�.
					if (ii[2] == g_pRoh->m_nCharIndex)
					{
						if( i == 0 &&
							((isBossStoneGolem == true && (ii[4] == 4 || ii[4] == 5)) == false) )
						{
							pMob->SetAttackChaId( g_pRoh->m_nCharIndex );
							pMob->Attack(g_pRoh->m_wx, g_pRoh->m_wz);
						}

						// �� ���̾�Ʈ / ��ȭ �� ���̾�Ʈ
						if( pMob->m_nMobNum == 38 || pMob->m_nMobNum == 331
								|| pMob->m_nMobNum == 455 || pMob->m_nMobNum == 462 ) ///�±�����Ʈ�̺�Ʈ ��û���� ���ͺ��� ���� �̻��� ���.
							InsertMagic(NULL, pMob, g_pRoh, NULL,EFFECT_SKILL_WARGIANT_MULTI);// SKILL_WARGIANT_MULTI);
						// ���� ��ũ �ҿ�
						else if(pMob->m_nMobNum == 334)
							InsertMagic(NULL, pMob, g_pRoh, NULL, EFFECT_SKILL_LIGHTNING);
						// ȭ��Ʈ ȥ ���� ����
						else if(pMob->m_nMobNum == 352)
							InsertMagic(NULL, pMob, g_pRoh, NULL, EFFECT_SKILL_WAND_METEORITE);
						// nate 2005-09-22 : ���Ʈ�� �߰����� - ���Ʈ
						else if(pMob->m_nMobNum == 416)
							InsertMagic(NULL, NULL, g_pRoh, NULL, EFFECT_DURATT_TARGET);
					}
					// ��Ÿ �÷��̾��.
					else if (pCha = FindChaById(ii[2]))
					{
						if( i == 0 &&
							((isBossStoneGolem == true && (ii[4] == 4 || ii[4] == 5)) == false) )
						{
							pMob->SetAttackChaId( g_pRoh->m_nCharIndex );
							pMob->Attack(pCha->m_wx, pCha->m_wz);
						}

						pCha->SetAttackVital(ii[3]);
						// �� ���̾�Ʈ / ��ȭ �� ���̾�Ʈ
						if(pMob->m_nMobNum == 38 || pMob->m_nMobNum == 331
								|| pMob->m_nMobNum == 455 || pMob->m_nMobNum == 462 )
							InsertMagic(NULL, pMob, pCha, NULL, EFFECT_SKILL_WARGIANT_MULTI);
						// ���� ��ũ �ҿ�
						else if(pMob->m_nMobNum == 334)
							InsertMagic(NULL, pMob, pCha, NULL, EFFECT_SKILL_LIGHTNING);
						// ȭ��Ʈ ȥ ���� ����
						else if(pMob->m_nMobNum == 352)
							InsertMagic(NULL, pMob, pCha, NULL, EFFECT_SKILL_WAND_METEORITE);
						// nate 2005-09-22 : ���Ʈ�� �߰����� - ���Ʈ
						else if(pMob->m_nMobNum == 416)
							InsertMagic(NULL, NULL, pCha, NULL, EFFECT_DURATT_TARGET);
					}
				}
				else if (!strncmp(buf, "p", 1))
				{
					// npc to pet
					arg = AnyOneArg(arg, buf);
					ii[2] = atoi(buf);	//pet�� �ε���
					arg = AnyOneArg(arg, buf);
					ii[3] = atoi(buf);	//vital
					arg = AnyOneArg(arg, buf);
					ii[4] = atoi(buf);	//not use yet
					if (pCMyApp->m_pMyPet && pCMyApp->m_pMyPet->m_nVirId == ii[2])
					{
						// Ȥ�� ������?
						if(i==0)
							pMob->Attack(pCMyApp->m_pMyPet->m_wx, pCMyApp->m_pMyPet->m_wz);

						pCMyApp->m_pMyPet->SetAttackVital(ii[3]);
					}
					else if (pPet = FindPetById(ii[2]))
					{
						if( i == 0 )
							pMob->Attack(pPet->m_wx, pPet->m_wz);

						pPet->SetAttackVital(ii[3]);
					}
				}
				else
				{
					// npc to npc
					//// ���� �� �����ϱ�.���̵���� ��ȯ��
					arg = AnyOneArg(arg, buf);
					ii[2] = atoi(buf);	//���� �ε���
					arg = AnyOneArg(arg, buf);
					ii[3] = atoi(buf);	//vital
					arg = AnyOneArg(arg, buf);
					ii[4] = atoi(buf);	//not use yet
					pMob2 = FindMobById(ii[2]);//�´� ��

					if(pMob && pMob2)
					{
						if( i == 0 )
						{
							pMob->Attack(pMob2->m_wx, pMob2->m_wz);
							pMob->SetAttackMobId(pMob2->m_nVirId);
						}
						pMob2->SetAttackVital(ii[3]);
						// �� ���̾�Ʈ / ��ȭ �� ���̾�Ʈ
						if( pMob->m_nMobNum == 38 || pMob->m_nMobNum == 331
								|| pMob->m_nMobNum == 455 || pMob->m_nMobNum == 462 )
							InsertMagic(NULL, pMob, NULL, pMob2, EFFECT_SKILL_WARGIANT_MULTI);
						// ���� ��ũ �ҿ�
						else if(pMob->m_nMobNum == 334)
							InsertMagic(NULL, pMob, NULL, pMob2, EFFECT_SKILL_LIGHTNING);
						// ȭ��Ʈ ȥ ���� ����
						else if(pMob->m_nMobNum == 352)
							InsertMagic(NULL, pMob, NULL, pMob2, EFFECT_SKILL_WAND_METEORITE);
					}
				}
			}
		}
	}
	m_bMultiAttack = FALSE;

	return;
}



///2003 ���� attack �޽���

//--------------------------------------------------------------------------
// CmdSubAttack
//--------------------------------------------------------------------------
// ���� ���ÿ� ���õ� �޼���
void CUIMgr::CmdSubAttack(char *msg)
{
	int ii[7]= {0,};

	char second_arg[20], third_arg[20];
	CNkCharacter *pCha, *pCha2;
	CNkMob *pMob;

	if (msg == NULL)
		return;
	// Read Message
	sscanf(msg, "%s %d %s %d %d %d %d %d %d",  second_arg, &ii[0], third_arg, &ii[1], &ii[2], &ii[3],&ii[4],&ii[5],&ii[6]);

	if (!strncmp(second_arg, "c", 1))
	{
		// to ĳ�� ����
		if (!strncmp(third_arg, "c", 1))
		{
			// player to player
			// ������ ��� ã��.
			if( pCha = GetCharacterByID(ii[0]) )
			{
				// �´� ����� ���ΰ��ΰ�?
				{
					if (ii[1] == g_pRoh->m_nCharIndex)
					{
						if(pCha->m_Race==RACE_BULKAN)
						{
							// ��ũ��
							if(ii[5])
							{
								pCha->m_bChakramatt = true;
								pCha->Attack(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz,ii[6]);
							}
							// �����̾�
							else
							{
								if(pCha->m_Wearing[WEARING_CLOAK] && GET_TYPE(pCha->m_Wearing[WEARING_CLOAK]) == ITYPE_SUB)
									pCha->Attack(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz,ii[6]);
							}
						}
						// ī�̸��� ( �ϵ� �ۿ� ����)
						else if(pCha->m_Race==RACE_KAILIPTON)
						{
							if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
								pCha->Attack(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz,ii[6]);
						}
						// ���̵��
						else if(pCha->m_Race==RACE_AIDIA)
						{
							if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
								pCha->Attack(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz,ii[6]);
						}
						// �޸�
						else if(pCha->m_Race==RACE_HUMAN)
						{
							if( ii[6] == SKILL_HANDLE )
							{
								if(pCha->m_Wearing[WEARING_CLOAK] && GET_TYPE(pCha->m_Wearing[WEARING_CLOAK]) == ITYPE_SUB)
									pCha->Attack(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz,ii[6]);
							}
							else if( ii[6] == SKILL_DEEP_ATTACK ||  ii[6] == SKILL_CHAIN_ATTACK )
							{
								if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
									pCha->Attack(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz,ii[6]);
							}
						}
						pCha->SetAttackChaId(g_pRoh->m_nCharIndex);
						return;
					}

					// �´� ĳ���� ã�´�.
					if( pCha2 = GetCharacterByID(ii[1]) )
					{
						if(pCha->m_Race==RACE_BULKAN)
						{
							// ��ũ��
							if(ii[5])
							{
								pCha->m_bChakramatt = true;
								pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,	SKILL_THROW);
							}
							else
							{
								if(pCha->m_Wearing[WEARING_CLOAK] && GET_TYPE(pCha->m_Wearing[WEARING_CLOAK]) == ITYPE_SUB)
									pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,	ii[6]);
							}
						}
						// ī��
						else if(pCha->m_Race==RACE_KAILIPTON)
						{
							if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
								pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,ii[6]);
						}
						// ���̵��
						else if(pCha->m_Race==RACE_AIDIA)
						{
							if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
								pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,ii[6]);
						}
						// �޸�
						else if(pCha->m_Race==RACE_HUMAN)
						{
							if( ii[6] == SKILL_DEEP_ATTACK ||  ii[6] == SKILL_CHAIN_ATTACK )
							{
								if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
									pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,ii[6]);
							}
							else if( ii[6] == SKILL_HANDLE )
							{
								if(pCha->m_Wearing[WEARING_CLOAK] && GET_TYPE(pCha->m_Wearing[WEARING_CLOAK]) == ITYPE_SUB)
									pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,ii[6]);
							}
						}

						pCha->SetAttackChaId(pCha2->m_nCharIndex);
						pCha2->SetAttackVital(ii[2]);
						pCha->SetAttackType(ii[3]);//Ư������
					}
					return;
				}
			}
		}
		else      // to Mob
		{
			if( pMob = GetMobByID(ii[1]) )
			{
				// ���� ��ü�� ���ΰ��ΰ� Ȯ��.
				if( ii[ 0 ] == g_pRoh->m_nCharIndex )
					return;
				else
				{
					// ���� ��ü ĳ���͸� ã�´�.
					if( pCha = GetCharacterByID( ii[0] ) )
					{
						{
							// ��ĭ
							if(pCha->m_Race==RACE_BULKAN)
							{
								// Chakram ����
								if(ii[5])
								{
									pCha->m_bChakramatt = true;
									pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,	ii[6]);
								}
								// �����̾�
								else
								{
									if(pCha->m_Wearing[WEARING_CLOAK] && GET_TYPE(pCha->m_Wearing[WEARING_CLOAK]) == ITYPE_SUB)
										pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,ii[6]);
								}
							}
							// ī��
							else if(pCha->m_Race==RACE_KAILIPTON)
							{
								if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
									pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,ii[6]);
							}
							// ���̵��
							else if(pCha->m_Race==RACE_AIDIA)
							{
								if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
									pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,ii[6]);
							}
							// �޸�
							else if(pCha->m_Race==RACE_HUMAN)
							{
								if( ii[6] == SKILL_HANDLE )
								{
									if(pCha->m_Wearing[WEARING_CLOAK] && GET_TYPE(pCha->m_Wearing[WEARING_CLOAK]) == ITYPE_SUB)
										pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,ii[6]);
								}
								else if( ii[6] == SKILL_DEEP_ATTACK ||  ii[6] == SKILL_CHAIN_ATTACK )
								{
									if(pCha->m_Wearing[WEARING_SHIELD] && GET_TYPE(pCha->m_Wearing[WEARING_SHIELD]) == ITYPE_SUB)
										pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,ii[6]);
								}
							}
							pCha->SetAttackMobId(pMob->m_nVirId);
							pMob->SetAttackVital(ii[2]);
							if(ii[4]==0)
								pMob->SetClassType(ii[4]);
							pCha->SetAttackType(ii[3]);//Ư������

							return;
						}
					}
				}
			}
		}
	}
	//wan:2004-12 ȭ��Ʈȥ ���� �������� ��������
	//pMob to pCha
	else if(!strncmp(second_arg, "n", 1))
	{
		if (!strncmp(third_arg, "c", 1))
		{
			// mob to player
			//�´� �������� �ι�° ���ݵ��ۼ���
			if( pMob = GetMobByID( ii[0] ) )
			{
				// �´� ����� ���ΰ��ΰ�?
				if (ii[1] == g_pRoh->m_nCharIndex)
				{
					if(pMob->m_nMobNum==353)//Ű�緹
						InsertMagic(NULL, pMob, g_pRoh, NULL,EFFECT_SKILL_SLAYER);
					else if(pMob->m_nMobNum==354)//��ũ��
						InsertMagic(NULL, pMob, g_pRoh, NULL,EFFECT_SKILL_WAND_CHAIN);
					else if(pMob->m_nMobNum==355)//��ũ�ε�
						InsertMagic(NULL, pMob, g_pRoh, NULL,EFFECT_SKILL_WARGIANT_MULTI);

					pMob->Attack(g_pRoh->m_wx, g_pRoh->m_wz);
				}
				else
				{
					if( pCha = GetCharacterByID( ii[1] ) )
					{
						if(pMob->m_nMobNum==353)//Ű�緹
							InsertMagic(NULL, pMob, pCha, NULL,EFFECT_SKILL_SLAYER);
						else if(pMob->m_nMobNum==354)//��ũ��
							InsertMagic(NULL, pMob, pCha, NULL,EFFECT_SKILL_WAND_CHAIN);
						else if(pMob->m_nMobNum==355)//��ũ�ε�
							InsertMagic(NULL, pMob, pCha, NULL,EFFECT_SKILL_WARGIANT_MULTI);

						pCha->SetAttackVital(ii[2]);
						pMob->Attack(pCha->m_wx, pCha->m_wz);
					}
				}
			}
		}
		return;
	}
}

// 2004.11.20
// �������� ���� ��ƾ�̹Ƿ� CmdClick �� ���� �и� ������.
// NPC �� Ŭ�� �Ǵ� �� Event �߻�
// Return val - false : NPC Ŭ�� ����.
//            - true  : NPC Ŭ��
bool CUIMgr::MouseClickEvent_NPC(CNkMob *pMob, int which_button)
{

	char tmp[200], Tmp2[100];
	int iAdd = 0;
	int expense;
	int Level = g_pRoh->m_Level;
	int Str, Int, Dex, Con, Cha;
	int Max_Str, Max_Int, Max_Dex, Max_Con, Max_Cha;

	if( pMob->m_nMobNum == NPC_INDEX_SHAILON_GATE1 )
	{
		pCMyApp->StopHero();

		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage("gocastle 0\n");
		return 1;
	}
	else if( pMob->m_nMobNum == NPC_INDEX_SHAILON_GATE2 )
	{
		pCMyApp->StopHero();

		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage("gocastle 1\n");
		return 1;
	}
	else if (pMob->m_Flag & NPC_SHOPKEEPER)
	{
		if (DistPlToPl(g_pRoh->m_wx, g_pRoh->m_wz, pMob->m_wx, pMob->m_wz) >= 200)
			return 1;

		//  [1/15/2008 �����] �Ϻ� ���� ���� : ������ ��ȭ�� �ٸ� NPC Ŭ���ص� �������̽� �ȹٲ��
		if( g_dwClientCountry == CTRY_JPN )
		{
			if( g_pNk2DFrame->IsUpgradeVisible() )
				return 1;
		}

		if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009)
		{
			switch( pMob->m_nMobNum )
			{
			case 639:
			case 640:
			case 641: // ���帶�� ������ �е帶�� ���ո� ������ �����ϵ���
				if( g_pRoh->m_GuildIndex != 1 )
					return 1;
				break;

			case 642:
			case 643:
			case 644:
				if( g_pRoh->m_GuildIndex != 2)
					return 1;
				break;

			case 661: // ���ְ� �� ����
				if( g_pRoh->m_GuildLevel != 10 ) // ���ְ��� �ƴϸ� ������ ���� �ʴ´�.
					return 1;
				break;
			}
		}
		
		switch(pMob->m_nMobNum)
		{
		case 139: // â������
			{	
				g_pNk2DFrame->ToggleWareHouseWindow();
				CControlWareHouse* pControlWareHouse = g_pNk2DFrame->GetControlWareHouse();
				if( pControlWareHouse != NULL )
				{
					pControlWareHouse->SetNpcIndex(pMob->m_nVirId);
				}
				
				return 1;
			}
			break;

		case 166: // Ĩ��ȯ��
			{
				g_pNk2DFrame->ToggleGambleWindow(0);
				return 1;
			}
			break;

		case 167: // �׺�
			{
				g_pNk2DFrame->ToggleGambleWindow(1);
				return 1;
			}
			break;

		case 211: // �Ľ��� ����
			{
				switch( pCMyApp->GetCurWorld() )
				{
				case WORLD_GUILD:
					{
						if (g_pTcpIp)g_pTcpIp->SendNetMessage("g_war\n");
						return 1;
					}
					break;

				case WORLD_MATRIX: // ��Ʈ���� ���� - ���ӸŴ���.
					{
						if(!g_pNk2DFrame->CloseAllWindow())
							return 1;

						if (g_pTcpIp)
						{
							g_pTcpIp->SendNetMessage("list_room\n");
							return 1;
						}
					}
					break;
				}
			}
			break;

		case 293:
			{
				g_pNk2DFrame->ToggleGambleWindow(2);
				return 1;
			}
			break;

		case 602:
			{
				if( pMob->m_wx == 6668 && pMob->m_wz == 5135 )
				{
					g_pNk2DFrame->ToggleGambleWindow(5);
					return 1;
				}
			}

		case NPC_INDEX_BANI_GIRL:
			{
				if( pCMyApp->GetCurWorld() == 4 )
				{
					g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_PRESENT_2010 );
					return 1;
				}

				if( pCMyApp->GetCurWorld() == 4 && pMob->m_wx == 6832 && pMob->m_wz == 5110 )
				{					
					g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_PARENTSDAY);
					return 1;
				}
			}
			break;

		case NPC_INDEX_ADVENTURE_MARY:
			{
				g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_NEW_SUPPORT_2011 );	// �ű�����
				return 1;
			}
			return 1;

		case NPC_INDEX_SEXY_GIRL:
			if( g_dwClientCountry == CTRY_KOR )
			{
				if( pCMyApp->GetCurWorld() == 4 )
				{
					g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_HALLOWEEN ); // Ƽ����� �»� 2008.10.15
					return 1;
				}
			}
			return 1;

		case 330: // ���̵�� ���ջ��� // 2004.09.14
			{
				g_pNk2DFrame->ToggleGambleWindow(3);
				return 1;
			}
			break;

		case 426: // ��ȭ��
			switch( pCMyApp->m_nCurWorldIdx )
			{
			case WORLD_START:
				g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_NPCUPGRADE, pMob->GetMobName() );
				return 1;
			}
			break;
		case 490: // �� ��ɰ�
			{
				{
					if( g_pNk2DFrame->GetTgaUIWindow()->IsOpenWindow() )
						return 1;

					pCMyApp->StopHero();

					g_pNk2DFrame->CloseAllWindow();

					if(g_pRoh->GetMyGuildData() != NULL)
						g_pNk2DFrame->m_pUIWindow->OnOpenWindow(WINDOW_GUILD_MEMBER);
					else
						g_pNk2DFrame->m_pUIWindow->OnOpenWindow(WINDOW_GUILD_NONMEMBER);

					return 1;
				}
			}
			break;
		case NPC_INDEX_HUNTERMASTER:// ������� ���(491)
			{
				if( g_SvrType == ST_ADULT_ONLY )
				{
					if( g_pNk2DFrame->GetUIWindow()->IsOpenWindow() )
						return 1;

					pCMyApp->StopHero();

					g_pNk2DFrame->m_pTgaUIWindow->OnOpenWindow(WINDOW_TGA_WANTED_PAGE);
					return 1;
				}
			}
			break;
		case 606: // ����
			{
				g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_GIRASI_EXCH); // 2008 ���� 3���� ������ ������ �̺�Ʈ
				return 1;
			}
			break;

		case 608:
			{
				// �̽��� ���� SK �ΰ� ����
				if(pCMyApp->m_nCurWorldIdx == WORLD_START)
					g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_SK_200804);
				return 1;
			}
			break;

		case 609: //���� NPC
			{
				if(pCMyApp->m_nCurWorldIdx == WORLD_START)
				{
					if( g_dwClientCountry == CTRY_KOR)		g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_081114_PREMIUM_EVENT);
					else									g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_LP_GIFTBOX_CHANGE_JP); //  [10/29/2008 parkmj] �Ϻ������� �ý���
				}
				return 1;
			}
			break;
		case 613:
				g_pNk2DFrame->ToggleHeroPrivilegeWindow();
			return 1;
		case 614:
			g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_NEW_DEFENITEM_ITEM_EXCH);
			return 1;
		case 645: // ��ȭ�밡 �����ڴ�

			switch( pCMyApp->m_nCurWorldIdx )
			{
			case WORLD_WHITEHORN:
				g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_NEW_NPCUPGRADE, pMob->GetMobName() );
				return 1;
			}
			break;

		// [4/22/2009 D.K ] : â�� ���� ��ƾ. (��׷��� �� ���¿����� ����.
		case 666:
			if( m_bAutoHunt )
			{
				if( m_AutoPlay->GetCurrentState() == WARE )
				{
					g_pNk2DFrame->ToggleWareHouseWindow();
					return 1;
				}
			}
			break;

		case 667: // ���ǵ� �߽��� ����
			pCMyApp->StopHero();
			g_pTcpIp->SendNetMessage("student_npc 0\n");
			return 1;

		case 668: // ������ ������ ������
			if( g_pNk2DFrame->ControlSelmenuSetMetuList(0) )
				g_pNk2DFrame->ShowControlSelMenu(TRUE);
			return 1;

		case NPC_INDEX_KIRAK:  // ���踶���� Ű��ũ
			{
				// �ͽ�Ʈ�� �κ��� �������� �ִ°� üũ ������ �޽���â
				CItem *pItem = g_pRoh->m_ExgInven;
				if( pItem )
				{
					g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_LOCKSMITH_MSG),TYPE_NOR_OK, 1);
					return 1;
				}

				g_pNk2DFrame->ToggleLockSmithWindow();
				return 1;
			}
		case NPC_INDEX_DENY:
			g_pNk2DFrame->ToggleGambleWindow(8);
			return 1;

		case NPC_INDEX_JANY:
			g_pNk2DFrame->ToggleGambleWindow(7);
			return 1;
		case NPC_INDEX_NEWYEAR_HELPER:
			g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_NEWYEAR_LUCKYBAG);
			return 1;
		}


		// nate 2005-07-12 : Dmitron - npc Ŭ���� �̵� ����Ʈ ���̱�
		if( pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON4
				&& pMob->m_nMobNum == NPC_INDEX_RESEARCHER )
		{
			g_pTcpIp->SendNetMessage( "quest click 384\n" ); //mungmae 2006/03/15  250~274 ����� ����Ʈ

			if(  g_dwClientCountry == CTRY_TH || g_dwClientCountry == CTRY_JPN ) // �±� �Ϻ��� �̺�Ʈ�� ���巹�� ���� ����.
			{
				g_pNk2DFrame->ShowInterfaceWindow(true, GATE, WORLD_DUNGEON4);
				return 1;
			}
			else
			{
				//mungmae-2005/10/25 ���Ʈ�� ���� ����
				if( g_pRoh->m_Level >=275 )
				{
					g_pNk2DFrame->ShowInterfaceWindow(true, GATE, WORLD_DUNGEON4);
					return 1;
				}
				else
				{
					if( !g_pRoh->m_bSecialQuest )
					{
						// IDS_LIMIT_LEVEL275 : ����275�̻� ���Ʈ�п� �����Ͻ� �� �ֽ��ϴ�.
						g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LIMIT_LEVEL275), TYPE_NOR_OK, 1 );
						pCMyApp->StopHero();
					}
					return 1;
				}
			}
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_BULKAN && pMob->m_nMobNum == 546 && pMob->m_wx == 2285 && pMob->m_wz == 9475 )
		{
			pCMyApp->StopHero();
			g_pTcpIp->SendNetMessage( "quest click 546\n" ); // ��ĭ�� ����Ʈ
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_BULKAN && pMob->m_nMobNum == 546 )
		{
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_DMITRON && pMob->m_nMobNum == 604 )
		{
			g_pNk2DFrame->ShowBossraidInfoWindow(TRUE);
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_START && pMob->m_nMobNum == 605 ) // ��Ÿ ���� ��ȯ
		{
			// �̺�Ʈ ��ȯ ������� ó������

			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_STARSTONE_EXCH );
			return 1;
		}

		//------------------------------------------------------------------
		else if (pMob->m_nMobNum == 317)
		{
			// �Ҿƹ��� 317, �ҸӴ� 318
			BOOL IsSebe = FALSE;

			if (pCMyApp->m_nCurWorldIdx == 4
					&& pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 7155, 5346, 7194, 5306) )
				IsSebe = TRUE;
			else if (pCMyApp->m_nCurWorldIdx == 7
					 && pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 8760, 8140, 8800, 8100) )
				IsSebe = TRUE;
			else if (pCMyApp->m_nCurWorldIdx == 3
					 && pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 7544, 11755, 7585, 11715) )
				IsSebe = TRUE;
			else if (pCMyApp->m_nCurWorldIdx == 0
					 && pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 6505, 6548, 6545, 6508) )
				IsSebe = TRUE;
			else if (pCMyApp->m_nCurWorldIdx == 6
					 && ( pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 11940, 11410, 11980, 11370)
						  || pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 1530, 1445, 1570, 1405) ) )
				IsSebe = TRUE;

			if (IsSebe)
			{
				float	dx, dz;
				dx = pMob->m_wx - g_pRoh->m_wx;
				dz = pMob->m_wz - g_pRoh->m_wz;

				g_pRoh->m_toDir = (float) atan2(dz, dx);
				g_pRoh->SetMotionState(CHA_SOCIAL, 74); // ���� �̺�Ʈ ���ϱ�
				pCMyApp->StopHero();

				if (g_pTcpIp)
				{
					sprintf(tmp, "sebe 0\n");
					g_pTcpIp->SendNetMessage(tmp);
					sprintf(tmp, "stop %.0f %.0f %.0f %.0f\n", g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_wy, (g_pRoh->m_toDir) * 10000);
					g_pTcpIp->SendNetMessage(tmp);
					sprintf(tmp, "social 74\n");
					g_pTcpIp->SendNetMessage(tmp);
				}
			}
			return 1;
		}
		else if (pMob->m_nMobNum == 318)
		{
			// �Ҿƹ��� 317, �ҸӴ� 318
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_THAI_MOTHERS_DAY );  // �±� ��Ӵϳ� �̺�Ʈ.

			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_VIDBLINE && pMob->m_nMobNum == NPC_INDEX_BELION )
		{
			g_pNk2DFrame->ShowGateWindow(true, (1<<4)|(1<<7)|(1<<8) ,false);
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_DISPOSAL && pMob->m_nMobNum == NPC_INDEX_BELION )
		{
			g_pNk2DFrame->ShowGateWindow(true, (1<<9|1<<22) ,false);
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_FORLORN_S2 && pMob->m_nMobNum == NPC_INDEX_BELION )
		{
			g_pNk2DFrame->ShowGateWindow(true, (1<<20) ,false);
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_FORLORN_S3 && pMob->m_nMobNum == NPC_INDEX_BELION )
		{
			g_pNk2DFrame->ShowGateWindow(true, 4,true);
			return 1;
		}

		else if( pCMyApp->IsCurWorldID_BossraidZone() && pMob->m_nMobNum == NPC_INDEX_BELION )
		{
			if( g_dwClientCountry == CTRY_JPN )
			{
				CControlGate* pGate = (CControlGate*)g_pNk2DFrame->GetInterface(GATE);
				pGate->SetSubType( 100 );
				g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
			}
			else
				PrepareChangeWorld(TRUE, WORLD_DMITRON, 0);
			return 1;
		}
		else if(pCMyApp->m_nCurWorldIdx == WORLD_DMITRON && pMob->m_nMobNum == NPC_INDEX_BELION )
		{
			CControlGate* pGate = (CControlGate*)g_pNk2DFrame->GetInterface(GATE);
			pGate->SetSubType( 100 ); // ������ ���� â
			g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
			return 1;
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_HUMAN && pMob->m_nMobNum == 548 )
		{

			CItem *pKeyItem = NULL;
			pKeyItem = g_pRoh->FindItemByVnumFromAll( 1833 ); // ����� ���踦 ������ �ִ��� ã�´�.

			if( pKeyItem ) // ���谡 �ִٸ�
			{
				// �� ����޶�� ��Ŷ�� ������.
				pCMyApp->StopHero();

				int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

				if( PackNum >= 0 && PackNum <= PACK_NUM ) // �κ��� ��ȯâ�� �˻��Ѵ�.
				{
					// br_key [packnum] [key item index] [room num]

					if( pMob->m_wx == 3946 && pMob->m_wz == 6309 ) // 1 ����
					{
						sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, 1 );
						if( g_pTcpIp )
							g_pTcpIp->SendNetMessage(m_commOut);
					}
					else if( pMob->m_wx == 3620 && pMob->m_wz == 6303 ) // 2 ���� w
					{
						sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, 2 );
						if( g_pTcpIp )
							g_pTcpIp->SendNetMessage(m_commOut);
					}
					else if( pMob->m_wx == 3621 && pMob->m_wz == 6633 ) // 3 ����
					{
						sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, 3 );
						if( g_pTcpIp )
							g_pTcpIp->SendNetMessage(m_commOut);
					}
					else if( pMob->m_wx == 3957 && pMob->m_wz == 6627 ) // 4 ����
					{
						sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, 4 );
						if( g_pTcpIp )
							g_pTcpIp->SendNetMessage(m_commOut);
					}

					return 1;
				}
			}
			else if( pCMyApp->IsInsideRhombus(g_pRoh->m_wx, g_pRoh->m_wz, 3410,6480,3770,6120,4100,6480,3770,6840)  || // ���
					 pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 4020, 6570, 4240, 6370 ))  // �Ա���
			{
				pCMyApp->StopHero();
				if( pMob->m_wx == 3946 && pMob->m_wz == 6309 ) // 1 ����
				{
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage("br_key -1 -1 1\n");
				}
				else if( pMob->m_wx == 3620 && pMob->m_wz == 6303 ) // 2 ����
				{
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage("br_key -1 -1 2\n");
				}
				else if( pMob->m_wx == 3621 && pMob->m_wz == 6633 ) // 3 ����
				{
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage("br_key -1 -1 3\n");
				}
				else if( pMob->m_wx == 3957 && pMob->m_wz == 6627 ) // 4 ����
				{
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage("br_key -1 -1 4\n");
				}
			}

			return 1;

		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_FINALBOSS && pMob->m_nMobNum == 603 )
		{
			pCMyApp->StopHero();

			CItem *pKeyItem = NULL;
			pKeyItem = g_pRoh->FindItemByVnumFromAll( 1930 ); // ����� ���踦 ������ �ִ��� ã�´�.

			if( pKeyItem ) // ���谡 �ִٸ�
			{
				// �� ����޶�� ��Ŷ�� ������.
				int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

				if( PackNum >= 0 && PackNum <= PACK_NUM ) // �κ��� ��ȯâ�� �˻��Ѵ�.
				{
					// br_key [packnum] [key item index] [room num]
					sprintf(m_commOut, "br_key %d %d 1\n", PackNum, pKeyItem->m_Index);
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage(m_commOut);
				}
			}
			else
			{
				// �������� ���� ������ üũ�Ѵ�. Ű�� ��� ��  �� �ִ� ��찡 �ֱ� ������
				if( g_pTcpIp )
					g_pTcpIp->SendNetMessage("br_key -1 -1 1\n");
				// IDS_MARBODEN_TIKET_DONT_HAVE : �������� ������� �����ϴ�.
				//g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_MARBODEN_TIKET_DONT_HAVE), TYPE_NOR_OK, 1);
			}

			return 1;
		}
		//------------------------------------------------------------------
		//�������,���Ҿƹ���255,��������257
		else if (pMob->m_nMobNum == 257 )
		{
			g_pNk2DFrame->ToggleEventAncientWindow(0);

			char tmp[100];
			if( g_pRoh->m_bYanQuest )
			{
				sprintf(tmp, "quest sp\n");
				g_pTcpIp->SendNetMessage(tmp);
			}
			else if(!g_pRoh->m_bYanQuest && g_pTcpIp)
			{
				sprintf(tmp, "quest click 257\n");
				g_pTcpIp->SendNetMessage(tmp);
			}
			return 1;
		}
		else if( pMob->m_nMobNum == 454 ) // ������ ��(������ �� ��ȯ NPC)
		{
			g_pNk2DFrame->ToggleEventAncientWindow( 8 );

			return 1;
		}
		else if (pMob->m_nMobNum == NPC_INDEX_SAN_GRANDFATHER)
		{
			g_pNk2DFrame->ToggleSummerEventWindow(TRUE); // �ҷ� ��� ������ ��ȯ�̺�Ʈ
			return 1;
		}
		else if( g_dwClientCountry == CTRY_TWN && pMob->m_nMobNum == 471 )  // �븸�� ��Ÿ���� ��Ÿ��� ��ȯ NPC�� ���.
		{
			g_pNk2DFrame->ToggleEventAncientWindow(5);
			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_TOY_GRANDFATHER)
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_CHILDDAY );
			return 1;
		}
		else if( pMob->m_nMobNum == 351 ) // ��Ÿ
		{
		}

		else if( pMob->m_nMobNum == NPC_INDEX_SERA ) // ��Ƽ��Ż ����
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_NEWYEAR_2011 );
			return 1;
		}

		//------------------------------------------------------------------
		// nate 2004 - 4
		// CastleWar
		else if (pMob->m_nMobNum == 303)
		{
			// �ν�Ʈ���� ��� ������
			if( m_bIsLowGuildMaster )
				m_bIsLowGuildMaster = FALSE;
			else
				m_bIsLowGuildMaster = TRUE;

			if( m_bIsLowGuildMaster )
			{
				pCMyApp->StopHero();
				if( m_pLowGuildMaster )
				{
					delete m_pLowGuildMaster;
					m_pLowGuildMaster = NULL;
				}
				m_pLowGuildMaster = new CControlLowGuildMaster();
				m_pLowGuildMaster->LoadRes();
				if (g_pTcpIp)
					g_pTcpIp->SendNetMessage( "mguild minor_date\n" );
			}
			return 1;
		}
		//------------------------------------------------------------------
		// nate 2004 - 9
		// GuildHunt
		else if( pMob->m_nMobNum == 336)
		{
			if( m_bIsGuildHunt )
				m_bIsGuildHunt = FALSE;
			else
			{
				// �κ����� �����츦 �ݴ´�
				g_pNk2DFrame->CloseAllWindow();
				// ������ �������� ���ִ��� Ȯ��
				if( m_bIsScrollBox )
				{
					if( m_pScrollBox )
						SAFE_DELETE( m_pScrollBox );
					m_bIsScrollBox = FALSE;
				}
				m_bIsGuildHunt = TRUE;
			}

			if( m_bIsGuildHunt )
			{
				pCMyApp->StopHero();
				if( m_pGuildHunt )
					SAFE_DELETE( m_pGuildHunt );

				m_pGuildHunt = new CGuildHunt();
				m_pGuildHunt->LoadRes();
				m_pGuildHunt->SendQuestApplyMsg( 1 );	// GUILDHUNT_OPEN == 1
			}
			return 1;
		}
		else if( pMob->m_nMobNum == 510 && pCMyApp->m_nCurWorldIdx == WORLD_DMITRON)
		{
			pCMyApp->StopHero();
			// �κ����� �����츦 �ݴ´�
			g_pNk2DFrame->CloseAllWindow();

			// ������ �������� ���ִ��� Ȯ��
			if( m_bIsScrollBox )
			{
				if( m_pScrollBox )
					SAFE_DELETE( m_pScrollBox );
				m_bIsScrollBox = FALSE;
			}

			if (g_pTcpIp)
				g_pTcpIp->SendNetMessage("occp bt open\n");

			return 1;
		}
		else if( pMob->m_nMobNum == 506 )
		{
			pCMyApp->StopHero();
			// �κ����� �����츦 �ݴ´�
			g_pNk2DFrame->CloseAllWindow();

			// ������ �������� ���ִ��� Ȯ��
			if( m_bIsScrollBox )
			{
				if( m_pScrollBox )
					SAFE_DELETE( m_pScrollBox );
				m_bIsScrollBox = FALSE;
			}

			int nSubType = CDmitronZone::SearchPortalManager(pMob->m_wx, pMob->m_wz);
			if (g_pTcpIp && nSubType >= 0)
			{
				sprintf(m_commOut, "occp cash open %d\n", nSubType);
				g_pTcpIp->SendNetMessage( m_commOut );
			}
			CDmitronBattleTax::SetSubType( nSubType );
			return 1;
		}

		else if (pMob->m_nMobNum == NPC_INDEX_PCBANG_PET)
		{
			g_pNk2DFrame->ToggleEventAncientWindow(EVENT_TYPE_PCBANG_ARUPAKA);
			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_CHARM_BANI )
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_GREENBUD_2011 );
			return 1;
		}
		else if(pMob->m_nMobNum == 742 ) //���� ���� ���� ��ȯ npc
		{
			if( pCMyApp->m_nCurWorldIdx == WORLD_FIELD ) // WORLD_START
			{
				g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_BIRTH_CELEBRATE_2010 );
				return 1;

			}
		}

		//------------------------------------------------------------------
		else if( pMob->m_nMobNum == NPC_INDEX_MCEE )
		{
			pCMyApp->StopHero();

			if( IsInvenLock() )
				return 1;


			//wan:2004-11
			// ��Ʈ���� �Էµ��� �ʾҽ�
			// ��ǰ�� �ֵ���� �� �������� �޴°ɷ� ����..
			g_pTcpIp->SendNetMessage( "req_gwar_prize\n" );
			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_PRESENCE_EMCEE )
		{
			pCMyApp->StopHero();

			if( IsInvenLock() )
				return 1;

			// by evilkiki 2009.10.13 �⼮�̺�Ʈ�� ��ȸ��
			// "attend"
			if( g_pTcpIp )
				g_pTcpIp->SendNetMessage( "attend\n" );
			return 1;
		}
		//------------------------------------------------------------------
		// �÷�Ƽ�� NPC
		else if(pMob->m_nMobNum == 76 && pCMyApp->m_nCurWorldIdx == WORLD_FIELD )
		{
			if( g_SvrType == ST_ADULT_ONLY ) // [2/27/2007 Theodoric] ��þƮ
				g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_ENCHANT, pMob->GetMobName() );
			else
				g_pNk2DFrame->TogglePlatinumExchWindow(1);

			return 1;
		}
		//------------------------------------------------------------------
		// ��̳� NPC
		else if (pMob->m_nMobNum == 266 || pMob->m_nMobNum == 269)
		{
			g_pNk2DFrame->ToggleEventAncientWindow(1);
			return 1;
		}
		//------------------------------------------------------------------
		// ����̳� Event
		// 2004.05.03
		// Lyul / �����Ϸ�
		else if(pMob->m_nMobNum == 267 || pMob->m_nMobNum == 268) // NPC ����
		{
			g_pNk2DFrame->ToggleEventAncientWindow(2);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//3.1�� �̺�Ʈ(������ NPC)
		else if ( pMob->m_nMobNum == 447 )
		{
			g_pNk2DFrame->ToggleEventAncientWindow(6);
			return 1;
		}
		//------------------------------------------------------------------
		// �޸� ��������.
		else if (pMob->m_nMobNum == 51)
		{
			g_pNk2DFrame->ToggleProductWindow(TRUE);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//------------------------------------------------------------------
		// ���� ���� NPC 67
		else if(pMob->m_nMobNum == 67)
		{
			g_pNk2DFrame->TogglePetProductWindow(TRUE);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//------------------------------------------------------------------
		else if(pMob->m_nMobNum == 167)
		{
			if(!g_pNk2DFrame->CloseAllWindow())
				return 1;

			if(m_bIsGuildWar)
				m_bIsGuildWar = FALSE;
			else
				m_bIsGuildWar = TRUE;

			static int mode = -1;

			if(m_bIsGuildWar)
			{
				pCMyApp->StopHero();

				if(m_pGuildWar)
				{
					delete m_pGuildWar;
					m_pGuildWar = NULL;
				}
				m_pGuildWar = new CGuildWar(mode);
			}
			return 1;
		}
		//------------------------------------------------------------------
		// ����� npc
		else if (pMob->m_nMobNum == 176)
		{
			if (!g_pNk2DFrame->CloseAllWindow())
				// �������̽� �����찡 �� ������ ��쿡�� ����.
				return 1;

			if(m_bIsChangeHair)
				m_bIsChangeHair = FALSE;
			else
				m_bIsChangeHair = TRUE;

			if(m_bIsChangeHair)
			{
				pCMyApp->StopHero();

				if (m_pChangeHair)
				{
					delete m_pChangeHair;
					m_pChangeHair = NULL;
				}
				m_pChangeHair = new CChangeHair();

				// nate 2004 - 4
				// CastleWar
				// ���ֱ����������� 10% ���ΰ��� ����
				char tmp[100];
				if( IsMasterGuild()
						&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
							 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN ) )
					// IDS_UIMGR_PET_PRICE : ��� : 100,000 ����
					strcpy(tmp, G_STRING(IDS_UIMGR_PET_PRICE));
				else
					// IDS_UIMGR_PET_PRICE2 : ��� : 100,000 ����
					strcpy(tmp, G_STRING(IDS_UIMGR_PET_PRICE2));

				m_pChangeHair->m_pText->SetString(tmp);
			}
			return 1;
		}
		//------------------------------------------------------------------
		// �ֿϵ��� ���� ����
		else if(pMob->m_nMobNum == 188)
		{
			if( g_MyPetStatus.m_Class >= 3 )
			{
				g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_NEWPET_MSG3) , TYPE_NOR_OK, 1);
				return 1;
			}

			if(!g_pNk2DFrame->CloseAllWindow())
				return 1;
			if(m_bIsPetShop)
				m_bIsPetShop = FALSE;
			else
				m_bIsPetShop = TRUE;

			if(m_bIsPetShop)
			{
				if ( NULL != pCMyApp )
					pCMyApp->StopHero();
				SAFE_DELETE(m_pPetShop);

				m_pPetShop = new CControlPetShop2();
				m_pPetShop->LoadRes();
			}
			return 1;
		}
		//------------------------------------------------------------------
		// �ֿϵ��� ������
		else if(pMob->m_nMobNum == 189)
		{
			pCMyApp->StopHero();

			if( g_MyPetStatus.mode == MYPET_MODE_NONE )
			{
				// IDS_UIMGR_PET_NOTUSE : ���� �����ϼž� �̿��Ͻ� �� �ֽ��ϴ�
				CmdErrorMsg((char*)G_STRING(IDS_UIMGR_PET_NOTUSE));
			}
			else
			{
				if(!g_pNk2DFrame->CloseAllWindow())
					return 1;

				char tmp[100];
				sprintf(tmp, "p_keep open\n");

				if (g_pTcpIp)
					g_pTcpIp->SendNetMessage(tmp);
			}
			return 1;
		}
		//------------------------------------------------------------------
		else if(pMob->m_nMobNum == 190)
		{
			pCMyApp->StopHero();

			if(g_MyPetStatus.mode==MYPET_MODE_NONE)
			{
				// IDS_PETLEV_PRE_BUY : ���� �ֿϵ����� ��ž� �մϴ�.
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_PETLEV_PRE_BUY), TYPE_NOR_OK, 1 );
				return 1;
			}
			else if(g_MyPetStatus.mode==MYPET_MODE_EGG)
			{
				// IDS_PETLEV_PRE_REVIVE : ���� �ֿϵ����� ��ȭ���Ѿ� �մϴ�.
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_PETLEV_PRE_REVIVE), TYPE_NOR_OK, 1 );
				return 1;
			}
			else if(g_MyPetStatus.mode==MYPET_MODE_KEEP || g_MyPetStatus.mode==MYPET_MODE_HOLD)
			{
				// IDS_PETLEV_PRE_TAKE : ���� �ֿϵ����� ã���ž� �մϴ�.
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_PETLEV_PRE_TAKE), TYPE_NOR_OK, 1 );
				return 1;
			}
			if( g_pNk2DFrame )
				g_pNk2DFrame->ShowPetLevelMenu();//pCha);
			return 1;
		}
		//------------------------------------------------------------------
		// ������ȯ npc
		else if (pMob->m_nMobNum == 175)
		{
			if (!g_pNk2DFrame->CloseAllWindow())
				// �������̽� �����찡 �� ������ ��쿡�� ����.
				return 1;


			if( g_pRoh->IsWearing() ) // ���� ���� ��� ������ ���¿��� ������ ��ȯ�ϸ� Ŭ�� ƨ���. ��� ��� ������ �Ѵ�.
			{
				pCMyApp->StopHero();

				// IDS_PLZ_KIT_OFF �̺�Ʈ �ǻ�� ��� Ż���Ͻʽÿ�.
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_PLZ_KIT_OFF), TYPE_NOR_OK, 1 );
				return 1;
			}

			if(m_bIsChSexBox)
				m_bIsChSexBox = FALSE;
			else
				m_bIsChSexBox = TRUE;

			if(m_bIsChSexBox)
			{
				pCMyApp->StopHero();

				if (m_pChSexBox)
					delete m_pChSexBox;

				m_pChSexBox = new CScrollBox(TYPE_DELIV_BOX);
				m_pChSexBox->Init(5, 5);

				int sex = g_pRoh->m_Sex;
				char tmp[100];

				if(sex == 0)
					// IDS_UIMGR_CHASEX_BOY_GIRL : ������ ���ڿ��� ���ڷ� ��ȯ
					strcpy(tmp, G_STRING(IDS_UIMGR_CHASEX_BOY_GIRL));
				else
					// IDS_UIMGR_CHASEX_GIRL_BOY : ������ ���ڿ��� ���ڷ� ��ȯ
					strcpy(tmp, G_STRING(IDS_UIMGR_CHASEX_GIRL_BOY));

				// IDS_UIMGR_CHASEX_EVENT_TITLE : ������ȯ �̺�Ʈ
				m_pChSexBox->SetTitleStr((char*)G_STRING(IDS_UIMGR_CHASEX_EVENT_TITLE));

				if( !(g_bGlobalMatrix && g_MatrixSvr != 0) ) ///���������� ������ȯ�� ��¥.
				{
					//==============================================================
					// nate 2004 - 4
					// CastleWar
					// ���ֱ����������� 10% ���ΰ��� ����
					if( IsMasterGuild()
							&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
								 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN ) )
						// IDS_UIMGR_CHASEX_TEXT0 : ������ȯ�� �ʿ��� �ݾ��� 90��
						m_pChSexBox->SetAddStr( (char*)G_STRING(IDS_UIMGR_CHASEX_TEXT0));
					else
						// IDS_UIMGR_CHASEX_TEXT0_1 : ������ȯ�� �ʿ��� �ݾ��� 100��
						m_pChSexBox->SetAddStr( (char*)G_STRING(IDS_UIMGR_CHASEX_TEXT0_1));
					//==============================================================
					// IDS_UIMGR_CHASEX_TEXT1 : ���� �Դϴ�.
					// m_pChSexBox->SetAddStr((char*)G_STRING(IDS_UIMGR_CHASEX_TEXT1));
				}
				m_pChSexBox->SetAddStr("   ");
				m_pChSexBox->SetAddStr(tmp);
				// IDS_UIMGR_CHASEX_TEXT2 : �Ͻð� ���ϱ�?
				m_pChSexBox->SetAddStr((char*)G_STRING(IDS_UIMGR_CHASEX_TEXT2));
				m_pChSexBox->LoadRes();
			}
			else
			{
				if(m_pChSexBox)
					SAFE_DELETE(m_pChSexBox);
			}
			return 1;
		}
		//------------------------------------------------------------------
		else if(pMob->m_nMobNum == 191) // �ǽ� �Ĵ� ��
		{
			switch (g_MyPetStatus.mode)
			{
			case MYPET_MODE_NONE:
				pCMyApp->StopHero();
				// IDS_UIMGR_PET_SRVMSG_NOTEXIST : ����� �ֿϵ����� �⸣�� ���� �ʽ��ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_UIMGR_PET_SRVMSG_NOTEXIST),TYPE_NOR_OK, 1);
				break;
			case MYPET_MODE_EGG:
				pCMyApp->StopHero();
				// IDS_UIMGR_PET_SRVMSG_NOT_YET : ����� �ֿϵ����� ���� ��ȭ���� �ʽ��ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_UIMGR_PET_SRVMSG_NOT_YET),TYPE_NOR_OK, 1);
				break;
			case MYPET_MODE_KEEP://�����߿��� �Ľ� ���� �ȵǰ�
				pCMyApp->StopHero();
				// IDS_UIMGR_PET_SRVMSG_KEEPING : ����� �ֿϵ����� ���� ���������Դϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_UIMGR_PET_SRVMSG_KEEPING),TYPE_NOR_OK, 1);
				break;
			case MYPET_MODE_HOLD:
				g_pNk2DFrame->TogglePeiceShopWindow();
				break;
			default:
				g_pNk2DFrame->TogglePeiceShopWindow();
				break;
			}
			return 1;
		}
		else if( pMob->m_nMobNum == 446 ) ///�븸����̺�Ʈ
		{
			g_pNk2DFrame->ToggleEventAncientWindow(7);
			return 1;
		}
		else if( pMob->m_nMobNum == 425 && pCMyApp->m_nCurWorldIdx == WORLD_START ) // ����� ///�޴��������̽�
		{
			if( IsInvenLock() )
				return 1;

			// �˻��� ���� ȸ���� ���� ���� �޴� �������̽��� ����.
			g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_USERSHOP, pMob->GetMobName() ); // �޴� ����. �ϴ� ���⸸ ������ �ȴ�.

			return 1;
		}
		else if( pMob->m_nMobNum == 473 ) // �±� ũ�������� Ʈ��
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_THAI_XMAS_TREE ); // �±� ũ�������� �¸����� �� ��ȯ
			return 1;
		}
		// �̺�Ʈ ���� �ߵ���
		else if(pMob->m_nMobNum == 503 ) // [9/11/2007 Theodoric] 2007�� �߼��̺�Ʈ ������ ���뺹�� ü�� NPC
		{
			pCMyApp->StopHero();

			if( g_pTcpIp )
				g_pTcpIp->SendNetMessage( "v_c\n" ); //mungmae 2006/04/24  250~274 ����� ����Ʈ
			return 1;
		}

		else if(pMob->m_nMobNum == NPC_INDEX_DECARDI_BATTLE)
		{
			pCMyApp->StopHero();
			SendDecardiBattleReq();
			
			return 1;
		}

		else if (pMob->m_nMobNum == 509) // [5/7/2008 �����] �±� ���� ���� �̺�Ʈ �Ҿƹ���
		{
			if( m_bPocketPapa_Click )
				return 1;

			float	dx, dz;
			dx = pMob->m_wx - g_pRoh->m_wx;
			dz = pMob->m_wz - g_pRoh->m_wz;

			g_pRoh->m_toDir = (float) atan2(dz, dx);
			g_pRoh->SetMotionState(CHA_SOCIAL, 74);
			pCMyApp->StopHero();

			if(g_pTcpIp)
			{
				// [5/7/2008 �����] �±� ���� ���� �̺�Ʈ ��Ŷ �߰� �κ�
				sprintf(tmp, "ev_buff\n");
				g_pTcpIp->SendNetMessage(tmp);

				sprintf(tmp, "stop %.0f %.0f %.0f %.0f\n", g_pRoh->m_wx, g_pRoh->m_wz, g_pRoh->m_wy, (g_pRoh->m_toDir) * 10000);
				g_pTcpIp->SendNetMessage(tmp);

				sprintf(tmp, "social 74\n");
				g_pTcpIp->SendNetMessage(tmp);
			}

			m_bPocketPapa_Click = TRUE;

			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_GOODS )
		{
			g_pNk2DFrame->CloseAllWindow();

			if( g_pNk2DFrame->ShowTakeboxWindow(true, TakeBox_Type__User) )
				return 1;

			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_PRESENT )
		{
			g_pNk2DFrame->CloseAllWindow();

			if( g_pNk2DFrame->ShowTakeboxWindow(true, TakeBox_Type__Character) )
				return 1;

			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_PRESENT_SERVERMOVE )
		{
			g_pNk2DFrame->CloseAllWindow();

			if( g_pNk2DFrame->ShowTakeboxWindow(true, TakeBox_Type__ServerMove) )
				return 1;

			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_EVENT_MAD )
		{
			g_pNk2DFrame->CloseAllWindow();
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_EVENT_MAD_INPUT), TYPE_EXCHANGE, POPUP_EVENT_MAD_INPUT);
			
			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_BATTLELEAGE )
		{
			g_pNk2DFrame->CloseAllWindow();
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_BATTLELEAGUE_POPUP), TYPE_NOR_OKCANCLE, POPUP_BATTLELEAGUE);
			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_GIFTTIME )
		{	
			g_pNk2DFrame->CloseAllWindow();
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_GIFTTIME_POPUP), TYPE_NOR_OKCANCLE, POPUP_GIFTTIME);
			return 1;
		}
		else if (pMob->m_nMobNum == NPC_INDEX_BLESS_BANI)
		{
			pCMyApp->StopHero();
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_LP_PRESENT_BOX );
			return 1;

		}		
		else if (pMob->m_nMobNum == NPC_INDEX_SANTA_BANI)
		{
			pCMyApp->StopHero();
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_GOD_WEAPON_EXPERIENCE );
			return 1;
		}
		else if( pMob->m_nMobNum == NPC_INDEX_KAIN )
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_FORLOM_MAP );
			return 1; 
		}
		else if( pMob->m_nMobNum == NPC_INDEX_ROONY )
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_FORLOM_DEVICE );
			return 1; 
		}
		else if(pMob->m_nMobNum == NPC_INDEX_SCIENTIST )
		{
			int limit_level = 350;
			if( pCMyApp->GetCurWorld() == WORLD_DMITRON )
			{
				if( g_pRoh->m_Level < limit_level )
				{
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LHSTRING1888) , TYPE_NOR_OK, 1);
					return 1;
				}
				g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_FORLOM_DEVICE_DM );
				return 1;
			}
		}



		else if ( pMob->m_nMobNum == NPC_INDEX_BUFFMAKE )
		{
			g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_BUFFMAKE, pMob->GetMobName() );
			return 1;
		}
		else if ( pMob->m_nMobNum == NPC_INDEX_ITEMMAKE )
		{
			switch( pCMyApp->m_nCurWorldIdx )
			{
			case WORLD_START:
				g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYEP_ITEMMAKE, pMob->GetMobName() );
				return 1;
			}
		}
		else if ( pMob->m_nMobNum == NPC_INDEX_10YEAREVENT )
		{
			switch( pCMyApp->m_nCurWorldIdx )
			{
			case WORLD_START:
			case WORLD_DMITRON:
			case WORLD_DISPOSAL:
				g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_10YEAR_ITEM );
				return 1;
			}
		}
		else if ( pMob->m_nMobNum == NPC_INDEX_MAGICSTONE ) //������ȯ��
		{
			g_pNk2DFrame->ToggleUpgradeWindow( INTERFACE_TYPE_GMAGICSTONE );
			return 1;
		}


		else if ( pMob->m_nMobNum == NPC_INDEX_DEVICE )
		{
			g_pNk2DFrame->ToggleEventAncientWindow( EVENT_TYPE_S1TOS2 );
			return 1;
		}

		g_pNk2DFrame->ToggleShopWindow();
		if (g_pNk2DFrame->IsShopVisible())
		{
			g_pNk2DFrame->GetControlShop()->SetKeeper(pMob->m_nVirId, pMob->m_wx, pMob->m_wz);
			sprintf(m_commOut, "shop %d %.0f %.0f\n", pMob->m_nVirId, pMob->m_wx, pMob->m_wz);
			g_pTcpIp->SendNetMessage(m_commOut);

			if( pMob->m_nMobNum == 380 ) // BP ���� NPC �ȳ��� �޴�������ϴ� ����ó��
				g_pNk2DFrame->ToggleShopWindow(); // �ٽ� �ݾ��ش�.
		}
		return 1;
	}
	else if (pMob->m_nMobNum == 450)
	{
		pCMyApp->StopHero();

		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage( "quest click 450\n" ); //mungmae 2006/04/24  250~274 ����� ����Ʈ
		return 1;
	}
	//------------------------------------------------------------------------
	// Shop �� �ƴϳ� ����� ������ �ϴ°�.
	//------------------------------------------------------------------------
	else
	{
		// ������ �������� �������̽�  = ������ ���Ϸ� ������ Ŭ��!! (�α渶 �̻�� Ŭ�� ����)
		if (!m_bOnBattle
				&& pMob->m_nMobNum == 135
				&& IsMasterGuild()
				&& g_pRoh->m_GuildLevel >= 9)
		{
			if (!g_pNk2DFrame->CloseAllWindow())
				// �������̽� �����찡 �� ������ ��쿡�� ����.
				return 1;

			if(m_bIsWarTax)
				m_bIsWarTax = FALSE;
			else
				m_bIsWarTax = TRUE;

			if(m_bIsWarTax)
			{
				pCMyApp->StopHero();

				if (m_pWarTax)
				{
					delete m_pWarTax;
					m_pWarTax = NULL;
				}
				// ���� ¡�� �ݾװ�, ����¡������ ������ ���� �޾Ƽ� ó���Ѵ�.
				m_pWarTax = new CWarTax();
			}
			return 1;
		}
		// nate 2004 - 4
		// CastleWar
		// ������ ��û!! = ���Ϸ� ������ Ŭ��!!
		else if ( !m_bOnBattle
				  && ( pMob->m_nMobNum == 136
					   || pMob->m_nMobNum == 319 )
				  && strlen( m_MasterGuild1 ) > 0 )
		{
			if( !g_pNk2DFrame->CloseAllWindow() )
				return 1;

			if( m_bIsWarReq )
				m_bIsWarReq = FALSE;
			else
				m_bIsWarReq = TRUE;

			if( m_bIsWarReq )
			{
				pCMyApp->StopHero();

				if( m_pWarReq )
				{
					delete m_pWarReq;
					m_pWarReq = NULL;
				}
				// ���� ¡�� �ݾװ�, ����¡�� ���� ������ ���� �޾Ƽ� ó���Ѵ�.
				m_pWarReq = new CWarRequest();
			}
			return 1;
		}
		//--------------------------------------------------------------------
		// ��ȣž ����!!  = ����Ÿ�� Ŭ��
		else if(!m_bOnBattle
				&& pMob->m_nMobNum >=179
				&& pMob->m_nMobNum <=187
				&& IsMasterGuild()
				&& g_pRoh->m_GuildLevel >= 10)
		{
			if(!g_pNk2DFrame->CloseAllWindow())
				return 1;
			if(m_bIsTower)
				m_bIsTower = FALSE;
			else
				m_bIsTower = TRUE;

			if(m_bIsTower)
			{
				pCMyApp->StopHero();

				if(m_pTower)
				{
					delete m_pTower;
					m_pTower = NULL;
				}
				m_pTower = new CGuardTower(pMob->m_nMobNum, pMob->m_nVirId, pMob->m_Mutant);
			}
			return 1;
		}
		//--------------------------------------------------------------------
		// �������� ���� "���������" ���� Ȯ��..
		else if((pMob->m_nMobNum == 177
				 || pMob->m_nMobNum == 178)
				&& g_pRoh->m_ExtraSlot
				&& g_pRoh->m_ExtraSlot->m_Vnum == 613)
		{
			pCMyApp->StopHero();

			bool available = false;
			if( g_pRoh->m_pstrGuildName )
			{
				if( pCMyApp->GetCurWorld() == WORLD_GUILD )
				{
					if( !strcmp( g_pRoh->m_pstrGuildName, pCMyApp->m_pUIMgr->m_MasterGuild1 ) )
					{
						available = true;
					}
				}
				else if( pCMyApp->GetCurWorld() == WORLD_WHITEHORN )
				{
					if(!strcmp(g_pRoh->m_pstrGuildName, m_SubGuild[0])
							|| !strcmp(g_pRoh->m_pstrGuildName, m_SubGuild[1])
							|| !strcmp(g_pRoh->m_pstrGuildName, m_SubGuild[2])
							|| !strcmp(g_pRoh->m_pstrGuildName, m_SubGuild[3]) )
					{
						available = true;
					}
				}
			}
			else
			{
			}
			if( available )
			{
				char tmp[100];
				sprintf(tmp, "upenergy %d %d\n",  pMob->m_nVirId, pMob->m_nMobNum);
				if (g_pTcpIp)
					g_pTcpIp->SendNetMessage(tmp);
			}
			else
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_LHSTRING1886) , -1);
			}
		}
		//--------------------------------------------------------------------
		// ��� ����
		else if (pMob->m_nMobNum == 117)
		{
			g_pNk2DFrame->ToggleInterchangeWindow(TRUE);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//--------------------------------------------------------------------
		// �޸� ��������.
		else if (pMob->m_nMobNum == 51)
		{
			g_pNk2DFrame->ToggleProductWindow(TRUE);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//--------------------------------------------------------------------
		// ���� ���� NPC	67
		else if (pMob->m_nMobNum == 67)
		{
			g_pNk2DFrame->TogglePetProductWindow(TRUE);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//--------------------------------------------------------------------
		// �÷�Ƽ�� NPC
		else if(pMob->m_nMobNum == 76 && pCMyApp->m_nCurWorldIdx == WORLD_FIELD )
		{
			if( g_SvrType == ST_ADULT_ONLY ) // [2/27/2007 Theodoric] ��þƮ ���� ����
				g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_ENCHANT, pMob->GetMobName() );
			else
				g_pNk2DFrame->TogglePlatinumExchWindow(1);

			return 1;
		}
		//--------------------------------------------------------------------
		// ���� ��� NPC 96
		else if(pMob->m_nMobNum == 322)
		{
			g_pNk2DFrame->ToggleSummerEventWindow(0);
			return 1;
		}
		//--------------------------------------------------------------------
		// �������255,���Ҿƹ���,��������257
		else if (pMob->m_nMobNum == 257)
		{
			g_pNk2DFrame->ToggleEventAncientWindow(0);
			if (which_button == BUTTON_RIGHT)
			{
				pCMyApp->EndRotateCamera();
				which_button = BUTTON_LEFT;
			}
			return 1;
		}
		//--------------------------------------------------------------------
		// ���Ϸ� ������
		else if (pMob->m_nMobNum == 136 || pMob->m_nMobNum == 319)
		{}
		else if( pMob->m_nMobNum == 463 ) // �±� 3�ֳ� ��� ����
		{
			// Ŭ���� �Ҳ� ��.
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));
			// �Ҳ� �߰�.
			ef_sort.nType = FX_FIREWORKS;
			ef_sort.vPos = D3DVECTOR(pMob->m_wx, pMob->m_wy, pMob->m_wz);
			ef_sort.num = rand()%4;
			if( g_pDSound )
			{
				switch(ef_sort.num)
				{
				case 0:
					g_pDSound->Play(g_EffectSound[EFF_SND_FIREWORKS_4]);
					break;
				case 1:
					g_pDSound->Play(g_EffectSound[EFF_SND_FIREWORKS_RAINBOW]);
					break;
				case 2:
					g_pDSound->Play(g_EffectSound[EFF_SND_FIREWORKS_SCREW]);
					break;
				case 3:
					g_pDSound->Play(g_EffectSound[EFF_SND_FIREWORKS_FOUNTAIN]);
					break;
				}
			}

			pMob->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );

			return 1;
		}
		else if( pMob->m_nMobNum == 465 && pCMyApp->GetCurWorld() == 1 ) // ��ī�� ����� ���� ��. ///�δ�1
		{
			pCMyApp->StopHero();

			// ���踦 üũ�Ѵ�.
			CItem *pKeyItem = NULL;
			pKeyItem = g_pRoh->FindItemByVnumFromAll( 1490 ); // ��ī�� ö�� ���谡 �ִ��� üũ.

			if( pKeyItem ) // ������..
			{
				// �� ����޶�� ��Ŷ�� ������.
				int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

				if( PackNum >= 0 && PackNum <=PACK_NUM ) // �κ��� ��ȯâ�� ����.
				{
					sprintf(m_commOut, "use_key %d %d %d\n", PackNum, pKeyItem->m_Index, pMob->m_nVirId );
					if( g_pTcpIp )
						g_pTcpIp->SendNetMessage(m_commOut);

					return 1;
				}
			}
		}
		else if( pMob->m_nMobNum == 504 ) //����Ʈ �̵� ��Ż
		{
			pCMyApp->StopHero();

			if (pCMyApp->GetCurWorld() == WORLD_DMITRON ) // ���Ʈ�� �ܺ� ��Ż
			{
				int nSubType = CDmitronZone::SearchGateStone(pMob->m_wx, pMob->m_wz);
				if (nSubType >= 0)
				{
					if( g_pTcpIp )
					{
						sprintf(m_commOut, "occp bt go %d\n", nSubType);
						g_pTcpIp->SendNetMessage(m_commOut);
					}
				}
				return 1;
			}
		}
		//--------------------------------------------------------------------
		else if (pMob->m_Flag & NPC_GUARD)
		{
			if( pMob->m_nMobNum == 57 && IsEventScenePlaying() == 5 ) ///Ʃ�丮�� ���̸� ������ Ŭ�� ����
				return 1;


			// ��Ʈ �� ������...�ʱ�ȭ!!!
			// by evilkiki 2009.10.13
			pCMyApp->StopHero();

			if(Level <  100)
				iAdd = 4;
			else if(Level >= 100 && Level < 120)
				iAdd = 7;
			else if(Level >= 120)
				iAdd = 10;

			expense = (Level*Level*Level)*iAdd / 10;	// 10 �� ���Ӵ��� ����.
			//==============================================================
			// nate 2004 - 4
			// CastleWar
			// ���ֱ����������� 10% ���ΰ��� ����
			if( IsMasterGuild()
					&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
						 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN ) )
				expense = expense - ( expense * 3 / 10 );

			//==============================================================
			// IDS_UIMGR_SPOPUP_LINE_01 : ��й� ������ %d ��
			sprintf(tmp,G_STRING(IDS_UIMGR_SPOPUP_LINE_01), (expense));

			if(m_bIsScrollBox)
				m_bIsScrollBox = FALSE;
			else
				m_bIsScrollBox = TRUE;

			if(m_bIsScrollBox)
			{
				switch(g_pRoh->m_Race)
				{
				case RACE_BULKAN:
					Str = 30, Int = 5, Dex = 5,	Con = 30, Cha = 10;
					Max_Str = 30, Max_Int = 10, Max_Dex = 10, Max_Con = 30, Max_Cha = 20;
					break;
				case RACE_KAILIPTON:
					Str = 15, Int = 30, Dex = 5, Con = 15, Cha = 15;
					Max_Str = 15, Max_Int = 30, Max_Dex = 20, Max_Con = 15, Max_Cha = 20;
					break;
				case RACE_AIDIA:
					Str = 15, Int = 30, Dex = 5, Con = 15, Cha = 15;
					Max_Str = 15, Max_Int = 30, Max_Dex = 20, Max_Con = 15, Max_Cha = 20;
					break;
				case RACE_HUMAN:
					Str = 15, Int = 5, Dex = 30, Con = 20, Cha = 10;
					Max_Str = 20, Max_Int = 20, Max_Dex = 30, Max_Con = 20, Max_Cha = 20;
					break;
				case RACE_FREAK:
					Str = 30, Int = 10, Dex = 10, Con = 25, Cha = 5;
					Max_Str = 30, Max_Int = 20, Max_Dex = 20, Max_Con = 35, Max_Cha = 15;
					break;
				case RACE_PEROM:
					Str = 30, Int = 10, Dex = 10, Con = 25, Cha = 5;
					Max_Str = 30, Max_Int = 20, Max_Dex = 20, Max_Con = 35, Max_Cha = 15;
					break;
				}

				sprintf(Tmp2, "(%d)   (%d)   (%d)   (%d)   (%d)", Max_Str, Max_Int, Max_Dex, Max_Con, Max_Cha);
				if (m_pScrollBox)
					delete m_pScrollBox;
				m_pScrollBox = new CScrollBox(TYPE_REDISTRIBUTION);
				m_pScrollBox->Init(6, 6);
				// IDS_UIMGR_SPOPUP_TITLE : ����Ʈ ��й�
				m_pScrollBox->SetTitleStr((char*)G_STRING(IDS_UIMGR_SPOPUP_TITLE));
				m_pScrollBox->SetAddStr(tmp);
				// IDS_UIMGR_SPOPUP_LINE_02 : �Դϴ�.
				m_pScrollBox->SetAddStr((char*)G_STRING(IDS_UIMGR_SPOPUP_LINE_02));
				// IDS_UIMGR_SPOPUP_LINE_03 : �ʱ�ȭ�� ��ġ�� �Է��� �ּ���.
				m_pScrollBox->SetAddStr((char*)G_STRING(IDS_UIMGR_SPOPUP_LINE_03));
				// IDS_UIMGR_SPOPUP_LINE_04 : ( )���� ���� �ִ밪!! �ּҰ�:5
				m_pScrollBox->SetAddStr((char*)G_STRING(IDS_UIMGR_SPOPUP_LINE_04));
				// IDS_UIMGR_SPOPUP_LINE_05 : ��    ����  ��μ�  ü��  ��ַ�
				m_pScrollBox->SetAddStr((char*)G_STRING(IDS_UIMGR_SPOPUP_LINE_05));
				m_pScrollBox->SetAddStr(Tmp2);
				m_pScrollBox->PreSetValForInBox(Str, Int, Dex, Con, Cha);
				m_pScrollBox->LoadRes();
			}
			//--------------------------------------------------------------------
			else
			{
				if(m_pScrollBox)
					SAFE_DELETE(m_pScrollBox);
			}

			return 1;
			// �������� ���߿� ó��...
		}
	} // end of if NPC_SHOPKEPPER else

	return 0;
}


int CUIMgr::CmdClick(int which_button, WPARAM wParam,int mx, int my)
{
	if (g_bGhost)
		return 0;

	if(pCMyApp->IsSoccerZone() && which_button == BUTTON_RIGHT)
		return 0;

	BOOL bGuildwar = FALSE;

	bControlKey = FALSE;
	if( MK_CONTROL & wParam )
		bControlKey = TRUE;

	CNkMob *pMob = NULL;
	CNkPet *pPet = NULL;
	CNkCharacter *pCha = NULL;

	m_bNextAction = FALSE;
	int cur_skill = 0;
	if(which_button == BUTTON_RIGHT)
		cur_skill = g_pNk2DFrame->GetRSkill();
	else
		cur_skill = g_pNk2DFrame->GetLSkill();

	if( which_button == BUTTON_RIGHT && cur_skill == SELECTED_SKILL_ROTATE )
		return 0;

	if(m_bWorldCupDash)
	{
		sprintf(m_commOut, "use_effect %d %d\n", 1, TRUE);
		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage(m_commOut);
	}

	if(which_button == BUTTON_LEFT
			&& (m_b_Attack || m_b_SecAttack || m_bChakramAtt || m_bBookSpellAtt )
			&& g_pRoh->GetMotionState() != CHA_C_HELLDOWN )// || m_b_MovingForAttack))
	{
		m_b_Attack			= false;
		m_b_MovingForAttack = false;
		m_b_SecAttack		= false;
		m_bChakramAtt		= false;
		m_bChakram			= false;
		m_bBookSpellAtt 	= false;
		m_bBookSpell		= false;
		return 0;
	}
	else
	{
		if(which_button == BUTTON_RIGHT)
		{
			if( g_pRoh->GetMotionState() == CHA_F_DASH && g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_A_DSLASH )
			{
				D3DVECTOR ptVec;

				if( m_pLand->PickPoint(ptVec, mx, my) == TRUE )
				{
					if( !pCMyApp->IsInsideMap(ptVec.x,ptVec.z) )
						return 0;

					if( m_bNextGoto )
					{
						float fDist = DistPlToPlAbs(g_pRoh->m_wx,g_pRoh->m_wz, ptVec.x,ptVec.z);

						D3DVECTOR Temp;

						Temp.x = ptVec.x - g_pRoh->m_wx;
						Temp.y = 0.0f;
						Temp.z = ptVec.z - g_pRoh->m_wz;

						Temp = Normalize(Temp);

						if( pCMyApp->GetSkillDistance(g_ChaSkill.GetArrayIndex(SKILLF_A_DASH)) < fDist )
						{
							Temp *= pCMyApp->GetSkillDistance( g_ChaSkill.GetArrayIndex(SKILLF_A_DASH) );

							ptVec.x = Temp.x + g_pRoh->m_wx;
							ptVec.z = Temp.z + g_pRoh->m_wz;

							fDist = pCMyApp->GetSkillDistance( g_ChaSkill.GetArrayIndex(SKILLF_A_DASH) );
						}

						if( pCMyApp->SkillConditionCheck(cur_skill)
								&& m_pLand->IsMovableArea(ptVec.x, ptVec.z)
								&& fDist > 15.0f
								&& IsNotBlocked(g_pRoh->m_wx, g_pRoh->m_wz, ptVec.x, ptVec.z)
								&& g_pRoh->GetMotionState() != CHA_F_SHADOWSLASH )
						{	
							SendCharUseSkill_Position(SKILL_F_DASHSLASH, ptVec.x, ptVec.z);

							g_pRoh->m_bComboSucceed = true;
							m_b_MotionForAttack = TRUE; // �̰� ����� �� �ִϸ��̼��� ������ �����ش�.
						}
					}
					return 1;
				}
			}

			if( g_pRoh->GetMotionState() == CHA_F_DASHSLASH
					&& g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_F_SHADOWSLASH
					&& timeGetTime()-g_pRoh->m_dwComboTick > 500
					&& timeGetTime()-g_pRoh->m_dwComboTick < 1000 )
			{
				if( bControlKey )
				{
					if( pCha = GetCharacterByColorKey(m_wColor) )
					{
						float fDist = DistPlToPlAbs( g_pRoh->m_wx,g_pRoh->m_wz, pCha->m_wx,pCha->m_wz );

						if( pCMyApp->SkillConditionCheck(cur_skill)	&& fDist < ATTACK_RANGE+30.0f )
						{
							pCMyApp->SetHeroAttGoCha( pCha );
							pCMyApp->AttackMsgSend( SKILL_F_SLASHSHADOW );

							g_pRoh->m_bComboSucceed = true;
						}

						return 1;
					}
				}
				else
				{
					if( pMob = GetMobByColorKey( m_wColor ) )
					{
						float fDist = DistPlToPlAbs( g_pRoh->m_wx,g_pRoh->m_wz, pMob->m_wx,pMob->m_wz );

						if( pCMyApp->SkillConditionCheck(cur_skill) && fDist < ATTACK_RANGE+30.0f )
						{
							pCMyApp->SetHeroAttGoMob( pMob );
							pCMyApp->AttackMsgSend( SKILL_F_SLASHSHADOW );

							g_pRoh->m_bComboSucceed = true;

							return 1;
						}
					}
				}
				return 1;
			}

			if( g_pRoh->GetMotionState() == CHA_F_STONEBASH
					&& g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_E_REFLECTION
					&& pCMyApp->SkillConditionCheck(cur_skill) )
			{
				if( g_pRoh->Get_m_CurFrame() > 21 && g_pRoh->Get_m_CurFrame() < 30 )
					pCMyApp->AttackMsgSend( SKILL_F_BASHREFLECT1 );

				return 1;
			}

			m_nClickTimeCheck++;
			if( g_pRoh->m_bComboReady && m_nClickTimeCheck == 1 )
			{
				if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_THROW)
				{
					g_pRoh->SetMotionState(CHA_THROW_SLAYER);

					if(pCMyApp->m_pHeroAttGoMob)
						sprintf(m_commOut,
								"subat npc %d %d %d\n",
								pCMyApp->m_pHeroAttGoMob->m_nVirId,
								g_ChaSkill.m_SkillIndex[cur_skill],
								g_pRoh->m_nComboFrame );
					else if(pCMyApp->m_pHeroAttGoCha)
						sprintf( m_commOut,
								 "subat char %d %d %d\n",
								 pCMyApp->m_pHeroAttGoCha->m_nCharIndex,	// ĳ�� ���̵�
								 g_ChaSkill.m_SkillIndex[cur_skill],	// ���� ��ų��ȣ
								 g_pRoh->m_nComboFrame );	// �޺� ���� ����

					pCMyApp->m_pUIMgr->SendAttackMessage(m_commOut);
					g_pRoh->m_bComboSucceed = true;
					return 1;
				}
				else
					g_pRoh->m_bComboSucceed = false;
			}
			else
				g_pRoh->m_bComboSucceed = false;

			if(  g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_A_DSTONE
					&& pCMyApp->SkillConditionCheck(cur_skill)
					&& ( g_pRoh->m_wy > CNKObjQuadNode::GetHeightOnWater( g_pRoh->m_wz, g_pRoh->m_wx )
						 || ( g_pRoh->m_wy <= CNKObjQuadNode::GetHeightOnWater( g_pRoh->m_wz, g_pRoh->m_wx )
							  && pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_BULKAN  )) )
			{
				float x = g_pRoh->m_wx - cos(g_pRoh->m_toDir)  * 15.0f;
				float z = g_pRoh->m_wz - sin(g_pRoh->m_toDir)  * 15.0f;

				if(m_pLand->IsMovableArea(x, z))
				{
					// Motion
					pCMyApp->StopHero();
					g_pRoh->SetMotionState(CHA_F_DSTONE);					
					SendCharUseSkill_DStone(SKILLF_A_DSTONE, (int)(g_pRoh->m_toDir*10), x, z);
					InsertMagic(g_pRoh, NULL, g_pRoh, NULL, EFFECT_SKILL_DSTONE);

					m_b_MotionForAttack = true; // �� �༮�� Ȱ��ȭ ������� ������ �ڴ� ����߿� ������ ���Ѵ�.(Ǯ���°� �� ��� ������ Ǯ���� �Ǿ�����.) (05-10-27 ����)
					m_b_MovingForAttack= false;
					m_b_Attack= false;
					m_b_SecAttack = false;
					g_pRoh->m_bstone = false;       // ����� ������ ����߳�. Framemov���� ���� ������ ���� Ȱ��ȭ �ȴ�.
					g_pRoh->m_bresstone = false;    // ����� ������ ������ �غ� �ƴ°�.
					g_pRoh->m_resmobidx =0;    // ������ ���� �ε���
					g_pRoh->m_resmobvnum =0;   // ������ ���� vnum
					return 1;
				}
			}
			//--------------------------------------------------------------------
			// Ÿ�� ����
			else if(g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_A_TIMECHARGE)
			{
				pMob = FindMobById(g_pRoh->m_resmobidx);
				if(pCMyApp->SkillConditionCheck(cur_skill)
						&& pMob )
				{	
					SendCharUseSkill(g_ChaSkill.m_SkillIndex[cur_skill]);
					G_SK_SetCooltime(g_ChaSkill.m_SkillIndex[cur_skill]);
					pCMyApp->StopHero();
					g_pRoh->SetMotionState(CHA_F_TIMECHARGE);

					InsertMagic(g_pRoh, NULL, NULL, pMob, EFFECT_SKILL_TIMECHG);

					float m_dx = pMob->m_wx - g_pRoh->m_wx;
					float m_dz = pMob->m_wz - g_pRoh->m_wz;

					g_pRoh->m_toDir = (float) atan2(m_dz, m_dx);

					// ���� ��Ȱ��
					m_b_MotionForAttack = false;
					m_b_MovingForAttack= false;
					m_b_Attack= false;
					m_b_SecAttack = false;
					return 1;
				}
			}
			else if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_A_DASH
					 && ( g_pRoh->m_wy > CNKObjQuadNode::GetHeightOnWater( g_pRoh->m_wz, g_pRoh->m_wx )
						  || (g_pRoh->m_wy <= CNKObjQuadNode::GetHeightOnWater( g_pRoh->m_wz, g_pRoh->m_wx) &&
							  pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_BULKAN )))	// �� �� ��� �Ұ�.
			{
				static D3DVECTOR ptVec;

				// ���� ������ ��� �Ұ�.
				if (g_pRoh->m_CancelState == 1 &&
						(g_pRoh->m_ChaCondition == CONDITION_STONY ||
						 g_pRoh->m_ChaCondition == CONDITION_PARALYSIS))
					return 1;

				if (m_pLand->PickPoint(ptVec, mx, my) == TRUE)
				{
					if( !pCMyApp->IsInsideMap(ptVec.x,ptVec.z) )  // �� ���� ���� ������� ��� �������� �߰� ó��(by ����)
						return 0; // �ʿ��� ���� ������� ĵ��.

					// ���콺�� ���� �Ϻκ��� �����.
					if (/*!g_pRoh->IsCantMove()   // 06-09-01 �뽬�� �����߿� ĵ���� �� �ֵ��� ����.
						&& */m_bNextGoto ) //wan:2005-04	mat_jump�� gZone�� ������ goto�� �ޱ����� �뽬�� �ϸ� ���� ��ǥ�� �뽬�� ��
					{
						float fDist = DistPlToPlAbs(g_pRoh->m_wx,g_pRoh->m_wz, ptVec.x,ptVec.z);

						//�뽬 ��ų �Ÿ����� ���� ���콺 ��ǥ�� Ŭ ��� ���� ��ų �Ÿ���ŭ �̵�
						if(pCMyApp->GetSkillDistance(cur_skill) < fDist)
						{
							D3DVECTOR Temp;

							Temp.x = ptVec.x - g_pRoh->m_wx;
							Temp.y = 0.0f;
							Temp.z = ptVec.z - g_pRoh->m_wz;

							Temp = Normalize(Temp);

							Temp *= pCMyApp->GetSkillDistance(cur_skill);

							ptVec.x = Temp.x + g_pRoh->m_wx;
							ptVec.z = Temp.z + g_pRoh->m_wz;

							fDist = pCMyApp->GetSkillDistance(cur_skill);
						}
						if(pCMyApp->SkillConditionCheck(cur_skill)
								&& m_pLand->IsMovableArea(ptVec.x, ptVec.z)
								&& fDist > 15.0f
								&& IsNotBlocked(g_pRoh->m_wx, g_pRoh->m_wz, ptVec.x, ptVec.z)
								&& g_pRoh->GetMotionState() != CHA_F_SHADOWSLASH )
						{	
							SendCharUseSkill_Position(g_ChaSkill.m_SkillIndex[cur_skill], ptVec.x, ptVec.z);
						}
					}// end of if iscantmove
					return 1;
				}
			}
			else if(g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_TELEPORT
					&& !g_pRoh->m_bCrystalOwner )
			{
				static D3DVECTOR ptVec;

				if( pCMyApp->GetCurWorld() == WORLD_DUNGEON1 )
				{
					g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1); // ä��â���� �����ش�.
					return 0;
				}

				if( pCMyApp->GetCurWorld() == WORLD_BOSSRAID_HUMAN)
				{
					int nCharX = g_pRoh->m_wx;
					int nCharZ = g_pRoh->m_wz;

					int maxX = 4104;
					if( CommonConfig::Instance()->GetZone16WarpBlock() == true )
					{
						maxX = 4500;
					}

					if( (nCharX < maxX && 3430 < nCharX) && (nCharZ < 6809 && 6132 < nCharZ) ) // �չ� ����
					{
						//-- IDS_CANT_USE_THIS_AREA : �� ���������� ����� �� �����ϴ�.
						g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1); // ä��â���� �����ش�.
						return 0;
					}
				}

				//  [8/31/2009 ppmmjj83] 15�� �� �չ濡���� �����̵� �Ұ�
				if( pCMyApp->GetCurWorld() == WORLD_BOSSRAID_AIDIA )
				{
					int nCharX = g_pRoh->m_wx;
					int nCharZ = g_pRoh->m_wz;

					if( (nCharX < 11666 && 9117 < nCharX) && (nCharZ < 8633 && 4758 < nCharZ) ) // �չ� ����
					{
						//-- IDS_CANT_USE_THIS_AREA : �� ���������� ����� �� �����ϴ�.
						g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1); // ä��â���� �����ش�.
						return 0;
					}
				}

				//  [8/31/2009 ppmmjj83] 16�� �� �չ濡���� �����̵� �Ұ�
				if( pCMyApp->GetCurWorld() ==  WORLD_BOSSRAID_KAILIPTON)
				{
					int nCharX = g_pRoh->m_wx;
					int nCharZ = g_pRoh->m_wz;

					if( (nCharX < 12362 && 9011 < nCharX) && (nCharZ < 4445 && 1000 < nCharZ) ) // �չ� ����
					{
						//-- IDS_CANT_USE_THIS_AREA : �� ���������� ����� �� �����ϴ�.
						g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1); // ä��â���� �����ش�.
						return 0;
					}
				}


				// by evilkiki 2010.03.30 ���̺긮�� ������ �ڷ���Ʈ?
				if( pCMyApp->GetCurWorld() ==  WORLD_BOSSRAID_HYBRIDER)
				{
// 					int nCharX = g_pRoh->m_wx;
// 					int nCharZ = g_pRoh->m_wz;
//
// 					if( (nCharX < 12362 && 9011 < nCharX) && (nCharZ < 4445 && 1000 < nCharZ) ) // �չ� ����
// 					{
// 						//-- IDS_CANT_USE_THIS_AREA : �� ���������� ����� �� �����ϴ�.
// 						g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1); // ä��â���� �����ش�.
// 						return 0;
// 					}
				}

				if (m_pLand->PickPoint(ptVec, mx, my) == TRUE)
				{
					if( !pCMyApp->IsInsideMap(ptVec.x, ptVec.z) )  // �� ���� ���� ������� ��� �������� �߰� ó��(by ����)
						return 0; // �ʿ��� ���� ������� ĵ��.

					// ���콺�� ���� �Ϻκ��� �����.
					if (!g_pRoh->IsCantMove()
							&& m_pLand->IsMovableArea(ptVec.x, ptVec.z))
					{
						if( !IsTeleportArea( ptVec.x, ptVec.z, g_pRoh->m_wx, g_pRoh->m_wz) )
							return 0;

						if(pCMyApp->SkillConditionCheck(cur_skill))
						{
							float fDist = DistPlToPlAbs(g_pRoh->m_wx,g_pRoh->m_wz, ptVec.x,ptVec.z);
							// ���ο� �Ÿ� ���(mungmae-2005/09/30)
							if(g_Skills[SKILL_TELEPORT].GetApp0(g_ChaSkill.m_SkillLevel[cur_skill]) < fDist)
							{
								D3DVECTOR Temp;

								Temp.x = ptVec.x - g_pRoh->m_wx;
								Temp.y = 0.0f;
								Temp.z = ptVec.z - g_pRoh->m_wz;

								Temp = Normalize(Temp);

								Temp *= ( g_Skills[SKILL_TELEPORT].GetApp0(g_ChaSkill.m_SkillLevel[cur_skill]) + 50.0f );

								ptVec.x = Temp.x + g_pRoh->m_wx;
								ptVec.z = Temp.z + g_pRoh->m_wz;

								if( !m_pLand->IsMovableArea(ptVec.x, ptVec.z) ) // �������� �ٲ�����Ƿ� �����ִ� ������ �ٽ� �ѹ� üũ (06-06-16 ���� �߰�)
									return 0;

								fDist = g_Skills[SKILL_TELEPORT].GetApp0(g_ChaSkill.m_SkillLevel[cur_skill]);
							}							
							SendCharUseSkill_Position(SKILL_TELEPORT, ptVec.x, ptVec.z);
							m_bTeleport = TRUE;
							G_SK_SetCooltime(g_ChaSkill.m_SkillIndex[cur_skill]);
							// ���� ��Ȱ��
							m_b_MotionForAttack = false;
							m_b_MovingForAttack= false;
							m_b_Attack= false;
							m_b_SecAttack = false;
							return 1;
						}
					}
				}
			}
			// SKILL_HEAL_SELF ( ��Ŀ���� )
			else if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_HEAL_SELF )
			{
				if(g_Skills[ g_ChaSkill.m_SkillIndex[cur_skill]].GetEnerge0(g_ChaSkill.m_SkillLevel[cur_skill]) <= g_pRoh->m_Mana)
				{	
					SendCharUseSkill(6);
					InsertMagic(NULL, NULL, g_pRoh, NULL, EFFECT_SKILL_HEAL_SELF);

					return 1;
				}
			}
			// SKILL_SUMMON_PARTITION
			else if(g_MatrixSvr == 0
					&& m_pSummonMob[0]
					&& g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_SUMMON_PARTITION )
			{
				// ���� ������ ��� �Ұ�.
				if( !(g_pRoh->m_CancelState==1 &&
						g_pRoh->m_ChaCondition==CONDITION_PARALYSIS ||
						g_pRoh->m_ChaCondition==CONDITION_ENTANGLE))
				{
					if(!G_SK_Getflag(SKILL_SUMMON_PARTITION))
					{
						m_b_SecAttack = true;
						pCMyApp->AttackMsgSend(cur_skill);
						return 1;
					}
				}
			}
			else if(g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_SAFETY_SHIELD	// SKILL_SAFETY_SHIELD
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_MANA_SHIELD		// ī�� : Mana Shield
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_RECALL			// ī�� : Recall
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_BLOODY_MANA		// ī�� : Bloody Mana
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_F_ADRENALINE		// nate 2005-12-12 : �Ϸ�Ʈ�� �ǵ�
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_ELECTRIC_SHIELD 	// �޸� Electric shield
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_E_CLOAKING     // ���̺긮�� : ���̵�.
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILLF_E_REFLECTION     // ���̺긮�� : ���÷���
					|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_B_PROTECTION_SHIELDS
					|| g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S134		// �۷� �ʵ�
					|| g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S139		// D-System
					|| g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S141		// D-System
					|| g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S148		//
					|| g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S149		//
					|| g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S150		//

				   )
			{
				if( !pCMyApp->SkillConditionCheck( cur_skill ) )
					return 1;

				if( G_SK_Getflag(cur_skill) )
					return 1;

				if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_BLOODY_MANA )
					InsertMagic(NULL, NULL, g_pRoh, NULL, EFFECT_SKILL_BLOODY_MANA);



				if( g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S134 )
				{
					if( g_pRoh->IsActiveField() )
						return 1;

					G_SK_SetCooltime(PEROM_SKILL_S134);
				}
				if( g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S139 )
				{
// 					if( g_pRoh->IsActiveDSystem() )
// 						return 1;
					if( !g_pRoh->IsActiveDSystem() && g_pRoh->m_Wearing[WEARING_CLOAK] && g_pRoh->m_Wearing[WEARING_CLOAK]->m_Special== 5 )
					{
						g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_LHSTRING1906) , -1);
						return 1;
					}

					G_SK_SetCooltime(PEROM_SKILL_S139);
				}
				if( g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S148 )
				{
					if( g_pRoh->IsActiveCritical() )
						return 1;
					G_SK_SetCooltime(PEROM_SKILL_S148);
				}
				if( g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S149 )
				{
					if( g_pRoh->IsActiveEngage() )
						return 1;
					G_SK_SetCooltime(PEROM_SKILL_S149);
				}
				if(g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S141 )
				{
					if( !g_pRoh->IsActiveDSystem() )
						return 1;

					G_SK_SetCooltime(PEROM_SKILL_S141);
				}
				if(g_ChaSkill.m_SkillIndex[cur_skill] == PEROM_SKILL_S150 )
				{
					if( !g_pRoh->IsActiveDSystem() )
						return 1;
					if( !g_pRoh->IsActiveField() )
						return 1;

					G_SK_SetCooltime(PEROM_SKILL_S150);
				}

				if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_B_PROTECTION_SHIELDS )
				{
					if(G_SK_Getflag(SKILL_B_PROTECTION_SHIELDS)
							|| g_pRoh->m_bProtectionShield || !pCMyApp->SkillConditionCheck( cur_skill ) )	// ��Ÿ�ӽ� �޼��� ���� ����
						return 1;

					if(g_pRoh && !g_pRoh->m_bProtectionShield )
					{
						SendCharUseSkill(g_ChaSkill.m_SkillIndex[cur_skill]);
					}
				}
				else
				{	
					SendCharUseSkill(g_ChaSkill.m_SkillIndex[cur_skill]);
				}
				return 1;
			}
			// �޸� Hide �ẹ��
			else if ( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_HIDE)
			{
				// ��ȭ ��� , ũ����Ż ���ʾƴ� ���. �������� �ƴ� ���.
				if(!(g_pRoh->GetCombat())
						&& !(g_pRoh->m_bCrystalOwner) // ��ȭ��忡���� ����!
						&& pCMyApp->GetCurWorld() != WORLD_GUILD_WAR // ��� ���忡�� ��� ����
						&& !(m_b_Attack))
				{
					pCMyApp->StopHero(); // ������ �̰͵� ���⼱ ���ƾ� ���� ������ Ȥ�� �� ��ǥ ����ȭ�� ���Ͽ� ���⼭�� �ѹ� ������.
//					if (g_pRoh->ToggleHide()) ///07-04-27 �ẹ���� �������� �ް� �����ϰ� ����.(Ư�� ���� �Ұ� ó���� ���ؼ�)
					{
						if( g_pRoh->m_HideStatus )
						{	
							SendCharUseSkill_Hide(SKILL_HIDE, false);
						}
						else
						{	
							SendCharUseSkill_Hide(SKILL_HIDE, true);
						}						
					}
				}
			}
			// nate 2005-07-15 : Summon Squad - �޼��� ����
			else if(g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_SUMMONS_SQUAD)
			{
				if( pCMyApp->GetCurWorld() == WORLD_DUNGEON1 ) // ��ī������ �����̵� �Ұ�. ///�δ�1
				{
					// �޼����� �ѷ��ش�.
					//-- IDS_CANT_USE_THIS_AREA : �� ���������� ����� �� �����ϴ�.
					g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1); // ä��â���� �����ش�.
					return 0;
				}

				if( g_pRoh->m_bIsParty
						&& pCMyApp->SkillConditionCheck(cur_skill) )
				{	
					g_pRoh->SetMotionState( CHA_A_SUMMONSQUAD );					
					SendCharUseSkill(SKILL_A_SUMMONS_SQUAD);

					return 1;
				}
			}
		}
		//----------------------------------------------------------------------
		// Sec Attack ó��
		// Attack?
		if(m_b_Attack)
		{
			// Sec Attack??
			if(G_SK_IsSecAttack(cur_skill))
			{
				m_b_SecAttack = true;
				return 1;
			}
		}
	}
	// �ẹ���̸� ���� �� ��Ÿ �ൿ ����
	if( g_pRoh->m_HideStatus == HIDE_HIDDEN		// �޸� �ẹ�� ���� üũ
			|| g_pRoh->m_HideStatus == HIDE_HIDING )	// ���̵� �߿��� �� �� ���ϰ� �߰�.(by ����)
		return false;

	//------------------------------------------------------------------------
	// ��ü ���� �߿��� Ŭ���� ���� ã�Ƽ� ó��.
	//------------------------------------------------------------------------
	if( pMob = GetMobByColorKey(m_wColor) )
	{
		{
			// NPC �� Ŭ�� �Ǿ��ٸ� return 1;
			if(MouseClickEvent_NPC(pMob, which_button))
				return 1;
			// �� �Ѿ� ���� �Ұ�.
			if(!IsNotBlocked(g_pRoh->m_wx, g_pRoh->m_wz, pMob->m_wx, pMob->m_wz))
				return 1;
			//-----------------------------------------------------------------------
			// ���� ó��
			//-----------------------------------------------------------------------
			// NPC ���ƴ� �ٸ� �� ���� Pick ���� ���
			// ���� ó���� �Ѵ�.
			// 2004.10.04 - Lyul
			else
			{
				// ��ȭ���������� ���� �Ұ�.
				if (pCMyApp->IsPeaceArea())
					return 1;
				// �� �ӿ��� ���� �Ұ�.
				if( g_bNewTerrain )
				{
					if( g_pRoh->m_wy <= CNKObjQuadNode::GetHeightOnWater( g_pRoh->m_wz, g_pRoh->m_wx )
							&& pCMyApp->GetCurWorldID() !=WORLD_BOSSRAID_BULKAN )
						return 1;
				}
				else
				{
					if( g_pRoh->m_wy <= WATER_HEIGHT )
						return 1;
				}
				//-----------------------------------------------------------------------
				// ��Ʈ���� �������� �� Ŭ���� ���� ����
				if(g_MatrixSvr == 1 && !pCMyApp->IsSoccerZone())
				{
					// nate 2005-05-24 : ����ũ��� ���� ��Ʈ�������� �ڱ� ������ ũ����Ż, ����Ʈ���� ���� �Ұ�
					if( g_pRoh->m_Wearing[WEARING_WEAPON]
							&& g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum ==1238	// ����ũ���
							&& ( ( ( pMob->m_nMobNum == 371 || pMob->m_nMobNum == 377)
								   && g_pRoh->m_GuildIndex == 1)
								 || ( ( pMob->m_nMobNum == 372 || pMob->m_nMobNum == 378)
									  && g_pRoh->m_GuildIndex == 2)
								 || ( ( pMob->m_nMobNum == 373 || pMob->m_nMobNum == 379)
									  && g_pRoh->m_GuildIndex == 3) ) )
						return 1;
					// nate 2005-05-23 : ��Ʈ���� �� ��ȯ���� ���� �ȵ�
					if( !g_pRoh->m_GuildIndex		// ��尡 ���ų�
							|| pMob->m_MobAttributeType == g_pRoh->m_GuildIndex )
						return 1;
					// nate 2005-05-23 : Ȧ���������� �Ϲݸ� ���� �Ұ�.
					if( !( pMob->m_nMobNum > 370 && pMob->m_nMobNum < 380 )
							&& g_pRoh->m_Wearing[ WEARING_WEAPON ]
							&& ( g_pRoh->m_Wearing[ WEARING_WEAPON ]->m_Vnum == 1259
								 || g_pRoh->m_Wearing[ WEARING_WEAPON ]->m_Vnum == 1260
								 || g_pRoh->m_Wearing[ WEARING_WEAPON ]->m_Vnum == 1261 ) )
						return 1;
					// nate 2005-05-23 : ����ũ��ų� Ȧ�������� �������� GP����, ����Ʈ ���� ���ݺҰ�
					if( (pMob->m_nMobNum >373 && pMob->m_nMobNum <380)
							&& ( (g_pRoh->m_Wearing[WEARING_WEAPON]
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum !=1238	// ����ũ���
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum !=1259	// Ȧ�� ������( ȣũ )
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum !=1260	// Ȧ�� ������( ���� )
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum !=1261 )	// Ȧ�� ������( ���� )
								 || !g_pRoh->m_Wearing[WEARING_WEAPON] ) )
						return 1;

					if( g_bGlobalMatrix ) ///���������� ����ó��
					{
						if( pMob->m_nMobNum >= 371 && pMob->m_nMobNum <= 373 ) // �׶��� ũ����Ż ��
						{
							if( g_pRoh->m_Wearing[WEARING_WEAPON] ) // �ϴ� ���⸦ ���� �ִ� ���.
							{
								if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1259 )	// Ȧ�� ������( ȣũ )
								{
									if( pMob->m_nMobNum != 371 )
										return 1;
								}
								else if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1260 ) // Ȧ�� ������( ���� )
								{
									if( pMob->m_nMobNum != 372 )
										return 1;
								}
								else if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1261 ) // Ȧ�� ������( ���� )
								{
									if( pMob->m_nMobNum != 373 )
										return 1;
								}
								else if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1238 ) // Ȧ�� ��������..���� ũ��ŵ� �ƴϸ� ũ����Ż ���� �Ұ�.
								{
									return 1;
								}
							}
							else // ���Ⱑ ��� ����������..
							{
								return 1;
							}
						}
					}
				}
				if( g_MatrixSvr == 2 ) // [2008/11/11 Theodoric] WORLD_MATRIX_2009
				{
					// ����ũ��� ���� ��Ʈ�������� �ڱ� ������ ũ����Ż, ����Ʈ���� ���� �Ұ�
					if(g_pRoh->m_Wearing[WEARING_WEAPON] && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2172 )
					{
						if( pMob->m_nMobNum == 623 && g_pRoh->m_GuildIndex == 1) // ���帶�� ũ����Ż
							return 1;

						if( pMob->m_nMobNum == 624 && g_pRoh->m_GuildIndex == 2) // �ȱ׸��� ũ����Ż
							return 1;

						if((pMob->m_nMobNum >= 628 && pMob->m_nMobNum <= 632 )
								&& g_pRoh->m_GuildIndex == m_nStoneState[pMob->m_nMobNum - 622] )
							return 1;
					}

					// �ٸ� ������ ũ����Ż�� ġ������ ���ϰ� �� G���� ġ�� ���ϰ�
					if( g_pRoh->m_Wearing[WEARING_WEAPON]
							&& (g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2170 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2171 ) )
					{
						int itemVnum = g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum;

						// ��� ���� ũ����Ż ġ�� �Ұ�
						if(    (itemVnum == 2170 && pMob->m_nMobNum == 624)
								|| (itemVnum == 2171 && pMob->m_nMobNum == 623) )
							return 1;

						// G������ �ڽ��� �͸� ġ�ᰡ �����ϰ�
						if((pMob->m_nMobNum >= 628 && pMob->m_nMobNum <= 632 )
								&& g_pRoh->m_GuildIndex != m_nStoneState[pMob->m_nMobNum - 622] )
							return 1;

						// GP ������ ġ�� �Ұ�
						if( pMob->m_nMobNum >= 625 && pMob->m_nMobNum <= 627 )
							return 1;
					}

					// nate 2005-05-23 : ��Ʈ���� �� ��ȯ���� ���� �ȵ�
					if( !g_pRoh->m_GuildIndex || pMob->m_MobAttributeType == g_pRoh->m_GuildIndex )
						return 1;

					// nate 2005-05-23 : Ȧ���������� �Ϲݸ� ���� �Ұ�.
					if( !( pMob->m_nMobNum > 622 && pMob->m_nMobNum < 633 )
							&& g_pRoh->m_Wearing[ WEARING_WEAPON ]
							&& (   g_pRoh->m_Wearing[ WEARING_WEAPON ]->m_Vnum == 2170
								   || g_pRoh->m_Wearing[ WEARING_WEAPON ]->m_Vnum == 2171 ) )
						return 1;

					// nate 2005-05-23 : ����ũ��ų� Ȧ�������� �������� GP����, ����Ʈ ���� ���ݺҰ�
					if( (pMob->m_nMobNum > 624 && pMob->m_nMobNum < 633
							&& (( g_pRoh->m_Wearing[WEARING_WEAPON]
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 2172		// ����ũ���
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 2170		// Ȧ�� ������(����)
								  && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 2171	))	// Ȧ�� ������(�ȱ�)
							|| !g_pRoh->m_Wearing[WEARING_WEAPON] ) )
						return 1;

					if( g_bGlobalMatrix ) ///���������� ����ó��
					{
						if( pMob->m_nMobNum >= 623 && pMob->m_nMobNum <= 624 ) // �׶��� ũ����Ż ��
						{
							if( g_pRoh->m_Wearing[WEARING_WEAPON] ) // �ϴ� ���⸦ ���� �ִ� ���.
							{
								if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2170 )	// Ȧ�� ������(����)
								{
									if( pMob->m_nMobNum != 623 )
										return 1;
								}
								else if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2171 ) // Ȧ�� ������(�ȱ�)
								{
									if( pMob->m_nMobNum != 624 )
										return 1;
								}
								else if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 2172 ) // Ȧ�� ��������..���� ũ��ŵ� �ƴϸ� ũ����Ż ���� �Ұ�.
								{
									return 1;
								}
							}
							else // ���Ⱑ ��� ����������..
							{
								return 1;
							}
						}
					}
				}
				//-----------------------------------------------------------------------
				// �������� ���̶� ������ ������ ���� �Ұ���...
				if(pMob->m_MobClassType==1
						&& ( !( g_pRoh->m_Wearing[WEARING_BRACELET])
							 || g_pRoh->m_Wearing[WEARING_BRACELET]->m_Vnum != 829)
						&& (!(g_pRoh->m_Wearing[WEARING_BRACELET])
							|| g_pRoh->m_Wearing[WEARING_BRACELET]->m_Vnum != 841)
						&& !(g_pRoh->m_Wearing[WEARING_CLOAK]
							 && GET_SHAPE(g_pRoh->m_Wearing[WEARING_CLOAK])==ISUB_L_EQUIP
							 && (0x1 & g_pRoh->m_Wearing[WEARING_CLOAK]->m_Special)))
				{
					return 1;
				}
				// ��ȥ ��
				if(pMob->m_MobClassType==4
						&& g_ChaSkill.m_SkillIndex[cur_skill] != SKILL_LIFE_LIGHT)
					return 1;

				if( pMob->CheckRenderHolloweenMob(pMob->m_nMobNum) == false )
				{
					return 1;
				}

				if (!(wParam & MK_SHIFT) )//&& snifing_range <= 0)
				{
				}
				//----------------------------------------------------------------------
				// Right : �� Ŭ��.
				//----------------------------------------------------------------------
				// �Ϲ� �� Sec_Attack �Ǻ�
				if(which_button == BUTTON_RIGHT)
				{
					// Attack ���� �ƴ϶�� ���������� ���� �ƴ� ��츦 �Ǵ��Ѵ�.
					// Motion �߿� ���� ���� ���� ����.
					if(!m_b_Attack && !m_b_MotionForAttack)
					{
						int cur_skill = g_pNk2DFrame->GetRSkill();
						// SecAttack??
						if(G_SK_IsSecAttack(cur_skill))
						{
							m_b_SecAttack = true;
							pCMyApp->SetHeroAttGoMob(pMob);
							pCMyApp->CompareHeroAttGo();
							return 1;
						}
						// Normal Attack
						else if(!g_pNk2DFrame->GetControlBottom()->SelectedRotate()
								&& g_ChaSkill.m_SkillIndex[cur_skill] != SKILL_TELEPORT)
						{
							m_b_Attack = true;
							pCMyApp->SetHeroCurSkill(1);
							pCMyApp->SetHeroAttGoMob(pMob);
							pCMyApp->CompareHeroAttGo();
							return 1;
						}
					}
				}
				//----------------------------------------------------------------------
				// Left : �� Ŭ��.
				//----------------------------------------------------------------------
				// �Ϲ� �� QS_Attack �Ǻ�
				// ������ �� ���ٴ� �ǹ̴� ���� ����� ������ :�׷��߸� ��Ÿ�� ���� ���ο� ���� �����⸦ ����.
				else if(which_button == BUTTON_LEFT && !m_b_MotionForAttack  )// && !g_pRoh->IsCantMove())
				{
					if(m_bChakram) // ��ũ��
						m_bChakramAtt = true;
					else if(m_bBookSpell) // ��ũ��
						m_bBookSpellAtt = true;
					else //  �Ϲ� ����
					{
						m_b_Attack = true;
						pCMyApp->SetHeroCurSkill(0);
					}
					pCMyApp->SetHeroAttGoMob(pMob);
					pCMyApp->CompareHeroAttGo();
				} // End of if Left/Right
				return 1;
			} // End of else(pMob->m_wColorIdx == m_wColor)
		}
	}
	// nate 205-11-15 : Item Click ��ƾ ���� - mousedown�� cmdclick�� �л�Ǿ� �ִ� ��ƾ�� ����
	// Mouse L Button ���� ������ Ŭ��. ( �켱���� :�� > Item > Character )
	if (!g_pRoh->IsCantMove()
			&& which_button == BUTTON_LEFT
			&& IsInside_MouseDown_Itm_Namebox(mx, my))
		return true;
	// Char Click
	// �ڵ� CTRL Key ����
	// ĳ���� �����ϱ� ���ؼ� CTRL Ű�� ������ �ȴ�.
	// �ڵ� ��ų �� ��Ȳ�� ���� Auto Ctrl Key ����
	// ����
	if( m_bOnBattle
			&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
				 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN
				 || pCMyApp->GetCurWorld() == WORLD_FIELD) ) // [6/19/2007 Theodoric] ��� �����϶�
		bControlKey = TRUE;
	// ��Ʈ���� ������ ����Ʋ
	else if( (g_MatrixSvr != 0 &&!(GetKeyState(VK_RSHIFT)&0x80)) || m_bOnTeamBattle ) // ��Ʈ�������� ������ ����Ʈ�� ���ݾ��ϰ� ����(06-02-18 ����)
		bControlKey = TRUE;
	else if( g_pRoh->m_bNowFreePVP ) ///������� �߿� �ڵ� ��Ʈ��.(����̿޿� �ƿ� ��ŷ�� �ȵȴ�.)
		bControlKey = TRUE;

	// �ڵ� ��Ʈ�� ��ų ( �������� Target �� C �� ǥ��Ǵ� Skill �̴�.)
	if(cur_skill >= 0 &&
			( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_BLESSING				// ������ �ູ
			  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_LIFE_EXPANSION	// nate 2005-07-06 : Life Expansion - Set Control Key
			  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_JOINT_LIFE		// ���� ����
			  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_LIFE_LIGHT		// ������ ��
			  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_MELODY_OF_DEF	// ��ȣ�� ����
			  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_REMOVE 		// ī�� ����
			  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_RESURRECTION )         // ��Ȱ (07-02-26 �߰�)
	  )
		bControlKey = TRUE;

	if( pCMyApp->GetCurWorld() == WORLD_GUILD_WAR )
		bControlKey = TRUE;
	else if( pCMyApp->GetCurWorld() == WORLD_DMITRON_BATTLE )
		bControlKey = TRUE;

	if( DecardiBattleManager::GetInstance()->IsStart() == true &&
		pCMyApp->GetCurWorld() == WORLD_FIELD )
		bControlKey = TRUE;

// [6/19/2007 Theodoric] ��� ħ���� :: �켱 ĥ���ϰų� ���� ���¶�� ������ ���� �÷��׷� ��������
	// ��� �ڵ� ���� �巴�� �Ѥ�;;
	if( g_pRoh->GetMyGuildData() != NULL &&
			(g_pRoh->GetMyGuildData()->IsInvasion_Attack() ||
			 g_pRoh->GetMyGuildData()->IsInvasion_Defense() ))
		bGuildwar = TRUE;

	if ( bControlKey || bGuildwar )
	{
		if (g_SvrType == ST_ADULT_ONLY) // �ż���
		{
			if (g_pNk2DFrame->IsPVPVisible() &&
					(g_bDungeon == FALSE &&
					 g_bNewTerrainDungeon == FALSE))
			{
				// Do nothing!
			}
		}
		else
		{
			//������
			// [3/29/2007 Theodoric] �±� ��ũ�� �̺�Ʈ ������������� ���� �����ϰ�
			if(g_dwClientCountry == CTRY_TH && g_pRoh->m_Wearing[WEARING_WEAPON])
			{
				if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1538 && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1539 )
				{
					// PK ���� : ��ȭ���� / ���� 10����
					if (pCMyApp->IsPeaceArea() || g_pRoh->m_Level <= 10)
						return 0;
				}
			}
			else if( pCMyApp->IsPeaceArea() )
			{
				if(	g_pRoh->GetMyGuildData() != NULL &&
						( g_pRoh->GetMyGuildData()->IsInvasion_Attack() || g_pRoh->GetMyGuildData()->IsInvasion_Defense() ) )
				{
					if( pCMyApp->GetCurWorld() == 4 )
					{
						if( pCMyApp->IsInsideRect(g_pRoh->m_wx, g_pRoh->m_wz, 6800, 5450, 7250, 5000) )
							return 0;
					}
				}
			}
		}

		// [3/29/2007 Theodoric] �±� ��ũ�� �̺�Ʈ ������������� ���� �����ϰ�
		if(g_dwClientCountry == CTRY_TH && g_pRoh->m_Wearing[WEARING_WEAPON])
		{
			if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1538 && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1539 )
			{
				// Pet ���� ����
				if( pPet = GetPetByColorKey(m_wColor) )
				{
					if (pCMyApp->m_pMyPet && pPet != pCMyApp->m_pMyPet)
					{
						pCMyApp->m_pMyPet->SetCombatMob(-1, -1, pPet->m_nVirId);
					}
					return 1;
				}
			}
		}
		//------------------------------------------------------------------------
		// ��ü ĳ���� �߿��� Ŭ���� ĳ���� ã�Ƽ� ó��.
		//------------------------------------------------------------------------
		if( pCha = GetCharacterByColorKey(m_wColor) )
		{
			if( m_bOnBattle && pCha->m_bMyGuild
					&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
						 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN
						 || pCMyApp->GetCurWorld() == WORLD_FIELD
						 || IsMatrix() )
			  )
			{
				if(cur_skill >= 0 &&
						( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_BLESSING				// ������ �ູ
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_LIFE_EXPANSION	// nate 2005-07-06 : Life Expansion - Set Control Key // �뷱�� ���� ������ Ǯ������ �ʴ´�.
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_JOINT_LIFE		// ���� ����
						  //						|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_LIFE_LIGHT		// ������ �� // �뷱�� ���� ������ Ǯ������ �ʴ´�.
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_MELODY_OF_DEF	// ��ȣ�� ���� // �̰� �뷱�� ����غ���.
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_REMOVE 		// ī�� ����
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_RESURRECTION )         // ��Ȱ (07-02-26 �߰�)
				  )
				{
					// ���� ������ �����ϱ� ���� �������� �ǰ� ���ش�.
				}
				else
				{
					return 1; // ���� ������ ���� �������� �ȵǰ�...
				}
			}

			// 071004 �Ϻ����� ��û���� ��� ����
			// ���������� ���� �������� ���� �ȵǰ�.
			// [5/7/2008 parkmj] �Ϻ��� �ǰ�.
			if( m_bOnBattle && pCha->m_bMyGuild && g_dwClientCountry == CTRY_JPN

					&& ( pCMyApp->GetCurWorld() == WORLD_GUILD || pCMyApp->GetCurWorld() == WORLD_WHITEHORN
						 || pCMyApp->GetCurWorld() == WORLD_FIELD || pCMyApp->GetCurWorld() == WORLD_MATRIX )

					// ���Ʈ�� ������������ ������ų�����ϵ���
					|| pCMyApp->GetCurWorld() == WORLD_DMITRON_BATTLE
			  )
			{
				if(cur_skill >= 0 &&
						( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_BLESSING				// ������ �ູ
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_LIFE_EXPANSION	// nate 2005-07-06 : Life Expansion - Set Control Key // �뷱�� ���� ������ Ǯ������ �ʴ´�.
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_JOINT_LIFE		// ���� ����
						  //						|| g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_LIFE_LIGHT		// ������ �� // �뷱�� ���� ������ Ǯ������ �ʴ´�.
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_MELODY_OF_DEF	// ��ȣ�� ���� // �̰� �뷱�� ����غ���.
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_REMOVE 		// ī�� ����
						  || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_RESURRECTION )// ��Ȱ (07-02-26 �߰�)
				  )
				{
					// ���� ������ �����ϱ� ���� �������� �ǰ� ���ش�.
					if(pCMyApp->SkillConditionCheck(cur_skill))
					{
						// [5/29/2008 parkmj]  ���̵�� ��Ȱ ��ų ���� üŷ �Լ�.

						if( Check_Skill_Resurrection( cur_skill, pCha ) )
						{
							return 1; // �������� Ŭ���� ������ ���⼭ ����.
						}

						else
						{
							if( g_ChaSkill.m_SkillIndex[cur_skill] != SKILL_BLESSING ) ///�������ູ��Ÿ���� �������� �����ϵ��� �ٲ��.
								G_SK_SetCooltime(g_ChaSkill.m_SkillIndex[cur_skill]);
							
							SendCharUseSkill_Target(g_ChaSkill.m_SkillIndex[cur_skill], eCharType_Char, pCha->m_nCharIndex);

							return 1;
						}
					}
				}
			}

			//����ũ��ſ� Ȧ���������� ĳ�� ���� �ȵ�
			if( g_pRoh->m_Wearing[WEARING_WEAPON]
					&& ( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1238			// ����ũ���
						 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1259		// Ȧ�� ������( ȣũ )
						 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1260		// Ȧ�� ������( ���� )
						 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 1261
						 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2170		// [2008/11/24 Theodoric] WORLD_MATRIX_2009
						 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2171
						 || g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum == 2172
					   )
			  )
				return 1;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// �� �Ѿ� ���� �Ұ�.
			if(!IsNotBlocked(g_pRoh->m_wx, g_pRoh->m_wz, pCha->m_wx, pCha->m_wz))
				return 1;

			if (g_SvrType == ST_ADULT_ONLY) // �ż���
			{
				if (g_pNk2DFrame->IsPVPVisible() &&
						(g_bDungeon == FALSE &&
						 g_bNewTerrainDungeon == FALSE))
				{
					// Do nothing!
				}
			}
			else
			{
				//������
				// [3/29/2007 Theodoric] �±� ��ũ�� �̺�Ʈ ������������� ���� �����ϰ�
				if( g_dwClientCountry == CTRY_TH &&  g_pRoh->m_Wearing[WEARING_WEAPON] )
				{
					if( g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1538 && g_pRoh->m_Wearing[WEARING_WEAPON]->m_Vnum != 1539 )
					{
						// ��ȭ���������� ���� �Ұ�.
						if (pCMyApp->IsPeaceArea())
							return 1;
					}
				}
				else if( pCMyApp->GetCurWorld() == WORLD_GUILD_WAR )
				{
					if( g_pRoh->m_GuildIndex == pCha->m_GuildIndex )
						return 1;
				}
				else if( pCMyApp->GetCurWorld() == WORLD_DMITRON_BATTLE )
				{
					if( g_pRoh->m_GuildIndex == pCha->m_GuildIndex )
						return 1;
				}
				else if( DecardiBattleManager::GetInstance()->IsStart() == true &&
						 pCMyApp->GetCurWorld() == WORLD_FIELD )
				{
					if( DecardiBattleManager::GetInstance()->IsSameTeam(g_pRoh->m_nCharIndex, pCha->m_nCharIndex) == true )
						return 1;
				}
				else
				{
					if(	g_pRoh->GetMyGuildData() != NULL &&
							g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCha->m_GuildIndex))
					{
						if( pCMyApp->GetCurWorld() == 4 )
						{
							if( pCMyApp->IsInsideRect(pCha->m_wx, pCha->m_wz, 6800, 5450, 7250, 5000) )
								return 1;
						}
					}
					else if( !bControlKey )
						return 0;
				}
			}

			// �� �ӿ��� ���� �Ұ�.
			if( g_bNewTerrain )
			{
				if( g_pRoh->m_wy <= CNKObjQuadNode::GetHeightOnWater( g_pRoh->m_wz, g_pRoh->m_wx )
						&& pCMyApp->GetCurWorldID() != WORLD_BOSSRAID_BULKAN )
					return 1;
			}
			else
			{
				if( g_pRoh->m_wy <= WATER_HEIGHT )
					return 1;
			}

			///07-05-31 PK�� �ٸ� ĳ���� �׾����� ������ ���߱� �۾��� �¹��� ���������� �Ƚ����� ���������� ����.
			//				if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_RESURRECTION && pCha->GetMotionState() != CHA_DEAD ) // ��Ȱ�� ��밡 �׾������� ��������...
			//					return 1;

			if( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_RESURRECTION ) // ���������� ������ �ѰŶ��...
			{
				if( pCha->GetMotionState() == CHA_DEAD && pCMyApp->SkillConditionCheck(cur_skill) ) // ���� ������׸�...
				{
					pCMyApp->SetHeroAttGoCha( pCha );

					///070723 �Ϻ����׸���Ʈ ����
					g_pRoh->m_nResurrection_ChaId = pCha->m_nCharIndex; // �̰͵� ���⼭ �����ϵ��� ����.
					float fDist;
					fDist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pCha->m_wx, pCha->m_wz);
					float att_Dist = pCMyApp->GetSkillDistance(cur_skill);

					if( att_Dist < fDist ) // �Ÿ��� �ʹ� �ָ�...
					{
						// �� ��ų�� ó���� ����� ������ �ٰ����� ������ �ʰ� �Ÿ��� �־ �ȵȴٰ� ���޼����� �ش�.
						//- IDS_SKILL_RANGEOUT:   ��ų�� �����Ÿ��� ����� ��ҵǾ����ϴ�.
						if( g_pNk2DFrame )
							g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_SKILL_RANGEOUT), -1);
					}
					else
					{
						pCMyApp->AttackMsgSend( cur_skill ); // ���⼭ ���Ƿ� ��Ŷ�� �����������.
						g_pRoh->SetMagicCha(pCMyApp->m_pHeroAttGoCha, SKILL_A_RESURRECTION);  // ���⼭ ������ �ٲ��.
					}
				}

				return 1; // �������� Ŭ���� ������ ���⼭ ����.
			}

			// [5/29/2008 �����]  ���̵�� ��Ȱ ��ų ���� üŷ �Լ�.
			if( Check_Skill_Resurrection( cur_skill, pCha ) )
			{
				return 1; // �������� Ŭ���� ������ ���⼭ ����.
			}

			if (!(wParam & MK_SHIFT) )//&& snifing_range <= 0)
			{
			}

			//----------------------------------------------------------------------
			// Right : Char Ŭ��.
			//----------------------------------------------------------------------
			// �Ϲ� �� Sec_Attack �Ǻ�
			if(which_button == BUTTON_RIGHT)
			{
				// Attack ���� �ƴ϶�� ���������� ���� �ƴ� ��츦 �Ǵ��Ѵ�.
				// Motion �߿� ���� ���� ���� ����.
				if(!m_b_Attack && !m_b_MotionForAttack)
				{
					int cur_skill = g_pNk2DFrame->GetRSkill();
					// SecAttack??
					if(G_SK_IsSecAttack(cur_skill))
					{
						m_b_SecAttack = true;
						pCMyApp->SetHeroAttGoCha(pCha);
						pCMyApp->CompareHeroAttGo();
						return 1;
					}
					// Normal Attack
					else if(!g_pNk2DFrame->GetControlBottom()->SelectedRotate())
					{
						m_b_Attack = true;
						pCMyApp->SetHeroCurSkill(1);
						pCMyApp->SetHeroAttGoCha(pCha);
						pCMyApp->CompareHeroAttGo();
						return 1;
					}
				}
			}
			//----------------------------------------------------------------------
			// Left : Char Ŭ��.
			//----------------------------------------------------------------------
			// �Ϲ� �� QS_Attack �Ǻ�
			// ������ �� ���ٴ� �ǹ̴� ���� ����� ������ :�׷��߸� ��Ÿ�� ���� ���ο� ���� �����⸦ ����.
			else if(which_button == BUTTON_LEFT && !m_b_MotionForAttack  )// && !g_pRoh->IsCantMove())
			{
				if(m_bChakram) // ��ũ��
					m_bChakramAtt = true;
				else if(m_bBookSpell) // ��ũ��
					m_bBookSpellAtt = true;
				else //  �Ϲ� ����
				{
					m_b_Attack = true;
					pCMyApp->SetHeroCurSkill(0);
				}
				pCMyApp->SetHeroAttGoCha(pCha);
				pCMyApp->CompareHeroAttGo();
			} // End of if Left/Right
			return 1;

		}// end of for
	}// end of if bControlKey


	//------------------------------------------------------------------------
	// ��� ( �ڱ� �ڽ� ��� ) Skill - 2
	//------------------------------------------------------------------------
	// ���� ��ġ�ϴ� Skill ���� �켱������ ���� ��� ��ų���̴�
	// ��Ÿ� ������ ����. �������� P �� ǥ�õȴ�.
	// ��, ĳ�� �� �ٸ� Ÿ���� ���� ���� �ִ� Skill �̹Ƿ� ���������� T Ŭ�� üũ.
	// ī�� : REMOVE
	if ( cur_skill >= 0
			&& ( g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_REMOVE				// ī�� ����
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_MELODY_OF_DEF	// ���� ��ȣ�� ����
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_A_LIFE_EXPANSION	// nate 2005-07-06 : Life Expansion - send "use_skill"
				 || g_ChaSkill.m_SkillIndex[cur_skill] == SKILL_BLESSING))		// ���� ������ �ູ
	{
		// �̹� �ڽſ��� ��ų�� �ɷ��ִ� ���¿��� �� ������ ��츸 Ŭ���̾�Ʈ���� ĵ�����ش�. (06-02-06 ����)
		if( (g_ChaSkill.m_SkillIndex[cur_skill]==SKILL_MELODY_OF_DEF && g_pRoh->m_InChaAidiaSkill==SKILL_MELODY_OF_DEF) // ��ȣ�� ���谡 �̹� �ɷ��ִٸ�...
				|| (g_ChaSkill.m_SkillIndex[cur_skill]==SKILL_BLESSING && g_pRoh->m_InChaSkill==SKILL_BLESSING) // ������ �ູ�� �̹� �ɷ��ִٸ�...
		  )
		{
			return 1;
		}

		if(pCMyApp->SkillConditionCheck(cur_skill))
		{
			if( g_ChaSkill.m_SkillIndex[cur_skill] != SKILL_BLESSING			///������ �ູ ��Ÿ���� �������� �����ϵ��� �ٲ��.
					&& g_ChaSkill.m_SkillIndex[cur_skill] != SKILL_MELODY_OF_DEF)	///��ȣ�� ���� ��Ÿ���� �������� �����ϵ��� �ٲ��.
				G_SK_SetCooltime(g_ChaSkill.m_SkillIndex[cur_skill]);
			
			SendCharUseSkill_Target(g_ChaSkill.m_SkillIndex[cur_skill], eCharType_Char, g_pRoh->m_nCharIndex);

			return 1;
		}
	}

	m_bBookSpell= FALSE;
	m_bBookSpellAtt= FALSE;
	m_bChakram = FALSE;
	m_bChakramAtt = FALSE;

	return 0;
}

// ���콺 �̺�Ʈ ó�� - (������ ����, ����Ÿ�� ���� �� )
// ��ƾ : mousedown() -> cmdclick()



// nate 2005-12-14 : �� Ÿ�� ������ �ٸ� Ÿ���� ã����
int CUIMgr::FindNearTarget(float base_x, float base_z, void* pBaseTarget, float distance, float area, bool bMob, int nTargetCount, bool bStoneBash ) ///�����޺�
// distance : �� ĳ������ �Ÿ�
// area : �� Ÿ�ٰ��� �Ÿ�
// nTargetCount : Ÿ�� ����
{
	if( !pBaseTarget || nTargetCount > 10 )
		return 0;

	int nCount = 0;
	CNkMob *pBaseMob = NULL;
	CNkCharacter *pBaseCha = NULL;
	if( bMob )
		pBaseMob = (CNkMob*)pBaseTarget;
	else
		pBaseCha = (CNkCharacter*)pBaseTarget;

	CNkCharacter *pCha = NULL;
	LHCharacterMap_it prCha;
	CNkMob *pMob = NULL;
	LHMobMap_it prMob;

	for(int i = 0 ; i < nTargetCount ; i++)
	{
		if( bMob )
			g_pTargetMob[i] = NULL;
		else
			g_pTargetCha[i] = NULL;
	}

	if( bStoneBash ) // �ڽ��� ����ν����� �������� �ֺ� ĳ���͸� �����ϰ� ������ ����Ϸ��� bStoneBash �߰� ///�����޺�
	{
		// �� ��� �׻� ��(����ν���)�� ���̽��� �ȴ�.
		pBaseMob = (CNkMob*)pBaseTarget;
		pBaseCha = NULL;

		if( bMob )
		{
			for (prMob = m_mob_map.begin(); prMob != m_mob_map.end() && nCount < nTargetCount; prMob++)
			{
				pMob = (*prMob).second;

				if (pMob == pBaseMob || pMob->IsDead() || pMob->m_MobClassType==4 || pMob->m_MobClassType==9 )	// ��Ÿ�� �̰ų� ��ȥ�迭, �Ǵ� ���� �����̸� �ǳʶڴ�. ( 06-03-17 ���� ����ν��浵 ���߰��� �� ����Ʈ�� �� ������ ���� )
					continue;

				if (pMob->m_Flag & NPC_SHOPKEEPER
						|| pMob->m_Flag & NPC_GUARD
						|| pMob->m_nMobNum == 139
						|| pMob->m_nMobNum == 117
						|| pMob->m_nMobNum == 136)
					continue;

				if(IsNotBlocked(base_x, base_z, pMob->m_wx, pMob->m_wz)) // �� �༮�� �� Ÿ���� �ƴ϶� ����ڸ� �������� �˻��Կ� ����
				{
					// �� Ÿ�ٰ��� �Ÿ� ���
					if( area >= DistPlToPlAbs(pBaseMob->m_wx, pBaseMob->m_wz,pMob->m_wx,pMob->m_wz) )
						g_pTargetMob[nCount++] = pMob;
				}
			}
		}
		else
		{
			for (prCha = m_character_map.begin(); prCha != m_character_map.end() && nCount < nTargetCount; prCha++)
			{
				pCha = (*prCha).second;

				if( pCha == g_pRoh || pCha->IsDead() ) // �ڽ��̰ų� ���� �����̸� �ǳʶڴ�.
					continue;

				if(IsNotBlocked(base_x, base_z, pCha->m_wx, pCha->m_wz)) // �� �༮�� �� Ÿ���� �ƴ϶� ����ڸ� �������� �˻��Կ� ����
				{
					// �� Ÿ�ٰ��� �Ÿ� ���
					if(  area >= DistPlToPlAbs(pBaseMob->m_wx, pBaseMob->m_wz,pCha->m_wx,pCha->m_wz)  )
					{
						if( (m_bOnBattle
								&& ( pCMyApp->GetCurWorld() == WORLD_GUILD
									 || pCMyApp->GetCurWorld() == WORLD_WHITEHORN
									 || pCMyApp->GetCurWorld() == WORLD_FIELD
									 || IsMatrix()	))
								|| (g_pNk2DFrame->IsPVPVisible() == TRUE) )
						{
							if( g_pRoh->GetMyGuildData() != NULL &&
									g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCha->m_GuildIndex )  &&
									!(pCMyApp->GetCurWorld() == 4 &&
									  pCMyApp->IsInsideRect(pCha->m_wx, pCha->m_wz, 6800, 5450, 7250, 5000)) )
							{
								g_pTargetCha[nCount++] = pCha;
							}
						}
						else
						{
							g_pTargetCha[nCount++] = pCha;
						}
					}
				}
			}
		}
	}
	else if( bMob )
	{
		for (prMob = m_mob_map.begin(); prMob != m_mob_map.end() && nCount < nTargetCount; prMob++)
		{
			pMob = (*prMob).second;

			if (pMob == pBaseMob || pMob->IsDead() || pMob->m_MobClassType==4 || pMob->m_MobClassType==9 )	// ��Ÿ�� �̰ų� ��ȥ�迭, �Ǵ� ���� �����̸� �ǳʶڴ�. ( 06-03-17 ���� ����ν��浵 ���߰��� �� ����Ʈ�� �� ������ ���� )
				continue;

			if (pMob->m_Flag & NPC_SHOPKEEPER
					|| pMob->m_Flag & NPC_GUARD
					|| pMob->m_nMobNum == 139
					|| pMob->m_nMobNum == 117
					|| pMob->m_nMobNum == 136)
				continue;

			if(IsNotBlocked(base_x, base_z, pMob->m_wx, pMob->m_wz))
			{
				// �� Ÿ�ٰ��� �Ÿ� ���
				if(area >= DistPlToPlAbs(pBaseMob->m_wx, pBaseMob->m_wz, pMob->m_wx, pMob->m_wz))
					g_pTargetMob[nCount++] = pMob;
			}
		}
	}
	else
	{
		for (prCha = m_character_map.begin(); prCha != m_character_map.end() && nCount < nTargetCount; prCha++)
		{
			pCha = (*prCha).second;

			if (pCha == pBaseCha || pCha->IsDead())	// ��Ÿ�� �̰ų� ���� �����̸� �ǳʶڴ�.
				continue;

			if(IsNotBlocked(base_x, base_z, pCha->m_wx, pCha->m_wz))
			{
				// �� Ÿ�ٰ��� �Ÿ� ���
				if(area >= DistPlToPlAbs(pBaseCha->m_wx, pBaseCha->m_wz, pCha->m_wx, pCha->m_wz))
					g_pTargetCha[nCount++] = pCha;
			}
		}
	}
	return nCount;	// ī��Ʈ�� 1 ���� �Ǿ� �ֱ� ������ 1 ����.
}

// �β��� ���� ������ �浹 üũ �Լ� ///�����޺�
int CUIMgr::FindLineTarget( float LineStartX, float LineStartZ, float LineEndX, float LineEndZ, float LineThick, bool bMob, int nTargetCount )
{
	if( nTargetCount > 10 )
		return 0;

	int nCount = 0;

	CNkCharacter *pCha = NULL;
	LHCharacterMap_it prCha;
	CNkMob *pMob = NULL;
	LHMobMap_it prMob;

	for( int i = 0 ; i < nTargetCount ; i++ )
	{
		if( bMob )
			g_pTargetMob[i] = NULL;
		else
			g_pTargetCha[i] = NULL;
	}

	D3DVECTOR LineStartPos = D3DVECTOR( LineStartX, 0.0f, LineStartZ ); // ������ ���������� ���ͷ� �����д�.
	D3DVECTOR LineEndPos = D3DVECTOR( LineEndX, 0.0f, LineEndZ );       // ������ ���� ������ ���ͷ� �����д�.
	D3DVECTOR TargetPos; // ���̳� ĳ������ ��ǥ ��.

	D3DVECTOR TempVec1;
	D3DVECTOR TempVec2;
	D3DVECTOR TempVec3;
	float TempFloat1 = 0.0f;
	float TempFloat2 = 0.0f;

	if( bMob )
	{
		for( prMob = m_mob_map.begin() ; prMob != m_mob_map.end() && nCount < nTargetCount ; prMob++ )
		{
			pMob = (*prMob).second;

			if( pMob->IsDead() || pMob->m_MobClassType==4 )	// ��Ÿ�� �̰ų� ��ȥ�迭, �Ǵ� ���� �����̸� �ǳʶڴ�.
				continue;

			if (pMob->m_Flag & NPC_SHOPKEEPER
					|| pMob->m_Flag & NPC_GUARD
					|| pMob->m_nMobNum == 139
					|| pMob->m_nMobNum == 117
					|| pMob->m_nMobNum == 136)
				continue;

			TargetPos = D3DVECTOR( pMob->m_wx, 0.0f, pMob->m_wz );

			TempVec1 = LineStartPos - TargetPos; // v1 ����.
			TempVec2 = LineStartPos - LineEndPos; // v2 ����.
			TempFloat1 = DotProduct( TempVec1, TempVec2 ); // V1 * V2
			TempFloat2 = DotProduct( TempVec2, TempVec2 ); // V2 * V2

			// ���а� ���� ��ġ�� ���� üũ����� �޶�����.
			if( TempFloat1 > 0 && TempFloat1 < TempFloat2 ) // ���� �߰��� ���ϴ� ��ġ�� ���...
			{
				TempFloat1 = TempFloat1 / Magnitude( TempVec2 ); // v1�� v2�� ������ ����.
				TempVec3 = Normalize(TempVec2); // �ϴ� �������ͷ� �̾Ƽ�...
				TempVec3 = TempFloat1 * TempVec3; // �̷��� �ϸ� V1�� V2�� ������ ���Ͱ� ���´�.
				TempVec2 = TempVec1 - TempVec3;  // �������Ͱ� ���´�.(������ ������ ���� ���Ѵ�.)
				TempFloat2 = Magnitude( TempVec2 ); // ���� ������ �Ÿ�.

				if( TempFloat2 < LineThick ) // �Ÿ�(���� �α�+������Ʈ ũ��)�� ���������� �F���� �浹.(������Ʈ ũ��� ���� ���� �����Ƿ� ���Ƿ� ����.)
				{
					g_pTargetMob[nCount] = pMob;
					nCount++;
				}
			}
			else if( TempFloat1 > TempFloat2 ) // ������ ���ʿ� ���ϴ� ��ġ�ϰ��....
			{
				continue; // �̳༮�� �ϴ� ����� ����
				/*
								TempVec2 = LineEndPos - TargetPos;
								TempFloat2 = Magnitude( TempVec2 ); // ���� ������ �Ÿ�.

								if( TempFloat2 < LineThick ) // �Ÿ�(���� �α�+������Ʈ ũ��)�� ���������� �F���� �浹.(������Ʈ ũ��� ���� ���� �����Ƿ� ���Ƿ� ����.)
								{
									g_pTargetMob[nCount] = pMob;
									nCount++;
								}
				*/
			}
			else if( TempFloat1 < 0 ) // ������ ����. ����� �����Ѵ�.
			{
				continue;
			}
		}
	}
	else
	{
		for (prCha = m_character_map.begin(); prCha != m_character_map.end() && nCount < nTargetCount; prCha++)
		{
			pCha = (*prCha).second;

			if( pCha->IsDead() )	// ��Ÿ�� �̰ų� ���� �����̸� �ǳʶڴ�.
				continue;

			TargetPos = D3DVECTOR( pCha->m_wx, 0.0f, pCha->m_wz );

			TempVec1 = LineStartPos - TargetPos; // v1 ����.
			TempVec2 = LineStartPos - LineEndPos; // v2 ����.
			TempFloat1 = DotProduct( TempVec1, TempVec2 ); // V1 * V2
			TempFloat2 = DotProduct( TempVec2, TempVec2 ); // V2 * V2

			// ���а� ���� ��ġ�� ���� üũ����� �޶�����.
			if( TempFloat1 > 0 && TempFloat1 < TempFloat2 ) // ���� �߰��� ���ϴ� ��ġ�� ���...
			{
				TempFloat1 = TempFloat1 / Magnitude( TempVec2 ); // v1�� v2�� ������ ����.
				TempVec3 = Normalize(TempVec2); // �ϴ� �������ͷ� �̾Ƽ�...
				TempVec3 = TempFloat1 * TempVec3; // �̷��� �ϸ� V1�� V2�� ������ ���Ͱ� ���´�.
				TempVec2 = TempVec1 - TempVec3;  // �������Ͱ� ���´�.(������ ������ ���� ���Ѵ�.)
				TempFloat2 = Magnitude( TempVec2 ); // ���� ������ �Ÿ�.

				if( TempFloat2 < LineThick ) // �Ÿ�(���� �α�+������Ʈ ũ��)�� ���������� �F���� �浹.(������Ʈ ũ��� ���� ���� �����Ƿ� ���Ƿ� ����.)
				{
					g_pTargetCha[nCount] = pCha;
					nCount++;
				}
			}
			else if( TempFloat1 > TempFloat2 ) // ������ ���ʿ� ���ϴ� ��ġ�ϰ��....
			{
				continue; // �̳༮�� �ϴ� ����� ����
			}
			else if( TempFloat1 < 0 ) // ������ ����. ����� �����Ѵ�.
			{
				continue;
			}
		}
	}
	return nCount;	// ī��Ʈ�� 1 ���� �Ǿ� �ֱ� ������ 1 ����.
}


int CUIMgr::FindLineTargetGuildWar( float LineStartX, float LineStartZ, float LineEndX, float LineEndZ, float LineThick, int nTargetCount, int GuildWarType ) // [2008/1/18 Theodoric]
{
	if( nTargetCount > 10 )
		return 0;

	int nCount = 0;

	CNkCharacter *pCha = NULL;
	LHCharacterMap_it prCha;
	CNkMob *pMob = NULL;
	LHMobMap_it prMob;

	for( int i = 0 ; i < nTargetCount ; i++ )
	{
		g_pTargetCha[i] = NULL;
	}

	D3DVECTOR LineStartPos = D3DVECTOR( LineStartX, 0.0f, LineStartZ ); // ������ ���������� ���ͷ� �����д�.
	D3DVECTOR LineEndPos = D3DVECTOR( LineEndX, 0.0f, LineEndZ );       // ������ ���� ������ ���ͷ� �����д�.
	D3DVECTOR TargetPos; // ���̳� ĳ������ ��ǥ ��.

	D3DVECTOR TempVec1;
	D3DVECTOR TempVec2;
	D3DVECTOR TempVec3;
	float TempFloat1 = 0.0f;
	float TempFloat2 = 0.0f;


	for (prCha = m_character_map.begin(); prCha != m_character_map.end() && nCount < nTargetCount; prCha++)
	{
		pCha = (*prCha).second;

		if( pCha->IsDead() )	// ��Ÿ�� �̰ų� ���� �����̸� �ǳʶڴ�.
			continue;

		if( GuildWarType == 0 )
		{
			if( g_pRoh->m_GuildIndex == pCha->m_GuildIndex )// ��ŷ�� �ϰ�� ���� ��� �ε����� �˻����� �ʴ´�.
				continue;
		}
		else if( GuildWarType == 1 )
		{
			if( !g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCha->m_GuildIndex ) )
				continue;
		}
		else
			return 0;


		TargetPos = D3DVECTOR( pCha->m_wx, 0.0f, pCha->m_wz );

		TempVec1 = LineStartPos - TargetPos; // v1 ����.
		TempVec2 = LineStartPos - LineEndPos; // v2 ����.
		TempFloat1 = DotProduct( TempVec1, TempVec2 ); // V1 * V2
		TempFloat2 = DotProduct( TempVec2, TempVec2 ); // V2 * V2

		// ���а� ���� ��ġ�� ���� üũ����� �޶�����.
		if( TempFloat1 > 0 && TempFloat1 < TempFloat2 ) // ���� �߰��� ���ϴ� ��ġ�� ���...
		{
			TempFloat1 = TempFloat1 / Magnitude( TempVec2 ); // v1�� v2�� ������ ����.
			TempVec3 = Normalize(TempVec2); // �ϴ� �������ͷ� �̾Ƽ�...
			TempVec3 = TempFloat1 * TempVec3; // �̷��� �ϸ� V1�� V2�� ������ ���Ͱ� ���´�.
			TempVec2 = TempVec1 - TempVec3;  // �������Ͱ� ���´�.(������ ������ ���� ���Ѵ�.)
			TempFloat2 = Magnitude( TempVec2 ); // ���� ������ �Ÿ�.

			if( TempFloat2 < LineThick ) // �Ÿ�(���� �α�+������Ʈ ũ��)�� ���������� �F���� �浹.(������Ʈ ũ��� ���� ���� �����Ƿ� ���Ƿ� ����.)
			{
				g_pTargetCha[nCount] = pCha;
				nCount++;
			}
		}
		else if( TempFloat1 > TempFloat2 ) // ������ ���ʿ� ���ϴ� ��ġ�ϰ��....
		{
			continue; // �̳༮�� �ϴ� ����� ����
		}
		else if( TempFloat1 < 0 ) // ������ ����. ����� �����Ѵ�.
		{
			continue;
		}
	}
	return nCount;	// ī��Ʈ�� 1 ���� �Ǿ� �ֱ� ������ 1 ����.
}

void CUIMgr::InsertPetHitEffects(CNkPet *pet_from, CNkMob *mob_from, CNkCharacter *ch_to, CNkPet *pet_to, CNkMob *mob_to, int skill_idx)
{
	static EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));

	int i = 0;
	float TargetHeight = 0.0f;

	if (mob_to)
	{
		switch (mob_to->m_Height)
		{
		case MOB_HEIGHT_HIGH_NUM:
			TargetHeight = MOB_HEIGHT_HIGH_VAL;
			break;
		case MOB_HEIGHT_LOW_NUM:
			TargetHeight = MOB_HEIGHT_LOW_VAL;
			break;
		default: // MOB_HEIGHT_MIDDLE_NUM:
			TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
			break;
		}
	}
	else if (pet_to)
	{
		TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
	}
	else if (ch_to)
	{
		TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
	}

	switch (skill_idx)
	{
	case PET_HIT_NAIL:
	case PET_HIT_KICK:
	case PET_HIT_HEADING:
	case PET_HIT_BITE:
	case PET_HIT_STRIKE:
	case PET_HIT_FIRE:
	case PET_HIT_LIGHT:
	case PET_HIT_RELICS:
	case PET_HIT_GAS:
		ef_sort.nType = FX_HITPETEFFECTS;

		if (pet_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(pet_to->m_wx, pet_to->m_wy + TargetHeight, pet_to->m_wz);
			ef_sort.pNkPetTo = pet_to;
			if (pet_from)
			{
				ef_sort.vPos = D3DVECTOR(pet_from->m_wx, pet_from->m_wy, pet_from->m_wz);
			}
			else if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			pet_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (mob_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
			ef_sort.pMobTo = mob_to;
			if (pet_from)
			{
				ef_sort.vPos = D3DVECTOR(pet_from->m_wx, pet_from->m_wy, pet_from->m_wz);
			}
			else if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (ch_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
			ef_sort.pNkChaTo = ch_to;
			if (pet_from)
			{
				ef_sort.vPos = D3DVECTOR(pet_from->m_wx, pet_from->m_wy, pet_from->m_wz);
			}
			else if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else
		{
			return;
		}

		break;
	default:
		break;
	}

	return;
}

//--------------------------------------------------------------------------
// InsertHitEffects
//--------------------------------------------------------------------------
// ���� Ÿ�� ����Ʈ�� �߻���Ų��.

// 2005.01.28
// Lyul / �̵��� �߰�. (HIT_DSWORD)
void CUIMgr::InsertHitEffects(CNkCharacter *ch_from, CNkMob *mob_from, CNkCharacter *ch_to, CNkMob *mob_to, Hit_Index hit_index)
{
	static EffectSort ef_sort;

	ZeroMemory(&ef_sort, sizeof(EffectSort));

	float TargetHeight = 0.0f;

	if (mob_to)
	{
		switch (mob_to->m_Height)
		{
		case MOB_HEIGHT_HIGH_NUM:
			TargetHeight = MOB_HEIGHT_HIGH_VAL;
			break;
		case MOB_HEIGHT_LOW_NUM:
			TargetHeight = MOB_HEIGHT_LOW_VAL;
			break;
		default: // MOB_HEIGHT_MIDDLE_NUM:
			TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
			break;
		}
	}
	else if (ch_to)
	{
		TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
	}

	ef_sort.Index = (int)hit_index;

	switch (hit_index)
	{
	// �̵���
	case HIT_DSWORD:
		ef_sort.nType = FX_HITBOOMEFFECTS;
		ef_sort.num = 1;
		ef_sort.subNum = rand()%(360);
		ef_sort.dwColor = rand()%(360);

		// To Character
		if (ch_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
			ef_sort.pNkChaTo = ch_to;
			if (ch_from)
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		// to mob
		else if (mob_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
			ef_sort.pMobTo = mob_to;
			if (ch_from)
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else
			return;
		break;

	case HIT_SOWRD_ROTATE_ATTACK:
	case HIT_AXE_JUMP_ATTACK:
	case HIT_AXE:
	case HIT_STAFF:
	case HIT_SWORD:
		ef_sort.nType = FX_HITBOOMEFFECTS;
		ef_sort.num = 0;
		if (ch_to)  	// �´� ��.
		{
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
			ef_sort.pNkChaTo = ch_to;
			if (ch_from)  	// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			}
			else if (mob_from)  	// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (mob_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
			ef_sort.pMobTo = mob_to;
			if (ch_from)
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			}
			else if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else
		{
			return;
		}
		break;


	case HIT_HAND:
		ef_sort.nType = FX_HITEFFECTS;
		if (ch_to)  	// �´� ��.
		{
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
			ef_sort.pNkChaTo = ch_to;
			if (ch_from)  	// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			}
			else if (mob_from)  	// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (mob_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
			ef_sort.pMobTo = mob_to;
			if (ch_from)
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			}
			else if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			}
			else
			{
				return;
			}
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else
		{
			return;
		}
		break;

	case HIT_WARGIANT_ATTACK:
		ef_sort.nType = FX_WARGIANTATTACK;
		if (ch_to)
		{
			// �´� ��.
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
			ef_sort.pNkChaTo = ch_to;
			if (ch_from)	// ������ ��.
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)	// ������ ��.
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;
			ef_sort.nCurFrame = 0; //  �� �༮�� ���������� ������ �ʱ�ȭ�� ���ϹǷ� ���� �����ؾ��Ѵ�. ///�δ�1 �� �߰�
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			ef_sort.nCurFrame = -8;
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (mob_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
			ef_sort.pMobTo = mob_to;
			if (ch_from)
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;
			ef_sort.nCurFrame = 0; //  �� �༮�� ���������� ������ �ʱ�ȭ�� ���ϹǷ� ���� �����ؾ��Ѵ�. ///�δ�1 �� �߰�
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			ef_sort.nCurFrame = -8;
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else
			return;
		break;

	case HIT_LEGKNOCK_ATTACK: ///�δ�1
		ef_sort.nType = FX_WARGIANTATTACK;
		ef_sort.subNum = 1; // ����Ʈ Ÿ������ ���.(����ó������ ����.)
		if (ch_to)
		{
			// �´� ��.
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
			ef_sort.pNkChaTo = ch_to;
			if (ch_from)	// ������ ��.
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)	// ������ ��.
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;
			ef_sort.nCurFrame = 0;
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			ef_sort.nCurFrame = -18;
			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (mob_to)
		{
			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
			ef_sort.pMobTo = mob_to;
			if (ch_from)
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;
			ef_sort.nCurFrame = 0; //  �� �༮�� ���������� ������ �ʱ�ȭ�� ���ϹǷ� ���� �����ؾ��Ѵ�.
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			ef_sort.nCurFrame = -18; // �ణ �� Ÿ�ֿ̹� �ϳ� �� �־��ش�.(�ι������� ����.)
			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else
			return;
		break;

	case HIT_HEART: ///��Ʈ�ε�
		InsertMagic( ch_from, mob_from, ch_to, mob_to, EFFECT_HEART_PARTICLE ); // �Ϲ� ����Ʈ�ε� �����ְ� �̷��� ���.
		break;
	case HIT_LIP : // �Լ�(ȭ��Ʈ) // 2007.03.14 ȭ��Ʈ
		InsertMagic( ch_from, mob_from, ch_to, mob_to, EFFECT_LIP_PARTICLE ); // �Ϲ� ����Ʈ�ε� �����ְ� �̷��� ���.
		break;
	case HIT_LOVE : // ����(ȭ��Ʈ) // 2007.03.14 ȭ��Ʈ
		InsertMagic( ch_from, mob_from, ch_to, mob_to, EFFECT_LOVE_PARTICLE ); // �Ϲ� ����Ʈ�ε� �����ְ� �̷��� ���.
		break;

	case HIT_SONGKRAN:	// [3/27/2007 Theodoric] �±� ��ũ�� �̺�Ʈ
		InsertMagic(ch_from, mob_from, ch_to, mob_to, EFFECT_SONGKRAN_WTRSPRINKLE );
		break;


	default:
		break;
	}
	return;
}


void CUIMgr::InsertMagic(CNkCharacter *ch_from, CNkMob *mob_from, CNkCharacter *ch_to, CNkMob *mob_to, int skill_idx)
{
	static EffectSort ef_sort;
	//float x, y, z;

	ZeroMemory(&ef_sort, sizeof(EffectSort));

	float TargetHeight = 0.0f;
	int ChaAttackType = 0;
	int i = 0;
	int nEffInserNum = 0;

	D3DVECTOR vDir, vPosFrom, vPosTo;

	switch (skill_idx)
	{
	case EFFECT_SKILL_FIRE_BALL:
		{
			ef_sort.nType = FX_FIREBALL;
			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)	// ������ ��.
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				else if (mob_from) 	// ������ ��.
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				//mob_from->Magic(x, z);
				else
					return;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				else if (mob_from)
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				//mob_from->Magic(x, z);
				else
					return;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;
				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT1], x, y, z);
			}
		}
		break;
	case EFFECT_SKILL_LIGHTNING_BALL:
		{
			ef_sort.nType = FX_LIGHTBALL;

			if (ch_to)
			{
				// �´� �� (ĳ���Ͱ� ������)
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (ch_from) 	// ������ ��.
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				else if (mob_from)
				{
					// ������ ��.
					//wan:2004-12
					if(mob_from->m_nMobNum==361)
					{
						//���ݼ�ȣž
						ef_sort.pMobFrom = mob_from;
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy+10.0f, mob_from->m_wz);
					}
					else
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
					return;

				// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum( nEffInserNum );
				if( mob_from && mob_from->m_nMobNum==361 ) // ���� ��ȣž�� ���� ���ʿ��� ���.
					mob_from->InsertEffectNum( nEffInserNum );
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				else if (mob_from)
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				//mob_from->Magic(x, z);
				else
					return;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;
				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT2], x, y, z);
			}
		}
		break;
	case EFFECT_SKILL_LIGHTNING:
		{
			ef_sort.nType = FX_LIGHTNING;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_LIGHTNING], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_FIRE_PILLAR:			// �ұ��.
		{
			ef_sort.nType = FX_METEOR;
			if (ch_to)
			{
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_FIRE_PILLAR], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_PEBBLE_SHOT:
		{
			ef_sort.nType = FX_PEBBLESHOT;
			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (ch_from)	// ������ ��.
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				else if (mob_from)	// ������ ��.
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				//mob_from->Magic(x, z);
				else
					return;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				else if (mob_from)
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				//mob_from->Magic(x, z);
				else
					return;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;
				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT1], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_FALL_STONE:
		{
			ef_sort.nType = FX_STONESHOT;
			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx+15.0f, ch_to->m_wy+50.0f, ch_to->m_wz+15.0f);
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx+20.0f, ch_to->m_wy+50.0f, ch_to->m_wz+20.0f);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx+20.0f, mob_to->m_wy+50.0f, mob_to->m_wz+20.0f);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_DROP_STONE], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_ENERGYBALL:
		{
			ef_sort.nType = FX_AIDIAFIRE;
			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				//....
			}
		}
		break;

	case EFFECT_SKILL_HEAL_SELF:
	case EFFECT_SKILL_BLOODY_MANA:
	case EFFECT_SKILL_HEAL_OTHER:
		{
			ef_sort.nType = FX_HEALEFFECTS;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_STAR_FLARE:
		{
			ef_sort.nType = FX_STARFLARE;
			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx+15.0f, ch_to->m_wy+50.0f, ch_to->m_wz+15.0f);
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx+20.0f, ch_to->m_wy+50.0f, ch_to->m_wz+20.0f);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx+20.0f, mob_to->m_wy+50.0f, mob_to->m_wz+20.0f);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_STAR_FLARE], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_SHOCK_SPEAR:
	case EFFECT_DURANT_ATTACK:	// nate 2005-09-26 : ���Ʈ - ����
		{
			ef_sort.nType = FX_SHOCKSPEAR;

			if( skill_idx == EFFECT_DURANT_ATTACK )
			{
				if( mob_from )
				{
					ef_sort.Index = 1;	// nate 2005-09-26 : ���Ʈ - ����( ���� �÷��� )
					ef_sort.pMobFrom = mob_from;
					mob_from->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );
				}
				else
					return;
			}
			else
			{
				ef_sort.Index = 0;
				if (ch_to)
				{
					ef_sort.pNkChaTo = ch_to;
					// nate 2004 - 6 : ���彺 ���� �ȵ鸮�� ���� ����
					ef_sort.vPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
					ch_to->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );
				}
				else if (mob_to)
				{
					ef_sort.pMobTo = mob_to;
					// nate 2004 - 6 : ���彺 ���� �ȵ鸮�� ���� ����
					ef_sort.vPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy, mob_to->m_wz );
					mob_to->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );
				}
				else
					return;
			}

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_SHOCK], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_STONE_LANCE:
	case EFFECT_SKILL_BURNINGCRASH2:	// nate 2005-06-16 : Burning Crash - �� Ƣ�� ����Ʈ �߰�
		{
			ef_sort.nType = FX_STONERANCE;

			if( skill_idx == EFFECT_SKILL_BURNINGCRASH2 )
				ef_sort.Index = 1;
			else
				ef_sort.Index = 0;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				if( skill_idx == EFFECT_SKILL_BURNINGCRASH2 )
					g_pDSound->Play(g_EffectSound[EFF_SND_STONE_BREAK], x, y, z);
				else
					g_pDSound->Play(g_EffectSound[EFF_SND_STONE_LANCE], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_BUTTER:
		{
			ef_sort.nType = FX_FLY;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_BUTTERFLY], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_BEE:
		{
			ef_sort.nType = FX_BEE;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_BEE], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_MOTH:
		{
			ef_sort.nType = FX_MOTH;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_MOTH], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_BORA:
		{
			ef_sort.nType = FX_BORA;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_BORA], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_MOB_SHILON:
		{
			ef_sort.nType = FX_SHILON;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, ch_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}

			if (g_pDSound)
			{
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_EXPLO], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_HORN:
		{
			ef_sort.nType = FX_HORN;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_HORN], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_SILVERFLY:
		{
			ef_sort.nType = FX_SILVERFLY;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_SILVER_FLY], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_RAVEN:
		{
			ef_sort.nType = FX_RAVEN;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_RAVEN], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_KINES:
		{
			ef_sort.nType = FX_KINES;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_KYNES], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_NEO:
		{
			ef_sort.nType = FX_NEO;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_NEO_SNAKE], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_RING_KAISEN:
		{
			ef_sort.nType = FX_KAISEN;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_KAIZEN], x, y, z);
			}
		}
		break;

	//----------------------------------------------------------------------
	// �ϵ� (ü�� ����Ʈ��, ������ ����)
	//----------------------------------------------------------------------
	// Lyul_2005 �߰�
	// nate 2005-05-20 : Ȧ���δ�
	case EFFECT_SKILL_HOLLEY:
	case EFFECT_SKILL_WAND_CHAIN:
	case EFFECT_SKILL_WAND_WAVE_OF_DEATH:

		{
			ef_sort.nType = FX_WAND_CHAIN;

			if(skill_idx == EFFECT_SKILL_WAND_WAVE_OF_DEATH)
				ef_sort.num = 0;
			else if( skill_idx == EFFECT_SKILL_HOLLEY )
				ef_sort.num = 2;
			else
				ef_sort.num = 1;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)  	// ������ ��.
				{
					if(mob_from->m_nMobNum==354)//��ũ��...
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy+10.0f, mob_from->m_wz);
					else
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					if(mob_from->m_nMobNum==354)//��ũ��...
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy+10.0f, mob_from->m_wz);
					else
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_MOB_WORLDCUP_HAND:
	case EFFECT_SKILL_MOB_WORLDCUP_FOOT:
		{
			ef_sort.nType = FX_WORLDCUP;
			//		ef_sort.nCurFrame = m_CurFrame - m_AttackFrame -1;
			if( skill_idx == EFFECT_SKILL_MOB_WORLDCUP_HAND )
				ef_sort.Index = HIT_MOB_WORLDCUP_HAND;
			else if ( skill_idx == EFFECT_SKILL_MOB_WORLDCUP_FOOT )
				ef_sort.Index = HIT_MOB_WORLDCUP_FOOT;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			//		if (g_pDSound) {
			//			float x, y, z;
			//			x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
			//			y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
			//			z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

			//			g_pDSound->Play(g_EffectSound[EFF_SND_EXPLO], x, y, z);
			//		}
		}
		break;

	case EFFECT_SKILL_MOB_GUARDTOWER_FIRE:
		{
			ef_sort.nType = FX_GUARDTOWER;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			//		if (g_pDSound) {
			//			float x, y, z;
			//			x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
			//			y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
			//			z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

			//			g_pDSound->Play(g_EffectSound[EFF_SND_EXPLO], x, y, z);
			//		}
		}
		break;

	case EFFECT_SKILL_MOB_GUARDTOWER_LIGHTBALL:
		{
			ef_sort.nType = FX_LIGHTBALL;

			if (ch_to)  	// �´� �� (ĳ���Ͱ� ������)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy + 80.0f, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 80.0f, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT2], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_MOB_GUARDTOWER_PEBBLESHOT:
		{
			ef_sort.nType = FX_PEBBLESHOT;
			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy + 80.0f, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 80.0f, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT1], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_MOB_SHILONMASTER:
		{
			ef_sort.nType = FX_SHILONMASTER;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			//		if (g_pDSound) {
			//			float x, y, z;
			//			x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
			//			y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
			//			z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

			//			g_pDSound->Play(g_EffectSound[EFF_SND_EXPLO], x, y, z);
			//		}
		}
		break;

	case EFFECT_SKILL_CONTROL_LIGHT_GUARD:
		{
			ef_sort.nType = FX_CONTROL_LIGHT;
			ef_sort.Index = MONSTER_CONTROL_GUARD;

			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_CONTROL_LIGHT_DAMAGE:
		{
			ef_sort.nType = FX_CONTROL_LIGHT;
			ef_sort.Index = MONSTER_CONTROL_DAMAGE;

			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_MOB_MOB_SHINING_JAKAL:
		{
			ef_sort.nType = FX_LIGHTBALL;

			if (ch_to)  	// �´� �� (ĳ���Ͱ� ������)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;

				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 20.0f, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}

				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT2], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_MOB_BABYWORM:
		{
			ef_sort.nType = FX_GREENSMOKE;

			if (ch_to)  	// �´� �� (ĳ���Ͱ� ������)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (mob_from)  	// ������ ��.
				{
					if(mob_from->m_nMobNum == 360)
					{
						ef_sort.pMobFrom = mob_from;
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy +15.0f, mob_from->m_wz);
					}
					else
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy - 7.0f, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum( nEffInserNum );
				if( mob_from && mob_from->m_nMobNum==360 ) // �� ���� ���ʿ��� ���.
					mob_from->InsertEffectNum( nEffInserNum );
			}

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_SHOT2], x, y, z);
			}
		}
		break;
	case EFFECT_SKILL_MOB_ACCUMULATE:
		{
			ef_sort.nType = FX_LIGHTBALLBOOMNEW;

			if (ch_to)  	// �´� �� (ĳ���Ͱ� ������)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//x = ch_to->m_wx; y = ch_to->m_wy; z = ch_to->m_wz;
				if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_BOOM2], x, y, z);
			}
		}
		break;
	case EFFECT_SKILL_MOB_FIRE:
		{
			ef_sort.nType = FX_FIREBOOMSHORT;

			if (ch_to)  	// �´� �� (ĳ���Ͱ� ������)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)  	// �´� �� (ĳ���Ͱ� ������)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_BOOM1], x, y, z);
			}
		}
		break;
	case EFFECT_CONDITION:
		{
			ef_sort.nType = FX_CONDITIONEFFECTS;
			ef_sort.dwColor = timeGetTime();
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.pMobTo = NULL;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(mob_to)
			{
				ef_sort.pNkChaTo = NULL;
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_CONDITION2:
		{
			ef_sort.nType = FX_CONDITIONEFFECTS2;
			ef_sort.dwColor = timeGetTime();
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.pMobTo = NULL;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(mob_to)
			{
				ef_sort.pNkChaTo = NULL;
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_LIFEEXPENSION:	// nate 2005-07-06 : Life Expansion - InsertEffectNum
	case EFFECT_OPTIONSKILL:
		{
			if( skill_idx == EFFECT_SKILL_LIFEEXPENSION )
				ef_sort.nType = FX_LIFEEXPENSION;
			else
				ef_sort.nType = FX_OPTIONSKILLEFFECTS;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(mob_to)
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_HITPOWER:
		{
			ef_sort.nType = FX_HITPOWEREFFECTS;

			if( ch_from )
				ChaAttackType = ch_from->m_ChaAttackType;
			//		else if( mob_from )
			//			ChaAttackType = mob_from->m_ChaAttackType;

			switch( ChaAttackType )
			{
			case ATTACK_COUNT_HIT:
				ef_sort.Index = ATTACK_COUNT_HIT;
				break;
			case ATTACK_CRITICAL_HIT:
				ef_sort.Index = ATTACK_CRITICAL_HIT;
				break;
			case ATTACK_DEMOLITION_HIT:
				ef_sort.Index = ATTACK_DEMOLITION_HIT;
				break;
			case ATTACK_CROSS_HIT:
				ef_sort.Index = ATTACK_CROSS_HIT;
				break;

			case ATTACK_VAMPIRE_HIT: //�� ���� ���� ///�Ϻ����������׽�Ʈ ������ ���󸶻��� ȿ��.

				if( ch_from
						&& ch_from->m_Wearing[WEARING_WEAPON]
						&& (ch_from->m_Wearing[WEARING_WEAPON]->m_Vnum==1590 || ch_from->m_Wearing[WEARING_WEAPON]->m_Vnum==2694)
				  ) // ���󸶻縦 ����ִ� �� ���� �����̶��
				{
					InsertMagic( ch_from, mob_from, ch_to, mob_to, EFFECT_MURAMASA_GHOST );
					return; // ��ŵ�Ѵ�.
				}

				break;

			default:
				ef_sort.Index = ATTACK_CROSS_HIT;
				break;
			}
			if (ch_to)  	// �´� ��.
			{
				TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy + TargetHeight, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				switch (mob_to->m_Height)
				{
				case MOB_HEIGHT_HIGH_NUM:
					TargetHeight = MOB_HEIGHT_HIGH_VAL;
					break;
				case MOB_HEIGHT_LOW_NUM:
					TargetHeight = MOB_HEIGHT_LOW_VAL;
					break;
				default: // MOB_HEIGHT_MIDDLE_NUM:
					TargetHeight = MOB_HEIGHT_MIDDLE_VAL;
					break;
				}
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy + TargetHeight, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_ICE:
	case EFFECT_SKILL_WAND_ICE_STORM:
		{
			ef_sort.nType = FX_FROST;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_SLAYER:
	case EFFECT_SKILL_BURNINGCRASH:
		{
			ef_sort.nType = FX_EARTHQUAKE;
			// nate 2005-06-16 : Burning Crash - ����Ʈ �ε��� ����
			if( skill_idx == EFFECT_SKILL_BURNINGCRASH )
				ef_sort.Index = 1;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					// ������ ��.
					// 				ef_sort.pNkChaFrom = ch_from; // ���� �̰� �ȳ־��൵ �ȴ�. // 07-03-26 ����
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.nCurFrame = 0;
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
					return;

				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					// 				ef_sort.pNkChaFrom = ch_from; // ���� �̰� �ȳ־��൵ �ȴ�. // 07-03-26 ����
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_USE_BOOK_SPELL:
		{
			ef_sort.nType = FX_SCROLL_LIGHT;

			if (ch_from)
			{
				for( i = 0; i < 10; i++ )
				{
					ef_sort.nCurFrame = -i*2;
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx + RandomNum(-5.0f, 5.0f), ch_from->m_wy, ch_from->m_wz + RandomNum(-5.0f, 5.0f));
					ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				}
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_USE_BOOK:
		{
			ef_sort.nType = FX_SCROLLRING;

			if (ch_from)  	// �´� ��.
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_BOOK:
		{
			ef_sort.nType = FX_SCROLLDAMAGE;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.pNkChaTo = ch_to;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)  	// �´� ��.
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_SPELL:
		{
			ef_sort.nType = FX_SKILL_LIGHT;

			if (ch_from)
			{
				for( i = 0; i < 10; i++ )
				{
					ef_sort.nCurFrame = -i*2;
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx + RandomNum(-5.0f, 5.0f), ch_from->m_wy, ch_from->m_wz + RandomNum(-5.0f, 5.0f));
					ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				}
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_BLACKHOLE:
		{
			ef_sort.nType = FX_BLACKHOLE;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_AUTOLASER:
		{
			ef_sort.nType = FX_AUTOLASER;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.pNkChaFrom = ch_from;
				}
				else if (mob_from)
				{
					ef_sort.pMobFrom = mob_from;
				}
				else
				{
					return;
				}

				int effectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum(effectNum);
				if( ch_from )
					ch_from->InsertEffectNum(effectNum);
				if( mob_from )
					mob_from->InsertEffectNum(effectNum);
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.pNkChaFrom = ch_from;
				}
				else if (mob_from)
				{
					ef_sort.pMobFrom = mob_from;
				}
				else
				{
					return;
				}

				int effectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum(effectNum);
				if( ch_from )
					ch_from->InsertEffectNum(effectNum);
				if( mob_from )
					mob_from->InsertEffectNum(effectNum);
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_CHARGECANNON:
		{
			ef_sort.nType = FX_CHARGECANNON;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_FLAME:
		{
			ef_sort.nType = FX_FLAME;

			if (ch_from)	// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);

				if (ch_to)	// �´� �� (ĳ���Ͱ� ������)
					ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				else if (mob_to)
					ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				else
					ef_sort.vTargetPos = D3DVECTOR(ch_from->m_wx + (cos(ch_from->m_dir) * 15.0f)
												   , ch_from->m_wy
												   , ch_from->m_wz + (sin(ch_from->m_dir) * 15.0f));

				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -2;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_from)	// ������ ��.
			{
				ef_sort.subNum = 1;
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx + (cos(mob_from->m_dir) * 3.0f)
										 , mob_from->m_wy
										 , mob_from->m_wz + (sin(mob_from->m_dir) * 3.0f));

				if (ch_to)	// �´� �� (ĳ���Ͱ� ������)
					ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				else if (mob_to)
					ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				else
					ef_sort.vTargetPos = D3DVECTOR(mob_from->m_wx + (cos(mob_from->m_dir) * 20.0f)
												   , mob_from->m_wy
												   , mob_from->m_wz + (sin(mob_from->m_dir) * 20.0f));

				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -2;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_S_EQUIP:
		{
			ef_sort.nType = FX_ONOFFEFFECTS;
			ef_sort.Index = 1; // ���� �̰���...�� ������....
			if (ch_from)
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SCANVIEW:
		{
			ef_sort.nType = FX_SCANVIEW;

			if (ch_from)
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_JOINT_LIFE:
		{
			ef_sort.nType = FX_LIFECOMMON;

			if (ch_from)
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_LIFE_LIGHT:
		{
			ef_sort.nType = FX_LIFELIGHT;

			if (ch_from)
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	case EFFECT_SKILL_WAND_ARROW:
		{
			ef_sort.nType = FX_MAGICARROW;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					if( mob_from->m_nMobNum == 288 )
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 5.0f, mob_from->m_wz);
					else
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_WAND_LASER:
		{
			ef_sort.nType = FX_MAGICLASER;

			if( skill_idx == EFFECT_SKILL_WAND_LASER )
				ef_sort.Index = 1;

			if (ch_from)
				ef_sort.pNkChaFrom = ch_from;
			else if (mob_from)
				ef_sort.pMobFrom = mob_from;
			else
				return;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));		// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));	 // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else
				return;

			// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}

		break;

	case EFFECT_SMALL_ROCKET:
	case EFFECT_MIDDLE_ROCKET:
		{
			ef_sort.nType = FX_ROCKET;

			if( skill_idx == EFFECT_SMALL_ROCKET )
				ef_sort.Index = 1;
			else if( skill_idx == EFFECT_MIDDLE_ROCKET )
				ef_sort.Index = 2;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_DEMICRUSHER:
		{
			ef_sort.nType = FX_DEMICRUSHER;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;
	//��Ʈ���� �׷��� ���� ���� ����Ʈ ����(mungmae-3/21)
	case EFFECT_FIRETOWER_EFF:
		{
			ef_sort.nType = FX_FIRETOWER;

			if (mob_from)
			{
				ef_sort.pMobFrom = mob_from;
				ef_sort.vTargetPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_WAND_METEORITE:
		{
			ef_sort.nType = FX_METEORITE;
			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx+20.0f, ch_to->m_wy+100.0f, ch_to->m_wz+20.0f);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx+20.0f, mob_to->m_wy+100.0f, mob_to->m_wz+20.0f);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - g_pRoh->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - g_pRoh->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - g_pRoh->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_DROP_STONE], x, y, z);
			}
		}
		break;

	case EFFECT_SKILL_WAND_CHAOS:
		{
			ef_sort.nType = FX_CHAOS;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_GATHERING:
		{
			ef_sort.nType = FX_GATHERINGGUN;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.pNkChaFrom = ch_from;
				}
				else if (mob_from)
				{
					ef_sort.pMobFrom = mob_from;
				}
				else
				{
					return;
				}

				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));		// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����

			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.pNkChaFrom = ch_from;
				}
				else if (mob_from)
				{
					ef_sort.pMobFrom = mob_from;
				}
				else
				{
					return;
				}
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));	// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else
			{
				return;
			}

			// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_SKILL_DRAGON_FIRE:
		{
			ef_sort.nType = FX_DRAGONEFFECTS;
			ef_sort.num = 0;
			int nEffectNum = 0;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.pNkChaFrom = ch_from;
					ef_sort.Index = ch_from->m_nCharIndex;
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 80.0f, mob_from->m_wz);
					ef_sort.pMobFrom = mob_from;
					ef_sort.Index = mob_from->m_nVirId;
				}
				else
				{
					return;
				}
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

				ef_sort.nCurFrame = -1;
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

				ef_sort.nCurFrame = -2;
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

				ef_sort.nCurFrame = -3;
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.pNkChaFrom = ch_from;
					ef_sort.Index = ch_from->m_nCharIndex;
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					ef_sort.pMobFrom = mob_from;
					ef_sort.Index = mob_from->m_nVirId;
				}
				else
				{
					return;
				}
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

				ef_sort.nCurFrame = -1;
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

				ef_sort.nCurFrame = -2;
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;
				ef_sort.nCurFrame = -3;
				nEffectNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum(nEffectNum);
				if (ch_from)
					ch_from->InsertEffectNum(nEffectNum);
				else if (mob_from)
					mob_from->InsertEffectNum(nEffectNum);
				else
					return;

			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_DRAGON_ICE:
		{
			ef_sort.nType = FX_DRAGONEFFECTS;
			ef_sort.num = 1;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.pNkChaFrom = ch_from;
					ef_sort.Index = ch_from->m_nCharIndex;
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 80.0f, mob_from->m_wz);
					ef_sort.pMobFrom = mob_from;
					ef_sort.Index = mob_from->m_nVirId;
				}
				else
				{
					return;
				}
				/*
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -1;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -2;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -3;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				*/          // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -1;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -2;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -3;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.pNkChaFrom = ch_from;
					ef_sort.Index = ch_from->m_nCharIndex;
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					ef_sort.pMobFrom = mob_from;
					ef_sort.Index = mob_from->m_nVirId;
				}
				else
				{
					return;
				}
				/*
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -1;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -2;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -3;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				*/          // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -1;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -2;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -3;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_to->InsertEffectNum( nEffInserNum );
				if( ch_from )
					ch_from->InsertEffectNum( nEffInserNum );
				if( mob_from )
					mob_from->InsertEffectNum( nEffInserNum );

			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_PET_BLESS: // �� ��ų �극�� ����Ʈ.
		{
			ef_sort.nType = FX_DRAGONEFFECTS;
			ef_sort.num = 2; // �̰� �� �극����� ǥ��

			if( mob_from ) // �� ��ų�̴ϱ� �길����.
			{
				ef_sort.vPos = D3DVECTOR( mob_from->m_wx, mob_from->m_wy + 16.0f, mob_from->m_wz );
				ef_sort.pMobFrom = mob_from;
				ef_sort.Index = mob_from->m_nVirId; // ���� �ε����� ����صд�.

				if( ch_to )
				{
					ef_sort.pNkChaTo = ch_to;
					ef_sort.vTargetPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
				}
				else if( mob_to )
				{
					ef_sort.pMobTo = mob_to;
					ef_sort.vTargetPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy, mob_to->m_wz );
				}
				else
					return;
				/*
				ef_sort.nCurFrame = -21;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -22;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -23;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				ef_sort.nCurFrame = -24;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				*/          // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				ef_sort.nCurFrame = -21;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
				if( ch_to )
					ch_to->InsertEffectNum( nEffInserNum );
				if( mob_to )
					mob_to->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -22;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
				if( ch_to )
					ch_to->InsertEffectNum( nEffInserNum );
				if( mob_to )
					mob_to->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -23;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
				if( ch_to )
					ch_to->InsertEffectNum( nEffInserNum );
				if( mob_to )
					mob_to->InsertEffectNum( nEffInserNum );

				ef_sort.nCurFrame = -24;
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
				if( ch_to )
					ch_to->InsertEffectNum( nEffInserNum );
				if( mob_to )
					mob_to->InsertEffectNum( nEffInserNum );
			}
		}
		break;

	case EFFECT_SKILL_RING_SHININGEAGLE:
		{
			ef_sort.nType = FX_PHENIX;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_RING_GRYPHON:
		{
			ef_sort.nType = FX_GRYPHON;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	case EFFECT_SKILL_RING_DRAGON2: ///����������
	case EFFECT_SKILL_RING_DRAGON:
		{
			ef_sort.nType = FX_DRAGON;

			if( skill_idx == EFFECT_SKILL_RING_DRAGON2 ) ///����������
				ef_sort.num = 1; // �̰ɷ� �� �巡�� ������ �ƴϸ� �׳� �巡�� ������ ����.
			else
				ef_sort.num = 0;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	case EFFECT_SKILL_RING_SPHINX:
		{
			ef_sort.nType = FX_SPHINX;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_KHAN_HIT:
		{
			ef_sort.nType = FX_KHANHITEFFECTS;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_WARGIANT_MULTI://wan:2005-01	//���ǵ� ���̾�(�ٷ���)�� ����
		{
			ef_sort.nType = FX_WARGIANTMULTI;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if( mob_from )
				{
					vPosFrom = D3DVECTOR(mob_from->m_wx, 0, mob_from->m_wz);
					vPosTo = D3DVECTOR(ch_to->m_wx, 0, ch_to->m_wz);
					get_normal_vector(vDir, vPosFrom, vPosTo);
					vDir *= -10.0f;

					ef_sort.vTargetPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					ef_sort.vTargetPos += D3DVECTOR(RandomNum(-7.0f, 7.0f), 100.0f, RandomNum(-7.0f, 7.0f));
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					ef_sort.vPos += vDir;
				}
				else if(ch_from) //wan:2005-01	//���ǵ� ���̾�(�ٷ���)
				{
					vPosFrom = D3DVECTOR(ch_from->m_wx, 0, ch_from->m_wz);
					vPosTo = D3DVECTOR(ch_to->m_wx, 0, ch_to->m_wz);
					get_normal_vector(vDir, vPosFrom, vPosTo);
					vDir *= -3.0f;

					ef_sort.vTargetPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.vTargetPos += D3DVECTOR(RandomNum(-7.0f, 7.0f), 100.0f, RandomNum(-7.0f, 7.0f));
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.vPos += vDir;
				}
				else
					return;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				if( mob_from )
				{
					vPosFrom = D3DVECTOR(mob_from->m_wx, 0, mob_from->m_wz);
					vPosTo = D3DVECTOR(mob_to->m_wx, 0, mob_to->m_wz);
					get_normal_vector(vDir, vPosFrom, vPosTo);
					vDir *= -10.0f;

					ef_sort.vTargetPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					ef_sort.vTargetPos += D3DVECTOR(RandomNum(-7.0f, 7.0f), 100.0f, RandomNum(-7.0f, 7.0f));
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					ef_sort.vPos += vDir;
				}
				else if(ch_from) //wan:2005-01	//���ǵ� ���̾�(�ٷ���)
				{
					vPosFrom = D3DVECTOR(ch_from->m_wx, 0, ch_from->m_wz);
					vPosTo = D3DVECTOR(mob_to->m_wx, 0, mob_to->m_wz);
					get_normal_vector(vDir, vPosFrom, vPosTo);
					vDir *= -3.0f;

					ef_sort.vTargetPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.vTargetPos += D3DVECTOR(RandomNum(-7.0f, 7.0f), 100.0f, RandomNum(-7.0f, 7.0f));
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					ef_sort.vPos += vDir;
				}
				else
					return;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_MOB_SOULDUST:	// ���� ���� ����
		{
			ef_sort.nType = FX_SOULDUST;

			if (ch_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;

				if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;

				if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_WAND_MAGICSWORD:	// ���� ���� ����
		{
			ef_sort.nType = FX_MAGICSWORD;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					if( mob_from->m_nMobNum == 290 )
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy + 45.0f, mob_from->m_wz);
					else
						ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_HELL_TOUCH:
		{
			ef_sort.nType = FX_VAMPIREATTACK;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_VANPIRE_TOUCH:
		{
			ef_sort.nType = FX_VAMPIRE;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_MELODY_OF_DEF:
	case EFFECT_SKILL_MELODY_OF_GUD:
		{
			ef_sort.nType = FX_MUSICALNOTE;

			if (ch_from)
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_SKILL_MOB_FALLOFFSTONE:
		{
			ef_sort.nType = FX_FALLOFFSTONE;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_MOB_STONERANCE2:
		{
			ef_sort.nType = FX_STONERANCE2;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_MOB_DRILLSTONE:
		{
			ef_sort.nType = FX_DRILLSTONE;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;




//-------------------------------------------------------------------------
// EFFECT_DROPCANDY
	case EFFECT_DROPCANDY: // �ջ��� �ӽ� ��ȣ
		{
			ef_sort.nType = FX_DROPCANDY;
			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					// ������ �Ѹ� ���ǵǸ� �ȴ�.
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_DROPCANDY], x, y, z);
				}
			}
			else if(ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					// ������ �Ѹ� ���ǵǸ� �ȴ�.
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_DROPCANDY], x, y, z);
				}
			}
		}
		break;


	//-------------------------------------------------------------------------
	// EFFECT_DROPAPPLE
	case EFFECT_DROPAPPLE: // �ջ��� �ӽ� ��ȣ
		{
			ef_sort.nType = FX_DROPAPPLE;
			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
			if (g_pDSound)
			{
				// ������ �Ѹ� ���ǵǸ� �ȴ�.
				float x, y, z;
				x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
				y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
				z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;

				g_pDSound->Play(g_EffectSound[EFF_SND_DROPCANDY], x, y, z);
			}
		}
		break;

	case EFFECT_DROPSTARCANDY: // �ջ��� �ӽ� ��ȣ
		{
			ef_sort.nType = FX_DROPSTARCANDY;
			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.dwColor = timeGetTime();
				ef_sort.pParticle = new Deco_Particle[FX_DROP_STARCANDY_COUNT];
				ZeroMemory(ef_sort.pParticle, sizeof(Deco_Particle) * FX_DROP_STARCANDY_COUNT);

				for( int i = 0; i < FX_DROP_STARCANDY_COUNT; ++i)
				{
					int dx = (rand()%101 - 50), dy = (rand()%31 - 10), dz = (rand()%101 - 50);
					ef_sort.pParticle[i].first_Pos = D3DVECTOR(mob_to->m_wx + dx,
													 mob_to->m_wy + 100 + dy,
													 mob_to->m_wz + dz);
					ef_sort.pParticle[i].start_time = 0;
				}

				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					// ������ �Ѹ� ���ǵǸ� �ȴ�.
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_DROPCANDY], x, y, z);
				}
			}
			else if(ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.dwColor = timeGetTime();
				ef_sort.pParticle = new Deco_Particle[FX_DROP_STARCANDY_COUNT];
				ZeroMemory(ef_sort.pParticle, sizeof(Deco_Particle) * FX_DROP_STARCANDY_COUNT);
				for( int i = 0; i < FX_DROP_STARCANDY_COUNT; ++i)
				{
					int dx = (rand()%101 - 50), dy = (rand()%31 - 10), dz = (rand()%101 - 50);
					ef_sort.pParticle[i].first_Pos = D3DVECTOR(mob_to->m_wx + dx,
													 mob_to->m_wy + 100 + dy,
													 mob_to->m_wz + dz);
					ef_sort.pParticle[i].start_time = 0;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					// ������ �Ѹ� ���ǵǸ� �ȴ�.
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_DROPCANDY], x, y, z);
				}
			}
		}
		break;
	//-------------------------------------------------------------------------------------------
	//	�߰� �߰� ��ų
	//-------------------------------------------------------------------------------------------
	//(��ĭ, Active, 200)
	case EFFECT_SKILL_HELL_CRY:
		{
			ef_sort.nType = FX_HELLCRY;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_HELL], x, y, z);
				}
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_HELL], x, y, z);
				}
			}
			else if (ch_from)  	// ������ ��.
			{
				ef_sort.pNkChaTo = ch_from;
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - ch_from->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_from->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_from->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_HELL], x, y, z);
				}
			}
			else
				return;
		}
		break;

	//(ī�̸���, Active, 200)
	case EFFECT_SKILL_TORNADO_RUIN:
		{
			ef_sort.nType = FX_TORNADORUIN;
			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_TONADO], x, y, z);
				}
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
					return;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_TONADO], x, y, z);
				}
			}
			else
				return;
		}
		break;

	//(�޸�, Active, 200)
	case EFFECT_SKILL_AIR_RAID:
		{
			ef_sort.nType = FX_AIRRAID;

			if (ch_from)		// ������ ��.
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			else if (mob_from)	// ������ ��.
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	//(���̵��, Active, 200)�����Ǽ�
	case EFFECT_SKILL_SUMMON_PARTITION:
		{
			ef_sort.nType = FX_SUMMONPARTITION;
			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));

				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_FISSION], x, y, z);
				}
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_RING_DEVIL2: ///����������
	case EFFECT_SKILL_RING_DEVIL:
		{
			ef_sort.nType = FX_DEVILRING;

			if( skill_idx == EFFECT_SKILL_RING_DEVIL2 ) ///����������
				ef_sort.num = 1; // �̰ɷ� �� �巡�� ������ �ƴϸ� �׳� �巡�� ������ ����.
			else
				ef_sort.num = 0;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_RING_BULKAN: ///��ĭ��
		{
			ef_sort.nType = FX_SUMMONRING; // ��ȯ�� �� ����Ʈ.
			ef_sort.num = EFFECT_SKILL_RING_BULKAN;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx-20.0f, ch_to->m_wy, ch_to->m_wz); // �ణ ���� ������ �Ű�����Ѵ�.
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx-20.0f, mob_to->m_wy, mob_to->m_wz); // �ణ ���� ������ �Ű�����Ѵ�.
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	//------------------------------------------------------------------
	// Lyul_2005 Skill Effect
	//------------------------------------------------------------------

	// ����� ���� Effect
	// �ƹ� ǥ���� ���� ������ ��� Effect�� ���;� �ϴµ�..
	case EFFECT_SKILL_DSTONE:
		{
			if(ch_from)
			{
				ef_sort.nType = FX_DSTONE;
				float x = cos(ch_from->m_dir)  * 15.0f;
				float z = sin(ch_from->m_dir)  * 15.0f;
				ef_sort.vTargetPos = D3DVECTOR(ch_from->m_wx + x, ch_from->m_wy, ch_from->m_wz + z);
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			}
			else
				return;
		}
		break;
	// ���������Ϳ� �������� �ʰ� ��ǥ�� ����صΰ� ����.(by ����) (�ڼ��Ѱ� FxAsult.cpp �ּ� ����.)
	case EFFECT_SKILL_ASSAULT:	// ���Ʈ
	case EFFECT_SKILL_DASSAULT:	// ��� ���Ʈ
		{
			if( ch_from )
			{
				ef_sort.nType = FX_ASSAULT;

				if( skill_idx == EFFECT_SKILL_DASSAULT )
				{
					ef_sort.num = 1;
					// Sound
					if( g_pDSound )
					{
						if(ch_from->m_Sex)
							g_pDSound->Play(g_EffectSound[EFF_SND_W_ASSAULT2]);
						else
							g_pDSound->Play(g_EffectSound[EFF_SND_M_ASSAULT2]);
					}
				}
				else
				{
					ef_sort.num = 0;
					// Sound
					if( g_pDSound )
					{
						if(ch_from->m_Sex)
							g_pDSound->Play(g_EffectSound[EFF_SND_W_ASSAULT1]);
						else
							g_pDSound->Play(g_EffectSound[EFF_SND_M_ASSAULT1]);
					}
				}

				if (ch_to)
					ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				else if (mob_to)
					ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);

				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);

				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			}
			else
				return;
		}
		break;

	// ����� ���� ���� ����Ʈ
	case EFFECT_DSTONE_EFF:
		{
			if(mob_from)
			{
				ef_sort.nType = FX_DSTONEEFF;
				ef_sort.pMobFrom = mob_from;
				ef_sort.num = mob_from->m_nVirId;
				ef_sort.subNum = mob_from->m_nMobNum;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	//------------------------------------------------------------------
	// �转
	case EFFECT_SKILL_BASH:
		{
			if(mob_to)
			{
				ef_sort.nType = FX_BASH;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx , mob_to->m_wy, mob_to->m_wz );
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(ch_to)
			{
				ef_sort.nType = FX_BASH;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx , ch_to->m_wy, ch_to->m_wz );
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}

		break;
	//wan:2004-12
	//------------------------------------------------------------------
	// ���� ������
	case EFFECT_SKILL_DSLASH:
		{
			if(mob_from)
				ef_sort.num = 1;
			else
				ef_sort.num = 0;

			if(mob_to)
			{
				ef_sort.nType = FX_DSLASH;
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx , mob_to->m_wy, mob_to->m_wz );
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(ch_to)
			{
				ef_sort.nType = FX_DSLASH;
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx , ch_to->m_wy, ch_to->m_wz );
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}

		break;
	//------------------------------------------------------------------
	// Ÿ������
	case EFFECT_SKILL_TIMECHG:
		{
			ef_sort.nType = FX_VAMPIREATTACK;
			if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else
					return;

				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
//-------------------------------------------------------------------------------------------
	case EFFECT_SKILL_STONEBRUST:
		{
			if(mob_from)
			{
				ef_sort.nType = FX_DSTONEBRUST;
				ef_sort.pMobFrom = mob_from;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	// nate 2005-06-15 : Auto Mine - Set Effect
	case EFFECT_SKILL_MINE:
		{

			if( !ch_from )
				return;

			ef_sort.nType = FX_AUTOMINE;
			ef_sort.pNkChaFrom = ch_from;
			ef_sort.num = ch_from->m_nSkillLevel;
			ef_sort.subNum = ch_from->m_nSkillStep;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				else if (mob_from)
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				else
					return;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));			 // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;

				if (ch_from)
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				else if (mob_from)
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				else
					return;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));	// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else
				return;

			// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}

		break;
	// nate 2005-07-08 : Summon Squad - Insert Magic
	case EFFECT_SKILL_SUMMONSQUAD:
		{
			if( ch_from )
			{
				ef_sort.nType = FX_SUMMONSQUAD;
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;
	case EFFECT_SKILL_HELLDOWN:
		{
			if( ch_from )
			{
				if(( g_pRoh == ch_from && m_bRClickDown == 1 )
						|| ( g_pRoh != ch_from && ch_from->m_nSkillStep <= 1 ) )
				{
					ef_sort.nType = FX_HELLDOWN;
					if (g_pDSound)
					{
						if( g_pRoh->m_Sex == 0)
							g_pDSound->Play(g_EffectSound[EFF_SND_HELLDOWN_CAST_M]);
						else
							g_pDSound->Play(g_EffectSound[EFF_SND_HELLDOWN_CAST_W]);
					}
				}
				else if(( g_pRoh == ch_from &&  m_bRClickDown == 2 )
						|| ( g_pRoh != ch_from && ch_from->m_nSkillStep == 10 ) )
				{
					ef_sort.nType = FX_HELLDOWN2;
					if (g_pDSound)
					{
						if( g_pRoh->m_Sex == 0)
						{
							g_pDSound->Stop(g_EffectSound[EFF_SND_HELLDOWN_CAST_M]);
							g_pDSound->Play(g_EffectSound[EFF_SND_HELLDOWN_FINISH_M]);
						}
						else
						{
							g_pDSound->Stop(g_EffectSound[EFF_SND_HELLDOWN_CAST_W]);
							g_pDSound->Play(g_EffectSound[EFF_SND_HELLDOWN_FINISH_W]);
						}
					}
				}
				else
					return;

				if(ch_to)
				{
					/*
					ef_sort.pNkChaTo = ch_to;
					ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					ef_sort.pNkChaFrom = ch_from;
					ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					*/
					// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
					ef_sort.pNkChaTo = ch_to;
					ef_sort.pNkChaFrom = ch_from;
					nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
					ch_to->InsertEffectNum(nEffInserNum);
					ch_from->InsertEffectNum(nEffInserNum);
				}
				else if(mob_to)
				{
					/*
					ef_sort.pMobTo = mob_to;
					mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					ef_sort.pNkChaFrom = ch_from;
					ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					*/
					// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
					ef_sort.pMobTo = mob_to;
					ef_sort.pNkChaFrom = ch_from;
					nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
					mob_to->InsertEffectNum(nEffInserNum);
					ch_from->InsertEffectNum(nEffInserNum);
				}
				else
					return;
			}
			else
				return;
		}
		break;

	case EFFECT_DURANT_BEAM:	// nate 2005-09-29 : ���Ʈ - ����
		{
			if( mob_from )
			{
				ef_sort.nType = FX_DURANT_BEAM;
				ef_sort.pMobFrom = mob_from;
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;

	case EFFECT_DURATT_TARGET:	// nate 2005-09-26 : ���Ʈ - ��󿡰� �������� ����Ʈ
		{
			if( ch_to )
			{
				ef_sort.nType = FX_DURANT_TARGET;
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
				ch_to->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );
			}
		}
		break;

	case EFFECT_SKILL_POISON:	// nate 2005-11-03 : ������ - InsertEffect
		{
			ef_sort.nType = FX_POISON;
			ef_sort.Index = skill_idx;	// ���� ���� ������ ��ų ����

			if( ch_from )
			{
				float fX = cos(ch_from->m_dir) * 12.0f;
				float fZ = sin(ch_from->m_dir) * 12.0f;
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx + fX, ch_from->m_wy, ch_from->m_wz + fZ);

				if( ch_to )
					ef_sort.vTargetPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
				else if( mob_to )
					ef_sort.vTargetPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy, mob_to->m_wz );
				else
					return;

				ch_from->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );
			}
			else if( mob_from )
			{
				float fX = cos(ch_from->m_dir) * 12.0f;
				float fZ = sin(ch_from->m_dir) * 12.0f;
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx + fX, mob_from->m_wy, mob_from->m_wz + fZ);

				if( ch_to )
					ef_sort.vTargetPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
				else if( mob_to )
					ef_sort.vTargetPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy, mob_to->m_wz );
				else
					return;

				mob_from->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );
			}
		}
		break;

	//==============================================================
	// �ѷθ� �̵���Ű�� ��ų�� ���⿡ ���� ó���Ͻÿ�
	case EFFECT_CACTUS:		// nate 2005-11-22 : ��ȯ ĳũ�ͽ�
	case EFFECT_DANDELION:	// nate 2005-11-22 : �������
		{
			ef_sort.nType = FX_ATTACK_MOVELOLO;
			ef_sort.Index = skill_idx;
			if( mob_from )
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			else
				return;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	//===============================================================
	// ��ġ�� ������ �ѷ� ���ϸ��̼� ����Ʈ�� �̰����� ó���Ͻÿ�
	// ���� : Ÿ�� ��ǥ�� ����
	case EFFECT_SPORE:		// nate 2005-11-22 : ������
		{
			ef_sort.nType = FX_ATTACK_FIXLOLO;
			ef_sort.Index = skill_idx;	// ���� ���� ������ ��ų ����

			if (ch_to)
			{
				ef_sort.vTargetPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy, mob_to->m_wz );
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	//===============================================================
	// ��ġ�� ������ �ѷ� ���ϸ��̼� ����Ʈ�� �̰����� ó���Ͻÿ�
	// ���� : �ҽ� ��ǥ�� ����
	case EFFECT_SKILL_ELECTRICSHOT:		// nate 2005-11-23 : �Ϸ�Ʈ�� �� ���� ����Ʈ - ���� Ŀ���� ���
	case EFFECT_SKILL_MOB_SNAKEBOSS:	// nate 2006-01-03 : ���Ʈ�� ���� �޵��
	case EFFECT_SKILL_MOB_SNAKEBOSS3:	// nate 2006-01-26 : ���Ʈ�� ���� �޵�� - ���� ��ų
		{
			ef_sort.Index = skill_idx;	// ���� ���� ������ ��ų ����
			ef_sort.nType = FX_ATTACK_FIXLOLO;

			if (ch_from)
			{
				float fX = 0.0f, fZ = 0.0f;
				if( skill_idx == EFFECT_SKILL_ELECTRICSHOT )
				{
					fX = cos(ch_from->m_dir)  * 18.0f;
					fZ = sin(ch_from->m_dir)  * 18.0f;

					if (ch_to)
						ef_sort.vTargetPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy + 17.0f, ch_to->m_wz );
					else if (mob_to)
						ef_sort.vTargetPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy + 17.0f, mob_to->m_wz );

					ef_sort.pNkChaFrom = ch_from;
				}

				ef_sort.vPos = D3DVECTOR( ch_from->m_wx + fX, ch_from->m_wy, ch_from->m_wz + fZ );
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(mob_from)
			{
				ef_sort.pMobFrom = mob_from;
				ef_sort.vPos = D3DVECTOR( mob_from->m_wx, mob_from->m_wy, mob_from->m_wz );
				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_FLAMESPEAR: // ī�� 300���� ��ų ///�÷��ӽ��Ǿ�
		{
			ef_sort.nType = FX_FLAMESPEAR;
			ef_sort.num = 0; // Phase �� ���δ�.

			if( ch_from )
			{
				ef_sort.pNkChaFrom = ch_from;
				if( ch_to )
				{
					ef_sort.pNkChaTo = ch_to;
					ef_sort.vPos = D3DVECTOR( ch_from->m_wx, ch_from->m_wy+35.0f, ch_from->m_wz ); // ������ǥ.
					ef_sort.vCurPos = ef_sort.vPos; // ������ǥ.
					ef_sort.vTargetPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy+10.0f, ch_to->m_wz ); // ���� ��ǥ�� �Ǵ� ��ġ.(���⸦ �������� Ÿ���� �����Ѵ�.) // �ణ ���� Ÿ�����Ѵ�.
					ef_sort.vSortPos = Normalize( ef_sort.vTargetPos - ef_sort.vPos ); // ���� Ÿ�� ��ġ�� �ƴ϶� â�� ���ϴ� ���� ���ͷ� ���.
					i = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort); // From�� To ���ʿ� �߰��Ѵ�.
					ch_to->InsertEffectNum( i );
				}
				else if( mob_to )
				{
					ef_sort.pMobTo = mob_to;
					ef_sort.vPos = D3DVECTOR( ch_from->m_wx, ch_from->m_wy+35.0f, ch_from->m_wz ); // ������ǥ.
					ef_sort.vCurPos = ef_sort.vPos; // ������ǥ.
					ef_sort.vSortPos = Normalize( ef_sort.vTargetPos - ef_sort.vPos ); // ���� Ÿ�� ��ġ�� �ƴ϶� â�� ���ϴ� ���� ���ͷ� ���.
					i = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort); // From�� To ���ʿ� �߰��Ѵ�.
					mob_to->InsertEffectNum( i );
				}
				else
					return;

				ch_from->InsertEffectNum( i );
			}
			else
				return;
		}
		break;

	case EFFECT_FROZEN_SHOT:		// �޸� ������ ��.
		{
			ef_sort.Index = skill_idx;	// ���� ���� ������ ��ų ����
			ef_sort.nType = FX_ATTACK_FIXLOLO;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR( ch_to->m_wx, ch_to->m_wy, ch_to->m_wz );
				// ������ ���� �ٴҰű� ������ ���� ���� �ε����� ����صд�.
				ef_sort.subNum = rand() % ch_to->GetBiped()->m_BipedNum; // ���� ���� �ε����� �����ϰ� ���Ѵ�.
				ef_sort.dwColor = timeGetTime(); // ������ �ð�. �����ð� �پ��ִ� �������� ������ �ʿ�.

				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));

				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_FROZEN_SHOT], x, y, z);
				}
			}
			else if(mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR( mob_to->m_wx, mob_to->m_wy, mob_to->m_wz );
				// ������ ���� �ٴҰű� ������ ���� ���� �ε����� ����صд�.
				ef_sort.subNum = rand() % mob_to->GetBiped(0)->m_BipedNum; // ���� ���� �ε����� �����ϰ� ���Ѵ�.

				// ���ý��� ���̴� ���... �ӵ� ������ ĵ��.
				//			ef_sort.num = rand() % mob_to->m_pCapSyong->m_ObjectCount; // ���� �Ž� ��ȣ.
				//			ef_sort.subNum = rand() % mob_to->m_pCapSyong->m_Csy[ef_sort.num].m_VertexCount; // �Ž��� ������ ���.

				ef_sort.dwColor = timeGetTime(); // ������ �ð�. �����ð� �پ��ִ� �������� ������ �ʿ�.

				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));

				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_FROZEN_SHOT], x, y, z);
				}
			}
			else
				return;
		}
		break;

	///�δ�1
	case EFFECT_SKILL_MOB_LEGKNOCK1:	// ��ī�� �δ� ���� ���׳� �Ϲݰ��� ����Ʈ. ///�δ�1
	case EFFECT_SKILL_MOB_LEGKNOCK2:	// ��ī�� �δ� ���� ���׳� ���߰��� ����Ʈ. ///�δ�1

		{
			ef_sort.nType = FX_ATTACK_FIXLOLO;
			ef_sort.Index = skill_idx;	// ���� ���� ������ ��ų ����

			if( mob_from )
			{
				ef_sort.pMobFrom = mob_from;
				ef_sort.vPos = D3DVECTOR( mob_from->m_wx, mob_from->m_wy, mob_from->m_wz );

				// ��Ƽ ������ ���� ���� ������ ���� ���� ���̸� ����صд�.
				D3DVECTOR Eye;
				pCMyApp->GetEyePos( Eye );
				D3DVECTOR At;
				pCMyApp->GetEyeAtPos( At );
				ef_sort.vSortPos.x = Eye.y; // vSortPos���� ���.
				ef_sort.vSortPos.y = At.y;


				mob_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	//====================================================================
	// 2D ����Ʈ
	// ���� : �� ĳ������ ����
	case EFFECT_SKILL_MOB_SNAKEBOSS2:	// nate 2006-01-26 : ����Ʈ �� �Ϲݰ���
		{
			ef_sort.nType = FX_TLVERTEX;
			ef_sort.Index = EFFECT_SKILL_MOB_SNAKEBOSS2;
			if(g_pRoh)
				g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		break;

	case EFFECT_SKILL_FLYINGCRASH2:
		{
			ef_sort.nType = FX_FLYINGCRASH;
			if (ch_from)
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_FLYINGCRASH:
		{
			ef_sort.nType = FX_FLYINGCRASH2;
			if(mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx , mob_to->m_wy, mob_to->m_wz );
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(ch_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx , ch_to->m_wy, ch_to->m_wz );
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_SHADOWSLASH:// mungmae 2005/12/01 : ���̺긮�� - ������ ������(���۽�)
		{
			ef_sort.nType = FX_SHADOWSLASH;
			if( ch_from )
			{
				ef_sort.vPos = D3DVECTOR( ch_from->m_wx, ch_from->m_wy, ch_from->m_wz ); ///�����޺� �� ����.
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;

	case EFFECT_SKILL_SHADOWSLASH2:// mungmae 2005/12/01 : ���̺긮�� - ������ ������(���۽�)
		{
			ef_sort.nType = FX_SHADOWSLASH2;
			if( ch_from )
			{
				//			ef_sort.pNkChaFrom = ch_from;
				ef_sort.vPos = D3DVECTOR( ch_from->m_wx, ch_from->m_wy, ch_from->m_wz ); ///�����޺� �� ����.
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;

	case EFFECT_SPEEDUPSMOKE:
		{
			ef_sort.nType = FX_SPEEDUPSMOKE;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				else
					return;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;

	case EFFECT_SPIRITMODE:// ���Ǹ�(�ߵ��� ���)
		{
			ef_sort.nType = FX_SPIRITMODE;
			if( ch_from )
			{
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;

	case EFFECT_SPIRITMODE2:// ���Ǹ�(�������� ȿ��)
		{
			if( ch_from )
			{
				ef_sort.nType = FX_SPIRITMODE2;
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
		}
		break;

	case EFFECT_SKILL_STONEBASH: ///�����޺�
		{
			ef_sort.nType = FX_HELLCRY;
			ef_sort.subNum = 1; // ���� �转���� ǥ���� �ش�.

			// ���̺긮�� ����转�� ����Ʈ. Į���κ��� �����Ѵ�.
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_HELL], x, y, z);
				}
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_HELL], x, y, z);
				}
			}
			else
				return;
		}
		break;

	case EFFECT_SKILL_BASHREFLECTION: ///�����޺�
		{
			ef_sort.nType = FX_SUMMONRING; // ��ȯ�� �� ����Ʈ�ε� ���̺긮�� �н� �޺��ε� �������.
			ef_sort.num = EFFECT_SKILL_BASHREFLECTION;

			if( ch_from ) // from�� �ݵ�� �ʿ��ϴ�.
			{
				ef_sort.pNkChaFrom = ch_from;

				float move_X = 0.0f,move_Z = 0.0f;

				move_X = RandomNum( -20.0f, 20.0f );

				if( move_X < 0.0f && move_X > -10.0f )
					move_X = -10.0f;
				if( move_X > 0.0f && move_X < 10.0f )
					move_X = 10.0f;

				move_Z = RandomNum( -20.0f, 20.0f );
				if( move_Z < 0.0f && move_Z > -10.0f )
					move_Z = -10.0f;
				if( move_Z > 0.0f && move_Z < 10.0f )
					move_Z = 10.0f;

				ef_sort.dwColor = timeGetTime();
				if (ch_to)
				{
					ef_sort.pNkChaTo = ch_to;
					ef_sort.vPos = D3DVECTOR(ch_to->m_wx+move_X, ch_to->m_wy, ch_to->m_wz+move_Z); // �ణ ���� ������ �Ű�����Ѵ�.
					ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz); // �ణ ���� ������ �Ű�����Ѵ�.
					ef_sort.vSortPos.z = (float) atan2( ef_sort.vTargetPos.z-ef_sort.vPos.z, ef_sort.vTargetPos.x-ef_sort.vPos.x ); // ȸ�������� ���.
					ef_sort.Index = 1; // ���� phase �ʱ�ȭ.
					ef_sort.subNum = 0; // �ʱ�ȭ.

					//				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort)); // ����ڿ� �ͼӽ�Ŵ�� ���� // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				}
				else if (mob_to)
				{
					ef_sort.pMobTo = mob_to;
					ef_sort.vPos = D3DVECTOR(mob_to->m_wx+move_X, mob_to->m_wy, mob_to->m_wz+move_Z); // �ణ ���� ������ �Ű�����Ѵ�.
					ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz); // �ణ ���� ������ �Ű�����Ѵ�.
					ef_sort.vSortPos.z = (float) atan2( ef_sort.vTargetPos.z-ef_sort.vPos.z, ef_sort.vTargetPos.x-ef_sort.vPos.x ); // ȸ�������� ���.
					ef_sort.Index = 1; // ���� phase �ʱ�ȭ.
					ef_sort.subNum = 0; // �ʱ�ȭ.

					//				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort)); // ����ڿ� �ͼӽ�Ŵ�� ���� // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				}
				else
					return;

				// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				ch_from->InsertEffectNum( nEffInserNum );
				if( ch_to )
					ch_to->InsertEffectNum( nEffInserNum );
				if( mob_to )
					mob_to->InsertEffectNum( nEffInserNum );
			}
		}
		break;
	case EFFECT_SPACE_SLASH:
		{
			ef_sort.nType = FX_SPACESLASH;

			if (ch_from)		// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
			}
			else
				return;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}
		break;
	case EFFECT_ELECTRIC_HAMMER:
		{
			ef_sort.nType = FX_ELECTRICHAMMER;
			if (ch_from)		// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
			}
			else
				return;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_SKILL_SUMMONFIRE:
		{
			ef_sort.nType = FX_SUMMONFIRE;
			if (ch_from)		// ������ ��.
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
			}
			else
				return;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_SKILL_MERCERNERYSLASH:
		{
			if( ch_from )
			{
				ef_sort.nType = FX_MERCERNERYSLASH;
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	case EFFECT_SKILL_RANDOMFIRE:
		{
			if( ch_from )
			{
				ef_sort.nType = FX_RANDOMFIRE;
				ef_sort.num = ch_from->m_nSkillLevel;
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	case EFFECT_SKILL_ICEBOLT:
		{
			ef_sort.nType = FX_ICEBLOT;
			if (ch_from)
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
			}
			else
				return;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}

		break;

	case EFFECT_SKILL_WILDSMASH:
		{
			ef_sort.nType = FX_WILDSMASH;
			if (ch_from)
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
			}
			else
				return;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}

		break;
	case EFFECT_SKILL_TORNADO_HAMMER:
		{
			ef_sort.nType = FX_TORNADO_HAMMER;
			if (ch_from)
			{
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
				ch_from->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}

		break;
	case EFFECT_LIP_PARTICLE : // 2007.03.14 ȭ��Ʈ
	case EFFECT_HEART_PARTICLE: ///��Ʈ�ε�
		{

			ef_sort.nType = FX_TYPE_PARTICLE;
			if(skill_idx == EFFECT_LIP_PARTICLE)
			{
				ef_sort.Index = FX_PARTICLE_TYPE_LIP;
			}
			else
				ef_sort.Index = FX_PARTICLE_TYPE_HEARTLORD;

			ef_sort.num = MAX_PARTICLE_FOR_HEARTLOAD; // ��ƼŬ ����.

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
			}
			else
				return;

			// ��ƼŬ ����
			Deco_Particle *ParticleInfoArray;
			ParticleInfoArray = new Deco_Particle[MAX_PARTICLE_FOR_HEARTLOAD];
			ZeroMemory( ParticleInfoArray, sizeof(Deco_Particle)*MAX_PARTICLE_FOR_HEARTLOAD );
			for( i = 0 ; i < MAX_PARTICLE_FOR_HEARTLOAD ; ++i )
			{
				ParticleInfoArray[i].first_Pos.x = ef_sort.vTargetPos.x + RandomNum(-2.0f,2.0f);
				ParticleInfoArray[i].first_Pos.y = ef_sort.vTargetPos.y + RandomNum(10.0f,20.0f);
				ParticleInfoArray[i].first_Pos.z = ef_sort.vTargetPos.z + RandomNum(-2.0f,2.0f);
				ParticleInfoArray[i].cur_Pos = ParticleInfoArray[i].first_Pos; // �ʱ�ȭ
				ParticleInfoArray[i].start_time = timeGetTime() - (int)RandomNum( -500.0f,0.0f ); // �ణ �ʰ� �����Ǵ� �༮�� ���̵���.
				ParticleInfoArray[i].cur_time = ParticleInfoArray[i].start_time;
				ParticleInfoArray[i].life_time = (int)RandomNum( 1000.0f,2000.0f );
				ParticleInfoArray[i].gravity = D3DVECTOR( RandomNum(-1.0f,1.0f),RandomNum(-1.0f,1.0f),RandomNum(-1.0f,1.0f) ); // ���� ���⵵ �����ϰ�
				Normalize( ParticleInfoArray[i].gravity );
				ParticleInfoArray[i].direction = D3DVECTOR( RandomNum(0.002f,0.01f),0.0f,0.0f ); // �ӵ������� ���. ( �̵� �ӵ�, ??, ȸ���� ȸ����(���⼱ �ʱ�ȭ) )

				if( rand()%2 )
				{
					ParticleInfoArray[i].red = 1.0f;
					ParticleInfoArray[i].blue = 1.0f;
					ParticleInfoArray[i].green = 1.0f;
				}
				else
				{
					ParticleInfoArray[i].red = 0.9f;
					ParticleInfoArray[i].blue = 0.4f;
					ParticleInfoArray[i].green = 0.4f;
				}
				ParticleInfoArray[i].fade = 100.0f;
				ParticleInfoArray[i].scale = RandomNum( 0.7f,2.0f );
				ParticleInfoArray[i].texFrame = rand()%3; // ����� 3���� ������ Ÿ������... // �̰� ������ Ÿ������ ��(�� ����Ʈ�� �ؽ��� �ִϸ��̼��� �Ⱦ��Ƿ�...)
				//			ParticleInfoArray[i].texFrame = 0; // �ΰ��� �����̴� Ÿ���� �־������ �길�ϱ⸸ �ϰ� �� �̻ڴ���. �׳� ������ ���������Ը� �ص�.
			}

			ef_sort.effects = ParticleInfoArray; // �� ����Ʈ ���� ��ƼŬ �޸��ּҸ� ���.


			if (ch_to)  	// �´� ��.
			{
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			}
			else if (mob_to)
			{
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			}
			else
				return;
		}

		break;

	case EFFECT_LOVE_PARTICLE : // 2007.03.14 ȭ��Ʈ
		{
			ef_sort.nType = FX_TYPE_PARTICLE;
			ef_sort.num = MAX_PARTICLE_FOR_HEARTLOAD; // ��ƼŬ ����.

			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
			}
			else
				return;

			// ��ƼŬ ����
			Deco_Particle *ParticleInfoArray[4];

			for(int j = 0; j < 4; j++)
			{
				ef_sort.Index = FX_PARTICLE_TYPE_L + j;
				ParticleInfoArray[j] = new Deco_Particle[MAX_PARTICLE_FOR_HEARTLOAD];
				ZeroMemory( ParticleInfoArray[j], sizeof(Deco_Particle)*MAX_PARTICLE_FOR_HEARTLOAD );

				for( i = 0 ; i < MAX_PARTICLE_FOR_HEARTLOAD ; ++i )
				{
					ParticleInfoArray[j][i].first_Pos.x = ef_sort.vTargetPos.x + RandomNum(-2.0f,2.0f);
					ParticleInfoArray[j][i].first_Pos.y = ef_sort.vTargetPos.y + RandomNum(10.0f,20.0f);
					ParticleInfoArray[j][i].first_Pos.z = ef_sort.vTargetPos.z + RandomNum(-2.0f,2.0f);
					ParticleInfoArray[j][i].cur_Pos = ParticleInfoArray[j][i].first_Pos; // �ʱ�ȭ
					ParticleInfoArray[j][i].start_time = timeGetTime() - (int)RandomNum( -500.0f,0.0f ); // �ణ �ʰ� �����Ǵ� �༮�� ���̵���.
					ParticleInfoArray[j][i].cur_time = ParticleInfoArray[j][i].start_time;
					ParticleInfoArray[j][i].life_time = (int)RandomNum( 1000.0f,2000.0f );
					ParticleInfoArray[j][i].gravity = D3DVECTOR( RandomNum(-1.0f,1.0f),RandomNum(-1.0f,1.0f),RandomNum(-1.0f,1.0f) ); // ���� ���⵵ �����ϰ�
					Normalize( ParticleInfoArray[j][i].gravity );
					ParticleInfoArray[j][i].direction = D3DVECTOR( RandomNum(0.002f,0.01f),0.0f,0.0f ); // �ӵ������� ���. ( �̵� �ӵ�, ??, ȸ���� ȸ����(���⼱ �ʱ�ȭ) )

					if( rand()%2 )
					{
						ParticleInfoArray[j][i].red = 1.0f;
						ParticleInfoArray[j][i].blue = 1.0f;
						ParticleInfoArray[j][i].green = 1.0f;
					}
					else
					{
						ParticleInfoArray[j][i].red = 0.9f;
						ParticleInfoArray[j][i].blue = 0.4f;
						ParticleInfoArray[j][i].green = 0.4f;
					}
					ParticleInfoArray[j][i].fade = 100.0f;
					ParticleInfoArray[j][i].scale = RandomNum( 0.7f,2.0f );
					ParticleInfoArray[j][i].texFrame = rand()%3; // ����� 3���� ������ Ÿ������... // �̰� ������ Ÿ������ ��(�� ����Ʈ�� �ؽ��� �ִϸ��̼��� �Ⱦ��Ƿ�...)
				}

				ef_sort.effects = ParticleInfoArray[j]; // �� ����Ʈ ���� ��ƼŬ �޸��ּҸ� ���.

				if (ch_to)  	// �´� ��.
				{
					pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				}
				else if (mob_to)
				{
					pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				}
				else
					return;
			}
		}
		break;

	case EFFECT_PIG_HEALING: // ����
		{

			ef_sort.nType = FX_TYPE_PARTICLE;
			ef_sort.Index = FX_PARTICLE_TYPE_LUCKYPIG; // �Ϻ� �߷�Ÿ�ε��� ������ ��Ʈ�ε�,���귯��ε� �� ����Ʈ. ��Ʈ���� �ȶ� �ȶ�~
			ef_sort.num = MAX_PARTICLE_FOR_LUCKYPIG; // ��ƼŬ ����.(�׳� ��Ʈ�ε�� ���� ���)

			if (ch_to) // �´� ��
			{
				ef_sort.pNkChaTo = ch_to; // �� �༮�� ��ǥ�� ���.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			}
			else
				return;


			// ��ƼŬ ����
			{
				Deco_Particle *ParticleInfoArray;
				ParticleInfoArray = new Deco_Particle[MAX_PARTICLE_FOR_LUCKYPIG];
				ZeroMemory( ParticleInfoArray, sizeof(Deco_Particle)*MAX_PARTICLE_FOR_LUCKYPIG );
				for( i = 0 ; i < MAX_PARTICLE_FOR_LUCKYPIG ; ++i )
				{
					ParticleInfoArray[i].first_Pos.x = RandomNum(-5.0f,5.0f); // Ÿ�ٿ����� �����ǥ�ӿ� ����
					ParticleInfoArray[i].first_Pos.y = 30.0f;//RandomNum(10.0f,30.0f);
					ParticleInfoArray[i].first_Pos.z = RandomNum(-5.0f,5.0f);
					ParticleInfoArray[i].cur_Pos = ParticleInfoArray[i].first_Pos; // �ʱ�ȭ
					ParticleInfoArray[i].start_time = timeGetTime() - (int)RandomNum( -1500.0f,-1000.0f ); // �ణ �ʰ� �����Ǵ� �༮�� ���̵���.
					ParticleInfoArray[i].cur_time = ParticleInfoArray[i].start_time;
					ParticleInfoArray[i].life_time = (int)RandomNum( 1000.0f,2000.0f );
					ParticleInfoArray[i].gravity = D3DVECTOR( RandomNum(-1.0f,1.0f),RandomNum(-10.0f,-15.0f), RandomNum(-1.0f,1.0f) ); // ���� ���⵵ �����ϰ�
					Normalize( ParticleInfoArray[i].gravity );
					ParticleInfoArray[i].direction = D3DVECTOR( RandomNum(0.002f,0.01f),0.0f,0.0f ); // �ӵ������� ���. ( �̵� �ӵ�, ??, ȸ���� ȸ����(���⼱ �ʱ�ȭ) )

					ParticleInfoArray[i].red = RandomNum(0.0f,1.0f);
					ParticleInfoArray[i].blue = RandomNum(0.0f,1.0f);
					ParticleInfoArray[i].green = RandomNum(0.0f,1.0f);

					ParticleInfoArray[i].fade = 70.0f;
					ParticleInfoArray[i].scale = RandomNum( 0.3f,0.7f );
				}

				ef_sort.effects = ParticleInfoArray; // �� ����Ʈ ���� ��ƼŬ �޸��ּҸ� ���.
			}

			if (ch_to)  	// �´� ��.
			{
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort)); // �� �༮�� ��ǥ�� ���.
			}
			else
				return;

		}

		break;

	case EFFECT_SONGKRAN_WTRSPRINKLE:  // [3/27/2007 Theodoric] �±� ��ũ�� �̺�Ʈ

		{
			ef_sort.nType = FX_WTRSPRINKLE;

			if (ch_to)
			{
				ef_sort.pNkChaFrom = ch_from;
				ef_sort.pNkChaTo = ch_to;

				if (ch_from)
				{
					// ������ ��.
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}

				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);

				ef_sort.pNkChaFrom = ch_from;
				ef_sort.pMobTo = mob_to;

				//x = mob_to->m_wx; y = mob_to->m_wy; z = mob_to->m_wz;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
					//ch_from->Magic(x, y, z, CHA_MAGIC_SOFT);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
					//mob_from->Magic(x, z);
				}
				else
				{
					return;
				}

				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}
		break;

	case EFFECT_MURAMASA_GHOST: ///�Ϻ����������׽�Ʈ ������ ���󸶻� �� �ͽ� ����Ʈ.
		{

			ef_sort.nType = FX_MURAMASA_GHOST;
			ef_sort.Index = 0; // Ȥ�� �ٸ����̼��� ���� ��츦 ����ؼ�...

			if( ch_from ) // ������ ��
			{
				ef_sort.pNkChaFrom = ch_from; // �� �༮�� ��ǥ�� ���.
				//			ef_sort.vCurPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
			}
			else
				return;

			// �´� ��.
			if( ch_to )
			{
				ef_sort.pNkChaTo = ch_to; // �� �༮�� ��ǥ�� ���.
				//			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			}
			else if( mob_to )
			{
				ef_sort.pMobTo = mob_to; // �� �༮�� ��ǥ�� ���.
				//			ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
			}
			else
				return;

			ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.
			ef_sort.num = 0; // ���� ������ ���.

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}

		break;

	case EFFECT_BOSSRAID_BULKAN1_02:
		{

			ef_sort.nType		= FX_BOSSRAID_BULKAN1_02;
			ef_sort.pMobFrom	= mob_from;		// ������ ��
			ef_sort.pNkChaTo	= ch_to;		// �´� �� (����Ʈ�� ���ư��� ���� (���� �����̴�.)

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}

		break;

	case EFFECT_BOSSRAID_BULKAN1_03:
		{

			ef_sort.nType		= FX_BOSSRAID_BULKAN1_03;
			ef_sort.pMobFrom	= mob_from;
			ef_sort.pNkChaTo	= ch_to;

			if(mob_from)
				mob_from->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );
		}
		break;

	case EFFECT_BOSSRAID_BULKAN2_02:
		{
			if (mob_from)
			{
				Deco_Particle *ParticleInfoArray;
				ParticleInfoArray = new Deco_Particle[FX_BOSSRAID_BULKAN2_02_MAX_SWORD];
				ZeroMemory(ParticleInfoArray, FX_BOSSRAID_BULKAN2_02_MAX_SWORD * sizeof(Deco_Particle));
				for(int i = 0; i < FX_BOSSRAID_BULKAN2_02_MAX_SWORD; ++i)
				{
					ParticleInfoArray[i].cur_Pos = D3DVECTOR(-150 + rand()%301, 100, -150 + rand()%301);
				}

				ef_sort.nType = FX_BOSSRAID_BULKAN2_02;
				ef_sort.Index = 0;
				ef_sort.pMobFrom = mob_from;
				ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pParticle = ParticleInfoArray;
				ef_sort.dwColor = 0;

				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
			}
		}
		break;

	case EFFECT_BOSSRAID_BULKAN3_01:
		{
			ef_sort.nType = FX_BOSSRAID_BULKAN3_01;
			ef_sort.Index = EFFECT_BOSSRAID_BULKAN3_01;
			if(g_pRoh == ch_to)
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}
		break;

	case EFFECT_BOSSRAID_BULKAN3_02:
		{
			ef_sort.nType = FX_BOSSRAID_BULKAN3_02;
			if (ch_to)  	// �´� ��.
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
				{
					return;
				}
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - ch_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - ch_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - ch_to->m_wz) / g_fDSDistance;
					g_pDSound->Play(g_EffectSound[EFF_SND_TONADO], x, y, z);
				}
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
					return;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				if (g_pDSound)
				{
					float x, y, z;
					x = (ef_sort.vPos.x - mob_to->m_wx) / g_fDSDistance;
					y = (ef_sort.vPos.y - mob_to->m_wy) / g_fDSDistance;
					z = (ef_sort.vPos.z - mob_to->m_wz) / g_fDSDistance;

					g_pDSound->Play(g_EffectSound[EFF_SND_TONADO], x, y, z);
				}
			}
		}
		break;

	case EFFECT_BOSSRAID_HUMAN1_02:
		{

			ef_sort.nType		= FX_BOSSRAID_HUMAN1_02;
			ef_sort.pMobFrom	= mob_from;
			ef_sort.pNkChaTo	= ch_to;

			if(mob_from)
				mob_from->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );
		}
		break;

	case EFFECT_BOSSRAID_HUMAN1_03:
		{
			ef_sort.nType		= FX_BOSSRAID_HUMAN1_03;
			ef_sort.pMobFrom	= mob_from;
			ef_sort.pNkChaTo	= ch_to;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if(mob_from)
				mob_from->InsertEffectNum( nEffInserNum );

			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}

		break;

	case EFFECT_BOSSRAID_HUMAN2_02:
		{
			if (mob_from)
			{
				ef_sort.nType = FX_BOSSRAID_HUMAN2_02;
				ef_sort.Index = 0;
				ef_sort.pMobFrom = mob_from;
				ef_sort.pNkChaTo = ch_to;
				ef_sort.dwColor = timeGetTime();
				ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
			}
		}
		break;

	case EFFECT_BOSSRAID_HUMAN2_03:
		{
			if (mob_from)
			{
				Deco_Particle *ParticleInfoArray;
				ParticleInfoArray = new Deco_Particle[FX_BOSSRAID_HUMAN2_03_MAX_LASER];
				ZeroMemory(ParticleInfoArray, FX_BOSSRAID_HUMAN2_03_MAX_LASER * sizeof(Deco_Particle));
				for(int i = 0; i < FX_BOSSRAID_HUMAN2_03_MAX_LASER; ++i)
				{
					ParticleInfoArray[i].texFrame = 0;
					ParticleInfoArray[i].start_time = 0;
					ParticleInfoArray[i].cur_Pos = D3DVECTOR( 0, 0, 0);
					ParticleInfoArray[i].first_Pos = D3DVECTOR( 0, 0, 0);
				}

				ef_sort.nType = FX_BOSSRAID_HUMAN2_03;
				ef_sort.Index = 0;
				ef_sort.pMobFrom = mob_from;
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.vPos.x = ch_to->m_wx - mob_from->m_wx;
				ef_sort.vPos.z = ch_to->m_wz - mob_from->m_wz;
				ef_sort.vPos.y = 0;

				//Divided By Zero ����
				if (ef_sort.vPos.x == 0 && ef_sort.vPos.z)
				{
					ef_sort.vPos.x = 1;
					ef_sort.vPos.z = 0;
				}

				ef_sort.vPos = Normalize( ef_sort.vPos ) * 120.0f;
				ef_sort.vPos.x += mob_from->m_wx;
				ef_sort.vPos.z += mob_from->m_wz;
				ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight(ef_sort.vPos.x, ef_sort.vPos.z);
				ef_sort.pParticle = ParticleInfoArray;

				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
				mob_from->InsertEffectNum( nEffInserNum );
			}
		}
		break;

	case EFFECT_BOSSRAID_HUMAN3_02:				// [12/25/2007 �����] �������̵� �޸պ���3-02 ��ų
		{
			ef_sort.nType = FX_BOSSRAID_HUMAN3_02;
			ef_sort.Index = EFFECT_BOSSRAID_HUMAN3_02;
			ef_sort.pMobFrom = mob_from;

			if(g_pRoh == ch_to)
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}
		break;

	case EFFECT_BOSSRAID_HYBRI1_01:
		{
			ef_sort.nType = FX_BOSSRAID_HYBRI1_01;
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.dwColor = timeGetTime();
			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}
		break;

	case EFFECT_BOSSRAID_HYBRI1_02:
		{
			ef_sort.nType = FX_BOSSRAID_HYBRI1_02;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_HYBRI2_02:
		{
			ef_sort.nType = FX_BOSSRAID_HYBRI2_02;
			ef_sort.Index = EFFECT_BOSSRAID_HYBRI2_02;
			ef_sort.pMobFrom = mob_from;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_HYBRI3_01:				// [1/16/2008 �����] �������̵� ���̺긮������3-01 ��� ����
		{
			ef_sort.nType = FX_BOSSRAID_HYBRI3_01;
			ef_sort.Index = EFFECT_BOSSRAID_HYBRI3_01;
			ef_sort.pMobFrom = mob_from;

			if(g_pRoh == ch_to)
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}
		break;

	case EFFECT_BOSSRAID_HYBRI3_02:				// [01/17/2008 �����] �������̵� ���̺긮������3, 2�� ��ų
		{
			ef_sort.nType = FX_BOSSRAID_HYBRI3_02;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;
	case EFFECT_BOSSRAID_KAI1_01:
		{
			ef_sort.nType = FX_BOSSRAID_KAI1_01;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_KAI1_02:
		{
			ef_sort.nType = FX_BOSSRAID_KAI1_02;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_KAI2_01:				// [2/5/2008 �����] ī�̸��溸��2 1 ����
		{
			ef_sort.nType = FX_BOSSRAID_KAI2_01;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_KAI2_02:				// [2/5/2008 �����] ī�̸��溸��2 2 ����
		{
			ef_sort.nType = FX_BOSSRAID_KAI2_02;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_KAI2_03:				// [2/5/2008 �����] ī�̸��溸��2 2 ����
		{
			ef_sort.nType = FX_BOSSRAID_KAI2_03;
			if( mob_from )
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pMobFrom = mob_from;
				ef_sort.pNkChaTo = ch_to;

				nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

				mob_from->InsertEffectNum( nEffInserNum );
			}
		}
		break;

	case EFFECT_BOSSRAID_KAI3_01:				// [2/4/2008 �����] ī�̸��溸��3 ��� ����
		{
			ef_sort.nType = FX_BOSSRAID_KAI3_01;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_KAI3_02:				// [2/4/2008 �����] ī�̸��溸��3 2����ų
		{
			ef_sort.nType = FX_BOSSRAID_KAI3_02;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_KAI3_03:				// [2/11/2008 �����] ī�̸��溸��3 3����ų
		{
			ef_sort.nType = FX_BOSSRAID_KAI3_03;
			ef_sort.Index = EFFECT_BOSSRAID_KAI3_03;
			ef_sort.pMobFrom = mob_from;

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}
		break;

	case EFFECT_BOSSRAID_AIDIA1_01:				// ���̵�� 1_01 �븻 ����
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA1_01;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );

			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;



	case EFFECT_BOSSRAID_AIDIA1_02:				// ���̵�� 1_01 �븻 ����
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA1_02;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_AIDIA2_01:
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA2_01;
			ef_sort.Index = 1;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
			ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_AIDIA2_02:
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA2_02;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
			ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_AIDIA2_03:
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA2_03;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			Deco_Particle *ParticleInfoArray;
			ParticleInfoArray = new Deco_Particle[FX_BOSSRAID_ADIA2_03_MAX_PARTICLE];
			ZeroMemory(ParticleInfoArray, FX_BOSSRAID_ADIA2_03_MAX_PARTICLE * sizeof(Deco_Particle));
			for(int i = 0; i < FX_BOSSRAID_ADIA2_03_MAX_PARTICLE; ++i)
			{
				ParticleInfoArray[i].cur_Pos = D3DVECTOR(-100 + rand()%151, 0, -100 + rand()%151);
			}
			ef_sort.pParticle = ParticleInfoArray;
			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_AIDIA3_01:				// [3/6/2008 �����] ���̵�ƺ���3 ��� ����
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA3_01;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_AIDIA3_02:				// [3/6/2008 �����] ���̵�ƺ���3 2�� ��ų
		{
			ef_sort.nType = FX_BOSSRAID_AIDIA3_02;
			if (mob_from)
			{
				ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				ef_sort.pMobFrom = mob_from;
			}
			else
				return;

			if (ch_to)
			{
				// �´� ��.
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
		}
		break;


	case EFFECT_BOSSRAID_LASTBOSS_02:
		{
			ef_sort.nType		= FX_BOSSRAID_LASTBOSS_02;
			ef_sort.Index		= 0;
			ef_sort.pMobFrom	= mob_from;
			ef_sort.pNkChaTo	= ch_to;
			ef_sort.dwColor		= timeGetTime();
			ef_sort.vCurPos		= D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos	= D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);

			Deco_Particle *ParticleInfoArray;
			ParticleInfoArray = new Deco_Particle[FX_BOSSRAID_LASTBOSS_02_MAX_PARTICLE];
			ZeroMemory(ParticleInfoArray, FX_BOSSRAID_LASTBOSS_02_MAX_PARTICLE * sizeof(Deco_Particle));
			for(int i = 0; i < FX_BOSSRAID_LASTBOSS_02_MAX_PARTICLE; ++i)
			{
				ParticleInfoArray[i].cur_Pos = D3DVECTOR(-150 + rand()%301, 0, -150 + rand()%301);
				ParticleInfoArray[i].cur_time = -1;
			}
			ef_sort.pParticle = ParticleInfoArray;
			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_LASTBOSS_03:
		{
			ef_sort.nType = FX_BOSSRAID_LASTBOSS_03;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			ef_sort.pParticle = pCMyApp->m_pFxSet->m_pFxBossRaidLastBoss_03->MakeParticle(mob_from->m_dir);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	case EFFECT_BOSSRAID_LASTBOSS_04:
		{
			ef_sort.nType = FX_BOSSRAID_LASTBOSS_04;
			ef_sort.Index = 0;
			ef_sort.pMobFrom = mob_from;
			ef_sort.pNkChaTo = ch_to;
			ef_sort.dwColor = timeGetTime();
			ef_sort.vCurPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
			ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
			ef_sort.pParticle =  pCMyApp->m_pFxSet->m_pFxBossRaidLastBoss_04->MakeParticle(mob_from->m_dir);

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			mob_from->InsertEffectNum( nEffInserNum );
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case EFFECT_HEROEFFECT:
		{
			ef_sort.nType		= FX_HERO_EFFECT;
			ef_sort.num			= 0;
			ef_sort.nCurFrame	= 0;
			ef_sort.pNkChaTo	= ch_to;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			ch_to->InsertEffectNum( nEffInserNum );
		}
		break;
	case EFFECT_SKILL_RING_SARNGA:	// [12/3/2008 Theodoric] �縪��
	case EFFECT_SKILL_RING_SARNGA2: // [12/3/2008 Theodoric] ���� �縪��
		{
			ef_sort.nType = FX_SARNGA_MOUEL;

			if( skill_idx == EFFECT_SKILL_RING_SARNGA2 ) // [12/3/2008 Theodoric] ���� �縪��(����������)
				ef_sort.num = 1;
			else
				ef_sort.num = 0;

			if(ch_from)
				ef_sort.vCurPos.x = ch_from->m_dir;
			if(mob_from)
				ef_sort.vCurPos.x = mob_from->m_dir;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	case EFFECT_SKILL_RING_GRIFFON: // [12/3/2008 Theodoric] ���� �縪��
		{
			ef_sort.nType = FX_GRIFFON_RING;

			ef_sort.num = 0;

			if(ch_from)
				ef_sort.vCurPos.x = ch_from->m_dir;
			if(mob_from)
				ef_sort.vCurPos.x = mob_from->m_dir;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ef_sort.vPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if (mob_to)
			{
				ef_sort.pMobTo = mob_to;
				ef_sort.vPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
				return;
		}
		break;
	case EFFECT_PEROM_SKILL_S125:
		{
//			ef_sort.nType = FX_PEROM_SKILL_S125;
		}
		break;
	case EFFECT_PEROM_SKILL_S126:
		{
//			ef_sort.nType = FX_PEROM_SKILL_S126;
		}
		break;

	case EFFECT_PEROM_SKILL_S127:
	case EFFECT_PEROM_SKILL_S128:
	case EFFECT_PEROM_SKILL_S129:
	case EFFECT_PEROM_SKILL_S130:
	case EFFECT_PEROM_SKILL_S131:
	case EFFECT_PEROM_SKILL_S132:
	case EFFECT_PEROM_SKILL_S133:
	case EFFECT_PEROM_SKILL_S134:
	case EFFECT_PEROM_SKILL_S135:
	case EFFECT_PEROM_SKILL_S136:
	case EFFECT_PEROM_SKILL_S137:
	case EFFECT_PEROM_SKILL_S138:
	case EFFECT_PEROM_SKILL_S140:
		{
			ef_sort.nType = (skill_idx-EFFECT_PEROM_SKILL_S125)+ FX_PEROM_SKILL_S125;

			if (ch_from)
			{
				ef_sort.nCurFrame = 5;
				ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				ef_sort.pNkChaFrom = ch_from;
			}
			else
				return;

			if (ch_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(ch_to->m_wx, ch_to->m_wy, ch_to->m_wz);
				ef_sort.pNkChaTo = ch_to;
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
			}
			else
				return;

			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );

		}
		break;
	case EFFECT_PEROM_OPTIONSKILL_S134:
	case EFFECT_PEROM_OPTIONSKILL_S148:
	case EFFECT_PEROM_OPTIONSKILL_S149:
	case EFFECT_PEROM_OPTIONSKILL_S150:
		{
			ef_sort.nType = FX_OPTIONSKILLEFFECTS;

			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else if(mob_to)
			{
				ef_sort.pMobTo = mob_to;
				mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
			}
			else
			{
				return;
			}
		}

// 	case EFFECT_PEROM_SKILL_S140:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S140;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S141:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S141;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S142:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S142;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S143:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S143;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S144:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S144;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S145:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S145;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S146:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S146;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S147:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S147;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S148:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S148;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S149:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S149;
// 		}
// 		break;
// 	case EFFECT_PEROM_SKILL_S150:
// 		{
// 			ef_sort.nType = FX_PEROM_SKILL_S150;
// 		}
// 		break;

	default:
		{
			ef_sort.nType = FX_CHAKRAM;
			ef_sort.subNum = skill_idx - 2000;
			ef_sort.pNkChaFrom = ch_from;
			ef_sort.pMobFrom = mob_from;
			if (ch_to)
			{
				ef_sort.pNkChaTo = ch_to;
				if (ch_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)  	// ������ ��.
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
					return;
				//			ch_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort)); // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else if (mob_to)
			{
				ef_sort.vTargetPos = D3DVECTOR(mob_to->m_wx, mob_to->m_wy, mob_to->m_wz);
				ef_sort.pMobTo = mob_to;
				if (ch_from)
				{
					ef_sort.vPos = D3DVECTOR(ch_from->m_wx, ch_from->m_wy, ch_from->m_wz);
				}
				else if (mob_from)
				{
					ef_sort.vPos = D3DVECTOR(mob_from->m_wx, mob_from->m_wy, mob_from->m_wz);
				}
				else
					return;
				//			mob_to->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort)); // 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			}
			else
				return;

			// 07-03-26 ���� . ����Ʈ ƨ�� ���� ����
			nEffInserNum = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			if( ch_from )
				ch_from->InsertEffectNum( nEffInserNum );
			if( mob_from )
				mob_from->InsertEffectNum( nEffInserNum );
			if( ch_to )
				ch_to->InsertEffectNum( nEffInserNum );
			if( mob_to )
				mob_to->InsertEffectNum( nEffInserNum );
		}
		break;
	}
}

#define ABS(a)	((a) >= 0 ? (a) : (-(a)))
BOOL CUIMgr::IsNotBlocked(float x1, float z1, float x2, float z2, BOOL bIgnore)
{
	if (bIgnore)
		return TRUE;

	float x_diff = x1 - x2;
	float z_diff = z1 - z2;
	// �ڽ��� �ִ� ��ġ�� ����� �Ǿ� �־ �ȵȴ�.
	if (!m_pLand->IsMovableArea(x1 , z1))
		return FALSE;

	if( pCMyApp->GetCurWorld() == WORLD_FIELD && DecardiBattleManager::GetInstance()->IsAttackable(x2, z2) == true )
		return TRUE;

	/////////////////////////////////////////////////////////////////
	// ������   : �̿���
	// ������   : 05-03-31
	// �������� : ��ī���� ������ ��ȣž ���ݰ���ó��(�Ӽ��� �ڵ����� ����� ������ ���༮���� �߰��� �Ӽ� ó���� ������� ����.) //DEC_TOWER
	if( pCMyApp->GetCurWorld() == 0 && m_bOnBattle )
	{
		for( int i = 0 ; i < DECWAR_LAND_ATT_COUNT ; i ++ )
		{
			if( i == 0 || i == 2 || i == 4 || i == 6 ) // 0 2 4 6 �� �������� �������� ������Ʈ�� �Ӽ� ó���� ��.( by ���� )
			{
				continue;
			}

			if (x2 > g_fDecardi_Protect_Tower_Left_X[i] - 5.0f && x2 < g_fDecardi_Protect_Tower_Right_X[i] + 5.0f &&
					z2 > g_fDecardi_Protect_Tower_Bottom_Z[i] - 5.0f && z2 < g_fDecardi_Protect_Tower_Top_Z[i] + 5.0f)
			{
				return TRUE;
			}
		}
	}
	/////////////////////////////////////////////////////////////////

	// ȭ��Ʈȥ ������ �߿��� �ܼ� ���ݽ� ��ϵ��� �ʾҴٰ� ���ش�. ��.��
	if (pCMyApp->GetCurWorld() == WORLD_WHITEHORN && m_bOnBattle)
	{
		for (int i = 0; i < 8; i++)
		{
			if (x2 > g_OutsideDoorX[i] - 5.0f && x2 < g_OutsideDoorX[i] + 5.0f &&
					z2 > g_OutsideDoorZ[i] - 5.0f && z2 < g_OutsideDoorZ[i] + 5.0f)
			{
				return TRUE;
			}
		}
	}
//====================================================================
	// nate 2004 - 11
	// ���Ϸ� ��ȣž �Ӽ�üũ�������� ��? �����Ͼ� �ǰŵ�.
	if( pCMyApp->GetCurWorld() == WORLD_GUILD && m_bOnBattle )
	{
		for( int i = 0 ; i < 4 ; i ++ )
		{
			if( x2 > g_fGuardTowerX[ i ] - 6.0f && x2 < g_fGuardTowerX[ i ] + 6.0f &&
					z2 > g_fGuardTowerZ[ i ] - 6.0f && z2 < g_fGuardTowerZ[ i ] + 6.0f )
			{
				return TRUE;
			}
		}
	}
//====================================================================
//====================================================================
	// nate 2004 - 11
	// ���Ϸ� ��ȣž �Ӽ�üũ�������� ��? �����Ͼ� �ǰŵ�.
	if( pCMyApp->GetCurWorld() == WORLD_MATRIX )
	{
		for( int i = 0 ; i < 12 ; i ++ )
		{
			if( x2 > g_fGPStoneX[ i ] - 50.0f && x2 < g_fGPStoneX[ i ] + 50.0f &&
					z2 > g_fGPStoneZ[ i ] - 50.0f && z2 < g_fGPStoneZ[ i ] + 50.0f )
			{
				return TRUE;
			}
		}
	}
	if( pCMyApp->GetCurWorld() == WORLD_MATRIX_2009 ) // [2008/11/12 Theodoric] WORLD_MATRIX_2009
	{
		for( int i = 0 ; i < 10 ; i ++ )
		{
			if( x2 > g_fGPStone2009X1[ i ] && x2 < g_fGPStone2009X2[ i ] &&
					z2 > g_fGPStone2009Z1[ i ] && z2 < g_fGPStone2009Z2[ i ] )
			{
				return TRUE;
			}
		}
	}
//====================================================================
	if( pCMyApp->GetCurWorld() == WORLD_DUNGEON1 ) ///�δ�1
	{
		if( x2 > 6330.0f && x2 < 6400.0f && // 1�� ���� ����ó��.(�Ӽ��� ������ ĥ���� ���� npc�� �����ؾ��� ��� ����ó���� �ʿ��ϴ�.)
				z2 > 1720.0f && z2 < 1850.0f )
		{
			return TRUE;
		}
		if( x2 > 5616.0f && x2 < 5720.0f && // 2�� ���� ����ó��.(�Ӽ��� ������ ĥ���� ���� npc�� �����ؾ��� ��� ����ó���� �ʿ��ϴ�.)
				z2 > 8200.0f && z2 < 8245.0f )
		{
			return TRUE;
		}
		if( x2 > 4744.0f && x2 < 4785.0f && // 2�� ���� ����ó��.(�Ӽ��� ������ ĥ���� ���� npc�� �����ؾ��� ��� ����ó���� �ʿ��ϴ�.)
				z2 > 8715.0f && z2 < 8840.0f )
		{
			return TRUE;
		}
	}

	if( pCMyApp->GetCurWorld() == WORLD_DISPOSAL )
	{
		//189, 6212, 564, 5577
		if( x2 > 189.0f && x2 < 564.0f && // 2�� ���� ����ó��.(�Ӽ��� ������ ĥ���� ���� npc�� �����ؾ��� ��� ����ó���� �ʿ��ϴ�.)
			z2 > 5577.0f && z2 < 6212.0f )
		{
			return TRUE;
		}
	}

	// X ����  Z �ຸ�� ū ���...
	if (ABS(x_diff) > ABS(z_diff))
	{
		// x_diff �� ���� 0�̸� ��.. ���ڸ� �Ƴ�?
		if (ABS(x_diff) >= g_EPSILON)
		{
			if (x_diff > 0)
			{
				// X�� 10�� �����ϰ�.. Z�� ������ŭ ���� �����Ѵ�.
				float x_inc = 10.0f;
				float z_inc = 10.0f * z_diff / x_diff;
				for (int i = 0; x2 + (x_inc * i) < x1; i++)
				{
					//att = GetAttr(x + (x_inc * i), z + (z_inc * i));
					//if (att != 2 && att != 3)
					float	fX = x2 + x_inc * i;
					float	fZ = z2 + z_inc * i;
					if( !m_pLand->IsMovableArea( fX, fZ ) )
						return FALSE;
					if( g_bNewTerrain )
					{
						if( m_pLand->GetHFHeight( fX, fZ ) > CNKObjQuadNode::GetHeightOnObject( fZ, fX, 0.0f ) )
							if( m_pLand->GetHFHeight( fX, fZ ) < CNKObjQuadNode::GetHeightOnWater( fZ, fX ) )
								return FALSE;
					}
					else
					{
						if( m_pLand->GetHFHeight( fX, fZ ) < WATER_HEIGHT )
							return FALSE;
					}
				}
			}
			else
			{
				// X�� -10�� �����ϰ�.. Z�� ������ŭ ���� �����Ѵ�.
				float x_inc = -10.0f;
				float z_inc = 10.0f * z_diff / (-x_diff);
				for (int i = 0; x2 + (x_inc * i) > x1; i++)
				{
					//att = GetAttr(x + (x_inc * i), z + (z_inc * i));
					//if (att != 2 && att != 3)
					float	fX = x2 + x_inc * i;
					float	fZ = z2 + z_inc * i;
					if( !m_pLand->IsMovableArea( fX, fZ ) )
						return FALSE;
					if( g_bNewTerrain )
					{
						if( m_pLand->GetHFHeight( fX, fZ ) > CNKObjQuadNode::GetHeightOnObject( fZ, fX, 0.0f ) )
						{
							if( m_pLand->GetHFHeight( fX, fZ ) < CNKObjQuadNode::GetHeightOnWater( fZ, fX )
									&& pCMyApp->GetCurWorldID() != WORLD_BOSSRAID_BULKAN )
							{
								return FALSE;
							}
						}
					}
					else
					{
						if( m_pLand->GetHFHeight( fX, fZ ) < WATER_HEIGHT )
							return FALSE;
					}
				}
			}
		}
	}
	else
	{
		// z_diff �� ���� 0�̸� ��.. ����.. ���ڸ� �Ƴ�?
		if (ABS(z_diff) >= g_EPSILON)
		{
			if (z_diff > 0)
			{
				// Z�� 10�� �����ϰ�.. X�� ������ŭ ���� �����Ѵ�.
				float z_inc = 10.0f;
				float x_inc = 10.0f * x_diff / z_diff;
				for (int i = 0; z2 + (z_inc * i) < z1; i++)
				{
					//att = GetAttr(x + (x_inc * i), z + (z_inc * i));
					float	fX = x2 + x_inc * i;
					float	fZ = z2 + z_inc * i;
					if( !m_pLand->IsMovableArea( fX, fZ ) )
						return FALSE;
					if( g_bNewTerrain )
					{
						if( m_pLand->GetHFHeight( fX, fZ ) > CNKObjQuadNode::GetHeightOnObject( fZ, fX, 0.0f ) )
							if( m_pLand->GetHFHeight( fX, fZ ) < CNKObjQuadNode::GetHeightOnWater( fZ, fX )
									&& pCMyApp->GetCurWorldID() != WORLD_BOSSRAID_BULKAN )
								return FALSE;
					}
					else
					{
						if( m_pLand->GetHFHeight( fX, fZ ) < WATER_HEIGHT )
							return FALSE;
					}
				}
			}
			else
			{
				// Z�� -10�� �����ϰ�.. X�� ������ŭ ���� �����Ѵ�.
				float z_inc = -10.0f;
				float x_inc = 10.0f * x_diff / (-z_diff);
				for (int i = 0; z2 + (z_inc * i) > z1; i++)
				{
					//att = GetAttr(x + (x_inc * i), z + (z_inc * i));
					//if (att != 2 && att != 3)
					float	fX = x2 + x_inc * i;
					float	fZ = z2 + z_inc * i;
					if( !m_pLand->IsMovableArea( fX, fZ ) )
						return FALSE;
					if( g_bNewTerrain )
					{
						if( m_pLand->GetHFHeight( fX, fZ ) > CNKObjQuadNode::GetHeightOnObject( fZ, fX, 0.0f ) )
							if( m_pLand->GetHFHeight( fX, fZ ) < CNKObjQuadNode::GetHeightOnWater( fZ, fX )
									&& pCMyApp->GetCurWorldID() != WORLD_BOSSRAID_BULKAN )
								return FALSE;
					}
					else
					{
						if( m_pLand->GetHFHeight( fX, fZ ) < WATER_HEIGHT )
							return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

// -------------------------------------------------------------------
// Name : WhatColorOnPick()
// Desc : ��ŷ ���ۿ��� ������ �о�´�.
//        ���ϰ��� 0�̸� ���� �Ǵ� �ƹ��͵� �ƴ�.(������Ʈ�� ���ٴ� ��)
// -------------------------------------------------------------------
WORD CUIMgr::WhatColorOnPick(int x, int y)
{
	DDSURFACEDESC2 ddsd;
	D3DVIEWPORT7 vp;
	HRESULT hr;
	int half_x, half_y;			// ��ŷ ������ ������� ������ �������� 1/2�̴�.
	WORD inx = 0;		// 16bit Į�� ��.
	DWORD dwIdx = 0 ;
	BYTE R, G, B;

	// x,y �� ������ �Ǵ� ���� ��ǥ���� Ȯ��. - ���߿� ���� ����� ���ؼ� ���� �ʿ�.
	hr = GET_D3DDEVICE()->GetViewport( &vp );
	if (FAILED(hr))
		return 0;

	if ( x >= vp.dwWidth || y >= vp.dwHeight )
		return 0;

	// ��ŷ ���� ������� ���δ�.
	half_x = x >> 1;
	half_y = y >> 1;

	if (GET_DDSBPICK()->IsLost() == DDERR_SURFACELOST)
	{
		GET_DDSBPICK()->Restore();
		OutputDebugString("GET_DDSBPICK()->IsLost()\n");
		return 0;
	}

	// 16��Ʈ Į���� �������� ��ƾ�̴�.
	DWORD nResolution =  pCMyApp->GetCurResolution();

	ddsd.dwSize = sizeof(DDSURFACEDESC2);

	if( FAILED( GET_DDSBPICK()->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) ) )
		return 0;

	/*  ///��ŷ���׼��� �غ����� ����...
		if (nResolution == 16)
		{
	//		dwIdx = *((DWORD *)((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x<<2))));
	//		GET_DDSBPICK()->Unlock(NULL);

	//		GET_DDSBPICK()->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
			inx = *((WORD *)((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x<<1))));


			dwIdx = (WORD)inx;
		}
		else if (nResolution == 32)
	 		dwIdx = *((DWORD *)((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x<<2))));

		GET_DDSBPICK()->Unlock(NULL);

		if( dwIdx != 0 )
			int adf =345;

		return dwIdx;
	*/
	if (nResolution == 16)
	{
		inx = *((WORD *)((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x<<1))));
		GET_DDSBPICK()->Unlock(NULL);
	}
	else if (nResolution == 24)
	{
		B = *((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x*3)));
		G = *((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x*3) + 1));
		R = *((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x*3) + 2));
		GET_DDSBPICK()->Unlock(NULL);
		inx = g_ClrAlloc->ConvertRGB24ToWord(R, G, B);
	}
	else if (nResolution == 32)
	{
		dwIdx = *((DWORD *)((BYTE *)ddsd.lpSurface + (half_y * ddsd.lPitch + (half_x<<2))));
		GET_DDSBPICK()->Unlock(NULL);
		inx = g_ClrAlloc->ConvertDWordColorToWord(dwIdx);
	}

	/*
	FILE *fp = NULL;

	fp = fopen("hehe.raw", "wb");
	for (int i=0; i < 240; i++) {
		for (int j=0; j < 320; j++) {
			WORD ch = *((WORD *)((BYTE *)ddsd.lpSurface + (i * ddsd.lPitch + (j<<1))));
			fwrite(&ch, 2, 1, fp);
		}
	}
	fclose(fp);
	*/

	//GET_DDSBPICK()->Unlock(NULL);

	return inx;
}

#define DECO_DIST_CULLING	(1500.0f)
#define DECO_DIST_BLEND		(1000.0f)
#define DECO_DIST_BLEND_SKY		(1400.0f)
//#define DECO_DIST_BLEND		(1500.0f)
// -------------------------------------------------------------------
// Name : RenderDecoObjs()
// Desc : �������� ���� �׷��ֱ� ���ؼ� DecoObj������ �κ��� ���� ����.
// -------------------------------------------------------------------
void CUIMgr::RenderDecoObjs()
{
	// ���� ������ �Ǵ� Decoration Objects�� ����ϱ� ���ؼ� ����Ʈ�� ����.
	g_listRenderedDecoColor.clear();
	g_listRenderedDeco.clear();
	g_listAlphaDeco.clear();
	g_listLastDeco.clear();
	g_listFarDeco.clear();

	D3DVECTOR vPos, vEye;
	// ȭ���� �߽�(ī�޶� ���� �ִ� ���� ã�´�.)
	pCMyApp->GetEyeAtPos(vPos);
	// ī�޶��� ��ġ�� ���Ѵ�.
	pCMyApp->GetEyePos(vEye);

	if( g_bNewTerrain )
	{
		// Set camera state
		CNKObjQuadNode::SetCameraAtPos( vPos );
		CNKObjQuadNode::SetCameraEyePos( vEye );

		// Check if a decoobj exists
		if( CNKObjQuadNode::GetOpenDeco() )
		{
			if( !CNKObjQuadNode::GetOpenDeco()->IsInside( vPos.x, vPos.z ) )
			{
				pCMyApp->m_pWeatherMgr->ResumeWeatherSystem();
				CNKObjQuadNode::SetOpenDeco( NULL );
			}
		}
		// Render decoobjs
		CNKObjQuadNode::PrepareRender();
		g_pObjTree->Render( VFCULL_OVERLAP );
	}
	else
	{
		//g_listDecoObj
		BOOL bAlpha = FALSE, bOpenRoof = FALSE;
		CDecoObj *pDecoObj;
		list<CDecoObj *>::iterator prDeco;
		float render_dist, blend_dist;
		int w, h, w_pos, h_pos;

		// �����ִ� ������Ʈ�� �ֳ�����
		if(m_pOpenDeco)
		{
			if (!m_pOpenDeco->IsInside(vPos.x, vPos.z))
			{
				pCMyApp->m_pWeatherMgr->ResumeWeatherSystem();
				m_pOpenDeco = NULL;
			}
		}

		w_pos = (int) vPos.x;
		h_pos = (int) vPos.z;
		w_pos /= g_nMapCellWidth;
		h_pos /= g_nMapCellHeight;

		// �������� ���������� �ָ����� ������Ʈ�� �˻��Ͽ� �׷��ش�.
		// ������ ���ȿ� ���� ������ ���� �ָ������� �˻����� �ʴ´�.
		if (pCMyApp->GetCurWorld() == WORLD_GUILD)
			// �� ��ó�� �ִ°� Ȯ���Ѵ�.
			render_dist = 1000.0f;
		else
			render_dist = 1500.0f;

		if (pCMyApp->GetCurWorld() == WORLD_SKY)
			blend_dist = DECO_DIST_BLEND_SKY;
		else
			blend_dist = DECO_DIST_BLEND;

		for (h = h_pos - 5; h <= h_pos+5; h++)
		{
			if (h < 0 || h >= g_nMapCellHeightCount)	// �� ������ ����°� Ȯ��.
				continue;

			for (w = w_pos-5; w <= w_pos+5; w++)
			{
				if (w < 0 || w >= g_nMapCellWidthCount)
					continue;
				for (prDeco = g_listDecoObj[h][w].begin(); prDeco != g_listDecoObj[h][w].end(); prDeco++)
				{
					pDecoObj = *prDeco;

					// �Ÿ��� ���� �ø�.- 1�� �ø�.
					float deco_dist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pDecoObj->m_wx, pDecoObj->m_wz);
					if (deco_dist <= DECO_DIST_CULLING)
					{
						// 2�� �ø� - Frustum �ø�.
						if (m_pFrustum)
						{
							list<WORD>::iterator prColor;
							list<CDecoObj *>::iterator prRenderedDeco;
							list<CDecoObj *>::iterator prAlphaDeco;
							list<CDecoObj *>::iterator prLastDeco;

							if (m_pFrustum->FrustumCull(pDecoObj->m_vBoundBox, 8) != VFCULL_OUTSIDE)
							{
								// ���� ������ ����� �ϴ°��� �Ǵ��Ѵ�.
								if (g_pDecoObjSet->m_pnObjType[pDecoObj->m_nLoloId] <= BLD_HOUSE)
								{
									bOpenRoof = pDecoObj->IsInside(vPos.x, vPos.z);
									if (bOpenRoof)
									{
										m_pOpenDeco = pDecoObj;
										pCMyApp->m_pWeatherMgr->StopWeatherSystem();
									}
								}
								else
									bOpenRoof = FALSE;

								// ī�޶�� ���ĺ������Ѿ� �ϴ°��� Ȯ���Ѵ�.
								if (g_pDecoObjSet->m_pnObjType[pDecoObj->m_nLoloId] <= BLD_TREE)
								{
									//bAlpha = pDecoObj->IsInside(vEye.x, vEye.z);
									for (int i=6; i > 1; i--)
									{
										bAlpha = pDecoObj->IsInside(	vPos.x+(vEye.x-vPos.x)*i/6, vPos.z+(vEye.z-vPos.z)*i/6 );
										if (bAlpha)
											break;
									}
								}
								else
									bAlpha = FALSE;

								if (bOpenRoof && bAlpha)
									bAlpha = FALSE;

								if (deco_dist > blend_dist)
								{
									pDecoObj->m_farFactor = (float)(DECO_DIST_CULLING - deco_dist) / (DECO_DIST_CULLING - blend_dist);
									prLastDeco = g_listFarDeco.begin();
									g_listFarDeco.insert(prLastDeco, pDecoObj);
								}
								else if (bAlpha)
								{
									prAlphaDeco = g_listAlphaDeco.begin();
									g_listAlphaDeco.insert(prAlphaDeco, pDecoObj);
								}
								else if (pDecoObj->MustRenderLast())
								{
									prLastDeco = g_listLastDeco.begin();
									g_listLastDeco.insert(prLastDeco, pDecoObj);
								}
								else
								{
									pDecoObj->Render(bOpenRoof);
								}
								prColor = g_listRenderedDecoColor.begin();
								g_listRenderedDecoColor.insert(prColor, pDecoObj->m_wColorIdx);

								// ������ �Ǵ� ��� ���� ������Ʈ�� ���⿡ �ִ´�.
								prRenderedDeco = g_listRenderedDeco.begin();
								g_listRenderedDeco.insert(prRenderedDeco, pDecoObj);
							}  // end of if (m_pFrustum->FrustumCull(pDecoObj->m_vBoundBox, 8) != VFCULL_OUTSIDE) {}

						}
					}
					else
					{
						if( pDecoObj->m_LineEffectsLoad )
							pDecoObj->DeleteEffectNum();
					}
				}
			}
		}

		for (h = h_pos-10; h <= h_pos+10; h++)
		{
			if (h < 0 || h >= g_nMapCellHeightCount)	// �� ������ ����°� Ȯ��.
				continue;
			for (w = w_pos-10; w <= w_pos+10; w++)
			{
				if (w < 0 || w >= g_nMapCellWidthCount)
					continue;
				for (prDeco = g_listDecoObj[h][w].begin(); prDeco != g_listDecoObj[h][w].end(); prDeco++)
				{
					pDecoObj = *prDeco;

					float deco_dist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pDecoObj->m_wx, pDecoObj->m_wz);
					if (deco_dist >= DECO_DIST_CULLING)
					{
						if( pDecoObj->m_LineEffectsLoad )
						{
							pDecoObj->DeleteEffectNum();
						}
					}

				}
			}
		}
	}
}

// -------------------------------------------------------------------
// Name : RenderAlphaObjs()
// Desc : ���� ������ ������Ʈ�� �׸���.
// -------------------------------------------------------------------
void CUIMgr::RenderAlphaObjs()
{
	list<CDecoObj *>::iterator prDeco;
	CDecoObj *pDecoObj;

	DWORD dwZWriteEnable;

	pCMyApp->GetDevice()->GetRenderState(D3DRENDERSTATE_ZWRITEENABLE, &dwZWriteEnable);
	pCMyApp->GetDevice()->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

	for (prDeco = g_listAlphaDeco.begin(); prDeco != g_listAlphaDeco.end(); prDeco++)
	{
		pDecoObj = *prDeco;
		pDecoObj->Render(FALSE, DECO_ALPHA_SEE);
	}
	pCMyApp->GetDevice()->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, dwZWriteEnable);

	for (prDeco = g_listLastDeco.begin(); prDeco != g_listLastDeco.end(); prDeco++)
	{
		pDecoObj = *prDeco;
		pDecoObj->Render(FALSE);
	}
	for (prDeco = g_listFarDeco.begin(); prDeco != g_listFarDeco.end(); prDeco++)
	{
		pDecoObj = *prDeco;
		pDecoObj->Render(FALSE, DECO_ALPHA_FAR);
	}
}

extern int GetHideSight(int skill_level);

#define PLAYER_SPEAR_SIZE 20.0f			// ���� �ʿ�.. ������ �˻簡 �ʿ��ϴ�.
#define MONSTER_SPEAR_SIZE 30.0f
// -------------------------------------------------------------------
// Name : RenderPlayers()
// Desc : �÷��̾���� �׸���.
// -------------------------------------------------------------------
void CUIMgr::RenderPlayers()
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;
	pCMyApp->m_bTest = FALSE;
	g_nPlRenNum = 0;

	float fSight, fDist;
	if( pCMyApp->IsSoccerZone() )
		fSight = 1500.0f;
	else
		fSight = 500.0f;

	if (g_pRoh->IsHidden())
	{
		fSight = (float) GetHideSight(g_ChaSkill.GetLevelByIndex(SKILL_HIDE));
	}

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;

		//mungmae 2006/06/21 ������ ����忡���� �ɸ��� �Ÿ��� ���� �־����� ���̰Բ� �Ѵ�.
		fDist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pCha->m_wx, pCha->m_wz);
		if( pCMyApp->IsSoccerZone() && fDist<= 1500.0f )
		{
			BOOL bVisible = TRUE;
			if (m_pFrustum->FrustumCullPoint(pCha->m_wx, pCha->m_wy, pCha->m_wz, PLAYER_SPEAR_SIZE) == VFCULL_OUTSIDE)
				bVisible = FALSE;

			if (fDist > fSight)
				bVisible = FALSE;

			if (bVisible)
				g_nPlRenNum++;

			if (pCha->m_wColorIdx == m_wColor)
				pCha->Render(GET_D3DPICK() , TRUE);
			else
				pCha->Render(GET_D3DPICK() , FALSE, bVisible);
		}
		else if ( !pCMyApp->IsSoccerZone() && fDist <= 500.0f)	// �Ÿ��� ���� ������ ��� �Ǵ�.
		{
			BOOL bVisible = TRUE;
			if (m_pFrustum->FrustumCullPoint(pCha->m_wx, pCha->m_wy, pCha->m_wz, PLAYER_SPEAR_SIZE) == VFCULL_OUTSIDE)
				bVisible = FALSE;

			if (fDist > fSight)
				bVisible = FALSE;

			if (bVisible)
				g_nPlRenNum++;

			if (pCha->m_wColorIdx == m_wColor)
				pCha->Render(GET_D3DPICK() , TRUE);
			else
				pCha->Render(GET_D3DPICK() , FALSE, bVisible);
		}
	}

	g_nPlListNum = m_character_map.size();
}

// nate
// ����Ʈ�� ĳ���� �˾�â �׷���
void CUIMgr::DrawChatPopups()
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;	// ����Ʈ�� �ö� ĳ���͵��� �����͸� ���´�.

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;

		// �׸��� ���
//		pCha->DrawChatPopup(g_pNk2DFrame->GetControlBottom()->IsChatWide());
		// ǳ������ ��/������ �������ִ� ��ư�� �߰��ؼ� ���� ����.
		pCha->DrawChatPopup( !g_pNk2DFrame->GetControlBottom()->m_ChatOutOpt_BalloonOnOff.GetToggleState() ); // �� �༮�� ���ڰ��� TRUE�� ��� �����̴�.(�� ��۹�ư �ݴ�� �������.)
	}

	CNkMob* pMob;
	LHMobMap_it prMob;	// ����Ʈ�� �ö� ĳ���͵��� �����͸� ���´�.
	for (prMob = m_mob_map.begin(); prMob != m_mob_map.end(); prMob++)
	{
		pMob = (*prMob).second;
		// ǳ������ ��/������ �������ִ� ��ư�� �߰��ؼ� ���� ����.
		pMob->DrawMobChatPopup();
	}
}

//=================================================================================
// nate 2004 - 4
// Crash_Miss
void CUIMgr::InitChatPopups()
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;

	CNkMob* pMob;
	LHMobMap_it prMob;

	for ( pr = m_character_map.begin() ; pr != m_character_map.end() ; pr ++ )
	{
		pCha = (*pr).second;
		pCha->InitChatPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight() );
	}

	for( prMob = m_mob_map.begin() ; prMob != m_mob_map.end() ; prMob ++ )
	{
		pMob = (*prMob).second;
// ����Ʈ ��, �׽�Ʈ ���� ���� �ּ� ó��
//		if( pMob->m_nVirId == 324 )
		pMob->InitMobChatPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight() );
		pMob->InitCrash_MissPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight() );
	}

	///��������
	CUserShopNpc *pUserShopNpc;
	LHUserShopNpcMap_it prUserShopNpc;
	for( prUserShopNpc = m_usershopnpc_map.begin() ; prUserShopNpc != m_usershopnpc_map.end() ; prUserShopNpc++ )
	{
		pUserShopNpc = (*prUserShopNpc).second;
		pUserShopNpc->InitCrash_MissPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight() );
	}

	if ( g_pRoh )
		g_pRoh->InitChatPopup( g_pNk2DFrame->GetClientWidth(), g_pNk2DFrame->GetClientHeight() );
}
//=================================================================================

// -------------------------------------------------------------------
// Name : RenderMobs()
// Desc : ���͵��� �׸���.
// -------------------------------------------------------------------
void CUIMgr::RenderMobs()
{
	CNkMob *pMob;
	LHMobMap_it prMob;
	float fDist, fDistMin;

	fDistMin = 10000.0f;	// ����� ū ���� ��´�.

	pCMyApp->m_pNearMob = NULL;

	g_nMobRenNum = 0;

	float fSight = 700.0f;
	if (g_pRoh->IsHidden())
		fSight = (float) GetHideSight(g_ChaSkill.GetLevelByIndex(SKILL_HIDE));

	std::map<int, WORD>	dead_map; // vir_id , colorkey
	BOOL isControlKeyPressed = (GetKeyState(VK_CONTROL) & 0x80) == 0 ? FALSE : TRUE;
	for (prMob = m_mob_map.begin(); prMob != m_mob_map.end(); prMob++)
	{
		pMob = (*prMob).second;

		if( pMob->GetDeadFrame() > 100 )
			dead_map.insert( std::map<int, WORD>::value_type( pMob->m_nVirId , pMob->m_wColorIdx ) );

		// nate 2005-03-31
		// G.P.Stone �����Ŀ� �ٷ� �׸��� ����.
		if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX )
		{
			if( m_nStoneState[ 9 ]	&& pMob->m_nMobNum == 376 )
				continue;
			if( m_nStoneState[ 10 ] && pMob->m_nMobNum == 374 )
				continue;
			if( m_nStoneState[ 11 ] && pMob->m_nMobNum == 375 )
				continue;
		}

		/* // ������ �����鼭 �״� ����� �׳� ��������. �Ѥ�;;
		// [2008/11/10 Theodoric] WORLD_MATRIX_2009
		if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009 )
		{
			if( m_nStoneState[ 6 ] != 0	 && pMob->m_nMobNum == 628 )
				continue;
			if( m_nStoneState[ 7 ] != 0	 && pMob->m_nMobNum == 629 )
				continue;
			if( m_nStoneState[ 8 ] != 0	 && pMob->m_nMobNum == 630 )
				continue;
			if( m_nStoneState[ 9 ] != 0	 && pMob->m_nMobNum == 631 )
				continue;
			if( m_nStoneState[ 10 ]	!= 0 && pMob->m_nMobNum == 632 )
				continue;
		}
		*/

		// �Ÿ��� ���� ������ ��� �Ǵ�.
		fDist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pMob->m_wx, pMob->m_wz);
		if( fDist <= 700.0f )
		{
			if (fDist < fDistMin && !pMob->IsDead())
			{
				fDistMin = fDist;
				pCMyApp->m_pNearMob = pMob;
			}

			BOOL bVisible = TRUE;
			if (m_pFrustum->FrustumCullPoint(pMob->m_wx, pMob->m_wy, pMob->m_wz, MONSTER_SPEAR_SIZE) == VFCULL_OUTSIDE)
				bVisible = FALSE;

			if (fDist > fSight)
				bVisible = FALSE;

			if (bVisible)
				g_nMobRenNum++;			

			if (pMob->m_wColorIdx == m_wColor)
				pMob->Render(TRUE, TRUE, isControlKeyPressed);
			else
				pMob->Render(FALSE, bVisible, isControlKeyPressed);
		}
	}

	if( !dead_map.empty() )
	{
		printf( "mob dead : %d\n" , dead_map.size() );
		std::map<int, WORD>::iterator it;
		for( it=dead_map.begin() ; it!=dead_map.end() ; ++it )
		{
			DelColorKeyMap( (*it).second );
			DelMob((*it).first);
		}
		dead_map.clear();
	}

	g_nMobListNum = m_mob_map.size();
}

void CUIMgr::RenderUserShopNpc() ///��������.
{
	CUserShopNpc *pUserShopNpc;
	LHUserShopNpcMap_it prUserShopNpc;
	float fDist, fDistMin;

	fDistMin = 10000.0f;	// ����� ū ���� ��´�.

	float fSight = 700.0f;
	if (g_pRoh->IsHidden())
	{
		fSight = (float) GetHideSight(g_ChaSkill.GetLevelByIndex(SKILL_HIDE));
	}

	pCMyApp->GetDevice()->SetRenderState( D3DRENDERSTATE_FOGENABLE, FALSE ); // ���׸� ����� ���� ����� ����̵ȴ�.

	BOOL isControlKeyPressed = (GetKeyState(VK_CONTROL) & 0x80) == 0 ? FALSE : TRUE;
	for( prUserShopNpc = m_usershopnpc_map.begin() ; prUserShopNpc != m_usershopnpc_map.end() ; ++prUserShopNpc )
	{
		pUserShopNpc = (*prUserShopNpc).second;

		// �Ÿ��� ���� ������ ��� �Ǵ�.
		fDist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pUserShopNpc->m_wx, pUserShopNpc->m_wz);
		if( fDist <= fSight )
		{
			BOOL bVisible = TRUE;
			if( m_pFrustum->FrustumCullPoint(pUserShopNpc->m_wx, pUserShopNpc->m_wy, pUserShopNpc->m_wz, MONSTER_SPEAR_SIZE) == VFCULL_OUTSIDE )
				bVisible = FALSE;

			if( fDist > fSight )
				bVisible = FALSE;			

			if( pUserShopNpc->m_wColorIdx == m_wColor )
				pUserShopNpc->Render( TRUE, TRUE, isControlKeyPressed );
			else
				pUserShopNpc->Render( FALSE, bVisible, isControlKeyPressed );
		}
	}

	if( pCMyApp->m_bCanDoVertexFog && !g_bDungeon ) // ������ ���׸� Ű�� �ȵȴ�.
		pCMyApp->GetDevice()->SetRenderState( D3DRENDERSTATE_FOGENABLE, TRUE ); // ������ �ٽ� Ų��.
}

void CUIMgr::RenderPets()
{
	CNkPet *pPet;
	LHPetMap_it prPet;
	float fDist, fDistMin;

	fDistMin = 10000.0f;	// ����� ū ���� ��´�.

	g_nPetRenNum = 0;

	float fSight = 700.0f;
	if (g_pRoh->IsHidden())
	{
		fSight = (float) GetHideSight(g_ChaSkill.GetLevelByIndex(SKILL_HIDE));
	}

	std::map<int, WORD>	dead_map;	// vir_id , colorkey
	BOOL isControlKeyPressed = (GetKeyState(VK_CONTROL) & 0x80) == 0 ? FALSE : TRUE;
	for (prPet = m_pet_map.begin(); prPet != m_pet_map.end(); prPet++)
	{
		pPet = (*prPet).second;

		if( pPet->GetDeadFrame() > 100 )
			dead_map.insert( std::map<int, WORD>::value_type( pPet->m_nVirId , pPet->m_wColorIdx ) );

		// �Ÿ��� ���� ������ ��� �Ǵ�.
		fDist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pPet->m_wx, pPet->m_wz);
		if ( fDist <= 700.0f)
		{
			if (fDist < fDistMin && !pPet->IsDead())
				fDistMin = fDist;

			BOOL bVisible = TRUE;
			if (m_pFrustum->FrustumCullPoint(pPet->m_wx, pPet->m_wy, pPet->m_wz, MONSTER_SPEAR_SIZE) == VFCULL_OUTSIDE)
				bVisible = FALSE;

			if (fDist > fSight)
				bVisible = FALSE;

			if (bVisible)
				g_nPetRenNum++;			

			if (pPet->m_wColorIdx == m_wColor)
				pPet->Render(TRUE, TRUE, isControlKeyPressed);
			else
				pPet->Render(FALSE, bVisible, isControlKeyPressed);
		}
	}

	if( !dead_map.empty() )
	{
		printf( "pet dead : %d\n" , dead_map.size() );
		std::map<int, WORD>::iterator it;
		for( it=dead_map.begin() ; it!=dead_map.end() ; ++it )
		{
			DelColorKeyMap( (*it).second );
			DeletePet((*it).first);
		}
		dead_map.clear();
	}

	g_nPetListNum = m_pet_map.size();
}



// -------------------------------------------------------------------
// Name : RenderItems()
// Desc : �ٴڿ� ������ �����۵��� �׸���.
// -------------------------------------------------------------------
#define ITEM_SPEAR_SIZE 10
void CUIMgr::RenderItems()
{
	int cnt = -1;
	CItemInfo *pItemInfo = NULL;
	LHItemInfoMap_it prItemInfo;

	D3DMATRIX matView;
	pCMyApp->GetDevice()->GetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
	BOOL isControlKeyPressed = (GetKeyState(VK_CONTROL) & 0x80) == 0 ? FALSE : TRUE;

	for (prItemInfo = m_iteminfo_map.begin(); prItemInfo != m_iteminfo_map.end(); prItemInfo++)
	{
		pItemInfo = (*prItemInfo).second;
		BOOL bVisible = TRUE;
		if (m_pFrustum->FrustumCullPoint(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Y, pItemInfo->m_Item.m_Z, ITEM_SPEAR_SIZE) == VFCULL_OUTSIDE)
			bVisible = FALSE;		

		pItemInfo->m_Item.Render(&matView, bVisible, isControlKeyPressed);

		if (bVisible && m_bAlt)
			ShowDroppedItemName(pItemInfo);
	}
}

// �� ü�� �ٲ�� ���̴� �͵� �ٲ��ش�.
void CUIMgr::SetShowVital(int mob_idx, int vital)
{
	if (mob_idx == m_ShowVitalId)
	{
		m_Vital = vital;
	}
}

// -------------------------------------------------------------------
// Name : Render()
// Desc : �׽�Ʈ�� ����
// [3/30/2007 Theodoric] ����� �� ǥ�� :: ���콺 �ö󰣳Ѱ� �������� ���� ����¹ٸ� �׷�����.
// -------------------------------------------------------------------
void CUIMgr::Render()
{
	m_bShowName = FALSE;
	m_ShowVitalId = -1;

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(g_pDisplay->GetHWnd(), &point);

	if( ( m_wColor = WhatColorOnPick(point.x, point.y ) ) > 0 )
	{
		int target_idx = -1;
		ShowName(target_idx);

		if (m_bShowName)
		{
			//	m_NameBox.m_FontColor = RGB(0, 0, 0);
			m_NameBox.m_bCenter = TRUE;
			m_NameBox.Draw();
		}
		if (m_ShowVitalId >= 0)
		{
			if (m_Vital < 0)
				m_Vital = 0;
			else if (m_Vital > 100)
				m_Vital = 100;

			int vital_x = (g_pNk2DFrame->GetClientWidth() - VITAL_BACK_WIDTH) / 2;
			RECT rect;
			rect.top = 0;
			rect.bottom = VITAL_BACK_HEIGHT;
			rect.left = 0;
			rect.right = VITAL_BACK_WIDTH * m_Vital / 100;

			g_pDisplay->Blt(m_NameBox.m_PosX - (VITAL_BACK_WIDTH/2),
							m_NameBox.m_PosY - 8,
							m_pVitalBack);

			vital_x = (g_pNk2DFrame->GetClientWidth() - VITAL_FRONT_WIDTH) / 2;
			rect.top = 0;
			rect.bottom = VITAL_FRONT_HEIGHT;
			rect.left = 0;
			rect.right = VITAL_FRONT_WIDTH * m_Vital / 100;

			g_pDisplay->Blt(m_NameBox.m_PosX - (VITAL_FRONT_WIDTH/2),
							m_NameBox.m_PosY - 8 + (VITAL_BACK_HEIGHT - VITAL_FRONT_HEIGHT ) /2 ,
							m_pVitalFront, &rect);

		}
	}

	// [3/30/2007 Theodoric] �������� ���� ������ ȭ�鿡 ǥ�� ������.
	if( pCMyApp->m_pHeroAttGoMob != NULL )
	{

		RECT rect;
		int vital;

		if( pCMyApp->m_pHeroAttGoMob->m_Vital < 0 )
		{
			vital = 0;
		}
		else if( pCMyApp->m_pHeroAttGoMob->m_Vital > 100)
		{
			vital = VITAL_FRONT_WIDTH_C;
		}
		else
		{
			vital = ( VITAL_FRONT_WIDTH_C * pCMyApp->m_pHeroAttGoMob->m_Vital) / 100 ;
		}

		int vitalX = (g_pNk2DFrame->GetClientWidth() - VITAL_BACK_WIDTH_C ) / 2;
		rect.top = 0;
		rect.bottom = VITAL_BACK_HEIGHT_C;
		rect.left = 0;
		rect.right = VITAL_BACK_WIDTH_C;


		g_pDisplay->Blt(vitalX, 30+VITAL_BACK_Y, m_pVitalBack_Center);

		vitalX = (g_pNk2DFrame->GetClientWidth() - VITAL_FRONT_WIDTH_C ) / 2;
		rect.top = 0;
		rect.bottom = VITAL_FRONT_HEIGHT_C;
		rect.left = 0;
		rect.right = vital;

		g_pDisplay->Blt(vitalX, 30+VITAL_FRONT_Y, m_pVitalFront_Center, &rect);

		CTextOutBox NameBox;
		NameBox.Init(PLAYERNAME_FONTSIZE, PLAYERNAME_FONTCOLOR,
					 g_pNk2DFrame->GetClientWidth() / 2, 30+VITAL_FRONT_Y + 8, -1, -1, TRUE);
		NameBox.SetVisible(TRUE);
		SetShowName( &NameBox, pCMyApp->m_pHeroAttGoMob );
		NameBox.Draw();
	}

	if( m_bAutoHunt )
	{
		m_AutoPlay->Render();
	}
}

void CUIMgr::EraseAllList()
{
	ClearAll();

	// g_listDecoObj�� DeleteDecoObjData() �Լ����� �����.
	g_listRenderedDeco.clear();				// �� �κ��� Ŭ��� �����ָ� �ȴ�.

	m_pOpenDeco = NULL;

	g_nMobInNum = 0;
	g_nPetInNum = 0;
	g_nPlInNum = 0;
	g_nItemListNum = 0;
}

// ---------------------------------------------------------------------
// FixCameraPos()
// Desc : �÷����ϱ� ���� ī�޶� ��ġ�� ���߾� �ش�.
// ---------------------------------------------------------------------
#define CAM_ANI_TOTAL_FRAME 20
BOOL CUIMgr::FixCameraPos()
{
	static D3DVECTOR vTarget;
	static D3DVECTOR vCurPos;
	static int nCount = 0;
	static int nTotalFrame = CAM_ANI_TOTAL_FRAME;
	static D3DVECTOR vFramePos[CAM_ANI_TOTAL_FRAME];
	D3DVECTOR vAt;


	if (m_bAdjustingCamera == FALSE)
	{
		vTarget.x = g_pRoh->m_wx;
		if (g_dwClientCountry == 0 || g_dwLangType == 0)
		{
			vTarget.y = g_pRoh->m_wy + 70.0f;
			vTarget.z = g_pRoh->m_wz - 103.0f;
		}
		else if (g_dwClientCountry == CTRY_TH || g_dwClientCountry == CTRY_TEN || g_dwClientCountry == CTRY_ENG)
		{
			vTarget.y = g_pRoh->m_wy + 53.0f;
			vTarget.z = g_pRoh->m_wz - 90.0f;
		}
		else
		{
			vTarget.y = g_pRoh->m_wy + 53.0f;
			vTarget.z = g_pRoh->m_wz - 90.0f;
		}

		// ��� ������ �Ѵ�.
		pCMyApp->GetEyePos(vCurPos);

		for (int i=0; i < nTotalFrame; i++)
		{
			vFramePos[i].x = vCurPos.x + (vTarget.x - vCurPos.x)*0.05*i;
			vFramePos[i].y = vCurPos.y + (vTarget.y - vCurPos.y)*0.05*i;
			vFramePos[i].z = vCurPos.z + (vTarget.z - vCurPos.z)*0.05*i;
		}

		nCount = 0;
		m_bAdjustingCamera = TRUE;
	}
	else
	{
		// ī�޶� ������ ��ȭ�� ���� �����Ѵ�.
		pCMyApp->GetEyeAtPos(vAt);
		pCMyApp->SetCameraInitPos(vFramePos[nCount], vAt);
		nCount++;
		if (nCount >= CAM_ANI_TOTAL_FRAME)
		{
			pCMyApp->SetHeroInitPos(g_pRoh->m_wx, g_pRoh->m_wy, g_pRoh->m_wz, g_pRoh->m_dir);
			//pCMyApp->SetFov(0.75f);
			pCMyApp->SetFov(0.75f);
			pCMyApp->UpdateProjectMatrix();
			m_bAdjustingCamera = FALSE;
			return FALSE;
		}
	}

	return m_bAdjustingCamera;
}
/////////////////////////////////////////////////////////////////////////////////
// TestEffect() : Ư���� ȿ���� ó���ϱ� ���ؼ� .. ���� ��Ƽ�.
//
// nate 2004 - 7
// ��� ����

void CUIMgr::TestEffect(int type)
{
	// ���� �ܰ�..
	// ��𿡼� ���� �� ���ΰ�?

	// ��� ��..
	D3DVECTOR vFrom, vAt;

	vFrom.x = g_pRoh->m_wx;
	vFrom.y = g_pRoh->m_wy;
	vFrom.z = g_pRoh->m_wz;

	// ī�޶��� ��������  �Ÿ��� 100 ���� ������ ������ ���� ����..
	vAt = pCMyApp->GetEyeDirection();
	float mag = (float) sqrt(vAt.x*vAt.x + vAt.z*vAt.z);
	vAt.x = vAt.x / mag;
	vAt.z = vAt.z / mag;
	vAt.y = vFrom.y;

	int nRand;

	do
	{
		nRand = rand();
		nRand = nRand % 100;
	}
	while ( (nRand < 80) || (nRand >= 100) );

	vAt.x = vAt.x * nRand;
	vAt.z = vAt.z * nRand;

	vAt.x = vFrom.x + vAt.x;
	vAt.z = vFrom.z + vAt.z;
	vAt.y = vFrom.y;

	// nate 2004 - 8 ��� �ȵǴ� Ŭ����
//	pCMyApp->m_pTestEffect->CalBullet(vFrom, vAt, type);
}

//-------------------------------------------------------------------------
// IsPortal()
// Desc :  �̵�����Ʈ�ΰ� Ȯ���Ѵ�.
// [2008/5/6 Theodoric] �̵� ����Ʈ �Ӹ� �ƴ϶� decoobject�� ����ϴ� ��� ���� üũ�ϴ� ������ ����Ѵ�.
// ������ ���� ���� ���� bool���� int������ �ٲ㼭 ����ߴ�.
// 1:��Ż 2: ���� ��
//-------------------------------------------------------------------------
int CUIMgr::IsPortal(D3DVECTOR &vLoc)
{
	list<CDecoObj *>::iterator prDeco;
	CDecoObj *pDecoObj;

	for (prDeco = g_listRenderedDeco.begin(); prDeco != g_listRenderedDeco.end(); prDeco++)
	{
		pDecoObj = *prDeco;

		if (pDecoObj->m_wColorIdx == m_wColor)
		{
			int a = pDecoObj->m_nLoloId;

			if( pCMyApp->GetCurWorldID() == 4 )
			{
				if( a == 46 )
					return 1;

				{
					switch( a )
					{
					case 150:
					case 151:
					case 152:
					case 153:
					case 154:
						return 2;
					}
				}
			}

			// nate 2005-03-07 : Matrix - �̵�����Ʈ �߰�
			if( g_MatrixSvr == 1 ) // ��Ʈ���� ������ ��� �� �� PK�� �̵�����Ʈ. (by ����)
			{
				//  [7/14/2009 ppmmjj83] �Ϻ� ����콺 �౸�� �̵���Ż ���콺 ������ ��ȭ ����..
				if( g_dwClientCountry == CTRY_JPN )
				{
					if( a == 129 || a == 134 || a == 157
							|| a == 87 || a == 88 || a == 89
							|| a == 94 || a == 163 || a == 164 )// (�����̵� ����Ʈ) (���->PK) (PK->���)
						return 1;
				}
				else
				{
					if( a == 129 || a == 134 || a == 157
							|| a == 87 || a == 88 || a == 89
							|| a == 94 || a == 163 || a == 164 // (�����̵� ����Ʈ) (���->PK) (PK->���)
							|| a == 190 || a == 191 )	// �౸�� ��Ż
						return 1;
				}
			}

			if( g_MatrixSvr == 2 )  // [2008/11/3 Theodoric] WORLD_MATRIX_2009
			{
				switch( a )
				{
				case 4:					// ���� ���� ����Ʈ ���帶��
				case 5:					// ���� ���� ����Ʈ �ȱ׸���
				case 214:
				case 210:	// ���� -> PK��, ��Ʈ���� �̵� ����Ʈ
				case 211:				// PK�� -> ���� �̵� ����Ʈ
					return 1;
				}
			}
			// nate 2004 - 12 : work_gate - ȭ��Ʈȥ, ȭ��Ʈȥ ���� ����Ʈ �߰�
			if(
				a == 49  || a==222
				|| a == 220  || a==219
				|| a==67 || a==189 || a==181 || a==294
				|| a == 241	// ȭ��Ʈȥ(�����Ա�)
				|| a == 81	// ȭ��Ʈȥ����
			)
			{
				return 1;
			}

			if( pCMyApp->GetCurWorldID() == 0 )
			{
				switch( a )
				{
				case 68:
				case 223: // �ذ� ���� �Ա�
				case 224: // ����2�ʵ��Ա�
					return 1;
				}
			}

			if( pCMyApp->GetCurWorldID() == 2 )
			{
				switch( a )
				{
				case 38:
				case 51:
				case 59:
				case 60:
				case 61:
				case 62:
				case 63:
					return 1;
				}
			}

			if( pCMyApp->GetCurWorldID() == WORLD_WHITEHORN )
			{
				if( a == 81 || a == 241 )
					return 1;
			}

			if( pCMyApp->GetCurWorldID() == WORLD_DMITRON
// by evilkiki 2009.07.15
					|| pCMyApp->GetCurWorldID() == WORLD_DMITRON_BATTLE
			  )
			{
				switch( a )
				{
				case 209:
					return 1;
				case 384: // �ذ� ���� �Ա�
					// [2008/8/22 Theodoric] ���ɷм��� ���Ʈ�� ���� ����
					return 1;
				}
			}

			if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_BULKAN)
			{
				if( a == 79 || a == 80 || a == 81 )
					return 1;
			}

			if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_KAILIPTON)
			{
				if( a == 68 || a == 69 || a == 70 )
					return 1;
			}

			if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_AIDIA)
			{
				if( a == 36 || a == 37 || a == 38 )
					return 1;
			}

			if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_HYBRIDER)
			{
				if( a == 114 || a == 115 || a == 116 /* || a == 117*/ )
					return 1;
			}

			if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_FINALBOSS)
			{
				if( a == 35 )
					return 1;
			}

			if( pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON1 ) // ��ī�� �̵� ����Ʈ�� üũ.. ���� �̷������� �� üũ�� �ؾ��Ѵ�. ///�δ�1
			{
				if( a == 34 || a == 29 || a == 35 || a == 55 ) // ���������� �ⱸ, ����->1��, 1��->2��
					return 1;
			}
		}
	}
	return 0;
}

int CUIMgr::IsChangeWorld(D3DVECTOR &vLoc)
{
	int nVal = 0;

	// ���� �ִ� �ǹ� ����Ʈ���� �̺�Ʈ �ǹ��� �ִ°� Ȯ���ϰ�

	// �� �ǹ��ȿ��� �ش�Ǵ°� ����.
	list<CDecoObj *>::iterator prDeco;
	CDecoObj *pDecoObj;

	for (prDeco = g_listRenderedDeco.begin(); prDeco != g_listRenderedDeco.end(); prDeco++)
	{
		pDecoObj = *prDeco;

		if (pDecoObj->m_wColorIdx == m_wColor)
		{
			if (g_pDecoObjSet->m_pnObjType[pDecoObj->m_nLoloId] == BLD_EVENT_1)
			{
				if ( DistPlToPl(pDecoObj->m_wx, pDecoObj->m_wz, g_pRoh->m_wx, g_pRoh->m_wz) >= 200.0f)
					return 0;

				if (pCMyApp->m_nCurWorldIdx == WORLD_FIELD)
				{
					if (pDecoObj->m_nLoloId == 223)
					{
						nVal = 1;
						m_nChangeWorldIdx = 1;
						m_nChangeLocalIdx = 0;
					}
					else if (pDecoObj->m_nLoloId == 224)
					{
						nVal = 1;
						m_nChangeWorldIdx = 2;
						m_nChangeLocalIdx = 0;
					}
					else
						if (pDecoObj->m_nLoloId == 68)
						{
							g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
							nVal = 2;
						}
				}
				else if (pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON1)
				{
					if (pDecoObj->m_nLoloId == 34)
					{
						nVal = 1;
						m_nChangeWorldIdx = 0;
						m_nChangeLocalIdx = 4;
					}
				}
				else if (pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON2)
				{
					if (pDecoObj->m_nLoloId == 38)
					{
						nVal = 1;
						m_nChangeWorldIdx = 0;
						m_nChangeLocalIdx = 5;
					}
				}
				else if (pCMyApp->m_nCurWorldIdx == WORLD_GUILD)
				{
					// by evilkiki 2009.07.16 ���Ϸ� �ѹ�
					if (pDecoObj->m_nLoloId == 238)
					{
						//					{
						nVal = 1;
						m_nChangeWorldIdx = WORLD_DUNGEON_S;
						m_nChangeLocalIdx = 0;
					}
					else
					{
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
						nVal = 2;
					}
				}
				else if (pCMyApp->m_nCurWorldIdx == WORLD_START)
				{
					switch( pDecoObj->m_nLoloId )
					{
					case 143: //�⼮üũ ������
						{
							if (g_pTcpIp)
								//							g_pTcpIp->SendNetMessage( "v_c\n" ); // �⼮üũ ��Ŷ

								nVal = 2;
						}
						break;

					case 46:
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
						nVal = 2;
						break;

					case 150:
						{
							g_pNk2DFrame->ShowHeroRankListWindow(TRUE, RACE_AIDIA);
							nVal = 2;
						}
						break;

					case 151:
						{
							g_pNk2DFrame->ShowHeroRankListWindow(TRUE, RACE_BULKAN);
							nVal = 2;
						}
						break;

					case 152:
						{
							g_pNk2DFrame->ShowHeroRankListWindow(TRUE, RACE_FREAK);
							nVal = 2;
						}
						break;

					case 153:
						{
							g_pNk2DFrame->ShowHeroRankListWindow(TRUE, RACE_HUMAN);
							nVal = 2;
						}
						break;

					case 154:
						{
							g_pNk2DFrame->ShowHeroRankListWindow(TRUE, RACE_KAILIPTON);
							nVal = 2;
						}
						break;
					case 155:
						{
							g_pNk2DFrame->ShowHeroRankListWindow(TRUE, RACE_PEROM);
							nVal = 2;
						}
						break;
					}
				}
				else if (pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON_S)
				{
					if (pDecoObj->m_nLoloId == 67)
					{
						// dungeon to field
						nVal = 1;
						m_nChangeWorldIdx = WORLD_GUILD;
						m_nChangeLocalIdx = 0;
					}
					if (pDecoObj->m_nLoloId == 189)  	// dungeon to field
					{
						nVal = 1;
						m_nChangeWorldIdx = WORLD_SKY;
						m_nChangeLocalIdx = 0;
					}
				}
				else if (pCMyApp->m_nCurWorldIdx == WORLD_SKY)
				{
					if (pDecoObj->m_nLoloId == 181)  	// paros to searust
					{
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
						nVal = 2;
					}
					if (pDecoObj->m_nLoloId == 294)
					{
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, 916);
						nVal = 2;
					}
				}
				else if( pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN )
				{
					if( pDecoObj->m_nLoloId == 222 )
					{
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
						nVal = 2;
					}
					//wan:2004-12 ȭ��Ʈȥ ���� �� ����Ʈ
					else if( pDecoObj->m_nLoloId == 241 )
					{
						nVal = 1;
						m_nChangeWorldIdx = WORLD_DUNGEON4;
						m_nChangeLocalIdx = 0;
					}
				}
				//WAN:2004-12 ȭ��Ʈȥ ���� �ƿ� ����Ʈ
				else if( pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON4 )
				{
					if( pDecoObj->m_nLoloId == 81 )
					{
						nVal = 1;
						m_nChangeWorldIdx = WORLD_WHITEHORN;
						m_nChangeLocalIdx = 0;
					}
				}
				// nate 2005-03-07 : Matrix - �̵�����Ʈ
				else if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX )
				{
					if( ( pDecoObj->m_nLoloId >= 87 && pDecoObj->m_nLoloId <= 89 )
							|| pDecoObj->m_nLoloId == 94
							|| pDecoObj->m_nLoloId == 163
							|| pDecoObj->m_nLoloId == 164 )
					{

						m_nWarpGateIndex = pDecoObj->m_nLoloId;

						// ������ �����ֱ�
						// cmd���� �⼼���� �ް� �����ٰ�...
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx );
						nVal = 2;
					}
				}
				else if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009 )
				{
					switch(pDecoObj->m_nLoloId)
					{
					case 4:
					case 5: // ���� ��������Ʈ
						m_nWarpGateIndex = pDecoObj->m_nLoloId;
						g_pNk2DFrame->ShowInterfaceWindow( true, GATE, WORLD_MATRIX_2009 );
						nVal = 2;
						break;

					case 210:
						m_nWarpGateIndex = pDecoObj->m_nLoloId;
						g_pNk2DFrame->ShowInterfaceWindow(true, GATE, 1011);
						nVal = 2;
						break;
					}
				}
				// nate 2005-07-12 : Dmitron - Obj ����Ʈ ������ ����
				else if( (pCMyApp->m_nCurWorldIdx == WORLD_DMITRON || pCMyApp->m_nCurWorldIdx == WORLD_DMITRON_BATTLE )  )
				{
					if( pDecoObj->m_nLoloId == 209  )
					{
						CControlGate* pGate = (CControlGate*)g_pNk2DFrame->GetInterface(GATE);

						{
							if (g_pTcpIp)
							{
								sprintf(m_commOut, "occp bt trans 5\n" );
								g_pTcpIp->SendNetMessage( m_commOut );
								pGate->SetSubType( 5 );
							}
						}
						nVal = 2;
					}
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_BULKAN )
				{
					if( pDecoObj->m_nLoloId == 79 ||  pDecoObj->m_nLoloId == 80 ||  pDecoObj->m_nLoloId == 81 )
					{
						CItem *pKeyItem = NULL;
						pKeyItem = g_pRoh->FindItemByVnumFromAll( 1831 ); // ����� ���踦 ������ �ִ��� ã�´�.

						if( pKeyItem ) // ���谡 �ִٸ�
						{
							// �� ����޶�� ��Ŷ�� ������.
							int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

							if( PackNum >= 0 && PackNum <= PACK_NUM ) // �κ��� ��ȯâ�� �˻��Ѵ�.
							{
								// br_key [packnum] [key item index] [room num]
								sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, pDecoObj->m_nLoloId - 77 );
								if( g_pTcpIp )
									g_pTcpIp->SendNetMessage(m_commOut);
							}
						}
						else if( pCMyApp->IsPeaceArea(g_pRoh) )  // ���谡 ���ٸ� �ʿ��ϴٴ� �޽����� ��������.
						{
							sprintf(m_commOut, "br_key -1 -1 %d\n", pDecoObj->m_nLoloId - 77 );
							if( g_pTcpIp )
								g_pTcpIp->SendNetMessage(m_commOut);
						}

						nVal = 2;
					}
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_KAILIPTON )
				{
					if( pDecoObj->m_nLoloId == 68 ||  pDecoObj->m_nLoloId == 69 ||  pDecoObj->m_nLoloId == 70 )
					{
						CItem *pKeyItem = NULL;
						pKeyItem = g_pRoh->FindItemByVnumFromAll( 1865 ); // ����� ���踦 ������ �ִ��� ã�´�.

						if( pKeyItem ) // ���谡 �ִٸ�
						{
							// �� ����޶�� ��Ŷ�� ������.
							int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

							if( PackNum >= 0 && PackNum <= PACK_NUM ) // �κ��� ��ȯâ�� �˻��Ѵ�.
							{
								// br_key [packnum] [key item index] [room num]
								sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, pDecoObj->m_nLoloId - 67 );
								if( g_pTcpIp )
									g_pTcpIp->SendNetMessage(m_commOut);
							}
						}
						else if( pCMyApp->IsPeaceArea(g_pRoh) )  // ���谡 ���ٸ� �ʿ��ϴٴ� �޽����� ��������.
						{
							sprintf(m_commOut, "br_key -1 -1 %d\n", pDecoObj->m_nLoloId - 67 );
							if( g_pTcpIp )
								g_pTcpIp->SendNetMessage(m_commOut);
						}

						nVal = 2;
					}
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_AIDIA )
				{
					if( pDecoObj->m_nLoloId == 36 ||  pDecoObj->m_nLoloId == 37 ||  pDecoObj->m_nLoloId == 38 )
					{
						CItem *pKeyItem = NULL;
						pKeyItem = g_pRoh->FindItemByVnumFromAll( 1903 ); // �ٸ����� ���踦 ������ �ִ��� ã�´�.

						if( pKeyItem ) // ���谡 �ִٸ�
						{
							// �� ����޶�� ��Ŷ�� ������.
							int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

							if( PackNum >= 0 && PackNum <= PACK_NUM ) // �κ��� ��ȯâ�� �˻��Ѵ�.
							{
								// br_key [packnum] [key item index] [room num]
								sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, pDecoObj->m_nLoloId - 35 );
								if( g_pTcpIp )
									g_pTcpIp->SendNetMessage(m_commOut);
							}
						}
						else if( pCMyApp->IsPeaceArea(g_pRoh) )  // ���谡 ���ٸ� �ʿ��ϴٴ� �޽����� ��������.
						{
							sprintf(m_commOut, "br_key -1 -1 %d\n", pDecoObj->m_nLoloId - 35 );
							if( g_pTcpIp )
								g_pTcpIp->SendNetMessage(m_commOut);
						}

						nVal = 2;
					}
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_HYBRIDER )
				{
					if( pDecoObj->m_nLoloId == 114 || pDecoObj->m_nLoloId == 115 ||  pDecoObj->m_nLoloId == 116 /* || pDecoObj->m_nLoloId == 117 */ )
					{
						CItem *pKeyItem = NULL;
						pKeyItem = g_pRoh->FindItemByVnumFromAll( 1846 ); // ����� ���踦 ������ �ִ��� ã�´�.

						if( pKeyItem ) // ���谡 �ִٸ�
						{
							// �� ����޶�� ��Ŷ�� ������.
							int PackNum = g_pRoh->CheckWherePackItem( pKeyItem );

							if( PackNum >= 0 && PackNum <= PACK_NUM ) // �κ��� ��ȯâ�� �˻��Ѵ�.
							{
								// br_key [packnum] [key item index] [room num]
								sprintf(m_commOut, "br_key %d %d %d\n", PackNum, pKeyItem->m_Index, pDecoObj->m_nLoloId - 113 );
								if( g_pTcpIp )
									g_pTcpIp->SendNetMessage(m_commOut);
							}
						}
						else if( pCMyApp->IsPeaceArea(g_pRoh) )  // ���谡 ���ٸ� �ʿ��ϴٴ� �޽����� ��������.
						{
							sprintf(m_commOut, "br_key -1 -1 %d\n", pDecoObj->m_nLoloId - 113 );
							if( g_pTcpIp )
								g_pTcpIp->SendNetMessage(m_commOut);
						}

						nVal = 2;
					}
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_DISPOSAL )
				{
					g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
					nVal = 2;
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_VIDBLINE )
				{
					g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
					nVal = 2;
				}
				else if( pCMyApp->GetCurWorldID() == WORLD_FORLORN_S2 )
				{
					g_pNk2DFrame->ShowInterfaceWindow(true, GATE, pCMyApp->m_nCurWorldIdx);
					nVal = 2;
				}
				pCMyApp->StopHero(FALSE);
			}
			else if (g_pDecoObjSet->m_pnObjType[pDecoObj->m_nLoloId] == BLD_EVENT_2)
			{
				if( pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN )
				{
					if ( pDecoObj->m_nLoloId == LOLO_CRYSTAL_TOWER )   // ũ����Ż Ÿ��
					{
						if (IsMasterGuild() && g_pRoh->m_GuildLevel >= 9)
						{
							if (!g_pNk2DFrame->CloseAllWindow())
								// �������̽� �����찡 �� ������ ��쿡�� ����.
								break;

							if(m_bIsWarTax) m_bIsWarTax = FALSE;
							else m_bIsWarTax = TRUE;

							if(m_bIsWarTax)
							{
								if (m_pWarTax)
								{
									delete m_pWarTax;
									m_pWarTax = NULL;
								}
								// ���� ¡�� �ݾװ�, ����¡������ ������ ���� �޾Ƽ� ó���Ѵ�.
								m_pWarTax = new CWarTax();
							}
							nVal = 2;
						}
					}
					else if ( pDecoObj->m_nLoloId == LOLO_CASTLE_FLAG )     // �ܼ� ���
					{
						int flag = 0;
						switch((int)pDecoObj->m_wx)
						{
						case 10209://��
							flag = 0;
							break;
						case 11518://��
							flag = 1;
							break;
						case 10232://��
							flag = 2;
							break;
						case 11515://��
							flag = 3;
							break;
						default:
							flag = 4;
							break;
						}
						if (IsSubGuild(flag) && g_pRoh->m_GuildLevel >= 9)   //�ܼ��� ���üũ
						{
							// �ܼ��� �α渶 �̻��̶��... �� �����ϴµ�...
							if (!g_pNk2DFrame->CloseAllWindow())
								// �������̽� �����찡 �� ������ ��쿡�� ����.
								break;

							if(m_bIsWarTax) m_bIsWarTax = FALSE;
							else m_bIsWarTax = TRUE;

							if(m_bIsWarTax)
							{
								if (m_pWarTax)
								{
									delete m_pWarTax;
									m_pWarTax = NULL;
								}
								// ���� ¡�� �ݾװ�, ����¡������ ������ ���� �޾Ƽ� ó���Ѵ�.
								m_pWarTax = new CWarTax();
								m_pWarTax->SetArrowEnable(FALSE);
							}
							nVal = 2;
						}
					}
				}
			}
			break;
		}
	}

	return nVal;
}

BOOL CUIMgr::IsValidGate(int world_idx, int gate_vnum, float x, float z)
{
	return TRUE;
}

//-------------------------------------------------------------------------
// PrepareChangeWorld()
// Desc :
//-------------------------------------------------------------------------
void CUIMgr::PrepareChangeWorld(BOOL bUseGate, int nWorldIdx, int nLocalIdx, int sub)
{
	// ��ȯ �� �϶����� �޼����� ������.
	if (g_pNk2DFrame)
	{
		if (g_pNk2DFrame->GetControlExchange())
		{
			if (g_pNk2DFrame->GetControlExchange()->IsExch())
			{
				if (g_pTcpIp)
				{
					g_pTcpIp->SendNetMessage("exch cancel\n", FALSE);
				}
			}
		}
	}

	m_nChangeWorldIdx = nWorldIdx;
	m_nChangeLocalIdx = nLocalIdx;

	if (pCMyApp->m_nCurWorldIdx == WORLD_FIELD)
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if (pCMyApp->m_nCurWorldIdx == WORLD_GUILD)
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if (pCMyApp->m_nCurWorldIdx == WORLD_START)
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if (pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON1)
	{
		sprintf(m_commOut, "go_world %d 4\n", m_nChangeWorldIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if (pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON2)
	{
		sprintf(m_commOut, "go_world %d 5\n", m_nChangeWorldIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if (pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON_S)
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if (pCMyApp->m_nCurWorldIdx == WORLD_SKY)
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if(pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN )
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	// wan:2004-11 : Whitehorn Dungeon
	else if( pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON4 )
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	// nate 2005-07-11 : Dmitron
	else if( pCMyApp->m_nCurWorldIdx == WORLD_DMITRON )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx );
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_DMITRON_BATTLE )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx );
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	// nate 2005-03-11 : Matrix - ��Ʈ���� �������� ���� ����Ʈ �̺�Ʈ ó��
	else if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX )
	{
		m_bNextGoto = FALSE;
		sprintf( m_commOut, "mat_jump %d\n", m_nChangeWorldIdx );
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
		return;
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_GUILD_WAR )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
		return;
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_BULKAN )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_KAILIPTON)
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_AIDIA )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_HUMAN )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_HYBRIDER )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_BOSSRAID_FINALBOSS )
	{
		sprintf( m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009)
	{
		m_bNextGoto = FALSE;
		sprintf( m_commOut, "mat_jump %d\n", m_nChangeWorldIdx );
		if( g_pTcpIp )
		{
			g_pTcpIp->SendNetMessage( m_commOut, TRUE );
		}
		return;
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_DISPOSAL )
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_VIDBLINE )
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_FORLORN_S2 )
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}
	else if( pCMyApp->m_nCurWorldIdx == WORLD_FORLORN_S3 )
	{
		sprintf(m_commOut, "go_world %d %d\n", m_nChangeWorldIdx, m_nChangeLocalIdx);
		if (g_pTcpIp)
		{
			g_pTcpIp->SendNetMessage(m_commOut, TRUE);
		}
	}

	CPacketControl::EnableSend(FALSE);
	pCMyApp->PrepareChangeWorld();
}

//-------------------------------------------------------------------------
// CanTransFloor()
// Desc : ����Ʈ�������� �� �̵��� ���õ� �Լ�.
//-------------------------------------------------------------------------
int CUIMgr::CanTransFloor(int nWorldNum)
{
	int gate_idx = -1;

	// ���� �ִ� �ǹ� ����Ʈ���� �̺�Ʈ �ǹ��� �ִ°� Ȯ���ϰ�

	// �� �ǹ��ȿ��� �ش�Ǵ°� ����.
	list<CDecoObj *>::iterator prDeco;
	CDecoObj *pDecoObj;

	if (nWorldNum == WORLD_DUNGEON1)
	{
		for (prDeco = g_listRenderedDeco.begin(); prDeco != g_listRenderedDeco.end(); prDeco++)
		{
			pDecoObj = *prDeco;

			if (pDecoObj->m_wColorIdx == m_wColor)
			{
				if (g_pDecoObjSet->m_pnObjType[pDecoObj->m_nLoloId] == BLD_EVENT_2 && DistPlToPlAbs(pDecoObj->m_wx, pDecoObj->m_wz, g_pRoh->m_wx, g_pRoh->m_wz ) < 200 ) // �Ÿ��� �ʹ� ª���� ���콺�� Ŭ���ص� �̵����� �ʰ� �Ѵ�.
				{
					gate_idx = pDecoObj->m_nLoloId;
					break;
				}
			}
		}
	}
	else if (nWorldNum == WORLD_DUNGEON2)
	{
		for (prDeco = g_listRenderedDeco.begin(); prDeco != g_listRenderedDeco.end(); prDeco++)
		{
			pDecoObj = *prDeco;

			if (pDecoObj->m_wColorIdx == m_wColor)
			{
				if (g_pDecoObjSet->m_pnObjType[pDecoObj->m_nLoloId] == BLD_EVENT_2 && DistPlToPlAbs(pDecoObj->m_wx, pDecoObj->m_wz, g_pRoh->m_wx, g_pRoh->m_wz ) < 200 ) // �Ÿ��� �ʹ� ª���� ���콺�� Ŭ���ص� �̵����� �ʰ� �Ѵ�.
				{
					gate_idx = pDecoObj->m_nLoloId;
					break;
				}
			}
		}
	}

	return gate_idx;


}

//-------------------------------------------------------------------------
// CanTransFloor()
// Desc : ����Ʈ�������� �� �̵��� ���õ� �Լ�.
//-------------------------------------------------------------------------
void CUIMgr::TransFloor(int nWorldNum, int gate_idx)
{
	float min_x = 0;
	float min_z = 0;
	float width = 0;
	float height = 0;

	if (nWorldNum == WORLD_DUNGEON1)
	{
		switch (gate_idx)
		{
		case 29: // ����->1��

			//-- IDS_WANT_GO_DEK1 : ��ī�� 1������ �̵��Ͻðڽ��ϱ�?
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_WANT_GO_DEK1),TYPE_NOR_OKCANCLE, 36);

			return;

		case 35: // 1��->2��

			//-- IDS_WANT_GO_DEK2 : ��ī�� 2������ �̵��Ͻðڽ��ϱ�?
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_WANT_GO_DEK2),TYPE_NOR_OKCANCLE, 37);

			return;

		case 55: // 1��->����

			//-- IDS_WANT_GO_DEK3 : ���Ƿ� �̵��Ͻðڽ��ϱ�?
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_WANT_GO_DEK3),TYPE_NOR_OKCANCLE, 38);

			return;

		default:
			return;
		}
	}
	else if (nWorldNum == WORLD_DUNGEON2)
	{
		switch (gate_idx)
		{
		case 51:	// 4->3 �� �� ������. 3-4 ��ġ�� ����.
			min_x = 4848;
			min_z = 125;
			width = 4969-4848;
			height = 235-125;
			m_nCurFloor = 2;
			break;

		case 59:	// 1->2 ��
			min_x = 1729;
			min_z = 4900;
			width = 1909-1729;
			height = 4960-4900;
			m_nCurFloor = 1;
			break;

		case 60:	// 2->3
			min_x = 3060;
			min_z = 1727;
			width = 3229-3060;
			height = 1785-1727;
			m_nCurFloor = 2;
			break;

		case 61:	// 3->4
			min_x = 4803;
			min_z = 3860;
			width = 4863-4803;
			height = 3957-3860;
			m_nCurFloor = 3;
			break;

		case 62:	// 3->2
			min_x = 958;
			min_z = 3299;
			width = 1105-958;
			height = 3343-3299;
			m_nCurFloor = 1;
			break;

		case 63:	// 2->1
			min_x = 1709;
			min_z = 2224;
			width = 1897-1709;
			height = 2275-2224;
			m_nCurFloor = 0;
			break;

		default:
			return;
		}
	}



	srand( (unsigned)time( NULL ) );

	float r_x, r_z;

	r_x = rand() % (int) width;
	r_z = rand() % (int) height;

	if (g_pTcpIp)
	{
		sprintf(m_commOut, "trans %f %f\n", min_x+r_x, min_z+r_z);
		pCMyApp->SetTransTime();
		g_pTcpIp->SendNetMessage(m_commOut);
	}

	pCMyApp->StopHero(FALSE);
}

//-------------------------------------------------------------------------
// ChangeWorld()
// Desc :
//-------------------------------------------------------------------------
void CUIMgr::GoWorld(char *strIpAddr, int nPort, int nWorldNum, int nAreaNum)
{
	if( strIpAddr == NULL )
		return;

	EndEventScene(); // Ȥ�� �̺�Ʈ ���� �÷������̿��ٸ� ����(�ʱ�ȭ) �����ش�. ///�δ�1
	pCMyApp->StopHero(FALSE);
	pCMyApp->GoWorld(strIpAddr, nPort, nWorldNum, nAreaNum);

	if(g_bNc)
		g_pTcpIp->SendNetMessage("nc\n");


}

void CUIMgr::GoWorldFail()
{
	pCMyApp->m_bBeforeGoWorld = FALSE;
	CPacketControl::EnableSend(TRUE);
}

//-------------------------------------------------------------------------
// AskExchange()
// Desc : �ٸ� �������� �ŷ� ��û�� ��������..
//-------------------------------------------------------------------------
void CUIMgr::AskExchange(char *player_name)
{
	if( player_name == NULL )
		return;

	if (g_pRoh->GetMotionState() == CHA_STAND && !g_pRoh->GetCombat()
			&& !g_pNk2DFrame->IsUserShopVisible()				// ���λ��� �߿��� �ڵ� ��� ///���λ���
			&& g_pNk2DFrame->GetControlExchange() )
		g_pNk2DFrame->GetControlExchange()->AskExchange(player_name);
	else
	{
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage("exch cancel 1\n");
	}
}

//-------------------------------------------------------------------------
// ExchStart()
// Desc : �ٸ� ������ ��ȯ�� �����϶�. �ŷ�â�� ���� �ȴ�.
//		�ŷ� Ȱ�� �÷��׸� on ��Ų��.
//-------------------------------------------------------------------------
void CUIMgr::ExchStart(char *player_name, int nPlayer_level)
{
	if( player_name == NULL )
		return;

	m_bExch = TRUE;
	strcpy(m_strExchPlayerName, player_name);

	// �ŷ�â�� ����.
	g_pNk2DFrame->ShowExchangeWindow(TRUE, TRUE);
	// �ŷ� ������ �̸��� �������ش�.
	if (g_pNk2DFrame->GetControlExchange())
	{
		g_pNk2DFrame->GetControlExchange()->SetOppName(m_strExchPlayerName);
		g_pNk2DFrame->GetControlExchange()->SetOppLevel(nPlayer_level);
	}
}

//-------------------------------------------------------------------------
// ExchMoney()
// Desc : ��ȯ�� ����� ������ �÷����� �ݾ�.
//-------------------------------------------------------------------------
void CUIMgr::ExchMoney(char *strMoney)
{
	if( strMoney == NULL )
		return;
	if( g_pNk2DFrame )
		g_pNk2DFrame->GetControlExchange()->ExchMoney(strMoney);
}

//-------------------------------------------------------------------------
// ExchInvenTo()
// Desc : ��ȯ�� ����� ������ �÷����� ������.
//-------------------------------------------------------------------------
// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::ExchInvenTo(int x, int y, int index, int vnum, int gem_num, int special, int special2,
						 int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur) ///�Ź���ȭ�ý���
{
	if( g_pNk2DFrame )
		g_pNk2DFrame->GetControlExchange()->ExchInvenTo(x, y, index, vnum, gem_num, special, special2,
				UpEndur, MaxUpdEndur, Endur, MaxEndur);  ///�Ź���ȭ�ý���
}

//-------------------------------------------------------------------------
// ExchInvenFrom()
// Desc : ��ȯ�� ����� ������ ���ø� ������.
//-------------------------------------------------------------------------
void CUIMgr::ExchInvenFrom(int x, int y)
{
	if( g_pNk2DFrame )
		g_pNk2DFrame->GetControlExchange()->ExchInvenFrom(x, y);
}

//-------------------------------------------------------------------------
// Exch()
// Desc :
//-------------------------------------------------------------------------
void CUIMgr::Exch( char *cmd )
{
	if( cmd == NULL )
		return;

	if (!strcmp("disable", cmd))
	{
		g_pNk2DFrame->GetControlExchange()->ExchDisable();
	}
	else if (!strcmp("trade", cmd))
	{
		g_pNk2DFrame->GetControlExchange()->ExchTrade();
	}
	else if (!strcmp("change", cmd))
	{
		g_pNk2DFrame->GetControlExchange()->ExchChange();
	}
	else if (!strcmp("cancel", cmd))
	{
		// ������� �ŷ��� ����ߴٴ� �޽����� ������.
		g_pNk2DFrame->GetControlExchange()->ExchCancel();
	}
	else if( !strcmp("pet", cmd) ) // ���� ��ȯ�� ��ȯâ ���� ó��.( by ���� )
	{
		g_pNk2DFrame->ShowExchangeWindow( FALSE, FALSE ); // ���̱�,�ŷ���� �Ѵ� ���.
		// IDS_DRAGON_EXCH_SUCCESS : ���� ��ȯ�� �����ϼ̽��ϴ�.
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_DRAGON_EXCH_SUCCESS), TYPE_NOR_OK, 1 );
	}
}

void CUIMgr::CmdMsRequest(char *player_name)
{
	if( player_name == NULL )
		return;

	if( g_pRoh->GetMotionState() == CHA_STAND
			&& !g_pRoh->GetCombat()
			&& g_pNk2DFrame->GetRefine()
			&& !g_pNk2DFrame->IsUserShopVisible() // ���λ��� �߿��� �ڵ� ��� ///���λ���
	  )	// �������� �ƴϸ�
		g_pNk2DFrame->GetRefine()->AskMsRequest( player_name );
	else	// ����
	{
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage("ms reject\n");
	}
}

void CUIMgr::CmdMsStart( int type, char *player_name, int nSection ) // nSection �� ������ ���� ó�� �Ϸ��ٸ� ���� ���� �� �������� �׳� ���ξ���.(����)
{
	if( player_name == NULL )
		return;

	if ( strlen( player_name ) )
		strcpy( m_strMsPlayerName, player_name );
	else
		m_strMsPlayerName[ 0 ] = NULL;

	if (g_pNk2DFrame->GetRefine())
		g_pNk2DFrame->GetRefine()->SetOppName( m_strMsPlayerName );

	g_pNk2DFrame->ShowRefineWindow( TRUE, type );
}

// [6/7/2007 Theodoric] ������ ���� :: �Լ� ���� �߰�.
void CUIMgr::MsInvenTo(int x, int y, int index, int vnum, int gem_num, int special, int nSection,
					   int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur ) // nSection�� ������ ����ó�� �Ϸ��� �� ����. ���� ���ϼ������� ���ܵ�(����)
{
	if( g_pNk2DFrame->GetRefine() )
		g_pNk2DFrame->GetRefine()->MsInvenTo(x, y, index, vnum, gem_num, special,
											 UpEndur, MaxUpdEndur, Endur, MaxEndur);
}

void CUIMgr::MsInvenFrom(int x, int y, int nSection )  // nSection�� ������ ����ó�� �Ϸ��� �� ����. ���� ���ϼ������� ���ܵ�(����)
{
	if( g_pNk2DFrame->GetRefine() )
		g_pNk2DFrame->GetRefine()->MsInvenFrom(x, y);
}
void CUIMgr::MsMoney( char *strMoney, int nSection )
{
	if( strMoney == NULL )
		return;

	g_pNk2DFrame->GetRefine()->MsMoney(strMoney);
}
void CUIMgr::MsSuccess(int clear_flag, int vnum, int index, int x, int y, int nSection )
{
	g_pNk2DFrame->GetRefine()->MsSuccess( clear_flag, vnum, index, x, y );
}

void CUIMgr::MsFail( int nSection )
{
	if (g_pNk2DFrame->GetRefine()
			&& g_pNk2DFrame->GetRefine()->IsRefineConnection() )
		g_pNk2DFrame->GetRefine()->ResetConnection();	// ������ ���Ḹ ���´�.
}

//-------------------------------------------------------------------------
// CmdMsUpgrade()
// Desc : ������ �̿��� �ɼ� ���׷��̵�

//-------------------------------------------------------------------------
void CUIMgr::CmdMsUpgrade(int nSuccess, int where, int item_index, int special, int special2)
{
	CNkCharacter *pNkCha = g_pRoh;

	if( !g_pRoh )
		return;

	// �������� ã�´�. ã�� ����, ���â, extra, �κ�, ��ȯ.
	CItem *pItem = pNkCha->FindItemByIndexFromAll(item_index);

	if (pItem && 0 != nSuccess )
	{
		pItem->m_Special = special;
		ResetItemValue(pItem);
//		pItem->m_Num9 = pItem->m_Num1;//�ӽ����� 1021

		SetSpecialValue(pItem, GET_TYPE(pItem), GET_SHAPE(pItem), special, special2);

//		pItem->m_Num1 = pItem->m_Num9;//�ٽ� ��������.
		g_pNk2DFrame->GetControlInven()->ResetItemInfo();
	}

	if (nSuccess == 0)
	{
		// IDS_UIMGR_FAIL_ADDOP : �ɼ� �߰��� �����߽��ϴ�
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_FAIL_ADDOP), -1);
	}
	else if (nSuccess == 1)
	{
		// IDS_UIMGR_ADDOP : �ɼ��� �߰��Ǿ����ϴ�
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_ADDOP), -1);
	}
	else
	{
		// IDS_UIMGR_DOWNGRADE_OP : �ɼ��� �Ѵܰ� ���� �Ǿ����ϴ�
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_DOWNGRADE_OP), -1);
	}
}

//-------------------------------------------------------------------------
// InterchangeTo()
// Desc : �������� ������ ��ȯ�� �뺸��.
//-------------------------------------------------------------------------
// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::InterchangeTo(int old_idx, int new_idx, int vnum, int gem_num, int special, int special2,
						   int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetInterchange()->InterchangeTo(old_idx, new_idx, vnum, gem_num, special, special2,
			UpEndur, MaxUpdEndur, Endur, MaxEndur); ///�Ź���ȭ�ý���
}

//-------------------------------------------------------------------------
// ChipExchange()
// Desc : ������ȯ �ý���.
//----------------------------------------------------------------------------
void CUIMgr::ChipExchangeMulti(int type, BOOL bResult, int vnum, int count, int binggo_num, char * arg)
{
	if (g_pNk2DFrame->GetGamble())
		g_pNk2DFrame->GetGamble()->ChipExchangeMulti(type, bResult, vnum, count, binggo_num, arg);
}
void CUIMgr::ChipExchange(int type, BOOL bResult, int vnum, int svr_idx, int binggo_num)
{
	if (g_pNk2DFrame->GetGamble())
		g_pNk2DFrame->GetGamble()->ChipExchange(type, bResult, vnum, svr_idx, binggo_num);
}
void CUIMgr::JewelExchange(BOOL bResult, int vnum, int svr_idx)
{
	if (g_pNk2DFrame->GetGamble())
		g_pNk2DFrame->GetGamble()->JewelExchange(bResult, vnum, svr_idx);
}


//0120 ����� ������ ��ȯ���.
void CUIMgr::EventAncientExchange(int result, int type, int vnum_money, int index, int gem_num)
{
	if (g_pNk2DFrame->GetEventAncient())
		g_pNk2DFrame->GetEventAncient()->Exchange(result, type, vnum_money, index, gem_num);
}

//0401 �ĸ��� �̺�Ʈ ��ȯ ���

void CUIMgr::EventTreeExchange(int result, int type, int vnum, int index)
{
	if (g_pNk2DFrame->GetEventAncient())
		g_pNk2DFrame->GetEventAncient()->ExchangeTree(result, type, vnum, index);
}

// �̺�Ʈ �������̽� �󿡼� ������ ������ ��ȯ ������ ������ �Լ�. (by ����) ///���߱�ȯ
void CUIMgr::EventMultiExchange( int NumItem, char* Packet )
{
	if (g_pNk2DFrame->GetEventAncient())
		g_pNk2DFrame->GetEventAncient()->MultiExchange( NumItem, Packet );
}

//-------------------------------------------------------------------------
// SuccessWork()
// Desc : ������ ���������� �Ѿ���� �Լ�.
//		������ vnum�� �˾Ƴ��� ���Կ� �־��ֱ⸸ �Ѹ� �ȴ�.
//-------------------------------------------------------------------------
void CUIMgr::SuccessWork(int slot_num, int gemstone_index, int gem_index)
{
	CNkCharacter *pNkCha = g_pRoh;

	if( !g_pRoh )
		return;

	// ������ vnum�� �˾Ƴ��� ���Կ� �־��ֱ⸸ �Ѹ� �ȴ�.
	// ���ο��� ���� �ɷ� �ִ� ������ �����Ѵ�.
	if (pNkCha->m_QuickSlot[slot_num])
	{
		// IDS_UIMGR_SUCCEED_SEKONG : �� ���� �����Դϴٿ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_SUCCEED_SEKONG), -1);

//2003 �Լ� ���� ������  plus,specil �� 0���� �־���.
//		pNkCha->ToQuickSlot(slot_num, gem_index, GET_TOGEM_VNUM(pNkCha->m_QuickSlot[slot_num]));
		pNkCha->ToQuickSlot(slot_num, gem_index, GET_TOGEM_VNUM(pNkCha->m_QuickSlot[slot_num]),0,0,0);//
	}
	else
	{
		OutputDebugString("���� : SuccessWork\n");
	}
}

//-------------------------------------------------------------------------
// FailedWork()
// Desc : ������ ���������� �Ѿ�����Լ�
//-------------------------------------------------------------------------
void CUIMgr::FailedWork(int slot_num)
{
	// ���� �޽��� ���..
	// IDS_UIMGR_FAIL_SEKONG : �� ������ �����߽��ϴ�.
	g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_FAIL_SEKONG), -1);
	// ���� Ǯ���ֱ⸸ �ϸ� �ȴ�.
	g_pRoh->m_bQuickSlotLock[slot_num] = FALSE;
}

// ������ ���� upgrade �� ����� �޾Ƽ� �� ó���� ��
// 2004.03.05
// Lyul / ����(���̾� ���� )
// ���׷��̵� �� �������� ���� �޼���
//                upgrade |sucess|where_num|itemidx|gem_num
// ���� �ҽ� : ���׷��̵� �� ���� ����� Min_LEV ������ ���̾Ƹ� �Ǻ��Ϸ���
// ->�� ������ ���� Item �� Min_LEV �� ������ 0�̹Ƿ� �ڼ��� ������ �Ǻ�
// ����    : Global Item List ���� ���� ����� Item MinLevel �� ���̾Ʊ� �Ǻ�
// 2004.08.13
// Lyul / �߰�(����Ʈ ���̾�)
// ��� �Ҹ� ��ƾ �߰�.
void CUIMgr::Upgrade(int nSuccess, int where, int item_index, int gem_num)
{
	if( !g_pRoh )
		return;

	CNkCharacter *pNkCha = g_pRoh;

	// ���� ���� Pointer �� �������Ƿ� �ӽ÷� ���� ��� ������ ������ ��ġ
	int Ltemp_item_min_lev;
	// Up grade �� �������� ã�´�.
	CItem *pItem = pNkCha->FindItemByIndexFromAll(item_index);
	// ã������
	if (pItem)
	{
		// �ش� �������� ���� min_lev�� ���� �´�.
		Ltemp_item_min_lev = GET_ITEM_LEVEL(pItem);

		// ���̾� �� �̻�.
		if(Ltemp_item_min_lev>=181)
			pItem->SetDiaGemNum(gem_num);
		// ���̾� �̸���.
		else
			pItem->SetGemNum(gem_num);

		g_pNk2DFrame->GetControlInven()->m_pItemInfo->SetIndex(-1);
	}

	//--------------------------------------------------------------------------
	// Message ���
	//------------------------------------------------------------------------
	// ������ ���
	if (nSuccess == 1)
	{
		// ���� �޽��� ���.
		if (pItem->m_GemNum != 0)
			// IDS_UIMGR_COMPLETE_JEWEL : �� ������ �߰��Ǿ����ϴ�.
			g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_COMPLETE_JEWEL), -1);
		else
			// IDS_UIMGR_SUCCEED_UPGRADE : �� ��� ���׷��̵忡 �����߽��ϴ�
			g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_SUCCEED_UPGRADE), -1);
	}
	//------------------------------------------------------------------------
	// ������ ���( �޼��� ����� ��� �Ҹ�)
	else if(nSuccess == -1)
	{
		// IDS_UIMGR_REMOVE_UPGRADE : �� ��� �Ҹ�Ǿ����ϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_REMOVE_UPGRADE), -1);
		pNkCha->Remove(where);
	}
	//------------------------------------------------------------------------
	// ���� �� ���
	else
		// IDS_UIMGR_FAIL_UPGRADE : �� ��� ���׷��̵忡 �����߽��ϴ�.
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_FAIL_UPGRADE), -1);
}

//-------------------------------------------------------------------------
// Desc : ��ų�� ��ۻ���, ���� ���� �˷��ִ� �Լ��̴�.
// nSkill_OnOff : ����Ʈ�� ���ϰ����� ����
// index : ĳ���� �ε���
// skill_index : ��ų ���ؽ�
//-------------------------------------------------------------------------
void CUIMgr::SkillOnOff(int nSkill_OnOff, BOOL bChar, int index, int skill_index)
{
	CNkCharacter *pCha = NULL;
	CNkMob *pMob = NULL;

	if (bChar)
	{
		pCha = FindChaById(index, TRUE);
		if (pCha)
		{
			switch(skill_index)
			{
			case SKILL_MANA_SHIELD:
				pCha->SetManaShield(nSkill_OnOff);
				if (g_pDSound)
				{
					if (nSkill_OnOff > 0)
						g_pDSound->Play(g_EffectSound[EFF_SND_MANASHIELD1]);
				}
				break;
			case SKILL_ELECTRIC_SHIELD:
				pCha->SetElectricShield(nSkill_OnOff);
				if (g_pDSound)
				{
					if (nSkill_OnOff > 0)
						g_pDSound->Play(g_EffectSound[EFF_SND_ELECSHIELD1]);
				}
				break;
			case SKILL_SAFETY_SHIELD:
				pCha->SetSafetyShield(nSkill_OnOff);
				if (g_pDSound)
				{
					if (nSkill_OnOff > 0)
						g_pDSound->Play(g_EffectSound[EFF_SND_SAFETYSHIELD1]);
				}
				break;
			case SKILL_HIDE:

				if( pCha == g_pRoh ) ///07-04-27 �ẹ���� �������� �ް� �����ϰ� ����.(Ư�� ���� �Ұ� ó���� ���ؼ�)
					pCMyApp->StopHero(); // �̰� �߰������� ������Ѵ�.

				if (nSkill_OnOff > 0)
					pCha->SetHide(HIDE_HIDING);	//����!
				else
					pCha->SetHide(HIDE_RISING);	// ����!
				break;
			//----------------------------------------------------------
			// Skill Flag onoff
			//----------------------------------------------------------
			// Lyul_2005 �߰�
			// ��������� ��ų ������ Shadow �� Ȱ��ȭ �Ѵ�.
			case SKILL_JOINT_LIFE:
				if(pCha == g_pRoh ) // �ڱ� �ڽ��϶��� ó��
				{
					if( nSkill_OnOff==0 ) // ��ų�� ��������..
						G_SK_INVCooltime(SKILL_JOINT_LIFE); // ��Ÿ���� ������.
					else // ��ų�� ��������
						G_SK_SetCooltime(SKILL_JOINT_LIFE); // ��Ȱ��ȭ ��Ų��. (�ٸ� ������ �ڽſ��� �ɾ ������ �Կ� ����.)
				}

			case SKILL_LIFE_LIGHT:
			case SKILL_MELODY_OF_DEF:
			case SKILL_MELODY_OF_GUD:
				if(nSkill_OnOff==0)
					skill_index=0;
				pCha->SetInAidiaSkill(skill_index);//���̵�� ��ų.
				break;
			case SKILL_VANPIRE_TOUCH:
			case SKILL_HELL_CRY:
			case SKILL_TORNADO_RUIN:
			case SKILL_SUMMON_PARTITION:
			case SKILL_AIR_RAID:
				break;
			//----------------------------------------------------------
			// ����ũ ����
			//----------------------------------------------------------
			case SKILLF_E_BLEED:
				// ����
				if(nSkill_OnOff == 0)
				{
					pCha->m_bBleed = false;
					G_SK_INVCooltime(SKILLF_E_BLEED);
				}
				// ���
				else if(pCha)
				{
					pCha->m_bBleed = true;
					EffectSort ef_sort;

					// Effect ( Insetmagic �� ��ġ�� ���� )
					ef_sort.nType = FX_BLEED;
					ef_sort.pNkChaFrom = pCha;
					pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					return;
				}
				break;

			case SKILLF_E_REFLECTION:
				if( nSkill_OnOff == 1 )
				{
					pCha->m_ShowReflection = TRUE;
					EffectSort ef_sort;
					ef_sort.nType = FX_REFLECTION;
					ef_sort.pNkChaFrom = pCha;
					pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));

					if( pCha == g_pRoh ) // [1/15/2008 �����]�Ϻ� ���� ���� : ��ų ������ �̵� ���߱�� �ڱ� �ڽŸ�..
						pCMyApp->StopHero();

					pCha->SetMotionState(CHA_F_REFLECTION);
				}
				else
				{
					if( pCha == g_pRoh )
					{
						G_SK_SetCooltime(SKILLF_E_REFLECTION);
					}
					pCha->m_ShowReflection = FALSE;

				}
				break;

			case SKILL_A_SUMMONS_SQUAD:
				pCha->SetMotionState( CHA_A_SUMMONSQUAD );
				if( pCha == g_pRoh ) ///07-04-27 ��Ƽ��ȯ ��Ÿ�� �������� �ް� �������� ����.
					G_SK_SetCooltime(SKILL_A_SUMMONS_SQUAD);
				break;
			case SKILL_A_LIFE_EXPANSION:
			case SKILL_PET_LIFE:
				InsertMagic(NULL, NULL, pCha, NULL, EFFECT_SKILL_LIFEEXPENSION);
				pCha->m_byShowLIfeExpantion = nSkill_OnOff;
				break;
			case SKILLF_E_CLOAKING:
				if( nSkill_OnOff == 1 )
				{
					pCha->m_bCloaking = TRUE;
					G_SK_SetCooltime(SKILLF_E_CLOAKING);
				}
				else
					pCha->m_bCloaking = FALSE;

				if( nSkill_OnOff == -1)
					pCha->m_bCloaking_Waring = TRUE;
				else
					pCha->m_bCloaking_Waring = FALSE;
				break;
			case SKILL_K_POISON:	// nate 2005-11-14 : ������ - ��������� ����(Skill_OnOff)
				pCha->m_bPoisoning = nSkill_OnOff;
				break;
			case SKILL_F_ADRENALINE:	//mungmae-2005/11/21 - �Ƶ巹����
				if( nSkill_OnOff == 1 )
				{
					pCha->m_bShowAdrenaline = TRUE;
					EffectSort ef_sort;
					ef_sort.nType = FX_ADRENALINE;
					ef_sort.pNkChaFrom = pCha;
					pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
				}
				else
				{
					G_SK_SetCooltime(SKILL_F_ADRENALINE);
					pCha->m_bShowAdrenaline = FALSE;
				}
				break;

			case SKILL_B_PROTECTION_SHIELDS:
				if( nSkill_OnOff == 1 )
				{
					pCha->m_bProtectionShield = TRUE;
					EffectSort ef_sort;
					ef_sort.nType = FX_PROTECTIONSHIELD;
					ef_sort.pNkChaFrom = pCha;
					pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					pCMyApp->StopHero();
					pCha->SetMotionState(CHA_B_PROTECTION_SHIELD);
				}
				else
				{
					G_SK_SetCooltime(SKILL_B_PROTECTION_SHIELDS);
					pCha->m_bProtectionShield = FALSE;
				}
				break;

			case SKILL_FAIRY: // 345���� ���� ����Ʈ ��. ĳ���� ���� ����Ʈ�̱⶧���� k ��Ŷ�� ���Խ�Ų��. ///��
			case SKILL_FAIRY_HUMAN_SILVER:
			case SKILL_FAIRY_HUMAN_BLACK:
			case SKILL_FAIRY_KAI_BLUE:
			case SKILL_FAIRY_KAI_RED:
			case SKILL_FAIRY_HYB_SILVER:
			case SKILL_FAIRY_HYB_GOLD:
			case SKILL_FAIRY_AID_BLUE:
			case SKILL_FAIRY_AID_GREEN:
			case SKILL_FAIRY_BUL_SILVER:
			case SKILL_FAIRY_BUL_VIOLET:
				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
					ef_sort.Index = 0; // ��

					// �ʱ�ȭ.
					ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.subNum = 1; // ���Ⱚ���� ���.(1�� ������)
					ef_sort.vSortPos.x = 2.3f; // ũ�Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.12f; // �ӵ������� ���.

					if( skill_index == SKILL_FAIRY )
						ef_sort.dwColor = RGBA_MAKE(91,152,255,255);
					else if( skill_index == SKILL_FAIRY_HUMAN_SILVER )
						ef_sort.dwColor = RGBA_MAKE(91,152,255,255);
					else if( skill_index == SKILL_FAIRY_HUMAN_BLACK )
						ef_sort.dwColor = RGBA_MAKE(242,207,117,255);
					else if( skill_index == SKILL_FAIRY_KAI_BLUE )
						ef_sort.dwColor = RGBA_MAKE(240,210,156,255);
					else if( skill_index == SKILL_FAIRY_KAI_RED )
						ef_sort.dwColor = RGBA_MAKE(236,151,142,255);
					else if( skill_index == SKILL_FAIRY_HYB_SILVER )
						ef_sort.dwColor = RGBA_MAKE(242,221,140,255);
					else if( skill_index == SKILL_FAIRY_HYB_GOLD )
						ef_sort.dwColor = RGBA_MAKE(218,201,220,255);
					else if( skill_index == SKILL_FAIRY_AID_BLUE )
						ef_sort.dwColor = RGBA_MAKE(240,210,156,255);
					else if( skill_index == SKILL_FAIRY_AID_GREEN )
						ef_sort.dwColor = RGBA_MAKE(117,239,230,255);
					else if( skill_index == SKILL_FAIRY_BUL_SILVER )
						ef_sort.dwColor = RGBA_MAKE(221,148,111,255);
					else if( skill_index == SKILL_FAIRY_BUL_VIOLET )
						ef_sort.dwColor = RGBA_MAKE(147,126,205,255);

					// ��ƼŬ ����
					Deco_Particle *ParticleInfoArray;
					ParticleInfoArray = new Deco_Particle[MAX_PARTICLE_FOR_FXFOLLOW];
					ZeroMemory( ParticleInfoArray, sizeof(Deco_Particle)*MAX_PARTICLE_FOR_FXFOLLOW );
					for( int i = 0 ; i < MAX_PARTICLE_FOR_FXFOLLOW ; ++i )
					{
						ParticleInfoArray[i].red	= RGBA_GETRED(ef_sort.dwColor) / 255.0f;
						ParticleInfoArray[i].green	= RGBA_GETGREEN(ef_sort.dwColor) / 255.0f;
						ParticleInfoArray[i].blue	= RGBA_GETBLUE(ef_sort.dwColor) / 255.0f;

						ParticleInfoArray[i].life_time = -i*10; // ������ Ÿ���� ���� �ʱ�ȭ�� ������Ѵ�.
					}
					ef_sort.effects = ParticleInfoArray; // �� ����Ʈ ���� ��ƼŬ �޸��ּҸ� ���.

					if( pCha )
					{
						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
						ef_sort.vCurPos.y = ef_sort.pNkChaFrom->m_wy +RandomNum( 15.0f, 20.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f );

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else // ����. ���ִ� �͵� �������� ��Ŷ�� �޾Ƽ� ���־��Ѵ�.(���� ���� �� ��..)
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}

				break;

			case SKILL_LUCKYPIG1: // ���� ������
			case SKILL_LUCKYPIG2: // ���� ������
			case SKILL_LUCKYPIG3: // ���� ������
			case SKILL_LUCKYPIG4: // ���� ������

				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
					ef_sort.Index = 1; // ������.
					ef_sort.subNum = skill_index; // ������ ����. �� 4��.

					// �ʱ�ȭ.
					ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
					ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
					ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

					if( pCha )
					{
						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
						ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else // ����. ���ִ� �͵� �������� ��Ŷ�� �޾Ƽ� ���־��Ѵ�.(���� ���� �� ��..)
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}

				break;

			// [7/31/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ���̺� �ҿ�
			case SKILL_BABYSOUL_1: // ��ġ
			case SKILL_BABYSOUL_2: // ��ġ
			case SKILL_BABYSOUL_3: // ��ġ


				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
					ef_sort.Index = 2; // FX_FOLLOW_TYPE_BABYSOUL 2
					ef_sort.subNum = skill_index; // ����ٴϴ� ��ų

					// �ʱ�ȭ.
					ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
					ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
					ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

					if( pCha )
					{
						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
						ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else // ����. ���ִ� �͵� �������� ��Ŷ�� �޾Ƽ� ���־��Ѵ�.(���� ���� �� ��..)
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}

				break;

			case SKILL_VAMPIREBAT: ///�����̾���� ����

				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
					ef_sort.Index = 3; // ����

					// �ʱ�ȭ.
					ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.subNum = 1; // ���Ⱚ���� ���.(1�� ������)
					ef_sort.vSortPos.x = 4.0f; // ũ�Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.06f; // �ӵ������� ���.

					// ���� ������ ����Ʈ ����.
					list<D3DVECTOR> *TraceInfoList;
					TraceInfoList = new (list<D3DVECTOR>);
					ef_sort.effects = TraceInfoList; // �� ����Ʈ ���� ��ƼŬ �޸��ּҸ� ���.

					if( pCha )
					{
						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
						ef_sort.vCurPos.y = ef_sort.pNkChaFrom->m_wy +RandomNum( 15.0f, 20.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f );

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else // ����. ���ִ� �͵� �������� ��Ŷ�� �޾Ƽ� ���־��Ѵ�.(���� ���� �� ��..)
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}

				break;

			case SKILL_PETRUDOLPH: ///��絹��
			case SKILL_PETRUDOLPH_BLACK:	///��絹��_����
			case SKILL_PETRUDOLPH_BLUE:		///��絹��_�Ķ�
			case SKILL_PETRUDOLPH_GREEN:	///��絹��_���
			case SKILL_PETRUDOLPH_YELLOW:	///��絹��_���
			case SKILL_PETRUDOLPH_KOR_PREMIUM:

				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
					ef_sort.Index = 4; // �絹��.
					ef_sort.subNum = skill_index; // ������ ����. �� 4��.

					// �ʱ�ȭ.
					ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
					ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
					ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

					switch(skill_index)
					{
					case SKILL_PETRUDOLPH:			///��絹��
						ef_sort.nTargetType = 0; // ��絹�� ����. �� 4��.;			// [12/10/2007 parkmj] �絹�� ���� �ĺ� ��ȣ ����.
						break;

					case SKILL_PETRUDOLPH_BLACK:	///��絹��_����
						ef_sort.nTargetType = 1;
						break;

					case SKILL_PETRUDOLPH_BLUE:		///��絹��_�Ķ�
						ef_sort.nTargetType = 2;
						break;

					case SKILL_PETRUDOLPH_GREEN:	///��絹��_���
						ef_sort.nTargetType = 3;
						break;

					case SKILL_PETRUDOLPH_YELLOW:	///��絹��_���
						ef_sort.nTargetType = 4;
						break;

					case SKILL_PETRUDOLPH_KOR_PREMIUM: // [2008/11/3 Theodoric] ���� �����̾� ��ǰ
						ef_sort.nTargetType = 5;
						break;

					default:
						ef_sort.nTargetType = 0;
						break;
					}

					if( pCha )
					{
						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
						ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else // ����. ���ִ� �͵� �������� ��Ŷ�� �޾Ƽ� ���־��Ѵ�.(���� ���� �� ��..)
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}
				break;

			case SKILL_ARUPAKA_PET:
			case SKILL_ARUPAKA_PET_BE:
			case SKILL_ARUPAKA_PET_BR:
				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW;		// ����ٴϴ� ����Ʈ��
					ef_sort.Index = 6;				// ����ī��
					ef_sort.subNum = skill_index;	// ����ī ����. �� 3��.

					// �ʱ�ȭ.
					ef_sort.num = 20;				// ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.vSortPos.x = 0.0f;		// ���Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.0f;		// ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
					ef_sort.vSortPos.z = 0.0f;		// ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
					ef_sort.dwColor = timeGetTime();// �ִϸ��̼� ����� ���� �ð����� ���.

					switch(skill_index)
					{
					case SKILL_ARUPAKA_PET:			///����ī��
						ef_sort.nTargetType = 0; // ����ī�� ����. �� 3��.;
						break;
					case SKILL_ARUPAKA_PET_BE:
						ef_sort.nTargetType = 1;
						break;
					case SKILL_ARUPAKA_PET_BR:
						ef_sort.nTargetType = 2;
						break;
					default:
						ef_sort.nTargetType = 0;
						break;
					}

					if( pCha )
					{
						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
						ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else // ����. ���ִ� �͵� �������� ��Ŷ�� �޾Ƽ� ���־��Ѵ�.(���� ���� �� ��..)
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}
				break;

			case SKILL_PET_CATS_BLACK:
			case SKILL_PET_CATS_WHITE:
			case SKILL_PET_CATS_MIX:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_CATS; // ������.
						ef_sort.subNum = skill_index; // ������ ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

						switch(skill_index)
						{
						case SKILL_PET_CATS_BLACK:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_CATS_WHITE:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_CATS_MIX:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_RABBIT_GOLD:
			case SKILL_PET_RABBIT_MIX:
			case SKILL_PET_RABBIT_WHITE:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW;
						ef_sort.Index = FX_FOLLOW_TYPE_RABBIT;
						ef_sort.subNum = skill_index;

						ef_sort.num = 0;
						ef_sort.vSortPos.x = 0.0f;
						ef_sort.vSortPos.y = 0.0f;
						ef_sort.vSortPos.z = 0.0f;
						ef_sort.dwColor = timeGetTime();

						switch(skill_index)
						{
						case SKILL_PET_RABBIT_GOLD:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_RABBIT_MIX:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_RABBIT_WHITE:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_ZORO_BLACK:
			case SKILL_PET_ZORO_WHITE:
			case SKILL_PET_ZORO_GREEN:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_ZORO; // ������.
						ef_sort.subNum = skill_index; // ������ ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

						switch(skill_index)
						{
						case SKILL_PET_ZORO_BLACK:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_ZORO_WHITE:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_ZORO_GREEN:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_DOGS_SOLID:
			case SKILL_PET_DOGS_WHITE:
			case SKILL_PET_DOGS_BLACK_WHITE:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_DOGS; // ������.
						ef_sort.subNum = skill_index; // ������ ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

						switch(skill_index)
						{
						case SKILL_PET_DOGS_SOLID:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_DOGS_WHITE:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_DOGS_BLACK_WHITE:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_VALO_BLACK:
			case SKILL_PET_VALO_WHITE:
			case SKILL_PET_VALO_GREEN:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_VALO; // ������.
						ef_sort.subNum = skill_index; // ������ ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

						switch(skill_index)
						{
						case SKILL_PET_VALO_BLACK:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_VALO_WHITE:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_VALO_GREEN:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_BEAR_BLACK:
			case SKILL_PET_BEAR_WHITE:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_BEAR; // ��
						ef_sort.subNum = skill_index; // ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.

						switch(skill_index)
						{
						case SKILL_PET_BEAR_BLACK:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_BEAR_WHITE:
							ef_sort.nTargetType = 1;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_HORSE_BLUE:
			case SKILL_PET_HORSE_RED:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_HORSE; // ��
						ef_sort.subNum = skill_index; // ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.
						switch(skill_index)
						{
						case SKILL_PET_HORSE_BLUE:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_HORSE_RED:
							ef_sort.nTargetType = 1;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}						

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_JEGUAR_1:
			case SKILL_PET_JEGUAR_2:
			case SKILL_PET_JEGUAR_3:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW; // ����ٴϴ� ����Ʈ��
						ef_sort.Index = FX_FOLLOW_TYPE_JEGUAR; // ��
						ef_sort.subNum = skill_index; // ����. �� 4��.

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.
						switch(skill_index)
						{
						case SKILL_PET_JEGUAR_1:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_JEGUAR_2:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_JEGUAR_3:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}						

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_PET_BONI_1:
			case SKILL_PET_BONI_2:
			case SKILL_PET_BONI_3:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							break;
						}

						EffectSort ef_sort;
						ef_sort.nType = FX_FOLLOW;
						ef_sort.Index = FX_FOLLOW_TYPE_BONI;
						ef_sort.subNum = skill_index;

						// �ʱ�ȭ.
						ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
						ef_sort.vSortPos.x = 0.0f; // ���Ⱚ���� ���.
						ef_sort.vSortPos.y = 0.0f; // ������ ������ ���.(������ ����Ʈ�� ������ �����ϱ� ���� �̰ɷ� ���)
						ef_sort.vSortPos.z = 0.0f; // ȸ�� Ÿ�̹��� ���� Ÿ�� �÷��׷� ���. (FrameMove���� ElapseTick�� �������Ѽ� ����Ѵ�.)
						ef_sort.dwColor = timeGetTime(); // �ִϸ��̼� ����� ���� �ð����� ���.
						switch(skill_index)
						{
						case SKILL_PET_BONI_1:
							ef_sort.nTargetType = 0;
							break;

						case SKILL_PET_BONI_2:
							ef_sort.nTargetType = 1;
							break;

						case SKILL_PET_BONI_3:
							ef_sort.nTargetType = 2;
							break;

						default:
							ef_sort.nTargetType = 0;
							break;
						}						

						if( pCha )
						{
							ef_sort.pNkChaFrom = pCha;
							ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + RandomNum( -10.0f, 10.0f ); // �ʱ� ��ġ
							ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz +RandomNum( -10.0f, 10.0f ); // �����͸� �߽����� �� ���� ��ǥ�ӿ� ����.
							ef_sort.vCurPos.y = m_pLand->GetHFHeight(ef_sort.vCurPos.x, ef_sort.vCurPos.z);

							pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						}
					}
					else
					{
						EffectSort *TempEffect = NULL;
						TempEffect = pCha->FindMyFairy( skill_index );
						if( TempEffect )
						{
							pCha->DeleteEffectNum( TempEffect->nNum );
							pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
						}
					}
				}
				break;

			case SKILL_RING_LIGHT_WHITE:
			case SKILL_RING_LIGHT_DARK:
			case SKILL_RING_LIGHT_RED:
			case SKILL_RING_LIGHT_BLUE:
			case SKILL_RING_LIGHT_GREEN:

			case SKILL_RING_LIGHT_GOLD:
				if( nSkill_OnOff == 1 )
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						break;
					}

					EffectSort ef_sort;
					ef_sort.nType = FX_FOLLOW;
					ef_sort.Index = 5;

					// �ʱ�ȭ.
					ef_sort.num = 0; // ���°�(�Ǵ� �ִϸ��̼�)���� ���.(0�� ������.)
					ef_sort.vSortPos.x = 4.0f; // ũ�Ⱚ���� ���.
					ef_sort.vSortPos.y = 0.06f; // �ӵ������� ���.
					ef_sort.nCurFrame = timeGetTime();
					ef_sort.nTargetType = skill_index; // ����Ʈ �÷��� ���� ��ҷ� ���.

					// ���� ������ ����Ʈ ����.
					list<D3DVECTOR> *TraceInfoList;
					TraceInfoList = new (list<D3DVECTOR>);
					ef_sort.effects = TraceInfoList; // �� ����Ʈ ���� ��ƼŬ �޸��ּҸ� ���.

					if( pCha && pCha->GetBiped() )
					{
						int actNum = 24;
						int ignoreActNum = 2;
						D3DVECTOR vTemp;

						if( pCha->GetBiped()->m_AnimCount == 21 )
						{
							vTemp = D3DVECTOR( pCha->GetBiped()->m_AniMat[actNum].m_Mats[pCha->Get_m_CurFrame()/ignoreActNum]._41,
											   pCha->GetBiped()->m_AniMat[actNum].m_Mats[pCha->Get_m_CurFrame()/ignoreActNum]._42,
											   pCha->GetBiped()->m_AniMat[actNum].m_Mats[pCha->Get_m_CurFrame()/ignoreActNum]._43 );
						}
						else
						{
							vTemp = D3DVECTOR( pCha->GetBiped()->m_AniMat[actNum].m_Mats[pCha->Get_m_CurFrame()]._41,
											   pCha->GetBiped()->m_AniMat[actNum].m_Mats[pCha->Get_m_CurFrame()]._42,
											   pCha->GetBiped()->m_AniMat[actNum].m_Mats[pCha->Get_m_CurFrame()]._43 );
						}

						ef_sort.pNkChaFrom = pCha;
						ef_sort.vCurPos.x = ef_sort.pNkChaFrom->m_wx + vTemp.x;
						ef_sort.vCurPos.y = ef_sort.pNkChaFrom->m_wy + vTemp.y;
						ef_sort.vCurPos.z = ef_sort.pNkChaFrom->m_wz + vTemp.z;

						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
					}
				}
				else
				{
					EffectSort *TempEffect = NULL;
					TempEffect = pCha->FindMyFairy( skill_index );
					if( TempEffect )
					{
						pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
						pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
					}
				}

				break;

			case SKILL_LV400_GREEN:
			case SKILL_LV400_BULE:
			case SKILL_LV400_RED:
				{
					pCha->DeleteEffectNum(pCha->GetLv400Effect());
					pCMyApp->m_pFxSet->DeleteEffect(pCha->GetLv400Effect());
					pCha->SetLv400Effect(-1);

					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ZeroMemory(&ef_sort, sizeof(EffectSort));
						ef_sort.nNum = skill_index;


						switch(skill_index)
						{
						case SKILL_LV400_GREEN:
							ef_sort.nType = FX_LV400_EFFECT_GREEN;
							break;
						case SKILL_LV400_BULE:
							ef_sort.nType = FX_LV450_EFFECT_BLUE;
							break;
						case SKILL_LV400_RED:
							ef_sort.nType = FX_LV500_EFFECT_RED;
							break;
						}
						ef_sort.num			= 0;
						ef_sort.nCurFrame	= 0;
						ef_sort.pNkChaTo	= pCha;
						int eff_index = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
						pCha->InsertEffectNum(eff_index);
						pCha->SetLv400Effect(eff_index);
					}
				}
				break;

			case PEROM_SKILL_S134:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ZeroMemory(&ef_sort, sizeof(EffectSort));
						ef_sort.nType = FX_PEROM_SKILL_S134;
						ef_sort.pNkChaFrom = pCha;
						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						pCMyApp->StopHero();
						pCha->SetMotionState(LHCha_Action__Perom_S10);
						pCha->SetActiveField();

						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1920,-1);
					}
					else
					{
						pCha->SetDeactiveField();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1921,-1);
					}
					break;
				}
				break;
			case PEROM_SKILL_S139:
				{
					if( nSkill_OnOff == 1 )
					{
						pCha->SetActiveDSystem();

						EffectSort ef_sort;
						ZeroMemory(&ef_sort, sizeof(EffectSort));
						ef_sort.nType = FX_PEROM_SKILL_S139;
						ef_sort.pNkChaFrom = pCha;
						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));

						pCMyApp->StopHero();
						pCha->SetMotionState(LHCha_Action__Perom_S15);

						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1922,-1);
					}
					else
					{
						pCha->SetDeactiveDSystem();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1923,-1);

						if( pCha->IsActiveField_Ex() )
						{
							pCha->SetDeactiveField_Ex();
							if( pCha == g_pRoh )
								g_pNk2DFrame->AddChatStr(IDS_LHSTRING1929,-1);
						}
					}

					if( pCha == g_pRoh )
						g_pRoh->SetDefense();
				}
				break;
			case PEROM_SKILL_S141:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ef_sort.nType = FX_PEROM_SKILL_S141;
						ef_sort.pNkChaFrom = pCha;
						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						pCMyApp->StopHero();
						pCha->SetMotionState(LHCha_Action__Perom_S10);
					}
				}
				break;
			case PEROM_SKILL_S148:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ef_sort.nType = FX_PEROM_SKILL_S148;
						ef_sort.pNkChaFrom = pCha;
						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						pCMyApp->StopHero();
						pCha->SetMotionState(LHCha_Action__Perom_S10);
						pCha->SetActiveCritical();

						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1924,-1);
					}
					else
					{
						pCha->SetDeactiveCritical();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1925,-1);
					}
				}
				break;
			case PEROM_SKILL_S149:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ef_sort.nType = FX_PEROM_SKILL_S149;
						ef_sort.pNkChaFrom = pCha;
						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						pCMyApp->StopHero();
						pCha->SetMotionState(LHCha_Action__Perom_S10);

						pCha->SetActiveEngage();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1926,-1);
					}
					else
					{
						pCha->SetDeactiveEngage();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1927,-1);
					}
				}
				break;
			case PEROM_SKILL_S150:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ef_sort.nType = FX_PEROM_SKILL_S150;
						ef_sort.pNkChaFrom = pCha;
						pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
						pCMyApp->StopHero();
						pCha->SetMotionState(LHCha_Action__Perom_S10);

						pCha->SetActiveField_Ex();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1928,-1);
					}
					else
					{
						pCha->SetDeactiveField_Ex();
						if( pCha == g_pRoh )
							g_pNk2DFrame->AddChatStr(IDS_LHSTRING1929,-1);
					}
				}
				break;
			case PEROM_SKILL_S125:
			case PEROM_SKILL_S126:
			case PEROM_SKILL_S127:
			case PEROM_SKILL_S128:
			case PEROM_SKILL_S129:
			case PEROM_SKILL_S130:
			case PEROM_SKILL_S131:
			case PEROM_SKILL_S132:
			case PEROM_SKILL_S133:
			case PEROM_SKILL_S135:
			case PEROM_SKILL_S136:
			case PEROM_SKILL_S137:
			case PEROM_SKILL_S138:
			case PEROM_SKILL_S142:
			case PEROM_SKILL_S143:
			case PEROM_SKILL_S144:
			case PEROM_SKILL_S145:
			case PEROM_SKILL_S146:
			case PEROM_SKILL_S147:
				{
					if( nSkill_OnOff == 1 )
					{
						EffectSort ef_sort;
						ZeroMemory(&ef_sort, sizeof(EffectSort));
						ef_sort.nNum = skill_index;
						ef_sort.num			= 0;
						ef_sort.nCurFrame	= 0;
						ef_sort.pNkChaTo	= pCha;
						int eff_index = pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
						pCha->InsertEffectNum(eff_index);
					}
				}
				break;

			default:
				//////2003 �ٸ� ĳ���Ͱ� ȭ�鿡 �������� ���ӽ�ų ����.
				if(nSkill_OnOff==0)
					skill_index=0;
				pCha->SetInSkill(skill_index);//��ų�� ���ִ°�...��ų��ȣ
				break;
			}
		}
		else
			OutputDebugString("SkillOnOff()���� ĳ���� ã�� ���߽��ϴ�.");
	}
	else	// nate 2005-11-14 : ������ - npc�� ������ ������
	{
		pMob = FindMobById(index);
		if( pMob )
		{
			switch( skill_index )
			{
			case SKILL_K_POISON:
				pMob->m_bPoisoning = nSkill_OnOff;
				break;
			}
		}
		else
			OutputDebugString("SkillOnOff()���� ���� ã�� ���߽��ϴ�.");
	}
	// npc�� ��쿡�� ���� �ش������ ����.
}


//////////////////////////////////////////////////////////////////////////////////
// ShowDroppedName()
// - alt �� ����ÿ� Ȱ��ȭ�ȴ�.
//////////////////////////////////////////////////////////////////////////////////
void CUIMgr::ShowDroppedItemName(CItemInfo *pItemInfo)
{
	if (pItemInfo)
	{
		CalNamePos(pItemInfo, pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_BoundVert[5].y, pItemInfo->m_Item.m_Z, 2);
		//CalNamePos2(pItem->m_X, pItem->m_BoundVert[5].y, pItem->m_Z, 2, m_DropItemAllCnt);
		if(!pItemInfo->m_bActive)
			pItemInfo->m_TextOutBox.Draw();
		else
			pItemInfo->m_TextOutBox_Active.Draw();
	}
}

// --------------------------------------------------------------------------------------------------
//					��ǰâ ���� �Լ���..


#define TIME_MAIN_FRAME   60000
#define TIME_ANGEL_FRAME  80
#define TIME_BOX_FRAME    75
#define TIME_TEXT_FRAME   1

#define CUR_MODE_640		0
#define CUR_MODE_800		1
#define CUR_MODE_1024		2

void CUIMgr::CmdEvent(char *msg)
{
	if(m_bF11) // f11�� ���ȴ�..
		return;

	char strMsg[256];

	strcpy(strMsg, msg);

	// �޼��� ť�� �˻��Ѵ�
	if(check_queue() == 0 )  // ť�� �ƹ������� ����...
	{
		put(strMsg);
		CreAllFromMsg(strMsg);
	}
	else // �޼���ť�� �̹� ������ �ִٸ� put���۸��Ѵ�
		put(strMsg);
}

// Event Test
void CUIMgr::CmdEventtt(char *msg)
{
	if(m_bF11) // f11�� ���ȴ�..
		return;

	char strMsg[256];

	strcpy(strMsg, msg);
	// IDS_UIMGR_REALTIME_SYSTEM : �ǽð� �̺�Ʈ �߰� �ý����Դϴ�.
	strcat(strMsg, G_STRING(IDS_UIMGR_REALTIME_SYSTEM));

	// �޼��� ť�� �˻��Ѵ�
	if(check_queue() == 0 )  // ť�� �ƹ������� ����...
	{
		put(strMsg);
		CreAllFromMsg(strMsg);
	}
	else // �޼���ť�� �̹� ������ �ִٸ� put���۸��Ѵ�
		put(strMsg);

}

// -------------------------------------------------------------------
// Name : CreAllFromMsg()
// Desc : ��ǰ����â  �����κ�..
// ------------------------------------------------------------------
void CUIMgr::CreAllFromMsg(char* msg)
{
	int i, font_size;
	char tmp[MAX_PRESENT_BOX][100];
	char tmp2[MAX_ANGEL_CNT][100];

	RECT ClientRc;
	m_hWnd =  g_pDisplay->GetHWnd();
	GetClientRect(m_hWnd, &ClientRc);
	m_ScreenWidth = ClientRc.right;
	m_ScreenHeight = ClientRc.bottom;


	DeleteAllPresent();


	font_size = 16;
	m_iCurMode = CUR_MODE_800;
	m_iMainXpos  = 80;
	m_iMainYpos = 0;
	for(i=0; i<MAX_PRESENT_BOX; i++)
	{
		sprintf(tmp[i], "interface/event/present_box%d.bmp", i);
		g_pDisplay->CreateSurfaceFromBitmap(&m_pPresentBox[i], tmp[i]);
		m_pPresentBox[i]->SetColorKey(RGB(255, 0, 255));
	}
	for(i=0; i<MAX_ANGEL_CNT; i++)
	{
		sprintf(tmp2[i], "interface/event/angel%d.bmp", i);
		g_pDisplay->CreateSurfaceFromBitmap(&m_pAngel[i], tmp2[i]);
		m_pAngel[i]->SetColorKey(RGB(255, 0, 255));
	}

	m_pPresentText = new CTextOutBox();
	m_pPresentText->Init(font_size, RGB(0, 255, 0),0, 0);
	m_pPresentText->SetString(msg);

	m_iStartX = m_iMainXpos+187;
	m_iStartY = m_iMainYpos+10;

	m_bShowPresentBox = TRUE;
	m_BoxFrameCnt = m_AngelFrameCnt = 0;
	m_iTextFFrameCnt =  m_iTextEFrameCnt = 0;
	m_MainTime = m_AngelTime = m_BoxTime = m_TextTime = timeGetTime();
	m_bAngelSta = FALSE;
	m_bAngelAniActive = m_bShowAngel    = true;
	m_iCnt      = 0;


	// ������ ��..����ְ�..
	if (g_pDSound)
		g_pDSound->Play(g_EffectSound[EFF_SND_CONGR]);

}





// -------------------------------------------------------------------
// Name : DeleteAllPresent()
// Desc : ��ǰ����â  �޸�����
// ------------------------------------------------------------------

void CUIMgr::DeleteAllPresent()
{
	for(int i=0; i<MAX_PRESENT_BOX; i++)
		SAFE_DELETE(m_pPresentBox[i]);
	for(int i=0; i<MAX_ANGEL_CNT; i++)
		SAFE_DELETE(m_pAngel[i]);

	SAFE_DELETE(m_pPresentText);

	m_bShowPresentBox = FALSE;

}



// -------------------------------------------------------------------
// Name : ShowAllPresent()
// Desc : ��ǰ����â  ��ºκ�
// ------------------------------------------------------------------
void CUIMgr::DrawAllPresent()
{

	if(!m_bShowPresentBox || m_bF11)
		return;

	int ret;
	DWORD curTime = timeGetTime();

	if(curTime - m_MainTime >= TIME_MAIN_FRAME)
	{

		// ���� Ÿ���� �����Ͽ���.. �˻��غ���
		ret = check_queue();
		if(ret == 0)  // ť�� �ƹ��͵� �������
		{

			return;
		}
		else if(ret == 1)  // �Ѱ��� �޼����� �����Ұ�� ���..�����ش�..
		{
		}
		else                // �ΰ� �̻��� ���
		{

			DeleteAllPresent();
			get();				// ���� ���Դ� �޼����ϳ���  ť���� �����Ѵ�.
			CreAllFromMsg(GetFirstMsg());	// �ٽ� ������ �����ش�
			return;
		}
		m_bAngelAniActive = false;
	}

	if(m_bAngelAniActive)
	{
		if (curTime - m_BoxTime >= TIME_BOX_FRAME)
		{
			m_BoxFrameCnt++;
			if(m_BoxFrameCnt>=MAX_PRESENT_BOX) m_BoxFrameCnt=0;
			m_BoxTime = curTime;
		}
	}
	else
		m_BoxFrameCnt=0;


	ShowAngel();
	if(m_bShowAngel == FALSE)
	{
		m_iMainXpos	= g_pNk2DFrame->GetControlBottom()->m_pBottom->Xpos + 293;
		m_iMainYpos	= g_pNk2DFrame->GetControlBottom()->m_pBottom->Ypos - 20;
		m_iMainYpos -= 35;


		RenderOj(m_iMainXpos+20, m_iMainYpos+10, 181, 30);
		g_pDisplay->Blt(m_iMainXpos, m_iMainYpos, m_pPresentBox[m_BoxFrameCnt]);
		ShowPresentText();
		//g_pDisplay->Blt(ptDraw.x, ptDraw.y, m_pAngel[m_AngelFrameCnt]);


	}
}

// -------------------------------------------------------------------
// Name : ShowAngel(int, int)
// Desc : õ�� ���ϸ��̼� ��� ��ƾ
// ------------------------------------------------------------------
void CUIMgr::ShowAngel()
{
	if(!m_bShowAngel)
		return;

	DWORD curTime = timeGetTime();
	if (curTime - m_AngelTime >= TIME_ANGEL_FRAME)
	{

		if(m_bAngelSta == FALSE)
			m_AngelFrameCnt++;
		else
			m_AngelFrameCnt--;

		if(m_AngelFrameCnt>=MAX_ANGEL_CNT-1 || m_AngelFrameCnt <= 0)
		{
			m_bAngelSta == TRUE ? m_bAngelSta = 0 : m_bAngelSta = 1;
			m_iCnt++;
		}

		m_AngelTime = curTime;
		if(m_iCnt >2) // ���ϸ޼��� 2���� ������..(�ι� �Դ�..����..�Ѵ��� �������)
			m_bShowAngel = false;
	}

	m_iMainXpos	= g_pNk2DFrame->GetControlBottom()->m_pBottom->Xpos + 293;
	m_iMainYpos	= g_pNk2DFrame->GetControlBottom()->m_pBottom->Ypos - 20;
	m_iMainYpos -= 35;


	g_pDisplay->Blt(m_iMainXpos, m_iMainYpos, m_pAngel[m_AngelFrameCnt]);
}



// -------------------------------------------------------------------
// Name : ShowAngel(int, int)
// Desc : �޼��� ��� ��ƾ
// ------------------------------------------------------------------
void CUIMgr::ShowPresentText()
{
	RECT rc;

	DWORD curTime = timeGetTime();
	if (curTime - m_TextTime >= TIME_TEXT_FRAME)
	{
		m_iStartX-=2;
		m_iTextEFrameCnt+=2;
		m_TextTime = curTime;

		if(m_iStartX <= m_iMainXpos+30)
			m_iTextFFrameCnt+=2;
	}

	if(m_iTextEFrameCnt >= m_pPresentText->m_Width)
		m_iTextEFrameCnt = m_pPresentText->m_Width;

	if(m_iStartX <= m_iMainXpos+30)
		m_iStartX = m_iMainXpos+30;

	if(m_iTextEFrameCnt <= m_iTextFFrameCnt)
	{
		m_iTextFFrameCnt = 0 ;
		m_iTextEFrameCnt = 0 ;
		m_iStartX = m_iMainXpos+187;
		m_iStartY = m_iMainYpos+10;

		if(m_iCurMode == CUR_MODE_1024)
		{
			m_iStartX = m_iMainXpos+293;
			m_iStartY = m_iMainYpos+10;
		}
		return;
	}

	SetRect(&rc, m_iTextFFrameCnt, 0, m_iTextEFrameCnt, 16);


	m_pPresentText->Draw(rc, m_iStartX, m_iStartY+10);
}





//-----------------------------------------------------------------
// name : RenderOj
// desc : ������ ��� ��� ��ƾ
//-----------------------------------------------------------------

extern int g_EffectTextr[];

void CUIMgr::RenderOj(int xpos, int ypos, int cx, int cy)
{

	//xpos = X1, ypos = Y1; // TextSur�� ��ġ�� ���� ��� ��ġ�� ���� �Ѵ�
	LPDIRECTDRAWSURFACE7 lpTexture = NULL;

	D3DMATRIX matWorld, matView, matProjOld, matProjNew;
	//D3DVECTOR vEyePt, vLookatPt, vUpVec;
	D3DVIEWPORT7 vpOld, vpNew;

	DWORD	dwColor;

	// ������ ����Ʈ�� �����ϰ� ���Ӱ� ����Ʈ�� �����Ѵ�.
	GET_D3DDEVICE()->GetViewport(&vpOld);
	vpNew = vpOld;
	vpNew.dwWidth  = m_ScreenWidth;
	vpNew.dwHeight = m_ScreenHeight;
	GET_D3DDEVICE()->SetViewport(&vpNew);

	//// �������� ��Ʈ���� ����.
	float fAspect = (float) ((double) vpNew.dwHeight / (double) vpNew.dwWidth);
	GET_D3DDEVICE()->GetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProjOld);
	D3DUtil_SetProjectionMatrix(matProjNew, 1.0f, fAspect, 1.0f, 2000.0f );
	GET_D3DDEVICE()->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProjNew);

	TLVec[0] = D3DTLVERTEX(D3DVECTOR(xpos,    ypos,      0), 1, 0x00ffffff, 0, 0, 0);
	TLVec[1] = D3DTLVERTEX(D3DVECTOR(xpos+cx, ypos,     0), 1, 0x00ffffff, 0, 1, 0);
	TLVec[2] = D3DTLVERTEX(D3DVECTOR(xpos,    ypos+cy,  0), 1, 0x00ffffff, 0, 0, 1);
	TLVec[3] = D3DTLVERTEX(D3DVECTOR(xpos+cx, ypos+cy,  0), 1, 0x00ffffff, 0, 1, 1);


	// ������
	GET_D3DDEVICE()->GetRenderState(D3DRENDERSTATE_AMBIENT, &dwColor );
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_AMBIENT, 0x00FFFFFF);
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_LIGHTING, FALSE);

	//--------------�׸��� ���� / �� --------------
	if( SUCCEEDED( GET_D3DDEVICE()->BeginScene() ) )
	{
		//---------------------TLVERTEX �� �̿��� ������ ���(ȭ���� ���� ��ǥ�� �Է��Ѵ�)

		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE   , TRUE);
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE   , FALSE);

		lpTexture = g_pCapsyongTexture->GetSurfaceByIdx(g_EffectTextr[EFF_TEXTR_BLACK]);


		GET_D3DDEVICE()->SetTexture(0, lpTexture);

		//GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
		GET_D3DDEVICE()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, TLVec, 4, 0);
		//GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
		//GET_D3DDEVICE()->SetTexture(0, NULL);
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE   , FALSE);

		GET_D3DDEVICE()->EndScene();
	}

	// ���󺹱�.
	GET_D3DDEVICE()->SetViewport(&vpOld);
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_AMBIENT, dwColor );
	GET_D3DDEVICE()->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProjOld);
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_LIGHTING, TRUE);
}




//--------------------------------------------------------------------------------
// name : init_queue()
// desc : ť�� �ʱ�ȭ �Ѵ�
//--------------------------------------------------------------------------------

void CUIMgr::init_queue()
{
	head  = new dnode;
	tail  = new dnode;

	head->prev = head;
	head->next = tail;
	tail->prev = head;
	tail->next = tail;
	head->str = NULL;
	tail->str = NULL;
}


//--------------------------------------------------------------------------------
// name : put(int k)
// desc : ���ڷ� �־��� k�� ���� ������ ��带 ����� ������ �տ� �����ϸ�ȴ�
// ���ο� ��带 �����Ҷ� �޸� �Ҵ� ������ �߻��ϴ��� �˻��Ѵ�
//--------------------------------------------------------------------------------

void CUIMgr::put(char* msg)
{
	dnode* t = NULL;

	t = new  dnode;
	t->str = new char[strlen(msg)+2];

	strcpy(t->str, msg);

	tail->prev->next = t; // ������ ������� �������� tail �� �ƴ� t�� ���Եȴ�
	tail->prev = t; // ������ �� ���� t
	t->next = tail; // t�� ���� ���� �׻� �����̴�
}


//--------------------------------------------------------------------------------
// name : get()
// desc : get ������ �켱 ť�� ����ִ����� Ȯ���Ͽ� ������� ������
// �Ӹ��� ���� ��带 �����Ѵ�.
// ť�� ����ִ��� Ȯ���Ϸ��� �Ӹ��� ������尡 ���� �������
// (head->next == tail) Ȯ���ϸ�ȴ�
//--------------------------------------------------------------------------------
BOOL CUIMgr::get()
{
	dnode* t; // �˻��� ����

	t = head->next; // �Ӹ��� ���� ���

	if(t == tail)  // ť�� ����ִٸ� Underflow ���� ó���� �Ѵ�
	{
		return FALSE;
	}

	head->next = t->next; // �Ӹ��� ���� ��带 ����
	t->next->prev = head;

	delete t->str;
	t->str = NULL;

	delete t;
	t = NULL;

	return TRUE;
}


//--------------------------------------------------------------------------------
// name : clear_queue()
// desc : �����ϴ� ��� ����Ʈ�� �����Ѵ�
//
//--------------------------------------------------------------------------------

void CUIMgr::clear_queue()
{
	dnode* t; // �˻���
	dnode* s; // ������

	t = head->next;

	while(t != tail)
	{
		s = t;
		t = t->next;
		delete s->str;
		s->str = NULL;

		delete s;
		s = NULL;
	}

	head->next = tail;
	tail->prev = head;
	head->str = NULL;
	tail->str = NULL;
}


//--------------------------------------------------------------------------------
// name : delete_queue_ptr()
// desc : �����ͷ� ����� queue ������ �޷θ� ����
//--------------------------------------------------------------------------------
void CUIMgr::delete_queue_ptr()
{
	clear_queue();

	if(head)
	{
		//delete head->str;
		//head->str = NULL;

		delete head;
		head = NULL;
	}
	if(tail)
	{
		//delete tail->str;
		//tail->str = NULL;

		delete tail;
		tail = NULL;
	}
}


//--------------------------------------------------------------------------------
// name : check_queue()
// desc : ť�� ������ �ִ°�??
//--------------------------------------------------------------------------------

int CUIMgr::check_queue()
{
	int count = 0;
	dnode* t;
	t = head->next;

	while(t != tail)
	{
		count++;
		t = t->next;
		//return t->str;
	}
	return count;
}


char* CUIMgr::GetFirstMsg()
{
	dnode*t;
	t=head->next;
	while(t != tail)
	{
		return t->str;
	}
	return NULL;
}

void CUIMgr::OnBattle(int nOnBattle)
{
	int i;

	if (nOnBattle == 1)
	{
		m_bOnBattle = TRUE;
		g_bPath = TRUE;
//===========================================
		// nate 2004 - 4
		// CastleWar
		if( pCMyApp->m_nCurWorldIdx == WORLD_FIELD )
		{
			// ��ȣž �̿ܿ� ������ ������� ������Ʈ���� ���� �̵��Ұ��� Ǯ���ش�.(by ����) //DEC_TOWER
			DecardiCastleWarLandAttr( 0, TRUE );
			DecardiCastleWarLandAttr( 2, TRUE );
			DecardiCastleWarLandAttr( 4, TRUE );
			DecardiCastleWarLandAttr( 6, TRUE );

			// ��ī���� ���� ����
			// ���� ��庯ȯ����
			m_byOnBattleDecardi = 1;

			//==============================
			// nate 2004 - 6
			// ���� ��Ÿ ���� �ٴ� �׸���
			if( !m_pNamPlane )
				m_pNamPlane = new CRectPlane;
			m_pNamPlane->Create( 17.0f, 17.0f, FALSE );
			//==============================

			// ���� �� �Ӽ�ó�� ///07-01-31
			if( g_dwClientCountry == CTRY_BRA ) // �ϴ� ����� ��û�̹Ƿ� ������� ����ó���� ����.
			{
				pCMyApp->GetLandPtr()->SetFieldAttr( 6000, 6730, 6050, 6740, FALSE); // FALSE �� ��������.
			}
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_GUILD )
		{
//===========================================
			// ITS #9596 ���Ϸ� ������������ ���� ���� by.Sol9 [2012.06.15]
			// ��ī���� ���� ���� ���� ���� ���
			// ���� ��庯ȯ����
			m_byOnBattleDecardi = 1;

			// nate 2004 - 6 : ��ī���� ���� ����, ��Ÿ ������ �ٴ� �׸���
			SAFE_DELETE(m_pNamPlane);
			for (i=0; i < 4; i++)
			{
				pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_top_left_x[i], guild_castle_top_left_z[i],
													guild_castle_top_right_x[i], guild_castle_top_right_z[i], FALSE);
			}
			// 07-08-16 ������ ����� �Ӽ� �״�� �ΰ� ����.(������ �ӿ� ���� ����� ���ٰ� ��.)
//			for (i=0; i < 4; i++) {
//				pCMyApp->GetLandPtr()->SetFieldAttr(guild_control_left_x[i], guild_control_left_z[i],
//					guild_control_right_x[i], guild_control_right_z[i], TRUE );
//			}
		}
		else if( pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN )
		{
			m_byOnBattleDecardi = 1;

			// nate 2004 - 6 : ��ī���� ���� ����, ��Ÿ ������ �ٴ� �׸���
			SAFE_DELETE(m_pNamPlane);
			// �� ����������..
			for (i = 0; i < 8; i++)
			{
				pCMyApp->GetLandPtr()->SetFieldAttr(whitehorn_outsidedoor_left_x[i], whitehorn_outsidedoor_bottom_z[i],
													whitehorn_outsidedoor_right_x[i], whitehorn_outsidedoor_top_z[i], FALSE);
			}
			// ũ����Ż ��������..
			pCMyApp->GetLandPtr()->SetFieldAttr(crystal_tower_left_x, crystal_tower_bottom_z,
												crystal_tower_right_x, crystal_tower_top_z, TRUE);
			// �ּ��� ����������...
			pCMyApp->GetLandPtr()->SetFieldAttr(whitehorn_castle_gate_left_x, whitehorn_castle_gate_bottom_z,
												whitehorn_castle_gate_right_x, whitehorn_castle_gate_top_z, FALSE);
			// 07-08-16 ������ ����� �Ӽ� �״�� �ΰ� ����.(������ �ӿ� ���� ����� ���ٰ� ��.)
			// ����� ��������...
//			for (i=0; i < 4; i++)
//			{
//				pCMyApp->GetLandPtr()->SetFieldAttr(whitehorn_control_left_x[i], whitehorn_control_left_z[i],
//					whitehorn_control_right_x[i], whitehorn_control_right_z[i], TRUE);
//			}
		}
		else
		{
			// nate 2004 - 6 : ��ī���� ���� ����, ��Ÿ ������ �ٴ� �׸���
			SAFE_DELETE(m_pNamPlane);
		}
	}
	else
	{
//=======================================
		// nate 2004 - 5
		// ��ī���� ���� ����
		// ���׸�� ����
		// ITS #9596 ���Ϸ� ������������ ���� ���� by.Sol9 [2012.06.15]
		m_byOnBattleDecardi = 0;

		if( pCMyApp->GetCurWorld() == WORLD_FIELD ||
				pCMyApp->GetCurWorld() == WORLD_GUILD ||
				pCMyApp->GetCurWorld() == WORLD_WHITEHORN )
		{
			if( g_pRoh->m_bCrystalOwner )
				g_pRoh->m_bRun = TRUE;

			// ���� �� �Ӽ�ó�� ///07-01-31
			if( g_dwClientCountry == CTRY_BRA ) // �ϴ� ����� ��û�̹Ƿ� ������� ����ó���� ����.
			{
				pCMyApp->GetLandPtr()->SetFieldAttr( 6000, 6730, 6050, 6740, TRUE ); // TRUE �� ������.
			}
		}
//=======================================
		// nate 2004 - 6 : ��ī���� ���� ����, ��Ÿ ������ �ٴ� �׸���
		SAFE_DELETE(m_pNamPlane);

		if (m_bOnBattle == TRUE)
		{
			pCMyApp->GetPath()->ClearAll();
			g_pRoh->m_bCrystalOwner = FALSE;
			g_pRoh->m_bCrystalGuild = FALSE;
		}
		m_bOnBattle = FALSE;

		if (!m_bOnTeamBattle)
			g_bPath = FALSE;
		if (pCMyApp->m_nCurWorldIdx == WORLD_GUILD)
		{
			for (i=0; i < 4; i++)
			{
				pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_top_left_x[i], guild_castle_top_left_z[i],
													guild_castle_top_right_x[i], guild_castle_top_right_z[i], FALSE);
			}
			for (i=0; i < 4; i++)
			{
				pCMyApp->GetLandPtr()->SetFieldAttr(guild_control_left_x[i], guild_control_left_z[i],
													guild_control_right_x[i], guild_control_right_z[i], FALSE);
			}
		}
		else if (pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN)
		{
			// �� ��������...
			for (i = 0; i < 8; i++)
			{
				pCMyApp->GetLandPtr()->SetFieldAttr(whitehorn_outsidedoor_left_x[i], whitehorn_outsidedoor_bottom_z[i],
													whitehorn_outsidedoor_right_x[i], whitehorn_outsidedoor_top_z[i], TRUE);
			}
			// ũ����Ż ����������...
			pCMyApp->GetLandPtr()->SetFieldAttr(crystal_tower_left_x, crystal_tower_bottom_z,
												crystal_tower_right_x, crystal_tower_top_z, FALSE);
			// �ּ��� ��������...�Ѥ�
			pCMyApp->GetLandPtr()->SetFieldAttr(whitehorn_castle_gate_left_x, whitehorn_castle_gate_bottom_z,
												whitehorn_castle_gate_right_x, whitehorn_castle_gate_top_z, TRUE);
			// ����� ����������...
			for (i=0; i < 4; i++)
			{
				pCMyApp->GetLandPtr()->SetFieldAttr(whitehorn_control_left_x[i], whitehorn_control_left_z[i],
													whitehorn_control_right_x[i], whitehorn_control_right_z[i], FALSE);
			}
		}

//===========================================
		// nate 2004 - 4
		// CastleWar
		// ��ȣž ����Ҽ� �ְ�
		if( pCMyApp->m_nCurWorldIdx == WORLD_FIELD )
		{
			// ������ �������� ��(��ȣž ���)�� ����(ũ����Ż Ÿ�� ��ġ)�� �̵� ���ϰ� �����ش�. //DEC_TOWER
			DecardiCastleWarLandAttr( 0, FALSE );
			DecardiCastleWarLandAttr( 1, FALSE );
			DecardiCastleWarLandAttr( 2, FALSE );
			DecardiCastleWarLandAttr( 3, FALSE );
			DecardiCastleWarLandAttr( 4, FALSE );
			DecardiCastleWarLandAttr( 5, FALSE );
			DecardiCastleWarLandAttr( 6, FALSE );
			DecardiCastleWarLandAttr( 7, FALSE );
			DecardiCastleWarLandAttr( 8, TRUE ); // ������ �����ش�.
		}
//===========================================

	}
	/*strcpy(m_MasterGuild, master_guild);
	strcpy(m_MasterGuild2, master_guild2);
	m_MasterZone = master_zone;
	m_MasterZone2 = master_zone2;*/
}

// ���ʹ�.
/*float guild_castle_door1_min_x = 3153.0f;
float guild_castle_door1_max_x = 3205.0f;
float guild_castle_door1_min_z = 9653.0f;
float guild_castle_door1_max_z = 9722.0f;*/
float guild_castle_door1_min_x = 3141.0f;
float guild_castle_door1_max_x = 3218.0f;
float guild_castle_door1_min_z = 9653.0f;
float guild_castle_door1_max_z = 9722.0f;

//�����ʹ�.
/*float guild_castle_door2_min_x = 3153.0f;
float guild_castle_door2_max_x = 3205.0f;
float guild_castle_door2_min_z = 8555.0f;
float guild_castle_door2_max_z = 8625.0f;*/
float guild_castle_door2_min_x = 3143.0f;
float guild_castle_door2_max_x = 3215.0f;
float guild_castle_door2_min_z = 8555.0f;
float guild_castle_door2_max_z = 8625.0f;

float guild_castle_north_right[] = {3253, 10000, 3275, 10110};
float guild_castle_north_left[] = {3075, 10000, 3100, 10110};
float guild_castle_south_right[] = {3253, 8136, 3289, 8300};
float guild_castle_south_left[] = {3054, 8136, 3089, 8300};

void CUIMgr::OpenCastle(int nState)
{
	if (pCMyApp->GetCurWorld() == WORLD_GUILD)
	{
		if (nState == 0)
		{
			// ���� ��
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door1_min_x, guild_castle_door1_min_z,
												guild_castle_door1_max_x, guild_castle_door1_max_z, FALSE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door2_min_x, guild_castle_door2_min_z,
												guild_castle_door2_max_x, guild_castle_door2_max_z, FALSE);

			// ���� �ٸ�����Ʈ
			/*pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_right[0], guild_castle_north_right[1],
				guild_castle_north_right[2], guild_castle_north_right[3], FALSE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_left[0], guild_castle_north_left[1],
				guild_castle_north_left[2], guild_castle_north_left[3], FALSE);

			// ���� �ٸ�����Ʈ
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_right[0], guild_castle_south_right[1],
				guild_castle_south_right[2], guild_castle_south_right[3], FALSE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_left[0], guild_castle_south_left[1],
				guild_castle_south_left[2], guild_castle_south_left[3], FALSE);*/

			m_nCastleDoorState = nState;
		}
		else if (nState == 1)
		{
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door1_min_x, guild_castle_door1_min_z,
												guild_castle_door1_max_x, guild_castle_door1_max_z, TRUE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door2_min_x, guild_castle_door2_min_z,
												guild_castle_door2_max_x, guild_castle_door2_max_z, FALSE);

			// ���� �ٸ�����Ʈ
			/*pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_right[0], guild_castle_north_right[1],
				guild_castle_north_right[2], guild_castle_north_right[3], TRUE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_left[0], guild_castle_north_left[1],
				guild_castle_north_left[2], guild_castle_north_left[3], TRUE);

			// ���� �ٸ�����Ʈ
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_right[0], guild_castle_south_right[1],
				guild_castle_south_right[2], guild_castle_south_right[3], FALSE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_left[0], guild_castle_south_left[1],
				guild_castle_south_left[2], guild_castle_south_left[3], FALSE);*/

			m_nCastleDoorState = nState;
		}
		else if (nState == 2)
		{
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door1_min_x, guild_castle_door1_min_z,
												guild_castle_door1_max_x, guild_castle_door1_max_z, FALSE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door2_min_x, guild_castle_door2_min_z,
												guild_castle_door2_max_x, guild_castle_door2_max_z, TRUE);

			// ���� �ٸ�����Ʈ
			/*pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_right[0], guild_castle_north_right[1],
				guild_castle_north_right[2], guild_castle_north_right[3], FALSE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_left[0], guild_castle_north_left[1],
				guild_castle_north_left[2], guild_castle_north_left[3], FALSE);

			// ���� �ٸ�����Ʈ
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_right[0], guild_castle_south_right[1],
				guild_castle_south_right[2], guild_castle_south_right[3], TRUE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_left[0], guild_castle_south_left[1],
				guild_castle_south_left[2], guild_castle_south_left[3], TRUE);*/

			m_nCastleDoorState = nState;
		}
		else if (nState == 3)
		{
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door1_min_x, guild_castle_door1_min_z,
												guild_castle_door1_max_x, guild_castle_door1_max_z, TRUE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door2_min_x, guild_castle_door2_min_z,
												guild_castle_door2_max_x, guild_castle_door2_max_z, TRUE);

			// ���� �ٸ�����Ʈ
			/*pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_right[0], guild_castle_north_right[1],
				guild_castle_north_right[2], guild_castle_north_right[3], TRUE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_north_left[0], guild_castle_north_left[1],
				guild_castle_north_left[2], guild_castle_north_left[3], TRUE);

			// ���� �ٸ�����Ʈ
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_right[0], guild_castle_south_right[1],
				guild_castle_south_right[2], guild_castle_south_right[3], TRUE);
			pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_south_left[0], guild_castle_south_left[1],
				guild_castle_south_left[2], guild_castle_south_left[3], TRUE);*/

			m_nCastleDoorState = nState;
		}
	}
}

void CUIMgr::CloseCastle()
{
	//if (pCMyApp->GetCurWorld() == WORLD_GUILD) {
	//	pCMyApp->GetLandPtr()->SetFieldAttr(guild_castle_door_min_x, guild_castle_door_min_z,
	//		guild_castle_door_max_x, guild_castle_door_max_z, FALSE);
	//}
	//m_bCastleOpened = FALSE;
}

//wan:2004-12
//whitehorn Dungeon
//������ ��ǥ �Ӽ�
float whiteDungeon_bossDoor_left_x = 3920;
float whiteDungeon_bossDoor_right_x = 4030;
float whiteDungeon_bossDoor_top_z = 4660;
float whiteDungeon_bossDoor_bottom_z = 4630;

// nate 2004 - 11
// ���Ϸ� ��ȣž�ֺ� �Ӽ� ����
// ȭ��Ʈȥ �ܼ��� �Ӽ�����
void CUIMgr::OpenDoor( int nZone, int* nState )
{
	int i;
	if( nZone == 7 )
	{
		for( i = 0; i < 8 ; i ++ )
		{
			g_OutsideDoorOpen[ i ] = nState[ i ];
			// �� ��������...
			if( g_OutsideDoorOpen[ i ] )
			{
				pCMyApp->GetLandPtr()->SetFieldAttr( whitehorn_outsidedoor_left_x[ i ], whitehorn_outsidedoor_bottom_z[ i ],
													 whitehorn_outsidedoor_right_x[ i ], whitehorn_outsidedoor_top_z[ i ],
													 TRUE );
			}
		}
	}
	else if( nZone == 3 )
	{
		for( i = 0 ; i < 4 ; i ++ )
		{
			if( nState[ i ] )
			{
				pCMyApp->GetLandPtr()->SetFieldAttr( guild_castle_top_left_x[ i ], guild_castle_top_left_z[ i ],
													 guild_castle_top_right_x[ i ], guild_castle_top_right_z[ i ],
													 TRUE );
			}
		}
	}
//wan:2004-12
//Whitehorn Dungeon
//������ �Ӽ� ����
//SetFieldAttr(float fMinX, float fMinZ, float fMaxX, float fMaxZ, BOOL bPass)
	else if( nZone == 8 )
	{
		if( nState[0] )  //����
		{
			m_bBossGateClosedRender = FALSE;
			pCMyApp->GetLandPtr()->SetFieldAttr( whiteDungeon_bossDoor_left_x, whiteDungeon_bossDoor_bottom_z,
												 whiteDungeon_bossDoor_right_x, whiteDungeon_bossDoor_top_z,TRUE );
		}
		else  //����
		{
			m_bBossGateClosedRender = TRUE;
			pCMyApp->GetLandPtr()->SetFieldAttr( whiteDungeon_bossDoor_left_x, whiteDungeon_bossDoor_bottom_z,
												 whiteDungeon_bossDoor_right_x, whiteDungeon_bossDoor_top_z,FALSE );
		}
	}
	else if( nZone == 0 ) // ��ī���� ��ȣž ó�� (by ����) //DEC_TOWER
	{
		int j = 0;

		for( i = 0; i < 4 ; i ++ ) // ��ȣž 4���� ó��.
		{
			j = (i*2)+1; // ����� �� ���Ŀ� �°� ���� �Ǿ������� ���߿� ���� �߰��Ǹ� Ʋ�������� ������ ����.

			DecardiCastleWarLandAttr( j, (nState[i]?FALSE:TRUE) ); // 0�̸� �̵�����, 1�̸� �̵��Ұ�
		}

	}
}

void CUIMgr::BattleCount(int nSec)
{
	if (!m_pWarInfo)
	{
		m_pWarInfo = new CWarInfo;
		m_pWarInfo->FontInit();

		RECT ClientRc;
		GetClientRect(g_pDisplay->GetHWnd(), &ClientRc);
		m_pWarInfo->LoadRes(ClientRc.right, ClientRc.bottom);
	}

	m_pWarInfo->SetBattleCount(nSec);
}

// nate 2005-03-11
// Matrix
void CUIMgr::MatTimeCount( int nHawklawPoint, int nCoolrainPoint, int nShiberPoint, int nBattleTime )
{
	if( !m_pWarInfo )
	{
		m_pWarInfo = new CWarInfo;
		m_pWarInfo->FontInit();

		RECT ClientRc;
		GetClientRect(g_pDisplay->GetHWnd(), &ClientRc);
		m_pWarInfo->LoadRes(ClientRc.right, ClientRc.bottom);
	}
	m_nGuildPoint[0] = (int) nHawklawPoint / 100;
	m_nGuildPoint[1] = (int) nCoolrainPoint / 100;
	m_nGuildPoint[2] = (int) nShiberPoint / 100;

	m_pWarInfo->SetMatWarInfo( nHawklawPoint, nCoolrainPoint, nShiberPoint, nBattleTime );
}


void CUIMgr::MatTimeCount( int nGuild1, int nGuild2, int nBattleTime )
{
	if( !m_pWarInfo )
	{
		m_pWarInfo = new CWarInfo;
		m_pWarInfo->FontInit();

		RECT ClientRc;
		GetClientRect(g_pDisplay->GetHWnd(), &ClientRc);
		m_pWarInfo->LoadRes(ClientRc.right, ClientRc.bottom);
	}

	m_nGuildPoint[0] = nGuild1 / 100;
	m_nGuildPoint[1] = nGuild2 / 100;
	m_nGuildPoint[2] = 0;

	m_pWarInfo->SetMatWar2009Info( nGuild1, nGuild2, nBattleTime );
}


void CUIMgr::MatBattlePoint(int nBattlePoint)
{
	if( !m_pWarInfo )
	{
		m_pWarInfo = new CWarInfo;
		m_pWarInfo->FontInit();

		RECT ClientRc;
		GetClientRect(g_pDisplay->GetHWnd(), &ClientRc);
		m_pWarInfo->LoadRes(ClientRc.right, ClientRc.bottom);

	}
	m_pWarInfo->SetMatBattlePoint( nBattlePoint);
}


void CUIMgr::TimeCount(char *guild_name, char *owner_name, int nOwnerSec, char *first_guild_name, int nFirstSec, float owner_x, float owner_z, int point)
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;

//==========================================================================================
	// nate 2004 - 5
	// ũ����Ż ������ ��ġ Ȯ��
	((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_nCristalOwnerX = owner_x;
	((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_nCristalOwnerZ = owner_z;
//==========================================================================================

	// time_count ī��Ʈ�� ����������.
	// ũ����Ż ���� �ʱ�ȭ.
	if (strlen(guild_name) == 0)
	{
		g_pRoh->m_bCrystalOwner = FALSE;
		g_pRoh->m_bCrystalGuild = FALSE;
//============================================
		// nate 2004 - 4
		// CastleWar
		// ������ ���϶�����
		if( m_bOnBattle == TRUE )
		{
			if( pCMyApp->m_nCurWorldIdx == WORLD_GUILD )
			{
				// IDS_UIMGR_CRISTAL_MOVE_MASTERROOM : ���Ϸ�ũ����Ż�� ���Ϸи����� ������ �̵��߽��ϴ�
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_CRISTAL_MOVE_MASTERROOM),4); ///070723 �Ϻ����׸���Ʈ ����
				g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_UIMGR_CRISTAL_MOVE_MASTERROOM));
			}
			else if( pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN )
			{
				// IDS_MOVE_CRYSTAL_CASTLE : ȭ��Ʈȥ ũ����Ż�� ���߾����� �̵��Ǿ����ϴ�.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_MOVE_CRYSTAL_CASTLE),4); ///070723 �Ϻ����׸���Ʈ ����
				g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_MOVE_CRYSTAL_CASTLE));
			}
			else if( pCMyApp->m_nCurWorldIdx == WORLD_FIELD )
			{
				// IDS_MOVE_CRYSTAL_DECARDI : ��ī���� ũ����Ż�� ���߾����� �̵��Ǿ����ϴ�.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_MOVE_CRYSTAL_DECARDI),4); ///070723 �Ϻ����׸���Ʈ ����
				g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_MOVE_CRYSTAL_DECARDI));
			}
		}
//============================================
	}

	// ������ ���� �ƴϸ� ����.
	if (!m_bOnBattle)
		return;

	if (!m_pWarInfo)
	{
		m_pWarInfo = new CWarInfo;
		m_pWarInfo->FontInit();

		RECT ClientRc;
		GetClientRect(g_pDisplay->GetHWnd(), &ClientRc);
		m_pWarInfo->LoadRes(ClientRc.right, ClientRc.bottom);
	}

	else
	{
		// ������������ ������ ���� �ִ� ����� ���� ���ֱ����� �ִ� ����.
		if (!strcmp(guild_name, "0"))
		{
			m_pWarInfo->SetWarInfo("", "", 0, first_guild_name, nFirstSec, owner_x, owner_z, point);
			return;
		}
		else
			m_pWarInfo->SetWarInfo(guild_name, owner_name, nOwnerSec, first_guild_name, nFirstSec, owner_x, owner_z, point);
	}

	// ���� owner�� �����ΰ� Ȯ���Ѵ�.
	// ���� ����ΰ� �ƴѰ� Ȯ���� �Ѵ�. �ڽ��� Ȯ���� �ʿ䰡 ����.
	if (!strcmp(g_pRoh->m_pstrName, owner_name))
	{
		g_pRoh->m_bCrystalOwner = TRUE;
//=====================================================
		// nate 2004 - 5
		// ��ī���� ���� ����
		// �ȱ� ��� ����
		// ITS #9596 ���Ϸ� ������������ ���� ���� by.Sol9 [2012.06.15]
		if( pCMyApp->GetCurWorld() == WORLD_FIELD ||
				pCMyApp->GetCurWorld() == WORLD_GUILD ||
				pCMyApp->GetCurWorld() == WORLD_WHITEHORN )
			g_pRoh->m_bRun = FALSE;

		g_pRoh->m_bCrystalGuild = TRUE;
	}
	else
	{
		if( pCMyApp->GetCurWorld() == WORLD_FIELD ||
				pCMyApp->GetCurWorld() == WORLD_WHITEHORN )
			g_pRoh->m_bRun = TRUE;
	}
//=====================================================

	// ��������ΰ� Ȯ���� �Ѵ�.
	if (g_pRoh->m_pstrGuildName)
	{
		if (!strcmp(g_pRoh->m_pstrGuildName, guild_name))
		{
			g_pRoh->m_bCrystalGuild = TRUE;
		}
		else
		{
			g_pRoh->m_bCrystalGuild = FALSE;
		}
	}
	else
	{
		g_pRoh->m_bCrystalGuild = FALSE;
	}

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;

		if (!strcmp(pCha->m_pstrName, owner_name))
			pCha->m_bCrystalOwner = TRUE;
		else
			pCha->m_bCrystalOwner = FALSE;

		if ( pCha->m_pstrGuildName && (!strcmp(pCha->m_pstrGuildName, guild_name)))
		{
			if (pCha->m_bMyGuild)
				pCha->m_bCrystalGuild = TRUE;
			else
				pCha->m_bOppGuild = TRUE;
		}
		else
		{
			pCha->m_bOppGuild = FALSE;
			pCha->m_bCrystalGuild = FALSE;
		}
	}

}

void CUIMgr::TimeCount_Flag(int flagType, char *owner_name, char *guild_name)
{
	//0 - ��	1 -	��	2 -	��	3 -	��

	CNkCharacter *pCha;
	LHCharacterMap_it pr;

	// time_count ī��Ʈ�� ����������.
	// ���� ��� ���� �ʱ�ȭ.
	//if (strlen(owner_name) == 0) {
	if (strcmp(owner_name, "NOFLAG") == 0)
	{
		g_pRoh->m_bFlagOwner[flagType] = FALSE;
		g_pRoh->m_bFlagGuild[flagType] = FALSE;
		// ������ ���϶�����
		if (m_bOnBattle == TRUE)
		{
			if (pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN)
			{
				if( flagType == 0 )
				{
					// IDS_MOVE_FLAG_N :���ʿܼ� ����� ���ڸ��� �̵��߽��ϴ�
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_MOVE_FLAG_N),4); ///070723 �Ϻ����׸���Ʈ ����
					g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_MOVE_FLAG_N));
				}
				else if( flagType == 1 )
				{
					// IDS_MOVE_FLAG_E : ���ʿܼ� ����� ���ڸ��� �̵��߽��ϴ�
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_MOVE_FLAG_E),4); ///070723 �Ϻ����׸���Ʈ ����
					g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_MOVE_FLAG_E));
				}
				else if( flagType == 2 )
				{
					// IDS_MOVE_FLAG_W : ���ʿܼ� ����� ���ڸ��� �̵��߽��ϴ�
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_MOVE_FLAG_W),4); ///070723 �Ϻ����׸���Ʈ ����
					g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_MOVE_FLAG_W));
				}
				else if( flagType == 3 )
				{
					// IDS_MOVE_FLAG_S : ���ʿܼ� ����� ���ڸ��� �̵��߽��ϴ�
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_MOVE_FLAG_S),4); ///070723 �Ϻ����׸���Ʈ ����
					g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_MOVE_FLAG_S));
				}
			}
		}
	}

	// ������ ���� �ƴϸ� ����.
	if (!m_bOnBattle)
		return;

	// ������������ ������ ���� �ִ� ����� ���� ���ֱ����� �ִ� ����.
	if (!strcmp(guild_name, "0"))
		return;

	// ���� owner�� �����ΰ� Ȯ���Ѵ�.
	// ���� ����ΰ� �ƴѰ� Ȯ���� �Ѵ�. �ڽ��� Ȯ���� �ʿ䰡 ����.
	if (!strcmp(g_pRoh->m_pstrName, owner_name))
	{
		g_pRoh->m_bFlagOwner[flagType] = TRUE;
	}
	else
	{
		g_pRoh->m_bFlagOwner[flagType] = FALSE;
	}

	// ��������ΰ� Ȯ���� �Ѵ�.
	if (g_pRoh->m_pstrGuildName)
	{
		if (!strcmp(g_pRoh->m_pstrGuildName, guild_name))
		{
			g_pRoh->m_bFlagGuild[flagType] = TRUE;
		}
		else
		{
			g_pRoh->m_bFlagGuild[flagType] = FALSE;
		}
	}
	else
	{
		g_pRoh->m_bFlagGuild[flagType] = FALSE;
	}

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;

		if (!strcmp(pCha->m_pstrName, owner_name))
		{
			pCha->m_bFlagOwner[flagType] = TRUE;

			// �Ϻ��� �䱸�� ���� �߰� : ������ �г�Ƽ - ũ����Ż �����ڴ� �ۼ� ���� �ϱ� ���� , 2007.11.12 �����
			// Ÿ �����鵵 �����ϰ� ���� by Sol9 [2012.06.01] // ???�̰ǹ���
			pCha->SetRunState( FALSE );
		}
		else
			pCha->m_bFlagOwner[flagType] = FALSE;

		if ( pCha->m_pstrGuildName && (!strcmp(pCha->m_pstrGuildName, guild_name)))
			pCha->m_bFlagGuild[flagType] = TRUE;
		else
			pCha->m_bFlagGuild[flagType] = FALSE;
	}

	if (!m_pWarInfo)
	{
		m_pWarInfo = new CWarInfo;
		m_pWarInfo->FontInit();

		RECT ClientRc;
		GetClientRect(g_pDisplay->GetHWnd(), &ClientRc);
		m_pWarInfo->LoadRes(ClientRc.right, ClientRc.bottom);
	}

	if( strcmp(owner_name, "NOFLAG") == 0 )
	{
		m_pWarInfo->SetWarInfo2(flagType, "****", "****");
	}
	else
		m_pWarInfo->SetWarInfo2(flagType, guild_name, owner_name);

}

void CUIMgr::DrawWarCastleInfo()
{
	if (m_bOnBattle && m_bWarInfo)
	{
		if (m_pWarInfo)
		{
			m_pWarInfo->Draw();
		}
	}
}

// �Ǽ��� �̵� üũ �� ���

void CUIMgr::RecalPath()
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;

	// �� Ŭ����.
	pCMyApp->GetPath()->ClearAll();

	if( g_bPath == FALSE || m_bOnBattle == FALSE )
		return;

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;
		if (!pCha->IsMoving() && !pCha->IsHidden() && !pCha->IsHiding())
		{
			pCMyApp->GetPath()->SetMapMovable(pCha->m_wx, pCha->m_wz, FALSE);
		}
	}
}

// ------------------------------------------------------------------------------------
// ��ǰ������ ���� ��ƾ.
// ------------------------------------------------------------------------------------
// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::Stash(int slot_num, int vnum, int plus, int special, int special2,
				   int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur , int count, int time_limit) ///�ð��������� �ð��� �߰�(050711 by ����) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetControlWareHouse()->Stash(slot_num, vnum, plus, special, special2,
			UpEndur, MaxUpdEndur, Endur, MaxEndur , count, time_limit); ///�Ź���ȭ�ý���
}

// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::StashTo(int slot_num, int vnum, int plus, int special, int special2,
					 int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur, int count, int swap_flagr) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetControlWareHouse()->StashTo(slot_num, vnum, plus, special, special2, UpEndur, MaxUpdEndur,
			Endur, MaxEndur, count, swap_flagr ); ///�Ź���ȭ�ý���
}

// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::StashFrom(int slot_num, int index, int vnum, int plus, int special, int special2,
					   int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur, int count) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetControlWareHouse()->StashFrom(slot_num, index, vnum, plus, special, special2,
			UpEndur, MaxUpdEndur, Endur, MaxEndur, count); ///�Ź���ȭ�ý���
}

// nate
// ������ �ٷ��̵� ����
void CUIMgr::StashPut( int nVnum, int nInvenPackNum, int mWarePackNum, int nWareSlotNum, int nInven_X, int nInven_Y )
{
	g_pNk2DFrame->GetControlWareHouse()->StashPut( nVnum, nInvenPackNum, mWarePackNum, nWareSlotNum, nInven_X, nInven_Y );
}

// nate
// ������ �ٷ��̵� ����
void CUIMgr::StashGet( int nVnum,  int nInvenPackNum,int mWarePackNum, int nWareSlotNum, int nItemIndex, int nInven_X, int nInven_Y )
{
	g_pNk2DFrame->GetControlWareHouse()->StashGet( nVnum, nInvenPackNum, mWarePackNum, nWareSlotNum, nItemIndex, nInven_X, nInven_Y );
}

void CUIMgr::StashEnd()
{
	g_pNk2DFrame->GetControlWareHouse()->StashEnd();
}

// [6/7/2007 Theodoric] ������ ���� :: �Լ� ���� �߰�
void CUIMgr::guild_Stash(int slot_num, int vnum, int plus, int special, int special2,
						 int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur, int count, int time_limit ) ///�ð��������� �ð��� �߰�(050711 by ����) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetControlGStorehouse()->Stash(slot_num, vnum, plus, special, special2,
			UpEndur, MaxUpdEndur, Endur, MaxEndur, count, time_limit ); ///�Ź���ȭ�ý���

}
// [6/7/2007 Theodoric] ������ ���� :: �Լ� ���� �߰�
void CUIMgr::guild_StashTo(int slot_num, int vnum, int plus, int special, int special2,
						   int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur, int count, int swap_flag) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetControlGStorehouse()->StashTo(slot_num, vnum, plus, special, special2,
			UpEndur, MaxUpdEndur, Endur, MaxEndur, count, swap_flag); ///�Ź���ȭ�ý���
}
// [6/7/2007 Theodoric] ������ ���� :: �Լ� ���� �߰�
void CUIMgr::guild_StashFrom(int slot_num, int index, int vnum, int plus, int special, int special2,
							 int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur, int count) ///�Ź���ȭ�ý���
{
	g_pNk2DFrame->GetControlGStorehouse()->StashFrom(slot_num, index, vnum, plus, special, special2,
			UpEndur, MaxUpdEndur, Endur, MaxEndur, count); ///�Ź���ȭ�ý���
}

// ������ �ٷ��̵� ����
void CUIMgr::guild_StashPut( int nVnum, int nInvenPackNum, int mWarePackNum, int nWareSlotNum, int nInven_X, int nInven_Y )
{
	g_pNk2DFrame->GetControlGStorehouse()->StashPut( nVnum, nInvenPackNum, mWarePackNum, nWareSlotNum, nInven_X, nInven_Y );
}

// ������ �ٷ��̵� ����
void CUIMgr::guild_StashGet( int nVnum,  int nInvenPackNum,int mWarePackNum, int nWareSlotNum, int nItemIndex, int nInven_X, int nInven_Y )
{
	g_pNk2DFrame->GetControlGStorehouse()->StashGet( nVnum, nInvenPackNum, mWarePackNum, nWareSlotNum, nItemIndex, nInven_X, nInven_Y );
}

void CUIMgr::guild_StashEnd()
{
	g_pNk2DFrame->GetControlGStorehouse()->StashEnd();
}

BOOL CUIMgr::IsInside_MouseDown_Itm_Namebox(int x, int y)
{
	CItemInfo *pItemInfo;
	LHItemInfoMap_it prItemInfo;

	BOOL bVisible = TRUE;
	size_t size = m_iteminfo_map.size();
	printf("%u\n", size );

	for (prItemInfo = m_iteminfo_map.begin(); prItemInfo != m_iteminfo_map.end(); prItemInfo++)
	{
		pItemInfo = (*prItemInfo).second;
		if( !pItemInfo )
			return false;

		if( m_bAlt )
		{
			if (m_pFrustum->FrustumCullPoint(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Y, pItemInfo->m_Item.m_Z, ITEM_SPEAR_SIZE) == VFCULL_OUTSIDE)
				bVisible = false;
			else
				bVisible = true;

			if (bVisible)
			{
				if(pItemInfo->m_bActive)
				{
					if( IsInvenLock() )
						return 1;

					sprintf(m_commOut, "pick %d\n", pItemInfo->m_Item.m_Index);
					// item�� ���ΰ����� �Ÿ��� ���Ͽ� ������ ��ɾ ������

					// �׷��� ������ �������� �ִ� ������ �̵��� �Ѵ�.
					if( abs(g_pRoh->m_wx - pItemInfo->m_Item.m_X) <= 13.0f && abs(g_pRoh->m_wz - pItemInfo->m_Item.m_Z) <= 13.0f )
						//if (DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z) <= 15.0f)
					{
						g_pTcpIp->SendNetMessage(m_commOut);
						// ��Ŷ�� ������ ���ÿ� pick�� �õ� �ߴٴ� �÷��׸� ����( by ���� )
						m_bPickLock = TRUE; ///pick_bug
					}
					else
					{
						m_bNextAction = TRUE;
						m_Action.nActionKind = 0;
						strcpy(m_Action.strCmd, m_commOut);
						if (g_bPath)
							pCMyApp->MoveHeroT(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z);
						else
							pCMyApp->MoveHero(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z);
					}
					return TRUE;
				}
			}
		}
		// Item Click
		if(pItemInfo->m_Item.m_wColorIdx == m_wColor)
		{
			// ��� Lock üũ �� Pick
			if(!pCMyApp->m_bEquipLock
					&& !pCMyApp->m_bRingLock)
			{
				if( IsInvenLock() )
					return 1;

				sprintf(m_commOut, "pick %d\n", pItemInfo->m_Item.m_Index);
			}
			// item�� ���ΰ����� �Ÿ��� ���Ͽ� ������ Picking
			float distX = abs(g_pRoh->m_wx - pItemInfo->m_Item.m_X);
			float distZ = abs(g_pRoh->m_wz - pItemInfo->m_Item.m_Z);
			if( abs(g_pRoh->m_wx - pItemInfo->m_Item.m_X) <= 13.0f && abs(g_pRoh->m_wz - pItemInfo->m_Item.m_Z) <= 13.0f )
				//if (DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z) <= 15.0f)
			{
				if( g_pTcpIp )
					g_pTcpIp->SendNetMessage(m_commOut);
				// ��Ŷ�� ������ ���ÿ� pick�� �õ� �ߴٴ� �÷��׸� ����( by ���� )
				m_bPickLock = TRUE; ///pick_bug
			}
			// �׷��� ������ �������� �ִ� ������ �̵��� �Ѵ�.
			else
			{
				m_bNextAction = TRUE;
				m_Action.nActionKind = 0;
				strcpy(m_Action.strCmd, m_commOut);

				if (g_bPath)
					pCMyApp->MoveHeroT(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z);
				else
					pCMyApp->MoveHero(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z);
			}
			return true;
		}
	}
	return false;
}



BOOL CUIMgr::IsInside_MouseMove_Itm_Namebox(int x, int y)
{
	int aa = 0;

	if(!m_bAlt)
	{
		return FALSE;
	}

	CItemInfo *pItemInfo;
	LHItemInfoMap_it prItemInfo;
	for (prItemInfo = m_iteminfo_map.begin(); prItemInfo != m_iteminfo_map.end(); prItemInfo++)
	{
		pItemInfo = (*prItemInfo).second;
		BOOL bVisible = TRUE;
		if (m_pFrustum->FrustumCullPoint(pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Y, pItemInfo->m_Item.m_Z, ITEM_SPEAR_SIZE) == VFCULL_OUTSIDE)
		{
			bVisible = FALSE;
		}
		if (bVisible && m_bAlt)
		{
			int ix, iy, icx, icy;
			ix = pItemInfo->m_TextOutBox.m_StringPosX;
			iy = pItemInfo->m_TextOutBox.m_StringPosY;
			icx = pItemInfo->m_TextOutBox.m_pSurf->GetWidth();
			icy = pItemInfo->m_TextOutBox.m_pSurf->GetHeight();

			if(x >= ix && x <= ix+icx && y >=iy && y <=iy+icy)
			{
				pItemInfo->m_bActive = TRUE;
				Except_All_False(aa);
				return TRUE;
			}
			else
			{
				pItemInfo->m_bActive = FALSE;
			}
		}
		aa++;
	}
	return FALSE;
}


void CUIMgr::Except_All_False(int val)
{
	int aa = 0;
	CItemInfo *pItemInfo;
	LHItemInfoMap_it prItemInfo;
	for (prItemInfo = m_iteminfo_map.begin(); prItemInfo != m_iteminfo_map.end(); prItemInfo++)
	{
		pItemInfo = (*prItemInfo).second;
		if(val != aa)
			pItemInfo->m_bActive = false;
		aa++;
	}
}

void CUIMgr::CheckCarnation(int state)
{

	if(state == _DELIV_OPEN)  // ��ȯâ�� �������
	{

		if (m_pDelivBox)
		{
			m_pDelivBox->m_iViewCnt = 3;
			m_pDelivBox->m_iStartViewCnt = 0;
			m_pDelivBox->m_iEndViewCnt = 3;
			m_pDelivBox->m_pBtn1->SetState(BTN_NORMAL);
			m_pDelivBox->m_pBtn2->SetState(BTN_NORMAL);
		}
		m_iCurDelivState = _DELIV_OPEN;

		g_pNk2DFrame->CloseAllWindow();
	}
	else if(state == _DELIV_FAIL)   // ��ȯ �����ϰ��
	{

		if (m_pDelivBox)
		{
			m_pDelivBox->m_iViewCnt = 4;
			m_pDelivBox->m_iStartViewCnt = 3;
			m_pDelivBox->m_iEndViewCnt = 7;
			m_pDelivBox->m_pBtn2->SetState(BTN_DISABLE);
		}
		g_pRoh->m_bExgLock = FALSE;
		m_iCurDelivState = _DELIV_FAIL;

		g_pNk2DFrame->CloseAllWindow();
	}
	else if(state == _DELIV_SUCCEED)  // ���������� ī���̼��� ��ȯ�� �Ȱ��
	{

		if (m_pDelivBox)
		{
			m_pDelivBox->m_iViewCnt = 4;
			m_pDelivBox->m_iStartViewCnt = 8;
			m_pDelivBox->m_iEndViewCnt = 12;
			m_pDelivBox->m_pBtn2->SetState(BTN_DISABLE);
		}
		g_pRoh->m_bExgLock = FALSE;
		m_iCurDelivState = _DELIV_SUCCEED;

		g_pNk2DFrame->CloseAllWindow();
	}
}

BOOL CUIMgr::CheckCarnationExist()
{
	CItem *pItem = g_pRoh->m_ExgInven;

	while (pItem)
	{
		if (pItem->m_Vnum == 560)
			return TRUE;
		else
			pItem = pItem->m_Next;
	}

	return FALSE;
}




BOOL CUIMgr::Save_Screen_Shot(HWND hWnd)
{
	DWORD dwFrameWidth    = GetSystemMetrics( SM_CXSIZEFRAME );
	DWORD dwFrameHeight   = GetSystemMetrics( SM_CYSIZEFRAME );
	DWORD dwMenuHeight    = GetSystemMetrics( SM_CYMENU );
	DWORD dwCaptionHeight = GetSystemMetrics( SM_CYCAPTION );

	// ���� ������ �����̸� �����.
	char path[1024];
	char *strPath = pCMyApp->GetExePath();
	_chdir(strPath);
	sprintf(path, "%s\\lag_shot\\", strPath);
	_mkdir(path);

	char date[180];
	char time[180];
	char fname[400];
	_strdate( date );
	date[2] = date[5] = '-';
	_strtime( time );
	time[2] = time[5] = ';';
	sprintf(fname, "(%s)%s.jpg", date, time);	

	char tmp[800];
	sprintf(tmp, "%s%s", path, fname);

	FILE* fp = NULL;
	fp = fopen(tmp, "rb");

	if(fp)
	{
		fclose(fp);

		int cnt = 0;
		char a[10];
		while(1)
		{
			fname[18] = '\0';
			sprintf(a, "_%d.jpg", cnt++);
			strcat(fname, a);
			sprintf(tmp, "%s%s", path, fname);
			if((fp = fopen(tmp, "rb")) != NULL)
			{
				fclose(fp);
				continue;
			}
			else
			{
				break;
			}
		}		
	}

	strcat(path, fname);

	CControlBottom* pBottom = g_pNk2DFrame->GetControlBottom();
	if( pBottom )
	{
		int year = (date[6]-'0')*10+(date[7]-'0'); 
		int month = (date[0]-'0')*10+(date[1]-'0'); 
		int day = (date[3]-'0')*10+(date[4]-'0');
		int hour = (time[0]-'0')*10+(time[1]-'0');
		int min = (time[3]-'0')*10+(time[4]-'0');
		int sec = (time[6]-'0')*10+(time[7]-'0');

		char buf[1024] = {0};
		sprintf(buf, G_STRING(IDS_SCREEN_SHOT_DESC), year, month, day, hour, min, sec, path);

		g_pNk2DFrame->AddChatStr(buf, -3);
		
		// �ι� ȣ���� �´� ���̴� ������ ����
		pCMyApp->ProcessNextFrame(pCMyApp->Get_hWnd());	// Render�� ����
		pCMyApp->ProcessNextFrame(pCMyApp->Get_hWnd());	// ShowFrame�� ����
	}

	if(g_bFFullMode)
	{
		dwCaptionHeight = dwMenuHeight = dwFrameHeight = dwFrameWidth = 0;
	}
	else if(!g_bFFullMode && !g_bAdmin)
	{
		dwCaptionHeight = 0;
	}

	HDC hDC=GetDC(hWnd);

	RECT rect;
	GetClientRect(hWnd, &rect);

	rect.right = rect.right+(dwFrameWidth*2);
	rect.bottom = rect.bottom+(dwFrameHeight*2)+dwMenuHeight+dwCaptionHeight;


	// ����ũž ��������� dc�� �̿��ؼ� hBitamp�� �����Ѵ�.
	// �� �ױ�� Ŭ���̾�Ʈ ��ü ����(Ŭ���̾�Ʈ + ��Ŭ���̾�Ʈ ����)
	HWND desk_hwnd = GetDesktopWindow();
	HDC desk_hdc=GetDC(desk_hwnd);
	HBITMAP hbitmap=CreateCompatibleBitmap(desk_hdc, rect.right, rect.bottom);


	RECT desk_rc;
	GetWindowRect(hWnd, &desk_rc);

	int cx, cy;

	cx = desk_rc.right - desk_rc.left;
	cy = desk_rc.bottom - desk_rc.top;

	HDC memdc=CreateCompatibleDC(desk_hdc);

	SelectObject(memdc, hbitmap);
	// �ҽ� ī�ǽÿ��� ����ũž�����쿡�� ���� Ŭ���̾�Ʈ�� ��ġ�� ���������� ���� ����.
	//BitBlt(memdc, 0, 0, rect.right, rect.bottom, desk_hdc, desk_rc.left, desk_rc.top, SRCCOPY);
	StretchBlt(memdc, 0, 0, rect.right, rect.bottom, desk_hdc, desk_rc.left, desk_rc.top, cx, cy, SRCCOPY);

	DeleteDC(memdc);


	if(HBITMAP hBitmap=(HBITMAP)hbitmap)
	{

		BITMAP  bm;
		int cx, cy;

		HDC hMemDC=CreateCompatibleDC(hDC);
		SelectObject(hMemDC, (HBITMAP)hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bm);


		cx = bm.bmWidth;
		cy = bm.bmHeight;

		//StretchBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, cx, cy, SRCCOPY);
		//BitBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDC, rect.left, rect.top, SRCCOPY);

		HGLOBAL hglb;
		unsigned char* lpbBuf;

		LPBITMAPFILEHEADER lpBmpfh;
		LPBITMAPINFO lpBi;
		LPBITMAPINFOHEADER lpBih;
		DWORD nHeader;
		DWORD nFSize;
		DWORD nLineBytes = cx * 3; //RGB: 3bytes

		nHeader = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		nFSize = nHeader + (nLineBytes * rect.bottom);

		hglb = GlobalAlloc(GPTR, nFSize);
		lpbBuf = (unsigned char*)GlobalLock(hglb);

		// Bitmap file header
		lpBmpfh = (LPBITMAPFILEHEADER)lpbBuf;
		lpBmpfh->bfType = 'MB';
		lpBmpfh->bfSize = nFSize;
		lpBmpfh->bfReserved1= 0;
		lpBmpfh->bfReserved2= 0;
		lpBmpfh->bfOffBits = nHeader;

		// Bitmap Information
		lpBi = (LPBITMAPINFO)(lpbBuf + sizeof(BITMAPFILEHEADER));
		lpBih = (LPBITMAPINFOHEADER)lpBi;
		lpBih->biSize = sizeof(BITMAPINFOHEADER);
		lpBih->biWidth = cx;
		lpBih->biHeight = cy;
		lpBih->biPlanes = 1;
		lpBih->biBitCount = 24;
		lpBih->biCompression= BI_RGB;
		lpBih->biSizeImage = 0;
		lpBih->biXPelsPerMeter = 0;
		lpBih->biYPelsPerMeter = 0;
		lpBih->biClrUsed = 0;
		lpBih->biClrImportant = 0;


		GetDIBits(hDC, (HBITMAP)hBitmap, 0, (DWORD)lpBih->biHeight,
				  lpBi->bmiColors, (LPBITMAPINFO)lpBi, (DWORD)DIB_RGB_COLORS);

		DeleteObject(hbitmap);// �̰� ������� �޸� ���� ���� �߻���..

		JPEG_CORE_PROPERTIES jcp;
		if(ijlInit(&jcp) != IJL_OK)
		{
			ijlFree(&jcp);
			GlobalUnlock(hglb);
			GlobalFree(hglb);
			DeleteDC(hMemDC);
			return FALSE;
		}

		long DIBLineSize = ((lpBih->biWidth)*3)/4*4;

		jcp.DIBChannels = 3;
		jcp.DIBColor = IJL_BGR;
		jcp.DIBHeight = -lpBih->biHeight; // ������ �ϴϱ� �������� �׸��� �ٽ� �������..
		jcp.DIBWidth = lpBih->biWidth;
		jcp.DIBPadBytes = DIBLineSize - lpBih->biWidth*3;

		jcp.JPGHeight = lpBih->biHeight;
		jcp.JPGWidth = lpBih->biWidth;
		jcp.jquality = 100;
		
		jcp.JPGFile = path;
		jcp.DIBBytes = (unsigned char*)lpbBuf+nHeader;

		if(ijlWrite(&jcp, IJL_JFILE_WRITEWHOLEIMAGE) != IJL_OK)
		{
			ijlFree(&jcp);
			GlobalUnlock(hglb);
			GlobalFree(hglb);
			DeleteDC(hMemDC);
			return FALSE;
		}
		ijlFree(&jcp);
		GlobalUnlock(hglb);
		GlobalFree(hglb);
		DeleteDC(hMemDC);
	}
	else
		return FALSE;

	ReleaseDC(hWnd, hDC);

	return TRUE;
}

void CUIMgr::GetServMsg_WarTax(int account, int rate)
{

	if(m_pWarTax)
	{
		m_pWarTax->GetMsg(account, rate);
	}
}

void CUIMgr::GetServMsg_WarReq(char* date, int time, int type)
{
	if(m_pWarReq)
	{
		m_pWarReq->GetMsg(date, time, type);
	}
}

BOOL CUIMgr::IsMasterGuild()
{
	if ((g_pRoh->m_pstrGuildName))
	{
//==============================================
		// nate 2004 - 4
		// CastleWar
		if( m_MasterGuild1 && !strcmp(g_pRoh->m_pstrGuildName, m_MasterGuild1 ) )
//==============================================
			return TRUE;
		/*if (m_MasterGuild2 && !strcmp(g_pRoh->m_pstrGuildName, m_MasterGuild2))
			return TRUE;*/
	}

	/*if (!strcmp(g_pRoh->m_pstrGuildName, "��")) {
		if (!strcmp("�ˢ�", m_MasterGuild))
			return TRUE;
	}*/
	return FALSE;
}
BOOL CUIMgr::IsSubGuild(int m_nFlag)//��:0 ��:1 ��:2 ��:3 �ܼ��� üũ
{
	if ((g_pRoh->m_pstrGuildName))
	{
		if (m_nFlag>3 || (m_SubGuild[m_nFlag] && !strcmp(g_pRoh->m_pstrGuildName, m_SubGuild[m_nFlag])) )
			return TRUE;
	}
	return FALSE;
}

void CUIMgr::CmdSetKeepInfo(char *Name, int KeepMode, int level, int health, int loyalty, int hunger, int pay, int time)
{
	if(m_bIsPetKeep)
		m_bIsPetKeep = FALSE;
	else m_bIsPetKeep = TRUE;

	if(m_bIsPetKeep)
	{
		if(m_pPetKeep)
		{
			delete m_pPetKeep;
			m_pPetKeep = NULL;
		}
		m_pPetKeep = new CControlPetKeep();
		m_pPetKeep->LoadRes();
		m_pPetKeep->SetKeepInfo(Name, KeepMode, level, health, loyalty, hunger, pay, time);
	}
	return;
}

void CUIMgr::CmdErrorMsg(char *Name)
{
	g_pNk2DFrame->InsertPopup(Name, TYPE_NOR_OK, 1 );
	return;
}

void CUIMgr::CmdLoadZonePos()
{
	if(m_bIsTeleportItem)
		m_bIsTeleportItem = FALSE;
	else
	{
		g_pNk2DFrame->CloseAllWindow();
		m_bIsTeleportItem = TRUE;
	}

	if(m_bIsTeleportItem)
	{
		if(m_pTeleportItem)
		{
			delete m_pTeleportItem;
			m_pTeleportItem = NULL;
		}
		m_pTeleportItem = new CControlTeleportItem();
		m_pTeleportItem->LoadRes(m_iQuickSlotNum);
	}
	else // �������� �������̽��� ����...(by ����)
	{
		if(m_pTeleportItem)  // �������̽� ��ü�� �����ִٸ�...
		{
			delete m_pTeleportItem; // �����ش�.
			m_pTeleportItem = NULL;
		}
	}
	return;
}


////////////////////////////////////////////////////////////////////////////////
// �����

// -----------------------------------------------------------------------------
void CUIMgr::GuildWarStaus(int nStatus, char *strTeamName, char *strBossName, char *strMoney, char *strHead)
{
	if(!m_bIsGuildWar)
	{
		m_bIsGuildWar = TRUE;
		if(m_pGuildWar)
		{
			delete m_pGuildWar;
			m_pGuildWar = NULL;
		}
		m_pGuildWar = new CGuildWar(nStatus);

	}
	if (m_pGuildWar)
	{
		if (nStatus == 3)
		{
			m_bIsGuildWar = FALSE;
			SAFE_DELETE(m_pGuildWar);
			// IDS_UIMGR_GWAR_ALREADY : �ٸ� ������� ��û���Դϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_UIMGR_GWAR_ALREADY),TYPE_NOR_OK, 1);
		}
		else
		{
			m_pGuildWar->GetMsg(nStatus, strTeamName, strBossName, strMoney, strHead);
		}

	}
}

void CUIMgr::GWarCancel(int nCause)
{
	char buf[100];
	char name[30];  // ��û�� ���

	char name2[30]; // ��û���� ���

	BOOL bName = FALSE;
	if(m_pGuildWar)
	{
		if(m_pGuildWar->m_pTextIn[2])
		{
			bName = TRUE;
		}
	}

	if(bName)
	{
		strcpy(name, m_pGuildWar->m_pTextIn[0]->GetString());
		strcpy(name2, m_pGuildWar->m_pTextIn[2]->GetString());
	}
	else
	{
		// IDS_UIMGR_GWAR_REQ : ��û�� ��
		strcpy(name, G_STRING(IDS_UIMGR_GWAR_REQ));
		// IDS_UIMGR_GWAR_REQ2 : ��û�� ����
		strcpy(name2, G_STRING(IDS_UIMGR_GWAR_REQ2));
	}

	if (nCause == 0)
		// IDS_UIMGR_GWAR_CONNECT_CLOSE : ������ ���� �����ϴ�.
		g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_UIMGR_GWAR_CONNECT_CLOSE),TYPE_NOR_OK, 1);
	else if (nCause == 1)
	{
		// IDS_UIMGR_GWAR_CANCEL : [%s]���� ��Ҹ� �Ͽ����ϴ�
		sprintf(buf, G_STRING(IDS_UIMGR_GWAR_CANCEL), name);
		g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);
	}
	else if (nCause == 2)
	{
		// IDS_UIMGR_GWAR_CANCEL : [%s]���� ��Ҹ� �Ͽ����ϴ�
		sprintf(buf, G_STRING(IDS_UIMGR_GWAR_CANCEL), name2);
		g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);
	}
}

void CUIMgr::GWarNotify(char *strNotify)
{
	char buf[100];
	char name[30];
	BOOL bName = FALSE;

	CNkCharacter *pNkCha;
	LHCharacterMap_it pr;

	if(m_pGuildWar)
	{
		if(m_pGuildWar->m_pTextIn[2])
		{
			bName = TRUE;
		}
	}

	if(bName)
		strcpy(name, m_pGuildWar->m_pTextIn[2]->GetString());
	else
		// IDS_UIMGR_GWAR_OTHER : ����
		strcpy(name, G_STRING(IDS_UIMGR_GWAR_OTHER));


	if (!strcmp(strNotify, "ok"))
	{
		// IDS_UIMGR_GWAR_AGREE_BATTLE : ����Ʋ���� �����Ǿ����ϴ�.
		sprintf(buf, G_STRING(IDS_UIMGR_GWAR_AGREE_BATTLE), name);
		g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);

		// �� ��� �κ�. Ȯ��ġ �ʾƼ� g_war start �κп��� ����.
		g_bPath = TRUE;

		if(m_bShowScore)
		{
			m_pTextScoreA->SetString("0");
			m_pTextScoreB->SetString("0");
		}
	}
	else if (!strcmp(strNotify, "already"))
	{
		// IDS_UIMGR_GWAR_ALREADY_REQ : [%s]���� �̹� �ٸ� ���� ��û���Դϴ�.
		sprintf(buf, G_STRING(IDS_UIMGR_GWAR_ALREADY_REQ), name);
		g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);
	}
	else if (!strcmp(strNotify, "non_exist"))
	{
		// IDS_UIMGR_GWAR_NOTEXIST : [%s]���� �������� �ʽ��ϴ�.
		sprintf(buf, G_STRING(IDS_UIMGR_GWAR_NOTEXIST), name);
		g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);
	}
	else if (!strcmp(strNotify, "end"))
	{
		// IDS_UIMGR_GWAR_END : ����Ʋ�� ����Ǿ����ϴ�
		sprintf(buf, G_STRING(IDS_UIMGR_GWAR_END));
		g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);

		// ������� �÷��׸� ���� �ٲپ� �ش�.
		for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
		{
			pNkCha = (*pr).second;
			pNkCha->m_nTeamMemGrade = TEAM_BATTLE_NONE;
		}

		// ���� �÷��׵� �ٲپ� �ش�.
		g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_NONE;

		// ��� �κ�..
		m_bOnTeamBattle = FALSE;
		g_bPath = FALSE;
	}
	else if (!strcmp(strNotify, "start"))
	{
		m_bOnTeamBattle = TRUE;
		g_bPath = TRUE;
	}
}

void CUIMgr::CreateScore()
{
	SAFE_DELETE(m_pBack_Score);
	SAFE_DELETE(m_pTextScoreA);
	SAFE_DELETE(m_pTextScoreB);
	SAFE_DELETE(m_pTextTeamNameA);
	SAFE_DELETE(m_pTextTeamNameB);

	RECT ClientRc;
	m_hWnd =  g_pDisplay->GetHWnd();
	GetClientRect(m_hWnd, &ClientRc);
	m_ScreenWidth = ClientRc.right;
	m_ScreenHeight = ClientRc.bottom;

	m_pBack_Score		=  NULL;
	g_pDisplay->CreateSurfaceFromBitmap(&m_pBack_Score, "interface/guildwar/score.bmp");
	m_pBack_Score->SetColorKey(RGB(255, 0, 255));


	m_pTextScoreA = NULL;
	m_pTextScoreA = new CTextOutBox();
	m_pTextScoreA->Init(16, _FCOLOR_YELLOW, 0, 0);
	m_pTextScoreA->SetString("0");


	m_pTextScoreB = NULL;
	m_pTextScoreB = new CTextOutBox();
	m_pTextScoreB->Init(16, _FCOLOR_YELLOW, 0, 0);
	m_pTextScoreB->SetString("0");
	//�� �̸� ����
	m_pTextTeamNameA = NULL;
	m_pTextTeamNameA = new CTextOutBox();
	m_pTextTeamNameA->Init(16, RGB(255,0,0), 0, 0);
	m_pTextTeamNameA->SetString("");

	m_pTextTeamNameB = NULL;
	m_pTextTeamNameB = new CTextOutBox();
	m_pTextTeamNameB->Init(16, RGB(0,0,255), 0, 0);
	m_pTextTeamNameB->SetString("");
	m_bShowScore = TRUE;
}

void CUIMgr::DestroyScore()
{
	SAFE_DELETE(m_pBack_Score);
	SAFE_DELETE(m_pTextScoreA);
	SAFE_DELETE(m_pTextScoreB);
	SAFE_DELETE(m_pTextTeamNameA);
	SAFE_DELETE(m_pTextTeamNameB);

	m_bShowScore = FALSE;
}


void CUIMgr::ShowScore()
{
	int mode = g_pNk2DFrame->GetControlBottom()->IsChatWide();

	if(!mode)  // chat normal
	{
		m_pBack_Score->Xpos = m_ScreenWidth - m_pBack_Score->GetWidth();
		m_pBack_Score->Ypos = 113;
	}
	else
	{
		m_pBack_Score->Xpos = m_ScreenWidth / 2 - m_pBack_Score->GetWidth()/2;
		m_pBack_Score->Ypos = m_ScreenHeight - 102 - m_pBack_Score->GetHeight();
	}

	g_pDisplay->Blt(m_pBack_Score->Xpos, m_pBack_Score->Ypos, m_pBack_Score);

	if(g_dwClientCountry == CTRY_KOR)
	{
		m_pTextScoreA->SetPos(m_pBack_Score->Xpos+140+(70/2)-m_pTextScoreA->GetBoxWidth()/2, m_pBack_Score->Ypos+ 9);
		m_pTextScoreB->SetPos(m_pBack_Score->Xpos+140+(70/2)-m_pTextScoreA->GetBoxWidth()/2, m_pBack_Score->Ypos+ 29);
		m_pTextTeamNameA->SetPos(m_pBack_Score->Xpos+10, m_pBack_Score->Ypos+ 9);
		m_pTextTeamNameB->SetPos(m_pBack_Score->Xpos+10, m_pBack_Score->Ypos+ 29);

		m_pTextScoreA->Draw();
		m_pTextScoreB->Draw();
		m_pTextTeamNameA->Draw();
		m_pTextTeamNameB->Draw();
	}
	else
	{
		m_pTextScoreA->SetPos(m_pBack_Score->Xpos+28-m_pTextScoreA->GetBoxWidth()/2, m_pBack_Score->Ypos+ 47);
		m_pTextScoreB->SetPos(m_pBack_Score->Xpos+118-m_pTextScoreA->GetBoxWidth()/2, m_pBack_Score->Ypos+ 47);
		m_pTextScoreA->Draw();
		m_pTextScoreB->Draw();
	}

}

///����Ʈ�� ������ �� �� ���� �޵��� ����
void CUIMgr::GWarPoint(int a_point, int b_point, char *a_team, char *b_team,CNkCharacter *pCha)
{
	CNkCharacter *pNkCha;
	LHCharacterMap_it pr;

	// ���� ��ƾ ȣ��.
	if(a_point<0) a_point = 0;
	if(b_point<0) b_point = 0;

	char tmp[30];

	if(!m_bShowScore)
	{
		CreateScore();
		m_pTextScoreA->SetString(itoa(a_point, tmp, 10));
		m_pTextScoreB->SetString(itoa(b_point, tmp, 10));
		m_pTextTeamNameA->SetString(a_team);
		m_pTextTeamNameB->SetString(b_team);

	}
	else
	{
		m_pTextScoreA->SetString(itoa(a_point, tmp, 10));
		m_pTextScoreB->SetString(itoa(b_point, tmp, 10));
	}

	// ��� �����ڰ� ���� ��� (��ź ��� ����)
	if (pCha == NULL)
	{
		for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
		{
			pNkCha = (*pr).second;
			if (pNkCha->m_nTeamMemGrade == TEAM_BATTLE_AHEAD || pNkCha->m_nTeamMemGrade == TEAM_BATTLE_AFLAG)
			{
				pNkCha->m_nTeamMemGrade = TEAM_BATTLE_AMEMBER;
			}
			else if (pNkCha->m_nTeamMemGrade == TEAM_BATTLE_BHEAD || pNkCha->m_nTeamMemGrade == TEAM_BATTLE_BFLAG)
			{
				pNkCha->m_nTeamMemGrade = TEAM_BATTLE_BMEMBER;
			}
		}

		if (g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_AFLAG)
			g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_AMEMBER;
		else if (g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_BFLAG)
			g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_BMEMBER;

		// ������ �ö󰥶����� �����ش�.
		g_bPath = TRUE;
		m_bOnTeamBattle = TRUE;

		return;
	}

	// ��� ������ ǥ��
	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pNkCha = (*pr).second;
		if (pNkCha->m_nCharIndex == pCha->m_nCharIndex)
		{
			if (pNkCha->m_nTeamMemGrade == TEAM_BATTLE_AHEAD || pNkCha->m_nTeamMemGrade == TEAM_BATTLE_AMEMBER)
			{
				pNkCha->m_nTeamMemGrade = TEAM_BATTLE_AFLAG;
			}
			else if (pNkCha->m_nTeamMemGrade == TEAM_BATTLE_BHEAD || pNkCha->m_nTeamMemGrade == TEAM_BATTLE_BMEMBER)
			{
				pNkCha->m_nTeamMemGrade = TEAM_BATTLE_BFLAG;
			}
		}
		else
		{
			if (pNkCha->m_nTeamMemGrade == TEAM_BATTLE_AFLAG)
				pNkCha->m_nTeamMemGrade = TEAM_BATTLE_AMEMBER;
			else if (pNkCha->m_nTeamMemGrade == TEAM_BATTLE_BFLAG)
				pNkCha->m_nTeamMemGrade = TEAM_BATTLE_BMEMBER;
		}
	}

	if (g_pRoh->m_nCharIndex == pCha->m_nCharIndex)
	{
		if (g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_AHEAD || g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_AMEMBER || g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_AFLAG)
		{
			g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_AFLAG;
		}
		else
		{
			g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_BFLAG;
		}
	}
	else  	// ��߼����ڰ� ���� �ƴϴ�.
	{
		if (g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_AFLAG)
			g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_AMEMBER;
		else if (g_pRoh->m_nTeamMemGrade == TEAM_BATTLE_BFLAG)
			g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_BMEMBER;
	}

	// ������ �ö󰥶����� �����ش�.
	g_bPath = TRUE;
	m_bOnTeamBattle = TRUE;
}

void CUIMgr::GWarHead(char *a_head, char *b_head)
{
	char buf[100];

	if (!strcmp(g_pRoh->m_pstrName, a_head))
		g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_AHEAD;

	if (!strcmp(g_pRoh->m_pstrName, b_head))
		g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_BHEAD;

	// �� �ֺ��� �ִ� ����� Ahead�ΰ� Bhead�ΰ� Ȯ��.
	CNkCharacter *pCha;
	LHCharacterMap_it pr;

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;
		if (!strcmp(pCha->m_pstrName, a_head))
		{
			pCha->m_nTeamMemGrade = TEAM_BATTLE_AHEAD;
		}
	}

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;
		if (!strcmp(pCha->m_pstrName, b_head))
		{
			pCha->m_nTeamMemGrade = TEAM_BATTLE_BHEAD;
		}
	}
	DestroyScore();
	// IDS_UIMGR_GWAR_AGREE : ����Ʋ�� �����Ǿ����ϴ�.
	sprintf(buf, G_STRING(IDS_UIMGR_GWAR_AGREE));
	g_pNk2DFrame->InsertPopup(buf,TYPE_NOR_OK, 1);
}

void CUIMgr::AddTeamMem(char *strName, int nGrade)
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;

	if (strName == NULL)
		return;

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;
		if (!strcmp(pCha->m_pstrName, strName))
		{
			pCha->m_nTeamMemGrade = nGrade - 2;
		}
	}

	if (!strcmp(g_pRoh->m_pstrName, strName))
	{
		g_pRoh->m_nTeamMemGrade = nGrade - 2;
	}

	if (g_MatrixSvr != 0)
	{
		if (!strcmp(g_pRoh->m_pstrName, &strName[3]))  			// ��Ʈ���� �������� �̸� ����.
		{
			g_pRoh->m_nTeamMemGrade = nGrade - 2;
		}
	}
}
///2003 ��������

void CUIMgr::AssemblySuccess(int vnum,int index,int plus,int special)
{
	//g_pNk2DFrame->GetControlExchange()->AssemblySuccess(vnum,index);
	g_pNk2DFrame->GetProduct()->AssemblySuccess(vnum,index,plus,special);
}

void CUIMgr::AssemblyFail(BOOL bfail)
{
	g_pNk2DFrame->GetProduct()->AssemblyFail(bfail);
}

// PetProduct ���� ���� �Լ�

void CUIMgr::PetAssemblySuccess(int vnum,int index,int slot_x, int slot_y)
{
	g_pNk2DFrame->GetPetProduct()->AssemblySuccess(vnum,index,slot_x,slot_y);
}

void CUIMgr::PetAssemblyFail(BOOL bfail)
{
	g_pNk2DFrame->GetPetProduct()->AssemblyFail(bfail);
}

void CUIMgr::SetSummonLock(BOOL bLock)
{
	if (m_bSummonLock)
	{
		m_timeSummonLock += 1000;
	}
	else
	{
		m_bSummonLock = TRUE;
		m_timeSummonLock = timeGetTime();
	}
}

///1023
void CUIMgr::FindFreePkGuild(char *guild_name, int on_off)
{
	CNkCharacter *pCha;
	LHCharacterMap_it pr;

	if(g_pRoh->m_pstrGuildName)
	{
		if(strcmp(g_pRoh->m_pstrGuildName,guild_name) == 0)
			g_pRoh->m_Free_Pk = on_off;
	}

	for (pr = m_character_map.begin(); pr != m_character_map.end(); pr++)
	{
		pCha = (*pr).second;
		if(pCha->m_pstrGuildName)
		{
			if ( strcmp(pCha->m_pstrGuildName, guild_name) == 0)
				pCha->m_Free_Pk = on_off;
		}
	}
}

BOOL CUIMgr::HelpMessage(int num) //1203 �������ÿ� ��Ÿ���� ���� â.
{
	FILE *fp;
	int index,tot_line,tot_index;
	char strTemp[100];

	if ((fp = fopen("data/etc/help.txt", "rb")) == NULL)
	{
		MessageBox(NULL, "������ ���� �� �����ϴ�.", "����!", MB_OK);
		return 0;
	}

	fscanf(fp, "%d", &tot_index); //�� �ε��� ����

	index = -1;
	while(index!=num) //�̰��� ���� ��Ÿ���� ������ �޶���.���� ������ skip
	{
		fscanf(fp, "%d", &index);	//�ε��� ��ȣ
		fscanf(fp, "%d", &tot_line); //�� �ε����� ���Ե� ������ ���μ�
		for(int i=0; i<tot_line; i++)
		{
			ReadLine2(fp, strTemp);
		}
	}

	if(m_bIsScrollBox) m_bIsScrollBox = FALSE;
	else m_bIsScrollBox = TRUE;

	if(m_bIsScrollBox)
	{
		if (m_pScrollBox)
			delete m_pScrollBox;
		m_pScrollBox = new CScrollBox(TYPE_HELP_BOX);

		fscanf(fp, "%d", &index);	//�ε��� ��ȣ
		fscanf(fp, "%d", &tot_line);

		m_pScrollBox->Init(tot_line, 7);
		if (g_dwLangType == 0 && g_dwClientCountry == 0)
			m_pScrollBox->SetTitleStr("  ��  ��  ��");
		else
			m_pScrollBox->SetTitleStr(" Help Message");

		for(int i=0; i<tot_line; i++)
		{
			ReadLine2(fp, strTemp);
			m_pScrollBox->SetAddStr(strTemp);
		}//17���ڰ� �ְ� ���̷� ����� ��.

		m_pScrollBox->LoadRes();
	}
	else
	{
		if(m_pScrollBox)
			SAFE_DELETE(m_pScrollBox);
	}

	fclose(fp);

	return 1;
}


BOOL CUIMgr::GuildMessage(int guildindex, bool isnetmable) // ��� ����â
{
	if(m_bIsScrollBox)
		m_bIsScrollBox = FALSE;
	else
		m_bIsScrollBox = TRUE;

	if(m_bIsScrollBox)
	{
		if (m_pScrollBox)
			delete m_pScrollBox;

		m_pScrollBox = new CScrollBox(TYPE_GUILD_NOTICE);

		CWebWorld	webworld;

		char address[256] = "";
		char index[256] = "";

		if( isnetmable )
			sprintf(address, "http://laghaim.barunsonena.com/utils/game_nguild_notice.asp?guild_index=");
		else
			sprintf(address, "http://laghaim.barunsonena.com/utils/game_guild_notice.asp?guild_index=");

		sprintf(index, "%d", guildindex);
		strcat( address, index );

		if(webworld.GetWebPage(address) )
		{
			// nate 2005-10-06 : ��� ���� - �� ������ �װŰ� �߸��� ���� �� ��� �÷��׷� üũ
			int noticelen = strlen(webworld.m_UrlData);
			{
				int nSuccess = 0;
				sscanf( webworld.m_UrlData, "%d", &nSuccess );
				if( nSuccess != 1 )
				{
					m_bIsScrollBox = FALSE;
					if(m_pScrollBox)
						SAFE_DELETE(m_pScrollBox);
					return 1;
				}
			}
			noticelen = noticelen / 32;

			m_pScrollBox->Init(noticelen+1, 5);

			if (g_dwLangType == 0 && g_dwClientCountry == 0)
				m_pScrollBox->SetTitleStr(g_pRoh->m_pstrGuildName);
			else
				m_pScrollBox->SetTitleStr("Guild Notice");

			if( webworld.m_UrlData[0] == '\0' )
				m_pScrollBox->AddStringMulti("��ſ� ������� ��⼼��~��", 32);
			else
				m_pScrollBox->AddStringMulti(&webworld.m_UrlData[ 2 ], 32);

			m_pScrollBox->LoadRes();
		}
		else
			m_bIsScrollBox = false;
	}
	else
	{
		if(m_pScrollBox)
			SAFE_DELETE(m_pScrollBox);
	}

	return 1;
}

BOOL CUIMgr::MatrixMessage(int num)
{
	FILE *fp;
	int index,tot_line,tot_index;
	char strTemp[100];

	if ((fp = fopen("data/etc/Matrix.txt", "rb")) == NULL)
	{
		//MessageBox(NULL, "������ ���� �� �����ϴ�.", "����!", MB_OK);
		return 0;
	}

	fscanf(fp, "%d", &tot_index); //�� �ε��� ����

	index = -1;
	while(index!=num) //�̰��� ���� ��Ÿ���� ������ �޶���.���� ������ skip
	{
		fscanf(fp, "%d", &index);	//�ε��� ��ȣ
		fscanf(fp, "%d", &tot_line); //�� �ε����� ���Ե� ������ ���μ�
		for(int i=0; i<tot_line; i++)
		{
			ReadLine2(fp, strTemp);
		}
	}

	if(m_bIsScrollBox) m_bIsScrollBox = FALSE;
	else m_bIsScrollBox = TRUE;

	if(m_bIsScrollBox)
	{
		if (m_pScrollBox)
			delete m_pScrollBox;
		m_pScrollBox = new CScrollBox(TYPE_HELP_BOX);

		fscanf(fp, "%d", &index);	//�ε��� ��ȣ
		fscanf(fp, "%d", &tot_line);

		m_pScrollBox->Init(tot_line, 7);
		if (g_dwLangType == 0 && g_dwClientCountry == 0)
			m_pScrollBox->SetTitleStr("��Ʈ���� ����");
		else
			m_pScrollBox->SetTitleStr("Matrix Message");

		for(int i=0; i<tot_line; i++)
		{
			ReadLine2(fp, strTemp);
			m_pScrollBox->SetAddStr(strTemp);
		}//17���ڰ� �ְ� ���̷� ����� ��.

		m_pScrollBox->LoadRes();
	}
	else
	{
		if(m_pScrollBox)
			SAFE_DELETE(m_pScrollBox);
	}

	fclose(fp);

	return 1;

}


BOOL CUIMgr::IsVk1Pressed()
{
	DWORD tmpTime = timeGetTime();

	// ������ ���ؼ� Ű���� üũ�� �ѹ� ���ش�.
	if ( GetAsyncKeyState('1') & 0x8000)
	{
		m_dwVk1KeyTime = timeGetTime();
	}

	if ( GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
		m_dwVk1KeyTime = timeGetTime();
	}

	double fRes = fabs((double) tmpTime - (double) m_dwVk1KeyTime);
	if (fRes > 1000.0f)
	{
		return FALSE;
	}

	return TRUE;
}

void CUIMgr::DoRoomListStart()
{
	if(m_bIsMatList)
	{
		if (m_pMatList)
		{
			m_pMatList->ClearAllRoomList();
		}
	}
	else
	{
		m_bIsMatList = TRUE;

		if(m_pMatList)
		{
			delete m_pMatList;
			m_pMatList = NULL;
		}

		m_pMatList = new CMatList();
	}
}

void CUIMgr::ShowRoomList(int nRoomNum, int nRoomType, char *strRoomName, int nCount, int nMaxCount, char *strMaster, int nState, int nMinLevel, int nMaxLevel, int nFee, char *strPasswd)
{
	m_pMatList->AddRoomData(nRoomNum, nRoomType, strRoomName, nCount, nMaxCount, strMaster, nState, nMinLevel, nMaxLevel, nFee, strPasswd);
}

void CUIMgr::MakeGameRoom()
{
	if(!g_pNk2DFrame->CloseAllWindow())
		return;

	if(m_bIsMatMakeRoom)
		m_bIsMatMakeRoom = FALSE;
	else
		m_bIsMatMakeRoom = TRUE;

	if(m_bIsMatMakeRoom)
	{
		if(m_pMatMakeRoom)
		{
			delete m_pMatMakeRoom;
			m_pMatMakeRoom = NULL;
		}
		m_pMatMakeRoom = new CMatMakeRoom();
	}
}

void CUIMgr::WaitingRoom()
{
	if(!g_pNk2DFrame->CloseAllWindow())
		return;

	if(m_bIsMatBattle)
		m_bIsMatBattle = FALSE;
	else
		m_bIsMatBattle = TRUE;

	if(m_bIsMatBattle)
	{
		if(m_pBattleUI)
		{
			delete m_pBattleUI;
			m_pBattleUI = NULL;
		}
		m_pBattleUI = new CMatBattleUI();
	}
}

void CUIMgr::EnterRoom(int nRoomType, char* MyName, int nUserType)
{
	if(!g_pNk2DFrame->CloseAllWindow())
		return;

	m_bIsMatBattle = FALSE;
	m_bIsMatDeath = FALSE;
	m_bIsMatSurvival = FALSE;
	m_bIsMatSurvivalMon = FALSE;
	m_bIsMatChat = FALSE;

	switch (nRoomType)
	{

	case 0:							// �Ϲ� ��ȭ��


		break;
	case 1:	//	case 6:					// ����Ʋ
		m_bIsMatBattle = TRUE;
		break;
	case 2:							// �����̹�

		m_bIsMatSurvival = TRUE;
		break;
	case 3:							// �����̹�+����
		m_bIsMatSurvivalMon = TRUE;
		break;
	case 4:							//�Ϲݴ�ȭ��

		m_bIsMatChat = TRUE;
		break;
	case 5:							// ������ġ
		m_bIsMatDeath = TRUE;
		break;
	default:
		return;
	}

	if (m_bIsMatBattle || m_bIsMatDeath)
	{
		if (m_pBattleUI)
		{
			delete m_pBattleUI;
			m_pBattleUI = NULL;
		}
		m_pBattleUI = new CMatBattleUI();

		strcpy(m_pBattleUI->m_MyName, MyName);
		if(nUserType)
			m_pBattleUI->m_bMaster = TRUE; //�� �������� �����̴�..
		if (nUserType)
			m_pBattleUI->SetUserType(TRUE);
		else
			m_pBattleUI->SetUserType(FALSE);
	}
	else if(m_bIsMatSurvival || m_bIsMatSurvivalMon || m_bIsMatChat)
	{
		if (m_pSurvivalUI)
		{
			delete m_pSurvivalUI;
			m_pSurvivalUI = NULL;
		}
		m_pSurvivalUI = new CMatSurvivalUI();

		strcpy(m_pSurvivalUI->m_MyName, MyName);
		if(nUserType)
			m_pSurvivalUI->m_bMaster = TRUE; //�� �������� �����̴�..
		if (nUserType)
			m_pSurvivalUI->SetUserType(TRUE);
		else
			m_pSurvivalUI->SetUserType(FALSE);
	}
}

void CUIMgr::TRoomIn(char *strName, int which_loc, BOOL bWaiting, BOOL bOwner)
{
	if (m_pBattleUI)
	{
		m_pBattleUI->AddMember(strName, which_loc, bWaiting, bOwner);
	}
	else if (m_pSurvivalUI)
	{
		m_pSurvivalUI->AddMember(strName, which_loc, bWaiting, bOwner);
	}
}

void CUIMgr::TRoom(char *cmd, char *strName)
{
	if (m_pBattleUI)
	{
		m_pBattleUI->TRoom(cmd, strName);
	}
	if (m_pSurvivalUI)
	{
		m_pSurvivalUI->TRoom(cmd, strName);
	}
}


void CUIMgr::TRoomUpdate(int what_cmd, char *strName)
{
	if (m_pBattleUI)
	{
		if(what_cmd==1 && !strcmp(m_pBattleUI->m_MyName,strName))
		{
			SAFE_DELETE(m_pBattleUI);
			m_bIsMatBattle = FALSE;
			m_bIsMatDeath = FALSE;
		}
		else
			m_pBattleUI->RoomUpdate(what_cmd, strName);
	}
	else if(m_pSurvivalUI)
	{
		if(what_cmd==1 && !strcmp(m_pSurvivalUI->m_MyName,strName))
		{
			SAFE_DELETE(m_pSurvivalUI);
			m_bIsMatSurvival = FALSE;
			m_bIsMatSurvivalMon = FALSE;
			m_bIsMatChat = FALSE;
		}
		else
			m_pSurvivalUI->RoomUpdate(what_cmd, strName);
	}
}


void CUIMgr::TRoomClose(BOOL bOut)
{
	if (bOut)
		g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_NONE;

	if (m_pBattleUI)
	{
		SAFE_DELETE(m_pBattleUI);
		m_bIsMatBattle = FALSE;
		m_bIsMatDeath = FALSE;
	}
	else if (m_pSurvivalUI)
	{
		SAFE_DELETE(m_pSurvivalUI);
		m_bIsMatSurvival = FALSE;
		m_bIsMatSurvivalMon = FALSE;
		m_bIsMatChat = FALSE;
	}
}

void CUIMgr::TwPackage( int nDate )
{
	if( nDate > 0 )
	{
		char	szTemp[100];
		int		nTemp, nYear, nMonth, nDay;
		nYear = nDate / 10000;
		nTemp = nDate - nYear * 10000;
		nMonth = nTemp / 100;
		nDay = nTemp - nMonth * 100;

		sprintf( szTemp, "Package event end time : %d/%d/%d", nYear, nMonth, nDay );
		g_pNk2DFrame->GetControlBottom()->AddStrQlist( szTemp, -1 );
		g_bActivePackage = TRUE;
	}
	else
		g_bActivePackage = FALSE;
}

// �����Կ� �ִ� ������ �߿��� ���� ��� ã�� ������ ��� ��ƾ.
void CUIMgr::UseQuickFindPetItem(int slot_num)
{
	CNkCharacter *pNkCha = g_pRoh;

	if (!CanUseFindPetItem())
		return;

	sprintf(m_commOut, "p_qk %d\n", slot_num);//use_quick
	if (g_pTcpIp)
		g_pTcpIp->SendNetMessage(m_commOut);
}

bool CUIMgr::CanUseFindPetItem()
{
	// �������� ����� �� �ִ��� �˻� ������ �ۼ��Ѵ�
	// Pet�� ������ ���� ���� ��� ����� ����
	// Pet�� ��ȭ�� �ȵȰ��...
	// pet�� ���� �ִ� ��� ����� �� ����
	if(g_MyPetStatus.mode != MYPET_MODE_KEEP
			|| pCMyApp->m_pMyPet!=NULL
			|| pCMyApp->IsGuildHuntArea() )
	{
		//���� �������� �ƴϰų� ���� ������ �������� ����Ҽ� ����
		//�� ��ü �ܻ��� ������� ���� ȣ�� �Ҽ� ����
		//	if(g_MyPetstatus.mode == MYPET_MODE_HOLD)
		//	if(g_MyPetstatus.mode == MYPET_MODE_EGG)
		return false;
	}
	return true;
}
// ���� �絵 ���� �Լ���

void CUIMgr::CmdPetExchOppInfo(char* PetName, char* Petlevel, char* PetHP, char* PetAttack, char* PetDefense, int PetClass, int Skill1_Level, int Skill2_Level, int Skill3_Level, int Skill4_Level )
{
	// �̸� ���� ����� ���ݷ� ����
	if( PetName == NULL
			|| Petlevel == NULL
			|| PetHP == NULL
			|| PetAttack == NULL
			|| PetDefense == NULL )
		return;

	g_pNk2DFrame->GetControlExchange()->SetExchPetInfo(PetName, Petlevel, PetHP, PetAttack, PetDefense, PetClass, Skill1_Level, Skill2_Level, Skill3_Level, Skill4_Level );
}

void CUIMgr::CmdExchPetClear() // �� �������� �����
{
	if( g_pNk2DFrame->GetControlExchange() )
		g_pNk2DFrame->GetControlExchange()->ExchangedPetClear();
}
//�÷�Ƽ�� ���� �Լ�.
void CUIMgr::PlatimumExch(int result, int type, int vnum, int index, int gem_num)
{
	if (g_pNk2DFrame->GetPlatinum())
		g_pNk2DFrame->GetPlatinum()->Exchange(result, type, vnum, index, gem_num);
}
//���� ��� �̺�Ʈ ���� �Լ�.
void CUIMgr::SummerEvent(int bsucceed, int type, int vnum, int index)
{
	if (g_pNk2DFrame->GetSummerEvent())
		g_pNk2DFrame->GetSummerEvent()->Exchange(bsucceed, type, vnum, index);
}
// ����� ��û
void CUIMgr::GuildPK(int sub_type, char *GuildName1, char *GuildName2, int PKstate)
{
	g_pNk2DFrame->GuildPK(sub_type, GuildName1,GuildName2, PKstate);
}

// nate
// ���丶�콺 ����
void CUIMgr::Dictionary(char* word1,char*word2)
{
	if( word1 == NULL
			|| word2 == NULL )
		return;

	// ����� �� �����ϰ� ��Ŀ���� �����.
	g_pNk2DFrame->GetAutoMouse()->AddWord(word1,word2,
										  g_pNk2DFrame->GetControlBottom()->m_CurTextView,
										  g_pNk2DFrame->GetControlBottom()->m_bAct);

	g_pNk2DFrame->ShowAutoMouseWindow(TRUE);
}

//==============================================================================================
// nate 2004 - 4
// ��ȯ�� ������ �ڵ� ä���
BOOL CUIMgr::CheckSummonToInven( int nDelSlot )
// �κ����� ������ üũ�ϰ�, ������ ��ȯ�� 1�� �����ϰ� �����Կ� ��´�
{
	return FALSE;
}
//==============================================================================================


//==============================================================
// nate 2004 - 4
// Crash_Miss
void CUIMgr::ComputeMiss( char* szChar, int CharIndex )
{
	if( szChar == NULL )
		return;

	LHCharacterMap_it prChar;
	LHMobMap_it prMob;
	CNkCharacter* pChar;
	CNkMob* pMob;
	// Character
	if( !( strcmp( szChar, "c" ) ) )
	{
		if( CharIndex == g_pRoh->m_nCharIndex )
		{
			g_pRoh->SetShowCrash_Miss( 2 );
			return;
		}

		// by evilkiki 2009.05.22.
		if( pChar = GetCharacterByID(CharIndex) )
			pChar->SetShowCrash_Miss( 2 );
// 		for( prChar = m_character_map.begin() ; prChar != m_character_map.end() ; prChar ++ )
// 		{
// 			pChar = (*prChar).second;
// 			if( CharIndex == pChar->m_nVirId )
// 			{
// 				pChar->SetShowCrash_Miss( 2 );
// 			}
// 		}
	}
	// NPC
	else
	{
		if( pMob = GetMobByID(CharIndex) )
		{
			pMob->SetShowCrash_Miss( 2 );
		}
// 		for( prMob = m_mob_map.begin() ; prMob != m_mob_map.end() ; prMob ++ )
// 		{
// 			pMob = (*prMob).second;
// 			if( CharIndex == pMob->m_nVirId )
// 			{
// 				pMob->SetShowCrash_Miss( 2 );
// 			}
// 		}
	}
}

void CUIMgr::ComputeBlock( char *BlockCharType, int BlockCharIndex, char *AttackCharType, int AttackCharIndex ) // Block ȿ��. ///��
{
	LHCharacterMap_it prChar;
	LHMobMap_it prMob;
	CNkCharacter* pBlockChar = NULL;
	CNkMob* pBlockMob = NULL;
	CNkCharacter* pAttackChar = NULL;
	CNkMob* pAttackMob = NULL;

	D3DVECTOR vAttackerPos; // ���� �� ��ǥ.
	D3DVECTOR vBlockerPos;  // ���� �� ��ǥ.

	EffectSort *TempEffect = NULL;

	// �켱 ���� �༮���� ã�´�.
	if( strcmp(AttackCharType,"c") == 0 )
	{
		CNkCharacter* pChar;

		if( AttackCharIndex == g_pRoh->m_nCharIndex ) // �ڱ��ڽ��� m_character_map�� ���⶧���� ���� �˻�.
		{
			pAttackChar = g_pRoh;
			vAttackerPos = D3DVECTOR( g_pRoh->m_wx, 0.0f, g_pRoh->m_wz ); // 2���� ��ǥ��...
		}
		else
		{
			if( pChar = GetCharacterByID(AttackCharIndex) )
			{
				pAttackChar = pChar;
				vAttackerPos = D3DVECTOR( pChar->m_wx, 0.0f, pChar->m_wz ); // 2���� ��ǥ��...
			}
		}
	}
	else if( strcmp(AttackCharType,"n") == 0 ) // mob
	{
		CNkMob* pMob;

		if( pMob = GetMobByID(AttackCharIndex) )
		{
			pAttackMob = pMob;
			vAttackerPos = D3DVECTOR( pMob->m_wx, 0.0f, pMob->m_wz ); // 2���� ��ǥ��...
		}
	}

	if( !pAttackChar && !pAttackMob ) // �Ѵ� ������...
		return;


	// ������ ���� �༮�� ã�´�.
	if( strcmp(BlockCharType,"c") == 0 )
	{
		CNkCharacter* pChar;

		if( BlockCharIndex == g_pRoh->m_nCharIndex ) // �ڱ��ڽ��� m_character_map�� ���⶧���� ���� �˻�.
		{
			pBlockChar = g_pRoh;
			vBlockerPos = D3DVECTOR( g_pRoh->m_wx, 0.0f, g_pRoh->m_wz ); // 2���� ��ǥ��...
		}
		else
		{
			if( pChar = GetCharacterByID(BlockCharIndex) )
			{
				pBlockChar = pChar;
				vBlockerPos = D3DVECTOR( pChar->m_wx, 0.0f, pChar->m_wz ); // 2���� ��ǥ��...
			}
		}
	}
	else if( strcmp(BlockCharType,"n") == 0 ) // mob
	{
		CNkMob* pMob;

		if( pMob = GetMobByID(BlockCharIndex) )
		{
			pBlockMob = pMob;
			vBlockerPos = D3DVECTOR( pMob->m_wx, 0.0f, pMob->m_wz ); // 2���� ��ǥ��...
		}
	}

	if( !pBlockChar && !pBlockMob ) // �Ѵ� ������...
		return;

	// ���� ���͸� ���صд�.
	D3DVECTOR vBlockDir = vAttackerPos - vBlockerPos;
	float fDist = Magnitude( vBlockDir );
	vBlockDir = Normalize( vBlockDir );

	if( pBlockChar )
	{
		pBlockChar->SetShowCrash_Miss( 3 ); // �� ���� �����.

		TempEffect = pBlockChar->FindMyFairy( SKILL_FAIRY );
		if( TempEffect ) // �� ����Ʈ�� ã�Ƽ�.
		{
			TempEffect->num = FX_FAIRY_STATE_BLOCKING; // ��ŷ ����Ʈ�� ����
			TempEffect->nCurFrame = 0;
			TempEffect->vTargetPos = vBlockDir; // ���ϴ� ���� ���͸� ����صд�.

			vBlockDir *= 9.5f;
			TempEffect->vCurPos.x = vBlockDir.x + pBlockChar->m_wx; // ��ǥ�� �����̵� ��������Ѵ�.( y���� )
			TempEffect->vCurPos.z = vBlockDir.z + pBlockChar->m_wz; // ��ǥ�� �����̵� ��������Ѵ�.

			vBlockDir = TempEffect->vTargetPos;
			vBlockDir *= 6.0f;
			TempEffect->vPos.x = vBlockDir.x + pBlockChar->m_wx; // �� ��ġ�� ���.
			TempEffect->vPos.y = TempEffect->vCurPos.y-10.0f; // �� ��ġ�� ���.
			TempEffect->vPos.z = vBlockDir.z + pBlockChar->m_wz; // �� ��ġ�� ���.

			TempEffect->vSortPos.y = (float)atan2(vAttackerPos.z - vBlockerPos.z, vAttackerPos.x - vBlockerPos.x); // ���Ⱚ���� ���.

			// Ÿ�� ����Ʈ ���.
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));

			ef_sort.nType = FX_HITBOOMEFFECTS;
			ef_sort.num = 0;

			vBlockDir = TempEffect->vTargetPos;
			vBlockDir *= 16.0f; // �� ��ġ���� ������ �߿��ϴ�. ������ �ڳ� ���̳Ŀ� ���� �� ���� ��굵 �ݴ밡 �ȴ�.
			ef_sort.vTargetPos.x = vBlockDir.x + pBlockChar->m_wx;
			ef_sort.vTargetPos.y = TempEffect->vCurPos.y+2.0f;
			ef_sort.vTargetPos.z = vBlockDir.z + pBlockChar->m_wz;
			ef_sort.vPos = vBlockerPos; // �� ����Ʈ�� ������ ���������� �߰� ȿ���� �ִ�. �̳༮�� �ݻ�Ǵ� ������ ���� �´����� ��ǥ�� ������ ��ǥ�� ����.

			pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ); // �� ����Ʈ�� ���� ĳ���ͳ� ���� �ͼӽ�Ű�� ������ ����.

			// �� ȿ���� ���
			if( g_pDSound )
				g_pDSound->Play( g_EffectSound[EFF_SND_BLOCK] );

		}
	}
	else if( pBlockMob )
	{
		// ���� �� ���� ���� �ȵ�.
	}	
}

//==============================================================================================

//==================================================
// nate 2004 - 4
// quest
// ĳ���� ��� ���
int	CUIMgr::ComputeCharClass( int nLevel )
{
	if( nLevel < 10 )
		return 0;
	else if( nLevel >= 10 && nLevel < 44 )
		return 1;
	else if( nLevel >= 44 && nLevel < 87 )
		return 2;
	else if( nLevel >= 87 && nLevel < 130 )
		return 3;
	else if( nLevel >= 130 && nLevel < 173 )
		return 4;
	else if( nLevel >= 173 && nLevel < 216 )
		return 5;
	else if( nLevel >= 216 && nLevel < 259 )
		return 6;
	else if( nLevel >= 259 && nLevel < 302 )
		return 7;
	else if( nLevel >= 302 && nLevel < 345 )
		return 8;
	else if( nLevel >= 345 && nLevel < 388 )
		return 9;
	else if( nLevel >= 388 && nLevel < 431 )
		return 10;
	else
		return 0;
}
//==============================================================================================

//-----------------------------------------------------
// ���� �˸���� �߰� <wan>
void CUIMgr::CreLetterMsgBox()
{
	int i;
	char tmp[MAX_LETTER_MSG_BOX][100];

	RECT ClientRc;
	m_hWnd =  g_pDisplay->GetHWnd();
	GetClientRect(m_hWnd, &ClientRc);
	m_ScreenWidth = ClientRc.right;
	m_ScreenHeight = ClientRc.bottom;

	m_iCurMode = CUR_MODE_800;
	m_iMainXpos  = 340;
	m_iMainYpos = 0;
	m_iMove = 350;

	for(i=0; i<MAX_LETTER_MSG_BOX; i++)
	{
		sprintf(tmp[i], "interface/LetterSystem/LetterMsgBox/letter_msg%d.bmp", i+1);
		g_pDisplay->CreateSurfaceFromBitmap(&m_pLetterMsgBox[i], tmp[i]);
		m_pLetterMsgBox[i]->SetColorKey(RGB(1, 1, 1));
	}

	m_iStartX = m_iMainXpos;
	m_iStartY = m_iMainYpos;

	m_iCnt      = 0;

}
void CUIMgr::DeleteLetterMsgBox()
{
	for(int i=0; i<MAX_LETTER_MSG_BOX; i++)
		SAFE_DELETE(m_pLetterMsgBox[i])

		m_bShowLetterMsgBox = FALSE;
}
void CUIMgr::DrawLetterMsgBox()
{
	if(!m_bShowLetterMsgBox)
		return;

	DWORD curTime = timeGetTime();
	if (curTime - m_LetterTime >= TIME_LETTER_FRAME)
	{
		if(m_LetterFrameCnt<5)
			m_LetterFrameCnt++;
		else
			m_iCnt=m_iCnt+10;

		m_LetterTime = curTime;

		if(m_iCnt >m_iMove)
		{
			m_bShowLetterMsgBox = false;
			m_LetterFrameCnt=0;
		}
	}
	if( g_pDisplay )
		g_pDisplay->Blt(m_iStartX-m_iCnt, m_iStartY, m_pLetterMsgBox[m_LetterFrameCnt]);
}

void CUIMgr::isNewLetter()
{	
}
//-------------------------------------------------------------------------------------

//==============================================================================================
// nate 2004 - 4
// exchange

// Exch -> Inven
// ��뿡�� ǥ�õȴ� �κ�
void CUIMgr::ExchGetTarget( int nX, int nY )
{
	if( g_pNk2DFrame->GetControlExchange() )
		g_pNk2DFrame->GetControlExchange()->ExchInvenFrom( nX, nY );
}

// �κ� ó����
// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::ExchGetInven( int nInvenPackNum, int nItemIndex, int nVnum, int nPlusNum, int nSpecialNum, int special2,
						   int UpEndur, int MaxUpdEndur, int nX, int nY, int Endur, int MaxEndur ) ///�Ź���ȭ�ý���
{
	g_pRoh->AddToInven( nInvenPackNum, nX, nY, nItemIndex, nVnum, nPlusNum, nSpecialNum, special2,
						UpEndur, MaxUpdEndur, Endur, MaxEndur ); ///�Ź���ȭ�ý���
}

// ��ȯâ ó����
void CUIMgr::ExchGetExch( int nX, int nY )
{
	g_pRoh->DelFromExgInven( nX, nY );
}

// Inven -> Exch
// ��뿡�� ǥ�õȴ� �κ�
// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::ExchPutTarget( int nItemIndex, int nVnum, int nPlusNum, int nSpecialNum, int special2,
							int UpEndur, int MaxUpdEndur, int nX, int nY, int Endur, int MaxEndur ) ///�Ź���ȭ�ý���
{
	if( g_pNk2DFrame->GetControlExchange() )
		g_pNk2DFrame->GetControlExchange()->ExchInvenTo( nX, nY, nItemIndex, nVnum, nPlusNum, nSpecialNum, special2,
				UpEndur, MaxUpdEndur, Endur, MaxEndur ); ///�Ź���ȭ�ý���
}

// �κ� ó����
void CUIMgr::ExchPutInven( int nInvenPackNum, int nSlot_X, int nSlot_Y )
{
	CItem *pItem = NULL;

	// �κ� ���� ��ġ�� ������ �ε��� ����
	int item_idx = g_pRoh->GetItemIndexInSlot( nInvenPackNum, nSlot_X, nSlot_Y, 1, 1 );
	if ( item_idx >= 0 )
	{
		// ���� �κ��ѳѿ� �ִ� �������� �ε����� �˻��ؼ� ����
		// �Լ���ü�� �޸� ���� ����( ���� �ʿ� )
		pItem = g_pRoh->PickItemInPack( nInvenPackNum, item_idx );
	}

	if ( pItem )
		delete pItem;
}

// ��ȯâ ó����
// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::ExchPutExch(int nItemIndex, int nVnum, int nPlusNum, int nSpecialNum, int special2,
						 int UpEndur, int MaxUpdEndur, int nX, int nY, int Endur, int MaxEndur ) ///�Ź���ȭ�ý���
{
	g_pRoh->AddToExgInven( nX, nY, nItemIndex, nVnum, nPlusNum, nSpecialNum, special2,
						   UpEndur, MaxUpdEndur, Endur, MaxEndur, TRUE ); ///�Ź���ȭ�ý���
	g_pNk2DFrame->GetUpgrade()->CheckUpgradeNeed();
}
//==============================================================================================

//========================================
// nate 2004 - 4
// CastleWar
void CUIMgr::DecardiCastleWarLandAttr( int Where, BOOL bPass ) // 8�������� �ϳ��� �����ϰ� ����.(by ����) //DEC_TOWER
{
	// 0,2,4(������)��  /  1,3,5(������) - ��ȣž   (������) - ��    /   6 - ����(������)   /     7 - ũ����Ż Ÿ��(������)
	if( Where < DECWAR_LAND_ATT_COUNT )
	{
		pCMyApp->GetLandPtr()->SetFieldAttr( g_fDecardi_Protect_Tower_Left_X[ Where ],
											 g_fDecardi_Protect_Tower_Bottom_Z[ Where ],
											 g_fDecardi_Protect_Tower_Right_X[ Where ],
											 g_fDecardi_Protect_Tower_Top_Z[ Where ],
											 bPass );
	}
	else if( Where == DECWAR_LAND_ATT_COUNT ) // �� �迭 �ٷ� ���� �ε����� ����.
	{
		pCMyApp->GetLandPtr()->SetFieldAttr( g_fDecardi_Wine_Door_Left_X
											 , g_fDecardi_Wine_Door_Bottom_Z
											 , g_fDecardi_Wine_Door_Right_X
											 , g_fDecardi_Wine_Door_Top_Z
											 , bPass );
	}
}

//pk�� ������ ���(�߱�)
void CUIMgr::PKItemDrop(int nInvenNum,int nSlotX,int nSlotY,int nWidth,int nHeight)
{
	int nDropItemIndex=0;
	nDropItemIndex=g_pRoh->GetItemIndexInSlot(nInvenNum, nSlotX, nSlotY, nWidth, nHeight);
	g_pRoh->PickItemInPack(nInvenNum, nDropItemIndex);
}


//=====================================================
// nate 2004 - 10
// GuildHunt
void CUIMgr::GuildHuntLandAttr(BOOL bPass)
// bPass : ĳ���� ����Ҽ� �ִ°�
{
	// ��� ������� ������ ���Թ� �Ӽ��� ����
	if( pCMyApp->m_nCurWorldIdx == WORLD_GUILD )
		pCMyApp->GetLandPtr()->SetFieldAttr( 4430, 2385, 4490, 2440, bPass );
	else if( pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN )
	{
		pCMyApp->GetLandPtr()->SetFieldAttr( 9300, 1030, 9340, 1070, bPass );
		pCMyApp->GetLandPtr()->SetFieldAttr( 9410, 1030, 9440, 1070, bPass );
	}

	// ��� �Ҽ� ������
	if( bPass == FALSE )
		m_byDoorOpen = 0;	// ����
	else	// �ƴϸ�
		m_byDoorOpen = 1;	// ����
}
//=====================================================

//=====================================================
// nate 2004 - 10
// ��ī���� ��������
// ����, ��Ÿ ���� ����
void CUIMgr::SetDecardiGuildName(char *szGuildName, BYTE byGammaDelta)
// byGammaDelta( 1 : ����, 2 : ��Ÿ )
{
	if( byGammaDelta == 1 )
	{
		if( m_szDecardiGuildGamma )
		{
			delete[] m_szDecardiGuildGamma;
			m_szDecardiGuildGamma = NULL;
		}
		if( szGuildName )
		{
			int nGuildNameLen = strlen( szGuildName );
			if( nGuildNameLen > 0 )
			{
				m_szDecardiGuildGamma = new char[ nGuildNameLen + 1 ];
				strcpy( m_szDecardiGuildGamma, szGuildName );
			}
		}
	}
	else if( byGammaDelta == 2 )
	{
		if( m_szDecardiGuildDelta )
		{
			delete[] m_szDecardiGuildDelta;
			m_szDecardiGuildDelta = NULL;
		}
		if( szGuildName )
		{
			int nGuildNameLen = strlen( szGuildName );
			if( nGuildNameLen > 0 )
			{
				m_szDecardiGuildDelta = new char[ nGuildNameLen + 1 ];
				strcpy( m_szDecardiGuildDelta, szGuildName );
			}
		}
	}
}
//=====================================================

//--------------------------------------------------------------------------
// SetBRFalg
//--------------------------------------------------------------------------
// ������ Flag �� �����Ѵ�
// 2004.11.02
// Lyul /�߰��Ϸ�
// Cmd �� ���� ȣ��
void CUIMgr::SetBRFalg(CItem *pItem, int flag)
{
	if( !pItem )
		return;
	ResetItemValue(pItem);
	pItem->m_Special = flag;
}

// ��ǥ �̵��� ȣ��Ǹ� ī�޶� ���Ƿ� �����δ�
// 24AUTO �� �����ϱ� ���� ��å
void CUIMgr::RandomCameraRotate()
{
	int mv = (rand()%11)-5;
	POINT ptNext;
	ptNext.x = 10;
	ptNext.y = 10;

	int i=0;
	for(i=0; i<abs(mv); i++)
	{
		if(mv>0)
		{
			pCMyApp->ForwardCamDirection();
			pCMyApp->RotateRight();
			pCMyApp->RotateRight();
			pCMyApp->RotateRight();
			pCMyApp->RotateRight();
			pCMyApp->RotateCamera(ptNext, 20, 0);
		}
		else
		{
			pCMyApp->ForwardCamDirection();
			pCMyApp->RotateLeft();
			pCMyApp->RotateLeft();
			pCMyApp->RotateLeft();
			pCMyApp->RotateLeft();
			pCMyApp->RotateCamera(ptNext, 20, 20);
		}
	}
}

// ���� Message �� �����Ѵ�.
void CUIMgr::SendAttackMessage(char *Msg)
{
	if( Msg == NULL )
		return;

	if( g_pTcpIp )
		g_pTcpIp->SendNetMessage(Msg);
}

//��Ʈ���� ���� ���� ó��(mungmae-03/21)
void CUIMgr::OpenMatrixGate()
{
	switch(g_MatrixSvr)	//���� ��ǥ(mungmae-03/21)
	{
	case 1:
		{
			float Matrix_gate_left_x[] =   { 7010, 5380, 2930, 3960, 8320, 9290 };
			float Matrix_gate_bottom_z[] = { 2960, 2930, 7200, 8740, 8780, 7280 };
			float Matrix_gate_right_x[] =  { 7210, 5470, 3320, 4720, 8600, 9640 };
			float Matrix_gate_top_z[] =	   { 3290, 3320, 7250, 8990, 9050, 7440 };

			//����Ʈ ���� ��ǥ(mungmae-03/22)
			float Matrix_gatestone_left_x[] =	{ 6950, 5560, 4440, 5170, 7310, 8080 };
			float Matrix_gatestone_bottom_z[] = { 4470, 4560, 6530, 7800, 7810, 6560 };
			float Matrix_gatestone_right_x[] =  { 7050, 5650, 4530, 5280, 7410, 8180 };
			float Matrix_gatestone_top_z[] =	{ 4570, 4650, 6620, 7900, 7910, 6650 };

			//�׶��Ʈ ũ����Ż ��ǥ(mungmae-03/22)
			float Matrix_ground_left_x[] = { 6250, 3550, 8920};
			float Matrix_ground_bottom_z[] = { 2950, 8000, 8050};
			float Matrix_ground_right_x[] = { 6390, 3670, 9050};
			float Matrix_ground_top_z[] = { 3080, 8120, 8170};

			//����Ʈ ����
			for(int cnt = 0; cnt < 6; cnt++ )
			{

				if( m_nStoneState[ cnt ] == 0 )
				{
					// ����������...
					pCMyApp->GetLandPtr()->SetFieldAttr( Matrix_gate_left_x[ cnt ], Matrix_gate_bottom_z[ cnt ],
														 Matrix_gate_right_x[ cnt ], Matrix_gate_top_z[ cnt ],
														 TRUE );

					//����Ʈ ���� ���������� ����������
					pCMyApp->GetLandPtr()->SetFieldAttr( Matrix_gatestone_left_x[ cnt ], Matrix_gatestone_bottom_z[ cnt ],
														 Matrix_gatestone_right_x[ cnt ], Matrix_gatestone_top_z[ cnt ],
														 TRUE );
				}
			}

			for( int cnt = 6; cnt < 9; cnt++ )
			{
				//�׶��� ũ����Ż ��������...
				if( m_nStoneState[ cnt ] == 0 )
				{
					pCMyApp->GetLandPtr()->SetFieldAttr( Matrix_ground_left_x[ cnt-6 ], Matrix_ground_bottom_z[ cnt-6 ],
														 Matrix_ground_right_x[ cnt-6 ], Matrix_ground_top_z[ cnt-6 ],
														 TRUE );
				}
			}
		}
		break;
	case 2:
		{
			for(int i = 0; i < 11; i++ )
			{
				if( m_nStoneState[i] != m_nStoneState2[i] ) // ���� ���¿� ���ؼ� ���ߴٸ� �׶� �Ӽ��� ��������
				{
					m_nStoneState2[i] = m_nStoneState[i];
					switch( i )
					{
					case 0: // ���帶�� �������Ʈ
						{
							float tempX1[10] = { 2050,  2060,  2070,  2080,  2090,  2100,  2110,  2120,  2130,  2140};
							float tempX2[10] = { 2070,  2080,  2090,  2100,  2110,  2120,  2130,  2140,  2140,  2150};
							float tempZ1[10] = {10880, 10890, 10900, 10910, 10920, 10930, 10940, 10950, 10980, 10960};
							float tempZ2[10] = {10900, 10910, 10930, 10940, 10950, 10960, 10970, 10980, 10990, 10980};

							for(int j=0; j<10 ; j++)
							{
								if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
									pCMyApp->GetLandPtr()->SetFieldAttr( tempX1[j], tempZ1[j], tempX2[j], tempZ2[j], TRUE );
								else
									pCMyApp->GetLandPtr()->SetFieldAttr( tempX1[j], tempZ1[j], tempX2[j], tempZ2[j], FALSE );
							}

							// ���帶�� �������Ʈ�� �����Ÿ�
							// �̸̹� GP ������ ���� �ŹǷ� �����ٴ� �� �ֵ��� ���ش�.
							if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
								pCMyApp->GetLandPtr()->SetFieldAttr( 5940, 6160, 5020, 6230, TRUE );
							else
								pCMyApp->GetLandPtr()->SetFieldAttr( 5940, 6160, 6020, 6230, FALSE );

						}
						break;

					case 1: //  �̸̹� ���帶�� �������Ʈ
						{
							float tempX1[7] = {5850, 5840, 5820, 5810, 5790, 5780, 5770};
							float tempX2[7] = {5880, 5860, 5859, 5830, 5820, 5800, 5790};
							float tempZ1[7] = {8320, 8310, 8300, 8290, 8280, 8270, 8260};
							float tempZ2[7] = {8340, 8330, 8320, 8310, 8300, 8290, 8280};

							for(int j=0; j<7 ;  j++)
							{
								if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
									pCMyApp->GetLandPtr()->SetFieldAttr( tempX1[j], tempZ1[j], tempX2[j], tempZ2[j], TRUE );
								else
									pCMyApp->GetLandPtr()->SetFieldAttr( tempX1[j], tempZ1[j], tempX2[j], tempZ2[j], FALSE );
							}
						}
						break;

					case 2: // �̸̹� �ȱ׸��� �������Ʈ
						{
							if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
								pCMyApp->GetLandPtr()->SetFieldAttr( 6800, 5200, 6940, 5220, TRUE );
							else
								pCMyApp->GetLandPtr()->SetFieldAttr( 6800, 5200, 6940, 5220, FALSE );
						}
						break;

					case 3: // �ȱ׸��� �������Ʈ
						{
							float tempX1[10] = {10830, 10820, 10830, 10840, 10850, 10860, 10870, 10880, 10890, 10900};
							float tempX2[10] = {10840, 10850, 10860, 10870, 10880, 10890, 10900, 10910, 10920, 10910};
							float tempZ1[10] = { 1710,  1720,  1730,  1740,  1750,  1760,  1780,  1790,  1800,  1820};
							float tempZ2[10] = { 1720,  1740,  1750,  1760,  1770,  1780,  1790,  1810,  1820,  1830};

							for(int j=0; j<10 ; j++)
							{
								if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
									pCMyApp->GetLandPtr()->SetFieldAttr( tempX1[j], tempZ1[j], tempX2[j], tempZ2[j], TRUE );
								else
									pCMyApp->GetLandPtr()->SetFieldAttr( tempX1[j], tempZ1[j], tempX2[j], tempZ2[j], FALSE );
							}
						}
						break;

					case 4: // ���帶�� �׶��� ũ����Ż
						{
							if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
								pCMyApp->GetLandPtr()->SetFieldAttr( 1910, 11040, 1980, 11110, TRUE );
						}
						break;

					case 5: // �ȱ׸��� �׶��� ũ����Ż
						{
							if( m_nStoneState[i] == 0) // 0 �̸� ������ �� �ֵ���
								pCMyApp->GetLandPtr()->SetFieldAttr( 11000, 1630, 11060, 1690, TRUE );
						}
						break;
					}
				}
			}
		}
		break;
	}
}

// nate 2005-03-21
// Matrix : �ٴ� ��ũ �׸���
void CUIMgr::CreateMatrixMark()
{
	if( g_MatrixSvr != 0)
	{
		m_pMatrixMark = new CRectPlane();
		m_pMatrixMark->Create( 20, 20, TRUE );
		m_pMatrixMark->SetColor( 255, 255, 255, 255 );
		m_pMatrixMark->Scale( 1.0f, 1.0f, 1.0f );
	}
}

// nate 2005-04-22 : �޺� ����ϱ�
void CUIMgr::ComputeCombo( int nCharIndex, int nFrameIndex )
{
	CNkCharacter* pChar;

	if( nCharIndex == g_pRoh->m_nCharIndex )
	{
		g_pRoh->SetShowCrash_Miss( nFrameIndex );
		return;
	}

	if( pChar = GetCharacterByID( nCharIndex) )
	{
		pChar->SetShowCrash_Miss( nFrameIndex );
	}
}

// nate 2005-05-09 : �̺�Ʈ����Ʈ(EP)ȹ��� ���� �޼����� ���� ��Ÿ��
void CUIMgr::ComputeEventPoint( int nCharIndex )
{
	// ������ ���
	if( nCharIndex == g_pRoh->m_nCharIndex )
	{
		g_pRoh->SetShowCrash_Miss( 20 );
		return;
	}

	// Ÿ���� ���
	CNkCharacter* pChar;
	if( pChar = GetCharacterByID( nCharIndex) )
	{
		pChar->SetShowCrash_Miss( 20 );
	}
}

void CUIMgr::SetItemTimeLimit( int item_index, int time ) // �������� �ð��� ���������� �����Ѵ�.(by ����) ///�ð���������
{
	CNkCharacter *pNkCha = g_pRoh;

	CItem *pItem = pNkCha->FindItemByIndexFromAll( item_index );

	if( pItem )
	{
		// Ư�� �п� �޼����� ������ش�.
		if( g_pNk2DFrame && (time/3600) <= 0 ) // �д����� ��������...(�ð� ���� �̻��� ������ ����)
		{
			char temp[256];
			int Limit_Min  = (time/60) % 60; // ���� ��

			if( Limit_Min == 10 || Limit_Min == 5 || Limit_Min == 1 ) // Ư�� ���� ��������. (���� ���� �ݺ������� ���ų� �ǳʶٴ� ���� ���ٰ� �������� �����ؾ��Ѵ�.)
			{
				//-- IDS_REMAIN_ITEMTIME : %s �������� ���ѽð��� %d�� ���ҽ��ϴ�.
				sprintf( temp, (char*)G_STRING(IDS_REMAIN_ITEMTIME), GET_ITEM_NAME_VNUM(pItem->m_Vnum), Limit_Min );
				g_pNk2DFrame->AddChatStr( temp, -1 );
			}
		}

		pItem->SetTimeLimitItem( time );
	}
}

void CUIMgr::SetItemExPrice( int item_index, int PriceType, int Price ) // �����ۿ� Ư�������� �����Ѵ�. ///BP����.
{
	CNkCharacter *pNkCha = g_pRoh;

	CItem *pItem = pNkCha->FindItemByIndexFromAll( item_index );

	if( pItem )
		pItem->SetExPrice( PriceType, Price );
}

// nate 2005-06-17 : ��Ĵ�� ��ų���� �Ǻ�
BOOL CUIMgr::IsRohSkill( int nSkill_Idx )
{
	if( nSkill_Idx == SKILL_HELL_CRY
			|| nSkill_Idx == SKILL_TORNADO_RUIN
			|| nSkill_Idx == SKILL_SUMMON_PARTITION
			|| nSkill_Idx == SKILL_AIR_RAID
			|| nSkill_Idx == SKILLF_C_DASSAULT
			|| nSkill_Idx == SKILL_H_AUTOMINE
//		|| nSkill_Idx == SKILL_C_HELLDOWN
			|| nSkill_Idx == SKILL_F_DASHSLASH ///�����޺�
			|| nSkill_Idx == SKILL_F_SLASHSHADOW ///�����޺�
			|| nSkill_Idx == SKILL_F_STONEBASH1 ///�����޺�
			|| nSkill_Idx == SKILL_F_STONEBASH2 ///�����޺�
			|| nSkill_Idx == SKILL_F_BASHREFLECT1 ///�����޺�
			|| nSkill_Idx == SKILL_F_BASHREFLECT2 ///�����޺�
	  )
		return TRUE;

	return FALSE;
}

// [6/1/2007 Theodoric] ������ ���� :: �Լ� �Ķ���� ������ ����
void CUIMgr::UpdateItem(int Index, int vnum, int plus, int special, int special2,
						int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur )	// ������ ���� ���ſ� ���� �Լ�(05-10-21). ///�Ź���ȭ�ý���
{
	int i = 0;
	CNkCharacter *pNkCha = g_pRoh;

	if( !pNkCha )
		return;

	CItem *pItem = pNkCha->FindItemByIndexFromAll( Index );

	if( pItem ) // �ε����� �´� �������� ������ �׳� �ٲ۴�.(vnum�� �ٲ������. ���� ���� ��ȭ������ ����� �������� ���Ƽ� üũ������ �Ⱦ��� �׳� �ٲ۴�.)
	{
		pItem->m_Vnum = vnum;
		// pItem->m_PlusNum = plus;

		//0917  �κ�â�� ����������� �÷��� ���������� �ν��ϴ°� ����.
		if(GET_TYPE(pItem)==ITYPE_SUB)
		{
			pItem->m_PlusNum = plus;
		}
		else if (plus > 0)
		{
			// 2004. 03. 22  / Lyul
			// ������ ���̾� ��� �ν� ���� Big Fix
			if(GET_ITEM_LEVEL(pItem)>=181)
				pItem->SetDiaGemNum(plus);
			else
				pItem->SetGemNum(plus);
		}

		pItem->m_Special = special;
		pItem->m_Special2 = special2;
		pItem->m_UpgradeEndurance = UpEndur;
		pItem->m_MaxUpgradeEndurance = MaxUpdEndur;

		pItem->m_Endurance = Endur;
		pItem->m_MaxEndurance = MaxEndur;

		if( pCMyApp && g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
			g_pNk2DFrame->GetControlInven()->m_bDrawInfoUpdate = TRUE; // ������ ������ ������ ���Ž�Ų��.(�̷��� ���ϸ� �������� ��ų� �ٸ� �������� �ôٰ� �;��� ���ŵȴ�.)

		// �������� 0�ε� �������� �������̶�� �������ͽ� ȭ���� ���� ����� �ٽ� ���ش�.
		if( UpEndur == 0 && CheckCanNpcUpgradeItem(pItem) ) // ��ȭ �������� ����� ������������ üũ������Կ� ����.
		{
			for( int i = 0 ; i <= 8 ; ++i )
			{
				if( pNkCha->m_Wearing[i] && pNkCha->m_Wearing[i]->m_Index == pItem->m_Index ) // �������� �������̶��...
					((CControlScore*)g_pNk2DFrame->GetInterface(SCORE))->SetDefense();
			}
		}
	}
}

void CUIMgr::CmdProcessAccept( int type, char *player_name )
{
	if( player_name == NULL )
		return;

	if ( strlen( player_name ) )
		strcpy( m_strProcessPlayerName, player_name );
	else
		m_strProcessPlayerName[ 0 ] = NULL;

	if ( g_pNk2DFrame->GetProcess() )
		g_pNk2DFrame->GetProcess()->SetOppName( m_strProcessPlayerName );

	g_pNk2DFrame->ShowProcessWindow( TRUE, type );
}

void CUIMgr::CmdProcessRequest(char *player_name)
{
	if( player_name == NULL )
		return;

	if( g_pRoh->GetMotionState() == CHA_STAND
			&& !g_pRoh->GetCombat()
			&& !g_pNk2DFrame->IsUserShopVisible() ) // ���λ��� �߿��� �ڵ� ��� ///���λ���
		g_pNk2DFrame->GetProcess()->AskProcessRequest( player_name );
	else	// ����
	{
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage("process ans reject\n");
	}
}

// [6/7/2007 Theodoric] ������ ���� :: �Լ� ���� �߰�.
void CUIMgr::ProcessInvenTo(int x, int y, int index, int vnum, int gem_num, int special,
							int UpEndur, int MaxUpdEndur, int Endur, int MaxEndur )
{
	if( g_pNk2DFrame->GetProcess() )
		g_pNk2DFrame->GetProcess()->ProcessInvenTo(x, y, index, vnum, gem_num, special,
				UpEndur, MaxUpdEndur, Endur, MaxEndur );
}

void CUIMgr::ProcessInvenFrom(int x, int y )
{
	if( g_pNk2DFrame->GetProcess() )
		g_pNk2DFrame->GetProcess()->ProcessInvenFrom(x, y);
}

void CUIMgr::ProcessMoney( char *strMoney)
{
	if( strMoney == NULL )
		return;

	g_pNk2DFrame->GetProcess()->ProcessMoney(strMoney);
}

void CUIMgr::ProcessSuccess(int vnum, int index, int x, int y )
{
	CmdErrorMsg( (char*)G_STRING(IDS_PROCESS_SUCC) );
	g_pNk2DFrame->GetProcess()->ProcessSuccess(vnum, index, x, y );
}

void CUIMgr::ProcessFail()
{
	CmdErrorMsg( (char*)G_STRING(IDS_PROCESS_FAIL) );
	if (g_pNk2DFrame->GetProcess()
			&& g_pNk2DFrame->GetProcess()->IsProcessConnection() )
		g_pNk2DFrame->GetProcess()->ResetConnection();
}

void CUIMgr::WorldCupTime( int time )
{
	if ( g_pNk2DFrame->GetWorldCup() )
		g_pNk2DFrame->GetWorldCup()->SetRemainTime(time);
}

void CUIMgr::WorldCupScore( int A_Team, int B_Team )
{
	if ( g_pNk2DFrame->GetWorldCup() )
		g_pNk2DFrame->GetWorldCup()->SetScore( A_Team, B_Team );
}
// mungmae-2006/06/13 : ������ ���ǵ�� ����Ʈ
void CUIMgr::SpeedUpEffect(CNkCharacter *pCha, BOOL bVisual)
{
	if( bVisual )
		InsertMagic(pCha, NULL, pCha, NULL, EFFECT_SPEEDUPSMOKE);
}

void CUIMgr::SpiritModeEffect(CNkCharacter *pCha, BOOL bVisual)
{
	pCha->m_bSpiritModeEffect = bVisual;
	if( bVisual == 0 ) // ����Ʈ�� ���ﶧ
	{
		EffectSort *TempEffect = NULL;
		TempEffect = pCha->FindMySpirit();
		if( TempEffect )
		{
			pCha->DeleteEffectNum( TempEffect->nNum ); // ĳ���Ϳ��� ����ϰ��ִ� �����ε��� �迭������ �����ش�.(���� ����Ʈ���� �̰��� ���ߴ�. ��, ���� ����Ʈ���� �޸� ��� �׿�����...-_-; )
			pCMyApp->m_pFxSet->DeleteEffect( TempEffect->nNum );
		}
	}
	else // ����Ʈ�� ������
	{
		InsertMagic(pCha, NULL, pCha, NULL, EFFECT_SPIRITMODE2);
	}
}

void CUIMgr::WorldCupGuildName(char *ch_AGuild, char *ch_BGuild)
{
	if ( g_pNk2DFrame->GetWorldCup() )
		g_pNk2DFrame->GetWorldCup()->SetGuildName( ch_AGuild, ch_BGuild );
}

//�İ���
void CUIMgr::CmdHelperRequest(char *player_name)
{
	if( player_name == NULL )
		return;

	if( g_pRoh->GetMotionState() == CHA_STAND
			&& !g_pRoh->GetCombat()
			&& !g_pNk2DFrame->IsUserShopVisible() ) // ���λ��� �߿��� �ڵ� ��� ///���λ���
		g_pNk2DFrame->GetControlHelper()->AskHelperRequest( player_name );
	else	// ����
	{
		if (g_pTcpIp)
			g_pTcpIp->SendNetMessage("support ans 0\n");
	}
}

void CUIMgr::SpiritTime(int nRemainTime)
{
	g_pNk2DFrame->GetSpiritMode()->SetSpiritTime( nRemainTime );
}

void CUIMgr::SpiritPoint( int nGet_Thousand, int nGet_Hundred, int nGet_Ten, int nGet_One, int nTaget_Hundred, int nTaget_Ten, int nTaget_One)
{
	g_pNk2DFrame->GetSpiritMode()->SpiritSetPoint( nGet_Thousand, nGet_Hundred, nGet_Ten, nGet_One, nTaget_Hundred, nTaget_Ten, nTaget_One);
	g_pNk2DFrame->GetSpiritMode()->SetFrame(0);
}

void CUIMgr::InitEventScene() // �̺�Ʈ �ŵ��� �ʱ�ȭ ///�δ�1 �� �߰�
{
	m_nNowPlayingEvent = 0;
	m_dwEventStartTime = 0; // ���� �ð��� ���.

	// ������ ���۵ɶ� �Ǵ� �༮. �� �ȿ��� �� �̺�Ʈ ��ü���� new �� ���ְ�, �ε� �뷮�� ���� ������ �̸� �ε� ���ҽ��� �صд�.(�ƴ� �༮�� �� ���۽� �ε�, �� ������ ����� �Ѵ�.)
	m_pEvent_LegKnock_Appear = new CEventLegKnockAppear(); // �δ� ��ī�� ���� ���� ��. �� �༮�� ȣ�⸶�� �����͸� �ε��Ѵ�.
	m_pEventScript = new CEventScriptActor(); // �̺�Ʈ ��ũ��Ʈ ///Ʃ�丮�� �� �߰�
}

void CUIMgr::StartEventScene( int EventIndex, float PosX, float PosZ, float Dir ) // Ư�� ���� �̺�Ʈ �� ///�δ�1 �� �߰�
{
	switch( EventIndex )
	{
	case EVENTACTION_DEKAREN_BOSS_IN: // �δ� ��ī�� ���� ���� ��.

//		if( g_nCurWorldIdx != 1 ) // ��ī���� �ƴϸ� ����.
//			return;

		pCMyApp->StopHero(); // �������� ��Ų��.

		m_pEvent_LegKnock_Appear->LoadRes(); // ���� �����Ҷ� �����͸� �ε�.(�ε差�� ���� �༮�� �ٸ��� �ؾ��Ѵ�.)

		m_nNowPlayingEvent = EventIndex; // ���� �÷��� ������ ����.
		m_dwEventStartTime = timeGetTime(); // ���� �ð��� ���.

		m_pEvent_LegKnock_Appear->m_PosX = PosX;
		m_pEvent_LegKnock_Appear->m_PosY = m_pLand->GetHFHeight(PosX, PosZ);
		m_pEvent_LegKnock_Appear->m_PosZ = PosZ;
		m_pEvent_LegKnock_Appear->m_dir = Dir;

		{
			D3DVECTOR EyePos;
			pCMyApp->GetEyePos( EyePos ); // ���� �Լ��� �̵����� ������ �� �ۿ� ������...

			m_pEvent_LegKnock_Appear->Init( EyePos, pCMyApp->GetEyeAtPos() ); // �� �ȿ��� ���� ���� �����κ��� ī�޶� ��ǥ ���õ��� ���ش�.
		}

		g_pNk2DFrame->CloseAllWindow(); // �������̽����� ���� �ݾ��ش�.

		break;

	case EVENTACTION_TUTORIAL: ///Ʃ�丮�� ��ũ��Ʈ �ʱ�ȭ ����.

		m_pEventScript->m_ScriptState = EVENT_SCRIPT_STATE_RUN;
		pCMyApp->StopHero(); // �������� ��Ų��.

		// ��ũ��Ʈ �ε������� ��⼭ ���������ҵ�.(Ÿ�̹� ��)

		if( !m_pEventScript->LoadScript( "data/EventScript/Tutorial.scr" ) ) // Ʃ�丮�� ��ũ��Ʈ�� ����. ��ũ��Ʈ�� �ε��ϰ� �̹������� �ε��صд�.
		{
			MessageBox( NULL, "Tutorial Script Load Failed!", "Warring", MB_OK );
			return;
		}


		g_pNk2DFrame->CloseAllWindow(); // �������̽����� ���� �ݾ��ش�.

		m_nNowPlayingEvent = EventIndex; // ���� �÷��� ������ ����.
		m_dwEventStartTime = timeGetTime(); // ���� �ð��� ���.

		m_pEventScript->SceneChange( 1 ); // ���� ó�� ������ ��ȯ�����ش�.

		break;

	}
}

void CUIMgr::PlayEventScene() // Ư�� ���� �̺�Ʈ �� ///�δ�1 �� �߰�
{
	switch( m_nNowPlayingEvent )
	{
	case EVENTACTION_DEKAREN_BOSS_IN: // �δ� ��ī�� ���� ���� ��.
		if( m_pEvent_LegKnock_Appear->Render(m_dwEventStartTime) ) // TRUE�� ���ϵǸ� ����Ʈ�� ����ȴ�.(ĵ���̵� �Ϸ��...����� �� �̺�Ʈ�� ĵ�� �ȵ�)
			m_nNowPlayingEvent = 0; // �̺�Ʈ �� ����.
		break;

	case EVENTACTION_TUTORIAL: ///Ʃ�丮�� ��ũ��Ʈ �ʱ�ȭ ����.
		// Ʃ�丮�� �߿� ���ΰ��� �Ϻ� Npc���� ���� �׷���� �Ѵ�.
		pCMyApp->DrawPlayer(); // �̰� ������ �߿��ϴ���. RunScript�� �����ϸ� ����ũ��Ʈ �ȿ��� �׸��� �͵鿡 ����������.
		pCMyApp->m_pUIMgr->RenderMobs();

		m_pEventScript->RunScript();

		break;

	}
}

BOOL CUIMgr::EventSceneMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) // �̺�Ʈ ���� �޼��� ���ν���. ///Ʃ�丮�� �� �߰�
{
	switch( m_nNowPlayingEvent )
	{
	case EVENTACTION_DEKAREN_BOSS_IN: // �δ� ��ī�� ���� ���� ��.
		return TRUE; // �ٸ� �޼����� ���� ��Ű�� ���� ����. �̰� ������.

	case EVENTACTION_TUTORIAL: ///Ʃ�丮�� ��ũ��Ʈ �ʱ�ȭ ����.
		return m_pEventScript->MsgProc( hWnd, msg, wParam, lParam );
	}

	return TRUE;
}

void CUIMgr::EndEventScene() // Ư�� ���� �̺�Ʈ �� ����. �ʱ�ȭ ///�δ�1 �� �߰�
{
	switch( m_nNowPlayingEvent )
	{
	case EVENTACTION_DEKAREN_BOSS_IN: // �δ� ��ī�� ���� ���� ��.
		m_pEvent_LegKnock_Appear->DeleteRes();
		break;

	case EVENTACTION_TUTORIAL: ///Ʃ�丮�� ��ũ��Ʈ �ʱ�ȭ ����.
		m_pEventScript->Init(); // ���� �޸𸮵鸸 �����Ѵ�.

		// Ʃ�丮�� ��� ��Ŷ�� �����ش�.(�Ϸ�ÿ��� �ѹ����������� �������� �������ش�)
		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage( "tutorial -1" );

		break;
	}

	m_nNowPlayingEvent = 0;
	m_dwEventStartTime = 0; // ���� �ð��� ���.
}

void CUIMgr::ReleaseEventScene() // �̺�Ʈ �ŵ��� ���� ///�δ�1 �� �߰�
{
	// InitEventScene ���� �ε��� �༮�� ���⼭ DeleteRes�� �ؾ��Ѵ�.
	SAFE_DELETE( m_pEventScript ); ///Ʃ�丮�� �� �߰�
	SAFE_DELETE( m_pEvent_LegKnock_Appear );
}

void CUIMgr::Siren_flag(int switch_flag, int nCharIdx, int color)
{
	if( g_SvrType != ST_ADULT_ONLY )
		return;

	if(g_pRoh->m_nCharIndex == nCharIdx)
	{
		g_pRoh->Siren_Switch(switch_flag, color);
		return;
	}

	LHCharacterMap_it _iter_;

	CNkCharacter* pTemp = NULL;
	if( pTemp = GetCharacterByID(nCharIdx) )
	{
		pTemp->Siren_Switch(switch_flag, color);
	}
}

BOOL CUIMgr::thread_create(int nServerIndex)
{
	m_nServerIndex = nServerIndex;

	if (m_bIsThread == FALSE)
	{
		m_hThread  = NULL;
		m_ThreadID = 0;

		m_bIsThread = TRUE;

		m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadDataLoad, this, 0, &m_ThreadID);

		if( INVALID_HANDLE_VALUE != m_hThread )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
	}
	return FALSE;
}

void CUIMgr::thread_finish()
{
	m_bIsThread = FALSE;
	SetEvent(m_hWaitObject);
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle( m_hThread );

	clearguildmark();
	std::queue<int> empty;
	std::swap(m_GuildMarkStack, empty);

	SAFE_DELETE(m_phttpConnection);
}

void CUIMgr::isguildmark(int nGuildIndex)
{
	if( CommonConfig::Instance()->GetGuildMark() == false )
		return;

	list_guildmark::iterator _iter_;

	for(_iter_ = m_GuildMarkList.begin(); _iter_ != m_GuildMarkList.end(); _iter_++)
	{
		if( (*_iter_)->Get_GuildIndex() == nGuildIndex )
		{
			return;
		}
	}
	m_GuildMarkMutex.lock();
	m_GuildMarkStack.push(nGuildIndex);
	m_GuildMarkMutex.unlock();
	SetEvent(m_hWaitObject);
}

void CUIMgr::clearguildmark()
{
	list_guildmark::iterator it = m_GuildMarkList.begin();
	list_guildmark::iterator itEnd = m_GuildMarkList.end();

	CGuildMark* pMark;
	for( ; it != itEnd; ++it )
	{
		pMark = (*it);
		SAFE_DELETE(pMark);
	}

	m_GuildMarkList.clear();
}

unsigned __stdcall CUIMgr::ThreadDataLoad(void* pParam )
{
	CUIMgr* pTemp = (CUIMgr*)pParam;

	while(pTemp->ThreadMsg() != 0)
	{

	}

	return 1;
}

int	CUIMgr::ThreadMsg()
{
	try
	{
		DWORD dwResult = ::WaitForSingleObject(m_hWaitObject, INFINITE);
		if (dwResult == WAIT_FAILED)
		{
			return 0;
		}

		if( m_bIsThread == FALSE )
		{
			return 0;
		}

		while(1)
		{
			m_GuildMarkMutex.lock();

			if( m_GuildMarkStack.empty() )
			{
				m_GuildMarkMutex.unlock();
				break;
			}

			int nGuildIndex = m_GuildMarkStack.front();
			m_GuildMarkStack.pop();

			m_GuildMarkMutex.unlock();

			guildmark_create(nGuildIndex);
		}

		ResetEvent(m_hWaitObject);
	}
	catch(...)
	{
		return 0;
	}

	return 1;
}

void CUIMgr::guildmark_create(int nIndex)
{
	if(!m_phttpConnection)	return;

	CSurface* pSurface = NULL;
	char szTmp[256], szTmp1[256];
	ZeroMemory(szTmp , sizeof(szTmp ));
	ZeroMemory(szTmp1, sizeof(szTmp1));

	sprintf(szTmp , m_strGuildMarkURL.c_str() , nIndex%10, m_nServerIndex, nIndex);
	sprintf(szTmp1, GUILD_MARK_FILE, m_nServerIndex, nIndex);

	if(m_phttpConnection->ConnectDown(szTmp, szTmp1))
	{
		char buffff[512];
		sprintf( buffff, "%s\n" , szTmp );
		OutputDebugString( buffff );

		m_GuildMarkMutex.lock();
		m_GuildMarkTemp.push_back(nIndex);
		m_GuildMarkMutex.unlock();
	}

	pCMyApp->SignalPostLoad();
}

bool CUIMgr::guildmark_exist(int gidx)
{
	if( CommonConfig::Instance()->GetGuildMark() == false )
		return false;

	if( gidx <= 0 )
		return false;

	list_guildmark::iterator _iter_;

	for(_iter_ = m_GuildMarkList.begin(); _iter_ != m_GuildMarkList.end(); _iter_++)
	{
		if((*_iter_)->Get_GuildIndex() == gidx)
		{
			return true;
		}
	}

	return false;
}

void CUIMgr::guildmark_render(int gidx, float fx, float fy)
{
	if( CommonConfig::Instance()->GetGuildMark() == false )
		return;

	if(gidx <= 0)
		return;

	list_guildmark::iterator _iter_;

	for(_iter_ = m_GuildMarkList.begin(); _iter_ != m_GuildMarkList.end(); _iter_++)
	{
		if((*_iter_)->Get_GuildIndex() == gidx)
		{
			(*_iter_)->Render(m_hWnd, fx, fy);
			return;
		}

	}
}

void CUIMgr::PostLoadGuildMark()
{
	if( CommonConfig::Instance()->GetGuildMark() == false )
		return;

	char szFileName[MAX_PATH] = {0,};

	m_GuildMarkMutex.lock();

	list_guildtemp::iterator _iter_;
	for(_iter_ = m_GuildMarkTemp.begin(); _iter_ != m_GuildMarkTemp.end(); _iter_++)
	{
		int nIndex = *_iter_;
		CGuildMark* pMark = NULL;
		sprintf(szFileName, "%d_%d.wxy", m_nServerIndex, nIndex);
		pMark = CGuildMark::Create(nIndex, szFileName);

		m_GuildMarkList.push_back(pMark);
	}
	m_GuildMarkTemp.clear();
	m_GuildMarkMutex.unlock();
}

BOOL CUIMgr::AutoItemTake( float itemTakeRange )
{
	if( m_b_Attack ) //- ���� ���̶�� �������� ���� ���ô�.
		return FALSE;

	if( timeGetTime() - m_AutoItemTakeDelayTime < 800 )
		return FALSE;

	m_AutoItemTakeDelayTime = timeGetTime();

	CItemInfo *pItemInfo = NULL;
	CItemInfo *pTargetItem = NULL;

	LHItemInfoMap_it pr;

	float distance = itemTakeRange;
	float dist_temp;

	for (pr = pCMyApp->m_pUIMgr->m_iteminfo_map.begin(); pr != pCMyApp->m_pUIMgr->m_iteminfo_map.end(); pr++)
	{
		pItemInfo = (*pr).second;
		CItem *pItem = &pItemInfo->m_Item;

		if (pItemInfo->m_Item.m_Dropping < 0)
		{
			// �ϴ� ���� ����� �� ã�´�
			dist_temp = DistPlToPl( g_pRoh->m_wx, g_pRoh->m_wz, pItemInfo->m_Item.m_X, pItemInfo->m_Item.m_Z);

			if ( dist_temp < distance )
			{
				distance = dist_temp;
				pTargetItem = pItemInfo;

				if( distance <= 15.0f ) // �������� �ʰ� ���� ������ ����� �Ÿ���� �������� ����. for�� ��� ������ ����.
					break;
			}
		}
	}

	if( pTargetItem != NULL )
	{
		if( IsInvenLock() )
			return 1;

		char commOut[512];
		sprintf( commOut, "pick %d\n", pTargetItem->m_Item.m_Index);

		if ( DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pTargetItem->m_Item.m_X, pTargetItem->m_Item.m_Z) <= 15.0f)
		{
			if( g_pTcpIp )
			{
				g_pTcpIp->SendNetMessage(commOut);
			}
			// ��Ŷ�� ������ ���ÿ� pick�� �õ� �ߴٴ� �÷��׸� ����( by ���� )
			pCMyApp->m_pUIMgr->m_bPickLock = TRUE; ///pick_bug
		}
		else // �������� �ִ� ������ �̵��� ����.
		{
			pCMyApp->m_pUIMgr->m_bNextAction = TRUE;
			pCMyApp->m_pUIMgr->m_Action.nActionKind = 0;
			strcpy(pCMyApp->m_pUIMgr->m_Action.strCmd, commOut);

			if (g_bPath)
			{
				pCMyApp->MoveHeroT(pTargetItem->m_Item.m_X, pTargetItem->m_Item.m_Z);
			}
			else
			{
				pCMyApp->MoveHero( pTargetItem->m_Item.m_X, pTargetItem->m_Item.m_Z);
			}
		}
		return TRUE;
	}

	return FALSE;
}


bool CUIMgr::IsInvasionGuildChar(WORD ColorIndex)
{
	if( !g_pRoh || !g_pRoh->GetMyGuildData() )
		return false;

	CNkCharacter* pCha = GetCharacterByColorKey( ColorIndex );

	if( pCha == NULL )
		return false;

	if( g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCha->m_GuildIndex ) )
	{
		return true;
	}

	return false;
}


CNkCharacter* CUIMgr::GetChaFromPickColor( DWORD ColorIndex)
{
	return GetCharacterByColorKey(ColorIndex);
}

// ���̵�� �����̵� ���ϴ� ����- �Ӽ����� ������ �����̵��Ǵ� ���� �� ���� ���̾ �ϵ��ڵ�~~ �̤�
BOOL CUIMgr::IsTeleportArea(float wx, float wz, float roh_wx, float roh_wz)
{
	switch( pCMyApp->GetCurWorld() )
	{
	case WORLD_BOSSRAID_HUMAN:
		{
			BOOL bCenterArea = pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 3260,6510,3770,5960,4240,6490,3370,7030);

			if( bCenterArea
					&& pCMyApp->IsInsideRhombus(wx, wz, 2960,5780,3100,5660,3670,6220,3510,6370) )
				return FALSE;

			if( bCenterArea
					&& pCMyApp->IsInsideRhombus(wx, wz, 3890,6220,4460,5650,4610,5790,4020,6360) )
				return FALSE;

			if( bCenterArea
					&& pCMyApp->IsInsideRhombus(wx, wz, 3900,6740,4040,6590,4610,7170,4460,7300) )
				return FALSE;

			if( bCenterArea
					&& pCMyApp->IsInsideRhombus(wx, wz, 2940,7160,3520,6570,3670,6730,3100,7300) )
				return FALSE;

			bCenterArea = pCMyApp->IsInsideRhombus(wx, wz, 3260,6510,3770,5960,4240,6490,3370,7030);

			if( pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 2960,5780,3100,5660,3670,6220,3510,6370)
					&& bCenterArea)
				return FALSE;

			if( pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 3890,6220,4460,5650,4610,5790,4020,6360)
					&& bCenterArea)
				return FALSE;

			if( pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 3900,6740,4040,6590,4610,7170,4460,7300)
					&& bCenterArea)
				return FALSE;

			if( pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 2940,7160,3520,6570,3670,6730,3100,7300)
					&& bCenterArea)
				return FALSE;
		}
		break;

	case 19: // WORLD_MATRIX_2009
		if( m_nStoneState[0] ) // ���帶�� ���� ����Ʈ�� ���� �ִٸ� �Ʒ� �������� �����̵� �Ұ�
		{
			if( pCMyApp->IsInsideRhombus(wx, wz, 1470,10960,2010,10800,2250,11050,1980,11420) )
				return FALSE;
		}

		if( m_nStoneState[1]) // �̸̹� ��/�� ����Ʈ�� ��� ���� �ִٸ�
		{
			if( pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 5370,8530,5730,8200,5990,8400,5620,8740) )
			{
				if( pCMyApp->IsInsideRhombus(wx, wz, 5680,8250,5800,7970,6180,8140,5930,8440) )
					return FALSE;
			}

			if( pCMyApp->IsInsideRhombus(roh_wx, roh_wz, 5680,8250,5800,7970,6180,8140,5930,8440) )
			{
				if( pCMyApp->IsInsideRhombus(wx, wz, 5370,8530,5730,8200,5990,8400,5620,8740) )
					return FALSE;
			}
		}

		if( m_nStoneState[2])
		{
			if( pCMyApp->IsInsideRect(roh_wx, roh_wz, 6630, 5600, 7010, 5180) )
			{
				if( pCMyApp->IsInsideRect(wx, wz, 6700, 5250, 7030, 4800))
					return FALSE;
			}

			if( pCMyApp->IsInsideRect(roh_wx, roh_wz, 6700, 5250, 7030, 4800))
			{
				if( pCMyApp->IsInsideRect(wx, wz, 6630, 5600, 7010, 5180))
					return FALSE;
			}
		}

		if( m_nStoneState[3] ) // �ȱ׸��� ���� ����Ʈ�� ���� �ִٸ� �Ʒ� �������� �����̵� �Ұ�
		{
			if( pCMyApp->IsInsideRhombus(wx, wz, 10640,1580,11090,1290,11460,1740,11030,2010) )
				return FALSE;
		}
		break;
	default:
		return TRUE;
	}

	return TRUE;
}

bool CUIMgr::AddColorKeyMap(WORD colorkey, int index, int type , void * data)
{
	if( GetEntityByColorKey(colorkey, type) != -6)
		return false;

	LHEntityInfo * entity = new LHEntityInfo(index, type);
	m_colorkey_map.insert( LHColorKeyMap_vt(colorkey, entity) );

	return true;
}


bool CUIMgr::AddCharacter(CNkCharacter* target)
{
	if( !target )
		return false;

	AddColorKeyMap( target->m_wColorIdx , target->m_nCharIndex , 0 , target );
	m_character_map.insert( LHCharacterMap_vt(target->m_nCharIndex,target) );
	return true;
}

bool CUIMgr::AddMob(CNkMob* target)
{
	if( !target )	return false;

	AddColorKeyMap( target->m_wColorIdx , target->m_nVirId , 1 , target );
	m_mob_map.insert( LHMobMap_vt(target->m_nVirId,target) );
	return true;
}

bool CUIMgr::AddUserShopNpc(CUserShopNpc* target)
{
	if( !target )
		return false;

	AddColorKeyMap( target->m_wColorIdx , target->m_nVirId , 2 , target );
	m_usershopnpc_map.insert( LHUserShopNpcMap_vt(target->m_nVirId,target) );
	return true;
}

bool CUIMgr::AddPet(CNkPet* target)
{
	if( !target )
		return false;
	AddColorKeyMap( target->m_wColorIdx , target->m_nVirId , 3 , target );
	m_pet_map.insert( LHPetMap_vt(target->m_nVirId,target) );
	return true;
}

bool CUIMgr::AddItemInfo(CItemInfo* target)
{
	if( !target )
		return false;
	AddColorKeyMap( target->m_Item.m_wColorIdx , target->m_Item.m_Index , 4 , target );
	m_iteminfo_map.insert( LHItemInfoMap_vt(target->m_Item.m_Index,target) );
	return true;
}

void CUIMgr::DelColorKeyMap(WORD colorkey)
{
	safe_delete_associate_key(m_colorkey_map, colorkey);
}

void CUIMgr::DelCharacter(int index)
{
	CNkCharacter* target = GetCharacterByID(index);
	if( target )
		DelColorKeyMap(target->m_wColorIdx);

	safe_delete_associate_key(m_character_map, index);
}

void CUIMgr::DelMob(int index)
{
	if( m_AutoPlay && m_AutoPlay->IsRun() )
	{
		if( m_AutoPlay->m_pSelectedMob && m_AutoPlay->m_pSelectedMob->m_nVirId == index )
			m_AutoPlay->OutOfRange_Mob();
	}

	CNkMob* target = GetMobByID(index);
	if( target )
		DelColorKeyMap(target->m_wColorIdx);

	safe_delete_associate_key(m_mob_map, index);
}

void CUIMgr::DelUserShopNpc(int index)
{
	CUserShopNpc * target = GetUserShopNpcByID(index);
	if( target )
		DelColorKeyMap(target->m_wColorIdx);

	safe_delete_associate_key(m_usershopnpc_map, index);
}

void CUIMgr::DelPet(int index)
{
	CNkPet* target = GetPetByID(index);
	if( target )
		DelColorKeyMap(target->m_wColorIdx);

	safe_delete_associate_key(m_pet_map, index);
}

void CUIMgr::DelItemInfo(int index)
{
	if( m_AutoPlay && m_AutoPlay->IsRun() )
	{
		if( m_AutoPlay->m_pTargetItem && m_AutoPlay->m_pTargetItem->m_Item.m_Index == index )
			m_AutoPlay->OutOfRange_Mob();
	}

	CItemInfo* target = GetItemInforByID(index);
	if( target )
		DelColorKeyMap(target->m_Item.m_wColorIdx);

	safe_delete_associate_key(m_iteminfo_map, index);
}


void CUIMgr::ClearAll()
{
	safe_delete_associate(m_colorkey_map);
	safe_delete_associate(m_character_map);
	safe_delete_associate(m_mob_map);
	safe_delete_associate(m_usershopnpc_map);
	safe_delete_associate(m_pet_map);
	safe_delete_associate(m_iteminfo_map);
}


int	CUIMgr::GetEntityByColorKey(int key,int type)
{
	LHColorKeyMap_it it = m_colorkey_map.find(key);
	if( it!=m_colorkey_map.end() )
	{
		if( (*it).second->entity_type == type )
			return (*it).second->index;
	}

	return -6;
}


CNkCharacter * CUIMgr::GetCharacterByColorKey(WORD colorkey)
{
	int index = GetEntityByColorKey(colorkey,0);
	if( index == -6)
		return NULL;

	LHCharacterMap_it it = m_character_map.find(index);
	if( it!=m_character_map.end() )
		return (*it).second;

	return NULL;
}

CNkMob * CUIMgr::GetMobByColorKey(WORD colorkey)
{
	int index = GetEntityByColorKey(colorkey, 1);
	if( index == -6)
		return NULL;

	LHMobMap_it it = m_mob_map.find(index);
	if( it!=m_mob_map.end() )
		return (*it).second;

	return NULL;
}

CUserShopNpc * CUIMgr::GetUserShopNpcByColorKey(WORD colorkey)
{
	int index = GetEntityByColorKey(colorkey,2);
	if( index == -6)
		return NULL;

	LHUserShopNpcMap_it it = m_usershopnpc_map.find(index);
	if( it!=m_usershopnpc_map.end() )
		return (*it).second;

	return NULL;
}

CNkPet * CUIMgr::GetPetByColorKey(WORD colorkey)
{
	int index = GetEntityByColorKey(colorkey,3);
	if( index == -6)
		return NULL;

	LHPetMap_it it = m_pet_map.find(index);
	if( it!=m_pet_map.end() )
		return (*it).second;

	return NULL;
}

CItemInfo *	CUIMgr::GetItemInfoByColorKey(WORD colorkey)
{
	int index = GetEntityByColorKey(colorkey,4);
	if( index == -6)
		return NULL;

	LHItemInfoMap_it it = m_iteminfo_map.find(index);
	if( it!=m_iteminfo_map.end() )
		return (*it).second;

	return NULL;
}


CNkCharacter * CUIMgr::GetCharacterByID(int id)
{
	if( m_character_map.empty() || id == -6 )
		return NULL;

	LHCharacterMap_it it = m_character_map.find(id);
	if( it!=m_character_map.end() )
		return (*it).second;

	return NULL;
}

CNkMob * CUIMgr::GetMobByID(int id)
{
	if( m_mob_map.empty() || id == -6 )
		return NULL;

	LHMobMap_it it = m_mob_map.find(id);
	if( it!=m_mob_map.end() )
		return (*it).second;

	return NULL;
}

CUserShopNpc * CUIMgr::GetUserShopNpcByID(int id)
{
	if( m_usershopnpc_map.empty() || id == -6 )
		return NULL;

	LHUserShopNpcMap_it it = m_usershopnpc_map.find(id);
	if( it!=m_usershopnpc_map.end() || id == -6 )
		return (*it).second;

	return NULL;
}

CNkPet * CUIMgr::GetPetByID(int id)
{
	if( m_pet_map.empty() || id == -6 )
		return NULL;

	LHPetMap_it it = m_pet_map.find(id);
	if( it!=m_pet_map.end() )
		return (*it).second;

	return NULL;
}

CItemInfo * CUIMgr::GetItemInforByID(int id)
{
	if( m_iteminfo_map.empty() || id == -6 )
		return NULL;

	LHItemInfoMap_it it = m_iteminfo_map.find(id);
	if( it!=m_iteminfo_map.end() )
		return (*it).second;

	return NULL;
}

// [5/29/2008 �����]  ���̵�� ��Ȱ ��ų ���� üŷ �Լ�.
int  CUIMgr::Check_Skill_Resurrection( int skill_Index, CNkCharacter *pCha )
{
	if( g_ChaSkill.m_SkillIndex[skill_Index] == SKILL_A_RESURRECTION ) // ���������� ������ �ѰŶ��...
	{
		if( pCha->GetMotionState() == CHA_DEAD && pCMyApp->SkillConditionCheck(skill_Index) ) // ���� ������׸�...
		{
			pCMyApp->SetHeroAttGoCha( pCha );

			///070723 �Ϻ����׸���Ʈ ����
			g_pRoh->m_nResurrection_ChaId = pCha->m_nCharIndex; // �̰͵� ���⼭ �����ϵ��� ����.
			float fDist;
			fDist = DistPlToPlAbs(g_pRoh->m_wx, g_pRoh->m_wz, pCha->m_wx, pCha->m_wz);
			float att_Dist = pCMyApp->GetSkillDistance(skill_Index);

			if( att_Dist < fDist ) // �Ÿ��� �ʹ� �ָ�...
			{
				// �� ��ų�� ó���� ����� ������ �ٰ����� ������ �ʰ� �Ÿ��� �־ �ȵȴٰ� ���޼����� �ش�.
				//- IDS_SKILL_RANGEOUT:   ��ų�� �����Ÿ��� ����� ��ҵǾ����ϴ�.
				if( g_pNk2DFrame )
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_SKILL_RANGEOUT), -1);
			}
			else
			{
				pCMyApp->AttackMsgSend( skill_Index ); // ���⼭ ���Ƿ� ��Ŷ�� �����������.
				g_pRoh->SetMagicCha(pCMyApp->m_pHeroAttGoCha, SKILL_A_RESURRECTION);  // ���⼭ ������ �ٲ��.
			}
		}

		return 1; // �������� Ŭ���� ������ ���⼭ ����.
	}

	return 0;
}

bool CUIMgr::IsInvenLock()
{
	return false;
}

void CUIMgr::ConvertWorldPos(float x, float z, float& rx, float &rz)
{
	if( pCMyApp->GetCurWorld() == 1
			|| pCMyApp->GetCurWorld() == 2
			|| pCMyApp->GetCurWorld() == 5 )
	{
		rx = (x/(gMapExtention/4));
		rz = (int)(gMapHeight*4-(z/(gMapExtention/4)));
	}
	else
	{
		rx = (x/(gMapExtention/5));
		rz = (int)(gMapHeight*5-(z/(gMapExtention/5)));
	}
}

//=============================================================================
// by evilkiki 2010.01.
//=============================================================================
bool CUIMgr::Send_UseQuickItem(int vnum, int type, int slot, int index, char * param , bool need_lock)
{
	if( (Use_QuickItem_Type)type == Use_QuickItem__NotDefine )
		return false;

	char msg_buf[256];
	if( param )
		sprintf( msg_buf , "using_item %d %d %d %d %s\n" , vnum, type, slot, index , param );
	else
		sprintf( msg_buf , "using_item %d %d %d %d\n" , vnum, type, slot , index );

	LH_SEND_NET_MSG(msg_buf);

	if( need_lock )
		g_pRoh->m_bQuickSlotLock[slot] = TRUE;

	if( m_AutoPlay && m_AutoPlay->IsRun() )
		m_AutoPlay->SetSendMove(slot);

	return true;
}

bool CUIMgr::Send_UseQuickItem(CItem* pItem, char * param, bool need_lock)
{
	if( !pItem )
		return false;

	int type = GET_SHAPE(pItem);
	int slot_num = GetQuickIndex(pItem);
	int index = pItem->m_Index;
	int vnum = pItem->m_Vnum;

	char msg_buf[256];
	if( param )
		sprintf( msg_buf , "using_item %d %d %d %d %s\n" , vnum, type, slot_num, index , param );
	else
		sprintf( msg_buf , "using_item %d %d %d %d\n" , vnum, type, slot_num , index );

	LH_SEND_NET_MSG(msg_buf);

	if( m_AutoPlay && m_AutoPlay->IsRun() )
		m_AutoPlay->SetSendMove(slot_num);

	return true;
}

bool CUIMgr::Send_MoveToItem(int slot , int pack , int index)
{
	char msg_buf[256];
	sprintf( msg_buf , "moving_item %d %d %d\n" , slot , pack , index );
	LH_SEND_NET_MSG( msg_buf );

	if( m_AutoPlay && m_AutoPlay->IsRun() )
		m_AutoPlay->SetSendMove(slot);

	return true;
}

bool CUIMgr::Send_InvenToStash(char * /*param*/)
{
	return true;
}

bool CUIMgr::Send_StashToInven(char * /*param*/)
{
	return true;
}

// bool CUIMgr::Send_InvenToGuildStash()
// {
// 	char buf[256];
// 	buf[0] = 0;
// 	sprintf( buf , "mg stash p " , 0 );
//
// 	// 10�Ʃ�����
// 	// vnum
// 	// inven pack
// 	// warehouse pack
// 	// param( x,y )
//
// 	// 1�Ʃ�����
// 	// sprintf(m_MsgBuf, "mg stash t %d %d %d\n", slot_index, vnum, item_plus);
// 	return true;
//}

// bool CUIMgr::Send_GuildStashToInven()
// {
// 	char buf[256];
// 	buf[0] = 0;
// 	sprintf( buf , "mg stash g " , 0 );
//
//
// 	// 10�Ʃ�����
// 	// vnum
//
// 	sprintf(m_MsgBuf, "mg stash g %d %d %d %d\n", nVnum, m_pNkCha->m_CurPackNum, m_nPackNum, slot_index);
//
// 	// 1�Ʃ�����
// 	// sprintf(m_MsgBuf, "mg stash t %d %d %d\n", slot_index, vnum, item_plus);
//
// // if( m_pNkCha )
// // 	sprintf(m_MsgBuf, "mg stash g %d %d %d %d\n", nVnum, m_pNkCha->m_CurPackNum, m_nPackNum, slot_index);
// // m_bMsgWaiting = TRUE;
//
// 	return true;
//}

void CUIMgr::UseQuickItem(int slot_num)
{
	if( !g_pRoh )
		return;

	if (slot_num < 0 || slot_num >= QUICK_SLOT_NUM*QUICK_SLOT_PAGE)
		return;

	CItem * pQuickItem = g_pRoh->m_QuickSlot[slot_num];
	if( !pQuickItem )
		return;

	int type = GET_TYPE(pQuickItem);

	if( type == ITYPE_SUB )
	{
		if( !CanUseQuickSubItem(pQuickItem) )
			return;

		char msg_buf[128] = {0,};
		sprintf(msg_buf, "use_sub %d\n", slot_num);
		LH_SEND_NET_MSG( msg_buf );
	}
	else if( type == ITYPE_ETC )
	{
		if( !CanUseQuickItem(pQuickItem) )
			return;

		g_pNk2DFrame->m_iQuicSlotNum = slot_num;
		m_dwUseQuickTick = timeGetTime();
	}
}


bool CUIMgr::CanUseQuickSubItem(CItem *pUseQuickItem)
{
	if( !g_pRoh )
		return false;

	static int past_time = timeGetTime();
	int cur_time = timeGetTime();
	if( cur_time - past_time > 100)
		past_time = cur_time;
	else
		return false;

	int slot_num = GetQuickIndex(pUseQuickItem);
	if( slot_num == -1 )
		return false;

// 	if( (g_pRoh->GetMotionState() == CHA_B_BURNINGCRASH)
//		&& (GET_TYPE(pUseQuickItem) == ITYPE_SUB)
//		&& (GET_SHAPE(pUseQuickItem) == ISUB_CHAKRAM) )
//		return false;

	switch( GET_SHAPE(pUseQuickItem) )
	{
	case ISUB_SLAYER:
		break;
	case ISUB_WAND:
		break;
	case ISUB_COMPONENT:
		break;
	case ISUB_COLLECT:
		break;
	case ISUB_S_EQUIP:
		break;
	case ISUB_L_EQUIP:
		break;
	case ISUB_BLASTER:
		break;
	case ISUB_DSTONE:
		break;

	case ISUB_CHAKRAM:
		{
			if( g_pRoh->m_Stamina >= pUseQuickItem->m_Num4 )
			{
				if(pUseQuickItem->m_Special ==0 || pUseQuickItem->m_Special == 1)
				{
					pUseQuickItem->m_Special = 0;
					return false;
				}
				else
				{
					int cur_skill = 9 ;
					if(g_ChaSkill.m_SkillLevel[cur_skill] >= pUseQuickItem->m_MinLevel)
					{
						if(!pCMyApp->IsPeaceArea())
						{
							m_bChakram= TRUE;
							m_ChakramSlotNum = slot_num;
						}
						else
						{
							m_bChakram= FALSE;
							m_bChakramAtt = FALSE;
							m_ChakramSlotNum = -1;
						}
					}
					else
					{
						m_bChakram= FALSE;
						m_bChakramAtt = FALSE;
						m_ChakramSlotNum = -1;
					}
					return true;
				}
			}
		}
		break;
	case ISUB_BOOK:
		{
			if(pUseQuickItem->m_PlusNum==0)
			{
				return false;
			}
			else
			{
				if( g_pRoh->GetMyGuildData() != NULL &&
						pCMyApp->m_pHeroAttGoCha != NULL &&
						g_pRoh->GetMyGuildData()->CheckInvasionGuild( pCMyApp->m_pHeroAttGoCha->m_GuildIndex )  &&
						!( pCMyApp->GetCurWorld() == 4 &&
						   pCMyApp->IsInsideRect(pCMyApp->m_pHeroAttGoCha->m_wx, pCMyApp->m_pHeroAttGoCha->m_wz, 6800, 5450, 7250, 5000) ) )
				{
					m_bBookSpell= TRUE;
					m_BookSlotNum = slot_num;
					return true;
				}

				if(pCMyApp->IsPeaceArea())
				{
					m_bBookSpell= FALSE;
					m_BookSlotNum = -1;
				}
				else
				{
					m_bBookSpell= TRUE;
					m_BookSlotNum = slot_num;
				}
				return true;
			}
		}
		break;
	case IETC_SCROLL:
		break;
	case IETC_SUMMON:
		break;
	case IETC_SHELL:
		break;
	case IETC_CHARGE:
		break;
	}

// 	sprintf(m_commOut, "use_sub %d\n", slot_num);
// 	if (g_pTcpIp)
// 		g_pTcpIp->SendNetMessage(m_commOut);

	return false;
}

bool CUIMgr::CanUseQuickItem(CItem* pUseQuickItem)
{
	if(pCMyApp->IsSoccerZone())
		return false;

	if( CommonConfig::Instance()->GetUseItemSoccerZone() == false )
	{
		if(pCMyApp->IsColo(g_pRoh->m_wx, g_pRoh->m_wz) )
			return false;
	}	

	if (g_pNk2DFrame->IsVisiblePremiumExchange())
		return false;

	if( GET_ATT_FLAG(pUseQuickItem) & IATT_MAX_LEVEL ) // �ּҷ��� �ݵ��� �־����
	{
		if( g_pRoh->m_Level > GET_ITEM_MAXLEVEL(pUseQuickItem ) || g_pRoh->m_Level < GET_ITEM_LEVEL(pUseQuickItem) )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1850) , -1 );
			return false;
		}
	}
	else
	{
		if( g_pRoh->m_Level < GET_ITEM_LEVEL(pUseQuickItem) )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1850) , -1 );
			return false;
		}
	}



	switch(GET_SHAPE(pUseQuickItem))
	{
	case IETC_GEMSTONE:
		return UseGemStone(pUseQuickItem);
	case IETC_PART:
		return UsePart(pUseQuickItem);
	case IETC_RECOVERY:
		return UseRecovery(pUseQuickItem);
	case IETC_GEM:
		return UseGem(pUseQuickItem);
	case IETC_GIFT:
		return UseGift(pUseQuickItem);
	case IETC_QUICK:
		return UseForQuick(pUseQuickItem);
	case IETC_ETC:
		return UseEtc(pUseQuickItem);
	case IETC_GEMCHIP:
		return UseGemChip(pUseQuickItem);
	case IETC_BUFF:
		return UseBuff(pUseQuickItem);
	case IETC_WARP:
		return UseWarp(pUseQuickItem);
	case IETC_QUEST:
		return UseQuest(pUseQuickItem);
	case IETC_PET:
		return UsePet(pUseQuickItem);
	case IETC_PREMIUM: // ������� �̸�����
		return UsePremium(pUseQuickItem);
	case IETC_SKILL:
		return UseDocument(pUseQuickItem);
	case IETC_USING:
		return UseUsing(pUseQuickItem);
	case IETC_SCROLL:
		return UseScroll(pUseQuickItem);
	case IETC_SUMMON:
		return UseSummon(pUseQuickItem);
	case IETC_SHELL:
		return UseShell(pUseQuickItem);
	case IETC_CHARGE:
		return UseCharge(pUseQuickItem);
	case IECT_MOBSUMMON:
		return UseMobSummon(pUseQuickItem);
	case IETC_SUMMONNPC:
		return UseNpcSummon(pUseQuickItem);
	default:
		break;
	}

	return false;

// �������̽� ���°��� ������ ������ ���� �����!!!
// ���λ��� , ��������(���׻�����) , �����̾� ,
// ��ũ��, ��ũ��, �ϰ�����?
	return true;
}

bool CUIMgr::UseGemStone(CItem *pQuickItem)
{
	if( !g_pRoh )
		return false;

	int slot_num = GetQuickIndex(pQuickItem);
	if( slot_num == -1 )
		return false;

	if (!g_ChaSkill.CanUseSkill(SKILL_WORK_GEM))
	{
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_UNABLE_SEKONG_SKILL), -1);
		return false;
	}

	if (g_pRoh->m_Level < GET_ITEM_LEVEL(pQuickItem))
	{
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_UNABLE_SEKONG), -1);
		return false;
	}

	if (g_pRoh->m_bQuickSlotLock[slot_num])
	{
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_SEKONG_WORKING), -1);
		return false;
	}

	int NeedKitNum = GET_NEEDKIT_NUM(pQuickItem);
	if ( NeedKitNum > g_pRoh->GetKitsCount())
	{
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UIMGR_SCARCE_KIT), -1);
		return false;
	}

	char param[512];
	param[0] = 0;

	int count = 0;
	CItem *pItem = NULL;
	CItem *pItemPrev = NULL;
	CItem *pDelItem = NULL;

	for (int pack_num = 0; pack_num < PACK_NUM && count < NeedKitNum; pack_num++)
	{
		pItem = g_pRoh->m_Inven[pack_num];
		pItemPrev = NULL;
		pDelItem = NULL;

		while (pItem)
		{
			if (pItem->m_Vnum == 229)
			{
				if (pItemPrev)
				{
					pItemPrev->m_Next = pItem->m_Next;
				}
				else
				{
					g_pRoh->m_Inven[pack_num] = pItem->m_Next;
				}
				pDelItem = pItem;
				pItem = pItem->m_Next;

				char temp[128];
				sprintf( temp, "%d %d %d", pack_num, pDelItem->m_SlotX, pDelItem->m_SlotY ); // ���� ���� ��ȣ�� 100,101,102�� ������ �ڸ����� ���̱� ���� 0,1,2�� ����, ����ŰƮ�� �ε����� ������ ���� ���� x,y�� �������� ����. (05-10-04 ����)
				strcat( param , temp );
				g_pRoh->m_Slot[pack_num][pDelItem->m_SlotX][pDelItem->m_SlotY] = -1;

				SAFE_DELETE(pDelItem);

				count++;
				if (count >= NeedKitNum)
				{
					break;
				}
				else
				{
					strcat( param , " " );
					continue;
				}
			}
			else
			{
				pItemPrev = pItem;
				pItem = pItem->m_Next;
			}
		}
	}

	if( Send_UseQuickItem( pQuickItem , param , true ) )
		return false;

	return true;
}

bool CUIMgr::UsePart(CItem *pItem)
{
	// ������
	return false;
}

bool CUIMgr::UseRecovery(CItem *pItem)
{
	switch( GET_APPTO(pItem) )
	{
	case 0:	// ��
		if ( (int)g_pRoh->m_Vital >= (int)g_pRoh->m_MaxVital )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1845), -1 );
			return false;
		}
		break;
	case 1:	// ����
		if ( (int)g_pRoh->m_Mana >= (int)g_pRoh->m_MaxMana )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1846), -1 );
			return false;
		}
		break;
	case 2:	// ���׹̳�
		if ( (int)g_pRoh->m_Stamina >= (int)g_pRoh->m_MaxStamina )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1847), -1 );
			return false;
		}
		break;
	case 3:	// ����
		if ( (int)g_pRoh->m_Epower >= (int)g_pRoh->m_MaxEpower )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1848), -1 );
			return false;
		}
		break;
	case 4:	// ����
		// ���� ���̵���ġ��
		return false;
		break;
	case 5: // ��ü
		if ( (int)g_pRoh->m_Vital >= (int)g_pRoh->m_MaxVital &&
				(int)g_pRoh->m_Mana >= (int)g_pRoh->m_MaxMana  &&
				(int)g_pRoh->m_Stamina >= (int)g_pRoh->m_MaxStamina &&
				(int)g_pRoh->m_Epower >= (int)g_pRoh->m_MaxEpower )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1849), -1 );
			return false;
		}
		break;
	case 6: // ������ ��������
		break;
	case 7: // �̻���� ����
		break;
	case 8: // ����� %
		if ( (int)g_pRoh->m_Vital >= (int)g_pRoh->m_MaxVital )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1845), -1 );
			return false;
		}
		break;
	case 9: // ���� %
		if ( (int)g_pRoh->m_Mana >= (int)g_pRoh->m_MaxMana )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1846), -1 );
			return false;
		}
		break;
	case 10: // �����̸� %
		if ( (int)g_pRoh->m_Stamina >= (int)g_pRoh->m_MaxStamina )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1847), -1 );
			return false;
		}
		break;
	case 11: // ����� %
		if ( (int)g_pRoh->m_Epower >= (int)g_pRoh->m_MaxEpower )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1848), -1 );
			return false;
		}
		break;
	case 12: // �����,����,���׹̳�,����� % ȸ��
		if ( (int)g_pRoh->m_Vital >= (int)g_pRoh->m_MaxVital &&
				(int)g_pRoh->m_Mana >= (int)g_pRoh->m_MaxMana  &&
				(int)g_pRoh->m_Stamina >= (int)g_pRoh->m_MaxStamina &&
				(int)g_pRoh->m_Epower >= (int)g_pRoh->m_MaxEpower )
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1849), -1 );
			return false;
		}
		break;
	case 13: // ���
		{
			g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_ITEM), -1 );
			return false;
		}
		break;
	}




	char param[32] = {0,};
	int count = 0;
	if( pItem->m_Num9 )
		count = pItem->m_Special;
	sprintf( param , "%d" , count );
	Send_UseQuickItem(pItem , param );

	// moving_item ...
	return true;
}

bool CUIMgr::UseGem(CItem *pItem)
{
	// ������
	return false;
}

bool CUIMgr::UseGift(CItem *pItem)
{
	// ������
	return false;
}

// ���÷θ� ����ϴ� �����۵�!!!
// �ϴ��� �ϵ��ڵ����� ������!!!
bool CUIMgr::UseForQuick(CItem *pUseQuickItem)
{
	if( !pUseQuickItem )
		return false;

	if( pUseQuickItem->m_Vnum == 1596 )
	{
		if( g_pNk2DFrame )
			g_pNk2DFrame->ToggleHelpePetWindow(0);

		return true;
	}
	else if( pUseQuickItem->m_Vnum == 3795 )
	{
		return UseShout(pUseQuickItem);
	}

	return false;
}

bool CUIMgr::UseEtc(CItem *pUseQuickItem)
{	
	return false;
}

bool CUIMgr::UseGemChip(CItem *pItem)
{
	// ������
	return false;
}

bool CUIMgr::UseBuff(CItem *pUseQuickItem)
{
	enum Etc_Buff_Target // num1
	{
		Etc_Buff_Target__Mine,
		Etc_Buff_Target__Pet,
		Etc_Buff_Target__NotDefine
	};

	if( pUseQuickItem->m_Vnum == 688 && pCMyApp->GetCurWorld() != WORLD_GUILD_WAR )
	{
		g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1);
		return false;
	}


	char param[32] = {0,};
	int count = 0;
	if( pUseQuickItem->m_Num9 )
		count = pUseQuickItem->m_Special;
	sprintf( param , "%d" , count );
	Send_UseQuickItem(pUseQuickItem , param );

	return true;
}

bool CUIMgr::UseWarp(CItem *pItem)
{
	if( m_bRClickDown == 1 && pCMyApp->DrawCasting )
	{
		g_pRoh->HellDownFail( g_pRoh, NULL );
	}


	enum Etc_Warp_Type
	{
		Etc_Warp__Return,
		Etc_Warp__Trans,
		Etc_Warp__Zone,
		Etc_Warp__NotDefine
	};

	switch( pItem->m_Num0 )
	{
	case Etc_Warp__Return:
		{
			if( pCMyApp->IsPeaceArea() )
			{
				g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANNOT_USE_IN_PEACEZONE) , -1);
				return false;
			}

			if( pCMyApp->GetCurWorld() == WORLD_GUILD_WAR )
			{
				g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANT_USE_THIS_AREA) , -1);
				return false;
			}
			// ��ȯ��
			// ��ȭ�������Ұ� ó��
			// 172 Ư���������� �޼���
			// 173 Ư���������� �޼���
			// 174 Ư���������� �޼���
			// 307 ��׶��̸� ��ȭ���� ���Ұ�
			// 308 ��׶��̸� ��ȭ���� ���Ұ�
			// 516 ���ֱ�� ���� �������� �̵� : ����ó��
			// 611 ���ֱ�� ���� ������������ �̵� : ����ó��
			// 612 ���ֱ�� ���� ������������ �̵� : ����ó��
			Send_UseQuickItem( pItem , "0" , false );
			return true;
		}
		break;

	case Etc_Warp__Trans:
		{
			if( pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON1 || pCMyApp->m_nCurWorldIdx == WORLD_DUNGEON4 ||
				pCMyApp->m_nCurWorldIdx == WORLD_FORLORN_S3 )
			{
				g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_CANNOT_USEINZONE) , -1 );
				return false;
			}
			Send_UseQuickItem( pItem , "0" , false );
			return true;
		}
		return true;

	case Etc_Warp__Zone:
		{
			if( pItem->m_Num1 == 0 )
			{
				char param[32];
				param[0] = 0;

				if( pItem->m_Num2 < 0 )
					return false;

				sprintf( param, "%d" , pItem->m_Num2 );
				Send_UseQuickItem( pItem , param , false );
				return true;
			}
			if( pItem->m_Num1 == 1 )
			{
				g_pNk2DFrame->ShowGateWindow( true , pItem->m_Num2 , true );
				if( g_pNk2DFrame->GetGate() )
					g_pNk2DFrame->GetGate()->SetSlot( GetQuickIndex(pItem) );

				return true;
			}
			if( pItem->m_Num1 == 2 )
			{
				if( pItem->m_Vnum == 894 )
				{
					g_pNk2DFrame->ShowGateWindow( true , pItem->m_Num2 , false );
					if( g_pNk2DFrame->GetGate() )
					{
						g_pNk2DFrame->GetGate()->ExceptionItem();
						g_pNk2DFrame->GetGate()->SetSlot( GetQuickIndex(pItem) );
					}
				}
				else
				{
					g_pNk2DFrame->ShowGateWindow( true , pItem->m_Num2 , false );
					if( g_pNk2DFrame->GetGate() )
						g_pNk2DFrame->GetGate()->SetSlot( GetQuickIndex(pItem) );
				}
				return true;
			}
		}
		break;
	}

	return true;
}

bool CUIMgr::UseWarp(int slot, char * param)
{
	enum Etc_Warp_Type
	{
		Etc_Warp__Return,
		Etc_Warp__Trans,
		Etc_Warp__Zone,
		Etc_Warp__NotDefine
	};

	if( slot < 0 )
		return false;

	CItem * pUseQuickItem = g_pRoh->m_QuickSlot[slot];

	switch( (Etc_Warp_Type)pUseQuickItem->m_Num0 )
	{
	case Etc_Warp__Trans:
		break;
	case Etc_Warp__Zone:
		break;

	default:
		return false;
	}

	if( !Send_UseQuickItem(pUseQuickItem , param) )
		return false;

	return true;
}

bool CUIMgr::UseQuest(CItem *pUseQuickItem)
{
	if( m_bRClickDown == 1 && pCMyApp->DrawCasting )
	{
		g_pRoh->HellDownFail( g_pRoh, NULL );
	}

	enum Etc_Quest__Type
	{
		Etc_Quest__Random,
		Etc_Quest__Fix,
		Etc_Quest__Dependence,
		Etc_Quest__Document,

		Etc_Quest__EndOfEnum
	};

	char param[32];
	param[0] = 0;

	// ���������� �ɾ������?
	switch( pUseQuickItem->m_Num0 )
	{
	case Etc_Quest__Random:
		{
			if( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_Index != -1 )
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_HAVE_QUEST) , TYPE_NOR_OK, 1 );
				return false;
			}

			int max_level = GET_ITEM_MAXLEVEL(pUseQuickItem);
			if( max_level != 0 && g_pRoh->m_Level > max_level )
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_QUEST_CONFIRM_LEVEL) , TYPE_NOR_OK );
				return false;
			}

			if( pUseQuickItem->m_Special == 0 )
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_QUEST_UNABLE_MACHINE), TYPE_NOR_OK, 1 );
				return false;
			}

			sprintf( param , "%d" , pUseQuickItem->m_Special );
		}
		break;
	case Etc_Quest__Fix:
		{
			if( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_Index != -1 )
			{
				// 1671
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_HAVE_QUEST) , TYPE_NOR_OK, 1 );
				return false;
			}

			int max_level = GET_ITEM_MAXLEVEL(pUseQuickItem);
			if( max_level != 0 && g_pRoh->m_Level > max_level )
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_QUEST_CONFIRM_LEVEL) , TYPE_NOR_OK );
				return false;
			}

			sprintf( param , "1" );
		}
		break;
	case Etc_Quest__Dependence:
		{
			if( pCMyApp->IsPeaceArea() )
				return false;
		}
		break;
	case Etc_Quest__Document:
		{
			if( pUseQuickItem->m_Vnum == 1359 )
			{
				if( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_Index != -1 )
				{
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_HAVE_QUEST) , TYPE_NOR_OK, 1 );
					return false;
				}

				int max_level = GET_ITEM_MAXLEVEL(pUseQuickItem);
				if( max_level != 0 && g_pRoh->m_Level > max_level )
				{
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_QUEST_CONFIRM_LEVEL) , TYPE_NOR_OK );
					return false;
				}

				// �̰� �����ϴ°���?
				sprintf( param , "1" );
			}
			else if( pUseQuickItem->m_Vnum == 3843 )
			{
				break;
			}
			else
			{
				return false;
			}
		}
		break;
	}

	if( !Send_UseQuickItem( pUseQuickItem , param , false ) )
		return false;

	return true;
}

bool CUIMgr::UseQuest(int slot , char* param)
{
	return true;
}

bool CUIMgr::UsePet(CItem *pUseQuickItem)
{
	if( g_MyPetStatus.mode == MYPET_MODE_NONE )
	{
		// IDS_UQ_ERR_01
		// ����(����)�� �����ϴ�.
		return false;
	}

	enum Etc_Pet__Type
	{
		Etc_Pet__Call,
		Etc_Pet__Buff,
		Etc_Pet__EndOfEnum
	};

	switch( (Etc_Pet__Type)pUseQuickItem->m_Num0 )
	{
	case Etc_Pet__Call:
		{
// 			if( g_MyPetStatus.mode != MYPET_MODE_KEEP )
// 			{
// 				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_CANT_USE_ITEM) , -1 );
// 				return false;
// 			}
		}
		break;
	case Etc_Pet__Buff:
		{
			enum Etc_Pet_Buff__Type
			{
				Etc_Pet_Buff__Egg,
				Etc_Pet_Buff__Exp,
				Etc_Pet_Buff__Att,
				Etc_Pet_Buff__Def,
				Etc_Pet_Buff__EndOfEnum
			};

			switch( (Etc_Pet_Buff__Type)pUseQuickItem->m_Num1 )
			{
			case Etc_Pet_Buff__Egg:
				{
					if( g_MyPetStatus.mode != MYPET_MODE_EGG )
					{
						g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_CANT_USE_ITEM) , -1 );
						return false;
					}
				}
				break;
			case Etc_Pet_Buff__Exp:
			case Etc_Pet_Buff__Att:
			case Etc_Pet_Buff__Def:
				{
					if( g_MyPetStatus.mode <= MYPET_MODE_KEEP )
					{
						g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_CANT_USE_ITEM) , -1 );
						return false;
					}
				}
				break;
			}
		}
		break;
	}

	Send_UseQuickItem( pUseQuickItem , NULL , true );

	return true;
}

bool CUIMgr::UsePremium(CItem *pItem)
{
	enum Etc_Premium_Type
	{
		Etc_Premium__Guild,
		Etc_Premium__Char,
		Etc_Premium__Pet,
		Etc_Premium__CharMove,
		Etc_Premium__Adjust,

		Etc_Premium__EndOfEnum
	};

	int slot = GetQuickIndex( pItem );
	if( slot < 0 )
		return false;

	switch( pItem->m_Num0 )
	{
	case Etc_Premium__Char:
	case Etc_Premium__Guild:
		{
			if( IsStartZone() )
			{
				if( g_pRoh->m_bWanted )
				{
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CANT_USE_ITEM), TYPE_NOR_OK, 1 );
					return false;
				}

				g_pNk2DFrame->ShowPremiumExchange(pItem->m_Num0, slot);
			}
			else
			{
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_35), TYPE_NOR_OK, 1);
				return false;
			}
		}
		break;

	case Etc_Premium__CharMove:
		// ����� ���غ��� �𸣰���
		{
			if( IsStartZone() )
			{
				// ��� , ģ�����

				if( g_pRoh->m_bWanted )
				{
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CANT_USE_ITEM), TYPE_NOR_OK, 1 );
					return false;
				}

				if( g_pRoh->m_GuildIndex != 0 )
				{
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_11), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
					return false;
				}

				if( g_pRoh->m_UserShopLevel != 0 )
				{
					// ���λ���
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_10), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
					return false;
				}

				if( g_pRoh->m_bIsParty )
				{
					// ��Ƽ��
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_12), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
					return false;
				}

				if( g_pNk2DFrame->GetControlHelper() && g_pNk2DFrame->GetControlHelper()->m_MemberCount != 0 )
				{
					// �İ���
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_13), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
					return false;
				}

				if( g_pNk2DFrame->CheckPremiumChaMoveInfo() == FALSE )
					return false;

				Send_UseQuickItem(pItem,NULL,true);
			}
			else
			{
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_35), TYPE_NOR_OK, 1);
				return false;
			}
		}
		break;

	case Etc_Premium__Pet:
		{

			// ���� �̸�ǥ �� ����....1,2,5,8 ���Ұ�....

			if(g_MyPetStatus.mode == MYPET_MODE_NONE)
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_UIMGR_PET_NOTEXIST), TYPE_NOR_OK, 1 );
				return false;
			}
			else if(g_MyPetStatus.mode==MYPET_MODE_EGG)
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_UIMGR_PET_UNABLE_NAME), TYPE_NOR_OK, 1 );
				return false;
			}
			else if(g_MyPetStatus.mode==MYPET_MODE_KEEP || g_MyPetStatus.mode==MYPET_MODE_HOLD)
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_UIMGR_PET_UNABLE_NAME2), TYPE_NOR_OK, 1 );
				return false;
			}
			else if((g_MyPetStatus.level < 30))
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_UIMGR_PET_NOTENOUGHT_LEVEL), TYPE_NOR_OK, 1 );
				return false;
			}

			if( pCMyApp->GetCurWorld() == 1 ||
					pCMyApp->GetCurWorld() == 2 ||
					pCMyApp->GetCurWorld() == 5 ||
					pCMyApp->GetCurWorld() == 8 )
			{
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LHSTRING1832), TYPE_NOR_OK, 1 );
				return false;
			}

			if( g_pNk2DFrame->GetControlPetStatus() )
			{
				g_pNk2DFrame->GetControlPetStatus()->SetSlot( slot );
				g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_UIMGR_PET_MAKE_NAME), TYPE_EXCHANGE, POPUP_PETNAME );
				CMsgPopUp* p = g_pNk2DFrame->FindPopup(POPUP_PETNAME);
				if( p != NULL )
				{
					p->m_InputLine.SetEnable(FALSE);
				}
			}
		}
		break;

	case Etc_Premium__Adjust:
		// ��й������?
		Send_UseQuickItem(pItem,NULL,true);
		break;
	}

	return true;
}

bool CUIMgr::UsePremium(int slot , char * param)
{
	if( slot < 0 || !param || !param[0] )
		return false;

	if( !Send_UseQuickItem(g_pRoh->m_QuickSlot[slot] , param,true) )
		return false;

	return true;
}

bool CUIMgr::UseDocument(CItem *pItem)
{
	if( !g_pRoh )
		return false;

	int slot_num = GetQuickIndex( pItem );
	if( slot_num < 0 )
		return false;

	int nSkillItem_level = pItem->m_Num0;

	if( g_pRoh->m_Race == RACE_BULKAN )//��ĭ
	{
		if( g_ChaSkill.m_SkillLevel[17] + 1 == nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[19] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 1, slot_num);
		else if( g_ChaSkill.m_SkillLevel[17] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[19] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 2, slot_num);
		else if( g_ChaSkill.m_SkillLevel[17] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[19] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 3, slot_num);
		else
		{
			//IDS_SKILL_NOT  �ش� ��ų ������ ���� ��ų�� ���� ���� �ʽ��ϴ�.
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_SKILL_NOT), TYPE_NOR_OK, 1 );
			return false;
		}
	}
	else if( g_pRoh->m_Race == RACE_KAILIPTON )//ī�̸���
	{
		if( g_ChaSkill.m_SkillLevel[27] + 1 == nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[29] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10, slot_num);
		else if( g_ChaSkill.m_SkillLevel[27] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[29] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 11, slot_num);
		else if( g_ChaSkill.m_SkillLevel[27] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[29] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 12, slot_num);
		else
		{
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_SKILL_NOT), TYPE_NOR_OK, 1 );
			return false;
		}
	}
	else if( g_pRoh->m_Race == RACE_AIDIA )//���̵��
	{
		if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 100, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 101, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 101, slot_num);
		else
		{
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_SKILL_NOT), TYPE_NOR_OK, 1 );
			return false;
		}
	}
	else if( g_pRoh->m_Race == RACE_HUMAN )//�޸�
	{
		if( g_ChaSkill.m_SkillLevel[17] + 1 == nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[19] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 1000, slot_num);
		else if( g_ChaSkill.m_SkillLevel[17] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[19] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 1001, slot_num);
		else if( g_ChaSkill.m_SkillLevel[17] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[19] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 1002, slot_num);
		else
		{
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_SKILL_NOT), TYPE_NOR_OK, 1 );
			return false;
		}
	}
	else if( g_pRoh->m_Race == RACE_FREAK )//���̺긮��
	{
		if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level
				&& g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10000, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10001, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10002, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10003, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10004, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10005, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10006, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10007, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10008, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10009, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10010, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10011, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 != nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10012, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10013, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 != nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10014, slot_num);
		else if( g_ChaSkill.m_SkillLevel[20] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[21] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[22] + 1 == nSkillItem_level
				 && g_ChaSkill.m_SkillLevel[23] + 1 == nSkillItem_level )
			g_pNk2DFrame->ShowInterfaceWindow(true, DOCUMENT, 10015, slot_num);
		else if( g_pRoh->m_Race == RACE_PEROM )
		{
		}
		else
		{
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_SKILL_NOT), TYPE_NOR_OK, 1 );
			return false;
		}
	}

	if( g_pNk2DFrame->GetInterface(DOCUMENT) )
	{
		CControlDocument * doc = (CControlDocument*)g_pNk2DFrame->GetInterface(DOCUMENT);
		doc->SetSlot( slot_num );
	}

	return true;
}

bool CUIMgr::UseDocument(int slot, char * param)
{
	if( !Send_UseQuickItem( g_pRoh->m_QuickSlot[slot] , param ) )
		return false;

	return true;
}

bool CUIMgr::UseUsing(CItem *pUseQuickItem)
{
	if(m_bOnBattle)
		return false;

	enum Etc_Using__Type
	{
		Etc_Using__Normal,
		Etc_Using__Shop,
		Etc_Using__ExtSlot,
		Etc_Using__Upgrade,
		Etc_Using__BP,

		Etc_Using__EndOfEnum
	};

	switch( pUseQuickItem->m_Num0 )
	{
	case Etc_Using__Normal:
		{
			// �̳��� �ð������� �ִ�.?
			static DWORD dwOldTick = 0;
			if( dwOldTick == 0 )
			{
				dwOldTick = GetTickCount();
			}
			else
			{
				DWORD dwTick = GetTickCount();
				if( GetTickCount() - dwOldTick < 3000 )
				{
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_LHSTRING1831),-1);
					return false;
				}

				dwOldTick = GetTickCount();
			}
		}
		break;
	case Etc_Using__Shop:
		{
			if( pCMyApp->IsCurWorldID_BossraidZone() )
			{
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_CANT_USE_ITEM), TYPE_NOR_OK, 1);
				return false;
			}
		}
		break;
	case Etc_Using__ExtSlot:
		{

			// Ȱ��ȭ��!!!
			// ����Ҳ���??
			// ����Ҽ� ����!!!

		}
		break;
	case Etc_Using__Upgrade:
		{
		}
		break;
	case Etc_Using__BP:
		{
		}
		break;
	}

	Send_UseQuickItem( pUseQuickItem , NULL , false );

	return true;
}

bool CUIMgr::UseUsing(int slot, char * param)
{
	enum Etc_Using__Type
	{
		Etc_Using__Normal,
		Etc_Using__Shop,

		Etc_Using__EndOfEnum
	};

	return true;
}

bool CUIMgr::UseScroll(CItem * pUseQuickItem)
{
	// ���� �� ��Ÿ üũ!!!
	enum Etc_Scroll__Type
	{
		Etc_Scroll__Wand,
		Etc_Scroll__Book1,
		Etc_Scroll__Book2,
		Etc_Scroll__Book3,
		Etc_Scroll__Book4,
		Etc_Scroll__Book5,
		Etc_Scroll__Book6,
		Etc_Scroll__Self,
	};

	switch( pUseQuickItem->m_Num0 )
	{
	case Etc_Scroll__Wand:
		{
			if( !g_pRoh->m_Wearing[WEARING_SHIELD] )
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
				return false;
			}
			if( !(GET_ATT_FLAG(g_pRoh->m_Wearing[WEARING_SHIELD]) & IATT_SUB_WEAPON) ||
					pUseQuickItem->m_MinLevel != g_pRoh->m_Wearing[WEARING_SHIELD]->m_MinLevel )
			{
				g_pNk2DFrame->AddChatStr(IDS_ENCHANT_FAIL_ITEM,-1);
				return false;
			}
			if(g_pRoh->m_Wearing[WEARING_SHIELD]->m_Num3 <= g_pRoh->m_Wearing[WEARING_SHIELD]->m_PlusNum)
			{
				// ������ �ʿ䰡 ����. IDS_UQ_ERR_02
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
		}
		break;
	case Etc_Scroll__Book1:
	case Etc_Scroll__Book2:
	case Etc_Scroll__Book3:
	case Etc_Scroll__Book4:
	case Etc_Scroll__Book5:
	case Etc_Scroll__Book6:
		{
			CItem * pBookItem = NULL;
			int book_scrl_idx = 0;
			for(int i = 0; i<QUICK_SLOT_NUM*QUICK_SLOT_PAGE; i++)
			{
				if( g_pRoh->m_QuickSlot[i] && (GET_SHAPE(g_pRoh->m_QuickSlot[i]) == ISUB_BOOK))
				{
					book_scrl_idx = g_pRoh->m_QuickSlot[i]->m_Special;
					if( book_scrl_idx == pUseQuickItem->m_Vnum || book_scrl_idx ==0 )
					{
						if(pUseQuickItem->m_MinLevel <= g_pRoh->m_QuickSlot[i]->m_Num7 )
						{
							if(g_pRoh->m_QuickSlot[i]->m_Num3 > g_pRoh->m_QuickSlot[i]->m_PlusNum)
							{
								pBookItem = g_pRoh->m_QuickSlot[i];
								break;
							}
						}
					}
				}
			}

			if( !pBookItem )
			{
				// ������ ������ �� ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_03),-1);
				return false;
			}
		}
		break;
	case Etc_Scroll__Self:
		break;
	}

	Send_UseQuickItem( pUseQuickItem , NULL , true );

	return true;
}

bool CUIMgr::UseSummon(CItem * pUseQuickItem)
{
	enum Etc_Summon__Type
	{
		Etc_Summon__Summon,
		Etc_Summon__Skill,
	};

	if( g_pRoh->m_Mana < pUseQuickItem->m_Num4 )
	{
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1); // ������ �����մϴ�.
		return false;
	}

// 	switch( pUseQuickItem->m_Num4 )
// 	{
// 	case Etc_Summon__Summon:
// 		break;
// 	case  Etc_Summon__Skill:
// 		break;
// 	}

	Send_UseQuickItem( pUseQuickItem , NULL , true );

	return true;
}

bool CUIMgr::UseShell(CItem * pUseQuickItem)
{
	// ���� �� ��Ÿ üũ!!!
	enum Etc_Shell__Type
	{
		Etc_Shell__Bomb = 1,
		Etc_Shell__Fire,
		Etc_Shell__Laser,
		Etc_Shell__Mine,
		Etc_Shell__Roket,
		Etc_Shell__Roket2,
		Etc_Shell__Missile,
	};

	if( !g_pRoh->m_Wearing[WEARING_CLOAK] )
	{
		// �������� ��� ����.IDS_UQ_ERR_06
		g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
		return false;
	}
	if(!(GET_ATT_FLAG(g_pRoh->m_Wearing[WEARING_CLOAK])&IATT_SUB_WEAPON))
	{
		// �߸��� �������̴�.
		g_pNk2DFrame->AddChatStr(IDS_ENCHANT_FAIL_ITEM,-1);
		return false;
	}

	int slot_num = GetQuickIndex(pUseQuickItem);

	// WEARING_CLOAK
	switch( pUseQuickItem->m_Num0 )
	{
	case Etc_Shell__Bomb:
	case Etc_Shell__Fire:
	case Etc_Shell__Laser:
	case Etc_Shell__Mine:
	case Etc_Shell__Roket:
	case Etc_Shell__Roket2:
	case Etc_Shell__Missile:
		{
			if( g_pRoh->m_Wearing[WEARING_CLOAK]->m_Num9 != pUseQuickItem->m_Num0 )
			{
				//g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_ENCHANT_FAIL_ITEM),-1);
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
				return false;
			}
			if( pUseQuickItem->m_Num1 > g_pRoh->m_Wearing[WEARING_CLOAK]->m_Num3 - g_pRoh->m_Wearing[WEARING_CLOAK]->m_PlusNum )
			{
				// ������ �ʿ䰡 ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
		}
		break;
	}

	Send_UseQuickItem( pUseQuickItem , NULL , true );

	return true;
}

bool CUIMgr::UseCharge(CItem * pUseQuickItem)
{
	// ���� �� ��Ÿ üũ!!!
	enum Etc_Charge__Type
	{
		Etc_Charge__Chakram,
		Etc_Charge__Slayer,
		Etc_Charge__Stone,
		Etc_Charge__Yan,
		Etc_Charge__Panel,
		Etc_Charge__Cleaner,
	};

	switch( pUseQuickItem->m_Num0 )
	{
	case Etc_Charge__Chakram:
		{
			CItem * pChakramItem = NULL;
			for( int i=0 ; i<QUICK_SLOT_NUM*QUICK_SLOT_PAGE ; i++ )
			{
				if( g_pRoh->m_QuickSlot[i] )
				{
					int type = GET_TYPE(g_pRoh->m_QuickSlot[i]);

					if( type != ITYPE_SUB )
						continue;

					int shape = GET_SHAPE(g_pRoh->m_QuickSlot[i]);
					if( shape != ISUB_CHAKRAM )
						continue;

					pChakramItem = g_pRoh->m_QuickSlot[i];
					break;
				}
			}

			if( !pChakramItem )
			{
				// ��ũ���� ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_LHSTRING1852),-1);
				return false;
			}

			if( pUseQuickItem->m_Num1 > pChakramItem->m_Num3 - pChakramItem->m_Special )
			{
				// ������ �ʿ䰡 ����.
				return false;
			}
		}
		break;
	case Etc_Charge__Slayer:
		{
			if( !g_pRoh->m_Wearing[WEARING_CLOAK])
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
				return false;
			}
			if( !(GET_ATT_FLAG(g_pRoh->m_Wearing[WEARING_CLOAK])&IATT_SUB_WEAPON))
			{
				// �߸��� �������̴�.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
			if( pUseQuickItem->m_Num1 > g_pRoh->m_Wearing[WEARING_CLOAK]->m_Num3 - g_pRoh->m_Wearing[WEARING_CLOAK]->m_Special)
			{
				// ������ �ʿ䰡 ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
		}
		break;
	case Etc_Charge__Stone:
		{
			if(!g_pRoh->m_Wearing[WEARING_CLOAK])
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
				return false;
			}
			if( GET_SHAPE(g_pRoh->m_Wearing[WEARING_CLOAK]) != ISUB_DSTONE)
			{
				// �߸��� ������
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_ENCHANT_FAIL_ITEM),-1);
				return false;
			}
			if( pUseQuickItem->m_Num1 > g_pRoh->m_Wearing[WEARING_CLOAK]->m_Num3 - g_pRoh->m_Wearing[WEARING_CLOAK]->m_Special)
			{
				// �����ʿ� ����.

				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
		}
		break;
	case Etc_Charge__Yan:
		{
			if( !g_pRoh->m_Wearing[WEARING_BRACELET] )
			{
				// �������� ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
				return false;
			}
			if(g_pRoh->m_Wearing[WEARING_BRACELET] && g_pRoh->m_Wearing[WEARING_BRACELET]->m_Vnum != pUseQuickItem->m_Num2 )
			{
				// �߸��� ������ IDS_ENCHANT_FAIL_ITEM
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_ENCHANT_FAIL_ITEM),-1);
				return false;
			}
		}
		break;

	case Etc_Charge__Panel:
		{
			if( !g_pRoh->m_Wearing[WEARING_CLOAK])
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06),-1);
				return false;
			}
			if( !(GET_ATT_FLAG(g_pRoh->m_Wearing[WEARING_CLOAK])&IATT_SUB_WEAPON))
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
			if( pUseQuickItem->m_Num1 > g_pRoh->m_Wearing[WEARING_CLOAK]->m_Num3 - g_pRoh->m_Wearing[WEARING_CLOAK]->m_Special)
			{
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
		}
		break;

	case Etc_Charge__Cleaner:
		{
			if (!g_pRoh->m_Wearing[WEARING_SHIELD])
			{
				// �������� ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_06), -1);
				return false;
			}

			if (!(g_pRoh->m_Wearing[WEARING_SHIELD]->m_Vnum == 1022 || g_pRoh->m_Wearing[WEARING_SHIELD]->m_Vnum == 3067))
			{
				// �߸��� ������ IDS_ENCHANT_FAIL_ITEM
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_ENCHANT_FAIL_ITEM),-1);
				return false;
			}

			if( pUseQuickItem->m_Num1 > g_pRoh->m_Wearing[WEARING_SHIELD]->m_Num3 - g_pRoh->m_Wearing[WEARING_SHIELD]->m_PlusNum)
			{
				// �����ʿ� ����.
				g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_UQ_ERR_02),-1);
				return false;
			}
		}
		break;
	}

	Send_UseQuickItem( pUseQuickItem , NULL , false );

	return true;
}


bool CUIMgr::UseMobSummon(CItem * pUseQuickItem)
{
	// ����üũ�ʿ�
	enum Num0_Type
	{
		Num0_Type_mebius,
		Num0_Type_castlewar,
		Num0_Type_dmitron,
		Num0_Type_guild,
	};


	switch(pUseQuickItem->m_Num0)
	{
	case Num0_Type_mebius:

		if(! (g_pRoh->m_GuildLevel == 10))
		{
			return false;
		}

		if( !( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX || pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009 ) )
		{
			return false;
		}
		// ���ְ�
		break;
	case Num0_Type_castlewar:
		if( !g_pRoh->m_bCrystalOwner )
		{
			return false;
		}

		if( !( pCMyApp->m_nCurWorldIdx == WORLD_GUILD || pCMyApp->m_nCurWorldIdx == WORLD_FIELD || pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN) )
		{
			return false;
		}		// �渶,�α渶
		break;
	case Num0_Type_dmitron:

		if( g_pRoh->GetMyGuildData()->GetMyInfo().s_glevel < JOB_ASSISTANTMASTER )
		{
			return false;
		}

		if( !( pCMyApp->m_nCurWorldIdx ==WORLD_DMITRON_BATTLE ) )
		{
			return false;
		}
		// �渶,�α渶
		break;
	case Num0_Type_guild:

		if( g_pRoh->GetMyGuildData()->GetMyInfo().s_glevel < JOB_ASSISTANTMASTER )
		{
			return false;
		}

		if( !( pCMyApp->m_nCurWorldIdx == WORLD_GUILD_WAR ) )
		{
			return false;
		}
		// �渶?
		break;
	}

	Send_UseQuickItem( pUseQuickItem , NULL , false );

	return true;
}

bool CUIMgr::UseNpcSummon(CItem * pUseQuickItem)
{
	if( pUseQuickItem == NULL )
		return false;

	int type = GET_SHAPE(pUseQuickItem);
	int slot_num = GetQuickIndex(pUseQuickItem);
	int index = pUseQuickItem->m_Index;

	char msg_buf[256];
	sprintf( msg_buf , "check_npc_summon %d %d %d\n", type, slot_num, index);
	LH_SEND_NET_MSG(msg_buf);

	return true;
}

bool CUIMgr::UseShout(CItem* pUseQuickItem)
{
	if( pUseQuickItem == NULL )
		return false;

	int slot_num = GetQuickIndex(pUseQuickItem);

	g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_SHOUT_INPUT), TYPE_SHOUT, POPUP_CHAT_SHOUT, 30, 0, (void*)slot_num);
	CMsgPopUp* p = g_pNk2DFrame->FindPopup(POPUP_CHAT_SHOUT);
	if( p != NULL )
	{
		p->m_InputLine.SetEnable(FALSE);
	}

	return true;
}

void CUIMgr::StashPuts(int vnum , int ware_slot , int inven_pack , int item_index)
{
	g_pNk2DFrame->GetControlWareHouse()->StashPuts(vnum , ware_slot , inven_pack , item_index);
}

void CUIMgr::StashGets(int vnum , int ware_slot , int inven_pack , int item_index , int inven_x , int inven_y)
{
	g_pNk2DFrame->GetControlWareHouse()->StashGets(vnum , ware_slot , inven_pack , item_index , inven_x , inven_y);
}


int CUIMgr::GetQuickIndex(CItem* pQuickSlotItem)
{
	for(int i= 0 ; i< QUICK_SLOT_NUM*QUICK_SLOT_PAGE ; i++ )
	{
		if( g_pRoh->m_QuickSlot[i] && g_pRoh->m_QuickSlot[i]->m_Index == pQuickSlotItem->m_Index )
			return i;
	}

	return -1;
}


// �����ϰ�쿡��!!!
int	CUIMgr::GetNum2_ZoneCount(int value)
{
	int num_zone = 0;
	for( int i=0 ; i<22 ; i++ )
	{
		if( (1<<i) & value )
		{
			num_zone++;
		}
	}

	return num_zone;
}

bool CUIMgr::IsMatrix()
{
	if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX )
		return true;

	if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009 )
		return true;

	return false;
}

bool CUIMgr::IsStartZone()
{
	return (pCMyApp->m_nCurWorldIdx == WORLD_START)?true:false;
}

BOOL CUIMgr::GetLagrushPayment()
{
	if( !m_bPaymentLagrush )
		g_pNk2DFrame->InsertPopup("��׷��� ���� �� �̿��� �����մϴ�.",TYPE_NOR_OK, 1);
	return m_bPaymentLagrush;
}


void CUIMgr::SetAttackState(bool activate)
{
	m_b_Attack			= activate;
	m_b_MovingForAttack = activate;
	m_b_SecAttack		= activate;
	m_bChakramAtt		= activate;
	m_bChakram			= activate;
	m_bBookSpellAtt 	= activate;
	m_bBookSpell		= activate;
}

void CUIMgr::CloseTeleportItem()
{
	if(m_pTeleportItem)
	{
		delete m_pTeleportItem;
		m_pTeleportItem = NULL;
	}
	m_bIsTeleportItem = FALSE;
}

void CUIMgr::SetVisibleMob(int vnum, BOOL bVisible)
{
	LHMobVisibleMap::iterator itFind = m_mob_visible_map.find(vnum);
	if( itFind != m_mob_visible_map.end() )
	{
		(*itFind).second = bVisible;
		return;
	}

	m_mob_visible_map.insert(std::make_pair(vnum, bVisible));
}

BOOL CUIMgr::IsVisibleMob(int vnum)
{
	LHMobVisibleMap::iterator itFind = m_mob_visible_map.find(vnum);
	if( itFind != m_mob_visible_map.end() )
	{
		return (*itFind).second;
	}

	return TRUE;
}

void CUIMgr::LoadGuildMarkURL()
{
	PFILE* fp = NULL;
	fp = pfopen("data/GUILDMARK_URL.TXT", "rt");

	if( fp == NULL )
		return;

	char strTemp[MAX_PATH] = {0,};
	pfgets(strTemp, sizeof(strTemp), fp);
	m_strGuildMarkURL = strTemp;

	pfclose(fp);
}
