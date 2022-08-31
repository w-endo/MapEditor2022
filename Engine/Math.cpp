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

    //v0からv2に向かうベクトル「e02」を求める

    //「e01*u + e02*v - dir*l = start - v0」を解いてu,v,lを求める

    //u,v,lが条件に合ってたら「return true」

    //ダメなら「return false」
}
