//
// Created by FangCybertron
//
#pragma once

#include "FangCyR/ZhackZ/LoaderSdk.hpp"

enum BattleState {
    WaitConnect,
    WaitReady,
    SelectHero,
    WaitLoading,
    Loading,
    Play,
    WaitEnd,
    End,
};

enum SkillUseType {
    CommonATK,
    NormalUse,
    ExpandUse,
    Passive,
    JustLearn,
    EquipSkill,
    HideConditionSkill,
};

enum EntityCampType {
    CampTypeUnkown,
    CampTypeA,
    CampTypeB,
    CampTypeA_Monster,
    CampTypeB_Monster,
    CampTypeJudger,
    CampTypeA_Looker,
    CampTypeB_Looker,
    CampTypeChickenStart,
    CampTypeChickenEnd,
    CampTypeNeutral,
};

enum SPELL_CAST_RESULT
{
    SPELL_CAST_NOCARE ,
    SPELL_CAST_NO_BASE_SPELL,
    SPELL_CAST_NO_OWNER,
    SPELL_CAST_IN_COOLDOWN,
    SPELL_CAST_ALLOC_MEM,
    SPELL_CAST_BULLET_NO_SPEED,
    SPELL_CAST_NO_ATT_SPEED,
    SPELL_CAST_NO_BASE_EFFECT,
    SPELL_CAST_WRONG_STATUS,
    SPELL_CAST_WRONG_STATUS_NOT_ATTACK,
    SPELL_CAST_OUT_DIS,
    SPELL_CAST_DEATH,
    SPELL_CAST_TRANSFER_ERROR,
    SPELL_CAST_CONTROL_NO_ADDTION,
    SPELL_CAST_TRANSER_SINGLE,
    SPELL_CAST_NO_ENOUGH_HP,
    SPELL_CAST_NO_ENOUGH_MP,
    SPELL_CAST_NO_ENOUGH_XP,
    SPELL_CAST_NO_UNIT,
    SPELL_CAST_WRONG_POS,
    SPELL_CAST_LOOP_CAST,
    SPELL_CAST_NO_SPELL,
    SPELL_CAST_NO_ENOUGH_LEVEL,
    SPELL_CAST_NO_LOCKTARGET,
    SPELL_LOCK_CATCHMOVE,
    SPELL_SEVER_BUSY,
    SPELL_MOVE_NO_LOCKTARGET,
    SPELL_CAST_WRONG_BEHAVIOR,
    SPELL_CAST_WRONG_LOCKSKILLID,
    SPELL_CAST_WRONG_LOCKSKILLBUFFID,
    SPELL_Cheack_Target_Inevitable,
    SPELL_Cheack_OneFrameSkillMaxNum,
    SPELL_IN_AUTO_ATTACK_AI,
    SPELL_Cheack_TranSkillID_Inevitable,
    SPELL_NO_FIGHTER,
    SPELL_FAIL_NOT_QUICK_MOVE,
    SPELL_CAST_ALREADY_LEARNED,
    SPELL_CAST_SkillBit,
    SPELL_CAST_HOLY_REPEAT,
    SPELL_ExceedMaxTriggerNumber,
    SPELL_NoSkillConfig,
    SPELL_HasQueue,
    SPELL_IN_AUTO_ATTACK_AI_COOLDOWN,
    SPELL_IsStoreSkill_Inevitable,
    SPELL_IsStoreSkill,
    SPELL_Cheack_SkillOvelap,
    SPELL_Cheack_Xuli_Inevitable,
    SPELL_CAST_SUCCESS,
};

class Screen {
public:
    static float get_dpi() {
        static const auto _ = reinterpret_cast<float(__fastcall *)()>(Class::Screen::get_dpi);
        return (float) _();
    }
    static void SetResolution(int width, int height, bool fullscreen) {
        static const auto _ = reinterpret_cast<void(__fastcall *)(int, int, bool)>(Class::Screen::SetResolution);
        return (void) _(width, height, fullscreen);
	}
};

class Display {
    public:
    static Display *_mainDisplay() {
        return *(Display **)(Class::Display::_mainDisplay);
    }
    int get_systemWidth() {
        static const auto _ = reinterpret_cast<int(__fastcall *)(Display *)>(Class::Display::get_systemWidth);
        return (int) _(this);
    }
    int get_systemHeight() {
        static const auto _ = reinterpret_cast<int(__fastcall *)(Display *)>(Class::Display::get_systemHeight);
        return (int) _(this);
    }
};

class Camera {
    public:
    static Camera *get_main() {
        static const auto _ = reinterpret_cast<Camera *(__fastcall *)()>(Class::Camera::get_main);
        return (Camera *) _();
    }
    float get_fieldOfView() {
        static const auto _ = reinterpret_cast<float(__fastcall *)(Camera *)>(Class::Camera::get_fieldOfView);
        return (float) _(this);
    }
    void set_fieldOfView(float value) {
        static const auto _ = reinterpret_cast<void(__fastcall *)(Camera *, float)>(Class::Camera::set_fieldOfView);
        return (void) _(this, value);
    }
    Vector3 WorldToScreenPoint(Vector3 position) {
        static const auto _ = reinterpret_cast<Vector3(__fastcall *)(Camera *, Vector3)>(Class::Camera::WorldToScreenPoint);
        return (Vector3) _(this, position);
    }
};

class ShowSkillData {
    public:
    int m_InitSkillID() {
        return *(int *)(this + Class::ShowSkillData::m_InitSkillID);
    }
};

class ShowOwnSkillComp {
    public:
    IL2CppList<ShowSkillData*> *m_SkillList() {
        return *(IL2CppList<ShowSkillData*> **)(this + Class::ShowOwnSkillComp::m_SkillList);
    }
};

class EntityBase {
    public:
    EntityCampType m_EntityCampType() {
        return *(EntityCampType *)(this + Class::EntityBase::m_EntityCampType);
    }
    bool m_bInitComplete() {
        return *(bool *)(this + Class::EntityBase::m_bInitComplete);
    }
    bool m_bDeath() {
        return *(bool *)(this + Class::EntityBase::m_bDeath);
    }
    bool m_bSameCampType() {
        return *(bool *)(this + Class::EntityBase::m_bSameCampType);
    }
    int m_Hp() {
        return *(int *)(this + Class::EntityBase::m_Hp);
    }
    int m_HpMax() {
        return *(int *)(this + Class::EntityBase::m_HpMax);
    }
    int m_iType() {
        return *(int *)(this + Class::EntityBase::m_iType);
    }
    int m_ID() {
        return *(int *)(this + Class::EntityBase::m_ID);
    }
    int m_Level() {
        return *(int *)(this + Class::EntityBase::m_Level);
    }
};

class ShowEntity : public EntityBase {
    public:
    bool m_bShowLayer() {
        return *(bool *)(this + Class::ShowEntity::m_bShowLayer);
    }
    Vector3 _Position() {
        return *(Vector3 *)(this + Class::ShowEntity::_Position);
    }
    ShowOwnSkillComp *m_OwnSkillComp() {
        return *(ShowOwnSkillComp **)(this + Class::ShowEntity::m_OwnSkillComp);
    }
};

class FightPlayerData {
    public:
    int iMythPoint(){
        return *(int *)(this + Class::FightPlayerData::iMythPoint);
    }
    int uiRankLevel(){//rank level
        return *(int *)(this + Class::FightPlayerData::uiRankLevel);
    }
};


class ShowPlayer : public ShowEntity{
    public:
    Il2CppString *m_HeroName() {
        return *(Il2CppString **)(this + Class::ShowPlayer::m_HeroName);
    }
    int m_iSummonSkillId() {
        return *(int *)(this + Class::ShowPlayer::m_iSummonSkillId);
    }
    SkillUseType GetSkillUseType(int skillId) {
        static const auto _ = reinterpret_cast<SkillUseType(__fastcall *)(ShowPlayer *, int)>(Class::ShowPlayer::GetSkillUseType);
        return (SkillUseType) _(this, skillId);
    }
    FightPlayerData *m_SynFightData(){//get player data in battle
        return *(FightPlayerData **)(this + Class::ShowPlayer::m_SynFightData);
    }
};

class ShowSelfPlayer{
public:
    SPELL_CAST_RESULT TryUseSkill(int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAttack = true, bool bAlong = false, bool isInFirstDragRange = false, bool bIgnoreQueue = false, uint dragTime = 0)
    {
        typedef SPELL_CAST_RESULT (__fastcall * t_TryUseSkill)(ShowSelfPlayer * Base, int skillId, Vector3 dir, bool dirDefault, Vector3 pos, bool bCommonAttack, bool bAlong, bool isInFirstDragRange, bool bIgnoreQueue, uint dragTime);
        static t_TryUseSkill TryUseSkill = (t_TryUseSkill)(this + Class::ShowSelfPlayer::TryUseSkill);
        return TryUseSkill(this, skillId, dir, dirDefault, pos, bCommonAttack, bAlong, isInFirstDragRange, bIgnoreQueue, dragTime);
    }
};

class BattleManager {
    public:
    static BattleManager *Instance(){
        return *(BattleManager **)(Class::BattleManager::Instance);
    }
    ShowPlayer *m_LocalPlayerShow() {
        return *(ShowPlayer **)(this + Class::BattleManager::m_LocalPlayerShow);
    }
    IL2CppDictionary<int, ShowPlayer*> *m_dicPlayerShow() {
        return *(IL2CppDictionary<int, ShowPlayer*> **)(this + Class::BattleManager::m_dicPlayerShow);
    }
    IL2CppDictionary<int, ShowPlayer*> *m_dicMonsterShow() {
        return *(IL2CppDictionary<int, ShowPlayer*> **)(this + Class::BattleManager::m_dicMonsterShow);
    }
    IL2CppList<ShowEntity*> *m_ShowPlayers() {
        return *(IL2CppList<ShowEntity*> **)(this + Class::BattleManager::m_ShowPlayers);
    }
    IL2CppList<ShowEntity*> *m_ShowMonsters() {
        return *(IL2CppList<ShowEntity*> **)(this + Class::BattleManager::m_ShowMonsters);
    }
};

class CoolDownData {
    public:
    int GetCoolTime() {
        static const auto _ = reinterpret_cast<int(__fastcall *)(CoolDownData *)>(Class::CoolDownData::GetCoolTime);
        return (int) _(this);
    }
};

class CoolDownComp {
    public:
    bool IsCoolDownForShowRealId(int iSpellID) {
        static const auto _ = reinterpret_cast<bool(__fastcall *)(CoolDownComp *, int)>(Class::CoolDownComp::IsCoolDownForShowRealId);
        return (bool) _(this, iSpellID);
    }
};

class LogicSkillComp {
    public:
    CoolDownData *GetSkillMaxCDDown(int skillid) {
        static const auto _ = reinterpret_cast<CoolDownData *(__fastcall *)(LogicSkillComp *, int)>(Class::LogicSkillComp::GetSkillMaxCDDown);
        return (CoolDownData *) _(this, skillid);
    }
    CoolDownComp *m_CoolDownComp() {
        return *(CoolDownComp **)(this + Class::LogicSkillComp::m_CoolDownComp);
    }
};

class LogicFighter : public EntityBase {
    public:
    LogicSkillComp *m_SkillComp() {
        return *(LogicSkillComp **)(this + Class::LogicFighter::m_SkillComp);
    }
};

class PlayerData {
    public:
    int killNum(){
        return *(int *)(this + Class::PlayerData::_killNum);
    }

    int assistNum(){
        return *(int *)(this + Class::PlayerData::_assistNum);
    }

};

class LogicPlayer {
    public:
    int KillWildTimes() {
        return *(int *)(this + Class::LogicPlayer::_KillWildTimes);
    }

    static PlayerData *m_PlayerData(){
        return *(PlayerData **)(Class::LogicPlayer::m_PlayerData);
    }
};

class LogicBattleManager {
    public:
    static LogicBattleManager *Instance() {
        return *(LogicBattleManager **)(Class::LogicBattleManager::Instance);
    }
    BattleState _m_eState() {
        return *(BattleState *)(this + Class::LogicBattleManager::_m_eState);
    }
    LogicFighter *GetFighterLogic(int id) {
        static const auto _ = reinterpret_cast<LogicFighter *(__fastcall *)(LogicBattleManager *, int)>(Class::LogicBattleManager::GetFighterLogic);
        return (LogicFighter *) _(this, id);
    }

    static LogicPlayer *GetPlayerRealSelf(){
        return *(LogicPlayer **)(Class::LogicBattleManager::GetPlayerRealSelf);
    }
};

class BattleBridge {
    public:
    bool bStartBattle() {
        return *(bool *)(this + Class::BattleBridge::bStartBattle);
    }
};

class RoomData {
    public:
    Il2CppString *_sName() {
        return *(Il2CppString **)(this + Class::RoomData::_sName);
    }
    int iCamp() {
        return *(int *)(this + Class::RoomData::iCamp);
    }
    int iPos() {
        return *(int *)(this + Class::RoomData::iPos);
    }
    int lUid() {
        return *(int *)(this + Class::RoomData::lUid);
    }
    int uiZoneId() {
        return *(int *)(this + Class::RoomData::uiZoneId);
    }
    int uiRankLevel() {
        return *(int *)(this + Class::RoomData::uiRankLevel);
    }
    int iMythPoint() {
        return *(int *)(this + Class::RoomData::iMythPoint);
    }
    int iCertify() {
        return *(int *)(this + Class::RoomData::iCertify);
    }
    int heroid() {
        return *(int *)(this + Class::RoomData::heroid);
    }
    int summonSkillId() {
        return *(int *)(this + Class::RoomData::summonSkillId);
    }
};

class SystemData {
    public:
    static int m_uiID() {
        return *(int *)(Class::SystemData::m_uiID);
    }
    static int m_reportRate(){
        return *(int *)(Class::SystemData::m_reportRate);
    }
    static bool IsVpn(){
        if(Class::SystemData::IsVpn != 0 || Class::SystemData::IsVpn != NULL){
            return *(bool *)(Class::SystemData::IsVpn);
        }
        return false;
    }
    static IL2CppList<RoomData*> *GetBattlePlayerInfo() {
        static const auto _ = reinterpret_cast<IL2CppList<RoomData*> *(__fastcall *)()>(Class::SystemData::GetBattlePlayerInfo);
        return (IL2CppList<RoomData*> *) _();
    }
};

class BattleData {
    public:
    static BattleManager *battleManager() {
        return *(BattleManager **)(Class::BattleData::battleManager);
    }
    static BattleBridge *m_BattleBridge() {
        return *(BattleBridge **)(Class::BattleData::m_BattleBridge);
    }
};

class GameMain {
    public:
    static GameMain *Instance() {
        return *(GameMain **)(Class::GameMain::Instance);
    }
    bool _bGameInitDone() {
        return *(bool *)(this + Class::GameMain::_bGameInitDone);
    }
};
bool (*oIsSignatureSame)(std::string kSignature);
bool IsSignatureSame(std::string kSignature){
    return true;
}

void (*oPlugInTesting)(void *unk);
void PlugInTesting(void *unk) {
    return;

}
