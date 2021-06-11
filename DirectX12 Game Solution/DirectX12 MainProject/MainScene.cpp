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

    positionX = 600.0f;
    positionY = 55.0f;

    expansionX = 1.0f;
    expansionY = 1.0f;

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

    bgTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bgTestSprite.png");
    proteinSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"protein.png");

    camera->SetPerspectiveFieldOfView(XM_PIDIV4, 16.0f / 9.0f, 1.0f, 10000.0f);

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

    positionY += 7.5f;

    expansionX += 2.0f * deltaTime;
    expansionY += 2.0f * deltaTime;
    

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

    //DX9::SpriteBatch->Draw(bgTestSprite.Get(),
    //    SimpleMath::Vector3(640.0f, 360.0f, 0.0f),
    //    Rect(0, 0, 1280, 720),
    //    DX9::Colors::RGBA(255, 255, 255, 255),
    //    SimpleMath::Vector3(XMConvertToRadians(45.0f), 0, 0),
    //    SimpleMath::Vector3(640.0f, 360.0f, 0.0f),
    //    SimpleMath::Vector2(1, 1)
    //);

    //DX9::SpriteBatch->ResetTransform();
    DX9::SpriteBatch->DrawSimple(bgTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    DX9::SpriteBatch->Draw(proteinSprite.Get(),
        SimpleMath::Vector3(positionX, positionY, 0.0f),
        Rect(0, 0, 110, 110),
        DX9::Colors::RGBA(255, 255, 255, 255),
        SimpleMath::Vector3(0, 0, 0),
        SimpleMath::Vector3(55.0f,55.0f,0.0f),
        SimpleMath::Vector2(expansionX, expansionY)
    );

        /*DX9::SpriteBatch->Draw(
    SPRITE�^�̕ϐ�.Get(),
    SimpleMath::Vector3(x���W, y���W, �d�Ȃ��),
    Rect(�]��������x, �]��������y, �]�����E��x, �]�����E��y),
    DX9::Colors::RGBA(�J���[�}�X�NR, �J���[�}�X�NG, �J���[�}�X�NB, �����l),
    SimpleMath::Vector3(x��]�p, y��]�p, z��]�p),
    SimpleMath::Vector3(���_x���W, ���_y���W, ���_z���W),
    �g��k���l �܂��� SimpleMath::Vector2(x�g��k���l, y�g��k���l)
);*/


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