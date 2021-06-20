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


    //�v���C���[
    playerPositionX = 100;
    playerPositionY = 300;


    //��Q��
    //��
    bigRockPositionX = 1500;
    bigRockPositionY = 300;

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

    
    //��Q��
    //��
    birdTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"kingfisherTestSprite.png");

    //��(��)
    bigRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bigRockTestSprite.png");

    //��(��)
    smallRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"smallRockTestSprite.png");

    //��
    wormTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"wormTestSprite.png");

    //��
    woodTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"woodTestSprite.png");


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
    

    //�v���C���[
    playerControlUpdate(deltaTime);


    //��Q��
    //��
    bigRockPositionX -= 10;
    if (bigRockPositionX <= 500)
    {
        bigRockPositionX = 1500;
    }

    //�����蔻��
    /*if (!(playerPositionX > bigRockPositionX + 237.0f || playerPositionX + 265.0f < bigRockPositionX ||
        playerPositionY > bigRockPositionY + 200.0f || playerPositionY + 164.0f < bigRockPositionY)) 
    {
        bigRockPositionX = 1500;
    }*/


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
    DX9::SpriteBatch->DrawSimple(goldfishTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));
    //�i�}�Y
    DX9::SpriteBatch->DrawSimple(catfishTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, 0));
    //��
    DX9::SpriteBatch->DrawSimple(carpTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));


    //��Q��
    //�� 
    DX9::SpriteBatch->DrawSimple(birdTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));
   
    //��(��)
    DX9::SpriteBatch->DrawSimple(bigRockTestSprite.Get(), SimpleMath::Vector3(bigRockPositionX, bigRockPositionY, 0));
    
    //��(��)
    DX9::SpriteBatch->DrawSimple(smallRockTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    //��
    DX9::SpriteBatch->DrawSimple(wormTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    //��
    DX9::SpriteBatch->DrawSimple(woodTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));



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

//�w�i
void MainScene::bgMoveUpdate(const float deltaTime)
{
    bgPositionX -= bgMoveSpeed * deltaTime;
    if (bgPositionX <= -2560)
    {
        bgPositionX = 0;
    }
}


//�v���C���[
void MainScene::playerControlUpdate(const float deltaTime)
{
    //�ړ��͈�
    if (playerPositionX <= playerPositionLeft)
    {
        playerPositionX = playerPositionLeft;
    }
    if (playerPositionY <= playerPositionTop)
    {
        playerPositionY = playerPositionTop;
    }

    //����
    playerPositionX -= 5;
    //�L�[�{�[�h
    if (DXTK->KeyState->D)
    {
        playerPositionX += 10;
    }
    if (DXTK->KeyState->A)
    {
        playerPositionX -= 10;
    }
    if (DXTK->KeyState->W)
    {
        playerPositionY -= 10;
    }
    if (DXTK->KeyState->S)
    {
        playerPositionY += 10;
    }

    //�p�b�h
    if (DXTK->GamePadState[0].IsDPadRightPressed())
    {
        playerPositionX += 10;
    }
    if (DXTK->GamePadState[0].IsDPadLeftPressed())
    {
        playerPositionX -= 10;
    }
    if (DXTK->GamePadState[0].IsDPadUpPressed())
    {
        playerPositionY -= 10;
    }
    if (DXTK->GamePadState[0].IsDPadDownPressed())
    {
        playerPositionY += 10;
    }
}