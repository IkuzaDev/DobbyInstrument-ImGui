//
// Created by FangCybertron
//
#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include <thread>
#include <pthread.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <elf.h>
#include <sys/system_properties.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <codecvt>
#include <tgmath.h>
#include <time.h>
#include <queue>
#include <android/native_window.h>
#include <android/input.h>
#include <android/keycodes.h>

#include "ImGui/Misc/imgui.h"
#include "ImGui/Misc/imgui_impl_opengl3.h"
#include "ImGui/Misc/imgui_internal.h"
#include "ImGui/Misc/imgui_image.h"
#include "ImGui/Misc/imgui_themes.h"
#include "ImGui/Misc/SlateForOnePlus.h"

#include "FangCyR/Config.hpp"
#include "FangCyR/Obfuscate.hpp"
#include "FangCyR/Base64.hpp"
#include "FangCyR/JniStuff.hpp"

#include "FangCyR/Engine/Elf/include/D5Tools.h"
#include "FangCyR/Engine/Dobby/Dobby.hpp"
#include "FangCyR/Engine/UTF8/checked.h"
#include "FangCyR/Engine/UTF8/unchecked.h"
#include "FangCyR/Engine/IL2CPP/il2cpp-api.hpp"
#include "FangCyR/Engine/UNITY/Unity.hpp"

#include "FangCyR/Validation/Json.hpp"
#include "FangCyR/Validation/Login.hpp"

#include "FangCyR/ZhackZ/IconList.hpp"
#include "FangCyR/ZhackZ/SpellList.hpp"
#include "FangCyR/ZhackZ/IconHero.hpp"
#include "FangCyR/ZhackZ/DrawEsp.hpp"
#include "FangCyR/ZhackZ/aim.hpp"
#include "FangCyR/ZhackZ/UnlockSkin.hpp"
#include "FangCyR/ZhackZ/Features.hpp"


static void LockResolution(int width, int height) {
    CONFIG::DisplayWidth = width;
    CONFIG::DisplayHeight = height;
}

void LockDraw() {
    if (CONFIG::DisplayWidth != CONFIG::EglWidth || CONFIG::DisplayHeight != CONFIG::EglHeight) {
        Screen::SetResolution(CONFIG::DisplayWidth, CONFIG::DisplayHeight, true);
	}
    ImGuiDrawEsp();
    DrawEsp();
    ListFeatures();
}

void eglSwapBuffers_handler(RegisterContext * ctx, const HookEntryInfo * info)
{
    static int count = 0;
    if(count < 25){
        count++; //Delay for fix Sandbox etc.
    }else{
        if (!Display_Window::m_pWindow()->getViewPort()) return;
        CONFIG::EglWidth = Display_Window::m_pWindow()->getWidth();
        CONFIG::EglHeight = Display_Window::m_pWindow()->getHeight();
        CONFIG::DisplayWidth = Display::_mainDisplay()->get_systemWidth();
        CONFIG::DisplayHeight = Display::_mainDisplay()->get_systemHeight();
        if (!CONFIG::Initialized) {
            float Scaling = Screen::get_dpi() / 150;
            ImGui::CreateContext();
            ImGuiStyle& style = ImGui::GetStyle();

            style.Alpha = 1.0f;
            style.DisabledAlpha = 1.0f;
            style.WindowPadding = ImVec2(12.0f, 12.0f);
            style.WindowRounding = 5.5f;
            style.WindowBorderSize = 0.0f;
            style.WindowMinSize = ImVec2(20.0f, 20.0f);
            style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
            style.WindowMenuButtonPosition = ImGuiDir_Right;
            style.ChildRounding = 0.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 0.0f;
            style.PopupBorderSize = 1.0f;
            style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
            style.FrameRounding = 5.89999961853027f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
            style.ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
            style.CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
            style.IndentSpacing = 0.0f;
            style.ColumnsMinSpacing = 4.900000095367432f;
            style.ScrollbarSize = 11.60000038146973f;
            style.ScrollbarRounding = 15.89999961853027f;
            style.GrabMinSize = 3.700000047683716f;
            style.GrabRounding = 20.0f;
            style.TabRounding = 0.0f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = ImGuiDir_Right;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
            style.ScaleAllSizes(Scaling);

            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09411764889955521f, 0.1019607856869698f, 0.1176470592617989f, 1.0f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1137254908680916f, 0.125490203499794f, 0.1529411822557449f, 1.0f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.7960784435272217f, 0.4980392158031464f, 1.0f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1803921610116959f, 0.1882352977991104f, 0.196078434586525f, 1.0f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1529411822557449f, 0.1529411822557449f, 0.1529411822557449f, 1.0f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.1411764770746231f, 0.1647058874368668f, 0.2078431397676468f, 1.0f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.105882354080677f, 0.105882354080677f, 0.105882354080677f, 1.0f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.1294117718935013f, 0.1490196138620377f, 0.1921568661928177f, 1.0f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
            style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1450980454683304f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.125490203499794f, 0.2745098173618317f, 0.572549045085907f, 1.0f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8823529481887817f, 0.7960784435272217f, 0.5607843399047852f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95686274766922f, 0.95686274766922f, 0.95686274766922f, 1.0f);
            style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
            style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
            style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
            style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
            style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2666666805744171f, 0.2901960909366608f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
            style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
            ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 300 es"));

            ImGuiIO *io = &ImGui::GetIO();
            io->ConfigWindowsMoveFromTitleBarOnly = true;
            io->IniFilename = nullptr;

            ImFontConfig fonts_config;
            fonts_config.GlyphRanges = io->Fonts->GetGlyphRangesCyrillic();
            fonts_config.FontDataOwnedByAtlas = false;
            io->Fonts->AddFontFromMemoryCompressedBase85TTF(SlateForOnePlus_compressed_data_base85, Scaling * 10.0f, &fonts_config);

            AttachIcon();
            AttachSpell();
            LockResolution(CONFIG::EglWidth, CONFIG::EglHeight);
            CONFIG::Initialized = true;
        }

        ImGuiIO *io = &ImGui::GetIO();
        io->DisplaySize = ImVec2((float)CONFIG::DisplayWidth, (float)CONFIG::DisplayHeight);
        io->DisplayFramebufferScale = ImVec2((float)CONFIG::EglWidth / CONFIG::DisplayWidth, (float)CONFIG::EglHeight / CONFIG::DisplayHeight);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        if(SystemData::IsVpn()){
            auto centerPOS = Display_Window::m_pWindow()->getCenter();
            auto Scaling = ImGui::GetIO().FontGlobalScale;
            float Thiz = 5.0f;
            std::string str = "Please Disable VPN connection!!";
            ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), Scaling * 22.0f, ImVec2(centerPOS.x + Thiz, centerPOS.y + Scaling * 5), IM_COL32(255, 255, 0, 255), str.c_str());
        }

        LockDraw();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

EGLBoolean (*Orig_EglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean EglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    
    eglQuerySurface(dpy, surface, EGL_WIDTH, &CONFIG::EglWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &CONFIG::EglHeight);
    CONFIG::DisplayWidth = Display::_mainDisplay()->get_systemWidth();
    CONFIG::DisplayHeight = Display::_mainDisplay()->get_systemHeight();
    
    if (!CONFIG::Initialized) {
        float Scaling = Screen::get_dpi() / 120;
        ImGui::CreateContext();
        SetBlackGoldTheme();
        ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 300 es"));
        
        ImGuiIO *io = &ImGui::GetIO();
        io->ConfigWindowsMoveFromTitleBarOnly = true;
        io->IniFilename = nullptr;
        
        ImFontConfig fonts_config;
        fonts_config.GlyphRanges = io->Fonts->GetGlyphRangesCyrillic();
        fonts_config.FontDataOwnedByAtlas = false;
        io->Fonts->AddFontFromMemoryCompressedBase85TTF(SlateForOnePlus_compressed_data_base85, Scaling * 10.0f, &fonts_config);
        
        ImGuiStyle *style = &ImGui::GetStyle();
        style->WindowTitleAlign = ImVec2(0.0f, 0.5f);
        style->ScaleAllSizes(Scaling);
        AttachIcon();
        AttachSpell();
        LockResolution(CONFIG::EglWidth, CONFIG::EglHeight);
        CONFIG::Initialized = true;
    }
    ImGuiIO *io = &ImGui::GetIO();
    io->DisplaySize = ImVec2((float)CONFIG::DisplayWidth, (float)CONFIG::DisplayHeight);
    io->DisplayFramebufferScale = ImVec2((float)CONFIG::EglWidth / CONFIG::DisplayWidth, (float)CONFIG::EglHeight / CONFIG::DisplayHeight);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    LockDraw();
    
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return Orig_EglSwapBuffers(dpy, surface);
}

jboolean (*Orig_NativeInjectEvent)(JNIEnv *env, jobject instance, jobject event);
jboolean NativeInjectEvent(JNIEnv *env, jobject instance, jobject event) {
    ImGuiIO *io = &ImGui::GetIO();
    jclass KeyEvent = env->FindClass(OBFUSCATE("android/view/KeyEvent"));
    jclass MotionEvent = env->FindClass((OBFUSCATE("android/view/MotionEvent")));
    if (env->IsInstanceOf(event, KeyEvent)) {
        jmethodID getKeyCodeMethod = env->GetMethodID(KeyEvent, OBFUSCATE("getKeyCode"), OBFUSCATE("()I"));
        switch (env->CallIntMethod(event, getKeyCodeMethod)) {
            case 4:
                CONFIG::ShowImGui = true;
                break;
            default:
            break;
        }
    }
    if (!env->IsInstanceOf(event, MotionEvent)) {
        return Orig_NativeInjectEvent(env, instance, event);
    }
    if (env->IsInstanceOf(event, MotionEvent)) {
        jmethodID getXMethod = env->GetMethodID(MotionEvent,(OBFUSCATE("getX")),(OBFUSCATE("()F")));
        jmethodID getYMethod = env->GetMethodID(MotionEvent,(OBFUSCATE("getY")),(OBFUSCATE("()F")));
        jmethodID getActionMethod = env->GetMethodID(MotionEvent,(OBFUSCATE("getAction")),(OBFUSCATE("()I")));
        switch (env->CallIntMethod(event, getActionMethod)) {
            case 0:
                io->AddMousePosEvent(env->CallFloatMethod(event, getXMethod), env->CallFloatMethod(event, getYMethod));
                io->AddMouseButtonEvent(0, true);
                break;
            case 1:
                io->AddMouseButtonEvent(0, false);
                io->AddMousePosEvent(-1, -1);
                break;
            case 2:
                io->AddMousePosEvent(env->CallFloatMethod(event, getXMethod), env->CallFloatMethod(event, getYMethod));
                break;
            default:
            break;
        }
    }
    if (io->MouseDownOwnedUnlessPopupClose[0]) {
        return false;
    }
    return Orig_NativeInjectEvent(env,instance,event);
};
