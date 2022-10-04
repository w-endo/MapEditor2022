#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[5];

    struct
    {
        int type;
        int height;
    } table_[15][15];

    int mode_;
    int select_;



public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};