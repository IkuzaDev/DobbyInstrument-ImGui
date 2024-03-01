
#pragma once

static std::string Wsx = OBFUSCATE("");
static std::string serial = OBFUSCATE("");
static bool IsLoading = false;
static bool Activated = false;
static float SizeFile;

void CheckSafe(const char* pkg){
    std::string param = std::string(pkg);
    if(param == std::string("com.mobilelegends.hwag")){
        ImGui::TextColored(ImVec4(1.00f, 1.00f, 0.00f, 1.00f), "Safe [-]");
    }else{
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Risk [-]");
    }
}

std::string SetButtonText(std::string text, bool separator){
    if(separator){
        return text +  " [ ON ]";
    }
    return text +  " [ OFF ]";
}

void LoginThread(const std::string &user_key, bool *success) {
    IsLoading = true;
    Wsx = Login(user_key.c_str(), success);
    IsLoading = false;
}

void SerialThread(){
    serial = GetSerial();
}

void GameSharedPreferences() {
    std::string apkPkg = Tools::GetPackageName(Env(), Context());
    std::string playerprefs = apkPkg.c_str() + std::string(OBFUSCATE(".v2.playerprefs"));
    SharedPreferences sharedPref(Env(), Context(), playerprefs.c_str());
    SharedPreferences_Editor editor = sharedPref.edit();
    
    bool ActiveRefreshRate = sharedPref.getBoolean(OBFUSCATE("ActiveRefreshRate"));
    if (OTHERS::RefreshRate == 0) {
        editor.putBoolean(OBFUSCATE("ActiveRefreshRate"), false);
        editor.commit();
    } else if (OTHERS::RefreshRate == 1) {
        editor.putBoolean(OBFUSCATE("ActiveRefreshRate"), true);
        editor.putInt(OBFUSCATE("HighFpsModeSee"), 1);
        editor.commit();
    } else if (OTHERS::RefreshRate == 2) {
        editor.putBoolean(OBFUSCATE("ActiveRefreshRate"), true);
        editor.putInt(OBFUSCATE("HighFpsModeSee"), 2);
        editor.commit();
    } else if (OTHERS::RefreshRate == 3) {
        editor.putBoolean(OBFUSCATE("ActiveRefreshRate"), true);
        editor.putInt(OBFUSCATE("HighFpsModeSee"), 3);
        editor.commit();
    } else if (OTHERS::RefreshRate == 4) {
        editor.putBoolean(OBFUSCATE("ActiveRefreshRate"), true);
        editor.putInt(OBFUSCATE("HighFpsModeSee"), 4);
        editor.commit();
    }
    if (ActiveRefreshRate) {
        OTHERS::RefreshRate = sharedPref.getInt(OBFUSCATE("HighFpsModeSee"));
    }
    
    bool ActiveGraphics = sharedPref.getBoolean(OBFUSCATE("ActiveGraphics"));
    if (OTHERS::Graphics == 0) {
        editor.putBoolean(OBFUSCATE("ActiveGraphics"), false);
        editor.commit();
    } else if (OTHERS::Graphics == 1) {
        editor.putBoolean(OBFUSCATE("ActiveGraphics"), true);
        editor.putInt(OBFUSCATE("PerformanceDevice_EnableQuality_new"), 1);
        editor.commit();
    } else if (OTHERS::Graphics == 2) {
        editor.putBoolean(OBFUSCATE("ActiveGraphics"), true);
        editor.putInt(OBFUSCATE("PerformanceDevice_EnableQuality_new"), 2);
        editor.commit();
    } else if (OTHERS::Graphics == 3) {
        editor.putBoolean(OBFUSCATE("ActiveGraphics"), true);
        editor.putInt(OBFUSCATE("PerformanceDevice_EnableQuality_new"), 3);
        editor.commit();
    } else if (OTHERS::Graphics == 4) {
        editor.putBoolean(OBFUSCATE("ActiveGraphics"), true);
        editor.putInt(OBFUSCATE("PerformanceDevice_EnableQuality_new"), 4);
        editor.commit();
    }
    if (ActiveGraphics) {
        OTHERS::Graphics = sharedPref.getInt(OBFUSCATE("PerformanceDevice_EnableQuality_new"));
    }
    if (!OTHERS::EnableCamera) {
        OTHERS::Auto2xCamera = false;
        OTHERS::SetFieldOfView = 0.0f;
    }
    if (OTHERS::Auto2xCamera) {
        OTHERS::SetFieldOfView = 10.0f;
    }
}

void ListFeatures() {
    GameSharedPreferences();
    static bool CloseMenu = false;
    static bool anu;
    std::string apkPkg = Tools::GetPackageName(Env(), Context());
    std::string playerprefs = apkPkg.c_str() + std::string(OBFUSCATE(".v2.playerprefs"));
    SharedPreferences sharedPref(Env(), Context(), playerprefs.c_str());
    SharedPreferences_Editor editor = sharedPref.edit();
    bool ActiveSettingMinimap = sharedPref.getBoolean(OBFUSCATE("ActiveSettingMinimap"));
    if (CONFIG::ShowImGui) {
        
        std::string mytitle = std::string(OBFUSCATE("D5STUDIO")) + std::string(" | SIMPLE ") + std::string("v2.3(NewSystem)") + std::string(" ") + std::string(ABI);
        
        ImGui::Begin(mytitle.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiTableFlags_NoSavedSettings);
        static char Key[150];
		if (!Activated) {
            Activated = false;
            static bool Prefs = false;
            ImGui::BeginGroupPanel(OBFUSCATE("Please Login! (Copy Key to Clipboard)"), ImVec2(ImGui::GetContentRegionAvail().x, 0));
            ImGui::InputTextWithHint(OBFUSCATE("##SerialNumber"), OBFUSCATE("Your Key Here"), Key, IM_ARRAYSIZE(Key), ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_Password);
            ImGui::Separator();
            if (!Prefs) {
                auto LoadKey = sharedPref.getString(OBFUSCATE("Serial Number"));
                strncpy(Key, LoadKey.c_str(), sizeof Key);
                Prefs = true;
            }
            if (IsLoading) {
                ImGui::Text(OBFUSCATE("Getting Data %c"), OBFUSCATE("<-._>")[(int)(ImGui::GetTime() / 0.05f) & 3]);
            } else {
                if (ImGui::Button(OBFUSCATE("PASTE KEY"), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                    auto PasteKey = Clipboard();
                    strncpy(Key, PasteKey.c_str(), sizeof Key);
                }
                if (ImGui::Button(OBFUSCATE("LOGIN"), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                    std::thread(LoginThread, std::string(Key), &Activated).detach();
                    std::thread(SerialThread).detach();
                }
			}
            ImGui::Spacing();
			ImGui::EndGroupPanel();
            if (!IsLoading && !Wsx.empty()) {
                ImGui::Text(OBFUSCATE("%s"), Wsx.c_str());
            }
        } else {
            if (!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) {
               if(title.empty() && battleData.empty()){
                   if (Activated) {
                       editor.putString(OBFUSCATE("Serial Number"), Key);
                       editor.commit();
                   }
                   ImGui::BeginTabBar(OBFUSCATE("##TabBar"), ImGuiTabBarFlags_FittingPolicyScroll);

                   if (ImGui::BeginTabItem("Visual Menu")) {
                       ImGui::BeginGroupPanel("Player ESP", ImVec2(0.0f, 0.0f));
                       {
                           ImGui::Checkbox(OBFUSCATE("Health Bar"), &ESP::PlayerHealth);
                           ImGui::Checkbox(OBFUSCATE("Level Hero"), &ESP::HeroLevel);
                           ImGui::Checkbox(OBFUSCATE("Hero Name"), &ESP::HeroName);
                           ImGui::Spacing();
                       }
                       ImGui::EndGroupPanel();

                       ImGui::SameLine();

                       ImGui::BeginGroup();
                       {
                           ImGui::BeginGroupPanel("Jungle ESP", ImVec2(-1.0f, 0.0f));
                           {
                               ImGui::Checkbox(OBFUSCATE("Round ##clone"), &ESP::MonsterRound);
                               ImGui::SameLine();
                               ImGui::Checkbox(OBFUSCATE("Health ##clone"), &ESP::MonsterHealth);
                               ImGui::SameLine();
                           }
                           ImGui::EndGroupPanel();

                           ImGui::BeginGroupPanel("Info ESP", ImVec2(-1.0f, 0.0f));
                           {
                               ImGui::Checkbox(OBFUSCATE("Skill CD"), &ESP::ShowSkillCD);
                               ImGui::Checkbox(OBFUSCATE("Spell CD"), &ESP::ShowSpellCD);
                               //ImGui::Checkbox(OBFUSCATE("Icon Hero"), &ESP::PlayerAvatar);
                               ImGui::Spacing();
                           }
                           ImGui::EndGroupPanel();
                       }
                       ImGui::EndGroup();

                       ImGui::BeginGroupPanel("Additional", ImVec2(-1.0f, 0.0f));
                       {
                           ImGui::Checkbox(OBFUSCATE("Enable"), &OTHERS::EnableCamera);
                           ImGui::SameLine();
                           ImGui::Checkbox(OBFUSCATE("Auto 10x"), &OTHERS::Auto2xCamera);
                           ImGui::SliderFloat(OBFUSCATE("##CameraView"), &OTHERS::SetFieldOfView, 0.0f, 20.0f, OBFUSCATE("%.1f"));
                           ImGui::Spacing();
                       }
                       ImGui::EndGroupPanel();

                       ImGui::EndTabItem();
                   }

                   if (ImGui::BeginTabItem(OBFUSCATE("Room Info"))) {
                       ImGui::BeginGroupPanel(OBFUSCATE("Settings"), ImVec2(0, 0));
                       {
                           if (ImGui::Button(SetButtonText("Info Team", InfoRoom.bTeam).c_str(), ImVec2(ImGui::GetContentRegionAvail().x / 2, 0))) {
                               InfoRoom.bTeam = !InfoRoom.bTeam;
                           }
                           ImGui::SameLine();
                           if (ImGui::Button(SetButtonText("Info Enemy", InfoRoom.bEnemy).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                               InfoRoom.bEnemy = !InfoRoom.bEnemy;
                           }
                       }
                       ImGui::EndGroupPanel();
                       if(InfoRoom.bEnemy || InfoRoom.bTeam){
                           ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, ImVec4(0.26f, 0.59f, 0.98f, 0.40f));
                           ImGui::PushStyleColor(ImGuiCol_TableBorderStrong, ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
                           ImGui::PushStyleColor(ImGuiCol_TableBorderLight, ImVec4(0.26f, 0.59f, 0.98f, 1.00f));
                       }

                       if(InfoRoom.bTeam){
                           ImGui::TextColored(ImVec4(0.06f, 0.53f, 0.98f, 1.00f), OBFUSCATE("Team"));
                           if (ImGui::BeginTable(OBFUSCATE("##Team"), 7, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
                               ImGui::TableSetupColumn(OBFUSCATE("Name"));
                               ImGui::TableSetupColumn(OBFUSCATE("ID"));
                               ImGui::TableSetupColumn(OBFUSCATE("Verified"));
                               ImGui::TableSetupColumn(OBFUSCATE("Rank"));
                               ImGui::TableSetupColumn(OBFUSCATE("Star"));
                               ImGui::TableSetupColumn(OBFUSCATE("Hero"));
                               ImGui::TableSetupColumn(OBFUSCATE("Spell"));
                               ImGui::TableHeadersRow();
                               for (int row = 0; row < 5; row ++) {
                                   ImGui::TableNextRow();
                                   for (int column = 0; column < 7; column ++) {
                                       ImGui::TableSetColumnIndex(column);
                                       char buf[32];
                                       if (InfoRoom.Active) {
                                           if(!InfoRoom.Team[row].bEnemy && InfoRoom.Team[row].bTeam){
                                               if (column == 0) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Team[row].Name.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 1) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Team[row].UserID.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 2) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Team[row].Verified.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 3) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Team[row].Rank.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 4) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Team[row].Point.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 5) {
                                                   RoomInfoHero(InfoRoom.Team[row].HeroID);
                                               } else if (column == 6) {
                                                   RoomInfoSpell(InfoRoom.Team[row].SpellID);
                                               }
                                           }
                                       } else {
                                           ImGui::TextUnformatted(OBFUSCATE(""));
                                       }
                                   }
                               }
                               ImGui::EndTable();
                           }
                       }
                       if(InfoRoom.bEnemy){
                           ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), OBFUSCATE("Enemy"));
                           if (ImGui::BeginTable(OBFUSCATE("##Enemy"), 7, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
                               ImGui::TableSetupColumn(OBFUSCATE("Name"));
                               ImGui::TableSetupColumn(OBFUSCATE("ID"));
                               ImGui::TableSetupColumn(OBFUSCATE("Verified"));
                               ImGui::TableSetupColumn(OBFUSCATE("Rank"));
                               ImGui::TableSetupColumn(OBFUSCATE("Star"));
                               ImGui::TableSetupColumn(OBFUSCATE("Hero"));
                               ImGui::TableSetupColumn(OBFUSCATE("Spell"));
                               ImGui::TableHeadersRow();
                               for (int row = 0; row < 5; row ++) {
                                   ImGui::TableNextRow();
                                   for (int column = 0; column < 7; column ++) {
                                       ImGui::TableSetColumnIndex(column);
                                       char buf[32];
                                       if (InfoRoom.Active) {
                                           if(!InfoRoom.Enemy[row].bTeam && InfoRoom.Enemy[row].bEnemy){
                                               if (column == 0) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Enemy[row].Name.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 1) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Enemy[row].UserID.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 2) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Enemy[row].Verified.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 3) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Enemy[row].Rank.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 4) {
                                                   sprintf(buf, OBFUSCATE("%s"), InfoRoom.Enemy[row].Point.c_str());
                                                   ImGui::TextUnformatted(buf);
                                               } else if (column == 5) {
                                                   RoomInfoHero(InfoRoom.Enemy[row].HeroID);
                                               } else if (column == 6) {
                                                   RoomInfoSpell(InfoRoom.Enemy[row].SpellID);
                                               }
                                           }
                                       } else {
                                           ImGui::TextUnformatted(OBFUSCATE(""));
                                       }
                                   }
                               }
                               ImGui::EndTable();
                           }
                       }

                       if(InfoRoom.bEnemy || InfoRoom.bTeam){
                           ImGui::PopStyleColor();
                           ImGui::PopStyleColor();
                           ImGui::PopStyleColor();
                       }

                       ImGui::EndTabItem();
                   } // Room Info

                   /*if (ImGui::BeginTabItem(OBFUSCATE("Auto Spell"))) {

                       ImGui::BeginGroupPanel(OBFUSCATE("Retribution"), ImVec2(0, 0));
                       {
                           ImGui::Checkbox("Target[Turtle]", &Aim.Helper.AutoRetribution.Turtle);
                           ImGui::SameLine();
                           ImGui::Checkbox("Target[Litho]", &Aim.Helper.AutoRetribution.Litho);
                           ImGui::SameLine();
                           ImGui::Checkbox("Target[Lord]", &Aim.Helper.AutoRetribution.Lord);
                           ImGui::SameLine();
                           ImGui::Checkbox("Target[Crab]", &Aim.Helper.AutoRetribution.Crab);
                           ImGui::SameLine();
                           ImGui::Checkbox("Target[Buff]", &Aim.Helper.AutoRetribution.Buff);
                           ImGui::Spacing();
                       }
                       ImGui::EndGroupPanel();

                       ImGui::EndTabItem();
                   }//spell*/

                   if (ImGui::BeginTabItem(OBFUSCATE("Others"))) {

                       ImGui::BeginGroup();
                       {
                           //show AccID
                           if(SystemData::m_uiID() != 0){
                               std::string myUID = std::string(OBFUSCATE("MyID :"));
                               ImGui::Text(myUID.c_str());
                               ImGui::SameLine();
                               ImGui::TextColored(ImVec4(1.00f, 1.00f, 0.00f, 1.00f), TextFormatv1("%d", SystemData::m_uiID()));
                           }
                           //show version
                           //std::string apkVersion = std::string(OBFUSCATE("Version :"));
                           //ImGui::Text(apkVersion.c_str());
                           //ImGui::SameLine();
                           //CheckSafe(Tools::GetPackageName(Env(), Context()));

                           //show expired
                           std::string keyExpired = std::string(OBFUSCATE("Expired :"));
                           ImGui::Text(keyExpired.c_str());
                           ImGui::SameLine();
                           ImGui::TextColored(ImVec4(1.00f, 1.00f, 0.00f, 1.00f), expired.c_str());

                           ImGui::Spacing();
                       }
                       ImGui::EndGroup();

                       ImGui::BeginGroupPanel(OBFUSCATE("Settings"), ImVec2(0, 0));
                       {
                           if (ImGui::Button(OBFUSCATE("Close Menu"), ImVec2(500, 0))) {
                               ImGui::OpenPopup(OBFUSCATE("CloseMenu"));
                               CloseMenu = true;
                           }
                           if (CloseMenu) {
                               ImGui::BeginPopupModal(OBFUSCATE("CloseMenu"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiTableFlags_NoSavedSettings);
                               ImGui::Text(OBFUSCATE("Close Menu - Are You Sure?"));
                               ImGui::Text(OBFUSCATE("(Press Back To Show Menu)"));
                               ImGui::Separator();
                               ImGui::Spacing();
                               if (ImGui::Button(OBFUSCATE("YES"), ImVec2(-1, 0))) {
                                   CONFIG::ShowImGui = false;
                                   CloseMenu = false;
                               }
                               ImGui::SetItemDefaultFocus();
                               if (ImGui::Button(OBFUSCATE("NO"), ImVec2(-1, 0))) {
                                   CloseMenu = false;
                               }
                               ImGui::EndPopup();
                           }
                           ImGui::Spacing();
                       }
                       ImGui::EndGroupPanel(); // Settings
                       ImGui::EndTabItem();
                   } // Others

                   ImGui::EndTabBar();
               }
            } // Check Login
        } // If Login
        ImGui::End();
    } // Close Menu
}
