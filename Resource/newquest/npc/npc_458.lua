local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 458);

require "define822"

function visit_458(npc)
	return visit_npc(npc);
end

function state_458(npc)
	return state_npc(npc);
end