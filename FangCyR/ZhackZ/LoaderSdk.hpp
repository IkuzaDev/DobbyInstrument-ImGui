//
// Created by FangCybertron
// public FightPlayerData m_SynFightData; // 0x5C0
#pragma once

namespace Class {
    namespace Screen {
        uintptr_t get_dpi = 0;
        uintptr_t SetResolution = 0;
    }
    namespace Display {
        uintptr_t _mainDisplay = 0;
        uintptr_t get_systemWidth = 0;
        uintptr_t get_systemHeight = 0;
    }
    namespace Camera {
        uintptr_t get_main = 0;
        uintptr_t get_fieldOfView = 0;
        uintptr_t set_fieldOfView = 0;
        uintptr_t WorldToScreenPoint = 0;
    }
    namespace ShowSkillData {
        uintptr_t m_InitSkillID = 0;
    }
    namespace ShowOwnSkillComp {
        uintptr_t m_SkillList = 0;
    }
    namespace EntityBase {
        uintptr_t m_EntityCampType = 0;
        uintptr_t m_bInitComplete = 0;
        uintptr_t m_bDeath = 0;
        uintptr_t m_bSameCampType = 0;
        uintptr_t m_Hp = 0;
        uintptr_t m_HpMax = 0;
        uintptr_t m_iType = 0;
        uintptr_t m_ID = 0;
        uintptr_t m_Level = 0;
    }
    namespace ShowEntity {
        uintptr_t m_bShowLayer = 0;
        uintptr_t _Position = 0;
        uintptr_t m_OwnSkillComp = 0;
    }
    namespace FightPlayerData {//esp rank
        uintptr_t uiRankLevel = 0;
        uintptr_t iMythPoint = 0;
    }
    namespace ShowPlayer {
        uintptr_t GetSkillUseType = 0;
        uintptr_t m_HeroName = 0;
        uintptr_t m_iSummonSkillId = 0;
        uintptr_t m_SynFightData = 0;
    }
    namespace BattleManager {
        uintptr_t m_LocalPlayerShow = 0;
        uintptr_t m_dicPlayerShow = 0;
        uintptr_t m_dicMonsterShow = 0;
        uintptr_t Instance = 0;
        uintptr_t m_ShowPlayers = 0;
        uintptr_t _RunBullets = 0;
        uintptr_t m_ShowMonsters = 0;
    }
    namespace CoolDownData {
        uintptr_t GetCoolTime = 0;
    }
    namespace CoolDownComp {
        uintptr_t IsCoolDownForShowRealId = 0;
    }
    namespace LogicSkillComp {
        uintptr_t GetSkillMaxCDDown = 0;
        uintptr_t m_CoolDownComp = 0;
    }
    namespace LogicFighter {
        uintptr_t m_SkillComp = 0;
    }
    namespace LogicBattleManager {
        uintptr_t Instance = 0;
        uintptr_t _m_eState = 0;
        uintptr_t GetFighterLogic = 0;
        uintptr_t GetPlayerRealSelf = 0;
    }
    namespace BattleBridge {
        uintptr_t bStartBattle = 0;
    }
    namespace RoomData {
        uintptr_t iPos = 0;
        uintptr_t iCamp = 0;
        uintptr_t _sName = 0;
        uintptr_t lUid = 0;
        uintptr_t uiZoneId = 0;
        uintptr_t uiRankLevel = 0;
        uintptr_t iMythPoint = 0;
        uintptr_t iCertify = 0;
        uintptr_t heroid = 0;
        uintptr_t summonSkillId = 0;
    }
    namespace SystemData {
        uintptr_t m_uiID = 0;
        uintptr_t m_reportRate = 0;
        uintptr_t IsVpn = 0;
        uintptr_t GetBattlePlayerInfo = 0;
        uintptr_t GetHeroSkin = 0;
        uintptr_t IsHaveSkin = 0;
        uintptr_t IsHaveSkinForever = 0;
        uintptr_t IsForbidSkin = 0;
        uintptr_t IsForbidARSkin = 0;
    }
    namespace BattleData {
        uintptr_t battleManager = 0;
        uintptr_t m_BattleBridge = 0;
    }
    namespace GameMain {
        uintptr_t Instance = 0;
        uintptr_t _bGameInitDone = 0;
        uintptr_t PlugInTesting = 0;
    }
    namespace UIRankHeroChangeShow {
        uintptr_t iSelfHero = 0;
        uintptr_t SendUseSkin = 0;
    }
    namespace UIChooseHero {
        uintptr_t BatttleSelectSkin = 0;
    }
    namespace UIRankHero {
        uintptr_t BatttleSelectSkin = 0;
    }
    namespace ChooseHeroMgr {
        uintptr_t SendSelectSkin = 0;
    }
    namespace BattleReceiveMessage {
        uintptr_t SetPlayerData = 0;
        uintptr_t SetPlayerData_ = 0;
        uintptr_t AddPlayerInfo = 0;
        uintptr_t AddPlayerInfo_ = 0;
    }
    namespace BattlePlayerInfo {
        uintptr_t lUid = 0;
        uintptr_t uiSelHero = 0;
        uintptr_t uiSkinId = 0;
        uintptr_t uiRankLevel = 0;
        uintptr_t bBanChat = 0;
        uintptr_t uiRoleLevel = 0;
    }
    namespace LoginLogData {
        uintptr_t m_StepID = 0;
    }
    namespace ShowSelfPlayer {
        uintptr_t TryUseSkill = 0;
        uintptr_t OnUpdate = 0;
    }
    namespace Bullet {
        uintptr_t m_Id = 0;
        uintptr_t m_Target = 0;
        uintptr_t transform = 0;
    }
    namespace Transform {
        uintptr_t get_position = 0;
    }
    namespace LogicPlayer {
        uintptr_t _KillWildTimes = 0;
        uintptr_t m_PlayerData = 0;
    }
    namespace PlayerData {
        uintptr_t _killNum = 0;
        uintptr_t _assistNum = 0;
    }
    namespace ClientLogReportSwitch{
        uintptr_t iReportPercentage = 0;
    }
    namespace APKSignature{
        uintptr_t IsSignatureSame = 0;
        uintptr_t SetAPKSignature = 0;
    }
    namespace GameReceiveMessage{
        uintptr_t SendGameReport = 0;
    }
}

void LoaderPrivate() {
    auto Screen = new FangEngine(OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"));
    Class::Screen::get_dpi = (uintptr_t) Screen->Il2CppGetMethod(OBFUSCATE("get_dpi"), 0);
    Class::Screen::SetResolution = (uintptr_t) Screen->Il2CppGetMethod(OBFUSCATE("SetResolution"), 3);
    
    auto Display = new FangEngine(OBFUSCATE("UnityEngine"), OBFUSCATE("Display"));
    Class::Display::_mainDisplay = (uintptr_t) Display->Il2CppGetField(OBFUSCATE("_mainDisplay"));
    Class::Display::get_systemWidth = (uintptr_t) Display->Il2CppGetMethod(OBFUSCATE("get_systemWidth"), 0);
    Class::Display::get_systemHeight = (uintptr_t) Display->Il2CppGetMethod(OBFUSCATE("get_systemHeight"), 0);
}

void LoaderPublic() {
    auto Camera = new FangEngine(OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"));
    Class::Camera::get_main = (uintptr_t) Camera->Il2CppGetMethod(OBFUSCATE("get_main"), 0);
    Class::Camera::get_fieldOfView = (uintptr_t) Camera->Il2CppGetMethod(OBFUSCATE("get_fieldOfView"), 0);
    Class::Camera::set_fieldOfView = (uintptr_t) Camera->Il2CppGetMethod(OBFUSCATE("set_fieldOfView"), 1);
    Class::Camera::WorldToScreenPoint = (uintptr_t) Camera->Il2CppGetMethod(OBFUSCATE("WorldToScreenPoint"), 1);
    
    auto ShowSkillData = new FangEngine(OBFUSCATE(""), OBFUSCATE("ShowSkillData"));
    Class::ShowSkillData::m_InitSkillID = (uintptr_t) ShowSkillData->Il2CppGetField(OBFUSCATE("m_InitSkillID"));
    
    auto ShowOwnSkillComp = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("ShowOwnSkillComp"));
    Class::ShowOwnSkillComp::m_SkillList = (uintptr_t) ShowOwnSkillComp->Il2CppGetField(OBFUSCATE("m_SkillList"));
    
    auto EntityBase = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("ShowEntityBase"));
    Class::EntityBase::m_EntityCampType = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_EntityCampType"));
    Class::EntityBase::m_bInitComplete = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_bInitComplete"));
    Class::EntityBase::m_bDeath = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("<m_bDeath>k__BackingField"));
    Class::EntityBase::m_bSameCampType = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_bSameCampType"));
    Class::EntityBase::m_Hp = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_Hp"));
    Class::EntityBase::m_HpMax = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_HpMax"));
    Class::EntityBase::m_iType = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_iType"));
    Class::EntityBase::m_ID = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_ID"));
    Class::EntityBase::m_Level = (uintptr_t) EntityBase->Il2CppGetField(OBFUSCATE("m_Level"));
    
    auto ShowEntity = new FangEngine(OBFUSCATE(""), OBFUSCATE("ShowEntity"));
    Class::ShowEntity::m_bShowLayer = (uintptr_t) ShowEntity->Il2CppGetField(OBFUSCATE("m_bShowLayer"));
    Class::ShowEntity::_Position = (uintptr_t) ShowEntity->Il2CppGetField(OBFUSCATE("_Position"));
    Class::ShowEntity::m_OwnSkillComp = (uintptr_t) ShowEntity->Il2CppGetField(OBFUSCATE("m_OwnSkillComp"));

    auto FightPlayerData = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("FightPlayerData"));
    Class::FightPlayerData::iMythPoint = (uintptr_t) FightPlayerData->Il2CppGetField(OBFUSCATE("iMythPoint"));
    Class::FightPlayerData::uiRankLevel = (uintptr_t) FightPlayerData->Il2CppGetField(OBFUSCATE("uiRankLevel"));
    
    auto ShowPlayer = new FangEngine(OBFUSCATE(""), OBFUSCATE("ShowPlayer"));
    Class::ShowPlayer::m_HeroName = (uintptr_t) ShowPlayer->Il2CppGetField(OBFUSCATE("m_HeroName"));
    Class::ShowPlayer::m_iSummonSkillId = (uintptr_t) ShowPlayer->Il2CppGetField(OBFUSCATE("m_iSummonSkillId"));
    Class::ShowPlayer::GetSkillUseType = (uintptr_t) ShowPlayer->Il2CppGetMethod(OBFUSCATE("GetSkillUseType"), 1);
    Class::ShowPlayer::m_SynFightData = (uintptr_t) ShowPlayer->Il2CppGetField(OBFUSCATE("m_SynFightData"));
    
    
    auto BattleManager = new FangEngine(OBFUSCATE(""), OBFUSCATE("BattleManager"));
    Class::BattleManager::m_LocalPlayerShow = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("m_LocalPlayerShow"));
    Class::BattleManager::m_dicPlayerShow = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("m_dicPlayerShow"));
    Class::BattleManager::m_dicMonsterShow = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("m_dicMonsterShow"));
    Class::BattleManager::Instance = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("Instance"));
    Class::BattleManager::m_ShowPlayers = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("m_ShowPlayers"));
    Class::BattleManager::_RunBullets = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("_RunBullets"));
    Class::BattleManager::m_ShowMonsters = (uintptr_t) BattleManager->Il2CppGetField(OBFUSCATE("m_ShowMonsters"));
    
    auto CoolDownData = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("CoolDownData"));
    Class::CoolDownData::GetCoolTime = (uintptr_t) CoolDownData->Il2CppGetMethod(OBFUSCATE("GetCoolTime"), 0);
    
    auto CoolDownComp = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("CoolDownComp"));
    Class::CoolDownComp::IsCoolDownForShowRealId = (uintptr_t) CoolDownComp->Il2CppGetMethod(OBFUSCATE("IsCoolDownForShowRealId"), 1);
    
    auto LogicSkillComp = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("LogicSkillComp"));
    Class::LogicSkillComp::GetSkillMaxCDDown = (uintptr_t) LogicSkillComp->Il2CppGetMethod(OBFUSCATE("GetSkillMaxCDDown"), 1);
    Class::LogicSkillComp::m_CoolDownComp = (uintptr_t) LogicSkillComp->Il2CppGetField(OBFUSCATE("m_CoolDownComp"));
    
    auto LogicFighter = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("LogicFighter"));
    Class::LogicFighter::m_SkillComp = (uintptr_t) LogicFighter->Il2CppGetField(OBFUSCATE("m_SkillComp"));
    
    auto LogicBattleManager = new FangEngine(OBFUSCATE(""), OBFUSCATE("LogicBattleManager"));
    Class::LogicBattleManager::Instance = (uintptr_t) LogicBattleManager->Il2CppGetField(OBFUSCATE("Instance"));
    Class::LogicBattleManager::_m_eState = (uintptr_t) LogicBattleManager->Il2CppGetField(OBFUSCATE("_m_eState"));
    Class::LogicBattleManager::GetFighterLogic = (uintptr_t) LogicBattleManager->Il2CppGetMethod(OBFUSCATE("GetFighterLogic"), 1);
    Class::LogicBattleManager::GetPlayerRealSelf = (uintptr_t) LogicBattleManager->Il2CppGetMethod(OBFUSCATE("GetPlayerRealSelf"), 0);
    
    auto BattleBridge = new FangEngine(OBFUSCATE(""), OBFUSCATE("BattleBridge"));
    Class::BattleBridge::bStartBattle = (uintptr_t) BattleBridge->Il2CppGetField(OBFUSCATE("bStartBattle"));
    
    auto RoomData = new FangEngine(OBFUSCATE(""), OBFUSCATE("SystemData/RoomData"));
    Class::RoomData::_sName = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("_sName"));
    Class::RoomData::iCamp = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("iCamp"));
    Class::RoomData::iPos = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("iPos"));
    Class::RoomData::lUid = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("lUid"));
    Class::RoomData::uiZoneId = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("uiZoneId"));
    Class::RoomData::uiRankLevel = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("uiRankLevel"));
    Class::RoomData::iMythPoint = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("iMythPoint"));
    Class::RoomData::iCertify = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("iCertify"));
    Class::RoomData::heroid = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("heroid"));
    Class::RoomData::summonSkillId = (uintptr_t) RoomData->Il2CppGetField(OBFUSCATE("summonSkillId"));
    
    auto SystemData = new FangEngine(OBFUSCATE(""), OBFUSCATE("SystemData"));
    Class::SystemData::m_uiID = (uintptr_t) SystemData->Il2CppGetField(OBFUSCATE("m_uiID"));
    Class::SystemData::IsVpn = (uintptr_t) SystemData->Il2CppGetField(OBFUSCATE("IsVpn"));
    Class::SystemData::m_reportRate = (uintptr_t) SystemData->Il2CppGetField(OBFUSCATE("m_reportRate"));
    Class::SystemData::GetBattlePlayerInfo = (uintptr_t) SystemData->Il2CppGetMethod(OBFUSCATE("GetBattlePlayerInfo"), 0);
    Class::SystemData::GetHeroSkin = (uintptr_t) SystemData->Il2CppGetMethod(OBFUSCATE("GetHeroSkin"), 2);
    Class::SystemData::IsHaveSkin = (uintptr_t) SystemData->Il2CppGetMethod(OBFUSCATE("IsHaveSkin"), 1);
    Class::SystemData::IsHaveSkinForever = (uintptr_t) SystemData->Il2CppGetMethod(OBFUSCATE("IsHaveSkinForever"), 1);
    Class::SystemData::IsForbidSkin = (uintptr_t) SystemData->Il2CppGetMethod(OBFUSCATE("IsForbidSkin"), 1);
    Class::SystemData::IsForbidARSkin = (uintptr_t) SystemData->Il2CppGetMethod(OBFUSCATE("IsForbidARSkin"), 1);
    
    auto BattleData = new FangEngine(OBFUSCATE(""), OBFUSCATE("BattleData"));
    Class::BattleData::battleManager = (uintptr_t) BattleData->Il2CppGetField(OBFUSCATE("battleManager"));
    Class::BattleData::m_BattleBridge = (uintptr_t) BattleData->Il2CppGetField(OBFUSCATE("m_BattleBridge"));
    
    auto GameMain = new FangEngine(OBFUSCATE(""), OBFUSCATE("GameMain"));
    Class::GameMain::Instance = (uintptr_t) GameMain->Il2CppGetField(OBFUSCATE("Instance"));
    Class::GameMain::_bGameInitDone = (uintptr_t) GameMain->Il2CppGetField(OBFUSCATE("_bGameInitDone"));
    Class::GameMain::PlugInTesting = (uintptr_t) GameMain->Il2CppGetMethod(OBFUSCATE("PlugInTesting"), 0);
    
    auto UIRankHeroChangeShow = new FangEngine(OBFUSCATE(""), OBFUSCATE("UIRankHero/ChangeShow"));
    Class::UIRankHeroChangeShow::iSelfHero = (uintptr_t) UIRankHeroChangeShow->Il2CppGetField(OBFUSCATE("iSelfHero"));
    Class::UIRankHeroChangeShow::SendUseSkin = (uintptr_t) UIRankHeroChangeShow->Il2CppGetMethod(OBFUSCATE("SendUseSkin"), 2);
    
    auto UIChooseHero = new FangEngine(OBFUSCATE(""), OBFUSCATE("UIChooseHero"));
    Class::UIChooseHero::BatttleSelectSkin = (uintptr_t) UIChooseHero->Il2CppGetMethod(OBFUSCATE("BatttleSelectSkin"), 2);
    
    auto UIRankHero = new FangEngine(OBFUSCATE(""), OBFUSCATE("UIRankHero"));
    Class::UIRankHero::BatttleSelectSkin = (uintptr_t) UIRankHero->Il2CppGetMethod(OBFUSCATE("BatttleSelectSkin"), 2);
    
    auto ChooseHeroMgr = new FangEngine(OBFUSCATE(""), OBFUSCATE("ChooseHeroMgr"));
    Class::ChooseHeroMgr::SendSelectSkin = (uintptr_t) ChooseHeroMgr->Il2CppGetMethod(OBFUSCATE("SendSelectSkin"), 2);
    
    auto BattleReceiveMessage = new FangEngine(OBFUSCATE(""), OBFUSCATE("BattleReceiveMessage"));
    Class::BattleReceiveMessage::SetPlayerData = (uintptr_t) BattleReceiveMessage->Il2CppGetMethod(OBFUSCATE("SetPlayerData"), 2);
    Class::BattleReceiveMessage::SetPlayerData_ = (uintptr_t) BattleReceiveMessage->Il2CppGetMethod(OBFUSCATE("SetPlayerData"), 1);
    Class::BattleReceiveMessage::AddPlayerInfo = (uintptr_t) BattleReceiveMessage->Il2CppGetMethod(OBFUSCATE("AddPlayerInfo"), 4);
    Class::BattleReceiveMessage::AddPlayerInfo_ = (uintptr_t) BattleReceiveMessage->Il2CppGetMethod(OBFUSCATE("AddPlayerInfo"), 2);
    
    auto BattlePlayerInfo = new FangEngine(OBFUSCATE("MTTDProto"), OBFUSCATE("BattlePlayerInfo"));
    Class::BattlePlayerInfo::lUid = (uintptr_t) BattlePlayerInfo->Il2CppGetField(OBFUSCATE("lUid"));
    Class::BattlePlayerInfo::uiSelHero = (uintptr_t) BattlePlayerInfo->Il2CppGetField(OBFUSCATE("uiSelHero"));
    Class::BattlePlayerInfo::uiSkinId = (uintptr_t) BattlePlayerInfo->Il2CppGetField(OBFUSCATE("uiSkinId"));
    Class::BattlePlayerInfo::uiRankLevel = (uintptr_t) BattlePlayerInfo->Il2CppGetField(OBFUSCATE("uiRankLevel"));
    Class::BattlePlayerInfo::bBanChat = (uintptr_t) BattlePlayerInfo->Il2CppGetField(OBFUSCATE("bBanChat"));
    Class::BattlePlayerInfo::uiRoleLevel = (uintptr_t) BattlePlayerInfo->Il2CppGetField(OBFUSCATE("uiRoleLevel"));

    auto ShowSelfPlayer = new FangEngine(OBFUSCATE(""), OBFUSCATE("ShowSelfPlayer"));
    Class::ShowSelfPlayer::TryUseSkill = (uintptr_t) ShowSelfPlayer->Il2CppGetMethod(OBFUSCATE("TryUseSkill"), 9);
    Class::ShowSelfPlayer::OnUpdate = (uintptr_t) ShowSelfPlayer->Il2CppGetMethod(OBFUSCATE("OnUpdate"), 0);

    auto LogicPlayer = new FangEngine(OBFUSCATE("Battle"), OBFUSCATE("LogicPlayer"));
    Class::LogicPlayer::_KillWildTimes = (uintptr_t) LogicPlayer->Il2CppGetField(OBFUSCATE("_KillWildTimes"));
    Class::LogicPlayer::m_PlayerData = (uintptr_t) LogicPlayer->Il2CppGetField(OBFUSCATE("m_PlayerData"));

    auto PlayerData = new FangEngine(OBFUSCATE(""), OBFUSCATE("PlayerData"));
    Class::PlayerData::_killNum = (uintptr_t) PlayerData->Il2CppGetField(OBFUSCATE("_killNum"));
    Class::PlayerData::_assistNum = (uintptr_t) PlayerData->Il2CppGetField(OBFUSCATE("_assistNum"));

    auto ClientLogReportSwitch = new FangEngine(OBFUSCATE("MTTDProto"), OBFUSCATE("ClientLogReportSwitch"));
    Class::ClientLogReportSwitch::iReportPercentage = (uintptr_t) PlayerData->Il2CppGetField(OBFUSCATE("iReportPercentage"));

    auto APKSignature = new FangEngine(OBFUSCATE(""), OBFUSCATE("APKSignature"));
    Class::APKSignature::IsSignatureSame = (uintptr_t) APKSignature->Il2CppGetMethod(OBFUSCATE("IsSignatureSame"), 1);
    Class::APKSignature::SetAPKSignature = (uintptr_t) APKSignature->Il2CppGetMethod(OBFUSCATE("SetAPKSignature"), 1);
}

