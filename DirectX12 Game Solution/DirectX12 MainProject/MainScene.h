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

    // �ϐ��̐錾

    //�w�i
    DX9::SPRITE bgTestSprite;
    float bgPositionX;

    //�v���C���[
    //����
    DX9::SPRITE goldfishTestSprite;

    //�i�}�Y
    DX9::SPRITE catfishTestSprite;

    //��
    DX9::SPRITE carpTestSprite;

    //�v���C���[�ʒu
    float playerPositionX, playerPositionY;


    //��Q��
    //��
    DX9::SPRITE birdTestSprite;
    float birdPositionX, birdPositionY;

    //��(��)
    DX9::SPRITE bigRockTestSprite;
    float bigRockPositionX,bigRockPositionY;
    
    //��(��)
    DX9::SPRITE smallRockTestSprite;
    float smallRockPositionX, smallRockPositionY;

    //��
    DX9::SPRITE wormTestSprite;
    float wormPositionX, wormPositionY;

    //��
    DX9::SPRITE woodTestSprite;
    float woodPositionX, woodPositionY;

};