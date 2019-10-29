#ifndef _FX_FOLLOW_H_
#define _FX_FOLLOW_H_

// FOLLOW ����Ʈ�� ����.
/*#define FX_FOLLOW_TYPE_FAIRY		0 // 345���� ������ ��.
#define FX_FOLLOW_TYPE_LUCKYPIG     1 // ���� �̺�Ʈ ������
#define FX_FOLLOW_TYPE_BABYSOUL		2 // [7/31/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ������ �ҿ�
#define FX_FOLLOW_TYPE_VAMPIREBAT   3 ///�����̾���� ����
#define FX_FOLLOW_TYPE_RUDOLPH		4 ///��絹��
#define FX_FOLLOW_TYPE_RING_LIGHT	5 // [1/15/2008 �����] �Ϻ� �� ������ ����Ʈ*/
enum FXTYPE
{
	FX_FOLLOW_TYPE_FAIRY,		// 345���� ������ ��.
	FX_FOLLOW_TYPE_LUCKYPIG,	// ���� �̺�Ʈ ������
	FX_FOLLOW_TYPE_BABYSOUL,	// 6�ֳ� ��� �̺�Ʈ ������ �ҿ�
	FX_FOLLOW_TYPE_VAMPIREBAT,	// �����̾���� ����
	FX_FOLLOW_TYPE_RUDOLPH,		// ��絹��
	FX_FOLLOW_TYPE_RING_LIGHT,	// �Ϻ� �� ������ ����Ʈ
	FX_FOLLOW_TYPE_ARUPAKAPET,	// ����ī��
	FX_FOLLOW_TYPE_CATS,
	FX_FOLLOW_TYPE_RABBIT,
	FX_FOLLOW_TYPE_ZORO,
	FX_FOLLOW_TYPE_DOGS,
	FX_FOLLOW_TYPE_VALO,
	FX_FOLLOW_TYPE_BEAR,
	FX_FOLLOW_TYPE_HORSE,
	FX_FOLLOW_TYPE_JEGUAR,
	FX_FOLLOW_TYPE_BONI,

	FX_FOLLOW_TYPE__ENDOFENUM,
};

//#define FX_FAIRY_SIZE 20.0f // �� ũ��

// ������ ���� ����
#define FX_FAIRY_MOVE_FRAME_TOTAL 16 // �� ������ �ִϸ��̼��� �� ������ ��
#define FX_FAIRY_MOVE_FRAME_WIDTH 8 // �� ������ �ִϸ��̼��� ���� ������ ��

#define FX_FAIRY_BLOCK_FRAME_TOTAL 16 // �� ��ŷ �ִϸ��̼��� �� ������ ��
#define FX_FAIRY_BLOCK_FRAME_WIDTH 8 // �� ��ŷ �ִϸ��̼��� ���� ������ ��

#define FX_FAIRY_SHOW1_FRAME_TOTAL 8 // �� ���� ������ �ִϸ��̼��� �� �����Ӽ�
#define FX_FAIRY_SHOW1_FRAME_WIDTH 8 // �� ���� ������ �ִϸ��̼��� ���� ������ ��

// AI ������Ʈ
#define FX_FAIRY_STATE_STAND		0  // �յ� ���ִ� ����.
#define FX_FAIRY_STATE_SIDESTEP		1  // �¿�� ������ �̵�.
#define FX_FAIRY_STATE_TURNROUND	2  // ������ ���� ���� ����.
#define FX_FAIRY_STATE_FOLLOW		3  // ������ �i�ư��� ����.
#define FX_FAIRY_STATE_BLOCKING		4  // ��ġ��.
#define FX_FAIRY_STATE_SHOW1		5  // ê���� ���� ���.

#define MAX_PARTICLE_FOR_FXFOLLOW  15 // ��ƼŬ �ִ� ����.

// ������ AI ������Ʈ
#define FX_LUCKYPIG_STATE_STAND			0  // �׳� ���ִ� ����.
#define FX_LUCKYPIG_STATE_RANDOMWALK	1  // �ƹ� �������γ� �ɾ.(õõ��)
#define FX_LUCKYPIG_STATE_FOLLOW		2  // ������ �i�ư��� ����.
#define FX_LUCKYPIG_STATE_SOCIAL1		3  // ���� �ֱ�����
#define FX_LUCKYPIG_STATE_SOCIAL2		4  // Ŭ���̾�Ʈ���� �ֺ� ������ ��
#define FX_LUCKYPIG_STATE_HEAL			5  // ȸ�� ���

#define KIND_LUCKY_PIG_CSY 4 // �������� ���� ����.
#define KIND_LUCKY_PIG_BPD 5 // �������� ���� ����.

// ������ �ִϸ��̼� ����
#define FX_LUCKYPIG_ANI_STAND		0  // �׳� ���ִ� ����.
#define FX_LUCKYPIG_ANI_WALK		1  // �ƹ� �������γ� �ɾ.(õõ��)
#define FX_LUCKYPIG_ANI_SOCIAL1		2  // ���� �ֱ�����
#define FX_LUCKYPIG_ANI_SOCIAL2		3  // Ŭ���̾�Ʈ���� �ֺ� ������ ��
#define FX_LUCKYPIG_ANI_HEAL		4  // ȸ�� ���

// [1/15/2008 �����] �Ϻ� �� ������ ����
#define FX_RING_WHITE			0  // ���̴� ��
#define FX_RING_DARK			1  // ������ ��
#define FX_RING_RED				2  // �����Ʈ ���� ��
#define FX_RING_BLUE			3  // �����Ʈ ��� ��
#define FX_RING_GREEN			4  // �����Ʈ �׸� ��
#define FX_RING_GOLD			5  // by evilkiki 2010.07.09 ��� ����Ʈ



//////////////////////////////////////////////////////////////////////////
// [7/31/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ���̺� �ҿ�

// ���� ����
enum babysoul_state
{
	FX_BABYSOUL_STATE_NONE = -1,
	FX_BABYSOUL_STATE_STAND,			// ��������
	FX_BABYSOUL_STATE_STAND_TO,			// ���ִ�   ���ۿ��� ���� �������� �̾����� ���� ���� �۾�
	FX_BABYSOUL_STATE_STAND_UP,			// �������� �������� 1 : ������ ������
	FX_BABYSOUL_STATE_STAND_UP_TO,		// ���ִ�   ���ۿ��� ���� �������� �̾����� ���� ���� �۾�
	FX_BABYSOUL_STATE_STAND_TELE,		// �������� �������� 2 : �׷���Ʈ
	FX_BABYSOUL_STATE_STAND_TELE_TO,	// ���ִ�   ���ۿ��� ���� �������� �̾����� ���� ���� �۾�
	FX_BABYSOUL_STATE_WALK,				// �ɾ�� ���
	FX_BABYSOUL_STATE_WALK_TO,			// �ȴ�     ���ۿ��� ���� �������� �̾����� ���� ���� �۾�
	FX_BABYSOUL_STATE_CRITICAL,			// ũ��Ƽ��
};

// ���ϸ޿��� ����
enum babysoul_ani
{
	FX_BABYSOUL_ANI_STAND = 0,	// ��������
	FX_BABYSOUL_ANI_STAND_UP,	// ������ ������
	FX_BABYSOUL_ANI_WALK,		// �ɾ�� ���
	FX_BABYSOUL_ANI_CRITICAL,	// ũ��Ƽ��
};

enum babysoul_tele_state
{
	BS_TELE_SHOW = -1,
	BS_TELE_FADEIN,
	BS_TELE_HIDE,
	BS_TELE_FADEOUT,
};

#define KIND_BABYSOUL_CSY 3 // CSY ����.
#define KIND_BABYSOUL_BPD (FX_BABYSOUL_ANI_CRITICAL+1) // BPD ����.

//////////////////////////////////////////////////////////////////////////

///�����̾���� ���� AI ������Ʈ
#define FX_VAPIREBAT_STATE_STAND			0  // �׳� ���ִ� ����. �Ĵ��Ĵ�, �� ��鸰��.
#define FX_VAPIREBAT_STATE_TURNROUND		1  // ������ ���� ���� ����.
#define FX_VAPIREBAT_STATE_FOLLOW			2  // ������ �i�ư��� ����.

///�����̾���� ���� �ִϸ��̼� ����
#define FX_VAPIREBAT_STAND_FRAME_TOTAL 12 // �� ������ �ִϸ��̼��� �� ������ ��
#define FX_VAPIREBAT_STAND_FRAME_WIDTH 4 // �� ������ �ִϸ��̼��� ���� ������ ��
#define FX_VAPIREBAT_MOVE_FRAME_TOTAL 12 // �� ������ �ִϸ��̼��� �� ������ ��
#define FX_VAPIREBAT_MOVE_FRAME_WIDTH 4 // �� ������ �ִϸ��̼��� ���� ������ ��

#define MAX_VAMPIREBAT_TRACE 25 ///�����̾���� ���� ��������Ʈ ���ý� ��
#define MAX_RING_LIGHT_TRACE 25 // [1/15/2008 �����] �Ϻ� �������� ����Ʈ ���ؽ� ��

///��絹�� AI ������Ʈ
#define FX_RUDOLPH_STATE_STAND			0  // �׳� ���ִ� ����.
#define FX_RUDOLPH_STATE_RANDOMWALK	1  // �ƹ� �������γ� �ɾ.(õõ��)
#define FX_RUDOLPH_STATE_FOLLOW		2  // ������ �i�ư��� ����.
#define FX_RUDOLPH_STATE_SOCIAL1		3  // ���� �ֱ�����(�ٸ� ����)
#define FX_RUDOLPH_STATE_SOCIAL2		4  // Ŭ���̾�Ʈ���� �ֺ� ������ ��,(���ݸ�� �̿�.����.)

#define KIND_RUDOLPH_CSY 6 // �絹�� �ִϸ��̼� CSY ����. // [2008/11/3 Theodoric] ���� �����̾� �̺�Ʈ������ �ϳ� ���� 5+1
#define KIND_RUDOLPH_BPD 4 // �絹�� �ִϸ��̼� ���� ����.
///��絹�� �ִϸ��̼� ����
#define FX_RUDOLPH_ANI_STAND		0  // �׳� ���ִ� ����.
#define FX_RUDOLPH_ANI_WALK			1  // �ƹ� �������γ� �ɾ.(õõ��)
#define FX_RUDOLPH_ANI_SOCIAL1		2  // ���ݵ���
#define FX_RUDOLPH_ANI_SOCIAL2		3  // �״� ����

// [1/15/2007 �����] �Ϻ� �������� ������Ʈ
#define FX_RING_LIGHT_STATE_FOLLOW		1  // ������ �i�ư��� ����.


#define ARUPAKA_CSY_MAX		3	// ĸ�� ����

enum ARUPAKAANI
{
	FX_ARUPAKA_ANI_WALK,		// �ȴ� ����
	FX_ARUPAKA_ANI_DOWN,		// �Ѿ����� ����
	FX_ARUPAKA_ANI_SPIT,		// ħ��� ����
	FX_ARUPAKA_ANI_MAX,			// �����е� ����

	FX_ARUPAKA_ANI_RANDOMWALK	= 10,
	FX_ARUPAKA_ANI_STAND		= 20
};


#define CATS_CSY_MAX		3
enum
{
	FX_CATS_ANI_STAND,
	FX_CATS_ANI_STAND2,
	FX_CATS_ANI_WALK,

	FX_CATS_ANI_MAX
};

enum
{
	CAT_STATE__STAND,
	CAT_STATE__SOCIAL1,
	CAT_STATE__RANDOMMOVE,
	CAT_STATE__FOLLOW,
};


#define RABBIT_CSY_MAX		3
enum
{
	FX_RABBIT_ANI_STAND,
	FX_RABBIT_ANI_STAND2,
	FX_RABBIT_ANI_WALK,

	FX_RABBIT_ANI_MAX
};

enum
{
	RABBIT_STATE__STAND,
	RABBIT_STATE__SOCIAL1,
	RABBIT_STATE__RANDOMMOVE,
	RABBIT_STATE__FOLLOW,
};

#define ZORO_CSY_MAX		3
enum
{
	FX_ZORO_ANI_STAND,
	FX_ZORO_ANI_STAND2,
	FX_ZORO_ANI_MOVE,
	FX_ZORO_ANI_MAX
};

enum
{
	ZORO_STATE_STAND,
	ZORO_STATE_SOCIAL1,
	ZORO_STATE_RANDOMMOVE,
	ZORO_STATE_FOLLOW,
};


#define DOGS_CSY_MAX		3
enum
{
	FX_DOGS_ANI_STAND,
	FX_DOGS_ANI_STAND2,
	FX_DOGS_ANI_MOVE,
	FX_DOGS_ANI_MAX
};

enum
{
	DOGS_STATE_STAND,
	DOGS_STATE_SOCIAL1,
	DOGS_STATE_RANDOMMOVE,
	DOGS_STATE_FOLLOW,
};

#define VALO_CSY_MAX		3

enum
{
	FX_VALO_ANI_STAND,
	FX_VALO_ANI_STAND2,
	FX_VALO_ANI_MOVE,
	FX_VALO_ANI_MAX
};
enum
{
	VALO_STATE_STAND,
	VALO_STATE_SOCIAL1,
	VALO_STATE_RANDOMMOVE,
	VALO_STATE_FOLLOW,
};

#define BEAR_CSY_MAX		2
enum
{
	FX_BEAR_ANI_IDLE,
	FX_BEAR_ANI_MOVE,
	FX_BEAR_ANI_STAND,
	FX_BEAR_ANI_MAX
};

enum
{
	BEAR_STATE_STAND,
	BEAR_STATE_IDLE,
	BEAR_STATE_RANDOMMOVE,
	BEAR_STATE_FOLLOW,
};

#define HORSE_CSY_MAX		2
enum
{
	FX_HORSE_ANI_STAND,
	FX_HORSE_ANI_STAND2,
	FX_HORSE_ANI_MOVE,
	FX_HORSE_ANI_MAX
};

enum
{
	HORSE_STATE_STAND,
	HORSE_STATE_SOCIAL1,
	HORSE_STATE_RANDOMMOVE,
	HORSE_STATE_FOLLOW,
};

#define JEGUAR_CSY_MAX		3
enum
{
	FX_JEGUAR_ANI_STAND,
	FX_JEGUAR_ANI_STAND2,
	FX_JEGUAR_ANI_MOVE,
	FX_JEGUAR_ANI_MAX
};

enum
{
	JEGUAR_STATE_STAND,
	JEGUAR_STATE_SOCIAL1,
	JEGUAR_STATE_SOCIAL2,
	JEGUAR_STATE_RANDOMMOVE,
	JEGUAR_STATE_FOLLOW,
};

#define BONI_CSY_MAX	3
enum
{
	FX_BONI_ANI_STAND,
	FX_BONI_ANI_STAND2,
	FX_BONI_ANI_MOVE,
	FX_BONI_ANI_MAX
};

enum
{
	BONI_STATE_STAND,
	BONI_STATE_SOCIAL1,
	BONI_STATE_RANDOMMOVE,
	BONI_STATE_FOLLOW,
};
// 345���� ������ ����Ʈ. ����.
class CFxFollow // ���𰡸� ����ٴϴ� ������ ����Ʈ. AI�� ���� ���� �ִ�.
{
public:
	CFxFollow();
	~CFxFollow();

	void DeleteRes();
	void LoadRes();

	void FrameMove( EffectSort &effect_sort, int nAddFrame ); // effect_sort�� �� �� ��Ʈ���� �����ȴ�. �� effect_sort�� �����ذ��鼭 ���������.
	void Render( EffectSort &effect_sort ); // �ְ�� ����� ��ο�.(����� 2D�� ����ӿ� ����. �����ú��� 3D�� �ƴ϶� 2D��ǥ��.)

	// �� ��
	CRectPlane* m_pMainObject;    // ������� �� ���� �ִ� Ŭ����.
	CRectPlane* m_pEffect1;
	CRectPlane* m_pEffect2;
	CLolos*		m_pLolo1;

	Deco_Particle *m_pParticleInfoArray; // Tail_Info Ŭ������ ��ƼŬ ���� Ŭ������ ����.


	// ���� �̺�Ʈ �� ������.
	CCapsyong *m_pCsyLuckyPig[KIND_LUCKY_PIG_CSY];
	CBiped	  *m_pBpdLuckyPig[KIND_LUCKY_PIG_BPD];


	// [7/31/2007 Theodoric] 6�ֳ� ��� �̺�Ʈ ���̺� �ҿ�
	int			m_BabySoulTextrIndex[KIND_BABYSOUL_CSY-1];
	CCapsyong*	m_pCsyBabySoul; //[KIND_BABYSOUL_CSY];
	CBiped*		m_pBpdBabySoul[KIND_BABYSOUL_BPD];

	///��絹��
	CCapsyong *m_pCsyRudolph[KIND_RUDOLPH_CSY];
	CBiped	  *m_pBpdRudolph[KIND_RUDOLPH_BPD];


	CCapsyong	*m_pCsyArupaka[ARUPAKA_CSY_MAX];
	CBiped		*m_pBpdArupaka[FX_ARUPAKA_ANI_MAX];
	bool		m_bSpit;
	CRectPlane	*m_pRectPlane;
	D3DVECTOR	m_vMasterPosDir;

	void SpitRender(EffectSort &effect_sort);


	CCapsyong * m_pCsyCats[CATS_CSY_MAX];
	CBiped * m_pBpdCats[FX_CATS_ANI_MAX];
	CCapsyong * m_pCsyRabbit[RABBIT_CSY_MAX];
	CBiped * m_pBpdRabbit[FX_RABBIT_ANI_MAX];
	CCapsyong * m_pCsyZoro[ZORO_CSY_MAX];
	CBiped * m_pBpdZoro[FX_ZORO_ANI_MAX];
	CCapsyong * m_pCsyDogs[DOGS_CSY_MAX];
	CBiped * m_pBpdDogs[FX_DOGS_ANI_MAX];
	CCapsyong * m_pCsyValo[VALO_CSY_MAX];
	CBiped * m_pBpdValo[FX_VALO_ANI_MAX];
	CCapsyong * m_pCsyBear[BEAR_CSY_MAX];
	CBiped * m_pBpdBear[FX_BEAR_ANI_MAX];
	CCapsyong * m_pCsyHorse[HORSE_CSY_MAX];
	CBiped * m_pBpdHorse[FX_HORSE_ANI_MAX];
	CCapsyong * m_pCsyJeguar[JEGUAR_CSY_MAX];
	CBiped * m_pBpdJeguar[FX_JEGUAR_ANI_MAX];
	CCapsyong * m_pCsyBoni[JEGUAR_CSY_MAX];
	CBiped * m_pBpdBoni[FX_JEGUAR_ANI_MAX];

	// [1/15/2008 �����] �Ϻ� �������� ����Ʈ ����.
	DWORD m_ring_Light_Color;
	DWORD m_ring_Light_TailColor;

	void	SetRing_Light_Color( int ringNum );

};

#endif // _FX_FOLLOW_H_