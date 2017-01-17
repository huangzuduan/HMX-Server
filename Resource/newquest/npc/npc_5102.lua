local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 5102);

require "define890"
require "define891"


function visit_5102(npc)
	return visit_npc(npc);
end

function state_5102(npc)
	return state_npc(npc);
end