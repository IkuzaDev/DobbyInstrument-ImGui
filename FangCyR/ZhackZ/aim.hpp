//
// Created by Admin on 2/6/2024.
//

#pragma once

struct sAim {
    struct sHelper {
        struct sSkills {
            bool Basic;
            bool Spell;
            bool Skill1;
            bool Skill2;
            bool Skill3;
            bool Skill4;
        };
        sSkills Skills{0};

        struct sPriority {
            int Target = 0;
            int SpeedControl = 0;
            float SkillControl = 0;
            bool AutoTakeSword;
            bool ManualTakeSword;
        };
        sPriority Priority{0};

        struct sCombo {
            //S1
            bool Brody;
            bool Franco;
            bool Xavier;
            bool Selena;
            //S2
            bool Xborg;
            bool Badang;
            bool Saber;
            bool Gord;
            //S3
            bool Pharsa;
            bool Eudora;
            bool Jawhead;
            bool Martis;
            //UF//FU
            bool Chou;
            bool Tigreal;
            bool Atlas;
            bool Franco1;
            bool Lolita;
        };
        sCombo Combo{0};

        struct sAutoCombo {
            //Line1
            bool Gusion;
            bool Paquito;
            bool LunoxLight;
            bool LunoxDark;
            //Line2
            bool Kimmy;
            bool Pharsa;
            bool Kagura;
            bool Eudora;
            //Line3
            bool Vale;
            bool Edith;
            bool Hayabusa;
            bool Ruby;
        };
        sAutoCombo AutoCombo{0};

        struct sManualCombo {
            //Line1
            bool Gusion;
            bool Paquito;
            bool LunoxLight;
            bool LunoxDark;
            //Line2
            bool Kimmy;
            bool Pharsa;
            bool Kagura;
            bool Eudora;
            //Line3
            bool Vale;
            bool Edith;
            bool Hayabusa;
            bool Ruby;
        };
        sManualCombo ManualCombo{0};

        struct sAutoUltimate {
            //1
            bool Beatrix;
            bool Xavier;
            bool Balmond;
            //2
            bool Layla;
            bool Moskov;
            bool Nana;
            bool Gord;
            //3
            bool Hilda;
            bool Martis;
            bool Thamuz;
            bool Argus;
        };
        sAutoUltimate AutoUltimate{0};

        struct sAutoSteal {
            bool Moskov;
            bool Xavier;
            bool Layla;
            bool Beatrix;
        };
        sAutoSteal AutoSteal{0};

        struct sSettings {
            int Target = 0;
        };
        sSettings Settings{0};

        struct sAutoSpell {
            bool Executed;
            bool FlameShoot;
            bool Vengeance;
            bool Flicker;
            bool Aegis;
        };
        sAutoSpell AutoSpell{0};

        struct sAutoRetribution {
            bool Buff;
            bool Turtle;
            bool Lord;
            bool Crab;
            bool Litho;
        };
        sAutoRetribution AutoRetribution{0};

    };
    sHelper Helper{0};
};
sAim Aim{0};

static float RangeFOV = 10.0f;

int CalculateRetriDamage(int m_Level, int _KillWildTimes, int _killNum, int _assistNum) {
    if ((_KillWildTimes + _killNum + _assistNum) < 5) {
        return 520 + (80 * m_Level);
    } else {
        return 1.521 * (520 + (80 * m_Level));
    }
}

std::pair<Vector3, Vector3> getMonster() {
    int iCalculate;
    Vector3 monsterPos = Vector3::Zero();
    Vector3 selfPos = Vector3::Zero();
    auto GameMainInstance = GameMain::Instance();
    if(GameMainInstance){
        auto _bGameInitDone = GameMainInstance->_bGameInitDone();
        if (_bGameInitDone){//if GameInitDone true
            auto BattleDataBattleBridge = BattleData::m_BattleBridge();
            if(BattleDataBattleBridge){//if battlebrigde not null
                auto bStartBattle = BattleDataBattleBridge->bStartBattle();
                if (bStartBattle){// battle start
                    auto BattleDataBattleManager = BattleData::battleManager();
                    if (BattleDataBattleManager) {
                        auto LocalPlayer = BattleDataBattleManager->m_LocalPlayerShow();
                        if(LocalPlayer){
                            auto m_Level = LocalPlayer->m_Level();
                            auto LogicBattleManager = LogicBattleManager::Instance();
                            if(LogicBattleManager){
                                auto playerSelf = LogicBattleManager->GetPlayerRealSelf();
                                selfPos = LocalPlayer->_Position();
                                auto _KillWildTimes = playerSelf->KillWildTimes();
                                auto m_PlayerData = playerSelf->m_PlayerData();
                                if(m_PlayerData){
                                    auto _killNum = m_PlayerData->killNum();
                                    auto _assistNum = m_PlayerData->assistNum();
                                    iCalculate = CalculateRetriDamage(m_Level, _KillWildTimes, _killNum, _assistNum);
                                }
                                auto MonsterList = BattleDataBattleManager->m_ShowMonsters();
                                if(MonsterList){
                                    for (int i = 0; i < MonsterList->getSize(); i++) {
                                        auto values = MonsterList->getItems()[i];
                                        if(values){
                                            auto m_ID = values->m_ID();
                                            auto m_bDeath = values->m_bDeath();
                                            auto m_bSameCampType = values->m_bSameCampType();
                                            auto m_HP = values->m_Hp();
                                            auto Max_HP = values->m_HpMax();
                                            auto position = values->_Position();
                                            float fDistance = Vector3::Distance(selfPos, position);
                                            if (fDistance <= 8.0f && m_HP < iCalculate) {
                                                auto iTargetEnemy = Vector3::Normalized(position - selfPos);
                                                if (Aim.Helper.AutoRetribution.Lord && (m_ID == 2002)) {
                                                    monsterPos = position;
                                                }
                                                if (Aim.Helper.AutoRetribution.Turtle && (m_ID == 2003)) {
                                                    monsterPos = position;
                                                }
                                                if (Aim.Helper.AutoRetribution.Buff && (m_ID == 2004 || m_ID == 2005)) {
                                                    monsterPos = position;
                                                }
                                                if (Aim.Helper.AutoRetribution.Crab && (m_ID == 2011 || m_ID == 2013)) {
                                                    monsterPos = position;
                                                }
                                                if (Aim.Helper.AutoRetribution.Litho && (m_ID == 2056)) {
                                                    monsterPos = position;
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
    return {selfPos, monsterPos};
}

void OnUpdate_handler(RegisterContext * ctx, const HookEntryInfo * info){
#if defined(__arm64__) || defined(__aarch64__)
    ShowSelfPlayer * SelfPlayer = (ShowSelfPlayer*)(ctx->general.x[0]);
#elif defined(__arm__)
    ShowSelfPlayer * SelfPlayer = (ShowSelfPlayer*)(ctx->general.r[0]);
#endif
    auto GameMainInstance = GameMain::Instance();
    if(GameMainInstance){
        auto _bGameInitDone = GameMainInstance->_bGameInitDone();
        if (_bGameInitDone){//if GameInitDone true
            auto BattleDataBattleBridge = BattleData::m_BattleBridge();
            if(BattleDataBattleBridge){//if battlebrigde not null
                auto bStartBattle = BattleDataBattleBridge->bStartBattle();
                if (bStartBattle){// battle start
                    auto BattleDataBattleManager = BattleData::battleManager();
                    if (BattleDataBattleManager) {
                        auto LocalPlayer = BattleDataBattleManager->m_LocalPlayerShow();
                        if(LocalPlayer){
                            if(Aim.Helper.AutoRetribution.Lord || Aim.Helper.AutoRetribution.Turtle || Aim.Helper.AutoRetribution.Crab || Aim.Helper.AutoRetribution.Buff || Aim.Helper.AutoRetribution.Litho){
                                if (SelfPlayer != NULL) {
                                    auto GetSkillUseType = LocalPlayer->GetSkillUseType(20020);
                                    static bool skilluse;
                                    auto [selfPos, monsterPos] = getMonster();
                                    if ((selfPos != Vector3::Zero()) && (monsterPos != Vector3::Zero())) {
                                        auto dir = Vector3::Normalized(monsterPos - selfPos);
                                        if(SelfPlayer->TryUseSkill(20020, dir, false, Vector3::Zero()) != SPELL_CAST_IN_COOLDOWN){
                                            skilluse = false;
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