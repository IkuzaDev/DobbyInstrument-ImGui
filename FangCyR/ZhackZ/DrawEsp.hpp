//
// Created by FangCybertron
//
#pragma once

#include "FangCyR/ZhackZ/ToString.hpp"
#include "FangCyR/ZhackZ/StructSdk.hpp"
#include "FangCyR/ZhackZ/UnlockSkin.hpp"

const char ascii_hex_4bit[23] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};
static bool InitializeNick;
static inline char to_upper(char c)
{
    if ((c >= 'a') && (c <= 'z')) return c ^ 0x20;
    return c;
}

char * urldecode(const char * str)
{
    size_t i, j, len = strlen(str);
    char c, d, url_hex;
    char * decoded = (char*)malloc(len + 1);
    if (decoded == NULL) return NULL;
    i = 0;
    j = 0;
    do {
        c = str[i];
        d = 0;
        if (c == '%') {
            url_hex = to_upper(str[++i]);
            if (((url_hex >= '0') && (url_hex <= '9')) || ((url_hex >= 'A') && (url_hex <= 'F'))) {
                d = ascii_hex_4bit[url_hex - 48] << 4;

                url_hex = to_upper(str[++i]);
                if (((url_hex >= '0') && (url_hex <= '9')) || ((url_hex >= 'A') && (url_hex <= 'F'))) {
                    d |= ascii_hex_4bit[url_hex - 48];
                } else {
                    d = 0;
                }
            }
        }
        else if (c == '+') {
            d = ' ';
        }
        else if ((c == '*') || (c == '-') || (c == '.') || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || (c == '_')  || ((c >= 'a') && (c <= 'z'))) {
            d = c;
        }
        decoded[j++] = d;
        ++i;
    } while ((i < len) && (d != 0));

    decoded[j] = 0;
    return decoded;
}

std::string GetNickName(std::string UserId, std::string ZoneId)
{
    std::string Result = "Connecting...";
    struct MemoryStruct chunk {};
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;

    CURL * curl = curl_easy_init();
    if (curl != NULL) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://order-sg.codashop.com/initPayment.action");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        struct curl_slist * headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Origin: https://www.codashop.com");
        headers = curl_slist_append(headers, "Referer: https://www.codashop.com/");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Mobile Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string PostData = "{\"voucherPricePoint.id\": \"27670\", \"voucherPricePoint.price\": \"242535.0\", \"voucherPricePoint.variablePrice\": \"0\", \"n\": \"12/7/2022-2046\", \"email\": \"\", \"userVariablePrice\": \"0\", \"order.data.profile\": \"eyJuYW1lIjoiICIsImRhdGVvZmJpcnRoIjoiIiwiaWRfbm8iOiIifQ==\", \"user.userId\": \"" + UserId + "\", \"user.zoneId\": \"" + ZoneId + "\", \"msisdn\": \"\", \"voucherTypeName\": \"MOBILE_LEGENDS\", \"shopLang\": \"id_ID\", \"voucherTypeId\": \"5\", \"gvtId\": \"19\", \"checkoutId\": \"\", \"affiliateTrackingId\": \"\", \"impactClickId\": \"\", \"anonymousId\": \"\"}";

        curl_easy_setopt(curl, CURLOPT_POST, true);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json Response = json::parse(chunk.memory);
                if (Response["success"]) {
                    std::string Encrypt = Response["confirmationFields"]["username"].get<std::string>();
                    Result = urldecode(Encrypt.c_str());
                }else{
                    Result = "Failed";
                }
            } catch (json::exception & e) {
            }
        }
    }
    curl_easy_cleanup(curl);

    return Result;
}

const char * TextFormatv1(const char * Str, ...)
{
    char buf[10000] = { 0 };
    va_list arg;
    va_start(arg, Str);
    vsprintf(buf, Str, arg);
    va_end(arg);
    return buf;
}

bool GetGIDRegister(int UserID, bool success){
    bool result;
    struct MemoryStruct chunk {};
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;

    CURL * curl = curl_easy_init();
    if (curl != NULL) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://order-sg.codashop.com/initPayment.action");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        struct curl_slist * headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Origin: https://www.codashop.com");
        headers = curl_slist_append(headers, "Referer: https://www.codashop.com/");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Mobile Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string PostData = "{\"userId\": \"" + std::string(TextFormatv1("%d",UserID)) + "\", \"GAME\": \"MOBILE_LEGENDS\", \"Type\": \"userID\"}";

        curl_easy_setopt(curl, CURLOPT_POST, true);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json Response = json::parse(chunk.memory);
                result = Response["status"];
                if (Response["status"]) {
                    success = true;
                }else{
                    success = false;
                }
            } catch (json::exception & e) {
            }
        }
    }
    curl_easy_cleanup(curl);

    return result;
}

std::string Nick[10];

void * DoThreadGetNickName(void*)
{
    auto GetBattlePlayerInfo = SystemData::GetBattlePlayerInfo();
    if (!GetBattlePlayerInfo) nullptr;
    for (int i = 0; i < GetBattlePlayerInfo->getSize(); i++) {
        auto roomData = GetBattlePlayerInfo->getItems()[i];
        if (roomData != NULL) {
            auto iCamp = roomData->iCamp();
            auto lUid = roomData->lUid();
            auto uiZoneId = roomData->uiZoneId();
            if(lUid < 9999){
                if(uiZoneId < 999){
                    Nick[i] = "Server Bot";
                }
            }else{
                Nick[i] = GetNickName(TextFormatv1("%d", lUid), TextFormatv1("%d", uiZoneId));
            }
        }
    }
    pthread_exit(nullptr);
    return nullptr;
}

Vector2 WorldToMinimap(float angle, Vector3 HeroPosition) {
    float angleCos = (float)std::cos(angle);
    float angleSin = (float)std::sin(angle);
    Vector2 Res0;
    Res0.X = (angleCos * HeroPosition.X - angleSin * (HeroPosition.Z * -1)) / 72.0f;
    Res0.Y = (angleSin * HeroPosition.X + angleCos * (HeroPosition.Z * -1)) / 72.0f;
    Vector2 Res1;
    Res1.X = (Res0.X * ESP::MinimapSize) + ESP::MinimapPos + ESP::MinimapSize / 2.f;
    Res1.Y = (Res0.Y * ESP::MinimapSize) + ESP::MinimapSize / 2.f;
    return Res1;
}

void ViewCamera(float value) {
    static float GetFieldOfView = 0.0f;
    if (GetFieldOfView == 0.0f) {
        GetFieldOfView = Camera::get_main()->get_fieldOfView();
    }
    if (GetFieldOfView != 0.0f) {
        if (value > 0.0f) {
            Camera::get_main()->set_fieldOfView((float)GetFieldOfView + value);
        }
        if (value == 0.0f) {
            Camera::get_main()->set_fieldOfView((float)GetFieldOfView);
        }
    }
}

void ImGuiDrawEsp() {
    if (!CONFIG::LoginValid) {
        return;
    }
    auto Scaling = ImGui::GetIO().FontGlobalScale;
    auto GameMainInstance = GameMain::Instance();
    if (GameMainInstance) {
        auto _bGameInitDone = GameMainInstance->_bGameInitDone();
        if (_bGameInitDone) {
            //ROOM INFO
            auto LogicBattleManagerInstance = LogicBattleManager::Instance();
            if (LogicBattleManagerInstance) {
                auto _m_eState = LogicBattleManagerInstance->_m_eState();
                if (_m_eState != WaitConnect) {
                    InfoRoom.Active = true;
                    if(InfoRoom.Active){
                        if(_m_eState == SelectHero || _m_eState == WaitReady){
                            if (InitializeNick == false) {
                                pthread_t thread;
                                pthread_create(&thread, NULL, DoThreadGetNickName, NULL);
                                InitializeNick = true;
                            }
                        }
                        if (_m_eState == WaitEnd || _m_eState == End) {
                            for (int i = 0; i < 10; i++) Nick[i] = "Clearing...";
                        }
                    }
                } else {
                    InfoRoom.Active = false;
                    InitializeNick = false;
                }

                auto GetBattlePlayerInfo = SystemData::GetBattlePlayerInfo();
                if (GetBattlePlayerInfo) {
                    int Team = 0, Enemy = 0;
                    for (int i = 0; i < GetBattlePlayerInfo->getSize(); i++) {
                        auto PlayerInfo = GetBattlePlayerInfo->getItems()[i];
                        if (PlayerInfo) {
                            auto iCamp = PlayerInfo->iCamp();
                            auto lUid = PlayerInfo->lUid();
                            if (lUid != SystemData::m_uiID()) {
                                InfoRoom.SelfCamp = iCamp;
                                break;
                            }
                        }
                    }
                    for (int i = 0; i < GetBattlePlayerInfo->getSize(); i++) {
                        auto PlayerInfo = GetBattlePlayerInfo->getItems()[i];
                        if (PlayerInfo) {
                            auto iCamp = PlayerInfo->iCamp();
                            auto iPos = PlayerInfo->iPos();
                            auto _sName = PlayerInfo->_sName();
                            auto lUid = PlayerInfo->lUid();
                            auto uiZoneId = PlayerInfo->uiZoneId();
                            auto uiRankLevel = PlayerInfo->uiRankLevel();
                            auto iMythPoint = PlayerInfo->iMythPoint();
                            auto iCertify = PlayerInfo->iCertify();
                            auto heroid = PlayerInfo->heroid();
                            auto summonSkillId = PlayerInfo->summonSkillId();
                            auto splitRank = SplitRankAndStars(uiRankLevel, iMythPoint);
                            std::string rankName = std::get<0>(splitRank);
                            std::string starCount = std::get<1>(splitRank);
                            std::string UserID = std::to_string(lUid) + std::string(OBFUSCATE(" ")) + std::string(OBFUSCATE("(")) + std::to_string(uiZoneId) + std::string(OBFUSCATE(")"));
                            if(InfoRoom.SelfCamp != -1){
                                if (iCamp == InfoRoom.SelfCamp) {
                                    //InfoRoom.bTeam = true;
                                    InfoRoom.Team[Team].bTeam = iCamp == InfoRoom.SelfCamp;
                                    InfoRoom.Team[Team].bEnemy = false;
                                    InfoRoom.Team[Team].Name = Nick[i].c_str();
                                    InfoRoom.Team[Team].UserID = UserID;
                                    InfoRoom.Team[Team].Verified = VerifiedToString(iCertify);
                                    InfoRoom.Team[Team].Rank = rankName;
                                    InfoRoom.Team[Team].Point = starCount;
                                    InfoRoom.Team[Team].HeroID = heroid;
                                    InfoRoom.Team[Team].SpellID = summonSkillId;
                                    Team++;
                                }else{
                                    InfoRoom.Enemy[Enemy].bEnemy = iCamp != InfoRoom.SelfCamp;
                                    InfoRoom.Enemy[Enemy].bTeam = false;
                                    InfoRoom.Enemy[Enemy].Name = Nick[i].c_str();
                                    InfoRoom.Enemy[Enemy].UserID = UserID;
                                    InfoRoom.Enemy[Enemy].Verified = VerifiedToString(iCertify);
                                    InfoRoom.Enemy[Enemy].Rank = rankName;
                                    InfoRoom.Enemy[Enemy].Point = starCount;
                                    InfoRoom.Enemy[Enemy].HeroID = heroid;
                                    InfoRoom.Enemy[Enemy].SpellID = summonSkillId;
                                    Enemy++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void DrawEsp() {
    ImDrawList *m_ImGui = ImGui::GetForegroundDrawList();
    if (!CONFIG::LoginValid) {
        return;
    }
    if (!m_ImGui) {
        return;
    }
    auto Scaling = ImGui::GetIO().FontGlobalScale;
    auto GameMainInstance = GameMain::Instance();
    if (GameMainInstance) {
        auto _bGameInitDone = GameMainInstance->_bGameInitDone();
        if (_bGameInitDone) {
            auto BattleDataBattleBridge = BattleData::m_BattleBridge();
            if (BattleDataBattleBridge) {
                auto bStartBattle = BattleDataBattleBridge->bStartBattle();
                if (bStartBattle) {
                    ViewCamera(OTHERS::SetFieldOfView);
                    auto BattleDataBattleManager = BattleData::battleManager();
                    if (BattleDataBattleManager) {
                        auto m_LocalPlayerShow = BattleDataBattleManager->m_LocalPlayerShow();
                        Vector2 LocalSC = {0,0};
                        if (m_LocalPlayerShow) {
                            if (OTHERS::MinimapSetting) {
                                m_ImGui->AddRectFilled(ImVec2(ESP::MinimapPos, 0), ImVec2(ESP::MinimapPos + ESP::MinimapSize, ESP::MinimapSize), IM_COL32(0, 255, 0, 155), 0);
                            }
                            auto LocalTF = m_LocalPlayerShow->_Position();
                            if (LocalTF != Vector3::Zero()) {
                                auto WorldToScreen = Camera::get_main()->WorldToScreenPoint(LocalTF);
                                LocalSC = {ImGui::GetIO().DisplaySize.x - WorldToScreen.X, WorldToScreen.Y};
                                if (WorldToScreen.Z > 0) {
                                    LocalSC = {WorldToScreen.X, ImGui::GetIO().DisplaySize.y - WorldToScreen.Y};
                                }
                            }
                        }
                        auto m_dicPlayerShow = BattleDataBattleManager->m_dicPlayerShow();
                        if (m_dicPlayerShow) {
                            for (int i = 0; i < m_dicPlayerShow->getSize(); i++) {
                                auto Keys = m_dicPlayerShow->getKeys()[i];
                                auto PlayerShow = m_dicPlayerShow->getValues()[i];
                                if (Keys && PlayerShow) {
                                    auto m_bInitComplete = PlayerShow->m_bInitComplete();
                                    if (m_bInitComplete) {
                                        auto m_bSameCampType = PlayerShow->m_bSameCampType();
                                        auto m_bDeath = PlayerShow->m_bDeath();
                                        auto m_bShowLayer = PlayerShow->m_bShowLayer();
                                        if (!m_bSameCampType && !m_bDeath) {
                                            auto m_ID = PlayerShow->m_ID();
                                            auto m_Hp = PlayerShow->m_Hp();
                                            auto m_HpMax = PlayerShow->m_HpMax();
                                            auto EntityRootTF = PlayerShow->_Position();
                                            auto WorldToScreen = Camera::get_main()->WorldToScreenPoint(EntityRootTF);
                                            auto EntityRootSC = Vector2(ImGui::GetIO().DisplaySize.x - WorldToScreen.X, WorldToScreen.Y);
                                            if (WorldToScreen.Z > 0) {
                                                EntityRootSC = Vector2(WorldToScreen.X, ImGui::GetIO().DisplaySize.y - WorldToScreen.Y);
                                            }

                                            if (ESP::ShowSkillCD || ESP::ShowSpellCD) {
                                                char CooldownString[10];
                                                auto PosCooldown = EntityRootSC + Vector2(Scaling * 50, 0);
                                                auto GetFighterLogic = LogicBattleManager::Instance()->GetFighterLogic(Keys);
                                                auto m_SkillComp = GetFighterLogic->m_SkillComp();
                                                auto m_OwnSkillComp = PlayerShow->m_OwnSkillComp();
                                                auto m_SkillList = m_OwnSkillComp->m_SkillList();
                                                if (m_SkillList) {
                                                    for (int i = 0; i < m_SkillList->getSize(); i++) {
                                                        auto m_SkillListItems = m_SkillList->getItems()[i];
                                                        if (m_SkillListItems) {
                                                            auto m_InitSkillID = m_SkillListItems->m_InitSkillID();
                                                            if (ESP::ShowSkillCD) {
                                                                auto GetSkillUseType = PlayerShow->GetSkillUseType(m_InitSkillID);
                                                                if (GetSkillUseType == NormalUse) {
                                                                    auto m_CoolDownComp = m_SkillComp->m_CoolDownComp();
                                                                    if (!m_CoolDownComp->IsCoolDownForShowRealId(m_InitSkillID)) {
                                                                        sprintf(CooldownString, OBFUSCATE("%.f"), (float)(m_SkillComp->GetSkillMaxCDDown(m_InitSkillID)->GetCoolTime() / 1000) + 1.f);
                                                                        auto CalcTextSize = ImGui::CalcTextSize(CooldownString, 0, 20.0f);
                                                                        m_ImGui->AddText(ImGui::GetFont(), Scaling * 20.0f, ImVec2(PosCooldown.X - (CalcTextSize.x / 2), PosCooldown.Y - Scaling * 23.5f), IM_COL32(255, 255, 255, 255), CooldownString);
                                                                        PosCooldown += Vector2(Scaling * 40, 0);
                                                                    } else {
                                                                        m_ImGui->AddCircleFilled(ImVec2(PosCooldown.X, PosCooldown.Y - Scaling * 14.0f), Scaling * 8.0f, IM_COL32(255, 255, 0, 255), 0);
                                                                        PosCooldown += Vector2(Scaling * 40, 0);
                                                                    }
                                                                }
                                                            }
                                                            if (ESP::ShowSpellCD) {
                                                                auto SummonSkillId = PlayerShow->m_iSummonSkillId();
                                                                if (m_InitSkillID == SummonSkillId) {
                                                                    auto m_CoolDownComp = m_SkillComp->m_CoolDownComp();
                                                                    if (!m_CoolDownComp->IsCoolDownForShowRealId(m_InitSkillID)) {
                                                                        sprintf(CooldownString, OBFUSCATE("%.f"), (float)(m_SkillComp->GetSkillMaxCDDown(m_InitSkillID)->GetCoolTime() / 1000) + 1.f);
                                                                        auto CalcTextSize = ImGui::CalcTextSize(CooldownString, 0, 20.0f);
                                                                        m_ImGui->AddText(ImGui::GetFont(), Scaling * 20.0f, ImVec2(PosCooldown.X - (CalcTextSize.x / 2), PosCooldown.Y - Scaling * 23.5f), IM_COL32(255, 255, 255, 255), CooldownString);
                                                                        PosCooldown += Vector2(Scaling * 40, 0);
                                                                    } else {
                                                                        m_ImGui->AddCircleFilled(ImVec2(PosCooldown.X, PosCooldown.Y - Scaling * 14.0f), Scaling * 8.0f, IM_COL32(30, 144, 255, 255), 0);
                                                                        PosCooldown += Vector2(Scaling * 40, 0);
                                                                    }
                                                                }
                                                            }

                                                        }
                                                    }
                                                }
                                                m_ImGui->AddLine(ImVec2(EntityRootSC.X, EntityRootSC.Y), ImVec2(PosCooldown.X - Scaling * 12.0f, PosCooldown.Y), IM_COL32(255, 255, 255, 255));
                                            }
                                            if (ESP::PlayerRound) {
                                                m_ImGui->AddCircleFilled(ImVec2(EntityRootSC.X, EntityRootSC.Y), Scaling * 6.0f, IM_COL32(255, 255, 255, 255), 0);
                                            }
                                            if (m_bShowLayer) {
                                                continue;
                                            }
                                            if (ESP::PlayerLine) {
                                                if (!m_LocalPlayerShow->m_bDeath()) {
                                                    m_ImGui->AddLine(ImVec2(LocalSC.X, LocalSC.Y), ImVec2(EntityRootSC.X, EntityRootSC.Y), IM_COL32(230, 230, 250, 255));
                                                }
                                            }
                                            if (ESP::PlayerHealth) {
                                                auto LineHealthStart = ImVec2(EntityRootSC.X + Scaling * 40, EntityRootSC.Y - Scaling * 30);
                                                auto LineHealthEnd = ImVec2(LineHealthStart.x + Scaling * 160, LineHealthStart.y);
                                                auto HealthStart = ImVec2(LineHealthStart.x, LineHealthStart.y - Scaling * 20);
                                                auto HealthEnd = ImVec2(LineHealthEnd.x, LineHealthEnd.y - Scaling * 5);
                                                auto HealthWidth = abs(HealthEnd.x - HealthStart.x);
                                                auto PercentHP = ((float)m_Hp * HealthWidth) / (float)m_HpMax;
                                                m_ImGui->AddLine(ImVec2(EntityRootSC.X, EntityRootSC.Y), LineHealthStart, IM_COL32(255, 255, 255, 255));
                                                m_ImGui->AddLine(LineHealthStart, LineHealthEnd, IM_COL32(255, 255, 255, 155));
                                                m_ImGui->AddRectFilled(HealthStart, HealthEnd, ImColor(0.22f, 0.22f, 0.22f, 1.00f), 10);
                                                m_ImGui->AddRectFilled(HealthStart, ImVec2(HealthStart.x + PercentHP, HealthEnd.y), IM_COL32(225, 0, 0, 255), 10);
                                                m_ImGui->AddRect(HealthStart, HealthEnd, IM_COL32(0, 0, 0, 255), 10);
                                            }
                                            if (ESP::HeroLevel || ESP::HeroName) {
                                                float Thiz = 5.0f;
                                                std::string str;
                                                auto m_Level = PlayerShow->m_Level();
                                                auto m_HeroName = PlayerShow->m_HeroName();
                                                if (ESP::HeroLevel) {
                                                    str += std::string(OBFUSCATE(" [")) + std::to_string(m_Level) + std::string(OBFUSCATE("] "));
                                                }
                                                if (ESP::HeroName) {
                                                    if (m_HeroName) {
                                                        str += Utf16ToUtf8(m_HeroName->chars);
                                                    }
                                                }
                                                if (ESP::PlayerAvatar) {
                                                    Thiz = 35.0f;
                                                }
                                                m_ImGui->AddText(ImGui::GetFont(), Scaling * 22.0f, ImVec2(EntityRootSC.X + Thiz, EntityRootSC.Y + Scaling * 5), IM_COL32(255, 255, 0, 255), str.c_str());
                                            }
                                            if (ESP::ShowMinimap) {
                                                float angle = (PlayerShow->m_EntityCampType() == CampTypeB ? 315.0f : 134.76f) * 0.017453292519943295;
                                                auto mapPos = WorldToMinimap(angle, EntityRootTF);
                                                m_ImGui->AddCircleFilled(ImVec2(mapPos.X, mapPos.Y), Scaling * 4.5f + ESP::AvatarSize, ImColor(0.22f, 0.22f, 0.22f, 1.00f), 0);
                                                DrawHealthRounded(ImVec2(mapPos.X, mapPos.Y), m_Hp, m_HpMax, Scaling * 2 + ESP::AvatarSize);
                                                DrawIconRounded(ImVec2(mapPos.X, mapPos.Y), m_ID, Scaling * ESP::AvatarSize);
                                            }
                                            if (ESP::PlayerAvatar) {
                                                DrawIconRounded(ImVec2(EntityRootSC.X, EntityRootSC.Y), m_ID, Scaling * 30);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        auto m_dicMonsterShow = BattleDataBattleManager->m_dicMonsterShow();
                        if (m_dicMonsterShow) {
                            for (int i = 0; i < m_dicMonsterShow->getSize(); i++) {
                                auto MonsterShow = m_dicMonsterShow->getValues()[i];
                                if (MonsterShow) {
                                    auto m_bInitComplete = MonsterShow->m_bInitComplete();
                                    if (m_bInitComplete) {
                                        auto m_bSameCampType = MonsterShow->m_bSameCampType();
                                        auto m_bDeath = MonsterShow->m_bDeath();
                                        auto m_bShowLayer = MonsterShow->m_bShowLayer();
                                        if (!m_bSameCampType && !m_bDeath) {
                                            auto m_iType = MonsterShow->m_iType();
                                            if (m_iType == 2 || m_iType == 5) {
                                                auto MonsterRootTF = MonsterShow->_Position();
                                                auto WorldToScreen = Camera::get_main()->WorldToScreenPoint(MonsterRootTF);
                                                auto MonsterRootSC = Vector2(ImGui::GetIO().DisplaySize.x - WorldToScreen.X, WorldToScreen.Y);
                                                if (WorldToScreen.Z > 0) {
                                                    MonsterRootSC = Vector2(WorldToScreen.X, ImGui::GetIO().DisplaySize.y - WorldToScreen.Y);
                                                }
                                                if (m_bShowLayer) {
                                                    continue;
                                                }
                                                if (ESP::MonsterRound) {
                                                    m_ImGui->AddCircleFilled(ImVec2(MonsterRootSC.X, MonsterRootSC.Y), Scaling * 6.0f, IM_COL32(255, 255, 255, 255), 0);
                                                }
                                                if (ESP::MonsterHealth) {
                                                    auto m_Hp = MonsterShow->m_Hp();
                                                    auto m_HpMax = MonsterShow->m_HpMax();
                                                    auto LineHealthStart = ImVec2(MonsterRootSC.X + Scaling * 40, MonsterRootSC.Y - Scaling * 30);
                                                    auto LineHealthEnd = ImVec2(LineHealthStart.x + Scaling * 160, LineHealthStart.y);
                                                    auto HealthStart = ImVec2(LineHealthStart.x, LineHealthStart.y - Scaling * 20);
                                                    auto HealthEnd = ImVec2(LineHealthEnd.x, LineHealthEnd.y - Scaling * 5);
                                                    auto HealthWidth = abs(HealthEnd.x - HealthStart.x);
                                                    auto PercentHP = ((float)m_Hp * HealthWidth) / (float)m_HpMax;
                                                    m_ImGui->AddLine(ImVec2(MonsterRootSC.X, MonsterRootSC.Y), LineHealthStart, IM_COL32(255, 255, 255, 255));
                                                    m_ImGui->AddLine(LineHealthStart, LineHealthEnd, IM_COL32(255, 255, 255, 155));
                                                    m_ImGui->AddRectFilled(HealthStart, HealthEnd, ImColor(0.22f, 0.22f, 0.22f, 1.00f), 10);
                                                    m_ImGui->AddRectFilled(HealthStart, ImVec2(HealthStart.x + PercentHP, HealthEnd.y), IM_COL32(225, 0, 0, 255), 10);
                                                    m_ImGui->AddRect(HealthStart, HealthEnd, IM_COL32(0, 0, 0, 255), 10);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
