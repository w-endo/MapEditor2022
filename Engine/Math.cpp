#include "Math.h"

float Math::Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
    return  a.x * b.y * c.z +
            a.z * b.x * c.y +
            a.y * b.z * c.x -
            a.z * b.y * c.x -
            a.y * b.x * c.z -
            a.x * b.z * c.y;
}


//三角形とレイの交差判定
//引数：start　レイの発射位置
//引数：dir    レイの方向
//引数：v0,v1,v2   三角形の各頂点の位置
//戻値：交差してれば true
bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    //v0からv1に向かうベクトル「e01」を求める
    XMFLOAT3 e01 = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);

    //v0からv2に向かうベクトル「e02」を求める
    XMFLOAT3 e02 = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

    //「e01*u + e02*v - dir*l = start - v0」を解いてu,v,lを求める
    XMFLOAT3 d = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u = Math::Det(d, e02, dir) / Math::Det(e01, e02, dir);
    float v = Math::Det(e01, d, dir) / Math::Det(e01, e02, dir);
    float l = Math::Det(e01, e02, d) / Math::Det(e01, e02, dir);


    //u,v,lが条件に合ってたら「return true」
    if(u >= 0 && u <=1 && v >= 0 && v <= 1 && (u+v) <= 1 && l >=0)
    {
        return true;
    }

    //ダメなら「return false」
    return false;
}
