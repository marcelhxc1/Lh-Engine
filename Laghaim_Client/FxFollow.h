#ifndef _FX_FOLLOW_H_
#define _FX_FOLLOW_H_

// FOLLOW 이펙트의 종류.
/*#define FX_FOLLOW_TYPE_FAIRY		0 // 345레벨 아이템 페어리.
#define FX_FOLLOW_TYPE_LUCKYPIG     1 // 설날 이벤트 복돼지
#define FX_FOLLOW_TYPE_BABYSOUL		2 // [7/31/2007 Theodoric] 6주년 기념 이벤트 베비이 소울
#define FX_FOLLOW_TYPE_VAMPIREBAT   3 ///뱀파이어망토 박쥐
#define FX_FOLLOW_TYPE_RUDOLPH		4 ///펫루돌프
#define FX_FOLLOW_TYPE_RING_LIGHT	5 // [1/15/2008 반재승] 일본 링 아이템 이펙트*/
enum FXTYPE
{
	FX_FOLLOW_TYPE_FAIRY,		// 345레벨 아이템 페어리.
	FX_FOLLOW_TYPE_LUCKYPIG,	// 설날 이벤트 복돼지
	FX_FOLLOW_TYPE_BABYSOUL,	// 6주년 기념 이벤트 베비이 소울
	FX_FOLLOW_TYPE_VAMPIREBAT,	// 뱀파이어망토 박쥐
	FX_FOLLOW_TYPE_RUDOLPH,		// 펫루돌프
	FX_FOLLOW_TYPE_RING_LIGHT,	// 일본 링 아이템 이펙트
	FX_FOLLOW_TYPE_ARUPAKAPET,	// 알파카펫
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

//#define FX_FAIRY_SIZE 20.0f // 페어리 크기

// 프레임 구성 정보
#define FX_FAIRY_MOVE_FRAME_TOTAL 16 // 페어리 움직임 애니메이션의 총 프레임 수
#define FX_FAIRY_MOVE_FRAME_WIDTH 8 // 페어리 움직임 애니메이션의 가로 프레임 수

#define FX_FAIRY_BLOCK_FRAME_TOTAL 16 // 페어리 블럭킹 애니메이션의 총 프레임 수
#define FX_FAIRY_BLOCK_FRAME_WIDTH 8 // 페어리 블럭킹 애니메이션의 가로 프레임 수

#define FX_FAIRY_SHOW1_FRAME_TOTAL 8 // 페어리 구라 때리기 애니메이션의 총 프레임수
#define FX_FAIRY_SHOW1_FRAME_WIDTH 8 // 페어리 구라 때리기 애니메이션의 가로 프레임 수

// AI 스테이트
#define FX_FAIRY_STATE_STAND		0  // 둥둥 떠있는 상태.
#define FX_FAIRY_STATE_SIDESTEP		1  // 좌우로 느리게 이동.
#define FX_FAIRY_STATE_TURNROUND	2  // 주인을 빙빙 도는 상태.
#define FX_FAIRY_STATE_FOLLOW		3  // 주인을 쫒아가는 상태.
#define FX_FAIRY_STATE_BLOCKING		4  // 방어막치기.
#define FX_FAIRY_STATE_SHOW1		5  // 챗바퀴 돌기 모션.

#define MAX_PARTICLE_FOR_FXFOLLOW  15 // 파티클 최대 갯수.

// 복돼지 AI 스테이트
#define FX_LUCKYPIG_STATE_STAND			0  // 그냥 서있는 상태.
#define FX_LUCKYPIG_STATE_RANDOMWALK	1  // 아무 방향으로나 걸어감.(천천히)
#define FX_LUCKYPIG_STATE_FOLLOW		2  // 주인을 쫒아가는 상태.
#define FX_LUCKYPIG_STATE_SOCIAL1		3  // 서서 애교동작
#define FX_LUCKYPIG_STATE_SOCIAL2		4  // 클라이언트에서 주변 돌리는 춤
#define FX_LUCKYPIG_STATE_HEAL			5  // 회복 모션

#define KIND_LUCKY_PIG_CSY 4 // 복돼지의 종류 갯수.
#define KIND_LUCKY_PIG_BPD 5 // 복돼지의 종류 갯수.

// 복돼지 애니메이션 구분
#define FX_LUCKYPIG_ANI_STAND		0  // 그냥 서있는 상태.
#define FX_LUCKYPIG_ANI_WALK		1  // 아무 방향으로나 걸어감.(천천히)
#define FX_LUCKYPIG_ANI_SOCIAL1		2  // 서서 애교동작
#define FX_LUCKYPIG_ANI_SOCIAL2		3  // 클라이언트에서 주변 돌리는 춤
#define FX_LUCKYPIG_ANI_HEAL		4  // 회복 모션

// [1/15/2008 반재승] 일본 링 아이템 종류
#define FX_RING_WHITE			0  // 샤이니 링
#define FX_RING_DARK			1  // 쉐도우 링
#define FX_RING_RED				2  // 브라이트 레드 링
#define FX_RING_BLUE			3  // 브라이트 블루 링
#define FX_RING_GREEN			4  // 브라이트 그린 링
#define FX_RING_GOLD			5  // by evilkiki 2010.07.09 골드 이펙트



//////////////////////////////////////////////////////////////////////////
// [7/31/2007 Theodoric] 6주년 기념 이벤트 베이비 소울

// 상태 구분
enum babysoul_state
{
	FX_BABYSOUL_STATE_NONE = -1,
	FX_BABYSOUL_STATE_STAND,			// 서있을때
	FX_BABYSOUL_STATE_STAND_TO,			// 서있는   동작에서 다음 동작으로 이어지기 위한 보정 작업
	FX_BABYSOUL_STATE_STAND_UP,			// 서있을때 랜덤동작 1 : 날개짓 오르기
	FX_BABYSOUL_STATE_STAND_UP_TO,		// 서있는   동작에서 다음 동작으로 이어지기 위한 보정 작업
	FX_BABYSOUL_STATE_STAND_TELE,		// 서있을때 랜덤동작 2 : 테렐포트
	FX_BABYSOUL_STATE_STAND_TELE_TO,	// 서있는   동작에서 다음 동작으로 이어지기 위한 보정 작업
	FX_BABYSOUL_STATE_WALK,				// 걸어가는 모습
	FX_BABYSOUL_STATE_WALK_TO,			// 걷는     동작에서 다음 동작으로 이어지기 위한 보정 작업
	FX_BABYSOUL_STATE_CRITICAL,			// 크리티컬
};

// 에니메에션 구분
enum babysoul_ani
{
	FX_BABYSOUL_ANI_STAND = 0,	// 서있을때
	FX_BABYSOUL_ANI_STAND_UP,	// 날개짓 오르기
	FX_BABYSOUL_ANI_WALK,		// 걸어가는 모습
	FX_BABYSOUL_ANI_CRITICAL,	// 크리티컬
};

enum babysoul_tele_state
{
	BS_TELE_SHOW = -1,
	BS_TELE_FADEIN,
	BS_TELE_HIDE,
	BS_TELE_FADEOUT,
};

#define KIND_BABYSOUL_CSY 3 // CSY 갯수.
#define KIND_BABYSOUL_BPD (FX_BABYSOUL_ANI_CRITICAL+1) // BPD 갯수.

//////////////////////////////////////////////////////////////////////////

///뱀파이어망토 박쥐 AI 스테이트
#define FX_VAPIREBAT_STATE_STAND			0  // 그냥 서있는 상태. 파닥파닥, 좀 흔들린다.
#define FX_VAPIREBAT_STATE_TURNROUND		1  // 주인을 빙빙 도는 상태.
#define FX_VAPIREBAT_STATE_FOLLOW			2  // 주인을 쫒아가는 상태.

///뱀파이어망토 박쥐 애니메이션 정보
#define FX_VAPIREBAT_STAND_FRAME_TOTAL 12 // 페어리 움직임 애니메이션의 총 프레임 수
#define FX_VAPIREBAT_STAND_FRAME_WIDTH 4 // 페어리 움직임 애니메이션의 가로 프레임 수
#define FX_VAPIREBAT_MOVE_FRAME_TOTAL 12 // 페어리 움직임 애니메이션의 총 프레임 수
#define FX_VAPIREBAT_MOVE_FRAME_WIDTH 4 // 페어리 움직임 애니메이션의 가로 프레임 수

#define MAX_VAMPIREBAT_TRACE 25 ///뱀파이어망토 박쥐 궤적이펙트 버택스 수
#define MAX_RING_LIGHT_TRACE 25 // [1/15/2008 반재승] 일본 링아이템 이펙트 버텍스 수

///펫루돌프 AI 스테이트
#define FX_RUDOLPH_STATE_STAND			0  // 그냥 서있는 상태.
#define FX_RUDOLPH_STATE_RANDOMWALK	1  // 아무 방향으로나 걸어감.(천천히)
#define FX_RUDOLPH_STATE_FOLLOW		2  // 주인을 쫒아가는 상태.
#define FX_RUDOLPH_STATE_SOCIAL1		3  // 서서 애교동작(다리 떨기)
#define FX_RUDOLPH_STATE_SOCIAL2		4  // 클라이언트에서 주변 돌리는 춤,(공격모션 이용.복싱.)

#define KIND_RUDOLPH_CSY 6 // 루돌프 애니메이션 CSY 접수. // [2008/11/3 Theodoric] 국내 프리미엄 이벤트용으로 하나 생성 5+1
#define KIND_RUDOLPH_BPD 4 // 루돌프 애니메이션 종류 갯수.
///펫루돌프 애니메이션 구분
#define FX_RUDOLPH_ANI_STAND		0  // 그냥 서있는 상태.
#define FX_RUDOLPH_ANI_WALK			1  // 아무 방향으로나 걸어감.(천천히)
#define FX_RUDOLPH_ANI_SOCIAL1		2  // 공격동작
#define FX_RUDOLPH_ANI_SOCIAL2		3  // 죽는 동작

// [1/15/2007 반재승] 일본 링아이템 스테이트
#define FX_RING_LIGHT_STATE_FOLLOW		1  // 주인을 쫒아가는 상태.


#define ARUPAKA_CSY_MAX		3	// 캡숑 갯수

enum ARUPAKAANI
{
	FX_ARUPAKA_ANI_WALK,		// 걷는 동작
	FX_ARUPAKA_ANI_DOWN,		// 넘어지는 동작
	FX_ARUPAKA_ANI_SPIT,		// 침뱉는 동작
	FX_ARUPAKA_ANI_MAX,			// 바이패드 갯수

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
// 345레벨 아이템 이펙트. 요정.
class CFxFollow // 무언가를 따라다니는 종류의 이펙트. AI를 가질 수도 있다.
{
public:
	CFxFollow();
	~CFxFollow();

	void DeleteRes();
	void LoadRes();

	void FrameMove( EffectSort &effect_sort, int nAddFrame ); // effect_sort는 각 페어리 셋트마다 생성된다. 이 effect_sort를 갱신해가면서 출력해주자.
	void Render( EffectSort &effect_sort ); // 왜곡된 평면을 드로우.(평면이 2D용 평면임에 유의. 만들당시부터 3D가 아니라 2D좌표다.)

	// 페어리 용
	CRectPlane* m_pMainObject;    // 빌보드로 쓸 수도 있는 클래스.
	CRectPlane* m_pEffect1;
	CRectPlane* m_pEffect2;
	CLolos*		m_pLolo1;

	Deco_Particle *m_pParticleInfoArray; // Tail_Info 클래스를 파티클 정보 클래스로 쓴다.


	// 설날 이벤트 복 돼지용.
	CCapsyong *m_pCsyLuckyPig[KIND_LUCKY_PIG_CSY];
	CBiped	  *m_pBpdLuckyPig[KIND_LUCKY_PIG_BPD];


	// [7/31/2007 Theodoric] 6주년 기념 이벤트 베이비 소울
	int			m_BabySoulTextrIndex[KIND_BABYSOUL_CSY-1];
	CCapsyong*	m_pCsyBabySoul; //[KIND_BABYSOUL_CSY];
	CBiped*		m_pBpdBabySoul[KIND_BABYSOUL_BPD];

	///펫루돌프
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

	// [1/15/2008 반재승] 일본 링아이템 이펙트 관련.
	DWORD m_ring_Light_Color;
	DWORD m_ring_Light_TailColor;

	void	SetRing_Light_Color( int ringNum );

};

#endif // _FX_FOLLOW_H_