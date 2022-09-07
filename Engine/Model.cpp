#include <vector>
#include "Model.h"
#include "Direct3D.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx;
		Transform transform;
		std::string fileName;
	};

	std::vector<ModelData*>	models;
}

int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->fileName = fileName;
	pData->pFbx = nullptr;
	for(int i = 0; i < models.size(); i++)
	{
		if (models[i]->fileName == fileName)
		{
			pData->pFbx = models[i]->pFbx;
			break;
		}
	}

	if(pData->pFbx == nullptr)
	{
		pData->pFbx = new Fbx;
		pData->pFbx->Load(fileName);
	}


	models.push_back(pData);
	return models.size() - 1;
}

void Model::SetTransform(int hModel, Transform transform)
{
	models[hModel]->transform = transform;
}

void Model::Draw(int hModel)
{
	models[hModel]->pFbx->Draw(models[hModel]->transform);
}

void Model::Release()
{
	for (int i = 0; i < models.size(); i++)
	{
		bool isExist = false;	//¡Á‚»‚¤‚Æ‚µ‚Ä‚éFbxƒf[ƒ^‚ðŽQÆ‚µ‚Ä‚é‚â‚Â‚ª‚¢‚é‚©‚Ç‚¤‚©
		for (int j = i + 1; j < models.size(); j++)
		{
			if (models[i]->pFbx == models[j]->pFbx)
			{
				isExist = true;
				break;
			}
		}

		//‚à‚¤‚»‚Ìƒf[ƒ^‚ð’N‚àŽQÆ‚µ‚Ä‚È‚¯‚ê‚Î
		if (!isExist)
		{
			SAFE_DELETE(models[i]->pFbx);
		}

		
		SAFE_DELETE(models[i]);
	}
	models.clear();
}

void Model::RayCast(int hModel, RayCastData& rayData)
{
	//‡@ƒ[ƒ‹ƒhs—ñ‚Ì‹ts—ñ
	models[hModel]->transform.Calclation();
	XMMATRIX matInv = XMMatrixInverse(nullptr, models[hModel]->transform.GetWorldMatrix());

	//‡AƒŒƒC‚Ì’Ê‰ß“_‚ð‹‚ß‚é
	XMVECTOR pass = { rayData.start.x + rayData.dir.x, rayData.start.y + rayData.dir.y, rayData.start.z + rayData.dir.z };

	//‡BrayData.start‚É‡@‚ð‚©‚¯‚é
	XMVECTOR vStart = XMLoadFloat3(&rayData.start);
	vStart = XMVector3TransformCoord(vStart, matInv);
	XMStoreFloat3(&rayData.start, vStart);

	//‡C’Ê‰ß“_i‡Aj‚É‡@‚ð‚©‚¯‚é
	pass = XMVector3TransformCoord(pass, matInv);

	//‡DrayData.dir‚ð‡B‚©‚ç‡C‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹‚É‚·‚é
	pass = pass - vStart;
	XMStoreFloat3(&rayData.dir, pass);

	models[hModel]->pFbx->RayCast(rayData);
}
