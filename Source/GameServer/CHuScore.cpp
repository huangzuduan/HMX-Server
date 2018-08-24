#include "CHuScore.h"

CHuScore::CHuScore()
{

}

CHuScore::~CHuScore()
{
}

void CHuScore::Load(const std::string& filename)
{
	zXMLParser xml = zXMLParser();
	if (!xml.initFile(filename))
	{
		return ;
	}

	xmlNodePtr rootNode = xml.getRootNode("hutype");
	if (!rootNode)
	{
		return ;
	}

	xmlNodePtr typeNode = xml.getChildNode(rootNode, "type");
	while (typeNode)
	{
		MyStruct item;
		xml.getNodePropNum(typeNode, "id", &item.id, sizeof(item.id));
		xml.getNodePropNum(typeNode, "value", &item.val, sizeof(item.val));
		m_mapTypeScore.insert(std::make_pair(item.id, item.val));
		typeNode = xml.getNextNode(typeNode, "type");
	}
	return ;
}

int16_t CHuScore::GetPaiXingScore(::msg_maj::hu_type hutype) const
{
	std::map<int32_t, int32_t>::const_iterator it = m_mapTypeScore.find((int32_t)hutype);
	if (it != m_mapTypeScore.end())
	{
		return it->second;
	}
	return 0;
}