#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <string>

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    ZeroMemory(table_, sizeof(table_));


}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    std::string fileName[] = {
        "BoxDefault.fbx" ,
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx" ,
        "BoxWater.fbx" };

    for (int i = 0; i < 5; i++)
    {
        std::string fn = "assets/" + fileName[i];
        hModel_[i] = Model::Load(fn);
        assert(hModel_[i] >= 0);
    }


    table_[3][4].type = 1;
    table_[13][8].type = 2;
    table_[5][0].type = 3;
    table_[7][7].type = 4;

    table_[7][7].height = 2;
    table_[1][1].height = 5;
}

//更新
void Stage::Update()
{
    //ビューポート行列
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;
    XMMATRIX vp = {
        w, 0, 0, 0,
        0,-h, 0, 0,
        0, 0, 1, 0,
        w, h, 0, 1
    };

    //各行列の逆行列
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    //XMMATRIX invPrj =
    //XMMATRIX invView =

    //マウス位置（手前）
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;

    //マウス位置（奥）
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //①　mousePosFrontをベクトルに変換
    //②　①にinvVP、invPrj、invViewをかける

    //③　mousePosBackをベクトルに変換
    //④　③にinvVP、invPrj、invViewをかける

    //⑤　②から④に向かってレイをうつ（とりあえずモデル番号はhModel_[0]）

    //⑥　レイが当たったらブレークポイントで止める

}

//描画
void Stage::Draw()
{
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height+1; y++)
            {
                int type = table_[x][z].type;

                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[type], trans);
                Model::Draw(hModel_[type]);
            }
        }
    }
}

//開放
void Stage::Release()
{
}