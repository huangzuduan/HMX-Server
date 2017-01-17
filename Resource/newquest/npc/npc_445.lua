local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 445);

require "define821"

function visit_445(npc)
	return visit_npc(npc);
end

function state_445(npc)
	return state_npc(npc);
end