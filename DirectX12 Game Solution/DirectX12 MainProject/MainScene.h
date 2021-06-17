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

    // ïœêîÇÃêÈåæ

    DX9::SPRITE bgTestSprite;

    DX9::SPRITE proteinSprite;
    float carpPositionX, carpPositionY;
    float carpExpansionX, carpExpansionY;


    DX9::SPRITE treeSprite;
    float treePositionX;
    float treePositionY;
    float treeExpansionX;
    float treeExpansionY;

    float treePosition2X;
    float treePosition2Y;
    float treeExpansion2X;
    float treeExpansion2Y;

    DX9::CAMERA camera;

};