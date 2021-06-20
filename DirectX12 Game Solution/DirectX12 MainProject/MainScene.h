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

    // ΟΜιΎ

    //wi
    DX9::SPRITE bgTestSprite;
    float bgPositionX;
    enum { bgMoveSpeed = 600 };


    //vC[
    //ΰ
    DX9::SPRITE goldfishTestSprite;

    //i}Y
    DX9::SPRITE catfishTestSprite;

    //ο
    DX9::SPRITE carpTestSprite;

    enum playerState {
        goldfishState,
        catfishState,
        carpState
    };

    //vC[Κu
    float playerPositionX, playerPositionY;
    enum playerPosition {
        playerPositionTop = 251,
        playerPositionBottom,
        playerPositionRight,
        playerPositionLeft = 0,
    };


    //αQ¨
    //Ή
    DX9::SPRITE birdTestSprite;
    float birdPositionX, birdPositionY;

    //β(ε)
    DX9::SPRITE bigRockTestSprite;
    float bigRockPositionX,bigRockPositionY;
    
    //β(¬)
    DX9::SPRITE smallRockTestSprite;
    float smallRockPositionX, smallRockPositionY;

    //
    DX9::SPRITE wormTestSprite;
    float wormPositionX, wormPositionY;

    //Ψ
    DX9::SPRITE woodTestSprite;
    float woodPositionX, woodPositionY;


private:
    //UpdateΰΦΜθ`

    //wi
    void bgMoveUpdate(const float deltaTime);


    //vC[
    void playerControlUpdate(const float deltaTime);
};