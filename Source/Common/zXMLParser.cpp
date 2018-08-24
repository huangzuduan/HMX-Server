/**
 * \brief zXMLParser类实现文件
 */
#include "SrvEngine.h"


//static void finalLibXML2() __attribute__ ((destructor));
static void finalLibXML2();
void finalLibXML2()
{
	xmlCleanupParser();
}

/**
* \brief 构造zXMLParser
*/
zXMLParser::zXMLParser()
{
	doc = NULL;
}

/**
* \brief zXMLParser的析构函数
*
* 回收分配的空间,关闭打开文件等
*/
zXMLParser::~zXMLParser()
{
	final();
}

/**
* \brief 初始化要解析的xml文件
*
*
* \param xmlFile 文件路径,绝对或者相对的。
* \return 成功返回true,失败返回false。
*/
bool zXMLParser::initFile(const std::string &xmlFile)
{
	return initFile(xmlFile.c_str());
}

/**
* \brief 初始化要解析的xml文件
* \param xmlFile 文件路径,绝对或者相对的。
* \return 成功返回true,失败返回false。
*/
bool zXMLParser::initFile(const char *xmlFile)
{
	H::logger->info("zXMLParser::initFile(%s)", xmlFile);
	final();
	if (xmlFile == NULL) return false;
	doc = xmlParseFile(xmlFile);
	return (doc != NULL);
}

/**
* \brief 初始化要解析的XML字符串
*
*
* \param xmlStr 被初始化的xml字符串。
* \return 成功返回true,失败返回false。
*/
bool zXMLParser::initStr(const std::string &xmlStr)
{
	return initStr(xmlStr.c_str());
}

/**
* \brief 初始化要解析的XML字符串
*
*
* \param xmlStr 被初始化的xml字符串。
* \return 成功返回true,失败返回false。
*/
bool zXMLParser::initStr(const char *xmlStr)
{
	final();
	if (xmlStr == NULL) return false;
	doc = xmlParseDoc((xmlChar *)xmlStr);
	return (doc != NULL);
}

/**
* \brief 初始化XML
* \return 成功返回true,失败返回false。
*/
bool zXMLParser::init()
{
	final();
	doc = xmlNewDoc((const xmlChar *)"1.0");
	return (doc != NULL);
}

/**
* \brief 释放被解析的xml文档
*
*
*/
void zXMLParser::final()
{
	if (doc)
	{
		xmlFreeDoc(doc);
		doc = NULL;
	}
}

/**
* \brief dump出XML文档
* \param s 文档存放位置
* \param format 输出时候是否格式化文档
* \return 返回s
*/
std::string & zXMLParser::dump(std::string & s, bool format)
{
	if (doc)
	{
		xmlChar *out = NULL;
		int size = 0;
		//xmlDocDumpMemory(doc,&out,&size);
		xmlDocDumpFormatMemory(doc, &out, &size, format ? 1 : 0);
		if (out != NULL)
		{
			s = (char *)out;
			xmlFree(out);
		}
	}
	return s;
}

/**
* \brief dump出某个节点
* \param dumpNode 要被Dump的节点
* \param s 文档存放位置
* \param head 是否添加xml文件头.默认true
* \return 返回s
*/
std::string & zXMLParser::dump(xmlNodePtr dumpNode, std::string & s, bool head)
{
	if (dumpNode == NULL) return s;
	xmlBufferPtr out = xmlBufferCreate();
	if (xmlNodeDump(out, doc, dumpNode, 1, 1) != -1)
	{
		if (out->content)
		{
			if (head)
			{
				s = "<?xml version=\"1.0\" encoding=\"";
				s += (char *)doc->encoding;
				s += "\"?>";
			}
			else
				s = "";
			s += (char *)out->content;
		}
	}
	xmlBufferFree(out);
	return s;
}

/**
* \brief 得到xml文档的根节点
* \param rootName 根节点的名字。
* \return 返回根节点指针,返回NULL失败。
*/
xmlNodePtr zXMLParser::getRootNode(const char *rootName)
{
	if (doc == NULL) return NULL;

	//得到根节点
	xmlNodePtr cur = xmlDocGetRootElement(doc);
	//准备起始节点
	if (rootName != NULL)
		while (cur != NULL && xmlStrcmp(cur->name, (const xmlChar *)rootName))
			cur = cur->next;
	return cur;
}

/**
* \brief 得到某个节点的子节点
*
*
* \param parent 父节点
* \param childName 子节点的名称,如果为NULL,将会得到第一个子节点。
* \return 子节点指针,返回NULL失败或者没有相应的节点。
*/
xmlNodePtr zXMLParser::getChildNode(const xmlNodePtr parent, const char *childName)
{
	if (parent == NULL) return NULL;
	xmlNodePtr retval = parent->children;
	if (childName)
		while (retval)
		{
			if (!xmlStrcmp(retval->name, (const xmlChar *)childName)) break;
			retval = retval->next;
		}
	else
		while (retval)
		{
			if (!xmlNodeIsText(retval)) break;
			retval = retval->next;
		}

	return retval;
}

/**
* \brief 得到下一个节点
*
*
* \param node 当前节点
* \param nextName 下一个节点的名字,如果为NULL,将会得到相邻的下一个节点。
* \return 下一个节点指针,返回NULL失败或者没有相应的节点。
*/
xmlNodePtr zXMLParser::getNextNode(const xmlNodePtr node, const char *nextName)
{
	if (node == NULL) return NULL;
	xmlNodePtr retval = node->next;
	if (nextName)
		while (retval)
		{
			if (!xmlStrcmp(retval->name, (const xmlChar *)nextName)) break;
			retval = retval->next;
		}
	else
		while (retval)
		{
			if (!xmlNodeIsText(retval)) break;
			retval = retval->next;
		}
	return retval;
}

/**
* \brief 统计子节点的数量
*
*
* \param parent 被统计的父节点
* \param childName 被统计子节点的名字,如果为NULL,统计所有子节点的数量
* \return 子节点的数量
*/
DWORD zXMLParser::getChildNodeNum(const xmlNodePtr parent, const char *childName)
{
	int retval = 0;
	if (parent == NULL) return retval;
	xmlNodePtr child = parent->children;
	if (childName)
		while (child)
		{
			if (!xmlStrcmp(child->name, (const xmlChar *)childName)) retval++;
			child = child->next;
		}
	else
		while (child)
		{
			if (!xmlNodeIsText(child)) retval++;
			child = child->next;
		}
	return retval;
}

/**
* \brief 为xml文档添加一个根节点
* \param rootName 根节点名称
* \return 添加节点以后,返回节点指针
*/
xmlNodePtr zXMLParser::newRootNode(const char *rootName)
{
	if (NULL == doc)
		return NULL;

	xmlNodePtr root_node = xmlNewNode(NULL, (const xmlChar *)rootName);
	xmlDocSetRootElement(doc, root_node);
	return root_node;
}

/**
* \brief 在一个节点下面添加子节点
* \param parent 父节点
* \param childName 子节点名称
* \param content 子节点内容
* \return 返回添加节点的指针
*/
xmlNodePtr zXMLParser::newChildNode(const xmlNodePtr parent, const char *childName, const char *content)
{
	if (NULL == parent)
		return NULL;

	return xmlNewChild(parent, NULL, (const xmlChar *)childName, (const xmlChar *)content);
}

bool zXMLParser::newNodeProp(const xmlNodePtr node, const char *propName, const char *prop)
{
	if (NULL == node)
		return false;

	return (NULL != xmlNewProp(node, (const xmlChar *)propName, (const xmlChar *)prop));
}

/**
* \brief 得到节点属性,并转化成数字
*
*
* \param node 对象节点
* \param propName 要得到的属性名称
* \param prop 返回结果的存储位置指针
* \param propSize prop的空间大小
* \return  成功返回true,否则返回false
*/
bool zXMLParser::getNodePropNum(const xmlNodePtr node, const char *propName, void *prop, const int propSize)
{
	char *temp = NULL;
	bool ret = true;
	if (node == NULL || prop == NULL || propName == NULL) return false;
	temp = (char *)xmlGetProp(node, (const xmlChar *)propName);
	if (temp == NULL) return false;
	switch (propSize)
	{
	case 1:
		*(BYTE*)prop = (BYTE)atoi(temp);
		break;
	case 2:
		*(WORD *)prop = (WORD)atoi(temp);
		break;
	case 4:
		*(DWORD *)prop = atoi(temp);
		break;
	case 8:
		*(QWORD *)prop = atol(temp);
		break;
	default:
		ret = false;
	}
	if (temp) xmlFree(temp);
	return ret;
}

/**
* \brief 得到节点属性
*
*
* \param node 对象节点
* \param propName 要得到的属性名称
* \param prop 返回结果的存储位置指针
* \param propSize prop的空间大小
* \return  成功返回true,否则返回false
*/
bool zXMLParser::getNodePropStr(const xmlNodePtr node, const char *propName, void *prop, int propSize)
{
	char *temp = NULL;
	bool ret = true;
	if (node == NULL || prop == NULL || propName == NULL) return false;
	temp = (char *)xmlGetProp(node, (const xmlChar *)propName);
	if (temp == NULL) return false;
	memset(prop, 0, propSize);
	strncpy((char *)prop, (const char*)temp, propSize - 1);
	if (temp) xmlFree(temp);
	return ret;
}

/**
* \brief 得到节点属性
*
*
* \param node 对象节点
* \param propName 要得到的属性名称
* \param prop 返回结果的存储位置
* \return  成功返回true,否则返回false
*/
bool zXMLParser::getNodePropStr(const xmlNodePtr node, const char *propName, std::string &prop)
{
	char *temp = NULL;
	bool ret = true;
	if (node == NULL || propName == NULL) return false;
	temp = (char *)xmlGetProp(node, (const xmlChar *)propName);
	if (temp == NULL) return false;
	prop = temp;
	if (temp) xmlFree(temp);
	return ret;
}

/**
* \brief 得到节点内容,并转化成数字
*
*
* \param node 对象节点
* \param content 返回结果的存储位置指针
* \param contentSize content的空间大小
* \return  成功返回true,否则返回false
*/
bool zXMLParser::getNodeContentNum(const xmlNodePtr node, void *content, int contentSize)
{
	char *temp = NULL;
	bool ret = true;
	if (node == NULL || content == NULL) return false;
	xmlNodePtr text = node->children;
	while (text != NULL)
	{
		if (!xmlStrcmp(text->name, (const xmlChar *) "text"))
		{
			temp = (char *)text->content;
			break;
		}
		text = text->next;
	}
	if (temp == NULL) return false;
	switch (contentSize)
	{
	case 1:
		*(BYTE*)content = (BYTE)atoi(temp);
		break;
	case 2:
		*(WORD *)content = (WORD)atoi(temp);
		break;
	case 4:
		*(DWORD *)content = atoi(temp);
		break;
	case 8:
		*(QWORD *)content = atol(temp);
		break;
	default:
		ret = false;
	}
	return ret;
}

/**
* \brief 得到节点内容
*
*
* \param node 对象节点
* \param content 返回结果的存储位置指针
* \param contentSize content的空间大小
* \return  成功返回true,否则返回false
*/
bool zXMLParser::getNodeContentStr(const xmlNodePtr node, void *content, const int contentSize)
{
	char *temp = NULL;
	bool ret = true;
	if (node == NULL || content == NULL) return false;
	xmlNodePtr text = node->children;
	while (text != NULL)
	{
		if (!xmlStrcmp(text->name, (const xmlChar *) "text"))
		{
			temp = (char *)text->content;
			break;
		}
		text = text->next;
	}
	if (temp == NULL) return false;
	memset(content, 0, contentSize);
	strncpy((char *)content, (const char *)temp, contentSize - 1);
	return ret;
}

/**
* \brief 得到节点内容
*
*
* \param node 对象节点
* \param content 返回结果的存储位置
* \return  成功返回true,否则返回false
*/
bool zXMLParser::getNodeContentStr(const xmlNodePtr node, std::string &content)
{
	char *temp = NULL;
	bool ret = true;
	if (node == NULL) return false;
	xmlNodePtr text = node->children;
	while (text != NULL)
	{
		if (!xmlStrcmp(text->name, (const xmlChar *) "text"))
		{
			temp = (char *)text->content;
			break;
		}
		text = text->next;
	}
	if (temp == NULL) return false;
	content = (char *)temp;
	return ret;
}

bool zXMLParser::getNodeContentStr(const xmlNodePtr node, std::string &content, bool head)
{
	if (node == NULL) return false;
	xmlBufferPtr out = xmlBufferCreate();
	if (xmlNodeDump(out, doc, node, 1, 1) != -1)
	{
		if (head)
		{
			content = "<?xml version=\"1.0\" encoding=\"";
			content += (char *)doc->encoding;
			content += "\"?>";
		}
		else
			content = "";
		content += (char *)out->content;
	}
	xmlBufferFree(out);
	return true;
}

//准备输入xml字符串
//返回内存指针必须手工释放
//BYTE* zXMLParser::charConv(BYTE *in, const char *fromEncoding, const char * toEncoding)
//{
//	BYTE *out;
//	size_t ret, size, out_size;
//
//	size = strlen((char *)in);
//	out_size = size * 2 + 1;
//	out = new BYTE[out_size];
//	memset(out,0,out_size);
//	if (out)
//	{
//		if (fromEncoding != NULL && toEncoding != NULL)
//		{
//			iconv_t icv_in = iconv_open(toEncoding, fromEncoding);
//			if ((iconv_t)-1 == icv_in)
//			{
//				S_SAFE_DELETE_VEC(out);
//				out = NULL;
//			}
//			else
//			{
//#ifdef WIN32
//				const char *fromtemp = (char *)in;
//#else
//				char *fromtemp = (char *)in;
//#endif
//				char *totemp = (char *)out;
//				size_t tempout = out_size - 1;
//				ret = iconv(icv_in, &fromtemp, &size, &totemp, &tempout);
//				if ((size_t)-1 == ret)
//				{
//					S_SAFE_DELETE_VEC(out);
//					out = NULL;
//				}
//				iconv_close(icv_in);
//			}
//		}
//		else
//			strncpy((char *)out, (char *)in, size);
//	}
//	return (out);
//}
