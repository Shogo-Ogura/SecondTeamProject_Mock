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
    float carpTime;

    //�v���C���[�T�C�Y
    enum playerScale {
        //����
        goldfishScaleX = 110,
        goldfishScaleY = 70,
        //�i�}�Y
        catfishScaleX = 150,
        catfishScaleY = 110,
        //��
        carpScaleX = 200,
        carpScaleY = 150
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
        //�L�[�{�[�h
        playerMoveSpeedUp = 550,
        playerMoveSpeedDown = 550,
        playerMoveSpeedRight = 550,
        playerMoveSpeedLeft = 550,
        //�p�b�h
        playerMoveSpeedX = 15,
        playerMoveSpeedY = 500
    };

    //�v���C���[�ړ��͈�
    enum playerMoveRange {
        playerMoveRangeTop = 251,
        playerMoveRangeBottom = 720,
        playerMoveRangeRight = 1280,
        playerMoveRangeLeft = 0
    };


    //��(�A�C�e��)
    DX9::SPRITE wormTestSprite;
    float wormPositionX, wormPositionY;
    //���T�C�Y
    enum {
        wormScaleX = 80,
        wormScaleY = 70
    };


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

    //��Q���T�C�Y
    enum obstacleScale {
        //��
        birdScaleX = 230,
        birdScaleY = 100,
        //��(��)
        bigRockScaleX = 230,
        bigRockScaleY = 210,
        //��(��)
        smallRockScaleX = 40,
        smallRockScaleY = 50,
        //��
        woodScaleX = 230,
        woodScaleY = 130
    };

    //��Q�����
    int obstacleStatus;
    enum obstacleState {
        birdState,
        bigRockState,
        smallRockState,
        woodState
    };


    //UI
    //�Q�[�W
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


    //�f�o�b�O�p
    DX9::SPRITEFONT playerStatusFont;
    DX9::SPRITEFONT gaugeStageFont;


private:
    //Update���֐��̒�`

    //�w�i
    void bgMoveUpdate(const float deltaTime);


    //��ԑJ�ڊ���
    void gaugePlayerStateAssignUpdate();

    //��ԑJ��
    void gaugePlayerStateUpdate(const float deltaTime);


    //�v���C���[
    //�ړ��\�͈�
    void playerMoveRangeUpdate();
    
    //�����ړ�
    void playerAutoMoveUpdate(const float deltaTime);
    
    //�L�[�{�[�h����
    void playerControlKeyboardUpdate(const float deltaTime);
   
    //�p�b�h����
    void playerControlGamepadUpdate(const float deltaTime);


    //��(�A�C�e��)
    //���ړ�
    void wormMoveUpdate(const float deltaTime);
    
    //�������蔻��
    bool wormCollisionDetectionUpdate();


    //��Q��
    //��Q���ړ�

    //��Q�������蔻�� 
    bool obstacleCollisionDetectionUpdate();


    //�����蔻��֐�
    //�x�[�X�����蔻��
    bool collisionDetectionBase(Rect& rect1, Rect& rect2);

    //�v���C���[�͈͐ݒ�ςݓ����蔻��
    bool PlayerCollisionDetection(Rect& rect2);

};