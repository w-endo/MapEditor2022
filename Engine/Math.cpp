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


//�O�p�`�ƃ��C�̌�������
//�����Fstart�@���C�̔��ˈʒu
//�����Fdir    ���C�̕���
//�����Fv0,v1,v2   �O�p�`�̊e���_�̈ʒu
//�ߒl�F�������Ă�� true
bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    //v0����v1�Ɍ������x�N�g���ue01�v�����߂�
    XMFLOAT3 e01 = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);

    //v0����v2�Ɍ������x�N�g���ue02�v�����߂�
    XMFLOAT3 e02 = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

    //�ue01*u + e02*v - dir*l = start - v0�v��������u,v,l�����߂�
    XMFLOAT3 d = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u = Math::Det(d, e02, dir) / Math::Det(e01, e02, dir);
    float v = Math::Det(e01, d, dir) / Math::Det(e01, e02, dir);
    float l = Math::Det(e01, e02, d) / Math::Det(e01, e02, dir);


    //u,v,l�������ɍ����Ă���ureturn true�v
    if(u >= 0 && u <=1 && v >= 0 && v <= 1 && (u+v) <= 1 && l >=0)
    {
        return true;
    }

    //�_���Ȃ�ureturn false�v
    return false;
}
