#include "SceneNpc.h"

#include "UnorderedMap.h"
#include "ResourceMgr.h"
#include "SceneNpcAIController.h"

SceneNpc::SceneNpc(zNpcB* _npc, const t_NpcDefine* _define, const SceneEntryType entrytype)
	: SceneEntryPk(entrytype)
	, define(_define)
	, npc(_npc)
{

	AIC = new SceneNpcAIController(this);

	//AIC->setActRegion(define->region.c, define->width / 2, define->height / 2);
	//AIC->loadScript(define->scriptID);

}





