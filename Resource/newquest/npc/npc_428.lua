local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 428);

require "define820"

function visit_428(npc)
	return visit_npc(npc);
end

function state_428(npc)
	return state_npc(npc);
end