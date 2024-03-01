//
// Created by FangCybertron
//
#pragma once

bool UnlockSkin = false;
bool ForbidSkin = false;

namespace MTTDProto {
    int HeroID = 0;
    int SkinID = 0;
    int m_Uid = 0;
};

struct CmdHeroSkin : Il2CppObject {
    int iId = 0;
    int iLimitTime = 0;
    int iSource = 0;
    int iGetTime = 0;
};
/*

CmdHeroSkin *AttributeSkin() {
    auto ClassCmdHeroSkin = new FangEngine(OBFUSCATE("MTTDProto"), OBFUSCATE("CmdHeroSkin"));
    auto ClassInstance = (CmdHeroSkin *)ClassCmdHeroSkin->Il2CppCreateClassInstance();
    auto Constructors = (void *(*)(CmdHeroSkin *))(ClassCmdHeroSkin->Il2CppGetMethod(OBFUSCATE(".ctor"), 0));
    if (Constructors(ClassInstance)) {
        ClassInstance->iId = 0;
        ClassInstance->iLimitTime = 0;
        ClassInstance->iSource = 0;
        ClassInstance->iGetTime = 0;
    }
    return ClassInstance;
}

bool (*Orig_SystemDataIsForbidSkin)(uint32_t skinid);
bool SystemDataIsForbidSkin(uint32_t skinid) {
    if (ForbidSkin) {
        return Orig_SystemDataIsForbidSkin(0);
    }
    return Orig_SystemDataIsForbidSkin(skinid);
}

bool (*Orig_SystemDataIsForbidARSkin)(uint32_t id);
bool SystemDataIsForbidARSkin(uint32_t id) {
    if (ForbidSkin) {
        return Orig_SystemDataIsForbidARSkin(0);
    }
    return Orig_SystemDataIsForbidARSkin(id);
}

CmdHeroSkin *(*Orig_SystemDataGetHeroSkin)(void *thiz, uintptr_t m_heroskins, uint skinid);
CmdHeroSkin *SystemDataGetHeroSkin(void *thiz, uintptr_t m_heroskins, uint skinid) {
    if (UnlockSkin) {
        return AttributeSkin();
    }
    return Orig_SystemDataGetHeroSkin(thiz, m_heroskins, skinid);
}

CmdHeroSkin *(*Orig_SystemDataIsHaveSkin)(void *thiz, int skinid);
CmdHeroSkin *SystemDataIsHaveSkin(void *thiz, int skinid) {
    if (UnlockSkin) {
        return AttributeSkin();
    }
    return Orig_SystemDataIsHaveSkin(thiz, skinid);
}

CmdHeroSkin *(*Orig_SystemDataIsHaveSkinForever)(void *thiz, int skinid);
CmdHeroSkin *SystemDataIsHaveSkinForever(void *thiz, int skinid) {
    if (UnlockSkin) {
        return AttributeSkin();
    }
    return Orig_SystemDataIsHaveSkinForever(thiz, skinid);
}

void (*Orig_UIChooseHeroBatttleSelectSkin)(void *thiz, uint64_t uid, uint skinid);
void UIChooseHeroBatttleSelectSkin(void *thiz, uint64_t uid, uint skinid) {
    if (UnlockSkin) {
        return Orig_UIChooseHeroBatttleSelectSkin(thiz, SystemData::m_uiID(), MTTDProto::SkinID);
    }
    return Orig_UIChooseHeroBatttleSelectSkin(thiz, uid, skinid);
}

void (*Orig_UIRankHeroBatttleSelectSkin)(void *thiz, uint64_t uid, uint skinid);
void UIRankHeroBatttleSelectSkin(void *thiz, uint64_t uid, uint skinid) {
    if (UnlockSkin) {
        return Orig_UIRankHeroBatttleSelectSkin(thiz, SystemData::m_uiID(), MTTDProto::SkinID);
    }
    return Orig_UIRankHeroBatttleSelectSkin(thiz, uid, skinid);
}

void (*Orig_ChooseHeroMgrSendSelectSkin)(void *thiz, uint32_t skinid, uint32_t heroid);
void ChooseHeroMgrSendSelectSkin(void *thiz, uint32_t skinid, uint32_t heroid) {
    if (UnlockSkin) {
        if (!Orig_SystemDataIsHaveSkin(0, skinid) || !Orig_SystemDataIsHaveSkinForever(0, skinid)) {
            MTTDProto::SkinID = skinid;
            MTTDProto::HeroID = heroid;
        }
        return Orig_ChooseHeroMgrSendSelectSkin(thiz, 0, 0);
    }
    return Orig_ChooseHeroMgrSendSelectSkin(thiz, skinid, heroid);
}

void (*Orig_UIRankHeroChangeShowSendUseSkin)(void *thiz, uint32_t skinid, bool bForce);
void UIRankHeroChangeShowSendUseSkin(void *thiz, uint32_t skinid, bool bForce) {
    uint32_t iSelfHero = *(uint32_t *)((uintptr_t)thiz + Class::UIRankHeroChangeShow::iSelfHero);
    if (UnlockSkin) {
        if (!Orig_SystemDataIsHaveSkin(0, skinid) || !Orig_SystemDataIsHaveSkinForever(0, skinid)) {
            MTTDProto::SkinID = skinid;
            MTTDProto::HeroID = iSelfHero;
        }
        return Orig_UIRankHeroChangeShowSendUseSkin(thiz, 0, false);
    }
    return Orig_UIRankHeroChangeShowSendUseSkin(thiz, skinid, bForce);
}
*/
void (*Orig_BattleReceiveMessageSetPlayerData)(void *thiz, uintptr_t playerinfo);
void BattleReceiveMessageSetPlayerData(void *thiz, uintptr_t playerinfo) {
    uint64_t m_uiID = *(uint64_t *)Class::SystemData::m_uiID;
    if(*(uint64_t *) (playerinfo + Class::BattlePlayerInfo::lUid) == m_uiID){
        if (ForbidSkin) {
            //role level
            int uiRoleLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel);
            if (uiRoleLevel < 30 && uiRoleLevel > 1) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel) = 30;
            }

            //bypass chat banned
            bool bBanChat = *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat);
            if (bBanChat) {
                *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat) = false;
            }

            //fakerank
            int uiRankLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel);
            if (uiRankLevel < 136) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 135;
            }

            if (uiRankLevel > 136){
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 136+99;
            };
        }
    }
    return Orig_BattleReceiveMessageSetPlayerData(thiz, playerinfo);
}

void (*Orig_BattleReceiveMessageSetPlayerData_)(void *thiz, uintptr_t playerinfo, uint32_t uiSelfCamp);
void BattleReceiveMessageSetPlayerData_(void *thiz, uintptr_t playerinfo, uint32_t uiSelfCamp) {
    uint64_t m_uiID = *(uint64_t *)Class::SystemData::m_uiID;
    if(*(uint64_t *) (playerinfo + Class::BattlePlayerInfo::lUid) == m_uiID){
        if (ForbidSkin) {
            //role level
            int uiRoleLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel);
            if (uiRoleLevel < 30 && uiRoleLevel > 1) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel) = 30;
            }

            //bypass chat banned
            bool bBanChat = *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat);
            if (bBanChat) {
                *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat) = false;
            }

            //fakerank
            int uiRankLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel);
            if (uiRankLevel < 136) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 135;
            }

            if (uiRankLevel > 136){
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 136+99;
            };
        }
    }
    return Orig_BattleReceiveMessageSetPlayerData_(thiz, playerinfo, uiSelfCamp);
}

//5 param
void (*Orig_AddPlayerInfo)(void *thiz, uintptr_t playerinfo, uint selfCamp, uintptr_t roomdata, bool ignoreEmblem);
void AddPlayerInfo(void *thiz, uintptr_t playerinfo, uint selfCamp, uintptr_t roomdata, bool ignoreEmblem){
    uint64_t m_uiID = *(uint64_t *)Class::SystemData::m_uiID;
    if(*(uint64_t *) (playerinfo + Class::BattlePlayerInfo::lUid) == m_uiID){
        if (ForbidSkin) {
            //role level
            int uiRoleLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel);
            if (uiRoleLevel < 30 && uiRoleLevel > 1) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel) = 30;
            }

            //bypass chat banned
            bool bBanChat = *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat);
            if (bBanChat) {
                *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat) = false;
            }

            //fakerank
            int uiRankLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel);
            if (uiRankLevel < 136) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 135;
            }

            if (uiRankLevel > 136){
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 136+99;
            };
        }
    }
    return Orig_AddPlayerInfo(thiz, playerinfo, selfCamp, roomdata, ignoreEmblem);
}
//3param
void (*Orig_AddPlayerInfo_)(void *thiz, uintptr_t playerinfo, uintptr_t roomdata);
void AddPlayerInfo_(void *thiz, uintptr_t playerinfo, uintptr_t roomdata){
    uint64_t m_uiID = *(uint64_t *)Class::SystemData::m_uiID;
    if(*(uint64_t *) (playerinfo + Class::BattlePlayerInfo::lUid) == m_uiID){
        if (ForbidSkin) {
            //role level
            int uiRoleLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel);
            if (uiRoleLevel < 30 && uiRoleLevel > 1) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRoleLevel) = 30;
            }

            //bypass chat banned
            bool bBanChat = *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat);
            if (bBanChat) {
                *(bool *)(playerinfo + Class::BattlePlayerInfo::bBanChat) = false;
            }

            //fakerank
            int uiRankLevel = *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel);
            if (uiRankLevel < 136) {
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 135;
            }

            if (uiRankLevel > 136){
                *(int *)(playerinfo + Class::BattlePlayerInfo::uiRankLevel) = 136+99;
            };
        }
    }
    return Orig_AddPlayerInfo_(thiz, playerinfo, roomdata);
}

