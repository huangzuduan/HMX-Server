#include "SceneEntryPk.h"

SceneEntryPk::SceneEntryPk(const SceneEntryType entrytype)
	: zSceneEntry(entrytype, SceneEntry_Hide)
{
	scene = NULL;

}


SWORD SceneEntryPk::directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify)
{

	return 0;
}

bool SceneEntryPk::AttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics, SWORD rangDamageBonus)
{
	return false;
}
