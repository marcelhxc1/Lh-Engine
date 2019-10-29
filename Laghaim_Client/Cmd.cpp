#include "stdafx.h"
#include <winuser.h>
#include <time.h>
#include <assert.h>
#include <boost/tokenizer.hpp> 
#include "main.h"
#include "Land.h"
#include "Nk2DFrame.h"
#include "NkCharacter.h"
#include "NkMob.h"
#include "UIMgr.h"
#include "Tcpipcon.h"
#include "TcpUtil.h"
#include "LoginDlg.h"
#include "GUtil.h"
#include "DecoObj.h"
#include "Frustum.h"
#include "D3DMath.h"
#include "WeatherMgr.h"
#include "NkKeyboard.h"
#include "SpecialItem.h"
#include "ControlBottom.h"
#include "ControlShop.h"
#include "ControlParty.h"
#include "ControlInven.h"
#include "ControlWareHouse.h"
#include "ItemProto.h"
#include "ChaAct.h"
#include "ChaSta.h"
#include "DirtSnd.h"
#include "LoadEffectSound.h"
#include "FxSet.h"
#include "Cmd.h"
#include "UIMgr.h"
#include "ControlLowGuildMaster.h"
#include "ControlMap.h"
#include "GuildHunt.h"
#include "Skill.h"
#include "ControlSkill.h"
#include "AlphaPopup.h"
#include "Path.h"
#include "Filtering.h"
#include "NoWhisper.h"
#include "NkPet.h"
#include "NkMyPet.h"
#include "controlpetstatus.h"
#include "controlpeiceshop.h"
#include "ControlScore.h"
#include "Event_Ancient.h"
#include "QuestData.h"
#include "Mp3Module.h"
#include "country.h"
#include "ControlTeleportItem.h"
#include "WarInfo.h"
#include "NKObjQuadNode.h"
#include "g_stringmanager.h"
#include "AutoMouse.h"
#include "BasicMenu.h"
#include "Sprite.h"
#include "ControlUpgrade.h"
#include "ControlUserShop.h"
#include "ControlCashShop.h"
#include "ControlHelper.h"
#include "SpiritMode.h"
#include "FxFollow.h"
#include "SvrMessage.h"
#include "PVPWidget.h"
#include "ControlHelpPet.h"
#include "PingTest.h"
#include "WarTax.h"
#include "WarRequest.h"
#include "ReservationWindow.h"
#include "s_guild_func.h"
#include "wanted_network_func.h"
#include "HackProcessMgr.h"
#include "WindowMgr.h"
#include "ControlGate.h"
#include "DmitronBattle.h"
#include "DmitronBattleTax.h"
#include "ControlGuildT.h"
#include "ControlPremiumServiceChaMove.h"
#include "AutoPlay_test.h"
#include "LockSmith.h"
#include "LHUI_OpEvent.h"
#include "Gamble.h"
#include "ControlStatus.h"
#include "ControlScore.h"
#include "LHUI_TakeBox.h"
#include "LHGlobal_String.h"
#include "BuffItemMgr.h"
#include "DataFriend.h"
#include "YutManager.h"
#include "ControlYutboard.h"
#include "FishingManager.h"
#include "FishingRewardManager.h"
#include "ControlFishing.h"
#include "ControlFishingReward.h"
#include "CommonConfig.h"
#include "SpeedCheck.h"
#include "DecardiBattleManager.h"
#include "ControlDecardiBattle.h"
#include "PacketSend.h"
#include "LottoManager.h"
#include "ControlLotto.h"
#include "SetItemEffMgr.h"

#pragma warning(disable : 4995)

#define IsSpace( c )	( c == 0x20 || ( c >= 0x09 && c <= 0x0D ) ) // �� ��ũ�� ���⼭ �ʿ��ؼ� ���� �߰�.(by ����) ///�����Է½ý��ۺ���

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;              
static boost::char_separator<char> sep(" \n", NULL, boost::drop_empty_tokens);

extern int	g_MatrixSvr;
extern float g_fDSDistance;
extern int g_EffectSound[];
extern float g_fTimeKey;
extern BOOL g_bDungeon;
extern BOOL g_bNewTerrainDungeon;
extern int g_SkillsNum;

// ����� ���� ��������
extern int		g_nMobRenNum;
extern int		g_nMobInNum;
extern int		g_nMobListNum;
extern int		g_nPlRenNum;
extern int		g_nPlInNum;
extern int		g_nPlListNum;
extern int		g_nItemListNum;

extern BOOL		g_bAdmin2;

extern BOOL		g_bPath;
extern DWORD	g_dwLangType;
extern DWORD	g_dwClientCountry;
extern CClrAlloc		 *g_ClrAlloc;
extern BOOL g_bMatrixMatch;
extern BOOL	g_bSalesView;
extern BOOL	g_bSendSalesOff;
extern BOOL	g_bNewTerrain;
extern BOOL g_bNewLetter;	//�ű� �޽����� �ִ°� �Ǵ� //���� �ý���
extern BOOL g_bGlobalMatrix; ///���������� �� Ŭ���̾�Ʈ ���� ����.



// [2008/5/8 Theodoric] point log
extern BOOL		g_bAdmin;
extern BOOL		g_bAdmin2;
extern bool		b_Lime;
extern bool		b_EXP;
extern bool		b_Damage;

extern DWORD	tab3_EXP;
extern DWORD	tab3_Lime;
extern DWORD	tab3_Dmg_base;
extern DWORD	tab3_Dmg_dam;
extern DWORD	tab3_Dmg_Last;

extern bool g_EventMad_Aleady;

extern void		G_DevAddPointString(char *str);
extern void		G_CatLocalTimeToStr( char* OUT strOut, char* IN strIN);

extern std::string GetMd5CheckSum();

int g_ii[20] = {0,};
BOOL g_bMoonEventContinue = FALSE;
int	g_nEventNum = -1;
int x = 0, z = 0, y = 0;
int g_nRun = 0;
float dir = 0.0f;
int vital = 0;
bool g_bFiltering = false;	// ���͸��� �Ҳ���?

int index[WEARING_NUM] = {0,};
int v_num[WEARING_NUM] = {0,};
int gem_num[WEARING_NUM] = {0,};
int special[WEARING_NUM] = {0,};

CNkCharacter *pCha = NULL, *pCha2 = NULL;
CNkMob *pMob = NULL, *pMob2 = NULL;
CNkPet *pPet = NULL, *pPet2 = NULL;

CPingTest PingTest;

CGuildCmd* g_pGuildCmd;
CWantedCmd* g_pWantedCmd;

enum eUseQuickError_Type
{
	eUseQuickError_None = -1,
	eUseQuickError_Invalid_Item ,
	eUseQuickError_Invalid_Slot ,
	eUseQuickError_Recovery ,
	eUseQuickError_Warp ,
	eUseQuickError_Buff ,
	eUseQuickError_Warp_Transport ,
	eUseQuickError_GemStone ,
	eUseQuickError_Premium ,
	eUseQuickError_Quest ,
	eUseQuickError_Pet ,
	eUseQuickError_Skill ,
	eUseQuickError_Using ,
	eUseQuickError_Scroll ,
	eUseQuickError_Summons ,
	eUseQuickError_Summon ,
	eUseQuickError_Shell ,
	eUseQuickError_Charge ,

	eUseQuickError_EndOfEnum
};

enum eMoveQuickError_Type
{
	eMoveQuickError_None = -1,
	eMoveQuickError_Invalid_Item,
	eMoveQuickError_Invalid_Slot,

	eMoveQuickError_Skillup,

	eMoveQuickError_EndOfEnum
};


char g_Buf[256] = "";
char g_Buf1[256] = "";
char g_Buf2[256] = "";
char g_Buf3[256] = "";
char g_Buf4[256] = "";

// ��ɾ� ó�� �Լ�..
void CmdIn(char *arg, CUIMgr *pMgr);
void CmdAppear(char *arg, CUIMgr *pMgr);
void CmdWalk(char *arg, CUIMgr *pMgr);
void CmdPlace(char *arg, CUIMgr *pMgr);
void CmdStop(char *arg, CUIMgr *pMgr);
void CmdRotateCharacter(char *arg, CUIMgr *pMgr); // ��� ������� ���⸸ �ٲ��ֱ� ���� ��Ŷ.
void CmdOut(char *arg, CUIMgr *pMgr);
void CmdAttack(char *arg, CUIMgr *pMgr);
void CmdSay(char *arg, CUIMgr *pMgr);
void CmdWearing(char *arg, CUIMgr *pMgr);
void CmdInven(char *arg, CUIMgr *pMgr);
void CmdExtra(char *arg, CUIMgr *pMgr);
void CmdPickExtra(char *arg, CUIMgr *pMgr);
void CmdQuick(char *arg, CUIMgr *pMgr);
void CmdRemoveAll(char *arg, CUIMgr *pMgr);
void CmdDrop(char *arg, CUIMgr *pMgr);
void CmdPick(char *arg, CUIMgr *pMgr);				// ���� �ڿ���..
void CmdPickup(char *arg, CUIMgr *pMgr);			// ������ ���� ȿ��
void CmdHour(char *arg, CUIMgr *pMgr);
void CmdWeather(char *arg, CUIMgr *pMgr);
void CmdStatus(char *arg, CUIMgr *pMgr);
void CmdAttackVital(char *arg, CUIMgr *pMgr);
void CmdKill(char *arg, CUIMgr *pMgr);
void CmdSocial(char *arg, CUIMgr *pMgr);
void CmdCombat(char *arg, CUIMgr *pMgr);
void CmdCharWear(char *arg, CUIMgr *pMgr);
void CmdCharEventWear(char *arg, CUIMgr *pMgr); ///�̺�Ʈ��������
void CmdCharRemove(char *arg, CUIMgr *pMgr);
void CmdCharEventWearRemove(char *arg, CUIMgr *pMgr); ///�̺�Ʈ��������
void CmdInfo(char *arg, CUIMgr *pMgr);
void CmdInfo2(char *arg, CUIMgr *pMgr);
void CmdNotice(char *arg, CUIMgr *pMgr); ///�����˾�â
void CmdAt(char *arg, CUIMgr *pMgr);
void CmdGoto(char *arg, CUIMgr *pMgr);
void CmdShopItem(char *arg, CUIMgr *pMgr);
void CmdShopSPItem(char *arg, CUIMgr *pMgr);	//�ɼǰ��� �߰��� �����۵� �������ְ� �ϴ� ���� by ���� ///BP����
void CmdShopRate(char *arg, CUIMgr *pMgr);
void CmdSpShopEnd(char *arg, CUIMgr *pMgr);
void CmdSkillLevel(char *arg, CUIMgr *pMgr);
void CmdSkillLevelAll(char *arg, CUIMgr *pMgr);
void CmdEffect(char *arg, CUIMgr *pMgr);
void CmdGoWorld(char *arg, CUIMgr *pMgr);
void CmdGoWorldFail(char *arg, CUIMgr *pMgr);
void CmdJump(char *arg, CUIMgr *pMgr);
void CmdEventNewYear(char *arg, CUIMgr *pMgr);	// Happy New Year Event
void CmdExchAsk(char *arg, CUIMgr *pMgr);		// ��ȯâ ����.
void CmdExch(char *arg, CUIMgr *pMgr);
void CmdExchStart(char *arg, CUIMgr *pMgr);
void CmdExchInvenTo(char *arg, CUIMgr *pMgr);
void CmdExchInvenFrom(char *arg, CUIMgr *pMgr);
void CmdExchMoney(char *arg, CUIMgr *pMgr);
void CmdPetExchOppInfo(char *arg, CUIMgr *pMgr);//// ���� �絵 ���� �Լ�
void CmdPetProduct(char *arg, CUIMgr *pMgr);	// ���� ���� ����
void CmdDelivStart(char *arg, CUIMgr *pMgr);	// ����� �޽��� ������ ��ȯ ����.
void CmdDeliv(char *arg, CUIMgr *pMgr);
void CmdDelivEnd(char *arg, CUIMgr *pMgr);		// ������ �� ���´ٴ� �޽���.
void CmdDelivFail(char *arg, CUIMgr *pMgr);
void CmdMs(char *arg, CUIMgr *pMgr);			// ���� �������̽� ����.
void CmdMsInvenTo(char *arg, CUIMgr *pMgr);
void CmdMsInvenFrom(char *arg, CUIMgr *pMgr);
void CmdSeMs(char *arg, CUIMgr *pMgr);			//wan:2004-12 ��������
void CmdMsUpgrade(char *arg, CUIMgr *pMgr);		// ���� ���׷��̵�
void CmdIChange(char *arg, CUIMgr *pMgr);		// �� ��ȯ ����.
void CmdChipExchange(char *arg, CUIMgr *pMgr);	// Gamble�� ����Ĩ ��ȯ.
void CmdJewelExchange(char *arg, CUIMgr *pMgr);
void CmdEventAncient(char *arg, CUIMgr *pMgr);
void CmdEventTree(char *arg, CUIMgr *pMgr);
void CmdWorked(char *arg, CUIMgr *pMgr);		//����?
void CmdUpgrade(char *arg, CUIMgr *pMgr);
void CmdParty(char *arg, CUIMgr *pMgr);
void CmdPv(char *arg, CUIMgr * pMgr);
void CmdSkill(char *arg, CUIMgr *pMgr);
void CmdGuildName(char *arg, CUIMgr *pMgr);
void CmdGuildGrade(char *arg, CUIMgr *pMgr);
void CmdMultiShot(char *arg, CUIMgr *pMgr);
void CmdEvent(char *arg, CUIMgr *pMgr);
void CmdVoiceChat(char *arg, CUIMgr *pMgr);
void CmdYouare(char *arg, CUIMgr *pMgr);		// who am i ��ɾ �����Ǵ� ���.
void CmdOpenCastle(char *arg, CUIMgr *pMgr);	// ������ ����.
void CmdCloseCastle(char *arg, CUIMgr *pMgr);
void CmdOpenDoor(char *arg, CUIMgr *pMgr);
void CmdOnBattle(char *arg, CUIMgr *pMgr);
void CmdBattleCount(char *arg, CUIMgr *pMgr);
void CmdTimeCount(char *arg, CUIMgr *pMgr);
void CmdStashItem(char *arg, CUIMgr *pMgr);			// ��ǰ ������ ����.
void CmdStashMoney(char *arg, CUIMgr *pMgr);
void CmdStashTo(char *arg, CUIMgr *pMgr);
void CmdStashFrom(char *arg, CUIMgr *pMgr);
void CmdStashEnd(char *arg, CUIMgr *pMgr);
void CmdLevelup(char *arg, CUIMgr *pMgr);		// level up
void CmdMsg(char *arg, CUIMgr *pMgr);			// ���ο� �޽��� �ڽ�
void CmdMsg2(char *arg, CUIMgr *pMgr);			// �޼��� ��ȣ�� �޾Ƽ� ����ϴ� ��� ///�����޼���
void CmdChangeSex(char *arg, CUIMgr *pMgr);
void CmdChangeHair(char *arg, CUIMgr *pMgr);
void CmdWarTax(char *arg, CUIMgr *pMgr);		// ������ ����¡�� ����
void CmdWarReq(char *arg, CUIMgr *pMgr);		// ������ ��û
void CmdWarReqFail(char *arg, CUIMgr *pMgr);
void CmdGuildLevel(char *arg, CUIMgr *pMgr);	// ��� ������ ��´�.
void CmdGWar(char *arg, CUIMgr *pMgr);			// ����Ʋ ����.
void CmdMyPet(char *arg, CUIMgr *pMgr);			// �ֿϵ��� ����...
void CmdPetStatus(char *arg, CUIMgr *pMgr);
void CmdKeepInfo(char *arg, CUIMgr *pMgr);
void CmdPetShop(char *arg, CUIMgr *pMgr);
void CmdPetSocial(char *arg, CUIMgr *pMgr);
void CmdSky(char *arg, CUIMgr *pMgr);				// ���༮ ����
void CmdChaCondition(char *arg, CUIMgr *pMgr);		//ĳ���� ����(��ȭ,���� ����)
void CmdConDistruction(char *arg, CUIMgr *pMgr);	//���� �迭�ı� ����
void CmdSubAttackVital(char *arg, CUIMgr *pMgr);	//��������� attackvital
void CmdUseQuickSubItem(char *arg, CUIMgr *pMgr);	//�������� ����������� ������
void CmdEffectSubItem(char *arg, CUIMgr *pMgr);		//å�� ��������� Ư��ȿ��
void CmdSubAttack(char *arg, CUIMgr *pMgr);			//������� ������.
void CmdAssembly(char *arg, CUIMgr *pMgr);			//�޸��� ����������.
void CmdCombine(char *arg, CUIMgr *pMgr);			//������� ������� �־�����.
void CmdSummonMob(char *arg, CUIMgr *pMgr);			//���� ��ȯ��.
void CmdChaotic(char *arg, CUIMgr *pMgr);			//ī���� �Ǿ�����...1023
void CmdGuildPk(char *arg, CUIMgr *pMgr);			//������� ���� ������..1023
void CmdPk(char *arg, CUIMgr *pMgr);				//���� ������....1111
void CmdMultiAttack(char *arg, CUIMgr *pMgr);		//0108 �����̾�Ʈ�� ��Ƽ����
void CmdQuest(char *arg, CUIMgr *pMgr);				//0318 ����Ʈ
void CmdRingCombine(char *arg, CUIMgr *pMgr);		//0407 ���� ����
void CmdNecklaceCombine(char *arg, CUIMgr *pMgr);	// ����� �ռ� ///��
void CmdQuestExchange(char *arg, CUIMgr *pMgr);
void CmdSales(char *arg, CUIMgr *pMgr);				// ��� ���� �޽��� ó��
void CmdParentsDay(char *arg, CUIMgr * pMgr);
void CmdRoomListStart(char *arg, CUIMgr *pMgr);		// ��Ʈ���� ���� ���� �޽���
void CmdRoomList(char *arg, CUIMgr *pMgr);
void CmdEnterRoom(char *arg, CUIMgr *pMgr);
void CmdTRoom(char *arg, CUIMgr *pMgr);
void CmdTwPackage(char* arg, CUIMgr *pMgr );		// ��Ű�� ���Կ��� ó�� �޽��� ( �븸 )
void CmdMalId(char *arg, CUIMgr *pMgr);				// �����̽þ� �� �̵� �κ� ó��
void CmdPlatinumExch(char *arg, CUIMgr *pMgr);		// �÷�Ƽ�� ���� �޽���
void CmdSummerEvent(char *arg, CUIMgr *pMgr);		// ���� ��� �̺�Ʈ ���� �޽���
void CmdDictionary(char *arg, CUIMgr *pMgr);		// ���丶�콺 ������� (�ܾ���)
void CmdQnA(char *arg, CUIMgr *pMgr);				// ���丶�콺 ������� (����ý���) ///QnA
void CmdQuiz(char *arg, CUIMgr *pMgr);
void CmdFreeUser( char* arg, CUIMgr* pMgr );		// ���� �̺�Ʈ
void CmdLoadZonePos(char *arg, CUIMgr *pMgr);		// ���� ��� ���� �ý���
void CmdUserType(char *arg, CUIMgr *pMgr);			// �Ǿ��� ���� Ȯ�� �ý���
void CmdDropCandy(char *arg, CUIMgr *pMgr);			// �ջ��� �̺�Ʈ�� �ӽ�...
void CmdDropApple(char *arg, CUIMgr *pMgr);			// �ջ��� �̺�Ʈ�� �ӽ�...

//  [3/23/2009 ppmmjj83] �Ϻ���û - ��� / ���� / �ҵ�


void CmdDropStarCandy(char* arg, CUIMgr *pMgr);		// ������ �̺�Ʈ�� �ӽ�...
void CmdStashPut( char *arg, CUIMgr *pMgr );		// nate - â�� ������ �ټ� �̵�, �κ� -> â��
void CmdStashGet( char *arg, CUIMgr *pMgr );		// nate - â�� ������ �ټ� �̵�, â�� -> �κ�
void CmdUserIndex( char *arg, CUIMgr *pMgr );		// ���� �ε���
void CmdUserId( char *arg, CUIMgr *pMgr );			// ���� ID
void CmdPostReceive(char *arg, CUIMgr *pMgr);		// ���� �����޽���
void CmdMiss( char* arg, CUIMgr* pMgr );			// nate 2004 - 4 : Crash_Miss
void CmdBlock( char* arg, CUIMgr* pMgr );			// Block ȿ��. ///��
void CmdEventPoint( char* arg, CUIMgr* pMgr );		// nate 2005-05-09 : �̺�Ʈ����Ʈ(EP)ȹ��� ���� �޼����� ���� ��Ÿ��
void CmdExchPut( char* arg, CUIMgr* pMgr );			// nate 2004 - 4 : exchange
void CmdExchGet( char* arg, CUIMgr* pMgr );
void CmdDecardiCastleWarTime( char* arg, CUIMgr* pMgr );	// nate 2004 - 4 : CastleWar
void CmdDecardiCaslteWarGift( char* arg, CUIMgr* pMgr );	// nate 2004 - 5 : CastleWar
void CmdPKItemDrop(char* arg, CUIMgr* pMgr);				//PK�� ������ ���//�߱��� �ش�
void CmdFireWork(char* arg, CUIMgr* pMgr);					// Firework(LyuL)
void CmdMixItem(char* arg, CUIMgr* pMgr);					// Mixitem(LyuL)
void CmdGuildHunt( char* arg, CUIMgr* pMgr );				// nate 2004 - 9 : GuildHunt
void CmdGuildHuntDoor( char* arg, CUIMgr* pMgr );
void CmdDecardiGuildIndex( char* arg, CUIMgr *pMgr );		// nate 2004 - 10 : Decardi Guild Index Setting
void CmdUpgradeBR(char* arg, CUIMgr *pMgr );				// 2004.10.14 / Lyul / �߰�. (����)
void CmdHackCheck( char* arg, CUIMgr* pMgr );				// nate 2004 - 11 : Hack Program Check
void CmdDstone( char* arg, CUIMgr* pMgr );
void CmdShopOpen(char *arg, CUIMgr *pMgr);					//wan:2004-12	ȭ��Ʈȥ ���� �߾ӱ��� Ÿ�� ��
void CmdMini( char *arg, CUIMgr* pMgr );	// nate 2005-03-11 : Matrix -  ��Ʈ���� : �̴ϸ� ���� ����Ʈ ���
void CmdMatBP( char *arg, CUIMgr* pMgr );	//wan:2005-3 : ��Ʈ���� ���� ��Ʋ����Ʈ
void CmdBattle( char *arg, CUIMgr* pMgr );	//��Ʈ���� ��Ʋ ��ŸƮ, ����
void CmdCombo( char* arg, CUIMgr* pMgr );	// nate 2005-04-22 : �޺�����Ʈ ���
void CmdItemExtraInfo( char* arg, CUIMgr* pMgr );  // 050711 �ð��� ������ ��Ŷ.(by ����) ///�ð���������
void CmdSquad( char* arg, CUIMgr* pMgr );	// nate 2005-07-08 : Summon Squad
void CmdUpdateItem( char* arg, CUIMgr* pMgr );	// ������ ���� ���ſ� ���� ��Ŷ(05-10-21). ///�Ź���ȭ�ý���
void CmdNpcUpgrade( char* arg, CUIMgr* pMgr ); // ��ȭ,��ȯ,���� �� NPC�� ���� ���׷��̵� ��Ŷ. ///�Ź���ȭ�ý���
void CmdGuildPos( char* arg, CUIMgr* pMgr ); // ���� ��ġ ã�� ��Ŷ. ///�̴ϸʱ���ã��
void CmdFillItem( char* arg, CUIMgr* pMgr ); // ������ ������ ��Ŷ. (��ȭ ������ ���� ������ �׷����� ���� �̰� ����ϱ�� ��.) ///�׷�����
void CmdMvSkill( char* arg, CUIMgr* pMgr ); //mungmae 2005-11-16 : ��ĭ �ö���ũ����
void CmdUserShop( char* arg, CUIMgr* pMgr ); ///���λ���
void CmdNpcWear( char* arg, CUIMgr* pMgr ); // Npc���� ��� ������ ���� ��Ŷ. ����� �������� NPC�� �����Ѵ�. ///�������� �� �߰�
void CmdProcess( char* arg, CUIMgr* pMgr ); //������
void CmdProcessInvenTo(char *arg, CUIMgr *pMgr);
void CmdProcessInvenFrom(char *arg, CUIMgr *pMgr);
void CmdBpShopList(char *arg, CUIMgr *pMgr); // BP������ ����Ʈ(NPC �ε���)�� �޾ƿ��� ��Ŷ. �� �ε����� ���� BP���� �޴��� ��ư�� �׼��� �ɾ�д�.
void CmdWorldCup(char *arg, CUIMgr *pMgr); // mungmae 2006/05/30 ������ �ð� & ���ھ� ���� ��Ŷ
void CmdUseEffect(char *arg, CUIMgr *pMgr); // mungmae 2006/06/09 �Ϲ� ����Ʈ ���� ��Ŷ
void CmdMultiShop( char *arg, CUIMgr *pMgr ); ///�������
void CmdPetEffect(char *arg, CUIMgr *pMgr); // ���� ��ų� ���̴� ��Ŷ
void CmdPetResult(char *arg, CUIMgr *pMgr); // ���� ��ȭ,��ų���� ��� ��Ŷ.
void CmdPetChange(char *arg, CUIMgr *pMgr); // ���� ���� ���� ��� ��Ŷ.
void CmdSupport(char *arg, CUIMgr *pMgr); // �İ���
void CmdSpirit(char *arg, CUIMgr *pMgr); // ���Ǹ�
void CmdMobSay(char *arg, CUIMgr *pMgr); // ���� ������ �� ǳ����
void CmdAlive(char *arg, CUIMgr *pMgr);
void CmdAttChange(char *arg, CUIMgr *pMgr); // ������ �Ӽ����� ���. ///�δ�1
void CmdEventAction(char *arg, CUIMgr *pMgr); // Ư������ �̺�Ʈ ���� ���� ��Ŷ. ///�δ�1
void CmdRevival(char *arg, CUIMgr *pMgr); // ��Ȱ ����
void CmdSkillCoolTime( char *arg, CUIMgr *pMgr ); // ������ ��Ÿ�� ���� ��Ŷ ///�������ູ��Ÿ���� �������� �����ϵ��� �ٲ��.
void CmdCheckJoin(char *arg, CUIMgr *pMgr); ///�븸ű��� ��Ŷ. �ٸ� ������ �ڽ��� ������ ����������� �˸�.
void CmdNvNWinner(char *arg, CUIMgr *pMgr); ///�������¸� ��ũ ǥ��.
void CmdStashCInfo(char *arg, CUIMgr *pMgr); // [4/20/2007 Theodoric] �±� ���� â�� ���� ��Ŷ
void CmdPingTest(char *arg, CUIMgr *pMgr);
void CmdEventWearTime(char *arg, CUIMgr *pMgr ); ///�̺�Ʈ��������
void CmdEventWearing(char *arg, CUIMgr *pMgr); ///�̺�Ʈ��������
void CmdEnchant( char *arg, CUIMgr *pMgr ); // [2/27/2007 Theodoric] ��þƮ
void CmdRepair( char *arg, CUIMgr *pMgr );  //  [2/27/2007 Theodoric] ������ ������ ���� (��þ�� �������� �� �̸� ����� ����)
void CmdPVP(char *arg, CUIMgr *pMgr); ///�������
void CmdSVN(char *arg, CUIMgr *pMgr); //���� �ε��� �޽���
void CmdGuildSystem(char *arg, CUIMgr *pMgr);
void CmdWantedSystem(char *arg, CUIMgr *pMgr);
void Cmdkillporc(char *arg, CUIMgr *pMgr);
void CmdHelpPet(char *arg, CUIMgr *pMgr ); ///�굵��
void CmdYut(char *arg, CUIMgr *pMgr);
void CmdSiren(char* arg, CUIMgr* pMgr);	// [9/11/2007 Theodoric] Siren
void CmdOccp(char* arg, CUIMgr *pMgr); // ���Ʈ�� ������
void CmdBossRaidAttack(char* arg, CUIMgr* pMgr);
void CmdBossRaidKill(char* arg, CUIMgr* pMgr);
void CmdBossRaidLicense(char* arg, CUIMgr* pMgr);
void CmdBossRaidFinalRank(char* arg, CUIMgr* pMgr);
void CmdSvrChannelNum(char* arg, CUIMgr* pMgr);
void CmdPremium(char* arg, CUIMgr* pMgr);

void CmdLaghaimPoint(char* arg, CUIMgr* pMgr);
void CmdLPShopList(char *arg, CUIMgr *pMgr) ;

void CmdBossraidHonorList(char *arg, CUIMgr *pMgr);
void CmdBossraidHeroPrivilege(char *arg, CUIMgr *pMgr);
void CmdEventWearFlag(char *arg, CUIMgr *pMgr);
void CmdSetItem(char *arg, CUIMgr *pMgr);
void CmdHeroInfo(char *arg, CUIMgr *pMgr);
void CmdInitInven(char *arg, CUIMgr *pMgr);
void CmdMatrixMsg(char *arg, CUIMgr *pMgr);
void CmdDeleteItem(char *arg, CUIMgr *pMgr);
void CmdRulletSystem(char *arg, CUIMgr *pMgr);
void CmdStudentList(char * arg, CUIMgr *pMgr);

void CmdLagrush( char* arg, CUIMgr* pMgr );
void CmdLagrushTime(char* arg, CUIMgr* pMgr);

void CmdLockSmith(char* arg, CUIMgr* pMgr);
void CmdMoveValue(char *arg, CUIMgr *pMgr);

void CmdArupakaMoveValue(char *arg, CUIMgr *pMgr);

void CmdBuyItemFail(char* arg, CUIMgr* pMgr);

void CmdLagrushItemResult(char*arg, CUIMgr*pMgr);
void CmdUsedQuickItem(char*arg, CUIMgr*pMgr);
void CmdMovedItem(char*arg, CUIMgr*pMgr);
void CmdRevival_Rcv(char*arg, CUIMgr*pMgr);
void CmdStashPutS(char*arg, CUIMgr*pMgr);
void CmdStashPutM(char*arg, CUIMgr*pMgr);
void CmdStashGetS(char*arg, CUIMgr*pMgr);
void CmdStashGetM(char*arg, CUIMgr*pMgr);
void CmdMovedApple(char*arg, CUIMgr*pMgr);
void CmdGetGoodsLists(char*arg, CUIMgr*pMgr);
void CmdGetPresentLists(char*arg, CUIMgr*pMgr);
void CmdGetGoodsResult(char*arg, CUIMgr*pMgr);
void CmdGetPresentResult(char*arg, CUIMgr*pMgr);
void CmdResultCaru(char*arg, CUIMgr*pMgr);
void CmdBuffEx(char*arg, CUIMgr*pMgr);
void CmdUpEnergy(char* arg, CUIMgr* pMgr);
void CmdItemMake(char*arg, CUIMgr*pMgr);
void CmdItemSeparate(char*arg, CUIMgr*pMgr);
void CmdBuffMakeMake(char*arg, CUIMgr*pMgr);
void CmdBuffMakeGatcha(char*arg, CUIMgr*pMgr);
void CmdBuffMakeMedal(char*arg, CUIMgr*pMgr);
void CmdContinueSkill(char*arg, CUIMgr*pMgr);
void CmdMaStone(char*arg, CUIMgr*pMgr);
void CmdShutdown(char*arg, CUIMgr*pMgr);
void CmdBuffItemInfo(char*arg, CUIMgr*pMgr);
void CmdCharacterScaling(char*arg, CUIMgr*pMgr);
void CmdFeverTime(char* arg, CUIMgr* pMgr);
void CmdNameHide(char* arg, CUIMgr* pMgr);
void CmdFriend(char* arg, CUIMgr* pMgr);
extern void RecvFriend(char* arg);

void CmdNVisible(char* arg, CUIMgr* pMgr);
void CmdYutThrow(char* arg, CUIMgr* pMgr);
void CmdYutInfo(char* arg, CUIMgr* pMgr);
void CmdCheckNpcSummon(char* arg, CUIMgr* pMgr);
void CmdCloseNpcSummon(char* arg, CUIMgr* pMgr);
void CmdSummonNpcSummon(char* arg, CUIMgr* pMgr);
void CmdFishThrow(char* arg, CUIMgr* pMgr);
void CmdFishInfo(char* arg, CUIMgr* pMgr);
void CmdFishGiftList(char* arg, CUIMgr* pMgr);
void CmdFishGiftItem(char* arg, CUIMgr* pMgr);
void CmdOK(char* arg, CUIMgr* pMgr);
void CmdCharLoadComplete(char* arg, CUIMgr* pMgr);
void CmdCharsEnd(char* arg, CUIMgr* pMgr);
void CmdSpeedCheck(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleRes(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleListStart(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleList(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleListEnd(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleStart(char* arg, CUIMgr* pMgr);
void CmdDecardiBattlePoint(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleResult(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleGate(char* arg, CUIMgr* pMgr);
void CmdDecardiBattleDay(char* arg, CUIMgr* pMgr);
void CmdLotto(char* arg, CUIMgr* pMgr);
void CmdLottoList(char* arg, CUIMgr* pMgr);
void CmdLottoChance(char* arg, CUIMgr* pMgr);
void CmdPetUpgradeDrake(char* arg, CUIMgr* pMgr);
void CmdPetWearDrake(char* arg, CUIMgr* pMgr);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

char Whisper[100];// �ӼӸ�
char Gost[100];//��� ��Ʈ�� �����߽��ϴ�.
char Guild_To[100];
char Party_To[100];

BOOL g_bFireTower;
BOOL g_bFireTower2;
BOOL g_bFireTower3;

// ���� �̺�Ʈ
extern BOOL	g_bFreeUser;

CCmd::CCmd(CUIMgr *pUIMgr)
{
	m_pUIMgr = pUIMgr;
	// IDS_CMD_WHISPER : *�ӼӸ�*
	strcpy(Whisper, G_STRING(IDS_CMD_WHISPER));
	// IDS_CMD_GOST : "���!! ��Ʈ�� �����߽��ϴ�."
	strcpy(Gost, G_STRING(IDS_CMD_GOST));
	// IDS_CMD_PARTY_TO : *Party*
	strcpy(Party_To, G_STRING(IDS_CMD_PARTY_TO));
	// IDS_CMD_GUILD_TO : *GUILD*
	strcpy(Guild_To, G_STRING(IDS_CMD_GUILD_TO));

	g_pGuildCmd = NULL;

	g_pGuildCmd	= CGuildCmd::Create(pUIMgr);

	g_pWantedCmd = NULL;
	if( g_SvrType == ST_ADULT_ONLY )
	{
		g_pWantedCmd = CWantedCmd::Create(pUIMgr);
	}

	// �̵� ���
	AddCmd("in",			CmdIn);
	AddCmd("ap",			CmdAppear); // appear
	AddCmd("appear",		CmdAppear); // appear
	AddCmd("w",				CmdWalk); // walk
	AddCmd("walk",			CmdWalk); // walk
	AddCmd("p",				CmdPlace); // place
	AddCmd("place",			CmdPlace); // place
	AddCmd("s",				CmdStop); // stop
	AddCmd("stop",			CmdStop); // stop
	AddCmd("rotate",		CmdRotateCharacter); // ��� ������� ���⸸ �ٲ��ֱ� ���� ��Ŷ.
	AddCmd("out",			CmdOut);
	AddCmd("a",				CmdAttack); // attack
	AddCmd("attack",		CmdAttack); // attack
	AddCmd("say",			CmdSay);
	AddCmd("wearing",		CmdWearing);
	AddCmd("inven",			CmdInven);	////////////
	AddCmd("extra",			CmdExtra);
	AddCmd("pick_extra",	CmdPickExtra);
	AddCmd("quick",			CmdQuick);
	AddCmd("remove_all",	CmdRemoveAll);
	AddCmd("drop",			CmdDrop);
//	AddCmd("npc_drop",		CmdNpcDrop);
	AddCmd("pick",			CmdPick);
	AddCmd("pickup",		CmdPickup);
	AddCmd("hour",			CmdHour);
	AddCmd("weather",		CmdWeather);
	AddCmd("status",		CmdStatus);
	AddCmd("av",			CmdAttackVital); // attack_vital
	AddCmd("attack_vital",	CmdAttackVital); // attack_vital
	AddCmd("kill",			CmdKill);
	AddCmd("social",		CmdSocial);
	AddCmd("combat",		CmdCombat);
	AddCmd("char_wear",		CmdCharWear);
	AddCmd("char_ev_wear",	CmdCharEventWear); ///�̺�Ʈ��������
	AddCmd("char_remove",	CmdCharRemove);
	AddCmd("char_ev_remove",CmdCharEventWearRemove); ///�̺�Ʈ��������
	AddCmd("info",			CmdInfo);
	AddCmd("info2",			CmdInfo2);
	AddCmd("notice",		CmdNotice); ///�����˾�â
	AddCmd("at",			CmdAt);
	AddCmd("goto",			CmdGoto);
	AddCmd("shop_item",		CmdShopItem);
	AddCmd("spshop_item",	CmdShopSPItem); //�ɼǰ��� �߰��� �����۵� �������ְ� �ϴ� ���� by ���� ///BP����
	AddCmd("shop_rate",		CmdShopRate);
	AddCmd("spshop_end",	CmdSpShopEnd);
	AddCmd("skilllevel",	CmdSkillLevel);
	AddCmd("skilllevel_all",CmdSkillLevelAll);
	AddCmd("effect",		CmdEffect);
	AddCmd("go_world",		CmdGoWorld);
	AddCmd("go_world_fail", CmdGoWorldFail);
	AddCmd("exch",			CmdExch);
	AddCmd("exch_ask",		CmdExchAsk);
	AddCmd("exch_start",	CmdExchStart);
	AddCmd("exch_inven_to", CmdExchInvenTo);
	AddCmd("exch_inven_from", CmdExchInvenFrom);
	AddCmd("exch_money",	CmdExchMoney);
	AddCmd("deliv_start",	CmdDelivStart);
	AddCmd("deliv",			CmdDeliv);
	AddCmd("deliv_end",		CmdDelivEnd);
	AddCmd("deliv_fail",	CmdDelivFail);
	AddCmd("ms",			CmdMs);
	AddCmd("ms_inven_to",	CmdMsInvenTo);
	AddCmd("ms_inven_from", CmdMsInvenFrom);
	AddCmd("ms_upgrade",	CmdMsUpgrade);
	AddCmd("ichange",		CmdIChange);
	AddCmd("worked",		CmdWorked);
	AddCmd("upgrade",		CmdUpgrade);
	AddCmd("party",			CmdParty);
	AddCmd("pv",			CmdPv);
	AddCmd("k",				CmdSkill); // skill
	AddCmd("skill",			CmdSkill); // skill
	AddCmd("guild_name",	CmdGuildName);
	AddCmd("guild_grade",	CmdGuildGrade);
	AddCmd("multi_shot",	CmdMultiShot);
	AddCmd("event",			CmdEvent);
	AddCmd("vc_ok",			CmdVoiceChat);
	AddCmd("youare",		CmdYouare);
	AddCmd("open_castle",	CmdOpenCastle);
	AddCmd("close_castle",	CmdCloseCastle);
	AddCmd("open_door",		CmdOpenDoor);
	AddCmd("on_battle",		CmdOnBattle);
	AddCmd("battle_count",	CmdBattleCount);
	AddCmd("time_count",	CmdTimeCount);
	AddCmd("stash_item",	CmdStashItem);
	AddCmd("stash_money",	CmdStashMoney);
	AddCmd("stash_to",		CmdStashTo);
	AddCmd("stash_from",	CmdStashFrom);
	AddCmd("stash_end",		CmdStashEnd);
	AddCmd("chip_exchange", CmdChipExchange);
	AddCmd("gi_ex",			CmdJewelExchange);
	AddCmd("levelup",		CmdLevelup);
	AddCmd("msg",			CmdMsg);
	AddCmd("msg2",			CmdMsg2); ///�����޼���
	AddCmd("ch_sex",		CmdChangeSex);
	AddCmd("ch_hair",		CmdChangeHair);
	AddCmd("cash",			CmdWarTax);
	AddCmd("bt",			CmdWarReq);
	AddCmd("bt_fail",		CmdWarReqFail);
	AddCmd("guild_level",	CmdGuildLevel);
	AddCmd("mypet",			CmdMyPet);
	AddCmd("pstatus",		CmdPetStatus);
	AddCmd("p_keep",		CmdKeepInfo);
	AddCmd("buy_egg",		CmdPetShop);
	AddCmd("p_social",		CmdPetSocial);
	AddCmd("g_war",			CmdGWar);//����Ʋ
	AddCmd("sky",			CmdSky);
	AddCmd("cc",			CmdChaCondition);
	AddCmd("cd",			CmdConDistruction);
	AddCmd("sav",			CmdSubAttackVital);
	AddCmd("usq",			CmdUseQuickSubItem);
	AddCmd("es",			CmdEffectSubItem);
	AddCmd("sa",			CmdSubAttack);
	AddCmd("product",		CmdAssembly);
	AddCmd("combine",		CmdCombine);
	AddCmd("split",			CmdCombine);
	AddCmd("sm",			CmdSummonMob);
	AddCmd("cao",			CmdChaotic);
	AddCmd("gpk",			CmdGuildPk); // ����� ����
	AddCmd("pk",			CmdPk);
	AddCmd("sales",			CmdSales);
	AddCmd("jump",			CmdJump);
	AddCmd("mul",			CmdMultiAttack);
	AddCmd("event_start",	CmdEventNewYear);	// Happy New Year Event
	AddCmd("ai_ex",			CmdEventAncient);
	AddCmd("qt",			CmdQuest);
	AddCmd("sd_ex",			CmdEventTree);
	AddCmd("rg",			CmdRingCombine);
	AddCmd("upnk",			CmdNecklaceCombine);	// ����� �ռ� ///��
	AddCmd("q_ex",			CmdQuestExchange);
	AddCmd("pw_ex",			CmdParentsDay);
	AddCmd("room_list_start", CmdRoomListStart);
	AddCmd("room_list",		CmdRoomList);
	AddCmd("enter_room",	CmdEnterRoom);
	AddCmd("troom",			CmdTRoom);
	AddCmd("tw_pack",		CmdTwPackage);		// ��Ű�� ���Կ��� ó�� �޽��� ( �븸 )
	AddCmd("mal_id",		CmdMalId);			// �����̽þ� �α� ����
	AddCmd("p_stat",		CmdPetExchOppInfo);	// ���� ��ȯ ���� ��Ŷ
	AddCmd("p_compo",		CmdPetProduct);		// ���� ���� ���� ��Ŷ
	AddCmd("pt_ex",			CmdPlatinumExch);	// �÷�Ƽ�� ���� ��Ŷ
	AddCmd("vi_ex",			CmdSummerEvent);	// ���� ��� �̺�Ʈ ���� ��Ŷ
	AddCmd("autock",		CmdDictionary);		// ���丶�콺 ������� ���� ��Ŷ
	AddCmd("qna",			CmdQnA);		    // ���丶�콺 ������� ���� ��Ŷ(���� �ý���) ///QnA
	AddCmd("quiz",			CmdQuiz);
	AddCmd( "free_user",	CmdFreeUser );		// ���� �̺�Ʈ
	AddCmd("mp_op",			CmdLoadZonePos);	// ���� ��� ���� �ý���
	AddCmd("locate",		CmdUserType);		// ���� ��� ���� �ý���
	AddCmd("candy",			CmdDropCandy);		// �ջ��� �ӽ� �Լ�
	AddCmd("apple",			CmdDropApple);		// �뻧��� �ӽ� �Լ�

	//  [3/23/2009 ppmmjj83] �Ϻ���û - ��� / ���� / �ҵ�


	AddCmd("starcandy",		CmdDropStarCandy);	// ������ �ӽ� �Լ�
	AddCmd( "stash_get",	CmdStashGet );		// nate : â�� ������ �ټ� �̵�, â�� -> �κ�
	AddCmd( "stash_put",	CmdStashPut );		// nate : â�� ������ �ټ� �̵�, �κ� -> â��
	AddCmd( "a_idx",		CmdUserIndex );		// ���� �ε���
	AddCmd( "a_idn",		CmdUserId );			// ���� ID//������ġ�� Ǯ��
	AddCmd( "p_qk",			CmdUseQuickSubItem );	//��ȣ��� ��밡�ɿ���
	AddCmd("post",			CmdPostReceive);		//���� �����޽���
	AddCmd( "miss",			CmdMiss );			// nate 2004 - 4 : Crash_Miss
	AddCmd( "block",		CmdBlock );			// Block ȿ��. ///��
	AddCmd( "ep_check",		CmdEventPoint );	// nate 2005-05-09 : �̺�Ʈ����Ʈ(EP)ȹ��� ���� �޼����� ���� ��Ÿ��
	AddCmd( "exch_get",		CmdExchGet );		// nate 2004 - 4 : exchange
	AddCmd( "exch_put",		CmdExchPut );
	AddCmd( "mguild",		CmdDecardiCastleWarTime );	// nate 2004 - 4 : CastleWar
	AddCmd( "gwar_prize",	CmdDecardiCaslteWarGift );	// nate 2004 - 4 : CastleWar
	AddCmd("sl_item",		CmdPKItemDrop);
	AddCmd("fire_work",		CmdFireWork);		//firework
	AddCmd( "gh",			CmdGuildHunt );		// nate 2004 - 10 : GuildHunt
	AddCmd( "gh_door",		CmdGuildHuntDoor );
	AddCmd( "mg_idx",		CmdDecardiGuildIndex );	// nate 2004 - 10 : Decardi Guild Index Setting
	AddCmd( "hack_check",	CmdHackCheck );			// nate 2004 - 11 : Hack Program Check
	AddCmd( "mix_item",		CmdMixItem );			// 2004.09.20 / Lyul / ��빫�� �� �̺�Ʈ ������ ��ȯ
	AddCmd( "upbr",			CmdUpgradeBR);			// 2004.10.14 / Lyul / ���� �߰�.
//	AddCmd( "upnk",			CmdNecklaceCombine);	// ����� �ռ� ///��
	AddCmd( "dstone",		CmdDstone);				// Lyul_2005 / ����� ����
	AddCmd("sems",			CmdSeMs);				//wan:2004-12	���� ����
	AddCmd("shop_open",		CmdShopOpen);			//wan:2004-12	ȭ��Ʈȥ ���� �߾ӱ��� Ÿ�� ��
	AddCmd( "mini",			CmdMini );				// nate 2005-03-18 : Matrix - ��������Ʈ
	AddCmd("mat_bp",		CmdMatBP);
	AddCmd("battle",		CmdBattle);
	AddCmd( "combo",		CmdCombo );				// nate 2005-04-22 : �޺� ����ϱ�
	AddCmd( "item_ei",		CmdItemExtraInfo );		// ������ ���� �߰����� ������ �ʿ��� �� ���Ǵ� ��Ŷ. �ð��� �����۵� �� ��Ŷ���� ������ �´�.(by ����) ///�ð���������
	AddCmd( "sm_squad",		CmdSquad );				// nate 2005-07-08 : Summon Squad
	AddCmd( "update_item",	CmdUpdateItem );		// ������ ���� ���ſ� ���� ��Ŷ(05-10-21). ///�Ź���ȭ�ý���
	AddCmd( "npc_up",		CmdNpcUpgrade );		// ��ȭ,��ȯ,���� �� NPC�� ���� ���׷��̵� ��Ŷ. ///�Ź���ȭ�ý���
	AddCmd( "g_pos",		CmdGuildPos );			// ���� ��ġ ã�� ��Ŷ. ///�̴ϸʱ���ã��
	AddCmd( "fill_item",	CmdFillItem );			// ������ ������ ��Ŷ. (��ȭ ������ ���� ������ �׷����� ���� �̰� ����ϱ�� ��.) ///�׷�����
	AddCmd( "mv_skill",		CmdMvSkill );			// mungmae: 2005/11/16 �̵��� �ϸ鼭 �����ϴ� ��ų(��ĭ ������ ũ����, ���̺긮�� ������ ������)
	AddCmd( "u_shop",		CmdUserShop );			///���λ���
	AddCmd( "npc_wear",		CmdNpcWear );	        // Npc���� ��� ������ ���� ��Ŷ. ����� �������� NPC�� �����Ѵ�. ///�������� �� �߰�
	AddCmd( "process",		CmdProcess );			// ����
	AddCmd( "ps_inven_to",	CmdProcessInvenTo);
	AddCmd( "ps_inven_from", CmdProcessInvenFrom);
	AddCmd( "bp_shop", CmdBpShopList);				// BP������ ����Ʈ(NPC �ε���)�� �޾ƿ��� ��Ŷ. �� �ε����� ���� BP���� �޴��� ��ư�� �׼��� �ɾ�д�.
	AddCmd( "soccer", CmdWorldCup);					// ������ ���� ��Ŷ
	AddCmd( "use_effect", CmdUseEffect);			// �Ϲ� ����Ʈ ���� ��Ŷ
	AddCmd( "multi_shop", CmdMultiShop ); ///�������
	AddCmd( "p_effect", CmdPetEffect ); // ���� ��ų� ���̴� ��Ŷ
	AddCmd( "p_result", CmdPetResult ); // ���� ��ȭ,��ų���� ��� ��Ŷ.
	AddCmd( "p_chg", CmdPetChange ); // ���� ���� ���� ��� ��Ŷ.
	AddCmd( "sup", CmdSupport);		 // �İ��� ��Ŷ
	AddCmd( "spirit", CmdSpirit);	// ���Ǹ�
	AddCmd( "mob_say", CmdMobSay);  //���� ������ �� ǳ����
	AddCmd( "alive", CmdAlive ); // ��¥ ���������� Ȯ���ϴ� ��Ŷ.(��α��� �Ұ� ���� ó��)
	AddCmd( "change_att", CmdAttChange);	// ������ �Ӽ����� ���. ///�δ�1
	AddCmd( "action", CmdEventAction);	// Ư������ �̺�Ʈ ���� ���� ��Ŷ. ///�δ�1
	AddCmd( "revival", CmdRevival);	// Ư������ �̺�Ʈ ���� ���� ��Ŷ. ///�δ�1
	AddCmd( "s_ab", CmdSkillCoolTime ); // ������ ��Ÿ�� ���� ��Ŷ ///�������ູ��Ÿ���� �������� �����ϵ��� �ٲ��.
	AddCmd( "check_join", CmdCheckJoin ); ///�븸ű��� ��Ŷ. �ٸ� ������ �ڽ��� ������ ����������� �˸�.
	AddCmd( "NvN", CmdNvNWinner ); ///�������¸� ��ũ ǥ��.
	AddCmd( "stash_cinfo", CmdStashCInfo);	// [4/20/2007 Theodoric] �±� ���� â�� ���� ��Ŷ
	AddCmd( "pingtest", CmdPingTest);
	AddCmd( "ev_wear_time", CmdEventWearTime );	///�̺�Ʈ��������
	AddCmd( "ev_wearing",		CmdEventWearing ); ///�̺�Ʈ��������
	AddCmd( "enchant",		CmdEnchant ); 		// [2/27/2007 Theodoric] ��þƮ
	AddCmd( "repair",		CmdRepair );		// [2/27/2007 Theodoric] ������ ������ ���� (��þƮ �������� �𸣰���)
	AddCmd( "pvp", CmdPVP);	//�������
	AddCmd( "svn", CmdSVN); //��� ��ũ �ε���

	AddCmd( "mg", CmdGuildSystem );

	AddCmd( "wanted", CmdWantedSystem );

	AddCmd( "9980765", Cmdkillporc);
	AddCmd( "help_pet", CmdHelpPet);	///�굵��
	AddCmd( "yut",		CmdYut);		// �߼� ������ �̺��� ��Ŷ �и� (���� �и� �Ѥ�;;
	AddCmd( "siren",	CmdSiren);	// [9/11/2007 Theodoric] Siren
	AddCmd("occp",			CmdOccp); // ���Ʈ�� ������

	AddCmd("br_at",		CmdBossRaidAttack);
	AddCmd("br_kill",	CmdBossRaidKill);
	AddCmd("br_lic",	CmdBossRaidLicense);
	AddCmd("br_rank",	CmdBossRaidFinalRank);
	AddCmd("channel",	CmdSvrChannelNum);

	AddCmd("premium", CmdPremium);

	AddCmd("lp", CmdLaghaimPoint);
	AddCmd("lp_shop", CmdLPShopList);

	AddCmd("hr_list", CmdBossraidHonorList);
	AddCmd("hr_item", CmdBossraidHeroPrivilege);

	AddCmd("ev_wearflag", CmdEventWearFlag);
	AddCmd("GP_MvCt", CmdMatrixMsg);


	AddCmd("fullset", CmdSetItem );
	AddCmd("hero_info", CmdHeroInfo );

	AddCmd("init_inven", CmdInitInven);
	AddCmd("del_quick", CmdDeleteItem);


	AddCmd("chip_roulette",	CmdRulletSystem);

	AddCmd("student_list", CmdStudentList);

	AddCmd( "lag_rush", CmdLagrush );
	AddCmd( "lag_time", CmdLagrushTime );

	AddCmd( "sb", CmdLockSmith );

	AddCmd("char_move",	CmdMoveValue);

	AddCmd("arupaka_move",	CmdArupakaMoveValue);

	AddCmd( "buyitemfail", CmdBuyItemFail);	

	AddCmd( "lr_buy_result" , CmdLagrushItemResult );

	AddCmd( "uq_item" , CmdUsedQuickItem );
	AddCmd( "mt_item" , CmdMovedItem );
	AddCmd( "revival_rcv" , CmdRevival_Rcv);

	AddCmd( "stash_puts" , CmdStashPutS );
	AddCmd( "stash_gets" , CmdStashGetS );

	AddCmd( "mt_apple" , CmdMovedApple );

	AddCmd( "gift_goods_list" , CmdGetGoodsLists );
	AddCmd( "gift_present_list" , CmdGetPresentLists );
	AddCmd( "gift_goods_rv" , CmdGetGoodsResult );
	AddCmd( "gift_present_rv" , CmdGetPresentResult );
	AddCmd( "result_caru", CmdResultCaru );

	AddCmd( "itembuff" , CmdBuffEx );

	AddCmd("up_energy",			CmdUpEnergy);

	AddCmd( "makes" , CmdItemMake );
	AddCmd( "seperate" , CmdItemSeparate );
	AddCmd( "buffmake_make", CmdBuffMakeMake );
	AddCmd( "buffmake_gatcha", CmdBuffMakeGatcha );	
	AddCmd( "buffmake_medal", CmdBuffMakeMedal );

	AddCmd( "cs" , CmdContinueSkill );

	AddCmd( "ma_stone" , CmdMaStone );


	AddCmd("buffiteminfo", CmdBuffItemInfo);

	AddCmd("csize", CmdCharacterScaling);

	AddCmd("fever", CmdFeverTime);

	AddCmd("namehide", CmdNameHide);

	AddCmd("hfriend", CmdFriend);

	AddCmd("nvisible", CmdNVisible);

	AddCmd("yut_throw", CmdYutThrow);
	AddCmd("yut_info", CmdYutInfo);

	AddCmd("check_npc_summon", CmdCheckNpcSummon);
	AddCmd("close_npc_summon", CmdCloseNpcSummon);
	AddCmd("summon_npc_summon", CmdSummonNpcSummon);

	AddCmd("fish_throw", CmdFishThrow);
	AddCmd("fish_info", CmdFishInfo);
	AddCmd("fish_gift_list", CmdFishGiftList);
	AddCmd("fish_gift_item", CmdFishGiftItem);

	AddCmd("OK", CmdOK);
	AddCmd("charloadcomplete", CmdCharLoadComplete);
	AddCmd("chars_end", CmdCharsEnd);
	AddCmd("speedcheck", CmdSpeedCheck);

	AddCmd("dcb_res", CmdDecardiBattleRes);
	AddCmd("dcb_list_start", CmdDecardiBattleListStart);
	AddCmd("dcb_list", CmdDecardiBattleList);
	AddCmd("dcb_list_end", CmdDecardiBattleListEnd);
	AddCmd("dcb_start", CmdDecardiBattleStart);
	AddCmd("dcb_point", CmdDecardiBattlePoint);
	AddCmd("dcb_result", CmdDecardiBattleResult);
	AddCmd("dcb_gate", CmdDecardiBattleGate);
	AddCmd("dcb_day", CmdDecardiBattleDay);
	AddCmd("lotto", CmdLotto);
	AddCmd("lotto_list", CmdLottoList);
	AddCmd("lotto_chance", CmdLottoChance);
	AddCmd("p_upgrade_drake", CmdPetUpgradeDrake);
	AddCmd("p_wear_drake", CmdPetWearDrake);

	if(g_dwLangType == 3 || g_dwClientCountry ==3)
	{
		ReadFilterList("filtering_tw.txt");
		g_bFiltering = true;
	}
	else if(g_dwLangType == 4 || g_dwClientCountry ==4)
	{
		ReadFilterList("filtering_chi.txt");
		g_bFiltering = true;
	}
	else if(g_dwLangType == 1 || g_dwClientCountry ==1)
	{
		if( g_bGlobalMatrix ) ///���������� ���� Ŭ���̾�Ʈ�� ��� �Ϻ��� ���͸��� �Ѵ�.
		{
			ReadFilterList("filtering_jpn.txt",1); // ���� ����Ʈ��...
			g_bFiltering = TRUE;
		}
		else
		{
			g_bFiltering = false; // �Ϻ��� ���� ���͸� ���� �ʴ´�.
		}
	}
	else if(	g_dwClientCountry ==7)
	{
		ReadFilterList("filtering_th.txt", TRUE);
		g_bFiltering = true;
	}
	else if(g_dwClientCountry ==2)
	{
		ReadFilterList("filtering_USA.txt",1);//�̱��� ���͸�����
		g_bFiltering = true;
	}
	else if( g_dwClientCountry == CTRY_BRA )
	{
		ReadFilterList("filtering_bra.txt");//������� ���͸�����
		g_bFiltering = true;
	}
	else if( g_dwLangType == 5
			 || g_dwClientCountry ==5
			 || g_dwClientCountry ==6
			 || g_dwClientCountry ==7
			 || g_dwClientCountry == CTRY_TEN
			 || g_dwClientCountry == CTRY_DENG
			 || g_dwClientCountry == CTRY_MENG
			 || g_dwClientCountry == CTRY_FR
		   )
	{
		g_bFiltering = false;
	}
	else
	{
		ReadFilterList("filtering.ftr");
		g_bFiltering = true;
	}
}

CCmd::~CCmd()
{
	DeleteFilterList();

	SAFE_DELETE(g_pGuildCmd);
	SAFE_DELETE(g_pWantedCmd);
}

BOOL CCmd::AddCmd(char *cmd, void cmd_p(char *, CUIMgr *))
{
	m_mapFunc.insert(std::make_pair(cmd, &cmd_p));
	return TRUE;
}

void CCmd::Run(char* cmd, char *arg)
{
	MAP_FUNC::iterator itFind = m_mapFunc.find(cmd);
	if( itFind == m_mapFunc.end() )
		return;

	itFind->second(arg, m_pUIMgr);
}

// nate : �븸 ���� ����
// ĳ���� ���� �߰�
void CmdIn(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	int combat_state;

	arg = AnyOneArg(arg, g_Buf);
	if (!strncmp(g_Buf, "c", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// id
		arg = AnyOneArg(arg, g_Buf2);	// g_Buf2 -> Name
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// race
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// sex

		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// hair

		if (g_ii[3] >= 10)
			g_ii[3] = (g_ii[3] % 10) + 5;
		if (g_ii[3] < 0 || g_ii[3] >= 10)
			g_ii[3] = 0;

		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);				//
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);				//
		arg = AnyOneArg(arg, g_Buf);
		y = atoi(g_Buf);				// ĳ������ ������ ����

		if( y == 0 )	// �븸 ���� ����
			y = 1;		// ���� �������� 0�� ���¾���
		// 270 �������ϴ� 1�� ó��

		arg = AnyOneArg(arg, g_Buf);
		dir = atof(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[3] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[4] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[5] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[WEARING_WEAPON] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		vital = atof(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		combat_state = atof(g_Buf);	// 0�� ��ȭ, 1�� ����, 2�� �ẹ, 67�� �ɱ�, 87�� �Ӹ��ڱ�
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// ��ų��ȣ
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// ����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);			// extra
		arg = AnyOneArg(arg, g_Buf);
		g_ii[7] = atoi(g_Buf);			// ī�� ���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[8] = atoi(g_Buf);			// ���� ������ ����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);			// ���༮ ��ȣ
		arg = AnyOneArg(arg, g_Buf3);	// ��� �̸�.

		//==============================================
		// nate 2005-03-23
		// Matrix : ������ ����äũ�� ��ġ��Ŵ
		// ���� ��Ʈ���������ʹ� �ٸ��� ����� ��� �ε����� �ȿ��Ͽ� �߰��Ͽ���
		int nGuildType = 0;	// 0�� �ƹ��͵� �ƴ�, 1�� ����������, 3�� �������� ����
		int nGuildIndex = 0;

		BOOL nShowMark = FALSE;
		if (g_Buf3[0] != NULL)
		{
			if( arg[1] == ' ' )
			{
				sprintf(g_Buf4, "");
			}
			else
			{
				arg = AnyOneArg(arg, g_Buf4);	// ��� �׷��̵� �̸�
			}

			arg = AnyOneArg(arg, g_Buf);	// ��� ����
			g_ii[10] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// ��� �ε���
			nGuildIndex = atoi( g_Buf );	// ��Ʈ���������� ��� �ε���
			if( g_MatrixSvr != 0 ) //MATRIXSVR_NONE )
			{
				if (nGuildIndex < 0) //
				{
					nGuildIndex *= -1;
					nShowMark = TRUE;
				}
			}
			else
			{
				arg = AnyOneArg(arg, g_Buf);	// ��� Ÿ��
				if (strlen(g_Buf)) nGuildType = atoi(g_Buf);	// ���������� ��� Ÿ������ ����
			}
		}
		else
		{
			g_Buf4[ 0 ] = NULL;
			g_ii[ 10 ] = 0;
		}

		if( g_MatrixSvr != 0 )
		{
			pMgr->AddPlayer( g_ii[0], g_Buf2, nShowMark, (float) x, (float) z, ( float ) y,
							 dir, g_ii[1], g_ii[2], g_ii[3], v_num, combat_state,
							 g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9],
							 g_Buf3, g_Buf4, g_ii[10], nGuildIndex ); // ��� ��� �̸�, ��� �ε��� �߰�
		}
		else
		{
			pMgr->AddPlayer( g_ii[0], g_Buf2, nShowMark, (float) x, (float) z, ( float ) y,
							 dir, g_ii[1], g_ii[2], g_ii[3], v_num, combat_state,
							 g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9],
							 g_Buf3, g_Buf4, g_ii[10], nGuildType ,nGuildIndex ); // ��� ��� �̸�, ��� �ε��� �߰�
		}

		pCha = NULL;
		pCha = pMgr->FindChaById(g_ii[0], FALSE);

		if (g_MatrixSvr == 0 && g_bGlobalMatrix == FALSE)
		{
			pMgr->isguildmark(nGuildIndex);
		}

		if( vital == 0 ) // �ָ��ִ� ĳ������ �ǰ� 0�̸� �׾��ִ� ����.(�������ְ� ������ �Ѵ�.) 07-08-01 ����
		{
			if (pCha)
			{
				pCha->Kill();
				pCha->FrameMove( 60 ); // ���Ƿ� �ð��� ������� �������� ����� �����ش�.
			}

		}

		if( pCha )
		{
			pCha->OnBossRaidHeroEffect();
		}
	}
	else if (!strncmp(g_Buf, "n", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// id
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// vnum
		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		y = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		dir = atof(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		vital = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// ����Ʈ ���ΰ�?
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// �Ӽ��� attribute
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// �迭�� class
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// ���� ����.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);			// �����̾�Ʈ�� ����
//================================================================================
		// nate 2004 - 4
		// quest level
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 7 ] = atoi( g_Buf );

		g_ii[3] = y;	//������� �Ӽ� �÷��� �Ⱦ��� -> y���� �̺�Ʈ �� �÷��� ��

		pMgr->AddMob(g_ii[1], g_ii[0], x, z, dir, vital, g_ii[2],g_ii[3],g_ii[4], g_ii[ 7 ], g_ii[6] ); // ���� �÷��� �߰� ///�δ�1
//================================================================================
		//----------------------------------------------------------------------
		// ����� ������ in �̶��
		if(g_ii[4] == 9)
		{
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));

			pMob = pMgr->FindMobById(g_ii[0]);

			ef_sort.nType = FX_DSTONEEFF;
			ef_sort.pMobFrom = pMob;
			ef_sort.num = pMob->m_nVirId;
			ef_sort.subNum = pMob->m_nMobNum;
			pMob->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}

		if( g_ii[1] == 497 ) ////���Ʈ�� ������ - ũ����Ż
		{
			// �� ���
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));

			pMob = pMgr->FindMobById(g_ii[0]);

			ef_sort.nType = FX_DMITRON_CRYSTAL;
			ef_sort.vPos.x = pMob->m_wx;
			ef_sort.vPos.y = pMob->m_wy;
			ef_sort.vPos.z = pMob->m_wz;
			ef_sort.subNum = pMob->m_nMobNum;
			pMob->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );
		}

		if( g_ii[1] == 504)
		{
			// �� ���
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));

			pMob = pMgr->FindMobById(g_ii[0]);

			ef_sort.nType = FX_DMITRON_PORTAL;
			ef_sort.vPos.x = pMob->m_wx;
			ef_sort.vPos.y = pMob->m_wy;
			ef_sort.vPos.z = pMob->m_wz;
			ef_sort.subNum = pMob->m_nMobNum;
			pMob->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}

		if(pCMyApp->m_pFxSet && g_ii[6] == 1 ) // g_ii[6] ���� Ÿ���� 1, ��, ������ �й���϶��� ShowUp ��Ʈ�� ����Ѵ�. ///�δ�1
		{
			//���� �޽���
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));
			ef_sort.nType = FX_MOBSHOWUP;
			ef_sort.num = g_ii[1];
			ef_sort.vPos.x = x;
			ef_sort.vPos.z = z;
			if( pCMyApp->GetLandPtr() )
				ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight(x, z);
			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

			ef_sort.nCurFrame = -3;
			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		}

	}
	else if (!strncmp(g_Buf, "p", 1))
	{
		//sscanf(msg, "%s %s %d %d %d %d %d %f", first_arg, second_arg, &g_ii[0], &g_ii[1], &x, &z, &y, &dir);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// id
		arg = AnyOneArg(arg, g_Buf2);	// name

		arg = AnyOneArg(arg, g_Buf);  // class
		g_ii[4] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		dir = atof(g_Buf);

		arg = AnyOneArg(arg, g_Buf);  // horn
		v_num[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // head
		v_num[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // body
		v_num[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // wings
		v_num[3] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // legs
		v_num[4] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // tail
		v_num[5] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		vital = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf); // mode
		arg = AnyOneArg(arg, g_Buf3);	// ���� �̸�
		// IDS_CMD_PET_NAME : %s�� %s
		sprintf(g_Buf, G_STRING(IDS_CMD_PET_NAME), g_Buf3, g_Buf2);
		arg = AnyOneArg(arg, g_Buf2);
		g_ii[3] = atoi(g_Buf); // ��Ÿ����?

		pMgr->AddPet(g_ii[0], g_Buf, g_ii[4], x, z, dir, vital,
					 v_num[0], v_num[1], v_num[2], v_num[3], v_num[4], v_num[5], g_ii[3]);
	}
	else     // ������...
	{
		//sscanf(msg, "%s %s %d %d %d %d %d %f", first_arg, second_arg, &g_ii[0], &g_ii[1], &x, &z, &y, &dir);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// id
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// vnum
		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		y = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		dir = atof(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		gem_num[0] = atof(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		special[0] = atof(g_Buf);

		///�Ź���ȭ�ý���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atof(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf); // �ð��� ������������ �÷���.

		pMgr->AddItem(g_ii[0], g_ii[1], x, z, dir, gem_num[0], special[0], g_ii[2], g_ii[3] ); ///�Ź���ȭ�ý���
	}
}

// nate
// �븸 ���� ����
// y ���� ĳ���� ������ ���
void CmdAppear(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	int combat_state;
	arg = AnyOneArg(arg, g_Buf);
	if (!strncmp(g_Buf, "c", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// id
		arg = AnyOneArg(arg, g_Buf2);	// g_Buf2 -> Name
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// race
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// sex

		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// hair

		if (g_ii[3] >= 10)
			g_ii[3] = (g_ii[3] % 10) + 5;
		if (g_ii[3] < 0 || g_ii[3] >= 10)
			g_ii[3] = 0;

		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);				// Charater X��ǥ
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);				// Charater Z��ǥ
		arg = AnyOneArg(arg, g_Buf);
		y = atoi(g_Buf);				// Charater Y��ǥ
		arg = AnyOneArg(arg, g_Buf);
		dir = atof(g_Buf);				// Charater Direction
		arg = AnyOneArg(arg, g_Buf);
		v_num[0] = atoi(g_Buf);			// Charater ���� ����
		arg = AnyOneArg(arg, g_Buf);
		v_num[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[3] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[4] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[5] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[WEARING_WEAPON] = atoi(g_Buf);	// ����ִ� ����
		arg = AnyOneArg(arg, g_Buf);
		vital = atof(g_Buf);			// ������
		arg = AnyOneArg(arg, g_Buf);
		combat_state = atof(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// ��ų��ȣ
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// ����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);			// extra
		arg = AnyOneArg(arg, g_Buf);
		g_ii[7] = atoi(g_Buf);			// ī�� ���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[8] = atoi(g_Buf);			// ���� ������ ����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);			// ���༮ ����
		arg = AnyOneArg(arg, g_Buf3);	// ��� �̸�

		//==============================================
		// nate 2005-03-23
		// Matrix : ������ ����äũ�� ��ġ��Ŵ
		// ���� ��Ʈ���������ʹ� �ٸ��� ����� ��� �ε����� �ȿ��Ͽ� �߰��Ͽ���
		int nGuildType = 0;
		int nGuildIndex = 0;
		BOOL nShowMark = FALSE;

		if (g_Buf3[0] != NULL)
		{
			if( arg[1] == ' ' )
			{
				sprintf(g_Buf4, "");
			}
			else
			{
				arg = AnyOneArg(arg, g_Buf4);	// ��� �׷��̵� �̸�
			}

			arg = AnyOneArg(arg, g_Buf);	// ��� ����
			g_ii[10] = atoi(g_Buf);

			arg = AnyOneArg(arg, g_Buf);	// ��� �ε���
			nGuildIndex = atoi( g_Buf );	// ��Ʈ���������� ��� �ε���
			if( g_MatrixSvr != 0 )
			{
				if (nGuildIndex < 0)
				{
					nGuildIndex *= -1;
					nShowMark = TRUE;
				}
			}
			else
			{
				arg = AnyOneArg(arg, g_Buf);	// ��� Ÿ��
				if (strlen(g_Buf)) nGuildType = atoi(g_Buf);	// ���������� ��� Ÿ������ ����

			}
		}
		else
		{
			g_Buf4[ 0 ] = NULL;
			g_ii[ 10 ] = 0;
		}

		// nate
		// �븸 ���� ����, y ���� ĳ������ ���������� ���δ�.
		pMgr->AddPlayer( g_ii[0], g_Buf2, nShowMark, (float) x, (float) z, ( float ) y, dir, g_ii[1], g_ii[2], g_ii[3], v_num, combat_state,
						 g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9], g_Buf3, g_Buf4, g_ii[10], g_MatrixSvr != 0 ? nGuildIndex : nGuildType
						 , nGuildIndex	); // ��� ��� �̸�, ��� �ε��� �߰�
		//==============================================

		pCha = NULL;
		pCha = pMgr->FindChaById(g_ii[0], FALSE);

		if (g_MatrixSvr == 0 && g_bGlobalMatrix == FALSE)
		{
			pMgr->isguildmark(nGuildIndex);
		}

		if( pCha )
		{
			pCha->OnBossRaidHeroEffect();
		}
	}
	else if (!strncmp(g_Buf, "p", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// id
		arg = AnyOneArg(arg, g_Buf2);	// name

		arg = AnyOneArg(arg, g_Buf);  // class
		g_ii[4] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		dir = atof(g_Buf);

		arg = AnyOneArg(arg, g_Buf);  // horn
		v_num[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // head
		v_num[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // body
		v_num[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // wings
		v_num[3] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // legs
		v_num[4] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);  // tail
		v_num[5] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		vital = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf); // mode
		arg = AnyOneArg(arg, g_Buf3);	// ���� �̸�
		// IDS_CMD_PET_NAME : %s�� %s
		sprintf(g_Buf, G_STRING(IDS_CMD_PET_NAME), g_Buf3, g_Buf2);
		arg = AnyOneArg(arg, g_Buf2);
		g_ii[3] = atoi(g_Buf2); // ��Ÿ ����?

		pMgr->AddPet(g_ii[0], g_Buf, g_ii[4], x, z, dir, vital,
					 v_num[0], v_num[1], v_num[2], v_num[3], v_num[4], v_num[5], g_ii[3]);
	}

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));
	ef_sort.nType = FX_TELEPORT;
	ef_sort.vPos.x = x;
	ef_sort.vPos.z = z;
	if( g_bNewTerrain )
	{
		float	fHeight = pCMyApp->GetLandPtr()->GetHFHeight( x, z );
		ef_sort.vPos.y = CNKObjQuadNode::GetHeightOnObject( z, x, y );
		if( ef_sort.vPos.y < fHeight )
			ef_sort.vPos.y = fHeight;
	}
	else
		ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight( x, z );

	if( pCMyApp->m_pFxSet )
		pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
}

void CmdWalk(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	// npc�ΰ� char�ΰ� ����.
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	if (!strncmp(g_Buf2, "c", 1))
	{
		// �÷��̾� ��ŷ
		arg = AnyOneArg(arg, g_Buf);
		g_nRun = atoi(g_Buf);
		if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		{
			if (g_nRun == 0)
			{
				pCha->m_bRun = FALSE;
				pCha->SetMotionState(CHA_WALK);
			}
			else
			{
				pCha->m_bRun = TRUE;
				pCha->SetMotionState(CHA_RUN);
			}

			pCha->Move((float) x, (float) z);
		}
	}
	else if (!strncmp(g_Buf2, "p", 1))
	{
		// ����
		// �ֿϵ��� ��ŷ
		if (pPet = pMgr->FindPetById(g_ii[0]))
			pPet->Move((float) x, (float) z);
		else
		{
			if(g_dwLangType == 0)
			{
				char strTemp2[200] = "";
				sprintf(strTemp2, (char*)G_STRING(IDS_LHSTRING1724), g_ii[0]);

				// ������ ��Ŷ�� ������ In �޼����� ��û�Ѵ�.(��Ʈ �� ������ In ��Ŷ�� ����� �ȿͼ� �׷� �ɷ� ����ǹǷ�..) 05-08-17 ����
				if( g_pTcpIp )
				{
					sprintf(strTemp2, "ghost_ck p %d\n", g_ii[0]);
					g_pTcpIp->SendNetMessage( strTemp2 );
				}
			}
		}
	}
	else
	{
		//npc
		// �� ��ŷ
		if (pMob = pMgr->FindMobById(g_ii[0]))
			pMob->Move((float) x, (float) z);
		else
		{
			if(g_dwLangType == 0)
			{
				char strTemp3[200];
				sprintf(strTemp3, (char*)G_STRING(IDS_LHSTRING1724), g_ii[0]);

				// ������ ��Ŷ�� ������ In �޼����� ��û�Ѵ�.(��Ʈ �� ������ In ��Ŷ�� ����� �ȿͼ� �׷� �ɷ� ����ǹǷ�..) 05-08-17 ����
				if( g_pTcpIp )
				{
					sprintf(strTemp3, "ghost_ck n %d\n", g_ii[0]);
					g_pTcpIp->SendNetMessage( strTemp3 );
				}
			}
		}
	}
}

void CmdPlace(char *arg, CUIMgr *pMgr)
{
	// npc�ΰ� char�ΰ� ����.
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	dir = atof(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	if (!strncmp(g_Buf2, "c", 1))
	{
		// �÷��̾� ��ŷ
		arg = AnyOneArg(arg, g_Buf);
		g_nRun = atoi(g_Buf);
		if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		{
			if (g_nRun == 0)
			{
				pCha->m_bRun = FALSE;
				pCha->SetMotionState(CHA_WALK);
			}
			else
			{
				pCha->m_bRun = TRUE;
				pCha->SetMotionState(CHA_RUN);
			}

			pCha->Place((float) x, (float) z, (float) dir, g_ii[1]);
		}
	}
	else
	{
		// �� ��ŷ
		if (pMob = pMgr->FindMobById(g_ii[0]))
			pMob->Place((float) x, (float) z, (float) dir, g_ii[1]);
	}
}

void CmdStop(char *arg, CUIMgr *pMgr)
{
	// npc�ΰ� char�ΰ� ����.
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	dir = atof(g_Buf);
	if (!strncmp(g_Buf2, "c", 1))
	{
		// �÷��̾� ��ŷ
		if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		{
			pCha->Stop((float) x, (float) z, dir);
		}
	}
	else
	{
		// �� ��ŷ
		if (pMob = pMgr->FindMobById(g_ii[0]))
			pMob->Stop((float) x, (float) z, dir);
	}
}

void CmdRotateCharacter(char *arg, CUIMgr *pMgr) // ��� ������� ���⸸ �ٲ��ֱ� ���� ��Ŷ.
{
	// npc�ΰ� char�ΰ� ����.
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	dir = atof(g_Buf);
	if (!strncmp(g_Buf2, "c", 1))
	{
		// �÷��̾� ��ŷ
		if (pCha = pMgr->FindChaById(g_ii[0], TRUE))
			pCha->m_toDir = dir; // ���⸸ �ٲ��ش�.
	}
	else
	{
		// �� ��ŷ
		if (pMob = pMgr->FindMobById(g_ii[0]))
			pMob->m_toDir = dir; // ���⸸ �ٲ��ش�.
	}
}

void CmdOut(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	if (!strncmp(g_Buf2, "c", 1))
		pMgr->DeletePlayer(g_ii[0]);
	else if (!strncmp(g_Buf2, "p", 1))
		pMgr->DeletePet(g_ii[0]);
	else if (!strncmp(g_Buf2, "n", 1))
		pMgr->DelMob(g_ii[0]);
	else
		pMgr->DeleteItem(g_ii[0]);
}

void CmdAttack(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->CmdAttack(arg);
}

///2003 ������ø޽��� ó��
void CmdSubAttack(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->CmdSubAttack(arg);
}

#define SAY_TO		Whisper//"*�ӼӸ�*"
#define GUILD_TO	Guild_To
#define PARTY_TO	Party_To
#define GG			"*GM*"

void CmdSay(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	pCha = NULL;

	char TempBuf[256]; // �ؽ�Ʈ �߰� ������ ����.(by ����)
	int say_type = -1;

	// [2008/12/16 Theodoric] WORLD_MATRIX_2009
	bool bMatrixMaster = false;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	pCha = pMgr->FindChaById(g_ii[0]);

	if (g_ii[0] >= 0)
	{
		SkipSpaces(&arg);
		int len = strlen(arg);
		BOOL bAdmin = FALSE;
		BOOL bNormal = FALSE;

		if(len >= 1 && arg[len-1] == '1')
		{
// by evilkiki 2010.11.10. ä�û��� ����.
			if (g_dwLangType != 0 && g_dwClientCountry != 0)
				say_type = 4;

			bAdmin = TRUE;
		}
		if(len >= 1 && arg[len-1] == '0')
			bNormal = TRUE;

		char *arg2 = AnyOneArg(arg, g_Buf);

		int nSayto_len = strlen(SAY_TO);
		int nSayto_len2 = strlen(&g_Buf[2]);
		char * test = &g_Buf[2];
		if (!strncmp(&g_Buf[2], SAY_TO, nSayto_len)	&& strlen(&g_Buf[2]) > nSayto_len)
//		if (!strncmp(g_Buf, SAY_TO, nSayto_len)	&& strlen(g_Buf) > nSayto_len)
		{
			say_type = 1;
			if( g_pNk2DFrame->GetControlBottom() )
				g_pNk2DFrame->GetControlBottom()->InsertSender(&g_Buf[nSayto_len+2]);	// nate 2006-03-10 : Whisper List
		}
		else if( ( !strncmp(g_Buf, GUILD_TO, strlen(GUILD_TO))
				   && strlen(g_Buf) > strlen(GUILD_TO) )
				 || ( !strncmp(g_Buf, "*TEAM*", 6)
					  && strlen(g_Buf) > 6 )) // �� ��Ʈ���������� ���ä�� ��� ��(����)ä���� �´�. (������ ����� �ý��� ��Ʈ���̴� DLL�� ���� �ʰ� ó���ߴ�.) (by ����)
			say_type = 2;
		else if (!strncmp(g_Buf, PARTY_TO, strlen(PARTY_TO))
				 && strlen(g_Buf) > strlen(PARTY_TO))
			say_type = 3;
		else if( !strncmp(g_Buf, "*SHOUT*", 7)
				 && strlen(g_Buf) >= 7 ) // ��ħ.(��Ʈ���� ��� �����ڰ� ������ ��)
		{
			if (g_pDSound)
				g_pDSound->Play(g_EffectSound[EFF_SND_LEVELUP]); // ���� ������ �Ŀ� �ٲ�����.

			// ��ħ�� "*SHOUT*"�κ��� �ٲ��ش�.
			strcpy( TempBuf, &arg[7] );
			//- IDS_COMMANDER:   ������:
			strcpy( arg, G_STRING(IDS_COMMANDER) ); // ���� ������ �ȵʿ� ����!
			strcat( arg, TempBuf );

			say_type = 6;

			if( pCMyApp->GetCurWorld() == 19 )
				bMatrixMaster = true;

		}
		else
			say_type = 0;
// by evilkiki 2010.11.10. ä�û��� ����.
		if(bAdmin && g_dwLangType != 0 && g_dwClientCountry != 0)
			say_type = 4;

		len = strlen(arg);
		if (len >= 2 && (bAdmin || bNormal))
			arg[len-2] = '\0';

		// �Ӹ� ���� ��������� Ȯ���Ѵ�.
		if (say_type == 1
				&& g_pNk2DFrame
				&& g_pNk2DFrame->GetControlBottom()
				&& g_pNk2DFrame->GetControlBottom()->GetNoWhisper()
				&& g_pNk2DFrame->GetControlBottom()->GetNoWhisper()->IsIntheList(&g_Buf[nSayto_len+2]))
//			&& g_pNk2DFrame->GetControlBottom()->GetNoWhisper()->IsIntheList(&g_Buf[nSayto_len]))
		{
			char buf[256];
			strcpy(buf, "nochat ");
			strcat(buf, &g_Buf[nSayto_len+2]);
//			strcat(buf, &g_Buf[nSayto_len]);
			strcat(buf, "\n");
			if( g_pTcpIp )
				g_pTcpIp->SendNetMessage(buf);
			return;
		}

		char *arg3 = arg2;
		SkipSpaces(&arg3);

		if(g_bFiltering)
			CheckAndRepair(arg3);

		arg2 = AnyOneArg(arg, g_Buf); // �� �༮ ��ġ�� ������ �߿��Կ� ����! ���� "char *arg3 = arg2;" �� �� ������ �;��Ѵ�.// ���⼭ �̰� �ٽ����ִ� ������ ������ arg�� ��Ʈ�� �պκ��� ���Ĺ����� ��ƾ�� �ִ�. �װ� �����ؼ� �������� arg2�� ������ؼ� �ٽ� �����Ѵ�.( by ���� )
		if( bMatrixMaster )
		{
			g_pNk2DFrame->SetInfoBox2(arg2);
		}
		if (pCha)
		{
			if( say_type == 1 )
			{
				pCha->SetChatMsg(&g_Buf[2], arg3);
			}
			else if( say_type == 0 )
			{
				if( DataFriend::GetInstance()->IsDenyFriend(g_ii[0]) == true )
					return;

				pCha->SetChatMsg(g_Buf, arg3);
			}
			else
			{
				pCha->SetChatMsg(g_Buf, arg3);
			}
		}

		// [5/6/2008 ppmmjj83] ����� ��û���� ä��â�� ǥ�õǴ� ���̵� ���� �ؽ�Ʈ ����
		if( g_dwClientCountry == CTRY_BRA )
		{
			*arg2 = '>';
		}

		else
		{
			*arg2 = ')';
		}
	}

	if( g_ii[0] == -2 ) // say -2 Ÿ���� �����޼����� ��ȣ�� �Ѿ���� Ÿ��. ///�����޼���
	{
		arg = AnyOneArg(arg, g_Buf); // �� �༮ ��ġ�� ������ �߿��Կ� ����! ���� "char *arg3 = arg2;" �� �� ������ �;��Ѵ�.// ���⼭ �̰� �ٽ����ִ� ������ ������ arg�� ��Ʈ�� �պκ��� ���Ĺ����� ��ƾ�� �ִ�. �װ� �����ؼ� �������� arg2�� ������ؼ� �ٽ� �����Ѵ�.( by ���� )
		g_ii[1] = atoi(g_Buf);			// ���� �޼��� ��ȣ.

		if( g_pNk2DFrame )
			g_pNk2DFrame->AddChatStr((char*)G_STRING(g_ii[1]), say_type);	 // �������� �ٷ� �޼��� ��ȣ�� �޵��� ���� ///07-04-27
	}

	// [5/6/2008 ppmmjj83] �±� ����� Ƽ���� ���� �̺�Ʈ ����.
	if( g_ii[0] == -3 )
	{
		char strTemp[512] = {0, };

		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);

		switch( g_ii[1] )
		{
		case 0:
			{
				arg = AnyOneArg(arg, g_Buf);
				g_ii[2] = atoi(g_Buf);

				sprintf( strTemp, (char*)G_STRING(IDS_YELOWWT_EVENTMSG0), g_ii[2] );
			}
			break;

		case 1:
			{
				arg = AnyOneArg(arg, g_Buf);
				g_ii[2] = atoi(g_Buf);

				sprintf( strTemp, (char*)G_STRING(IDS_YELOWWT_EVENTMSG1), g_ii[2] );
			}
			break;

		case 2:
			{
				if( g_pNk2DFrame )
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_YELOWWT_EVENTMSG2), say_type);
			}
		case 3:
			{
				if( g_pNk2DFrame )
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_YELOWWT_EVENTMSG3), say_type);
			}
			break;

		case 4:
			{
				if( g_pNk2DFrame )
					g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_YELOWWT_EVENTMSG4), say_type);
			}
			break;

		default:
			break;
		}

		if( strcmp( strTemp, "" ) != 0 )
		{
			if( g_pNk2DFrame )
				g_pNk2DFrame->AddChatStr(strTemp, say_type);
		}
	}

	else
	{
		SkipSpaces(&arg);
		//////////////////////////////////////////////////////////////////////////
		// [2008/5/8 Theodoric] log�����
		if( g_bAdmin )
		{
			char strTemp[1024] = {0,};
			char strWrite[1024] = {0,};
			sprintf(strTemp, "%s", arg);

			char* strTemp1 = AnyOneArg(strTemp, g_Buf);
			if( !strnicmp(g_Buf, "Base:", 5) )
			{
				// ��Ŷ ����
				int dmg_base = 0;
				int dmg_dam  = 0;

				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				dmg_base = atoi( g_Buf);

				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				dmg_dam  = atoi( g_Buf);

				sprintf(strTemp, "Base : %d  =>  Dam : %d  ", dmg_base, dmg_dam);
				G_CatLocalTimeToStr(strWrite, strTemp);

				if( b_Damage && g_bAdmin2 )
				{
					tab3_Dmg_base += dmg_base;
					tab3_Dmg_dam  += dmg_dam;

					FILE* fp = NULL;
					fp = fopen( "LhLog/DamageLog.txt", "a+" );
					fprintf( fp, strWrite );
					fclose( fp );
				}

				G_DevAddPointString(strWrite);
			}
			else if( !strnicmp(g_Buf, "*", 1) )
			{
				strTemp1 = AnyOneArg(strTemp1, g_Buf);

				if( !strnicmp(g_Buf, "Counter_DAM:", 12) )
				{
					int dmg = atoi(strTemp1);
					sprintf(strTemp, "=>  Counter_DAM : %d", dmg);

					if( b_Damage && g_bAdmin2 )
					{
						FILE* fp = NULL;
						fp = fopen( "LhLog/DamageLog.txt", "a+" );
						fprintf( fp, "%s\n", strTemp );
						fclose( fp );
					}

					G_CatLocalTimeToStr(strWrite, strTemp);
					G_DevAddPointString(strWrite);
				}
				else if( !strnicmp(g_Buf, "Critical_DAM::", 13) )
				{
					int dmg = atoi(strTemp1);

					sprintf(strTemp, "=>  Critical_DAM : %d", dmg);

					if( b_Damage && g_bAdmin2 )
					{
						FILE* fp = NULL;
						fp = fopen( "LhLog/DamageLog.txt", "a+" );
						fprintf( fp, "%s\n", strTemp );
						fclose( fp );
					}

					G_CatLocalTimeToStr(strWrite, strTemp);
					G_DevAddPointString(strWrite);

				}
			}
			else if( !strnicmp(g_Buf, "Last", 4) )
			{
				int dmg_last = 0;
				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				dmg_last = atoi( g_Buf);

				sprintf(strTemp, "=>  Last : %d", dmg_last);

				if( b_Damage && g_bAdmin2 )
				{
					tab3_Dmg_Last += dmg_last;

					FILE* fp = NULL;
					fp = fopen( "LhLog/DamageLog.txt", "a+" );
					fprintf( fp, "%s\n", strTemp );
					fclose( fp );
				}

				G_CatLocalTimeToStr(strWrite, strTemp);
				G_DevAddPointString(strWrite);
			}
			else if( !strnicmp(g_Buf, "����", 4) )
			{
				int exp  = 0;
				int lime = 0;

				char strTemp2[512];

				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				exp = atoi(g_Buf);

				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				strTemp1 = AnyOneArg(strTemp1, g_Buf);
				lime = atoi(g_Buf);

				if( b_EXP && g_bAdmin2 )
				{
					tab3_EXP += exp;

					FILE* fp = NULL;
					fp = fopen( "LhLog/ExpLog.txt", "a+" );
					sprintf(strTemp2, "EXP : %8d", exp);
					G_CatLocalTimeToStr(strWrite, strTemp2);
					fprintf( fp, "%s\n", strWrite );
					fclose( fp );
				}

				if( b_Lime && g_bAdmin2 )
				{
					tab3_Lime += lime;

					FILE* fp = NULL;
					fp = fopen( "LhLog/LimeLog.txt", "a+" );
					sprintf(strTemp2, "Lime : %8d", lime);
					G_CatLocalTimeToStr(strWrite, strTemp2);
					fprintf( fp, "%s\n", strWrite );
					fclose( fp );
				}
				G_CatLocalTimeToStr(strWrite, strTemp);
				G_DevAddPointString(strWrite);
			}

			//////////////////////////////////////////////////////////////////////////

		}

		if( g_pNk2DFrame && pCha && say_type == 0 && pCha->IsPressMan() )
			say_type = 	7;
		// [4/10/2009 D.K ] : ��׷��� �̿�� ���� ������ ��� ��׷��� ����.
		if( g_pNk2DFrame )
		{
			if( strstr( arg, "���� ����" ) && pCMyApp->m_pUIMgr->m_bAutoHunt )
				pCMyApp->m_pUIMgr->m_AutoPlay->StopProc(AutoPlay_StopProc__Laim_Not);
		}
		if( g_pNk2DFrame )
			g_pNk2DFrame->AddChatStr(arg, say_type);

	}
}



void CmdWearing(char *arg, CUIMgr *pMgr)
{
	for(int i=0; i<WEARING_NUM; i++)
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);
		///�Ź���ȭ�ý���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf); // �ƽ� ��ȭ ������.

		if( g_SvrType == ST_ADULT_ONLY)// [6/1/2007 Theodoric] ������ ����
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[7] = atoi(g_Buf);		// �Ϲ� ������
			arg = AnyOneArg(arg, g_Buf);
			g_ii[8] = atoi(g_Buf);		// �Ϲ� ������ max
		}

		if(g_pRoh)
		{
			if( g_SvrType == ST_ADULT_ONLY)
				g_pRoh->Wear(i, g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8] ); ///�Ź���ȭ�ý���
			else
				g_pRoh->Wear(i, g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], 0, 0 ); ///�Ź���ȭ�ý���
		}
	}

	g_pRoh->OnBossRaidHeroEffect();
}

void CmdInven(char *arg, CUIMgr *pMgr)
{
	//sscanf(msg, "%s %d %d %d %d %d", first_arg, &g_ii[0], &g_ii[1], &g_ii[2], &g_ii[3], &g_ii[4]);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);			// ???
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);		// ???

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);	// ???
	g_ii[5] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[8] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);			// �Ϲ� ������ Max
	}

	if( g_pRoh )
	{
		if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
			g_pRoh->AddToInven(g_ii[0], g_ii[3], g_ii[4], g_ii[1], g_ii[2], gem_num[0], special[0], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9] ); ///�Ź���ȭ�ý���
		else
			g_pRoh->AddToInven(g_ii[0], g_ii[3], g_ii[4], g_ii[1], g_ii[2], gem_num[0], special[0], g_ii[5], g_ii[6], g_ii[7], 0 , 0 ); ///�Ź���ȭ�ý���
	}
}

void CmdExtra(char *arg, CUIMgr *pMgr)
{
	//sscanf(msg, "%s %d %d", first_arg, &g_ii[0], &g_ii[1]);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);		// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);		// �Ϲ� ������ Max
	}

	if( g_pRoh )
	{
		if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
			g_pRoh->SetExtraSlot(g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6] ); ///�Ź���ȭ�ý���
		else
			g_pRoh->SetExtraSlot(g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[2], g_ii[3], g_ii[4], 0, 0 ); ///�Ź���ȭ�ý���
	}
}

void CmdPickExtra(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		// ��������
		g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1833) , -1 );

		if( CommonConfig::Instance()->GetLagrush() == true )
		{
			pMgr->m_AutoPlay->OnDontPick();
		}	

		return;
	}

	g_ii[0] = rv;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);		// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);		// �Ϲ� ������ Max
	}

	if (g_pNk2DFrame
			&& g_pNk2DFrame->GetControlInven())
	{
		g_pNk2DFrame->GetControlInven()->SetPickExtraTime();
	}

	if( g_pRoh )
	{
		if( g_SvrType == ST_ADULT_ONLY )
			g_pRoh->SetExtraSlot(g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6] ); ///�Ź���ȭ�ý���
		else
			g_pRoh->SetExtraSlot(g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[2], g_ii[3], g_ii[4], 0, 0 ); ///�Ź���ȭ�ý���
	}

	// ��Ŷ�� ���� �Ŀ� pick �÷��׸� ����( by ���� )
	if( pMgr )
		pMgr->m_bPickLock = FALSE; ///pick_bug
}

void CmdQuick(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[5] = atoi(g_Buf); // special2 (06-04-29 �߰�)

	if( g_pRoh )
		g_pRoh->ToQuickSlot(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5]);
}

void CmdRemoveAll(char *arg, CUIMgr *pMgr)
{
	if( g_pRoh )
		g_pRoh->RemoveAll();
}

void CmdDrop(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	dir = atof(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atof(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atof(g_Buf);

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf); // �߰� �ɼ� m_Special2.

	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf); // �ð��� ������������ �÷���.

	if( pMgr )
		pMgr->AddItem(g_ii[0], g_ii[1], x, z, dir, gem_num[0], special[0], g_ii[2], g_ii[3], TRUE); ///�Ź���ȭ�ý���
}
/*
void CmdNpcDrop(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	dir = atof(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);

	if (pMob = pMgr->FindMobById(g_ii[2]))
		pMob->SetDropItem(g_ii[0], g_ii[1], x, z, dir);
}
*/
void CmdPick(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// �ε���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// vnum
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);			// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);			// y
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf);			// ���� �ѹ�
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[5] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[8] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);			// �Ϲ� ������ Max.
	}

	if( g_pRoh )
	{
		if( g_SvrType == ST_ADULT_ONLY )
			g_pRoh->AddToInven(g_ii[4], g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9]); ///�Ź���ȭ�ý���
		else
			g_pRoh->AddToInven(g_ii[4], g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[5], g_ii[6], g_ii[7], 0, 0 ); ///�Ź���ȭ�ý���

		// [1/6/2009 D.K ] : ������ ����� ���� ������ �޽��� ���.
		char szMessage[128] = {0,};
		if( g_dwClientCountry == CTRY_KOR )
		{
			sprintf( szMessage, G_STRING(IDS_LHSTRING1725), GET_ITEM_NAME_VNUM(g_ii[1]) );
			g_pNk2DFrame->AddChatStr( szMessage, -1 );
		}
		else if( g_dwClientCountry == CTRY_JPN )
		{
			if(g_pNk2DFrame->GetControlShop() && g_pNk2DFrame->GetControlShop()->m_bMultibuy )
			{
				g_pNk2DFrame->GetControlShop()->m_iMulitCnt++;

				if( g_pNk2DFrame->GetControlShop()->m_iMulitCnt == 10 )
				{
					// IDS_LHSTRING1725
					// sprintf( szMessage, G_STRING(IDS_LHSTRING1725) , g_ItemList.m_ItemArray[g_ItemList.FindItem( g_ii[1])].m_Name );
					sprintf( szMessage, "%s 10�擾.", GET_ITEM_NAME_VNUM(g_ii[1]) );
					g_pNk2DFrame->GetControlShop()->m_iMulitCnt = 0;
					g_pNk2DFrame->GetControlShop()->m_bMultibuy = false;
					g_pNk2DFrame->AddChatStr( szMessage, -1 );
				}
			}
			else
			{
				sprintf( szMessage, "%s �擾.", GET_ITEM_NAME_VNUM(g_ii[1]) );
				// G_STRING(IDS_LHSTRING1725)
				g_pNk2DFrame->AddChatStr( szMessage, -1 );
			}
		}
		else
		{
			sprintf( szMessage, G_STRING(IDS_LHSTRING1725), GET_ITEM_NAME_VNUM( g_ii[1]) );
			g_pNk2DFrame->AddChatStr( szMessage, -1 );
		}

		g_pRoh->CountQuickAll();
	}

	if( g_pNk2DFrame && g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet() ) ///�굵�� �� �ߵ� ������ üũ�Ѵ�.
		g_pNk2DFrame->GetControlHelpPet()->CheckHelpCondition( 2, g_ii[1], TRUE ); // ������ ���� ������ ������ �ִ��� üũ�Ѵ�.

	// ��Ŷ�� ���� �Ŀ� pick �÷��׸� ����( by ���� ) (��� �� �÷��� ������ �ذ��ϴ� ���״� CmdPickExtra() �� ���ö� �ش��ϴ� ���������� �÷����� ������ ���⼭�� ������Ѵ�.)
	if( pMgr )
		pMgr->m_bPickLock = FALSE; ///pick_bug
}


void CmdPickup(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));
	ef_sort.nType = FX_EATEFFECTS;

	pCha = pMgr->FindChaById(g_ii[0], FALSE);

	if( pCha )
	{
		ef_sort.pNkChaTo = pCha;
		pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
	}
	else if (g_pRoh->m_nCharIndex == g_ii[0])
	{
		ef_sort.pNkChaTo = g_pRoh;
		if( g_pRoh )
			g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
	}
}

void CmdHour(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_BULKAN )
		pCMyApp->ChangeHour(23); // ������ ������ �����Ѵ�.
	else
		pCMyApp->ChangeHour(g_ii[0]);

	pCMyApp->SetWaterRender(TRUE);

	if( pCMyApp->GetCurWorldID() == WORLD_BOSSRAID_BULKAN && ( g_ii[0] >= 28 || g_ii[0] <= 3 ) )
		pCMyApp->SetWaterRender(FALSE);
}

void CmdWeather(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if(pCMyApp->IsAcropolis())
		g_ii[0] = 0;

	if (!(g_bDungeon || g_bNewTerrainDungeon )&& !pCMyApp->m_ProOption.bWeather)
		if( pCMyApp->m_pWeatherMgr )
			pCMyApp->m_pWeatherMgr->SetWeather(g_ii[0]);
}

void CmdStatus(char *arg, CUIMgr *pMgr)
{
	if( !g_pRoh || !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	// nate 2005-09-08 : ����ġ
	__int64 n64Exp = 0.0f;
	if( g_ii[0] == STATUS_EXP || g_ii[0] == STATUS_NEED_EXP )
		n64Exp = _atoi64( g_Buf );
	else
		g_ii[1] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);

	switch (g_ii[0])
	{
	case STATUS_VITAL:
		g_pRoh->SetVital(g_ii[1], g_ii[2]);
		break;
	case STATUS_MANA:
		g_pRoh->SetMana(g_ii[1], g_ii[2]);
		break;
	case STATUS_STAMINA:
		g_pRoh->SetStamina(g_ii[1], g_ii[2]);
		break;
	case STATUS_EPOWER:
		g_pRoh->SetEpower(g_ii[1], g_ii[2]);
		break;
	case STATUS_LEVEL:
		g_pRoh->SetLevel(g_ii[1]);
		break;
	case STATUS_LEVELUP_POINT:
		g_pRoh->SetLevelupPoint (g_ii[1]);
		break;
	case STATUS_EXP:
		g_pRoh->SetExp(n64Exp);
		break;
	case STATUS_NEED_EXP:
		g_pRoh->SetNeedExp(n64Exp);
		break;
	case STATUS_STR:
		g_pRoh->SetStr(g_ii[1]);
		break;
	case STATUS_INT:
		g_pRoh->SetInt(g_ii[1]);
		break;
	case STATUS_DEX:
		g_pRoh->SetDex(g_ii[1]);
		break;
	case STATUS_CON:
		g_pRoh->SetCon(g_ii[1]);
		break;
	case STATUS_CHA:
		g_pRoh->SetCha(g_ii[1]);
		break;
	case STATUS_MONEY:
		g_pRoh->SetMoney(g_ii[1]);
		break;
	case STATUS_PENALTY://1024
		g_pRoh->m_Chaotic_Num = g_ii[1];
		g_pRoh->SetPenalty();
		g_pRoh->SetDefense();	//�켱�� ���⿡�� ���� ǥ�� ���ֱ�.
		if(g_pRoh->m_Chaotic_Num<=-5000)
		{
			g_pRoh->m_Chaotic_Grade = 2;
		}
		else if(g_pRoh->m_Chaotic_Num <= -10 && g_pRoh->m_Chaotic_Num >= -4999)
		{
			if(g_pRoh->m_Chaotic_Grade <10)
				g_pRoh->m_Chaotic_Grade = 1;
		}
		break;

	case STATUS_CONFIRMCODE: // ���丶�콺 üũ ���� �ڵ�. ��Ŀ�� ���̱� ���� status ��Ŷ���� ���´�.(by ����) ///�����Է½ý��ۺ���

		if( g_pNk2DFrame->GetAutoMouse() )
			g_pNk2DFrame->GetAutoMouse()->SetConfirmNumber( g_ii[1], g_ii[2] );

		break;

	case STATUS_CASH: ///�������.
		g_pRoh->SetCash( g_ii[1] );
		break;

	case STATUS_FAME:
		g_pRoh->SetFame(g_ii[1]); //�İ���
		break;

	}

	//�ʽ� �ý��� �ű����� ��ư
	//ó�� �α��� ������ �ѹ� �űԸ޽������ִ��� üũ
	if(g_dwClientCountry == CTRY_KOR && pMgr->isFirstNewLetter)
	{
		pMgr->isNewLetter();
		pMgr->isFirstNewLetter = FALSE;
	}
}

void CmdAttackVital(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	vital = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);   //ĳ������ ����� ����
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2]= atoi(g_Buf); //�迭�� ��������.

	if( g_pRoh )
		g_pRoh->SetAttackType(g_ii[1]);

	if (!strncmp(g_Buf2, "n", 1))
	{
		if (pMob = pMgr->FindMobById(g_ii[0]))
		{
			if(g_ii[2]==0)
				pMob->SetClassType(g_ii[2]);

			pMob->SetAttackVital(vital);

			if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
			{
				if(vital == 0)
					pMgr->m_AutoPlay->KillMob(g_ii[0]);
			}
		}
	}
	else if (!strncmp(g_Buf2, "p", 1)) // �ٸ� ���� �׾������� ó���� ������ ������. �׷��� �߰�(05-10-27 ����)
	{
		if( vital <= 0 ) // ����� �׾��� ���� ó���� �ʿ�.
		{
			if (pPet = pMgr->FindPetById(g_ii[0]))
			{
				pPet->Kill(); // ���� �ٷ� �׿�������.
			}
		}
	}
	else
	{
		// "c"
		if (pCha = pMgr->FindChaById(g_ii[0]))
			pCha->SetAttackVital(vital);
	}

	// [8/7/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ���̺� �ҿ� :: ����� ���� ȿ�� �� ����
	if( g_pRoh && ( g_ii[1] == 1 || g_ii[1] == 2 ) )
	{
		EffectSort *TempEffect = NULL;
		for(int i=0; i<3; i++)
		{
			TempEffect = g_pRoh->FindMyFairy( SKILL_BABYSOUL_1+i);

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
					if(g_ii[1] == 2)	bAction = true;
					break;
				// ��ġ :: ī��Ʈ ����
				case SKILL_BABYSOUL_3 :
					if(g_ii[1] == 1)	bAction = true;
					break;
				}

				if( bAction )
				{
					TempEffect->num = FX_BABYSOUL_STATE_CRITICAL;
					TempEffect->vSortPos.y = 0.0f; // ������ �ʱ�ȭ.

					EffectSort ef_sort;
					ZeroMemory(&ef_sort, sizeof(EffectSort));

					ef_sort.nType		= FX_BABYSOUL;
					ef_sort.pNkChaTo	= g_pRoh;// g_pRoh;
					ef_sort.vPos		= D3DVECTOR(TempEffect->vCurPos.x, TempEffect->vCurPos.y-20.0f, TempEffect->vCurPos.z);
					ef_sort.num			= 0;

					g_pRoh->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );

					break;
				}

				continue;
			}

		}
	}

}

void CmdKill(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if (!strncmp(g_Buf2, "n", 1))
	{
		if (pMob = pMgr->FindMobById(g_ii[0]))
			pMob->Kill();
	}
	else if(!strncmp(g_Buf2, "p", 1))
	{
		if (pPet = pMgr->FindPetById(g_ii[0]))
			pPet->Kill();
	}
	else
	{
		// "c"
		if (pCha = pMgr->FindChaById(g_ii[0]))
			pCha->Kill();
	}
}

void CmdSocial(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	if ((g_ii[1] >= 67 && g_ii[1] <= 97) || g_ii[1] == 105 || (g_ii[1] >= 153 && g_ii[1] <= 158) )
	{
		if (!strncmp(g_Buf2, "c", 1))
		{
			if (pCha = pMgr->FindChaById(g_ii[0]))
				pCha->SetMotionState(CHA_SOCIAL, g_ii[1]);
		}
	}
}

void CmdCombat(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	if (pCha = pMgr->FindChaById(g_ii[0], TRUE)) // �ڱ� �ڽŵ� �ٲ�� �ְ� ����(��ȭ����� ���ݴ��ϸ� �������� �ٲ�Ը� �������� �Ǵ�����) ///������� �� ����
	{
		pCha->SetCombat(g_ii[1]);
		pCha->ResetMotionState();
	}
}

//--------------------------------------------------------------------------
// CmdCharWear
//--------------------------------------------------------------------------
// �ٸ� ĳ���� ��� ������ �� ���� �޼���.
// Lyul - 2004.08.31
// ����� ���� Gem_Num �� �����Ѵ�. (���� �߰��� ���� �ı�ȿ��!)
void CmdCharWear(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);    // Plus ��ġ
	g_ii[3] = atoi(g_Buf);

	if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		pCha->Wear(g_ii[1], -1, g_ii[2], g_ii[3] );
}

void CmdCharEventWear(char *arg, CUIMgr *pMgr) ///�̺�Ʈ��������
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf); // where
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf); // vnum
	g_ii[2] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);    // Plus ��ġ
	g_ii[3] = atoi(g_Buf);

	if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		pCha->EventWear(g_ii[1], -1, g_ii[2], g_ii[3] );
}

void CmdCharRemove(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		pCha->Remove(g_ii[1]);
}

void CmdCharEventWearRemove(char *arg, CUIMgr *pMgr) ///�̺�Ʈ��������
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		pCha->EventWearRemove(g_ii[1]);
}

void CmdInfo(char *arg, CUIMgr *pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	SkipSpaces(&arg);
	g_pNk2DFrame->SetInfoBox(arg);
	if (g_pDSound)
		g_pDSound->Play(g_EffectSound[EFF_SND_LEVELUP]);

	g_pNk2DFrame->AddChatStr(arg, 4);
}

void CmdInfo2(char *arg, CUIMgr *pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	SkipSpaces(&arg);
	
	g_pNk2DFrame->AddChatStr(arg, 4);
}

void CmdHeroInfo(char *arg, CUIMgr *pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	SkipSpaces(&arg);
	g_pNk2DFrame->SetInfoBox2(arg);
	if (g_pDSound)
		g_pDSound->Play(g_EffectSound[EFF_SND_LEVELUP]);

	g_pNk2DFrame->AddChatStr(arg, 8);
}

void CmdNotice(char *arg, CUIMgr *pMgr) ///�����˾�â
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	g_pNk2DFrame->ShowControlNoticeWindow( TRUE, 1, arg ); // ���� �������̽��� ��Ʈ���� �߰�.(������ �ȶ��־����� ���� ����.) �ι�°���� Ÿ�� 1�� ����콺 �Ʒ��� �߰��. ���߿� ��Ŷ���� ������.
	if (g_pDSound)
		g_pDSound->Play(g_EffectSound[EFF_SND_LEVELUP]);
}

void CmdAt(char *arg, CUIMgr *pMgr)
{
	if( !g_pRoh )
		return;	

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	dir = 0;

	// nate 2005-08-31 : �� ���� �ۿ��� �����Ǵ� ���׶�����
	if( pCMyApp->m_nCurWorldIdx == WORLD_START )
	{
		if( !pCMyApp->IsInsideMap( x, z ) )
		{
			char strTemp[50]; ///�ʿ����ۻ�������
			sprintf( strTemp, "Server send wrong position [%d, %d]\n", x, z );
			if( g_pNk2DFrame )
				g_pNk2DFrame->InsertPopup( strTemp, TYPE_NOR_OK, 1 );

			pCMyApp->SetHeroInitPos(7066, 0, 5257, 1.5707f); // �ϴ� ��׶�̾� ��� ������ �������ش�.
		}

		///�굵��Ȯ��
		// ���� ���� ���ᶧ �� ������ �ѳ������� ���θ� Ȯ��, �ѳ�����, �κ��� ������ ��(1596)�� �ִٸ� �굵���� ���ش�.
		if( g_pNk2DFrame && !g_pNk2DFrame->IsHelpPetVisible() ) // �ٸ� ������ �°ɼ��� ������ �̰� Ȯ��������.
		{
			FILE *fp;
			int OnOff = 0;
			fp = fopen( "data/etc/OnOff.txt", "rt" ); // �׾����� �������� ����.
			if( fp ) // ���� ������ ���ٸ� ��Ű�� �ȴ�.
			{
				fscanf( fp, "%d\n", &OnOff );
				fclose( fp );

				if( OnOff ) // ���־��ٸ�...
				{
					CItem *pItem = g_pRoh->FindItemByVnumFromAll(1596); // �κ��� �˻��Ѵ�.Ȥ�� �ѳ��� ������ �Ȱ� �������� ��� ���� �� ����� �������ϱ�.
					if( pItem ) // �����۵� ���� ��츸 ���ش�.
						g_pNk2DFrame->ToggleHelpePetWindow(0); // ���ش�.
					else // ���� �����־��µ� �������� �������ٸ�..
					{
						FILE *fp;
						fp = fopen( "data/etc/OnOff.txt", "wt" ); // �׾����� �������� ����.
						fprintf( fp, "0\n" ); // �÷��׸� �������ش�.
						fclose( fp );
					}
				}
			}
		}
	}

	g_pRoh->m_nCharIndex = g_ii[0];

	pCMyApp->SetHeroInitPos((float)x, (float)y, (float)z, (float)dir);	// ī�޶� ������ �ʿ�������.
	pCMyApp->StopHero(FALSE);
	g_pRoh->SetMotionState(CHA_STAND);

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));
	ef_sort.nType = FX_TELEPORT;
	ef_sort.vPos.x = x;
	ef_sort.vPos.z = z;
	if( g_bNewTerrain )
	{
		float	fHeight = pCMyApp->GetLandPtr()->GetHFHeight( x, z );
		ef_sort.vPos.y = CNKObjQuadNode::GetHeightOnObject( z, x, y );
		if( ef_sort.vPos.y < fHeight )
			ef_sort.vPos.y = fHeight;
	}
	else
		ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight( x, z );

	pCMyApp->InitTimeCtrl();
	if( pCMyApp->m_pFxSet )
		pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
	pCMyApp->m_bPlaying = TRUE;
	pCMyApp->m_bBeforeGoWorld = FALSE;						// connect�Ǿ��� �����̴�.
	// ���尣 �̵����� ���Ǵ� �÷���. ��ð� At�� �� ���� ���α׷� ������.
	pCMyApp->m_bWaitingAt = FALSE;
	// nate 2005-05-05 : ����Ʋ( ����� )���� ���̵��� �÷��� �ʱ�ȭ
	g_pRoh->m_nTeamMemGrade = TEAM_BATTLE_NONE;

	if( g_dev_client )
	{
		char buf[MAX_PATH] = {0,};
		sprintf(buf, "Laghaim [IP : %s][PORT : %d][UserIdx : %d][CharIdx : %d]", g_pTcpIp->GetIp().c_str(), g_pTcpIp->GetPort(), g_pRoh->m_nUserIndex, g_pRoh->m_nCharIndex);
		::SetWindowText(pCMyApp->Get_hWnd(), buf);
	}

	if( CommonConfig::Instance()->GetRenewerCharInfo() == true )
	{
		if( g_pNk2DFrame && (CControlScore*)g_pNk2DFrame->GetInterface(SCORE) )
		{
			CControlScore* pScore = (CControlScore*)g_pNk2DFrame->GetInterface(SCORE);
			pScore->LoadRes_Char(true);
		}
	}
}

void CmdGoto(char *arg, CUIMgr *pMgr)
{
	// nate 2004 - 11 : �� üũ�� ���� �������� Ȯ��
	g_pTcpIp->SendNetMessage( "hack_check goto\n" );
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	y = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	dir = atof(g_Buf);

	pMgr->EraseAllList();

	//wan:2005-04	 goto �� �޾Ҵ�. ���� DASH�ᵵ �ȴ�.
	pMgr->m_bNextGoto = TRUE;
	pCMyApp->SetHeroInitPos(x, y, z, dir, FALSE);	// ī�޶� ������ �ʿ�������.
	if( g_pRoh )
		g_pRoh->SetMotionState(CHA_STAND);
	pCMyApp->StopHero(FALSE);

	if( pCMyApp->m_pUIMgr->m_bAutoHunt )
	{
		if( pCMyApp->m_pUIMgr->m_AutoPlay->m_bUseTrans )
			pCMyApp->m_pUIMgr->m_AutoPlay->SetPos( g_pRoh->m_wx , g_pRoh->m_wz );
	}

	if( !pCMyApp->m_pFxSet )
		return;

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));
	ef_sort.nType = FX_SHOWUP2;
	ef_sort.vPos.x = x;
	ef_sort.vPos.z = z;

	if( g_bNewTerrain )
	{
		float	fHeight = pCMyApp->GetLandPtr()->GetHFHeight( x, z );
		ef_sort.vPos.y = CNKObjQuadNode::GetHeightOnObject( z, x, y );
		if( ef_sort.vPos.y < fHeight )
			ef_sort.vPos.y = fHeight;
	}
	else
		ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight( x, z );

	pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
	ef_sort.nCurFrame = -2;
	pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
	ef_sort.nCurFrame = -4;
	pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

	if(pMgr->m_bTeleport)
	{
		g_pTcpIp->SendNetMessage("tp\n");
		pMgr->m_bTeleport = FALSE;
	}
}

void CmdShopItem(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int item_vnum = atoi(g_Buf);

	if (g_pNk2DFrame && g_pNk2DFrame->IsShopVisible() && g_pNk2DFrame->GetControlShop() )
		g_pNk2DFrame->GetControlShop()->AddItem(0, item_vnum);
}

void CmdShopSPItem(char *arg, CUIMgr *pMgr) //�ɼǰ��� �߰��� �����۵� �������ְ� �ϴ� ���� by ���� ///BP����
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf); // index (������ ������ȣ. �߰��Ǵ� ����� ������ ��� �ȶ� �̰��� �־� ����Ѵ�.)

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf); // vnum

	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf); // plus ��ġ

	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf); // option ��

	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf); // option2 ��

	arg = AnyOneArg(arg, g_Buf);
	g_ii[5] = atoi(g_Buf); // ������ ��

	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // ���ѽð�(�ð��� �ƾ����� ���)

	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // ����

	arg = AnyOneArg(arg, g_Buf);
	g_ii[8] = atoi(g_Buf); // ���� ����.

	if (g_pNk2DFrame && g_pNk2DFrame->IsShopVisible() && g_pNk2DFrame->GetControlShop() )
		g_pNk2DFrame->GetControlShop()->AddSPItem( 0, g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8] );
}

void CmdShopRate(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf); // ���� Ÿ��. �� ������ BP��������, ���ӻ����������� �˷��ش�.(by ����) ///BP����

	if(g_pNk2DFrame && g_pNk2DFrame->GetControlShop()->IsLpShop() && g_pNk2DFrame->GetControlShop() )
	{
		g_pNk2DFrame->GetControlShop()->RemoveAllItems();
	}

	if (g_pNk2DFrame && g_pNk2DFrame->IsShopVisible() && g_pNk2DFrame->GetControlShop() )
	{
		if (g_bMatrixMatch)
			g_pNk2DFrame->GetControlShop()->SetRate(0, 0);
		else
			g_pNk2DFrame->GetControlShop()->SetRate(g_ii[0], g_ii[1], (BYTE)g_ii[2]); ///BP����
	}
}

void CmdSpShopEnd(char *arg, CUIMgr *pMgr)
{
	if( g_pNk2DFrame && g_pNk2DFrame->GetControlShop() && g_pNk2DFrame->IsShopVisible() && g_pNk2DFrame->GetControlShop()->IsLpShop() )
	{
		g_pNk2DFrame->GetControlShop()->SetLpShopReady();
	}
}

void CmdSkillLevel(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	g_ChaSkill.SetSkillLevel(g_ii[0], g_ii[1]);
	if( g_pNk2DFrame
			&& g_pNk2DFrame->GetControlSkill())
	{
		g_pNk2DFrame->GetControlSkill()->m_pSkillInfo->SetIndex(-100);
		g_pNk2DFrame->GetControlSkill()->SetSkillEnable();
	}

	CControlScore * score = (CControlScore*)g_pNk2DFrame->GetInterface(SCORE);
	if(score)
		score->SetAllScore();
}

void CmdSkillLevelAll(char *arg, CUIMgr *pMgr)
{
	while (TRUE)
	{
		arg = AnyOneArg(arg, g_Buf);
		if (*g_Buf == '\0')
			break;
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);

		g_ChaSkill.SetSkillLevel(g_ii[0], g_ii[1]);
	}
	if( g_pNk2DFrame && g_pNk2DFrame->GetControlSkill() )
		g_pNk2DFrame->GetControlSkill()->SetSkillEnable();

	if( !g_pNk2DFrame || !g_pNk2DFrame->GetControlBottom() )
		return;
// g_ii[0]    ��ų ��ȣ
// g_ii[1]	������� ����...
	for( int i  = 0 ; i < 8 ; i++ )
	{
		if(g_ChaSkill.m_SkillNum < g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill
				|| (g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].type<0
					&& g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].type>2)
				|| (g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill!=-1
					&& g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill!=-2
					&& g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill!=-99
					&& g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill<0))
		{
			for(int j=0; j<8; j++)
			{
				g_pNk2DFrame->GetControlBottom()->m_QuickSkill[j].skill=-99;
				g_pNk2DFrame->GetControlBottom()->m_QuickSkill[j].type=0;
			}
			return;
		}

		if( g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill!=-1
				&& g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill!=-2
				&& g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill!=-99)
		{
			if(g_ChaSkill.m_SkillLevel[g_pNk2DFrame->GetControlBottom()->m_QuickSkill[i].skill]<=0)
			{
				for(int j=0; j<8; j++)
				{
					g_pNk2DFrame->GetControlBottom()->m_QuickSkill[j].skill=-99;
					g_pNk2DFrame->GetControlBottom()->m_QuickSkill[j].type=0;
				}
				return;
			}
		}
	}

	g_pRoh->SetDeactiveField();
	g_pRoh->SetDeactiveField_Ex();
	g_pRoh->SetDeactiveCritical();
	g_pRoh->SetDeactiveEngage();
	g_pRoh->SetDeactiveDSystem();
	g_pRoh->m_activate_buff_skill = 0;

}

//--------------------------------------------------------------------------
// CmdEffect
//--------------------------------------------------------------------------
// ���� ����Ʈ ��. ĳ�� ���ݿ� ���� ����� ����� �޴´�. �ľ�~
void CmdEffect(char *arg, CUIMgr *pMgr)
{
	char szOriBuffer[1024] = {};
	strcpy( szOriBuffer, arg );

	static EffectSort ef_sort;

	arg = AnyOneArg(arg, g_Buf);	// skill index
	int skill_idx = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);	// source kind

	//----------------------------------------------------------------------
	// From ĳ��
	if (!strncmp(g_Buf, "c", 1))
	{
		if ((skill_idx >= 0 && skill_idx < MAX_SKILL && g_Skills[skill_idx].m_Kind == SKILL_KIND_TO)
				|| skill_idx == SKILL_F_DASHSLASH || skill_idx == SKILL_F_SLASHSHADOW
				|| skill_idx == SKILL_F_STONEBASH1 || skill_idx == SKILL_F_STONEBASH2
				|| skill_idx == SKILL_F_BASHREFLECT1 || skill_idx == SKILL_F_BASHREFLECT2 )  // �Ϻ� ��ų ����ó��(SKILL_KIND_TO�� �ƴѳ༮��) ///�����޺�
		{
			arg = AnyOneArg(arg, g_Buf);	// source index
			g_ii[0] = atoi(g_Buf);

			int source_index = g_ii[0];
			int target_index = -1;

			//�����Ǽ��϶��� �ڱ����� ����Ʈ ���̰�
			if (pCha = pMgr->FindChaById(g_ii[0], pMgr->IsRohSkill( skill_idx )))
			{
				// from Player �� ���
				// !!!! �ӽ�. ��ų�� ���� ���Ʈ�� ��� ����� �����ؾ� �Ѵ�.
				if(pCha == g_pRoh && skill_idx==SKILLF_C_DASSAULT)
					g_pRoh->SetMotionState(CHA_F_DASSAULT);

				if(pCha == g_pRoh && skill_idx==SKILL_SUMMON_PARTITION) ///07-04-10 ���� : �����Ǽ� ��Ÿ�� �����̰� ������ �ȸ´°� �Ϻ����� ���� ���Ƽ� ���⼭ ��Ÿ�� ������ �����ߴ�.
					G_SK_SetCooltime(SKILL_SUMMON_PARTITION);

				arg = AnyOneArg(arg, g_Buf);	// target kind
				//----------------------------------------------------------------------
				// To ĳ�� From ĳ��
				if(!strncmp(g_Buf, "c", 1))
				{
					arg = AnyOneArg(arg, g_Buf);	// target index
					g_ii[0] = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);	// target vital
					g_ii[1] = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);	// special attack
					g_ii[2] = atoi(g_Buf);//1022
					pCha->SetAttackType(g_ii[2]);//Ư������ 1022
					arg = AnyOneArg( arg, g_Buf );	// nate 2005-06-27 : npc effect�� ��Ŷ�� ����ȭ���� ������ ��
					arg = AnyOneArg( arg, g_Buf );	// nate 2005-06-17 : Skill Step
					g_ii[ 3 ] = atoi( g_Buf );
					arg = AnyOneArg( arg, g_Buf );	// nate 2005-06-17 : Skill Point Value
					g_ii[ 4 ] = atoi( g_Buf );

					target_index = g_ii[ 4 ];

					if (pCha2 = pMgr->FindChaById(g_ii[0], TRUE))
					{
						if (pCha2 != g_pRoh)
							pCha2->SetAttackVital(g_ii[1]);
						pCha->m_nSkillLevel = g_ii[ 4 ];			// ĳ���� ��ų ����Ʈ ��
						pCha->SetSkillStep( g_ii[ 3 ] );			// ���� ����
						pCha->SetAttackChaId(pCha2->m_nCharIndex);	// ���� ��� ����
						pCha->SetMagicCha(pCha2, skill_idx );	// ����Ʈ ����
					}
				}
				//----------------------------------------------------------------------
				// To �� from ĳ��
				// ���� �Ǽ��� ��� �ռ�ȯ������ �����ش�.
				else
				{
					// pCha To pMob
					arg = AnyOneArg(arg, g_Buf);	// target index
					g_ii[0] = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);	// target vital
					g_ii[1] = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);	// special attack
					g_ii[2] = atoi(g_Buf);			// ī���� ũ��Ƽ�� ���� Ư��Ÿ�� �˸�
					pCha->SetAttackType(g_ii[2]);
					arg = AnyOneArg(arg, g_Buf);	// Mob Class
					g_ii[3] = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);	// Skill Step
					g_ii[4] = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);	// Skill Level
					g_ii[5] = atoi(g_Buf);

					target_index = g_ii[ 0 ];


					if (pMob = pMgr->FindMobById(g_ii[0]))
					{
						pMob->SetAttackVital(g_ii[1]);
						if(g_ii[3]==0)
							pMob->SetClassType(g_ii[3]);
						pCha->m_nSkillLevel = g_ii[ 5 ];			// ĳ���� ��ų ����Ʈ ��
						pCha->SetSkillStep( g_ii[ 4 ] );			// ���� ����
						pCha->SetMagicMob(pMob, skill_idx);		// ����Ʈ ����
						pCha->SetAttackMobId(pMob->m_nVirId);	// ���� ��� ����

						if(skill_idx==73)
							pMob->SetFissionType(1);
					}
				}
			}

			if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
			{
				pMgr->m_AutoPlay->SetSurport( source_index , target_index );
			}

		}
	}
	//wan:2004-12	ȭ��Ʈȥ ���� ���������� ����
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		if (pMob = pMgr->FindMobById(g_ii[0]))
		{
			if( pMob->m_nMobNum == 430 || pMob->m_nMobNum == 432 )
			{
				pMgr->InsertMagic(NULL, pMob, NULL, NULL, skill_idx);
				return;
			}

			arg = AnyOneArg(arg, g_Buf);
			//�߰���ų����: attack2 ���
			if(skill_idx == 71 || skill_idx == 72 || skill_idx == 73 || skill_idx == 74 )
				pMgr->m_bMultiAttack = TRUE;
			if (!strncmp(g_Buf, "c", 1))
			{
				// pMob To pCha2
				arg = AnyOneArg(arg, g_Buf);
				g_ii[0] = atoi(g_Buf);
				arg = AnyOneArg(arg, g_Buf);
				g_ii[1] = atoi(g_Buf);
				arg = AnyOneArg(arg, g_Buf);	// special attack ���� �ʴ´�.
				arg = AnyOneArg( arg, g_Buf );	// nate 2005-06-27 : npc effect�� ��Ŷ�� ����ȭ���� ������ ��
				arg = AnyOneArg( arg, g_Buf );	// Skill Step ���̳� �ɸ����� �¾����� ��ٿ� ����ϱ� ����
				g_ii[2] = atoi( g_Buf );
				if (pCha2 = pMgr->FindChaById(g_ii[0], TRUE))
				{
					pCha2->SetFailStep( g_ii[2] );
					if (pCha2 != g_pRoh)
						pCha2->SetAttackVital(g_ii[1]);
					pMob->Attack(pCha2->m_wx,pCha2->m_wz);
					pMgr->InsertMagic(NULL, pMob, pCha2, NULL, skill_idx);
				}
			}
			else
			{
				// pMob To pMob2
				arg = AnyOneArg(arg, g_Buf);
				g_ii[0] = atoi(g_Buf);
				arg = AnyOneArg(arg, g_Buf);
				g_ii[1] = atoi(g_Buf);
				if (pMob2 = pMgr->FindMobById(g_ii[0]))
				{
					if(skill_idx==73)
						pMob2->SetFissionType(1);
					pMob->Attack(pMob2->m_wx,pMob2->m_wz);
					pMob->SetAttackVital(g_ii[1]);
				}
			}
		}
	}
}


void CmdGoWorld(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);			// ip_address

	arg = AnyOneArg(arg, g_Buf2);
	g_ii[0] = atoi(g_Buf2);					// port

	arg = AnyOneArg(arg, g_Buf2);			// world number
	if (g_Buf2[0] == NULL)
		g_ii[1] = 0;
	else
		g_ii[1] = atoi(g_Buf2);

	arg = AnyOneArg(arg, g_Buf2);
	if (g_Buf2[0] == NULL)
		g_ii[2] = 0;
	else
		g_ii[2] = atoi(g_Buf2);

	if( g_pRoh->GetMyGuildData() )
		g_pRoh->DeleteMyGuildData();

	g_pNk2DFrame->SetInfoBox_NextString("");
	g_pNk2DFrame->SetInfoBox_NextString2("");

	if( pMgr )
		pMgr->GoWorld(g_Buf, g_ii[0], g_ii[1], g_ii[2]);
}

void CmdGoWorldFail(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->GoWorldFail();
}

void CmdExch(char *arg, CUIMgr *pMgr) // Message "exch"
{
	arg = AnyOneArg(arg, g_Buf);	// lock, trade, change, cancel
	if( pMgr )
		pMgr->Exch(g_Buf);
}

// �ٸ� �������Լ� �ŷ� ��û�� ���Դ�.
void CmdExchAsk(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);	// ���� �̸�.
	if( pMgr )
		pMgr->AskExchange(g_Buf);
}

void CmdExchStart(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);	// ��ȯ�����϶�� ���� �̸�.
	arg = AnyOneArg(arg, g_Buf1);	// ��ȯ�����϶�� ���� ����.
	g_ii[0] = atoi(g_Buf1);
	if( pMgr )
		pMgr->ExchStart(g_Buf, g_ii[0]);		// ���ǿ� ������ ��ȯâ�� ����
}

// exch_inven_to index vnum x y
void CmdExchInvenTo(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				//index
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);				// vnum
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);				// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);				// y
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);				// y
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);				// y

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[5] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if( g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[7] = atoi(g_Buf);		// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[8] = atoi(g_Buf);		// �Ϲ� ������ Max
	}

	if( pMgr )
	{
		if( g_SvrType == ST_ADULT_ONLY )
			pMgr->ExchInvenTo(g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8] ); ///�Ź���ȭ�ý���
		else
			pMgr->ExchInvenTo(g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], g_ii[4], g_ii[5], g_ii[6], 0, 0 ); ///�Ź���ȭ�ý���
	}

	if( g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
		g_pNk2DFrame->GetControlInven()->ResetItemInfo();/// ���� ����.

	if( g_pNk2DFrame && g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet() ) ///�굵�� �� �ߵ� ������ üũ�Ѵ�.
		g_pNk2DFrame->GetControlHelpPet()->CheckHelpCondition( 2, g_ii[1], TRUE ); // ������ ���� ������ ������ �ִ��� üũ�Ѵ�.
}

void CmdExchInvenFrom(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);				// y

	if( pMgr )
		pMgr->ExchInvenFrom(g_ii[0], g_ii[1]);
}

void CmdExchMoney(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	if( pMgr )
		pMgr->ExchMoney(g_Buf);
}

void CmdDelivStart(char *arg, CUIMgr *pMgr)
{}

void CmdDeliv(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);					// index
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);					// vnum
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);					// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);					// y

	if( !g_pRoh )
		return;
	// ��ġ�� �ľ��Ͽ� ���� �������� �����Ѵ�.
	g_pRoh->DelFromExgInven(g_ii[2], g_ii[3]);
	// ��ȯâ�� �� �������� �ִ´�.
	g_pRoh->AddToExgInven(g_ii[2], g_ii[3], g_ii[0], g_ii[1], 0, 0, 0, 0, 0, 0, TRUE); ///�Ź���ȭ�ý���
}

void CmdDelivEnd(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->CheckCarnation(_DELIV_SUCCEED);
}

void CmdDelivFail(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->CheckCarnation(_DELIV_FAIL);
}

void CmdMs(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );		/// ���� �÷��� - 0:����, 1:����
	g_ii[ 0 ] = atoi( g_Buf );

	arg = AnyOneArg(arg, g_Buf);		// ���� ����

	if (!strcmp(g_Buf, "request"))
	{
		arg = AnyOneArg(arg, g_Buf);	// ��û�� �̸�
		if( pMgr )
			pMgr->CmdMsRequest(g_Buf);
	}
	else if (!strcmp(g_Buf, "start"))
	{
		arg = AnyOneArg(arg, g_Buf);	// 0: ��û�� ���, 1: �������� �������.
		g_ii[ 1 ] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);	// ���� �̸�
		if( pMgr )
			pMgr->CmdMsStart( g_ii[ 1 ], g_Buf, g_ii[ 0 ] );
	}
	else if (!strcmp(g_Buf, "money"))
	{
		arg = AnyOneArg( arg, g_Buf );	// �ݾ�
		if( pMgr )
			pMgr->MsMoney( g_Buf, g_ii[ 0 ] );
	}
	else if (!strcmp(g_Buf, "success"))	// ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// clear flag
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// index
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// vnum
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// x
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// y

		if( pMgr )
			pMgr->MsSuccess( g_ii[1], g_ii[3], g_ii[2], g_ii[4] ,g_ii[5], g_ii[ 0 ] );
	}
	else if (!strcmp(g_Buf, "fail"))	// ����
	{
		if( pMgr && g_pNk2DFrame )
		{
			pMgr->MsFail( g_ii[ 0 ] );
			g_pNk2DFrame->ShowRefineWindow( false );
		}
	}
	else if (!strcmp(g_Buf, "cancel"))	// ���� ��Ҵ� ms cancel�� �´�.
	{
		if( pMgr && g_pNk2DFrame )
		{
			g_pNk2DFrame->ShowProcessWindow(FALSE, 1);
		}
	}
}

// exch_inven_to index vnum x y
void CmdMsInvenTo(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );		/// ���� �÷��� - 0:����, 1:����
	int nSection = atoi( g_Buf );

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			//index
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// vnum
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);			// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);			// y
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);

	if( g_SvrType == ST_ADULT_ONLY ) // [6/7/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// ��ȭ ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// ��ȭ ������ Max
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[7] = atoi(g_Buf);			// �Ϲ� ������ Max
	}

	if( pMgr )
	{
		if( g_SvrType == ST_ADULT_ONLY )
			pMgr->MsInvenTo(g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], nSection, g_ii[4], g_ii[5], g_ii[6], g_ii[7]);
		else
			pMgr->MsInvenTo(g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], nSection, 0, 0, 0, 0 );
	}
}

void CmdMsInvenFrom(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );		/// ���� �÷��� - 0:����, 1:����
	int nSection = atoi( g_Buf );

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// y

	if( pMgr )
		pMgr->MsInvenFrom(g_ii[0], g_ii[1], nSection );
}

// ���� �ɼ� �߰�
// 0 : �߰� ����
// 1 : �߰� ����
// 2 : �ٿ� �׷��̵�.
void CmdMsUpgrade(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf);

	if( pMgr )
		pMgr->CmdMsUpgrade(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4]);
	if( g_pRoh )
		g_pRoh->SetDefense();//1114 �������׷��̵�� ���� ���� ��������Ƿ� �ٽ� ǥ��
}

void CmdIChange(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				// old_idx
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);				// new_idx
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);				// vnum
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);				// plus_point (x)
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf);				// special (y)

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[5] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if( g_SvrType == ST_ADULT_ONLY )// [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[8] = atoi(g_Buf);		// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);		// �Ϲ� ������ Max
	}

	if( pMgr )
	{
		if( g_SvrType == ST_ADULT_ONLY )
			pMgr->InterchangeTo(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9] ); ///�Ź���ȭ�ý���
		else
			pMgr->InterchangeTo(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], g_ii[7], 0, 0 ); ///�Ź���ȭ�ý���
	}
}

void CmdWorked(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				// slot_num
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);				// 0�� ����, 1�� ����.

	if (g_ii[1] == 0)
	{
		pMgr->FailedWork(g_ii[0]);
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// ���� Index (�����)
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// ���� Index (�����Ұ�)
		pMgr->SuccessWork(g_ii[0], g_ii[2], g_ii[3]);
	}
}

void CmdUpgrade(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				// 0�� ����, 1�� ����
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);				// where
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);				// Item Index
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);				// ���� ����.

	if( pMgr )
		pMgr->Upgrade(g_ii[0], g_ii[1], g_ii[2], g_ii[3]);
	if( g_pRoh )
		g_pRoh->SetDefense();//1114 ���׷��̵�� ���� ���� ��������Ƿ� �ٽ� ǥ��
}

void CmdParty(char *arg, CUIMgr *pMgr) ///��Ƽ����.
{
	if( !g_pNk2DFrame )
		return;

	char strTemp[200];
	arg = AnyOneArg(arg, g_Buf);

	if( !strcmp(g_Buf, "request") ) // ��û�� ������.. ��忡 ���� ��Ƽ���� �޴� ���� ������ �޴� ���� ������.
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // ��û���. ����� ���� ���� ��尡 �ٲ��.

		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf); // ��û�� ����� �ε���
		arg = AnyOneArg(arg, g_Buf1); // ��û�� ����� �̸�

		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf); // ��Ƽ���� �ε���
		arg = AnyOneArg(arg, g_Buf2); // ��Ƽ���� �̸�


		// ��Ƽ �źΰ� �Ǿ������� �ڵ� ���.
		if( g_pNk2DFrame->GetControlParty()
				&& g_pNk2DFrame->GetControlParty()->m_RequestRejection.GetToggleState() )
		{
			char strTemp[ 100 ];

			if( g_pNk2DFrame->GetControlParty()->m_bIsMaster ) // ��Ƽ�常 dismiss
				sprintf( strTemp, "party dismiss %d 1\n", g_ii[1] ); // �ڿ� 1�� �ڵ����(��Ƽ�ź�) �϶� ����.
			else
				sprintf( strTemp, "party secession %d 1\n", g_ii[1] ); // �ڿ� 1�� �ڵ����(��Ƽ�ź�) �϶� ����.

			if( g_pTcpIp )
				g_pTcpIp->SendNetMessage( strTemp );

			return; // request ó���� ���� �ʴ´�.
		}

		g_pNk2DFrame->m_PartyReadyIndex = g_ii[1];

		switch( g_ii[0] ) // ���� ��û���� 7��. ��忡���� �޴� ������ ���� �� �޼��� �ڽ��� �ڸ�Ʈ�� �ٲ��.
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:

			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf); // ����ġ �й� ���
			arg = AnyOneArg(arg, g_Buf);
			g_ii[4] = atoi(g_Buf); // ������ �Լ� ���

			if( pMgr->m_AutoPlay )
			{
				if( pMgr->m_AutoPlay->IsRun() )
				{
					if( pMgr->m_AutoPlay->IsAutoParty() )
					{
						char msgbuf[256] = {0,};
						sprintf(msgbuf , "party consist %d %d\n", g_ii[0], g_ii[1]);
						LH_SEND_NET_MSG( msgbuf );
						return;
					}
					else
					{
						if( g_pNk2DFrame->GetControlParty() && g_pNk2DFrame->GetControlParty()->m_PartyState == PARTY_STATE_MEMBER )
						{
							if( g_pNk2DFrame->GetControlParty()->m_bIsMaster )
							{
								char msgbuf[256] = {0,};
								sprintf(msgbuf , "party dismiss %d 0\n", g_ii[1]);
								LH_SEND_NET_MSG( msgbuf );
								return;
							}
						}

						char msgbuf[256] = {0,};
						sprintf(msgbuf , "party secession %d 0\n", g_ii[1]);
						LH_SEND_NET_MSG( msgbuf );
						return;
					}
				}
			} 

			if( g_pNk2DFrame->GetControlParty() )
				g_pNk2DFrame->GetControlParty()->AskParty( g_ii[0], g_Buf1, g_ii[2], g_Buf2, g_ii[3], g_ii[4] );

			break;

		case 5:
		case 6:
			if( pMgr->m_AutoPlay )
			{
				if( pMgr->m_AutoPlay->IsRun() )
				{
					if( pMgr->m_AutoPlay->IsAutoParty() )
					{
						char msgbuf[256] = {0,};
						sprintf(msgbuf , "party consist %d %d\n", g_ii[0], g_ii[1]);
						LH_SEND_NET_MSG( msgbuf );
						return;
					}
					else
					{
						if( g_pNk2DFrame->GetControlParty() && g_pNk2DFrame->GetControlParty()->m_PartyState == PARTY_STATE_MEMBER )
						{
							if( g_pNk2DFrame->GetControlParty()->m_bIsMaster )
							{
								char msgbuf[256] = {0,};
								sprintf(msgbuf , "party dismiss %d 0\n", g_ii[1]);
								LH_SEND_NET_MSG( msgbuf );
								return;
							}
						}

						char msgbuf[256] = {0,};
						sprintf(msgbuf , "party secession %d 0\n", g_ii[1]);
						LH_SEND_NET_MSG( msgbuf );
						return;
					}
				}
			}
 
			if( g_pNk2DFrame->GetControlParty() )
				g_pNk2DFrame->GetControlParty()->AskParty( g_ii[0], g_Buf1, g_ii[2], g_Buf2 );

			break;
		}

	}
	else if( !strcmp(g_Buf, "list") ) // ��Ƽ ��� ����Ʈ ����, ���� ���� ��������, ���� �������� ����Ʈ�� ���� ���´�.
	{
		// �� ��Ŷ�� ���� �������� ������� ����Ʈ�� �� �����.
		g_pNk2DFrame->GetControlParty()->RemoveMemberAll(); // �ϴ� �� �����.(���߿� ������Ʈ �÷��׸� ����������Ѵ�.(�ȱ׷��� ����Ʈ�� �ǽð����� �� �ٲ�����.)
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // ��Ƽ���� ��.
		g_pNk2DFrame->GetControlParty()->SetParty( TRUE );
		g_pRoh->m_bIsParty = TRUE;
	}
	else if( !strcmp(g_Buf, "list_end") ) // ��Ƽ ��� ����Ʈ ����, ���� ���� ��������, ���� �������� ����Ʈ�� ���� ���´�.
	{
		g_pNk2DFrame->GetControlParty()->SetPartyCount();
	}
	else if( !strcmp(g_Buf, "member") ) // ��Ƽ ��� ����Ʈ ����, �Ѹ� �� ��Ŷ���� ���´�.
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // ��Ƽ���� �ε���
		arg = AnyOneArg(arg, g_Buf); // ��Ƽ���� ĳ����
		g_pNk2DFrame->GetControlParty()->AddMember(g_ii[0], g_Buf);
	}
	else if( !strcmp(g_Buf, "dismiss") ) // �������� �ذ� ��������. �ڱ��ڽ��� �ذ� ���������� �ذ���� ����� �̸��� ������ֱ����� �������.
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // �ذ�� ����� �ε���(�ڱ� �ڽ������� üũ�ؾ��Ѵ�.)

		if( g_ii[0] == g_pRoh->m_nCharIndex && g_pRoh->m_bIsParty ) // �ڱ� �ڽ��� ������� ���. (��Ƽ�� ���� ��쿡�� ó��)
		{
			g_pNk2DFrame->GetControlParty()->RemoveMemberAll();
			g_pNk2DFrame->GetControlParty()->SetParty( FALSE );
			g_pRoh->m_bIsParty = FALSE;
			//IDS_PARTY_DISMISS_YOU : ����� ��Ƽ���� �ذ� ���ϼ̽��ϴ�.
			sprintf( strTemp, G_STRING(IDS_PARTY_DISMISS_YOU) );
			g_pNk2DFrame->AddChatStr( strTemp, -1 );
		}
		else
		{
			//IDS_PARTY_DISMISS : %s ���� ��Ƽ���� �ذ� ���ϼ̽��ϴ�.
			sprintf( strTemp, G_STRING(IDS_PARTY_DISMISS), g_pNk2DFrame->GetControlParty()->GetMemberName(g_ii[0]) );
			g_pNk2DFrame->AddChatStr( strTemp, -1 );
		}
	}
	else if( !strcmp(g_Buf, "disband") ) // �ػ�. ������ �ػ��� ������ ��.
	{
		// �츮 ��Ƽ ��ü���~~~
		if( g_pRoh->m_bIsParty ) // ��Ƽ�� ���� ��쿡�� ó��
		{
			g_pNk2DFrame->GetControlParty()->RemoveMemberAll();
			g_pNk2DFrame->GetControlParty()->SetParty( FALSE );
			g_pRoh->m_bIsParty = FALSE;

			char strTemp[200];
			sprintf( strTemp, G_STRING(IDS_PARTY_DISBAND) );
			// IDS_PARTY_DISBAND : ��Ƽ�� ��ü�Ǿ����ϴ�.
			g_pNk2DFrame->AddChatStr( strTemp, -1 );
		}
	}
	else if( !strcmp(g_Buf, "change") ) // ����ġ, ������ �Լ� ��� ����(�Ǵ� ���� �Ἲ��) �� ���� ��Ŷ.(����� ������ ���� ���� �Ἲ�ÿ��� �´�.)
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // �� �ٲٴ���...

		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf); // �ٲ� ��.

		switch( g_ii[0] )
		{
		case 1: // ����ġ �й� ���.
			g_pNk2DFrame->GetControlParty()->m_ExpGetRule.SetSelect( g_ii[1] );
			break;

		case 2: // ������ ��� ���.
			g_pNk2DFrame->GetControlParty()->m_ItemGetRule.SetSelect( g_ii[1] );
			break;
		}
	}
	else if( !strcmp(g_Buf, "secession") ) // ������ ������ ���.
	{
		// �ٸ� ����� ������ ���� �׳� �����ص� �ȴ�.(������ ��� ����Ʈ�� ���� �޾� ������.)
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // �ε���

		if( g_ii[0] == g_pRoh->m_nCharIndex && g_pRoh->m_bIsParty ) // �ڱ� �ڽ��̸�...
		{
			// �ʱ�ȭ�� ���ش�.
			g_pNk2DFrame->GetControlParty()->RemoveMemberAll();
			g_pNk2DFrame->GetControlParty()->SetParty( FALSE );
			g_pRoh->m_bIsParty = FALSE;

			char strTemp[200];
			sprintf( strTemp, G_STRING(IDS_PARTY_DISBAND) );
			// IDS_PARTY_DISBAND : ��Ƽ�� ��ü�Ǿ����ϴ�.
			g_pNk2DFrame->AddChatStr( strTemp, -1 );
		}
	}
}

void CmdPv(char *arg, CUIMgr *pMgr)
{
	if( g_pRoh )
		g_pRoh->GetPvInfo(arg);
}

// skill <1/0> <char/npc> index skill_index
void CmdSkill(char *arg, CUIMgr *pMgr)
{
	BOOL bSucess = FALSE;
	BOOL bChar = FALSE;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				// 0�� ����, 1�� ����
	arg = AnyOneArg(arg, g_Buf);		// npc or char
	arg = AnyOneArg(arg, g_Buf2);
	g_ii[1] = atoi(g_Buf2);				// npc or char index
	arg = AnyOneArg(arg, g_Buf2);
	g_ii[2] = atoi(g_Buf2);				// skill_index
	if( g_ii[2] == SKILLF_C_STONEBRUST)
	{
		//mungmae-2005/05/10 �������Ʈ ����Ʈ �߰�
		CNkMob *pMob = pMgr->FindMobById(g_ii[1]);
		pMgr->InsertMagic(NULL, pMob, NULL, NULL, EFFECT_SKILL_STONEBRUST);
	}

	if (strncmp(g_Buf, "c", 1) == 0)
		bChar = TRUE;
	else
		bChar = FALSE;

	pMgr->SkillOnOff(g_ii[0], bChar, g_ii[1], g_ii[2]);
}

//==============================
// nate 2004 - 4
// CastleWar
// ���� �׸��� ǥ�� ���� ����
void CmdGuildName(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);				// 0�� ����, 1�� ����
	arg = AnyOneArg(arg, g_Buf);		// npc or char

	CNkCharacter* pChar = NULL;
	LHCharacterMap_it prChar;

	if( !g_pRoh )
		return;

	if( g_pRoh->m_nCharIndex == g_ii[ 0 ] )
	{
		g_pRoh->SetGuildName( g_Buf );

		if( g_pNk2DFrame->GetControlGuild() )
			g_pNk2DFrame->GetControlGuild()->ChangeGuildInfo(g_Buf);

		if( strlen( g_Buf ) <= 0 )
			g_pRoh->m_GuildIndex = 0;

		for( prChar = pMgr->m_character_map.begin() ; prChar != pMgr->m_character_map.end() ; prChar ++ )
		{
			pChar = (*prChar).second;

			if( g_pRoh->m_pstrGuildName && pChar->m_pstrGuildName )
			{
				if( strcmp( g_pRoh->m_pstrGuildName, pChar->m_pstrGuildName ) )
					pChar->SetMyGuild( FALSE );
				else
					pChar->SetMyGuild( TRUE );
			}
			else
				pChar->SetMyGuild( FALSE );
		}
	}
	else
	{
		if( pChar = pMgr->FindChaById( g_ii[ 0 ], TRUE ) )
		{
			pChar->SetGuildName( g_Buf );

			/*      // ������ �̺�Ʈ �� ����콺 �ʿ��� ��� �̸����� �ε����� �ٲ��ִ� �ڵ�. �ؿܸ� ������߱⿡ ����. (�������� �౸������ ����콺 ������ ������ �ֱ�� ����)
						if( g_bMatrixSvr ) // ����콺�� ��� �ε����� ���� ó�����ֱ�� ����.
						{
							if(!strcmp(g_Buf, "ȣũ"))
								pChar->m_GuildIndex = 1;
							else if(!strcmp(g_Buf, "����"))
								pChar->m_GuildIndex = 2;
							else if(!strcmp(g_Buf, "����"))
								pChar->m_GuildIndex = 3;
							else
								pChar->m_GuildIndex = 0;
						}
			*/
			if( strlen( g_Buf ) <= 0 )
				pChar->m_GuildIndex = 0;

			if( g_pRoh->m_pstrGuildName && g_Buf )
			{
				if( strcmp( g_pRoh->m_pstrGuildName, g_Buf ) )
					pChar->SetMyGuild( FALSE );
				else
					pChar->SetMyGuild( TRUE );
			}
			else
				pChar->SetMyGuild( FALSE );

		}
	}	
}

void CmdGuildGrade(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);		// ĳ���� �ε���
	g_ii[0] = atoi(g_Buf);

	if (pCha = pMgr->FindChaById(g_ii[0], TRUE))
	{
		arg = AnyOneArg(arg, g_Buf);	// ��� ���� �ε���
		g_ii[1] = atoi(g_Buf);

		if( arg[1] == ' ' )
		{
			sprintf(g_Buf3, "");
		}
		else
		{
			arg = AnyOneArg(arg, g_Buf3);	// ��� ��� �̸�
		}

		arg = AnyOneArg(arg, g_Buf);	// ��� ��� �ε���
		g_ii[2] = atoi(g_Buf);			// �渶 : 10, �α渶 : 9, ���� : 7, ���� : 1

		pCha->m_GuildIndex = g_ii[1];
		
		pMgr->isguildmark(g_ii[1]);
		pCha->SetGuildGrade(g_Buf3);

		if( g_MatrixSvr  != 0 )
		{
			if (g_ii[1] < 0)
			{
				g_ii[1] *= -1;
				pCha->ShowMatrixMark(TRUE);
			}
			else
				pCha->ShowMatrixMark(FALSE);

			pCha->SetGuildIndex( g_ii[1]);
		}
		else
		{
			pCha->ShowMatrixMark(FALSE);
			pCha->SetGuildIndex( g_ii[1]);
		}

//=========================================
		// nate 2004 - 5
		// m_GuildLevel�� m_GuildGradeIndex�� ������ ���� ������ ���δ�.
		pCha->m_GuildLevel = pCha->m_GuildGradeIndex = g_ii[2];
//=========================================
	}
}

//--------------------------------------------------------------------------
// CmdMultiShot
//--------------------------------------------------------------------------
// �޸� ���� �� ���ݼ�
// 2005.01.20 / Lyul
// ������ ��� -1�� �´٤�.
void CmdMultiShot(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	// Other Character : �������� ó�� ����
	if (!strncmp(g_Buf, "c", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);

		if (pCha = pMgr->FindChaById(g_ii[0], FALSE))
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[1] = atoi(g_Buf);

			// ����Ƚ��
			if (g_ii[1] >= 2)
			{
				pCha->SetNextMultiShot(g_ii[1] - 1);
			}
			else if (g_ii[1] == -1)
			{
				pCha->mb_Snifing = true;
			}
			else if (g_ii[1] < 0)
			{
				pCha->SetSnifing(TRUE);
			}
		}
	}
	// Player : �������� ó�� ����
	else if (!strcmp(g_Buf, "me"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);

		// ���� Ƚ��
		if (g_pRoh && g_ii[1] >= 2)
			g_pRoh->SetNextMultiShot(g_ii[1] - 1);
	}
}

const int FE_TYPE_DROP = 2;
const int FE_TYPE_ATT = 3;
const int FE_TYPE_DEF = 4;
const int FE_TYPE_HP = 5;
const int FE_TYPE_EXP = 6;
const int FE_TYPE_LUCKY = 9;
const int FE_TYPE_LESS_EXP = 10;

void CmdEvent(char *arg, CUIMgr *pMgr)
{
	strcpy(g_Buf2, arg);

	arg = AnyOneArg(arg, g_Buf);

	// Event ��Ŷ�� ���� ���� ȿ�� ǥ�� ��� �߰�. ///�̺�Ʈ����ǥ��
	if(!strcmp(g_Buf, "drop"))
	{
		arg = AnyOneArg(arg, g_Buf);

		g_pNk2DFrame->SetEventType(FE_TYPE_DROP, atoi(g_Buf));

		return;
	}
	else if(!strcmp(g_Buf, "att"))
	{
		arg = AnyOneArg(arg, g_Buf);

		g_pNk2DFrame->SetEventType(FE_TYPE_ATT, atoi(g_Buf));
		return;
	}
	else if(!strcmp(g_Buf, "def"))
	{
		arg = AnyOneArg(arg, g_Buf);

		g_pNk2DFrame->SetEventType(FE_TYPE_DEF, atoi(g_Buf));
		return;
	}
	else if(!strcmp(g_Buf, "hp"))
	{
		arg = AnyOneArg(arg, g_Buf);

		g_pNk2DFrame->SetEventType(FE_TYPE_HP, atoi(g_Buf));
		return;
	}
	else if(!strcmp(g_Buf, "exp"))
	{
		arg = AnyOneArg(arg, g_Buf);

		int value = atoi(g_Buf);
		
		if( CommonConfig::Instance()->GetEventLessExp() == false )
		{
			g_pNk2DFrame->SetEventType(FE_TYPE_EXP, value);
		}
		else
		{
			if (value > 0 && value < 10)
			{
				g_pNk2DFrame->SetEventType(FE_TYPE_EXP, value);
				g_pNk2DFrame->SetEventType(FE_TYPE_LESS_EXP, 0);
			}
			else if (value > 100 && value < 110)
			{
				g_pNk2DFrame->SetEventType(FE_TYPE_LESS_EXP, value - 100);
				g_pNk2DFrame->SetEventType(FE_TYPE_EXP, 0);
			}
			else if (value == 0)
			{
				g_pNk2DFrame->SetEventType(FE_TYPE_EXP, 0);
				g_pNk2DFrame->SetEventType(FE_TYPE_LESS_EXP, 0);
			}
		}
		return;
	}

	else if(!strcmp(g_Buf, "luckey")) //���� event lucky 1  ,  event lucky 0
	{
		arg = AnyOneArg(arg, g_Buf);

		g_pNk2DFrame->SetEventType(FE_TYPE_LUCKY, atoi(g_Buf));
		return;
	}

	else if(!strcmp(g_Buf, "event"))
	{
		g_pTcpIp->SendNetMessage( g_Buf2 );
		return;
	}

	else
	{
		if( pMgr )
			pMgr->CmdEvent(g_Buf2);
	}
}

void CmdVoiceChat(char *arg, CUIMgr *pMgr)
{
}

void CmdYouare(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if (g_ii[0] > 2)
	{
		g_bAdmin2 = TRUE;
		pCMyApp->m_bFastMove = TRUE;
	}
}
//-----------------------------------------
// ������ ���� ��ɾ�
//-----------------------------------------
void CmdOpenCastle(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if( pMgr )
		pMgr->OpenCastle(g_ii[0]);
}

void CmdCloseCastle(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->CloseCastle();
}

// nate 2004 - 11
// ������ ȭ��Ʈȥ�� �ܼ����� ������
// ���Ϸ��� ��ȣž�� ������
void CmdOpenDoor(char *arg, CUIMgr *pMgr)
{
	int i;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );

	if( g_ii[ 0 ] == 7 )  		// ȭ��Ʈȥ
	{
		for ( i = 0 ; i < 8 ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ i ] = atoi( g_Buf );
		}
		if( pMgr )
			pMgr->OpenDoor( 7, g_ii );
	}
	else if( g_ii[ 0 ] == 3 )  	// ���Ϸ�
	{
		for( i = 0 ; i < 4 ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ i ] = atoi( g_Buf );
		}
		if( pMgr )
			pMgr->OpenDoor( 3, g_ii );
	}
	// wan:2004-12 : whitehorn Dungeon
	else if( g_ii[ 0 ] == 8 )  	// ȭ��Ʈȥ ����
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf );
		if( pMgr )
			pMgr->OpenDoor( 8, g_ii );
	}
	else if( g_ii[ 0 ] == 0 ) // ��ī���� �߰�(by ����)
	{
		for ( i = 0 ; i < 4 ; i ++ ) // ���� ��ī������ ��ȣž�� 4��
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ i ] = atoi( g_Buf );
		}
		if( pMgr )
			pMgr->OpenDoor( 0, g_ii );
	}
}

//=======================================
// nate 2004 - 4 : CastleWar
void CmdOnBattle(char *arg, CUIMgr *pMgr)
{
	if( pMgr == NULL )
		return;

	// nate 2005-03-11 : Matrix - ������ ���°�
	if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX )
	{
		// wan_mat : ��Ŷ�� �� �տ� ���� �÷��� �ϳ� �߰�
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf); // ���� ���̳� �ƴϳ�.
		if(g_ii[0])
			pMgr->m_bOnBattle = TRUE;
		else
		{
			pMgr->m_bOnBattle = FALSE;
			g_bFireTower = 0;
			g_bFireTower2 = 0;
			g_bFireTower3 = 0;
		}

		for( int i = 0 ; i < 12 ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			pMgr->m_nStoneState[ i ] = atoi( g_Buf );
			pMgr->OpenMatrixGate();
		}
		//�׷��� ũ����Ż ���õ� ó��(mungmae-3/22)
		// �����ٸ� ȿ�� ��Ÿ����
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));

		ef_sort.nType = FX_FIRETOWER;
		ef_sort.dwColor = 1; // ���� �÷��׷� ���.

		if( g_bFireTower == 0 && pMgr->m_nStoneState[6] == 2)
		{
			ef_sort.num = 1; // ��� �ұ�������� üũ�ϴµ� ���.
			ef_sort.vTargetPos = D3DVECTOR(6315, 350, 3015);

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			g_bFireTower = 1;
		}
		else if(  g_bFireTower != 0 && pMgr->m_nStoneState[6] != 2 )
			g_bFireTower = 0;

		if( g_bFireTower2 == 0 && pMgr->m_nStoneState[7] == 2 )
		{
			ef_sort.num = 2;
			ef_sort.vTargetPos = D3DVECTOR(3608, 350, 8058);

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			g_bFireTower2 = 1;
		}
		else if(  g_bFireTower2 != 0 && pMgr->m_nStoneState[7] != 2 )
			g_bFireTower2 = 0;

		if( g_bFireTower3 == 0 && pMgr->m_nStoneState[8] == 2)
		{
			ef_sort.num = 3;
			ef_sort.vTargetPos = D3DVECTOR(8980, 350, 8105);

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			g_bFireTower3 = 1;
		}
		else if(  g_bFireTower3 != 0 && pMgr->m_nStoneState[8] != 2 )
			g_bFireTower3 = 0;

		return;
	}

	if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009 )
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);

		if(g_ii[0]) // ���� ���̸�
			pMgr->m_bOnBattle = TRUE;
		else
		{
			pMgr->m_bOnBattle	= FALSE;
			g_bFireTower		= 0;
			g_bFireTower2		= 0;
			g_bFireTower3		= 0;
		}
		/*
			//////////////////////////////////////////////////////////////////////
			// ���� ��
			// 0 :: ����
			// 1 :: ����

			0	:: ���帶�� �������Ʈ
			1	:: �̸̹� ���帶�� �������Ʈ
			2	:: �̸̹� �ȱ׸��� �������Ʈ
			3	:: �ȱ׸��� �������Ʈ


			//////////////////////////////////////////////////////////////////////
			// ���� ��
			// 1 	:: ����ü�� > 1/2
			// 2 	:: ����ü�� < 1/2
			// 0 	:: �׶��� ũ��Ż�� ������

			4	:: ���帶�� �׶��� ũ����Ż
			5	:: �ȱ׸��� �׶��� ũ����Ż


			//////////////////////////////////////////////////////////////////////
			// ������
			// 0 	:: ������ ��尡 ���� ��
			// 0<n 	:: ������ ���� �ε��� ��ȣ (�ڽ��� ��� �ε����� �˻��غ���.)

			6	:: �ȵ���� �Ϻ� G���� ������ ���� �ε��� ��ȣ
			7	:: ���帶�� ���� G���� ������ ���� �ε��� ��ȣ
			8 	:: �̸̹� G���� ������ ���� �ε��� ��ȣ
			9	:: �ȱ׸��� �Ϻ� G���� ������ ���� �ε��� ��ȣ
			10	:: �ȵ���� ���� G���� ������ ���� �ε��� ��ȣ
			11	:: ������
		*/
		// ���⼭�� 7���� ����Ѵ�. �������Ʈ 4 + GPũ����Ż 3
		for( int i = 0 ; i < 11 ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			pMgr->m_nStoneState[ i ] = atoi( g_Buf );
			pMgr->OpenMatrixGate();
		}

		// ũ����Ż �����ٸ� ȿ�� ��Ÿ����
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));

		ef_sort.nType = FX_FIRETOWER;
		ef_sort.dwColor = 1; // ���� �÷��׷� ���.

		// ���帶�� ũ����Ż
		if( g_bFireTower == 0 && pMgr->m_nStoneState[4] == 2)
		{
			ef_sort.num = 2; // ��� �ұ�������� üũ�ϴµ� ���.
			ef_sort.vTargetPos = D3DVECTOR(1942, 274, 11076);

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			g_bFireTower = 1;
		}
		else if(  g_bFireTower != 0 && pMgr->m_nStoneState[4] != 2 )
			g_bFireTower = 0;

		// ��帶�� ũ����Ż
		if( g_bFireTower2 == 0 && pMgr->m_nStoneState[5] == 2 )
		{
			ef_sort.num = 3;
			ef_sort.vTargetPos = D3DVECTOR(11027, 250, 1659);

			pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			g_bFireTower2 = 1;
		}
		else if(  g_bFireTower2 != 0 && pMgr->m_nStoneState[5] != 2 )
			g_bFireTower2 = 0;

		return;
	}
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf); // ���� ���̳� �ƴϳ�.

	if( g_ii[ 0 ] == 1 )
		pMgr->m_byEndDecardiCastleWar = 1;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf); // ���� 1 ��
	arg = AnyOneArg(arg, g_Buf); // ���� 1 ����
	strcpy(pMgr->m_MasterGuild1, g_Buf);
	pMgr->m_MasterZone1 = g_ii[1];

	arg = AnyOneArg(arg, g_Buf2);
	g_ii[2] = atoi(g_Buf2); // ���� 2 ��
	arg = AnyOneArg(arg, g_Buf2); // ���� 2 ����
	strcpy(pMgr->m_MasterGuild2, g_Buf2);
	pMgr->m_MasterZone2 = g_ii[2];

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 3 ] = atoi( g_Buf ); // ���� 3 ��

	if( g_ii[ 3 ]  < 700 )
	{
		arg = AnyOneArg( arg, g_Buf3 ); // ���� 3 ����
		strcpy( pMgr->m_MasterGuild3, g_Buf3 );
		pMgr->m_MasterZone3 = g_ii[ 3 ];

		// �ܼ��� ����
		arg = AnyOneArg(arg, g_Buf);
	}

	while (*g_Buf)
	{
		g_ii[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf2);
		if (g_ii[1] >= 100)   // �ܼ����� ���� ����ġ ������ 100���� ũ��.
		{
			g_ii[2] = g_ii[1] / 100; // �� ����
			g_ii[3] = g_ii[1] % 100; // ����ġ (��,��,��,��)
			if (g_ii[3] < 4 && *g_Buf2)
			{
				strcpy(pMgr->m_SubGuild[g_ii[3]], g_Buf2);
			}
		}
		arg = AnyOneArg(arg, g_Buf);
	}

	if( pMgr )
		pMgr->OnBattle(g_ii[0]);
}
//=======================================

// ������ ���� �ð�, �ʷ� ȯ���ؼ� ����.
void CmdBattleCount(char *arg, CUIMgr *pMgr)
{
	//g_pNk2DFrame->AddChatStr(arg, 0);		// �ӽ�.

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if( pMgr )
		pMgr->BattleCount(g_ii[0]);
}

// ���� ���� ��� Ÿ�� ī��Ʈ.
// ��������, ������, �����ð�, �ϵ���, �ϵ�����ð�.
void CmdTimeCount(char *arg, CUIMgr *pMgr)
{
	// nate 2005-03-11
	// Matrix
	// ��Ʈ���� �������� ������°���
	if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX )
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf );	// ȣũ�ο� ���� ����Ʈ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf );	// ���� ��������Ʈ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 2 ] = atoi( g_Buf );	// ���� ��������Ʈ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 3 ] = atoi( g_Buf );	// ��Ʋ ���� �ð�(��)

		if( pMgr )
			pMgr->MatTimeCount( g_ii[ 0 ], g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ] );

		return;
	}
	if( pCMyApp->m_nCurWorldIdx == WORLD_MATRIX_2009  ) // ���� ���
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf );	// ���� ���� ����Ʈ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf );	// �ȱ� ��������Ʈ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 2 ] = atoi( g_Buf );	// ��Ʋ ���� �ð�(��)

		if( pMgr )
			pMgr->MatTimeCount( g_ii[ 0 ], g_ii[ 1 ], g_ii[ 2 ] );

		return;
	}
	arg = AnyOneArg(arg, g_Buf);				// ��� �̸�
	g_ii[0] = atoi(g_Buf);
	if( g_ii[0] == -1 )
	{
		arg = AnyOneArg(arg, g_Buf2);			// ����߸� ��� ����
		g_ii[1] = atoi(g_Buf2);
		if( pMgr )
			pMgr->TimeCount_Flag(g_ii[1], "NOFLAG", "NOFLAG");
		return;
	}

//===========================================
	// nate 2004 - 4
	// CastleWar
	if( g_ii[ 0 ] == -2 )
	{
		if( pMgr )
			pMgr->m_byEndDecardiCastleWar = 0;
		return;
	}
//===========================================

	arg = AnyOneArg(arg, g_Buf2);				// ������ �̸�.
	arg = AnyOneArg(arg, g_Buf3);
	g_ii[0] = atoi(g_Buf3);						// ���� �ð�
	arg = AnyOneArg(arg, g_Buf3);				// 1�� ���
	arg = AnyOneArg(arg, g_Buf4);
	g_ii[1] = atoi(g_Buf4);						// 1�� �ð�
	arg = AnyOneArg(arg, g_Buf4);
	g_ii[2] = atoi(g_Buf4);						// ������ x
	arg = AnyOneArg(arg, g_Buf4);
	g_ii[3] = atoi(g_Buf4);						// ������ z
	arg = AnyOneArg(arg, g_Buf4);
	g_ii[4] = atoi(g_Buf4);						// �ڱ� ��� ����

	if( pMgr )
		pMgr->TimeCount(g_Buf, g_Buf2, g_ii[0], g_Buf3, g_ii[1], (float) g_ii[2], (float) g_ii[3], g_ii[4]);

	if (pCMyApp->m_nCurWorldIdx == WORLD_WHITEHORN)
	{
		for (int i = 0; i < WARINFO2_NUM; i++)
		{
			arg = AnyOneArg(arg, g_Buf);
			arg = AnyOneArg(arg, g_Buf2);
			if( pMgr )
				pMgr->TimeCount_Flag(i, g_Buf2, g_Buf);
		}
	}
}

void CmdGuildLevel(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	if( g_pRoh )
		g_pRoh->m_GuildLevel = g_pRoh->m_GuildGradeIndex =g_ii[0];
}


//----------------------------------------
// â�� ���� ��ɾ�
//----------------------------------------
void CmdStashItem(char *arg, CUIMgr *pMgr)
{
	enum
	{
		STASH_ITEM_LOOP_COUNT = 0,

		STASH_ITEM_SLOT,
		STASH_ITEM_VNUM,
		STASH_ITEM_PLUS,
		STASH_ITEM_FLAG,
		STASH_ITEM_FLAG2,
		STASH_ITEM_UPENDUR,
		STASH_ITEM_MAXUPENDUR,
		STASH_ITEM_COUNT,
		STASH_ITEM_ENDUR,
		STASH_ITEM_MAXENDUR,		

		STASH_ITEM_ELEMENT_COUNT,
	};

	std::string str(arg);
	tokenizer token(str, sep);
	std::vector<std::string> vecItem;
	vecItem.assign(token.begin(), token.end());

	int loopCount = std::stoi(vecItem[STASH_ITEM_LOOP_COUNT]);
	
	int slot = 0;
	int vnum = 0;
	int plus = 0;
	int flag = 0;
	int flag2 = 0;
	int upEndur = 0;
	int maxUpEndur = 0;
	int endur = 0;
	int maxEndur = 0;
	int count = 0;	

	int temp = 0;
	for( int i = 0; i < loopCount; ++i )
	{
		temp		= (STASH_ITEM_ELEMENT_COUNT - 1) * i;

		slot		= std::stoi(vecItem[STASH_ITEM_SLOT + temp]);
		vnum		= std::stoi(vecItem[STASH_ITEM_VNUM + temp]);
		plus		= std::stoi(vecItem[STASH_ITEM_PLUS + temp]);
		flag		= std::stoi(vecItem[STASH_ITEM_FLAG + temp]);
		flag2		= std::stoi(vecItem[STASH_ITEM_FLAG2 + temp]);
		upEndur		= std::stoi(vecItem[STASH_ITEM_UPENDUR + temp]);
		maxUpEndur	= std::stoi(vecItem[STASH_ITEM_MAXUPENDUR + temp]);
		count		= std::stoi(vecItem[STASH_ITEM_COUNT + temp]);
		endur		= std::stoi(vecItem[STASH_ITEM_ENDUR + temp]);
		maxEndur	= std::stoi(vecItem[STASH_ITEM_MAXENDUR + temp]);		

		pMgr->Stash(slot, vnum, plus, flag, flag2, upEndur, maxUpEndur, endur, maxEndur, count, 0);
	}	
}

void CmdStashMoney(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int money = atoi(g_Buf);

	pMgr->Stash(12, 0, money, 0, 0, 0, 0, 0, 0, 0, 0);
}

void CmdStashTo(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);	// ���Թ�ȣ
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// item_vnum
	g_ii[1] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// item_plus
	g_ii[2] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// item_flag
	g_ii[3] = atoi(g_Buf);

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[8] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[10] = atoi(g_Buf);			// �̹� ������ Max
	}

	arg = AnyOneArg(arg, g_Buf);	// count
	g_ii[4] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// swap flag
	g_ii[5] = atoi(g_Buf);

	if( pMgr )
	{
		if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		{
			pMgr->StashTo(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[6],
						  g_ii[7], g_ii[8], g_ii[9], g_ii[10], g_ii[4], g_ii[5]);	///�Ź���ȭ�ý���
		}
		else
		{
			pMgr->StashTo(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[6],
						  g_ii[7], g_ii[8], 0, 0, g_ii[4], g_ii[5]);	///�Ź���ȭ�ý���
		}
	}
}

void CmdStashFrom(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);	// ���Թ�ȣ
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// item_index
	g_ii[1] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// item_vnum
	g_ii[2] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// item_plus
	g_ii[3] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// flag
	g_ii[4] = atoi(g_Buf);

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[8] = atoi(g_Buf); // �ƽ� ��ȭ ������..

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);		// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[10] = atoi(g_Buf);		// �Ϲ� ������ Max
	}

	arg = AnyOneArg(arg, g_Buf);	// count
	g_ii[5] = atoi(g_Buf);

	if( pMgr )
	{
		if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		{
			pMgr->StashFrom(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[6],
							g_ii[7], g_ii[8], g_ii[9], g_ii[10], g_ii[5]); ///�Ź���ȭ�ý���
		}
		else
		{
			pMgr->StashFrom(g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[6],
							g_ii[7], g_ii[8], 0, 0, g_ii[5]); ///�Ź���ȭ�ý���
		}
	}
}

void CmdStashEnd(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->StashEnd();

	if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
		pMgr->m_AutoPlay->OnRecvStash();
}

void CmdChipExchange(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);		//0�� Ĩ ��ȯ, 1�� �׺� (type)
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);		// ����, ���� �޽���.

	if (g_ii[0] == 0)
	{
		if (!strcmp(g_Buf, "ok"))
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[1] = atoi(g_Buf);		// �ٲ� ������ ��ȣ.
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);		// server index

			pMgr->ChipExchange(g_ii[0], TRUE, g_ii[1], g_ii[2], -1);
		}
		else
			pMgr->ChipExchange(g_ii[0], FALSE, -1, -1, -1);
	}
	else if (g_ii[0] == 1)
	{
		if (!strcmp(g_Buf, "ok"))
		{
			arg = AnyOneArg(arg, g_Buf);	// win or lose
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[1] = atoi(g_Buf2);			// vnum or -1
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[2] = atoi(g_Buf2);			// ��÷ ��ȣ
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[4] = atoi(g_Buf2);

			if( g_ii[4] == 1 )
			{
				arg = AnyOneArg(arg, g_Buf2);
				g_ii[3] = atoi(g_Buf2);
			}

			if (!strcmp(g_Buf, "win"))
			{
				if( g_ii[4] == 1 )
					pMgr->ChipExchange(g_ii[0], TRUE, g_ii[1], g_ii[3], g_ii[2]);
				else
					pMgr->ChipExchangeMulti(g_ii[0], TRUE, g_ii[1], g_ii[4], g_ii[2], arg);
			}
			else
			{
				if( g_ii[4] == 1 || g_ii[1] == -1 )
					pMgr->ChipExchange(g_ii[0], FALSE, g_ii[1], g_ii[3], g_ii[2]);
				else
					pMgr->ChipExchangeMulti(g_ii[0], FALSE, g_ii[1], g_ii[4], g_ii[2],arg);
			}
		}
		else if (!strcmp(g_Buf, "fail"))
		{}
		else
			return;
	}

	//connie

	else if (g_ii[0] == 2)
	{
		if (!strcmp(g_Buf, "ok"))
		{
			arg = AnyOneArg(arg, g_Buf);	// win or lose
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[1] = atoi(g_Buf2);			// vnum or -1
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[2] = atoi(g_Buf2);			// ��÷ ��ȣ
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[4] = atoi(g_Buf2);

			if( g_ii[4] == 1 )
			{
				arg = AnyOneArg(arg, g_Buf2);
				g_ii[3] = atoi(g_Buf2);
			}

			if (!strcmp(g_Buf, "win"))
			{
				if( g_ii[4] == 1 )
					pMgr->ChipExchange(g_ii[0], TRUE, g_ii[1], g_ii[3], g_ii[2]);
				else
					pMgr->ChipExchangeMulti(g_ii[0], TRUE, g_ii[1], g_ii[4], g_ii[2], arg);
			}
			else
			{
				if( g_ii[4] == 1 || g_ii[1] == -1 )
					pMgr->ChipExchange(g_ii[0], FALSE, g_ii[1], g_ii[3], g_ii[2]);
				else
					pMgr->ChipExchangeMulti(g_ii[0], FALSE, g_ii[1], g_ii[4], g_ii[2],arg);
			}
		}
		else if (!strcmp(g_Buf, "fail"))
		{}
		else
			return;
	}

	else
		return;
}

void CmdYut(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);		//0�� Ĩ ��ȯ, 1�� �׺� (type)
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);		// ����, ���� �޽���.

	if (g_ii[0] == 0)
	{
		if (!strcmp(g_Buf, "ok"))
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[1] = atoi(g_Buf);		// �ٲ� ������ ��ȣ.
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);		// server index

			pMgr->ChipExchange(g_ii[0], TRUE, g_ii[1], g_ii[2], -1);
		}
		else
			pMgr->ChipExchange(g_ii[0], FALSE, -1, -1, -1);
	}
	else if (g_ii[0] == 1)
	{
		if (!strcmp(g_Buf, "ok"))
		{
			arg = AnyOneArg(arg, g_Buf);	// win or lose
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[1] = atoi(g_Buf2);			// vnum or -1
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[2] = atoi(g_Buf2);			// ��÷ ��ȣ
			arg = AnyOneArg(arg, g_Buf2);
			g_ii[3] = atoi(g_Buf2);			// server index

			if (!strcmp(g_Buf, "win"))
				pMgr->ChipExchange(g_ii[0], TRUE, g_ii[1], g_ii[3], g_ii[2]);
			else
				pMgr->ChipExchange(g_ii[0], FALSE, g_ii[1], g_ii[3], g_ii[2]);
		}
		else if (!strcmp(g_Buf, "fail"))
		{}
		else
			return;
	}
	else
		return;
}
void CmdEventAncient(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);		//0�� ����, 1�� ����
	g_ii[0] = atoi(g_Buf);

	if(g_ii[0]==0)  //����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf); //� �����ΰ�.
		pMgr->EventAncientExchange(g_ii[0],g_ii[1],-1,-1,-1);

	}
	else   //����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);
		if(g_ii[1]==0)  //������
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);
			pMgr->EventAncientExchange(g_ii[0],g_ii[1],g_ii[2],g_ii[3],-1);
		}
		else if(g_ii[1]==1)  //+������
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[4] = atoi(g_Buf);
			pMgr->EventAncientExchange(g_ii[0],g_ii[1],g_ii[2],g_ii[3],g_ii[4]);
		}
		else if(g_ii[1]==2)  //����
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);
			pMgr->EventAncientExchange(g_ii[0],g_ii[1],g_ii[2],g_ii[3],-1);
		}
		else if(g_ii[1]==4)  //������ ������ ������ ��Ŷ. (by ����) ///���߱�ȯ
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf); // ����.
			// ���Ŀ� ��Ŷ ä�� �Ѱ��ش�.
			pMgr->EventMultiExchange( g_ii[2], arg );
		}
	}
}

void CmdEventTree(char *arg, CUIMgr *pMgr)//0401 �ĸ��� �̺�Ʈ
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);		//0�� ����, 1�� ����
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	if(g_ii[0]==0)	//����
		pMgr->EventTreeExchange(g_ii[0],g_ii[1],-1,-1);
	else if(g_ii[0]==1)	//����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);
		pMgr->EventTreeExchange(g_ii[0],-1,g_ii[1],g_ii[2]);
	}
}

// nate
// �븸 ���� ����
// ������ �߰�
void CmdLevelup(char *arg, CUIMgr *pMgr)
// ĳ���� �������ϸ� ���۵Ǵ� �޼���
{
	CNkCharacter *pCha;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// ĳ���� �ε���

	if( g_dwClientCountry == CTRY_TWN )
	{
		arg = AnyOneArg( arg, g_Buf );	// �븸 ���� ����
		g_ii[ 1 ] = atoi( g_Buf );		// 270������ ��쿡�� ������ ����
	}									// �� �ܿ��� 1�� ����

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));
	ef_sort.nType = FX_LEVELUP;

	pCha = pMgr->FindChaById(g_ii[0], FALSE);

	// �븸 ���� ����
	// ���� ����
	// ���� 270�̻��� ��� 270���� ������ ��
	// 270���� �̸��ϴ� ��� 1
	if( g_dwClientCountry == CTRY_TWN )
	{
		if( g_ii[ 1 ] == 270 && pCha )
			pCha->SetLevel( g_ii[ 1 ] );
	}

	// ĳ���͸� ��ȸ�ϰ� ĳ���� ���� ���� ���� ������� �з�
	if( !pCMyApp->m_pFxSet || !pCMyApp->GetLandPtr() )
		return;

	if (pCha)
	{
		ef_sort.pNkChaTo = pCha;

		ef_sort.vPos = D3DVECTOR( pCha->m_wx,
								  pCMyApp->GetLandPtr()->GetHFHeight(pCha->m_wx, pCha->m_wz),
								  pCha->m_wz);

		pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );

		ef_sort.nCurFrame = -5;
		pCha->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );

		if ( g_pDSound )
			g_pDSound->Play(g_EffectSound[EFF_SND_LEVELUP]);		// �������ÿ��� ���� ������ ����
	}
	else if( g_pRoh->m_nCharIndex == g_ii[0] )
	{
		ef_sort.pNkChaTo = g_pRoh;

		ef_sort.vPos = D3DVECTOR( g_pRoh->m_wx,
								  pCMyApp->GetLandPtr()->GetHFHeight(g_pRoh->m_wx, g_pRoh->m_wz),
								  g_pRoh->m_wz );

		g_pRoh->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );

		ef_sort.nCurFrame = -5;
		g_pRoh->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect( ef_sort ) );

		if ( g_pDSound )
			g_pDSound->Play(g_EffectSound[ EFF_SND_LEVELUP ]);

		if( g_pNk2DFrame && g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet() ) ///�굵�� �� �ߵ� ������ üũ�Ѵ�.
			g_pNk2DFrame->GetControlHelpPet()->CheckHelpCondition( 0, g_pRoh->m_Level, TRUE ); // ���� ������ ������ �ִ��� üũ�Ѵ�.
	}

}

void CmdMsg(char *arg, CUIMgr *pMgr)
{
	if( g_pNk2DFrame )
		g_pNk2DFrame->InsertPopup( arg, TYPE_NOR_OK, 1 );
}

void CmdMsg2(char *arg, CUIMgr *pMgr) ///�����޼���
{
	// UI Manager�� �Լ� ȣ��.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// ���� �޼��� ��ȣ.

	if( g_pNk2DFrame )
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(g_ii[0]), TYPE_NOR_OK, 1 ); // �������� �ٷ� �޼��� ��ȣ�� �޵��� ���� ///07-04-27
}

void CmdChangeSex(char *arg, CUIMgr *pMgr)
{
	// npc�ΰ� char�ΰ� ����.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// sex
	if (g_ii[1] != 0 && g_ii[1] != 1)
		return;

	if (pCha = pMgr->FindChaById(g_ii[0]))
	{
		pCha->m_Sex = g_ii[1];
		pCha->MakeBasicBody();
		if( g_pNk2DFrame )
			((CControlScore*)g_pNk2DFrame->GetInterface(SCORE))->SetSex();
		pCha->ResetMotionState();
		g_pNk2DFrame->GetControlStatus()->SetNkChar();
	}
}

void CmdChangeHair(char *arg, CUIMgr *pMgr)
{
	//sscanf(msg, "%s %s %d %d %d %d", first_arg, second_arg, &g_ii[0], &x, &z, &y);
	// npc�ΰ� char�ΰ� ����.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// sex
	if (g_ii[1] >= 10)
		g_ii[1] = (g_ii[1] % 10) + 5;

	if (g_ii[1] < 0 || g_ii[1] >= 10)
		return;

	if (pCha = pMgr->FindChaById(g_ii[0]))
	{
		pCha->m_Hair = g_ii[1];
		pCha->MakeBasicBody();
		pCha->ResetMotionState();
	}
}


void CmdWarTax(char *arg, CUIMgr * pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// ����¡����
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// ������

	if( g_ii[0] == -1 ) // -1�� ������ ������ ����ó��.(���ִ� ��ġ����� ���� ���ǿ����ؼ�..)
	{
		// �� ��� â�� �ݴ´�.
		if( pMgr->m_pWarTax)
		{
			delete pMgr->m_pWarTax;
			pMgr->m_pWarTax = NULL;
		}
		pMgr->m_bIsWarTax = FALSE;
	}

	if( pMgr )
		pMgr->GetServMsg_WarTax(g_ii[0], g_ii[1]);
}


void CmdWarReq(char *arg, CUIMgr * pMgr)
{
	arg = AnyOneArg(arg, g_Buf);  // ����
	arg = AnyOneArg(arg, g_Buf2); // �ð�
	arg = AnyOneArg(arg, g_Buf3); // �ð�
	g_ii[0] = atoi(g_Buf3);

	arg = AnyOneArg(arg, g_Buf4); // Ÿ��
	g_ii[1] = atoi(g_Buf4);

	if( pMgr )
		pMgr->GetServMsg_WarReq(g_Buf2, g_ii[0], g_ii[1]);
}

void CmdWarReqFail(char *arg, CUIMgr * pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	arg = AnyOneArg(arg, g_Buf);  // "req" �� �ð��̴�..

	if (!strcmp(g_Buf, "req"))
	{
		// IDS_CANNOT_CASTLE1 : ���� ��û�� �Ͻ� �� �����ϴ�.
		g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_CANNOT_CASTLE1),TYPE_NOR_OK, 1);
	}
	else if (!strcmp(g_Buf, "time"))
	{
		// IDS_CANNOT_CASTLE2 : "���� ��û �ð��� �̻��� �ֽ��ϴ�."
		g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_CANNOT_CASTLE2),TYPE_NOR_OK, 1);
	}

	pMgr->m_bIsWarReq = FALSE;
	SAFE_DELETE( pMgr->m_pWarReq );
}

void CmdMyPet(char *arg, CUIMgr * pMgr)
{
	arg = AnyOneArg(arg, g_Buf);  // del or index

	if (!strcmp(g_Buf, "del"))
	{
		SAFE_DELETE( pCMyApp->m_pMyPet );

		if(g_pNk2DFrame && g_pNk2DFrame->IsLShiftVisible())
			g_pNk2DFrame->SetShowLShiftFlag(FALSE);
		return;
	}
	if (!strcmp(g_Buf, "clear"))
	{
		SAFE_DELETE( pCMyApp->m_pMyPet );	// Pet����

		if(g_pNk2DFrame && g_pNk2DFrame->IsLShiftVisible())
			g_pNk2DFrame->SetShowLShiftFlag(FALSE);
		ZeroMemory( &g_MyPetStatus, sizeof( g_MyPetStatus ) );
		if( pMgr )
			pMgr->CmdExchPetClear();
		return;
	}

	g_ii[0] = atoi(g_Buf); // index
	arg = AnyOneArg(arg, g_Buf2);  // name

	arg = AnyOneArg(arg, g_Buf);  // class
	g_ii[1] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);  // x
	x = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // z
	z = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // dir
	dir = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // horn
	v_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // head
	v_num[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // body
	v_num[2] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // wings
	v_num[3] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // legs
	v_num[4] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);  // tail
	v_num[5] = atoi(g_Buf);

	SAFE_DELETE( pCMyApp->m_pMyPet );
	pCMyApp->m_pMyPet = new CNkMyPet(g_ClrAlloc);
	if( !pCMyApp->m_pMyPet )
		return;
	pCMyApp->m_pMyPet->m_bPet = TRUE;
	if (g_pRoh
			&& g_pRoh->m_Level >= 250)
		pCMyApp->m_pMyPet->SetMetaPet(TRUE);

	pCMyApp->m_pMyPet->m_PetClass = g_ii[1]; // �� Ÿ��(�⺻��0,�����1,������2)
	g_MyPetStatus.SetClassType( g_ii[1] ); // �������̽� Ŭ�������� ����صд�.

	pCMyApp->m_pMyPet->SetInitPos(x, z, dir);
	pCMyApp->m_pMyPet->m_nVirId = g_ii[0];
	pCMyApp->m_pMyPet->SetMotionState(PET_STAND);
	pCMyApp->m_pMyPet->SetBody(v_num[0], v_num[1], v_num[2], v_num[3], v_num[4], v_num[5]);
	// �ֿϵ��� �̸��� �޴´�.
	pCMyApp->m_pMyPet->SetName(g_Buf2);
	if( g_pNk2DFrame->GetControlPetStatus() )
	{
		g_pNk2DFrame->GetControlPetStatus()->Reposition();
		g_pNk2DFrame->GetControlPetStatus()->SetPetName(g_Buf2);
	}
	// Ȥ�� ���� ������ ������ ������!
	g_pRoh->RemoveAllEggs();
}


void CmdPetStatus(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);
	/*  // �̰� ����? Ȥ�� �ٸ� ��� ���� ������ �ܻ󳲴°� �����Ϸ��� �����ΰ�? �ϴ� �ҽ� ��ü�� ���ǹ��ϰ� �߸��� �ҽ��� �ּ�ó����. (05-10-27 ����)
		if (pPet = pMgr->FindPetById(g_ii[2]))
		{
			if(g_ii[2] >0 )
				pPet->GetDeadFrame();
		}
	*/
	if( !g_pNk2DFrame->GetControlPetStatus() )
		return;

	switch (g_ii[0])
	{
	case PET_VITAL: // �����
		g_MyPetStatus.SetVital(g_ii[1], g_ii[2]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_VITAL, g_ii[1], g_ii[2]);
		break;
	case PET_DAM_RANGE: //���ݰ���
		g_MyPetStatus.SetRangeAtt(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_DAM_RANGE, g_ii[1]);
		break;
	case PET_DAM_MELEE: //��������
		g_MyPetStatus.SetMeleeAtt(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_DAM_MELEE, g_ii[1]);
		break;
	case PET_ARMOR_RANGE://���ݹ��
		g_MyPetStatus.SetRangeDef(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_ARMOR_RANGE, g_ii[1]);
		break;
	case PET_ARMOR_MELEE://�������
		g_MyPetStatus.SetMeleeDef(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_ARMOR_MELEE, g_ii[1]);
		break;
	case PET_SPEED://�̵��ӵ�
		g_MyPetStatus.SetSpeed(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_SPEED, g_ii[1]);
		break;
	case PET_COMPOSE://���շ���
		g_MyPetStatus.SetLevel_Compos(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_COMPOSE, g_ii[1]);
		break;
	case PET_PICK://ȹ�淹��
		g_MyPetStatus.SetLevel_Pick(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_PICK, g_ii[1]);
		break;
	case PET_LOYALTY://�漺��
		g_MyPetStatus.SetLoyalty(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_LOYALTY, g_ii[1]);
		break;
	case PET_HUNGER://������
		g_MyPetStatus.SetHunger(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_HUNGER, g_ii[1]);
		break;
	case PET_LEVEL://����
		g_MyPetStatus.SetLevel(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_LEVEL, g_ii[1]);
		break;
	case PET_EXP://����ġ
		g_MyPetStatus.SetExp(g_ii[1]);
		g_pNk2DFrame->GetControlPetStatus()->SetPetStatus(PET_EXP, g_ii[1]);
		g_pNk2DFrame->GetControlPeiceShop()->SetMyPetExp(g_ii[1]);
		g_pNk2DFrame->GetControlPeiceShop()->SetPieceName();
		break;
	case PET_MODE://���
		if( g_ii[2] )
		{
			if( pCMyApp->m_pMyPet == pMgr->FindPetById(g_ii[2]) )
			{
				g_MyPetStatus.SetMode(g_ii[1]);
				if(g_pNk2DFrame->IsLShiftVisible()
						&& g_ii[1] == MYPET_MODE_KEEP)	//��������(�������)
					g_pNk2DFrame->SetShowLShiftFlag(FALSE);
			}
		}
		else
		{
			g_MyPetStatus.SetMode(g_ii[1]);
			if( g_pNk2DFrame->IsLShiftVisible()
					&& g_ii[1] == MYPET_MODE_KEEP)	//��������(�������)
				g_pNk2DFrame->SetShowLShiftFlag(FALSE);
		}
		break;
	case PET_BAG://�ٱ��� �ٱ���!
		g_MyPetStatus.SetBag(g_ii[1]);
		break;
	case PET_BAG_COUNT://������ � ��� �ּ�?
		g_MyPetStatus.SetFoodCount(g_ii[1]);
		break;
	case PET_NEED_MONEY://�������ÿ� �ʿ��� ��
		g_MyPetStatus.SetNeedMoney(g_ii[1]);
		break;
	case PET_NEED_EXP://�������ÿ� �ʿ��� ����
		g_MyPetStatus.SetNeedExp(g_ii[1]);
		break;
	case PET_NECKLACE://����� �ٱ �̻���? �̻��ڳ�~~!
		g_MyPetStatus.SetNecklace(g_ii[1]);
		break;
	case PET_SKILL: // ��ų ����. �� ������� �ƿ� �� �ð��̴�.
		g_MyPetStatus.SetSkill( g_ii[1],g_ii[2] );
		break;
	}
}


void CmdKeepInfo(char *arg, CUIMgr *pMgr)
{
	char Name[255] = {0,};

	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "info"))
	{
		arg = AnyOneArg(arg, Name);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// ��������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// ����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// ü��
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// �漺��
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// ã�±ݾ�
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);			// �ð�

		if( pMgr )
			pMgr->CmdSetKeepInfo(Name, g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6]);
	}
	else if (!strcmp(g_Buf, "fail"))
	{
		if( g_MyPetStatus.mode == MYPET_MODE_KEEP
				|| g_MyPetStatus.mode == MYPET_MODE_HOLD)
			// IDS_CMD_NOTYET_EGG : ���� ã���� �� �����ϴ�.
			pMgr->CmdErrorMsg((char *)G_STRING(IDS_CMD_NOTYET_EGG));
		else if( g_MyPetStatus.mode == MYPET_MODE_EGG )
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[0] = atoi(g_Buf);			// �����ð�

			char tmp[255];
			int hour = 0, min = 0;
			int total = g_ii[0] + 1;

			hour = total / 60 / 60;
			min = (total - (hour*60*60)) / 60;

			// IDS_CMD_LIVE_TIME : ��ȭ���� %d�ð� %d�� ���ҽ��ϴ�
			sprintf(tmp, G_STRING(IDS_CMD_LIVE_TIME), hour, min);
			if( pMgr )
				pMgr->CmdErrorMsg(tmp);
		}
	}
}

void CmdPetShop(char *arg, CUIMgr *pMgr)
{
	char Name[255] = {0,};

	arg = AnyOneArg(arg, g_Buf);
	if (pMgr && !strcmp(g_Buf, "fail"))
		// IDS_CMD_UNABLE_BUY : ���̻� �����Ͻ� �� �����ϴ�
		pMgr->CmdErrorMsg((char *)G_STRING(IDS_CMD_UNABLE_BUY));
}

void CmdPetSocial(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);		// �ֿϵ��� ID
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);		// ���� Index
	arg = AnyOneArg(arg, g_Buf);
	x = atoi(g_Buf);			// x
	arg = AnyOneArg(arg, g_Buf);
	z = atoi(g_Buf);			// z

	if (pPet = pMgr->FindPetById(g_ii[0]))
	{
		if (g_ii[1] == MYPET_SOCIAL_PICKUP)
			pPet->Pickup((float) x, (float) z);
	}
}

void CmdGWar(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	if (!strcmp(g_Buf, "0")
			|| !strcmp(g_Buf, "1")
			|| !strcmp(g_Buf, "2")
			|| !strcmp(g_Buf, "3"))
	{
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		arg = AnyOneArg(arg, g_Buf2);
		arg = AnyOneArg(arg, g_Buf3);
		arg = AnyOneArg(arg, g_Buf4);
		if( pMgr )
			pMgr->GuildWarStaus(g_ii[0], g_Buf, g_Buf2, g_Buf3, g_Buf4);
	}
	else if (!strcmp(g_Buf, "cancel"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		if( pMgr )
			pMgr->GWarCancel(g_ii[0]);
	}
	else if (!strcmp(g_Buf, "point"))
	{
		arg = AnyOneArg(arg, g_Buf1);//A�� �̸�
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf2);//B�� �̸�
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);
		if( pMgr )
		{
			pCha = pMgr->FindChaById(g_ii[2], TRUE);
			pMgr->GWarPoint(g_ii[0], g_ii[1], g_Buf1, g_Buf2,pCha);
		}
	}
	else if (!strcmp(g_Buf, "head"))
	{
		arg = AnyOneArg(arg, g_Buf);
		arg = AnyOneArg(arg, g_Buf2);
		if( pMgr )
			pMgr->GWarHead(g_Buf, g_Buf2);
	}
	else if (!strcmp(g_Buf, "effect"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		x = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		z = atoi(g_Buf);

		if( !pCMyApp->m_pFxSet )
			return;

		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));
		ef_sort.nType = FX_STARFLAREBOOM;
		ef_sort.vPos.x = x;
		ef_sort.vPos.z = z;
		ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight(x, z);
		pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
	}
	else if (!strcmp(g_Buf, "char"))
	{
		arg = AnyOneArg(arg, g_Buf);
		arg = AnyOneArg(arg, g_Buf2);
		g_ii[0] = atoi(g_Buf2);
		if( pMgr )
			pMgr->AddTeamMem(g_Buf, g_ii[0]);
	}
	else if( pMgr )
		pMgr->GWarNotify(g_Buf);
}

///2003 ĳ���ͳ� ���� ����(��ȭ,����) �޽���
void CmdChaCondition(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	if (!strncmp(g_Buf, "c", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);		// �ε���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);		// ���¹�ȣ
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);		// 0/1.	1�� ���� On

		if(pCha = pMgr->FindChaById(g_ii[0]))
		{
			if(g_ii[1]==5)
			{
				//�����̶��,0925ore
				if(g_ii[2]==1)	//���½����̶��,
					pCha->m_Accumulate = TRUE;
				else
					pCha->m_Accumulate = FALSE;
			}
			else
			{
				pCha->SetChaCondition(g_ii[1], g_ii[2]);
			}
		}

	}
	else
	{
		//���϶�.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);		// �ε���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);		// ���¹�ȣ
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// 0/1

		if(pMob = pMgr->FindMobById(g_ii[0]))
		{
			pMob->SetChaCondition(g_ii[1], g_ii[2]);
		}
	}
}


////2003 �迭�ı� �޽���
void CmdConDistruction(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	if (!strncmp(g_Buf, "n", 1))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);//�迭�ı�,�Ǵ� ����

		if (pMob = pMgr->FindMobById(g_ii[0]))
			pMob->SetClassType(g_ii[1]);
	}
}

//--------------------------------------------------------------------------
// CmdSubAttackVital
//--------------------------------------------------------------------------
// ���� �������� ���� ��� ������ �޼���
// 2005.02.12
// Lyul / ����� ���� �߰�.
// !!!! ����� ���� ����  Get_shape �� �Ἥ ó��
// ���� ��ƾ�� ������ ��ũ�� �����̾� �κ� �����ٶ�!!!!!!!!!!
// ���� �ð��� ���. ( �Ƹ� �彽 ���� ���� �� )
// �����̾�� ��ũ���� ó����ƾ�� Ʋ���� �Ѵ�.
void CmdSubAttackVital(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);     //�ε���
	arg = AnyOneArg(arg, g_Buf);
	vital = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);     //ĳ������ ����� ����
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2]= atoi(g_Buf);      //�迭�� ��������.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3]= atoi(g_Buf);      //����������� ����
	arg = AnyOneArg(arg, g_Buf);
	g_ii[4]= atoi(g_Buf);      //Wearing ��ġ.(��� ����������.)

	CNkCharacter *pNkCha = g_pRoh;
	CItem *pItem = NULL;

	pItem = pNkCha->m_Wearing[ g_ii[4] ];
	if(pItem)
	{
		if(pItem->m_Vnum==693
				|| (pItem->m_Vnum>=731 && pItem->m_Vnum<=738)//íũ��
				|| (pItem->m_Vnum>=724 && pItem->m_Vnum<=730)
				|| (pItem->m_Vnum==947||pItem->m_Vnum==948)
				|| (pItem->m_Vnum==3064) // ��ĭ
		  )
		{
			//�����̾�
			if(g_ii[3]==1)//�������� 1�̸� 0�̶���.
				pItem->m_Special = 0;
			else
				pItem->m_Special = g_ii[3]; //����
		}
		else if( (pItem->m_Vnum>=740 && pItem->m_Vnum<=756)				   //�������
				 || (pItem->m_Vnum>=768 && pItem->m_Vnum<=775)
				 || (pItem->m_Vnum >= 949 && pItem->m_Vnum <= 955)
				 || (pItem->m_Vnum >= 1021 && pItem->m_Vnum <= 1023)
				 || (pItem->m_Vnum == 3068) // �޸�
				 || (pItem->m_Vnum == 3065) // ī��
				 || (pItem->m_Vnum == 3067 || pItem->m_Vnum == 3261) // ���̵��
			   )
			pItem->m_PlusNum = g_ii[3]; //����
		// ����� ����
		else if ( (GET_SHAPE(pItem) == ISUB_DSTONE) )
			pItem->m_Special = g_ii[3]; //����
		else if( GET_SHAPE(pItem) == ISUB_PANEL )
		{
			pItem->m_Special = g_ii[3];
		}
	}
	if( pMgr )
		g_pNk2DFrame->GetControlInven()->ResetItemInfo();

	if( g_ii[1] == -1 )
		return;

	if( g_pRoh )
		g_pRoh->SetAttackType(g_ii[1]);//����� ����

	if (!strncmp(g_Buf2, "n", 1))
	{
		if (pMob = pMgr->FindMobById(g_ii[0]))
		{
			if(g_ii[2]==0)
				pMob->SetClassType(g_ii[2]);
			pMob->SetAttackVital(vital);
		}
	}
	else
	{
		// "c"
		if (pCha = pMgr->FindChaById(g_ii[0]))
			pCha->SetAttackVital(vital);
	}
}

//////2003 �������� ���������(��ũ��,źȯ,������)�� ������ �޽���
void CmdUseQuickSubItem(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "fail"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		if(g_ii[0]!=-1)
			g_pRoh->m_bQuickSlotLock[g_ii[0]]=FALSE;

		for(int i=0; i<=5; i++)
			g_pRoh->m_bQuickSlotLock[i]=FALSE;
	}
	else if (!strcmp(g_Buf, "succ") || !strcmp(g_Buf, "remain"))
	{
		// ������ ��¦ �ٲ��ߵɵ�!
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// del_slot
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// fill_slot
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2]= atoi(g_Buf);			// plus_num
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3]= atoi(g_Buf);			// special_num

		if( pMgr )
			pMgr->UseQuickSubItem(g_ii[0],g_ii[1],g_ii[2],g_ii[3]);
	}
}

/////2003  �������� ����å�� ������ ȿ�� �޼��� ,������ųȿ�� �޽���.
void CmdEffectSubItem(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "1"))	//���濡�� ���긶���� �ɶ�.
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			//npc.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			//�ε���

		pCha = pMgr->FindChaById(g_ii[1]);//���� �Ŵ� ���.�׻� ĳ����.
		if(pCha==NULL)
			return;

		arg = AnyOneArg(arg, g_Buf);    //npc

		if (!strncmp(g_Buf, "n", 1))	//Ÿ��
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);		//�ε���
			arg = AnyOneArg(arg, g_Buf);
			g_ii[4] = atoi(g_Buf);		//������,å�̳�..

			if (g_ii[4]==SKILL_REMOVE)
				pCha->SetUseBookEffect(EFFECT_REMOVE);		//������ ����� ȿ��
			else if (g_ii[4]==SKILL_LIFE_LIGHT)
				pCha->SetUseBookEffect(EFFECT_LIFE_LIGHT);	//������ �� ����� ȿ��.
			else//å
				pCha->SetUseBookEffect(EFFECT_USE_BOOK);	//å�� ����� ȿ��

			if (pMob = pMgr->FindMobById(g_ii[3]))
			{
				if(g_ii[4]==0)
				{
					//��Ȧ�̶��
					if(pCha->m_nCharIndex != g_pRoh->m_nCharIndex)
					{
						pCha->SetAttackMobId(pMob->m_nVirId);
						pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,SKILL_BOOK_READ);
					}
					pMob->SetUseBookEffect(EFFECT_BLACKHOLE);
				}
				else
				{
					if(pCha->m_nCharIndex != g_pRoh->m_nCharIndex)
					{
						pCha->SetAttackMobId(pMob->m_nVirId);
						pCha->Attack(pMob->m_wx, pMob->m_wy, pMob->m_wz,g_ii[4]);
					}
					pMob->SetUseBookEffect(EFFECT_BOOK); //���� å,���� �����´� ȿ�� On
				}
			}
		}
		else
		{
			// "c"
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);			//�ε���
			arg = AnyOneArg(arg, g_Buf);
			g_ii[4] = atoi(g_Buf);			//������,å�̳�..

			if (g_ii[4]==SKILL_REMOVE) 	//���� 52
				pCha->SetUseBookEffect(EFFECT_REMOVE);   //������ ����� ȿ��
			else if (g_ii[4]==SKILL_LIFE_LIGHT)
				pCha->SetUseBookEffect(EFFECT_LIFE_LIGHT);   //������ �� ����� ȿ��.
			else//å
				pCha->SetUseBookEffect(EFFECT_USE_BOOK);   //å�� ����� ȿ��

			if (pCha2 = pMgr->FindChaById(g_ii[3]))
			{
				if(g_ii[4]==0)
				{
					//��Ȧ�̶��
					if(pCha->m_nCharIndex != g_pRoh->m_nCharIndex)
					{
						pCha->SetAttackChaId(pCha2->m_nCharIndex);
						pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,SKILL_BOOK_READ);
					}
					pCha2->SetUseBookEffect(EFFECT_BLACKHOLE);//��Ȧ ȿ��
				}
				else
				{
					if(pCha->m_nCharIndex != g_pRoh->m_nCharIndex)
					{
						pCha->SetAttackChaId(pCha2->m_nCharIndex);
						pCha->Attack(pCha2->m_wx, pCha2->m_wy, pCha2->m_wz,g_ii[4]);
					}
					pCha2->SetUseBookEffect(EFFECT_BOOK);//ĳ���� å,���� ���� �´� ȿ�� On
				}

				// ��ٿ� ��� ���� ó�� 07-03-14 ����
				if( pCha2 == g_pRoh ) // �´°� �ڽ��̸�..
				{
					if( g_pRoh->GetMotionState() == CHA_C_HELLDOWN ) // ��ٿ� ������� ���̾��ٸ�...
					{
						g_pRoh->HellDownFail( g_pRoh, NULL ); // ��ٿ��� ��ҽ�Ų��.
					}
				}
			}
		}
	}
	else
	{
		//0���� �ö�,�ڽſ��� ���� ���� �ɶ�.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			 //npc. �׻� c�� ��.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			 //�ε���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2]= atoi(g_Buf);				 //Ÿ��(���� ó�� ����)
		if(pCha = pMgr->FindChaById(g_ii[1]))
		{
			//���� �׻� ĳ����...
			if(g_ii[2])//1�̶�� on
				pCha->SetUseBookEffect(EFFECT_SCANVIEW);
		}
	}
}
///2003 �����޽���.
void CmdAssembly(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;
	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "succ"))
	{
		arg = AnyOneArg(arg, g_Buf); //������ ������ vnum
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf); //������ ������ �ε���.
		g_ii[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf); //������ ������ vnum
		g_ii[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf); //������ ������ �ε���.
		g_ii[3] = atoi(g_Buf);

		pMgr->AssemblySuccess(g_ii[0],g_ii[1],g_ii[2],g_ii[3]);
		pMgr->AssemblyFail(FALSE);
	}
	else	// fiall
		pMgr->AssemblyFail(TRUE);
}

void CmdCombine(char *arg, CUIMgr *pMgr)//������� ������� �ֱ�.����(split)
{
	CNkCharacter *pNkCha = g_pRoh;
	CItem *pItem = NULL;

	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "succ"))
	{
		arg = AnyOneArg(arg, g_Buf); //������� (����Ʈ)
		g_ii[0] = atoi(g_Buf);
		pNkCha->m_Wearing[3]->m_Special = g_ii[0];
		pCMyApp->m_bEquipLock = FALSE;//������� �� ���� 1009

		if( pMgr )
			g_pNk2DFrame->GetControlInven()->ResetItemInfo();///0928  ���� ����.
	}
	else
		pCMyApp->m_bEquipLock = FALSE;//������� �� ����

	for(int i=0; i<=5; i++)
	{
		if( g_pRoh )
			g_pRoh->m_bQuickSlotLock[i] = FALSE;
	}
}

//--------------------------------------------------------------------------
// CmdSummonMob
//--------------------------------------------------------------------------
// ��ȯ���� ����� ���ſ� ���õ� �޼���
// sm  c 'ch' n '�� �ε���' ��ǥ ���
void CmdSummonMob(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	CNkCharacter *pNkCha = g_pRoh;

	arg = AnyOneArg(arg, g_Buf);//c
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			//�ε���
	pCha = pMgr->FindChaById(g_ii[0]);//��ȯ�ϴ� ĳ����

	arg = AnyOneArg(arg, g_Buf);    //n
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);		//�ε���
	pMob = pMgr->FindMobById(g_ii[1]);//��ȯ�ϴ� ĳ����

	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);			//x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);			//z

	arg = AnyOneArg(arg, g_Buf);
	g_ii[4] = atoi(g_Buf);		//��ȯ,����ȯ

	if(g_ii[4] == 1 || g_ii[4] == 11)	// �Ϲݼ�ȯ�� : 0(�Ҹ�)_1(����), �����ö�� ��ȯ�� : 10(�Ҹ�)_11(����)
	{
		// �� ��ȯ�����
		if(pCha == pNkCha)
		{
			if( g_ii[4] == 1 )
				pMgr->m_pSummonMob[ 0 ] = pMob;
			else if( g_ii[4] == 11 )
				pMgr->m_pSummonMob[ 1 ] = pMob;
		}

		if( !pCMyApp->m_pFxSet )
			return;

		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));
		ef_sort.nType = FX_SHOWUP2;
		ef_sort.vPos.x = g_ii[2];
		ef_sort.vPos.z = g_ii[3];
		ef_sort.vPos.y = pCMyApp->GetLandPtr()->GetHFHeight(x, z);
		pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		ef_sort.nCurFrame = -2;
		pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
		ef_sort.nCurFrame = -4;
		pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
	}
	else if( g_ii[4] == 0 || g_ii[4] == 10 )
	{
		//����ȯ,�Ǵ� �ð� �ٵǼ� �������.
		if(pCha == pNkCha)
		{
			if( g_ii[4] == 0 )
				pMgr->m_pSummonMob[ 0 ] = NULL;
			else if( g_ii[4] == 10 )
				pMgr->m_pSummonMob[ 1 ] = NULL;
		}
	}
}

void CmdChaotic(char *arg, CUIMgr *pMgr) //1023
{

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			//�ε���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			//���

	if( pMgr )
	{
		pCha = pMgr->FindChaById(g_ii[0]);//
		if(pCha)
		{
			pCha->m_Chaotic_Grade = g_ii[1];
			pCha->SetChatMsg(pCha->m_pstrName, "");//1112
		}
	}
}

void CmdGuildPk(char *arg, CUIMgr *pMgr)
{
	if( !g_pRoh )
		return;

	int type = -1;
	int index = -1;

	arg = AnyOneArg(arg,g_Buf); // ���� ��ɾ�
	if(strcmp(g_Buf,"end") == 0)
	{
		// ����� ����
		g_pRoh->m_bGuildPK = false;
		g_pRoh->m_nTeamMemGrade = 0;
	}
	else if(strcmp(g_Buf,"start") == 0)
	{
		// ����� ���� (�Ӹ��� �ָ� ǥ�� ?? )
		arg = AnyOneArg(arg,g_Buf1);  // ������̸�
		g_pRoh->m_bGuildPK = true;
		g_pRoh->m_nTeamMemGrade= 9;
		ZeroMemory(g_pRoh->m_sEnemyGName,sizeof(g_pRoh->m_sEnemyGName));
		strcpy(g_pRoh->m_sEnemyGName,g_Buf1);
	}
	else if(strcmp(g_Buf,"request") == 0)
	{
		// ����� ��û
		type = 0;
		arg = AnyOneArg(arg,g_Buf1);// ��û�� ��� �̸�
		if( pMgr )
			pMgr->GuildPK(type,g_Buf1,g_Buf2,g_ii[0]);// �����ɾ� type, ��� //, ���(or �渶), PK ���� ��
	}
	else if(strcmp(g_Buf,"sder") == 0)
	{
		// ����� �׺�
		type = 1; // surrender
		arg = AnyOneArg(arg,g_Buf1); // �׺��� ��� �̸�
		arg = AnyOneArg(arg,g_Buf2); // �׺��� ����� ��� ������ �̸�
		if( pMgr )
			pMgr->GuildPK(type,g_Buf1,g_Buf2,g_ii[0]);// �����ɾ� type, ��� , ���(or �渶) //, PK ���� ��
	}
	else if(strcmp(g_Buf,"play") == 0)
	{
		arg = AnyOneArg(arg,g_Buf1); //��� �̸�
		arg = AnyOneArg(arg,g_Buf2); //��� �̸�
		CNkCharacter *pCha;
		LHCharacterMap_it pr;
		for (pr = pMgr->m_character_map.begin(); pr != pMgr->m_character_map.end(); pr++)
		{
			pCha = (*pr).second;
			if(pCha->m_pstrGuildName)
			{
				if(strcmp(g_Buf1,pCha->m_pstrGuildName) == 0 || strcmp(g_Buf2,pCha->m_pstrGuildName)==0)
					pCha->m_nTeamMemGrade = 9;
			}
		}
	}
	else if(strcmp(g_Buf,"stop") == 0)
	{
		arg = AnyOneArg(arg,g_Buf1); //������ ��� �̸�
		CNkCharacter *pCha;
		LHCharacterMap_it pr;
		for (pr = pMgr->m_character_map.begin(); pr != pMgr->m_character_map.end(); pr++)
		{
			pCha = (*pr).second;
			if(pCha->m_pstrGuildName)
			{
				if(strcmp(g_Buf1,pCha->m_pstrGuildName) == 0 )
					pCha->m_nTeamMemGrade = 0;
			}
		}
	}
}

void CmdPk(char *arg, CUIMgr *pMgr) //1111
{
	arg = AnyOneArg(arg, g_Buf);		//ĳ��index.
	g_ii[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			//0/1 1:���� 0:��.

	if(pCha = pMgr->FindChaById(g_ii[0]))
	{
		if(g_ii[1]==2 && !pCha->m_bNonPK)//0305 non������ ����.
			pCha->m_bNonPK = TRUE;
		else if(g_ii[1]==0 && pCha->m_bNonPK)//non ������ ����.
			pCha->m_bNonPK = FALSE;
		else
			pCha->m_Free_Pk = g_ii[1];

		pCha->m_bPk_render = TRUE;
		pCha->m_bShowChatPopup = TRUE; //0310 �����̳� �������� ����ÿ� â �ѹ� ����ֱ�.
		pCha->DrawChatPopup(FALSE);
	}
}

void CmdSky(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// id
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// ���༮ ����

	if (pCha = pMgr->FindChaById(g_ii[0], TRUE))
		pCha->SetFlyLevel(g_ii[1]);
}

void CmdSales(char *arg, CUIMgr *pMgr)
{
	if( !g_bSalesView )
	{
		if( g_bSendSalesOff )
			return ;

		if( g_pTcpIp )
			g_pTcpIp->SendNetMessage("sales_on 0\n");
		g_bSendSalesOff = TRUE;
		return ;
	}

	int say_type = 5;
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);


	if (g_ii[0] >= 0)
	{
		SkipSpaces(&arg);

		if(g_bFiltering)
			CheckAndRepair(arg);

		int len = strlen(arg);
		char *arg2 = AnyOneArg(arg, g_Buf);

		if (pCha = pMgr->FindChaById(g_ii[0]))
		{
			char *arg3 = arg;
			SkipSpaces(&arg3);
			pCha->SetChatMsg(g_Buf, arg2);
		}

		*arg2 = '>';
	}
	else if( g_ii[0] == -1 ) // -1�� ������ ��Ʈ�������� ���ְ� ���� ��Ŷ�̴�.(���� ������ ��縻 ��Ŷ���� ó���ߴ�.) (by ����)
	{
		SkipSpaces(&arg);
		g_pNk2DFrame->SetInfoBox2(arg); // ��� ������ ����ϰ� ȭ�� ����� ������ 3������ ����ش�.

		if (g_pDSound) // ¡�Ҹ� ���.
			g_pDSound->Play(g_EffectSound[EFF_SND_ENTRANCE]);
	}

	SkipSpaces(&arg);
	g_pNk2DFrame->AddChatStr(arg, say_type);
}


//============================================
// nate 2004 - 5
// �� �̵��� ����հ� ä�� ��ǥ�� �񵿱�ȭ ����
void CmdJump( char *arg, CUIMgr *pMgr )
{
	arg = AnyOneArg( arg, g_Buf );
	x = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );
	z = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );

	if( pCha = pMgr->FindChaById( g_ii[ 0 ] ) )
	{
		if( !pCMyApp->m_pFxSet )
			return;

		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));
		ef_sort.nType = FX_TELEPORT;
		ef_sort.vPos.x = pCha->m_wx;
		ef_sort.vPos.y = pCha->m_wy;
		ef_sort.vPos.z = pCha->m_wz;

		pCMyApp->m_pFxSet->InsertFxEffect( ef_sort );
	}

	return;
}
//============================================

// Happy New Year Event
void CmdEventNewYear(char *arg, CUIMgr *pMgr)
{
	// nate 2004 - 11 : Happy New Year Event
	pCMyApp->CreateHappyNewYear();

	if( g_pDSound )
		g_pDSound->Play(g_EffectSound[EFF_SND_HAPPYNEWYEAR]);

	return;
}

void CmdMultiAttack(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->CmdMultiAttack(arg);
}

void CmdQuest(char *arg, CUIMgr *pMgr)	// qt
{
	if( !g_pNk2DFrame )
		return;

	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);		// ����Ʈ ��ȣ,���͹�ȣ,�迭��ȣ,������ȣ

	if (!strcmp(g_Buf2, "get"))
	{
		g_pNk2DFrame->ShowInterfaceWindow(true, QUEST);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);		// ����Ʈ ��� ��Ŷ

		if(g_ii[1]==-1)	//����Ʈ ���
		{
			if( g_ii[0] >= 735 && g_ii[0] <= 801 )//mungmae-2006/06/22 ����� ����Ʈ�� ������ false
				g_pRoh->m_bSecialQuest = FALSE;

			// nate 2004 - 4 : quest
			pMgr->SetQuest2StartFlag( 0 );
			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetNoQuest();
			// �κ����� 1053 ������ ���� �����.
			CItem *pItem = NULL;
			// Inven ���� �����
			do
			{
				pItem = NULL;
				for (int i = 0; i < PACK_NUM; i++)
				{
					pItem = g_pRoh->PickItemInPack(i, 1053, TRUE);
					if (pItem)
						break;
				}
				if (pItem)
					delete pItem;
			}
			while (pItem);
			// ��ȯâ���� �����
			do
			{
				pItem = g_pRoh->PickItemInExgPack(1053, TRUE);
				if (pItem)
					delete pItem;
			}
			while (pItem);
			// �����Կ��� �����
			for (int i = 0; i < QUICK_SLOT_NUM*QUICK_SLOT_PAGE; i++)
			{
				if (g_pRoh->m_QuickSlot[i]
						&& g_pRoh->m_QuickSlot[i]->m_Vnum == 1053)
					SAFE_DELETE(g_pRoh->m_QuickSlot[i]);
			}
		}
		else if(g_ii[0]>=0)	//����Ʈ ����
		{
			if( g_ii[0] >= 735 && g_ii[0] <= 801 )//mungmae-2006/06/22 �ε��� 735~801�̸� 250~275 ����� ����Ʈ
				g_pRoh->m_bSecialQuest = TRUE;

			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->Read("data/quest.dta", g_ii[0]);

			// nate 2004 - 4 : quest
			if( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_Type == 2 )
				pMgr->SetQuest2StartFlag( 1 );

			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetName();
		}
	}
	else if(!strcmp(g_Buf2, "end"))
	{
		if( g_ii[0] >= 735 && g_ii[0] <= 801 )//mungmae-2006/06/22 ����� ����Ʈ�� ������ false
			g_pRoh->m_bSecialQuest = FALSE;

		// nate 2004 - 4 : quest
		pMgr->SetQuest2StartFlag( 0 );
		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetNoQuest();
	}
	else if(!strcmp(g_Buf2, "king"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);  //���μ���

		pMob = pMgr->FindMobById(g_ii[0]);//��

		if(pMob)
		{
			if(g_ii[1]==0)	//ŷ->�Ϲ�
				pMob->m_bQuestMob = FALSE;
			else if(g_ii[1]==1)	//�Ϲ�->ŷ
			{
				pMob->m_bQuestMob = TRUE;

				EffectSort ef_sort;
				ZeroMemory(&ef_sort, sizeof(EffectSort));
				ef_sort.nType = FX_MOBSHOWUP;
				ef_sort.num = g_ii[0];
				ef_sort.vPos.x = pMob->m_wx;
				ef_sort.vPos.z = pMob->m_wz;
				ef_sort.vPos.y = pMob->m_wy;
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);

				ef_sort.nCurFrame = -3;
				pCMyApp->m_pFxSet->InsertFxEffect(ef_sort);
			}
		}
	}
	else if(!strcmp(g_Buf2, "kill"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);  //���μ���

		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->Reload(g_ii[0],g_ii[1]);
	}
	else if(!strcmp(g_Buf2, "quick"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);  //������ ��ȣ
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);  //��������

		if(g_ii[1]>=0)
			g_pRoh->m_QuickSlot[g_ii[0]]->m_Special = g_ii[1]; //����Ʈ ���� ���� ����
		g_pNk2DFrame->GetControlInven()->ResetItemInfo();
	}
	else if(!strcmp(g_Buf2, "fail"))
	{
		if(!g_pNk2DFrame->IsInterfaceVisible(QUEST))
			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->QuestMessage();

		g_pNk2DFrame->ShowInterfaceWindow(true, QUEST);
		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->PopUpMsg(g_ii[0]);
	}
	else if(!strcmp(g_Buf2, "eff"))	//��ī���� ���谡�� �´�.
	{
		if( !pCMyApp->m_pFxSet )
			return;

		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);  //Z��
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);  //ĳ�� ���̵�

		pCha = pMgr->FindChaById(g_ii[2]);//ĳ����
		/////���⿡ ��ī���� ���谡 ����Ʈ ���� ȿ�� ����....

		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));

		if (g_pRoh->m_nCharIndex == g_ii[2])
		{
			ef_sort.nType = FX_GHOSTHUNT;
			ef_sort.pNkChaTo = g_pRoh;
			ef_sort.vPos = D3DVECTOR(g_ii[0], pCMyApp->GetLandPtr()->GetHFHeight(g_ii[0], g_ii[1]), g_ii[1]);
			g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if (pCha)
		{
			ef_sort.nType = FX_GHOSTHUNT;
			ef_sort.pNkChaTo = pCha;
			ef_sort.vPos = D3DVECTOR(g_ii[0], pCMyApp->GetLandPtr()->GetHFHeight(g_ii[0], g_ii[1]), g_ii[1]);
			pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
		else if(g_ii[2]== -1)
		{
			ef_sort.nType = FX_GHOSTRISE;
			ef_sort.vPos = D3DVECTOR(g_ii[0], pCMyApp->GetLandPtr()->GetHFHeight(g_ii[0], g_ii[1]), g_ii[1]);
			g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}

	}
	// nate 2004 - 4 : quest - ����Ʈ���� ������ �� ����Ʈ
	else if( !strcmp( g_Buf2, "tp" ) )
		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetTotalPoint( g_ii[ 0 ] );
	// �����߿� ���� �����鼭 ��ԵǴ� ���� ����Ʈ
	else if( !strcmp( g_Buf2, "pt" ) )
	{
		// ���� ����Ʈ
		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetRemainPoint( g_ii[ 0 ] );
		arg = AnyOneArg( arg, g_Buf1 );
		g_ii[ 1 ] = atoi( g_Buf1 );

		// ���� ����Ʈ
		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetAddPoint( g_ii[ 1 ] );

		// ��ũ�� �� ������� �α׸� ����� ���� �������� �˸�
		// ��ũ : ������ ��Ż������ �������� + ȹ�洩������ ��
		if( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_nQuestTotalPoint != ( g_ii[ 0 ] + g_ii[ 1 ] ) )
		{
			char strTemp[ 100 ];
			sprintf( strTemp, "qt_pt %d %d", g_ii[ 0 ], g_ii[ 1 ] );
			g_pTcpIp->SendNetMessage( strTemp );
		}
	}
	else if( !strcmp( g_Buf2, "nt" ) )
		((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->SetNextQuest();
	else if(!strcmp(g_Buf2, "sp"))
	{
		//����Ʈ ���� ����( 0, 1 );
		if( g_ii[0] )
			g_pRoh->m_bYanQuest = TRUE;
		else
			g_pRoh->m_bYanQuest = FALSE;
	}
	else if( !strcmp(g_Buf2, "bn") ) // ���� x���� ǥ��.
	{
		switch( g_ii[0] )
		{
		case 0: // ���ʽ� �ؽ�Ʈ ���ֱ�
			SAFE_DELETE( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_pBonusText );
			break;
		case 1: // ���� ���� ���ʽ� ���� x5��

			SAFE_DELETE( ((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_pBonusText );

			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_pBonusText = new CTextOutBox;
			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_pBonusText->Init( 20, RGB(250,100,100), 0, 0 );
			((CQuestData*)g_pNk2DFrame->GetInterface(QUEST))->m_pBonusText->SetString_withOutLine( "x5",RGB(250,250,250),RGB(250,50,50) );
			break;

		}
	}
}

void CmdRingCombine(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg( arg, g_Buf );
	g_ii[1] = atoi( g_Buf );  // Item_Flag

	if(g_ii[0]==-1) // ����
	{
		if(g_pNk2DFrame
				&& g_pNk2DFrame->GetEventAncient())
		{
			g_pNk2DFrame->GetEventAncient()->m_bExchange =FALSE;
			// IDS_CMD_FAIL_RING : ������ ȸ���� �����߽��ϴ�.
			if( g_pNk2DFrame )
			{
				if( g_ii[1] == 1 )
				{
					g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CMD_FAIL_RING_COMB), TYPE_NOR_OK, 1 );
				}
				else
				{
					if( g_dwClientCountry == CTRY_JPN )
						g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_ITEM_COMBINE_FAIL), TYPE_NOR_OK, 1 );
					else
						g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CMD_FAIL_RING), TYPE_NOR_OK, 1 );
				}
			}
		}

	}
	else if(g_ii[0]==-2)	// ��������
	{
		if( g_pRoh )
		{
			delete g_pRoh->m_Wearing[IARMOR_RING];
			g_pRoh->m_Wearing[IARMOR_RING] = NULL;	//�κ����� ���� ����...
		}
		if( g_pNk2DFrame && g_pNk2DFrame->GetEventAncient() )
			g_pNk2DFrame->GetEventAncient()->m_bExchange =FALSE;
	}
	else
	{
		//���� �߰�
		if( g_pRoh )
		{
			g_pRoh->m_Wearing[IARMOR_RING]->m_Special = g_ii[0];
			g_pRoh->m_Wearing[IARMOR_RING]->m_PlusNum = g_ii[1];
		}
		if( g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
			g_pNk2DFrame->GetControlInven()->ResetItemInfo();/// ���� ����.
	}

	pCMyApp->m_bRingLock = FALSE;//���� �� ����

	for(int i=0; i<=5; i++)
		g_pRoh->m_bQuickSlotLock[i] = FALSE;
}

void CmdNecklaceCombine(char *arg, CUIMgr *pMgr) // ����� �ռ� ///��
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// Item_Flag

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 2 ] = atoi( g_Buf );  // Item_Flag

	if( g_ii[0]== 1 ) // ����. (������ �������� �������. �ɼǰ��� �������ָ� �ȴ�.(������� Extra ���� ó���� �������� �˾Ƽ� ����.)
	{
		if( g_pRoh )
		{
			g_pRoh->m_Wearing[IARMOR_NECKLACE]->m_Special = g_ii[1];
			g_pRoh->m_Wearing[IARMOR_NECKLACE]->m_PlusNum = g_ii[2];
		}
		if( g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
			g_pNk2DFrame->GetControlInven()->ResetItemInfo();

		// status update
		if( g_pNk2DFrame->GetInterface(SCORE) )
			((CControlScore*)(g_pNk2DFrame->GetInterface(SCORE)))->SetAllScore();

	}
	else if( g_ii[0] == 0 ) // ���� (�ռ��� ����̿� �ռ��Ϸ��� ��� ����� ��..
	{
		_asm nop;
	}

	pCMyApp->m_bNecklaceLock = FALSE; // �� ����

	for(int i=0; i<=5; i++)
		g_pRoh->m_bQuickSlotLock[i] = FALSE;
}

void CmdQuestExchange(char *arg, CUIMgr *pMgr)//�������ڰ� ������ �ٲ��ֱ�.
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if( pMgr )
		g_pNk2DFrame->GetEventAncient()->QuestExchange(g_ii[0]);
}

void CmdParentsDay(char * arg, CUIMgr * pMgr)
{
	if( !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if(g_ii[0] == 1 || g_ii[0] ==2)  // ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);
		g_pNk2DFrame->GetEventAncient()->GetMsgParentsDay(TRUE, g_ii[0], g_ii[1]);
	}
	else
		g_pNk2DFrame->GetEventAncient()->GetMsgParentsDay(FALSE, 0, 0);
}

void CmdRoomListStart(char *arg, CUIMgr *pMgr)
{
	if( pMgr )
		pMgr->DoRoomListStart();
}

void CmdRoomList(char *arg, CUIMgr *pMgr)
{
	int room_num, room_type, count, max_count, min_level, max_level, fee;
	int state;

	arg = AnyOneArg(arg, g_Buf);		// ���ȣ
	room_num = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	room_type = atoi(g_Buf);			// ������
	arg = GetSentence(arg, g_Buf);		// ����
	arg = AnyOneArg(arg, g_Buf2);
	count = atoi(g_Buf2);
	arg = AnyOneArg(arg, g_Buf2);
	max_count = atoi(g_Buf2);
	arg = AnyOneArg(arg, g_Buf2);		// ���� �̸�.
	arg = AnyOneArg(arg, g_Buf3);		// waiting, playing
	state = atoi(g_Buf3);
	arg = AnyOneArg(arg, g_Buf3);		// min level
	min_level = atoi(g_Buf3);
	arg = AnyOneArg(arg, g_Buf3);		// max level
	max_level = atoi(g_Buf3);
	arg = AnyOneArg(arg, g_Buf3);		// min fee
	fee = atoi(g_Buf3);
	arg = AnyOneArg(arg, g_Buf3);		// ��й�ȣ

	if( pMgr )
		pMgr->ShowRoomList(room_num, room_type, g_Buf, count, max_count, g_Buf2, state, min_level, max_level, fee, g_Buf3);
}

void CmdEnterRoom(char *arg, CUIMgr *pMgr)
{
	int room_type, user_type;

	arg = AnyOneArg(arg, g_Buf);
	room_type = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf2);
	arg = AnyOneArg(arg, g_Buf);
	user_type = atoi(g_Buf);

	if( pMgr )
		pMgr->EnterRoom(room_type, g_Buf2, user_type);
}

void CmdTRoom(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	int which_loc;
	BOOL bWaiting, bOwner;

	arg = AnyOneArg(arg, g_Buf);			// command

	if (!strcmp("in", g_Buf))   //���Դ�.
	{
		arg = AnyOneArg(arg, g_Buf);		// ĳ���� �̸�
		arg = AnyOneArg(arg, g_Buf2);		// ����ġ, ���, ȫ��, û��
		which_loc = atoi(g_Buf2);

		arg = AnyOneArg(arg, g_Buf2);		// waiting, ready
		if (atoi(g_Buf2) == 0)
			bWaiting = FALSE;
		else
			bWaiting = TRUE;

		arg = AnyOneArg(arg, g_Buf2);		// 0: normal user, 1: master
		if (atoi(g_Buf2) == 0)
			bOwner = FALSE;
		else
			bOwner = TRUE;

		if( pMgr )
			pMgr->TRoomIn(g_Buf, which_loc, bWaiting, bOwner);

		return;
	}
	else if (!strcmp("out", g_Buf))
	{
		//������.
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(1, g_Buf);

		return;
	}
	else if (!strcmp("ready", g_Buf))
	{
		//���� �����̴�.
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(2, g_Buf);
		return;
	}
	else if (!strcmp("wait", g_Buf))
	{
		//��� �����̴�.
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(3, g_Buf);
		return;
	}
	else if (!strcmp("shop", g_Buf))
	{
		//�޿� �� �����̴�.
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(4, g_Buf);
		return;
	}
	else if (!strcmp("be_a", g_Buf))
	{
		//A�� û��
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(5, g_Buf);
		return;
	}
	else if (!strcmp("be_b", g_Buf))
	{
		//B�� ȫ��
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(6, g_Buf);
		return;
	}
	else if (!strcmp("master", g_Buf))
	{
		//�����̴�.
		arg = AnyOneArg(arg, g_Buf);
		if( pMgr )
			pMgr->TRoomUpdate(7, g_Buf);
		return;
	}
	else if (!strcmp("start", g_Buf))
	{
		//��� ����.(â �ݾ�����)
		pMgr->TRoomClose(FALSE);
		//// Room�� ���� Score �ʱ�ȭ
		if(pMgr->m_pTextScoreA)
			pMgr->m_pTextScoreA->SetString("0");
		if(pMgr->m_pTextScoreB)
			pMgr->m_pTextScoreB->SetString("0");
		return;
	}
	else if (!strcmp("kick", g_Buf))
	{
		pMgr->TRoomClose();
		// Close Score Board...
		if(pMgr->m_bShowScore)
			pMgr->DestroyScore();

		// If Shop Window is shown, Toggle Shop Window(Close)...
		if(g_pNk2DFrame && g_pNk2DFrame->IsShopVisible())
			g_pNk2DFrame->ToggleShopWindow();
		return;
	}

	arg = AnyOneArg(arg, g_Buf2);			// maybe character name

	pMgr->TRoom(g_Buf, g_Buf2);
}


void CmdTwPackage(char* arg, CUIMgr *pMgr )
{
	int	nDate;

	arg = AnyOneArg(arg, g_Buf);
	nDate = atoi(g_Buf);

	if( pMgr )
		pMgr->TwPackage( nDate );
}

void CmdMalId(char *arg, CUIMgr *pMar)
{
	arg = AnyOneArg(arg, g_Buf);
	strcpy(pCMyApp->m_strUserId, g_Buf);
}

//// ���� ��ȯ ���� �Լ�
void CmdPetExchOppInfo(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;

	//	"p_stat" : �̸� ���� ����� ���ݷ� ����  //�ٸ���� �ֿϵ��� ���� ����
	int cnt = 0;
	char strTemp[256];
	while(strlen(arg)>2 || strcmp(arg,"\0") != 0) //����
	{
		switch(cnt)
		{
		case 0:
			arg = AnyOneArg(arg, g_Buf);
			break; //�̸�
		case 1:
			arg = AnyOneArg(arg, g_Buf1);
			break;//����
		case 2:
			arg = AnyOneArg(arg, g_Buf2);
			break;//�����
		case 3:
			arg = AnyOneArg(arg, g_Buf3);
			break;//���ݷ�
		case 4:
			arg = AnyOneArg(arg, g_Buf4);
			break;//����
		case 5: // ���� Ŭ����(Ÿ��)
			arg = AnyOneArg(arg, strTemp);
			g_ii[0] = atoi( strTemp );
			break;
		case 6: // ��ų1 ����
			arg = AnyOneArg(arg, strTemp);
			g_ii[1] = atoi( strTemp );
			break;
		case 7: // ��ų2 ����
			arg = AnyOneArg(arg, strTemp);
			g_ii[2] = atoi( strTemp );
			break;
		case 8: // ��ų3 ����
			arg = AnyOneArg(arg, strTemp);
			g_ii[3] = atoi( strTemp );
			break;
		case 9: // ��ų4 ����
			arg = AnyOneArg(arg, strTemp);
			g_ii[4] = atoi( strTemp );
			break;
		}
		cnt++;
	}

	pMgr->CmdPetExchOppInfo(g_Buf,g_Buf1,g_Buf2,g_Buf3,g_Buf4,g_ii[0],g_ii[1],g_ii[2],g_ii[3],g_ii[4]);
}

void CmdPetProduct(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;
//	p_compo 0 //���� ����
//  p_compo 1 vnum index slotX slotY //���ռ���
	BOOL bSuccess = 0;
	arg = AnyOneArg(arg, g_Buf);
	bSuccess = atoi(g_Buf);
	if(bSuccess)
	{
		arg = AnyOneArg(arg, g_Buf); // vnum
		g_ii[0] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf); // index
		g_ii[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf); // slotX
		g_ii[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);// sloatY
		g_ii[3] = atoi(g_Buf);
		pMgr->PetAssemblySuccess(g_ii[0],g_ii[1],g_ii[2],g_ii[3] );
		pMgr->PetAssemblyFail(FALSE);
	}
	else
		pMgr->PetAssemblyFail(TRUE);
}

// �÷�Ƽ������ �Լ�
void CmdPlatinumExch(char *arg, CUIMgr *pMgr)
{
	g_ii[0] = g_ii[1] = g_ii[2] = g_ii[3] = g_ii[4] = -1;
	arg = AnyOneArg(arg, g_Buf);		//0�� ����, 1�� ����
	g_ii[0] = atoi(g_Buf);

	if(g_ii[0]==0)
	{
		//����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf); //� �����ΰ�.
	}
	else
	{
		//����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);
		if(g_ii[1]==0)
		{
			//������
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[4] = atoi(g_Buf);
		}
		else if(g_ii[1]==1)
		{
			//+������
			arg = AnyOneArg(arg, g_Buf);
			g_ii[2] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[3] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_ii[4] = atoi(g_Buf);
		}
	}
	if( pMgr )
		pMgr->PlatimumExch(g_ii[0],g_ii[1],g_ii[2],g_ii[3],g_ii[4]);
}

// ���� ��� �̺�Ʈ ���� �Լ�
void CmdSummerEvent(char *arg, CUIMgr *pMgr)
{
	g_ii[0] =g_ii[1] =g_ii[2] = g_ii[3] = g_ii[4] = -1;
	arg = AnyOneArg(arg, g_Buf);		//0�� ����, 1�� ����
	g_ii[0] = atoi(g_Buf);

	if(g_ii[0]==0)
	{
		//����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf); //� �����ΰ�.
	}
	else if(g_ii[0] == 1)
	{
		//����
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);
	}
	if( pMgr )
		pMgr->SummerEvent(g_ii[0],g_ii[1],g_ii[2],g_ii[3]);
}

// nate
// ���丶�콺 ������� ���� �Լ�
void CmdDictionary(char *arg, CUIMgr *pMgr)
{
	// �δܾ� �Է°�
	arg = AnyOneArg(arg,g_Buf);

	// ���������� ���и� �������� üũ�ؼ� �����ֵ��� �ٲپ���. g_Buf���� "fail", "ok", ���ڰ� ���� �� �ִ�. ( by ���� ) ///�����Է½ý��ۺ���
	if( strcmp(g_Buf,"error") == 0 ) // �� ���д� �Է� ���� �Ǵ� ���� ����. ������ �������� �ʾҰ� ��ȸ�� �����ִ´�.
	{
		// ���н� �ѹ��� �ٽ� ���������� �Ѵ�.(�ð����� ���ŵǴ� Ÿ�ֽ̹� �������� ���̵����� �����Ҽ��� �����Ƿ�.)
		if( !g_pNk2DFrame->GetAutoMouse()->m_bOneFailed ) // ù ���н�..
		{
			// �ѹ� �� �����ش�.(�������� �ð� ��輱 ������ ������ ��츦 ����.)
			char *buf;
			buf = g_pNk2DFrame->GetAutoMouse()->m_pTextIn->GetString();// or buf = m_pTextIn->GetStrBuf();

			int nSize = sizeof( buf ) / sizeof( char );
			char arStr[ 256 ] = {0,};

			int i = 0;
			while( *buf )
			{
				if( !IsSpace( *buf ) )
				{
					arStr[ i++ ] = *buf;
				}
				buf++;
			}

			g_pNk2DFrame->GetAutoMouse()->SendConfirm( arStr );

			g_pNk2DFrame->GetAutoMouse()->m_bOneFailed = TRUE;
		}
		else // �ι�° ���н�
		{
			// ������ ���� �����ش�. (���⼭ �ؾ��� �������� Ÿ�̹��� ���´�.)
			g_pNk2DFrame->GetAutoMouse()->m_pTextIn->ClearText();
			g_pNk2DFrame->GetAutoMouse()->SetTextInFocus();
		}

		return;
	}
	else if( strcmp(g_Buf,"fail") == 0 ) // ���� ����. ������ ��������.
	{
		g_pNk2DFrame->GetControlBottom()->m_CurTextView = g_pNk2DFrame->GetAutoMouse()->m_CurTextView;//��ư
		g_pNk2DFrame->GetControlBottom()->m_bAct = g_pNk2DFrame->GetAutoMouse()->m_bCurAct;//âũ��
		g_pNk2DFrame->ShowAutoMouseWindow(FALSE);
		g_pNk2DFrame->GetAutoMouse()->m_pTextIn->ClearText();
		g_pNk2DFrame->GetAutoMouse()->m_pTextIn->SetEnable(FALSE);

		return;
	}
	else if( strcmp(g_Buf,"ok") == 0 )
	{
		// �� �κ��� ó���� �ܼ��� �ý��� �г��� �ݾ��� ���̴�. ���� ��Ŀ�� ���Ƿ� Ŭ���̾�Ʈ���� ok������ ���¾ ���ǹ��ϴ�.(��Ģ�� �������� �Ǵ��ؼ� �����ϱ�)
		g_pNk2DFrame->GetControlBottom()->m_CurTextView = g_pNk2DFrame->GetAutoMouse()->m_CurTextView;//��ư
		g_pNk2DFrame->GetControlBottom()->m_bAct = g_pNk2DFrame->GetAutoMouse()->m_bCurAct;//âũ��
		g_pNk2DFrame->ShowAutoMouseWindow(FALSE);
		g_pNk2DFrame->GetAutoMouse()->m_pTextIn->ClearText();
		g_pNk2DFrame->GetAutoMouse()->m_pTextIn->SetEnable(FALSE);

		return;
	}

	arg = AnyOneArg(arg,g_Buf1);

	// ���丶�콺 Ȯ��
	pMgr->Dictionary(g_Buf,g_Buf1);
}

void CmdQnA(char *arg, CUIMgr *pMgr) ///QnA
{
	// ��Ŷ�� ������ �ٷ� ���� ��Ʈ���� ����´�.
	if( strcmp(arg," fail") == 0 ) // ����. â�� �ݱ� ���� ���.
	{
		g_pNk2DFrame->ShowAutoMouseWindow( FALSE ); // â�� �ݴ´�.

		return; // ���� �װ͸�..
	}

	g_pNk2DFrame->ShowAutoMouseWindow( TRUE, 1 ); // ���� Ÿ���� â�� �����ش�.
	g_pNk2DFrame->GetAutoMouse()->m_pMunjaText->SetString( arg );
	g_pNk2DFrame->GetAutoMouse()->m_pHelpInfo->SetIndex(-1); // ������ ���� �ֱ� ����...

	CMultiText MultiText; // �̰��� �̿��ؼ� ����.
	MultiText.AddStringMulti( arg, 26, TRUE, RGB(255,255,0) );
	g_pNk2DFrame->GetAutoMouse()->m_pHelpInfo->PutString( &MultiText ); // ���� ���ǽ��� �����.

	g_pNk2DFrame->GetAutoMouse()->SetTextInFocus();
}

void CmdQuiz(char *arg, CUIMgr *pMgr) // Quiz �̺�Ʈ.
{
	// ��Ŷ�� ������ �ٷ� ���� ��Ʈ���� ����´�.
	if( strcmp(arg," fail") == 0 ) // ����. â�� �ݱ� ���� ���.
	{
		g_pNk2DFrame->ShowAutoMouseWindow( FALSE ); // â�� �ݴ´�.

		return; // ���� �װ͸�..
	}

	g_pNk2DFrame->ShowAutoMouseWindow( TRUE, 2 ); // ���� Ÿ���� â�� �����ش�.

	g_pNk2DFrame->GetAutoMouse()->m_pMunjaText->SetString( arg );
	g_pNk2DFrame->GetAutoMouse()->m_pHelpInfo->SetIndex(-1); // ������ ���� �ֱ� ����...

	CMultiText MultiText; // �̰��� �̿��ؼ� ����.
	MultiText.AddStringMulti( arg, 26, TRUE, RGB(255,255,0) );
	g_pNk2DFrame->GetAutoMouse()->m_pHelpInfo->PutString( &MultiText ); // ���� ���ǽ��� �����.

	g_pNk2DFrame->GetAutoMouse()->SetTextInFocus();

//	g_pNk2DFrame->GetAutoMouse()->m_OpenTick = timeGetTime(); // ������ �ð��� ����ؼ� �����ð� �Է¾����� ������ �Ѵ�.
}

void CmdJewelExchange(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;
	arg = AnyOneArg(arg, g_Buf);		// 0�� ����, 1�� ����
	g_ii[0] = atoi(g_Buf);

	if (g_ii[0] == 0)
		pMgr->JewelExchange(0, -1, -1);
	else if ( g_ii[0] == 1 )
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);		// �ٲ� ������ ��ȣ.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);		// server index

		pMgr->JewelExchange(1, g_ii[1], g_ii[2]);
	}
}

void CmdLoadZonePos(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;
	pMgr->CmdLoadZonePos();

	if( pMgr->m_bIsTeleportItem ) // ������ ���� ���� ó���� ��.(by ����)
	{
		arg = AnyOneArg(arg, g_Buf);
		int slot = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int item_index = atoi(g_Buf);

		for( int index = 0; index < MAX_TELEPORT_COUNT; index++ )
		{
			arg = AnyOneArg(arg, g_Buf);		// �� �ε���
			g_ii[0] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);		// X ��ǥ
			g_ii[1] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);		// Y ��ǥ
			g_ii[2] = atoi(g_Buf);

			pMgr->m_pTeleportItem->SetZonePosString(index, g_ii[0], g_ii[1], g_ii[2]);
		}
		pMgr->m_pTeleportItem->SetSlot(slot);
	}
}

void CmdFreeUser( char* arg, CUIMgr* pMgr )
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf );

	if( g_ii[0] == 0 )
		g_bFreeUser = FALSE;
	else
		g_bFreeUser = TRUE;
}

void CmdUserType(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf );

	// �߰� �ʿ�
	// LP ��

	arg = AnyOneArg( arg, g_Buf );
	int lp = atoi( g_Buf );

	switch( g_ii[0] )
	{
	case 0:	// �Ϲݰ��� (30,90��)
		pCMyApp->m_IsPcBang_User = g_ii[0];
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pc , 0 );
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pre , 0 );
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Normal , 0 );
		break;

	case 1: // �ǽù� ����( ����,���װ���? )
		pCMyApp->m_IsPcBang_User = 1;
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pc , 1 );
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pre , 0 );
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Normal , 0 );
		pCMyApp->m_PcBangStartTime = timeGetTime(); // [2008/5/29 Theodoric] Pc�� 30�� üũ
		break;

	case 2:	// �ǽù� 30�а�� �޼���
		pCMyApp->m_PcBangStartTime = timeGetTime(); // [2008/5/29 Theodoric] Pc�� 30�� üũ
		{
			char buf[128] = {0,};
			sprintf( buf , G_STRING(IDS_LHSTRING1727), lp );
			g_pNk2DFrame->AddChatStr( buf, -1 );
		}
		break;
	case 3:
		{
			g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Normal , 1 );
			g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pc , 0 );
			g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pre , 0 );
			pCMyApp->m_PcBangStartTime = timeGetTime();
		}
		break;
	case 10:	// �����̾� ���� �����
		pCMyApp->m_IsPcBang_User = 2;
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pre , 1 );
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Pc , 0 );
		g_pNk2DFrame->GetNewEvent()->SetEvent( OpEvent_Type__Normal , 0 );
		pCMyApp->m_PcBangStartTime = timeGetTime();
		break;

	case 20: // �����̾� 30�а��
		pCMyApp->m_PcBangStartTime = timeGetTime();
		{
			char buf[128] = {0,};
			sprintf( buf , G_STRING(IDS_LHSTRING1727) , lp );
			g_pNk2DFrame->AddChatStr( buf, -1 );
		}
		break;
	case 30: // ���ΰ��� 30�а���޼���
		pCMyApp->m_PcBangStartTime = timeGetTime();
		{
			char buf[128] = {0,};
			sprintf( buf , G_STRING(IDS_LHSTRING1727) , lp );
			g_pNk2DFrame->AddChatStr( buf, -1 );
		}
		break;
	}
	return;
}

void CmdDropCandy(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if (pMob = pMgr->FindMobById(g_ii[0]))
	{
		pMgr->InsertMagic(NULL, NULL, NULL, pMob, EFFECT_DROPCANDY );
	}
	else if (pCha = pMgr->FindChaById(g_ii[0], TRUE))
	{
		pMgr->InsertMagic(NULL, NULL, pCha, NULL, EFFECT_DROPCANDY );
	}
}

//////////////////////////////////////////////////////////////////////////


void CmdDropApple(char *arg, CUIMgr *pMgr)		//�뻧 ��� �̺�Ʈ�� �ӽ�...
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if (pMob = pMgr->FindMobById(g_ii[0]))
		pMgr->InsertMagic(NULL, NULL, NULL, pMob, EFFECT_DROPAPPLE );
}


void CmdDropStarCandy(char *arg, CUIMgr *pMgr) // ������ �̺�Ʈ��
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if (pMob = pMgr->FindMobById(g_ii[0]))
	{
		pMgr->InsertMagic(NULL, NULL, NULL, pMob, EFFECT_DROPSTARCANDY );
	}
	else if (pCha = pMgr->FindChaById(g_ii[0], TRUE))
	{
		pMgr->InsertMagic(NULL, NULL, pCha, NULL, EFFECT_DROPSTARCANDY );
	}
}

// nate
void CmdStashPut( char *arg, CUIMgr *pMgr )
// ������ �̵� : �κ� -> â��
// arg : �������� ���۵� ��Ŷ ��ü�� �ִ�.
// ��� : ��Ŷ�� �����Ͽ� UIMgr�� stashPut() �� ����
{
	if( !pMgr )
		return;
	// AmyOneArg() �Լ��� ������ �������� �ϳ��� �߶� ������ �Լ�.
	arg = AnyOneArg( arg, g_Buf );

	g_ii[ 0 ] = atoi( g_Buf );	// ���� ���� Ȯ�� �޼���
	if( g_ii[ 0 ] == 1 )
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf );		// ������ ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 2 ] = atoi( g_Buf );		// �κ� �� ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 3 ] = atoi( g_Buf );		// â�� �� ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 4 ] = atoi( g_Buf );		// â�� ���� ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 5 ] = atoi( g_Buf );		// ������ ����

		for( int i = 0 ; i < g_ii[ 5 ]  ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );		// X ��ǥ
			g_ii[ 6 ] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );		// Y ��ǥ
			g_ii[ 7 ] = atoi( g_Buf );

			pMgr->StashPut( g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ], g_ii[ 4 ], g_ii[ 6 ], g_ii[ 7 ] );
		}
	}
	else
	{
		_asm nop;
	}
}

// nate
void CmdStashGet( char *arg, CUIMgr *pMgr )
// ������ �̵� : â�� -> �κ�
// arg : �������� ���۵� ��Ŷ ��ü�� �ִ�.
// ��� : ��Ŷ�� �����Ͽ� UIMgr�� stashGet() �� ����
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf );

	g_ii[ 0 ] = atoi( g_Buf );	// ���� ���� Ȯ�� �޼���
	if( g_ii[ 0 ] == 1 )
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf );		// ������ ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 2 ] = atoi( g_Buf );		// �κ� �� ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 3 ] = atoi( g_Buf );		// â�� �� ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 4 ] = atoi( g_Buf );		// â�� ���� ��ȣ
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 5 ] = atoi( g_Buf );		// ������ ī��Ʈ

		for( int i = 0 ; i < g_ii[ 5 ]  ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );		// Item Index
			g_ii[ 6 ] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );		// X ��ǥ
			g_ii[ 7 ] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );		// Y ��ǥ
			g_ii[ 8 ] = atoi( g_Buf );
			pMgr->StashGet( g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ], g_ii[ 4 ],  g_ii[ 6 ], g_ii[ 7 ], g_ii[ 8 ] );
		}
	}
	else
	{
		_asm nop;
		// error code....
	}
}

// ���� �ε���
void CmdUserIndex( char *arg, CUIMgr *pMgr )
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );
	if( g_pRoh )
		g_pRoh->m_nUserIndex = g_ii[ 0 ];
}
// ���� ID
void CmdUserId( char *arg, CUIMgr *pMgr )
{
	arg = AnyOneArg( arg, g_Buf );
	strcpy(pCMyApp->m_strLetterUserId,g_Buf);
}
//�������� �޽���
void CmdPostReceive( char *arg, CUIMgr *pMgr )
{
	if( !pMgr )
		return;
	arg = AnyOneArg( arg, g_Buf );
	pMgr->CreLetterMsgBox();
	pMgr->m_bShowLetterMsgBox = TRUE;
	g_bNewLetter = TRUE;//������ �˸���ư
}

// nate 2004 - 4 : Crash_Miss
void CmdMiss( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;
	arg = AnyOneArg( arg, g_Buf );
	arg = AnyOneArg( arg, g_Buf1 );
	g_ii[ 0 ] = atoi( g_Buf1 );

	pMgr->ComputeMiss( g_Buf, g_ii[ 0 ] );

	arg = AnyOneArg( arg, g_Buf );
	g_ii[1] = atoi( g_Buf ); // ��ų �ε���
	if( g_ii[ 1 ] == SKILL_B_PROTECTION_SHIELDS )
	{
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));
		ef_sort.nType = FX_SHIELDBLOCK;

		pCha = pMgr->FindChaById(g_ii[0], TRUE);

		if( pCha )
		{
			ef_sort.pNkChaFrom = pCha;
			pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
		}
	}
}

void CmdBlock( char* arg, CUIMgr* pMgr ) // Block ȿ��. ///��
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf1 ); // �� ĳ���� Ÿ��.(c or n)
	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf ); // �� ĳ���� �ε���.

	arg = AnyOneArg( arg, g_Buf2 ); // ���� ĳ���� Ÿ��.(c or n)
	arg = AnyOneArg( arg, g_Buf );
	g_ii[1] = atoi( g_Buf ); // ���� ĳ���� �ε���.

	pMgr->ComputeBlock( g_Buf1, g_ii[0], g_Buf2, g_ii[1] );
}

// nate 2004 - 4 : exchange
// Inven -> Exch
void CmdExchPut( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		// Who( Target or Source )

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// unum

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 2 ] = atoi( g_Buf );		// plus

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 3 ] = atoi( g_Buf );		// special

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[11] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[12] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[13] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[14] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[15] = atoi(g_Buf);			// �Ϲ� ������ Max
	}

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 4 ] = atoi( g_Buf );		// count

	// Source
	if( g_ii[ 0 ] == 0 )
	{
		// Exch
		for( int i = 0 ; i < g_ii[ 4 ] ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 5 ] = atoi( g_Buf );	// item index

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 6 ] = atoi( g_Buf );	// X

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 7 ] = atoi( g_Buf );	// Y

			if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
			{
				// Conpute
				pMgr->ExchPutExch( g_ii[ 5 ], g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ], g_ii[11], g_ii[12], g_ii[13],
								   g_ii[ 6 ], g_ii[ 7 ], g_ii[14], g_ii[15] ); ///�Ź���ȭ�ý���
			}
			else
			{
				pMgr->ExchPutExch( g_ii[ 5 ], g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ], g_ii[11], g_ii[12], g_ii[13],
								   g_ii[ 6 ], g_ii[ 7 ], 0, 0 ); ///�Ź���ȭ�ý���
			}
		}

		// Inven
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 8 ] = atoi( g_Buf );		// inven pack num

		for( int i = 0 ; i < g_ii[ 4 ] ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 9 ] = atoi( g_Buf );	// X

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 10 ] = atoi( g_Buf );	// Y

			// Compute
			pMgr->ExchPutInven( g_ii[ 8 ],  g_ii[ 9 ], g_ii[ 10 ] );
		}
	}
	// Target
	else if( g_ii[ 0 ] == 1 )
	{
		for( int i = 0 ; i < g_ii[ 4 ] ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 5 ] = atoi( g_Buf );	// item index

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 6 ] = atoi( g_Buf );	// X

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 7 ] = atoi( g_Buf );	// Y

			// Compute
			if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
			{
				pMgr->ExchPutTarget( g_ii[ 5 ], g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ], g_ii[11], g_ii[12], g_ii[13],
									 g_ii[ 6 ], g_ii[ 7 ], g_ii[14], g_ii[15] ); ///�Ź���ȭ�ý���
			}
			else
			{
				pMgr->ExchPutTarget( g_ii[ 5 ], g_ii[ 1 ], g_ii[ 2 ], g_ii[ 3 ], g_ii[11], g_ii[12], g_ii[13],
									 g_ii[ 6 ], g_ii[ 7 ], 0, 0 ); ///�Ź���ȭ�ý���
			}
		}
	}
}

// Exch -> Inven
void CmdExchGet( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );			// Who( Target or Source )

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );			// count

	// Source
	if( g_ii[ 0 ] == 0 )
	{
		// Exch
		for( int i = 0 ; i < g_ii[ 1 ] ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 2 ] = atoi( g_Buf );		// X

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 3 ] = atoi( g_Buf );		// Y

			// Compute
			pMgr->ExchGetExch( g_ii[ 2 ], g_ii[ 3 ] );
		}

		// Inven
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 4 ] = atoi( g_Buf );		// Inven Pack Num

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 5 ] = atoi( g_Buf );		// unum

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 6 ] = atoi( g_Buf );		// plus

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 7 ] = atoi( g_Buf );		// special

		///�Ź���ȭ�ý���
		arg = AnyOneArg(arg, g_Buf);
		g_ii[11] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[12] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
		arg = AnyOneArg(arg, g_Buf);
		g_ii[13] = atoi(g_Buf); // �ƽ� ��ȭ ������.

		if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[14] = atoi(g_Buf);			// �Ϲ� ������
			arg = AnyOneArg(arg, g_Buf);
			g_ii[15] = atoi(g_Buf);			// �Ϲ� ������ Max
		}

		for( int i = 0 ; i < g_ii[ 1 ] ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 8 ] = atoi( g_Buf );		// item index

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 9 ] = atoi( g_Buf );		// X

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 10 ] = atoi( g_Buf );		// Y

			// Compute
			if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
			{
				pMgr->ExchGetInven( g_ii[ 4 ], g_ii[ 8 ], g_ii[ 5 ], g_ii[ 6 ], g_ii[ 7 ], g_ii[11], g_ii[12], g_ii[13],
									g_ii[ 9 ], g_ii[ 10 ], g_ii[14], g_ii[15] ); ///�Ź���ȭ�ý���
			}
			else
			{
				pMgr->ExchGetInven( g_ii[ 4 ], g_ii[ 8 ], g_ii[ 5 ], g_ii[ 6 ], g_ii[ 7 ], g_ii[11], g_ii[12], g_ii[13],
									g_ii[ 9 ], g_ii[ 10 ], 0, 0 ); ///�Ź���ȭ�ý���
			}
		}
	}
	// Target
	else if( g_ii[ 0 ] == 1 )
	{
		for( int i = 0 ; i < g_ii[ 1 ] ; i ++ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 2 ] = atoi( g_Buf );		// X

			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 3 ] = atoi( g_Buf );		// Y

			// Compute
			pMgr->ExchGetTarget( g_ii[ 2 ], g_ii[ 3 ] );
		}
	}
}
//=================================================

//==============================================================================
// nate 2004 - 4
// CastleWar
void CmdDecardiCastleWarTime( char* arg, CUIMgr* pMgr )
{
	arg = AnyOneArg( arg, g_Buf );

	if( pMgr && pMgr->m_pLowGuildMaster )
		pMgr->m_pLowGuildMaster->SetSiegeDateString( arg );
}
//==============================================================================

//==============================================================================
// nate 2004 - 4
// CastleWar
void CmdDecardiCaslteWarGift( char* arg, CUIMgr* pMgr )
{
	if( !g_pRoh )
		return;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );

	if( g_ii[ 0 ] > 0 )
		g_pRoh->m_byShowGiftMessage = 1;
	else
		g_pRoh->m_byShowGiftMessage = 0;
}
//==============================================================================
void CmdPKItemDrop(char *arg, CUIMgr *pMgr)
{
	if( !pMgr )
		return;
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		// inven_num

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// slot_x

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 2 ] = atoi( g_Buf );		// slot_y

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 3 ] = atoi( g_Buf );		// width

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 4 ] = atoi( g_Buf );		// heith

	pMgr->PKItemDrop(g_ii[ 0 ],g_ii[ 1 ],g_ii[ 2 ],g_ii[ 3 ],g_ii[ 4 ]);
}
//--------------------------------------------------------------------------
// Firework
//--------------------------------------------------------------------------
// 2004.09.10
// Lyul / �߰�.
// �Ҳ� ǥ��.
void CmdFireWork(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		// inven_num

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// char

	if( !pCMyApp->m_pFxSet )
		return;

	// �ش� ĳ���� ã�´�.
	pCha = pMgr->FindChaById(g_ii[1], TRUE);

	EffectSort ef_sort;
	ZeroMemory(&ef_sort, sizeof(EffectSort));
	// �Ҳ� �߰�.
	if( pCha )
	{
		ef_sort.nType = FX_FIREWORKS;
		ef_sort.pNkChaTo = pCha;// g_pRoh;
		ef_sort.vPos = D3DVECTOR(pCha->m_wx, pCha->m_wy, pCha->m_wz);
		ef_sort.num =g_ii[0];
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

		pCha->InsertEffectNum( pCMyApp->m_pFxSet->InsertFxEffect(ef_sort) );
	}
}
//--------------------------------------------------------------------------
// MixItem
//--------------------------------------------------------------------------
// 2004.09.10
// Lyul / �߰�.
// ��ȯâ�� �ִ� ��� �������� ����� ���ο��� �������� �ִ´�.
void CmdMixItem(char* arg, CUIMgr* pMgr)
{
	CItem *pItem = NULL;
	CItem *nextItem = NULL;

	pItem = g_pRoh->m_ExgInven;

	//------------------------------------------------------------------------
	// Remove All
	while (pItem)
	{
		nextItem = pItem->m_Next;
		delete pItem;
		pItem = nextItem;
	}
	g_pRoh->m_ExgInven = NULL;

	int x_idx, y_idx;

	for (x_idx = 0; x_idx < EXG_SLOT_X_NUM; x_idx++)
	{
		for (y_idx = 0; y_idx < EXG_SLOT_Y_NUM; y_idx++)
			g_pRoh->m_ExgSlot[x_idx][y_idx] = -1;
	}
	//------------------------------------------------------------------------
	// ��ȯâ�� �߰�
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		// index

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// vnum

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 2 ] = atoi( g_Buf );		// slot_x

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 3 ] = atoi( g_Buf );		// slot_y

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 4 ] = atoi( g_Buf );		// gem_num

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 5 ] = atoi( g_Buf );		// special

	///�Ź���ȭ�ý���
	arg = AnyOneArg(arg, g_Buf);
	g_ii[6] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[7] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[8] = atoi(g_Buf); // �ƽ� ��ȭ ������.

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[9] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[10] = atoi(g_Buf);			// �Ϲ� ������ Max
	}

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		g_pRoh->AddToExgInven(g_ii[2], g_ii[3], g_ii[0], g_ii[1], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8], g_ii[9], g_ii[10], false); ///�Ź���ȭ�ý���
	else
		g_pRoh->AddToExgInven(g_ii[2], g_ii[3], g_ii[0], g_ii[1], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8], 0, 0 , false); ///�Ź���ȭ�ý���
}
//=====================================================================================
// nate 2004 - 9
// GuildHunt
void CmdGuildHunt( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;

	int i;
	arg = AnyOneArg( arg, g_Buf );
	if( !strcmp( g_Buf, "op" ) )
	{
		if( pMgr->m_pGuildHunt )
		{
			arg = AnyOneArg( arg, g_Buf );	// ��¥ ����
			pMgr->m_pGuildHunt->SetGuildDate( g_Buf );

			for( i = 0 ; i < 5 ; i ++ )
			{
				arg = AnyOneArg( arg, g_Buf );	// ��� �̸�
				arg = AnyOneArg( arg, g_Buf1 );	// ��û��
				arg = AnyOneArg( arg, g_Buf2 );	// ����
				g_ii[ 0 ] = atoi( g_Buf2 );

				pMgr->m_pGuildHunt->SetReservationInform( g_Buf, g_Buf1, g_ii[ 0 ], i );
			}
		}
	}
	else if( !strcmp( g_Buf, "ok" ) )
	{
		if( !g_pNk2DFrame )
			return;

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf );

		if( g_ii[ 0 ] == 0 )
			// IDS_GUH_COMP_CANCLE : ��� �Ϸ�
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_COMP_CANCLE),TYPE_NOR_OK, 1);
		else if( g_ii[ 0 ] == 1 )
			// IDS_GUH_COMP_REQ : ��û �Ϸ�
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_COMP_REQ),TYPE_NOR_OK, 1);
	}
	else if( !strcmp( g_Buf, "err" ) )
	{
		if( !g_pNk2DFrame )
			return;
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf );

		if( g_ii[ 0 ] == 0 )
			// IDS_GUH_DENIDE	: �������� ������ �����ϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_DENIDE),TYPE_NOR_OK, 1);
		else if( g_ii[ 0 ] == 1 )
			// IDS_GUH_LAIM	: �������� �γ��մϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_LAIM),TYPE_NOR_OK, 1);
		else if( g_ii[ 0 ] == 2 )
			// IDS_GUH_MIS_INFO	: ��û ������ ���� �ʽ��ϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_MIS_INFO),TYPE_NOR_OK, 1);
		else if( g_ii[ 0 ] == 3 )
		{
			// IDS_GUH_LIMIT_GU	: �� ���� 1�� 2ȸ ���̻� ������ �Ұ��� �մϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_LIMIT_GU),TYPE_NOR_OK, 1);
			SAFE_DELETE( pMgr->m_pReservationWindow );
			pMgr->m_bIsReservationWindow = FALSE;
		}
		else if( g_ii[ 0 ] == 4 )
			// IDS_GUH_LIMIT_MEMBER	: �����ο� �ʰ� �Դϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_LIMIT_MEMBER),TYPE_NOR_OK, 1);
		else if( g_ii[ 0 ] == 5 )
			// IDS_GUH_MIS_TIME	: ��û �ð��� ���� �ʽ��ϴ�.
			g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_GUH_MIS_TIME),TYPE_NOR_OK, 1);

		SAFE_DELETE( pMgr->m_pReservationWindow );
		pMgr->m_bIsReservationWindow = FALSE;
	}
}

// ��� ����� ������
void CmdGuildHuntDoor( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );	// �� ���󿩺�

	if( g_ii[ 0 ] == 0 )	// ����
		pMgr->GuildHuntLandAttr( FALSE );
	else	// ����
		pMgr->GuildHuntLandAttr( TRUE );
}
//=====================================================================================


//=====================================================================================
// nate 2004 - 10
// Decardi CastleWar
// �� ����� �������� ����, ��Ÿ �ε����� �ٸ���
// ����, �������� ����, ��Ÿ�� �ε����� ������� ������
// �Ʒ��� ������ ����, ��Ÿ �ε����� �����Ͽ�
// ������ ����, ��Ÿ ���� �ٴ�ȣ�� ���� �׸���.
void CmdDecardiGuildIndex( char* arg, CUIMgr *pMgr )
{
	if( !pMgr )
		return;
	arg = AnyOneArg( arg, g_Buf );		// ���� ���
	pMgr->SetDecardiGuildName( g_Buf, 1 );
	arg = AnyOneArg( arg, g_Buf );		// ��Ÿ ���
	pMgr->SetDecardiGuildName( g_Buf, 2 );
}
//=====================================================================================

//--------------------------------------------------------------------------
// CmdUpgradeBR
//--------------------------------------------------------------------------
// ���� ���׷��̵� ����� �޴´�.
// 2004.10.18
// Lyul / �߰�.
// ���� ���� ��ī������ ������ ����.
// 1. �߰��� �����Ǹ� Extra Slot �� ������ �����.
// 2. �������� �߰��� �Ǹ� �Ӽ��� �������� �ش�.
// 3. �߰��� �� ������ ������ �˸��� pick_up ���� �ٽ�Extra Slot �� ��� �ش�.
// 4. ��� �� ��쿡�� �׳� ��� �ش�.
// 5. �� �Լ����� �������� ���� ���� ��� ���� ����̴�.
void CmdUpgradeBR(char* arg, CUIMgr *pMgr )
{
	CItem *pItem = g_pRoh->m_Wearing[IARMOR_BRACELET];

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		// result

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// Item_Flag

	pCMyApp->m_bBrLock= FALSE;// ���� �� ����

	for(int i=0; i<=5; i++)
		if( g_pRoh )
			g_pRoh->m_bQuickSlotLock[i] = FALSE;

	// ����.
	if(g_ii[0] ==1)
	{
		if( pMgr
				&& g_pNk2DFrame
				&& g_pNk2DFrame->GetControlInven() )
		{
			g_pNk2DFrame->GetControlInven()->ResetItemInfo();
			pMgr->SetBRFalg(pItem, g_ii[1]);
		}
	}
	// ������.
	if(g_ii[0] == -1)
		if( g_pRoh )
			SAFE_DELETE(g_pRoh->m_Wearing[IARMOR_BRACELET]);
}

// nate 2004 - 11 : Hack Program Check
void CmdHackCheck( char* arg, CUIMgr* pMgr )
{
	arg = AnyOneArg( arg, g_Buf );
	if( !strcmp( g_Buf, "go_world" ) )
	{
		pCMyApp->m_bBeforeGoWorld = FALSE;		
	}
}

// ����� ���濡 ���� ó���� �Ѵ�.
void CmdDstone( char* arg, CUIMgr* pMgr )
{
	float x,z;
	float dir;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		// flag

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		// char idx

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 2 ] = atoi( g_Buf );		// Mob idx

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 3 ] = atoi( g_Buf );		// Mob Vunm

	arg = AnyOneArg( arg, g_Buf );
	dir = atof( g_Buf );			// char dir
	dir /=10.0f;

	arg = AnyOneArg( arg, g_Buf );
	x = atof( g_Buf );				// char x

	arg = AnyOneArg( arg, g_Buf );
	z = atof( g_Buf );				// char z

	// �ش� ĳ���� ã�´�.
	pCha = pMgr->FindChaById(g_ii[1], FALSE);

	// ����
	// �� ���������� ��������� �ʰ� �ش� ĳ���� FrameMove ���� ���������.����!!
	if(g_ii[0])
	{
		// �ش� ĳ���� ����� ������ �����Ѵ�.
		if(pCha && pCha->m_Wearing[WEARING_CLOAK])
		{
			// Motion
			pCha->m_dir = dir;
			pCha->m_wx = x;
			pCha->m_wz = z;
			pCha->SetMotionState(CHA_F_DSTONE);

			// Effect
			pMgr->InsertMagic(pCha, NULL, pCha, NULL, SKILLF_A_DSTONE);

			// Add mob (char)
			pCha->m_bresstone = true;    // ����� ������ ������ �غ� �ƴ°�.
			pCha->m_resmobidx = g_ii[2];    // ������ ���� �ε���
			pCha->m_resmobvnum = g_ii[3];   // ������ ���� vnum
			pCha->m_resmobx =x + cos(dir)  * 15.0f;	  // ������ ���� ��ǥ
			pCha->m_resmobz =z + sin(dir)  * 15.0f;
			pCha->m_resmobdir = dir;
		}
		// �÷��̾��� ��
		else if(g_ii[1] == g_pRoh->m_nCharIndex)
		{
			// Add mob (player)
			g_pRoh->m_bresstone = true;    // ����� ������ ������ �غ� �ƴ°�.
			g_pRoh->m_resmobidx = g_ii[2];    // ������ ���� �ε���
			g_pRoh->m_resmobvnum = g_ii[3];   // ������ ���� vnum
			g_pRoh->m_resmobx =x + cos(dir)  * 15.0f;	  // ������ ���� ��ǥ
			g_pRoh->m_resmobz =z + sin(dir)  * 15.0f;
			g_pRoh->m_resmobdir = dir;
			int cur_skill = g_pNk2DFrame->GetRSkill();
			G_SK_SetCooltime(SKILLF_A_DSTONE);
		}
	}
	// ����
	else
	{
		if(g_ii[1]  == g_pRoh->m_nCharIndex) // �÷��̾�
		{
			pMgr->DelMob(g_ii[2]);
			g_pRoh->m_bresstone = false;
			g_pRoh->m_bstone = false;

			G_SK_INVCooltime(SKILLF_A_DSTONE);
		}
		else // �ٸ� ����
		{
			pMgr->DelMob(g_ii[2]);
			if(pCha)
				pCha->m_bresstone = false;
			if(pCha)
				pCha->m_bstone = false;
		}
	}
}

//wan:2004-12 ��������
void CmdSeMs(char *arg, CUIMgr *pMgr)
{
	if( !g_pRoh || !pMgr )
		return;

	arg = AnyOneArg(arg, g_Buf);

	if (!strcmp(g_Buf, "success"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf); // clear falg
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf); // index
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf); // vnum
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf); // x
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf); // y

		if(g_ii[1])	//Ŭ����
		{
			CItem *pItem = NULL;
			CItem *nextItem = NULL;
			pItem = g_pRoh->m_ExgInven;

			// Remove All
			while (pItem)
			{
				nextItem = pItem->m_Next;
				delete pItem;
				pItem = nextItem;
			}
			g_pRoh->m_ExgInven = NULL;

			int x_idx, y_idx;

			for (x_idx = 0; x_idx < EXG_SLOT_X_NUM; x_idx++)
			{
				for (y_idx = 0; y_idx < EXG_SLOT_Y_NUM; y_idx++)
					g_pRoh->m_ExgSlot[x_idx][y_idx] = -1;
			}
		}
		//������ ����
		g_pRoh->AddToExgInven(g_ii[4], g_ii[5], g_ii[2],  g_ii[3], 0, 0, 0, 0, 0, 0, FALSE); ///�Ź���ȭ�ý���
	}
	else if (!strcmp(g_Buf, "cancel"))
		pMgr->MsFail();
}
//==========================================================
//wan:2004-12	ȭ��Ʈȥ ���� �߾ӱ��� Ÿ�� ��
void CmdShopOpen(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	if ( pMgr
			&& g_pNk2DFrame
			&& !strcmp(g_Buf, "0"))
		g_pNk2DFrame->ShowShopWindow(FALSE);
}

//==========================================================
// nate 2005-03-18
// Matrix
// ��Ʈ���� : �̴ϸ� ���� ����Ʈ ���
void CmdMini( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;
	arg = AnyOneArg( arg, g_Buf );	// X ��ǥ
	g_ii[ 0 ] = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// Y ��ǥ
	g_ii[ 1 ] = atoi( g_Buf );

	if( g_pNk2DFrame
			&& g_pNk2DFrame->GetInterface(MAP) )
	{
		((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_bIndication_Point = 2;
		((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_dwTimeIndication = timeGetTime();
		((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_nCurClick_X = ((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_minimap_x + g_ii[ 0 ];
		((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_nCurClick_Y = ((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_minimap_y + g_ii[ 1 ];

		g_pNk2DFrame->AddChatStr( arg, 6 );	// arg : �����ڰ� ��ġ����� �Ͽ����ϴ�.
	}

	if (g_pDSound)
		g_pDSound->Play(g_EffectSound[EFF_SND_MINI]); // ���� ������ �Ŀ� �ٲ�����.
}
//==========================================================

void CmdMatBP(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );//���� ȹ�� BP
	arg = AnyOneArg(arg, g_Buf);
	g_ii[ 1 ] = atoi(g_Buf); // ���� BP
	arg = AnyOneArg(arg, g_Buf);
	g_ii[ 2 ] = atoi(g_Buf); // GHP

	if( pMgr )
		pMgr->MatBattlePoint( g_ii[ 0 ] );// ���� BP ���

	if( g_pRoh )
	{
		g_pRoh->SetBattlePoint(g_ii[ 1 ]);// ���� BP ����
		g_pRoh->SetGHPoint(g_ii[ 2 ]);// ���� GHP ����
	}

	// ���� ������ ���� ������ ������ �� ǥ�úκ��� ���� ���ش�.(BP������ ��� �ڽ��� BP�ܷ� ������ ���ؼ�) (by ����)
	if( pMgr
			&& g_pNk2DFrame
			&& g_pNk2DFrame->IsShopVisible() )
		g_pNk2DFrame->GetControlShop()->SetMoney();  // ��� ���� ������ ���� ���⼭ �����൵ �Ǳ��Ѵ�.
}


//wan:2005-03 wan_mat
//��Ʈ���� ��Ʋ ��ŸƮ, ����(win,lose)
void CmdBattle(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "start"))
		pCMyApp->CreateBattleStart(2);
	else if(!strcmp(g_Buf,"end"))
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf );
		pCMyApp->CreateBattleStart(g_ii[ 0 ]);
	}
	else if(!strcmp(g_Buf,"cancel")) // ī��Ʈ ��� ///�δ�1
	{
		pCMyApp->DeleteBattleStart();
		pCMyApp->DrawBattleStart = FALSE;
	}
}

// nate 2005-04-22 : �޺� ����ϱ�
void CmdCombo( char* arg, CUIMgr* pMgr )
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );
	arg = AnyOneArg(arg, g_Buf);
	g_ii[ 1 ] = atoi(g_Buf);		//������ ������.

	pMgr->ComputeCombo( g_ii[ 0 ], g_ii[ 1 ] );
}

// nate 2005-05-09 : �̺�Ʈ����Ʈ(EP)ȹ��� ���� �޼����� ���� ��Ÿ��
void CmdEventPoint( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;
	arg = AnyOneArg( arg, g_Buf1 );	// ĳ�� �ε���
	g_ii[ 0 ] = atoi( g_Buf1 );

	pMgr->ComputeEventPoint( g_ii[ 0 ] );
}

void CmdItemExtraInfo( char* arg, CUIMgr* pMgr ) // ������ ���� �߰����� ������ �ʿ��� �� ���Ǵ� ��Ŷ. �ð��� �����۵� �� ��Ŷ���� ������ �´�.(by ����) ///�ð���������
{
	arg = AnyOneArg( arg, g_Buf );

	if( !strcmp(g_Buf,"remain") ) // ���� �ð� ��Ŷ.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf ); // ������ �ε���.(������ȣ)

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf ); // ���� �ð� �ʴ���.

		if( pMgr )
			pMgr->SetItemTimeLimit( g_ii[0], g_ii[1] ); // �ð��� ������ ����.		
	}
	else if( !strcmp(g_Buf,"del") ) // �ð� ����� ������ ����.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf ); // ������ �ε���.(������ȣ)

		if( g_pRoh )
		{
			CItem *pItem = g_pRoh->FindItemByIndexFromAll( g_ii[0] );
			if( pItem ) // �������� Ȯ���� �ִٸ�..
			{
				if( pItem->m_bTimeLimit ) // �ð��� �����۸� ������ٴ� �޼��� ����ϰ� ���� 07-04-18 ///�����Ǹ�
				{
					char temp[256];
					sprintf( temp, (char*)G_STRING(IDS_ITEM_REMOVED), GET_ITEM_NAME_VNUM(pItem->m_Vnum) );
					g_pNk2DFrame->AddChatStr( temp, -1 );
				}

				g_pRoh->RemoveByIndex( g_ii[0] ); // 06-05-09 ��ġ���� ����.
				g_pRoh->CountQuickAll(); // ������ �������� �־��� ���� ������ �ٽ� �����ش�. RemoveByIndex() ���ʿ��� �ϱ�� �� ������ �ִ�. ///07-05-31
			}
		}
	}
	else if( !strcmp(g_Buf,"price") ) // Ư������ ����.(�Ӽ� �÷��׿� Ư���������� ���������� ���ΰ� ǥ�õǾ��ִ�.)
	{
		// ���⼭ �Ӽ� �÷��׸� üũ���ִ� �͵� ����.

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf ); // ������ �ε���.(������ȣ)

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf ); // ����Ÿ�� ��, ����(0), BP(1) ���� �´�.

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 2 ] = atoi( g_Buf ); // ���� ��.

		if( pMgr )
			pMgr->SetItemExPrice( g_ii[0], g_ii[1], g_ii[2] ); // Ư�������� �����Ѵ�.
	}
	else if( !strcmp(g_Buf,"all") ) // �ð��� �̸鼭 ���� ���� �������� ���. ��Ŷ�� �ι� �ޱ� ���ϴϱ� �ѹ��� �޴´�.(�α��ε��� ��쿡�� ������ �ɷ�. ���� remain���� �ణ Ʋ����. �� �༮�� �ð��� �������̴� ��� ���� �˷��ֱ� ���� ���δٰ� ����ɵ�.)
	{
		if( !pMgr )
			return;

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 0 ] = atoi( g_Buf ); // ������ �ε���.(������ȣ)

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf ); // ���� �ð� �ʴ���.

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 2 ] = atoi( g_Buf ); // ����Ÿ�� ��, ����(0), BP(1) ���� �´�.

		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 3 ] = atoi( g_Buf ); // ���� ��.

		if( g_ii[1] != 0 )
			pMgr->SetItemTimeLimit( g_ii[0], g_ii[1] ); // �ð��� ������ ����.

		pMgr->SetItemExPrice( g_ii[0], g_ii[2], g_ii[3] ); // Ư�������� �����Ѵ�.
	}

	if( g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
	{
		g_pNk2DFrame->GetControlInven()->m_bDrawInfoUpdate = TRUE;
	}
}

// nate 2005-07-08 : Summon Squad - �������� ���޹��� �޼��� ó��
void CmdSquad( char* arg, CUIMgr* pMgr )
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf );	// Char Index
	g_ii[ 0 ] = atoi( g_Buf );

	pCha = pMgr->FindChaById(g_ii[0], TRUE);
	if( pCha )
		pMgr->InsertMagic( pCha, NULL, NULL, NULL, EFFECT_SKILL_SUMMONSQUAD );
}


void CmdUpdateItem( char* arg, CUIMgr* pMgr )	// ������ ���� ���ſ� ���� ��Ŷ(05-10-21). ///�Ź���ȭ�ý���
{
	if( !pMgr )
		return;

	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf ); // �ε���

	arg = AnyOneArg( arg, g_Buf );
	g_ii[1] = atoi( g_Buf ); // vnum

	arg = AnyOneArg( arg, g_Buf );
	g_ii[2] = atoi( g_Buf ); // plus

	arg = AnyOneArg( arg, g_Buf );
	g_ii[3] = atoi( g_Buf ); // special

	arg = AnyOneArg( arg, g_Buf );
	g_ii[4] = atoi( g_Buf ); // special2

	arg = AnyOneArg( arg, g_Buf );
	g_ii[5] = atoi( g_Buf ); // ��ȭ ������ ����ġ

	arg = AnyOneArg( arg, g_Buf );
	g_ii[6] = atoi( g_Buf ); // ��ȭ ������ �ƽ�ġ

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[7] = atoi( g_Buf );		// �Ϲ� ������
		arg = AnyOneArg( arg, g_Buf );
		g_ii[8] = atoi( g_Buf );		// �Ϲ� ������ Max
	}

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		pMgr->UpdateItem( g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8] );
	else
		pMgr->UpdateItem( g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], 0, 0 );
}

void CmdNpcUpgrade(  char* arg, CUIMgr* pMgr ) // ��ȭ,��ȯ,���� �� NPC�� ���� ���׷��̵� ��Ŷ. ///�Ź���ȭ�ý���
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetUpgrade() )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ��ȭ �ִϸ��̼����� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_ING;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].m_AniType = SPRITE_ANITYPE_LOOP; // ��ȭ�� �ִϸ��̼��� ���� �ݺ����� ����.
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].SetStart(); // �ִϸ��̼� ����.
	g_pNk2DFrame->GetUpgrade()->m_dwStartTickTime = timeGetTime(); // �ִϸ��̼��� ���۵� �ð��� ���.

	switch( pCMyApp->GetCurWorld() )
	{
	case 4:
		if( !strcmp(g_Buf,"armor") || !strcmp(g_Buf,"weapon") || !strcmp(g_Buf,"conv") || !strcmp(g_Buf,"reload") || !strcmp(g_Buf,"refine")) // ��ȭ,����,��ȯ�� ����..
		{
			arg = AnyOneArg( arg, g_Buf ); // �����.

			// ���⼭ ������� ����صд�.
			if( !strcmp(g_Buf,"succ") )
			{
				g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS; // �ִϻ��� �������� �״�� �־ �ȴ�.(�����ϰ� ���缭 ���.)
			}
			else if( !strcmp(g_Buf,"fail") )
			{
				g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_FAIL;
			}
			else if( !strcmp(g_Buf,"brk") )
			{
				g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_BROKEN;
			}
			else if( !strcmp(g_Buf,"error") ) // ���� �̻��� ���� ���. �ִϸ��̼��� ������ �ʰ� �ʱ�ȭ �Ѵ�.
			{
				g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_Result = 0; // ����� �ʱ�ȭ...
			}
			else if( !strcmp(g_Buf, "check") )
			{
				g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_Result = 0; // ����� �ʱ�ȭ...

				arg = AnyOneArg( arg, g_Buf );
				int type = atoi(g_Buf);
				if( 1 == type )
				{
					g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_UPGRADE_11_WARNING),TYPE_NOR_OKCANCLE, POPUP_NPCUPGRADE_BROKEN_CHECK);
				}
				else if( 2 == type )
				{
					g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_LHSTRING1955),TYPE_NOR_OKCANCLE, POPUP_NPCUPGRADE_BROKEN_CHECK);
				}
			}

			if( g_pNk2DFrame->GetControlInven() )
			{
				g_pNk2DFrame->GetControlInven()->m_bDrawInfoUpdate = TRUE; // DrawItemInfo() ���� ������Ʈ.
			}
		}
		break;

		// ��Ʈ�� �߰�

	case 7:
		if( !strcmp(g_Buf,"conv") || !strcmp(g_Buf,"weapon") || !strcmp(g_Buf,"godpower") )
		{
			arg = AnyOneArg( arg, g_Buf ); // �����.

			if( !strcmp(g_Buf,"succ") )
			{
				g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS; // �ִϻ��� �������� �״�� �־ �ȴ�.(�����ϰ� ���缭 ���.)
			}
			else if( !strcmp(g_Buf,"fail") )
			{
				g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_FAIL;
			}
			else if( !strcmp(g_Buf,"brk") )
			{
				g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_BROKEN;
			}
			else if( !strcmp(g_Buf,"error") || !strcmp(g_Buf,"unsuccessful") ) // ���� �̻��� ���� ���. �ִϸ��̼��� ������ �ʰ� �ʱ�ȭ �Ѵ�.
			{
				g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
				g_pNk2DFrame->GetUpgrade()->m_Result = 0; // ����� �ʱ�ȭ...
			}

			if( g_pNk2DFrame->GetControlInven() )
			{
				g_pNk2DFrame->GetControlInven()->m_bDrawInfoUpdate = TRUE; // DrawItemInfo() ���� ������Ʈ.
			}
		}
		break;
	}


}

void CmdGuildPos( char* arg, CUIMgr* pMgr ) // ���� ��ġ ã�� ��Ŷ. ///�̴ϸʱ���ã��
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetInterface(MAP) )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ���⼭ ������� ����صд�.
	if( !strcmp(g_Buf,"start") )
	{
		((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->GuildFindTick = timeGetTime(); // �ð� ����. �� �ð��� �������� ����Ѵ�. Ÿ�̹��� �߿��ϴ�.

		// ����Ʈ �ʱ�ȭ.  ///�̴ϸʱ���ã��3D
		vector<sGuildPosInfo>::iterator prGuildPosVector;
		prGuildPosVector = ((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_GuildPosVector.begin();
		while( prGuildPosVector != ((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_GuildPosVector.end() )
		{
			prGuildPosVector = ((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_GuildPosVector.erase( prGuildPosVector );
		}
	}
	else if( !strcmp(g_Buf,"body") ) // ����
	{
		sGuildPosInfo TempInfo;

		arg = AnyOneArg( arg, g_Buf );
		TempInfo.m_Grade = atoi( g_Buf ); // ��� ���.

		arg = AnyOneArg( arg, g_Buf );
		strcpy( TempInfo.m_strName, g_Buf ); // ĳ���͸�.

		arg = AnyOneArg( arg, g_Buf );
		TempInfo.m_PosX = atoi( g_Buf ); // x ��ǥ.

		arg = AnyOneArg( arg, g_Buf );
		TempInfo.m_PosY = atoi( g_Buf ); // y ��ǥ

		// ����ִ´�.
		((CControlMap*)g_pNk2DFrame->GetInterface(MAP))->m_GuildPosVector.push_back( TempInfo ); // ���� ����־���Ѵ�.
	}
	else if( !strcmp(g_Buf,"end") )
	{
		/*      ///07-04-10 ����ã�� �׽�Ʈ��.
				// �ӽ� �׽�Ʈ.
				if( g_pTcpIp )
				{
					char strTemp[200];

					sprintf( strTemp, "callback m g_pos start\n" ); // �Ҽ� ��E?�̰� ��������ϴ���E
					g_pTcpIp->SendNetMessage( strTemp );
					sprintf( strTemp, "callback m g_pos body 1 a %d %d\n", (int)g_pRoh->m_wx, (int)g_pRoh->m_wz ); // �Ҽ� ��E?�̰� ��������ϴ���E
					g_pTcpIp->SendNetMessage( strTemp );
				}
		*/
	}
}

void CmdFillItem( char* arg, CUIMgr* pMgr ) // ������ ������ ��Ŷ. (��ȭ ������ ���� ������ �׷����� ���� �̰� ����ϱ�� ��.) ///�׷�����
{
	if( !pMgr || !pCMyApp )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// �̰� ���� ���и� �ִ�. (���� �ٸ� �� ��Ŷ�� ����ϴ� �������� ���ý� ����/���� ���� Ÿ�Ե� �߰��ؼ� ó��������.)
	if( !strcmp(g_Buf,"succ") )
	{
		// ������ ������ ���� ������ ���ش�.
		if( pMgr && g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
			g_pNk2DFrame->GetControlInven()->ResetItemInfo();
	}
	else if( !strcmp(g_Buf,"fail") )
	{
		// ������ �޼����� ��� �ϴ� �޼��� ����.
	}

}

void CmdMvSkill( char* arg, CUIMgr* pMgr )
{

	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf );		//��ų �ε���

	if( g_ii[ 0 ] == SKILL_KNOCKBACK2 ) // ���Ǹ� �˹�ó��. ������ �˹鵵 �����ϴ�. ��Ŷ ������ �ٸ� �༮�� Ʋ������ ���⿡�� ���� �˻�.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[ 1 ] = atoi( g_Buf );		//��ų ����� �ε���

		pCha = pMgr->FindChaById(g_ii[1], TRUE);
		if( !pCha ) return;

		if( pCha->m_nCharIndex == g_pRoh->m_nCharIndex )	// ���Ǹ��� �ߵ��� ĳ���� ��ĳ���� ���
		{
			// �˹��� ������ �����ش�.
			pMgr->m_b_MotionForAttack = false;
			pMgr->m_b_MovingForAttack= false;
			pMgr->m_b_Attack= false;
			pMgr->m_b_SecAttack = false;
			pMgr->m_bChakramAtt = false;
			pMgr->m_bChakram = false;
			pMgr->m_bBookSpellAtt = false;
			pMgr->m_bBookSpell = false;

			// 06-05-25 ���� ĵ�� �ʱ�ȭ �߰�.
			pCha->m_MagicChaId[0] = -1;
			pCha->m_MagicMobId[0] =  -1;
			pCha->m_MagicChaCount = 0;
			pCha->m_MagicMobCount = 0;
			pCha->m_AttackChaId = -1;
			pCha->m_AttackMobId = -1;

			pCMyApp->SetHeroAttGoMob( NULL ); // ���� ��� �����͸� �ʱ�ȭ(�� �ȿ��� ���ݴ�� �� �ܿ� ĳ���͵� �ʱ�ȭ �ȴ�.)
		}

		arg = AnyOneArg( arg, g_Buf );
		g_ii[1] = atoi( g_Buf );  // �˹� ����� ����.

		for( int i = 0 ; i < g_ii[1] ; ++i ) // �˹� ��� ��ŭ ����.
		{
			arg = AnyOneArg( arg, g_Buf2 );	//npc/char(Ÿ��)
			arg = AnyOneArg( arg, g_Buf );	//Ÿ�� �ε���
			g_ii[2] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );
			float x = atof( g_Buf );		// x	//�̵��� X��ǥ
			arg = AnyOneArg( arg, g_Buf );
			float z = atof( g_Buf );		// z	//�̵��� Z��ǥ

			if( !strcmp(g_Buf2,"n") ) // Ÿ���� ���� ���
			{
				pMob = pMgr->FindMobById( g_ii[2] );

				if( pMob )
					pMob->MoveSkill(x, z, g_ii[0] );
			}
			else
			{
				pCha2 = pMgr->FindChaById( g_ii[2], TRUE );

				if( pCha2 )
					pCha2->MoveSkill(x, z, g_ii[0] );
			}
		}


		return;
	}


	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 1 ] = atoi( g_Buf );		//��ų ����� �ε���
	arg = AnyOneArg( arg, g_Buf2 );	//npc/char(Ÿ��)
	arg = AnyOneArg( arg, g_Buf );	//Ÿ�� �ε���
	g_ii[ 2 ] = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );
	float x = atof( g_Buf );		// x	//�̵��� X��ǥ
	arg = AnyOneArg( arg, g_Buf );
	float z = atof( g_Buf );		// z	//�̵��� Z��ǥ
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 3 ] = atof( g_Buf );		//����

	pCha = pMgr->FindChaById(g_ii[1], TRUE);
	if( !pCha ) return;

	if( g_ii[ 0 ] == SKILL_KNOCKBACK ) // �˹� ó�� ///��
	{
		if( pCha->m_nCharIndex == g_pRoh->m_nCharIndex )	// ��ĳ���� ���
		{
			// �˹��� ������ �����ش�.
			pMgr->m_b_MotionForAttack = false;
			pMgr->m_b_MovingForAttack= false;
			pMgr->m_b_Attack= false;
			pMgr->m_b_SecAttack = false;
			pMgr->m_bChakramAtt = false;
			pMgr->m_bChakram = false;
			pMgr->m_bBookSpellAtt = false;
			pMgr->m_bBookSpell = false;

			// 06-05-25 ���� ĵ�� �ʱ�ȭ �߰�.
			pCha->m_MagicChaId[0] = -1;
			pCha->m_MagicMobId[0] =  -1;
			pCha->m_MagicChaCount = 0;
			pCha->m_MagicMobCount = 0;
			pCha->m_AttackChaId = -1;
			pCha->m_AttackMobId = -1;

			pCMyApp->SetHeroAttGoMob( NULL ); // ���� ��� �����͸� �ʱ�ȭ(�� �ȿ��� ���ݴ�� �� �ܿ� ĳ���͵� �ʱ�ȭ �ȴ�.)
		}
		pCha->MoveSkill(x, z, g_ii[ 0 ]);

		return;
	}

	if( g_ii[ 0 ] != SKILLF_A_DASH )	// �뽬�� Ÿ�� ���� ����
	{
		if(!strcmp(g_Buf2,"n"))
			pCha->SetAttackMobId(g_ii[ 2 ]);
		else
			pCha->SetAttackChaId(g_ii[ 2 ]);
	}

	if( pCha->m_nCharIndex == g_pRoh->m_nCharIndex )	// ��ĳ���� ���
	{
		if( g_ii[ 0 ] != SKILL_B_FLYINGCRASH ) // �ö���ũ������ ��� �� �߻��� �ߺ������ �Ǵ°Ͷ��� ���� ��Ÿ�ӵ������ �ٲپ���. 07-03-22 ����
			G_SK_SetCooltime(g_ii[ 0 ]);

		if( g_ii[ 0 ] != SKILLF_A_DASH )
		{
			pMgr->m_b_MotionForAttack = true;
			pMgr->m_b_MovingForAttack= false;
			pMgr->m_b_Attack= true;
			pMgr->m_b_SecAttack = false;
		}
		else
		{
			//���� ��Ȱ�� ��Ų��.
			pMgr->m_b_MotionForAttack = false;
			pMgr->m_b_MovingForAttack= false;
			pMgr->m_b_Attack= false;
			pMgr->m_b_SecAttack = false;
		}

		if( g_ii[0] == SKILLF_A_DASH ) ///�����޺�
		{
			// �޺���ų üũ�� ƽ�� ����.
			pCha->m_dwComboTick = timeGetTime();
		}

	}

	pCha->MoveSkill(x, z, g_ii[ 0 ]);
	if( g_ii[ 0 ] == SKILL_B_FLYINGCRASH )
		pCMyApp->m_pUIMgr->InsertMagic( pCha, NULL, NULL, NULL, EFFECT_SKILL_FLYINGCRASH2 );
	else if( g_ii[ 0 ] == SKILL_F_SHADOWSLASH )
		pCMyApp->m_pUIMgr->InsertMagic( pCha, NULL, NULL, NULL, EFFECT_SKILL_SHADOWSLASH );
}

void CmdUserShop( char* arg, CUIMgr* pMgr ) ///���λ���
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetControlUserShop() )
		return;

	char strTemp[200];
	int i = 0;
	__int64 ii64;

	arg = AnyOneArg( arg, g_Buf ); // ��Ŷ ����

	// ���⼭ ������� ����صд�.
	if( !strcmp(g_Buf,"in") ) // �þ� �� ĳ���Ͱ� ������ ������. �Ǵ� �þ� ������...
	{
		arg = AnyOneArg( arg, g_Buf2 ); // ĳ�������� npc����...

		if( !strcmp(g_Buf2,"c") ) // ���� ����.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[0] = atoi( g_Buf ); // ĳ���� �ε���

			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ���� ����.

			pCha = pMgr->FindChaById( g_ii[0], FALSE );
			if( pCha )
			{
				pCha->m_UserShopLevel = g_ii[1];

				strcpy( pCha->m_strUserShopMent, arg ); // m_strUserShopMent�� ���۱��̴� g_Buf�� ���̿� �Ȱ��� 256���� �����Ǿ��ִ�.��Ʈ�� �Ѱ���̸� 200������ ����.

				// ��Ʈ ��µ��� ���� �˾� ��ü�� �����Ѵ�.
				if( pCha->m_pUserShopPopup )
				{
					CMultiText multiText;
					char strTemp[100];

					//-- IDS_WHOS_USERSHOP : %s�� ���λ���
					sprintf( strTemp, (char*)G_STRING(IDS_WHOS_USERSHOP), pCha->m_pstrName );
					multiText.AddString( strTemp, RGB(252, 180, 180) );
					// ���ڿ��� �������E������ �����鼭 ���.
					// ���ڿ� ���̸� 15���� 35���� �÷� ����غ���. [2/8/2007 Theodoric]
					multiText.AddStringMulti( pCha->m_strUserShopMent, 15, TRUE, RGB(255, 251, 115) );
					pCha->m_pUserShopPopup->PutString(&multiText, TRUE);
				}
			}
		}
		else if( !strcmp(g_Buf2,"n") ) // ���� ����.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[0] = atoi( g_Buf ); // �������� ĳ���� �ε���

			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // Vnum

			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf ); // NpcIndex

			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf ); // x

			arg = AnyOneArg( arg, g_Buf );
			g_ii[4] = atoi( g_Buf ); // z

			arg = AnyOneArg( arg, g_Buf );
			g_ii[5] = atof(g_Buf); // dir

			arg = AnyOneArg( arg, strTemp ); // �̸�. (arg�� ������ ��Ʈ�� ������� )

			pMgr->AddUserShopNpc( g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], strTemp, arg );
		}
	}
	else if( !strcmp(g_Buf,"out") ) // �þ� �� ĳ���Ͱ� ������ ����.�Ǵ� �þ� ������...
	{
		arg = AnyOneArg( arg, g_Buf );

		if( !strcmp(g_Buf,"c") ) // ���� ����.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[0] = atoi( g_Buf ); // �ε���

			pCha = pMgr->FindChaById( g_ii[0], FALSE );
			if( pCha )
			{
				pCha->m_UserShopLevel = 0;
			}
		}
		else if( !strcmp(g_Buf,"n") ) // ���� ����.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[0] = atoi( g_Buf ); // �ε���

			pMgr->DeleteUserShopNpc( g_ii[0] );
		}
	}
	else if( !strcmp(g_Buf,"open") ) // ���� Ȯ��.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����

		if( g_ii[0] ) // ����
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ĳ���� �ε��� -1�̸� �ڱ��ڽ� ���λ��� ����. �ڱ� �ڽ� �ε��� �� �ڱ��ڽ� �������� �����̴�.

			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf ); // ������������ ���λ������� �÷���.(����μ� Ŭ���̾�Ʈ�� �Ű� �Ƚᵵ �ȴ�.) ���� 0, ���� 1

			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf ); // ���� �׷��̵�. �� �¥�� �����ΰ�? �������� 0,1,2 �� �����ִ� +1�ؼ� ����.

			g_pNk2DFrame->ToggleUserShopWindow( g_ii[1], g_ii[2], g_ii[3]+1 ); // ������ �����ش�.

			// ����ִ´�.
			if( g_ii[1] == -1 && g_ii[2] == 0 ) // �Ǹ����� ���.(���� ����) ///��������
			{
				// �ʰ� �ϱ� ó��...
				if (g_pRoh
//					&& !(g_pRoh->IsCantMove()) // ������������ üũ�ϴ� ���ε� �������̴��� ������ ���߰� ����.
						&& !(pCMyApp->GetHeroSwimming())
						&& g_pRoh->IsShown()
				   )
				{
					// ���� �������̸� ��������. (������ ������Ű�� ��ŭ ���� �L�� �������� �ִ�.)
					if( pMgr->m_b_Attack || pMgr->m_b_SecAttack || pMgr->m_bChakramAtt || pMgr->m_bBookSpellAtt )
					{
						pMgr->m_b_Attack = false;
						pMgr->m_b_MovingForAttack = false;
						pMgr->m_b_SecAttack = false;
						pMgr->m_bChakramAtt = false;
						pMgr->m_bChakram = false;
						pMgr->m_bBookSpellAtt = false;
						pMgr->m_bBookSpell = false;
					}

					pCMyApp->StopHero();

					g_pRoh->SetMotionState(CHA_SOCIAL, 67 );
					if( g_pTcpIp )
					{
						sprintf( strTemp, "combat 0\n" ); // �Ҽ� ���� �̰� ��������ϴ���.
						g_pTcpIp->SendNetMessage( strTemp );
						sprintf( strTemp, "social 67\n" );
						g_pTcpIp->SendNetMessage( strTemp );
					}
				}
			}

//			g_pNk2DFrame->GetControlUserShop()->m_bOpened = TRUE; // ShowUserShop()���� �ϵ��� ����.
		}
	}
	else if( !strcmp(g_Buf,"reg") ) // ������ �ֱ�. Ŭ���̾�Ʈ���� ��û�ѰͿ����� �������� �亯,�̰� �����Ŀ� ������ �Ű��ش�.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����

		if( g_ii[0] ) // ����
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ��� ��ȣ

			arg = AnyOneArg( arg, g_Buf );
			g_ii[7] = atoi( g_Buf ); // �ݱ�

			arg = AnyOneArg( arg, g_Buf );
			g_ii[8] = atoi( g_Buf ); // ����

			arg = AnyOneArg( arg, g_Buf );
			g_ii[9] = atoi( g_Buf ); // ����

			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf ); // ��� ����

			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf ); // �κ� �� ��ȣ.

			arg = AnyOneArg( arg, g_Buf );
			g_ii[4] = atoi( g_Buf ); // ��� ����

			BOOL bSlotInResult = TRUE; // ����� ����

			for( i = 0 ; i < g_ii[4] ; ++i )
			{
				arg = AnyOneArg( arg, g_Buf );
				g_ii[5] = atoi( g_Buf ); // �κ� x

				arg = AnyOneArg( arg, g_Buf );
				g_ii[6] = atoi( g_Buf ); // �κ� y

				bSlotInResult = g_pNk2DFrame->GetControlUserShop()->SlotIn( g_ii[1], g_ii[7], g_ii[8], g_ii[9], g_ii[2], g_ii[3], g_ii[5], g_ii[6] );
			}

			if( !bSlotInResult ) // ���� �����ߴٸ�...
			{
				// ������ ��Ŷ�� ������ �ֽ� ������ �������ٰ��� �䱸�Ѵ�.
				if( g_pTcpIp )
				{
					sprintf(strTemp, "u_shop refresh req 1 %d %d %d %d %d %d %d %d \n",  g_ii[1], g_ii[7], g_ii[8], g_ii[9], g_ii[2], g_ii[3], g_ii[5], g_ii[6]);
					g_pTcpIp->SendNetMessage( strTemp );
				}
			}


			if( pCMyApp && g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
				g_pNk2DFrame->GetControlInven()->ResetItemInfo(); // DrawItemInfo()�� ����.
		}
		else // ����. �ڿ� ���� �ε����� �´�.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ���� �ڵ�

			switch( g_ii[1] )
			{
			case -4: // ���Կ� ���� �� ���� ��û�ΰ��.(���������̳� �ٸ� ������.)

				//-- IDS_CHECK_ITEM : �������� Ȯ���� �ּ���!
				pMgr->CmdErrorMsg( (char*)G_STRING(IDS_CHECK_ITEM) );

				break;
			}
		}

		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"unreg") ) // ������ ����. Ŭ���̾�Ʈ���� ��û�ѰͿ����� �������� �亯,�̰� �����Ŀ� ������ �Ű��ش�.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����

		if( g_ii[0] ) // ����
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ��� ��ȣ

//			arg = AnyOneArg( arg, g_Buf );
//			g_ii[2] = atoi( g_Buf ); // �κ� �� ��ȣ.

			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf ); // ��� ����

			if( !g_pNk2DFrame->GetControlUserShop()->SlotOut( g_ii[1], g_ii[3] ) ) // ī��Ʈ�� �ٿ��ִ� �Լ�.
			{
				// ������ ��Ŷ�� ������ �ֽ� ������ �������ٰ��� �䱸�Ѵ�.
				if( g_pTcpIp )
				{
					sprintf(strTemp, "u_shop refresh req 2 %d %d\n",  g_ii[1], g_ii[3] );
					g_pTcpIp->SendNetMessage( strTemp );
				}
			}

			// Ŭ���̾�Ʈ���� ���� ���� �ʰ� ������ �ϳ��ϳ��� �������� �˾Ƽ� �����ְ� Ŭ���̾�Ʈ�� ���� ������ ������ �����ϴ� ������� �ٲ�.
			/*
						for( i = 0 ; i < g_ii[3] ; ++i )
						{
							arg = AnyOneArg( arg, g_Buf );
							g_ii[4] = atoi( g_Buf ); // �κ� x

							arg = AnyOneArg( arg, g_Buf );
							g_ii[5] = atoi( g_Buf ); // �κ� y

							if( g_pNk2DFrame->GetControlUserShop()->SlotOut( g_ii[1], g_ii[2], g_ii[4], g_ii[5] ) )
							{
								// ������ ��Ŷ�� ������ �ֽ� ������ �������ٰ��� �䱸�Ѵ�.
								if( g_pTcpIp )
								{
									sprintf(strTemp, "u_shop refresh req 3\n");
									g_pTcpIp->SendNetMessage( strTemp );
								}
							}
						}
			*/
		}
		else // ����. �ڿ� ���� �ε����� �´�.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ���� ����

			switch( g_ii[1] )
			{
			case -3: // ����Ʈ�� ����ִµ� ������ ��û�� ���.
				// ������ ��Ŷ�� ������ �ֽ� ������ �������ٰ��� �䱸�Ѵ�.
				if( g_pTcpIp )
				{
					sprintf(strTemp, "u_shop refresh req 4 %d\n", g_ii[1]);
					g_pTcpIp->SendNetMessage( strTemp );
				}
				break;
			}

		}

		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"close") ) // ���� �ݱ�. ���� �ݱ� ��Ŷ�� ���� ������ ����.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����
		if( g_ii[0] ) // ����
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // Ŭ���� Ÿ��.( 0 : ����, -1 : �������϶� �Ǹ��ڰ� ����(�Ǵ� ����), 1 : ������ ȸ�� �Ϸ� ������. )

			if( g_ii[1] == -1 ) // �����߿� �Ǹ��ڰ� �ݾƹ�������..
			{
				//-- IDS_USHOP_MASTERCLOSE : ���������� ������ �ݾҽ��ϴ�.
				pMgr->CmdErrorMsg( (char*)G_STRING(IDS_USHOP_MASTERCLOSE) );
			}
			if( g_ii[1] == 1 )
			{
				//-- IDS_USHOP_CANT_RECEIVE_ALL : ������ �������� ��� ȸ������ ���Ͽ����ϴ�. NPC���� ã�ư�����.
				pMgr->CmdErrorMsg( (char*)G_STRING(IDS_USHOP_CANT_RECEIVE_ALL) );
			}

			g_pRoh->m_UserShopLevel = 0; // �����ϴٰ��� �� �ǹ̰� ������ �׳� ������ ���ڸ� ����.

			g_pNk2DFrame->ShowUserShopWindow( FALSE ); // ������ �ݾ��ش�. // �� �ȿ��� m_bOpened�� FALSE�����ִ°� �߿��ϴ�.
		}
		else // ���н�.. ������ �ް� �������̽��� �Ȳ����� ��찡 �ִ�. �̰�� 5���� Ŭ���̾�Ʈ���� �ٽ� Ŭ���� ��û�� �ϴµ� Ŭ��� ���з� �ð��̴�. �̶����� �������̽��� �ݾƹ�����.(�ֳĸ� �ȱ׷��� Ŭ���̾�Ʈ�� �ٸ� ����� �ȹ޾Ƶ��δ�.)
		{
			// �ᱹ �� ���� ���״�. ���׸� ���� ��ã�Ƽ� ������ �κ�.
			//-- IDS_USHOP_CLOSE_ERROR : ���λ����� ������ ����Ǿ����ϴ�.
			pMgr->CmdErrorMsg( (char*)G_STRING(IDS_USHOP_CLOSE_ERROR) );

			g_pRoh->m_UserShopLevel = 0; // �����ϴٰ��� �� �ǹ̰� ������ �׳� ������ ���ڸ� ����.

			g_pNk2DFrame->ShowUserShopWindow( FALSE ); // ������ �ݾ��ش�. // �� �ȿ��� m_bOpened�� FALSE�����ִ°� �߿��ϴ�.
		}

		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"start") ) // ���� ���� ��û�� ���.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����
		if( g_ii[0] ) // ����
		{
			g_pNk2DFrame->GetControlUserShop()->m_SellStartBtn.SetDisable( TRUE );
			g_pNk2DFrame->GetControlUserShop()->m_ModifyBtn.SetDisable( FALSE );

			g_pNk2DFrame->GetControlUserShop()->m_bSlotLock = TRUE; // �ȱ� ���������Ƿ� �Ժη� ������ ���ǵ帮�� ���ִ� ���� �Ǵ�.

			if( g_pNk2DFrame->GetControlUserShop()->m_iType == USHOP_TYPE_SELLER ) // �ϴ� �Ǹ����� ��� ///��������
			{
				g_pRoh->m_UserShopLevel = g_pNk2DFrame->GetControlUserShop()->m_iPackNum; // �ڱ��ڽ��� ��ŸƮ�� ���� �������� �Ѱ��������� ���Ǵ븦 ��ġ���ش�

				// ��Ʈ ��µ��� ���� �˾� ��ü�� �����Ѵ�.
				if( g_pRoh->m_pUserShopPopup )
				{
					CMultiText multiText;
					char strTemp[100];

					//-- IDS_WHOS_USERSHOP : %s�� ���λ���
					sprintf( strTemp, (char*)G_STRING(IDS_WHOS_USERSHOP), g_pRoh->m_pstrName );
					multiText.AddString( strTemp, _FCOLOR_YELLOW );
					// ���ڿ��� �������E������ �����鼭 ���
					// ���ڿ� ���̸� 15���� 35���� �÷� ����غ���. [2/8/2007 Theodoric]
					multiText.AddStringMulti( g_pNk2DFrame->GetControlUserShop()->m_ShopMentText.GetStrBuf(), 15, TRUE );
					g_pRoh->m_pUserShopPopup->PutString(&multiText, TRUE);
				}
			}
			else if( g_pNk2DFrame->GetControlUserShop()->m_iType == USHOP_TYPE_ADMIN
					 || g_pNk2DFrame->GetControlUserShop()->m_iType == USHOP_TYPE_STORE ) // ���� �������� ���.
			{
				g_pNk2DFrame->ShowUserShopWindow( FALSE ); // �������̽��� �ݾ��ش�. ���ƴٴҼ��ֵ���.

				if( g_pTcpIp )
				{
					sprintf( strTemp, "u_shop m_close\n" ); // �������̽��� �ݾҴٰ� ������ �˷��ֱ� ���� ��Ŷ.
					g_pTcpIp->SendNetMessage( strTemp );
				}
			}
		}
		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"modify") ) // ���� ��û�� ���.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����
		if( g_ii[0] ) // ����
		{
			g_pNk2DFrame->GetControlUserShop()->m_SellStartBtn.SetDisable( FALSE );
			g_pNk2DFrame->GetControlUserShop()->m_ModifyBtn.SetDisable( TRUE );

			g_pRoh->m_UserShopLevel = 0; // �����ϴٰ��� �� �ǹ̰� ������ �׳� ������ ���ڸ� ����.
			g_pNk2DFrame->GetControlUserShop()->m_bSlotLock = FALSE; // �ȱ� ���������Ƿ� �Ժη� ������ ���ǵ帮�� ���ִ� ���� Ǭ��.
		}

		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"list_start") ) // ���� ��ǰ ǰ�� �ޱ� ����
	{
		g_pNk2DFrame->GetControlUserShop()->ClearSlot(); // �켱 ������ �ִ� ���Ե��� ���� ����������.
		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = TRUE; // �� �༮�� ���������� ���� �Ǵ�.
		g_pNk2DFrame->GetControlUserShop()->m_SrvMsgWaitTick = timeGetTime(); // ���� �޼����� ��ٸ��� �ֱ� ������ ������ ����صδ� ƽ. �����ð� �����޼����� ������ �÷��׸� Ǯ���ֱ����� �д�.(�̷��� Ǯ����� ������ �ݾƹ����� �ҵ�.)
	}
	else if( !strcmp(g_Buf,"list") ) // ���� ��ǰ ǰ�� ����.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ��ġ.

		arg = AnyOneArg( arg, g_Buf );
		g_ii[1] = atoi( g_Buf ); // vnum

		arg = AnyOneArg( arg, g_Buf );
		g_ii[2] = atoi( g_Buf ); // plus

		arg = AnyOneArg( arg, g_Buf );
		g_ii[3] = atoi( g_Buf ); // special1(�ɼ�1)

		arg = AnyOneArg( arg, g_Buf );
		g_ii[4] = atoi( g_Buf ); // special2(�ɼ�2)

		arg = AnyOneArg( arg, g_Buf );
		g_ii[5] = atoi( g_Buf ); // ���� ������

		arg = AnyOneArg( arg, g_Buf );
		g_ii[6] = atoi( g_Buf ); // �ִ� ������

		if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[12] = atoi( g_Buf );		// �Ϲ� ������
			arg = AnyOneArg( arg, g_Buf );
			g_ii[13] = atoi( g_Buf );		// �Ϲ� ������ Max
		}

		arg = AnyOneArg( arg, g_Buf );
		g_ii[9] = atoi( g_Buf ); // �ݱ�
		arg = AnyOneArg( arg, g_Buf );
		g_ii[10] = atoi( g_Buf ); // ����
		arg = AnyOneArg( arg, g_Buf );
		g_ii[11] = atoi( g_Buf ); // ����

		arg = AnyOneArg( arg, g_Buf );
		g_ii[7] = atoi( g_Buf ); // ����

		arg = AnyOneArg( arg, g_Buf );
		g_ii[8] = atoi( g_Buf ); // ����

		if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		{
			g_pNk2DFrame->GetControlUserShop()->SetSlotItem( g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6]
					, g_ii[12], g_ii[13], g_ii[9], g_ii[10], g_ii[11], g_ii[7], g_ii[8] ); // ������ ������ ����.
		}
		else
		{
			g_pNk2DFrame->GetControlUserShop()->SetSlotItem( g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6]
					, 0, 0 , g_ii[9], g_ii[10], g_ii[11], g_ii[7], g_ii[8]); // ������ ������ ����.
		}
	}
	else if( !strcmp(g_Buf,"list_end") ) // ���� ��ǰ ǰ�� �ޱ� ��.
	{
		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"buy") ) // ��ǰ���� ��û ���.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����
		if( g_ii[0] ) // ����
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ��� ��ȣ

			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf ); // ��� ����

			if( !g_pNk2DFrame->GetControlUserShop()->SlotOut( g_ii[1], g_ii[2] ) ) // ī��Ʈ�� �ٿ��ִ� �Լ�.
			{
				// ������ ��Ŷ�� ������ �ֽ� ������ �������ٰ��� �䱸�Ѵ�.
				if( g_pTcpIp )
				{
					sprintf(strTemp, "u_shop refresh req 5 %d %d\n", g_ii[1], g_ii[2] );
					g_pTcpIp->SendNetMessage( strTemp );
				}
			}

			if( g_ii[0] == 1 ) // �ڱ� �ڽ��� �� ���. ���� �޼����� ������ش�.
			{
				//-- IDS_ITEM_BUY_SUCC : �������� ���������� ���ŵǾ����ϴ�.
				pMgr->CmdErrorMsg( (char*)G_STRING(IDS_ITEM_BUY_SUCC) );
			}
		}
		else
		{
			//-- IDS_ITEM_BUY_FAIL : ������ ���ſ� �����Ͽ����ϴ�.
			pMgr->CmdErrorMsg( (char*)G_STRING(IDS_ITEM_BUY_FAIL) );
		}

		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"sell") ) // �ȷ���.
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����
		if( g_ii[0] ) // ����
		{
			// ���� ������ ��������.
			arg = AnyOneArg( arg, g_Buf );
			g_ii[1] = atoi( g_Buf ); // ���� ��ȣ.

			arg = AnyOneArg( arg, g_Buf );
			g_ii[4] = atoi( g_Buf ); // �� �Լ� �ݱ�.
			arg = AnyOneArg( arg, g_Buf );
			g_ii[5] = atoi( g_Buf ); // �� �Լ� ����.
			arg = AnyOneArg( arg, g_Buf );
			g_ii[6] = atoi( g_Buf ); // �� �Լ� ����.


			arg = AnyOneArg( arg, g_Buf );
			ii64 = _atoi64( g_Buf ); // �� �Լ� ����.(������ ���� ������ �ƴ϶� �Ǹűݾ׶� ���ſ� ����ؾ��Ѵ�.) (���ݱ��� �ȸ� �� �ݾ��� �´�.)

			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf ); // �ȸ� ����.(���� ������ �ƴԿ� ����.)(��������-�ȸ������� 0���ϸ� �������� �������Ѵ�.)

			g_pNk2DFrame->GetControlUserShop()->SelledItem( g_ii[1], g_ii[4], g_ii[5], g_ii[6], ii64, g_ii[3] );
		}

		g_pNk2DFrame->GetControlUserShop()->m_bSrvMsgWaiting = FALSE; // ��ٸ��� �� �÷��׸� ����.
	}
	else if( !strcmp(g_Buf,"req") ) // ȸ����û ���
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // ���� ����
		switch( g_ii[0] ) // ����
		{
		case 1: // ��� ȸ��
			//-- IDS_USHOP_RECEIVE_ALL : ��� �������� ���� �޾ҽ��ϴ�.
			pMgr->CmdErrorMsg( (char*)G_STRING(IDS_USHOP_RECEIVE_ALL) );
			break;
		case 0: // ȸ�������� ����.
			//-- IDS_USHOP_RECEIVE_NOT : ���� ���� �������� �����ϴ�.
			pMgr->CmdErrorMsg( (char*)G_STRING(IDS_USHOP_RECEIVE_NOT) );
			break;
		case -1: // ��� ȸ��
			//-- IDS_USHOP_RECEIVE_MORE : ���� ���� �������� �����ֽ��ϴ�. �κ��� ��켼��.
			pMgr->CmdErrorMsg( (char*)G_STRING(IDS_USHOP_RECEIVE_MORE) );
			break;
		}
	}
	else if( !strcmp(g_Buf,"slist_start") ) // ���� �˻� ��� �ޱ� ����
	{
		g_pNk2DFrame->GetUserShopSearch()->ClearList(); // �켱 ������ �ִ� ����Ʈ���� ���� ����������.

		g_pNk2DFrame->GetUserShopSearch()->m_bNowSearching = TRUE; // �� ã���ִ��� ǥ�ÿ�...
		g_pNk2DFrame->GetUserShopSearch()->m_NowSearchTick = timeGetTime(); // ��ŸƮ�� �� �ð��� ���.
		g_pNk2DFrame->GetUserShopSearch()->m_pRefSelOnItem = NULL; // �̰� �ʱ�ȭ ���ϸ� ƨ��� ��찡 �ִ�.
	}
	else if( !strcmp(g_Buf,"slist") ) // ���� �˻� ��� �ޱ� ����.
	{
		if( !g_pNk2DFrame->GetUserShopSearch()->m_bNowSearching ) // �̰� FALSE�� ����Ʈ�� �� �͵� �����Ѵ�.(�ð� �ʰ����� ���.)
			return;

		sUShopSearchData *TempSearchData; // �ӽ÷� �־��� �׸�.

		TempSearchData = new sUShopSearchData; // �޸𸮸� ���� ����ش�.
		CItem *TempItem = &(TempSearchData->Item);

		arg = AnyOneArg( arg, g_Buf ); // ���� ���� ��.(��Ʈ�� ���̿� ������ ������ ����)
		int TempLen = strlen( g_Buf );
		if( TempLen < 29 ) // ���� ���̺��� ª������ �ִ´�.
		{
			strcpy( TempSearchData->CharName, g_Buf );
			TempSearchData->CharName[TempLen] = '\0';
		}
		else // ���� ���̺��� ����ٸ�...
		{
			TempSearchData->CharName[0] = '\0';
		}

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->PosX = atoi( g_Buf ); // X ��ǥ

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->PosY = atoi( g_Buf ); // Y ��ǥ

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->ZoneNum = atoi( g_Buf ); // Zone

		// �� ���ϴ� ������ ����.
		TempSearchData->Item.m_Index = 0;

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->Item.m_Vnum = atoi( g_Buf ); // vnum

		TempSearchData->Item.m_ProtoNum = g_ItemList.FindItem( TempSearchData->Item.m_Vnum );

		arg = AnyOneArg( arg, g_Buf );
		g_ii[0] = atoi( g_Buf ); // plus

		if( GET_TYPE(TempItem) == ITYPE_SUB )
			TempItem->m_PlusNum = g_ii[0];
		else if( g_ii[0] > 0 )
		{
			if( GET_ITEM_LEVEL(TempItem) >= 181 )
				TempItem->SetDiaGemNum( g_ii[0] );
			else
				TempItem->SetGemNum( g_ii[0] );
		}

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->Item.m_Special = atoi( g_Buf ); // special(�ɼ�)

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->Item.m_Special2 = atoi( g_Buf ); // special2(�ɼ�2)

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->Item.m_UpgradeEndurance = atoi( g_Buf ); // ���� ������

		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->Item.m_MaxUpgradeEndurance = atoi( g_Buf ); // �ִ� ������

		if( g_SvrType == ST_ADULT_ONLY) // ������ ����
		{
			arg = AnyOneArg( arg, g_Buf );
			TempSearchData->Item.m_Endurance = atoi( g_Buf);

			arg = AnyOneArg( arg, g_Buf );
			TempSearchData->Item.m_MaxEndurance = atoi( g_Buf);
		}

		// ������ ���� �Է��غ���!
		ResetItemValue( TempItem );
		SetSpecialValue( TempItem, GET_TYPE(TempItem), GET_SHAPE(TempItem), TempItem->m_Special, TempItem->m_Special2 );


		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->MinPrice = _atoi64( g_Buf ); // �ּ� ����
		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->MaxPrice = _atoi64( g_Buf ); // �ִ� ����

		/*      // ������ ������ ǥ���ϱ�� �ٲ��.
				arg = AnyOneArg( arg, g_Buf );
				TempSearchData->GoldLime = atoi( g_Buf ); // �ݱ�
				arg = AnyOneArg( arg, g_Buf );
				TempSearchData->SilverLime = atoi( g_Buf ); // ����
				arg = AnyOneArg( arg, g_Buf );
				TempSearchData->BronzeLime = atoi( g_Buf ); // ����

				arg = AnyOneArg( arg, g_Buf );
				TempSearchData->Price = atoi( g_Buf ); // ����
		*/
		arg = AnyOneArg( arg, g_Buf );
		TempSearchData->Count = atoi( g_Buf ); // ����

		g_pNk2DFrame->GetUserShopSearch()->m_ResultList.push_back( TempSearchData ); // �ϳ��� �߰��Ѵ�.

		if( g_pNk2DFrame->GetUserShopSearch()->m_ResultList.size() >= 99 ) // 99�������� �޴´�.
			g_pNk2DFrame->GetUserShopSearch()->m_bNowSearching = FALSE; // �̷��� �ϸ� �׸� �ް� ��.
	}
	else if( !strcmp(g_Buf,"slist_end") ) // ���� �˻� ��� �ޱ� �� (���� �������� �����ֱⰡ ��ƴ��Ͽ� ���� �Ⱦ���. ������ ������ ���� �ϴ� ����.(�������� �����ָ� ����.)
	{
		if( g_pNk2DFrame->GetUserShopSearch()->m_ResultList.size() <= 0 ) // ���� ����Ʈ�� ���ٸ�...
		{
			// �����޼��� ���
			char StrTemp[256];
			//-- IDS_USHOPSEARCH_NOTSELL : [%s] �������� �Ȱ��ִ� ������ �����ϴ�.
			sprintf( StrTemp, (char*)G_STRING(IDS_USHOPSEARCH_NOTSELL), g_pNk2DFrame->GetUserShopSearch()->m_strSearchName );

			pMgr->CmdErrorMsg( StrTemp );
		}

		g_pNk2DFrame->GetUserShopSearch()->m_bNowSearching = FALSE; // �� ã���ִ��� ǥ�ÿ�...
	}
}

void CmdNpcWear( char* arg, CUIMgr* pMgr ) // Npc���� ��� ������ ���� ��Ŷ. ����� �������� NPC�� �����Ѵ�. ///�������� �� �߰�
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf ); // Npc �ε���. (�������� NPC�� �Ϲ� NPC�� �ε����� ���� ���ܴ�. ��, ��ġ�� �ʴ´�.

	arg = AnyOneArg( arg, g_Buf );
	g_ii[1] = atoi( g_Buf ); // ������ Vnum

	CUserShopNpc *TempUShopNpc = pMgr->FindUShopNpcById( g_ii[0] ); // �켱�� �������� NPC�� �˻�.

	if( TempUShopNpc ) // �ִ� �༮�̸�...
	{
		// ������ �÷��׵��� ������ �ɼ��� ����.(�󱼾��� �����͵�..)
		int ItemProtoNum = g_ItemList.FindItem( g_ii[1] );

		if( ItemProtoNum == -1 ) // ���� ��������.
			return;

		int RenderFlag = g_ItemList.m_ItemArray[ItemProtoNum].m_RenderFlag;

		if( TempUShopNpc->m_bRemoveHair ) // �̹� 1�̸� ���� ���Ѵ�.(���� �����۰� �Ⱦ��� �������� ���� �������� �켱��.
			TempUShopNpc->m_bRemoveHair = ( RenderFlag & ARMOR_REMOVE_HAIR );
		if( TempUShopNpc->m_bRemoveFace ) // �̹� 1�̸� ���� ���Ѵ�.(���� �����۰� �Ⱦ��� �������� ���� �������� �켱��.
			TempUShopNpc->m_bRemoveFace = ( RenderFlag & ARMOR_REMOVE_FACE );
		if( TempUShopNpc->m_bRemoveBody ) // �̹� 1�̸� ���� ���Ѵ�.(���� �����۰� �Ⱦ��� �������� ���� �������� �켱��.
			TempUShopNpc->m_bRemoveBody = ( RenderFlag & ARMOR_REMOVE_BODY );
		if( TempUShopNpc->m_bRemoveArms ) // �̹� 1�̸� ���� ���Ѵ�.(���� �����۰� �Ⱦ��� �������� ���� �������� �켱��.
			TempUShopNpc->m_bRemoveArms = ( RenderFlag & ARMOR_REMOVE_ARMS );
		if( TempUShopNpc->m_bRemoveLegs ) // �̹� 1�̸� ���� ���Ѵ�.(���� �����۰� �Ⱦ��� �������� ���� �������� �켱��.
			TempUShopNpc->m_bRemoveLegs = ( RenderFlag & ARMOR_REMOVE_LEGS );
		if( TempUShopNpc->m_bRemoveFoot ) // �̹� 1�̸� ���� ���Ѵ�.(���� �����۰� �Ⱦ��� �������� ���� �������� �켱��.
			TempUShopNpc->m_bRemoveFoot = ( RenderFlag & ARMOR_REMOVE_FEET );

		TempUShopNpc->m_WearList.push_back( g_ItemList.FindItem(g_ii[1]) ); // �������� ProtoNum�� �߰��Ѵ�.

		return; // ���� �Ϲ� NPC���� �� ��츦 ���� ����.
	}

	// ����� �������� NPC�� ����. ���� �Ϲ� NPC���� �ʿ��� ��� �� �ؿ��� �ε����� �˻��ؼ� ������.
}

void CmdProcess(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );

	if (!strcmp(g_Buf, "req"))
	{
		arg = AnyOneArg(arg, g_Buf);	// ��û�� �̸�
		if( pMgr )
			pMgr->CmdProcessRequest(g_Buf);
	}
	else if (!strcmp(g_Buf, "ans"))
	{
		arg = AnyOneArg(arg, g_Buf);
		if(!strcmp(g_Buf, "accept"))
		{
			arg = AnyOneArg(arg, g_Buf);	// 0: ��û�� ���, 1: �������� �������.
			g_ii[ 1 ] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// ���� �̸�
			if( pMgr )
				pMgr->CmdProcessAccept( g_ii[ 1 ], g_Buf);
		}
	}
	else if (!strcmp(g_Buf, "money"))
	{
		arg = AnyOneArg( arg, g_Buf );	// �ݾ�
		if( pMgr )
			pMgr->ProcessMoney( g_Buf );
	}
	else if (!strcmp(g_Buf, "succ"))	// ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);			// index
		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);			// vnum
		arg = AnyOneArg(arg, g_Buf);
		g_ii[3] = atoi(g_Buf);			// x
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// y

		if( pMgr )
			pMgr->ProcessSuccess( g_ii[1], g_ii[2], g_ii[3] ,g_ii[4]);
	}
	else if (!strcmp(g_Buf, "fail"))	// ����
	{
		if( pMgr && g_pNk2DFrame )
		{
			pMgr->ProcessFail();
			g_pNk2DFrame->ShowProcessWindow( false );
		}
	}
}

// exch_inven_to index vnum x y
void CmdProcessInvenTo(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			//index
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// vnum
	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);			// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);			// y
	arg = AnyOneArg(arg, g_Buf);
	gem_num[0] = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	special[0] = atoi(g_Buf);

	if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[4] = atoi(g_Buf);			// ��ȭ ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[5] = atoi(g_Buf);			// ��ȭ ������ Max
		arg = AnyOneArg(arg, g_Buf);
		g_ii[6] = atoi(g_Buf);			// �Ϲ� ������
		arg = AnyOneArg(arg, g_Buf);
		g_ii[7] = atoi(g_Buf);			// �Ϲ� ������ Max
	}

	if( pMgr )
	{
		if(	g_SvrType == ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		{
			pMgr->ProcessInvenTo(g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0],
								 g_ii[4], g_ii[5], g_ii[6], g_ii[7]);
		}
		else
		{
			pMgr->ProcessInvenTo(g_ii[2], g_ii[3], g_ii[0], g_ii[1], gem_num[0], special[0], 0, 0, 0, 0);
		}
	}
}

void CmdProcessInvenFrom(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// x
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// y

	if( pMgr )
		pMgr->ProcessInvenFrom(g_ii[0], g_ii[1]);
}

void CmdBpShopList(char *arg, CUIMgr *pMgr) // BP������ ����Ʈ(NPC �ε���)�� �޾ƿ��� ��Ŷ. �� �ε����� ���� BP���� �޴��� ��ư�� �׼��� �ɾ�д�.
{
	// �� �༮�� ���������� ShowControlMenuWindow �Լ� ȣ�� �� AddButton()�� LoadRes()�� ���ش�.
	CNkMob TempMobData;
	TempMobData.SetInfo( 380, 0 ); // �ȳ��� ������ ����.

	g_pNk2DFrame->ShowControlMenuWindow( TRUE, MENU_TYPE_BPSHOP, TempMobData.GetMobName() );

	// �� ��ư�� ���(�׼� �ε����� �������� ������ Npc �ε��� + 10000 ���� �����Ѵ�.) (������ ������ ��ϵ� ����.)
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);	// ����Ʈ ����

	for( int i = 0 ; i < g_ii[0] ; ++i )
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);	// ���� Ÿ��(���� ��������..)

		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);	// Npc �ε���.

		switch( g_ii[1] )
		{
		case 0: // Į
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_sword", 50, 225, g_ii[2]+10000 ); // Į BP ����.
			break;
		case 1: // ����
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_axe", 100, 225, g_ii[2]+10000 ); // ���� BP ����.
			break;
		case 2: // ������
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_staff", 150, 225, g_ii[2]+10000 ); // ������ BP ����.
			break;
		case 3: // ��
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_gun", 200, 225, g_ii[2]+10000 ); // �� BP ����.
			break;
		case 4: // ��
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_ring", 50, 250, g_ii[2]+10000 ); // �� BP ����.
			break;
		case 5: // �̵���
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_dsword", 100, 250, g_ii[2]+10000 ); // �̵��� BP ����.
			break;
		case 6: // �ظ�
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_hammer", 150, 250, g_ii[2]+10000 ); // �ظ� BP ����.
			break;
		case 7: // ��Ÿ
			g_pNk2DFrame->GetControlMenu()->AddButton( "Menu/btn_etc", 200, 250, g_ii[2]+10000 ); // ��Ÿ BP ����.
			break;
		}
	}

	g_pNk2DFrame->GetControlMenu()->LoadRes(); // �ʿ��� ���ҽ��� �ε��Ѵ�.
}




void CmdWorldCup(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	if (!strcmp(g_Buf, "time"))
	{
		arg = AnyOneArg( arg, g_Buf );	//�ð�
		g_ii[1] = atoi(g_Buf);
		if( pMgr )
			pMgr->WorldCupTime( g_ii[1] );
	}
	else if (!strcmp(g_Buf, "score"))
	{
		arg = AnyOneArg(arg, g_Buf);  //A�� ���ھ�
		g_ii[1] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);  //B�� ���ھ�
		g_ii[2] = atoi(g_Buf);

		if( pMgr )
			pMgr->WorldCupScore( g_ii[1], g_ii[2] );
	}
	else if (!strcmp(g_Buf, "name"))
	{
		arg = AnyOneArg(arg, g_Buf);	//A�� ��� ����
		arg = AnyOneArg(arg, g_Buf2);	//B�� ��� ����

		if( pMgr )
			pMgr->WorldCupGuildName( g_Buf, g_Buf2 );
	}
}

void CmdUseEffect(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );	//�ɸ� �ε���
	g_ii[0] = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	//�̺�Ʈ �ε���
	g_ii[1] = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );  //���̳� ����
	g_ii[2] = atoi( g_Buf );

	///�����޺� �� ����
	pCha = pMgr->FindChaById(g_ii[0]);

	if( pCha )
	{
		switch( g_ii[1] )
		{
		case EFFECT_CHA_DONT_ATTACK_STATE:
			switch(g_ii[2])
			{
			case 1:
				pCha->ChaDontAttackEffectStart();
				return;
			case 0:
				pCha->ChaDontAttackEffectEnd();
				return;
			}
			break;

		default:
			break;
		}

		if( g_ii[1] == EFFECT_NOTSKILL_SPEEDUP ) // ������ �뽬��� ����Ʈ.
		{
			if( pMgr )
				pMgr->SpeedUpEffect( pCha, g_ii[2] );
		}
		else if( g_ii[1] == EFFECT_NOTSKILL_SPIRITMODE )
		{
			if( pMgr )
				pMgr->SpiritModeEffect( pCha, g_ii[2] );
		}
		else if( g_ii[1] == EFFECT_SKILL_BASHREFLECTION ) // ���̺긮�� �ظ� �޺� �н� ����Ʈ�� Ÿ�� ����Ʈ��.
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf ); // Ÿ�� ����.(�� �༮�� On/Off �÷��׸� �Ⱦ��Ƿ� �����.)

			pCha->m_MultiTargetNum = g_ii[2];

			arg = AnyOneArg( arg, g_Buf ); // Ÿ�� ����
			if( !strncmp(g_Buf, "c", 1) )
				pCha->m_MultiTargetKind = MULTITARGET_KIND_CHAR; // Ÿ���� ĳ������
			else
				pCha->m_MultiTargetKind = MULTITARGET_KIND_MOB; // Ÿ���� ������


			for( int i = 0 ; i < g_ii[2] ; ++i )
			{
				arg = AnyOneArg( arg, g_Buf );
				g_ii[3] = atoi( g_Buf ); // Ÿ�� �ε���.

				pCha->m_MultiTargetArray[i] = g_ii[3];

				if( pCha->m_MultiTargetKind == MULTITARGET_KIND_CHAR )
				{
					pCha2 = pMgr->FindChaById( g_ii[3], FALSE );

					if( pCha2 )
					{
						// �н� ����Ʈ�� ����.
						pCMyApp->m_pUIMgr->InsertMagic( pCha, NULL, pCha2, NULL, EFFECT_SKILL_BASHREFLECTION );
					}
				}
				else if( pCha->m_MultiTargetKind == MULTITARGET_KIND_MOB )
				{
					pMob = pMgr->FindMobById( g_ii[3] );

					if( pMob )
					{
						// �н� ����Ʈ�� ����.
						pCMyApp->m_pUIMgr->InsertMagic( pCha, NULL, NULL, pMob, EFFECT_SKILL_BASHREFLECTION );
					}
				}
			}
		}
		else if( g_ii[1] == EFFECT_POISON_FOG ) // ��ī�� ������ ���Ȱ�. ȭ�鿡 2D�� �ѷ����� ���Ȱ� ����. ///�δ�1
		{
			EffectSort ef_sort;
			ZeroMemory(&ef_sort, sizeof(EffectSort));

			ef_sort.nType = FX_POISON_FOG;
			ef_sort.dwColor = timeGetTime();
			pCMyApp->m_pFxSet->InsertFxEffect( ef_sort );
		}
		else if( g_ii[1] >= SKILL_LUCKYPIG1 && g_ii[1] <= SKILL_LUCKYPIG4 ) // ���� ���� ȸ�� ��ų ���.
		{
			EffectSort *TempEffect = NULL;
			TempEffect = pCha->FindMyFairy( g_ii[1] ); // �ش� ĳ������ ������ ã�Ƽ�...

			// ����� �ٲ�ΰ� ����Ʈ�� �߰����ش�.
			if( TempEffect )
			{
				TempEffect->num = FX_LUCKYPIG_STATE_HEAL; // ȸ�� ���.
				TempEffect->vSortPos.y = 0; // ������ �ʱ�ȭ.

				pMgr->InsertMagic(NULL, NULL, pCha, NULL, EFFECT_PIG_HEALING );
			}
		}
		// [7/31/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ���̺� �ҿ� :: ũ��Ƽ�� ȿ��.(���ϸ��̼�)
//		else if( g_ii[1] >= SKILL_BABYSOUL_1 && g_ii[1] <= SKILL_BABYSOUL_3 )
//		{
//			EffectSort *TempEffect = NULL;
//			TempEffect = pCha->FindMyFairy( g_ii[1] ); // �ش� ĳ������ ������ ã�Ƽ�...
//
//			// ����� �ٲ�ΰ� ����Ʈ�� �߰����ش�.
//			if( TempEffect )
//			{
//				TempEffect->num = FX_BABYSOUL_STATE_CRITICAL; // ȸ�� ���.
//				TempEffect->vSortPos.y = 0; // ������ �ʱ�ȭ.
//
//				//pMgr->InsertMagic(NULL, NULL, pCha, NULL, EFFECT_PIG_HEALING );
//			}
//		}
	}
}

void CmdMultiShop( char *arg, CUIMgr *pMgr ) ///�������
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetControlCashShop() )
		return;


	arg = AnyOneArg( arg, g_Buf ); // ��Ŷ ����

	if( !strcmp(g_Buf,"buy") ) // ���� ���� ���� ����
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);			// �� ����.

		if( g_ii[0] == 0 ) // ���� ����
		{
			if( !g_pNk2DFrame->GetControlCashShop()->m_pWantBuyCatalog ) // Ȥ�� ������..
				return;

			// ���ų��� ����Ʈ�� �߰�.
			sSellCatalogInfo *TempCatalogInfo = NULL;
			TempCatalogInfo = new sSellCatalogInfo; // ���� �޸� ��Ƽ� ������Ѵ�.

			if( !TempCatalogInfo )
				return;

			memcpy( TempCatalogInfo, g_pNk2DFrame->GetControlCashShop()->m_pWantBuyCatalog, sizeof(*TempCatalogInfo) ); // ������ ����. ������ ������ ��������...

			TempCatalogInfo->m_pTextSur = NULL; // ���� �ʱ�ȭ ����. ���� ���� �ؾ��Կ� ����.

			GetSystemTime( &(TempCatalogInfo->m_BuyTime) ); // ���Žð��� �޾Ƴ��´�.

			g_pNk2DFrame->GetControlCashShop()->MakeBuyListText( TempCatalogInfo ); // �ش� ���ų����� �ؽ�Ʈ�θ� �̸� ����.

			g_pNk2DFrame->GetControlCashShop()->m_BuyCatalogList.push_back( TempCatalogInfo ); // ���� ������ �߰�.

			g_pNk2DFrame->GetControlCashShop()->m_TotalUseCash += TempCatalogInfo->m_Price; // ������ ����.
			g_pNk2DFrame->GetControlCashShop()->m_pWantBuyCatalog = NULL; // ���Դ��� Ǯ���ش�.

			if( g_pNk2DFrame->GetControlCashShop()->m_InfoTab.NowSelectedIndex == 1 ) // ���� ���� �����־��ٸ� ��ũ�� ����.
			{
				if( g_pNk2DFrame->GetControlCashShop()->m_BuyCatalogList.size() >= VIEW_INFO2_LINE+1 ) // ��ũ�� ���� ��
					g_pNk2DFrame->GetControlCashShop()->m_InfoScroll.SetRange( g_pNk2DFrame->GetControlCashShop()->m_BuyCatalogList.size() - VIEW_INFO2_LINE + 1 ); // ������ ���ο� ���缭 ���� ����.
				else
					g_pNk2DFrame->GetControlCashShop()->m_InfoScroll.SetRange( 1 );
			}
		}
		else // ���� ����
		{
			char strTemp[200] = "";

			if( g_ii[0] == -1 ) // �ܾ׺���
			{
				//-- IDS_CASHSHOP_ERROR1 : �ܾ��� �����մϴ�.
				strcpy( strTemp, (char*)G_STRING(IDS_CASHSHOP_ERROR1) );
			}
			else if( g_ii[0] == -2 ) // ���� �߻�
			{
				// IDS_ERROR : ����
				strcpy( strTemp, G_STRING(IDS_ERROR) );
			}
			else if( g_ii[0] == -3 ) // ���� ���� ����
			{
				//-- IDS_CASHSHOP_ERROR2 : ���� ������ �����ϴ�.
				strcpy( strTemp, (char*)G_STRING(IDS_CASHSHOP_ERROR2) );
			}
			else if( g_ii[0] == -4 ) // �κ� ����
			{
				//-- IDS_CASHSHOP_ERROR3 : �κ��丮�� �� ������ �����մϴ�.
				strcpy( strTemp, (char*)G_STRING(IDS_CASHSHOP_ERROR3) );
			}

			if( g_pNk2DFrame )
				g_pNk2DFrame->InsertPopup( strTemp, TYPE_NOR_OK, 1 );

			g_pNk2DFrame->GetControlCashShop()->m_pWantBuyCatalog = NULL; // ��� ��ǰ�� Ŭ����.
		}
	}
}

void CmdPetEffect(char *arg, CUIMgr *pMgr) // ���� ��ų� ���̴� ��Ŷ
{
	arg = AnyOneArg(arg, g_Buf);	// skill index
	int skill_idx = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);	// source kind

	if( !strncmp(g_Buf, "p", 1) ) // ���� ��� ��ü�� �길 �ִ�.
	{
		arg = AnyOneArg(arg, g_Buf);	// source index
		g_ii[0] = atoi(g_Buf);

		if( pPet = pMgr->FindPetById(g_ii[0]) )
		{
			arg = AnyOneArg( arg, g_Buf2 );	// target kind

			arg = AnyOneArg(arg, g_Buf);	// target index
			g_ii[0] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// target vital
			g_ii[1] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// special attack // ���� ���� ��ų�� �Ⱦ���. �Ϲ� effect ��Ŷ�� ������ ���߱����� �־��.
			g_ii[2] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// Mob Class
			g_ii[3] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// Skill Step // ���� ���� ��ų�� �Ⱦ���.
			g_ii[4] = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);	// Skill Level // ���� ���� ��ų�� �Ⱦ���.
			g_ii[5] = atoi(g_Buf);

			if (!strncmp(g_Buf2, "n", 1)) // ���Ϳ��� ���� ���.
			{
				if( pMob = pMgr->FindMobById(g_ii[0]) )
				{
					pMob->SetAttackVital(g_ii[1]);
					if( g_ii[3]==0 )
						pMob->SetClassType(g_ii[3]);

					pPet->Attack( pMob->m_wx, pMob->m_wz );
					pPet->m_AttackMobId = pMob->m_nVirId;

//					if( pPet == pCMyApp->m_pMyPet ) // �ڱ� ���̸�... // �̰� ����. ��帶�� �޶���ϱ⶧����...
//						pCMyApp->m_pMyPet->SetCombatMob( pMob->m_nVirId ); // ��� ������ ����.

					pPet->SetPetEffect( skill_idx, pMob, NULL ); // CNkCharater �� SetMagicMob,SetMagicCha ����� �Լ�. ��ų�� ����� ��� ��󿡴��� ����Ʈ,��ǵ��� �����Ѵ�.

				}
			}
			else if (!strncmp(g_Buf2, "c", 1)) // ĳ���Ϳ��� ���� ���.
			{
				if( pCha = pMgr->FindChaById(g_ii[0], TRUE) )
				{
					if( pCha != g_pRoh )
						pCha->SetAttackVital( g_ii[1] );

					pPet->Attack( pCha->m_wx, pCha->m_wz );
					pPet->m_AttackChaId = pCha->m_nCharIndex;

//					if( pPet == pCMyApp->m_pMyPet ) // �ڱ� ���̸�... // �̰� ����. ��帶�� �޶���ϱ⶧����...
//						pCMyApp->m_pMyPet->SetCombatMob( -1, pCha->m_nVirId ); // ������ ĳ���� ��� ������ ����.

					pPet->SetPetEffect( skill_idx, NULL, pCha ); // CNkCharater �� SetMagicMob,SetMagicCha ����� �Լ�. ��ų�� ����� ��� ��󿡴��� ����Ʈ,��ǵ��� �����Ѵ�.
				}
			}
		}
	}
	else // ����Ѱ� ���̾ƴϸ� ���� �̻��ѰŴ�.
	{

	}
}

void CmdPetResult(char *arg, CUIMgr *pMgr) // ���� ��ȭ,��ų���� ��� ��Ŷ.
{
	arg = AnyOneArg(arg, g_Buf);	// ��� ����
	g_ii[0] = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);	// ����, ����. 0���� ũ�� ����, 0���� ������ ����.
	g_ii[1] = atoi(g_Buf);

	switch( g_ii[0] )
	{
	case 0: // ��ȭ ���.

		if( g_ii[1] > 0 ) // ����.
		{
			if( g_pNk2DFrame )
				g_pNk2DFrame->SetShowPetLevelFlag(false); // �������̽� ���ش�.
		}
		else if( g_ii[1] < 0 ) // ����.
		{
			if( g_ii[1] == -8 ) // ����� ���������� ��ȭ ���ϵ���... ///070723 �Ϻ����׸���Ʈ ����
			{
				// �޼����� �˷��ش�.
				// IDS_CANT_PETEVOL_NEC : ������ ����̸� ������ �� �ٽ� �õ��ϼ���.
				g_pNk2DFrame->InsertPopup( (char *)G_STRING(IDS_CANT_PETEVOL_NEC),TYPE_NOR_OK, 1 );
			}
		}

		break;

	case 1: // ��ų ���� ���

		if( g_ii[1] > 0 ) // ����.
		{
			if( g_pNk2DFrame )
				g_pNk2DFrame->SetShowPetLevelFlag(false); // �������̽� ���ش�.
		}
		else if( g_ii[1] < 0 ) // ����.
		{
		}

		break;

	}

}

void CmdPetChange(char *arg, CUIMgr *pMgr) // ���� ���� ���� ��� ��Ŷ.
{
	// ����� ����ġ ���� ���и� �ִ�.
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetControlCashShop() )
		return;

	arg = AnyOneArg( arg, g_Buf ); // ��Ŷ ����

	if( !strcmp(g_Buf,"fail") ) // ���� �� ���.
	{
		// IDS_MORE_NEED_EXP : ����ġ�� �����մϴ�.
		g_pNk2DFrame->InsertPopup( (char *)G_STRING(IDS_MORE_NEED_EXP),TYPE_NOR_OK, 1 );
	}
}


void CmdSupport(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	if (!strcmp(g_Buf, "req"))
	{
		arg = AnyOneArg(arg, g_Buf1); // �߽��� ĳ����

		if( g_pNk2DFrame->GetControlHelper()->m_bHelperAccept == 0)
			g_pTcpIp->SendNetMessage( "support ans -14\n" );
		else
			pMgr->CmdHelperRequest(g_Buf1);
	}
	else if (!strcmp(g_Buf, "ans"))
	{
		arg = AnyOneArg( arg, g_Buf );	//���
		g_ii[0] = atoi( g_Buf );

		switch( g_ii[0] )
		{
		case -14:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_STATE_REJECT_HELPER), TYPE_NOR_OK, 1);
			break;
		case -13:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CAUSE_TROUBLE), TYPE_NOR_OK, 1);
			break;
		case -12:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_NOT_CONNECT_HELPER), TYPE_NOR_OK, 1);
			break;
		case -11:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CANT_ADD_TRAINEE), TYPE_NOR_OK, 1);
			break;
		case -10:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_NOTENOUGHT_HELPER_LEVEL), TYPE_NOR_OK, 1);
			break;
		case -4:
			{
				char str[128] = {0,};
				arg = AnyOneArg(arg, g_Buf1);
				int	LimitTime = DWORD(atoi(g_Buf1));
				int Limit_Day	= ((LimitTime/60)/60 ) / 24;	// ���� �ϼ�.
				int Limit_Hour	= ((LimitTime/60)/60 ) % 24;	// ���� �ð�.
				int Limit_Min	= ( LimitTime/60)%60;		// ���� ��
				int hours = Limit_Day * 24 + Limit_Hour+1;
				sprintf(str, (char*)G_STRING(IDS_SUPPORT_MSG_01), hours);  // "%d�ð� �Ŀ� �İ��� ���踦 ���� �� �ֽ��ϴ�."
				g_pNk2DFrame->InsertPopup( str, TYPE_NOR_OK, 1);
			}
			break;
		case -3:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_ALREADY_CONNECTION_ANOTHER), TYPE_NOR_OK, 1);
			break;
		case -2:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_NEGOTIATION_ANOTHER), TYPE_NOR_OK, 1);
			break;
		case -1:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_NOTENOUGH_TRAINEE_LEVEL), TYPE_NOR_OK, 1);
			break;
		case 0:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_REJECT_HELPER), TYPE_NOR_OK, 1);
			break;
		case 1:
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_CONNECT_HELPER_COMPLET), TYPE_NOR_OK, 1);
			break;
		}
		return;
	}
	else if ( !strcmp(g_Buf, "info") )
	{
		arg = AnyOneArg( arg, g_Buf );	//�İ��� 0, �߽��� 1
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//������ŭ ���� ���� �ݺ�
		g_ii[1] = atoi( g_Buf );
		if( g_pNk2DFrame->GetControlHelper() )
			g_pNk2DFrame->GetControlHelper()->SetMember( g_ii[0], g_ii[1] );

		for( int count = 0; count < g_ii[1]; count++ )
		{
			arg = AnyOneArg( arg, g_Buf );	//�ɸ� �ε���
			g_ii[2] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf1 );	//�ɸ��͸�
			arg = AnyOneArg( arg, g_Buf );	//�ɸ��ͷ���
			g_ii[3] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );	//�ɸ�������
			g_ii[4] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );	//�ɸ��ͼ���
			g_ii[5] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );	//���� ����( -1 ������ , 0~9 ����ȣ )
			g_ii[6] = atoi( g_Buf );
			arg = AnyOneArg( arg, g_Buf );	//���� ������.(�ʴ���time_t) ///07-05-03 ���� ��¥�� ǥ���ϱ� ���� ó��.
			g_ii[7] = (int)atol( g_Buf ); // unsigned ���ӿ� ����.
			if( g_pNk2DFrame->GetControlHelper() )
				g_pNk2DFrame->GetControlHelper()->Information(g_ii[2], count, g_Buf1, g_ii[3], g_ii[5], g_ii[4], g_ii[6], (DWORD)g_ii[7] );
		}
	}
	else if ( !strcmp(g_Buf, "disband") )
	{
		arg = AnyOneArg( arg, g_Buf );	//�ɸ� �ε���
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf1 ); //�߽��� �̸�
		char strTemp[128] = "";
		sprintf(strTemp, (char*)G_STRING(IDS_GIVEUP_CONNET_HELPER), g_Buf1);
		g_pNk2DFrame->InsertPopup(strTemp, TYPE_NOR_OK, 1);
	}
	else if (!strcmp(g_Buf, "succ"))	// ����
	{
		arg = AnyOneArg( arg, g_Buf );	//�İ���/�߽���
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//�ɸ� �ε���
		g_ii[1] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf1 ); //�İ���/�߽��� �̸�

		char strTemp[128] = "";
		if( g_ii[0] == 0 )
		{
			sprintf(strTemp, (char*)G_STRING(IDS_CONNECT_HELPER_END_FAMEPLUS), g_Buf1); ///07-04-23 ������ �޼����� ��µǰ� �־���.
			g_pNk2DFrame->InsertPopup(strTemp, TYPE_NOR_OK_LARGE, 1);
		}
		else if( g_ii[0] == 1 )
		{
			sprintf(strTemp, (char*)G_STRING(IDS_CONNECT_END_HELPER), g_Buf1);
			g_pNk2DFrame->InsertPopup(strTemp, TYPE_NOR_OK_LARGE, 1);
		}
	}
	else if (!strcmp(g_Buf, "fail"))	// ����
	{
		arg = AnyOneArg( arg, g_Buf );	//�İ���/�߽���
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//�ɸ� �ε���
		g_ii[1] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf1 ); //�߽��� �̸�
		char strTemp[128] = "";
		if( g_ii[0] == 0 )
		{
			sprintf(strTemp, (char*)G_STRING(IDS_TIMEOVER_FAIL_HELPER), g_Buf1);
			g_pNk2DFrame->InsertPopup(strTemp, TYPE_NOR_OK, 1);
		}
		else if( g_ii[0] == 1 )
		{
			sprintf(strTemp, (char*)G_STRING(IDS_TIMEOVER_FAIL_HELPER), g_Buf1);
			g_pNk2DFrame->InsertPopup(strTemp, TYPE_NOR_OK, 1);
		}
	}
	else if(!strcmp(g_Buf, "conn"))	// ���� ���� ����
	{
		arg = AnyOneArg( arg, g_Buf );	//�ɸ� �ε���
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//���� ����
		g_ii[1] = atoi( g_Buf );
		if( g_pNk2DFrame->GetControlHelper() )
			g_pNk2DFrame->GetControlHelper()->ConnectState( g_ii[0], g_ii[1] );
	}
	else if( !strcmp(g_Buf, "enable") )
	{
		arg = AnyOneArg( arg, g_Buf );	//1: ���� 2: �Ⱓ ���� 3: ���� ���� �����ƴ�
		g_ii[0] = atoi( g_Buf );
		if( g_pNk2DFrame->GetControlHelper() )
			g_pNk2DFrame->GetControlHelper()->HelperExplan( g_ii[0] );
	}
}

void CmdSpirit(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	if (!strcmp(g_Buf, "start"))
	{
		arg = AnyOneArg( arg, g_Buf );	//�ɸ��ε���
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//��ǥ ����
		g_ii[1] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//���� �ð�(��)
		g_ii[2] = atoi( g_Buf );

		int nTaget_Hundred = g_ii[1] / 100;
		int nTaget_Ten     = ( g_ii[1] - nTaget_Hundred * 100 ) / 10;
		int nTaget_One     = g_ii[1] - ( nTaget_Hundred * 100 ) - ( nTaget_Ten * 10 );

		if( g_pRoh->m_nCharIndex == g_ii[ 0 ] )
		{
			g_pNk2DFrame->m_bSpiritStart = TRUE;
			pCMyApp->m_SpiritRotateCamera = TRUE;
			pMgr->SpiritPoint( 0, 0, 0, nTaget_One, nTaget_Hundred, nTaget_Ten, nTaget_One);
			pMgr->SpiritTime(g_ii[2]);
		}

		pCha = pMgr->FindChaById(g_ii[0], TRUE);
		if( pCha )
		{
			pMgr->InsertMagic( pCha, NULL, NULL, NULL, EFFECT_SPIRITMODE );
			pCMyApp->StopHero();
			pCha->SetMotionState(CHA_SPIRITMODE);
		}
	}
	else if (!strcmp(g_Buf, "point"))
	{
		arg = AnyOneArg( arg, g_Buf );	//ȹ���� ����
		g_ii[0] = atoi( g_Buf );
		arg = AnyOneArg( arg, g_Buf );	//��ǥ ����
		g_ii[1] = atoi( g_Buf );

		int nGet_Thousand = g_ii[0] / 1000;
		int nGet_Hundred = ( g_ii[0] - nGet_Thousand * 1000 ) / 100;
		int nGet_Ten     = ( g_ii[0] - ( nGet_Thousand * 1000 ) - ( nGet_Hundred * 100 ) ) / 10;
		int nGet_One     = g_ii[0] - ( nGet_Thousand * 1000 ) - ( nGet_Hundred * 100 ) - ( nGet_Ten * 10 );

		int nTaget_Hundred = g_ii[1] / 100;
		int nTaget_Ten     = ( g_ii[1] - nTaget_Hundred * 100 ) / 10;
		int nTaget_One     = g_ii[1] - ( nTaget_Hundred * 100 ) - ( nTaget_Ten * 10 );

		pMgr->SpiritPoint( nGet_Thousand, nGet_Hundred, nGet_Ten, nGet_One, nTaget_Hundred, nTaget_Ten, nTaget_One);
	}
	else if (!strcmp(g_Buf, "time"))
	{
		arg = AnyOneArg( arg, g_Buf );	//���� �Ⱓ(��)
		g_ii[0] = atoi( g_Buf );
		pMgr->SpiritTime(g_ii[0]);
	}
	else if (!strcmp(g_Buf, "end"))
	{
		g_pNk2DFrame->m_bSpiritStart = FALSE;
		arg = AnyOneArg( arg, g_Buf );	//���� ����(0:����, 1:����)
		g_ii[0] = atoi( g_Buf );
	}
}

void CmdMobSay(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);
	if (g_ii[0] >= 0)
	{
		if (pMob = pMgr->FindMobById(g_ii[0]))
		{
			SkipSpaces(&arg);
			char *arg2 = AnyOneArg(arg, g_Buf);
			char *arg3 = arg2;
			SkipSpaces(&arg3);

			arg2 = AnyOneArg(arg, g_Buf);
			pMob->SetMobChatMsg(arg3);
			*arg2 = ')';
			SkipSpaces(&arg);
			if( g_pNk2DFrame )
				g_pNk2DFrame->AddChatStr(arg, 1);
		}
	}
}

void CmdAlive(char *arg, CUIMgr *pMgr)
{
	// ������ ���� ���¸� Ǯ���ֱ����� ������ ��α����� �õ��ϸ� ������ ���� alive�� ����´�. �̰� ������ ������ alive�� ������ ��¥ ���������� ǥ�����ش�.(���� ���ΰŶ�� alive�� �ȳ��� ���� �̰� �������� �������� �����ش�.)
	if( g_pTcpIp )
		g_pTcpIp->SendNetMessage( "alive\n" );
}

void CmdAttChange(char *arg, CUIMgr *pMgr) // ������ �Ӽ����� ���. ///�δ�1
{
	arg = AnyOneArg( arg, g_Buf );	// �Ӽ���.
	g_ii[0] = atoi( g_Buf );

	float x1,y1,x2,y2;

	arg = AnyOneArg( arg, g_Buf );	// ��ǥ
	x1 = atof( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// ��ǥ
	y1 = atof( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// ��ǥ
	x2 = atof( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// ��ǥ
	y2 = atof( g_Buf );

	pCMyApp->GetLandPtr()->SetFieldAttr( x1, y1, x2, y2, (BOOL)g_ii[0] ); // �Ӽ� ����. // 1�̸� �̵�����, 0�̸� �̵� �Ҵ�.
}

void CmdEventAction(char *arg, CUIMgr *pMgr) // Ư������ �̺�Ʈ ���� ���� ��Ŷ. ///�δ�1
{
	float x,z,dir;

	arg = AnyOneArg( arg, g_Buf );	// �����ȣ
	g_ii[0] = atoi( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// x ��ǥ
	x = atof( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// z ��ǥ
	z = atof( g_Buf );
	arg = AnyOneArg( arg, g_Buf );	// ����
	dir = atof( g_Buf );

	if( g_ii[0] == -1 ) // ���� ���� ĵ�� ��� ///Ʃ�丮�� �� �߰�
	{
		pMgr->m_nNowPlayingEvent = 0;
	}
	else if( g_ii[0] == EVENTACTION_DEKAREN_BOSS_IN ) // �δ� ��ī�� ���� ���� ��.
	{
		if( !pMgr->IsEventScenePlaying() ) // �̳༮�� ī�޶� ��ǥ ��ﶧ���� �ߺ��ؼ� ���� ����ϴ�.(��ǥ�� ������ �ȴ�.)
			pMgr->StartEventScene( g_ii[0], x, z, dir );
	}
	else if( g_ii[0] >= EVENTACTION_DECKAREN_CUT_IN1 && g_ii[0] <= EVENTACTION_DECKAREN_CUT_IN3 ) // ��ī�� 1�� ���� �̺�Ʈ�̸�...
	{
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));
		ef_sort.nType = FX_TLVERTEX;
		ef_sort.Index = EFFECT_DECKAREN_CUT_IN;
		ef_sort.subNum = g_ii[0]-EVENTACTION_DECKAREN_CUT_IN1; // �̰� ���� ��ȣ
		ef_sort.dwColor = timeGetTime(); // ���� �ð����� ���.
		pCMyApp->m_pFxSet->InsertFxEffect( ef_sort );
	}
	else if( g_ii[0] == EVENTACTION_TUTORIAL ) ///Ʃ�丮��
	{
		if( !pMgr->IsEventScenePlaying() ) // �̳༮�� ī�޶� ��ǥ ��ﶧ���� �ߺ��ؼ� ���� ����ϴ�.(��ǥ�� ������ �ȴ�.)
			pMgr->StartEventScene( g_ii[0], x, z, dir );
	}
}

void CmdRevival(char *arg, CUIMgr *pMgr) // ��Ȱ ����
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf );

	pCha = pMgr->FindChaById(g_ii[0]);

	if (pCha)
	{
		if (pCha == g_pRoh )
		{
			g_pNk2DFrame->DeletePopup();
		}

		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));
		ef_sort.nType = FX_RESURRECTION;

		ef_sort.pNkChaTo = pCha;
		pCha->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));

		pCha->m_DeadFrame = -1;
		pCha->m_Vital = 1;
		pCha->m_AttackVital = 1;

		pCha->m_dwReturnTime = 0;
		pCha->SetMotionState(CHA_STAND);

		if (g_pDSound)
			g_pDSound->Play(g_EffectSound[EFF_SND_REVIVAL]);
	}
}

void CmdSkillCoolTime(char *arg, CUIMgr *pMgr) // ������ ��Ÿ�� ���� ��Ŷ ///�������ູ��Ÿ���� �������� �����ϵ��� �ٲ��.
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// skill_idx
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// kind  // 0:��Ȱ��, 1:Ȱ��, 2:��Ÿ�� ����

	if( g_ii[1] == 0 ) // ��Ȱ��
	{
		// �� ����� �ϴ� ���� ������ �ʰ�, ������ �����ؼ� ����. ���߿� �ʿ��ϸ� ����.
	}
	else if( g_ii[1] == 1 ) // Ȱ��
	{
		// �� ����� �ϴ� ���� ������ �ʰ�, ������ �����ؼ� ����. ���߿� �ʿ��ϸ� ����.
	}
	else if( g_ii[1] == 2 ) // ��Ÿ�� ����
	{
		G_SK_SetCooltime( g_ii[0] );
	}
}

void CmdCheckJoin(char *arg, CUIMgr *pMgr) ///�븸ű��� ��Ŷ. �ٸ� ������ �ڽ��� ������ ����������� �˸�.
{
	// �� ��Ŷ�� ������ �޼��� �ڽ� �ϳ� ����ְ� ��.
	if( g_pNk2DFrame )
	{
		//-IDS_WARRING_LOGINKICK : ������ ���� �������� �����Ͽ����ϴ�. ������ �����մϴ�. ����� ���� ��ȣ�� ������� �ʾҴ��� �����Ͻñ� �ٶ��ϴ�.
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_WARRING_LOGINKICK), TYPE_NOR_OK, 4 ); // 4�� Ÿ�� �޼��� �ڽ��� �ؾ��Կ� ����.(Ŭ���̾�Ʈ ����� �˾��̴�. "���������� ���������ϴ�."�� �ȶ߰� �ϱ� ����.)
	}

	g_pTcpIp->SetTerminate();
}

void CmdNvNWinner(char *arg, CUIMgr *pMgr) ///�������¸� ��ũ ǥ��.
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// ĳ����

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);			// �¸� Ƚ��

	pCha = pMgr->FindChaById( g_ii[0] ); // �ڱ� �����ؼ� ã�´�.
	if( pCha )
	{
		pCha->m_NvNWin = g_ii[1]; // �¸� Ƚ�� ����.
	}
}


// [4/20/2007 Theodoric] �±� ���� â�� ���� ��Ŷ
void CmdStashCInfo(char *arg, CUIMgr *pMgr )
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// skill_idx
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	if( g_pNk2DFrame )
		g_pNk2DFrame->GetControlWareHouse()->SetCashInfo( g_ii[0], g_ii[1]);
}


void CmdPingTest(char *arg, CUIMgr *pMgr )
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi( g_Buf);

	if( g_ii[0] == 1 )
		PingTest.start();
	else
		PingTest.check();

}



void CmdEnchant(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	switch( g_ii[0] )
	{
	case -4:
		break; // �߸��� ��ȣ
	case -3:
		break; // �߸��� ������
	case -2:
		break; // ������
	case -1:
		break; // ��ȭ����
	case  0:
		break; // �ʱ�ȭ ����
	case  1:
		break; // ��ȭ����
	}

	if( pMgr )
	{
		pMgr->PlatimumExch(5,g_ii[0], 0, 0, 0);
	}
}

// [2/27/2007 Theodoric] ��þƮ�� ������ ������ ����
void CmdRepair(char *arg, CUIMgr *pMgr)
{
	if(	g_SvrType != ST_ADULT_ONLY ) // [6/1/2007 Theodoric] ������ ����
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if( !pCMyApp->m_pUIMgr->m_bAutoHunt )
	{
		switch( g_ii[0] )
		{
		case -4: // IDS_REPAIR_FAIL_ITEM01 "������ �� ���� �������Դϴ�."
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_REPAIR_FAIL_ITEM01),TYPE_NOR_OK, 1 );
			break;

		case -3: // IDS_REPAIR_FAIL_ITEM02 "���� ������� ������ �� �ֽ��ϴ�."
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_REPAIR_FAIL_ITEM02),TYPE_NOR_OK, 1 );
			break;

		case -2: // IDS_REPAIR_FAIL_NOTHING "������ �������� �����ϴ�."
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_REPAIR_FAIL_NOTHING),TYPE_NOR_OK, 1 );
			break;

		case -1: // IDS_WANTED_REG_FAIL_LAIM "������ �����մϴ�."
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_WANTED_REG_FAIL_LAIM),TYPE_NOR_OK, 1 );
			break;

		case  1: // IDS_REPAIR_SUC "������ ������ �Ϸ�Ǿ����ϴ�."
			g_pNk2DFrame->InsertPopup((char*)G_STRING(IDS_REPAIR_SUC),TYPE_NOR_OK, 1 );
			break;
		}
	}
}

void CmdPVP(char *arg, CUIMgr *pMgr) ///�������
{
	char strTemp[256] = "";

	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf ); // ��Ŷ ����. �� �༮�� �ܾ�ƴ� ��ȣ�� �������ڰ� ���������� ��û����.

	if( g_ii[0] == 1 ) // req ��û ����.
	{
		arg = AnyOneArg( arg, g_Buf );	//ĳ����

		// �ܼ��� ����⸸ �ϸ��.
		// IDS_F_PVP_REQ "%s ���� �ܷ�⸦ ��û �Ͽ����ϴ�. �����Ͻðڽ��ϱ�?"
		sprintf( strTemp, (char*)G_STRING(IDS_F_PVP_REQ), g_Buf );
		g_pNk2DFrame->InsertPopup( strTemp, TYPE_NOR_OKCANCLE, 39 );
	}
	else if( g_ii[0] == 2 ) // ans ��û�� ���� ���
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[1] = atoi( g_Buf );

		arg = AnyOneArg( arg, g_Buf ); // ��� �̸�.

		if( g_ii[1] == 1 ) // ����
		{
			// ����μ� ���� �ƹ��͵� ���ص� �� ��.
		}
		else if( g_ii[1] == 0 ) // ����
		{
			// IDS_F_PVP_REQ_FAIL "%s ���� �ܷ�⸦ ���� �Ͽ����ϴ�."
			sprintf( strTemp, (char*)G_STRING(IDS_F_PVP_REQ_FAIL), g_Buf );
			g_pNk2DFrame->InsertPopup( strTemp, TYPE_NOR_OK, 1 );
		}
	}
	else if( g_ii[0] == 3 ) // start ����
	{
		arg = AnyOneArg( arg, g_Buf );	// ��Ŷ Ÿ��
		g_ii[1] = atoi( g_Buf );

		if( g_ii[1] == 0 ) // �� ���� ��û ( ����� ���ε鿡�Ը� ������ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf );   // x��ǥ.
			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf );   // z��ǥ.

			g_pRoh->m_vPvpRingPos.x = (float)g_ii[2];
			if( pCMyApp->GetLandPtr() )
				g_pRoh->m_vPvpRingPos.y = pCMyApp->GetLandPtr()->GetHFHeight((float)g_ii[2], (float)g_ii[3]);
			else // ���࿡�� ���ٸ�.
				g_pRoh->m_vPvpRingPos.y = g_pRoh->m_wy; // �ϴ� �ڽ� ��ġ��..
			g_pRoh->m_vPvpRingPos.z = (float)g_ii[3];
			g_pRoh->m_dwRingCreateTick = timeGetTime(); // �ð��� ���.
			pCMyApp->CreateBattleStart(3); // ������� ���� ī��Ʈ.
		}
		else if( g_ii[1] == 1 ) // ����� �ε��� ( �� �ȿ� �ִ� ����鿡�� ���� ������ )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[2] = atoi( g_Buf );   // �ε���1
			arg = AnyOneArg( arg, g_Buf );
			g_ii[3] = atoi( g_Buf );   // �ε���2

			pCha = pMgr->FindChaById(g_ii[2], TRUE); // �ڽŵ� �����ؼ� ã�´�.
			pCha2 = pMgr->FindChaById(g_ii[3], TRUE); // �ڽŵ� �����ؼ� ã�´�.
			if( pCha )
				pCha->m_bNowFreePVP = TRUE;
			if( pCha2 )
				pCha2->m_bNowFreePVP = TRUE;

			if( pCha == g_pRoh ) // �ڱ� �ڽ��̸�...
			{
				g_pRoh->m_dwPvpDestIndex = g_ii[3]; // ������ �ֵ� ���� �ε����� ����صд�.

				g_pNk2DFrame->CloseAllWindow();
				g_pNk2DFrame->GetPVPWidget()->SetPVPInfo(pCha, pCha2); // ������ �� UI�� �׸���.
				g_pNk2DFrame->ShowPVPWidget(TRUE); // ������ �� UI�� �׸���.
			}
			if( pCha2 == g_pRoh ) // �ڱ� �ڽ��̸�...
			{
				g_pRoh->m_dwPvpDestIndex = g_ii[2]; // ������ �ֵ� ���� �ε����� ����صд�.

				g_pNk2DFrame->CloseAllWindow();
				g_pNk2DFrame->GetPVPWidget()->SetPVPInfo(pCha2, pCha); // ������ �� UI�� �׸���.
				g_pNk2DFrame->ShowPVPWidget(TRUE); // ������ �� UI�� �׸���.
			}
		}
	}
	else if( g_ii[0] == 5 ) // result ���
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[1] = atoi( g_Buf );   // ���� 0 ���� 1
		arg = AnyOneArg( arg, g_Buf );
		g_ii[2] = atoi( g_Buf );   // �ε���

		// ���� ���� ����Ʈ�� �����ָ� ��
		pCha = pMgr->FindChaById(g_ii[2], TRUE); // �ڽŵ� �����ؼ� ã�´�.

		if( pCha )
		{
			if( g_ii[1] == 0 ) // ������ ���
			{
				pCha->SetShowCrash_Miss( 22 );
			}
			else if( g_ii[1] == 1 ) // ������ ���
			{
				pCha->SetShowCrash_Miss( 21 );
				pCha->SetMotionState( CHA_STAND ); // ���ڴ� ���ְ�. (������ ���� ���� �ʿ�)
			}

			if( pCha == g_pRoh ) // �ڱ� �ڽ��� ���ԵǾ�������...
			{
				// �����ϴ��� ���ߵ���.
				pMgr->m_b_MotionForAttack = false;
				pMgr->m_b_MovingForAttack= false;
				pMgr->m_b_Attack= false;
				pMgr->m_b_SecAttack = false;
				pMgr->m_bChakramAtt = false;
				pMgr->m_bChakram = false;
				pMgr->m_bBookSpellAtt = false;
				pMgr->m_bBookSpell = false;

				pCha->m_MagicChaId[0] = -1;
				pCha->m_MagicMobId[0] =  -1;
				pCha->m_MagicChaCount = 0;
				pCha->m_MagicMobCount = 0;
				pCha->m_AttackChaId = -1;
				pCha->m_AttackMobId = -1;

				pCMyApp->SetHeroAttGoMob( NULL ); // ���� ��� �����͸� �ʱ�ȭ(�� �ȿ��� ���ݴ�� �� �ܿ� ĳ���͵� �ʱ�ȭ �ȴ�.)
				pCMyApp->SetHeroAttGoCha( NULL ); // ���� ��� �����͸� �ʱ�ȭ(�� �ȿ��� ���ݴ�� �� �ܿ� ĳ���͵� �ʱ�ȭ �ȴ�.)

				if( pCMyApp->DrawBattleStart )
				{
					pCMyApp->DeleteBattleStart();
					pCMyApp->DrawBattleStart = FALSE;
				}
			}
		}
	}
	else if( g_ii[0] == 4 ) // end ��� ����(���� ���� �´�. ��, 2�� �´�) (result 3���Ŀ� ��)
	{
		arg = AnyOneArg( arg, g_Buf );
		g_ii[1] = atoi( g_Buf );   // �ε���1

		// ��,������ ����(�÷��׸� ���� �ڵ����� �Ⱥ���.���� ���� �ʿ�� ����.)
		pCha = pMgr->FindChaById(g_ii[1], TRUE); // �ڽŵ� �����ؼ� ã�´�.
		if( pCha )
		{
			pCha->m_bNowFreePVP = FALSE;
			pCha->m_dwPvpDestIndex = 0; // �굵 ������ �ʱ�ȭ

			g_pNk2DFrame->ShowPVPWidget(FALSE); // ������ �� UI�� �׸���.
		}
	}
	else if( g_ii[0] == 6 ) // In ��Ŷ
	{
		arg = AnyOneArg( arg, g_Buf );	// �ε���
		g_ii[1] = atoi( g_Buf );

		pCha = pMgr->FindChaById(g_ii[1], TRUE); // �ڽŵ� �����ؼ� ã�´�.
		if( pCha )
			pCha->m_bNowFreePVP = TRUE; // �̰� �ڱ� �ڽſ��� ������ ������ �ε��� ������ �ʿ����.
	}
	else if( g_ii[0] == 7 ) // �������� ����
	{
		arg = AnyOneArg( arg, g_Buf );	// �÷��̾� HP
		g_ii[1] = atoi( g_Buf );

		arg = AnyOneArg( arg, g_Buf );	// �� HP
		g_ii[2] = atoi( g_Buf );

		g_pNk2DFrame->GetPVPWidget()->SetPVPStatus(g_ii[1], g_ii[2]);
	}
	else if( g_ii[0] == 8 ) // ���� ���
	{
		int player_win = 0;
		int player_lose = 0;
		int enemy_win = 0;
		int enemy_lose = 0;

		arg = AnyOneArg( arg, g_Buf ); // �÷��̾� �¼�
		player_win = atoi( g_Buf );

		arg = AnyOneArg( arg, g_Buf ); // �÷��̾� �й��
		player_lose = atoi( g_Buf );

		arg = AnyOneArg( arg, g_Buf ); // �� �¼�
		enemy_win = atoi( g_Buf );

		arg = AnyOneArg( arg, g_Buf ); // �� �й��
		enemy_lose = atoi( g_Buf );

		g_pNk2DFrame->GetPVPWidget()->SetPVPRecord(player_win, player_lose, enemy_win, enemy_lose);
	}
	else if( g_ii[0] < 0 ) // fail ��û�� ���� ����
	{
		if( g_ii[0] == -1 ) // not response
		{
			// IDS_F_PVP_REQ_FAIL_DONT_MEG "������ ������ ���� ���� ����� ��� �Ǿ����ϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_F_PVP_REQ_FAIL_DONT_MEG), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -2 ) // not found target
		{
			// IDS_F_PVP_REQ_FAIL_MISS_CHA "������ ã�� �� �����ϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_F_PVP_REQ_FAIL_MISS_CHA), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -3 ) // not battle
		{
			// IDS_F_PVP_CANCEL_ATTACK "����� �������� �ʾ� ��������� ��� �Ǿ����ϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_F_PVP_CANCEL_ATTACK), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -4 ) // out area
		{
			// IDS_F_PVP_CANCEL_RANGE "������� ������ ��� ��������� ��� �Ǿ����ϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_F_PVP_CANCEL_RANGE), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -5 ) // already doing
		{
			// IDS_F_PVP_REQ_FAIL_ING  "�̹� �ٸ� ����� ��� ���Դϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_F_PVP_REQ_FAIL_ING), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -6 ) //
		{
			// IDS_F_PVP_FAIL_HEALTH "HP�� �� ã������ ��û�Ͻ� �� �ֽ��ϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_F_PVP_FAIL_HEALTH), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -7 ) //
		{
			// IDS_PVP_FAIL_LEVEL "������ ���� ������� ��û�� �����߽��ϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_PVP_FAIL_LEVEL), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -8 ) //
		{
			// IDS_PVP_FAIL_ZONE "������� �Ұ� �����Դϴ�."
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_PVP_FAIL_ZONE), TYPE_NOR_OK, 1 );
		}
		if( g_ii[0] == -9 ) //
		{
			// IDS_PVP_FAIL_GUILD_INVASION "��� ħ���� �߿��� ������� ��û �Ұ��Դϴ�."
			g_pNk2DFrame->InsertPopup(  (char*)G_STRING(IDS_PVP_FAIL_GUILD_INVASION), TYPE_NOR_OK, 1 );
		}
	}
}

void CmdGuildSystem(char *arg, CUIMgr *pMgr)
{
	static char cmd[100];

	arg = AnyOneArg(arg, cmd);
	g_pGuildCmd->guild_run(cmd, arg);
}

void CmdSVN(char *arg, CUIMgr *pMgr)
{
	if( CommonConfig::Instance()->GetGuildMark() == false )
		return;

	char buffer[256];
	arg = AnyOneArg(arg, buffer);

	int serverIndex = atoi(buffer);

	if( pMgr->thread_create(serverIndex) )
		pMgr->m_phttpConnection = CHttpConnection::Create();	
}

void CmdWantedSystem(char *arg, CUIMgr *pMgr)
{
	if( g_SvrType != ST_ADULT_ONLY )
		return;

	static char cmd[100];

	arg = AnyOneArg(arg, cmd);
	g_pWantedCmd->wanted_run(cmd, arg);
}

void Cmdkillporc(char *arg, CUIMgr *pMgr)   // 9980765 filename
{
	CHackProcessMgr* HProcMgr = CHackProcessMgr::GetInstance();

	char EncString[512]	= {0,};
	char ProcName[64]	= {0,};


	{
		arg = AnyOneArg( arg, EncString );
		arg = AnyOneArg( arg, g_Buf );
		int quest = atoi( g_Buf );

		HProcMgr->DecodeAutoProcessName(ProcName, EncString );

		ZeroMemory( EncString, strlen(EncString));
		ZeroMemory( ProcName, strlen(ProcName));
	}
}


void CmdHelpPet(char *arg, CUIMgr *pMgr ) ///�굵��
{
	arg = AnyOneArg(arg, g_Buf);

	if( !strcmp(g_Buf, "run") ) // ���� ���� �ߵ� �޼������� ���� üũ
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);          // �ߵ� ����.

		if( g_pNk2DFrame && g_pNk2DFrame->IsHelpPetVisible() && g_pNk2DFrame->GetControlHelpPet() ) ///�굵�� �� �ߵ� ������ üũ�Ѵ�.
			g_pNk2DFrame->GetControlHelpPet()->CheckHelpCondition( 3, g_ii[1], TRUE ); // ������ ���� ������ ������ �ִ��� üũ�Ѵ�.


		return;
	}

	// �������� ���� �ʰ� Ŭ���̾�Ʈ���� ���� Ű�� ������� �ٲ��.( �׷��� ���������� Ű�� �����ֵ��� ���� �ҽ��� ���ܵд�. )
	g_ii[0] = atoi(g_Buf);			// �� Ÿ��.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);          // On/Off �÷���.

	if( g_pNk2DFrame )
		g_pNk2DFrame->ShowHelpPetWindow( g_ii[1], g_ii[0] ); // ���� ���� �ݴ��ӿ� ����!
}

void CmdEventWearTime(char *arg, CUIMgr *pMgr ) ///�̺�Ʈ��������
{
	arg = AnyOneArg(arg, g_Buf);

	g_ii[0] = atoi( g_Buf);

	if( g_pNk2DFrame && g_pNk2DFrame->GetControlInven() )
	{
		g_pNk2DFrame->GetControlInven()->m_EventWearTime = g_ii[0];
		g_pNk2DFrame->GetControlInven()->m_EventWearTimeUpdateTick = timeGetTime();	// ���� ���ŵ� �ð��� üũ.
	}
}

void CmdEventWearing(char *arg, CUIMgr *pMgr) // �ڱ� �ڽ� �̺�Ʈ ���� �κ� ���� ���� ///�̺�Ʈ��������
{
	int special2[WEARING_NUM], up_endur[WEARING_NUM], max_up_endur[WEARING_NUM], endur[WEARING_NUM], max_endur[WEARING_NUM];

	if( g_pRoh == NULL )
		return;

	for(int i = 0; i < WEARING_NUM; i++)
	{
		arg = AnyOneArg(arg, g_Buf);
		index[i] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		v_num[i] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		gem_num[i] = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		special[i] = atoi(g_Buf);
		///�Ź���ȭ�ý���
		arg = AnyOneArg(arg, g_Buf);
		special2[i] = atoi(g_Buf); // �߰� �ɼ� m_Special2.
		arg = AnyOneArg(arg, g_Buf);
		up_endur[i] = atoi(g_Buf); // ���� ��ȭ ������ ��ġ.
		arg = AnyOneArg(arg, g_Buf);
		max_up_endur[i] = atoi(g_Buf); // �ƽ� ��ȭ ������.

		if( g_SvrType == ST_ADULT_ONLY )
		{
			arg = AnyOneArg(arg, g_Buf);
			endur[i] = atoi(g_Buf);		// �Ϲ� ������
			arg = AnyOneArg(arg, g_Buf);
			max_endur[i] = atoi(g_Buf); // �Ϲ� ������ max
		}
		else
		{
			endur[i] = 0;
			max_endur[i] = 0;
		}

		g_pRoh->EventWear(i, index[i], v_num[i], gem_num[i], special[i], special2[i], up_endur[i], max_up_endur[i], endur[i], max_endur[i] );
	}	
}


// [9/11/2007 Theodoric] Siren
void CmdSiren(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf );   // ĳ���� �ε���

	arg = AnyOneArg( arg, g_Buf );
	g_ii[1] = atoi( g_Buf );   // ���̷� on/off

	arg = AnyOneArg( arg, g_Buf );
	g_ii[2] = atoi( g_Buf );   // ���̷� ����

	pMgr->Siren_flag(g_ii[1], g_ii[0], g_ii[2]);

}

void CmdOccp(char* arg, CUIMgr * pMgr) //���Ʈ�� ������
{
	arg = AnyOneArg(arg, g_Buf);

	//������ ���� ����
	if (strcmp(g_Buf , "info") == 0)
	{
		for(int i = 0; i < 5; ++i)
		{
			arg = AnyOneArg(arg, g_Buf);  // ���� ��ȣ
			int nIndex = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf2); // ��� �̸�
			arg = AnyOneArg(arg, g_Buf);
			int nStatus = atoi(g_Buf);	  // ���� ����
			arg = AnyOneArg(arg, g_Buf);
			int nBuff1 = atoi(g_Buf); // ���� ����1
			arg = AnyOneArg(arg, g_Buf);
			int nBuff2 = atoi(g_Buf); // ���� ����2

			if (g_pNk2DFrame)
			{
				CDmitronInfo::SetZoneInfo1( nIndex, g_Buf2, nStatus, nBuff1, nBuff2 );//������ ����
			}
		}

		if (g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_DMITRON_BATTLE) == TRUE)
		{
			CDmitronBattle* pDmitronBattle = (CDmitronBattle*)
											 g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE);
			pDmitronBattle->UpdateState();
		}
	}
	//���� ���� / ã��
	else if (strcmp(g_Buf , "cash") == 0)
	{
		arg = AnyOneArg(arg, g_Buf);
		if (strcmp(g_Buf , "open") == 0)
		{
			arg = AnyOneArg(arg, g_Buf);
			g_ii[0] = atoi(g_Buf);			// ����¡����
			arg = AnyOneArg(arg, g_Buf);
			g_ii[1] = atoi(g_Buf);			// ������

			g_pNk2DFrame->GetUIWindow()->OnOpenWindow(WINDOW_DMITRON_BATTLE_TAX);
			CDmitronBattleTax* pDmitronBattleTax = (CDmitronBattleTax*)
												   g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE_TAX);
			pDmitronBattleTax->InitVariables(g_ii[0], g_ii[1]);
		}
	}
	// ����
	else if (strcmp(g_Buf , "buff") == 0)
	{
		arg = AnyOneArg(arg, g_Buf); // ���� ����
		g_ii[0] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf); // ���� ����
		g_ii[1] = atoi(g_Buf);

		CDmitronInfo::SetBuff(g_ii[0], g_ii[1]);
	}
	//
	else if (strcmp(g_Buf , "bt") == 0)
	{
		arg = AnyOneArg(arg, g_Buf); // ���� �޽���

		// ��Ż �̿�
		if (strcmp(g_Buf , "trans") == 0)
		{
			char buff[256];

			arg = AnyOneArg(arg, g_Buf); // ī��Ʈ
			int nCount = atoi(g_Buf);

			if (nCount <= 0) return;

			CControlGate* pGate = (CControlGate*)g_pNk2DFrame->GetInterface(GATE);
			pGate->RemoveAll();

			g_pNk2DFrame->ShowInterfaceWindow(true, GATE, 200);

			for(int i = 0; i < nCount; ++i)
			{
				arg = AnyOneArg(arg, g_Buf); // ī��Ʈ
				int nZone = atoi(g_Buf);

				arg = AnyOneArg(arg, g_Buf); // ī��Ʈ
				int nToll = atoi(g_Buf);

				char format[256];
				// IDS_DMITRON_PORTAL_COST : %s(%d����)
				strcpy(format, (char*)G_STRING(IDS_DMITRON_PORTAL_COST));
				sprintf(buff, format, CDmitronString::Portal(nZone), nToll);
				pGate->AddItem(buff, new DmitronGate(nZone, nToll));
			}

			if(pGate->GetSubType() == 5)
			{
				if (pCMyApp->m_nCurWorldIdx == WORLD_DMITRON)
				{
					pGate->AddItem((char*)G_STRING(IDS_GATE_LAGRAMIA), NULL); // ��׶�̾� ����
					pGate->AddItem((char*)G_STRING(IDS_GATE_WHITEHORN_DUNGEON), NULL); // ������ ������Ƽ
				}
				else if(pCMyApp->m_nCurWorldIdx == WORLD_DMITRON_BATTLE)
				{
					pGate->AddItem((char*)G_STRING(IDS_GATE_DMITRON), NULL); // ���Ʈ��
				}
			}
			pGate->EndItem();
		}
		else if (!strcmp(g_Buf, "list"))
		{
			for(int i = 0; i < 5; ++i)
			{
				arg = AnyOneArg(arg, g_Buf);
				int nIndex = atoi(g_Buf);	  // �ε���
				arg = AnyOneArg(arg, g_Buf2); // ��� �̸�
				arg = AnyOneArg(arg, g_Buf);
				int nStatus = atoi(g_Buf);	  // ���� ��Ȳ
				arg = AnyOneArg(arg, g_Buf);
				int nHelper = atoi(g_Buf);
				CDmitronInfo::SetZoneInfo2( nIndex, g_Buf2, nStatus, nHelper );//������ ����
			}

			g_pNk2DFrame->GetUIWindow()->OnOpenWindow(WINDOW_DMITRON_BATTLE);
			CDmitronBattle* pWindow = (CDmitronBattle*)
									  g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE);
			pWindow->UpdateState();
			return;
		}
		else if(!strcmp(g_Buf, "info"))
		{
			if (g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_DMITRON_BATTLE) == TRUE)
			{
				CDmitronBattle* pDmitronBattle = (CDmitronBattle*)
												 g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE);

				arg = AnyOneArg(arg, g_Buf2);
				int nTime = atoi(g_Buf2);

				arg = AnyOneArg(arg, g_Buf2);
				g_pNk2DFrame->GetUIWindow()->OnOpenWindow(WINDOW_DMITRON_BATTLE_INFO);
				CDmitronBattleInfo* pWindow = (CDmitronBattleInfo*)
											  g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE_INFO);
				pWindow->ActivateInfoWindow(nTime, g_pRoh->m_pstrGuildName, g_Buf2);
			}
			return;
		}
		else if(!strcmp(g_Buf, "req"))
		{
			if (g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_DMITRON_BATTLE) == TRUE)
			{
				CDmitronBattle* pDmitronBattle = (CDmitronBattle*)
												 g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE);

				CDmitronInfo::UpdateZone(TRUE);
				pDmitronBattle->UpdateState();
			}
			return;
		}
		else if(!strcmp(g_Buf, "fail"))
		{
			arg = AnyOneArg(arg, g_Buf2); // �ð�

			if (g_pNk2DFrame->GetUIWindow()->IsOpenWindow(WINDOW_DMITRON_BATTLE) == TRUE)
			{
				CDmitronBattle* pDmitronBattle = (CDmitronBattle*)
												 g_pNk2DFrame->GetUIWindow()->GetWindow(WINDOW_DMITRON_BATTLE);

				CDmitronInfo::UpdateZone(FALSE);
				pDmitronBattle->HandleError(atoi(g_Buf2));
			}
			return;
		}
		else if(!strcmp(g_Buf, "go"))
		{
			arg = AnyOneArg(arg, g_Buf);
			int nZone = atoi(g_Buf);

			arg = AnyOneArg(arg, g_Buf);
			int nSuccess = atoi(g_Buf);

			if (nSuccess)
			{
				pMgr->PrepareChangeWorld(TRUE, WORLD_DMITRON_BATTLE, nZone+1); //1�� ���� ��
			}
		}
		else if(!strcmp(g_Buf, "end"))
		{
			arg = AnyOneArg(arg, g_Buf2); // ����ȣ

			if (pMgr)
				pMgr->PrepareChangeWorld(TRUE, WORLD_DMITRON, 0);
		}
		return;
	}
	else if(!strcmp(g_Buf, "count"))
	{
		char myGuild[256], topGuild[256];
		g_pNk2DFrame->InitDmitronInfo();

		for( int i = 0; i < DMITRON_BATTLE_ZONE; ++i )
		{
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 0 ] = atoi( g_Buf ); // ���� ��ȣ
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 1 ] = atoi( g_Buf ); // �ΰ� ����
			arg = AnyOneArg( arg, g_Buf );
			g_ii[ 2 ] = atoi( g_Buf ); // ���� ����
			if (g_ii[ 1 ] == FALSE)
			{
				g_pNk2DFrame->SetDmitronInfo1( g_ii[ 0 ], g_ii[ 2 ] );
			}
			else
			{
				arg = AnyOneArg( arg, myGuild ); // �Ҽ� ��� �̸�
				arg = AnyOneArg( arg, g_Buf ); // �Ҽ� ��� ����
				g_ii[ 3 ] = atoi( g_Buf );

				arg = AnyOneArg( arg, topGuild ); // �ְ� ��� �̸�
				arg = AnyOneArg( arg, g_Buf ); // �ְ� ��� ����
				g_ii[ 4 ] = atoi( g_Buf );

				arg = AnyOneArg( arg, g_Buf );
				g_ii[ 5 ] = atoi( g_Buf ); // ���� �ð�

				arg = AnyOneArg( arg, g_Buf );
				g_ii[ 6 ] = atoi( g_Buf ); // ���� �ð�

				g_pNk2DFrame->SetDmitronInfo2( g_ii[ 0 ], g_ii[ 2 ],
											   myGuild, g_ii[ 3 ], topGuild, g_ii[ 4 ], g_ii[5], g_ii[6] );
			}
		}
		g_pNk2DFrame->DisplayDmitronInfo();
		return;
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);  // ����
		arg = AnyOneArg(arg, g_Buf2); // �ð�
		arg = AnyOneArg(arg, g_Buf3); // �ð�
		g_ii[0] = atoi(g_Buf3);

		arg = AnyOneArg(arg, g_Buf4); // Ÿ��
		g_ii[1] = atoi(g_Buf4);

		if( pMgr )
			pMgr->GetServMsg_WarReq(g_Buf2, g_ii[0], g_ii[1]);
	}
}

void CmdBossRaidAttack(char* arg, CUIMgr* pMgr)
{
	// bossraid_at [boss Vnum] [skill index] [boss mob index] [character index]

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);	// skill index

	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi(g_Buf);	// boss index

	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi(g_Buf);	// character index

	pMob = NULL;
	pCha = NULL;

	pMob = pMgr->FindMobById( g_ii[2] );
	pCha = pMgr->FindChaById( g_ii[3] );

	// ���Ͱ� ������ ����Ʈ�� �����ϸ� �ȵǴ�.
	if( pMob == NULL )
		return;

	switch( pMob->m_nMobNum ) // boss vnum
	{
	case 511:  // ��ĭ ���� 1
		// ���Ͱ� ������ ����Ʈ�� �����ϸ� �ȵǴ�.
		if( pCha == NULL )
			return;

		if( g_ii[1] == EFFECT_BOSSRAID_BULKAN1_02 || g_ii[1] == EFFECT_BOSSRAID_BULKAN1_03 )
		{
			pMob->SetMotionState( MOB_EMPTY1 + g_ii[1] - EFFECT_BOSSRAID_BULKAN1_02 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

	case 512: // ��ĭ ���� 2
		if( pCha == NULL )
			return;

		if( g_ii[1] == EFFECT_BOSSRAID_BULKAN2_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

	case 513: // ��ĭ ���� 3
		if( g_ii[1] == EFFECT_BOSSRAID_BULKAN3_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

//////////////////////////////////////////////////////////////////////////
	case 514: // �޸� ���� 1
		if( pCha == NULL )
			return;

		if( g_ii[1] == EFFECT_BOSSRAID_HUMAN1_02 || g_ii[1] == EFFECT_BOSSRAID_HUMAN1_03 )
		{
			pMob->SetMotionState(MOB_EMPTY1 + g_ii[1] - EFFECT_BOSSRAID_HUMAN1_02 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;
	case 515: // �޸� ���� 21
		if( pCha == NULL )
			return;

		if( g_ii[1] == EFFECT_BOSSRAID_HUMAN2_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		else if ( g_ii[1] == EFFECT_BOSSRAID_HUMAN2_03 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 6 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;
	case 516: // [12/13/2007 �����] �������̵� �޸պ���3-02 ��ų
		if( g_ii[1] == EFFECT_BOSSRAID_HUMAN3_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

//////////////////////////////////////////////////////////////////////////
	case 517: // ���̵�� ���� 1
		if( g_ii[1] == EFFECT_BOSSRAID_AIDIA1_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

	case 518: // ���̵�� ���� 2
		if( g_ii[1] == EFFECT_BOSSRAID_AIDIA2_02)
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		else if( g_ii[1] == EFFECT_BOSSRAID_AIDIA2_03)
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 6 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

	case 519: // ���̵�� ���� 3
		if( g_ii[1] == EFFECT_BOSSRAID_AIDIA3_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case 520: // ���̺긮�� ���� 1
	case 740: // ������ ���� 1
		if( g_ii[1] == EFFECT_BOSSRAID_HYBRI1_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;
	case 521: // ���̺긮�� ���� 2
		if( g_ii[1] == EFFECT_BOSSRAID_HYBRI2_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;
	case 522: // ���̺긮�� ���� 2

		if( g_ii[1] == EFFECT_BOSSRAID_HYBRI3_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}

		break;
//////////////////////////////////////////////////////////////////////////
	case 523: // ī�̸��� ���� 1
		if( g_ii[1] == EFFECT_BOSSRAID_KAI1_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

	case 524: // ī�̸��� ���� 2
		if( g_ii[1] == EFFECT_BOSSRAID_KAI2_02 || g_ii[1] == EFFECT_BOSSRAID_KAI2_03 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( MOB_EMPTY1 + g_ii[1] - EFFECT_BOSSRAID_KAI2_02 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}

		break;

	case 525: // ī�̸��� ���� 3
		if( g_ii[1] == EFFECT_BOSSRAID_KAI3_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		else if( g_ii[1] == EFFECT_BOSSRAID_KAI3_03 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 6 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;

//////////////////////////////////////////////////////////////////////////
	case 526: // ���� ���� 1
	case 648: // ���� ���� 1
		if( g_ii[1] == EFFECT_BOSSRAID_LASTBOSS_02 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 5 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		else if( g_ii[1] == EFFECT_BOSSRAID_LASTBOSS_03 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 6 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		else if( g_ii[1] == EFFECT_BOSSRAID_LASTBOSS_04 )
		{
			pMob->SetAttackChaId( g_ii[3] );
			pMob->SetMotionState( 6 );
			pMgr->InsertMagic( NULL, pMob, pCha, NULL, g_ii[1] );
		}
		break;
	}
}


void CmdBossRaidKill(char* arg, CUIMgr* pMgr)
{
	BOOL KillFlag;
	g_pNk2DFrame->InitBossRaidKillCount();

	for(int i=0; i<5; i++)
		for(int j=0; j<3; j++)
		{
			arg = AnyOneArg(arg, g_Buf);
			KillFlag = ( atoi(g_Buf) == 0 )? FALSE : TRUE;
			g_pNk2DFrame->SetBossRaidInfo(i,j,KillFlag);
		}
}

void CmdBossRaidLicense(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	switch( g_ii[1] )
	{
	case 0:
		g_pNk2DFrame->InitBossRaidKillCount();
		break;
	}
}

// [2008/4/29 Theodoric] ������ ���� ���嵵 ���� ����Ʈ
void CmdBossRaidFinalRank(char* arg, CUIMgr* pMgr)
{

// ���� ���� ���嵵 ���� ���� ��Ŷ ����

// ����
// br_rank list ������1,2,3���� ĳ���� ... (��ĭ,ī�̸���,���̵��,�޸�,���̺긮�� ��)

// ex) ��ĭ1��, ī�̸���1,2��, ���̺긮�� 1���� ������ ���
// br_rank list ��ĭ1�� -1 -1 ī�̸���1�� ī�̸���2�� -1 -1 -1 -1 -1 -1 -1 ���̺긮�� 1�� -1 -1

	arg = AnyOneArg(arg, g_Buf);

	if( !strnicmp("list", g_Buf, 4) )
	{
		g_pNk2DFrame->SetHeroFinalRank( arg );
	}
}


void CmdSvrChannelNum(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf);

	g_pRoh->SetSvrChannelNum( g_ii[1]);
}

void CmdPremium(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	if(!strcmp(g_Buf, "chname_ack"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);

		switch( g_ii[1] )
		{
		case 0:	// ���� ���� ���� �޽���
			{
				switch (g_ii[2])
				{
				case 1:		// IDS_PREMIUM_MSG_01 ������ ���� �Ǿ����ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_01), TYPE_NOR_OK, 1);
					break;
				case 0:		// IDS_PREMIUM_MSG_02 ���� ������� �����ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_02), TYPE_NOR_OK, 1);
					break;
				case -1:	// IDS_CRECHA_ALLEADY_EXIST �� �̸��� �̹� ��� �� �Դϴ�
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_CRECHA_ALLEADY_EXIST), TYPE_NOR_OK, 1);
					break;
				case -2:	// IDS_PREMIUM_MSG_03 ���� ���� ������ �����ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_03), TYPE_NOR_OK, 1);
					break;
				case -3: // IDS_ENCHANT_FAIL_ITEM �߸��� �������Դϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_ENCHANT_FAIL_ITEM), TYPE_NOR_OK, 1);
					break;
				case -4:	// IDS_PREMIUM_MSG_04 �߸��� �̸��Դϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_04), TYPE_NOR_OK, 1);
					break;
				}
			}
			break;

		case 1: // ĳ���͸� ���� �޽���
			{
				switch (g_ii[2])
				{
				case 1:		// IDS_PREMIUM_MSG_05 ĳ������ ���� �Ǿ����ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_05), TYPE_NOR_OK, 1);
					break;
				case 0:	// IDS_PREMIUM_MSG_06 ĳ���� ������� �����ϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_06), TYPE_NOR_OK, 1);
					break;
				case -1:	// IDS_CRECHA_ALLEADY_EXIST �� �̸��� �̹� ��� �� �Դϴ�
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_04), TYPE_NOR_OK, 1);
					break;
				case -3: // IDS_ENCHANT_FAIL_ITEM �߸��� �������Դϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_ENCHANT_FAIL_ITEM), TYPE_NOR_OK, 1);
					break;
				case -4:	// IDS_PREMIUM_MSG_04 �߸��� �̸��Դϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_04), TYPE_NOR_OK, 1);
					break;
				case -5:	// IDS_PREMIUM_MSG_07 ��� �� 1���� ���Ŀ� ������ �����մϴ�.
					g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_07), TYPE_NOR_OK, 1);
					break;
				}
			}
			break;
		}

		if( g_ii[2] == 1 )
		{
			arg = AnyOneArg(arg, g_Buf);
			int slot = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int index = atoi(g_Buf);
			g_pRoh->RemoveQuickItem(slot, index , false);
		}
	}
	else if(!strcmp(g_Buf, "chname_msg"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);


		pCha = NULL;

		switch( g_ii[1] )
		{
		case 0: // ���� ����
			{
				if( g_pRoh && g_pRoh->m_GuildIndex == g_ii[2] )
				{
					g_pRoh->SetGuildName(g_Buf);
					if( g_pNk2DFrame->GetControlGuild() )
						g_pNk2DFrame->GetControlGuild()->ChangeGuildInfo(g_Buf);
				}

				LHCharacterMap_it pr;
				for( pr = pMgr->m_character_map.begin(); pr != pMgr->m_character_map.end(); pr++ )
				{
					pCha = (*pr).second;
					if( pCha->m_GuildIndex == g_ii[2] )
						pCha->SetGuildName(g_Buf);
				}
			}
			break;

		case 1: // ĳ���͸� ����
			{
				pCha = pMgr->FindChaById(g_ii[2], TRUE);

				if (pCha)
					pCha->SetCharName(g_Buf);

				if( g_pNk2DFrame && g_pRoh->m_nCharIndex == g_ii[2])
				{
					((CControlScore*)g_pNk2DFrame->GetInterface(SCORE))->SetName();

					if( g_pNk2DFrame->GetControlStatus() )
						g_pNk2DFrame->GetControlStatus()->SetName();
				}
			}
			break;
		}
	}
	else if( !strcmp(g_Buf, "chmove_req_step") )
	{
		arg = AnyOneArg(arg, g_Buf);
		int step = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int flag = atoi(g_Buf);

		switch( step )
		{
		case 0:
			switch( flag )
			{
			case 0:	// IDS_PREMIUM_MSG_08 ĳ���� �̵� �������� ����մϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_08), TYPE_NOR_OKCANCLE, POPUP_PREMIUM_CHA_MOVE_FROM);
				break;
			case 1:	// IDS_PREMIUM_MSG_09 ĳ���� �̵� �������� ����� �� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_09), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 2:		// IDS_PREMIUM_MSG_07 ��� �� 1���� ���Ŀ� ������ �����մϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_07), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 3:		// IDS_PREMIUM_MSG_10 ���� �������� �������� �Ǹ� �߿��� ����� �� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_10), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 4:	// IDS_PREMIUM_MSG_11 ��� ���ԵǾ� �־� ����� �� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_11), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 5:	// IDS_PREMIUM_MSG_12 ��Ƽ �߿��� ����� �� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_12), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 6:	// IDS_PREMIUM_MSG_13 �İ��� �߿��� ����� �� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_13), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			} // switch( flag )
			break;

		case 2:
			switch( flag )
			{
			case 0:	// IDS_PREMIUM_MSG_14 �Է��Ͻ� ĳ���� ������ ã�� �� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_14), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 1:	// IDS_PREMIUM_MSG_15 �ش� ĳ���Ͱ� ��׶�̾� ���� �����ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_15), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 2:	// IDS_PREMIUM_MSG_16 �����ô� ���� ���� ������ �Ǿ����� �ʽ��ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_16), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 3:	// IDS_PREMIUM_MSG_17 �����ô� ���� ������ ������� �ʽ��ϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_17), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;
			case 4:		// IDS_PREMIUM_MSG_18 ��ø� ��ٷ� �ֽʽÿ�. ������ ��ٸ��� �� �Դϴ�.
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_18), TYPE_PREMIUM_CHA_MOVE_WAIT, POPUP_PREMIUM_CHA_MOVE_WAIT);
				break;
			case 5: // ���� ������� ���� â�� ����.
				{
					// ĳ���� ������ �̸� �޾� ��������.
					arg = AnyOneArg(arg, g_Buf);	// name from
					arg = AnyOneArg(arg, g_Buf1);	// name to
					arg = AnyOneArg(arg, g_Buf2);	// level
					int level = atoi(g_Buf2);
					arg = AnyOneArg(arg, g_Buf2);	// race
					int race = atoi(g_Buf2);

					// �⺻ ���� ����
					g_pNk2DFrame->GetPremmiumChaMove()->ClearChaInfo();
					g_pNk2DFrame->GetPremmiumChaMove()->SetChaInfo( g_Buf, g_Buf1, level, race );

					// ���� ��� ����
					//////////////////////////////////////////////////////////////////////////

					arg = AnyOneArg(arg, g_Buf2);	// wearing �� �����ش�. �׳� ���⼭ �ɷ�������.

					for(int i=0; i<WEARING_NUM; i++)
					{
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[0] = atoi(g_Buf2);
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[1] = atoi(g_Buf2);
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[2] = atoi(g_Buf2);
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[3] = atoi(g_Buf2);
						///�Ź���ȭ�ý���
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[4] = atoi(g_Buf2); // �߰� �ɼ� m_Special2.
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[5] = atoi(g_Buf2); // ���� ��ȭ ������ ��ġ.
						arg = AnyOneArg(arg, g_Buf2);
						g_ii[6] = atoi(g_Buf2); // �ƽ� ��ȭ ������.

						if( g_SvrType == ST_ADULT_ONLY)// [6/1/2007 Theodoric] ������ ����
						{
							arg = AnyOneArg(arg, g_Buf2);
							g_ii[7] = atoi(g_Buf2);		// �Ϲ� ������
							arg = AnyOneArg(arg, g_Buf2);
							g_ii[8] = atoi(g_Buf2);		// �Ϲ� ������ max
						}

						if( g_pNk2DFrame->GetPremmiumChaMove() )
						{
							if( g_SvrType == ST_ADULT_ONLY)
								g_pNk2DFrame->PremiumChaMoveWear(i, g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], g_ii[7], g_ii[8] ); ///�Ź���ȭ�ý���
							else
								g_pNk2DFrame->PremiumChaMoveWear(i, g_ii[0], g_ii[1], g_ii[2], g_ii[3], g_ii[4], g_ii[5], g_ii[6], 0, 0 ); ///�Ź���ȭ�ý���
						}
					}
					//////////////////////////////////////////////////////////////////////////
					g_pNk2DFrame->SetProcLock(TRUE);
					// IDS_PREMIUM_MSG_19 %s���� ĳ���� �̵��� ��û �Ͽ����ϴ�. ���Ͻðڽ��ϱ�?
					sprintf( g_Buf2, (char *)G_STRING(IDS_PREMIUM_MSG_19), g_Buf );
					g_pNk2DFrame->InsertPopup(g_Buf2, TYPE_NOR_OKCANCLE, POPUP_PREMIUM_CHA_MOVE_TO );
				}
				break;
			case 7:
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_LHSTRING1945), TYPE_NOR_OK, POPUP_PREMIUM_CHA_MOVE_FAIL);
				break;

			} // switch( flag )
			break;

		case 4:
			switch( flag )
			{
			case 0: // ������ ����
				g_pNk2DFrame->OnClosePremiumChaMove();
				break;
			case 1:
				g_pNk2DFrame->ClossePremiumMsgBox();
				// IDS_PREMIUM_MSG_20 ĳ���� �̵��� �Ϸ� �Ǿ����ϴ�. ��� �� ������ �ڵ� ���� �˴ϴ�.
				g_pNk2DFrame->SetForceExit();
				g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_20), TYPE_PREMIUM_CHA_MOVE_WAIT, POPUP_PREMIUM_CHA_MOVE_SUC_EXIT);

				break;
			case 2:
				{
					exit(1);
				}
				break;

			} // switch( flag )
			break;
		} // switch( step )

	}
	else if( !strcmp(g_Buf, "chmove_req_stop") ) // ĳ���� �̵� ���
	{
		g_pNk2DFrame->OnClosePremiumChaMove();
		// IDS_PREMIUM_MSG_21 ĳ���� �̵��� ���� �Ǿ����ϴ�.
		g_pNk2DFrame->InsertPopup((char *)G_STRING(IDS_PREMIUM_MSG_21), TYPE_NOR_OK );
	}
}

void CmdLaghaimPoint(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg( arg, g_Buf );
	g_ii[ 0 ] = atoi( g_Buf ); //LP

	if( g_pRoh )
		g_pRoh->SetLaghaimPoint( g_ii[0] );
	if( pMgr && g_pNk2DFrame && g_pNk2DFrame->IsShopVisible() )
		g_pNk2DFrame->GetControlShop()->SetMoney();
}


void CmdLPShopList(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg( arg, g_Buf);
	g_ii[0] = atoi(g_Buf);	// ����Ʈ ����

	if(g_pNk2DFrame->GetControlShop())
	{
		g_pNk2DFrame->GetControlShop()->LPShopIndexClear();
		g_pNk2DFrame->GetControlShop()->SetLpShopFlag();
		g_pNk2DFrame->GetControlShop()->RemoveAllItems();
	}

	for( int i = 0 ; i < g_ii[0] ; ++i )
	{

		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi(g_Buf);	// ���� Ÿ��(���� ��������..)

		arg = AnyOneArg(arg, g_Buf);
		g_ii[2] = atoi(g_Buf);	// Npc �ε���.

		if(g_pNk2DFrame->GetControlShop())
		{
			g_pNk2DFrame->GetControlShop()->AddLPShopIndex( g_ii[2] );
		}
	}

	// index�� ��� �޾����� â�� ����
	if(g_pNk2DFrame->GetControlShop())
	{
		g_pNk2DFrame->ShowShopWindow(TRUE);
		g_pNk2DFrame->GetControlShop()->SetLpShopFlag(TRUE);

	}



}

void CmdBossraidHonorList(char *arg, CUIMgr *pMgr)
{
	if( g_pNk2DFrame->GetHeroRankList() )
		g_pNk2DFrame->SetHeroRankList( arg );
}

void CmdBossraidHeroPrivilege(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	if( g_pNk2DFrame->GetHeroPrivilege() )
		g_pNk2DFrame->SetHeroPrivilege( atoi(g_Buf) );

}


void CmdEventWearFlag(char *arg, CUIMgr *pMgr)
{
	// ev_ewarflag [char_index] [flag] // flag 0:off 1:on

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf); // cha index

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi(g_Buf); // flag

	pCha = NULL;
	pCha = pMgr->FindChaById(g_ii[0], TRUE );

	if(pCha)
		pCha->m_bEventWearFlag = g_ii[1];
}


void CmdSetItem(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	if(!strcmp(g_Buf, "flag"))
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi( g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		g_ii[1] = atoi( g_Buf);

		if( g_pNk2DFrame && (CControlScore*)g_pNk2DFrame->GetInterface(SCORE) )
		{
			CControlScore* pScore = (CControlScore*)g_pNk2DFrame->GetInterface(SCORE);
			pScore->SetSetitemFlag(g_ii[0], g_ii[1]);
		}
	}
}



// [2008/8/14 Theodoric] ��ڰ� �κ��� �ս��� ����� ���� ���� ��Ŷ
void CmdInitInven(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi( g_Buf);

	g_pRoh->RemoveAllInven(g_ii[0] );
}

void CmdMatrixMsg(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi( g_Buf);
	pMgr->m_pMatrixWarMsg->MatrixMsgSet( g_ii[0] );
}

// [3/30/2009 D.K ] : ������ ���� ��ƾ �߰�
void CmdDeleteItem(char *arg, CUIMgr *pMgr)
{
	// by evilkiki 2010.12.09. ������ƾ ����
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi( g_Buf );			// quick slot No.
	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi( g_Buf );			// index No.
	g_pRoh->RemoveByIndex( g_ii[1] );
	g_pRoh->CountQuickAll();
}


/*
pMgr->ChipExchange(g_ii[0], TRUE, g_ii[1], g_ii[3], g_ii[2]);
else
pMgr->ChipExchangeMulti(g_ii[0], TRUE, g_ii[1], g_ii[4], g_ii[2], arg);

  g_pNk2DFrame->GetGamble()->ChipExchange(type, bResult, vnum, svr_idx, binggo_num);
*/
void CmdRulletSystem(char *arg, CUIMgr *pMgr)
{
	strcpy(g_pNk2DFrame->GetGamble()->m_szArg, arg);

	/*
	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi( g_Buf );		// 1 : ����,   -1 : ����

	arg = AnyOneArg(arg, g_Buf);
	g_ii[1] = atoi( g_Buf );		// ���ǽ���[ ������ȣ ], ���[ 0:��, 1:�ѹ���, 2:1�ܰ�up, 3:1�ܰ�down, 4:2�ܰ�down
									// 5:2��, 6:3��, 7:4��, 8:5��

	arg = AnyOneArg(arg, g_Buf);
	g_ii[2] = atoi( g_Buf );		// ���� ���� ������ vnum

	arg = AnyOneArg(arg, g_Buf);
	g_ii[3] = atoi( g_Buf );		// ���� ���� ���� ����

	printf("state : %d,  result : %d,  Ite0mvNum : %d,  ItemCnt : %d,  ItemChar : %s\n",
		g_ii[0], g_ii[1], g_ii[2], g_ii[3], arg);
	*/

}


void CmdStudentList(char * arg, CUIMgr *pMgr)
{
	if( g_pNk2DFrame->ControlSelmenuSetMetuList(1, arg) )
		g_pNk2DFrame->ShowControlSelMenu(TRUE);
}

void CmdLagrush( char* arg, CUIMgr* pMgr )
{
	AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf );

	pMgr->SetLagrushPayment( g_ii[0] );

	if( pMgr->m_bAutoHunt && g_ii[0] == 0 )
	{
		// ����?
		pMgr->m_AutoPlay->StopProc();
	}
}

void CmdLagrushTime(char* arg, CUIMgr* pMgr)
{
	AnyOneArg( arg, g_Buf );
	g_ii[0] = atoi( g_Buf );

	if( pMgr->m_bAutoHunt && g_ii[0] == 0 )
		pMgr->m_AutoPlay->StopProc(AutoPlay_StopProc__TimeOver);
	else
	{
		char buf[128];
		sprintf( buf , G_STRING(IDS_LHSTRING1728) , g_ii[0] );
		g_pNk2DFrame->GetControlBottom()->AddStrQlist( buf , -1 );
	}
}

void CmdLockSmith(char* arg, CUIMgr* pMgr)
{
	strcpy(g_pNk2DFrame->GetLockSmith()->m_MsgBuf, arg);
}

void CmdMoveValue(char *arg, CUIMgr *pMgr)
{
	arg = AnyOneArg(arg, g_Buf);

	g_ii[0] = atoi( g_Buf );		// 0 : 0%,   1 : 10%,   2 : 20%

	switch( g_ii[0] )
	{
	case 0:
		pCMyApp->m_fMoveValue = 0.0f;
		break;
	case 1:
		pCMyApp->m_fMoveValue = 0.25f;		// 0.1
		break;
	case 2:
		pCMyApp->m_fMoveValue = 0.5f;		// 0.2
		break;
	default:
		printf( "character move value error!!!");
		break;
	}
}

void CmdArupakaMoveValue(char *arg, CUIMgr *pMgr)
{
}

void CmdBuyItemFail(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int shop_no = atoi( g_Buf );
	arg = AnyOneArg(arg, g_Buf);
	int item_vnum = atoi( g_Buf );

	if( pMgr->m_AutoPlay->IsRun() )
	{
		pMgr->m_AutoPlay->_OnInterrupt(LagRush_Interrupt__Error_Stash_Get);
	}
	else
	{
		// ���� �÷����� ��� ������ �Ұ�!!!
		_asm nop;
	}
}

void CmdLagrushItemResult(char* arg, CUIMgr* pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int buy_result = atoi( g_Buf );

	if( buy_result == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		int failed_reason = atoi( g_Buf );

		enum
		{
			Buy_Fail_Error__03,	// Slot_Full
			Buy_Fail_Error__04,	// Slot_needmoney
			Buy_Fail_Error__05, // Dont_buy
			Error__EndOfEnum

		};

		failed_reason += (int)LagRush_Interrupt__InvenFull - 3;
		if( pMgr->m_AutoPlay->IsRun() )
		{
			pMgr->m_AutoPlay->_OnInterrupt((LagRush_Interrupt)failed_reason);
		}
		else
		{
			// ���� �÷����� ��� ������ �Ұ�!!!
			_asm nop;
		}
	}
	else
	{
		pMgr->m_AutoPlay->OnRecvShop();
	}
}


void CmdUsedQuickItem(char*arg, CUIMgr*pMgr)
{
	bool moveto = false;

	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		// error message
		arg = AnyOneArg(arg, g_Buf);
		int slot = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int index = atoi(g_Buf);


		arg = AnyOneArg(arg, g_Buf);
		eUseQuickError_Type err = (eUseQuickError_Type)atoi(g_Buf);
		// error no( �̹̻��� �������̴� )

		CItem * pQuickSlotItem = g_pRoh->m_QuickSlot[slot];
		if( pQuickSlotItem && pQuickSlotItem->m_Index == index )
		{
			switch( GET_SHAPE(pQuickSlotItem) )
			{
			case IETC_GEMSTONE:
				{
				}
				break;
			case IETC_RECOVERY:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot
					  )
					{
						if( pQuickSlotItem->m_Num0 != 13 )
							moveto = true;
						g_pRoh->RemoveQuickItem(slot, index , moveto , true);
					}
				}
				break;
			case IETC_PREMIUM:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot
					  )
					{
						if( pQuickSlotItem->m_Num0 == 3 )
						{
						}
						else
						{
							moveto = true;
							g_pRoh->RemoveQuickItem(slot, index , moveto);
						}
					}
				}
				break;
			case IETC_QUICK:
				{
				}
				break;
			case IETC_QUEST:
				{
					enum Etc_Quest__Type
					{
						Etc_Quest__Random,
						Etc_Quest__Fix,
						Etc_Quest__Dependence,
						Etc_Quest__Document,


						Etc_Quest__EndOfEnum
					};

					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						switch( pQuickSlotItem->m_Num0 )
						{
						case Etc_Quest__Random:
							{
							}
							break;
						case Etc_Quest__Fix:
						case Etc_Quest__Dependence:
						case Etc_Quest__Document:
							{
								moveto = false;
								g_pRoh->RemoveQuickItem(slot, index , moveto);
							}
							break;
						}
					}
				}
				break;
			case IETC_PET:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot, index , moveto);
					}
				}
				break;

			case IETC_WARP:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						if( pQuickSlotItem->m_Num0 == 2 )
						{
							moveto = false;
						}

						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;

			case IETC_BUFF:
			case IETC_SUMMONNPC:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;
			case IETC_SKILL:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;

			case IETC_RESOURCE:
				break;
			case IETC_EFFECT:
				break;
			case IETC_USING:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;
			case IETC_SCROLL:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}


				}
				break;
			case IETC_SUMMON:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						// ������ ����
					}

					// 				if( state == 0 )
					// 				{
					// 				}
					// 				else if( state == 1 )
					// 				{
					// 				}
					// 				else if( state == 2 )
					// 				{
					// 					moveto = true;
					// 					g_pRoh->RemoveQuickItem(slot , index , moveto);
					// 				}
				}
				break;
			case IETC_SHELL:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;
			case IETC_CHARGE:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;
			case IECT_MOBSUMMON:
				{
					if( err == eUseQuickError_Invalid_Item
							|| err == eUseQuickError_Invalid_Slot )
					{
						moveto = false;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;
			}
		}
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int slot = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int index = atoi(g_Buf);

		CItem * pQuickSlotItem = g_pRoh->m_QuickSlot[slot];
		if( pQuickSlotItem && pQuickSlotItem->m_Index == index && rv )
		{
			switch( GET_SHAPE(pQuickSlotItem) )
			{
			case IETC_GEMSTONE:
				{
					arg = AnyOneArg(arg, g_Buf);
					int add_item = atoi(g_Buf);
					int gemToVnum = GET_TOGEM_VNUM(pQuickSlotItem);
					g_pRoh->RemoveQuickItem(slot, index , false);
					g_pRoh->ToQuickSlot(slot, add_item , gemToVnum ,0 , 0 , 0);
					g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1835) , -1 );
				}
				break;
			case IETC_RECOVERY:
				{
					arg = AnyOneArg(arg, g_Buf);
					int remain_count = atoi(g_Buf);
					if( remain_count > 0 )
					{
						g_pRoh->m_QuickSlot[slot]->m_Special = remain_count;
						g_pNk2DFrame->GetControlInven()->ResetItemInfo();
						return;
					}

					if( pQuickSlotItem->m_Num0 != 13 )
						moveto = true;
					g_pRoh->RemoveQuickItem(slot, index , moveto , true);
				}
				break;
			case IETC_PREMIUM:
				{
					if( pQuickSlotItem->m_Num0 == 3 )
					{
						// �� ������ ó��!!!
// 						arg = AnyOneArg(arg, g_Buf);
// 						int step = atoi(g_Buf);
					}
					else
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot, index , moveto);
					}
				}
				break;			
			
			case IETC_QUEST:
				{
					arg = AnyOneArg(arg, g_Buf);
					int remain_count = atoi(g_Buf);

					enum Etc_Quest__Type
					{
						Etc_Quest__Random,
						Etc_Quest__Fix,
						Etc_Quest__Dependence,
						Etc_Quest__Document,


						Etc_Quest__EndOfEnum
					};

					switch( pQuickSlotItem->m_Num0 )
					{
					case Etc_Quest__Random:
						{
							g_pRoh->m_QuickSlot[slot]->m_Special = remain_count;
							g_pNk2DFrame->GetControlInven()->ResetItemInfo();
						}
						break;
					case Etc_Quest__Fix:
					case Etc_Quest__Dependence:
					case Etc_Quest__Document:
						{
							moveto = false;
							g_pRoh->RemoveQuickItem(slot, index , moveto);
						}
						break;
					}
				}
				break;

			case IETC_PET:
				{
					moveto = true;
					g_pRoh->RemoveQuickItem(slot, index , moveto);
				}
				break;

			case IETC_QUICK:
				{
					moveto = true;
					g_pRoh->RemoveQuickItem(slot, index, moveto);
				}
				break;

			case IETC_WARP:
				{
					moveto = true;
					if( pQuickSlotItem->m_Num0 == 2 )
					{
						arg = AnyOneArg(arg, g_Buf);
						int zone_index = atoi(g_Buf);

						char msg_buf[64];
						msg_buf[0] = 0;
						sprintf( msg_buf , "go_zone %d %d 0\n" , slot , zone_index );
						LH_SEND_NET_MSG( msg_buf );

						pCMyApp->StopHero(TRUE);
						CPacketControl::EnableSend(FALSE);

						moveto = false;
					}

					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IETC_BUFF:
				{
					arg = AnyOneArg(arg, g_Buf);
					int remain_count = atoi(g_Buf);
					if( remain_count > 0 )
					{
						g_pRoh->m_QuickSlot[slot]->m_Special = remain_count;
						g_pNk2DFrame->GetControlInven()->ResetItemInfo();
						return;
					}

					// �̵��ʿ�
					CItem * buff_item = g_pRoh->m_QuickSlot[slot];

					if( !buff_item )
						return;

					moveto = true;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IETC_SUMMONNPC:
				{
					arg = AnyOneArg(arg, g_Buf);
					int remain_count = atoi(g_Buf);
					if( remain_count > 0 )
					{
						g_pRoh->m_QuickSlot[slot]->m_Special = remain_count;
						g_pNk2DFrame->GetControlInven()->ResetItemInfo();
						return;
					}

					moveto = true;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IETC_SKILL:
				{
					arg = AnyOneArg(arg, g_Buf);
					int skill_no = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int skill_level = atoi(g_Buf);

					g_ChaSkill.SetSkillLevel(skill_no , skill_level);
					if( g_pNk2DFrame
							&& g_pNk2DFrame->GetControlSkill())
					{
						g_pNk2DFrame->GetControlSkill()->m_pSkillInfo->SetIndex(-100);
						g_pNk2DFrame->GetControlSkill()->SetSkillEnable();
					}

					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;

			case IETC_RESOURCE:
				break;
			case IETC_EFFECT:
				break;
			case IETC_USING:
				{
					moveto = true;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IETC_SCROLL:
				{
					arg = AnyOneArg(arg, g_Buf);
					int plus_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int special_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int etc_slot = atoi(g_Buf);

					switch( g_pRoh->m_QuickSlot[slot]->m_Num0 )
					{
					case 0:
					case 7:
						{
							g_pRoh->UpdateEquipItem(plus_num , special_num , etc_slot);
						}
						break;
					default:
						{
							g_pRoh->UpdateQuickItem(plus_num , special_num , etc_slot);
						}
						break;
					}
					moveto = true;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IETC_SUMMON:
				{
					arg = AnyOneArg(arg, g_Buf);
					int plus_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int special_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);

					int state = atoi(g_Buf);

					g_pRoh->UpdateQuickItem(plus_num , special_num , slot);


					if( state == 0 )
					{
						// �ߵ�
					}
					else if( state == 1 )
					{
						// ����
					}
					else if( state == 2 )
					{
						moveto = true;
						g_pRoh->RemoveQuickItem(slot , index , moveto);
					}
				}
				break;
			case IETC_SHELL:
				{
					arg = AnyOneArg(arg, g_Buf);
					int plus_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int special_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int etc_slot = atoi(g_Buf);

					g_pRoh->UpdateEquipItem(plus_num , special_num , WEARING_CLOAK);
					moveto = true;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IETC_CHARGE:
				{
					arg = AnyOneArg(arg, g_Buf);
					int plus_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int special_num = atoi(g_Buf);
					arg = AnyOneArg(arg, g_Buf);
					int etc_slot = atoi(g_Buf);

					switch( g_pRoh->m_QuickSlot[slot]->m_Num0 )
					{
					case 0:
						{
							g_pRoh->UpdateQuickItem(plus_num , special_num , etc_slot);
						}
						break;
					case 1:
						g_pRoh->UpdateEquipItem(plus_num , special_num , WEARING_CLOAK);
						break;
					case 2:
						g_pRoh->UpdateEquipItem(plus_num , special_num , etc_slot);
						break;
					case 3:
						g_pRoh->UpdateEquipItem(plus_num , special_num , WEARING_BRACELET);
						break;
					default:
						{
							g_pRoh->UpdateEquipItem(plus_num , special_num , etc_slot);
						}
						break;
					}

					moveto = true;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			case IECT_MOBSUMMON:
				{
					moveto = false;
					g_pRoh->RemoveQuickItem(slot , index , moveto);
				}
				break;
			}
		}
	}
}

void CmdMovedItem(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		// error message
		arg = AnyOneArg(arg, g_Buf);
		int slot = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int index = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int err_no = atoi(g_Buf);

		// error ���� �Լ� �߰�����
		if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
		{
			switch( err_no )
			{
			case 1:
				pMgr->m_AutoPlay->AddLog( "*****�����Թ�ȣ ����*****" , 1 );
				break;
			case 2:
				pMgr->m_AutoPlay->AddLog( "*****�ѹ�ȣ ����*****" , 1 );
				break;
			case 3:
				pMgr->m_AutoPlay->AddLog( "*****�߸��� ������ �ε���*****" , 1 );
				break;
			}
		}
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int slot = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int index = atoi(g_Buf);

		if( !g_pRoh->InvenToQuick(slot , index) )
		{
			_asm nop;
		}
	}
}

void CmdRevival_Rcv(char*arg, CUIMgr*pMgr)
{
	// ��Ƴ����!!!
}

// �κ�->â��(�Ӽ��ִ�)
void CmdStashPutS(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		int nothing = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int err_code = atoi(g_Buf);

		if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
		{
			if( g_pNk2DFrame->IsWareHouseVisible() )
				g_pNk2DFrame->ToggleWareHouseWindow();

			err_code += (int)LagRush_Interrupt__Wrong_Zone;
			pMgr->m_AutoPlay->_OnInterrupt((LagRush_Interrupt)err_code);
		}
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int vnum = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int ware_slot = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int inven_pack = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int count = atoi(g_Buf);

		for( int i=0 ; i<count ; i++ )
		{
			arg = AnyOneArg(arg, g_Buf);
			int item_index = atoi(g_Buf);
			pMgr->StashPuts(vnum , ware_slot , inven_pack , item_index );
			g_pRoh->CountQuickAll();
		}

		if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
		{
			pMgr->m_AutoPlay->OnRecvStash();
		}
	}
}

// â��->�κ�(����)
void CmdStashGetS(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		int err_code = atoi(g_Buf);

		switch( err_code )
		{
		case 0:
			break;
		default:
			break;
		}

		g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_LHSTRING1836) , -1 );

		if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
		{			
			pMgr->m_AutoPlay->OnRecvStash();
		} 
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int vnum = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int ware_slot = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int inven_pack = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int count = atoi(g_Buf);

		for( int i=0 ; i<count ; i++ )
		{
			arg = AnyOneArg(arg, g_Buf);
			int item_index = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int slot_x = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int slot_y = atoi(g_Buf);
			pMgr->StashGets(vnum , ware_slot , inven_pack , item_index , slot_x , slot_y );
		}

		if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
		{
			pMgr->m_AutoPlay->OnRecvStash();
		} 
	}
}


void CmdMovedApple(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		int apple_count = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int item_index = atoi(g_Buf);

		g_MyPetStatus.SetFoodCount(apple_count);
		g_pRoh->RemoveInvenItem(item_index);
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int apple_count = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int item_index = atoi(g_Buf);

		g_MyPetStatus.SetFoodCount(apple_count);
		g_pRoh->RemoveInvenItem(item_index);

		if( pMgr->m_AutoPlay && pMgr->m_AutoPlay->IsRun() )
			pMgr->m_AutoPlay->OnRecvApple();
	}
}



void CmdGetGoodsLists(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int num_items = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int page_cur =  atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	int num_cur_item =  atoi(g_Buf);

	if( num_items == 0 )
	{
		g_pNk2DFrame->ShowTakeboxWindow(false,0);
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LHSTRING1854) , TYPE_NOR_OK );
		return;
	}

	if( g_pNk2DFrame->GetTakeOutBox() )
	{
		g_pNk2DFrame->GetTakeOutBox()->SetTakebox( TakeBox_Type__User , num_items , page_cur , num_items );

		for( int i=0 ; i<num_cur_item ; i++ )
		{
			arg = AnyOneArg(arg, g_Buf);
			int db_index =  atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int vnum =  atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int count =  atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			g_pNk2DFrame->GetTakeOutBox()->InsertItem( db_index , vnum , count , g_Buf );
		}

		g_pNk2DFrame->GetTakeOutBox()->SetRecived(2);
	}
}

void CmdGetPresentLists(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int type = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int num_items = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int page_cur =  atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	int num_cur_item =  atoi(g_Buf);

	if( num_items == 0 )
	{	
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LHSTRING1854) , TYPE_NOR_OK );		
	}
	
	LHUI_TakeBox* pTakeBox = g_pNk2DFrame->GetTakeOutBox();
	if( pTakeBox )
	{
		TakeBox_Type takeBoxType = TakeBox_Type__Character;
		if( type == 1 )
		{
			takeBoxType = TakeBox_Type__ServerMove;
		}		

		pTakeBox->ClearList();
		pTakeBox->SetTakebox( takeBoxType , num_items , page_cur , num_items );

		for( int i=0 ; i<num_cur_item ; i++ )
		{
			arg = AnyOneArg(arg, g_Buf);
			int db_index =  atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int vnum =  atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			int count =  atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			pTakeBox->InsertItem( db_index , vnum , count , g_Buf );
		}

		pTakeBox->SetRecived(2);
	}
}

// ���� 0 : ��ȿ�� ����
// ���� 1 : ��������( 0�϶� ����Ʈ ����, 0�̻��̸� ���� )
void CmdGetGoodsResult(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		int err_code = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int db_index = atoi(g_Buf);

		if( g_pNk2DFrame->GetTakeOutBox() )
			g_pNk2DFrame->GetTakeOutBox()->SetRecived(3);
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int remain_count = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int db_index = atoi(g_Buf);

		if( g_pNk2DFrame->GetTakeOutBox() )
		{
			g_pNk2DFrame->GetTakeOutBox()->EditItem(db_index , remain_count);
			g_pNk2DFrame->GetTakeOutBox()->SetRecived(2);
		}

		if( remain_count !=0 )
		{
			g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LHSTRING1855) , TYPE_NOR_OK );
		}
	}
}

void CmdGetPresentResult(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int rv = atoi(g_Buf);

	if( rv == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		int err_code = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int db_index = atoi(g_Buf);

		if( g_pNk2DFrame->GetTakeOutBox() )
			g_pNk2DFrame->GetTakeOutBox()->SetRecived(3);
	}
	else
	{
		arg = AnyOneArg(arg, g_Buf);
		int remain_count = atoi(g_Buf);
		arg = AnyOneArg(arg, g_Buf);
		int db_index = atoi(g_Buf);


		if( g_pNk2DFrame->GetTakeOutBox() )
		{
			g_pNk2DFrame->GetTakeOutBox()->EditItem(db_index , remain_count);
			g_pNk2DFrame->GetTakeOutBox()->SetRecived(2);
		}		
	}
}

void CmdResultCaru(char*arg, CUIMgr*pMgr)
{
	arg = AnyOneArg(arg, g_Buf);
	int count = atoi(g_Buf);

	if( count == 0 )
	{
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LHSTRING1855) , TYPE_NOR_OK );
		return;
	}

	g_pNk2DFrame->InsertPopup( "caru", TYPE_CARU_RESULT, POPUP_CARU_RESULT);
	CMsgPopUp* p = g_pNk2DFrame->FindPopup(POPUP_CARU_RESULT);
	CaruResultData* data = p->m_pCaruResultData;
	if( data == NULL )
	{
		return;
	}

	for(int i = 0; i < count; i++)
	{
		arg = AnyOneArg(arg, g_Buf);
		data->SetIndex(i, g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		int vnum = atoi(g_Buf);
		data->SetItemName(i, GET_ITEM_NAME_VNUM(vnum));

		arg = AnyOneArg(arg, g_Buf);
		data->SetItemCount(i, g_Buf);
	}
	p->RestoreAll();	
}

void CmdBuffEx(char*arg, CUIMgr*pMgr)
{
	int bv = 0; // ��ġ
	int type = 0;
	arg = AnyOneArg(arg, g_Buf);
	if (!strcmp(g_Buf, "att"))
	{
		arg = AnyOneArg(arg, g_Buf);
		bv = atoi(g_Buf);
		type = 0;
	}
	else if (!strcmp(g_Buf, "def"))
	{
		arg = AnyOneArg(arg, g_Buf);
		bv = atoi(g_Buf);
		type = 1;
	}
	else if (!strcmp(g_Buf, "exp"))
	{
		arg = AnyOneArg(arg, g_Buf);
		bv = atoi(g_Buf);
		type = 2;
	}
	else
	{
		return;
	}

	if( g_pNk2DFrame->GetNewEvent() )
		g_pNk2DFrame->GetNewEvent()->SetEvent_Ex( type , bv );
}



void CmdItemMake(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetUpgrade() )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ��ȭ �ִϸ��̼����� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_ING;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].m_AniType = SPRITE_ANITYPE_LOOP;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].SetStart();
	g_pNk2DFrame->GetUpgrade()->m_dwStartTickTime = timeGetTime();

	g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.


	if (!strcmp(g_Buf, "ok"))
	{
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS;
	}
	else if (!strcmp(g_Buf, "fail"))
	{
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_FAIL;
	}
	else
	{
		return;
	}
}

void CmdItemSeparate(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetUpgrade() )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ��ȭ �ִϸ��̼����� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_ING;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].m_AniType = SPRITE_ANITYPE_LOOP;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].SetStart();
	g_pNk2DFrame->GetUpgrade()->m_dwStartTickTime = timeGetTime();

	g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.


	if (!strcmp(g_Buf, "ok"))
	{
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS;
	}
	else
	{
		return;
	}
}

void CmdBuffMakeMake(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetUpgrade() )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ��ȭ �ִϸ��̼����� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_ING;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].m_AniType = SPRITE_ANITYPE_LOOP;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].SetStart();
	g_pNk2DFrame->GetUpgrade()->m_dwStartTickTime = timeGetTime();

	g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.

	int nResult = atoi(g_Buf);

	if( nResult == 0 )
	{
		g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_SUCCESS;
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS;
	}
	else
	{
		g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_FAIL;
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_FAIL;
	}
}

void CmdBuffMakeGatcha(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetUpgrade() )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ��ȭ �ִϸ��̼����� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_ING;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].m_AniType = SPRITE_ANITYPE_LOOP;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].SetStart();
	g_pNk2DFrame->GetUpgrade()->m_dwStartTickTime = timeGetTime();

	g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.

	int nResult = atoi(g_Buf);

	if( nResult == 0 )
	{
		g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_SUCCESS;
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS;
	}
	else
	{
		g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_FAIL;
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_FAIL;
	}
}

void CmdBuffMakeMedal(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame || !g_pNk2DFrame->GetUpgrade() )
		return;

	arg = AnyOneArg( arg, g_Buf );

	// ��ȭ �ִϸ��̼����� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_ING;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].m_AniType = SPRITE_ANITYPE_LOOP;
	g_pNk2DFrame->GetUpgrade()->m_SpriteAni[UPGRADE_ANI_ING].SetStart();
	g_pNk2DFrame->GetUpgrade()->m_dwStartTickTime = timeGetTime();

	g_pNk2DFrame->GetUpgrade()->m_bSlotLock = FALSE; // ���� ����.
	g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_NON; // ���� ����.

	int nResult = atoi(g_Buf);

	if( nResult == 0 )
	{
		g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_SUCCESS;
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_SUCCESS;
	}
	else
	{
		g_pNk2DFrame->GetUpgrade()->m_NowState = UPGRADE_ANI_FAIL;
		g_pNk2DFrame->GetUpgrade()->m_Result = UPGRADE_ANI_FAIL;
	}
}

void CmdUpEnergy(  char* arg, CUIMgr* pMgr )
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	arg = AnyOneArg( arg, g_Buf );
	int rv_type = atoi(g_Buf);
	arg = AnyOneArg( arg, g_Buf );
	int item_index = atoi(g_Buf);

	if( rv_type == TRUE )
	{
		g_pRoh->RemoveExtraItem(item_index);
	}
	else
	{
		arg = AnyOneArg( arg, g_Buf );
		int err_code = atoi(g_Buf);
		if(err_code == 0 )
		{
			g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_LHSTRING1886) , -1);
		}
		else
		{
			// ���κҸ�?
		}
	}
}

// ������ ��ų�� ����ٰ� �־��ٱ? 3������?
void CmdContinueSkill(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	arg = AnyOneArg( arg, g_Buf );
	int char_index = atoi(g_Buf);
	arg = AnyOneArg( arg, g_Buf );
	int skill_01 = atoi(g_Buf);		// �ʵ�
	arg = AnyOneArg( arg, g_Buf );
	int skill_02 = atoi(g_Buf);		// �ʵ� ex
	arg = AnyOneArg( arg, g_Buf );
	int skill_03 = atoi(g_Buf);		// d system
	arg = AnyOneArg( arg, g_Buf );
	int skill_04 = atoi(g_Buf);		// engage
	arg = AnyOneArg( arg, g_Buf );
	int skill_05 = atoi(g_Buf);		// critical

	CNkCharacter * target = pMgr->GetCharacterByID(char_index);
	if( !target )
		return;


	if( target->m_Race == RACE_PEROM )
	{
		if( skill_01 )
			target->SetActiveField();
		else
			target->SetDeactiveField();

		if( skill_02 )
			target->SetActiveField_Ex();
		else
			target->SetDeactiveField_Ex();

		if( skill_03 )
			target->SetActiveDSystem();
		else
			target->SetDeactiveDSystem();

		if( skill_04 )
			target->SetActiveEngage();
		else
			target->SetDeactiveEngage();

		if( skill_05 )
			target->SetActiveCritical();
		else
			target->SetDeactiveCritical();
	}
}

void CmdMaStone(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	arg = AnyOneArg( arg, g_Buf );
	int nResult = atoi(g_Buf);

	struct E_RESULT
	{
		enum { FAILED = 0, SUCCESS = 1 };
	};

	switch ( nResult )
	{
	case E_RESULT::FAILED://������ �����Ͽ����ϴ�.
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_ITEM_GMASUK_FAILED), TYPE_NOR_OK, 32 );
		g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_ITEM_GMASUK_FAILED), -1);
		break;

	case E_RESULT::SUCCESS://������ �����Ͽ����ϴ�.
		g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_ITEM_GMASUK_SUCCESS), TYPE_NOR_OK, 32 );
		g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_ITEM_GMASUK_SUCCESS), -1);
		break;
	}

}

void CmdShutdown(char*arg, CUIMgr*pMgr)
{
	if( !pMgr || !g_pNk2DFrame )
		return;

	g_pNk2DFrame->InsertPopup( "�˴ٿ���", TYPE_NOR_OK, 0 );
}

void CmdBuffItemInfo(char* arg, CUIMgr* pMgr)
{
	if( !pMgr )
		return;

	BuffItemMgr* buffItemMgr = BuffItemMgr::GetInstance();

	arg = AnyOneArg(arg, g_Buf);
	if( strcmp(g_Buf, "add") == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);

		int buffIndex = 0;
		int buffRemainTime = 0;
		int buffVal = 0;
		for( int i = 0; i < g_ii[0]; i++ )
		{
			arg = AnyOneArg(arg, g_Buf);
			buffIndex = atoi(g_Buf);
			arg = AnyOneArg(arg, g_Buf);
			buffRemainTime = atoi(g_Buf);
			buffRemainTime *= 1000;
			arg = AnyOneArg(arg, g_Buf);
			buffVal = atoi(g_Buf);

			buffItemMgr->AddBuff(buffIndex, (unsigned long)buffRemainTime, buffVal);
		}
	}
	else if( strcmp(g_Buf, "del") == 0 )
	{
		arg = AnyOneArg(arg, g_Buf);
		g_ii[0] = atoi(g_Buf);

		buffItemMgr->RemoveBuff(g_ii[0]);
	}
}

void CmdCharacterScaling(char* arg, CUIMgr* pMgr)
{
	if (!pMgr)
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);			// index

	arg = AnyOneArg(arg, g_Buf);
	float scaleValue = atof(g_Buf);

	pCha = pMgr->FindChaById(g_ii[0]);

	if (pCha)
	{
		pCha->scaleCharacter(scaleValue);
	}
}

void CmdFeverTime(char* arg, CUIMgr* pMgr)
{
	if (!pMgr || !g_pNk2DFrame)
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	g_pNk2DFrame->GetNewEvent()->SetEvent(OpEvent_Type__Fever_Time, g_ii[0]);
}

void CmdNameHide(char* arg, CUIMgr* pMgr)
{
	if (!pMgr || !g_pNk2DFrame)
		return;

	arg = AnyOneArg(arg, g_Buf);
	g_ii[0] = atoi(g_Buf);

	if (g_ii[0])
	{
		g_SvrMode = eSVR_MASTER;
	}
	else
	{
		g_SvrMode = eSVR_NORMAL;
	}
}

void CmdFriend(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	RecvFriend(arg);
}

void CmdNVisible(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int vnum = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	BOOL bVisible = atoi(g_Buf);

	pMgr->SetVisibleMob(vnum, bVisible);
}

void CmdYutThrow(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	YutManager* yutMgr = YutManager::GetInstance();
	ControlYutboard* board = (ControlYutboard*)g_pNk2DFrame->GetInterface(YUTBOARD);

	arg = AnyOneArg(arg, g_Buf);
	int error = atoi(g_Buf);

	if( error != 0 )
	{
		board->SetEnableStartBtn(true);
		return;
	}

	arg = AnyOneArg(arg, g_Buf);
	int result = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	int pos = atoi(g_Buf);

	yutMgr->SetPosIndex(pos);
	board->SetAniYutStart(result);
}

void CmdYutInfo(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	YutManager* yutMgr = YutManager::GetInstance();
	ControlYutboard* board = (ControlYutboard*)g_pNk2DFrame->GetInterface(YUTBOARD);

	arg = AnyOneArg(arg, g_Buf);
	int complete = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	int pos = atoi(g_Buf);
	arg = AnyOneArg(arg, g_Buf);
	BOOL bMapIn = atoi(g_Buf);

	yutMgr->SetCompleteCount(complete);
	if( bMapIn == TRUE )
	{
		board->SetCurPos(pos);
		board->SetCompleteCount(complete);
	}
}

void CmdCheckNpcSummon(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int itemIndex = atoi(g_Buf);

	g_pNk2DFrame->InsertPopup(arg, TYPE_NOR_OKCANCLE, POPUP_CHECK_SUMMON_NPC_NOTIFY, 30, 0, (void*)itemIndex);
}

void CmdCloseNpcSummon(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	g_pNk2DFrame->CloseAllWindow();
}

void CmdSummonNpcSummon(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int npcIndex = atoi(g_Buf);

	if( g_pRoh == NULL )
		return;

	g_pRoh->SetSummonNpcIndex(npcIndex);
}

void CmdFishThrow(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int errType = atoi(g_Buf);
	if( errType != 0 )
	{
		ControlFishing* board = (ControlFishing*)g_pNk2DFrame->GetInterface(FISHING);
		board->Init();

		return;
	}

	arg = AnyOneArg(arg, g_Buf);
	int fishType = atoi(g_Buf);

	FishingManager* fishMgr = FishingManager::GetInstance();
	int count = fishMgr->GetFishCount(fishType);
	++count;
	fishMgr->SetFishCount(fishType, count);

	ControlFishing* board = (ControlFishing*)g_pNk2DFrame->GetInterface(FISHING);
	board->SetResult(fishType);
}

void CmdFishInfo(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int typeCount = atoi(g_Buf);

	int count = 0;
	int fishType = 0;
	FishingManager* fishMgr = FishingManager::GetInstance();
	fishMgr->Clear();
	for(int i = 0; i < typeCount; i++)
	{
		arg = AnyOneArg(arg, g_Buf);
		fishType = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		count = atoi(g_Buf);		

		fishMgr->SetFishCount(fishType, count);
	}

	ControlFishing* board = (ControlFishing*)g_pNk2DFrame->GetInterface(FISHING);
	board->Init();	
}

void CmdFishGiftList(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	FishingRewardManager* rewardMgr = FishingRewardManager::GetInstance();
	rewardMgr->Clear();
	
	arg = AnyOneArg(arg, g_Buf);
	int count = atoi(g_Buf);

	int grade = 0;
	int index = 0;
	int type = 0;
	for(int i = 0; i < count; i++)
	{
		arg = AnyOneArg(arg, g_Buf);
		grade = atoi(g_Buf);
		
		arg = AnyOneArg(arg, g_Buf);
		index = atoi(g_Buf);

		arg = AnyOneArg(arg, g_Buf);
		type = atoi(g_Buf);

		{
			// ������ Ŭ���̾�Ʈ ��� ������ �ٸ�
			if( grade == 0 )
				grade = 2;
			else if( grade == 2 )
				grade = 0;
		}		

		if( type == 0 )
		{
			rewardMgr->AddCanGet(grade, index);
		}
		else if( type == 1 )
		{
			rewardMgr->AddAlready(grade, index);
		}
	}

	ControlFishingReward* board = (ControlFishingReward*)g_pNk2DFrame->GetInterface(FISHING_REWARD);
	board->Refresh();
}

void CmdFishGiftItem(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	FishingRewardManager* rewardMgr = FishingRewardManager::GetInstance();
	ControlFishingReward* board = (ControlFishingReward*)g_pNk2DFrame->GetInterface(FISHING_REWARD);

	arg = AnyOneArg(arg, g_Buf);
	int result = atoi(g_Buf);

	if( result != 0 )
	{
		board->Refresh();
		return;
	}

	arg = AnyOneArg(arg, g_Buf);
	int grade = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int index = atoi(g_Buf);

	{
		// ������ Ŭ���̾�Ʈ ��� ������ �ٸ�
		if( grade == 0 )
			grade = 2;
		else if( grade == 2 )
			grade = 0;
	}

	rewardMgr->AddAlready(grade, index);

	board->Refresh();
}

void CmdOK(char* arg, CUIMgr* pMgr)
{
	CPacketControl::EnableSend(TRUE);

	char temp[256] = {0, };
	if (g_pTcpIp)
	{
		if( CommonConfig::Instance()->GetThaFlag() == true )
		{
			sprintf(temp, "start_game %s\n", GetMd5CheckSum().c_str());
			g_pTcpIp->SendNetMessage(temp, TRUE);		
		}
		else
		{
			g_pTcpIp->SendNetMessage("start_game\n", TRUE);
		}
	}

	CPacketControl::EnableSend(FALSE);

	SetItemEffMgr::GetInstance()->Clear();
}

void CmdCharLoadComplete(char* arg, CUIMgr* pMgr)
{
	CPacketControl::EnableSend(TRUE);	
}

void CmdCharsEnd(char* arg, CUIMgr* pMgr)
{
	CPacketControl::EnableSend(TRUE);	
	if (g_pTcpIp)
	{
		char strBuf[MAX_PATH] = {0,};
		sprintf(strBuf, "start %d %d 0 0 0 0 0 0\n", pCMyApp->m_SlotNum, pCMyApp->m_nAreaNum);
		g_pTcpIp->SendNetMessage(strBuf, TRUE);
	}
	CPacketControl::EnableSend(FALSE);
}

void CmdSpeedCheck(char* arg, CUIMgr* pMgr)
{
	SpeedChecker::GetInstance()->StartCheck();
}

void CmdDecardiBattleRes(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int err = atoi(g_Buf);

	g_pNk2DFrame->AddChatStr( (char*)G_STRING(IDS_DCB_ERR_OK + err) , -1 );
	g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_DCB_ERR_OK + err) , TYPE_NOR_OK, 1 );
}

void CmdDecardiBattleListStart(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	DecardiBattleManager* dcbMgr = DecardiBattleManager::GetInstance();
	dcbMgr->ClearList();
}

void CmdDecardiBattleList(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int team = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int count = atoi(g_Buf);

	DecardiBattleManager* dcbMgr = DecardiBattleManager::GetInstance();

	int charIndex = 0;
	for(int i = 0; i < count; i++)
	{
		arg = AnyOneArg(arg, g_Buf);
		charIndex = atoi(g_Buf);

		dcbMgr->AddTeam(team, charIndex);
	}
}

void CmdDecardiBattleListEnd(char* arg, CUIMgr* pMgr)
{
}

void CmdDecardiBattleStart(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	DecardiBattleManager* dcbMgr = DecardiBattleManager::GetInstance();
	dcbMgr->Start();
	ControlDecardiBattle* uiDCB = g_pNk2DFrame->GetDecardiBattle();
	if( uiDCB )
	{
		uiDCB->Start();
	}	
}

void CmdDecardiBattlePoint(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int redPoint = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int bluePoint = atoi(g_Buf);

	DecardiBattleManager* dcbMgr = DecardiBattleManager::GetInstance();
	dcbMgr->SetPoint(0, redPoint);
	dcbMgr->SetPoint(1, bluePoint);
}

void CmdDecardiBattleResult(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int result = atoi(g_Buf);

	DecardiBattleManager* dcbMgr = DecardiBattleManager::GetInstance();
	dcbMgr->End();
	ControlDecardiBattle* uiDCB = g_pNk2DFrame->GetDecardiBattle();
	uiDCB->End(result);
}

void CmdDecardiBattleGate(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int nDraw = atoi(g_Buf);
	bool bDraw = (nDraw == 0 ? false : true);

	DecardiBattleManager* dcbMgr = DecardiBattleManager::GetInstance();
	dcbMgr->SetGate(bDraw);

	pCMyApp->GetLandPtr()->SetFieldAttr(dcbMgr->m_attackable[0].x1, dcbMgr->m_attackable[0].z1, dcbMgr->m_attackable[0].x2, dcbMgr->m_attackable[0].z2, nDraw);
	pCMyApp->GetLandPtr()->SetFieldAttr(dcbMgr->m_attackable[1].x1, dcbMgr->m_attackable[1].z1, dcbMgr->m_attackable[1].x2, dcbMgr->m_attackable[1].z2, nDraw);
	pCMyApp->GetLandPtr()->SetFieldAttr(dcbMgr->m_attackable[2].x1, dcbMgr->m_attackable[2].z1, dcbMgr->m_attackable[2].x2, dcbMgr->m_attackable[2].z2, nDraw);
	pCMyApp->GetLandPtr()->SetFieldAttr(dcbMgr->m_attackable[3].x1, dcbMgr->m_attackable[3].z1, dcbMgr->m_attackable[3].x2, dcbMgr->m_attackable[3].z2, nDraw);
	pCMyApp->GetLandPtr()->SetFieldAttr(dcbMgr->m_attackable[4].x1, dcbMgr->m_attackable[4].z1, dcbMgr->m_attackable[4].x2, dcbMgr->m_attackable[4].z2, nDraw);
}

void CmdDecardiBattleDay(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	g_pNk2DFrame->SetInfoBox((char*)G_STRING(IDS_DCB_DAY_INFO1));
	g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_DCB_DAY_INFO1), 4);
	g_pNk2DFrame->SetInfoBox2((char*)G_STRING(IDS_DCB_DAY_INFO2), RGB(255, 0, 255), RGB(100, 100, 250));
	g_pNk2DFrame->AddChatStr((char*)G_STRING(IDS_DCB_DAY_INFO2), 4);
	
	g_pNk2DFrame->SetInfoBox_NextString(G_STRING(IDS_DCB_DAY_INFO3));
	g_pNk2DFrame->SetInfoBox_NextString2(G_STRING(IDS_DCB_DAY_INFO4));
}

void CmdLotto(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int err = atoi(g_Buf);
	
	g_pNk2DFrame->InsertPopup( (char*)G_STRING(IDS_LOTTO_ERR_OK + err) , TYPE_NOR_OK, 1 );

	ControlLotto* pLotto = (ControlLotto*)(g_pNk2DFrame->GetInterface(LOTTO));
	pLotto->RefreshListReq(0);	
}

void CmdLottoList(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int maxPage = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int curPage = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int count = atoi(g_Buf);

	LottoManager* lottoMgr = LottoManager::GetInstance();
	std::vector<int> numbers;
	int num = 0;
		
	lottoMgr->ClearList();

	for(int i = 0; i < count; i++)
	{
		numbers.clear();

		for(int j = 0; j < MAX_LOTTO_INPUT; j++)
		{
			arg = AnyOneArg(arg, g_Buf);
			num = atoi(g_Buf);
			numbers.push_back(num);
		}

		std::sort(numbers.begin(), numbers.end());
		lottoMgr->AddList(numbers);
	}

	ControlLotto* pLotto = (ControlLotto*)(g_pNk2DFrame->GetInterface(LOTTO));
	pLotto->RefreshList();
	pLotto->SetCurPage(curPage);
	pLotto->SetMaxPage(maxPage);
}

void CmdLottoChance(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int count = atoi(g_Buf);

	LottoManager::GetInstance()->SetTicketCount(count);
}

void CmdPetUpgradeDrake(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;	
}

void CmdPetWearDrake(char* arg, CUIMgr* pMgr)
{
	if( pMgr == NULL || g_pNk2DFrame == NULL )
		return;

	arg = AnyOneArg(arg, g_Buf);
	int w = atoi(g_Buf);

	arg = AnyOneArg(arg, g_Buf);
	int vnum = atoi(g_Buf);

	g_MyPetStatus.SetEquip(w, vnum);
}
