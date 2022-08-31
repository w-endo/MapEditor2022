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

    //v0����v2�Ɍ������x�N�g���ue02�v�����߂�

    //�ue01*u + e02*v - dir*l = start - v0�v��������u,v,l�����߂�

    //u,v,l�������ɍ����Ă���ureturn true�v

    //�_���Ȃ�ureturn false�v
}
