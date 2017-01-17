local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 464);

require "define825"
require "define890"

function visit_464(npc)
	return visit_npc(npc);
end

function state_464(npc)
	return state_npc(npc);
end