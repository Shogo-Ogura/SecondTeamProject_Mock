//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{
    //�R���X�g���N�^�[
    //�ϐ��̏������i0�ɂ���j

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    //�Q�[���V�[���̏�����
    //�ϐ����������i��̓I�Ȑ��l��ݒ肷��j
    //�T�E���h��ǂݍ��񂾂肷��
    
    //�w�i
    bgPositionX = 0.0f;


    //�Q�[�W�i�K
    gaugeStage = firstStage;


    //�v���C���[
    //���W
    playerPositionX = 100.0f;
    playerPositionY = 300.0f;

    //���G����
    carpTime = 0.0f;

    //���
    playerStatus = goldfishState;


    //��(�A�C�e��)
    wormPositionX = 1500.0f;
    wormPositionY = 300.0f;


    //��Q��
    //��
    bigRockPositionX = 1500.0f;
    bigRockPositionY = 300.0f;


    //UI
    //�Q�[�W
    gaugeWidth = 140;
    
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
    //�O���t�B�b�N�̐ݒ������
    //Windows10�̓h���C�o���A�b�v�f�[�g�����Ɠǂݍ��ݒ������K�v�ɂȂ�

    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, 1280.0f, 720.0f,
        D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
    };

    

    spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();


    // �O���t�B�b�N���\�[�X�̏���������

    //�w�i
    bgTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bgTestSprite.png");
    
    
    //�v���C���[
    //����
    goldfishTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"goldfishTestSprite.png");

    //�i�}�Y
    catfishTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"catfishTestSprite.png");

    //��
    carpTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"carpTestSprite.png");


    //��(�A�C�e��)
    wormTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"wormTestSprite.png");


    //��Q��
    //��
    birdTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"kingfisherTestSprite.png");

    //��(��)
    bigRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bigRockTestSprite.png");

    //��(��)
    smallRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"smallRockTestSprite.png");

    //��
    woodTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"woodTestSprite.png");


    //UI
    //�Q�[�W
    gaugeTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"gaugeTestSprite.png");
    gaugeBgTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"gaugeBgTestSprite.png");


    //�f�o�b�O�p
    playerStatusFont = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"�l�r �o����", 20);
    gaugeStageFont = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"�l�r �o����", 20);

}

// Releasing resources required for termination.
void MainScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.
    //�Q�[��(�V�[��)�I�����ɉ����������ꍇ�Ɏg��
}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{
    //�h���C�o�[�A�b�v�f�[�g�����o�����ꍇ�Ɏg��
    //�ǂݍ��݂Ȃ����O�ɉ����������ꍇ�ɉ�������
}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{
    //�T�E���h�f�o�C�X���؂�ւ��ƃT�E���h���S����~����
    //BGM�Ȃǂ��ăX�^�[�g������
}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.
    //�Q�[���𓮂����v���O�������L�q����

    //�w�i
    bgMoveUpdate(deltaTime);


    //��ԑJ�ڊ���
    gaugePlayerStateAssignUpdate();
    
    //��ԑJ��
    gaugePlayerStateUpdate(deltaTime);
    

    //�v���C���[
    //�ړ��͈�
    playerMoveRangeUpdate();

    //�����ړ�
    playerAutoMoveUpdate(deltaTime);

    //�L�[�{�[�h����
    playerControlKeyboardUpdate(deltaTime);

    //�p�b�h����
    playerControlGamepadUpdate(deltaTime);


    //��(�A�C�e��)
    //�ړ�
    wormMoveUpdate(deltaTime);


    //��Q��
    //��
   

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    //�`��̃v���O����������
    
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // �菇1

    DXTK->Direct3D9->BeginScene();    // �菇2
    DX9::SpriteBatch->Begin();        // �菇4

    // (������2D�`��̏���������)     // �菇5

    //�w�i
    DX9::SpriteBatch->DrawSimple(bgTestSprite.Get(), SimpleMath::Vector3(bgPositionX, 0, 10));


    //�v���C���[
    //����
    if (gaugeStage == firstStage || gaugeStage == secondStage) {
        DX9::SpriteBatch->DrawSimple(goldfishTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, -5));
    }
    //�i�}�Y
    if (gaugeStage == thirdStage || gaugeStage == forthStage) {
        DX9::SpriteBatch->DrawSimple(catfishTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, -5));
    }
    //��
    if (gaugeStage == fifthStage) {
        DX9::SpriteBatch->DrawSimple(carpTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, -5));
    }


    //��(�A�C�e��)
    DX9::SpriteBatch->DrawSimple(wormTestSprite.Get(), SimpleMath::Vector3(wormPositionX, wormPositionY, 0));


    //��Q��
    //�� 
    DX9::SpriteBatch->DrawSimple(birdTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));
   
    //��(��)
    DX9::SpriteBatch->DrawSimple(bigRockTestSprite.Get(), SimpleMath::Vector3(bigRockPositionX, bigRockPositionY, 0));
    
    //��(��)
    DX9::SpriteBatch->DrawSimple(smallRockTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    //��
    DX9::SpriteBatch->DrawSimple(woodTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));


    //UI
    //�Q�[�W
    DX9::SpriteBatch->DrawSimple(gaugeTestSprite.Get(), SimpleMath::Vector3(100, 50, 8),
        RectWH(0.0f, 0.0f, gaugeWidth, 100.0f));
    DX9::SpriteBatch->DrawSimple(gaugeBgTestSprite.Get(), SimpleMath::Vector3(100, 50, 9));


    //�f�o�b�O�p
    DX9::SpriteBatch->DrawString(playerStatusFont.Get(), SimpleMath::Vector2(0, 670), DX9::Colors::RGBA(0, 0, 0, 255), L"playerStatus:%d", playerStatus+1);
    //DX9::SpriteBatch->DrawString(gaugeStageFont.Get(), SimpleMath::Vector2(230, 670), DX9::Colors::RGBA(0, 0, 0, 255), L"gaugeStage:%d", gaugeStage+1);


    DX9::SpriteBatch->End();          // �菇6
    DXTK->Direct3D9->EndScene();      // �菇7

    DXTK->Direct3D9->UpdateResource();

    DXTK->ResetCommand();
    DXTK->ClearRenderTarget(Colors::CornflowerBlue);

    const auto heapes = descriptorHeap->Heap();
    DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

    spriteBatch->Begin(DXTK->CommandList);
    spriteBatch->Draw(
        dx9GpuDescriptor,
        XMUINT2(1280, 720),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}

//Update���֐��̒�`

//�w�i���[�v
void MainScene::bgMoveUpdate(const float deltaTime)
{
    bgPositionX -= bgMoveSpeed * deltaTime;
    if (bgPositionX <= -bgResetPosition)
    {
        bgPositionX = 0;
    }
}


//��ԑJ�ڊ���
void MainScene::gaugePlayerStateAssignUpdate()
{
    if (gaugeStage == firstStage || gaugeStage == secondStage) {
        playerStatus = goldfishState;
    }
    if (gaugeStage == thirdStage || gaugeStage == forthStage) {
        playerStatus = catfishState;
    }
    if (gaugeStage == fifthStage) {
        playerStatus = carpState;
    }
}

//��ԑJ��
void MainScene::gaugePlayerStateUpdate(const float deltaTime)
{
    switch (gaugeStage) {
    case firstStage:
        gaugeWidth = firstStage;
        if (wormCollisionDetectionUpdate())
        {
            gaugeStage = secondStage;
            wormPositionX = 1500;
        }
        break;
    case secondStage:
        gaugeWidth = secondStage;
        if (wormCollisionDetectionUpdate())
        {
            gaugeStage = thirdStage;
            wormPositionX = 1500;
        }
        break;
    case thirdStage:
        gaugeWidth = thirdStage;
        if (wormCollisionDetectionUpdate())
        {
            gaugeStage = forthStage;
            wormPositionX = 1500;
        }
        break;
    case forthStage:
        gaugeWidth = forthStage;
        if (wormCollisionDetectionUpdate())
        {
            gaugeStage = fifthStage;
            wormPositionX = 1500;
        }
        break;
    case fifthStage:
        gaugeWidth = fifthStage;
        carpTime += deltaTime;
        if (carpTime >= 3.0f) {
            gaugeStage = thirdStage;
            carpTime = 0.0f;
        }
    }
}


//�v���C���[
//�ړ��\�͈�
void MainScene::playerMoveRangeUpdate()
{
    //��E��
    if (playerPositionY <= playerMoveRangeTop)
    {
        playerPositionY = playerMoveRangeTop;
    }
    if (playerPositionX <= playerMoveRangeLeft)
    {
        playerPositionX = playerMoveRangeLeft;
    }
    //�E�E��
    //����
    if (playerStatus == goldfishState) {
        if (playerPositionX >= playerMoveRangeRight - goldfishScaleX)
        {
            playerPositionX = playerMoveRangeRight - goldfishScaleX;
        }
        if (playerPositionY >= playerMoveRangeBottom - goldfishScaleY)
        {
            playerPositionY = playerMoveRangeBottom - goldfishScaleY;
        }
    }
    //�i�}�Y
    if (playerStatus == catfishState) {
        if (playerPositionX >= playerMoveRangeRight - catfishScaleX)
        {
            playerPositionX = playerMoveRangeRight - catfishScaleX;
        }
        if (playerPositionY >= playerMoveRangeBottom - catfishScaleY)
        {
            playerPositionY = playerMoveRangeBottom - catfishScaleY;
        }
    }
    //��
    if (playerStatus == carpState) {
        if (playerPositionX >= playerMoveRangeRight - carpScaleX)
        {
            playerPositionX = playerMoveRangeRight - carpScaleX;
        }
        if (playerPositionY >= playerMoveRangeBottom - carpScaleY)
        {
            playerPositionY = playerMoveRangeBottom - carpScaleY;
        }
    }
}

//�����ړ�
void MainScene::playerAutoMoveUpdate(const float deltaTime)
{
    playerPositionX -= playerAutoMoveSpeed * deltaTime;
}

//�L�[�{�[�h����
void MainScene::playerControlKeyboardUpdate(const float deltaTime)
{
    if (DXTK->KeyState->D)
    {
        playerPositionX += playerMoveSpeedRight * deltaTime;
    }
    if (DXTK->KeyState->A)
    {
        playerPositionX -= playerMoveSpeedLeft * deltaTime;
    }
    if (DXTK->KeyState->W)
    {
        playerPositionY -= playerMoveSpeedUp * deltaTime;
    }
    if (DXTK->KeyState->S)
    {
        playerPositionY += playerMoveSpeedDown * deltaTime;
    }
}

//�p�b�h����
void MainScene::playerControlGamepadUpdate(const float deltaTime)
{
    //�\���L�[����
    /*if (DXTK->GamePadState[0].IsDPadRightPressed())
    {
        playerPositionX += playerMoveSpeedRight * deltaTime;
    }
    if (DXTK->GamePadState[0].IsDPadLeftPressed())
    {
        playerPositionX -= playerMoveSpeedLeft * deltaTime;
    }
    if (DXTK->GamePadState[0].IsDPadUpPressed())
    {
        playerPositionY -= playerMoveSpeedUp * deltaTime;
    }
    if (DXTK->GamePadState[0].IsDPadDownPressed())
    {
        playerPositionY += playerMoveSpeedDown * deltaTime;
    }*/

    //�X�e�B�b�N����
    playerPositionX += playerMoveSpeedX * DXTK->GamePadState[0].thumbSticks.leftX + deltaTime;
    playerPositionY -= playerMoveSpeedY * DXTK->GamePadState[0].thumbSticks.leftY * deltaTime;
}


//��(�A�C�e��)
//�ړ�
void MainScene::wormMoveUpdate(const float deltaTime)
{
    wormPositionX -= 350 * deltaTime;

    //���[�v
    if (wormPositionX <= -200)
    {
        wormPositionX = 1500;
    }
}

//�������蔻��
bool MainScene::wormCollisionDetectionUpdate()
{
    switch (playerStatus) {
    case goldfishState:
        if (CollisionDetection(RectWH(playerPositionX, playerPositionY, goldfishScaleX, goldfishScaleY), RectWH(wormPositionX, wormPositionY, wormScaleX, wormScaleY)))
            return true;
        break;
    case catfishState:
        if (CollisionDetection(RectWH(playerPositionX, playerPositionY, catfishScaleX, catfishScaleY), RectWH(wormPositionX, wormPositionY, wormScaleX, wormScaleY)))
            return true;
        break;
    case carpState:
        if (CollisionDetection(RectWH(playerPositionX, playerPositionY, carpScaleX, carpScaleY), RectWH(wormPositionX, wormPositionY, wormScaleX, wormScaleY)))
            return true;
        break;
    }

    return false;
}


//��Q��
//��Q�������蔻��
bool MainScene::birdCollisionDetectionUpdate()
{

}


//�����蔻��֐�
bool MainScene::CollisionDetection(Rect& rect1, Rect& rect2) {

    if (rect1.left > rect2.right || rect1.right < rect2.left ||
        rect1.top > rect2.bottom || rect1.bottom < rect2.top) {
        return false;
    }
    return true;
}