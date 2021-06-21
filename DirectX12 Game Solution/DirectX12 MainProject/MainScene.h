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
    
    //�X�N���[�����x
    enum { bgMoveSpeed = 600 };

    //�w�i���[�v�ʒu
    enum { bgResetPosition = 2560 };


    //�v���C���[
    //����
    DX9::SPRITE goldfishTestSprite;

    //�i�}�Y
    DX9::SPRITE catfishTestSprite;

    //��
    DX9::SPRITE carpTestSprite;

    //�T�C�Y
    enum {
        //����
        goldfishX = 110,
        goldfishY = 70,
        //�i�}�Y
        catfishX = 150,
        catfishY = 110,
        //��
        carpX = 200,
        carpY = 150
    };

    //�v���C���[���
    int playerStatus;

    enum playerState {
        goldfishState,
        catfishState,
        carpState
    };

    //�v���C���[���W
    float playerPositionX, playerPositionY;

    //�v���C���[�����ړ����x
    enum { playerAutoMoveSpeed = 300 };

    //�v���C���[�ړ����x
    enum {
        playerMoveSpeedUp = 550,
        playerMoveSpeedDown = 550,
        playerMoveSpeedRight = 550,
        playerMoveSpeedLeft = 550
    };

    //�v���C���[�ړ��͈�
    enum playerMoveRange {
        playerMoveRangeTop = 251,
        playerMoveRangeBottom = 720,
        playerMoveRangeRight = 1280,
        playerMoveRangeLeft = 0,
    };


    //��(�A�C�e��)
    DX9::SPRITE wormTestSprite;
    float wormPositionX, wormPositionY;


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
    DX9::SPRITE woodTestSprite;
    float woodPositionX, woodPositionY;


private:
    //Update���֐��̒�`

    //�w�i
    void bgMoveUpdate(const float deltaTime);


    //�v���C���[
    //�ړ��\�͈�
    void playerMoveRangeUpdate(const float deltaTime);
    
    //�����ړ�
    void playerAutoMoveUpdate(const float deltaTime);
    
    //�L�[�{�[�h����
    void playerControlKeyboardUpdate(const float deltaTime);
   
    //�p�b�h����
    void playerControlGamepadUpdate(const float deltaTime);


    //��(�A�C�e��)
    //�ړ�
    void wormMoveUpdate(const float deltaTime);
    
    //�����蔻��
    void wormCollisionDetectionUpdate(const float deltaTime);


    //��Q��
    //�ړ�

    //�����蔻��
    //�� 
    void birdCollisionDetectionUpdate(const float deltaTime);
    //��(��)
    void bigRockCollisionDetectionUpdate(const float deltaTime);
    //��(��)
    void smallRockCollisionDetectionUpdate(const float deltaTime);
    //��
    void woodCollisionDetectionUpdate(const float deltaTime);



    //�����蔻��֐�
    bool CollisionDetection(Rect& rect1, Rect& rect2);
};