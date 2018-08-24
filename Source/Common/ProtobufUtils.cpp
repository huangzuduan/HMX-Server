#include "ProtobufUtils.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include "StringUtils.h"

namespace fogs
{
namespace protobuf
{

using namespace google::protobuf;


google::protobuf::Message * getMessageFromPool(const std::string & name)
{

    const DescriptorPool * pool = DescriptorPool::generated_pool();

    const Descriptor * msg_desc =
    		pool->FindMessageTypeByName(name);
    if (msg_desc == NULL)
    {
    	return NULL;
    }

    MessageFactory * factory = MessageFactory::generated_factory();
    if (factory == NULL)
    {
    	return NULL;
    }

    const Message * defaultMsg = factory->GetPrototype(msg_desc);
    if (defaultMsg == NULL)
    {
    	return NULL;
    }

    return defaultMsg->New();
}

bool setProtobufValue(google::protobuf::Message * msg,
		const std::string& field, const std::string& strValue)
{
	const Descriptor* desc  = msg->GetDescriptor();
	const Reflection* reflect = msg->GetReflection();
	std::string fieldName = field;
	boost::to_lower(fieldName);

	const FieldDescriptor* field_desc = desc->FindFieldByLowercaseName(fieldName);
	if (!field_desc)
	{
		return false;
	}

	switch (field_desc->type())
	{
		case  FieldDescriptor::TYPE_INT32:
		{
			int32 value = 0;
			StringUtils::toInt32(strValue, value);
			reflect->SetInt32(msg, field_desc, value);
			break;
		}
		case FieldDescriptor::TYPE_UINT32:
		{
			uint32 value = 0;
			StringUtils::toUInt32(strValue, value);
			reflect->SetUInt32(msg, field_desc, value);
			break;
		}
		case FieldDescriptor::TYPE_STRING:
		{
			reflect->SetString(msg, field_desc, strValue);
			break;
		}

		case FieldDescriptor::TYPE_INT64:
		{
			int64 value = 0;
			StringUtils::toInt64(strValue, value);
			reflect->SetInt64(msg, field_desc, value);
			break;
		}
		case FieldDescriptor::TYPE_UINT64:
		{
			uint64 value = 0;
			StringUtils::toUInt64(strValue, value);
			reflect->SetUInt64(msg, field_desc, value);
			break;
		}
		case FieldDescriptor::TYPE_ENUM:
		{
			const EnumDescriptor * enum_desc =  field_desc->enum_type();

			uint32 value = 0;
			StringUtils::toUInt32(strValue, value);
			const EnumValueDescriptor * enum_value_desc =
					enum_desc->FindValueByNumber(value);
			if (enum_value_desc != NULL)
			{
				reflect->SetEnum(msg, field_desc, enum_value_desc);
			}

			break;
		}

		default:
			return false;
	}

	return true;

}


}
}


