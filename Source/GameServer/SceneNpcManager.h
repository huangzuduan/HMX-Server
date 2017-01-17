#ifndef __CREATURE_MANAGER_H
#define __CREATURE_MANAGER_H

#include "SceneEntryPk.h"
#include "UnorderedSet.h"
#include "Single.h"
#include "srvEngine.h"

#include "SceneNpc.h"


class SceneNpcManager : public Single<SceneNpcManager>
{
	typedef UNORDERED_SET<SceneNpc*> CreatureUSetType;
public:
	SceneNpcManager();
	~SceneNpcManager();
	
	// 生物体添加 
	void AddCreature(SceneNpc& rCreature);

	// 生物体消失 
	void DelCreature(SceneNpc& rCreature);

	// 更新(nTimeElapse单位:毫秒) 
	void Update(int32 nTimeElapse);

private:
	
	CreatureUSetType	m_usetCreaturies;			// 所有生物体容器 

};

#endif
