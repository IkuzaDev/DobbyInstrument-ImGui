//
// Created by FangCybertron
//
#pragma once

namespace CONFIG {
	int EglWidth = 0;
	int EglHeight = 0;
    int DisplayWidth = 0;
    int DisplayHeight = 0;
    bool LoginValid = false;
    bool Initialized = false;
	bool ClearMouse = true;
	bool ShowImGui = true;
};

namespace ESP {
	bool PlayerAvatar = false;
	bool PlayerLine = false;
	bool PlayerRound = false;
	bool PlayerHealth = false;
	bool HeroLevel = false;
	bool HeroName = false;
	bool MonsterRound = false;
	bool MonsterHealth = false;
	bool ShowSkillCD = false;
	bool ShowSpellCD = false;
	bool ShowMinimap = false;
    int MinimapPos = 0;
    int MinimapSize = 336;
    int AvatarSize = 17;
};

namespace OTHERS {
    bool EnableCamera = false;
    bool Auto2xCamera = false;
    bool MinimapSetting = false;
    bool ForbidSkin = false;
    int RefreshRate = 0;
    int Graphics = 0;
	float SetFieldOfView = 0.0f;
};

struct CaseRoom {
    std::string Name;
    std::string UserID;
    std::string Verified;
    std::string Rank;
    std::string Point;
    bool bTeam;
    bool bEnemy;
    int HeroID;
    int SpellID;
};

struct {
    CaseRoom Team[5];
    CaseRoom Enemy[5];
    bool bTeam;
    bool bEnemy;
    int SelfCamp = -1;
    bool Active = false;
} InfoRoom;

uintptr_t INTLFoundation;

class Window
{
private:
    int ViewPort[4];

public:
    bool getViewPort() {
        glGetIntegerv(GL_VIEWPORT, this->ViewPort);
        if (this->ViewPort[2] && this->ViewPort[3]) return true;
        return false;
    }

    float getX() {
        return (float)this->ViewPort[0];
    }

    float getY() {
        return (float)this->ViewPort[1];
    }

    float getW() {
        return (float)this->ViewPort[2];
    }

    float getH() {
        return (float)this->ViewPort[3];
    }

    float getWidth() {
        return (this->getW() + (this->getX() * 2.0f));
    }

    float getHeight() {
        return (this->getH() + (this->getY() * 2.0f));
    }

    ImVec2 getSize() {
        return ImVec2(this->getWidth(), this->getHeight());
    }

    ImVec2 getCenter() {
        return ImVec2(this->getWidth() / 2.0f, this->getHeight() / 2.0f);
    }

    ImVec2 getScale() {
        return ImVec2(this->getWidth() * 0.00052083333f, this->getHeight() * 0.00092592592f);
    }

    bool isRotation() {
        if (this->getWidth() < this->getHeight()) return true;
        return false;
    }
};

class Display_Window
{
public:
    static Window * m_pWindow()
    {
        static Window * instance = NULL;
        if (instance == NULL) instance = new Window;
        return instance;
    }
};