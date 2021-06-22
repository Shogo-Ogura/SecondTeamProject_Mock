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


    //ゲージ段階
    gaugeStage = firstStage;


    //プレイヤー
    //座標
    playerPositionX = 100.0f;
    playerPositionY = 300.0f;

    //無敵時間
    carpTime = 0.0f;

    //状態
    playerStatus = goldfishState;


    //虫(アイテム)
    wormPositionX = 1500.0f;
    wormPositionY = 300.0f;


    //障害物
    //岩
    bigRockPositionX = 1500.0f;
    bigRockPositionY = 300.0f;


    //UI
    //ゲージ
    gaugeWidth = 140;
    
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


    //虫(アイテム)
    wormTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"wormTestSprite.png");


    //障害物
    //鳥
    birdTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"kingfisherTestSprite.png");

    //岩(大)
    bigRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"bigRockTestSprite.png");

    //岩(小)
    smallRockTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"smallRockTestSprite.png");

    //木
    woodTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"woodTestSprite.png");


    //UI
    //ゲージ
    gaugeTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"gaugeTestSprite.png");
    gaugeBgTestSprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"gaugeBgTestSprite.png");


    //デバッグ用
    playerStatusFont = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"ＭＳ Ｐ明朝", 20);
    gaugeStageFont = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"ＭＳ Ｐ明朝", 20);

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


    //状態遷移割当
    gaugePlayerStateAssignUpdate();
    
    //状態遷移
    gaugePlayerStateUpdate(deltaTime);
    

    //プレイヤー
    //移動範囲
    playerMoveRangeUpdate();

    //自動移動
    playerAutoMoveUpdate(deltaTime);

    //キーボード操作
    playerControlKeyboardUpdate(deltaTime);

    //パッド操作
    playerControlGamepadUpdate(deltaTime);


    //虫(アイテム)
    //移動
    wormMoveUpdate(deltaTime);


    //障害物
    //岩
   

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
    if (gaugeStage == firstStage || gaugeStage == secondStage) {
        DX9::SpriteBatch->DrawSimple(goldfishTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, -5));
    }
    //ナマズ
    if (gaugeStage == thirdStage || gaugeStage == forthStage) {
        DX9::SpriteBatch->DrawSimple(catfishTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, -5));
    }
    //鯉
    if (gaugeStage == fifthStage) {
        DX9::SpriteBatch->DrawSimple(carpTestSprite.Get(), SimpleMath::Vector3(playerPositionX, playerPositionY, -5));
    }


    //虫(アイテム)
    DX9::SpriteBatch->DrawSimple(wormTestSprite.Get(), SimpleMath::Vector3(wormPositionX, wormPositionY, 0));


    //障害物
    //鳥 
    DX9::SpriteBatch->DrawSimple(birdTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));
   
    //岩(大)
    DX9::SpriteBatch->DrawSimple(bigRockTestSprite.Get(), SimpleMath::Vector3(bigRockPositionX, bigRockPositionY, 0));
    
    //岩(小)
    DX9::SpriteBatch->DrawSimple(smallRockTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));

    //木
    DX9::SpriteBatch->DrawSimple(woodTestSprite.Get(), SimpleMath::Vector3(0, 0, 0));


    //UI
    //ゲージ
    DX9::SpriteBatch->DrawSimple(gaugeTestSprite.Get(), SimpleMath::Vector3(100, 50, 8),
        RectWH(0.0f, 0.0f, gaugeWidth, 100.0f));
    DX9::SpriteBatch->DrawSimple(gaugeBgTestSprite.Get(), SimpleMath::Vector3(100, 50, 9));


    //デバッグ用
    DX9::SpriteBatch->DrawString(playerStatusFont.Get(), SimpleMath::Vector2(0, 670), DX9::Colors::RGBA(0, 0, 0, 255), L"playerStatus:%d", playerStatus+1);
    //DX9::SpriteBatch->DrawString(gaugeStageFont.Get(), SimpleMath::Vector2(230, 670), DX9::Colors::RGBA(0, 0, 0, 255), L"gaugeStage:%d", gaugeStage+1);


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

//背景ループ
void MainScene::bgMoveUpdate(const float deltaTime)
{
    bgPositionX -= bgMoveSpeed * deltaTime;
    if (bgPositionX <= -bgResetPosition)
    {
        bgPositionX = 0;
    }
}


//状態遷移割当
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

//状態遷移
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


//プレイヤー
//移動可能範囲
void MainScene::playerMoveRangeUpdate()
{
    //上・左
    if (playerPositionY <= playerMoveRangeTop)
    {
        playerPositionY = playerMoveRangeTop;
    }
    if (playerPositionX <= playerMoveRangeLeft)
    {
        playerPositionX = playerMoveRangeLeft;
    }
    //右・下
    //金魚
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
    //ナマズ
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
    //鯉
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

//自動移動
void MainScene::playerAutoMoveUpdate(const float deltaTime)
{
    playerPositionX -= playerAutoMoveSpeed * deltaTime;
}

//キーボード操作
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

//パッド操作
void MainScene::playerControlGamepadUpdate(const float deltaTime)
{
    //十字キー操作
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

    //スティック操作
    playerPositionX += playerMoveSpeedX * DXTK->GamePadState[0].thumbSticks.leftX + deltaTime;
    playerPositionY -= playerMoveSpeedY * DXTK->GamePadState[0].thumbSticks.leftY * deltaTime;
}


//虫(アイテム)
//移動
void MainScene::wormMoveUpdate(const float deltaTime)
{
    wormPositionX -= 350 * deltaTime;

    //ループ
    if (wormPositionX <= -200)
    {
        wormPositionX = 1500;
    }
}

//虫当たり判定
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


//障害物
//障害物当たり判定
bool MainScene::birdCollisionDetectionUpdate()
{

}


//当たり判定関数
bool MainScene::CollisionDetection(Rect& rect1, Rect& rect2) {

    if (rect1.left > rect2.right || rect1.right < rect2.left ||
        rect1.top > rect2.bottom || rect1.bottom < rect2.top) {
        return false;
    }
    return true;
}