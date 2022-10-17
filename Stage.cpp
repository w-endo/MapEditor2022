#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Fbx.h"
#include "resource.h"
#include <string>

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    mode_(0), select_(0)
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
    if (Input::IsMouseButtonDown(0))
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
        XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
        XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

        //マウス位置（手前）
        XMFLOAT3 mousePosFront = Input::GetMousePosition();
        mousePosFront.z = 0.0f;

        //マウス位置（奥）
        XMFLOAT3 mousePosBack = Input::GetMousePosition();
        mousePosBack.z = 1.0f;

        //①　mousePosFrontをベクトルに変換
        XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);

        //②　①にinvVP、invPrj、invViewをかける
        vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invPrj * invView);

        //③　mousePosBackをベクトルに変換
        XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);

        //④　③にinvVP、invPrj、invViewをかける
        vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invPrj * invView);

        int bufX = -1, bufZ;
        float minDistance = 9999999;

        for (int x = 0; x < 15; x++)
        {
            for (int z = 0; z < 15; z++)
            {
                for (int y = 0; y < table_[x][z].height + 1; y++)
                {
                    //⑤　②から④に向かってレイをうつ（とりあえずモデル番号はhModel_[0]）
                    RayCastData data;
                    XMStoreFloat3(&data.start, vMouseFront);
                    XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

                    Transform trans;
                    trans.position_.x = x;
                    trans.position_.y = y;
                    trans.position_.z = z;
                    Model::SetTransform(hModel_[0], trans);

                    Model::RayCast(hModel_[0], data);
                    

                    //⑥　レイが当たったらブレークポイントで止める
                    if (data.hit)
                    {
                        //table_[x][z].height++;
                        //break;

                        if (minDistance > data.dist)
                        {
                            minDistance = data.dist;
                            bufX = x;
                            bufZ = z;
                        }
                    }
                }
            }
        }
        if (bufX >= 0)
        {
            switch (mode_)
            {
            case 0:
                table_[bufX][bufZ].height++;
                break;
            case 1:
                if (table_[bufX][bufZ].height > 0)
                {
                    table_[bufX][bufZ].height--;
                }
                break;
            case 2:
                table_[bufX][bufZ].type = select_;
                break;
            }
            
        }



    }
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


BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
        SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)L"草原");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)L"砂地");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_ADDSTRING, 0, (LPARAM)L"水");
        SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_SETCURSEL, 0, 0);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case IDC_RADIO_UP:
            mode_ = 0;
            return TRUE;

        case IDC_RADIO_DOWN:
            mode_ = 1;
            return TRUE;

        case IDC_RADIO_CHANGE:
            mode_ = 2;
            return TRUE;

        case IDC_COMBO_TYPE:
            select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_TYPE), CB_GETCURSEL, 0, 0);
            return TRUE;
        }
        return FALSE;

    }
    return FALSE;
}

void Stage::Save()
{
    char fileName[MAX_PATH] = "無題.map";  //ファイル名を入れる変数

    //「ファイルを保存」ダイアログの設定
    OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
        TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
    ofn.lpstrFile = (LPWSTR)fileName;               	//ファイル名
    ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
    ofn.lpstrDefExt = L"map";                  	//デフォルト拡張子

    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    //キャンセルしたら中断
    if (selFile == FALSE) return;



    HANDLE hFile;
    hFile = CreateFile(
        (LPWSTR)fileName,    //ファイル名
        GENERIC_WRITE,  //アクセスモード
        0,
        NULL,
        CREATE_ALWAYS,     //作成方法
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    std::string data = "";



    //data.length()


    DWORD bytes = 0;
    WriteFile(
        hFile,              //ファイルハンドル
        L"ABCDEF",          //保存したい文字列
        12,                  //保存する文字数
        &bytes,             //保存したサイズ
        NULL
    );



    CloseHandle(hFile);

}
