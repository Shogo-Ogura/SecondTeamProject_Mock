//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include<random>

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
    
    //スクロール速度
    enum { bgMoveSpeed = 600 };

    //背景ループ位置
    enum { bgResetPosition = 2560 };


    //プレイヤー
    //金魚
    DX9::SPRITE goldfishTestSprite;

    //ナマズ
    DX9::SPRITE catfishTestSprite;

    //鯉
    DX9::SPRITE carpTestSprite;
    float carpTime;

    //プレイヤーサイズ
    enum playerScale {
        //金魚
        goldfishScaleX = 110,
        goldfishScaleY = 70,
        //ナマズ
        catfishScaleX = 150,
        catfishScaleY = 110,
        //鯉
        carpScaleX = 200,
        carpScaleY = 150
    };

    //プレイヤー状態
    int playerStatus;
    enum playerState {
        goldfishState,
        catfishState,
        carpState
    };

    //プレイヤー座標
    float playerPositionX, playerPositionY;

    //プレイヤー自動移動速度
    enum { playerAutoMoveSpeed = 300 };

    //プレイヤー移動速度
    enum {
        //キーボード
        playerMoveSpeedUp = 550,
        playerMoveSpeedDown = 550,
        playerMoveSpeedRight = 550,
        playerMoveSpeedLeft = 550,
        //パッド
        playerMoveSpeedX = 15,
        playerMoveSpeedY = 500
    };

    //プレイヤー移動範囲
    enum playerMoveRange {
        playerMoveRangeTop = 251,
        playerMoveRangeBottom = 720,
        playerMoveRangeRight = 1280,
        playerMoveRangeLeft = 0
    };


    //虫(アイテム)
    DX9::SPRITE wormTestSprite;
    float wormPositionX, wormPositionY;
    //虫サイズ
    enum {
        wormScaleX = 80,
        wormScaleY = 70
    };


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

    //木
    DX9::SPRITE woodTestSprite;
    float woodPositionX, woodPositionY;

    //障害物サイズ
    enum obstacleScale {
        //鳥
        birdScaleX = 230,
        birdScaleY = 100,
        //岩(大)
        bigRockScaleX = 230,
        bigRockScaleY = 210,
        //岩(小)
        smallRockScaleX = 40,
        smallRockScaleY = 50,
        //木
        woodScaleX = 230,
        woodScaleY = 130
    };

    //障害物状態
    int obstacleStatus;
    enum obstacleState {
        birdState,
        bigRockState,
        smallRockState,
        woodState
    };


    //UI
    //ゲージ
    DX9::SPRITE gaugeTestSprite;
    DX9::SPRITE gaugeBgTestSprite;
    float gaugeWidth;
    int gaugeStage;
    enum gaugeState {
        firstStage = 140,
        secondStage = 280,
        thirdStage = 420,
        forthStage = 560,
        fifthStage = 700
    };


    //デバッグ用
    DX9::SPRITEFONT playerStatusFont;
    DX9::SPRITEFONT gaugeStageFont;


private:
    //Update内関数の定義

    //背景
    void bgMoveUpdate(const float deltaTime);


    //状態遷移割当
    void gaugePlayerStateAssignUpdate();

    //状態遷移
    void gaugePlayerStateUpdate(const float deltaTime);


    //プレイヤー
    //移動可能範囲
    void playerMoveRangeUpdate();
    
    //自動移動
    void playerAutoMoveUpdate(const float deltaTime);
    
    //キーボード操作
    void playerControlKeyboardUpdate(const float deltaTime);
   
    //パッド操作
    void playerControlGamepadUpdate(const float deltaTime);


    //虫(アイテム)
    //虫移動
    void wormMoveUpdate(const float deltaTime);
    
    //虫当たり判定
    bool wormCollisionDetectionUpdate();


    //障害物
    //障害物移動

    //障害物当たり判定 
    bool obstacleCollisionDetectionUpdate();


    //当たり判定関数
    //ベース当たり判定
    bool collisionDetectionBase(Rect& rect1, Rect& rect2);

    //プレイヤー範囲設定済み当たり判定
    bool PlayerCollisionDetection(Rect& rect2);

};