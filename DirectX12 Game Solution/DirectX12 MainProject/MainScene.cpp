//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{
    //コンストラクター
    //変数の初期化（0にする）

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    //ゲームシーンの初期化
    //変数を初期化（具体的な数値を設定する）
    //サウンドを読み込んだりする

    positionX = 600.0f;
    positionY = 55.0f;

    expansionX = 1.0f;
    expansionY = 1.0f;

}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
    //グラフィックの設定をする
    //Windows10はドライバがアップデートされると読み込み直しが必要になる

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


    // グラフィックリソースの初期化処理

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
    //ゲーム(シーン)終了時に何かしたい場合に使う
}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{
    //ドライバーアップデートを検出した場合に使う
    //読み込みなおす前に何かしたい場合に何か書く
}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{
    //サウンドデバイスが切り替わるとサウンドが全部停止する
    //BGMなどを再スタートさせる
}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.
    //ゲームを動かすプログラムを記述する

    positionY += 7.5f;

    expansionX += 2.0f * deltaTime;
    expansionY += 2.0f * deltaTime;
    

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    //描画のプログラムを書く
    
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 手順1

    DXTK->Direct3D9->BeginScene();    // 手順2
    DX9::SpriteBatch->Begin();        // 手順4

    // (ここに2D描画の処理が入る)     // 手順5

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
    SPRITE型の変数.Get(),
    SimpleMath::Vector3(x座標, y座標, 重なり方),
    Rect(転送元左上x, 転送元左上y, 転送元右下x, 転送元右下y),
    DX9::Colors::RGBA(カラーマスクR, カラーマスクG, カラーマスクB, 透明値),
    SimpleMath::Vector3(x回転角, y回転角, z回転角),
    SimpleMath::Vector3(原点x座標, 原点y座標, 原点z座標),
    拡大縮小値 または SimpleMath::Vector2(x拡大縮小値, y拡大縮小値)
);*/


    DX9::SpriteBatch->End();          // 手順6
    DXTK->Direct3D9->EndScene();      // 手順7

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