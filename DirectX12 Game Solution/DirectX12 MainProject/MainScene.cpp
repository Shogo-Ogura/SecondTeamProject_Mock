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
    
    //背景
    bgPositionX = 0.0f;


    //プレイヤー
    playerPositionX = 100;
    playerPositionY = 300;


    //障害物
    //岩
    bigRockPositionX = 1500;
    bigRockPositionY = 300;

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

    //背景
    bgTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bgTestSprite.png");
    
    
    //プレイヤー
    //金魚
    goldfishTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"goldfishTestSprite.png");

    //ナマズ
    catfishTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"catfishTestSprite.png");

    //鯉
    carpTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"carpTestSprite.png");

    
    //障害物
    //鳥
    birdTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"kingfisherTestSprite.png");

    //岩(大)
    bigRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bigRockTestSprite.png");

    //岩(小)
    smallRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"smallRockTestSprite.png");

    //虫
    wormTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"wormTestSprite.png");

    //木
    woodTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"woodTestSprite.png");


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

    //背景
    bgMoveUpdate(deltaTime);
    

    //プレイヤー
    playerControlUpdate(deltaTime);


    //障害物
    //岩
    bigRockPositionX -= 10;
    if (bigRockPositionX <= 500)
    {
        bigRockPositionX = 1500;
    }

    //当たり判定
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
    //描画のプログラムを書く
    
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 手順1

    DXTK->Direct3D9->BeginScene();    // 手順2
    DX9::SpriteBatch->Begin();        // 手順4

    // (ここに2D描画の処理が入る)     // 手順5

    //背景
    DX9::SpriteBatch->DrawSimple(bgTestSprite.Get(), SimpleMath::Vector3(bgPositionX, 0, 10));


    //プレイヤー
    //金魚
    DX9::SpriteBatch->DrawSimple(goldfishTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));
    //ナマズ
    DX9::SpriteBatch->DrawSimple(catfishTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, 0));
    //鯉
    DX9::SpriteBatch->DrawSimple(carpTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));


    //障害物
    //鳥 
    DX9::SpriteBatch->DrawSimple(birdTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));
   
    //岩(大)
    DX9::SpriteBatch->DrawSimple(bigRockTestSprite.Get(), SimpleMath::Vector3(bigRockPositionX, bigRockPositionY, 0));
    
    //岩(小)
    DX9::SpriteBatch->DrawSimple(smallRockTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    //虫
    DX9::SpriteBatch->DrawSimple(wormTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    //木
    DX9::SpriteBatch->DrawSimple(woodTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));



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

//Update内関数の定義

//背景
void MainScene::bgMoveUpdate(const float deltaTime)
{
    bgPositionX -= bgMoveSpeed * deltaTime;
    if (bgPositionX <= -2560)
    {
        bgPositionX = 0;
    }
}


//プレイヤー
void MainScene::playerControlUpdate(const float deltaTime)
{
    //移動範囲
    if (playerPositionX <= playerPositionLeft)
    {
        playerPositionX = playerPositionLeft;
    }
    if (playerPositionY <= playerPositionTop)
    {
        playerPositionY = playerPositionTop;
    }

    //操作
    playerPositionX -= 5;
    //キーボード
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

    //パッド
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