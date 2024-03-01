#pragma once

struct HeroIcon {
    GLuint Textures = 0;
    int Width = 0;
    int Height = 0;
    bool IsValid = false;
};

std::vector<HeroIcon> Looper;
std::vector<HeroIcon> Looper2;

HeroIcon ICTextures(int Id) {
    switch(Id) {
        case 9995:
            return Looper[18];
            break;
        case 9996:
            return Looper[16];
            break;
        case 9997:
            return Looper[6];
            break;
        case 9998:
            return Looper[16];
            break;
        case 9999:
            return Looper[18];
            break;
        default:
        return Looper[Id];
    }
    return Looper[Id];
}

HeroIcon SpellTexture(int Id) {
    switch(Id) {
    case 20060:
        return Looper2[1];
        break;
    case 20160:
        return Looper2[2];
        break;
    case 20150:
        return Looper2[3];
        break;
    case 20140:
        return Looper2[4];
        break;
    case 20100:
        return Looper2[5];
        break;
    case 20030:
        return Looper2[6];
        break;
    case 20070:
        return Looper2[7];
        break;    
    case 20080:
        return Looper2[8];
        break;
    case 20020:
        return Looper2[9];
        break;    
    case 20050:
        return Looper2[10];
        break;
    case 20040:
        return Looper2[11];
        break;
    case 20190:
        return Looper2[12];
        break;
    default:
    return Looper2[Id];
    }
    return Looper2[Id];
}

bool LoadTextureFromFile(const char *filename, HeroIcon *source) {
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
    return false;
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    #endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);
    source->Textures = image_texture;
    source->Width = image_width;
    source->Height = image_height;
    return true;
}

void AttachIcon() {
    for (int i = 0; i < 150; i++) {
        HeroIcon Source;
        std::string apkPkg = Tools::GetPackageName(Env(), Context());
        std::string Path = std::string(OBFUSCATE("/data/data/")) + apkPkg.c_str() + std::string(OBFUSCATE("/files/"));
        Path += std::to_string(i);
        WriteToFile(Path, base64::from_base64(IconAssets(i)));
        Source.IsValid = LoadTextureFromFile(Path.c_str(), &Source);
        std::remove(Path.c_str());
        Looper.push_back(Source);
    }
}

void AttachSpell() {
    for (int i = 0; i < 150; i++) {
        HeroIcon Source;
        std::string apkPkg = Tools::GetPackageName(Env(), Context());
        std::string Path = std::string(OBFUSCATE("/data/data/")) + apkPkg.c_str() + std::string(OBFUSCATE("/files/"));
        Path += std::to_string(i);
        WriteToFile(Path, base64::from_base64(SpellAssets[i]));
        Source.IsValid = LoadTextureFromFile(Path.c_str(), &Source);
        std::remove(Path.c_str());
        Looper2.push_back(Source);
    }
}

void DrawHealthRounded(ImVec2 pos, int m_Hp, int m_HpMax, int size) {
    float max = ((3.14159265359f * 2));
    ImGui::GetForegroundDrawList()->PathArcTo(pos, size, (-(max / 4.0f)) + (max / m_HpMax) * (m_HpMax - m_Hp), max - (max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(IM_COL32(225, 0, 0, 255), ImDrawFlags_None, (4));
}

void DrawIconRounded(ImVec2 pos, int m_ID, int size) {
    auto IconSrc = ICTextures(m_ID);
    if (IconSrc.IsValid) {
        ImGui::GetForegroundDrawList()->AddImageRounded((void*)(uintptr_t)IconSrc.Textures,
        ImVec2(pos.x - size, pos.y - size), ImVec2(pos.x + size, pos.y + size),
        ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255), 25.0f);
    }
}

void RoomInfoHero(int HeroID, float Size = 38) {
    auto IconI = ICTextures(HeroID);
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.Textures, ImVec2(Size, Size));
    }
}

void RoomInfoSpell(int HeroID, float Size = 38) {
    auto IconI = SpellTexture(HeroID);
    if (IconI.IsValid) {
        ImGui::Image((void*)(uintptr_t)IconI.Textures, ImVec2(Size, Size));
    }
}
