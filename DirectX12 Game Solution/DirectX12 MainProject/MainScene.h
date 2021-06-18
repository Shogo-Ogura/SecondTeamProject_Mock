//
// MainScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
    MainScene();
    virtual ~MainScene() { Terminate(); }

    MainScene(MainScene&&) = default;
    MainScene& operator= (MainScene&&) = default;

    MainScene(MainScene const&) = delete;
    MainScene& operator= (MainScene const&) = delete;

    // These are the functions you will implement.
    void Initialize() override;
    void LoadAssets() override;

    void Terminate() override;

    void OnDeviceLost() override;
    void OnRestartSound() override;

    NextScene Update(const float deltaTime) override;
    void Render() override;

private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

    // 変数の宣言

    //背景
    DX9::SPRITE bgTestSprite;
    float bgPositionX;

    //プレイヤー
    //金魚
    DX9::SPRITE goldfishTestSprite;

    //ナマズ
    DX9::SPRITE catfishTestSprite;

    //鯉
    DX9::SPRITE carpTestSprite;

    //プレイヤー位置
    float playerPositionX, playerPositionY;


    //障害物
    //鳥
    DX9::SPRITE birdTestSprite;
    float birdPositionX, birdPositionY;

    //岩(大)
    DX9::SPRITE bigRockTestSprite;
    float bigRockPositionX,bigRockPositionY;
    
    //岩(小)
    DX9::SPRITE smallRockTestSprite;
    float smallRockPositionX, smallRockPositionY;

    //虫
    DX9::SPRITE wormTestSprite;
    float wormPositionX, wormPositionY;

    //木
    DX9::SPRITE woodTestSprite;
    float woodPositionX, woodPositionY;

};